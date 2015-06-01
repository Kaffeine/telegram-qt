/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "CTelegramDispatcher.hpp"

#include "TelegramNamespace.hpp"
#include "CTelegramConnection.hpp"
#include "CTelegramStream.hpp"
#include "Utils.hpp"

#include <QTimer>

#include <QCryptographicHash>
#include <QDebug>

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

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
            QString masked = QString(QLatin1String("%1xx%2%3"))
                    .arg(number.mid(0, 2))
                    .arg(list.indexOf(number), listDigits, 10, QLatin1Char('0'))
                    .arg(QString(number.length() - 4 - listDigits, QLatin1Char('x')));
            result.append(masked);
        } else { // fallback
            result.append(maskPhoneNumber(number) + QLatin1String(" (fallback)"));
        }
    }

    return result;
}

const quint32 secretFormatVersion = 3;
const int s_userTypingActionPeriod = 6000; // 6 sec
const int s_localTypingDuration = 5000; // 5 sec
const int s_localTypingRecommendedRepeatInterval = 400; // (s_userTypingActionPeriod - s_localTypingDuration) / 2. Minus 100 ms for insurance.

#if QT_VERSION < 0x050000
const int s_timerMaxInterval = 500; // 0.5 sec. Needed to limit max possible typing time deviation in Qt4 by this value.
#endif

enum TelegramMessageFlags {
    TelegramMessageFlagNone   = 0x0,
    TelegramMessageFlagUnread = 0x1, // Message was *not* read
    TelegramMessageFlagOut    = 0x2  // Message is outgoing
};

const quint32 FileRequestDescriptor::c_chunkSize = 128 * 256;

FileRequestDescriptor FileRequestDescriptor::uploadRequest(const QByteArray &data, const QString &fileName, quint32 dc)
{
    FileRequestDescriptor result;

    result.m_type = Upload;
    result.m_data = data;
    result.m_size = data.size();
    result.m_fileName = fileName;
    result.m_dcId = dc;

    if (!result.isBigFile()) {
        result.m_hash = new QCryptographicHash(QCryptographicHash::Md5);
    }

    Utils::randomBytes(&result.m_fileId);

    return result;
}

FileRequestDescriptor FileRequestDescriptor::avatarRequest(const TLUser *user)
{
    if (user->photo.photoSmall.tlType != TLValue::FileLocation) {
        return FileRequestDescriptor();
    }

    FileRequestDescriptor result;

    result.m_type = Avatar;
    result.m_userId = user->id;
    result.setupLocation(user->photo.photoSmall);

    return result;
}

FileRequestDescriptor FileRequestDescriptor::messageMediaDataRequest(const TLMessage &message)
{
    const TLMessageMedia &media = message.media;

    FileRequestDescriptor result;
    result.m_type = MessageMediaData;
    result.m_messageId = message.id;

    switch (media.tlType) {
    case TLValue::MessageMediaPhoto:
        if (media.photo.sizes.isEmpty()) {
            return FileRequestDescriptor();
        } else {
            const TLPhotoSize s = media.photo.sizes.last();
            result.setupLocation(s.location);
            result.m_size = s.size;
        }
        break;
    case TLValue::MessageMediaAudio:
        result.m_dcId = media.audio.dcId;
        result.m_inputLocation.tlType = TLValue::InputAudioFileLocation;
        result.m_inputLocation.id = media.audio.id;
        result.m_inputLocation.accessHash = media.audio.accessHash;
        result.m_size = media.audio.size;
        break;
    case TLValue::MessageMediaVideo:
        result.m_dcId = media.video.dcId;
        result.m_inputLocation.tlType = TLValue::InputVideoFileLocation;
        result.m_inputLocation.id = media.video.id;
        result.m_inputLocation.accessHash = media.video.accessHash;
        result.m_size = media.video.size;
        break;
    case TLValue::MessageMediaDocument:
        result.m_dcId = media.document.dcId;
        result.m_inputLocation.tlType = TLValue::InputDocumentFileLocation;
        result.m_inputLocation.id = media.document.id;
        result.m_inputLocation.accessHash = media.document.accessHash;
        result.m_size = media.document.size;
        break;
    default:
        return FileRequestDescriptor();
    }

    return result;
}

TLInputFile FileRequestDescriptor::inputFile() const
{
    TLInputFile file;

    if (isBigFile()) {
        file.tlType = TLValue::InputFileBig;
    } else {
        file.tlType = TLValue::InputFile;
//        file.md5Checksum = QString::fromLatin1(md5Sum().toHex());
    }

    file.id = inputLocation().id;
    file.parts = parts();
    file.name = m_fileName;

#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << file;
#endif

    return file;
}

quint32 FileRequestDescriptor::parts() const
{
    quint32 parts = m_size / c_chunkSize;
    if (m_size % c_chunkSize) {
        ++parts;
    }

    return parts;
}

bool FileRequestDescriptor::isBigFile() const
{
    return size() > 10 * 1024 * 1024;
}

bool FileRequestDescriptor::finished() const
{
    return m_part * c_chunkSize >= size();
}

void FileRequestDescriptor::bumpPart()
{
    if (m_hash) {
        m_hash->addData(data());
    }

    ++m_part;
    m_offset = m_part * c_chunkSize;

    if (m_offset > m_size) {
        m_offset = m_size;
    }

    if (m_hash && finished()) {
        m_md5Sum = m_hash->result();
        delete m_hash;
        m_hash = 0;
    }
}

QByteArray FileRequestDescriptor::data() const
{
    return m_data.mid(m_part * c_chunkSize, c_chunkSize);
}

void FileRequestDescriptor::setupLocation(const TLFileLocation &fileLocation)
{
    m_dcId = fileLocation.dcId;

    m_inputLocation.tlType = TLValue::InputFileLocation;
    m_inputLocation.volumeId = fileLocation.volumeId;
    m_inputLocation.localId = fileLocation.localId;
    m_inputLocation.secret = fileLocation.secret;
}

FileRequestDescriptor::FileRequestDescriptor() :
    m_type(Invalid),
    m_size(0),
    m_offset(0),
    m_part(0),
    m_hash(0)
{

}

CTelegramDispatcher::CTelegramDispatcher(QObject *parent) :
    QObject(parent),
    m_connectionState(TelegramNamespace::ConnectionStateDisconnected),
    m_appInformation(0),
    m_messageReceivingFilterFlags(TelegramNamespace::MessageFlagRead),
    m_acceptableMessageTypes(TelegramNamespace::MessageTypeText),
    m_autoReconnectionEnabled(false),
    m_pingInterval(15000),
    m_mediaDataBufferSize(128 * 256), // 128 KB
    m_initializationState(0),
    m_requestedSteps(0),
    m_activeDc(0),
    m_wantedActiveDc(0),
    m_updatesStateIsLocked(false),
    m_selfUserId(0),
    m_fileRequestCounter(0),
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

qint32 CTelegramDispatcher::localTypingRecommendedRepeatInterval()
{
    return s_localTypingRecommendedRepeatInterval;
}

QString CTelegramDispatcher::selfPhone() const
{
    if (!m_selfUserId || !m_users.value(m_selfUserId)) {
        return QString();
    }

    return m_users.value(m_selfUserId)->phone;
}

