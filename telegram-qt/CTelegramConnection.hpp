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

#ifndef CTELEGRAMCONNECTION_HPP
#define CTELEGRAMCONNECTION_HPP

#include <QObject>
#include <QByteArray>
#include <QVector>
#include <QMap>
#include <QStringList>

#include "TelegramNamespace.hpp"
#include "TLTypes.hpp"
#include "TLNumbers.hpp"
#include "crypto-rsa.hpp"
#include "crypto-aes.hpp"

class CAppInformation;
class CTelegramStream;
class CTelegramTransport;

#ifdef NETWORK_LOGGING
class QFile;
#endif

class QTimer;

class CTelegramConnection : public QObject
{
    Q_OBJECT
public:
    enum ConnectionStatus {
        ConnectionStatusDisconnected,
        ConnectionStatusConnecting,
        ConnectionStatusConnected,
        ConnectionStatusAuthenticated,
        ConnectionStatusSigned
    };

    enum ConnectionStatusReason {
        ConnectionStatusReasonNone,
        ConnectionStatusReasonTimeout
    };

    enum AuthState {
        AuthStateNone,
        AuthStatePqRequested,
        AuthStateDhRequested,
        AuthStateDhGenerationResultRequested,
        AuthStateHaveAKey,
        AuthStateSignedIn
    };

    enum DeltaTimeHeuristicState {
        DeltaTimeIsOk,
        DeltaTimeCorrectionForward,
        DeltaTimeCorrectionBackward,
    };

    explicit CTelegramConnection(const CAppInformation *appInfo, QObject *parent = 0);

    void setDcInfo(const TLDcOption &newDcInfo);

    inline TLDcOption dcInfo() const { return m_dcInfo; }

public slots:
    void connectToDc();

public:
    inline ConnectionStatus status() const { return m_status; }

    static quint64 formatTimeStamp(qint64 timeInMs);
    static inline quint64 formatClientTimeStamp(qint64 timeInMs) { return formatTimeStamp(timeInMs) & ~quint64(3); }

    static quint64 timeStampToMSecsSinceEpoch(quint64 ts);

    void initAuth();
    void getConfiguration();

    void setKeepAliveSettings(quint32 interval, quint32 serverDisconnectionExtraTime);

