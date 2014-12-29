/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CTelegramDispatcher.hpp"

#include "TelegramNamespace.hpp"
#include "CTelegramConnection.hpp"
#include "CTelegramStream.hpp"
#include "Utils.hpp"

#include <QTimer>

#include <QDebug>

// Have a copy in CTelegramConnection
static QString maskPhoneNumber(const QString &phoneNumber)
{
    if (phoneNumber.isEmpty()) {
        return QString();
    }

    // We don't want to mask "numbers" like unknown777000, so lets check if phoneNumber is consist of digits only.
    bool ok1, ok2;
    phoneNumber.mid(0, phoneNumber.size() / 2).toInt(&ok1);

    if (ok1) {
        phoneNumber.mid(phoneNumber.size() / 2).toInt(&ok2);
    }

    if (ok1 && ok2) {
        // Expected something like: 55xxxxxxxx (hidden).
        return phoneNumber.mid(0, phoneNumber.size() / 4) + QString(phoneNumber.size() - phoneNumber.size() / 4, QLatin1Char('x')); // + QLatin1String(" (hidden)");
    } else {
        return phoneNumber;
    }
}

// Have a copy in CTelegramConnection
static QStringList maskPhoneNumberList(const QStringList &list)
{
    if (list.count() == 1) {
        return QStringList() << maskPhoneNumber(list.first());
    }

    QStringList result;

    const int listDigits = QString::number(list.count()).size();

    foreach (const QString &number, list) {
        if (number.length() >= 5 + listDigits) {
            QString masked = QString(QLatin1String("%1xx%2%3")).arg(number.mid(0, 2)).arg(list.indexOf(number), listDigits, 10, QLatin1Char('0')).arg(QString(number.length() - 4 - listDigits, QLatin1Char('x')));
            result.append(masked);
        } else { // fallback
            result.append(maskPhoneNumber(number) + QLatin1String(" (fallback)"));
        }
    }

    return result;
}

const quint32 secretFormatVersion = 2;
const int s_userTypingActionPeriod = 6000; // 6 sec
const int s_localTypingActionPeriod = 5000; // 5 sec

#if QT_VERSION < 0x050000
const int s_timerMaxInterval = 500; // 0.5 sec. Needed to limit max possible typing time deviation in Qt4 by this value.
#endif

CTelegramDispatcher::CTelegramDispatcher(QObject *parent) :
    QObject(parent),
    m_appInformation(0),
    m_initState(InitNothing),
    m_isAuthenticated(false),
    m_activeDc(0),
    m_wantedActiveDc(0),
    m_updatesStateIsLocked(false),
    m_emitOnlyIncomingUnreadMessages(true),
    m_selfUserId(0),
    m_typingUpdateTimer(new QTimer(this))
{
    m_typingUpdateTimer->setSingleShot(true);
    connect(m_typingUpdateTimer, SIGNAL(timeout()), SLOT(whenUserTypingTimerTimeout()));
}

CTelegramDispatcher::~CTelegramDispatcher()
{
    qDeleteAll(m_connections);
    qDeleteAll(m_users);
}

void CTelegramDispatcher::setAppInformation(const CAppInformation *newAppInfo)
{
    m_appInformation = newAppInfo;
}

bool CTelegramDispatcher::isConnected() const
{
    return activeConnection() && !m_dcConfiguration.isEmpty();
}

bool CTelegramDispatcher::isAuthenticated() const
{
    return isConnected() && m_isAuthenticated;
}

void CTelegramDispatcher::addContacts(const QStringList &phoneNumbers, bool replace)
{
    qDebug() << "addContacts" << maskPhoneNumberList(phoneNumbers);
    if (activeConnection()) {
        TLVector<TLInputContact> contactsVector;
        for (int i = 0; i < phoneNumbers.count(); ++i) {
            TLInputContact contact;
            contact.clientId = i;
            contact.phone = phoneNumbers.at(i);
            contactsVector.append(contact);
        }
        activeConnection()->contactsImportContacts(contactsVector, replace);
    } else {
        qDebug() << Q_FUNC_INFO << "No active connection.";
    }
}

void CTelegramDispatcher::deleteContacts(const QStringList &phoneNumbers)
{
    qDebug() << Q_FUNC_INFO << maskPhoneNumberList(phoneNumbers);

    QVector<TLInputUser> users;
    users.reserve(phoneNumbers.count());

    foreach (const QString &phoneNumber, phoneNumbers) {
        TLInputUser inputUser = phoneNumberToInputUser(phoneNumber);
        if (inputUser.tlType != InputUserEmpty) {
            users.append(inputUser);
        }
    }

    if (!users.isEmpty()) {
        activeConnection()->contactsDeleteContacts(users);
    }
}

QByteArray CTelegramDispatcher::connectionSecretInfo() const
{
    if (!activeConnection()) {
        return QByteArray();
    }

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << secretFormatVersion;
    outputStream << activeConnection()->deltaTime();
    outputStream << activeConnection()->dcInfo();
    outputStream << m_selfPhone;
    outputStream << activeConnection()->authKey();
    outputStream << activeConnection()->authId();
    outputStream << activeConnection()->serverSalt();
    outputStream << m_updatesState.pts;
    outputStream << m_updatesState.qts;
    outputStream << m_updatesState.date;
    outputStream << m_chatIds;

    return output;
}

void CTelegramDispatcher::initConnection(const QString &address, quint32 port)
{
    TLDcOption dcInfo;
    dcInfo.ipAddress = address;
    dcInfo.port = port;

    m_updatesState.pts = 1;
    m_updatesState.qts = 1;
    m_updatesState.date = 1;
    m_chatIds.clear();

    CTelegramConnection *connection = createConnection(dcInfo);

    m_connections.insert(0, connection);

    initConnectionSharedFinal();
}

bool CTelegramDispatcher::restoreConnection(const QByteArray &secret)
{
    CTelegramStream inputStream(secret);

    quint32 format;
    qint32 deltaTime;
    TLDcOption dcInfo;
    QByteArray authKey;
    quint64 authId;
    quint64 serverSalt;

    inputStream >> format;

    if (format > secretFormatVersion) {
        qDebug() << "Unknown format version";
        return false;
    }

    inputStream >> deltaTime;
    inputStream >> dcInfo;
    inputStream >> m_selfPhone;
    inputStream >> authKey;
    inputStream >> authId;
    inputStream >> serverSalt;

    if (format >= 1) {
        inputStream >> m_updatesState.pts;
        inputStream >> m_updatesState.qts;
        inputStream >> m_updatesState.date;
    } else {
        m_updatesState.pts = 1;
        m_updatesState.qts = 1;
        m_updatesState.date = 1;
    }

    m_chatIds.clear();

    if (format >= 2) {
        inputStream >> m_chatIds;
    }

    CTelegramConnection *connection = createConnection(dcInfo);

    connection->setDeltaTime(deltaTime);
    connection->setAuthKey(authKey);
    connection->setServerSalt(serverSalt);

    if (connection->authId() != authId) {
        qDebug() << "Invalid auth data.";
        delete connection;
        return false;
    }

    m_connections.insert(dcInfo.id, connection);

    initConnectionSharedFinal(dcInfo.id);

    return true;
}

