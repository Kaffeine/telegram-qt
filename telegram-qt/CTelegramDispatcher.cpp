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
#include "TelegramNamespace_p.hpp"
#include "CTelegramConnection.hpp"
#include "CTelegramStream.hpp"
#include "Utils.hpp"
#include "TelegramUtils.hpp"

using namespace TelegramUtils;

#include <QTimer>

#include <QCryptographicHash>
#include <QDebug>
#if QT_VERSION < 0x048000
#include <algorithm>
#endif

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

static const QVector<TelegramNamespace::DcOption> s_builtInDcs = QVector<TelegramNamespace::DcOption>()
        << TelegramNamespace::DcOption(QLatin1String("149.1.175.50") , 443)
        << TelegramNamespace::DcOption(QLatin1String("149.154.167.51") , 443)
        << TelegramNamespace::DcOption(QLatin1String("149.154.175.100"), 443)
        << TelegramNamespace::DcOption(QLatin1String("149.154.167.91") , 443)
        << TelegramNamespace::DcOption(QLatin1String("149.154.171.5")  , 443);

static const quint32 s_defaultPingInterval = 15000; // 15 sec

const quint32 secretFormatVersion = 3;
const int s_userTypingActionPeriod = 6000; // 6 sec
const int s_localTypingDuration = 5000; // 5 sec
const int s_localTypingRecommendedRepeatInterval = 400; // (s_userTypingActionPeriod - s_localTypingDuration) / 2. Minus 100 ms for insurance.

static const int s_autoConnectionIndexInvalid = -1; // App logic rely on (s_autoConnectionIndexInvalid + 1 == 0)

#if QT_VERSION < 0x050000
const int s_timerMaxInterval = 500; // 0.5 sec. Needed to limit max possible typing time deviation in Qt4 by this value.
#endif

