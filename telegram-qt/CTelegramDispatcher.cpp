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

const quint32 secretFormatVersion = 0;
const int s_userTypingActionPeriod = 6000; // 6 sec
const int s_localTypingActionPeriod = 5000; // 5 sec

#if QT_VERSION < 0x050000
const int s_timerMaxInterval = 500; // 0.5 sec. Needed to limit max possible typing time deviation in Qt4 by this value.
#endif

CTelegramDispatcher::CTelegramDispatcher(QObject *parent) :
    QObject(parent),
    m_appInformation(0),
    m_activeDc(0),
    m_wantedActiveDc(0),
    m_typingUpdateTimer(new QTimer(this))
{
    m_typingUpdateTimer->setSingleShot(true);
    connect(m_typingUpdateTimer, SIGNAL(timeout()), SLOT(whenUserTypingTimeout()));
}

void CTelegramDispatcher::setAppInformation(const CAppInformation *newAppInfo)
{
    m_appInformation = newAppInfo;
}

bool CTelegramDispatcher::isAuthenticated()
{
    return activeConnection() && (activeConnection()->authState() == CTelegramConnection::AuthStateSignedIn) && !m_dcConfiguration.isEmpty();
}

void CTelegramDispatcher::addContacts(const QStringList &phoneNumbers, bool replace)
{
    activeConnection()->addContacts(phoneNumbers, replace);
}

void CTelegramDispatcher::deleteContacts(const QStringList &phoneNumbers)
{
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

    return output;
}

void CTelegramDispatcher::initConnection(const QString &address, quint32 port)
{
    TLDcOption dcInfo;
    dcInfo.ipAddress = address;
    dcInfo.port = port;

    CTelegramConnection *connection = createConnection(dcInfo);

    m_connections.insert(0, connection);
    connection->connectToDc();

    setActiveDc(0);
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

    if (format != secretFormatVersion) {
        qDebug() << "Unknown format version";
        return false;
    }

    inputStream >> deltaTime;
    inputStream >> dcInfo;
    inputStream >> m_selfPhone;
    inputStream >> authKey;
    inputStream >> authId;
    inputStream >> serverSalt;

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

    setActiveDc(dcInfo.id);

    connection->connectToDc();

    return true;
}

void CTelegramDispatcher::requestPhoneStatus(const QString &phoneNumber)
{
    activeConnection()->requestPhoneStatus(phoneNumber);
}

void CTelegramDispatcher::signIn(const QString &phoneNumber, const QString &authCode)
{
    activeConnection()->signIn(phoneNumber, authCode);
}

void CTelegramDispatcher::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
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

void CTelegramDispatcher::requestContactList()
{
    activeConnection()->requestContacts();
}

void CTelegramDispatcher::requestContactAvatar(const QString &phoneNumber)
{
    qDebug() << Q_FUNC_INFO << phoneNumber;

    const TLUser *user = phoneNumberToUser(phoneNumber);
    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unknown user" << phoneNumber;
        return;
    }

    if (user->photo.tlType == UserProfilePhotoEmpty) {
        qDebug() << Q_FUNC_INFO << "User" << phoneNumber << "have no avatar";
        return;
    }

    TLFileLocation avatarLocation = user->photo.photoSmall;

    if (avatarLocation.tlType == FileLocationUnavailable) {
        qDebug() << Q_FUNC_INFO << "Contact" << phoneNumber << "avatar is not available";
        return;
    }

    TLInputFileLocation inputFile;
    inputFile.volumeId = avatarLocation.volumeId;
    inputFile.localId  = avatarLocation.localId;
    inputFile.secret   = avatarLocation.secret;

    requestFile(inputFile, avatarLocation.dcId, user->id);
    qDebug() << Q_FUNC_INFO << "Requested avatar for user " << phoneNumber;
}

quint64 CTelegramDispatcher::sendMessageToContact(const QString &phone, const QString &message)
{
    const TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << phone;
        return 0;
    }

    quint64 randomMessageId;
    Utils::randomBytes(&randomMessageId);

    activeConnection()->messagesSendMessage(peer, message, randomMessageId);

    if (m_localTypingMap.contains(phone)) {
        m_localTypingMap.remove(phone);
    }

    return randomMessageId;
}

void CTelegramDispatcher::setTyping(const QString &phone, bool typingStatus)
{
    if (typingStatus == m_localTypingMap.contains(phone)) {
        return; // Avoid flood
    }

    TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << phone;
        return;
    }

    activeConnection()->messagesSetTyping(peer, typingStatus);

    m_localTypingMap.insert(phone, s_localTypingActionPeriod);
    ensureTypingUpdateTimer(s_localTypingActionPeriod);
}