void CTelegramDispatcher::initConnectionSharedFinal(quint32 activeDc)
{
    m_initState = InitNothing;
    m_isAuthenticated = false;
    setActiveDc(activeDc);
    m_updatesStateIsLocked = false;
    m_selfUserId = 0;

    m_actualState = TLUpdatesState();

    activeConnection()->connectToDc();
}

void CTelegramDispatcher::closeConnection()
{
    foreach (CTelegramConnection *o, m_connections) {
        o->disconnect(this);
        o->deleteLater();
    }

    m_isAuthenticated = false;
    m_connections.clear();
    m_dcConfiguration.clear();
    m_delayedPackages.clear();
    qDeleteAll(m_users);
    m_users.clear();
    m_messagesMap.clear();
    m_contactList.clear();
    m_requestedFiles.clear();
    m_userTypingMap.clear();
    m_userChatTypingMap.clear();
    m_localTypingMap.clear();
    m_localChatTypingMap.clear();
    m_chatIds.clear();
    m_temporaryChatIdMap.clear();
    m_chatInfo.clear();
    m_chatFullInfo.clear();
}

void CTelegramDispatcher::requestPhoneStatus(const QString &phoneNumber)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->authCheckPhone(phoneNumber);
}

void CTelegramDispatcher::signIn(const QString &phoneNumber, const QString &authCode)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->signIn(phoneNumber, authCode);
}

void CTelegramDispatcher::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->signUp(phoneNumber, authCode, firstName, lastName);
}

void CTelegramDispatcher::requestPhoneCode(const QString &phoneNumber)
{
    if (!activeConnection()) {
        qDebug() << "Can't request phone code: there is no active connection.";
        return;
    }

    if (m_dcConfiguration.isEmpty()) {
        qDebug() << "Can't request phone code: DC Configuration is unknown.";
        return;
    }

    activeConnection()->requestPhoneCode(phoneNumber);
}

void CTelegramDispatcher::requestContactAvatar(const QString &phoneNumber)
{
    qDebug() << Q_FUNC_INFO << maskPhoneNumber(phoneNumber);

    const TLUser *user = phoneNumberToUser(phoneNumber);
    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unknown user" << maskPhoneNumber(phoneNumber);
        return;
    }

    if (user->photo.tlType == UserProfilePhotoEmpty) {
        qDebug() << Q_FUNC_INFO << "User" << maskPhoneNumber(phoneNumber) << "have no avatar";
        return;
    }

    TLFileLocation avatarLocation = user->photo.photoSmall;

    if (avatarLocation.tlType == FileLocationUnavailable) {
        qDebug() << Q_FUNC_INFO << "Contact" << maskPhoneNumber(phoneNumber) << "avatar is not available";
        return;
    }

    TLInputFileLocation inputFile;
    inputFile.volumeId = avatarLocation.volumeId;
    inputFile.localId  = avatarLocation.localId;
    inputFile.secret   = avatarLocation.secret;

    requestFile(inputFile, avatarLocation.dcId, user->id);
    qDebug() << Q_FUNC_INFO << "Requested avatar for user " << maskPhoneNumber(phoneNumber);
}

quint64 CTelegramDispatcher::sendMessageToContact(const QString &phone, const QString &message)
{
    if (!activeConnection()) {
        return 0;
    }
    const TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(phone);
        return 0;
    }

    if (m_localTypingMap.contains(phone)) {
        m_localTypingMap.remove(phone);
    }

    return sendMessages(peer, message);
}

quint64 CTelegramDispatcher::sendMessageToChat(quint32 publicChatId, const QString &message)
{
    if (!activeConnection()) {
        return 0;
    }
    const TLInputPeer peer = publicChatIdToInputPeer(publicChatId);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve chat" << publicChatId;
        return 0;
    }

    if (m_localChatTypingMap.contains(publicChatId)) {
        m_localChatTypingMap.remove(publicChatId);
    }

    return sendMessages(peer, message);
}

quint64 CTelegramDispatcher::sendMessages(const TLInputPeer &peer, const QString &message)
{
    quint64 randomMessageId;
    Utils::randomBytes(&randomMessageId);

    // Probably we have to implement GZip packing to fix this bug.
    if (message.length() > 400) {
        qDebug() << Q_FUNC_INFO << "Can not send such long message due to a bug. Current maximum length is 400 characters.";
        return 0;
    }

    if (message.length() > 4095) { // 4096 - 1
        qDebug() << Q_FUNC_INFO << "Can not send such long message due to server limitation. Current maximum length is 4095 characters.";
        return 0;
    }

    activeConnection()->messagesSendMessage(peer, message, randomMessageId);

    return randomMessageId;
}

quint32 CTelegramDispatcher::createChat(const QStringList &phones, const QString chatName)
{
    if (!activeConnection()) {
        return 0;
    }
    TLVector<TLInputUser> users;

    foreach (const QString &phone, phones) {
        const TLInputUser user = phoneNumberToInputUser(phone);
        users.append(user);
    }

    quint32 publicChatId = insertTelegramChatId(0); // Real telegram id is not known at this moment.
    quint64 apiCallId = activeConnection()->messagesCreateChat(users, chatName);

    m_temporaryChatIdMap.insert(apiCallId, publicChatId);

    return publicChatId;
}

void CTelegramDispatcher::setTyping(const QString &phone, bool typingStatus)
{
    if (!activeConnection()) {
        return;
    }
    if (typingStatus == m_localTypingMap.contains(phone)) {
        return; // Avoid flood
    }

    TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(phone);
        return;
    }

    TLSendMessageAction action;
    if (typingStatus) {
        action.tlType = SendMessageTypingAction;
    } else {
        action.tlType = SendMessageCancelAction;
    }

    activeConnection()->messagesSetTyping(peer, action);

    m_localTypingMap.insert(phone, s_localTypingActionPeriod);
    ensureTypingUpdateTimer(s_localTypingActionPeriod);
}