QStringList CTelegramDispatcher::contactList() const
{
    QStringList result;

    foreach (quint32 userId, m_contactList) {
        result.append(userIdToIdentifier(userId));
    }

    return result;
}

QList<quint32> CTelegramDispatcher::chatList() const
{
    QList<quint32> result;
    for (int i = 0; i < m_chatIds.count(); ++i) {
        result << i;
    }
    return result;
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
        if (inputUser.tlType != TLValue::InputUserEmpty) {
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
    outputStream << activeConnection()->authKey();
    outputStream << activeConnection()->authId();
    outputStream << activeConnection()->serverSalt();
    outputStream << m_updatesState.pts;
    outputStream << m_updatesState.qts;
    outputStream << m_updatesState.date;
    outputStream << m_chatIds;

    return output;
}

void CTelegramDispatcher::setMessageReceivingFilter(TelegramNamespace::MessageFlags flags)
{
    m_messageReceivingFilterFlags = flags;
}

void CTelegramDispatcher::setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types)
{
    m_acceptableMessageTypes = types;
}

void CTelegramDispatcher::setAutoReconnection(bool enable)
{
    m_autoReconnectionEnabled = enable;
}

void CTelegramDispatcher::setPingInterval(quint32 ms)
{
    m_pingInterval = ms;
}

void CTelegramDispatcher::setMediaDataBufferSize(quint32 size)
{
    if (size % 256) {
        qDebug() << Q_FUNC_INFO << "Unable to set incorrect size" << size << ". The value must be divisible by 1 KB";
        return;
    }

    if (!size) {
        size = 128 * 256;
    }

    m_mediaDataBufferSize = size;
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
        qDebug() << Q_FUNC_INFO << "Unknown format version";
        return false;
    }

    QString legacySelfPhone;

    inputStream >> deltaTime;
    inputStream >> dcInfo;

    if (format < 3) {
        inputStream >> legacySelfPhone;
    }

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
        qDebug() << Q_FUNC_INFO << "Invalid auth data.";
        delete connection;
        return false;
    }

    m_connections.insert(dcInfo.id, connection);

    initConnectionSharedFinal(dcInfo.id);

    return true;
}

void CTelegramDispatcher::initConnectionSharedFinal(quint32 activeDc)
{
    m_initializationState = StepFirst;
    m_requestedSteps = 0;
    setConnectionState(TelegramNamespace::ConnectionStateConnecting);
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

    m_connections.clear();

    m_dcConfiguration.clear();
    m_delayedPackages.clear();
    qDeleteAll(m_users);
    m_users.clear();
    m_messagesMap.clear();
    m_contactList.clear();
    m_requestedFileDescriptors.clear();
    m_fileRequestCounter = 0;
    m_userTypingMap.clear();
    m_userChatTypingMap.clear();
    m_localTypingMap.clear();
    m_chatIds.clear();
    m_temporaryChatIdMap.clear();
    m_chatInfo.clear();
    m_chatFullInfo.clear();

    setConnectionState(TelegramNamespace::ConnectionStateDisconnected);
}

bool CTelegramDispatcher::logOut()
{
    if (!activeConnection()) {
        return false;
    }

    activeConnection()->authLogOut();
    return true;
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
        qDebug() << Q_FUNC_INFO << "Can't request phone code: there is no active connection.";
        return;
    }

    if (m_dcConfiguration.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Can't request phone code: DC Configuration is unknown.";
        return;
    }

    activeConnection()->requestPhoneCode(phoneNumber);
}

void CTelegramDispatcher::requestContactAvatar(const QString &phoneNumber)
{
    qDebug() << Q_FUNC_INFO << maskPhoneNumber(phoneNumber);

    const TLUser *user = identifierToUser(phoneNumber);
    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unknown user" << maskPhoneNumber(phoneNumber);
        return;
    }

    if (user->photo.tlType == TLValue::UserProfilePhotoEmpty) {
        qDebug() << Q_FUNC_INFO << "User" << maskPhoneNumber(phoneNumber) << "have no avatar";
        return;
    }

    if (requestFile(FileRequestDescriptor::avatarRequest(user))) {
        qDebug() << Q_FUNC_INFO << "Requested avatar for user " << maskPhoneNumber(phoneNumber);
    } else {
        qDebug() << Q_FUNC_INFO << "Contact" << maskPhoneNumber(phoneNumber) << "avatar is not available";
    }
}

bool CTelegramDispatcher::requestMessageMediaData(quint32 messageId)
{
    if (!m_knownMediaMessages.contains(messageId)) {
        return false;
    }

    // TODO: MessageMediaContact, MessageMediaGeo

    return requestFile(FileRequestDescriptor::messageMediaDataRequest(m_knownMediaMessages.value(messageId)));
}

quint32 CTelegramDispatcher::uploadFile(const QByteArray &fileContent, const QString &fileName)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << fileName;
#endif
    return requestFile(FileRequestDescriptor::uploadRequest(fileContent, fileName, m_activeDc));
}

quint32 CTelegramDispatcher::uploadFile(QIODevice *source, const QString &fileName)
{
    return uploadFile(source->readAll(), fileName);
}

quint64 CTelegramDispatcher::sendMessage(const QString &identifier, const QString &message)
{
    if (!activeConnection()) {
        return 0;
    }
    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType == TLValue::InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return 0;
    }

    if (m_localTypingMap.contains(identifier)) {
        m_localTypingMap.remove(identifier);
    }

    return activeConnection()->sendMessage(peer, message);
}

quint64 CTelegramDispatcher::sendMedia(const QString &identifier, quint32 uploadedFileId, TelegramNamespace::MessageType type)
{
    if (!activeConnection()) {
        return 0;
    }
    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType == TLValue::InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return 0;
    }

    if (!m_requestedFileDescriptors.contains(uploadedFileId)) {
        qDebug() << Q_FUNC_INFO << "Unknown file id";
        return 0;
    }

    const FileRequestDescriptor descriptor = m_requestedFileDescriptors.value(uploadedFileId);
    TLInputMedia media;

    switch (type) {
    case TelegramNamespace::MessageTypePhoto:
        media.tlType = TLValue::InputMediaUploadedPhoto;
        media.file = descriptor.inputFile();
        break;
    default:
        break;
    }

    return activeConnection()->sendMedia(peer, media);
}

quint64 CTelegramDispatcher::forwardMedia(const QString &identifier, quint32 messageId)
{
    if (!activeConnection()) {
        return 0;
    }
    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType == TLValue::InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return 0;
    }

    if (!m_knownMediaMessages.contains(messageId)) {
        return 0;
    }

    const TLMessage &message = m_knownMediaMessages.value(messageId);

    TLInputMedia media;

    switch (message.media.tlType) {
    case TLValue::MessageMediaPhoto:
        media.tlType = TLValue::InputMediaPhoto;
        media.id.tlType = TLValue::InputPhoto;
        media.id.id = message.media.photo.id;
        media.id.accessHash = message.media.photo.accessHash;
        break;
    case TLValue::MessageMediaAudio:
        media.tlType = TLValue::InputMediaAudio;
        media.id.tlType = TLValue::InputAudio;
        media.id.id = message.media.audio.id;
        media.id.accessHash = message.media.audio.accessHash;
        break;
    case TLValue::MessageMediaVideo:
        media.tlType = TLValue::InputMediaVideo;
        media.id.tlType = TLValue::InputVideo;
        media.id.id = message.media.video.id;
        media.id.accessHash = message.media.video.accessHash;
        break;
    case TLValue::MessageMediaDocument:
        media.tlType = TLValue::InputMediaDocument;
        media.id.tlType = TLValue::InputDocument;
        media.id.id = message.media.document.id;
        media.id.accessHash = message.media.document.accessHash;
        break;
    default:
        return 0;
        break;
    }

    qDebug() << Q_FUNC_INFO << identifier << messageId;
    return activeConnection()->sendMedia(peer, media);
}

