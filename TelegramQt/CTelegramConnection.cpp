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

#include "CTelegramConnection.hpp"

#include <QDebug>

#include <QDateTime>
#include <QStringList>
#include <QTimer>

#include <QtEndian>

#ifdef NETWORK_LOGGING
#include <QDir>
#include <QFile>
#include <QTextStream>

const int valFieldWidth = 32;
QString formatTLValue(const TLValue &val)
{
    const QString text = val.toString();
    return QString(valFieldWidth - text.length(), QLatin1Char(' ')) + text;
}
#endif

#include "CAppInformation.hpp"
#include "CTelegramStream.hpp"
#include "CTcpTransport.hpp"
#include "Utils.hpp"
#include "TelegramUtils.hpp"

#ifdef DEVELOPER_BUILD
#include "TLRpcDebug.hpp"
#endif

using namespace TelegramUtils;

static const quint32 s_defaultAuthInterval = 15000; // 15 sec

CTelegramConnection::CTelegramConnection(const CAppInformation *appInfo, QObject *parent) :
    QObject(parent),
    m_status(ConnectionStatusDisconnected),
    m_appInfo(appInfo),
    m_transport(0),
    m_authTimer(0),
    m_pingTimer(0),
    m_ackTimer(new QTimer(this)),
    m_authState(AuthStateNone),
    m_authId(0),
    m_authKeyAuxHash(0),
    m_serverSalt(0),
    m_sessionId(0),
    m_lastMessageId(0),
    m_lastSentPingId(0),
    m_sequenceNumber(0),
    m_contentRelatedMessages(0),
    m_pingInterval(0),
    m_serverDisconnectionExtraTime(0),
    m_deltaTime(0),
    m_deltaTimeHeuristicState(DeltaTimeIsOk),
    m_serverPublicFingersprint(0)
  #ifdef NETWORK_LOGGING
  , m_logFile(0)
  #endif
{
    setTransport(new CTcpTransport(this));

    m_ackTimer->setInterval(90 * 1000);
    m_ackTimer->setSingleShot(true);
    connect(m_ackTimer, SIGNAL(timeout()), SLOT(whenItsTimeToAckMessages()));
}

void CTelegramConnection::setDcInfo(const TLDcOption &newDcInfo)
{
    m_dcInfo = newDcInfo;
}

void CTelegramConnection::connectToDc()
{
    if (m_status != ConnectionStatusDisconnected) {
        return;
    }

#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << m_dcInfo.id << m_dcInfo.ipAddress << m_dcInfo.port;
#endif

    if (m_transport->state() != QAbstractSocket::UnconnectedState) {
        m_transport->disconnectFromHost(); // Ensure that there is no connection
    }

    setStatus(ConnectionStatusConnecting);
    setAuthState(AuthStateNone);
    m_transport->connectToHost(m_dcInfo.ipAddress, m_dcInfo.port);
}

void CTelegramConnection::setTransport(CTelegramTransport *newTransport)
{
    m_transport = newTransport;

    connect(m_transport, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(whenTransportStateChanged()));
    connect(m_transport, SIGNAL(readyRead()), SLOT(whenTransportReadyRead()));
    connect(m_transport, SIGNAL(timeout()), SLOT(whenTransportTimeout()));
}

void CTelegramConnection::setAuthKey(const QByteArray &newAuthKey)
{
    m_authKey = newAuthKey;
    m_authId = Utils::getFingersprint(m_authKey);
    m_authKeyAuxHash = Utils::getFingersprint(m_authKey, /* lower-order */ false);
}

void CTelegramConnection::setDeltaTime(const qint32 newDt)
{
    m_deltaTime = newDt;

    // Message id depends on time, so if we fix time, we need to reset message id.
    m_lastMessageId = 0;
}

quint64 CTelegramConnection::formatTimeStamp(qint64 timeInMs)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;

    const quint64 secs = timeInMs / 1000;
    const quint64 msecs = maxMsecValue / 1000 * (timeInMs % 1000);

    return (secs << 32) + msecs;
}

quint64 CTelegramConnection::timeStampToMSecsSinceEpoch(quint64 ts)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;

    const quint64 secs = ts >> 32;
    quint64 msecs = ts & maxMsecValue;

    msecs = msecs * 10000 / maxMsecValue;

    if (msecs % 10 >= 5) {
        msecs += 5;
    }
    msecs /= 10;

    return secs * 1000 + msecs;
}

void CTelegramConnection::initAuth()
{
    if (m_authState == AuthStateNone) {
        m_authRetryId = 0;
        m_rsaKey = Utils::loadRsaKey();
        Utils::randomBytes(m_clientNonce.data, m_clientNonce.size());

        requestPqAuthorization();
    }
}

void CTelegramConnection::requestPqAuthorization()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << TLValue::ReqPq;
    outputStream << m_clientNonce;

    sendPlainPackage(output);

    setAuthState(AuthStatePqRequested);
}

void CTelegramConnection::setKeepAliveSettings(quint32 interval, quint32 serverDisconnectionExtraTime)
{
    qDebug() << Q_FUNC_INFO << interval << serverDisconnectionExtraTime;

    m_serverDisconnectionExtraTime = serverDisconnectionExtraTime;

    if (m_pingInterval == interval) {
        return;
    }

    m_pingInterval = interval;

    if (interval && m_authState >= AuthStateHaveAKey) {
        startPingTimer();
    } else {
        stopPingTimer();
    }
}

quint64 CTelegramConnection::requestPhoneCode(const QString &phoneNumber)
{
    qDebug() << Q_FUNC_INFO << "requestPhoneCode" << maskPhoneNumber(phoneNumber) << m_dcInfo.id;

    return authSendCode(phoneNumber, 0, m_appInfo->appId(), m_appInfo->appHash(), m_appInfo->languageCode());
}

quint64 CTelegramConnection::signIn(const QString &phoneNumber, const QString &authCode)
{
    qDebug() << "SignIn with number " << maskPhoneNumber(phoneNumber);

    return authSignIn(phoneNumber, m_authCodeHash, authCode);
}

quint64 CTelegramConnection::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    qDebug() << "SignUp with number " << maskPhoneNumber(phoneNumber);
    return authSignUp(phoneNumber, m_authCodeHash, authCode, firstName, lastName);
}

void CTelegramConnection::downloadFile(const TLInputFileLocation &inputLocation, quint32 offset, quint32 limit, quint32 requestId)
{
    if (m_requestedFilesIds.contains(requestId)) {
        // Prevent from (really possible) repeated request.
        return;
    }

    const quint64 messageId = uploadGetFile(inputLocation, offset, limit);
    qDebug() << Q_FUNC_INFO << messageId << "offset:" << offset << "limit:" << limit << "request:" << requestId;

    m_requestedFilesIds.insert(messageId, requestId);
}

void CTelegramConnection::uploadFile(quint64 fileId, quint32 filePart, const QByteArray &bytes, quint32 requestId)
{
    qDebug() << Q_FUNC_INFO << "id" << fileId << "part" << filePart << "size" << bytes.count() << "request" << requestId;
    const quint64 messageId = uploadSaveFilePart(fileId, filePart, bytes);

    m_requestedFilesIds.insert(messageId, requestId);
}

quint64 CTelegramConnection::sendMessage(const TLInputPeer &peer, const QString &message, quint64 randomMessageId)
{
    if (message.length() > 4095) { // 4096 - 1
        qDebug() << Q_FUNC_INFO << "Can not send such long message due to server limitation. Current maximum length is 4095 characters.";
        return 0;
    }

    const TLReplyMarkup replyMarkup;
    const TLVector<TLMessageEntity> entities;

    return messagesSendMessage(/* flags */0, peer, /* reply to message id*/ 0, message, randomMessageId, replyMarkup, entities);
}

quint64 CTelegramConnection::sendMedia(const TLInputPeer &peer, const TLInputMedia &media)
{
    quint64 randomMessageId;
    Utils::randomBytes(&randomMessageId);

    const TLReplyMarkup replyMarkup;

    messagesSendMedia(/* flags */0, peer, /* reply to message id*/ 0, media, randomMessageId, replyMarkup);

    return randomMessageId;
}