void CTelegramDispatcher::setChatTyping(quint32 publicChatId, bool typingStatus)
{
    if (!activeConnection()) {
        return;
    }
    if (typingStatus == m_localChatTypingMap.contains(publicChatId)) {
        return; // Avoid flood
    }

    const TLInputPeer peer = publicChatIdToInputPeer(publicChatId);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve chat" << publicChatId;
        return;
    }

    TLSendMessageAction action;
    if (typingStatus) {
        action.tlType = SendMessageTypingAction;
    } else {
        action.tlType = SendMessageCancelAction;
    }

    activeConnection()->messagesSetTyping(peer, action);

    m_localChatTypingMap.insert(publicChatId, s_localTypingActionPeriod);
    ensureTypingUpdateTimer(s_localTypingActionPeriod);
}

void CTelegramDispatcher::setMessageRead(const QString &phone, quint32 messageId)
{
    if (!activeConnection()) {
        return;
    }
    const TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType != InputPeerEmpty) {
        activeConnection()->messagesReadHistory(peer, messageId, /* offset */ 0, /* readContents */ false);
    }
}

void CTelegramDispatcher::setOnlineStatus(bool onlineStatus)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->accountUpdateStatus(!onlineStatus); // updateStatus accepts bool "offline"
}

TelegramNamespace::ContactStatus CTelegramDispatcher::contactStatus(const QString &phone) const
{
    const TLUser *user = phoneNumberToUser(phone);

    if (user) {
        return decodeContactStatus(user->status.tlType);
    }

    return TelegramNamespace::ContactStatusUnknown;
}

QString CTelegramDispatcher::contactFirstName(const QString &phone) const
{
    const TLUser *user = phoneNumberToUser(phone);

    if (user) {
        return user->firstName;
    } else {
        return QString();
    }
}

QString CTelegramDispatcher::contactLastName(const QString &phone) const
{
    const TLUser *user = phoneNumberToUser(phone);

    if (user) {
        return user->lastName;
    } else {
        return QString();
    }
}

QString CTelegramDispatcher::contactAvatarToken(const QString &identifier) const
{
    const TLUser *user = phoneNumberToUser(identifier);

    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unknown identifier" << maskPhoneNumber(identifier);
        return QString();
    }

    return userAvatarToken(user);
}

QString CTelegramDispatcher::chatTitle(quint32 publicChatId) const
{
    if (!havePublicChatId(publicChatId)) {
        return QString();
    }

    const quint32 chatId = m_chatIds.at(publicChatId);

    if (!m_chatInfo.contains(chatId)) {
        return QString();
    }

    return m_chatInfo.value(chatId).title;
}

QStringList CTelegramDispatcher::chatParticipants(quint32 publicChatId) const
{
    if (!havePublicChatId(publicChatId)) {
        return QStringList();
    }

    const quint32 chatId = m_chatIds.at(publicChatId);

    if (!m_chatFullInfo.contains(chatId)) {
        return QStringList();
    }

    const TLChatFull &fullChat = m_chatFullInfo.value(chatId);

    QStringList result;

    foreach (const TLChatParticipant &participant, fullChat.participants.participants) {
        result.append(userIdToIdentifier(participant.userId));
    }

    return result;
}

bool CTelegramDispatcher::getChatInfo(TelegramNamespace::GroupChat *outputChat, quint32 publicChatId) const
{
    if (!havePublicChatId(publicChatId)) {
        return false;
    }

    const quint32 chatId = m_chatIds.at(publicChatId);

    if (!chatId) {
        // Probably: New chat created, but telegram id is not known yet.
        return false;
    }

    if (!m_chatInfo.contains(chatId)) {
        return false;
    }

    if (!outputChat) {
        return false;
    }

    const TLChat &chat = m_chatInfo.value(chatId);
    outputChat->id = publicChatId;
    outputChat->title = chat.title;
    outputChat->participantsCount = chat.participantsCount;

    return true;
}

bool CTelegramDispatcher::getChatParticipants(QStringList *participants, quint32 publicChatId)
{
    if (!havePublicChatId(publicChatId)) {
        return false;
    }

    const quint32 chatId = m_chatIds.at(publicChatId);

    if (!chatId) {
        // Probably: New chat created, but telegram id is not known yet.
        return false;
    }

    participants->clear();

    if (m_chatFullInfo.contains(chatId)) {
        const TLChatFull &fullChat = m_chatFullInfo.value(chatId);

        foreach (const TLChatParticipant &participant, fullChat.participants.participants) {
            participants->append(userIdToIdentifier(participant.userId));
        }
        return true;
    } else {
        activeConnection()->messagesGetFullChat(chatId);
    }

    return true;
}

void CTelegramDispatcher::whenSelfPhoneReceived(const QString &phone)
{
    m_selfPhone = phone;
}

void CTelegramDispatcher::whenUsersReceived(const QVector<TLUser> &users)
{
    foreach (const TLUser &user, users) {
        TLUser *existsUser = m_users.value(user.id);

        if (existsUser) {
            *existsUser = user;
        } else {
            m_users.insert(user.id, new TLUser(user));
        }

        if (user.tlType == UserSelf) {
            m_selfUserId = user.id;
            m_selfPhone = user.phone;

            continueInitialization(InitKnowSelf);
        }
    }
}

void CTelegramDispatcher::whenContactListReceived(const QStringList &contactList)
{
    qDebug() << Q_FUNC_INFO << maskPhoneNumberList(contactList);

    QStringList newContactList = contactList;
    newContactList.sort();

    if (m_contactList != newContactList) {
        m_contactList = newContactList;
        emit contactListChanged();
    }

    continueInitialization(InitHaveContactList);
}

void CTelegramDispatcher::whenContactListChanged(const QStringList &added, const QStringList &removed)
{
    QStringList newContactList = m_contactList;

    newContactList.append(added);
    newContactList.removeDuplicates();

    foreach (const QString &contact, removed) {
        newContactList.removeAll(contact);
    }

    newContactList.sort();

    if (m_contactList != newContactList) {
        m_contactList = newContactList;
        emit contactListChanged();
    }
}

