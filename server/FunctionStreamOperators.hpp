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

#ifndef TELEGRAM_SERVER_FUNCTION_STREAM_OPERATORS_HPP
#define TELEGRAM_SERVER_FUNCTION_STREAM_OPERATORS_HPP

#include "TLFunctions.hpp"

class CTelegramStream;

namespace Telegram {

using namespace TLFunctions;

// Generated write operators
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountChangePhone &changePhoneFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountCheckUsername &checkUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountDeleteAccount &deleteAccountFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetAccountTTL &getAccountTTLFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetAuthorizations &getAuthorizationsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetNotifySettings &getNotifySettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetPassword &getPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetPasswordSettings &getPasswordSettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetPrivacy &getPrivacyFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetWallPapers &getWallPapersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountRegisterDevice &registerDeviceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountReportPeer &reportPeerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountResetAuthorization &resetAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountResetNotifySettings &resetNotifySettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSendChangePhoneCode &sendChangePhoneCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSetAccountTTL &setAccountTTLFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSetPrivacy &setPrivacyFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUnregisterDevice &unregisterDeviceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateDeviceLocked &updateDeviceLockedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateNotifySettings &updateNotifySettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdatePasswordSettings &updatePasswordSettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateProfile &updateProfileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateStatus &updateStatusFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateUsername &updateUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthBindTempAuthKey &bindTempAuthKeyFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthCheckPassword &checkPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthCheckPhone &checkPhoneFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthExportAuthorization &exportAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthImportAuthorization &importAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthImportBotAuthorization &importBotAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthLogOut &logOutFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthRecoverPassword &recoverPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthRequestPasswordRecovery &requestPasswordRecoveryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthResetAuthorizations &resetAuthorizationsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSendCall &sendCallFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSendCode &sendCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSendInvites &sendInvitesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSendSms &sendSmsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSignIn &signInFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSignUp &signUpFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsCheckUsername &checkUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsCreateChannel &createChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteChannel &deleteChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteMessages &deleteMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteUserHistory &deleteUserHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditAbout &editAboutFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditAdmin &editAdminFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditPhoto &editPhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditTitle &editTitleFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsExportInvite &exportInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetChannels &getChannelsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetDialogs &getDialogsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetFullChannel &getFullChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetImportantHistory &getImportantHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetMessages &getMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetParticipant &getParticipantFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetParticipants &getParticipantsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsInviteToChannel &inviteToChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsJoinChannel &joinChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsKickFromChannel &kickFromChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsLeaveChannel &leaveChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsReadHistory &readHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsReportSpam &reportSpamFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsToggleComments &toggleCommentsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsUpdateUsername &updateUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsBlock &blockFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsDeleteContact &deleteContactFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsDeleteContacts &deleteContactsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsExportCard &exportCardFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetBlocked &getBlockedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetContacts &getContactsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetStatuses &getStatusesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetSuggested &getSuggestedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsImportCard &importCardFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsImportContacts &importContactsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsResolveUsername &resolveUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsSearch &searchFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsUnblock &unblockFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetAppChangelog &getAppChangelogFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetAppUpdate &getAppUpdateFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetConfig &getConfigFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetInviteText &getInviteTextFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetNearestDc &getNearestDcFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetSupport &getSupportFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetTermsOfService &getTermsOfServiceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpSaveAppLog &saveAppLogFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLInitConnection &connectionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLInvokeAfterMsg &afterMsgFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLInvokeAfterMsgs &afterMsgsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLInvokeWithLayer &withLayerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLInvokeWithoutUpdates &withoutUpdatesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesAcceptEncryption &acceptEncryptionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesAddChatUser &addChatUserFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesCheckChatInvite &checkChatInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesCreateChat &createChatFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDeleteChatUser &deleteChatUserFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDeleteHistory &deleteHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDeleteMessages &deleteMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDiscardEncryption &discardEncryptionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditChatAdmin &editChatAdminFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditChatPhoto &editChatPhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditChatTitle &editChatTitleFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesExportChatInvite &exportChatInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesForwardMessage &forwardMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesForwardMessages &forwardMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetAllStickers &getAllStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetChats &getChatsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetDhConfig &getDhConfigFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetDialogs &getDialogsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetDocumentByHash &getDocumentByHashFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetFullChat &getFullChatFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetHistory &getHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetInlineBotResults &getInlineBotResultsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetMessages &getMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetMessagesViews &getMessagesViewsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetSavedGifs &getSavedGifsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetStickerSet &getStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetStickers &getStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetWebPagePreview &getWebPagePreviewFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesImportChatInvite &importChatInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesInstallStickerSet &installStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesMigrateChat &migrateChatFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadEncryptedHistory &readEncryptedHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadHistory &readHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadMessageContents &readMessageContentsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReceivedMessages &receivedMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReceivedQueue &receivedQueueFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReorderStickerSets &reorderStickerSetsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReportSpam &reportSpamFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesRequestEncryption &requestEncryptionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSaveGif &saveGifFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSearch &searchFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSearchGifs &searchGifsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSearchGlobal &searchGlobalFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendBroadcast &sendBroadcastFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendEncrypted &sendEncryptedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendEncryptedFile &sendEncryptedFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendEncryptedService &sendEncryptedServiceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendInlineBotResult &sendInlineBotResultFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendMedia &sendMediaFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendMessage &sendMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetEncryptedTyping &setEncryptedTypingFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetInlineBotResults &setInlineBotResultsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetTyping &setTypingFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesStartBot &startBotFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesToggleChatAdmins &toggleChatAdminsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesUninstallStickerSet &uninstallStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosDeletePhotos &deletePhotosFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosGetUserPhotos &getUserPhotosFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosUpdateProfilePhoto &updateProfilePhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosUploadProfilePhoto &uploadProfilePhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUpdatesGetChannelDifference &getChannelDifferenceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUpdatesGetDifference &getDifferenceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUpdatesGetState &getStateFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadGetFile &getFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadSaveBigFilePart &saveBigFilePartFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadSaveFilePart &saveFilePartFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUsersGetFullUser &getFullUserFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUsersGetUsers &getUsersFunction);
// End of generated write operators

} // Telegram

#endif // TELEGRAM_SERVER_FUNCTION_STREAM_OPERATORS_HPP