void CTelegramDispatcher::setMessageRead(const QString &phone, quint32 messageId)
{
    const TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType != InputPeerEmpty) {
        activeConnection()->messagesReadHistory(peer, messageId, 0);
    }
}

void CTelegramDispatcher::setOnlineStatus(bool onlineStatus)
{
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
    }
}

void CTelegramDispatcher::whenContactListReceived(const QStringList &contactList)
{
    QStringList newContactList = contactList;
    newContactList.sort();

    if (m_contactList != newContactList) {
        m_contactList = newContactList;
        emit contactListChanged();
    }
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

void CTelegramDispatcher::whenUserTypingTimeout()
{
    const QList<quint32> users = m_userTypingMap.keys();

#if QT_VERSION >= 0x050000
    int minTime = s_userTypingActionPeriod;
#else
    int minTime = s_timerMaxInterval;
#endif

    foreach (quint32 userId, users) {
        int timeRemains = m_userTypingMap.value(userId) - m_typingUpdateTimer->interval();
        if (timeRemains < 5) { // Let 5 ms be allowed correction
            m_userTypingMap.remove(userId);
            emit contactTypingStatusChanged(userIdToPhoneNumber(userId), /* typingStatus */ false);
        } else {
            m_userTypingMap.insert(userId, timeRemains);
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

    if (!m_userTypingMap.isEmpty() || !m_localTypingMap.isEmpty()) {
        m_typingUpdateTimer->start(minTime);
    }
}

void CTelegramDispatcher::whenMessageSentInfoReceived(quint64 randomId, quint32 messageId, quint32 pts, quint32 date, quint32 seq)
{
    m_messagesMap.insert(messageId, randomId);

    emit sentMessageStatusChanged(randomId, TelegramNamespace::MessageDeliveryStatusSent);
}

void CTelegramDispatcher::requestFile(const TLInputFileLocation &location, quint32 dc, quint32 fileId)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        qDebug() << "No connection";
    }

    if (connection && (connection->authState() == CTelegramConnection::AuthStateSignedIn)) {
        connection->getFile(location, fileId);
    } else {
        qDebug() << Q_FUNC_INFO << "There is no connection to dest dc. Not implemented." << dc;
        // TODO
    }
}

void CTelegramDispatcher::processUpdate(const TLUpdate &update)
{
    switch (update.tlType) {
//    case UpdateNewMessage:
//        update.message;
//        update.pts;
//        break;
//    case UpdateMessageID:
//        update.id;
//        update.randomId;
//        break;
    case UpdateReadMessages:
        foreach (quint32 messageId, update.messages) {
            emit sentMessageStatusChanged(m_messagesMap.value(messageId), TelegramNamespace::MessageDeliveryStatusRead);
        }

//        update.pts;
        break;
//    case UpdateDeleteMessages:
//        update.messages;
//        update.pts;
//        break;
//    case UpdateRestoreMessages:
//        update.messages;
//        update.pts;
//        break;
    case UpdateUserTyping: {
        TLUser *user = m_users.value(update.userId);
        if (user) {
            emit contactTypingStatusChanged(user->phone, /* typingStatus */ true);
#if QT_VERSION >= 0x050000
            m_userTypingMap.insert(user->id, m_typingUpdateTimer->remainingTime() + s_userTypingActionPeriod);
#else
            m_userTypingMap.insert(user->id, s_userTypingActionPeriod); // Missed timer remaining time method can leads to typing time period deviation.
#endif
            ensureTypingUpdateTimer(s_userTypingActionPeriod);
        }
        break;
    }
//    case UpdateChatUserTyping:
//        update.chatId;
//        update.userId;
//        break;
//    case UpdateChatParticipants:
//        update.participants;
//        break;
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

void CTelegramDispatcher::processMessageReceived(quint32 messageId, const QString &phone, const QString &message)
{
    emit messageReceived(phone, message, messageId);

    const quint32 userId = phoneNumberToUserId(phone);

    if (userId) {
        if (m_userTypingMap.value(userId, 0) > 0) {
            m_userTypingMap.remove(userId);
            emit contactTypingStatusChanged(phone, /* typingStatus */ false);
        }
    }
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
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown user type: " << QString::number(user->tlType, 16);
        }
    } else {
        qDebug() << Q_FUNC_INFO << "Unknown user.";
    }

    return inputUser;
}

QString CTelegramDispatcher::userIdToPhoneNumber(const quint32 id) const
{
    const TLUser *user = m_users.value(id);

    if (user) {
        return user->phone;
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

void CTelegramDispatcher::whenConnectionAuthChanged(int dc, int newState)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    if (newState >= CTelegramConnection::AuthStateSuccess) {
        if (m_dcConfiguration.isEmpty()) {
            connection->getConfiguration();
        }

        if (m_wantedActiveDc == dc) {
            setActiveDc(dc);
        }

        foreach (const QByteArray &data, m_delayedPackages.values(dc)) {
            connection->processRedirectedPackage(data);
        }

        m_delayedPackages.remove(dc);
    }

    if (newState == CTelegramConnection::AuthStateSignedIn) {
        connect(connection, SIGNAL(usersReceived(QVector<TLUser>)), SLOT(whenUsersReceived(QVector<TLUser>)));
        connect(connection, SIGNAL(contactListReceived(QStringList)), SLOT(whenContactListReceived(QStringList)));
        connect(connection, SIGNAL(contactListChanged(QStringList,QStringList)), SLOT(whenContactListChanged(QStringList,QStringList)));
        connect(connection, SIGNAL(updatesReceived(TLUpdates)), SLOT(whenUpdatesReceived(TLUpdates)));
        connect(connection, SIGNAL(messageSentInfoReceived(quint64,quint32,quint32,quint32,quint32)), SLOT(whenMessageSentInfoReceived(quint64,quint32,quint32,quint32,quint32)));

        if (isAuthenticated()) {
            emit authenticated();
        }
    }
}

void CTelegramDispatcher::whenConnectionConfigurationUpdated(int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    m_dcConfiguration = connection->dcConfiguration();

    qDebug() << "Core: Got DC Configuration.";

    emit dcConfigurationObtained();

    if (isAuthenticated()) {
        emit authenticated();
    }
}

void CTelegramDispatcher::whenConnectionDcIdUpdated(int connectionId, int newDcId)
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

void CTelegramDispatcher::whenPackageRedirected(const QByteArray &data, int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() >= CTelegramConnection::AuthStateSuccess) {
        connection->processRedirectedPackage(data);
    } else {
        m_delayedPackages.insertMulti(dc, data);
        establishConnectionToDc(dc);
    }
}

void CTelegramDispatcher::whenWantedActiveDcChanged(int dc)
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

    emit avatarReceived(user->phone, file.bytes, mimeType);
}

