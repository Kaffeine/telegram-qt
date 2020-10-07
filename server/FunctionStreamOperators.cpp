/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "FunctionStreamOperators.hpp"
#include "MTProto/Stream_p.hpp"
#include "MTProto/StreamExtraOperators.hpp"

namespace Telegram {

namespace MTProto {

// TODO: Generate templates instancing
template Stream &Stream::operator>>(TLVector<TLAuthorization> &v);
template Stream &Stream::operator>>(TLVector<TLPrivacyRule> &v);
template Stream &Stream::operator>>(TLVector<TLUser> &v);
template Stream &Stream::operator>>(TLVector<TLWallPaper> &v);
template Stream &Stream::operator>>(TLVector<TLContactBlocked> &v);
template Stream &Stream::operator>>(TLVector<TLContact> &v);
template Stream &Stream::operator>>(TLVector<TLContactStatus> &v);
template Stream &Stream::operator>>(TLVector<TLImportedContact> &v);
template Stream &Stream::operator>>(TLVector<TLChat> &v);
template Stream &Stream::operator>>(TLVector<TLPeer> &v);
template Stream &Stream::operator>>(TLVector<TLDcOption> &v);
template Stream &Stream::operator>>(TLVector<TLMessageEntity> &v);
template Stream &Stream::operator>>(TLVector<TLUpdate> &v);
template Stream &Stream::operator>>(TLVector<TLStickerSet> &v);
template Stream &Stream::operator>>(TLVector<TLDialog> &v);
template Stream &Stream::operator>>(TLVector<TLMessage> &v);
template Stream &Stream::operator>>(TLVector<TLDocumentAttribute> &v);
template Stream &Stream::operator>>(TLVector<TLBotInlineResult> &v);
template Stream &Stream::operator>>(TLVector<TLDocument> &v);
template Stream &Stream::operator>>(TLVector<TLStickerPack> &v);
template Stream &Stream::operator>>(TLVector<TLReceivedNotifyMessage> &v);
template Stream &Stream::operator>>(TLVector<TLFoundGif> &v);
template Stream &Stream::operator>>(TLVector<TLEncryptedMessage> &v);
template Stream &Stream::operator>>(TLVector<TLBotCommand> &v);
template Stream &Stream::operator>>(TLVector<TLChatParticipant> &v);
template Stream &Stream::operator>>(TLVector<TLKeyboardButton> &v);
template Stream &Stream::operator>>(TLVector<TLPhotoSize> &v);
template Stream &Stream::operator>>(TLVector<TLMessageRange> &v);
template Stream &Stream::operator>>(TLVector<TLInputUser> &v);
template Stream &Stream::operator>>(TLVector<TLKeyboardButtonRow> &v);
template Stream &Stream::operator>>(TLVector<TLChannelParticipant> &v);
template Stream &Stream::operator>>(TLVector<TLBotInfo> &v);
template Stream &Stream::operator>>(TLVector<TLPhoto> &v);
template Stream &Stream::operator>>(TLVector<TLInputPrivacyRule> &v);
template Stream &Stream::operator>>(TLVector<TLInputChannel> &v);
template Stream &Stream::operator>>(TLVector<TLInputContact> &v);
template Stream &Stream::operator>>(TLVector<TLInputAppEvent> &v);
template Stream &Stream::operator>>(TLVector<TLInputBotInlineResult> &v);
template Stream &Stream::operator>>(TLVector<TLInputPhoto> &v);

template Stream &Stream::operator<<(const TLVector<TLContactStatus> &v);
template Stream &Stream::operator<<(const TLVector<TLReceivedNotifyMessage> &v);
template Stream &Stream::operator<<(const TLVector<TLLangPackLanguage> &v);
template Stream &Stream::operator<<(const TLVector<TLWallPaper> &v);

Stream &operator>>(Stream &stream, Functions::TLPing &ping)
{
    // stream >> function.tlType;
    stream >> ping.tlType;
    switch (ping.tlType) {
    case Functions::TLPing::predicate:
        stream >> ping.pingId;
        break;
    case Functions::TLPing::predicateDisconnect:
        stream >> ping.pingId;
        stream >> ping.disconnectDelay;
        break;
    default:
        break;
    }
    return stream;
}

// Generated write operators
Stream &operator>>(Stream &stream, Functions::TLAccountAcceptAuthorization &accountAcceptAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> accountAcceptAuthorizationFunction.botId;
    stream >> accountAcceptAuthorizationFunction.scope;
    stream >> accountAcceptAuthorizationFunction.publicKey;
    stream >> accountAcceptAuthorizationFunction.valueHashes;
    stream >> accountAcceptAuthorizationFunction.credentials;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountCancelPasswordEmail &accountCancelPasswordEmailFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountCancelPasswordEmailFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountChangePhone &accountChangePhoneFunction)
{
    // stream >> function.tlType;
    stream >> accountChangePhoneFunction.phoneNumber;
    stream >> accountChangePhoneFunction.phoneCodeHash;
    stream >> accountChangePhoneFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountCheckUsername &accountCheckUsernameFunction)
{
    // stream >> function.tlType;
    stream >> accountCheckUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountConfirmPasswordEmail &accountConfirmPasswordEmailFunction)
{
    // stream >> function.tlType;
    stream >> accountConfirmPasswordEmailFunction.code;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountConfirmPhone &accountConfirmPhoneFunction)
{
    // stream >> function.tlType;
    stream >> accountConfirmPhoneFunction.phoneCodeHash;
    stream >> accountConfirmPhoneFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountDeleteAccount &accountDeleteAccountFunction)
{
    // stream >> function.tlType;
    stream >> accountDeleteAccountFunction.reason;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountDeleteSecureValue &accountDeleteSecureValueFunction)
{
    // stream >> function.tlType;
    stream >> accountDeleteSecureValueFunction.types;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountFinishTakeoutSession &accountFinishTakeoutSessionFunction)
{
    // stream >> function.tlType;
    stream >> accountFinishTakeoutSessionFunction.flags;
    // (accountFinishTakeoutSessionFunction.flags & 1 << 0) stands for success "true" value
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetAccountTTL &accountGetAccountTTLFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetAccountTTLFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetAllSecureValues &accountGetAllSecureValuesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetAllSecureValuesFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetAuthorizationForm &accountGetAuthorizationFormFunction)
{
    // stream >> function.tlType;
    stream >> accountGetAuthorizationFormFunction.botId;
    stream >> accountGetAuthorizationFormFunction.scope;
    stream >> accountGetAuthorizationFormFunction.publicKey;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetAuthorizations &accountGetAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetAuthorizationsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetContactSignUpNotification &accountGetContactSignUpNotificationFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetContactSignUpNotificationFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetNotifyExceptions &accountGetNotifyExceptionsFunction)
{
    // stream >> function.tlType;
    stream >> accountGetNotifyExceptionsFunction.flags;
    // (accountGetNotifyExceptionsFunction.flags & 1 << 1) stands for compareSound "true" value
    if (accountGetNotifyExceptionsFunction.flags & 1 << 0) {
        stream >> accountGetNotifyExceptionsFunction.peer;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetNotifySettings &accountGetNotifySettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountGetNotifySettingsFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetPassword &accountGetPasswordFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetPasswordFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetPasswordSettings &accountGetPasswordSettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountGetPasswordSettingsFunction.password;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetPrivacy &accountGetPrivacyFunction)
{
    // stream >> function.tlType;
    stream >> accountGetPrivacyFunction.key;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetSecureValue &accountGetSecureValueFunction)
{
    // stream >> function.tlType;
    stream >> accountGetSecureValueFunction.types;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetTmpPassword &accountGetTmpPasswordFunction)
{
    // stream >> function.tlType;
    stream >> accountGetTmpPasswordFunction.password;
    stream >> accountGetTmpPasswordFunction.period;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetWallPapers &accountGetWallPapersFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetWallPapersFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountGetWebAuthorizations &accountGetWebAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetWebAuthorizationsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountInitTakeoutSession &accountInitTakeoutSessionFunction)
{
    // stream >> function.tlType;
    stream >> accountInitTakeoutSessionFunction.flags;
    // (accountInitTakeoutSessionFunction.flags & 1 << 0) stands for contacts "true" value
    // (accountInitTakeoutSessionFunction.flags & 1 << 1) stands for messageUsers "true" value
    // (accountInitTakeoutSessionFunction.flags & 1 << 2) stands for messageChats "true" value
    // (accountInitTakeoutSessionFunction.flags & 1 << 3) stands for messageMegagroups "true" value
    // (accountInitTakeoutSessionFunction.flags & 1 << 4) stands for messageChannels "true" value
    // (accountInitTakeoutSessionFunction.flags & 1 << 5) stands for files "true" value
    if (accountInitTakeoutSessionFunction.flags & 1 << 5) {
        stream >> accountInitTakeoutSessionFunction.fileMaxSize;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountRegisterDevice &accountRegisterDeviceFunction)
{
    // stream >> function.tlType;
    stream >> accountRegisterDeviceFunction.tokenType;
    stream >> accountRegisterDeviceFunction.token;
    stream >> accountRegisterDeviceFunction.appSandbox;
    stream >> accountRegisterDeviceFunction.secret;
    stream >> accountRegisterDeviceFunction.otherUids;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountReportPeer &accountReportPeerFunction)
{
    // stream >> function.tlType;
    stream >> accountReportPeerFunction.peer;
    stream >> accountReportPeerFunction.reason;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountResendPasswordEmail &accountResendPasswordEmailFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountResendPasswordEmailFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountResetAuthorization &accountResetAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> accountResetAuthorizationFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountResetNotifySettings &accountResetNotifySettingsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountResetNotifySettingsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountResetWebAuthorization &accountResetWebAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> accountResetWebAuthorizationFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountResetWebAuthorizations &accountResetWebAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountResetWebAuthorizationsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSaveSecureValue &accountSaveSecureValueFunction)
{
    // stream >> function.tlType;
    stream >> accountSaveSecureValueFunction.value;
    stream >> accountSaveSecureValueFunction.secureSecretId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSendChangePhoneCode &accountSendChangePhoneCodeFunction)
{
    // stream >> function.tlType;
    stream >> accountSendChangePhoneCodeFunction.flags;
    // (accountSendChangePhoneCodeFunction.flags & 1 << 0) stands for allowFlashcall "true" value
    stream >> accountSendChangePhoneCodeFunction.phoneNumber;
    if (accountSendChangePhoneCodeFunction.flags & 1 << 0) {
        stream >> accountSendChangePhoneCodeFunction.currentNumber;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSendConfirmPhoneCode &accountSendConfirmPhoneCodeFunction)
{
    // stream >> function.tlType;
    stream >> accountSendConfirmPhoneCodeFunction.flags;
    // (accountSendConfirmPhoneCodeFunction.flags & 1 << 0) stands for allowFlashcall "true" value
    stream >> accountSendConfirmPhoneCodeFunction.hash;
    if (accountSendConfirmPhoneCodeFunction.flags & 1 << 0) {
        stream >> accountSendConfirmPhoneCodeFunction.currentNumber;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSendVerifyEmailCode &accountSendVerifyEmailCodeFunction)
{
    // stream >> function.tlType;
    stream >> accountSendVerifyEmailCodeFunction.email;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSendVerifyPhoneCode &accountSendVerifyPhoneCodeFunction)
{
    // stream >> function.tlType;
    stream >> accountSendVerifyPhoneCodeFunction.flags;
    // (accountSendVerifyPhoneCodeFunction.flags & 1 << 0) stands for allowFlashcall "true" value
    stream >> accountSendVerifyPhoneCodeFunction.phoneNumber;
    if (accountSendVerifyPhoneCodeFunction.flags & 1 << 0) {
        stream >> accountSendVerifyPhoneCodeFunction.currentNumber;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSetAccountTTL &accountSetAccountTTLFunction)
{
    // stream >> function.tlType;
    stream >> accountSetAccountTTLFunction.ttl;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSetContactSignUpNotification &accountSetContactSignUpNotificationFunction)
{
    // stream >> function.tlType;
    stream >> accountSetContactSignUpNotificationFunction.silent;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountSetPrivacy &accountSetPrivacyFunction)
{
    // stream >> function.tlType;
    stream >> accountSetPrivacyFunction.key;
    stream >> accountSetPrivacyFunction.rules;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUnregisterDevice &accountUnregisterDeviceFunction)
{
    // stream >> function.tlType;
    stream >> accountUnregisterDeviceFunction.tokenType;
    stream >> accountUnregisterDeviceFunction.token;
    stream >> accountUnregisterDeviceFunction.otherUids;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUpdateDeviceLocked &accountUpdateDeviceLockedFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateDeviceLockedFunction.period;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUpdateNotifySettings &accountUpdateNotifySettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateNotifySettingsFunction.peer;
    stream >> accountUpdateNotifySettingsFunction.settings;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUpdatePasswordSettings &accountUpdatePasswordSettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdatePasswordSettingsFunction.password;
    stream >> accountUpdatePasswordSettingsFunction.newSettings;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUpdateProfile &accountUpdateProfileFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateProfileFunction.flags;
    if (accountUpdateProfileFunction.flags & 1 << 0) {
        stream >> accountUpdateProfileFunction.firstName;
    }
    if (accountUpdateProfileFunction.flags & 1 << 1) {
        stream >> accountUpdateProfileFunction.lastName;
    }
    if (accountUpdateProfileFunction.flags & 1 << 2) {
        stream >> accountUpdateProfileFunction.about;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUpdateStatus &accountUpdateStatusFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateStatusFunction.offline;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountUpdateUsername &accountUpdateUsernameFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountVerifyEmail &accountVerifyEmailFunction)
{
    // stream >> function.tlType;
    stream >> accountVerifyEmailFunction.email;
    stream >> accountVerifyEmailFunction.code;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAccountVerifyPhone &accountVerifyPhoneFunction)
{
    // stream >> function.tlType;
    stream >> accountVerifyPhoneFunction.phoneNumber;
    stream >> accountVerifyPhoneFunction.phoneCodeHash;
    stream >> accountVerifyPhoneFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthBindTempAuthKey &authBindTempAuthKeyFunction)
{
    // stream >> function.tlType;
    stream >> authBindTempAuthKeyFunction.permAuthKeyId;
    stream >> authBindTempAuthKeyFunction.nonce;
    stream >> authBindTempAuthKeyFunction.expiresAt;
    stream >> authBindTempAuthKeyFunction.encryptedMessage;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthCancelCode &authCancelCodeFunction)
{
    // stream >> function.tlType;
    stream >> authCancelCodeFunction.phoneNumber;
    stream >> authCancelCodeFunction.phoneCodeHash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthCheckPassword &authCheckPasswordFunction)
{
    // stream >> function.tlType;
    stream >> authCheckPasswordFunction.password;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthDropTempAuthKeys &authDropTempAuthKeysFunction)
{
    // stream >> function.tlType;
    stream >> authDropTempAuthKeysFunction.exceptAuthKeys;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthExportAuthorization &authExportAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> authExportAuthorizationFunction.dcId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthImportAuthorization &authImportAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> authImportAuthorizationFunction.id;
    stream >> authImportAuthorizationFunction.bytes;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthImportBotAuthorization &authImportBotAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> authImportBotAuthorizationFunction.flags;
    stream >> authImportBotAuthorizationFunction.apiId;
    stream >> authImportBotAuthorizationFunction.apiHash;
    stream >> authImportBotAuthorizationFunction.botAuthToken;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthLogOut &authLogOutFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(authLogOutFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthRecoverPassword &authRecoverPasswordFunction)
{
    // stream >> function.tlType;
    stream >> authRecoverPasswordFunction.code;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthRequestPasswordRecovery &authRequestPasswordRecoveryFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(authRequestPasswordRecoveryFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthResendCode &authResendCodeFunction)
{
    // stream >> function.tlType;
    stream >> authResendCodeFunction.phoneNumber;
    stream >> authResendCodeFunction.phoneCodeHash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthResetAuthorizations &authResetAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(authResetAuthorizationsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthSendCode &authSendCodeFunction)
{
    // stream >> function.tlType;
    stream >> authSendCodeFunction.flags;
    // (authSendCodeFunction.flags & 1 << 0) stands for allowFlashcall "true" value
    stream >> authSendCodeFunction.phoneNumber;
    if (authSendCodeFunction.flags & 1 << 0) {
        stream >> authSendCodeFunction.currentNumber;
    }
    stream >> authSendCodeFunction.apiId;
    stream >> authSendCodeFunction.apiHash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthSignIn &authSignInFunction)
{
    // stream >> function.tlType;
    stream >> authSignInFunction.phoneNumber;
    stream >> authSignInFunction.phoneCodeHash;
    stream >> authSignInFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLAuthSignUp &authSignUpFunction)
{
    // stream >> function.tlType;
    stream >> authSignUpFunction.phoneNumber;
    stream >> authSignUpFunction.phoneCodeHash;
    stream >> authSignUpFunction.phoneCode;
    stream >> authSignUpFunction.firstName;
    stream >> authSignUpFunction.lastName;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLBotsAnswerWebhookJSONQuery &botsAnswerWebhookJSONQueryFunction)
{
    // stream >> function.tlType;
    stream >> botsAnswerWebhookJSONQueryFunction.queryId;
    stream >> botsAnswerWebhookJSONQueryFunction.data;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLBotsSendCustomRequest &botsSendCustomRequestFunction)
{
    // stream >> function.tlType;
    stream >> botsSendCustomRequestFunction.customMethod;
    stream >> botsSendCustomRequestFunction.params;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsCheckUsername &channelsCheckUsernameFunction)
{
    // stream >> function.tlType;
    stream >> channelsCheckUsernameFunction.channel;
    stream >> channelsCheckUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsCreateChannel &channelsCreateChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsCreateChannelFunction.flags;
    // (channelsCreateChannelFunction.flags & 1 << 0) stands for broadcast "true" value
    // (channelsCreateChannelFunction.flags & 1 << 1) stands for megagroup "true" value
    stream >> channelsCreateChannelFunction.title;
    stream >> channelsCreateChannelFunction.about;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsDeleteChannel &channelsDeleteChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsDeleteHistory &channelsDeleteHistoryFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteHistoryFunction.channel;
    stream >> channelsDeleteHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsDeleteMessages &channelsDeleteMessagesFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteMessagesFunction.channel;
    stream >> channelsDeleteMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsDeleteUserHistory &channelsDeleteUserHistoryFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteUserHistoryFunction.channel;
    stream >> channelsDeleteUserHistoryFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsEditAbout &channelsEditAboutFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditAboutFunction.channel;
    stream >> channelsEditAboutFunction.about;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsEditAdmin &channelsEditAdminFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditAdminFunction.channel;
    stream >> channelsEditAdminFunction.userId;
    stream >> channelsEditAdminFunction.adminRights;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsEditBanned &channelsEditBannedFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditBannedFunction.channel;
    stream >> channelsEditBannedFunction.userId;
    stream >> channelsEditBannedFunction.bannedRights;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsEditPhoto &channelsEditPhotoFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditPhotoFunction.channel;
    stream >> channelsEditPhotoFunction.photo;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsEditTitle &channelsEditTitleFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditTitleFunction.channel;
    stream >> channelsEditTitleFunction.title;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsExportInvite &channelsExportInviteFunction)
{
    // stream >> function.tlType;
    stream >> channelsExportInviteFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsExportMessageLink &channelsExportMessageLinkFunction)
{
    // stream >> function.tlType;
    stream >> channelsExportMessageLinkFunction.channel;
    stream >> channelsExportMessageLinkFunction.id;
    stream >> channelsExportMessageLinkFunction.grouped;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetAdminLog &channelsGetAdminLogFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetAdminLogFunction.flags;
    stream >> channelsGetAdminLogFunction.channel;
    stream >> channelsGetAdminLogFunction.q;
    if (channelsGetAdminLogFunction.flags & 1 << 0) {
        stream >> channelsGetAdminLogFunction.eventsFilter;
    }
    if (channelsGetAdminLogFunction.flags & 1 << 1) {
        stream >> channelsGetAdminLogFunction.admins;
    }
    stream >> channelsGetAdminLogFunction.maxId;
    stream >> channelsGetAdminLogFunction.minId;
    stream >> channelsGetAdminLogFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetAdminedPublicChannels &channelsGetAdminedPublicChannelsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(channelsGetAdminedPublicChannelsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetChannels &channelsGetChannelsFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetChannelsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetFullChannel &channelsGetFullChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetFullChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetLeftChannels &channelsGetLeftChannelsFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetLeftChannelsFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetMessages &channelsGetMessagesFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetMessagesFunction.channel;
    stream >> channelsGetMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetParticipant &channelsGetParticipantFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetParticipantFunction.channel;
    stream >> channelsGetParticipantFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsGetParticipants &channelsGetParticipantsFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetParticipantsFunction.channel;
    stream >> channelsGetParticipantsFunction.filter;
    stream >> channelsGetParticipantsFunction.offset;
    stream >> channelsGetParticipantsFunction.limit;
    stream >> channelsGetParticipantsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsInviteToChannel &channelsInviteToChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsInviteToChannelFunction.channel;
    stream >> channelsInviteToChannelFunction.users;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsJoinChannel &channelsJoinChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsJoinChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsLeaveChannel &channelsLeaveChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsLeaveChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsReadHistory &channelsReadHistoryFunction)
{
    // stream >> function.tlType;
    stream >> channelsReadHistoryFunction.channel;
    stream >> channelsReadHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsReadMessageContents &channelsReadMessageContentsFunction)
{
    // stream >> function.tlType;
    stream >> channelsReadMessageContentsFunction.channel;
    stream >> channelsReadMessageContentsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsReportSpam &channelsReportSpamFunction)
{
    // stream >> function.tlType;
    stream >> channelsReportSpamFunction.channel;
    stream >> channelsReportSpamFunction.userId;
    stream >> channelsReportSpamFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsSetStickers &channelsSetStickersFunction)
{
    // stream >> function.tlType;
    stream >> channelsSetStickersFunction.channel;
    stream >> channelsSetStickersFunction.stickerset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsToggleInvites &channelsToggleInvitesFunction)
{
    // stream >> function.tlType;
    stream >> channelsToggleInvitesFunction.channel;
    stream >> channelsToggleInvitesFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsTogglePreHistoryHidden &channelsTogglePreHistoryHiddenFunction)
{
    // stream >> function.tlType;
    stream >> channelsTogglePreHistoryHiddenFunction.channel;
    stream >> channelsTogglePreHistoryHiddenFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsToggleSignatures &channelsToggleSignaturesFunction)
{
    // stream >> function.tlType;
    stream >> channelsToggleSignaturesFunction.channel;
    stream >> channelsToggleSignaturesFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLChannelsUpdateUsername &channelsUpdateUsernameFunction)
{
    // stream >> function.tlType;
    stream >> channelsUpdateUsernameFunction.channel;
    stream >> channelsUpdateUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsBlock &contactsBlockFunction)
{
    // stream >> function.tlType;
    stream >> contactsBlockFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsDeleteByPhones &contactsDeleteByPhonesFunction)
{
    // stream >> function.tlType;
    stream >> contactsDeleteByPhonesFunction.phones;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsDeleteContact &contactsDeleteContactFunction)
{
    // stream >> function.tlType;
    stream >> contactsDeleteContactFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsDeleteContacts &contactsDeleteContactsFunction)
{
    // stream >> function.tlType;
    stream >> contactsDeleteContactsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsGetBlocked &contactsGetBlockedFunction)
{
    // stream >> function.tlType;
    stream >> contactsGetBlockedFunction.offset;
    stream >> contactsGetBlockedFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsGetContactIDs &contactsGetContactIDsFunction)
{
    // stream >> function.tlType;
    stream >> contactsGetContactIDsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsGetContacts &contactsGetContactsFunction)
{
    // stream >> function.tlType;
    stream >> contactsGetContactsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsGetSaved &contactsGetSavedFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(contactsGetSavedFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsGetStatuses &contactsGetStatusesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(contactsGetStatusesFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsGetTopPeers &contactsGetTopPeersFunction)
{
    // stream >> function.tlType;
    stream >> contactsGetTopPeersFunction.flags;
    // (contactsGetTopPeersFunction.flags & 1 << 0) stands for correspondents "true" value
    // (contactsGetTopPeersFunction.flags & 1 << 1) stands for botsPm "true" value
    // (contactsGetTopPeersFunction.flags & 1 << 2) stands for botsInline "true" value
    // (contactsGetTopPeersFunction.flags & 1 << 3) stands for phoneCalls "true" value
    // (contactsGetTopPeersFunction.flags & 1 << 10) stands for groups "true" value
    // (contactsGetTopPeersFunction.flags & 1 << 15) stands for channels "true" value
    stream >> contactsGetTopPeersFunction.offset;
    stream >> contactsGetTopPeersFunction.limit;
    stream >> contactsGetTopPeersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsImportContacts &contactsImportContactsFunction)
{
    // stream >> function.tlType;
    stream >> contactsImportContactsFunction.contacts;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsResetSaved &contactsResetSavedFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(contactsResetSavedFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsResetTopPeerRating &contactsResetTopPeerRatingFunction)
{
    // stream >> function.tlType;
    stream >> contactsResetTopPeerRatingFunction.category;
    stream >> contactsResetTopPeerRatingFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsResolveUsername &contactsResolveUsernameFunction)
{
    // stream >> function.tlType;
    stream >> contactsResolveUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsSearch &contactsSearchFunction)
{
    // stream >> function.tlType;
    stream >> contactsSearchFunction.q;
    stream >> contactsSearchFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsToggleTopPeers &contactsToggleTopPeersFunction)
{
    // stream >> function.tlType;
    stream >> contactsToggleTopPeersFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLContactsUnblock &contactsUnblockFunction)
{
    // stream >> function.tlType;
    stream >> contactsUnblockFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpAcceptTermsOfService &helpAcceptTermsOfServiceFunction)
{
    // stream >> function.tlType;
    stream >> helpAcceptTermsOfServiceFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpEditUserInfo &helpEditUserInfoFunction)
{
    // stream >> function.tlType;
    stream >> helpEditUserInfoFunction.userId;
    stream >> helpEditUserInfoFunction.message;
    stream >> helpEditUserInfoFunction.entities;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetAppChangelog &helpGetAppChangelogFunction)
{
    // stream >> function.tlType;
    stream >> helpGetAppChangelogFunction.prevAppVersion;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetAppConfig &helpGetAppConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetAppConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetAppUpdate &helpGetAppUpdateFunction)
{
    // stream >> function.tlType;
    stream >> helpGetAppUpdateFunction.source;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetCdnConfig &helpGetCdnConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetCdnConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetConfig &helpGetConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetDeepLinkInfo &helpGetDeepLinkInfoFunction)
{
    // stream >> function.tlType;
    stream >> helpGetDeepLinkInfoFunction.path;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetInviteText &helpGetInviteTextFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetInviteTextFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetNearestDc &helpGetNearestDcFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetNearestDcFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetPassportConfig &helpGetPassportConfigFunction)
{
    // stream >> function.tlType;
    stream >> helpGetPassportConfigFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetProxyData &helpGetProxyDataFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetProxyDataFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetRecentMeUrls &helpGetRecentMeUrlsFunction)
{
    // stream >> function.tlType;
    stream >> helpGetRecentMeUrlsFunction.referer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetSupport &helpGetSupportFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetSupportFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetSupportName &helpGetSupportNameFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetSupportNameFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetTermsOfServiceUpdate &helpGetTermsOfServiceUpdateFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetTermsOfServiceUpdateFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpGetUserInfo &helpGetUserInfoFunction)
{
    // stream >> function.tlType;
    stream >> helpGetUserInfoFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpSaveAppLog &helpSaveAppLogFunction)
{
    // stream >> function.tlType;
    stream >> helpSaveAppLogFunction.events;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLHelpSetBotUpdatesStatus &helpSetBotUpdatesStatusFunction)
{
    // stream >> function.tlType;
    stream >> helpSetBotUpdatesStatusFunction.pendingUpdatesCount;
    stream >> helpSetBotUpdatesStatusFunction.message;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLLangpackGetDifference &langpackGetDifferenceFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetDifferenceFunction.langCode;
    stream >> langpackGetDifferenceFunction.fromVersion;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLLangpackGetLangPack &langpackGetLangPackFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetLangPackFunction.langPack;
    stream >> langpackGetLangPackFunction.langCode;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLLangpackGetLanguage &langpackGetLanguageFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetLanguageFunction.langPack;
    stream >> langpackGetLanguageFunction.langCode;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLLangpackGetLanguages &langpackGetLanguagesFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetLanguagesFunction.langPack;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLLangpackGetStrings &langpackGetStringsFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetStringsFunction.langPack;
    stream >> langpackGetStringsFunction.langCode;
    stream >> langpackGetStringsFunction.keys;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesAcceptEncryption &messagesAcceptEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> messagesAcceptEncryptionFunction.peer;
    stream >> messagesAcceptEncryptionFunction.gB;
    stream >> messagesAcceptEncryptionFunction.keyFingerprint;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesAddChatUser &messagesAddChatUserFunction)
{
    // stream >> function.tlType;
    stream >> messagesAddChatUserFunction.chatId;
    stream >> messagesAddChatUserFunction.userId;
    stream >> messagesAddChatUserFunction.fwdLimit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesCheckChatInvite &messagesCheckChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> messagesCheckChatInviteFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesClearAllDrafts &messagesClearAllDraftsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesClearAllDraftsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesClearRecentStickers &messagesClearRecentStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesClearRecentStickersFunction.flags;
    // (messagesClearRecentStickersFunction.flags & 1 << 0) stands for attached "true" value
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesCreateChat &messagesCreateChatFunction)
{
    // stream >> function.tlType;
    stream >> messagesCreateChatFunction.users;
    stream >> messagesCreateChatFunction.title;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesDeleteChatUser &messagesDeleteChatUserFunction)
{
    // stream >> function.tlType;
    stream >> messagesDeleteChatUserFunction.chatId;
    stream >> messagesDeleteChatUserFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesDeleteHistory &messagesDeleteHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesDeleteHistoryFunction.flags;
    // (messagesDeleteHistoryFunction.flags & 1 << 0) stands for justClear "true" value
    stream >> messagesDeleteHistoryFunction.peer;
    stream >> messagesDeleteHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesDeleteMessages &messagesDeleteMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesDeleteMessagesFunction.flags;
    // (messagesDeleteMessagesFunction.flags & 1 << 0) stands for revoke "true" value
    stream >> messagesDeleteMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesDiscardEncryption &messagesDiscardEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> messagesDiscardEncryptionFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesEditChatAdmin &messagesEditChatAdminFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditChatAdminFunction.chatId;
    stream >> messagesEditChatAdminFunction.userId;
    stream >> messagesEditChatAdminFunction.isAdmin;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesEditChatPhoto &messagesEditChatPhotoFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditChatPhotoFunction.chatId;
    stream >> messagesEditChatPhotoFunction.photo;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesEditChatTitle &messagesEditChatTitleFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditChatTitleFunction.chatId;
    stream >> messagesEditChatTitleFunction.title;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesEditInlineBotMessage &messagesEditInlineBotMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditInlineBotMessageFunction.flags;
    // (messagesEditInlineBotMessageFunction.flags & 1 << 1) stands for noWebpage "true" value
    stream >> messagesEditInlineBotMessageFunction.id;
    if (messagesEditInlineBotMessageFunction.flags & 1 << 11) {
        stream >> messagesEditInlineBotMessageFunction.message;
    }
    if (messagesEditInlineBotMessageFunction.flags & 1 << 14) {
        stream >> messagesEditInlineBotMessageFunction.media;
    }
    if (messagesEditInlineBotMessageFunction.flags & 1 << 2) {
        stream >> messagesEditInlineBotMessageFunction.replyMarkup;
    }
    if (messagesEditInlineBotMessageFunction.flags & 1 << 3) {
        stream >> messagesEditInlineBotMessageFunction.entities;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesEditMessage &messagesEditMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditMessageFunction.flags;
    // (messagesEditMessageFunction.flags & 1 << 1) stands for noWebpage "true" value
    stream >> messagesEditMessageFunction.peer;
    stream >> messagesEditMessageFunction.id;
    if (messagesEditMessageFunction.flags & 1 << 11) {
        stream >> messagesEditMessageFunction.message;
    }
    if (messagesEditMessageFunction.flags & 1 << 14) {
        stream >> messagesEditMessageFunction.media;
    }
    if (messagesEditMessageFunction.flags & 1 << 2) {
        stream >> messagesEditMessageFunction.replyMarkup;
    }
    if (messagesEditMessageFunction.flags & 1 << 3) {
        stream >> messagesEditMessageFunction.entities;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesExportChatInvite &messagesExportChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> messagesExportChatInviteFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesFaveSticker &messagesFaveStickerFunction)
{
    // stream >> function.tlType;
    stream >> messagesFaveStickerFunction.id;
    stream >> messagesFaveStickerFunction.unfave;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesForwardMessages &messagesForwardMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesForwardMessagesFunction.flags;
    // (messagesForwardMessagesFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesForwardMessagesFunction.flags & 1 << 6) stands for background "true" value
    // (messagesForwardMessagesFunction.flags & 1 << 8) stands for withMyScore "true" value
    // (messagesForwardMessagesFunction.flags & 1 << 9) stands for grouped "true" value
    stream >> messagesForwardMessagesFunction.fromPeer;
    stream >> messagesForwardMessagesFunction.id;
    stream >> messagesForwardMessagesFunction.randomId;
    stream >> messagesForwardMessagesFunction.toPeer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetAllChats &messagesGetAllChatsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetAllChatsFunction.exceptIds;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetAllDrafts &messagesGetAllDraftsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesGetAllDraftsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetAllStickers &messagesGetAllStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetAllStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetArchivedStickers &messagesGetArchivedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetArchivedStickersFunction.flags;
    // (messagesGetArchivedStickersFunction.flags & 1 << 0) stands for masks "true" value
    stream >> messagesGetArchivedStickersFunction.offsetId;
    stream >> messagesGetArchivedStickersFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetAttachedStickers &messagesGetAttachedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetAttachedStickersFunction.media;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetBotCallbackAnswer &messagesGetBotCallbackAnswerFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetBotCallbackAnswerFunction.flags;
    // (messagesGetBotCallbackAnswerFunction.flags & 1 << 1) stands for game "true" value
    stream >> messagesGetBotCallbackAnswerFunction.peer;
    stream >> messagesGetBotCallbackAnswerFunction.msgId;
    if (messagesGetBotCallbackAnswerFunction.flags & 1 << 0) {
        stream >> messagesGetBotCallbackAnswerFunction.data;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetChats &messagesGetChatsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetChatsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetCommonChats &messagesGetCommonChatsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetCommonChatsFunction.userId;
    stream >> messagesGetCommonChatsFunction.maxId;
    stream >> messagesGetCommonChatsFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetDhConfig &messagesGetDhConfigFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetDhConfigFunction.version;
    stream >> messagesGetDhConfigFunction.randomLength;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetDialogUnreadMarks &messagesGetDialogUnreadMarksFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesGetDialogUnreadMarksFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetDialogs &messagesGetDialogsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetDialogsFunction.flags;
    // (messagesGetDialogsFunction.flags & 1 << 0) stands for excludePinned "true" value
    stream >> messagesGetDialogsFunction.offsetDate;
    stream >> messagesGetDialogsFunction.offsetId;
    stream >> messagesGetDialogsFunction.offsetPeer;
    stream >> messagesGetDialogsFunction.limit;
    stream >> messagesGetDialogsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetDocumentByHash &messagesGetDocumentByHashFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetDocumentByHashFunction.sha256;
    stream >> messagesGetDocumentByHashFunction.size;
    stream >> messagesGetDocumentByHashFunction.mimeType;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetFavedStickers &messagesGetFavedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetFavedStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetFeaturedStickers &messagesGetFeaturedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetFeaturedStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetFullChat &messagesGetFullChatFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetFullChatFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetGameHighScores &messagesGetGameHighScoresFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetGameHighScoresFunction.peer;
    stream >> messagesGetGameHighScoresFunction.id;
    stream >> messagesGetGameHighScoresFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetHistory &messagesGetHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetHistoryFunction.peer;
    stream >> messagesGetHistoryFunction.offsetId;
    stream >> messagesGetHistoryFunction.offsetDate;
    stream >> messagesGetHistoryFunction.addOffset;
    stream >> messagesGetHistoryFunction.limit;
    stream >> messagesGetHistoryFunction.maxId;
    stream >> messagesGetHistoryFunction.minId;
    stream >> messagesGetHistoryFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetInlineBotResults &messagesGetInlineBotResultsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetInlineBotResultsFunction.flags;
    stream >> messagesGetInlineBotResultsFunction.bot;
    stream >> messagesGetInlineBotResultsFunction.peer;
    if (messagesGetInlineBotResultsFunction.flags & 1 << 0) {
        stream >> messagesGetInlineBotResultsFunction.geoPoint;
    }
    stream >> messagesGetInlineBotResultsFunction.query;
    stream >> messagesGetInlineBotResultsFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetInlineGameHighScores &messagesGetInlineGameHighScoresFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetInlineGameHighScoresFunction.id;
    stream >> messagesGetInlineGameHighScoresFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetMaskStickers &messagesGetMaskStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMaskStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetMessageEditData &messagesGetMessageEditDataFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMessageEditDataFunction.peer;
    stream >> messagesGetMessageEditDataFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetMessages &messagesGetMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetMessagesViews &messagesGetMessagesViewsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMessagesViewsFunction.peer;
    stream >> messagesGetMessagesViewsFunction.id;
    stream >> messagesGetMessagesViewsFunction.increment;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetOnlines &messagesGetOnlinesFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetOnlinesFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetPeerDialogs &messagesGetPeerDialogsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetPeerDialogsFunction.peers;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetPeerSettings &messagesGetPeerSettingsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetPeerSettingsFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetPinnedDialogs &messagesGetPinnedDialogsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesGetPinnedDialogsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetPollResults &messagesGetPollResultsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetPollResultsFunction.peer;
    stream >> messagesGetPollResultsFunction.msgId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetRecentLocations &messagesGetRecentLocationsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetRecentLocationsFunction.peer;
    stream >> messagesGetRecentLocationsFunction.limit;
    stream >> messagesGetRecentLocationsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetRecentStickers &messagesGetRecentStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetRecentStickersFunction.flags;
    // (messagesGetRecentStickersFunction.flags & 1 << 0) stands for attached "true" value
    stream >> messagesGetRecentStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetSavedGifs &messagesGetSavedGifsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetSavedGifsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetSplitRanges &messagesGetSplitRangesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesGetSplitRangesFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetStatsURL &messagesGetStatsURLFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetStatsURLFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetStickerSet &messagesGetStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetStickerSetFunction.stickerset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetStickers &messagesGetStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetStickersFunction.emoticon;
    stream >> messagesGetStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetUnreadMentions &messagesGetUnreadMentionsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetUnreadMentionsFunction.peer;
    stream >> messagesGetUnreadMentionsFunction.offsetId;
    stream >> messagesGetUnreadMentionsFunction.addOffset;
    stream >> messagesGetUnreadMentionsFunction.limit;
    stream >> messagesGetUnreadMentionsFunction.maxId;
    stream >> messagesGetUnreadMentionsFunction.minId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetWebPage &messagesGetWebPageFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetWebPageFunction.url;
    stream >> messagesGetWebPageFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesGetWebPagePreview &messagesGetWebPagePreviewFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetWebPagePreviewFunction.flags;
    stream >> messagesGetWebPagePreviewFunction.message;
    if (messagesGetWebPagePreviewFunction.flags & 1 << 3) {
        stream >> messagesGetWebPagePreviewFunction.entities;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesHideReportSpam &messagesHideReportSpamFunction)
{
    // stream >> function.tlType;
    stream >> messagesHideReportSpamFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesImportChatInvite &messagesImportChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> messagesImportChatInviteFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesInstallStickerSet &messagesInstallStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> messagesInstallStickerSetFunction.stickerset;
    stream >> messagesInstallStickerSetFunction.archived;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesMarkDialogUnread &messagesMarkDialogUnreadFunction)
{
    // stream >> function.tlType;
    stream >> messagesMarkDialogUnreadFunction.flags;
    // (messagesMarkDialogUnreadFunction.flags & 1 << 0) stands for unread "true" value
    stream >> messagesMarkDialogUnreadFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesMigrateChat &messagesMigrateChatFunction)
{
    // stream >> function.tlType;
    stream >> messagesMigrateChatFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReadEncryptedHistory &messagesReadEncryptedHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadEncryptedHistoryFunction.peer;
    stream >> messagesReadEncryptedHistoryFunction.maxDate;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReadFeaturedStickers &messagesReadFeaturedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadFeaturedStickersFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReadHistory &messagesReadHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadHistoryFunction.peer;
    stream >> messagesReadHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReadMentions &messagesReadMentionsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadMentionsFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReadMessageContents &messagesReadMessageContentsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadMessageContentsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReceivedMessages &messagesReceivedMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesReceivedMessagesFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReceivedQueue &messagesReceivedQueueFunction)
{
    // stream >> function.tlType;
    stream >> messagesReceivedQueueFunction.maxQts;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReorderPinnedDialogs &messagesReorderPinnedDialogsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReorderPinnedDialogsFunction.flags;
    // (messagesReorderPinnedDialogsFunction.flags & 1 << 0) stands for force "true" value
    stream >> messagesReorderPinnedDialogsFunction.order;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReorderStickerSets &messagesReorderStickerSetsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReorderStickerSetsFunction.flags;
    // (messagesReorderStickerSetsFunction.flags & 1 << 0) stands for masks "true" value
    stream >> messagesReorderStickerSetsFunction.order;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReport &messagesReportFunction)
{
    // stream >> function.tlType;
    stream >> messagesReportFunction.peer;
    stream >> messagesReportFunction.id;
    stream >> messagesReportFunction.reason;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReportEncryptedSpam &messagesReportEncryptedSpamFunction)
{
    // stream >> function.tlType;
    stream >> messagesReportEncryptedSpamFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesReportSpam &messagesReportSpamFunction)
{
    // stream >> function.tlType;
    stream >> messagesReportSpamFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesRequestEncryption &messagesRequestEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> messagesRequestEncryptionFunction.userId;
    stream >> messagesRequestEncryptionFunction.randomId;
    stream >> messagesRequestEncryptionFunction.gA;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSaveDraft &messagesSaveDraftFunction)
{
    // stream >> function.tlType;
    stream >> messagesSaveDraftFunction.flags;
    // (messagesSaveDraftFunction.flags & 1 << 1) stands for noWebpage "true" value
    if (messagesSaveDraftFunction.flags & 1 << 0) {
        stream >> messagesSaveDraftFunction.replyToMsgId;
    }
    stream >> messagesSaveDraftFunction.peer;
    stream >> messagesSaveDraftFunction.message;
    if (messagesSaveDraftFunction.flags & 1 << 3) {
        stream >> messagesSaveDraftFunction.entities;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSaveGif &messagesSaveGifFunction)
{
    // stream >> function.tlType;
    stream >> messagesSaveGifFunction.id;
    stream >> messagesSaveGifFunction.unsave;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSaveRecentSticker &messagesSaveRecentStickerFunction)
{
    // stream >> function.tlType;
    stream >> messagesSaveRecentStickerFunction.flags;
    // (messagesSaveRecentStickerFunction.flags & 1 << 0) stands for attached "true" value
    stream >> messagesSaveRecentStickerFunction.id;
    stream >> messagesSaveRecentStickerFunction.unsave;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSearch &messagesSearchFunction)
{
    // stream >> function.tlType;
    stream >> messagesSearchFunction.flags;
    stream >> messagesSearchFunction.peer;
    stream >> messagesSearchFunction.q;
    if (messagesSearchFunction.flags & 1 << 0) {
        stream >> messagesSearchFunction.fromId;
    }
    stream >> messagesSearchFunction.filter;
    stream >> messagesSearchFunction.minDate;
    stream >> messagesSearchFunction.maxDate;
    stream >> messagesSearchFunction.offsetId;
    stream >> messagesSearchFunction.addOffset;
    stream >> messagesSearchFunction.limit;
    stream >> messagesSearchFunction.maxId;
    stream >> messagesSearchFunction.minId;
    stream >> messagesSearchFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSearchGifs &messagesSearchGifsFunction)
{
    // stream >> function.tlType;
    stream >> messagesSearchGifsFunction.q;
    stream >> messagesSearchGifsFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSearchGlobal &messagesSearchGlobalFunction)
{
    // stream >> function.tlType;
    stream >> messagesSearchGlobalFunction.q;
    stream >> messagesSearchGlobalFunction.offsetDate;
    stream >> messagesSearchGlobalFunction.offsetPeer;
    stream >> messagesSearchGlobalFunction.offsetId;
    stream >> messagesSearchGlobalFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSearchStickerSets &messagesSearchStickerSetsFunction)
{
    // stream >> function.tlType;
    stream >> messagesSearchStickerSetsFunction.flags;
    // (messagesSearchStickerSetsFunction.flags & 1 << 0) stands for excludeFeatured "true" value
    stream >> messagesSearchStickerSetsFunction.q;
    stream >> messagesSearchStickerSetsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendEncrypted &messagesSendEncryptedFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendEncryptedFunction.peer;
    stream >> messagesSendEncryptedFunction.randomId;
    stream >> messagesSendEncryptedFunction.data;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendEncryptedFile &messagesSendEncryptedFileFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendEncryptedFileFunction.peer;
    stream >> messagesSendEncryptedFileFunction.randomId;
    stream >> messagesSendEncryptedFileFunction.data;
    stream >> messagesSendEncryptedFileFunction.file;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendEncryptedService &messagesSendEncryptedServiceFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendEncryptedServiceFunction.peer;
    stream >> messagesSendEncryptedServiceFunction.randomId;
    stream >> messagesSendEncryptedServiceFunction.data;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendInlineBotResult &messagesSendInlineBotResultFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendInlineBotResultFunction.flags;
    // (messagesSendInlineBotResultFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesSendInlineBotResultFunction.flags & 1 << 6) stands for background "true" value
    // (messagesSendInlineBotResultFunction.flags & 1 << 7) stands for clearDraft "true" value
    // (messagesSendInlineBotResultFunction.flags & 1 << 11) stands for hideVia "true" value
    stream >> messagesSendInlineBotResultFunction.peer;
    if (messagesSendInlineBotResultFunction.flags & 1 << 0) {
        stream >> messagesSendInlineBotResultFunction.replyToMsgId;
    }
    stream >> messagesSendInlineBotResultFunction.randomId;
    stream >> messagesSendInlineBotResultFunction.queryId;
    stream >> messagesSendInlineBotResultFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendMedia &messagesSendMediaFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendMediaFunction.flags;
    // (messagesSendMediaFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesSendMediaFunction.flags & 1 << 6) stands for background "true" value
    // (messagesSendMediaFunction.flags & 1 << 7) stands for clearDraft "true" value
    stream >> messagesSendMediaFunction.peer;
    if (messagesSendMediaFunction.flags & 1 << 0) {
        stream >> messagesSendMediaFunction.replyToMsgId;
    }
    stream >> messagesSendMediaFunction.media;
    stream >> messagesSendMediaFunction.message;
    stream >> messagesSendMediaFunction.randomId;
    if (messagesSendMediaFunction.flags & 1 << 2) {
        stream >> messagesSendMediaFunction.replyMarkup;
    }
    if (messagesSendMediaFunction.flags & 1 << 3) {
        stream >> messagesSendMediaFunction.entities;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendMessage &messagesSendMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendMessageFunction.flags;
    // (messagesSendMessageFunction.flags & 1 << 1) stands for noWebpage "true" value
    // (messagesSendMessageFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesSendMessageFunction.flags & 1 << 6) stands for background "true" value
    // (messagesSendMessageFunction.flags & 1 << 7) stands for clearDraft "true" value
    stream >> messagesSendMessageFunction.peer;
    if (messagesSendMessageFunction.flags & 1 << 0) {
        stream >> messagesSendMessageFunction.replyToMsgId;
    }
    stream >> messagesSendMessageFunction.message;
    stream >> messagesSendMessageFunction.randomId;
    if (messagesSendMessageFunction.flags & 1 << 2) {
        stream >> messagesSendMessageFunction.replyMarkup;
    }
    if (messagesSendMessageFunction.flags & 1 << 3) {
        stream >> messagesSendMessageFunction.entities;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendMultiMedia &messagesSendMultiMediaFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendMultiMediaFunction.flags;
    // (messagesSendMultiMediaFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesSendMultiMediaFunction.flags & 1 << 6) stands for background "true" value
    // (messagesSendMultiMediaFunction.flags & 1 << 7) stands for clearDraft "true" value
    stream >> messagesSendMultiMediaFunction.peer;
    if (messagesSendMultiMediaFunction.flags & 1 << 0) {
        stream >> messagesSendMultiMediaFunction.replyToMsgId;
    }
    stream >> messagesSendMultiMediaFunction.multiMedia;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendScreenshotNotification &messagesSendScreenshotNotificationFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendScreenshotNotificationFunction.peer;
    stream >> messagesSendScreenshotNotificationFunction.replyToMsgId;
    stream >> messagesSendScreenshotNotificationFunction.randomId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSendVote &messagesSendVoteFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendVoteFunction.peer;
    stream >> messagesSendVoteFunction.msgId;
    stream >> messagesSendVoteFunction.options;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetBotCallbackAnswer &messagesSetBotCallbackAnswerFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetBotCallbackAnswerFunction.flags;
    // (messagesSetBotCallbackAnswerFunction.flags & 1 << 1) stands for alert "true" value
    stream >> messagesSetBotCallbackAnswerFunction.queryId;
    if (messagesSetBotCallbackAnswerFunction.flags & 1 << 0) {
        stream >> messagesSetBotCallbackAnswerFunction.message;
    }
    if (messagesSetBotCallbackAnswerFunction.flags & 1 << 2) {
        stream >> messagesSetBotCallbackAnswerFunction.url;
    }
    stream >> messagesSetBotCallbackAnswerFunction.cacheTime;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetBotPrecheckoutResults &messagesSetBotPrecheckoutResultsFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetBotPrecheckoutResultsFunction.flags;
    // (messagesSetBotPrecheckoutResultsFunction.flags & 1 << 1) stands for success "true" value
    stream >> messagesSetBotPrecheckoutResultsFunction.queryId;
    if (messagesSetBotPrecheckoutResultsFunction.flags & 1 << 0) {
        stream >> messagesSetBotPrecheckoutResultsFunction.error;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetBotShippingResults &messagesSetBotShippingResultsFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetBotShippingResultsFunction.flags;
    stream >> messagesSetBotShippingResultsFunction.queryId;
    if (messagesSetBotShippingResultsFunction.flags & 1 << 0) {
        stream >> messagesSetBotShippingResultsFunction.error;
    }
    if (messagesSetBotShippingResultsFunction.flags & 1 << 1) {
        stream >> messagesSetBotShippingResultsFunction.shippingOptions;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetEncryptedTyping &messagesSetEncryptedTypingFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetEncryptedTypingFunction.peer;
    stream >> messagesSetEncryptedTypingFunction.typing;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetGameScore &messagesSetGameScoreFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetGameScoreFunction.flags;
    // (messagesSetGameScoreFunction.flags & 1 << 0) stands for editMessage "true" value
    // (messagesSetGameScoreFunction.flags & 1 << 1) stands for force "true" value
    stream >> messagesSetGameScoreFunction.peer;
    stream >> messagesSetGameScoreFunction.id;
    stream >> messagesSetGameScoreFunction.userId;
    stream >> messagesSetGameScoreFunction.score;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetInlineBotResults &messagesSetInlineBotResultsFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetInlineBotResultsFunction.flags;
    // (messagesSetInlineBotResultsFunction.flags & 1 << 0) stands for gallery "true" value
    // (messagesSetInlineBotResultsFunction.flags & 1 << 1) stands for isPrivate "true" value
    stream >> messagesSetInlineBotResultsFunction.queryId;
    stream >> messagesSetInlineBotResultsFunction.results;
    stream >> messagesSetInlineBotResultsFunction.cacheTime;
    if (messagesSetInlineBotResultsFunction.flags & 1 << 2) {
        stream >> messagesSetInlineBotResultsFunction.nextOffset;
    }
    if (messagesSetInlineBotResultsFunction.flags & 1 << 3) {
        stream >> messagesSetInlineBotResultsFunction.switchPm;
    }
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetInlineGameScore &messagesSetInlineGameScoreFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetInlineGameScoreFunction.flags;
    // (messagesSetInlineGameScoreFunction.flags & 1 << 0) stands for editMessage "true" value
    // (messagesSetInlineGameScoreFunction.flags & 1 << 1) stands for force "true" value
    stream >> messagesSetInlineGameScoreFunction.id;
    stream >> messagesSetInlineGameScoreFunction.userId;
    stream >> messagesSetInlineGameScoreFunction.score;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesSetTyping &messagesSetTypingFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetTypingFunction.peer;
    stream >> messagesSetTypingFunction.action;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesStartBot &messagesStartBotFunction)
{
    // stream >> function.tlType;
    stream >> messagesStartBotFunction.bot;
    stream >> messagesStartBotFunction.peer;
    stream >> messagesStartBotFunction.randomId;
    stream >> messagesStartBotFunction.startParam;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesToggleChatAdmins &messagesToggleChatAdminsFunction)
{
    // stream >> function.tlType;
    stream >> messagesToggleChatAdminsFunction.chatId;
    stream >> messagesToggleChatAdminsFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesToggleDialogPin &messagesToggleDialogPinFunction)
{
    // stream >> function.tlType;
    stream >> messagesToggleDialogPinFunction.flags;
    // (messagesToggleDialogPinFunction.flags & 1 << 0) stands for pinned "true" value
    stream >> messagesToggleDialogPinFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesUninstallStickerSet &messagesUninstallStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> messagesUninstallStickerSetFunction.stickerset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesUpdatePinnedMessage &messagesUpdatePinnedMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesUpdatePinnedMessageFunction.flags;
    // (messagesUpdatePinnedMessageFunction.flags & 1 << 0) stands for silent "true" value
    stream >> messagesUpdatePinnedMessageFunction.peer;
    stream >> messagesUpdatePinnedMessageFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesUploadEncryptedFile &messagesUploadEncryptedFileFunction)
{
    // stream >> function.tlType;
    stream >> messagesUploadEncryptedFileFunction.peer;
    stream >> messagesUploadEncryptedFileFunction.file;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLMessagesUploadMedia &messagesUploadMediaFunction)
{
    // stream >> function.tlType;
    stream >> messagesUploadMediaFunction.peer;
    stream >> messagesUploadMediaFunction.media;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPaymentsClearSavedInfo &paymentsClearSavedInfoFunction)
{
    // stream >> function.tlType;
    stream >> paymentsClearSavedInfoFunction.flags;
    // (paymentsClearSavedInfoFunction.flags & 1 << 0) stands for credentials "true" value
    // (paymentsClearSavedInfoFunction.flags & 1 << 1) stands for info "true" value
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPaymentsGetPaymentForm &paymentsGetPaymentFormFunction)
{
    // stream >> function.tlType;
    stream >> paymentsGetPaymentFormFunction.msgId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPaymentsGetPaymentReceipt &paymentsGetPaymentReceiptFunction)
{
    // stream >> function.tlType;
    stream >> paymentsGetPaymentReceiptFunction.msgId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPaymentsGetSavedInfo &paymentsGetSavedInfoFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(paymentsGetSavedInfoFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPaymentsSendPaymentForm &paymentsSendPaymentFormFunction)
{
    // stream >> function.tlType;
    stream >> paymentsSendPaymentFormFunction.flags;
    stream >> paymentsSendPaymentFormFunction.msgId;
    if (paymentsSendPaymentFormFunction.flags & 1 << 0) {
        stream >> paymentsSendPaymentFormFunction.requestedInfoId;
    }
    if (paymentsSendPaymentFormFunction.flags & 1 << 1) {
        stream >> paymentsSendPaymentFormFunction.shippingOptionId;
    }
    stream >> paymentsSendPaymentFormFunction.credentials;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPaymentsValidateRequestedInfo &paymentsValidateRequestedInfoFunction)
{
    // stream >> function.tlType;
    stream >> paymentsValidateRequestedInfoFunction.flags;
    // (paymentsValidateRequestedInfoFunction.flags & 1 << 0) stands for save "true" value
    stream >> paymentsValidateRequestedInfoFunction.msgId;
    stream >> paymentsValidateRequestedInfoFunction.info;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneAcceptCall &phoneAcceptCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneAcceptCallFunction.peer;
    stream >> phoneAcceptCallFunction.gB;
    stream >> phoneAcceptCallFunction.protocol;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneConfirmCall &phoneConfirmCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneConfirmCallFunction.peer;
    stream >> phoneConfirmCallFunction.gA;
    stream >> phoneConfirmCallFunction.keyFingerprint;
    stream >> phoneConfirmCallFunction.protocol;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneDiscardCall &phoneDiscardCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneDiscardCallFunction.peer;
    stream >> phoneDiscardCallFunction.duration;
    stream >> phoneDiscardCallFunction.reason;
    stream >> phoneDiscardCallFunction.connectionId;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneGetCallConfig &phoneGetCallConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(phoneGetCallConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneReceivedCall &phoneReceivedCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneReceivedCallFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneRequestCall &phoneRequestCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneRequestCallFunction.userId;
    stream >> phoneRequestCallFunction.randomId;
    stream >> phoneRequestCallFunction.gAHash;
    stream >> phoneRequestCallFunction.protocol;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneSaveCallDebug &phoneSaveCallDebugFunction)
{
    // stream >> function.tlType;
    stream >> phoneSaveCallDebugFunction.peer;
    stream >> phoneSaveCallDebugFunction.debug;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhoneSetCallRating &phoneSetCallRatingFunction)
{
    // stream >> function.tlType;
    stream >> phoneSetCallRatingFunction.peer;
    stream >> phoneSetCallRatingFunction.rating;
    stream >> phoneSetCallRatingFunction.comment;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhotosDeletePhotos &photosDeletePhotosFunction)
{
    // stream >> function.tlType;
    stream >> photosDeletePhotosFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhotosGetUserPhotos &photosGetUserPhotosFunction)
{
    // stream >> function.tlType;
    stream >> photosGetUserPhotosFunction.userId;
    stream >> photosGetUserPhotosFunction.offset;
    stream >> photosGetUserPhotosFunction.maxId;
    stream >> photosGetUserPhotosFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhotosUpdateProfilePhoto &photosUpdateProfilePhotoFunction)
{
    // stream >> function.tlType;
    stream >> photosUpdateProfilePhotoFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLPhotosUploadProfilePhoto &photosUploadProfilePhotoFunction)
{
    // stream >> function.tlType;
    stream >> photosUploadProfilePhotoFunction.file;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLStickersAddStickerToSet &stickersAddStickerToSetFunction)
{
    // stream >> function.tlType;
    stream >> stickersAddStickerToSetFunction.stickerset;
    stream >> stickersAddStickerToSetFunction.sticker;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLStickersChangeStickerPosition &stickersChangeStickerPositionFunction)
{
    // stream >> function.tlType;
    stream >> stickersChangeStickerPositionFunction.sticker;
    stream >> stickersChangeStickerPositionFunction.position;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLStickersCreateStickerSet &stickersCreateStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> stickersCreateStickerSetFunction.flags;
    // (stickersCreateStickerSetFunction.flags & 1 << 0) stands for masks "true" value
    stream >> stickersCreateStickerSetFunction.userId;
    stream >> stickersCreateStickerSetFunction.title;
    stream >> stickersCreateStickerSetFunction.shortName;
    stream >> stickersCreateStickerSetFunction.stickers;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLStickersRemoveStickerFromSet &stickersRemoveStickerFromSetFunction)
{
    // stream >> function.tlType;
    stream >> stickersRemoveStickerFromSetFunction.sticker;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUpdatesGetChannelDifference &updatesGetChannelDifferenceFunction)
{
    // stream >> function.tlType;
    stream >> updatesGetChannelDifferenceFunction.flags;
    // (updatesGetChannelDifferenceFunction.flags & 1 << 0) stands for force "true" value
    stream >> updatesGetChannelDifferenceFunction.channel;
    stream >> updatesGetChannelDifferenceFunction.filter;
    stream >> updatesGetChannelDifferenceFunction.pts;
    stream >> updatesGetChannelDifferenceFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUpdatesGetDifference &updatesGetDifferenceFunction)
{
    // stream >> function.tlType;
    stream >> updatesGetDifferenceFunction.flags;
    stream >> updatesGetDifferenceFunction.pts;
    if (updatesGetDifferenceFunction.flags & 1 << 0) {
        stream >> updatesGetDifferenceFunction.ptsTotalLimit;
    }
    stream >> updatesGetDifferenceFunction.date;
    stream >> updatesGetDifferenceFunction.qts;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUpdatesGetState &updatesGetStateFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(updatesGetStateFunction)
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadGetCdnFile &uploadGetCdnFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetCdnFileFunction.fileToken;
    stream >> uploadGetCdnFileFunction.offset;
    stream >> uploadGetCdnFileFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadGetCdnFileHashes &uploadGetCdnFileHashesFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetCdnFileHashesFunction.fileToken;
    stream >> uploadGetCdnFileHashesFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadGetFile &uploadGetFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetFileFunction.location;
    stream >> uploadGetFileFunction.offset;
    stream >> uploadGetFileFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadGetFileHashes &uploadGetFileHashesFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetFileHashesFunction.location;
    stream >> uploadGetFileHashesFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadGetWebFile &uploadGetWebFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetWebFileFunction.location;
    stream >> uploadGetWebFileFunction.offset;
    stream >> uploadGetWebFileFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadReuploadCdnFile &uploadReuploadCdnFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadReuploadCdnFileFunction.fileToken;
    stream >> uploadReuploadCdnFileFunction.requestToken;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadSaveBigFilePart &uploadSaveBigFilePartFunction)
{
    // stream >> function.tlType;
    stream >> uploadSaveBigFilePartFunction.fileId;
    stream >> uploadSaveBigFilePartFunction.filePart;
    stream >> uploadSaveBigFilePartFunction.fileTotalParts;
    stream >> uploadSaveBigFilePartFunction.bytes;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUploadSaveFilePart &uploadSaveFilePartFunction)
{
    // stream >> function.tlType;
    stream >> uploadSaveFilePartFunction.fileId;
    stream >> uploadSaveFilePartFunction.filePart;
    stream >> uploadSaveFilePartFunction.bytes;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUsersGetFullUser &usersGetFullUserFunction)
{
    // stream >> function.tlType;
    stream >> usersGetFullUserFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUsersGetUsers &usersGetUsersFunction)
{
    // stream >> function.tlType;
    stream >> usersGetUsersFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, Functions::TLUsersSetSecureValueErrors &usersSetSecureValueErrorsFunction)
{
    // stream >> function.tlType;
    stream >> usersSetSecureValueErrorsFunction.id;
    stream >> usersSetSecureValueErrorsFunction.errors;
    return stream;
}
// End of generated write operators

} // MTProto namespace

} // Telegram namespace
