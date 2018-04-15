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
#include "CTelegramStream_p.hpp"
#include "CTelegramStreamExtraOperators.hpp"

// TODO: Generate templates instancing
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLAuthorization> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLWallPaper> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactBlocked> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactStatus> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactSuggested> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLImportedContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChat> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPeer> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDcOption> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDisabledFeature> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessageEntity> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUpdate> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLStickerSet> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDialog> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDocumentAttribute> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessageGroup> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLBotInlineResult> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDocument> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLStickerPack> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLReceivedNotifyMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLFoundGif> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLEncryptedMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLBotCommand> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChatParticipant> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLKeyboardButton> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPhotoSize> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessageRange> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLKeyboardButtonRow> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChannelParticipant> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLBotInfo> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPhoto> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputChannel> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputAppEvent> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputBotInlineResult> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputPhoto> &v);

template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLContactStatus> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLReceivedNotifyMessage> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLWallPaper> &v);

namespace Telegram {

// Generated write operators
CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountChangePhone &changePhoneFunction)
{
    // stream >> function.tlType;
    stream >> changePhoneFunction.phoneNumber;
    stream >> changePhoneFunction.phoneCodeHash;
    stream >> changePhoneFunction.phoneCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountCheckUsername &checkUsernameFunction)
{
    // stream >> function.tlType;
    stream >> checkUsernameFunction.username;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountDeleteAccount &deleteAccountFunction)
{
    // stream >> function.tlType;
    stream >> deleteAccountFunction.reason;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetAccountTTL &getAccountTTLFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getAccountTTLFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetAuthorizations &getAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getAuthorizationsFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetNotifySettings &getNotifySettingsFunction)
{
    // stream >> function.tlType;
    stream >> getNotifySettingsFunction.peer;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetPassword &getPasswordFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getPasswordFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetPasswordSettings &getPasswordSettingsFunction)
{
    // stream >> function.tlType;
    stream >> getPasswordSettingsFunction.currentPasswordHash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetPrivacy &getPrivacyFunction)
{
    // stream >> function.tlType;
    stream >> getPrivacyFunction.key;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountGetWallPapers &getWallPapersFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getWallPapersFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountRegisterDevice &registerDeviceFunction)
{
    // stream >> function.tlType;
    stream >> registerDeviceFunction.tokenType;
    stream >> registerDeviceFunction.token;
    stream >> registerDeviceFunction.deviceModel;
    stream >> registerDeviceFunction.systemVersion;
    stream >> registerDeviceFunction.appVersion;
    stream >> registerDeviceFunction.appSandbox;
    stream >> registerDeviceFunction.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountReportPeer &reportPeerFunction)
{
    // stream >> function.tlType;
    stream >> reportPeerFunction.peer;
    stream >> reportPeerFunction.reason;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountResetAuthorization &resetAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> resetAuthorizationFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountResetNotifySettings &resetNotifySettingsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(resetNotifySettingsFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountSendChangePhoneCode &sendChangePhoneCodeFunction)
{
    // stream >> function.tlType;
    stream >> sendChangePhoneCodeFunction.phoneNumber;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountSetAccountTTL &setAccountTTLFunction)
{
    // stream >> function.tlType;
    stream >> setAccountTTLFunction.ttl;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountSetPrivacy &setPrivacyFunction)
{
    // stream >> function.tlType;
    stream >> setPrivacyFunction.key;
    stream >> setPrivacyFunction.rules;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUnregisterDevice &unregisterDeviceFunction)
{
    // stream >> function.tlType;
    stream >> unregisterDeviceFunction.tokenType;
    stream >> unregisterDeviceFunction.token;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUpdateDeviceLocked &updateDeviceLockedFunction)
{
    // stream >> function.tlType;
    stream >> updateDeviceLockedFunction.period;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUpdateNotifySettings &updateNotifySettingsFunction)
{
    // stream >> function.tlType;
    stream >> updateNotifySettingsFunction.peer;
    stream >> updateNotifySettingsFunction.settings;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUpdatePasswordSettings &updatePasswordSettingsFunction)
{
    // stream >> function.tlType;
    stream >> updatePasswordSettingsFunction.currentPasswordHash;
    stream >> updatePasswordSettingsFunction.newSettings;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUpdateProfile &updateProfileFunction)
{
    // stream >> function.tlType;
    stream >> updateProfileFunction.firstName;
    stream >> updateProfileFunction.lastName;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUpdateStatus &updateStatusFunction)
{
    // stream >> function.tlType;
    stream >> updateStatusFunction.offline;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAccountUpdateUsername &updateUsernameFunction)
{
    // stream >> function.tlType;
    stream >> updateUsernameFunction.username;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthBindTempAuthKey &bindTempAuthKeyFunction)
{
    // stream >> function.tlType;
    stream >> bindTempAuthKeyFunction.permAuthKeyId;
    stream >> bindTempAuthKeyFunction.nonce;
    stream >> bindTempAuthKeyFunction.expiresAt;
    stream >> bindTempAuthKeyFunction.encryptedMessage;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthCheckPassword &checkPasswordFunction)
{
    // stream >> function.tlType;
    stream >> checkPasswordFunction.passwordHash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthCheckPhone &checkPhoneFunction)
{
    // stream >> function.tlType;
    stream >> checkPhoneFunction.phoneNumber;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthExportAuthorization &exportAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> exportAuthorizationFunction.dcId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthImportAuthorization &importAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> importAuthorizationFunction.id;
    stream >> importAuthorizationFunction.bytes;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthImportBotAuthorization &importBotAuthorizationFunction)
{
    // stream >> function.tlType;
    stream >> importBotAuthorizationFunction.flags;
    stream >> importBotAuthorizationFunction.apiId;
    stream >> importBotAuthorizationFunction.apiHash;
    stream >> importBotAuthorizationFunction.botAuthToken;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthLogOut &logOutFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(logOutFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthRecoverPassword &recoverPasswordFunction)
{
    // stream >> function.tlType;
    stream >> recoverPasswordFunction.code;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthRequestPasswordRecovery &requestPasswordRecoveryFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(requestPasswordRecoveryFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthResetAuthorizations &resetAuthorizationsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(resetAuthorizationsFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSendCall &sendCallFunction)
{
    // stream >> function.tlType;
    stream >> sendCallFunction.phoneNumber;
    stream >> sendCallFunction.phoneCodeHash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSendCode &sendCodeFunction)
{
    // stream >> function.tlType;
    stream >> sendCodeFunction.phoneNumber;
    stream >> sendCodeFunction.smsType;
    stream >> sendCodeFunction.apiId;
    stream >> sendCodeFunction.apiHash;
    stream >> sendCodeFunction.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSendInvites &sendInvitesFunction)
{
    // stream >> function.tlType;
    stream >> sendInvitesFunction.phoneNumbers;
    stream >> sendInvitesFunction.message;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSendSms &sendSmsFunction)
{
    // stream >> function.tlType;
    stream >> sendSmsFunction.phoneNumber;
    stream >> sendSmsFunction.phoneCodeHash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSignIn &signInFunction)
{
    // stream >> function.tlType;
    stream >> signInFunction.phoneNumber;
    stream >> signInFunction.phoneCodeHash;
    stream >> signInFunction.phoneCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSignUp &signUpFunction)
{
    // stream >> function.tlType;
    stream >> signUpFunction.phoneNumber;
    stream >> signUpFunction.phoneCodeHash;
    stream >> signUpFunction.phoneCode;
    stream >> signUpFunction.firstName;
    stream >> signUpFunction.lastName;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsCheckUsername &checkUsernameFunction)
{
    // stream >> function.tlType;
    stream >> checkUsernameFunction.channel;
    stream >> checkUsernameFunction.username;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsCreateChannel &createChannelFunction)
{
    // stream >> function.tlType;
    stream >> createChannelFunction.flags;
    // (createChannelFunction.flags & 1 << 0) stands for broadcast "true" value
    // (createChannelFunction.flags & 1 << 1) stands for megagroup "true" value
    stream >> createChannelFunction.title;
    stream >> createChannelFunction.about;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsDeleteChannel &deleteChannelFunction)
{
    // stream >> function.tlType;
    stream >> deleteChannelFunction.channel;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsDeleteMessages &deleteMessagesFunction)
{
    // stream >> function.tlType;
    stream >> deleteMessagesFunction.channel;
    stream >> deleteMessagesFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsDeleteUserHistory &deleteUserHistoryFunction)
{
    // stream >> function.tlType;
    stream >> deleteUserHistoryFunction.channel;
    stream >> deleteUserHistoryFunction.userId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsEditAbout &editAboutFunction)
{
    // stream >> function.tlType;
    stream >> editAboutFunction.channel;
    stream >> editAboutFunction.about;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsEditAdmin &editAdminFunction)
{
    // stream >> function.tlType;
    stream >> editAdminFunction.channel;
    stream >> editAdminFunction.userId;
    stream >> editAdminFunction.role;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsEditPhoto &editPhotoFunction)
{
    // stream >> function.tlType;
    stream >> editPhotoFunction.channel;
    stream >> editPhotoFunction.photo;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsEditTitle &editTitleFunction)
{
    // stream >> function.tlType;
    stream >> editTitleFunction.channel;
    stream >> editTitleFunction.title;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsExportInvite &exportInviteFunction)
{
    // stream >> function.tlType;
    stream >> exportInviteFunction.channel;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetChannels &getChannelsFunction)
{
    // stream >> function.tlType;
    stream >> getChannelsFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetDialogs &getDialogsFunction)
{
    // stream >> function.tlType;
    stream >> getDialogsFunction.offset;
    stream >> getDialogsFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetFullChannel &getFullChannelFunction)
{
    // stream >> function.tlType;
    stream >> getFullChannelFunction.channel;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetImportantHistory &getImportantHistoryFunction)
{
    // stream >> function.tlType;
    stream >> getImportantHistoryFunction.channel;
    stream >> getImportantHistoryFunction.offsetId;
    stream >> getImportantHistoryFunction.addOffset;
    stream >> getImportantHistoryFunction.limit;
    stream >> getImportantHistoryFunction.maxId;
    stream >> getImportantHistoryFunction.minId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetMessages &getMessagesFunction)
{
    // stream >> function.tlType;
    stream >> getMessagesFunction.channel;
    stream >> getMessagesFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetParticipant &getParticipantFunction)
{
    // stream >> function.tlType;
    stream >> getParticipantFunction.channel;
    stream >> getParticipantFunction.userId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsGetParticipants &getParticipantsFunction)
{
    // stream >> function.tlType;
    stream >> getParticipantsFunction.channel;
    stream >> getParticipantsFunction.filter;
    stream >> getParticipantsFunction.offset;
    stream >> getParticipantsFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsInviteToChannel &inviteToChannelFunction)
{
    // stream >> function.tlType;
    stream >> inviteToChannelFunction.channel;
    stream >> inviteToChannelFunction.users;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsJoinChannel &joinChannelFunction)
{
    // stream >> function.tlType;
    stream >> joinChannelFunction.channel;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsKickFromChannel &kickFromChannelFunction)
{
    // stream >> function.tlType;
    stream >> kickFromChannelFunction.channel;
    stream >> kickFromChannelFunction.userId;
    stream >> kickFromChannelFunction.kicked;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsLeaveChannel &leaveChannelFunction)
{
    // stream >> function.tlType;
    stream >> leaveChannelFunction.channel;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsReadHistory &readHistoryFunction)
{
    // stream >> function.tlType;
    stream >> readHistoryFunction.channel;
    stream >> readHistoryFunction.maxId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsReportSpam &reportSpamFunction)
{
    // stream >> function.tlType;
    stream >> reportSpamFunction.channel;
    stream >> reportSpamFunction.userId;
    stream >> reportSpamFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsToggleComments &toggleCommentsFunction)
{
    // stream >> function.tlType;
    stream >> toggleCommentsFunction.channel;
    stream >> toggleCommentsFunction.enabled;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLChannelsUpdateUsername &updateUsernameFunction)
{
    // stream >> function.tlType;
    stream >> updateUsernameFunction.channel;
    stream >> updateUsernameFunction.username;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsBlock &blockFunction)
{
    // stream >> function.tlType;
    stream >> blockFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsDeleteContact &deleteContactFunction)
{
    // stream >> function.tlType;
    stream >> deleteContactFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsDeleteContacts &deleteContactsFunction)
{
    // stream >> function.tlType;
    stream >> deleteContactsFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsExportCard &exportCardFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(exportCardFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsGetBlocked &getBlockedFunction)
{
    // stream >> function.tlType;
    stream >> getBlockedFunction.offset;
    stream >> getBlockedFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsGetContacts &getContactsFunction)
{
    // stream >> function.tlType;
    stream >> getContactsFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsGetStatuses &getStatusesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getStatusesFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsGetSuggested &getSuggestedFunction)
{
    // stream >> function.tlType;
    stream >> getSuggestedFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsImportCard &importCardFunction)
{
    // stream >> function.tlType;
    stream >> importCardFunction.exportCard;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsImportContacts &importContactsFunction)
{
    // stream >> function.tlType;
    stream >> importContactsFunction.contacts;
    stream >> importContactsFunction.replace;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsResolveUsername &resolveUsernameFunction)
{
    // stream >> function.tlType;
    stream >> resolveUsernameFunction.username;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsSearch &searchFunction)
{
    // stream >> function.tlType;
    stream >> searchFunction.q;
    stream >> searchFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLContactsUnblock &unblockFunction)
{
    // stream >> function.tlType;
    stream >> unblockFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetAppChangelog &getAppChangelogFunction)
{
    // stream >> function.tlType;
    stream >> getAppChangelogFunction.deviceModel;
    stream >> getAppChangelogFunction.systemVersion;
    stream >> getAppChangelogFunction.appVersion;
    stream >> getAppChangelogFunction.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetAppUpdate &getAppUpdateFunction)
{
    // stream >> function.tlType;
    stream >> getAppUpdateFunction.deviceModel;
    stream >> getAppUpdateFunction.systemVersion;
    stream >> getAppUpdateFunction.appVersion;
    stream >> getAppUpdateFunction.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetConfig &getConfigFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getConfigFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetInviteText &getInviteTextFunction)
{
    // stream >> function.tlType;
    stream >> getInviteTextFunction.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetNearestDc &getNearestDcFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getNearestDcFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetSupport &getSupportFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getSupportFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpGetTermsOfService &getTermsOfServiceFunction)
{
    // stream >> function.tlType;
    stream >> getTermsOfServiceFunction.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLHelpSaveAppLog &saveAppLogFunction)
{
    // stream >> function.tlType;
    stream >> saveAppLogFunction.events;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLInitConnection &connectionFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(connectionFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLInvokeAfterMsg &afterMsgFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(afterMsgFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLInvokeAfterMsgs &afterMsgsFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(afterMsgsFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLInvokeWithLayer &withLayerFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(withLayerFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLInvokeWithoutUpdates &withoutUpdatesFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(withoutUpdatesFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesAcceptEncryption &acceptEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> acceptEncryptionFunction.peer;
    stream >> acceptEncryptionFunction.gB;
    stream >> acceptEncryptionFunction.keyFingerprint;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesAddChatUser &addChatUserFunction)
{
    // stream >> function.tlType;
    stream >> addChatUserFunction.chatId;
    stream >> addChatUserFunction.userId;
    stream >> addChatUserFunction.fwdLimit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesCheckChatInvite &checkChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> checkChatInviteFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesCreateChat &createChatFunction)
{
    // stream >> function.tlType;
    stream >> createChatFunction.users;
    stream >> createChatFunction.title;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesDeleteChatUser &deleteChatUserFunction)
{
    // stream >> function.tlType;
    stream >> deleteChatUserFunction.chatId;
    stream >> deleteChatUserFunction.userId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesDeleteHistory &deleteHistoryFunction)
{
    // stream >> function.tlType;
    stream >> deleteHistoryFunction.peer;
    stream >> deleteHistoryFunction.maxId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesDeleteMessages &deleteMessagesFunction)
{
    // stream >> function.tlType;
    stream >> deleteMessagesFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesDiscardEncryption &discardEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> discardEncryptionFunction.chatId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesEditChatAdmin &editChatAdminFunction)
{
    // stream >> function.tlType;
    stream >> editChatAdminFunction.chatId;
    stream >> editChatAdminFunction.userId;
    stream >> editChatAdminFunction.isAdmin;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesEditChatPhoto &editChatPhotoFunction)
{
    // stream >> function.tlType;
    stream >> editChatPhotoFunction.chatId;
    stream >> editChatPhotoFunction.photo;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesEditChatTitle &editChatTitleFunction)
{
    // stream >> function.tlType;
    stream >> editChatTitleFunction.chatId;
    stream >> editChatTitleFunction.title;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesExportChatInvite &exportChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> exportChatInviteFunction.chatId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesForwardMessage &forwardMessageFunction)
{
    // stream >> function.tlType;
    stream >> forwardMessageFunction.peer;
    stream >> forwardMessageFunction.id;
    stream >> forwardMessageFunction.randomId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesForwardMessages &forwardMessagesFunction)
{
    // stream >> function.tlType;
    stream >> forwardMessagesFunction.flags;
    // (forwardMessagesFunction.flags & 1 << 4) stands for broadcast "true" value
    stream >> forwardMessagesFunction.fromPeer;
    stream >> forwardMessagesFunction.id;
    stream >> forwardMessagesFunction.randomId;
    stream >> forwardMessagesFunction.toPeer;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetAllStickers &getAllStickersFunction)
{
    // stream >> function.tlType;
    stream >> getAllStickersFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetChats &getChatsFunction)
{
    // stream >> function.tlType;
    stream >> getChatsFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetDhConfig &getDhConfigFunction)
{
    // stream >> function.tlType;
    stream >> getDhConfigFunction.version;
    stream >> getDhConfigFunction.randomLength;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetDialogs &getDialogsFunction)
{
    // stream >> function.tlType;
    stream >> getDialogsFunction.offsetDate;
    stream >> getDialogsFunction.offsetId;
    stream >> getDialogsFunction.offsetPeer;
    stream >> getDialogsFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetDocumentByHash &getDocumentByHashFunction)
{
    // stream >> function.tlType;
    stream >> getDocumentByHashFunction.sha256;
    stream >> getDocumentByHashFunction.size;
    stream >> getDocumentByHashFunction.mimeType;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetFullChat &getFullChatFunction)
{
    // stream >> function.tlType;
    stream >> getFullChatFunction.chatId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetHistory &getHistoryFunction)
{
    // stream >> function.tlType;
    stream >> getHistoryFunction.peer;
    stream >> getHistoryFunction.offsetId;
    stream >> getHistoryFunction.addOffset;
    stream >> getHistoryFunction.limit;
    stream >> getHistoryFunction.maxId;
    stream >> getHistoryFunction.minId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetInlineBotResults &getInlineBotResultsFunction)
{
    // stream >> function.tlType;
    stream >> getInlineBotResultsFunction.bot;
    stream >> getInlineBotResultsFunction.query;
    stream >> getInlineBotResultsFunction.offset;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetMessages &getMessagesFunction)
{
    // stream >> function.tlType;
    stream >> getMessagesFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetMessagesViews &getMessagesViewsFunction)
{
    // stream >> function.tlType;
    stream >> getMessagesViewsFunction.peer;
    stream >> getMessagesViewsFunction.id;
    stream >> getMessagesViewsFunction.increment;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetSavedGifs &getSavedGifsFunction)
{
    // stream >> function.tlType;
    stream >> getSavedGifsFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetStickerSet &getStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> getStickerSetFunction.stickerset;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetStickers &getStickersFunction)
{
    // stream >> function.tlType;
    stream >> getStickersFunction.emoticon;
    stream >> getStickersFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesGetWebPagePreview &getWebPagePreviewFunction)
{
    // stream >> function.tlType;
    stream >> getWebPagePreviewFunction.message;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesImportChatInvite &importChatInviteFunction)
{
    // stream >> function.tlType;
    stream >> importChatInviteFunction.hash;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesInstallStickerSet &installStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> installStickerSetFunction.stickerset;
    stream >> installStickerSetFunction.disabled;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesMigrateChat &migrateChatFunction)
{
    // stream >> function.tlType;
    stream >> migrateChatFunction.chatId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReadEncryptedHistory &readEncryptedHistoryFunction)
{
    // stream >> function.tlType;
    stream >> readEncryptedHistoryFunction.peer;
    stream >> readEncryptedHistoryFunction.maxDate;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReadHistory &readHistoryFunction)
{
    // stream >> function.tlType;
    stream >> readHistoryFunction.peer;
    stream >> readHistoryFunction.maxId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReadMessageContents &readMessageContentsFunction)
{
    // stream >> function.tlType;
    stream >> readMessageContentsFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReceivedMessages &receivedMessagesFunction)
{
    // stream >> function.tlType;
    stream >> receivedMessagesFunction.maxId;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReceivedQueue &receivedQueueFunction)
{
    // stream >> function.tlType;
    stream >> receivedQueueFunction.maxQts;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReorderStickerSets &reorderStickerSetsFunction)
{
    // stream >> function.tlType;
    stream >> reorderStickerSetsFunction.order;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesReportSpam &reportSpamFunction)
{
    // stream >> function.tlType;
    stream >> reportSpamFunction.peer;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesRequestEncryption &requestEncryptionFunction)
{
    // stream >> function.tlType;
    stream >> requestEncryptionFunction.userId;
    stream >> requestEncryptionFunction.randomId;
    stream >> requestEncryptionFunction.gA;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSaveGif &saveGifFunction)
{
    // stream >> function.tlType;
    stream >> saveGifFunction.id;
    stream >> saveGifFunction.unsave;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSearch &searchFunction)
{
    // stream >> function.tlType;
    stream >> searchFunction.flags;
    // (searchFunction.flags & 1 << 0) stands for importantOnly "true" value
    stream >> searchFunction.peer;
    stream >> searchFunction.q;
    stream >> searchFunction.filter;
    stream >> searchFunction.minDate;
    stream >> searchFunction.maxDate;
    stream >> searchFunction.offset;
    stream >> searchFunction.maxId;
    stream >> searchFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSearchGifs &searchGifsFunction)
{
    // stream >> function.tlType;
    stream >> searchGifsFunction.q;
    stream >> searchGifsFunction.offset;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSearchGlobal &searchGlobalFunction)
{
    // stream >> function.tlType;
    stream >> searchGlobalFunction.q;
    stream >> searchGlobalFunction.offsetDate;
    stream >> searchGlobalFunction.offsetPeer;
    stream >> searchGlobalFunction.offsetId;
    stream >> searchGlobalFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendBroadcast &sendBroadcastFunction)
{
    // stream >> function.tlType;
    stream >> sendBroadcastFunction.contacts;
    stream >> sendBroadcastFunction.randomId;
    stream >> sendBroadcastFunction.message;
    stream >> sendBroadcastFunction.media;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendEncrypted &sendEncryptedFunction)
{
    // stream >> function.tlType;
    stream >> sendEncryptedFunction.peer;
    stream >> sendEncryptedFunction.randomId;
    stream >> sendEncryptedFunction.data;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendEncryptedFile &sendEncryptedFileFunction)
{
    // stream >> function.tlType;
    stream >> sendEncryptedFileFunction.peer;
    stream >> sendEncryptedFileFunction.randomId;
    stream >> sendEncryptedFileFunction.data;
    stream >> sendEncryptedFileFunction.file;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendEncryptedService &sendEncryptedServiceFunction)
{
    // stream >> function.tlType;
    stream >> sendEncryptedServiceFunction.peer;
    stream >> sendEncryptedServiceFunction.randomId;
    stream >> sendEncryptedServiceFunction.data;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendInlineBotResult &sendInlineBotResultFunction)
{
    // stream >> function.tlType;
    stream >> sendInlineBotResultFunction.flags;
    // (sendInlineBotResultFunction.flags & 1 << 4) stands for broadcast "true" value
    stream >> sendInlineBotResultFunction.peer;
    if (sendInlineBotResultFunction.flags & 1 << 0) {
        stream >> sendInlineBotResultFunction.replyToMsgId;
    }
    stream >> sendInlineBotResultFunction.randomId;
    stream >> sendInlineBotResultFunction.queryId;
    stream >> sendInlineBotResultFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendMedia &sendMediaFunction)
{
    // stream >> function.tlType;
    stream >> sendMediaFunction.flags;
    // (sendMediaFunction.flags & 1 << 4) stands for broadcast "true" value
    stream >> sendMediaFunction.peer;
    if (sendMediaFunction.flags & 1 << 0) {
        stream >> sendMediaFunction.replyToMsgId;
    }
    stream >> sendMediaFunction.media;
    stream >> sendMediaFunction.randomId;
    if (sendMediaFunction.flags & 1 << 2) {
        stream >> sendMediaFunction.replyMarkup;
    }
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSendMessage &sendMessageFunction)
{
    // stream >> function.tlType;
    stream >> sendMessageFunction.flags;
    // (sendMessageFunction.flags & 1 << 1) stands for noWebpage "true" value
    // (sendMessageFunction.flags & 1 << 4) stands for broadcast "true" value
    stream >> sendMessageFunction.peer;
    if (sendMessageFunction.flags & 1 << 0) {
        stream >> sendMessageFunction.replyToMsgId;
    }
    stream >> sendMessageFunction.message;
    stream >> sendMessageFunction.randomId;
    if (sendMessageFunction.flags & 1 << 2) {
        stream >> sendMessageFunction.replyMarkup;
    }
    if (sendMessageFunction.flags & 1 << 3) {
        stream >> sendMessageFunction.entities;
    }
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSetEncryptedTyping &setEncryptedTypingFunction)
{
    // stream >> function.tlType;
    stream >> setEncryptedTypingFunction.peer;
    stream >> setEncryptedTypingFunction.typing;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSetInlineBotResults &setInlineBotResultsFunction)
{
    // stream >> function.tlType;
    stream >> setInlineBotResultsFunction.flags;
    // (setInlineBotResultsFunction.flags & 1 << 0) stands for gallery "true" value
    // (setInlineBotResultsFunction.flags & 1 << 1) stands for isPrivate "true" value
    stream >> setInlineBotResultsFunction.queryId;
    stream >> setInlineBotResultsFunction.results;
    stream >> setInlineBotResultsFunction.cacheTime;
    if (setInlineBotResultsFunction.flags & 1 << 2) {
        stream >> setInlineBotResultsFunction.nextOffset;
    }
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesSetTyping &setTypingFunction)
{
    // stream >> function.tlType;
    stream >> setTypingFunction.peer;
    stream >> setTypingFunction.action;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesStartBot &startBotFunction)
{
    // stream >> function.tlType;
    stream >> startBotFunction.bot;
    stream >> startBotFunction.peer;
    stream >> startBotFunction.randomId;
    stream >> startBotFunction.startParam;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesToggleChatAdmins &toggleChatAdminsFunction)
{
    // stream >> function.tlType;
    stream >> toggleChatAdminsFunction.chatId;
    stream >> toggleChatAdminsFunction.enabled;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLMessagesUninstallStickerSet &uninstallStickerSetFunction)
{
    // stream >> function.tlType;
    stream >> uninstallStickerSetFunction.stickerset;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLPhotosDeletePhotos &deletePhotosFunction)
{
    // stream >> function.tlType;
    stream >> deletePhotosFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLPhotosGetUserPhotos &getUserPhotosFunction)
{
    // stream >> function.tlType;
    stream >> getUserPhotosFunction.userId;
    stream >> getUserPhotosFunction.offset;
    stream >> getUserPhotosFunction.maxId;
    stream >> getUserPhotosFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLPhotosUpdateProfilePhoto &updateProfilePhotoFunction)
{
    // stream >> function.tlType;
    stream >> updateProfilePhotoFunction.id;
    stream >> updateProfilePhotoFunction.crop;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLPhotosUploadProfilePhoto &uploadProfilePhotoFunction)
{
    // stream >> function.tlType;
    stream >> uploadProfilePhotoFunction.file;
    stream >> uploadProfilePhotoFunction.caption;
    stream >> uploadProfilePhotoFunction.geoPoint;
    stream >> uploadProfilePhotoFunction.crop;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUpdatesGetChannelDifference &getChannelDifferenceFunction)
{
    // stream >> function.tlType;
    stream >> getChannelDifferenceFunction.channel;
    stream >> getChannelDifferenceFunction.filter;
    stream >> getChannelDifferenceFunction.pts;
    stream >> getChannelDifferenceFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUpdatesGetDifference &getDifferenceFunction)
{
    // stream >> function.tlType;
    stream >> getDifferenceFunction.pts;
    stream >> getDifferenceFunction.date;
    stream >> getDifferenceFunction.qts;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUpdatesGetState &getStateFunction)
{
    // stream >> function.tlType;
    Q_UNUSED(getStateFunction)
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUploadGetFile &getFileFunction)
{
    // stream >> function.tlType;
    stream >> getFileFunction.location;
    stream >> getFileFunction.offset;
    stream >> getFileFunction.limit;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUploadSaveBigFilePart &saveBigFilePartFunction)
{
    // stream >> function.tlType;
    stream >> saveBigFilePartFunction.fileId;
    stream >> saveBigFilePartFunction.filePart;
    stream >> saveBigFilePartFunction.fileTotalParts;
    stream >> saveBigFilePartFunction.bytes;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUploadSaveFilePart &saveFilePartFunction)
{
    // stream >> function.tlType;
    stream >> saveFilePartFunction.fileId;
    stream >> saveFilePartFunction.filePart;
    stream >> saveFilePartFunction.bytes;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUsersGetFullUser &getFullUserFunction)
{
    // stream >> function.tlType;
    stream >> getFullUserFunction.id;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLUsersGetUsers &getUsersFunction)
{
    // stream >> function.tlType;
    stream >> getUsersFunction.id;
    return stream;
}
// End of generated write operators

} // Telegram