void CTelegramDispatcher::whenUserTypingTimerTimeout()
{

#if QT_VERSION >= 0x050000
    int minTime = s_userTypingActionPeriod;
#else
    int minTime = s_timerMaxInterval;
#endif

    const QList<quint32> users = m_userTypingMap.keys();
    foreach (quint32 userId, users) {
        int timeRemains = m_userTypingMap.value(userId) - m_typingUpdateTimer->interval();
        if (timeRemains < 5) { // Let 5 ms be allowed correction
            m_userTypingMap.remove(userId);
            emit contactTypingStatusChanged(userIdToIdentifier(userId), /* typingStatus */ false);
        } else {
            m_userTypingMap.insert(userId, timeRemains);
            if (minTime > timeRemains) {
                minTime = timeRemains;
            }
        }
    }

    const QList<QPair<quint32, quint32> > usersInChat = m_userChatTypingMap.keys();
    QPair<quint32, quint32> userInChat;
    foreach (userInChat, usersInChat) {
        int timeRemains = m_userChatTypingMap.value(userInChat) - m_typingUpdateTimer->interval();
        if (timeRemains < 5) { // Let 5 ms be allowed correction
            m_userChatTypingMap.remove(userInChat);
            emit contactChatTypingStatusChanged(userInChat.first, userIdToIdentifier(userInChat.second), /* typingStatus */ false);
        } else {
            m_userChatTypingMap.insert(userInChat, timeRemains);
            if (minTime > timeRemains) {
                minTime = timeRemains;
            }
        }
    }

    const QList<QString> phones = m_localTypingMap.keys();
    foreach (const QString &phone, phones) {
        int timeRemains = m_localTypingMap.value(phone) - m_typingUpdateTimer->interval();
        if (timeRemains < 5) { // Let 5 ms be allowed correction
            m_localTypingMap.remove(phone);
            setTyping(phone, false);
        } else {
            m_localTypingMap.insert(phone, timeRemains);
            if (minTime > timeRemains) {
                minTime = timeRemains;
            }
        }
    }

    const QList<quint32> chats = m_localChatTypingMap.keys();
    foreach (quint32 chat, chats) {
        int timeRemains = m_localChatTypingMap.value(chat) - m_typingUpdateTimer->interval();
        if (timeRemains < 5) { // Let 5 ms be allowed correction
            m_localChatTypingMap.remove(chat);
            setChatTyping(chat, false);
        } else {
            m_localChatTypingMap.insert(chat, timeRemains);
            if (minTime > timeRemains) {
                minTime = timeRemains;
            }
        }
    }

    if (!m_userTypingMap.isEmpty() || !m_userChatTypingMap.isEmpty() || !m_localTypingMap.isEmpty() || !m_localChatTypingMap.isEmpty()) {
        m_typingUpdateTimer->start(minTime);
    }
}

void CTelegramDispatcher::whenStatedMessageReceived(const TLMessagesStatedMessage &statedMessage, quint64 messageId)
{
    qDebug() << Q_FUNC_INFO << m_temporaryChatIdMap;

    ensureUpdateState(statedMessage.pts, statedMessage.seq);

    if (m_temporaryChatIdMap.contains(messageId)) {
        if (statedMessage.chats.isEmpty()) {
            qDebug() << "Stated message expected to have chat id, but it haven't";
            return;
        }

        const quint32 publicChatId = m_temporaryChatIdMap.take(messageId);
        if (!havePublicChatId(publicChatId)) {
            qDebug() << Q_FUNC_INFO << "Unexpected stated message public id " << publicChatId << " for chat " << statedMessage.chats.first().id;
        } else {
            m_chatIds[publicChatId] = statedMessage.chats.first().id;
            qDebug() << Q_FUNC_INFO << "public chat id " << publicChatId << " resolved to " << statedMessage.chats.first().id;
        }
    }
}

void CTelegramDispatcher::whenMessageSentInfoReceived(const TLInputPeer &peer, quint64 randomId, quint32 messageId, quint32 pts, quint32 date, quint32 seq)
{
    const QString phone = userIdToIdentifier(peer.userId);
    QPair<QString, quint64> phoneAndId(phone, randomId);

    m_messagesMap.insert(messageId, phoneAndId);

    emit sentMessageStatusChanged(phoneAndId.first, phoneAndId.second, TelegramNamespace::MessageDeliveryStatusSent);

    ensureUpdateState(pts, seq, date);
}

void CTelegramDispatcher::getDcConfiguration()
{
    activeConnection()->getConfiguration();
}

void CTelegramDispatcher::getSelfUser()
{
    if (!m_selfUserId) {
        TLInputUser selfUser;
        selfUser.tlType = InputUserSelf;
        activeConnection()->usersGetUsers(QVector<TLInputUser>() << selfUser); // Get self-info
    }
}

void CTelegramDispatcher::getUser(quint32 id)
{
    TLInputUser user;
    user.tlType = InputUserContact;
    user.userId = id;
    activeConnection()->usersGetUsers(QVector<TLInputUser>() << user);
}

void CTelegramDispatcher::getInitialUsers()
{
    QVector<TLInputUser> users;

    TLInputUser user;

    user.tlType = InputUserSelf;
    users << user;

    user.tlType = InputUserContact;
    user.userId = 777000;
    users << user;

    activeConnection()->usersGetUsers(users);
}

void CTelegramDispatcher::getContacts()
{
    activeConnection()->contactsGetContacts(QString()); // Empty hash argument for now.
}

void CTelegramDispatcher::getChatsInfo()
{
    if (m_chatIds.isEmpty()) {
        continueInitialization(InitKnowChats);
    } else {
        activeConnection()->messagesGetChats(m_chatIds);
    }
}

void CTelegramDispatcher::getUpdatesState()
{
    m_updatesStateIsLocked = true;
    activeConnection()->updatesGetState();
}

void CTelegramDispatcher::whenUpdatesStateReceived(const TLUpdatesState &updatesState)
{
    m_actualState = updatesState;
    checkStateAndCallGetDifference();
}

// Should be called via checkStateAndCallGetDifference()
void CTelegramDispatcher::getDifference()
{
    activeConnection()->updatesGetDifference(m_updatesState.pts, m_updatesState.date, m_updatesState.qts);
}

void CTelegramDispatcher::whenUpdatesDifferenceReceived(const TLUpdatesDifference &updatesDifference)
{
    switch (updatesDifference.tlType) {
    case UpdatesDifference:
    case UpdatesDifferenceSlice:
        qDebug() << Q_FUNC_INFO << "UpdatesDifference" << updatesDifference.newMessages.count();
        foreach (const TLChat &chat, updatesDifference.chats) {
            updateChat(chat);
        }

        foreach (const TLMessage &message, updatesDifference.newMessages) {
//            qDebug() << "added message" << message.message;
            if (message.tlType != Message) {
                continue;
            }
            if (m_emitOnlyIncomingUnreadMessages) {
                if ((message.flags & MessageFlagOut) || !(message.flags & MessageFlagUnread)) {
                    continue;
                }
            }
            emit messageReceived(userIdToIdentifier(message.fromId), message.message, message.id);
        }
        if (updatesDifference.tlType == UpdatesDifference) {
            m_updatesState = updatesDifference.state;
        } else { // UpdatesDifferenceSlice
            m_updatesState = updatesDifference.intermediateState;
        }
        break;
    case UpdatesDifferenceEmpty:
        qDebug() << Q_FUNC_INFO << "UpdatesDifferenceEmpty";

        // Try to update actual and local state in this weird case.
        QTimer::singleShot(10, this, SLOT(getUpdatesState()));
        return;
        break;
    default:
        qDebug() << Q_FUNC_INFO << "unknown diff type:" << QString::number(updatesDifference.tlType, 16);
        break;
    }

    checkStateAndCallGetDifference();
}