void CTelegramDispatcher::whenUpdatesReceived(const TLUpdates &updates)
{
    switch (updates.tlType) {
    case UpdatesTooLong:
        qDebug() << Q_FUNC_INFO << "UpdatesTooLong processing is not implemented yet.";
        break;
    case UpdateShortMessage:
        processMessageReceived(updates.id, userIdToPhoneNumber(updates.fromId), updates.message);
        break;
    case UpdateShortChatMessage:
        qDebug() << Q_FUNC_INFO << "UpdateShortChatMessage processing is not implemented yet.";
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

void CTelegramDispatcher::setActiveDc(int dc, bool syncWantedDc)
{
    m_activeDc = dc;

    if (syncWantedDc) {
        m_wantedActiveDc = dc;
    }

    qDebug() << "New active dc:" << dc;
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

CTelegramConnection *CTelegramDispatcher::createConnection(const TLDcOption &dc)
{
    CTelegramConnection *connection = new CTelegramConnection(m_appInformation, this);

    connect(connection, SIGNAL(selfPhoneReceived(QString)), SLOT(whenSelfPhoneReceived(QString)));
    connect(connection, SIGNAL(authStateChanged(int,int)), SLOT(whenConnectionAuthChanged(int,int)));
    connect(connection, SIGNAL(dcConfigurationReceived(int)), SLOT(whenConnectionConfigurationUpdated(int)));
    connect(connection, SIGNAL(actualDcIdReceived(int,int)), SLOT(whenConnectionDcIdUpdated(int,int)));
    connect(connection, SIGNAL(newRedirectedPackage(QByteArray,int)), SLOT(whenPackageRedirected(QByteArray,int)));
    connect(connection, SIGNAL(wantedActiveDcChanged(int)), SLOT(whenWantedActiveDcChanged(int)));

    connect(connection, SIGNAL(phoneStatusReceived(QString,bool,bool)), SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(connection, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(connection, SIGNAL(phoneCodeIsInvalid()), SIGNAL(phoneCodeIsInvalid()));

    connect(connection, SIGNAL(fileReceived(TLUploadFile,quint32)), SLOT(whenFileReceived(TLUploadFile,quint32)));

    connection->setDcInfo(dc);

    return connection;
}

CTelegramConnection *CTelegramDispatcher::establishConnectionToDc(int dc)
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