bool CTelegramDispatcher::filterReceivedMessage(quint32 messageFlags) const
{
    return m_messageReceivingFilterFlags & messageFlags;
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

bool CTelegramDispatcher::addChatUser(quint32 publicChatId, const QString &contact, quint32 forwardMessages)
{
    if (!activeConnection()) {
        return false;
    }

    quint32 chatId = publicChatIdToChatId(publicChatId);

    if (!chatId) {
        return false;
    }

    const TLInputUser inputUser = phoneNumberToInputUser(contact);

    switch (inputUser.tlType) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
        return false;
    default:
        break;
    }

    activeConnection()->messagesAddChatUser(chatId, inputUser, forwardMessages);
    return true;
}

void CTelegramDispatcher::setTyping(const QString &identifier, bool typingStatus)
{
    if (!activeConnection()) {
        return;
    }
    if (typingStatus == m_localTypingMap.contains(identifier)) {
        return; // Avoid flood
    }

    TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType == TLValue::InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return;
    }

    TLSendMessageAction action;
    if (typingStatus) {
        action.tlType = TLValue::SendMessageTypingAction;
    } else {
        action.tlType = TLValue::SendMessageCancelAction;
    }

    activeConnection()->messagesSetTyping(peer, action);

    if (typingStatus) {
        m_localTypingMap.insert(identifier, s_localTypingDuration);
        ensureTypingUpdateTimer(s_localTypingDuration);
    } else {
        m_localTypingMap.remove(identifier);
    }
}

void CTelegramDispatcher::setMessageRead(const QString &identifier, quint32 messageId)
{
    if (!activeConnection()) {
        return;
    }
    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType != TLValue::InputPeerEmpty) {
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

void CTelegramDispatcher::checkUserName(const QString &userName)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->accountCheckUsername(userName);
}

void CTelegramDispatcher::setUserName(const QString &newUserName)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->accountUpdateUsername(newUserName);
}

TelegramNamespace::ContactStatus CTelegramDispatcher::contactStatus(const QString &phone) const
{
    const TLUser *user = identifierToUser(phone);

    if (user) {
        return decodeContactStatus(user->status.tlType);
    }

    return TelegramNamespace::ContactStatusUnknown;
}

quint32 CTelegramDispatcher::contactLastOnline(const QString &contact) const
{
    const TLUser *user = identifierToUser(contact);

    if (user) {
        switch (user->status.tlType) {
        case TLValue::UserStatusOnline:
            return user->status.expires;
        case TLValue::UserStatusOffline:
            return user->status.wasOnline;
        case TLValue::UserStatusRecently:
            return TelegramNamespace::ContactLastOnlineRecently;
        case TLValue::UserStatusLastWeek:
            return TelegramNamespace::ContactLastOnlineLastWeek;
        case TLValue::UserStatusLastMonth:
            return TelegramNamespace::ContactLastOnlineLastMonth;
        default:
            break;
        }
    }

    return TelegramNamespace::ContactLastOnlineUnknown;
}

QString CTelegramDispatcher::contactFirstName(const QString &contact) const
{
    const TLUser *user = identifierToUser(contact);

    if (user) {
        return user->firstName;
    } else {
        return QString();
    }
}

QString CTelegramDispatcher::contactLastName(const QString &contact) const
{
    const TLUser *user = identifierToUser(contact);

    if (user) {
        return user->lastName;
    } else {
        return QString();
    }
}

QString CTelegramDispatcher::contactUserName(const QString &contact) const
{
    const TLUser *user = identifierToUser(contact);

    if (user) {
        return user->username;
    } else {
        return QString();
    }
}

QString CTelegramDispatcher::contactAvatarToken(const QString &contact) const
{
    const TLUser *user = identifierToUser(contact);

    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unknown identifier" << maskPhoneNumber(contact);
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

void CTelegramDispatcher::whenUsersReceived(const QVector<TLUser> &users)
{
    qDebug() << Q_FUNC_INFO << users.count();
    foreach (const TLUser &user, users) {
        TLUser *existsUser = m_users.value(user.id);

        if (existsUser) {
            *existsUser = user;
        } else {
            m_users.insert(user.id, new TLUser(user));
        }

        if (user.tlType == TLValue::UserSelf) {
            m_selfUserId = user.id;

            continueInitialization(StepKnowSelf);
        }
    }
}

void CTelegramDispatcher::whenContactListReceived(const QList<quint32> &contactList)
{
    qDebug() << Q_FUNC_INFO << contactList;

    QList<quint32> newContactList = contactList;
    std::sort(newContactList.begin(), newContactList.end());

    if (m_contactList != newContactList) {
        m_contactList = newContactList;
        emit contactListChanged();
    }

    continueInitialization(StepContactList);
}

void CTelegramDispatcher::whenContactListChanged(const QList<quint32> &added, const QList<quint32> &removed)
{
    qDebug() << Q_FUNC_INFO << added << removed;
    QList<quint32> newContactList = m_contactList;

    // There is some redundant checks, but let's be paranoid
    foreach (const quint32 contact, added) {
        if (!newContactList.contains(contact)) {
            newContactList.append(contact);
        }
    }

    foreach (const quint32 contact, removed) {
        // We can use removeOne instead of remove All, because we warranty that there is no duplication
        newContactList.removeOne(contact);
    }

    std::sort(newContactList.begin(), newContactList.end());

    // There is no valid cases when lists are equal, but the check is (usually) cheap.
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

    const QList<QString> identifiers = m_localTypingMap.keys();
    foreach (const QString &identifier, identifiers) {
        int timeRemains = m_localTypingMap.value(identifier) - m_typingUpdateTimer->interval();
        if (timeRemains < 5) { // Let 5 ms be allowed correction
            m_localTypingMap.remove(identifier);
        } else {
            m_localTypingMap.insert(identifier, timeRemains);
            if (minTime > timeRemains) {
                minTime = timeRemains;
            }
        }
    }

    if (!m_userTypingMap.isEmpty() || !m_userChatTypingMap.isEmpty() || !m_localTypingMap.isEmpty()) {
        m_typingUpdateTimer->start(minTime);
    }
}

void CTelegramDispatcher::whenStatedMessageReceived(const TLMessagesStatedMessage &statedMessage, quint64 messageId)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << m_temporaryChatIdMap << statedMessage;
#else
    qDebug() << Q_FUNC_INFO << m_temporaryChatIdMap;
#endif

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

    switch (statedMessage.tlType) {
    case TLValue::MessagesStatedMessage:
        processMessageReceived(statedMessage.message);
        break;
    default:
        break;
    }

    ensureUpdateState(statedMessage.pts, statedMessage.seq);
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

void CTelegramDispatcher::getUser(quint32 id)
{
    TLInputUser user;
    user.tlType = TLValue::InputUserContact;
    user.userId = id;
    activeConnection()->usersGetUsers(QVector<TLInputUser>() << user);
}

void CTelegramDispatcher::getInitialUsers()
{
    QVector<TLInputUser> users;

    TLInputUser user;

    user.tlType = TLValue::InputUserSelf;
    users << user;

    user.tlType = TLValue::InputUserContact;
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
        continueInitialization(StepChatInfo);
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
    case TLValue::UpdatesDifference:
    case TLValue::UpdatesDifferenceSlice:
        qDebug() << Q_FUNC_INFO << "UpdatesDifference" << updatesDifference.newMessages.count();
        foreach (const TLChat &chat, updatesDifference.chats) {
            updateChat(chat);
        }

        foreach (const TLMessage &message, updatesDifference.newMessages) {
            if ((message.tlType != TLValue::MessageService) && (filterReceivedMessage(telegramMessageFlagsToPublicMessageFlags(message.flags)))) {
                continue;
            }

            processMessageReceived(message);
        }
        if (updatesDifference.tlType == TLValue::UpdatesDifference) {
            m_updatesState = updatesDifference.state;
        } else { // UpdatesDifferenceSlice
            m_updatesState = updatesDifference.intermediateState;
        }
        break;
    case TLValue::UpdatesDifferenceEmpty:
        qDebug() << Q_FUNC_INFO << "UpdatesDifferenceEmpty";

        // Try to update actual and local state in this weird case.
        QTimer::singleShot(10, this, SLOT(getUpdatesState()));
        return;
        break;
    default:
        qDebug() << Q_FUNC_INFO << "unknown diff type:" << updatesDifference.tlType.toString();
        break;
    }

    checkStateAndCallGetDifference();
}