void CTelegramDispatcher::whenMessagesChatsReceived(const QVector<TLChat> &chats)
{
    qDebug() << Q_FUNC_INFO << chats.count();

    foreach (const TLChat &chat, chats) {
        updateChat(chat);
    }

    continueInitialization(InitKnowChats);
}

// fileId is program-specific handler, not related to Telegram.
void CTelegramDispatcher::requestFile(const TLInputFileLocation &location, quint32 dc, quint32 fileId)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && (connection->authState() == CTelegramConnection::AuthStateSignedIn)) {
        connection->getFile(location, fileId);
    } else {
        m_requestedFiles.insertMulti(dc, SRequestedFile(location, fileId));
        ensureSignedConnection(dc);
    }
}

void CTelegramDispatcher::processUpdate(const TLUpdate &update)
{
    switch (update.tlType) {
    case UpdateNewMessage:
        qDebug() << "UpdateNewMessage";
        qDebug() << "from:" << update.message.fromId;
        qDebug() << "fwdFromId:" << update.message.fwdFromId;
        qDebug() << "to type:" << update.message.toId.tlType;
        qDebug() << "to userId:" << update.message.toId.userId;
        qDebug() << "to chatId:" << update.message.toId.chatId;
        qDebug() << "message:" << update.message.message;
        ensureUpdateState(update.pts);
        break;
//    case UpdateMessageID:
//        update.id;
//        update.randomId;
//        break;
    case UpdateReadMessages:
        foreach (quint32 messageId, update.messages) {
            const QPair<QString, quint64> phoneAndId = m_messagesMap.value(messageId);
            emit sentMessageStatusChanged(phoneAndId.first, phoneAndId.second, TelegramNamespace::MessageDeliveryStatusRead);
        }
        ensureUpdateState(update.pts);
        break;
//    case UpdateDeleteMessages:
//        update.messages;
//        ensureUpdateState(update.pts);
//        break;
//    case UpdateRestoreMessages:
//        update.messages;
//        ensureUpdateState(update.pts);
//        break;
    case UpdateUserTyping:
        if (m_users.contains(update.userId)) {
            emit contactTypingStatusChanged(userIdToIdentifier(update.userId), /* typingStatus */ true);
#if QT_VERSION >= 0x050000
            m_userTypingMap.insert(update.userId, m_typingUpdateTimer->remainingTime() + s_userTypingActionPeriod);
#else
            m_userTypingMap.insert(update.userId, s_userTypingActionPeriod); // Missed timer remaining time method can leads to typing time period deviation.
#endif
            ensureTypingUpdateTimer(s_userTypingActionPeriod);
        }
        break;
    case UpdateChatUserTyping:
        if (m_users.contains(update.userId)) {
            emit contactChatTypingStatusChanged(telegramChatIdToPublicId(update.chatId), userIdToIdentifier(update.userId), /* typingStatus */ true);
            const QPair<quint32,quint32> key(telegramChatIdToPublicId(update.chatId), update.userId);
#if QT_VERSION >= 0x050000
            m_userChatTypingMap.insert(key, m_typingUpdateTimer->remainingTime() + s_userTypingActionPeriod);
#else
            m_userChatTypingMap.insert(key, s_userTypingActionPeriod); // Missed timer remaining time method can leads to typing time period deviation.
#endif
            ensureTypingUpdateTimer(s_userTypingActionPeriod);
        }
        break;
    case UpdateChatParticipants: {
        TLChatFull newChatState = m_chatFullInfo.value(update.participants.chatId);
        newChatState.id = update.participants.chatId; // newChatState can be newly created emtpy chat
        newChatState.participants = update.participants;
        updateFullChat(newChatState);

        qDebug() << "chat id resolved to" << update.participants.chatId;
        break;
    }
    case UpdateUserStatus: {
        TLUser *user = m_users.value(update.userId);
        if (user) {
            user->status = update.status;
            emit contactStatusChanged(user->phone, decodeContactStatus(user->status.tlType));
        }
        break;
    }
//    case UpdateUserName:
//        update.userId;
//        update.firstName;
//        update.lastName;
//        break;
//    case UpdateUserPhoto:
//        update.userId;
//        update.date;
//        update.photo;
//        update.previous;
//        break;
//    case UpdateContactRegistered:
//        update.userId;
//        update.date;
//        break;
//    case UpdateContactLink:
//        update.userId;
//        update.myLink;
//        update.foreignLink;
//        break;
//    case UpdateActivation:
//        update.userId;
//        break;
//    case UpdateNewAuthorization:
//        update.authKeyId;
//        update.date;
//        update.device;
//        update.location;
//        break;
//    case UpdateNewGeoChatMessage:
//        update.message;
//        break;
//    case UpdateNewEncryptedMessage:
//        update.message;
//        update.qts;
//        break;
//    case UpdateEncryptedChatTyping:
//        update.chatId;
//        break;
//    case UpdateEncryption:
//        update.chat;
//        update.date;
//        break;
//    case UpdateEncryptedMessagesRead:
//        update.chatId;
//        update.maxDate;
//        update.date;
//        break;
//    case UpdateChatParticipantAdd:
//        update.chatId;
//        update.userId;
//        update.inviterId;
//        update.version;
//        break;
//    case UpdateChatParticipantDelete:
//        update.chatId;
//        update.userId;
//        update.version;
//        break;
//    case UpdateDcOptions:
//        update.dcOptions;
//        break;
//    case UpdateUserBlocked:
//        update.userId;
//        update.blocked;
//        break;
//    case UpdateNotifySettings:
//        update.peer;
//        update.notifySettings;
//        break;
    default:
        qDebug() << Q_FUNC_INFO << "Update type" << QString::number(update.tlType, 16) << "is not implemented yet.";
        break;
    }
}

void CTelegramDispatcher::processMessageReceived(quint32 messageId, quint32 fromId, const QString &message)
{
    const QString phone = userIdToIdentifier(fromId);

    emit messageReceived(phone, message, messageId);

    if (!phone.isEmpty()) {
        if (m_userTypingMap.value(fromId, 0) > 0) {
            m_userTypingMap.remove(fromId);
            emit contactTypingStatusChanged(phone, /* typingStatus */ false);
        }
    }
}

void CTelegramDispatcher::processChatMessageReceived(quint32 messageId, quint32 chatId, quint32 fromId, const QString &message)
{
    Q_UNUSED(messageId)

    const QString phone = userIdToIdentifier(fromId);
    const quint32 publicChatId = telegramChatIdToPublicId(chatId);

    emit chatMessageReceived(publicChatId, phone, message);

    const QPair<quint32,quint32> key(publicChatId, fromId);

    if (m_userChatTypingMap.contains(key)) {
        m_userChatTypingMap.remove(key);
        emit contactChatTypingStatusChanged(publicChatId, phone, /* typingStatus */ false);
    }
}

