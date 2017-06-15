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
#include <QNetworkProxy>
#include <QStringList>

#include "TelegramNamespace.hpp"
#include "TLTypes.hpp"
#include "TLNumbers.hpp"
#include "crypto-rsa.hpp"
#include "crypto-aes.hpp"

class CAppInformation;
class CTelegramStream;
class CTelegramTransport;
class RpcProcessingContext;

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

#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(ConnectionStatus)
    Q_ENUM(ConnectionStatusReason)
    Q_ENUM(AuthState)
    Q_ENUM(DeltaTimeHeuristicState)
#endif

    explicit CTelegramConnection(const CAppInformation *appInfo, QObject *parent = 0);

    void setProxy(const QNetworkProxy &proxy);
    void setDcInfo(const TLDcOption &newDcInfo);

    TLDcOption dcInfo() const { return m_dcInfo; }

public slots:
    void connectToDc();

public:
    ConnectionStatus status() const { return m_status; }

    static quint64 formatTimeStamp(qint64 timeInMs);
    static quint64 formatClientTimeStamp(qint64 timeInMs) { return formatTimeStamp(timeInMs) & ~quint64(3); }

    static quint64 timeStampToMSecsSinceEpoch(quint64 ts);

    void initAuth();
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
    quint64 accountReportPeer(const TLInputPeer &peer, const TLReportReason &reason);
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
    quint64 authImportBotAuthorization(quint32 flags, quint32 apiId, const QString &apiHash, const QString &botAuthToken);
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
    quint64 channelsCheckUsername(const TLInputChannel &channel, const QString &username);
    quint64 channelsCreateChannel(quint32 flags, const QString &title, const QString &about);
    quint64 channelsDeleteChannel(const TLInputChannel &channel);
    quint64 channelsDeleteMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    quint64 channelsDeleteUserHistory(const TLInputChannel &channel, const TLInputUser &userId);
    quint64 channelsEditAbout(const TLInputChannel &channel, const QString &about);
    quint64 channelsEditAdmin(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelParticipantRole &role);
    quint64 channelsEditPhoto(const TLInputChannel &channel, const TLInputChatPhoto &photo);
    quint64 channelsEditTitle(const TLInputChannel &channel, const QString &title);
    quint64 channelsExportInvite(const TLInputChannel &channel);
    quint64 channelsGetChannels(const TLVector<TLInputChannel> &id);
    quint64 channelsGetDialogs(quint32 offset, quint32 limit);
    quint64 channelsGetFullChannel(const TLInputChannel &channel);
    quint64 channelsGetImportantHistory(const TLInputChannel &channel, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    quint64 channelsGetMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    quint64 channelsGetParticipant(const TLInputChannel &channel, const TLInputUser &userId);
    quint64 channelsGetParticipants(const TLInputChannel &channel, const TLChannelParticipantsFilter &filter, quint32 offset, quint32 limit);
    quint64 channelsInviteToChannel(const TLInputChannel &channel, const TLVector<TLInputUser> &users);
    quint64 channelsJoinChannel(const TLInputChannel &channel);
    quint64 channelsKickFromChannel(const TLInputChannel &channel, const TLInputUser &userId, bool kicked);
    quint64 channelsLeaveChannel(const TLInputChannel &channel);
    quint64 channelsReadHistory(const TLInputChannel &channel, quint32 maxId);
    quint64 channelsReportSpam(const TLInputChannel &channel, const TLInputUser &userId, const TLVector<quint32> &id);
    quint64 channelsToggleComments(const TLInputChannel &channel, bool enabled);
    quint64 channelsUpdateUsername(const TLInputChannel &channel, const QString &username);
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
    quint64 helpGetAppChangelog(const QString &deviceModel, const QString &systemVersion, const QString &appVersion, const QString &langCode);
    quint64 helpGetAppUpdate(const QString &deviceModel, const QString &systemVersion, const QString &appVersion, const QString &langCode);
    quint64 helpGetConfig();
    quint64 helpGetInviteText(const QString &langCode);
    quint64 helpGetNearestDc();
    quint64 helpGetSupport();
    quint64 helpGetTermsOfService(const QString &langCode);
    quint64 helpSaveAppLog(const TLVector<TLInputAppEvent> &events);
    quint64 messagesAcceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint);
    quint64 messagesAddChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit);
    quint64 messagesCheckChatInvite(const QString &hash);
    quint64 messagesCreateChat(const TLVector<TLInputUser> &users, const QString &title);
    quint64 messagesDeleteChatUser(quint32 chatId, const TLInputUser &userId);
    quint64 messagesDeleteHistory(const TLInputPeer &peer, quint32 maxId);
    quint64 messagesDeleteMessages(const TLVector<quint32> &id);
    quint64 messagesDiscardEncryption(quint32 chatId);
    quint64 messagesEditChatAdmin(quint32 chatId, const TLInputUser &userId, bool isAdmin);
    quint64 messagesEditChatPhoto(quint32 chatId, const TLInputChatPhoto &photo);
    quint64 messagesEditChatTitle(quint32 chatId, const QString &title);
    quint64 messagesExportChatInvite(quint32 chatId);
    quint64 messagesForwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId);
    quint64 messagesForwardMessages(quint32 flags, const TLInputPeer &fromPeer, const TLVector<quint32> &id, const TLVector<quint64> &randomId, const TLInputPeer &toPeer);
    quint64 messagesGetAllStickers(quint32 hash);
    quint64 messagesGetChats(const TLVector<quint32> &id);
    quint64 messagesGetDhConfig(quint32 version, quint32 randomLength);
    quint64 messagesGetDialogs(quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit);
    quint64 messagesGetDocumentByHash(const QByteArray &sha256, quint32 size, const QString &mimeType);
    quint64 messagesGetFullChat(quint32 chatId);
    quint64 messagesGetHistory(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    quint64 messagesGetInlineBotResults(const TLInputUser &bot, const QString &query, const QString &offset);
    quint64 messagesGetMessages(const TLVector<quint32> &id);
    quint64 messagesGetMessagesViews(const TLInputPeer &peer, const TLVector<quint32> &id, bool increment);
    quint64 messagesGetSavedGifs(quint32 hash);
    quint64 messagesGetStickerSet(const TLInputStickerSet &stickerset);
    quint64 messagesGetStickers(const QString &emoticon, const QString &hash);
    quint64 messagesGetWebPagePreview(const QString &message);
    quint64 messagesImportChatInvite(const QString &hash);
    quint64 messagesInstallStickerSet(const TLInputStickerSet &stickerset, bool disabled);
    quint64 messagesMigrateChat(quint32 chatId);
    quint64 messagesReadEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate);
    quint64 messagesReadHistory(const TLInputPeer &peer, quint32 maxId);
    quint64 messagesReadMessageContents(const TLVector<quint32> &id);
    quint64 messagesReceivedMessages(quint32 maxId);
    quint64 messagesReceivedQueue(quint32 maxQts);
    quint64 messagesReorderStickerSets(const TLVector<quint64> &order);
    quint64 messagesReportSpam(const TLInputPeer &peer);
    quint64 messagesRequestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA);
    quint64 messagesSaveGif(const TLInputDocument &id, bool unsave);
    quint64 messagesSearch(quint32 flags, const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit);
    quint64 messagesSearchGifs(const QString &q, quint32 offset);
    quint64 messagesSearchGlobal(const QString &q, quint32 offsetDate, const TLInputPeer &offsetPeer, quint32 offsetId, quint32 limit);
    quint64 messagesSendBroadcast(const TLVector<TLInputUser> &contacts, const TLVector<quint64> &randomId, const QString &message, const TLInputMedia &media);
    quint64 messagesSendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    quint64 messagesSendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file);
    quint64 messagesSendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    quint64 messagesSendInlineBotResult(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId, quint64 queryId, const QString &id);
    quint64 messagesSendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId, const TLReplyMarkup &replyMarkup);
    quint64 messagesSendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities);
    quint64 messagesSetEncryptedTyping(const TLInputEncryptedChat &peer, bool typing);
    quint64 messagesSetInlineBotResults(quint32 flags, quint64 queryId, const TLVector<TLInputBotInlineResult> &results, quint32 cacheTime, const QString &nextOffset);
    quint64 messagesSetTyping(const TLInputPeer &peer, const TLSendMessageAction &action);
    quint64 messagesStartBot(const TLInputUser &bot, const TLInputPeer &peer, quint64 randomId, const QString &startParam);
    quint64 messagesToggleChatAdmins(quint32 chatId, bool enabled);
    quint64 messagesUninstallStickerSet(const TLInputStickerSet &stickerset);
    quint64 updatesGetChannelDifference(const TLInputChannel &channel, const TLChannelMessagesFilter &filter, quint32 pts, quint32 limit);
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

    quint64 sendMessage(const TLInputPeer &peer, const QString &message, quint64 randomMessageId);
    quint64 sendMedia(const TLInputPeer &peer, const TLInputMedia &media, quint64 randomMessageId);

    AuthState authState() { return m_authState; }

    void requestPqAuthorization();
    bool answerPqAuthorization(const QByteArray &payload);
    void requestDhParameters();
    bool answerDh(const QByteArray &payload);
    void requestDhGenerationResult();
    bool processServersDHAnswer(const QByteArray &payload);

    TLNumber128 clientNonce() const { return m_clientNonce; }
    TLNumber128 serverNonce() const { return m_serverNonce; }

    quint64 pq() const { return m_pq; }
    quint64 p() const { return m_p; }
    quint64 q() const { return m_q; }

    quint64 serverPublicFingersprint() const { return m_serverPublicFingersprint; }

    QByteArray authKey() const { return m_authKey; }
    void setAuthKey(const QByteArray &newAuthKey);
    quint64 authId() const { return m_authId; }

    quint64 serverSalt() const { return m_serverSalt; }
    void setServerSalt(const quint64 salt) { m_serverSalt = salt; }
    quint64 sessionId() const { return m_sessionId; }

    QVector<TLDcOption> dcConfiguration() const { return m_dcConfiguration; }

    qint32 deltaTime() const { return m_deltaTime; }
    void setDeltaTime(const qint32 newDt);

    void processRedirectedPackage(const QByteArray &data);

