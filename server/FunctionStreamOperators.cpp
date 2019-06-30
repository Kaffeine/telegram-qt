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
template Stream &Stream::operator>>(TLVector<TLDisabledFeature> &v);
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

Stream &operator>>(Stream &stream, TLFunctions::TLPing &ping)
{
    // stream >> function.tlType;
    stream >> ping.tlType;
    switch (ping.tlType) {
    case TLFunctions::TLPing::predicate:
        stream >> ping.pingId;
        break;
    case TLFunctions::TLPing::predicateDisconnect:
        stream >> ping.pingId;
        stream >> ping.disconnectDelay;
        break;
    default:
        break;
    }
    return stream;
}

// Generated write operators
Stream &operator>>(Stream &stream, TLFunctions::TLAccountChangePhone &accountChangePhoneFunction)
{
    // stream >> function.tlType;
    stream >> accountChangePhoneFunction.phoneNumber;
    stream >> accountChangePhoneFunction.phoneCodeHash;
    stream >> accountChangePhoneFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountCheckUsername &accountCheckUsernameFunction)
{
    // stream >> function.tlType;
    stream >> accountCheckUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountConfirmPhone &accountConfirmPhoneFunction)
{
    // stream >> function.tlType;
    stream >> accountConfirmPhoneFunction.phoneCodeHash;
    stream >> accountConfirmPhoneFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountDeleteAccount &accountDeleteAccountFunction)
{
    // stream >> function.tlType;
    stream >> accountDeleteAccountFunction.reason;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetAccountTTL &accountGetAccountTTLFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetAccountTTLFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetAuthorizations &accountGetAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetAuthorizationsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetNotifySettings &accountGetNotifySettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountGetNotifySettingsFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetPassword &accountGetPasswordFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetPasswordFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetPasswordSettings &accountGetPasswordSettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountGetPasswordSettingsFunction.currentPasswordHash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetPrivacy &accountGetPrivacyFunction)
{
    // stream >> function.tlType;
    stream >> accountGetPrivacyFunction.key;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetTmpPassword &accountGetTmpPasswordFunction)
{
    // stream >> function.tlType;
    stream >> accountGetTmpPasswordFunction.passwordHash;
    stream >> accountGetTmpPasswordFunction.period;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountGetWallPapers &accountGetWallPapersFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountGetWallPapersFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountRegisterDevice &accountRegisterDeviceFunction)
{
    // stream >> function.tlType;
    stream >> accountRegisterDeviceFunction.tokenType;
    stream >> accountRegisterDeviceFunction.token;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountReportPeer &accountReportPeerFunction)
{
    // stream >> function.tlType;
    stream >> accountReportPeerFunction.peer;
    stream >> accountReportPeerFunction.reason;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountResetAuthorization &accountResetAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> accountResetAuthorizationFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountResetNotifySettings &accountResetNotifySettingsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(accountResetNotifySettingsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountSendChangePhoneCode &accountSendChangePhoneCodeFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLAccountSendConfirmPhoneCode &accountSendConfirmPhoneCodeFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLAccountSetAccountTTL &accountSetAccountTTLFunction)
{
    // stream >> function.tlType;
    stream >> accountSetAccountTTLFunction.ttl;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountSetPrivacy &accountSetPrivacyFunction)
{
    // stream >> function.tlType;
    stream >> accountSetPrivacyFunction.key;
    stream >> accountSetPrivacyFunction.rules;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUnregisterDevice &accountUnregisterDeviceFunction)
{
    // stream >> function.tlType;
    stream >> accountUnregisterDeviceFunction.tokenType;
    stream >> accountUnregisterDeviceFunction.token;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUpdateDeviceLocked &accountUpdateDeviceLockedFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateDeviceLockedFunction.period;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUpdateNotifySettings &accountUpdateNotifySettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateNotifySettingsFunction.peer;
    stream >> accountUpdateNotifySettingsFunction.settings;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUpdatePasswordSettings &accountUpdatePasswordSettingsFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdatePasswordSettingsFunction.currentPasswordHash;
    stream >> accountUpdatePasswordSettingsFunction.newSettings;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUpdateProfile &accountUpdateProfileFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUpdateStatus &accountUpdateStatusFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateStatusFunction.offline;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAccountUpdateUsername &accountUpdateUsernameFunction)
{
    // stream >> function.tlType;
    stream >> accountUpdateUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthBindTempAuthKey &authBindTempAuthKeyFunction)
{
    // stream >> function.tlType;
    stream >> authBindTempAuthKeyFunction.permAuthKeyId;
    stream >> authBindTempAuthKeyFunction.nonce;
    stream >> authBindTempAuthKeyFunction.expiresAt;
    stream >> authBindTempAuthKeyFunction.encryptedMessage;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthCancelCode &authCancelCodeFunction)
{
    // stream >> function.tlType;
    stream >> authCancelCodeFunction.phoneNumber;
    stream >> authCancelCodeFunction.phoneCodeHash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthCheckPassword &authCheckPasswordFunction)
{
    // stream >> function.tlType;
    stream >> authCheckPasswordFunction.passwordHash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthCheckPhone &authCheckPhoneFunction)
{
    // stream >> function.tlType;
    stream >> authCheckPhoneFunction.phoneNumber;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthDropTempAuthKeys &authDropTempAuthKeysFunction)
{
    // stream >> function.tlType;
    stream >> authDropTempAuthKeysFunction.exceptAuthKeys;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthExportAuthorization &authExportAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> authExportAuthorizationFunction.dcId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthImportAuthorization &authImportAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> authImportAuthorizationFunction.id;
    stream >> authImportAuthorizationFunction.bytes;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthImportBotAuthorization &authImportBotAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> authImportBotAuthorizationFunction.flags;
    stream >> authImportBotAuthorizationFunction.apiId;
    stream >> authImportBotAuthorizationFunction.apiHash;
    stream >> authImportBotAuthorizationFunction.botAuthToken;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthLogOut &authLogOutFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(authLogOutFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthRecoverPassword &authRecoverPasswordFunction)
{
    // stream >> function.tlType;
    stream >> authRecoverPasswordFunction.code;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthRequestPasswordRecovery &authRequestPasswordRecoveryFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(authRequestPasswordRecoveryFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthResendCode &authResendCodeFunction)
{
    // stream >> function.tlType;
    stream >> authResendCodeFunction.phoneNumber;
    stream >> authResendCodeFunction.phoneCodeHash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthResetAuthorizations &authResetAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(authResetAuthorizationsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthSendCode &authSendCodeFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLAuthSendInvites &authSendInvitesFunction)
{
    // stream >> function.tlType;
    stream >> authSendInvitesFunction.phoneNumbers;
    stream >> authSendInvitesFunction.message;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthSignIn &authSignInFunction)
{
    // stream >> function.tlType;
    stream >> authSignInFunction.phoneNumber;
    stream >> authSignInFunction.phoneCodeHash;
    stream >> authSignInFunction.phoneCode;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLAuthSignUp &authSignUpFunction)
{
    // stream >> function.tlType;
    stream >> authSignUpFunction.phoneNumber;
    stream >> authSignUpFunction.phoneCodeHash;
    stream >> authSignUpFunction.phoneCode;
    stream >> authSignUpFunction.firstName;
    stream >> authSignUpFunction.lastName;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLBotsAnswerWebhookJSONQuery &botsAnswerWebhookJSONQueryFunction)
{
    // stream >> function.tlType;
    stream >> botsAnswerWebhookJSONQueryFunction.queryId;
    stream >> botsAnswerWebhookJSONQueryFunction.data;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLBotsSendCustomRequest &botsSendCustomRequestFunction)
{
    // stream >> function.tlType;
    stream >> botsSendCustomRequestFunction.customMethod;
    stream >> botsSendCustomRequestFunction.params;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsCheckUsername &channelsCheckUsernameFunction)
{
    // stream >> function.tlType;
    stream >> channelsCheckUsernameFunction.channel;
    stream >> channelsCheckUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsCreateChannel &channelsCreateChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsCreateChannelFunction.flags;
    // (channelsCreateChannelFunction.flags & 1 << 0) stands for broadcast "true" value
    // (channelsCreateChannelFunction.flags & 1 << 1) stands for megagroup "true" value
    stream >> channelsCreateChannelFunction.title;
    stream >> channelsCreateChannelFunction.about;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsDeleteChannel &channelsDeleteChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsDeleteHistory &channelsDeleteHistoryFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteHistoryFunction.channel;
    stream >> channelsDeleteHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsDeleteMessages &channelsDeleteMessagesFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteMessagesFunction.channel;
    stream >> channelsDeleteMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsDeleteUserHistory &channelsDeleteUserHistoryFunction)
{
    // stream >> function.tlType;
    stream >> channelsDeleteUserHistoryFunction.channel;
    stream >> channelsDeleteUserHistoryFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsEditAbout &channelsEditAboutFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditAboutFunction.channel;
    stream >> channelsEditAboutFunction.about;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsEditAdmin &channelsEditAdminFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditAdminFunction.channel;
    stream >> channelsEditAdminFunction.userId;
    stream >> channelsEditAdminFunction.adminRights;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsEditBanned &channelsEditBannedFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditBannedFunction.channel;
    stream >> channelsEditBannedFunction.userId;
    stream >> channelsEditBannedFunction.bannedRights;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsEditPhoto &channelsEditPhotoFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditPhotoFunction.channel;
    stream >> channelsEditPhotoFunction.photo;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsEditTitle &channelsEditTitleFunction)
{
    // stream >> function.tlType;
    stream >> channelsEditTitleFunction.channel;
    stream >> channelsEditTitleFunction.title;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsExportInvite &channelsExportInviteFunction)
{
    // stream >> function.tlType;
    stream >> channelsExportInviteFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsExportMessageLink &channelsExportMessageLinkFunction)
{
    // stream >> function.tlType;
    stream >> channelsExportMessageLinkFunction.channel;
    stream >> channelsExportMessageLinkFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetAdminLog &channelsGetAdminLogFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetAdminedPublicChannels &channelsGetAdminedPublicChannelsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(channelsGetAdminedPublicChannelsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetChannels &channelsGetChannelsFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetChannelsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetFullChannel &channelsGetFullChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetFullChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetMessages &channelsGetMessagesFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetMessagesFunction.channel;
    stream >> channelsGetMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetParticipant &channelsGetParticipantFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetParticipantFunction.channel;
    stream >> channelsGetParticipantFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsGetParticipants &channelsGetParticipantsFunction)
{
    // stream >> function.tlType;
    stream >> channelsGetParticipantsFunction.channel;
    stream >> channelsGetParticipantsFunction.filter;
    stream >> channelsGetParticipantsFunction.offset;
    stream >> channelsGetParticipantsFunction.limit;
    stream >> channelsGetParticipantsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsInviteToChannel &channelsInviteToChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsInviteToChannelFunction.channel;
    stream >> channelsInviteToChannelFunction.users;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsJoinChannel &channelsJoinChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsJoinChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsLeaveChannel &channelsLeaveChannelFunction)
{
    // stream >> function.tlType;
    stream >> channelsLeaveChannelFunction.channel;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsReadHistory &channelsReadHistoryFunction)
{
    // stream >> function.tlType;
    stream >> channelsReadHistoryFunction.channel;
    stream >> channelsReadHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsReadMessageContents &channelsReadMessageContentsFunction)
{
    // stream >> function.tlType;
    stream >> channelsReadMessageContentsFunction.channel;
    stream >> channelsReadMessageContentsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsReportSpam &channelsReportSpamFunction)
{
    // stream >> function.tlType;
    stream >> channelsReportSpamFunction.channel;
    stream >> channelsReportSpamFunction.userId;
    stream >> channelsReportSpamFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsSetStickers &channelsSetStickersFunction)
{
    // stream >> function.tlType;
    stream >> channelsSetStickersFunction.channel;
    stream >> channelsSetStickersFunction.stickerset;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsToggleInvites &channelsToggleInvitesFunction)
{
    // stream >> function.tlType;
    stream >> channelsToggleInvitesFunction.channel;
    stream >> channelsToggleInvitesFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsTogglePreHistoryHidden &channelsTogglePreHistoryHiddenFunction)
{
    // stream >> function.tlType;
    stream >> channelsTogglePreHistoryHiddenFunction.channel;
    stream >> channelsTogglePreHistoryHiddenFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsToggleSignatures &channelsToggleSignaturesFunction)
{
    // stream >> function.tlType;
    stream >> channelsToggleSignaturesFunction.channel;
    stream >> channelsToggleSignaturesFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsUpdatePinnedMessage &channelsUpdatePinnedMessageFunction)
{
    // stream >> function.tlType;
    stream >> channelsUpdatePinnedMessageFunction.flags;
    // (channelsUpdatePinnedMessageFunction.flags & 1 << 0) stands for silent "true" value
    stream >> channelsUpdatePinnedMessageFunction.channel;
    stream >> channelsUpdatePinnedMessageFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLChannelsUpdateUsername &channelsUpdateUsernameFunction)
{
    // stream >> function.tlType;
    stream >> channelsUpdateUsernameFunction.channel;
    stream >> channelsUpdateUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsBlock &contactsBlockFunction)
{
    // stream >> function.tlType;
    stream >> contactsBlockFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsDeleteContact &contactsDeleteContactFunction)
{
    // stream >> function.tlType;
    stream >> contactsDeleteContactFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsDeleteContacts &contactsDeleteContactsFunction)
{
    // stream >> function.tlType;
    stream >> contactsDeleteContactsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsExportCard &contactsExportCardFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(contactsExportCardFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsGetBlocked &contactsGetBlockedFunction)
{
    // stream >> function.tlType;
    stream >> contactsGetBlockedFunction.offset;
    stream >> contactsGetBlockedFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsGetContacts &contactsGetContactsFunction)
{
    // stream >> function.tlType;
    stream >> contactsGetContactsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsGetStatuses &contactsGetStatusesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(contactsGetStatusesFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsGetTopPeers &contactsGetTopPeersFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLContactsImportCard &contactsImportCardFunction)
{
    // stream >> function.tlType;
    stream >> contactsImportCardFunction.exportCard;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsImportContacts &contactsImportContactsFunction)
{
    // stream >> function.tlType;
    stream >> contactsImportContactsFunction.contacts;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsResetSaved &contactsResetSavedFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(contactsResetSavedFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsResetTopPeerRating &contactsResetTopPeerRatingFunction)
{
    // stream >> function.tlType;
    stream >> contactsResetTopPeerRatingFunction.category;
    stream >> contactsResetTopPeerRatingFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsResolveUsername &contactsResolveUsernameFunction)
{
    // stream >> function.tlType;
    stream >> contactsResolveUsernameFunction.username;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsSearch &contactsSearchFunction)
{
    // stream >> function.tlType;
    stream >> contactsSearchFunction.q;
    stream >> contactsSearchFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLContactsUnblock &contactsUnblockFunction)
{
    // stream >> function.tlType;
    stream >> contactsUnblockFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetAppChangelog &helpGetAppChangelogFunction)
{
    // stream >> function.tlType;
    stream >> helpGetAppChangelogFunction.prevAppVersion;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetAppUpdate &helpGetAppUpdateFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetAppUpdateFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetCdnConfig &helpGetCdnConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetCdnConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetConfig &helpGetConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetInviteText &helpGetInviteTextFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetInviteTextFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetNearestDc &helpGetNearestDcFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetNearestDcFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetRecentMeUrls &helpGetRecentMeUrlsFunction)
{
    // stream >> function.tlType;
    stream >> helpGetRecentMeUrlsFunction.referer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetSupport &helpGetSupportFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetSupportFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpGetTermsOfService &helpGetTermsOfServiceFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(helpGetTermsOfServiceFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpSaveAppLog &helpSaveAppLogFunction)
{
    // stream >> function.tlType;
    stream >> helpSaveAppLogFunction.events;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLHelpSetBotUpdatesStatus &helpSetBotUpdatesStatusFunction)
{
    // stream >> function.tlType;
    stream >> helpSetBotUpdatesStatusFunction.pendingUpdatesCount;
    stream >> helpSetBotUpdatesStatusFunction.message;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLLangpackGetDifference &langpackGetDifferenceFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetDifferenceFunction.fromVersion;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLLangpackGetLangPack &langpackGetLangPackFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetLangPackFunction.langCode;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLLangpackGetLanguages &langpackGetLanguagesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(langpackGetLanguagesFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLLangpackGetStrings &langpackGetStringsFunction)
{
    // stream >> function.tlType;
    stream >> langpackGetStringsFunction.langCode;
    stream >> langpackGetStringsFunction.keys;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesAcceptEncryption &messagesAcceptEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> messagesAcceptEncryptionFunction.peer;
    stream >> messagesAcceptEncryptionFunction.gB;
    stream >> messagesAcceptEncryptionFunction.keyFingerprint;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesAddChatUser &messagesAddChatUserFunction)
{
    // stream >> function.tlType;
    stream >> messagesAddChatUserFunction.chatId;
    stream >> messagesAddChatUserFunction.userId;
    stream >> messagesAddChatUserFunction.fwdLimit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesCheckChatInvite &messagesCheckChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> messagesCheckChatInviteFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesClearRecentStickers &messagesClearRecentStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesClearRecentStickersFunction.flags;
    // (messagesClearRecentStickersFunction.flags & 1 << 0) stands for attached "true" value
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesCreateChat &messagesCreateChatFunction)
{
    // stream >> function.tlType;
    stream >> messagesCreateChatFunction.users;
    stream >> messagesCreateChatFunction.title;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesDeleteChatUser &messagesDeleteChatUserFunction)
{
    // stream >> function.tlType;
    stream >> messagesDeleteChatUserFunction.chatId;
    stream >> messagesDeleteChatUserFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesDeleteHistory &messagesDeleteHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesDeleteHistoryFunction.flags;
    // (messagesDeleteHistoryFunction.flags & 1 << 0) stands for justClear "true" value
    stream >> messagesDeleteHistoryFunction.peer;
    stream >> messagesDeleteHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesDeleteMessages &messagesDeleteMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesDeleteMessagesFunction.flags;
    // (messagesDeleteMessagesFunction.flags & 1 << 0) stands for revoke "true" value
    stream >> messagesDeleteMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesDiscardEncryption &messagesDiscardEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> messagesDiscardEncryptionFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesEditChatAdmin &messagesEditChatAdminFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditChatAdminFunction.chatId;
    stream >> messagesEditChatAdminFunction.userId;
    stream >> messagesEditChatAdminFunction.isAdmin;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesEditChatPhoto &messagesEditChatPhotoFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditChatPhotoFunction.chatId;
    stream >> messagesEditChatPhotoFunction.photo;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesEditChatTitle &messagesEditChatTitleFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditChatTitleFunction.chatId;
    stream >> messagesEditChatTitleFunction.title;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesEditInlineBotMessage &messagesEditInlineBotMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditInlineBotMessageFunction.flags;
    // (messagesEditInlineBotMessageFunction.flags & 1 << 1) stands for noWebpage "true" value
    // (messagesEditInlineBotMessageFunction.flags & 1 << 12) stands for stopGeoLive "true" value
    stream >> messagesEditInlineBotMessageFunction.id;
    if (messagesEditInlineBotMessageFunction.flags & 1 << 11) {
        stream >> messagesEditInlineBotMessageFunction.message;
    }
    if (messagesEditInlineBotMessageFunction.flags & 1 << 2) {
        stream >> messagesEditInlineBotMessageFunction.replyMarkup;
    }
    if (messagesEditInlineBotMessageFunction.flags & 1 << 3) {
        stream >> messagesEditInlineBotMessageFunction.entities;
    }
    if (messagesEditInlineBotMessageFunction.flags & 1 << 13) {
        stream >> messagesEditInlineBotMessageFunction.geoPoint;
    }
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesEditMessage &messagesEditMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesEditMessageFunction.flags;
    // (messagesEditMessageFunction.flags & 1 << 1) stands for noWebpage "true" value
    // (messagesEditMessageFunction.flags & 1 << 12) stands for stopGeoLive "true" value
    stream >> messagesEditMessageFunction.peer;
    stream >> messagesEditMessageFunction.id;
    if (messagesEditMessageFunction.flags & 1 << 11) {
        stream >> messagesEditMessageFunction.message;
    }
    if (messagesEditMessageFunction.flags & 1 << 2) {
        stream >> messagesEditMessageFunction.replyMarkup;
    }
    if (messagesEditMessageFunction.flags & 1 << 3) {
        stream >> messagesEditMessageFunction.entities;
    }
    if (messagesEditMessageFunction.flags & 1 << 13) {
        stream >> messagesEditMessageFunction.geoPoint;
    }
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesExportChatInvite &messagesExportChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> messagesExportChatInviteFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesFaveSticker &messagesFaveStickerFunction)
{
    // stream >> function.tlType;
    stream >> messagesFaveStickerFunction.id;
    stream >> messagesFaveStickerFunction.unfave;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesForwardMessage &messagesForwardMessageFunction)
{
    // stream >> function.tlType;
    stream >> messagesForwardMessageFunction.peer;
    stream >> messagesForwardMessageFunction.id;
    stream >> messagesForwardMessageFunction.randomId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesForwardMessages &messagesForwardMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesForwardMessagesFunction.flags;
    // (messagesForwardMessagesFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesForwardMessagesFunction.flags & 1 << 6) stands for background "true" value
    // (messagesForwardMessagesFunction.flags & 1 << 8) stands for withMyScore "true" value
    stream >> messagesForwardMessagesFunction.fromPeer;
    stream >> messagesForwardMessagesFunction.id;
    stream >> messagesForwardMessagesFunction.randomId;
    stream >> messagesForwardMessagesFunction.toPeer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetAllChats &messagesGetAllChatsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetAllChatsFunction.exceptIds;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetAllDrafts &messagesGetAllDraftsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesGetAllDraftsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetAllStickers &messagesGetAllStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetAllStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetArchivedStickers &messagesGetArchivedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetArchivedStickersFunction.flags;
    // (messagesGetArchivedStickersFunction.flags & 1 << 0) stands for masks "true" value
    stream >> messagesGetArchivedStickersFunction.offsetId;
    stream >> messagesGetArchivedStickersFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetAttachedStickers &messagesGetAttachedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetAttachedStickersFunction.media;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetBotCallbackAnswer &messagesGetBotCallbackAnswerFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetChats &messagesGetChatsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetChatsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetCommonChats &messagesGetCommonChatsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetCommonChatsFunction.userId;
    stream >> messagesGetCommonChatsFunction.maxId;
    stream >> messagesGetCommonChatsFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetDhConfig &messagesGetDhConfigFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetDhConfigFunction.version;
    stream >> messagesGetDhConfigFunction.randomLength;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetDialogs &messagesGetDialogsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetDialogsFunction.flags;
    // (messagesGetDialogsFunction.flags & 1 << 0) stands for excludePinned "true" value
    stream >> messagesGetDialogsFunction.offsetDate;
    stream >> messagesGetDialogsFunction.offsetId;
    stream >> messagesGetDialogsFunction.offsetPeer;
    stream >> messagesGetDialogsFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetDocumentByHash &messagesGetDocumentByHashFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetDocumentByHashFunction.sha256;
    stream >> messagesGetDocumentByHashFunction.size;
    stream >> messagesGetDocumentByHashFunction.mimeType;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetFavedStickers &messagesGetFavedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetFavedStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetFeaturedStickers &messagesGetFeaturedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetFeaturedStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetFullChat &messagesGetFullChatFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetFullChatFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetGameHighScores &messagesGetGameHighScoresFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetGameHighScoresFunction.peer;
    stream >> messagesGetGameHighScoresFunction.id;
    stream >> messagesGetGameHighScoresFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetHistory &messagesGetHistoryFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetInlineBotResults &messagesGetInlineBotResultsFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetInlineGameHighScores &messagesGetInlineGameHighScoresFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetInlineGameHighScoresFunction.id;
    stream >> messagesGetInlineGameHighScoresFunction.userId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetMaskStickers &messagesGetMaskStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMaskStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetMessageEditData &messagesGetMessageEditDataFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMessageEditDataFunction.peer;
    stream >> messagesGetMessageEditDataFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetMessages &messagesGetMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMessagesFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetMessagesViews &messagesGetMessagesViewsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetMessagesViewsFunction.peer;
    stream >> messagesGetMessagesViewsFunction.id;
    stream >> messagesGetMessagesViewsFunction.increment;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetPeerDialogs &messagesGetPeerDialogsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetPeerDialogsFunction.peers;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetPeerSettings &messagesGetPeerSettingsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetPeerSettingsFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetPinnedDialogs &messagesGetPinnedDialogsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(messagesGetPinnedDialogsFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetRecentLocations &messagesGetRecentLocationsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetRecentLocationsFunction.peer;
    stream >> messagesGetRecentLocationsFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetRecentStickers &messagesGetRecentStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetRecentStickersFunction.flags;
    // (messagesGetRecentStickersFunction.flags & 1 << 0) stands for attached "true" value
    stream >> messagesGetRecentStickersFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetSavedGifs &messagesGetSavedGifsFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetSavedGifsFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetStickerSet &messagesGetStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetStickerSetFunction.stickerset;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetUnreadMentions &messagesGetUnreadMentionsFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetWebPage &messagesGetWebPageFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetWebPageFunction.url;
    stream >> messagesGetWebPageFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesGetWebPagePreview &messagesGetWebPagePreviewFunction)
{
    // stream >> function.tlType;
    stream >> messagesGetWebPagePreviewFunction.message;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesHideReportSpam &messagesHideReportSpamFunction)
{
    // stream >> function.tlType;
    stream >> messagesHideReportSpamFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesImportChatInvite &messagesImportChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> messagesImportChatInviteFunction.hash;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesInstallStickerSet &messagesInstallStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> messagesInstallStickerSetFunction.stickerset;
    stream >> messagesInstallStickerSetFunction.archived;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesMigrateChat &messagesMigrateChatFunction)
{
    // stream >> function.tlType;
    stream >> messagesMigrateChatFunction.chatId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReadEncryptedHistory &messagesReadEncryptedHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadEncryptedHistoryFunction.peer;
    stream >> messagesReadEncryptedHistoryFunction.maxDate;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReadFeaturedStickers &messagesReadFeaturedStickersFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadFeaturedStickersFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReadHistory &messagesReadHistoryFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadHistoryFunction.peer;
    stream >> messagesReadHistoryFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReadMentions &messagesReadMentionsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadMentionsFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReadMessageContents &messagesReadMessageContentsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReadMessageContentsFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReceivedMessages &messagesReceivedMessagesFunction)
{
    // stream >> function.tlType;
    stream >> messagesReceivedMessagesFunction.maxId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReceivedQueue &messagesReceivedQueueFunction)
{
    // stream >> function.tlType;
    stream >> messagesReceivedQueueFunction.maxQts;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReorderPinnedDialogs &messagesReorderPinnedDialogsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReorderPinnedDialogsFunction.flags;
    // (messagesReorderPinnedDialogsFunction.flags & 1 << 0) stands for force "true" value
    stream >> messagesReorderPinnedDialogsFunction.order;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReorderStickerSets &messagesReorderStickerSetsFunction)
{
    // stream >> function.tlType;
    stream >> messagesReorderStickerSetsFunction.flags;
    // (messagesReorderStickerSetsFunction.flags & 1 << 0) stands for masks "true" value
    stream >> messagesReorderStickerSetsFunction.order;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReportEncryptedSpam &messagesReportEncryptedSpamFunction)
{
    // stream >> function.tlType;
    stream >> messagesReportEncryptedSpamFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesReportSpam &messagesReportSpamFunction)
{
    // stream >> function.tlType;
    stream >> messagesReportSpamFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesRequestEncryption &messagesRequestEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> messagesRequestEncryptionFunction.userId;
    stream >> messagesRequestEncryptionFunction.randomId;
    stream >> messagesRequestEncryptionFunction.gA;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSaveDraft &messagesSaveDraftFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSaveGif &messagesSaveGifFunction)
{
    // stream >> function.tlType;
    stream >> messagesSaveGifFunction.id;
    stream >> messagesSaveGifFunction.unsave;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSaveRecentSticker &messagesSaveRecentStickerFunction)
{
    // stream >> function.tlType;
    stream >> messagesSaveRecentStickerFunction.flags;
    // (messagesSaveRecentStickerFunction.flags & 1 << 0) stands for attached "true" value
    stream >> messagesSaveRecentStickerFunction.id;
    stream >> messagesSaveRecentStickerFunction.unsave;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSearch &messagesSearchFunction)
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
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSearchGifs &messagesSearchGifsFunction)
{
    // stream >> function.tlType;
    stream >> messagesSearchGifsFunction.q;
    stream >> messagesSearchGifsFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSearchGlobal &messagesSearchGlobalFunction)
{
    // stream >> function.tlType;
    stream >> messagesSearchGlobalFunction.q;
    stream >> messagesSearchGlobalFunction.offsetDate;
    stream >> messagesSearchGlobalFunction.offsetPeer;
    stream >> messagesSearchGlobalFunction.offsetId;
    stream >> messagesSearchGlobalFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendEncrypted &messagesSendEncryptedFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendEncryptedFunction.peer;
    stream >> messagesSendEncryptedFunction.randomId;
    stream >> messagesSendEncryptedFunction.data;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendEncryptedFile &messagesSendEncryptedFileFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendEncryptedFileFunction.peer;
    stream >> messagesSendEncryptedFileFunction.randomId;
    stream >> messagesSendEncryptedFileFunction.data;
    stream >> messagesSendEncryptedFileFunction.file;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendEncryptedService &messagesSendEncryptedServiceFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendEncryptedServiceFunction.peer;
    stream >> messagesSendEncryptedServiceFunction.randomId;
    stream >> messagesSendEncryptedServiceFunction.data;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendInlineBotResult &messagesSendInlineBotResultFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendInlineBotResultFunction.flags;
    // (messagesSendInlineBotResultFunction.flags & 1 << 5) stands for silent "true" value
    // (messagesSendInlineBotResultFunction.flags & 1 << 6) stands for background "true" value
    // (messagesSendInlineBotResultFunction.flags & 1 << 7) stands for clearDraft "true" value
    stream >> messagesSendInlineBotResultFunction.peer;
    if (messagesSendInlineBotResultFunction.flags & 1 << 0) {
        stream >> messagesSendInlineBotResultFunction.replyToMsgId;
    }
    stream >> messagesSendInlineBotResultFunction.randomId;
    stream >> messagesSendInlineBotResultFunction.queryId;
    stream >> messagesSendInlineBotResultFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendMedia &messagesSendMediaFunction)
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
    stream >> messagesSendMediaFunction.randomId;
    if (messagesSendMediaFunction.flags & 1 << 2) {
        stream >> messagesSendMediaFunction.replyMarkup;
    }
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendMessage &messagesSendMessageFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSendScreenshotNotification &messagesSendScreenshotNotificationFunction)
{
    // stream >> function.tlType;
    stream >> messagesSendScreenshotNotificationFunction.peer;
    stream >> messagesSendScreenshotNotificationFunction.replyToMsgId;
    stream >> messagesSendScreenshotNotificationFunction.randomId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetBotCallbackAnswer &messagesSetBotCallbackAnswerFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetBotPrecheckoutResults &messagesSetBotPrecheckoutResultsFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetBotShippingResults &messagesSetBotShippingResultsFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetEncryptedTyping &messagesSetEncryptedTypingFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetEncryptedTypingFunction.peer;
    stream >> messagesSetEncryptedTypingFunction.typing;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetGameScore &messagesSetGameScoreFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetInlineBotResults &messagesSetInlineBotResultsFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetInlineGameScore &messagesSetInlineGameScoreFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesSetTyping &messagesSetTypingFunction)
{
    // stream >> function.tlType;
    stream >> messagesSetTypingFunction.peer;
    stream >> messagesSetTypingFunction.action;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesStartBot &messagesStartBotFunction)
{
    // stream >> function.tlType;
    stream >> messagesStartBotFunction.bot;
    stream >> messagesStartBotFunction.peer;
    stream >> messagesStartBotFunction.randomId;
    stream >> messagesStartBotFunction.startParam;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesToggleChatAdmins &messagesToggleChatAdminsFunction)
{
    // stream >> function.tlType;
    stream >> messagesToggleChatAdminsFunction.chatId;
    stream >> messagesToggleChatAdminsFunction.enabled;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesToggleDialogPin &messagesToggleDialogPinFunction)
{
    // stream >> function.tlType;
    stream >> messagesToggleDialogPinFunction.flags;
    // (messagesToggleDialogPinFunction.flags & 1 << 0) stands for pinned "true" value
    stream >> messagesToggleDialogPinFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesUninstallStickerSet &messagesUninstallStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> messagesUninstallStickerSetFunction.stickerset;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLMessagesUploadMedia &messagesUploadMediaFunction)
{
    // stream >> function.tlType;
    stream >> messagesUploadMediaFunction.peer;
    stream >> messagesUploadMediaFunction.media;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPaymentsClearSavedInfo &paymentsClearSavedInfoFunction)
{
    // stream >> function.tlType;
    stream >> paymentsClearSavedInfoFunction.flags;
    // (paymentsClearSavedInfoFunction.flags & 1 << 0) stands for credentials "true" value
    // (paymentsClearSavedInfoFunction.flags & 1 << 1) stands for info "true" value
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPaymentsGetPaymentForm &paymentsGetPaymentFormFunction)
{
    // stream >> function.tlType;
    stream >> paymentsGetPaymentFormFunction.msgId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPaymentsGetPaymentReceipt &paymentsGetPaymentReceiptFunction)
{
    // stream >> function.tlType;
    stream >> paymentsGetPaymentReceiptFunction.msgId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPaymentsGetSavedInfo &paymentsGetSavedInfoFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(paymentsGetSavedInfoFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPaymentsSendPaymentForm &paymentsSendPaymentFormFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLPaymentsValidateRequestedInfo &paymentsValidateRequestedInfoFunction)
{
    // stream >> function.tlType;
    stream >> paymentsValidateRequestedInfoFunction.flags;
    // (paymentsValidateRequestedInfoFunction.flags & 1 << 0) stands for save "true" value
    stream >> paymentsValidateRequestedInfoFunction.msgId;
    stream >> paymentsValidateRequestedInfoFunction.info;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneAcceptCall &phoneAcceptCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneAcceptCallFunction.peer;
    stream >> phoneAcceptCallFunction.gB;
    stream >> phoneAcceptCallFunction.protocol;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneConfirmCall &phoneConfirmCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneConfirmCallFunction.peer;
    stream >> phoneConfirmCallFunction.gA;
    stream >> phoneConfirmCallFunction.keyFingerprint;
    stream >> phoneConfirmCallFunction.protocol;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneDiscardCall &phoneDiscardCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneDiscardCallFunction.peer;
    stream >> phoneDiscardCallFunction.duration;
    stream >> phoneDiscardCallFunction.reason;
    stream >> phoneDiscardCallFunction.connectionId;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneGetCallConfig &phoneGetCallConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(phoneGetCallConfigFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneReceivedCall &phoneReceivedCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneReceivedCallFunction.peer;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneRequestCall &phoneRequestCallFunction)
{
    // stream >> function.tlType;
    stream >> phoneRequestCallFunction.userId;
    stream >> phoneRequestCallFunction.randomId;
    stream >> phoneRequestCallFunction.gAHash;
    stream >> phoneRequestCallFunction.protocol;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneSaveCallDebug &phoneSaveCallDebugFunction)
{
    // stream >> function.tlType;
    stream >> phoneSaveCallDebugFunction.peer;
    stream >> phoneSaveCallDebugFunction.debug;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhoneSetCallRating &phoneSetCallRatingFunction)
{
    // stream >> function.tlType;
    stream >> phoneSetCallRatingFunction.peer;
    stream >> phoneSetCallRatingFunction.rating;
    stream >> phoneSetCallRatingFunction.comment;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhotosDeletePhotos &photosDeletePhotosFunction)
{
    // stream >> function.tlType;
    stream >> photosDeletePhotosFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhotosGetUserPhotos &photosGetUserPhotosFunction)
{
    // stream >> function.tlType;
    stream >> photosGetUserPhotosFunction.userId;
    stream >> photosGetUserPhotosFunction.offset;
    stream >> photosGetUserPhotosFunction.maxId;
    stream >> photosGetUserPhotosFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhotosUpdateProfilePhoto &photosUpdateProfilePhotoFunction)
{
    // stream >> function.tlType;
    stream >> photosUpdateProfilePhotoFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLPhotosUploadProfilePhoto &photosUploadProfilePhotoFunction)
{
    // stream >> function.tlType;
    stream >> photosUploadProfilePhotoFunction.file;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLStickersAddStickerToSet &stickersAddStickerToSetFunction)
{
    // stream >> function.tlType;
    stream >> stickersAddStickerToSetFunction.stickerset;
    stream >> stickersAddStickerToSetFunction.sticker;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLStickersChangeStickerPosition &stickersChangeStickerPositionFunction)
{
    // stream >> function.tlType;
    stream >> stickersChangeStickerPositionFunction.sticker;
    stream >> stickersChangeStickerPositionFunction.position;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLStickersCreateStickerSet &stickersCreateStickerSetFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLStickersRemoveStickerFromSet &stickersRemoveStickerFromSetFunction)
{
    // stream >> function.tlType;
    stream >> stickersRemoveStickerFromSetFunction.sticker;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUpdatesGetChannelDifference &updatesGetChannelDifferenceFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLUpdatesGetDifference &updatesGetDifferenceFunction)
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

Stream &operator>>(Stream &stream, TLFunctions::TLUpdatesGetState &updatesGetStateFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(updatesGetStateFunction)
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadGetCdnFile &uploadGetCdnFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetCdnFileFunction.fileToken;
    stream >> uploadGetCdnFileFunction.offset;
    stream >> uploadGetCdnFileFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadGetCdnFileHashes &uploadGetCdnFileHashesFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetCdnFileHashesFunction.fileToken;
    stream >> uploadGetCdnFileHashesFunction.offset;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadGetFile &uploadGetFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetFileFunction.location;
    stream >> uploadGetFileFunction.offset;
    stream >> uploadGetFileFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadGetWebFile &uploadGetWebFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadGetWebFileFunction.location;
    stream >> uploadGetWebFileFunction.offset;
    stream >> uploadGetWebFileFunction.limit;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadReuploadCdnFile &uploadReuploadCdnFileFunction)
{
    // stream >> function.tlType;
    stream >> uploadReuploadCdnFileFunction.fileToken;
    stream >> uploadReuploadCdnFileFunction.requestToken;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadSaveBigFilePart &uploadSaveBigFilePartFunction)
{
    // stream >> function.tlType;
    stream >> uploadSaveBigFilePartFunction.fileId;
    stream >> uploadSaveBigFilePartFunction.filePart;
    stream >> uploadSaveBigFilePartFunction.fileTotalParts;
    stream >> uploadSaveBigFilePartFunction.bytes;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUploadSaveFilePart &uploadSaveFilePartFunction)
{
    // stream >> function.tlType;
    stream >> uploadSaveFilePartFunction.fileId;
    stream >> uploadSaveFilePartFunction.filePart;
    stream >> uploadSaveFilePartFunction.bytes;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUsersGetFullUser &usersGetFullUserFunction)
{
    // stream >> function.tlType;
    stream >> usersGetFullUserFunction.id;
    return stream;
}

Stream &operator>>(Stream &stream, TLFunctions::TLUsersGetUsers &usersGetUsersFunction)
{
    // stream >> function.tlType;
    stream >> usersGetUsersFunction.id;
    return stream;
}
// End of generated write operators

} // MTProto namespace

} // Telegram namespace