void CTelegramDispatcher::updateChat(const TLChat &newChat)
{
    int publicChatId = telegramChatIdToPublicId(newChat.id);
    if (!m_chatInfo.contains(newChat.id)) {
        m_chatInfo.insert(newChat.id, newChat);

        if (publicChatId < 0) {
            publicChatId = insertTelegramChatId(newChat.id);
            emit chatAdded(publicChatId);
        } else {
            emit chatChanged(publicChatId);
        }
    } else {
        m_chatInfo[newChat.id] = newChat;
        emit chatChanged(publicChatId);
    }
}

void CTelegramDispatcher::updateFullChat(const TLChatFull &newChat)
{
    int publicChatId = telegramChatIdToPublicId(newChat.id);
    if (!m_chatFullInfo.contains(newChat.id)) {
        m_chatFullInfo.insert(newChat.id, newChat);

        if (publicChatId < 0) {
            publicChatId = insertTelegramChatId(newChat.id);
            emit chatAdded(publicChatId);
        } else {
            emit chatChanged(publicChatId);
        }
    } else {
        m_chatFullInfo[newChat.id] = newChat;
        emit chatChanged(publicChatId);
    }
}

TLInputPeer CTelegramDispatcher::publicChatIdToInputPeer(quint32 publicChatId) const
{
    TLInputPeer inputPeer;

    quint32 chatId = m_chatIds.at(publicChatId);

    if (!chatId) {
        return inputPeer;
    }

    inputPeer.tlType = InputPeerChat;
    inputPeer.chatId = chatId;

    return inputPeer;
}

TLInputPeer CTelegramDispatcher::phoneNumberToInputPeer(const QString &phoneNumber) const
{
    TLInputPeer inputPeer;

    if (phoneNumber == m_selfPhone) {
        inputPeer.tlType = InputPeerSelf;
        return inputPeer;
    }

    const TLUser *user = phoneNumberToUser(phoneNumber);

    if (user) {
        if (user->tlType == UserContact) {
            inputPeer.tlType = InputPeerContact;
            inputPeer.userId = user->id;
        } else if (user->tlType == UserForeign) {
            inputPeer.tlType = InputPeerForeign;
            inputPeer.userId = user->id;
            inputPeer.accessHash = user->accessHash;
        } else if (user->tlType == UserRequest) {
            inputPeer.tlType = InputPeerContact; // TODO: Check if there should be InputPeerForeign. Seems like working as-is; can't test at this time.
            inputPeer.userId = user->id;
            inputPeer.accessHash = user->accessHash; // Seems to be useless.
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown user type: " << QString::number(user->tlType, 16);
        }
    } else {
        qDebug() << Q_FUNC_INFO << "Unknown user.";
    }

    return inputPeer;
}

TLInputUser CTelegramDispatcher::phoneNumberToInputUser(const QString &phoneNumber) const
{
    TLInputUser inputUser;

    if (phoneNumber == m_selfPhone) {
        inputUser.tlType = InputUserSelf;
        return inputUser;
    }

    const TLUser *user = phoneNumberToUser(phoneNumber);

    if (user) {
        if (user->tlType == UserContact) {
            inputUser.tlType = InputUserContact;
            inputUser.userId = user->id;
        } else if (user->tlType == UserForeign) {
            inputUser.tlType = InputUserForeign;
            inputUser.userId = user->id;
            inputUser.accessHash = user->accessHash;
        } else if (user->tlType == UserRequest) { // TODO: Check if there should be InputPeerForeign. Seems like working as-is; can't test at this time.
            inputUser.tlType = InputUserContact;
            inputUser.userId = user->id;
            inputUser.accessHash = user->accessHash; // Seems to be useless.
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown user type: " << QString::number(user->tlType, 16);
        }
    } else {
        qDebug() << Q_FUNC_INFO << "Unknown user.";
    }

    return inputUser;
}

QString CTelegramDispatcher::userIdToIdentifier(const quint32 id) const
{
    const TLUser *user = m_users.value(id);

    if (user) {
        if (!user->phone.isEmpty()) {
            return user->phone;
        }
    }

    return QString(QLatin1String("unknown%1")).arg(id);
}

quint32 CTelegramDispatcher::phoneNumberToUserId(const QString &phoneNumber) const
{
    foreach (const TLUser *user, m_users) {
        if (user->phone == phoneNumber) {
            return user->id;
        }
    }

    return 0;
}

TLUser *CTelegramDispatcher::phoneNumberToUser(const QString &phoneNumber) const
{
    return m_users.value(phoneNumberToUserId(phoneNumber));
}

QString CTelegramDispatcher::userAvatarToken(const TLUser *user) const
{
    const TLFileLocation &avatar = user->photo.photoSmall;

    if (avatar.tlType == FileLocationUnavailable) {
        return QString();
    } else {
        return QString(QLatin1String("%1%2%3"))
                .arg(avatar.dcId, sizeof(avatar.dcId) * 2, 16, QLatin1Char('0'))
                .arg(avatar.volumeId, sizeof(avatar.dcId) * 2, 16, QLatin1Char('0'))
                .arg(avatar.localId, sizeof(avatar.dcId) * 2, 16, QLatin1Char('0'));
    }
}

TelegramNamespace::ContactStatus CTelegramDispatcher::decodeContactStatus(TLValue status) const
{
    switch (status) {
    default:
    case UserStatusEmpty:
        return TelegramNamespace::ContactStatusUnknown;
    case UserStatusOnline:
        return TelegramNamespace::ContactStatusOnline;
    case UserStatusOffline:
        return TelegramNamespace::ContactStatusOffline;
    }
}

void CTelegramDispatcher::whenConnectionAuthChanged(int newState, quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    if (newState >= CTelegramConnection::AuthStateSuccess) {
        if (m_wantedActiveDc == dc) {
            setActiveDc(dc);
        }

        if (m_delayedPackages.contains(dc)) {
            foreach (const QByteArray &data, m_delayedPackages.values(dc)) {
                connection->processRedirectedPackage(data);
            }
            m_delayedPackages.remove(dc);
        }

        if (connection == activeConnection()) {
            continueInitialization(InitNothing);
        }
    }
}