    // Generated Telegram API methods declaration
    quint64 accountChangePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    quint64 accountCheckUsername(const QString &username);
    quint64 accountDeleteAccount(const QString &reason);
    quint64 accountGetAccountTTL();
    quint64 accountGetAuthorizations();
    quint64 accountGetNotifySettings(const TLInputNotifyPeer &peer);
    quint64 accountGetPassword();
    quint64 accountGetPasswordSettings(const QByteArray &currentPasswordHash);
    quint64 accountGetPrivacy(const TLInputPrivacyKey &key);
    quint64 accountGetWallPapers();
    quint64 accountRegisterDevice(quint32 tokenType, const QString &token, const QString &deviceModel, const QString &systemVersion, const QString &appVersion, bool appSandbox, const QString &langCode);
    quint64 accountResetAuthorization(quint64 hash);
    quint64 accountResetNotifySettings();
    quint64 accountSendChangePhoneCode(const QString &phoneNumber);
    quint64 accountSetAccountTTL(const TLAccountDaysTTL &ttl);
    quint64 accountSetPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules);
    quint64 accountUnregisterDevice(quint32 tokenType, const QString &token);
    quint64 accountUpdateDeviceLocked(quint32 period);
    quint64 accountUpdateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings);
    quint64 accountUpdatePasswordSettings(const QByteArray &currentPasswordHash, const TLAccountPasswordInputSettings &newSettings);
    quint64 accountUpdateProfile(const QString &firstName, const QString &lastName);
    quint64 accountUpdateStatus(bool offline);
    quint64 accountUpdateUsername(const QString &username);
    quint64 authBindTempAuthKey(quint64 permAuthKeyId, quint64 nonce, quint32 expiresAt, const QByteArray &encryptedMessage);
    quint64 authCheckPassword(const QByteArray &passwordHash);
    quint64 authCheckPhone(const QString &phoneNumber);
    quint64 authExportAuthorization(quint32 dcId);
    quint64 authImportAuthorization(quint32 id, const QByteArray &bytes);
    quint64 authLogOut();
    quint64 authRecoverPassword(const QString &code);
    quint64 authRequestPasswordRecovery();
    quint64 authResetAuthorizations();
    quint64 authSendCall(const QString &phoneNumber, const QString &phoneCodeHash);
    quint64 authSendCode(const QString &phoneNumber, quint32 smsType, quint32 apiId, const QString &apiHash, const QString &langCode);
    quint64 authSendInvites(const TLVector<QString> &phoneNumbers, const QString &message);
    quint64 authSendSms(const QString &phoneNumber, const QString &phoneCodeHash);
    quint64 authSignIn(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    quint64 authSignUp(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode, const QString &firstName, const QString &lastName);
    quint64 contactsBlock(const TLInputUser &id);
    quint64 contactsDeleteContact(const TLInputUser &id);
    quint64 contactsDeleteContacts(const TLVector<TLInputUser> &id);
    quint64 contactsExportCard();
    quint64 contactsGetBlocked(quint32 offset, quint32 limit);
    quint64 contactsGetContacts(const QString &hash);
    quint64 contactsGetStatuses();
    quint64 contactsGetSuggested(quint32 limit);
    quint64 contactsImportCard(const TLVector<quint32> &exportCard);
    quint64 contactsImportContacts(const TLVector<TLInputContact> &contacts, bool replace);
    quint64 contactsResolveUsername(const QString &username);
    quint64 contactsSearch(const QString &q, quint32 limit);
    quint64 contactsUnblock(const TLInputUser &id);
    quint64 messagesAcceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint);
    quint64 messagesAddChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit);
    quint64 messagesCheckChatInvite(const QString &hash);
    quint64 messagesCreateChat(const TLVector<TLInputUser> &users, const QString &title);
    quint64 messagesDeleteChatUser(quint32 chatId, const TLInputUser &userId);
    quint64 messagesDeleteHistory(const TLInputPeer &peer, quint32 offset);
    quint64 messagesDeleteMessages(const TLVector<quint32> &id);
    quint64 messagesDiscardEncryption(quint32 chatId);
    quint64 messagesEditChatPhoto(quint32 chatId, const TLInputChatPhoto &photo);
    quint64 messagesEditChatTitle(quint32 chatId, const QString &title);
    quint64 messagesExportChatInvite(quint32 chatId);
    quint64 messagesForwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId);
    quint64 messagesForwardMessages(const TLInputPeer &peer, const TLVector<quint32> &id, const TLVector<quint64> &randomId);
    quint64 messagesGetAllStickers(const QString &hash);
    quint64 messagesGetChats(const TLVector<quint32> &id);
    quint64 messagesGetDhConfig(quint32 version, quint32 randomLength);
    quint64 messagesGetDialogs(quint32 offset, quint32 maxId, quint32 limit);
    quint64 messagesGetFullChat(quint32 chatId);
    quint64 messagesGetHistory(const TLInputPeer &peer, quint32 offset, quint32 maxId, quint32 limit);
    quint64 messagesGetMessages(const TLVector<quint32> &id);
    quint64 messagesGetStickerSet(const TLInputStickerSet &stickerset);
    quint64 messagesGetStickers(const QString &emoticon, const QString &hash);
    quint64 messagesGetWebPagePreview(const QString &message);
    quint64 messagesImportChatInvite(const QString &hash);
    quint64 messagesInstallStickerSet(const TLInputStickerSet &stickerset);
    quint64 messagesReadEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate);
    quint64 messagesReadHistory(const TLInputPeer &peer, quint32 maxId, quint32 offset);
    quint64 messagesReadMessageContents(const TLVector<quint32> &id);
    quint64 messagesReceivedMessages(quint32 maxId);
    quint64 messagesReceivedQueue(quint32 maxQts);
    quint64 messagesRequestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA);
    quint64 messagesSearch(const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit);
    quint64 messagesSendBroadcast(const TLVector<TLInputUser> &contacts, const TLVector<quint64> &randomId, const QString &message, const TLInputMedia &media);
    quint64 messagesSendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    quint64 messagesSendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file);
    quint64 messagesSendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    quint64 messagesSendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId);
    quint64 messagesSendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId);
    quint64 messagesSetEncryptedTyping(const TLInputEncryptedChat &peer, bool typing);
    quint64 messagesSetTyping(const TLInputPeer &peer, const TLSendMessageAction &action);
    quint64 messagesUninstallStickerSet(const TLInputStickerSet &stickerset);
    quint64 updatesGetDifference(quint32 pts, quint32 date, quint32 qts);
    quint64 updatesGetState();
    quint64 uploadGetFile(const TLInputFileLocation &location, quint32 offset, quint32 limit);
    quint64 uploadSaveBigFilePart(quint64 fileId, quint32 filePart, quint32 fileTotalParts, const QByteArray &bytes);
    quint64 uploadSaveFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes);
    quint64 usersGetFullUser(const TLInputUser &id);
    quint64 usersGetUsers(const TLVector<TLInputUser> &id);
    // End of generated Telegram API methods declaration

    quint64 ping();
    quint64 pingDelayDisconnect(quint32 disconnectInSec);

    quint64 acknowledgeMessages(const TLVector<quint64> &idsVector);

    quint64 requestPhoneCode(const QString &phoneNumber);
    quint64 signIn(const QString &phoneNumber, const QString &authCode);
    quint64 signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void downloadFile(const TLInputFileLocation &inputLocation, quint32 offset, quint32 limit, quint32 requestId);
    void uploadFile(quint64 fileId, quint32 filePart, const QByteArray &bytes, quint32 requestId);

    quint64 sendMessage(const TLInputPeer &peer, const QString &message);
    quint64 sendMedia(const TLInputPeer &peer, const TLInputMedia &media);

    AuthState authState() { return m_authState; }

    void requestPqAuthorization();
    bool answerPqAuthorization(const QByteArray &payload);
    void requestDhParameters();
    bool answerDh(const QByteArray &payload);
    void requestDhGenerationResult();
    bool processServersDHAnswer(const QByteArray &payload);

    inline TLNumber128 clientNonce() const { return m_clientNonce; }
    inline TLNumber128 serverNonce() const { return m_serverNonce; }

    inline quint64 pq() const { return m_pq; }
    inline quint64 p() const { return m_p; }
    inline quint64 q() const { return m_q; }

    inline quint64 serverPublicFingersprint() const { return m_serverPublicFingersprint; }

    inline QByteArray authKey() const { return m_authKey; }
    void setAuthKey(const QByteArray &newAuthKey);
    inline quint64 authId() const { return m_authId; }

    inline quint64 serverSalt() const { return m_serverSalt; }
    void setServerSalt(const quint64 salt) { m_serverSalt = salt; }
    inline quint64 sessionId() const { return m_sessionId; }

    inline QVector<TLDcOption> dcConfiguration() const { return m_dcConfiguration; }

    inline qint32 deltaTime() const { return m_deltaTime; }
    void setDeltaTime(const qint32 newDt);

    void processRedirectedPackage(const QByteArray &data);