void CTelegramDispatcher::whenMessagesChatsReceived(const QVector<TLChat> &chats, const QVector<TLUser> &users)
{
    qDebug() << Q_FUNC_INFO << chats.count();

    whenUsersReceived(users);

    foreach (const TLChat &chat, chats) {
        updateChat(chat);
    }

    continueInitialization(StepChatInfo);
}

void CTelegramDispatcher::whenMessagesFullChatReceived(const TLChatFull &chat, const QVector<TLChat> &chats, const QVector<TLUser> &users)
{
    Q_UNUSED(chats);

    whenUsersReceived(users);
    updateFullChat(chat);
}

void CTelegramDispatcher::setConnectionState(TelegramNamespace::ConnectionState state)
{
    qDebug() << Q_FUNC_INFO << state;

    if (m_connectionState == state) {
        return;
    }

    m_connectionState = state;
    emit connectionStateChanged(state);
}

quint32 CTelegramDispatcher::requestFile(const FileRequestDescriptor &descriptor)
{
    if (!descriptor.isValid()) {
        return 0;
    }

    m_requestedFileDescriptors.insert(++m_fileRequestCounter, descriptor);

    CTelegramConnection *connection = m_connections.value(descriptor.dcId());

    if (connection && (connection->authState() == CTelegramConnection::AuthStateSignedIn)) {
        processFileRequestForConnection(connection, m_fileRequestCounter);
    } else {
        ensureSignedConnection(descriptor.dcId());
    }

    return m_fileRequestCounter;
}

void CTelegramDispatcher::processFileRequestForConnection(CTelegramConnection *connection, quint32 requestId)
{
    const FileRequestDescriptor descriptor = m_requestedFileDescriptors.value(requestId);
    qDebug() << Q_FUNC_INFO << requestId << descriptor.type();

    switch (descriptor.type()) {
    case FileRequestDescriptor::Avatar:
        connection->downloadFile(descriptor.inputLocation(), /* offset */ 0, /* limit */ 512 * 256, requestId); // Limit setted to some big number to download avatar at once
        break;
    case FileRequestDescriptor::MessageMediaData:
        connection->downloadFile(descriptor.inputLocation(), descriptor.offset(), m_mediaDataBufferSize, requestId);
        break;
    case FileRequestDescriptor::Upload:
        connection->uploadFile(descriptor.fileId(), descriptor.part(), descriptor.data(), requestId);
        break;
    default:
        break;
    }
}

inline bool ensureDcOption(QVector<TLDcOption> *vector, const TLDcOption &option)
{
    for (int i = 0; i < vector->count(); ++i) {
        if (vector->at(i).id == option.id) {
            vector->replace(i, option);
            return true;
        }
    }

    return false;
}