signals:
    void wantedMainDcChanged(quint32 dc, QString dcForPhoneNumber);
    void newRedirectedPackage(const QByteArray &data, quint32 dc);

    void statusChanged(int status, int reason, quint32 dc);
    void authStateChanged(int status, quint32 dc);
    void actualDcIdReceived(quint32 dc, quint32 newDcId);
    void dcConfigurationReceived(quint32 dc);
    void phoneStatusReceived(const QString &phone, bool registered);
    void passwordReceived(const TLAccountPassword &password, quint64 requestId);
    void phoneCodeRequired();
    void loggedOut(bool result);
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);
    void userNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status);
    void usersReceived(const QVector<TLUser> &users);
    void selfUserReceived(const TLUser &selfUser);
    void contactListReceived(const QVector<quint32> &contactList);
    void contactListChanged(const QVector<quint32> &added, const QVector<quint32> &removed);
    void fileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset);
    void fileDataSent(quint32 requestId);

    void messagesChatsReceived(const QVector<TLChat> &chats);
    void messagesFullChatReceived(const TLChatFull &chat, const QVector<TLChat> &chats, const QVector<TLUser> &users);
    void channelsParticipantsReceived(quint32 channelId, const TLVector<TLChannelParticipant> &participants);

    void fullUserReceived(const TLUserFull &userFull);
    void messagesHistoryReceived(const TLMessagesMessages &history, const TLInputPeer &peer);
    void messagesDialogsReceived(const TLMessagesDialogs &dialogs, quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit);
    void channelsDialogsReceived(const TLMessagesDialogs &dialogs, quint32 offsetId, quint32 limit);
    void messagesAffectedMessagesReceived(const TLMessagesAffectedMessages &affectedMessages);

    void updatesReceived(const TLUpdates &update, quint64 id);
    void updatesStateReceived(const TLUpdatesState &updatesState);
    void updatesChannelDifferenceReceived(const TLUpdatesChannelDifference &channelDifference);
    void updatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

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

    // Generated Telegram API RPC process declarations
    void processAccountChangePhone(RpcProcessingContext *context);
    void processAccountCheckUsername(RpcProcessingContext *context);
    void processAccountDeleteAccount(RpcProcessingContext *context);
    void processAccountGetAccountTTL(RpcProcessingContext *context);
    void processAccountGetAuthorizations(RpcProcessingContext *context);
    void processAccountGetNotifySettings(RpcProcessingContext *context);
    void processAccountGetPassword(RpcProcessingContext *context);
    void processAccountGetPasswordSettings(RpcProcessingContext *context);
    void processAccountGetPrivacy(RpcProcessingContext *context);
    void processAccountGetWallPapers(RpcProcessingContext *context);
    void processAccountRegisterDevice(RpcProcessingContext *context);
    void processAccountReportPeer(RpcProcessingContext *context);
    void processAccountResetAuthorization(RpcProcessingContext *context);
    void processAccountResetNotifySettings(RpcProcessingContext *context);
    void processAccountSendChangePhoneCode(RpcProcessingContext *context);
    void processAccountSetAccountTTL(RpcProcessingContext *context);
    void processAccountSetPrivacy(RpcProcessingContext *context);
    void processAccountUnregisterDevice(RpcProcessingContext *context);
    void processAccountUpdateDeviceLocked(RpcProcessingContext *context);
    void processAccountUpdateNotifySettings(RpcProcessingContext *context);
    void processAccountUpdatePasswordSettings(RpcProcessingContext *context);
    void processAccountUpdateProfile(RpcProcessingContext *context);
    void processAccountUpdateStatus(RpcProcessingContext *context);
    void processAccountUpdateUsername(RpcProcessingContext *context);
    void processAuthBindTempAuthKey(RpcProcessingContext *context);
    void processAuthCheckPassword(RpcProcessingContext *context);
    void processAuthCheckPhone(RpcProcessingContext *context);
    void processAuthExportAuthorization(RpcProcessingContext *context);
    void processAuthImportAuthorization(RpcProcessingContext *context);
    void processAuthImportBotAuthorization(RpcProcessingContext *context);
    void processAuthLogOut(RpcProcessingContext *context);
    void processAuthRecoverPassword(RpcProcessingContext *context);
    void processAuthRequestPasswordRecovery(RpcProcessingContext *context);
    void processAuthResetAuthorizations(RpcProcessingContext *context);
    void processAuthSendCall(RpcProcessingContext *context);
    void processAuthSendCode(RpcProcessingContext *context);
    void processAuthSendInvites(RpcProcessingContext *context);
    void processAuthSendSms(RpcProcessingContext *context);
    void processAuthSignIn(RpcProcessingContext *context);
    void processAuthSignUp(RpcProcessingContext *context);
    void processChannelsCheckUsername(RpcProcessingContext *context);
    void processChannelsDeleteMessages(RpcProcessingContext *context);
    void processChannelsDeleteUserHistory(RpcProcessingContext *context);
    void processChannelsEditAbout(RpcProcessingContext *context);
    void processChannelsExportInvite(RpcProcessingContext *context);
    void processChannelsGetChannels(RpcProcessingContext *context);
    void processChannelsGetDialogs(RpcProcessingContext *context);
    void processChannelsGetFullChannel(RpcProcessingContext *context);
    void processChannelsGetImportantHistory(RpcProcessingContext *context);
    void processChannelsGetMessages(RpcProcessingContext *context);
    void processChannelsGetParticipant(RpcProcessingContext *context);
    void processChannelsGetParticipants(RpcProcessingContext *context);
    void processChannelsReadHistory(RpcProcessingContext *context);
    void processChannelsReportSpam(RpcProcessingContext *context);
    void processChannelsUpdateUsername(RpcProcessingContext *context);
    void processContactsBlock(RpcProcessingContext *context);
    void processContactsDeleteContact(RpcProcessingContext *context);
    void processContactsDeleteContacts(RpcProcessingContext *context);
    void processContactsExportCard(RpcProcessingContext *context);
    void processContactsGetBlocked(RpcProcessingContext *context);
    void processContactsGetContacts(RpcProcessingContext *context);
    void processContactsGetStatuses(RpcProcessingContext *context);
    void processContactsGetSuggested(RpcProcessingContext *context);
    void processContactsImportCard(RpcProcessingContext *context);
    void processContactsImportContacts(RpcProcessingContext *context);
    void processContactsResolveUsername(RpcProcessingContext *context);
    void processContactsSearch(RpcProcessingContext *context);
    void processContactsUnblock(RpcProcessingContext *context);
    void processHelpGetAppChangelog(RpcProcessingContext *context);
    void processHelpGetAppUpdate(RpcProcessingContext *context);
    void processHelpGetConfig(RpcProcessingContext *context);
    void processHelpGetInviteText(RpcProcessingContext *context);
    void processHelpGetNearestDc(RpcProcessingContext *context);
    void processHelpGetSupport(RpcProcessingContext *context);
    void processHelpGetTermsOfService(RpcProcessingContext *context);
    void processHelpSaveAppLog(RpcProcessingContext *context);
    void processMessagesAcceptEncryption(RpcProcessingContext *context);
    void processMessagesCheckChatInvite(RpcProcessingContext *context);
    void processMessagesDeleteHistory(RpcProcessingContext *context);
    void processMessagesDeleteMessages(RpcProcessingContext *context);
    void processMessagesDiscardEncryption(RpcProcessingContext *context);
    void processMessagesEditChatAdmin(RpcProcessingContext *context);
    void processMessagesExportChatInvite(RpcProcessingContext *context);
    void processMessagesGetAllStickers(RpcProcessingContext *context);
    void processMessagesGetChats(RpcProcessingContext *context);
    void processMessagesGetDhConfig(RpcProcessingContext *context);
    void processMessagesGetDialogs(RpcProcessingContext *context);
    void processMessagesGetDocumentByHash(RpcProcessingContext *context);
    void processMessagesGetFullChat(RpcProcessingContext *context);
    void processMessagesGetHistory(RpcProcessingContext *context);
    void processMessagesGetInlineBotResults(RpcProcessingContext *context);
    void processMessagesGetMessages(RpcProcessingContext *context);
    void processMessagesGetMessagesViews(RpcProcessingContext *context);
    void processMessagesGetSavedGifs(RpcProcessingContext *context);
    void processMessagesGetStickerSet(RpcProcessingContext *context);
    void processMessagesGetStickers(RpcProcessingContext *context);
    void processMessagesGetWebPagePreview(RpcProcessingContext *context);
    void processMessagesInstallStickerSet(RpcProcessingContext *context);
    void processMessagesReadEncryptedHistory(RpcProcessingContext *context);
    void processMessagesReadHistory(RpcProcessingContext *context);
    void processMessagesReadMessageContents(RpcProcessingContext *context);
    void processMessagesReceivedMessages(RpcProcessingContext *context);
    void processMessagesReceivedQueue(RpcProcessingContext *context);
    void processMessagesReorderStickerSets(RpcProcessingContext *context);
    void processMessagesReportSpam(RpcProcessingContext *context);
    void processMessagesRequestEncryption(RpcProcessingContext *context);
    void processMessagesSaveGif(RpcProcessingContext *context);
    void processMessagesSearch(RpcProcessingContext *context);
    void processMessagesSearchGifs(RpcProcessingContext *context);
    void processMessagesSearchGlobal(RpcProcessingContext *context);
    void processMessagesSendEncrypted(RpcProcessingContext *context);
    void processMessagesSendEncryptedFile(RpcProcessingContext *context);
    void processMessagesSendEncryptedService(RpcProcessingContext *context);
    void processMessagesSetEncryptedTyping(RpcProcessingContext *context);
    void processMessagesSetInlineBotResults(RpcProcessingContext *context);
    void processMessagesSetTyping(RpcProcessingContext *context);
    void processMessagesUninstallStickerSet(RpcProcessingContext *context);
    void processUpdatesGetChannelDifference(RpcProcessingContext *context);
    void processUpdatesGetDifference(RpcProcessingContext *context);
    void processUpdatesGetState(RpcProcessingContext *context);
    void processUploadGetFile(RpcProcessingContext *context);
    void processUploadSaveBigFilePart(RpcProcessingContext *context);
    void processUploadSaveFilePart(RpcProcessingContext *context);
    void processUsersGetFullUser(RpcProcessingContext *context);
    void processUsersGetUsers(RpcProcessingContext *context);
    // End of generated Telegram API RPC process declarations

    void processAuthSign(RpcProcessingContext *context);
    bool processErrorSeeOther(const QString errorMessage, quint64 id);

    TLValue processUpdate(CTelegramStream &stream, bool *ok, quint64 id);

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

    void startAuthTimer();
    void stopAuthTimer();

    void startPingTimer();
    void stopPingTimer();

    void addMessageToAck(quint64 id);

protected slots:
    void onTransportStateChanged();
    void onTransportReadyRead();
    void onTransportTimeout();
    void onTimeToPing();
    void onTimeToAckMessages();

protected:
    ConnectionStatus m_status;
    const CAppInformation *m_appInfo;

    QMap<quint64, QByteArray> m_submittedPackages; // <message id, package data>
    QMap<quint64, quint32> m_requestedFilesIds; // <message id, file id>

    CTelegramTransport *m_transport;
    QTimer *m_authTimer;
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

    QNetworkProxy m_proxy;
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