signals:
    void wantedActiveDcChanged(quint32 dc);
    void newRedirectedPackage(const QByteArray &data, quint32 dc);

    void statusChanged(int status, int reason, quint32 dc);
    void authStateChanged(int status, quint32 dc);
    void actualDcIdReceived(quint32 dc, quint32 newDcId);
    void dcConfigurationReceived(quint32 dc);
    void phoneStatusReceived(const QString &phone, bool registered);
    void phoneCodeRequired();
    void loggedOut(bool result);
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void authorizationErrorReceived();
    void userNameStatusUpdated(const QString &userName, TelegramNamespace::AccountUserNameStatus status);
    void usersReceived(const QVector<TLUser> &users);
    void contactListReceived(const QVector<quint32> &contactList);
    void contactListChanged(const QVector<quint32> &added, const QVector<quint32> &removed);
    void fileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset);
    void fileDataSent(quint32 requestId);

    void messagesChatsReceived(const QVector<TLChat> &chats);
    void messagesFullChatReceived(const TLChatFull &chat, const QVector<TLChat> &chats, const QVector<TLUser> &users);

    void fullUserReceived(const TLUserFull &userFull);
    void messagesHistoryReceived(const TLMessagesMessages &history, const TLInputPeer &peer);

    void updatesReceived(const TLUpdates &update);
    void updatesStateReceived(const TLUpdatesState &updatesState);
    void updatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

    void messageSentInfoReceived(const TLInputPeer &peer, quint64 randomId, quint32 messageId, quint32 pts, quint32 date, quint32 seq);
    void authExportedAuthorizationReceived(quint32 dc, quint32 id, const QByteArray &data);