void CTelegramDispatcher::processUpdate(const TLUpdate &update)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << update;
#endif

    switch (update.tlType) {
    case TLValue::UpdateNewMessage:
        qDebug() << Q_FUNC_INFO << "UpdateNewMessage";
        processMessageReceived(update.message);
        ensureUpdateState(update.pts);
        break;
//    case TLValue::UpdateMessageID:
//        update.id;
//        update.randomId;
//        break;
    case TLValue::UpdateReadMessages:
        foreach (quint32 messageId, update.messages) {
            const QPair<QString, quint64> phoneAndId = m_messagesMap.value(messageId);
            emit sentMessageStatusChanged(phoneAndId.first, phoneAndId.second, TelegramNamespace::MessageDeliveryStatusRead);
        }
        ensureUpdateState(update.pts);
        break;
//    case TLValue::UpdateDeleteMessages:
//        update.messages;
//        ensureUpdateState(update.pts);
//        break;
//    case TLValue::UpdateRestoreMessages:
//        update.messages;
//        ensureUpdateState(update.pts);
//        break;
    case TLValue::UpdateUserTyping:
        if (m_users.contains(update.userId)) {
            emit contactTypingStatusChanged(userIdToIdentifier(update.userId), update.action.tlType == TLValue::SendMessageTypingAction);
#if QT_VERSION >= 0x050000
            m_userTypingMap.insert(update.userId, m_typingUpdateTimer->remainingTime() + s_userTypingActionPeriod);
#else
            m_userTypingMap.insert(update.userId, s_userTypingActionPeriod); // Missed timer remaining time method can leads to typing time period deviation.
#endif
            ensureTypingUpdateTimer(s_userTypingActionPeriod);
        }
        break;
    case TLValue::UpdateChatUserTyping:
        if (m_users.contains(update.userId)) {
            emit contactChatTypingStatusChanged(telegramChatIdToPublicId(update.chatId), userIdToIdentifier(update.userId),
                                                update.action.tlType == TLValue::SendMessageTypingAction);
            const QPair<quint32,quint32> key(telegramChatIdToPublicId(update.chatId), update.userId);
#if QT_VERSION >= 0x050000
            m_userChatTypingMap.insert(key, m_typingUpdateTimer->remainingTime() + s_userTypingActionPeriod);
#else
            m_userChatTypingMap.insert(key, s_userTypingActionPeriod); // Missed timer remaining time method can leads to typing time period deviation.
#endif
            ensureTypingUpdateTimer(s_userTypingActionPeriod);
        }
        break;
    case TLValue::UpdateChatParticipants: {
        TLChatFull newChatState = m_chatFullInfo.value(update.participants.chatId);
        newChatState.id = update.participants.chatId; // newChatState can be newly created emtpy chat
        newChatState.participants = update.participants;
        updateFullChat(newChatState);

        qDebug() << Q_FUNC_INFO << "chat id resolved to" << update.participants.chatId;
        break;
    }
    case TLValue::UpdateUserStatus: {
        if (update.userId == m_selfUserId) {
            break;
        }

        TLUser *user = m_users.value(update.userId);
        if (user) {
            user->status = update.status;
            emit contactStatusChanged(userIdToIdentifier(update.userId), decodeContactStatus(user->status.tlType));
        }
        break;
    }
    case TLValue::UpdateUserName: {
        TLUser *user = m_users.value(update.userId);
        if (user) {
            bool changed = (user->firstName == update.firstName) && (user->lastName == update.lastName);
            if (changed) {
                user->firstName = update.firstName;
                user->lastName = update.lastName;
                emit contactProfileChanged(userIdToIdentifier(user->id));
            }
        }
        break;
    }
//    case TLValue::UpdateUserPhoto:
//        update.userId;
//        update.date;
//        update.photo;
//        update.previous;
//        break;
//    case TLValue::UpdateContactRegistered:
//        update.userId;
//        update.date;
//        break;
//    case TLValue::UpdateContactLink:
//        update.userId;
//        update.myLink;
//        update.foreignLink;
//        break;
//    case TLValue::UpdateActivation:
//        update.userId;
//        break;
//    case TLValue::UpdateNewAuthorization:
//        update.authKeyId;
//        update.date;
//        update.device;
//        update.location;
//        break;
//    case TLValue::UpdateNewGeoChatMessage:
//        update.message;
//        break;
//    case TLValue::UpdateNewEncryptedMessage:
//        update.message;
//        update.qts;
//        break;
//    case TLValue::UpdateEncryptedChatTyping:
//        update.chatId;
//        break;
//    case TLValue::UpdateEncryption:
//        update.chat;
//        update.date;
//        break;
//    case TLValue::UpdateEncryptedMessagesRead:
//        update.chatId;
//        update.maxDate;
//        update.date;
//        break;
//    case TLValue::UpdateChatParticipantAdd:
//        update.chatId;
//        update.userId;
//        update.inviterId;
//        update.version;
//        break;
//    case TLValue::UpdateChatParticipantDelete:
//        update.chatId;
//        update.userId;
//        update.version;
//        break;
    case TLValue::UpdateDcOptions: {
        int dcUpdatesReplaced = 0;
        int dcUpdatesInserted = 0;
        foreach (const TLDcOption &option, update.dcOptions) {
            if (ensureDcOption(&m_dcConfiguration, option)) {
                ++dcUpdatesReplaced;
            } else {
                ++dcUpdatesInserted;
            }
        }

        qDebug() << Q_FUNC_INFO << "Dc configuration update replaces" << dcUpdatesReplaced << "options (" << dcUpdatesInserted << "options inserted).";
        break;
    }
//    case TLValue::UpdateUserBlocked:
//        update.userId;
//        update.blocked;
//        break;
//    case TLValue::UpdateNotifySettings:
//        update.peer;
//        update.notifySettings;
//        break;
    default:
        qDebug() << Q_FUNC_INFO << "Update type" << update.tlType.toString() << "is not implemented yet.";
        break;
    }
}

void CTelegramDispatcher::processMessageReceived(const TLMessage &message)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << message;
#endif
    if (message.tlType == TLValue::MessageEmpty) {
        return;
    }

    if (message.tlType == TLValue::MessageService) {
        const TLMessageAction &action = message.action;

        const quint32 chatId = message.toId.chatId;
        TLChat chat = m_chatInfo.value(chatId);
        TLChatFull fullChat = m_chatFullInfo.value(chatId);

        chat.id = chatId;
        fullChat.id = chatId;

        switch (action.tlType) {
        case TLValue::MessageActionChatCreate:
            chat.title = action.title;
            chat.participantsCount = action.users.count();
            updateChat(chat);
            break;
        case TLValue::MessageActionChatAddUser: {
            TLVector<TLChatParticipant> participants = fullChat.participants.participants;
            for (int i = 0; i < participants.count(); ++i) {
                if (participants.at(i).userId == action.userId) {
                    return;
                }
            }

            TLChatParticipant newParticipant;
            newParticipant.userId = action.userId;
            participants.append(newParticipant);

            fullChat.participants.participants = participants;
            chat.participantsCount = participants.count();
            updateChat(chat);
            updateFullChat(fullChat);
            }
            break;
        case TLValue::MessageActionChatDeleteUser: {
            TLVector<TLChatParticipant> participants = fullChat.participants.participants;
            for (int i = 0; i < participants.count(); ++i) {
                if (participants.at(i).userId == action.userId) {
                    participants.remove(i);
                    break;
                }
            }

            fullChat.participants.participants = participants;
            chat.participantsCount = participants.count();
            updateChat(chat);
            updateFullChat(fullChat);
            }
            break;
        case TLValue::MessageActionChatEditTitle:
            chat.title = action.title;
            updateChat(chat);
            break;
        case TLValue::MessageActionChatEditPhoto:
        case TLValue::MessageActionChatDeletePhoto:
            fullChat.chatPhoto = action.photo;
            updateFullChat(fullChat);
            break;
        default:
            break;
        }
        return;
    }

    TelegramNamespace::MessageFlags messageFlags = telegramMessageFlagsToPublicMessageFlags(message.flags);
    const TelegramNamespace::MessageType messageType = telegramMessageTypeToPublicMessageType(message.media.tlType);

    if (!(messageType & m_acceptableMessageTypes)) {
        return;
    }

    if (message.media.tlType != TLValue::MessageMediaEmpty) {
        m_knownMediaMessages.insert(message.id, message);
    }

    TelegramNamespace::Message apiMessage;

    if ((message.toId.tlType == TLValue::PeerChat) || (messageFlags & TelegramNamespace::MessageFlagOut)) {
        apiMessage.peer = peerToIdentifier(message.toId);
    } else {
        apiMessage.peer = userIdToIdentifier(message.fromId);
    }

    apiMessage.contact = userIdToIdentifier(message.fromId);
    apiMessage.type = messageType;
    apiMessage.text = message.message;
    apiMessage.id = message.id;
    apiMessage.timestamp = message.date;
    apiMessage.flags = messageFlags;

    emit messageReceived(apiMessage);

#ifndef TELEGRAMQT_NO_DEPRECATED
    if (message.toId.tlType == TLValue::PeerUser) {
        quint32 contactUserId = messageFlags & TelegramNamespace::MessageFlagOut ? message.toId.userId : message.fromId;
        emit messageReceived(userIdToIdentifier(contactUserId),
                             message.message, messageType, message.id, messageFlags, message.date);
    } else {
        emit chatMessageReceived(telegramChatIdToPublicId(message.toId.chatId), userIdToIdentifier(message.fromId),
                                 message.message, messageType, message.id, messageFlags, message.date);
    }
#endif
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

quint32 CTelegramDispatcher::publicChatIdToChatId(quint32 publicChatId) const
{
    if (int(publicChatId) >= m_chatIds.count()) {
        qDebug() << Q_FUNC_INFO << "Unknown public chat id" << publicChatId;
        return 0;
    }

    return m_chatIds.at(publicChatId);
}

TLInputPeer CTelegramDispatcher::publicChatIdToInputPeer(quint32 publicChatId) const
{
    TLInputPeer inputPeer;

    quint32 chatId = publicChatIdToChatId(publicChatId);

    if (!chatId) {
        return inputPeer;
    }

    inputPeer.tlType = TLValue::InputPeerChat;
    inputPeer.chatId = chatId;

    return inputPeer;
}