// Generated Telegram API methods implementation
quint64 CTelegramConnection::accountChangePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountChangePhone;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountCheckUsername(const QString &username)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountCheckUsername;
    outputStream << username;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountDeleteAccount(const QString &reason)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountDeleteAccount;
    outputStream << reason;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetAccountTTL()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetAccountTTL;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetAuthorizations()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetAuthorizations;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetNotifySettings(const TLInputNotifyPeer &peer)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetNotifySettings;
    outputStream << peer;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetPassword()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetPassword;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetPasswordSettings(const QByteArray &currentPasswordHash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetPasswordSettings;
    outputStream << currentPasswordHash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetPrivacy(const TLInputPrivacyKey &key)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetPrivacy;
    outputStream << key;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountGetWallPapers()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountGetWallPapers;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountRegisterDevice(quint32 tokenType, const QString &token, const QString &deviceModel, const QString &systemVersion, const QString &appVersion, bool appSandbox, const QString &langCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountRegisterDevice;
    outputStream << tokenType;
    outputStream << token;
    outputStream << deviceModel;
    outputStream << systemVersion;
    outputStream << appVersion;
    outputStream << appSandbox;
    outputStream << langCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountResetAuthorization(quint64 hash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountResetAuthorization;
    outputStream << hash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountResetNotifySettings()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountResetNotifySettings;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountSendChangePhoneCode(const QString &phoneNumber)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountSendChangePhoneCode;
    outputStream << phoneNumber;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountSetAccountTTL(const TLAccountDaysTTL &ttl)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountSetAccountTTL;
    outputStream << ttl;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountSetPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountSetPrivacy;
    outputStream << key;
    outputStream << rules;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUnregisterDevice(quint32 tokenType, const QString &token)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUnregisterDevice;
    outputStream << tokenType;
    outputStream << token;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUpdateDeviceLocked(quint32 period)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUpdateDeviceLocked;
    outputStream << period;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUpdateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUpdateNotifySettings;
    outputStream << peer;
    outputStream << settings;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUpdatePasswordSettings(const QByteArray &currentPasswordHash, const TLAccountPasswordInputSettings &newSettings)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUpdatePasswordSettings;
    outputStream << currentPasswordHash;
    outputStream << newSettings;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUpdateProfile(const QString &firstName, const QString &lastName)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUpdateProfile;
    outputStream << firstName;
    outputStream << lastName;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUpdateStatus(bool offline)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUpdateStatus;
    outputStream << offline;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::accountUpdateUsername(const QString &username)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AccountUpdateUsername;
    outputStream << username;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authBindTempAuthKey(quint64 permAuthKeyId, quint64 nonce, quint32 expiresAt, const QByteArray &encryptedMessage)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthBindTempAuthKey;
    outputStream << permAuthKeyId;
    outputStream << nonce;
    outputStream << expiresAt;
    outputStream << encryptedMessage;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authCheckPassword(const QByteArray &passwordHash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthCheckPassword;
    outputStream << passwordHash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authCheckPhone(const QString &phoneNumber)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthCheckPhone;
    outputStream << phoneNumber;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authExportAuthorization(quint32 dcId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthExportAuthorization;
    outputStream << dcId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authImportAuthorization(quint32 id, const QByteArray &bytes)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthImportAuthorization;
    outputStream << id;
    outputStream << bytes;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authImportBotAuthorization(quint32 flags, quint32 apiId, const QString &apiHash, const QString &botAuthToken)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthImportBotAuthorization;
    outputStream << flags;
    outputStream << apiId;
    outputStream << apiHash;
    outputStream << botAuthToken;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authLogOut()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthLogOut;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authRecoverPassword(const QString &code)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthRecoverPassword;
    outputStream << code;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authRequestPasswordRecovery()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthRequestPasswordRecovery;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authResetAuthorizations()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthResetAuthorizations;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authSendCall(const QString &phoneNumber, const QString &phoneCodeHash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthSendCall;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authSendCode(const QString &phoneNumber, quint32 smsType, quint32 apiId, const QString &apiHash, const QString &langCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthSendCode;
    outputStream << phoneNumber;
    outputStream << smsType;
    outputStream << apiId;
    outputStream << apiHash;
    outputStream << langCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authSendInvites(const TLVector<QString> &phoneNumbers, const QString &message)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthSendInvites;
    outputStream << phoneNumbers;
    outputStream << message;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authSendSms(const QString &phoneNumber, const QString &phoneCodeHash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthSendSms;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authSignIn(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthSignIn;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::authSignUp(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode, const QString &firstName, const QString &lastName)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::AuthSignUp;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    outputStream << firstName;
    outputStream << lastName;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsBlock(const TLInputUser &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsBlock;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsDeleteContact(const TLInputUser &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsDeleteContact;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsDeleteContacts(const TLVector<TLInputUser> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsDeleteContacts;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsExportCard()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsExportCard;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsGetBlocked(quint32 offset, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsGetBlocked;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsGetContacts(const QString &hash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsGetContacts;
    outputStream << hash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsGetStatuses()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsGetStatuses;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsGetSuggested(quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsGetSuggested;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsImportCard(const TLVector<quint32> &exportCard)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsImportCard;
    outputStream << exportCard;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsImportContacts(const TLVector<TLInputContact> &contacts, bool replace)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsImportContacts;
    outputStream << contacts;
    outputStream << replace;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsResolveUsername(const QString &username)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsResolveUsername;
    outputStream << username;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsSearch(const QString &q, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsSearch;
    outputStream << q;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::contactsUnblock(const TLInputUser &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ContactsUnblock;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpGetAppChangelog(const QString &deviceModel, const QString &systemVersion, const QString &appVersion, const QString &langCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpGetAppChangelog;
    outputStream << deviceModel;
    outputStream << systemVersion;
    outputStream << appVersion;
    outputStream << langCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpGetAppUpdate(const QString &deviceModel, const QString &systemVersion, const QString &appVersion, const QString &langCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpGetAppUpdate;
    outputStream << deviceModel;
    outputStream << systemVersion;
    outputStream << appVersion;
    outputStream << langCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpGetConfig()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpGetConfig;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpGetInviteText(const QString &langCode)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpGetInviteText;
    outputStream << langCode;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpGetNearestDc()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpGetNearestDc;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpGetSupport()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpGetSupport;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::helpSaveAppLog(const TLVector<TLInputAppEvent> &events)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::HelpSaveAppLog;
    outputStream << events;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesAcceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesAcceptEncryption;
    outputStream << peer;
    outputStream << gB;
    outputStream << keyFingerprint;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesAddChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesAddChatUser;
    outputStream << chatId;
    outputStream << userId;
    outputStream << fwdLimit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesCheckChatInvite(const QString &hash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesCheckChatInvite;
    outputStream << hash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesCreateChat(const TLVector<TLInputUser> &users, const QString &title)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesCreateChat;
    outputStream << users;
    outputStream << title;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDeleteChatUser(quint32 chatId, const TLInputUser &userId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesDeleteChatUser;
    outputStream << chatId;
    outputStream << userId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDeleteHistory(const TLInputPeer &peer, quint32 offset)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesDeleteHistory;
    outputStream << peer;
    outputStream << offset;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDeleteMessages(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesDeleteMessages;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDiscardEncryption(quint32 chatId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesDiscardEncryption;
    outputStream << chatId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesEditChatPhoto(quint32 chatId, const TLInputChatPhoto &photo)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesEditChatPhoto;
    outputStream << chatId;
    outputStream << photo;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesEditChatTitle(quint32 chatId, const QString &title)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesEditChatTitle;
    outputStream << chatId;
    outputStream << title;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesExportChatInvite(quint32 chatId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesExportChatInvite;
    outputStream << chatId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesForwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesForwardMessage;
    outputStream << peer;
    outputStream << id;
    outputStream << randomId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesForwardMessages(quint32 flags, const TLInputPeer &fromPeer, const TLVector<quint32> &id, const TLVector<quint64> &randomId, const TLInputPeer &toPeer)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesForwardMessages;
    outputStream << flags;
    outputStream << fromPeer;
    outputStream << id;
    outputStream << randomId;
    outputStream << toPeer;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetAllStickers(const QString &hash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetAllStickers;
    outputStream << hash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetChats(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetChats;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetDhConfig(quint32 version, quint32 randomLength)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetDhConfig;
    outputStream << version;
    outputStream << randomLength;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetDialogs(quint32 offset, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetDialogs;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetFullChat(quint32 chatId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetFullChat;
    outputStream << chatId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetHistory(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetHistory;
    outputStream << peer;
    outputStream << offsetId;
    outputStream << addOffset;
    outputStream << limit;
    outputStream << maxId;
    outputStream << minId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetMessages(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetMessages;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetMessagesViews(const TLInputPeer &peer, const TLVector<quint32> &id, bool increment)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetMessagesViews;
    outputStream << peer;
    outputStream << id;
    outputStream << increment;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetStickerSet(const TLInputStickerSet &stickerset)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetStickerSet;
    outputStream << stickerset;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetStickers(const QString &emoticon, const QString &hash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetStickers;
    outputStream << emoticon;
    outputStream << hash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetWebPagePreview(const QString &message)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesGetWebPagePreview;
    outputStream << message;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesImportChatInvite(const QString &hash)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesImportChatInvite;
    outputStream << hash;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesInstallStickerSet(const TLInputStickerSet &stickerset, bool disabled)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesInstallStickerSet;
    outputStream << stickerset;
    outputStream << disabled;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReadEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesReadEncryptedHistory;
    outputStream << peer;
    outputStream << maxDate;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReadHistory(const TLInputPeer &peer, quint32 maxId, quint32 offset)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesReadHistory;
    outputStream << peer;
    outputStream << maxId;
    outputStream << offset;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReadMessageContents(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesReadMessageContents;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReceivedMessages(quint32 maxId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesReceivedMessages;
    outputStream << maxId;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReceivedQueue(quint32 maxQts)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesReceivedQueue;
    outputStream << maxQts;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReportSpam(const TLInputPeer &peer)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesReportSpam;
    outputStream << peer;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesRequestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesRequestEncryption;
    outputStream << userId;
    outputStream << randomId;
    outputStream << gA;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSearch(quint32 flags, const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSearch;
    outputStream << flags;
    outputStream << peer;
    outputStream << q;
    outputStream << filter;
    outputStream << minDate;
    outputStream << maxDate;
    outputStream << offset;
    outputStream << maxId;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendBroadcast(const TLVector<TLInputUser> &contacts, const TLVector<quint64> &randomId, const QString &message, const TLInputMedia &media)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSendBroadcast;
    outputStream << contacts;
    outputStream << randomId;
    outputStream << message;
    outputStream << media;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSendEncrypted;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSendEncryptedFile;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    outputStream << file;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSendEncryptedService;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId, const TLReplyMarkup &replyMarkup)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSendMedia;
    outputStream << flags;
    outputStream << peer;
    if (flags & 1 << 0) {
        outputStream << replyToMsgId;
    }
    outputStream << media;
    outputStream << randomId;
    if (flags & 1 << 2) {
        outputStream << replyMarkup;
    }
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSendMessage;
    outputStream << flags;
    outputStream << peer;
    if (flags & 1 << 0) {
        outputStream << replyToMsgId;
    }
    outputStream << message;
    outputStream << randomId;
    if (flags & 1 << 2) {
        outputStream << replyMarkup;
    }
    if (flags & 1 << 3) {
        outputStream << entities;
    }
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSetEncryptedTyping(const TLInputEncryptedChat &peer, bool typing)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSetEncryptedTyping;
    outputStream << peer;
    outputStream << typing;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSetTyping(const TLInputPeer &peer, const TLSendMessageAction &action)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesSetTyping;
    outputStream << peer;
    outputStream << action;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesStartBot(const TLInputUser &bot, quint32 chatId, quint64 randomId, const QString &startParam)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesStartBot;
    outputStream << bot;
    outputStream << chatId;
    outputStream << randomId;
    outputStream << startParam;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesUninstallStickerSet(const TLInputStickerSet &stickerset)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::MessagesUninstallStickerSet;
    outputStream << stickerset;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::updatesGetChannelDifference(const TLInputChannel &channel, const TLChannelMessagesFilter &filter, quint32 pts, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UpdatesGetChannelDifference;
    outputStream << channel;
    outputStream << filter;
    outputStream << pts;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::updatesGetDifference(quint32 pts, quint32 date, quint32 qts)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UpdatesGetDifference;
    outputStream << pts;
    outputStream << date;
    outputStream << qts;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::updatesGetState()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UpdatesGetState;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::uploadGetFile(const TLInputFileLocation &location, quint32 offset, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UploadGetFile;
    outputStream << location;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::uploadSaveBigFilePart(quint64 fileId, quint32 filePart, quint32 fileTotalParts, const QByteArray &bytes)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UploadSaveBigFilePart;
    outputStream << fileId;
    outputStream << filePart;
    outputStream << fileTotalParts;
    outputStream << bytes;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::uploadSaveFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UploadSaveFilePart;
    outputStream << fileId;
    outputStream << filePart;
    outputStream << bytes;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::usersGetFullUser(const TLInputUser &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UsersGetFullUser;
    outputStream << id;
    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::usersGetUsers(const TLVector<TLInputUser> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::UsersGetUsers;
    outputStream << id;
    return sendEncryptedPackage(output);
}

// End of generated Telegram API methods implementation

quint64 CTelegramConnection::ping()
{
//    qDebug() << Q_FUNC_INFO;
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << TLValue::Ping;
    outputStream << ++m_lastSentPingId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::pingDelayDisconnect(quint32 disconnectInSec)
{
//    qDebug() << Q_FUNC_INFO << disconnectInSec;
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << TLValue::PingDelayDisconnect;
    outputStream << ++m_lastSentPingId;
    outputStream << disconnectInSec;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::acknowledgeMessages(const TLVector<quint64> &idsVector)
{
//    qDebug() << Q_FUNC_INFO << idsVector;

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << TLValue::MsgsAck;
    outputStream << idsVector;

    return sendEncryptedPackage(output, /* save package */ false);
}

bool CTelegramConnection::answerPqAuthorization(const QByteArray &payload)
{
    CTelegramStream inputStream(payload);

    TLValue responsePqValue;
    inputStream >> responsePqValue;

    if (responsePqValue != TLValue::ResPQ) {
        qDebug() << "Error: Unexpected operation code";
        return false;
    }

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    m_serverNonce = serverNonce;

    QByteArray pq;

    inputStream >> pq;

    if (pq.size() != 8) {
        qDebug() << "Error: PQ should be 8 bytes in length";
        return false;
    }

    m_pq = qFromBigEndian<quint64>((uchar *) pq.data());

    quint64 div1 = Utils::findDivider(m_pq);

    if (div1 == 1) {
        qDebug() << "Error: Can not solve PQ.";
        return false;
    }
    quint64 div2 = m_pq / div1;

    if (div1 < div2) {
        m_p = div1;
        m_q = div2;
    } else {
        m_p = div2;
        m_q = div1;
    }

    TLVector<quint64> fingersprints;

    inputStream >> fingersprints;

    if (fingersprints.count() != 1) {
        qDebug() << "Error: Unexpected Server RSA Fingersprints vector.";
        return false;
    }

    m_serverPublicFingersprint = fingersprints.at(0);

    if (m_rsaKey.fingersprint != m_serverPublicFingersprint) {
        qDebug() << "Error: Server RSA Fingersprint does not match to loaded key";
        return false;
    }

    return true;
}

void CTelegramConnection::requestDhParameters()
{
    Utils::randomBytes(m_newNonce.data, m_newNonce.size());

    QByteArray bigEndianNumber;
    bigEndianNumber.fill(char(0), 8);

    QByteArray encryptedPackage;
    {
        static const int requestedEncryptedPackageLength = 255;
        QByteArray innerData;
        CTelegramStream encryptedStream(&innerData, /* write */ true);

        encryptedStream << TLValue::PQInnerData;

        qToBigEndian(m_pq, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        bigEndianNumber.fill(char(0), 4);
        qToBigEndian(m_p, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        qToBigEndian(m_q, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        encryptedStream << m_clientNonce;
        encryptedStream << m_serverNonce;
        encryptedStream << m_newNonce;

        QByteArray sha = Utils::sha1(innerData);
        QByteArray randomPadding;
        randomPadding.resize(requestedEncryptedPackageLength - (sha.length() + innerData.length()));
        Utils::randomBytes(&randomPadding);

        encryptedPackage = Utils::rsa(sha + innerData + randomPadding, m_rsaKey);
    }

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << TLValue::ReqDHParams;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;

    bigEndianNumber.fill(char(0), 4);
    qToBigEndian(m_p, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    qToBigEndian(m_q, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    outputStream << m_serverPublicFingersprint;

    outputStream << encryptedPackage;

    sendPlainPackage(output);

    setAuthState(AuthStateDhRequested);
}

bool CTelegramConnection::answerDh(const QByteArray &payload)
{
    CTelegramStream inputStream(payload);

    TLValue responseTLValue;
    inputStream >> responseTLValue;

    if (responseTLValue != TLValue::ServerDHParamsOk) {
        qDebug() << "Error: Server did not accept our DH params.";
        return false;
    }

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    QByteArray encryptedAnswer;

    inputStream >> encryptedAnswer;

    m_tmpAesKey = generateTmpAesKey();

    QByteArray answer = Utils::aesDecrypt(encryptedAnswer, m_tmpAesKey);

    QByteArray sha1OfAnswer = answer.mid(0, 20);
    answer = answer.mid(20, 564);

    if (Utils::sha1(answer) != sha1OfAnswer) {
        qDebug() << "Error: SHA1 of encrypted answer is different from announced.";
        return false;
    }

    CTelegramStream encryptedInputStream(answer);

    encryptedInputStream >> responseTLValue;

    if (responseTLValue != TLValue::ServerDHInnerData) {
        qDebug() << "Error: Unexpected TL Value in encrypted answer.";
        return false;
    }

    encryptedInputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    encryptedInputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    encryptedInputStream >> m_g;
    encryptedInputStream >> m_dhPrime;
    encryptedInputStream >> m_gA;

    if ((m_g < 2) || (m_g > 7)) {
        qDebug() << "Error: Received 'g' number is out of acceptable range [2-7].";
        return false;
    }

    if (m_dhPrime.length() != 2048 / 8) {
        qDebug() << "Error: Received dhPrime number length is not correct." << m_dhPrime.length() << 2048 / 8;
        return false;
    }

    if (!(m_dhPrime.at(0) & 128)) {
        qDebug() << "Error: Received dhPrime is too small.";
        return false;
    }

    quint32 serverTime;

    encryptedInputStream >> serverTime;

    setDeltaTime(qint64(serverTime) - (QDateTime::currentMSecsSinceEpoch() / 1000));
    m_deltaTimeHeuristicState = DeltaTimeIsOk;

    m_b.resize(256);
    Utils::randomBytes(&m_b);

    return true;
}

void CTelegramConnection::requestDhGenerationResult()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << TLValue::SetClientDHParams;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;

    QByteArray encryptedPackage;
    {
        QByteArray innerData;
        CTelegramStream encryptedStream(&innerData, /* write */ true);

        encryptedStream << TLValue::ClientDHInnerData;

        encryptedStream << m_clientNonce;
        encryptedStream << m_serverNonce;
        encryptedStream << m_authRetryId;

        QByteArray binNumber;
        binNumber.resize(sizeof(m_g));
        qToBigEndian(m_g, (uchar *) binNumber.data());

        binNumber = Utils::binaryNumberModExp(binNumber, m_dhPrime, m_b);

        encryptedStream << binNumber;

        QByteArray sha = Utils::sha1(innerData);
        QByteArray randomPadding;

        int packageLength = sha.length() + innerData.length();
        if ((packageLength) % 16) {
            randomPadding.resize(16 - (packageLength % 16));
            Utils::randomBytes(&randomPadding);

            packageLength += randomPadding.size();
        }

        encryptedPackage = Utils::aesEncrypt(sha + innerData + randomPadding, m_tmpAesKey);

        encryptedPackage.truncate(packageLength);
    }

    outputStream << encryptedPackage;

    sendPlainPackage(output);
    setAuthState(AuthStateDhGenerationResultRequested);
}

bool CTelegramConnection::processServersDHAnswer(const QByteArray &payload)
{
    CTelegramStream inputStream(payload);

    TLValue responseTLValue;
    inputStream >> responseTLValue;

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    TLNumber128 newNonceHashLower128;

    inputStream >> newNonceHashLower128;

    QByteArray readedHashPart(newNonceHashLower128.data, newNonceHashLower128.size());

    QByteArray expectedHashData(m_newNonce.data, m_newNonce.size());

    QByteArray newAuthKey = Utils::binaryNumberModExp(m_gA, m_dhPrime, m_b);

    expectedHashData.append(Utils::sha1(newAuthKey).left(8));

    if (responseTLValue == TLValue::DhGenOk) {
//        qDebug() << "Answer OK";

        expectedHashData.insert(32, char(1));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }

        setAuthKey(newAuthKey);
        m_serverSalt = m_serverNonce.parts[0] ^ m_newNonce.parts[0];

        setAuthState(AuthStateHaveAKey);
        return true;
    } else if (responseTLValue == TLValue::DhGenRetry) {
        qDebug() << "Answer RETRY";

        expectedHashData.insert(32, char(2));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }
    } else if (responseTLValue == TLValue::DhGenFail) {
        qDebug() << "Answer FAIL";

        expectedHashData.insert(32, char(3));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }
    }

    qDebug() << "Error: Unexpected server response.";

    return false;
}

void CTelegramConnection::processRedirectedPackage(const QByteArray &data)
{
    sendEncryptedPackage(data);
}

TLValue CTelegramConnection::processRpcQuery(const QByteArray &data)
{
    CTelegramStream stream(data);

    bool isUpdate;
    TLValue value = processUpdate(stream, &isUpdate, /* requestId */ 0); // Doubtfully that this approach will work in next time.

    if (isUpdate) {
        return value;
    }

    switch (value) {
    case TLValue::NewSessionCreated:
        processSessionCreated(stream);
        break;
    case TLValue::MsgContainer:
        processContainer(stream);
        break;
    case TLValue::RpcResult:
        processRpcResult(stream);
        break;
    case TLValue::MsgsAck:
        processMessageAck(stream);
        break;
    case TLValue::BadMsgNotification:
    case TLValue::BadServerSalt:
        processIgnoredMessageNotification(stream);
        break;
    case TLValue::GzipPacked:
        processGzipPackedRpcQuery(stream);
        break;
    case TLValue::Pong:
        processPingPong(stream);
        break;
    default:
        qDebug() << Q_FUNC_INFO << "value:" << value.toString();
        break;
    }

    if ((value != TLValue::BadMsgNotification) && (m_deltaTimeHeuristicState != DeltaTimeIsOk)) {
        // If we have no bad message notification, then time is synced.
        m_deltaTimeHeuristicState = DeltaTimeIsOk;
    }

    if (stream.error()) {
        qWarning() << Q_FUNC_INFO << "Read of RPC result caused error. RPC type:" << value.toString() << "(read from the package -> can be misleading)";
    }

    return value;
}

void CTelegramConnection::processSessionCreated(CTelegramStream &stream)
{
    // https://core.telegram.org/mtproto/service_messages#new-session-creation-notification
    quint64 n;

    stream >> n;
    stream >> n;
    stream >> n;
}

void CTelegramConnection::processContainer(CTelegramStream &stream)
{
    // https://core.telegram.org/mtproto/service_messages#simple-container
    quint32 itemsCount;

    stream >> itemsCount;

    for (quint32 i = 0; i < itemsCount; ++i) {
        quint64 id;
        stream >> id;
        //todo: ack

        quint32 seqNo;
        stream >> seqNo;

        quint32 size;

        stream >> size;

        processRpcQuery(stream.readBytes(size));
    }
}

void CTelegramConnection::processRpcResult(CTelegramStream &stream, quint64 idHint)
{
    quint64 id = idHint;

    if (!id) {
        stream >> id;
    }

    TLValue request;

    const QByteArray &requestData = m_submittedPackages.value(id);

    if (!requestData.isEmpty()) {
        CTelegramStream storedStream(requestData);
        TLValue processingResult;

        storedStream >> request;

        if (storedStream.error()) {
            qWarning() << Q_FUNC_INFO << "Unable to read request type from the saved package. Package with id" << id << "ignored.";
            return;
        }

        switch (request) {
        case TLValue::ContactsGetContacts:
            processingResult = processContactsGetContacts(stream, id);
            break;
        case TLValue::ContactsImportContacts:
            processingResult = processContactsImportContacts(stream, id);
            break;
        case TLValue::ContactsDeleteContacts:
            processingResult = processContactsDeleteContacts(stream, id);
            break;
        case TLValue::ContactsResolveUsername:
            processingResult = processContactsResolveUsername(stream, id);
            break;
        case TLValue::UpdatesGetState:
            processingResult = processUpdatesGetState(stream, id);
            break;
        case TLValue::UpdatesGetDifference:
            processingResult = processUpdatesGetDifference(stream, id);
            break;
        case TLValue::UploadGetFile:
            processingResult = processUploadGetFile(stream, id);
            break;
        case TLValue::UploadSaveFilePart:
        case TLValue::UploadSaveBigFilePart:
            processingResult = processUploadSaveFilePart(stream, id);
            break;
        case TLValue::UsersGetUsers:
            processingResult = processUsersGetUsers(stream, id);
            break;
        case TLValue::UsersGetFullUser:
            processingResult = processUsersGetFullUser(stream, id);
            break;
        case TLValue::AuthCheckPassword:
        case TLValue::AuthImportAuthorization:
        case TLValue::AuthSignIn:
        case TLValue::AuthSignUp:
            processingResult = processAuthSign(stream, id);
            break;
        case TLValue::AuthLogOut:
            processingResult = processAuthLogOut(stream, id);
            break;
        case TLValue::HelpGetConfig:
            processingResult = processHelpGetConfig(stream, id);
            break;
        case TLValue::AuthCheckPhone:
            processingResult = processAuthCheckPhone(stream, id);
            break;
        case TLValue::AuthExportAuthorization:
            processingResult = processAuthExportAuthorization(stream, id);
            break;
        case TLValue::AuthSendCode:
            processingResult = processAuthSendCode(stream, id);
            break;
        case TLValue::AuthSendSms:
            processingResult = processAuthSendSms(stream, id);
            break;
        case TLValue::MessagesSetTyping:
            processingResult = processMessagesSetTyping(stream, id);
            break;
        case TLValue::MessagesReadHistory:
            processingResult = processMessagesReadHistory(stream, id);
            break;
        case TLValue::MessagesReceivedMessages:
            processingResult = processMessagesReceivedMessages(stream, id);
            break;
        case TLValue::MessagesGetHistory:
            processingResult = processMessagesGetHistory(stream, id);
            break;
        case TLValue::MessagesGetDialogs:
            processingResult = processMessagesGetDialogs(stream, id);
            break;
        case TLValue::MessagesGetChats:
            processingResult = processMessagesGetChats(stream, id);
            break;
        case TLValue::MessagesGetFullChat:
            processingResult = processMessagesGetFullChat(stream, id);
            break;
        case TLValue::AccountCheckUsername:
            processingResult = processAccountCheckUsername(stream, id);
            break;
        case TLValue::AccountGetPassword:
            processingResult = processAccountGetPassword(stream, id);
            break;
        case TLValue::AccountUpdateStatus:
            processingResult = processAccountUpdateStatus(stream, id);
            break;
        case TLValue::AccountUpdateUsername:
            processingResult = processAccountUpdateUsername(stream, id);
            break;
        case TLValue::MessagesEditChatTitle:
        case TLValue::MessagesEditChatPhoto:
        case TLValue::MessagesAddChatUser:
        case TLValue::MessagesDeleteChatUser:
        case TLValue::MessagesCreateChat:
        case TLValue::MessagesSendMessage:
        case TLValue::MessagesSendMedia:
        {
            bool ok;
            processingResult = processUpdate(stream, &ok, id);
        }
            break;
        default:
            qDebug() << "Unknown outgoing RPC type:" << request.toString();
            break;
        case TLValue::Ping:
            break;
        }

        switch (processingResult) {
        case TLValue::RpcError:
            processRpcError(stream, id, request);
            break;
        case TLValue::GzipPacked:
            processGzipPackedRpcResult(stream, id);
            break;
        default:
            // Any other results considered as success
            m_submittedPackages.remove(id);
            addMessageToAck(id);
            break;
        }
        if (stream.error()) {
            qWarning() << Q_FUNC_INFO << "Read of RPC result caused an error. RPC type:" << request.toString() << "Package id:" << id;
        }
    } else {
        stream >> request;
        qDebug() << "Unexpected RPC message:" << request.toString() << "id" << id;
    }
}

void CTelegramConnection::processGzipPackedRpcQuery(CTelegramStream &stream)
{
    QByteArray packedData;
    stream >> packedData;

    const QByteArray data = Utils::unpackGZip(packedData);

    if (!data.isEmpty()) {
        processRpcQuery(data);
    }
}

void CTelegramConnection::processGzipPackedRpcResult(CTelegramStream &stream, quint64 id)
{
    QByteArray packedData;
    stream >> packedData;

    const QByteArray data = Utils::unpackGZip(packedData);

    if (!data.isEmpty()) {
        CTelegramStream unpackedStream(data);
        processRpcResult(unpackedStream, id);
    }
}

bool CTelegramConnection::processRpcError(CTelegramStream &stream, quint64 id, TLValue request)
{
    quint32 errorCode;
    stream >> errorCode;

    QString errorMessage;
    stream >> errorMessage;

    qDebug() << Q_FUNC_INFO << QString(QLatin1String("RPC Error %1: %2 for message %3 %4 (dc %5|%6:%7)"))
                .arg(errorCode).arg(errorMessage).arg(id).arg(request.toString()).arg(m_dcInfo.id).arg(m_dcInfo.ipAddress).arg(m_dcInfo.port);

    switch (errorCode) {
    case 303: // ERROR_SEE_OTHER
        if (processErrorSeeOther(errorMessage, id)) {
            return true;
        }
        break;
    case 400: // BAD_REQUEST
#ifdef DEVELOPER_BUILD
        if (m_submittedPackages.contains(id)) {
            const QByteArray data = m_submittedPackages.value(id);
            CTelegramStream outputStream(data);
            dumpRpc(outputStream);
        } else {
            qDebug() << Q_FUNC_INFO << "Submitted package not found";
        }
#endif
        switch (request) {
        case TLValue::AuthCheckPassword:
        case TLValue::AuthCheckPhone:
        case TLValue::AuthSendCode:
        case TLValue::AuthSendCall:
        case TLValue::AuthSignIn:
        case TLValue::AuthSignUp:
            if (errorMessage == QLatin1String("API_ID_INVALID")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorAppIdIsInvalid, errorMessage);
            } else if (errorMessage == QLatin1String("PHONE_NUMBER_INVALID")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorPhoneNumberIsInvalid, errorMessage);
            } else if (errorMessage == QLatin1String("PHONE_NUMBER_OCCUPIED")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorPhoneNumberIsOccupied, errorMessage);
            } else if (errorMessage == QLatin1String("PHONE_NUMBER_UNOCCUPIED")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorPhoneNumberIsUnoccupied, errorMessage);
            } else if (errorMessage == QLatin1String("PHONE_CODE_INVALID")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorPhoneCodeIsInvalid, errorMessage);
            } else if (errorMessage == QLatin1String("PHONE_CODE_EXPIRED")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorPhoneCodeIsExpired, errorMessage);
            } else if (errorMessage == QLatin1String("PASSWORD_HASH_INVALID")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorPasswordHashInvalid, errorMessage);
            } else if (errorMessage == QLatin1String("FIRSTNAME_INVALID")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorFirstNameIsInvalid, errorMessage);
            } else if (errorMessage == QLatin1String("LASTNAME_INVALID")) {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorLastNameIsInvalid, errorMessage);
            } else {
                emit authSignErrorReceived(TelegramNamespace::AuthSignErrorUnknown, errorMessage);
            }

            return true;
        case TLValue::AccountCheckUsername:
        case TLValue::AccountUpdateUsername: {
            const QString userName = userNameFromPackage(id);

            if (errorMessage == QLatin1String("USERNAME_INVALID")) {
                emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusIsInvalid);
            } else if (errorMessage == QLatin1String("USERNAME_OCCUPIED")) {
                emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusIsOccupied);
            } else if (errorMessage == QLatin1String("USERNAME_NOT_MODIFIED")) {
                emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusIsNotModified);
            } else {
                emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusUnknown);
            }
        }
            return true;
            break;
        case TLValue::MessagesGetChats:
        {
            const QByteArray data = m_submittedPackages.value(id);
            CTelegramStream stream(data);

            TLValue request;
            stream >> request;
            TLVector<quint32> ids;
            stream >> ids;

            if (ids.count() != 1) {
                qDebug() << "Trying to restore by requesting chat one by one";
                foreach (const quint32 id, ids) {
                    messagesGetChats(TLVector<quint32>() << id);
                }
            }
        }
        default:
            break;
        }
        break;
    case 401: // UNAUTHORIZED
        if (errorMessage == QLatin1String("AUTH_KEY_UNREGISTERED")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorKeyUnregistered, errorMessage);
        } else if (errorMessage == QLatin1String("AUTH_KEY_INVALID")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorKeyInvalid, errorMessage);
        } else if (errorMessage == QLatin1String("USER_DEACTIVATED")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorUserDeactivated, errorMessage);
        } else if (errorMessage == QLatin1String("SESSION_REVOKED")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorUserSessionRevoked, errorMessage);
        } else if (errorMessage == QLatin1String("SESSION_EXPIRED")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorUserSessionExpired, errorMessage);
        } else if (errorMessage == QLatin1String("ACTIVE_USER_REQUIRED")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorActiveUserRequired, errorMessage);
        } else if (errorMessage == QLatin1String("AUTH_KEY_PERM_EMPTY")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedErrorNeedPermanentKey, errorMessage);
        } else if (errorMessage == QLatin1String("SESSION_PASSWORD_NEEDED")) {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedSessionPasswordNeeded, errorMessage);
        } else {
            emit authorizationErrorReceived(TelegramNamespace::UnauthorizedUnknownError, errorMessage);
        }
        break;

        return true;
    default:
        qDebug() << "RPC Error can not be handled.";
        break;
    }

    return false;
}

void CTelegramConnection::processMessageAck(CTelegramStream &stream)
{
    TLVector<quint64> idsVector;

    stream >> idsVector;

    foreach (quint64 id, idsVector) {
        qDebug() << Q_FUNC_INFO << "Package" << id << "acked";
//        m_submittedPackages.remove(id);
    }
}

void CTelegramConnection::processIgnoredMessageNotification(CTelegramStream &stream)
{
    // https://core.telegram.org/mtproto/service_messages_about_messages#notice-of-ignored-error-message
    quint64 id;
    stream >> id;

    quint32 seqNo;
    stream >> seqNo;

    quint32 errorCode;
    stream >> errorCode;

    QString errorText;
    switch (errorCode) {
    case 16:
        errorText = QLatin1String("Id too low");
        break;
    case 17:
        errorText = QLatin1String("Id too high");
        break;
    case 18:
        errorText = QLatin1String("Incorrect two lower order id bits");
        break;
    case 19:
        errorText = QLatin1String("Container id is the same as id of a previously received message");
        break;
    case 20:
        errorText = QLatin1String("Message too old, and it cannot be verified whether the server has received a message with this id or not");
        break;
    case 32:
        errorText = QLatin1String("Sequence number too low");
        break;
    case 33:
        errorText = QLatin1String("Sequence number too high");
        break;
    case 34:
        errorText = QLatin1String("An even sequence number expected");
        break;
    case 35:
        errorText = QLatin1String("Odd sequence number expected");
        break;
    case 48:
        errorText = QLatin1String("Incorrect server salt");
        break;
    case 64:
        errorText = QLatin1String("Invalid container");
        break;
    default:
        errorText = QLatin1String("Unknown error code");
        break;
    }
    qDebug() << QString(QLatin1String("Bad message %1/%2: Code %3 (%4).")).arg(id).arg(seqNo).arg(errorCode).arg(errorText);

    if (errorCode == 16) {
        if (m_deltaTimeHeuristicState == DeltaTimeIsOk) {
            m_deltaTimeHeuristicState = DeltaTimeCorrectionForward;
        }

        if (m_deltaTimeHeuristicState == DeltaTimeCorrectionForward) {
            setDeltaTime(deltaTime() + 1000);
        } else {
            setDeltaTime(deltaTime() + 100);
        }

        sendEncryptedPackageAgain(id);
        qDebug() << "DeltaTime factor increased to" << deltaTime();
    } else if (errorCode == 17) {
        if (m_deltaTimeHeuristicState == DeltaTimeIsOk) {
            m_deltaTimeHeuristicState = DeltaTimeCorrectionBackward;
        }

        if (m_deltaTimeHeuristicState == DeltaTimeCorrectionBackward) {
            setDeltaTime(deltaTime() - 1000);
        } else {
            setDeltaTime(deltaTime() - 100);
        }

        sendEncryptedPackageAgain(id);
        qDebug() << "DeltaTime factor reduced to" << deltaTime();
    } else if (errorCode == 48) {
        m_serverSalt = m_receivedServerSalt;
        sendEncryptedPackageAgain(id);
        qDebug() << "Local serverSalt fixed to" << m_serverSalt;
    }
}

void CTelegramConnection::processPingPong(CTelegramStream &stream)
{
    quint64 pid;
    quint64 msgId;
    stream >> msgId;
    stream >> pid;

    m_lastReceivedPingId = pid;
    m_lastReceivedPingTime = QDateTime::currentMSecsSinceEpoch();

//    qDebug() << Q_FUNC_INFO << m_lastReceivedPingId << m_lastReceivedPingTime;
}

TLValue CTelegramConnection::processHelpGetConfig(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLConfig result;
    stream >> result;

    if (result.tlType == TLValue::Config) {
        m_dcConfiguration = result.dcOptions;

        if (m_dcInfo.id != result.thisDc) {
            const quint32 oldId = m_dcInfo.id;
            m_dcInfo.id = result.thisDc;
            emit actualDcIdReceived(oldId, result.thisDc);
        }

        emit dcConfigurationReceived(m_dcInfo.id);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processContactsGetContacts(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLContactsContacts result;
    stream >> result;

    if (result.tlType == TLValue::ContactsContacts) {
        emit usersReceived(result.users);

        QVector<quint32> contactList;
        foreach (const TLUser &user, result.users) {
            contactList.append(user.id);
        }

        emit contactListReceived(contactList);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processContactsImportContacts(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLContactsImportedContacts result;
    stream >> result;

    if (result.tlType == TLValue::ContactsImportedContacts) {
        emit usersReceived(result.users);

        QVector<quint32> addedList;
        foreach (const TLUser &user, result.users) {
            addedList.append(user.id);
        }

        emit contactListChanged(addedList, QVector<quint32>());
    }

    return result.tlType;
}

TLValue CTelegramConnection::processContactsDeleteContacts(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLValue result;
    stream >> result;

    return result;
}

TLValue CTelegramConnection::processContactsResolveUsername(CTelegramStream &stream, quint64 id)
{
    TLUser result;
    stream >> result;

    const QString userName = userNameFromPackage(id);

    if (result.username == userName) {
        emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusResolved);
        emit usersReceived(QVector<TLUser>() << result);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processUpdatesGetState(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLUpdatesState result;
    stream >> result;

    switch (result.tlType) {
    case TLValue::UpdatesState:
        emit updatesStateReceived(result);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processUpdatesGetDifference(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLUpdatesDifference result;
    stream >> result;

    switch (result.tlType) {
    case TLValue::UpdatesDifference:
    case TLValue::UpdatesDifferenceSlice:
    case TLValue::UpdatesDifferenceEmpty:
        emit updatesDifferenceReceived(result);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthCheckPhone(CTelegramStream &stream, quint64 id)
{
    TLAuthCheckedPhone result;
    stream >> result;

    if (result.tlType == TLValue::AuthCheckedPhone) {
        const QByteArray data = m_submittedPackages.value(id);

        if (data.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Can not restore rpc message" << id;
            return result.tlType;
        }

        CTelegramStream stream(data);
        TLValue value;
        QString phone;
        stream >> value;
        stream >> phone;

        emit phoneStatusReceived(phone, result.phoneRegistered);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthExportAuthorization(CTelegramStream &stream, quint64 id)
{
    TLAuthExportedAuthorization result;
    stream >> result;

    if (result.tlType == TLValue::AuthExportedAuthorization) {
        const QByteArray data = m_submittedPackages.value(id);

        if (data.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Can not restore rpc message" << id;
            return result.tlType;
        }

        CTelegramStream stream(data);
        TLValue value;
        quint32 dc;
        stream >> value;
        stream >> dc;

        emit authExportedAuthorizationReceived(dc, result.id, result.bytes);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthSendCode(CTelegramStream &stream, quint64 id)
{
    TLAuthSentCode result;
    stream >> result;
    qDebug() << Q_FUNC_INFO << result.tlType.toString();

    if (result.tlType == TLValue::AuthSentCode) {
        m_authCodeHash = result.phoneCodeHash;

        emit phoneCodeRequired();
    } else if (result.tlType == TLValue::AuthSentAppCode) {
        qDebug() << Q_FUNC_INFO << "AuthSentAppCode";
        m_authCodeHash = result.phoneCodeHash;

        const QByteArray data = m_submittedPackages.value(id);

        if (data.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Can not restore rpc message" << id;
            return result.tlType;
        }

        CTelegramStream stream(data);
        TLValue value;
        QString phoneNumber;
        stream >> value;
        stream >> phoneNumber;

        authSendSms(phoneNumber, m_authCodeHash);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthSendSms(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLValue result;
    stream >> result;

    return result;
}

TLValue CTelegramConnection::processAuthSign(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLAuthAuthorization result;
    stream >> result;

    qDebug() << Q_FUNC_INFO << "AuthAuthorization" << maskPhoneNumber(result.user.phone);
    if (result.tlType == TLValue::AuthAuthorization) {
        emit selfUserReceived(result.user);
        emit usersReceived(QVector<TLUser>() << result.user);
        setAuthState(AuthStateSignedIn);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthLogOut(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLValue result;
    stream >> result;

    emit loggedOut(result == TLValue::BoolTrue);

    return result;
}

TLValue CTelegramConnection::processUploadGetFile(CTelegramStream &stream, quint64 id)
{
    TLUploadFile file;
    stream >> file;

    if (file.tlType == TLValue::UploadFile) {
        const QByteArray data = m_submittedPackages.value(id);

        if (data.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Can not restore rpc message" << id;
        } else {
            CTelegramStream stream(data);
            TLValue value;
            TLInputFileLocation location;
            quint32 offset;

            stream >> value;
            stream >> location;
            stream >> offset;

            emit fileDataReceived(file, m_requestedFilesIds.value(id), offset);
        }
    }

    return file.tlType;
}

TLValue CTelegramConnection::processUploadSaveFilePart(CTelegramStream &stream, quint64 id)
{
    TLValue result;
    stream >> result;

    if (result == TLValue::BoolTrue) {
        emit fileDataSent(m_requestedFilesIds.take(id));
    } else {
        // retry putFile() call?
    }

    return result;
}

TLValue CTelegramConnection::processUsersGetUsers(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLVector<TLUser> result;

    stream >> result;

    if (result.tlType == TLValue::Vector) {
        const QByteArray data = m_submittedPackages.value(id);

        if (data.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Can not restore rpc message" << id;
            return result.tlType;
        }

        CTelegramStream stream(data);
        TLValue value;
        TLVector<TLInputUser> inputUsers;
        stream >> value;
        stream >> inputUsers;

        if (result.count() != inputUsers.count()) {
            qWarning() << Q_FUNC_INFO << "Input user count != received user count";
        }

        if ((inputUsers.count() == 1) && (result.count() == 1)) {
            if (inputUsers.first().tlType == TLValue::InputUserSelf) {
                emit selfUserReceived(result.first());
            }
        }

        emit usersReceived(result);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processUsersGetFullUser(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLUserFull result;

    stream >> result;

    switch (result.tlType) {
    case TLValue::UserFull:
        emit fullUserReceived(result);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesSetTyping(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLValue result;
    stream >> result;

    return result;
}

TLValue CTelegramConnection::processMessagesReadHistory(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLMessagesAffectedHistory result;
    stream >> result;

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesReceivedMessages(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLVector<quint32> result;
    stream >> result;

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesGetHistory(CTelegramStream &stream, quint64 id)
{
    TLMessagesMessages result;
    stream >> result;

    const QByteArray data = m_submittedPackages.value(id);

    if (data.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Can not restore rpc message" << id;
    } else {
        CTelegramStream stream(data);
        TLValue value;
        TLInputPeer peer;

        stream >> value;
        stream >> peer;

        emit messagesHistoryReceived(result, peer);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesGetDialogs(CTelegramStream &stream, quint64 id)
{
    TLMessagesDialogs result;
    stream >> result;

    const QByteArray data = m_submittedPackages.value(id);

    quint32 offset = 0;
    quint32 maxId = 0;
    quint32 limit = 0;

    switch (result.tlType) {
    case TLValue::MessagesDialogs:
    case TLValue::MessagesDialogsSlice:
        if (data.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "Can not restore rpc message" << id;
        } else {
            CTelegramStream stream(data);
            TLValue method;
            stream >> method; // TLValue::MessagesGetDialogs
            stream >> offset;
            stream >> maxId;
            stream >> limit;
        }

        emit messagesDialogsReceived(result, offset, maxId, limit);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesGetChats(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLMessagesChats result;
    stream >> result;

    if (result.tlType == TLValue::MessagesChats) {
        emit messagesChatsReceived(result.chats);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesGetFullChat(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLMessagesChatFull result;
    stream >> result;

    if (result.tlType == TLValue::MessagesChatFull) {
        emit messagesFullChatReceived(result.fullChat, result.chats, result.users);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAccountCheckUsername(CTelegramStream &stream, quint64 id)
{
    TLValue result;
    stream >> result;

    const QString userName = userNameFromPackage(id);

    switch (result) {
    case TLValue::BoolTrue:
        emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusCanBeUsed);
        break;
    case TLValue::BoolFalse:
        emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusCanNotBeUsed);
        break;
    default:
        break;
    }

    return result;
}

TLValue CTelegramConnection::processAccountGetPassword(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLAccountPassword result;
    stream >> result;

    switch (result.tlType) {
    case TLValue::AccountNoPassword:
    case TLValue::AccountPassword:
        emit passwordReceived(result, id);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAccountUpdateStatus(CTelegramStream &stream, quint64 id)
{
    Q_UNUSED(id);

    TLValue result;
    stream >> result;

    return result;
}

TLValue CTelegramConnection::processAccountUpdateUsername(CTelegramStream &stream, quint64 id)
{
    TLUser result;
    stream >> result;

    const QString userName = userNameFromPackage(id);

    if (result.username == userName) {
        emit userNameStatusUpdated(userName, TelegramNamespace::UserNameStatusAccepted);
    }
    emit usersReceived(QVector<TLUser>() << result);

    return result.tlType;
}

bool CTelegramConnection::processErrorSeeOther(const QString errorMessage, quint64 id)
{
    int lastSectionIndex = errorMessage.lastIndexOf(QChar(QLatin1Char('_')));
    if (lastSectionIndex < 0) {
        return false;
    }

    quint16 dc = 0;

    bool ok;

    const QString dcStr = errorMessage.mid(lastSectionIndex + 1);
    dc = dcStr.toUInt(&ok);

    if (!ok) {
        return false;
    }

    const QByteArray data = m_submittedPackages.take(id);

    if (data.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Can not restore message" << id;
        return false;
    }

    CTelegramStream stream(data);
    TLValue value;
    stream >> value;

    switch (value) {
    case TLValue::AuthCheckPhone:
    case TLValue::AuthSendCode:
    case TLValue::AuthSendCall:
    case TLValue::AuthSendSms: {
        QString phoneNumber;
        stream >> phoneNumber;
        emit wantedMainDcChanged(dc, phoneNumber);
    }
    default:
        emit newRedirectedPackage(data, dc);
        break;
    }

    return true;
}

TLValue CTelegramConnection::processUpdate(CTelegramStream &stream, bool *ok, quint64 id)
{
    TLUpdates updates;
    stream >> updates;

    if (stream.error()) {
        qWarning() << Q_FUNC_INFO << "Read of an update caused an error.";
    }

    switch (updates.tlType) {
    case TLValue::UpdatesTooLong:
    case TLValue::UpdateShortMessage:
    case TLValue::UpdateShortChatMessage:
    case TLValue::UpdateShortSentMessage:
    case TLValue::UpdateShort:
    case TLValue::UpdatesCombined:
    case TLValue::Updates:
        emit updatesReceived(updates, id);
        *ok = true;
        break;
    default:
        *ok = false;
        break;
    }

    return updates.tlType;
}

void CTelegramConnection::whenTransportStateChanged()
{
#ifdef NETWORK_LOGGING
    if (!m_logFile) {
        QDir dir;
        dir.mkdir(QLatin1String("network"));

        m_logFile = new QFile(QLatin1String("network/") + m_dcInfo.ipAddress + QLatin1String(".log"));
        m_logFile->open(QIODevice::WriteOnly);
    }

    qDebug() << Q_FUNC_INFO << m_dcInfo.id << m_dcInfo.ipAddress << m_transport->state();
#endif

    switch (m_transport->state()) {
    case QAbstractSocket::ConnectedState:
        startAuthTimer();

        if (m_authKey.isEmpty()) {
            initAuth();
        } else {
            setAuthState(AuthStateSignedIn);
        }

        setStatus(ConnectionStatusConnected);
        break;
    case QAbstractSocket::UnconnectedState:
        setStatus(ConnectionStatusDisconnected);
        break;
    default:
        break;
    }
}

void CTelegramConnection::whenTransportReadyRead()
{
    QByteArray input = m_transport->getPackage();
    CRawStream inputStream(input);

    quint64 auth = 0;
    quint64 timeStamp = 0;
    quint32 length = 0;
    QByteArray payload;

    inputStream >> auth;

    /* Will be reimplemented later */

    if (!auth) {
        // Plain Message
        inputStream >> timeStamp;
        inputStream >> length;

        if (inputStream.bytesRemaining() != int(length)) {
            qDebug() << Q_FUNC_INFO << "Corrupted packet. Specified length does not equal to real length";
            return;
        }

        payload = inputStream.readBytes(length);

        switch (m_authState) {
        case AuthStatePqRequested:
            if (answerPqAuthorization(payload)) {
                requestDhParameters();
            }
            break;
        case AuthStateDhRequested:
            if (answerDh(payload)) {
                requestDhGenerationResult();
            }
            break;
        case AuthStateDhGenerationResultRequested:
            processServersDHAnswer(payload);
            break;
        default:
            break;
        }
    } else {
        if (m_authState < AuthStateHaveAKey) {
            qWarning() << Q_FUNC_INFO << "Unexpected message with auth data";
        }

        if (auth != m_authId) {
            qDebug() << Q_FUNC_INFO << "Incorrect auth id.";

#ifdef NETWORK_LOGGING
            QTextStream str(m_logFile);

            str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz")) << QLatin1Char('|');
            str << QLatin1String("pln|");
            str << QString(QLatin1String("size: %1|")).arg(input.length(), 4, 10, QLatin1Char('0'));
            str << QLatin1Char('|');
            str << input.toHex();
            str << endl;
            str.flush();
#endif

            return;
        }
        // Encrypted Message
        const QByteArray messageKey = inputStream.readBytes(16);
        const QByteArray data = inputStream.readBytes(inputStream.bytesRemaining());

        const SAesKey key = generateServerToClientAesKey(messageKey);

        QByteArray decryptedData = Utils::aesDecrypt(data, key).left(data.length());
        CRawStream decryptedStream(decryptedData);

        quint64 sessionId = 0;
        quint64 messageId  = 0;
        quint32 sequence = 0;
        quint32 contentLength = 0;

        decryptedStream >> m_receivedServerSalt;
        decryptedStream >> sessionId;
        decryptedStream >> messageId;
        decryptedStream >> sequence;
        decryptedStream >> contentLength;

        if (m_serverSalt != m_receivedServerSalt) {
            qDebug() << Q_FUNC_INFO << "Received different server salt:" << m_receivedServerSalt << "(remote) vs" << m_serverSalt << "(local)";
//            return;
        }

        if (m_sessionId != sessionId) {
            qDebug() << Q_FUNC_INFO << "Session Id is wrong.";
            return;
        }

        if (int(contentLength) > decryptedData.length()) {
            qDebug() << Q_FUNC_INFO << "Expected data length is more, than actual.";
            return;
        }

        const int headerLength = sizeof(m_receivedServerSalt) + sizeof(sessionId) + sizeof(messageId) + sizeof(sequence) + sizeof(contentLength);
        QByteArray expectedMessageKey = Utils::sha1(decryptedData.left(headerLength + contentLength)).mid(4);

        if (messageKey != expectedMessageKey) {
            qDebug() << Q_FUNC_INFO << "Wrong message key";
            return;
        }

        payload = decryptedStream.readRemainingBytes();

        processRpcQuery(payload);
    }

#ifdef DEVELOPER_BUILD
    TLValue firstValue;

    if (payload.length() >= 4) {
        quint32 *v = (quint32 *) payload.constData();
        firstValue = TLValue(*v);
    }

    static int packagesCount = 0;
    qDebug() << Q_FUNC_INFO << "Got package" << ++packagesCount << firstValue.toString();
#endif
}

void CTelegramConnection::whenTransportTimeout()
{
    setStatus(ConnectionStatusDisconnected, ConnectionStatusReasonTimeout);
}

void CTelegramConnection::whenItsTimeToPing()
{
//    qDebug() << Q_FUNC_INFO << QDateTime::currentMSecsSinceEpoch();

    if (status() < ConnectionStatusConnected) {
        // Nothing to do.
        return;
    }

    if (m_lastSentPingTime && (m_lastSentPingTime > m_lastReceivedPingTime + m_pingInterval)) {
        qDebug() << Q_FUNC_INFO << "pong time is out";
        setStatus(ConnectionStatusDisconnected, ConnectionStatusReasonTimeout);
        return;
    }

    m_lastSentPingTime = QDateTime::currentMSecsSinceEpoch();

    pingDelayDisconnect(m_pingInterval + m_serverDisconnectionExtraTime); // Server will close the connection after m_serverDisconnectionExtraTime ms more, than our ping interval.
}

void CTelegramConnection::whenItsTimeToAckMessages()
{
    if (m_messagesToAck.isEmpty()) {
        return;
    }

    acknowledgeMessages(m_messagesToAck);
    m_messagesToAck.clear();
}

SAesKey CTelegramConnection::generateTmpAesKey() const
{
    QByteArray newNonceAndServerNonce;
    newNonceAndServerNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndServerNonce.append(m_serverNonce.data, m_serverNonce.size());
    QByteArray serverNonceAndNewNonce;
    serverNonceAndNewNonce.append(m_serverNonce.data, m_serverNonce.size());
    serverNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    QByteArray newNonceAndNewNonce;
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());

    const QByteArray key = Utils::sha1(newNonceAndServerNonce) + Utils::sha1(serverNonceAndNewNonce).mid(0, 12);
    const QByteArray iv  = Utils::sha1(serverNonceAndNewNonce).mid(12, 8) + Utils::sha1(newNonceAndNewNonce) + QByteArray(m_newNonce.data, 4);

    return SAesKey(key, iv);
}

SAesKey CTelegramConnection::generateAesKey(const QByteArray &messageKey, int x) const
{
    QByteArray sha1_a = Utils::sha1(messageKey + m_authKey.mid(x, 32));
    QByteArray sha1_b = Utils::sha1(m_authKey.mid(32 + x, 16) + messageKey + m_authKey.mid(48 + x, 16));
    QByteArray sha1_c = Utils::sha1(m_authKey.mid(64 + x, 32) + messageKey);
    QByteArray sha1_d = Utils::sha1(messageKey + m_authKey.mid(96 + x, 32));

    const QByteArray key = sha1_a.mid(0, 8) + sha1_b.mid(8, 12) + sha1_c.mid(4, 12);
    const QByteArray iv  = sha1_a.mid(8, 12) + sha1_b.mid(0, 8) + sha1_c.mid(16, 4) + sha1_d.mid(0, 8);

    return SAesKey(key, iv);
}

void CTelegramConnection::insertInitConnection(QByteArray *data) const
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << "layer" << TLValue::CurrentLayer;
#endif

    CTelegramStream outputStream(data, /* write */ true);

    outputStream << TLValue::InvokeWithLayer;
    outputStream << TLValue::CurrentLayer;
    outputStream << TLValue::InitConnection;

    outputStream << m_appInfo->appId();
    outputStream << m_appInfo->deviceInfo();
    outputStream << m_appInfo->osInfo();
    outputStream << m_appInfo->appVersion();
    outputStream << m_appInfo->languageCode();
}

quint64 CTelegramConnection::sendPlainPackage(const QByteArray &buffer)
{
    quint64 messageId = newMessageId();

    QByteArray output;
    CRawStream outputStream(&output, /* write */ true);

    outputStream << quint64(0);
    outputStream << messageId;
    outputStream << quint32(buffer.length());
    outputStream << buffer;

    m_transport->sendPackage(output);

#ifdef NETWORK_LOGGING
    CTelegramStream readBack(buffer);
    TLValue val1;
    readBack >> val1;

    QTextStream str(m_logFile);

    str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz")) << QLatin1Char('|');
    str << QLatin1String("pln|");
    str << QString(QLatin1String("size: %1|")).arg(buffer.length(), 4, 10, QLatin1Char('0'));
    str << formatTLValue(val1) << QLatin1Char('|');
    str << buffer.toHex();
    str << endl;
    str.flush();
#endif

    return messageId;
}

quint64 CTelegramConnection::sendEncryptedPackage(const QByteArray &buffer, bool savePackage)
{
    QByteArray encryptedPackage;
    QByteArray messageKey;
    quint64 messageId;
    {
        messageId = newMessageId();

        m_sequenceNumber = m_contentRelatedMessages * 2 + 1;
        ++m_contentRelatedMessages;

        if (savePackage) {
            // Story only content-related messages
            m_submittedPackages.insert(messageId, buffer);
        }

        QByteArray innerData;
        CRawStream stream(&innerData, /* write */ true);

        stream << m_serverSalt;
        stream << m_sessionId;
        stream << messageId;
        stream << m_sequenceNumber;

        QByteArray header;
        if (m_sequenceNumber == 1) {
            insertInitConnection(&header);
        }

        stream << quint32(header.length() + buffer.length());
        stream << header + buffer;

        messageKey = Utils::sha1(innerData).mid(4);
        const SAesKey key = generateClientToServerAesKey(messageKey);

        quint32 packageLength = innerData.length();

        if ((packageLength) % 16) {
            QByteArray randomPadding;
            randomPadding.resize(16 - (packageLength % 16));
            Utils::randomBytes(&randomPadding);

            packageLength += randomPadding.size();

            stream << randomPadding;
        }

        encryptedPackage = Utils::aesEncrypt(innerData, key).left(packageLength);
    }

    QByteArray output;
    CRawStream outputStream(&output, /* write */ true);

    outputStream << m_authId;
    outputStream << messageKey;
    outputStream << encryptedPackage;

    m_transport->sendPackage(output);

#ifdef NETWORK_LOGGING
    CTelegramStream readBack(buffer);
    TLValue val1;
    readBack >> val1;

    QTextStream str(m_logFile);

    str << QString(QLatin1String("%1|enc|mId%2|seq%3|"))
           .arg(QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz")))
           .arg(messageId, 10, 10, QLatin1Char('0'))
           .arg(m_sequenceNumber, 4, 10, QLatin1Char('0'));

    str << QString(QLatin1String("size: %1|")).arg(buffer.length(), 4, 10, QLatin1Char('0'));

    str << formatTLValue(val1) << QLatin1Char('|');
    str << buffer.toHex();
    str << endl;
    str.flush();
#endif

    return messageId;
}

quint64 CTelegramConnection::sendEncryptedPackageAgain(quint64 id)
{
    --m_contentRelatedMessages;
    const QByteArray data = m_submittedPackages.take(id);
#ifdef DEVELOPER_BUILD
    TLValue firstValue = TLValue::firstFromArray(data);
    qDebug() << Q_FUNC_INFO << id << firstValue.toString();
#endif
    return sendEncryptedPackage(data);
}

void CTelegramConnection::setStatus(ConnectionStatus status, ConnectionStatusReason reason)
{
    if (m_status == status) {
        return;
    }

    m_status = status;
    emit statusChanged(status, reason, m_dcInfo.id);

    if (status < ConnectionStatusConnected) {
        stopPingTimer();
    }
}

void CTelegramConnection::setAuthState(CTelegramConnection::AuthState newState)
{
    if (m_authState == newState)
        return;

    m_authState = newState;

    if ((m_authState >= AuthStateHaveAKey) && !m_sessionId) {
        Utils::randomBytes(&m_sessionId);
    }

    emit authStateChanged(m_authState, m_dcInfo.id);

    if (m_authState >= AuthStateHaveAKey) {
        stopAuthTimer();

        if (m_pingInterval) {
            startPingTimer();
        }
    }
}

quint64 CTelegramConnection::newMessageId()
{
    quint64 newLastMessageId = formatClientTimeStamp(QDateTime::currentMSecsSinceEpoch() + deltaTime() * 1000);

    if (newLastMessageId <= m_lastMessageId) {
        newLastMessageId = m_lastMessageId + 4; // Client's outgoing message id should be divisible by 4 and be greater than previous message id.
    }

    if (!(newLastMessageId & quint64(0xffffff))) {
        // The lower 32 bits of messageId passed by the client must not contain that many zeroes.
        newLastMessageId += quint64(0x1230);
    }

    m_lastMessageId = newLastMessageId;

    return m_lastMessageId;
}

QString CTelegramConnection::userNameFromPackage(quint64 id) const
{
    const QByteArray data = m_submittedPackages.value(id);

    if (data.isEmpty()) {
        return QString();
    }

    CTelegramStream outputStream(data);

    TLValue method;

    outputStream >> method;

    switch (method) {
    case TLValue::AccountCheckUsername:
    case TLValue::AccountUpdateUsername:
    case TLValue::ContactsResolveUsername:
        break;
    default:
        return QString();
    }

    QString name;
    outputStream >> name;

    return name;
}

void CTelegramConnection::startAuthTimer()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_authTimer) {
        m_authTimer = new QTimer(this);
        m_authTimer->setInterval(s_defaultAuthInterval);
        m_authTimer->setSingleShot(true);
        connect(m_authTimer, SIGNAL(timeout()), SLOT(whenTransportTimeout()));
    }

    m_authTimer->start();
}

void CTelegramConnection::stopAuthTimer()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_authTimer) {
        return;
    }

    m_authTimer->deleteLater();
    m_authTimer = 0;
}

void CTelegramConnection::startPingTimer()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_pingTimer) {
        m_pingTimer = new QTimer(this);
        m_pingTimer->setSingleShot(false);
        connect(m_pingTimer, SIGNAL(timeout()), SLOT(whenItsTimeToPing()));
    }

    if (m_pingTimer->interval() != static_cast<int>(m_pingInterval)) {
        m_pingTimer->setInterval(m_pingInterval);
    }

    if (m_pingTimer->isActive()) {
        return;
    }

    m_lastReceivedPingId = 0;
    m_lastSentPingId = 0;
    m_lastReceivedPingTime = 0;
    m_lastSentPingTime = 0;

    m_pingTimer->start();
}

void CTelegramConnection::stopPingTimer()
{
    qDebug() << Q_FUNC_INFO;
    if (m_pingTimer) {
        m_pingTimer->stop();
    }
}

void CTelegramConnection::addMessageToAck(quint64 id)
{
//    qDebug() << Q_FUNC_INFO << id;
    if (!m_ackTimer->isActive()) {
        m_ackTimer->start();
    }

    m_messagesToAck.append(id);

    if (m_messagesToAck.count() > 6) {
        whenItsTimeToAckMessages();
        m_ackTimer->stop();
    }
}