void CTelegramDispatcher::whenConnectionStatusChanged(int newStatus, quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection == activeConnection()) {
        if (newStatus == CTelegramConnection::ConnectionStatusSigned) {
            connect(connection, SIGNAL(usersReceived(QVector<TLUser>)), SLOT(whenUsersReceived(QVector<TLUser>)));
            connect(connection, SIGNAL(contactListReceived(QStringList)), SLOT(whenContactListReceived(QStringList)));
            connect(connection, SIGNAL(contactListChanged(QStringList,QStringList)), SLOT(whenContactListChanged(QStringList,QStringList)));
            connect(connection, SIGNAL(updatesReceived(TLUpdates)), SLOT(whenUpdatesReceived(TLUpdates)));
            connect(connection, SIGNAL(messageSentInfoReceived(TLInputPeer,quint64,quint32,quint32,quint32,quint32)), SLOT(whenMessageSentInfoReceived(TLInputPeer,quint64,quint32,quint32,quint32,quint32)));
            connect(connection, SIGNAL(statedMessageReceived(TLMessagesStatedMessage,quint64)), SLOT(whenStatedMessageReceived(TLMessagesStatedMessage,quint64)));
            connect(connection, SIGNAL(updatesStateReceived(TLUpdatesState)), SLOT(whenUpdatesStateReceived(TLUpdatesState)));
            connect(connection, SIGNAL(updatesDifferenceReceived(TLUpdatesDifference)), SLOT(whenUpdatesDifferenceReceived(TLUpdatesDifference)));
            connect(connection, SIGNAL(authExportedAuthorizationReceived(quint32,quint32,QByteArray)), SLOT(whenAuthExportedAuthorizationReceived(quint32,quint32,QByteArray)));
            connect(connection, SIGNAL(messagesChatsReceived(QVector<TLChat>,QVector<TLUser>)), SLOT(whenMessagesChatsReceived(QVector<TLChat>)));

            continueInitialization(InitIsSignIn);
        }
    } else {
        switch (newStatus) {
        case CTelegramConnection::ConnectionStatusAuthenticated:
            ensureSignedConnection(dc);
            break;
        case CTelegramConnection::ConnectionStatusSigned:
            if (m_requestedFiles.contains(dc)) {
                foreach (const SRequestedFile &requestedFile, m_requestedFiles.values(dc)) {
                    connection->getFile(requestedFile.location, requestedFile.fileId);
                }
                m_requestedFiles.remove(dc);
            }
        default:
            break;
        }
    }
}

void CTelegramDispatcher::whenDcConfigurationUpdated(quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    m_dcConfiguration = connection->dcConfiguration();

    qDebug() << "Core: Got DC Configuration.";

    continueInitialization(InitHaveDcConfiguration);
}

void CTelegramDispatcher::whenConnectionDcIdUpdated(quint32 connectionId, quint32 newDcId)
{
    CTelegramConnection *connection = m_connections.value(connectionId);

    if (!connection) {
        return;
    }

    if (m_connections.value(newDcId)) {
        qDebug() << "Connection with wanted id already exists";
    } else {
        m_connections.remove(connectionId);
        m_connections.insert(newDcId, connection);

        TLDcOption info = connection->dcInfo();
        info.id = newDcId;
        connection->setDcInfo(info);

        if (m_activeDc == connectionId) {

            if (m_wantedActiveDc == m_activeDc) {
                m_wantedActiveDc = newDcId;
            }

            setActiveDc(newDcId);
        }

        qDebug() << "Connection DC Id changed from" << connectionId << "to" << newDcId;
    }
}

void CTelegramDispatcher::whenPackageRedirected(const QByteArray &data, quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() >= CTelegramConnection::AuthStateSuccess) {
        connection->processRedirectedPackage(data);
    } else {
        m_delayedPackages.insertMulti(dc, data);
        establishConnectionToDc(dc);
    }
}

void CTelegramDispatcher::whenWantedActiveDcChanged(quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() >= CTelegramConnection::AuthStateSuccess) {
        setActiveDc(dc);
    } else {
        m_wantedActiveDc = dc;
        establishConnectionToDc(dc);
    }
}

void CTelegramDispatcher::whenFileReceived(const TLUploadFile &file, quint32 fileId)
{
    // Proto version.

    QString mimeType = mimeTypeByStorageFileType(file.type.tlType);

    TLUser *user = m_users.value(fileId);

    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unexpected fileId" << fileId;
        return;
    }

    emit avatarReceived(user->phone, file.bytes, mimeType, userAvatarToken(user));
}

void CTelegramDispatcher::whenUpdatesReceived(const TLUpdates &updates)
{
    switch (updates.tlType) {
    case UpdatesTooLong:
        getUpdatesState();
        break;
    case UpdateShortMessage:
        processMessageReceived(updates.id, updates.fromId, updates.message);
        ensureUpdateState(updates.pts);
        break;
    case UpdateShortChatMessage:
        processChatMessageReceived(updates.id, updates.chatId, updates.fromId, updates.message);
        ensureUpdateState(updates.pts);
        break;
    case UpdateShort:
        processUpdate(updates.update);
        break;
    case UpdatesCombined:
        qDebug() << Q_FUNC_INFO << "UpdatesCombined processing is not implemented yet.";
        break;
    case Updates:
        // Initial implementation
        for (int i = 0; i < updates.updates.count(); ++i) {
            processUpdate(updates.updates.at(i));
        }
        break;
    default:
        break;
    }
}

void CTelegramDispatcher::whenAuthExportedAuthorizationReceived(quint32 dc, quint32 id, const QByteArray &data)
{
    m_exportedAuthentications.insert(dc, QPair<quint32, QByteArray>(id,data));

    CTelegramConnection *connection = m_connections.value(dc);
    if (connection && (connection->status() == CTelegramConnection::ConnectionStatusAuthenticated)) {
        connection->authImportAuthorization(id, data);
    }
}

void CTelegramDispatcher::setActiveDc(quint32 dc, bool syncWantedDc)
{
    if ((m_activeDc == dc) && (m_wantedActiveDc == dc)) {
        return;
    }

    m_activeDc = dc;

    if (syncWantedDc) {
        m_wantedActiveDc = dc;
    }

    qDebug() << Q_FUNC_INFO << dc;
}

void CTelegramDispatcher::ensureTypingUpdateTimer(int interval)
{
    if (!m_typingUpdateTimer->isActive()) {
#if QT_VERSION >= 0x050000
        m_typingUpdateTimer->start(interval);
#else
        Q_UNUSED(interval);
        m_typingUpdateTimer->start(s_timerMaxInterval);
#endif
    }
}