protected:
    TLValue processRpcQuery(const QByteArray &data);

    void processSessionCreated(CTelegramStream &stream);
    void processContainer(CTelegramStream &stream);
    void processRpcResult(CTelegramStream &stream, quint64 idHint = 0);
    void processGzipPackedRpcQuery(CTelegramStream &stream);
    void processGzipPackedRpcResult(CTelegramStream &stream, quint64 id);
    bool processRpcError(CTelegramStream &stream, quint64 id, TLValue request);

    void processMessageAck(CTelegramStream &stream);
    void processIgnoredMessageNotification(CTelegramStream &stream);
    void processPingPong(CTelegramStream &stream);

    TLValue processHelpGetConfig(CTelegramStream &stream, quint64 id);
    TLValue processContactsGetContacts(CTelegramStream &stream, quint64 id);
    TLValue processContactsImportContacts(CTelegramStream &stream, quint64 id);
    TLValue processContactsDeleteContacts(CTelegramStream &stream, quint64 id);
    TLValue processUpdatesGetState(CTelegramStream &stream, quint64 id);
    TLValue processUpdatesGetDifference(CTelegramStream &stream, quint64 id);
    TLValue processAuthCheckPhone(CTelegramStream &stream, quint64 id);
    TLValue processAuthExportAuthorization(CTelegramStream &stream, quint64 id);
    TLValue processAuthSendCode(CTelegramStream &stream, quint64 id);
    TLValue processAuthSendSms(CTelegramStream &stream, quint64 id);
    TLValue processAuthSign(CTelegramStream &stream, quint64 id);
    TLValue processAuthLogOut(CTelegramStream &stream, quint64 id);
    TLValue processUploadGetFile(CTelegramStream &stream, quint64 id);
    TLValue processUploadSaveFilePart(CTelegramStream &stream, quint64 id);
    TLValue processUsersGetUsers(CTelegramStream &stream, quint64 id);
    TLValue processUsersGetFullUser(CTelegramStream &stream, quint64 id);
    TLValue processMessagesSendMessage(CTelegramStream &stream, quint64 id);
    TLValue processMessagesSetTyping(CTelegramStream &stream, quint64 id);
    TLValue processMessagesReadHistory(CTelegramStream &stream, quint64 id);
    TLValue processMessagesReceivedMessages(CTelegramStream &stream, quint64 id);
    TLValue processMessagesGetHistory(CTelegramStream &stream, quint64 id);
    TLValue processMessagesGetChats(CTelegramStream &stream, quint64 id);
    TLValue processMessagesGetFullChat(CTelegramStream &stream, quint64 id);
    TLValue processAccountCheckUsername(CTelegramStream &stream, quint64 id);
    TLValue processAccountUpdateStatus(CTelegramStream &stream, quint64 id);
    TLValue processAccountUpdateUsername(CTelegramStream &stream, quint64 id);

    bool processErrorSeeOther(const QString errorMessage, quint64 id);

    TLValue processUpdate(CTelegramStream &stream, bool *ok);

    SAesKey generateTmpAesKey() const;
    SAesKey generateClientToServerAesKey(const QByteArray &messageKey) const;
    SAesKey generateServerToClientAesKey(const QByteArray &messageKey) const;

    SAesKey generateAesKey(const QByteArray &messageKey, int xValue) const;

    void insertInitConnection(QByteArray *data) const;

    quint64 sendPlainPackage(const QByteArray &buffer);
    quint64 sendEncryptedPackage(const QByteArray &buffer, bool savePackage = true);
    quint64 sendEncryptedPackageAgain(quint64 id);

    void setTransport(CTelegramTransport *newTransport);

    void setStatus(ConnectionStatus status, ConnectionStatusReason reason = ConnectionStatusReasonNone);
    void setAuthState(AuthState newState);

    quint64 newMessageId();

    QString userNameFromPackage(quint64 id) const;

    void startPingTimer();

    void addMessageToAck(quint64 id);