TLInputPeer CTelegramDispatcher::identifierToInputPeer(const QString &identifier) const
{
    TLInputPeer inputPeer;

    if (identifier.startsWith(QLatin1String("chat"))) {
        quint32 publicChatId = identifier.section(QLatin1String("chat"), 1).toUInt();
        return publicChatIdToInputPeer(publicChatId);
    }
    quint32 userId = identifierToUserId(identifier);

    if (userId == m_selfUserId) {
        inputPeer.tlType = TLValue::InputPeerSelf;
        return inputPeer;
    }

    const TLUser *user = m_users.value(userId);

    if (user) {
        if (user->tlType == TLValue::UserContact) {
            inputPeer.tlType = TLValue::InputPeerContact;
            inputPeer.userId = user->id;
        } else if (user->tlType == TLValue::UserForeign) {
            inputPeer.tlType = TLValue::InputPeerForeign;
            inputPeer.userId = user->id;
            inputPeer.accessHash = user->accessHash;
        } else if (user->tlType == TLValue::UserRequest) {
            inputPeer.tlType = TLValue::InputPeerContact; // TODO: Check if there should be InputPeerForeign. Seems like working as-is; can't test at this time.
            inputPeer.userId = user->id;
            inputPeer.accessHash = user->accessHash; // Seems to be useless.
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown user type: " << user->tlType.toString();
        }
    } else {
        if (userId) {
            // Guess contact
            inputPeer.tlType = TLValue::InputPeerContact;
            inputPeer.userId = userId;
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown user: " << maskPhoneNumber(identifier);
        }
    }

    return inputPeer;
}

TLInputUser CTelegramDispatcher::phoneNumberToInputUser(const QString &phoneNumber) const
{
    TLInputUser inputUser;

    if (phoneNumber == selfPhone()) {
        inputUser.tlType = TLValue::InputUserSelf;
        return inputUser;
    }

    const TLUser *user = identifierToUser(phoneNumber);

    if (user) {
        if (user->tlType == TLValue::UserContact) {
            inputUser.tlType = TLValue::InputUserContact;
            inputUser.userId = user->id;
        } else if (user->tlType == TLValue::UserForeign) {
            inputUser.tlType = TLValue::InputUserForeign;
            inputUser.userId = user->id;
            inputUser.accessHash = user->accessHash;
        } else if (user->tlType == TLValue::UserRequest) { // TODO: Check if there should be InputPeerForeign. Seems like working as-is; can't test at this time.
            inputUser.tlType = TLValue::InputUserContact;
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

    return QString(QLatin1String("user%1")).arg(id);
}

QString CTelegramDispatcher::chatIdToIdentifier(const quint32 id) const
{
    return QString(QLatin1String("chat%1")).arg(id);
}

QString CTelegramDispatcher::peerToIdentifier(const TLPeer &peer) const
{
    switch (peer.tlType) {
    case TLValue::PeerChat:
        return chatIdToIdentifier(telegramChatIdToPublicId(peer.chatId));
    case TLValue::PeerUser:
        return userIdToIdentifier(peer.userId);
    default:
        break;
    }

    qDebug() << Q_FUNC_INFO << "Unknown peer type";
    return QString();
}

quint32 CTelegramDispatcher::identifierToUserId(const QString &identifier) const
{
    if (identifier.startsWith(QLatin1String("user"))) {
        return identifier.section(QLatin1String("user"), 1).toUInt();
    }

    foreach (const TLUser *user, m_users) {
        if (user->phone == identifier) {
            return user->id;
        }
    }

    return 0;
}

TLUser *CTelegramDispatcher::identifierToUser(const QString &identifier) const
{
    return m_users.value(identifierToUserId(identifier));
}

QString CTelegramDispatcher::userAvatarToken(const TLUser *user) const
{
    const TLFileLocation &avatar = user->photo.photoSmall;

    if (avatar.tlType == TLValue::FileLocationUnavailable) {
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
    case TLValue::UserStatusEmpty:
        return TelegramNamespace::ContactStatusUnknown;
    case TLValue::UserStatusOnline:
        return TelegramNamespace::ContactStatusOnline;
    case TLValue::UserStatusOffline:
        return TelegramNamespace::ContactStatusOffline;
    }
}

void CTelegramDispatcher::whenConnectionAuthChanged(int newState, quint32 dc)
{
    qDebug() << Q_FUNC_INFO << "auth" << newState << "dc" << dc;
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    if (connection == activeConnection()) {
        if (newState == CTelegramConnection::AuthStateSignedIn) {
            connect(connection, SIGNAL(usersReceived(QVector<TLUser>)),
                    SLOT(whenUsersReceived(QVector<TLUser>)));
            connect(connection, SIGNAL(contactListReceived(QList<quint32>)),
                    SLOT(whenContactListReceived(QList<quint32>)));
            connect(connection, SIGNAL(contactListChanged(QList<quint32>,QList<quint32>)),
                    SLOT(whenContactListChanged(QList<quint32>,QList<quint32>)));
            connect(connection, SIGNAL(updatesReceived(TLUpdates)),
                    SLOT(whenUpdatesReceived(TLUpdates)));
            connect(connection, SIGNAL(messageSentInfoReceived(TLInputPeer,quint64,quint32,quint32,quint32,quint32)),
                    SLOT(whenMessageSentInfoReceived(TLInputPeer,quint64,quint32,quint32,quint32,quint32)));
            connect(connection, SIGNAL(statedMessageReceived(TLMessagesStatedMessage,quint64)),
                    SLOT(whenStatedMessageReceived(TLMessagesStatedMessage,quint64)));
            connect(connection, SIGNAL(updatesStateReceived(TLUpdatesState)),
                    SLOT(whenUpdatesStateReceived(TLUpdatesState)));
            connect(connection, SIGNAL(updatesDifferenceReceived(TLUpdatesDifference)),
                    SLOT(whenUpdatesDifferenceReceived(TLUpdatesDifference)));
            connect(connection, SIGNAL(authExportedAuthorizationReceived(quint32,quint32,QByteArray)),
                    SLOT(whenAuthExportedAuthorizationReceived(quint32,quint32,QByteArray)));
            connect(connection, SIGNAL(messagesChatsReceived(QVector<TLChat>,QVector<TLUser>)),
                    SLOT(whenMessagesChatsReceived(QVector<TLChat>,QVector<TLUser>)));
            connect(connection, SIGNAL(messagesFullChatReceived(TLChatFull,QVector<TLChat>,QVector<TLUser>)),
                    SLOT(whenMessagesFullChatReceived(TLChatFull,QVector<TLChat>,QVector<TLUser>)));
            connect(connection, SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::AccountUserNameStatus)),
                    SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::AccountUserNameStatus)));
            connect(connection, SIGNAL(loggedOut(bool)),
                    SIGNAL(loggedOut(bool)));

            continueInitialization(StepSignIn);
        } else if (newState == CTelegramConnection::AuthStateSuccess) {
            continueInitialization(StepFirst); // Start initialization, if it is not started yet.
        }
    } else {
        if (newState == CTelegramConnection::AuthStateSignedIn) {
            foreach (quint32 fileId, m_requestedFileDescriptors.keys()) {
                if (m_requestedFileDescriptors.value(fileId).dcId() != dc) {
                    continue;
                }

                processFileRequestForConnection(connection, fileId);
            }
        } else if (newState == CTelegramConnection::AuthStateSuccess) {
            ensureSignedConnection(dc);
        }
    }

    if (newState >= CTelegramConnection::AuthStateSuccess) {
        if (m_wantedActiveDc == dc) {
            setActiveDc(dc);
        }

        if (m_delayedPackages.contains(dc)) {
            qDebug() << Q_FUNC_INFO << "process" << m_delayedPackages.count(dc) << "redirected packages" << "for dc" << dc;
            foreach (const QByteArray &data, m_delayedPackages.values(dc)) {
                connection->processRedirectedPackage(data);
            }
            m_delayedPackages.remove(dc);
        }

        if (connection == activeConnection()) {
            continueInitialization(StepFirst);
        }
    }
}