enum TelegramMessageFlags {
    TelegramMessageFlagNone    = 0,
    TelegramMessageFlagUnread  = 1 << 0,
    TelegramMessageFlagOut     = 1 << 1,
    TelegramMessageFlagForward = 1 << 2,
    TelegramMessageFlagReply   = 1 << 3,
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
    m_pingInterval(s_defaultPingInterval),
    m_mediaDataBufferSize(128 * 256), // 128 KB
    m_initializationState(0),
    m_requestedSteps(0),
    m_activeDc(0),
    m_wantedActiveDc(0),
    m_autoConnectionDcIndex(s_autoConnectionIndexInvalid),
    m_updatesStateIsLocked(false),
    m_selfUserId(0),
    m_fileRequestCounter(0),
    m_typingUpdateTimer(new QTimer(this))
{
    m_typingUpdateTimer->setSingleShot(true);
    connect(m_typingUpdateTimer, SIGNAL(timeout()), SLOT(messageActionTimerTimeout()));
}

CTelegramDispatcher::~CTelegramDispatcher()
{
    qDeleteAll(m_connections);
    qDeleteAll(m_users);
}

QVector<TelegramNamespace::DcOption> CTelegramDispatcher::builtInDcs()
{
    return s_builtInDcs;
}

quint32 CTelegramDispatcher::defaultPingInterval()
{
    return s_defaultPingInterval;
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

QVector<quint32> CTelegramDispatcher::publicChatIdList() const
{
    QVector<quint32> result;
    for (int i = 0; i < m_chatIds.count(); ++i) {
        result << i + 1; // Skip 0 index as an invalid public chat id value.
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
    if (!activeConnection() || activeConnection()->authKey().isEmpty()) {
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

void CTelegramDispatcher::setPingInterval(quint32 ms, quint32 serverDisconnectionAdditionTime)
{
    m_pingInterval = ms;
    if (serverDisconnectionAdditionTime < 500) {
        serverDisconnectionAdditionTime = 500;
    }
    m_pingServerAdditionDisconnectionTime = serverDisconnectionAdditionTime;
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

bool CTelegramDispatcher::initConnection(const QVector<TelegramNamespace::DcOption> &dcs)
{
    if (!dcs.isEmpty()) {
        m_connectionAddresses = dcs;
    } else {
        m_connectionAddresses = s_builtInDcs;
    }

    initConnectionSharedClear();

    tryNextDcAddress();

    return true;
}

void CTelegramDispatcher::tryNextDcAddress()
{
    if (m_connectionAddresses.isEmpty()) {
        return;
    }

    ++m_autoConnectionDcIndex;

    qDebug() << "CTelegramDispatcher::tryNextBuiltInDcAddress(): Dc index" << m_autoConnectionDcIndex;

    if (m_autoConnectionDcIndex >= m_connectionAddresses.count()) {
        if (m_autoReconnectionEnabled) {
            qDebug() << "CTelegramDispatcher::tryNextBuiltInDcAddress(): Could not connect to any known dc. Reconnection enabled -> wrapping up and tring again.";
            m_autoConnectionDcIndex = 0;
        } else {
            qDebug() << "CTelegramDispatcher::tryNextBuiltInDcAddress(): Could not connect to any known dc. Giving up.";
            setConnectionState(TelegramNamespace::ConnectionStateDisconnected);
            return;
        }
    }

    TLDcOption dcInfo;
    dcInfo.ipAddress = m_connectionAddresses.at(m_autoConnectionDcIndex).address;
    dcInfo.port = m_connectionAddresses.at(m_autoConnectionDcIndex).port;

    if (!activeConnection()) {
        CTelegramConnection *connection = createConnection();
        m_connections.insert(0, connection);
    }

    activeConnection()->setDcInfo(dcInfo);

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
        qDebug() << Q_FUNC_INFO << "Unknown format version" << format;
        return false;
    } else {
        qDebug() << Q_FUNC_INFO << "Format version:" << format;
    }

    QString legacySelfPhone;

    inputStream >> deltaTime;
    inputStream >> dcInfo;

    qDebug() << Q_FUNC_INFO << dcInfo.ipAddress;

    if (format < 3) {
        inputStream >> legacySelfPhone;
    }

    inputStream >> authKey;

    if (authKey.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Empty auth key data.";
        return false;
    }

    inputStream >> authId;
    inputStream >> serverSalt;

    initConnectionSharedClear();

    if (format >= 1) {
        inputStream >> m_updatesState.pts;
        inputStream >> m_updatesState.qts;
        inputStream >> m_updatesState.date;
    }

    if (format >= 2) {
        inputStream >> m_chatIds;
    }

    CTelegramConnection *connection = createConnection();
    connection->setDcInfo(dcInfo);
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

void CTelegramDispatcher::initConnectionSharedClear()
{
    m_autoConnectionDcIndex = s_autoConnectionIndexInvalid;

    m_updatesState.pts = 1;
    m_updatesState.qts = 1;
    m_updatesState.date = 1;
    m_chatIds.clear();
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
    setConnectionState(TelegramNamespace::ConnectionStateDisconnected);

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
    m_contactsMessageActions.clear();
    m_localMessageActions.clear();
    m_chatIds.clear();
    m_temporaryChatIdMap.clear();
    m_chatInfo.clear();
    m_chatFullInfo.clear();
    m_activeDc = 0;
    m_wantedActiveDc = 0;
    m_autoConnectionDcIndex = s_autoConnectionIndexInvalid;
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
        qDebug() << Q_FUNC_INFO << "Unknown media message" << messageId;
        return false;
    }

    // TODO: MessageMediaContact, MessageMediaGeo

    return requestFile(FileRequestDescriptor::messageMediaDataRequest(m_knownMediaMessages.value(messageId)));
}

bool CTelegramDispatcher::getMessageMediaInfo(TelegramNamespace::MessageMediaInfo *messageInfo, quint32 messageId) const
{
    if (!m_knownMediaMessages.contains(messageId)) {
        qDebug() << Q_FUNC_INFO << "Unknown media message" << messageId;
        return false;
    }

    const TLMessage &message = m_knownMediaMessages.value(messageId);
    const TLMessageMedia &media = message.media;
    TLMessageMedia &info = *messageInfo->d;
    info = media;
    return true;
}

bool CTelegramDispatcher::requestHistory(const QString &identifier, quint32 offset, quint32 limit)
{
    if (!activeConnection()) {
        return false;
    }

    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType == TLValue::InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return false;
    }

    activeConnection()->messagesGetHistory(peer, offset, /* maxId */ 0, limit);

    return true;
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

    int actionIndex;

    switch (peer.tlType) {
    case TLValue::InputPeerEmpty:
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return 0;
    case TLValue::InputPeerSelf:
        // Makes sense?
        break;
    case TLValue::InputPeerContact:
    case TLValue::InputPeerForeign:
        actionIndex = TypingStatus::indexForUser(m_localMessageActions, peer.userId);
        break;
    case TLValue::InputPeerChat:
        actionIndex = TypingStatus::indexForChatAndUser(m_localMessageActions, peer.chatId);
        break;
    default:
        // Invalid InputPeer type
        return 0;
    }

    if (actionIndex >= 0) {
        m_localMessageActions.remove(actionIndex);
    }

    return activeConnection()->sendMessage(peer, message);
}

quint64 CTelegramDispatcher::forwardMessage(const QString &identifier, quint32 messageId)
{
    if (!activeConnection()) {
        return 0;
    }

    quint64 randomId;
    Utils::randomBytes(&randomId);

    return activeConnection()->messagesForwardMessage(identifierToInputPeer(identifier), messageId, randomId);
}

quint64 CTelegramDispatcher::sendMedia(const QString &identifier, const TelegramNamespace::MessageMediaInfo &info)
{
    if (!activeConnection()) {
        return 0;
    }
    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType == TLValue::InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return 0;
    }

    const TLMessageMedia *media = info.d;
    TLInputMedia inputMedia;

    switch (media->tlType) {
    case TLValue::MessageMediaPhoto:
        inputMedia.tlType = TLValue::InputMediaPhoto;
        inputMedia.idInputPhoto.tlType = TLValue::InputPhoto;
        inputMedia.idInputPhoto.id = media->photo.id;
        inputMedia.idInputPhoto.accessHash = media->photo.accessHash;
        break;
    case TLValue::MessageMediaAudio:
        inputMedia.tlType = TLValue::InputMediaAudio;
        inputMedia.idInputAudio.tlType = TLValue::InputAudio;
        inputMedia.idInputAudio.id = media->audio.id;
        inputMedia.idInputAudio.accessHash = media->audio.accessHash;
        break;
    case TLValue::MessageMediaVideo:
        inputMedia.tlType = TLValue::InputMediaVideo;
        inputMedia.idInputVeo.tlType = TLValue::InputVideo;
        inputMedia.idInputVeo.id = media->video.id;
        inputMedia.idInputVeo.accessHash = media->video.accessHash;
        break;
    case TLValue::MessageMediaGeo:
        inputMedia.tlType = TLValue::InputMediaGeoPoint;
        inputMedia.geoPoint.tlType = TLValue::InputGeoPoint;
        inputMedia.geoPoint.longitude = media->geo.longitude;
        inputMedia.geoPoint.latitude = media->geo.latitude;
        break;
    case TLValue::MessageMediaContact:
        inputMedia.tlType = TLValue::InputMediaContact;
        inputMedia.firstName = media->firstName;
        inputMedia.lastName = media->lastName;
        inputMedia.phoneNumber = media->phoneNumber;
        break;
    case TLValue::MessageMediaDocument:
        inputMedia.tlType = TLValue::InputMediaDocument;
        inputMedia.idInputDocument.tlType = TLValue::InputDocument;
        inputMedia.idInputDocument.id = media->document.id;
        inputMedia.idInputDocument.accessHash = media->document.accessHash;
        break;
    default:
        return 0;
        break;
    }

    return activeConnection()->sendMedia(peer, inputMedia);
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

void CTelegramDispatcher::setTyping(const QString &identifier, TelegramNamespace::MessageAction publicAction)
{
    if (!activeConnection()) {
        return;
    }

    TLInputPeer peer = identifierToInputPeer(identifier);

    int actionIndex = -1;

    switch (peer.tlType) {
    case TLValue::InputPeerEmpty:
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << maskPhoneNumber(identifier);
        return;
    case TLValue::InputPeerSelf:
        // Makes no sense
        return;
    case TLValue::InputPeerContact:
    case TLValue::InputPeerForeign:
        actionIndex = TypingStatus::indexForUser(m_localMessageActions, peer.userId);
        break;
    case TLValue::InputPeerChat:
        actionIndex = TypingStatus::indexForChatAndUser(m_localMessageActions, peer.chatId);
        break;
    default:
        // Invalid InputPeer type
        return;
    }

    if (actionIndex >= 0) {
        if (m_localMessageActions.at(actionIndex).action == publicAction) {
            return; // Avoid flood
        }
    } else if (publicAction == TelegramNamespace::MessageActionNone) {
        return; // Avoid flood
    }

    const TLValue::Value tlAction = publicMessageActionToTelegramAction(publicAction);

    TLSendMessageAction action;
    action.tlType = tlAction;

    activeConnection()->messagesSetTyping(peer, action);

    if (publicAction == TelegramNamespace::MessageActionNone) {
        m_localMessageActions.remove(actionIndex);
    } else {
        if (actionIndex >= 0) {
            m_localMessageActions[actionIndex].action = publicAction;
        } else {
            TypingStatus status;
            status.action = publicAction;
            if (peer.tlType == TLValue::InputPeerChat) {
                status.chatId = peer.chatId;
            } else {
                status.userId = peer.userId;
            }
            status.typingTime = s_localTypingDuration;

            m_localMessageActions.append(status);
        }

        ensureTypingUpdateTimer(s_localTypingDuration);
    }
}

void CTelegramDispatcher::setMessageRead(const QString &identifier, quint32 messageId)
{
    if (!activeConnection()) {
        return;
    }
    const TLInputPeer peer = identifierToInputPeer(identifier);

    if (peer.tlType != TLValue::InputPeerEmpty) {
        activeConnection()->messagesReadHistory(peer, messageId, /* offset */ 0);
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
    const quint32 chatId = publicChatIdToChatId(publicChatId);

    if (chatId == 0) {
        return QString();
    }

    if (!m_chatInfo.contains(chatId)) {
        return QString();
    }

    return m_chatInfo.value(chatId).title;
}

bool CTelegramDispatcher::getChatInfo(TelegramNamespace::GroupChat *outputChat, quint32 publicChatId) const
{
    const quint32 chatId = publicChatIdToChatId(publicChatId);

    if (!chatId) {
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
    outputChat->date = chat.date;
    outputChat->left = chat.left; // Is it checkedIn for Geo chat?

    return true;
}

bool CTelegramDispatcher::getChatParticipants(QStringList *participants, quint32 publicChatId)
{
    const quint32 chatId = publicChatIdToChatId(publicChatId);

    if (!chatId) {
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

void CTelegramDispatcher::whenContactListReceived(const QVector<quint32> &contactList)
{
    qDebug() << Q_FUNC_INFO << contactList;

    QVector<quint32> newContactList = contactList;
    std::sort(newContactList.begin(), newContactList.end());

    if (m_contactList != newContactList) {
        m_contactList = newContactList;
        emit contactListChanged();
    }

    continueInitialization(StepContactList);
}

void CTelegramDispatcher::whenContactListChanged(const QVector<quint32> &added, const QVector<quint32> &removed)
{
    qDebug() << Q_FUNC_INFO << added << removed;
    QVector<quint32> newContactList = m_contactList;

    // There is some redundant checks, but let's be paranoid
    foreach (const quint32 contact, added) {
        if (!newContactList.contains(contact)) {
            newContactList.append(contact);
        }
    }

    foreach (const quint32 contact, removed) {
        for (int i = 0; i < newContactList.count(); ++i) {
            // We can use remove one, because we warranty that there is no duplication
#if QT_VERSION >= 0x050400
            newContactList.removeOne(contact);
#else
            int index = newContactList.indexOf(contact);
            if (index < 0) {
                continue;
            }
            newContactList.remove(index);
#endif
        }
    }

    std::sort(newContactList.begin(), newContactList.end());

    // There is no valid cases when lists are equal, but the check is (usually) cheap.
    if (m_contactList != newContactList) {
        m_contactList = newContactList;
        emit contactListChanged();
    }
}

void CTelegramDispatcher::messageActionTimerTimeout()
{

#if QT_VERSION >= 0x050000
    int minTime = s_userTypingActionPeriod;
#else
    int minTime = s_timerMaxInterval;
#endif

    for (int i = m_contactsMessageActions.count() - 1; i >= 0; --i) {
        int remainingTime = m_contactsMessageActions.at(i).typingTime - m_typingUpdateTimer->interval();
        if (remainingTime < 15) { // Let 15 ms be allowed correction
            if (m_contactsMessageActions.at(i).chatId) {
                emit contactChatTypingStatusChanged(telegramChatIdToPublicId(m_contactsMessageActions.at(i).chatId),
                                                    userIdToIdentifier(m_contactsMessageActions.at(i).userId),
                                                    TelegramNamespace::MessageActionNone);
            } else {
                emit contactTypingStatusChanged(userIdToIdentifier(m_contactsMessageActions.at(i).userId),
                                                TelegramNamespace::MessageActionNone);
            }
            m_contactsMessageActions.remove(i);
        } else {
            m_contactsMessageActions[i].typingTime = remainingTime;
            if (minTime > remainingTime) {
                minTime = remainingTime;
            }
        }
    }

    for (int i = m_localMessageActions.count() - 1; i >= 0; --i) {
        int timeRemaining = m_localMessageActions.at(i).typingTime - m_typingUpdateTimer->interval();
        if (timeRemaining < 15) { // Let 15 ms be allowed correction
            m_localMessageActions.remove(i);
        } else {
            m_localMessageActions[i].typingTime = timeRemaining;
            if (minTime > timeRemaining) {
                minTime = timeRemaining;
            }
        }
    }

    if (!m_contactsMessageActions.isEmpty() || !m_localMessageActions.isEmpty()) {
        m_typingUpdateTimer->start(minTime);
    }
}

void CTelegramDispatcher::whenMessageSentInfoReceived(const TLInputPeer &peer, quint64 randomId, TLMessagesSentMessage info)
{
    const QString identifier = userIdToIdentifier(peer.userId);
    QPair<QString, quint64> phoneAndId(identifier, randomId);

    m_messagesMap.insert(info.id, phoneAndId);

    emit sentMessageStatusChanged(identifier, info.id, TelegramNamespace::MessageDeliveryStatusSent);

    ensureUpdateState(info.pts, info.seq, info.date);
}

void CTelegramDispatcher::whenMessagesHistoryReceived(const TLMessagesMessages &messages)
{
    foreach (const TLMessage &message, messages.messages) {
        processMessageReceived(message);
    }
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
    qDebug() << Q_FUNC_INFO;
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
            if ((message.tlType != TLValue::MessageService) && (filterReceivedMessage(getPublicMessageFlags(message)))) {
                continue;
            }

            processMessageReceived(message);
        }
        if (updatesDifference.tlType == TLValue::UpdatesDifference) {
            setUpdateState(updatesDifference.state.pts, updatesDifference.state.seq, updatesDifference.state.date);
        } else { // UpdatesDifferenceSlice
            // Looks like updatesDifference.intermediateState is always null nowadays.
            setUpdateState(updatesDifference.intermediateState.pts, updatesDifference.intermediateState.seq, updatesDifference.intermediateState.date);
        }

        foreach (const TLUpdate &update, updatesDifference.otherUpdates) {
            processUpdate(update);
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

void CTelegramDispatcher::whenMessagesChatsReceived(const QVector<TLChat> &chats)
{
    qDebug() << Q_FUNC_INFO << chats.count();

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

    CTelegramConnection *connection = 0;

    connection = getConnection(descriptor.dcId());

    if (connection->authState() == CTelegramConnection::AuthStateSignedIn) {
        processFileRequestForConnection(connection, m_fileRequestCounter);
    } else {
        ensureSignedConnection(connection);
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

    quint32 newPts = m_updatesState.pts;

    switch (update.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateReadMessagesContents:
    case TLValue::UpdateReadHistoryInbox:
    case TLValue::UpdateReadHistoryOutbox:
    case TLValue::UpdateDeleteMessages:
        // Official client also have TLValue::UpdateWebPage here. Why the hell?
        if (m_updatesState.pts + update.ptsCount != update.pts) {
            qDebug() << "Needed inner updates:" << m_updatesState.pts << update.ptsCount << update.pts;
            Q_ASSERT(0);
        } else {
            newPts = update.pts;
        }
        break;
    default:
        break;
    }

    switch (update.tlType) {
    case TLValue::UpdateNewMessage:
        qDebug() << Q_FUNC_INFO << "UpdateNewMessage";
        processMessageReceived(update.message);
        break;
//    case TLValue::UpdateMessageID:
//        update.id;
//        update.randomId;
//        break;
//    case TLValue::UpdateReadMessages:
//        foreach (quint32 messageId, update.messages) {
//            const QPair<QString, quint64> phoneAndId = m_messagesMap.value(messageId);
//            emit sentMessageStatusChanged(phoneAndId.first, phoneAndId.second, TelegramNamespace::MessageDeliveryStatusRead);
//        }
//        ensureUpdateState(update.pts);
//        break;
//    case TLValue::UpdateDeleteMessages:
//        update.messages;
//        ensureUpdateState(update.pts);
//        break;
//    case TLValue::UpdateRestoreMessages:
//        update.messages;
//        ensureUpdateState(update.pts);
//        break;
    case TLValue::UpdateUserTyping:
    case TLValue::UpdateChatUserTyping:
        if (m_users.contains(update.userId)) {
            TelegramNamespace::MessageAction action = telegramMessageActionToPublicAction(update.action.tlType);

            int remainingTime = s_userTypingActionPeriod;
#if QT_VERSION >= 0x050000
            remainingTime += m_typingUpdateTimer->remainingTime();
#else
            // Missed timer remaining time method can leads to typing time period deviation.
#endif

            int index = -1;
            if (update.tlType == TLValue::UpdateUserTyping) {
                index = TypingStatus::indexForUser(m_contactsMessageActions, update.userId);
                emit contactTypingStatusChanged(userIdToIdentifier(update.userId), action);
            } else {
                index = TypingStatus::indexForChatAndUser(m_contactsMessageActions, update.chatId, update.userId);
                emit contactChatTypingStatusChanged(telegramChatIdToPublicId(update.chatId),
                                                    userIdToIdentifier(update.userId), action);
            }

            if (index < 0) {
                index = m_contactsMessageActions.count();
                TypingStatus status;
                status.userId = update.userId;
                if (update.tlType == TLValue::UpdateChatUserTyping) {
                    status.chatId = update.chatId;
                }
                m_contactsMessageActions.append(status);
            }

            m_contactsMessageActions[index].action = action;
            m_contactsMessageActions[index].typingTime = remainingTime;

            ensureTypingUpdateTimer(remainingTime);
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
                user->username = update.username;
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

    ensureUpdateState(newPts);
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

    const TelegramNamespace::MessageType messageType = telegramMessageTypeToPublicMessageType(message.media.tlType);

    if (!(messageType & m_acceptableMessageTypes)) {
        return;
    }

    if (message.media.tlType != TLValue::MessageMediaEmpty) {
        m_knownMediaMessages.insert(message.id, message);
    }

    TelegramNamespace::Message apiMessage;

    TelegramNamespace::MessageFlags messageFlags = getPublicMessageFlags(message);
    if (messageFlags & TelegramNamespace::MessageFlagForwarded) {
        apiMessage.fwdContact = userIdToIdentifier(message.fwdFromId);
        apiMessage.fwdTimestamp = message.fwdDate;
    }

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
    if (!m_chatInfo.contains(newChat.id)) {
        m_chatInfo.insert(newChat.id, newChat);
    } else {
        m_chatInfo[newChat.id] = newChat;
    }

    quint32 publicChatId = telegramChatIdToPublicId(newChat.id);

    if (publicChatId == 0) {
        publicChatId = insertTelegramChatId(newChat.id);
        emit chatAdded(publicChatId);
    } else {
        emit chatChanged(publicChatId);
    }
}

void CTelegramDispatcher::updateFullChat(const TLChatFull &newChat)
{
    if (!m_chatFullInfo.contains(newChat.id)) {
        m_chatFullInfo.insert(newChat.id, newChat);
    } else {
        m_chatFullInfo[newChat.id] = newChat;
    }

    quint32 publicChatId = telegramChatIdToPublicId(newChat.id);

    if (publicChatId == 0) {
        publicChatId = insertTelegramChatId(newChat.id);
        emit chatAdded(publicChatId);
    } else {
        emit chatChanged(publicChatId);
    }
}

quint32 CTelegramDispatcher::publicChatIdToChatId(quint32 publicChatId) const
{
    if (!havePublicChatId(publicChatId)) {
        qDebug() << Q_FUNC_INFO << "Unknown public chat id" << publicChatId;
        return 0;
    }

    return m_chatIds.at(publicChatId - 1);
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

CTelegramConnection *CTelegramDispatcher::getConnection(quint32 dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        const TLDcOption dcInfo = dcInfoById(dc);

        if (dcInfo.ipAddress.isEmpty()) {
            qDebug() << "Error: Attempt to connect to unknown DC" << dc;
            return 0;
        }

        connection = createConnection();
        connection->setDcInfo(dcInfo);
        m_connections.insert(dc, connection);
    }

    return connection;
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
            connect(connection, SIGNAL(contactListReceived(QVector<quint32>)),
                    SLOT(whenContactListReceived(QVector<quint32>)));
            connect(connection, SIGNAL(contactListChanged(QVector<quint32>,QVector<quint32>)),
                    SLOT(whenContactListChanged(QVector<quint32>,QVector<quint32>)));
            connect(connection, SIGNAL(updatesReceived(TLUpdates)),
                    SLOT(whenUpdatesReceived(TLUpdates)));
            connect(connection, SIGNAL(messageSentInfoReceived(TLInputPeer,quint64,TLMessagesSentMessage)),
                    SLOT(whenMessageSentInfoReceived(TLInputPeer,quint64,TLMessagesSentMessage)));
            connect(connection, SIGNAL(messagesHistoryReceived(TLMessagesMessages,TLInputPeer)),
                    SLOT(whenMessagesHistoryReceived(TLMessagesMessages)));
            connect(connection, SIGNAL(updatesStateReceived(TLUpdatesState)),
                    SLOT(whenUpdatesStateReceived(TLUpdatesState)));
            connect(connection, SIGNAL(updatesDifferenceReceived(TLUpdatesDifference)),
                    SLOT(whenUpdatesDifferenceReceived(TLUpdatesDifference)));
            connect(connection, SIGNAL(authExportedAuthorizationReceived(quint32,quint32,QByteArray)),
                    SLOT(whenAuthExportedAuthorizationReceived(quint32,quint32,QByteArray)));
            connect(connection, SIGNAL(messagesChatsReceived(QVector<TLChat>)),
                    SLOT(whenMessagesChatsReceived(QVector<TLChat>)));
            connect(connection, SIGNAL(messagesFullChatReceived(TLChatFull,QVector<TLChat>,QVector<TLUser>)),
                    SLOT(whenMessagesFullChatReceived(TLChatFull,QVector<TLChat>,QVector<TLUser>)));
            connect(connection, SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::AccountUserNameStatus)),
                    SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::AccountUserNameStatus)));
            connect(connection, SIGNAL(loggedOut(bool)),
                    SIGNAL(loggedOut(bool)));

            continueInitialization(StepSignIn);
        } else if (newState == CTelegramConnection::AuthStateHaveAKey) {
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
        } else if (newState == CTelegramConnection::AuthStateHaveAKey) {
            ensureSignedConnection(connection);
        }
    }

    if (newState >= CTelegramConnection::AuthStateHaveAKey) {
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

void CTelegramDispatcher::whenConnectionStatusChanged(int newStatus, int reason, quint32 dc)
{
    qDebug() << Q_FUNC_INFO << "status" << newStatus << "reason" << reason << "dc" << dc;
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection == activeConnection()) {
        if (newStatus == CTelegramConnection::ConnectionStatusDisconnected) {
            if (connectionState() == TelegramNamespace::ConnectionStateDisconnected) {
                return;
            }

            if (connectionState() == TelegramNamespace::ConnectionStateConnecting) {
                // There is a problem with initial connection
                if (m_autoConnectionDcIndex >= 0) {
                    tryNextDcAddress();
                } else if (m_autoReconnectionEnabled) {
                    // Network error; try to reconnect after a second.
                    QTimer::singleShot(1000, connection, SLOT(connectToDc()));
                }
            } else {
                setConnectionState(TelegramNamespace::ConnectionStateDisconnected);

                if (m_autoReconnectionEnabled) {
                    connection->connectToDc();
                }
            }
        } else if (newStatus >= CTelegramConnection::ConnectionStatusConnected) {
            m_autoConnectionDcIndex = s_autoConnectionIndexInvalid;
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

    foreach (TLDcOption o, m_dcConfiguration) {
        qDebug() << o.ipAddress << o.port;
    }

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
    CTelegramConnection *connection = getConnection(dc);

    if (connection->authState() >= CTelegramConnection::AuthStateHaveAKey) {
        connection->processRedirectedPackage(data);
    } else {
        m_delayedPackages.insertMulti(dc, data);

        if (connection->status() == CTelegramConnection::ConnectionStatusDisconnected) {
            connection->connectToDc();
        }
    }
}

void CTelegramDispatcher::whenWantedActiveDcChanged(quint32 dc)
{
    qDebug() << Q_FUNC_INFO << dc;
    CTelegramConnection *connection = getConnection(dc);

    m_wantedActiveDc = dc;

    if (connection->authState() >= CTelegramConnection::AuthStateHaveAKey) {
        setActiveDc(dc);
    } else {
        if (connection->status() == CTelegramConnection::ConnectionStatusDisconnected) {
            connection->connectToDc();
        }
    }
}

#ifndef TELEGRAMQT_NO_DEPRECATED
void CTelegramDispatcher::whenPhoneStatusReceived(const QString &phone, bool registered)
{
    emit phoneStatusReceived(phone, registered, false);
}
#endif

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
            const TelegramNamespace::MessageFlags messageFlags = getPublicMessageFlags(message);
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
        qDebug() << "Updates too long!";
        getUpdatesState();
        break;
    case TLValue::UpdateShortMessage:
    case TLValue::UpdateShortChatMessage:
    {
        if (m_updatesState.pts + updates.ptsCount != updates.pts) {
            qDebug() << "Need to get difference.";
            Q_ASSERT(0);
            break;
        }
        TLMessage shortMessage;
        shortMessage.tlType = TLValue::Message;
        shortMessage.id = updates.id;
        shortMessage.flags = updates.flags;
        shortMessage.fromId = updates.fromId;
        shortMessage.message = updates.message;
        shortMessage.date = updates.date;
        shortMessage.media.tlType = TLValue::MessageMediaEmpty;

        int messageActionIndex = 0;
        if (updates.tlType == TLValue::UpdateShortMessage) {
            messageActionIndex = TypingStatus::indexForUser(m_contactsMessageActions, updates.fromId);
            shortMessage.toId.tlType = TLValue::PeerUser;

            if (messageActionIndex >= 0) {
                emit contactTypingStatusChanged(userIdToIdentifier(updates.fromId),
                                                TelegramNamespace::MessageActionNone);
            }

        } else {
            messageActionIndex = TypingStatus::indexForUser(m_contactsMessageActions, updates.fromId);
            shortMessage.toId.tlType = TLValue::PeerChat;
            shortMessage.toId.chatId = updates.chatId;

            if (messageActionIndex >= 0) {
                emit contactChatTypingStatusChanged(telegramChatIdToPublicId(updates.chatId),
                                                    userIdToIdentifier(updates.fromId),
                                                    TelegramNamespace::MessageActionNone);
            }
        }

        processMessageReceived(shortMessage);

        if (messageActionIndex > 0) {
            m_contactsMessageActions.remove(messageActionIndex);
        }
    }
        ensureUpdateState(updates.pts);
        break;
    case TLValue::UpdateShort:
        processUpdate(updates.update);
        break;
    case TLValue::UpdatesCombined:
        qDebug() << Q_FUNC_INFO << "UpdatesCombined processing is not implemented yet.";
        Q_ASSERT(0);
        break;
    case TLValue::Updates:

        if (!updates.updates.isEmpty()) {
            // Official client sorts updates by pts/qts. Wat?!
            // Ok, let's see if there would be unordered updates.
            quint32 pts = updates.updates.first().pts;
            for (int i = 0; i < updates.updates.count(); ++i) {
                if (updates.updates.at(i).pts < pts) {
                    qDebug() << "Unordered update!";
                    Q_ASSERT(0);
                }
                pts = updates.updates.at(i).pts;
            }

            // Initial implementation
            for (int i = 0; i < updates.updates.count(); ++i) {
                processUpdate(updates.updates.at(i));
            }
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
    if (connection && (connection->authState() == CTelegramConnection::AuthStateHaveAKey)) {
        connection->authImportAuthorization(id, data);
    }
}

void CTelegramDispatcher::setActiveDc(quint32 dc)
{
    if ((m_activeDc == dc) && (m_wantedActiveDc == dc)) {
        return;
    }

    m_activeDc = dc;

    m_wantedActiveDc = dc;

    if (m_connections.value(dc)) {
        m_connections.value(dc)->setKeepAliveSettings(m_pingInterval, m_pingServerAdditionDisconnectionTime);
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
        if (activeConnection()->authState() == CTelegramConnection::AuthStateHaveAKey) {
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

quint32 CTelegramDispatcher::telegramChatIdToPublicId(quint32 telegramChatId) const
{
    for (int i = 0; i < m_chatIds.count(); ++i) {
        if (m_chatIds.at(i) == telegramChatId) {
            return i + 1; // Skip 0 index as an invalid public chat id value.
        }
    }

    return 0;
}

/* Return public chat id */
quint32 CTelegramDispatcher::insertTelegramChatId(quint32 telegramChatId)
{
    m_chatIds.append(telegramChatId);
    return m_chatIds.count();
}

bool CTelegramDispatcher::havePublicChatId(quint32 publicChatId) const
{
    return (publicChatId != 0) && (m_chatIds.count() >= int(publicChatId));
}

// Basically we just revert Unread and Read flag.
TelegramNamespace::MessageFlags CTelegramDispatcher::getPublicMessageFlags(const TLMessage &message)
{
    TelegramNamespace::MessageFlags result = TelegramNamespace::MessageFlagNone;

    if (!message.flags & TelegramMessageFlagUnread) {
        result |= TelegramNamespace::MessageFlagRead;
    }

    if (message.flags & TelegramMessageFlagOut) {
        result |= TelegramNamespace::MessageFlagOut;
    }

    if (message.fromId == m_selfUserId) {
        result |= TelegramNamespace::MessageFlagOut;
    }

    if (message.flags & TelegramMessageFlagForward) {
        result |= TelegramNamespace::MessageFlagForwarded;
    }

    if (message.flags & TelegramMessageFlagReply) {
        result |= TelegramNamespace::MessageFlagIsReply;
    }

    return result;
}

void CTelegramDispatcher::ensureUpdateState(quint32 pts, quint32 seq, quint32 date)
{
    if (m_updatesStateIsLocked) {
        qDebug() << Q_FUNC_INFO << pts << seq << date << "locked.";
        /* Prevent m_updateState from updating before UpdatesGetState answer receiving to avoid
         * m_updateState <-> m_actualState messing (which may lead to ignore offline-messages) */
        return;
    }

    setUpdateState(pts, seq, date);
}

void CTelegramDispatcher::setUpdateState(quint32 pts, quint32 seq, quint32 date)
{
    qDebug() << Q_FUNC_INFO << pts << seq << date;

    if (pts > m_updatesState.pts) {
        qDebug() << Q_FUNC_INFO << "Update pts from " << m_updatesState.pts << "to" << pts;
        m_updatesState.pts = pts;
    }

    if (seq > m_updatesState.seq) {
        m_updatesState.seq = seq;
    }

    if (date > m_updatesState.date) {
        qDebug() << Q_FUNC_INFO << "Update date from " << m_updatesState.date << "to" << date;
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

CTelegramConnection *CTelegramDispatcher::createConnection()
{
    CTelegramConnection *connection = new CTelegramConnection(m_appInformation, this);

    connect(connection, SIGNAL(authStateChanged(int,quint32)), SLOT(whenConnectionAuthChanged(int,quint32)));
    connect(connection, SIGNAL(statusChanged(int,int,quint32)), SLOT(whenConnectionStatusChanged(int,int,quint32)));
    connect(connection, SIGNAL(dcConfigurationReceived(quint32)), SLOT(whenDcConfigurationUpdated(quint32)));
    connect(connection, SIGNAL(actualDcIdReceived(quint32,quint32)), SLOT(whenConnectionDcIdUpdated(quint32,quint32)));
    connect(connection, SIGNAL(newRedirectedPackage(QByteArray,quint32)), SLOT(whenPackageRedirected(QByteArray,quint32)));
    connect(connection, SIGNAL(wantedActiveDcChanged(quint32)), SLOT(whenWantedActiveDcChanged(quint32)));

    connect(connection, SIGNAL(phoneStatusReceived(QString,bool)), SIGNAL(phoneStatusReceived(QString,bool)));

#ifndef TELEGRAMQT_NO_DEPRECATED
    connect(connection, SIGNAL(phoneStatusReceived(QString,bool)), SLOT(whenPhoneStatusReceived(QString,bool)));
#endif

    connect(connection, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(connection,
            SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)),
            SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)));
    connect(connection, SIGNAL(authorizationErrorReceived()), SIGNAL(authorizationErrorReceived()));

    connect(connection, SIGNAL(fileDataReceived(TLUploadFile,quint32,quint32)), SLOT(whenFileDataReceived(TLUploadFile,quint32,quint32)));

    return connection;
}

void CTelegramDispatcher::ensureSignedConnection(CTelegramConnection *connection)
{
    if (connection->status() == CTelegramConnection::ConnectionStatusDisconnected) {
        connection->connectToDc();
    } else {
        if (connection->authState() == CTelegramConnection::AuthStateHaveAKey) { // Need an exported auth to sign in
            quint32 dc = connection->dcInfo().id;

            if (m_exportedAuthentications.contains(dc)) {
                connection->authImportAuthorization(m_exportedAuthentications.value(dc).first, m_exportedAuthentications.value(dc).second);
            } else {
                if (activeConnection()->authState() == CTelegramConnection::AuthStateSignedIn) {
                    activeConnection()->authExportAuthorization(dc);
                }
            }
        }
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