protected slots:
    void whenTransportStateChanged();
    void whenTransportReadyRead();
    void whenTransportTimeout();
    void whenItsTimeToPing();
    void whenItsTimeToAckMessages();

protected:
    ConnectionStatus m_status;
    const CAppInformation *m_appInfo;

    QMap<quint64, QByteArray> m_submittedPackages; // <message id, package data>
    QMap<quint64, quint32> m_requestedFilesIds; // <message id, file id>

    CTelegramTransport *m_transport;
    QTimer *m_pingTimer;
    QTimer *m_ackTimer;

    AuthState m_authState;

    QByteArray m_authKey;
    quint64 m_authId;
    quint64 m_authKeyAuxHash;
    quint64 m_serverSalt;
    quint64 m_receivedServerSalt;
    quint64 m_sessionId;
    quint64 m_lastMessageId;
    quint64 m_lastSentPingId;
    quint64 m_lastReceivedPingId;
    qint64 m_lastReceivedPingTime;
    qint64 m_lastSentPingTime;
    quint32 m_sequenceNumber;
    quint32 m_contentRelatedMessages;

    TLVector<quint64> m_messagesToAck;

    quint32 m_pingInterval;
    quint32 m_serverDisconnectionExtraTime;
    qint32 m_deltaTime;
    DeltaTimeHeuristicState m_deltaTimeHeuristicState;

    TLNumber128 m_clientNonce;
    TLNumber128 m_serverNonce;
    TLNumber256 m_newNonce;

    quint64 m_pq;
    quint32 m_p;
    quint32 m_q;

    quint64 m_serverPublicFingersprint;
    SRsaKey m_rsaKey;
    SAesKey m_tmpAesKey;

    quint32 m_g;
    QByteArray m_dhPrime;
    QByteArray m_gA;
    QByteArray m_b;

    quint64 m_authRetryId;

    TLDcOption m_dcInfo;

    QVector<TLDcOption> m_dcConfiguration;

    QString m_authCodeHash;

#ifdef NETWORK_LOGGING
    QFile *m_logFile;
#endif

};

inline SAesKey CTelegramConnection::generateClientToServerAesKey(const QByteArray &messageKey) const
{
    return generateAesKey(messageKey, 0);
}

inline SAesKey CTelegramConnection::generateServerToClientAesKey(const QByteArray &messageKey) const
{
    return generateAesKey(messageKey, 8);
}

#endif // CTELEGRAMCONNECTION_HPP