void CTelegramDispatcher::whenConnectionStatusChanged(int newStatus, quint32 dc)
{
    qDebug() << Q_FUNC_INFO << "status" << newStatus << "dc" << dc;
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection == activeConnection()) {
        if (newStatus == CTelegramConnection::ConnectionStatusDisconnected) {
            if (connectionState() == TelegramNamespace::ConnectionStateConnecting) {
                // We are connecting and there is Connecting->Disconnected changes in CTelegramConnection.
                // Consider it as network error; try to reconnect after a second.
                QTimer::singleShot(1000, connection, SLOT(connectToDc()));
            } else {
                setConnectionState(TelegramNamespace::ConnectionStateDisconnected);

                if (m_autoReconnectionEnabled) {
                    connection->connectToDc();
                }
            }
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

    continueInitialization(StepDcConfiguration);
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
    qDebug() << Q_FUNC_INFO << dc;
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() >= CTelegramConnection::AuthStateSuccess) {
        setActiveDc(dc);
    } else {
        m_wantedActiveDc = dc;
        establishConnectionToDc(dc);
    }
}

void CTelegramDispatcher::whenFileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset)
{
    if (!m_requestedFileDescriptors.contains(requestId)) {
        qDebug() << Q_FUNC_INFO << "Unexpected requestId" << requestId;
        return;
    }

    const QString mimeType = mimeTypeByStorageFileType(file.type.tlType);
    FileRequestDescriptor &descriptor = m_requestedFileDescriptors[requestId];

    const quint32 chunkSize = file.bytes.size();

    switch (descriptor.type()) {
    case FileRequestDescriptor::Avatar:
        if (m_users.contains(descriptor.userId())) {
            emit avatarReceived(userIdToIdentifier(descriptor.userId()), file.bytes, mimeType, userAvatarToken(m_users.value(descriptor.userId())));
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown userId" << descriptor.userId();
        }
        break;
    case FileRequestDescriptor::MessageMediaData:
        if (m_knownMediaMessages.contains(descriptor.messageId())) {
            const TLMessage message = m_knownMediaMessages.value(descriptor.messageId());
            const quint32 messageFlags = telegramMessageFlagsToPublicMessageFlags(message.flags);
            const TelegramNamespace::MessageType messageType = telegramMessageTypeToPublicMessageType(message.media.tlType);

            quint32 contactUserId = messageFlags & TelegramNamespace::MessageFlagOut ? message.toId.userId : message.fromId;
#ifdef DEVELOPER_BUILD
            qDebug() << Q_FUNC_INFO << "MessageMediaData:" << message.id << offset << "-" << offset + chunkSize << "/" << descriptor.size();
#endif
            emit messageMediaDataReceived(userIdToIdentifier(contactUserId), message.id, file.bytes, mimeType, messageType, offset, descriptor.size());
        } else {
            qDebug() << Q_FUNC_INFO << "Unknown media message data received" << descriptor.messageId();
        }

        if (descriptor.offset() + chunkSize == descriptor.size()) {
#ifdef DEVELOPER_BUILD
            qDebug() << Q_FUNC_INFO << "file" << requestId << "received.";
#endif
            m_requestedFileDescriptors.remove(requestId);
        } else {
            descriptor.setOffset(offset + chunkSize);

            CTelegramConnection *connection = qobject_cast<CTelegramConnection*>(sender());
            if (connection) {
                processFileRequestForConnection(connection, requestId);
            } else {
                qDebug() << Q_FUNC_INFO << "Invalid call. The method must be called only on CTelegramConnection signal.";
            }
        }
    default:
        break;
    }
}

void CTelegramDispatcher::whenFileDataUploaded(quint32 requestId)
{
    if (!m_requestedFileDescriptors.contains(requestId)) {
        qDebug() << Q_FUNC_INFO << "Unexpected fileId" << requestId;
        return;
    }

    FileRequestDescriptor &descriptor = m_requestedFileDescriptors[requestId];

    if (descriptor.type() != FileRequestDescriptor::Upload) {
        return;
    }

    descriptor.bumpPart();

    emit uploadingStatusUpdated(requestId, descriptor.offset(), descriptor.size());

    if (descriptor.finished()) {
        return;
    }

    CTelegramConnection *connection = qobject_cast<CTelegramConnection*>(sender());
    if (connection) {
        processFileRequestForConnection(connection, requestId);
    } else {
        qDebug() << Q_FUNC_INFO << "Invalid call. The method must be called only on CTelegramConnection signal.";
    }
}

void CTelegramDispatcher::whenUpdatesReceived(const TLUpdates &updates)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << updates;
#else
    qDebug() << Q_FUNC_INFO;