void CTelegramDispatcher::continueInitialization(CTelegramDispatcher::InitializationState justDone)
{
    qDebug() << Q_FUNC_INFO << justDone;

    if (justDone == InitNothing) {
        if (m_initState == InitNothing) {
            getDcConfiguration();
        } else {
            // We can have Dc Configuration obtained from *not* our primary dc. Silence this case.
            if (m_initState != InitHaveDcConfiguration) {
                qDebug() << "Invalid initialization order." << justDone;
            }
        }
        return;
    }

    if ((m_initState | justDone) == m_initState) {
        return; // Nothing new
    }

    m_initState = InitializationState(m_initState|justDone);

    if ((m_initState & InitHaveDcConfiguration) && (m_initState & InitIsSignIn)) { // Have config and sign in
        setAuthenticated(true);
    }

    if (justDone == InitHaveDcConfiguration) {
        emit connected();
    }

    if (m_initState == (InitHaveDcConfiguration|InitIsSignIn)) {
        getInitialUsers();
        // Sadly, we don't support creation of RPC messages containers, so we fails on attempt to send more than one package in time. (Got "Sequence number too high")
        // That is why we have to comment out this getContacts() and add #BadCode1.
//        getContacts();
        return;
    }

    // #BadCode1
    if (justDone == InitKnowSelf) {
        if (!(m_initState & InitHaveContactList)) {
            getContacts();
        }
    }

    if (m_initState == InitDone) {
        emit initializated();
        return;
    }

    if (m_initState == (InitDone & ~InitKnowChats)) {
        getChatsInfo();
    }

    if ((m_initState & InitHaveContactList) && (m_initState & InitKnowSelf)) {
        getUpdatesState();
        return;
    }
}

void CTelegramDispatcher::setAuthenticated(bool newAuth)
{
    if (m_isAuthenticated == newAuth) {
        return;
    }

    m_isAuthenticated = newAuth;

    if (m_isAuthenticated) {
        emit authenticated();
    }
}

qint32 CTelegramDispatcher::telegramChatIdToPublicId(quint32 telegramChatId) const
{
    for (int i = 0; i < m_chatIds.count(); ++i) {
        if (m_chatIds.at(i) == telegramChatId) {
            return i;
        }
    }

    return -1;
}

/* Return public chat id */
quint32 CTelegramDispatcher::insertTelegramChatId(quint32 telegramChatId)
{
    m_chatIds.append(telegramChatId);
    return m_chatIds.count() - 1;
}

bool CTelegramDispatcher::havePublicChatId(quint32 publicChatId) const
{
    return m_chatIds.count() > int(publicChatId);
}

void CTelegramDispatcher::ensureUpdateState(quint32 pts, quint32 seq, quint32 date)
{
    if (m_updatesStateIsLocked) {
        return; // Prevent m_updateState from updating before UpdatesGetState answer receiving to avoid m_updateState <-> m_actualState messing (which may lead to ignore offline-messages)
    }

    if (pts > m_updatesState.pts) {
        m_updatesState.pts = pts;
    }

    if (seq > m_updatesState.seq) {
        m_updatesState.seq = seq;
    }

    if (date > m_updatesState.date) {
        m_updatesState.date = date;
    }
}

void CTelegramDispatcher::checkStateAndCallGetDifference()
{
    m_updatesStateIsLocked = m_actualState.pts > m_updatesState.pts;

    if (m_updatesStateIsLocked) {
        QTimer::singleShot(10, this, SLOT(getDifference()));
    } else {
        continueInitialization(InitHaveUpdates);
    }
}

CTelegramConnection *CTelegramDispatcher::createConnection(const TLDcOption &dc)
{
    CTelegramConnection *connection = new CTelegramConnection(m_appInformation, this);

    connect(connection, SIGNAL(selfPhoneReceived(QString)), SLOT(whenSelfPhoneReceived(QString)));

    connect(connection, SIGNAL(authStateChanged(int,quint32)), SLOT(whenConnectionAuthChanged(int,quint32)));
    connect(connection, SIGNAL(statusChanged(int,quint32)), SLOT(whenConnectionStatusChanged(int,quint32)));
    connect(connection, SIGNAL(dcConfigurationReceived(quint32)), SLOT(whenDcConfigurationUpdated(quint32)));
    connect(connection, SIGNAL(actualDcIdReceived(quint32,quint32)), SLOT(whenConnectionDcIdUpdated(quint32,quint32)));
    connect(connection, SIGNAL(newRedirectedPackage(QByteArray,quint32)), SLOT(whenPackageRedirected(QByteArray,quint32)));
    connect(connection, SIGNAL(wantedActiveDcChanged(quint32)), SLOT(whenWantedActiveDcChanged(quint32)));

    connect(connection, SIGNAL(phoneStatusReceived(QString,bool,bool)), SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(connection, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(connection, SIGNAL(phoneCodeIsInvalid()), SIGNAL(phoneCodeIsInvalid()));
    connect(connection, SIGNAL(authorizationErrorReceived()), SIGNAL(authorizationErrorReceived()));

    connect(connection, SIGNAL(fileReceived(TLUploadFile,quint32)), SLOT(whenFileReceived(TLUploadFile,quint32)));

    connection->setDcInfo(dc);

    return connection;
}

CTelegramConnection *CTelegramDispatcher::establishConnectionToDc(quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        const TLDcOption info = dcInfoById(dc);

        if (info.ipAddress.isEmpty()) {
            qDebug() << "Error: Attempt to connect to unknown DC" << dc;
            return 0;
        }

        connection = createConnection(info);
        m_connections.insert(dc, connection);
    }

    if (!connection->isConnected()) {
        connection->connectToDc();
    }

    return connection;
}

void CTelegramDispatcher::ensureSignedConnection(quint32 dc)
{
    if (dc == m_activeDc) {
        return;
    }

    CTelegramConnection *connection = m_connections.value(dc);

    if (connection) {
        switch (connection->status()) {
        case CTelegramConnection::ConnectionStatusAuthenticated:
            if (m_exportedAuthentications.contains(dc)) {
                connection->authImportAuthorization(m_exportedAuthentications.value(dc).first, m_exportedAuthentications.value(dc).second);
            } else {
                activeConnection()->authExportAuthorization(dc);
            }
            // Fall through by design.
        case CTelegramConnection::ConnectionStatusSigned:
            return;
        default:
            break;
        }
    }
    establishConnectionToDc(dc);
}

TLDcOption CTelegramDispatcher::dcInfoById(quint32 dc)
{
    foreach (const TLDcOption option, m_dcConfiguration) {
        if (option.id == dc) {
            return option;
        }
    }

    return TLDcOption();
}

QString CTelegramDispatcher::mimeTypeByStorageFileType(TLValue type)
{
    switch (type) {
    case StorageFileJpeg:
        return QLatin1String("image/jpeg");
    case StorageFileGif:
        return QLatin1String("image/gif");
    case StorageFilePng:
        return QLatin1String("image/png");
    case StorageFilePdf:
        return QLatin1String("application/pdf");
    case StorageFileMp3:
        return QLatin1String("audio/mpeg");
    case StorageFileMov:
        return QLatin1String("video/quicktime");
    case StorageFileMp4:
        return QLatin1String("audio/mp4");
    case StorageFileWebp:
        return QLatin1String("image/webp");
    default:
        return QString();
    }
}