#endif
    switch (updates.tlType) {
    case TLValue::UpdatesTooLong:
        getUpdatesState();
        break;
    case TLValue::UpdateShortMessage:
    case TLValue::UpdateShortChatMessage:
    {
        TLMessage shortMessage;
        shortMessage.tlType = TLValue::Message;
        shortMessage.id = updates.id;
        shortMessage.flags = TelegramMessageFlagUnread;
        shortMessage.fromId = updates.fromId;
        shortMessage.message = updates.message;
        shortMessage.date = updates.date;
        shortMessage.media.tlType = TLValue::MessageMediaEmpty;

        if (updates.tlType == TLValue::UpdateShortMessage) {
            shortMessage.toId.tlType = TLValue::PeerUser;
            processMessageReceived(shortMessage);

            const QString phone = userIdToIdentifier(updates.fromId);
            if (!phone.isEmpty()) {
                if (m_userTypingMap.value(updates.fromId, 0) > 0) {
                    m_userTypingMap.remove(updates.fromId);
                    emit contactTypingStatusChanged(phone, /* typingStatus */ false);
                }
            }
        } else {
            shortMessage.toId.tlType = TLValue::PeerChat;
            shortMessage.toId.chatId = updates.chatId;
            processMessageReceived(shortMessage);

            const QString phone = userIdToIdentifier(updates.fromId);
            const quint32 publicChatId = telegramChatIdToPublicId(updates.chatId);
            const QPair<quint32,quint32> key(publicChatId, updates.fromId);

            if (m_userChatTypingMap.contains(key)) {
                m_userChatTypingMap.remove(key);
                emit contactChatTypingStatusChanged(publicChatId, phone, /* typingStatus */ false);
            }
        }
    }
        ensureUpdateState(updates.pts);
        break;
    case TLValue::UpdateShort:
        processUpdate(updates.update);
        break;
    case TLValue::UpdatesCombined:
        qDebug() << Q_FUNC_INFO << "UpdatesCombined processing is not implemented yet.";
        break;
    case TLValue::Updates:
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
    if (connection && (connection->authState() == CTelegramConnection::AuthStateSuccess)) {
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

    if (m_connections.value(dc)) {
        m_connections.value(dc)->setKeepAliveInterval(m_pingInterval);
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

void CTelegramDispatcher::continueInitialization(CTelegramDispatcher::InitializationStep justDone)
{
    qDebug() << Q_FUNC_INFO << justDone;

    if (justDone && ((m_initializationState | justDone) == m_initializationState)) {
        return; // Nothing new
    }

    m_initializationState = InitializationStep(m_initializationState|justDone);

    if (!(m_requestedSteps & StepDcConfiguration)) { // DC configuration is not requested yet
        getDcConfiguration();
        m_requestedSteps |= StepDcConfiguration;
    }

    if (!(m_initializationState & StepDcConfiguration)) { // DC configuration is unknown yet
        return;
    }

    if (justDone == StepDcConfiguration) {
        if (activeConnection()->authState() == CTelegramConnection::AuthStateSuccess) {
            setConnectionState(TelegramNamespace::ConnectionStateAuthRequired);
        } else {
            setConnectionState(TelegramNamespace::ConnectionStateConnected);
        }
    }

    if ((m_initializationState & StepDcConfiguration) && (m_initializationState & StepSignIn)) {
        setConnectionState(TelegramNamespace::ConnectionStateAuthenticated);

        if (!(m_requestedSteps & StepKnowSelf)) {
            getInitialUsers();
            m_requestedSteps |= StepKnowSelf;
        }

        if (!(m_requestedSteps & StepContactList)) {
            getContacts();
            m_requestedSteps |= StepContactList;
        }

        if (!(m_requestedSteps & StepChatInfo)) {
            getChatsInfo();
            m_requestedSteps |= StepChatInfo;
        }
    }

    if (m_initializationState == StepDone) {
        setConnectionState(TelegramNamespace::ConnectionStateReady);
        return;
    }

    if ((m_initializationState & StepContactList) && (m_initializationState & StepKnowSelf)) {
        // We need to know users (contact list and self) info to properly process updates.
        if (!(m_requestedSteps & StepUpdates)) {
            getUpdatesState();
            m_requestedSteps |= StepUpdates;
        }
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

// Basically we just revert Unread and Read flag.
TelegramNamespace::MessageFlags CTelegramDispatcher::telegramMessageFlagsToPublicMessageFlags(quint32 tgFlags)
{
    TelegramNamespace::MessageFlags result = TelegramNamespace::MessageFlagNone;

    if (tgFlags & TelegramMessageFlagOut) {
        result |= TelegramNamespace::MessageFlagOut;
    }

    if (!(tgFlags & TelegramMessageFlagUnread)) {
        result |= TelegramNamespace::MessageFlagRead;
    }

    return result;
}

void CTelegramDispatcher::ensureUpdateState(quint32 pts, quint32 seq, quint32 date)
{
    if (m_updatesStateIsLocked) {
        /* Prevent m_updateState from updating before UpdatesGetState answer receiving to avoid
         * m_updateState <-> m_actualState messing (which may lead to ignore offline-messages) */
        return;
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
        continueInitialization(StepUpdates);
    }
}

CTelegramConnection *CTelegramDispatcher::createConnection(const TLDcOption &dc)
{
    CTelegramConnection *connection = new CTelegramConnection(m_appInformation, this);

    connect(connection, SIGNAL(authStateChanged(int,quint32)), SLOT(whenConnectionAuthChanged(int,quint32)));
    connect(connection, SIGNAL(statusChanged(int,quint32)), SLOT(whenConnectionStatusChanged(int,quint32)));
    connect(connection, SIGNAL(dcConfigurationReceived(quint32)), SLOT(whenDcConfigurationUpdated(quint32)));
    connect(connection, SIGNAL(actualDcIdReceived(quint32,quint32)), SLOT(whenConnectionDcIdUpdated(quint32,quint32)));
    connect(connection, SIGNAL(newRedirectedPackage(QByteArray,quint32)), SLOT(whenPackageRedirected(QByteArray,quint32)));
    connect(connection, SIGNAL(wantedActiveDcChanged(quint32)), SLOT(whenWantedActiveDcChanged(quint32)));

    connect(connection, SIGNAL(phoneStatusReceived(QString,bool,bool)), SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(connection, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(connection,
            SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)),
            SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)));
    connect(connection, SIGNAL(authorizationErrorReceived()), SIGNAL(authorizationErrorReceived()));

    connect(connection, SIGNAL(fileDataReceived(TLUploadFile,quint32,quint32)), SLOT(whenFileDataReceived(TLUploadFile,quint32,quint32)));

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

    if (!connection->status() < CTelegramConnection::ConnectionStatusConnected) {
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

    if (connection && (connection->status() != CTelegramConnection::ConnectionStatusDisconnected)) {
        if (connection->authState() == CTelegramConnection::AuthStateSuccess) {
            if (m_exportedAuthentications.contains(dc)) {
                connection->authImportAuthorization(m_exportedAuthentications.value(dc).first, m_exportedAuthentications.value(dc).second);
            } else {
                if (activeConnection()->authState() == CTelegramConnection::AuthStateSignedIn) {
                    activeConnection()->authExportAuthorization(dc);
                }
            }
        }
    } else {
        establishConnectionToDc(dc);
    }
}

TLDcOption CTelegramDispatcher::dcInfoById(quint32 dc) const
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
    case TLValue::StorageFileJpeg:
        return QLatin1String("image/jpeg");
    case TLValue::StorageFileGif:
        return QLatin1String("image/gif");
    case TLValue::StorageFilePng:
        return QLatin1String("image/png");
    case TLValue::StorageFilePdf:
        return QLatin1String("application/pdf");
    case TLValue::StorageFileMp3:
        return QLatin1String("audio/mpeg");
    case TLValue::StorageFileMov:
        return QLatin1String("video/quicktime");
    case TLValue::StorageFileMp4:
        return QLatin1String("audio/mp4");
    case TLValue::StorageFileWebp:
        return QLatin1String("image/webp");
    default:
        return QString();
    }
}

TelegramNamespace::MessageType CTelegramDispatcher::telegramMessageTypeToPublicMessageType(TLValue type)
{
    switch (type) {
    case TLValue::MessageMediaEmpty:
        return TelegramNamespace::MessageTypeText;
    case TLValue::MessageMediaPhoto:
        return TelegramNamespace::MessageTypePhoto;
    case TLValue::MessageMediaVideo:
        return TelegramNamespace::MessageTypeVideo;
    case TLValue::MessageMediaGeo:
        return TelegramNamespace::MessageTypeGeo;
    case TLValue::MessageMediaContact:
        return TelegramNamespace::MessageTypeContact;
    case TLValue::MessageMediaAudio:
        return TelegramNamespace::MessageTypeAudio;
    case TLValue::MessageMediaDocument:
        return TelegramNamespace::MessageTypeDocument;
    default:
        return TelegramNamespace::MessageTypeUnsupported;
    }
}
