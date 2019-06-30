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

#include "MTProto/TLFunctions.hpp"

class CTelegramStream;

namespace Telegram {

using namespace TLFunctions;

CTelegramStream &operator>>(CTelegramStream &stream, TLPing &ping);
// Generated write operators
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountChangePhone &accountChangePhoneFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountCheckUsername &accountCheckUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountConfirmPhone &accountConfirmPhoneFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountDeleteAccount &accountDeleteAccountFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetAccountTTL &accountGetAccountTTLFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetAuthorizations &accountGetAuthorizationsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetNotifySettings &accountGetNotifySettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetPassword &accountGetPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetPasswordSettings &accountGetPasswordSettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetPrivacy &accountGetPrivacyFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetTmpPassword &accountGetTmpPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountGetWallPapers &accountGetWallPapersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountRegisterDevice &accountRegisterDeviceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountReportPeer &accountReportPeerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountResetAuthorization &accountResetAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountResetNotifySettings &accountResetNotifySettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSendChangePhoneCode &accountSendChangePhoneCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSendConfirmPhoneCode &accountSendConfirmPhoneCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSetAccountTTL &accountSetAccountTTLFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountSetPrivacy &accountSetPrivacyFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUnregisterDevice &accountUnregisterDeviceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateDeviceLocked &accountUpdateDeviceLockedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateNotifySettings &accountUpdateNotifySettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdatePasswordSettings &accountUpdatePasswordSettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateProfile &accountUpdateProfileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateStatus &accountUpdateStatusFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAccountUpdateUsername &accountUpdateUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthBindTempAuthKey &authBindTempAuthKeyFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthCancelCode &authCancelCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthCheckPassword &authCheckPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthCheckPhone &authCheckPhoneFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthDropTempAuthKeys &authDropTempAuthKeysFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthExportAuthorization &authExportAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthImportAuthorization &authImportAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthImportBotAuthorization &authImportBotAuthorizationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthLogOut &authLogOutFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthRecoverPassword &authRecoverPasswordFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthRequestPasswordRecovery &authRequestPasswordRecoveryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthResendCode &authResendCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthResetAuthorizations &authResetAuthorizationsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSendCode &authSendCodeFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSendInvites &authSendInvitesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSignIn &authSignInFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLAuthSignUp &authSignUpFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLBotsAnswerWebhookJSONQuery &botsAnswerWebhookJSONQueryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLBotsSendCustomRequest &botsSendCustomRequestFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsCheckUsername &channelsCheckUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsCreateChannel &channelsCreateChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteChannel &channelsDeleteChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteHistory &channelsDeleteHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteMessages &channelsDeleteMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsDeleteUserHistory &channelsDeleteUserHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditAbout &channelsEditAboutFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditAdmin &channelsEditAdminFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditBanned &channelsEditBannedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditPhoto &channelsEditPhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsEditTitle &channelsEditTitleFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsExportInvite &channelsExportInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsExportMessageLink &channelsExportMessageLinkFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetAdminLog &channelsGetAdminLogFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetAdminedPublicChannels &channelsGetAdminedPublicChannelsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetChannels &channelsGetChannelsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetFullChannel &channelsGetFullChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetMessages &channelsGetMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetParticipant &channelsGetParticipantFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsGetParticipants &channelsGetParticipantsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsInviteToChannel &channelsInviteToChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsJoinChannel &channelsJoinChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsLeaveChannel &channelsLeaveChannelFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsReadHistory &channelsReadHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsReadMessageContents &channelsReadMessageContentsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsReportSpam &channelsReportSpamFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsSetStickers &channelsSetStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsToggleInvites &channelsToggleInvitesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsTogglePreHistoryHidden &channelsTogglePreHistoryHiddenFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsToggleSignatures &channelsToggleSignaturesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsUpdatePinnedMessage &channelsUpdatePinnedMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLChannelsUpdateUsername &channelsUpdateUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsBlock &contactsBlockFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsDeleteContact &contactsDeleteContactFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsDeleteContacts &contactsDeleteContactsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsExportCard &contactsExportCardFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetBlocked &contactsGetBlockedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetContacts &contactsGetContactsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetStatuses &contactsGetStatusesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsGetTopPeers &contactsGetTopPeersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsImportCard &contactsImportCardFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsImportContacts &contactsImportContactsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsResetSaved &contactsResetSavedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsResetTopPeerRating &contactsResetTopPeerRatingFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsResolveUsername &contactsResolveUsernameFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsSearch &contactsSearchFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLContactsUnblock &contactsUnblockFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetAppChangelog &helpGetAppChangelogFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetAppUpdate &helpGetAppUpdateFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetCdnConfig &helpGetCdnConfigFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetConfig &helpGetConfigFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetInviteText &helpGetInviteTextFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetNearestDc &helpGetNearestDcFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetRecentMeUrls &helpGetRecentMeUrlsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetSupport &helpGetSupportFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpGetTermsOfService &helpGetTermsOfServiceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpSaveAppLog &helpSaveAppLogFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLHelpSetBotUpdatesStatus &helpSetBotUpdatesStatusFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLLangpackGetDifference &langpackGetDifferenceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLLangpackGetLangPack &langpackGetLangPackFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLLangpackGetLanguages &langpackGetLanguagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLLangpackGetStrings &langpackGetStringsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesAcceptEncryption &messagesAcceptEncryptionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesAddChatUser &messagesAddChatUserFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesCheckChatInvite &messagesCheckChatInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesClearRecentStickers &messagesClearRecentStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesCreateChat &messagesCreateChatFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDeleteChatUser &messagesDeleteChatUserFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDeleteHistory &messagesDeleteHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDeleteMessages &messagesDeleteMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesDiscardEncryption &messagesDiscardEncryptionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditChatAdmin &messagesEditChatAdminFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditChatPhoto &messagesEditChatPhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditChatTitle &messagesEditChatTitleFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditInlineBotMessage &messagesEditInlineBotMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesEditMessage &messagesEditMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesExportChatInvite &messagesExportChatInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesFaveSticker &messagesFaveStickerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesForwardMessage &messagesForwardMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesForwardMessages &messagesForwardMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetAllChats &messagesGetAllChatsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetAllDrafts &messagesGetAllDraftsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetAllStickers &messagesGetAllStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetArchivedStickers &messagesGetArchivedStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetAttachedStickers &messagesGetAttachedStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetBotCallbackAnswer &messagesGetBotCallbackAnswerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetChats &messagesGetChatsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetCommonChats &messagesGetCommonChatsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetDhConfig &messagesGetDhConfigFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetDialogs &messagesGetDialogsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetDocumentByHash &messagesGetDocumentByHashFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetFavedStickers &messagesGetFavedStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetFeaturedStickers &messagesGetFeaturedStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetFullChat &messagesGetFullChatFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetGameHighScores &messagesGetGameHighScoresFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetHistory &messagesGetHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetInlineBotResults &messagesGetInlineBotResultsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetInlineGameHighScores &messagesGetInlineGameHighScoresFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetMaskStickers &messagesGetMaskStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetMessageEditData &messagesGetMessageEditDataFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetMessages &messagesGetMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetMessagesViews &messagesGetMessagesViewsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetPeerDialogs &messagesGetPeerDialogsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetPeerSettings &messagesGetPeerSettingsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetPinnedDialogs &messagesGetPinnedDialogsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetRecentLocations &messagesGetRecentLocationsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetRecentStickers &messagesGetRecentStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetSavedGifs &messagesGetSavedGifsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetStickerSet &messagesGetStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetUnreadMentions &messagesGetUnreadMentionsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetWebPage &messagesGetWebPageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesGetWebPagePreview &messagesGetWebPagePreviewFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesHideReportSpam &messagesHideReportSpamFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesImportChatInvite &messagesImportChatInviteFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesInstallStickerSet &messagesInstallStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesMigrateChat &messagesMigrateChatFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadEncryptedHistory &messagesReadEncryptedHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadFeaturedStickers &messagesReadFeaturedStickersFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadHistory &messagesReadHistoryFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadMentions &messagesReadMentionsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReadMessageContents &messagesReadMessageContentsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReceivedMessages &messagesReceivedMessagesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReceivedQueue &messagesReceivedQueueFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReorderPinnedDialogs &messagesReorderPinnedDialogsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReorderStickerSets &messagesReorderStickerSetsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReportEncryptedSpam &messagesReportEncryptedSpamFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesReportSpam &messagesReportSpamFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesRequestEncryption &messagesRequestEncryptionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSaveDraft &messagesSaveDraftFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSaveGif &messagesSaveGifFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSaveRecentSticker &messagesSaveRecentStickerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSearch &messagesSearchFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSearchGifs &messagesSearchGifsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSearchGlobal &messagesSearchGlobalFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendEncrypted &messagesSendEncryptedFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendEncryptedFile &messagesSendEncryptedFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendEncryptedService &messagesSendEncryptedServiceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendInlineBotResult &messagesSendInlineBotResultFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendMedia &messagesSendMediaFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendMessage &messagesSendMessageFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSendScreenshotNotification &messagesSendScreenshotNotificationFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetBotCallbackAnswer &messagesSetBotCallbackAnswerFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetBotPrecheckoutResults &messagesSetBotPrecheckoutResultsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetBotShippingResults &messagesSetBotShippingResultsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetEncryptedTyping &messagesSetEncryptedTypingFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetGameScore &messagesSetGameScoreFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetInlineBotResults &messagesSetInlineBotResultsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetInlineGameScore &messagesSetInlineGameScoreFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesSetTyping &messagesSetTypingFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesStartBot &messagesStartBotFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesToggleChatAdmins &messagesToggleChatAdminsFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesToggleDialogPin &messagesToggleDialogPinFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesUninstallStickerSet &messagesUninstallStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLMessagesUploadMedia &messagesUploadMediaFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPaymentsClearSavedInfo &paymentsClearSavedInfoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPaymentsGetPaymentForm &paymentsGetPaymentFormFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPaymentsGetPaymentReceipt &paymentsGetPaymentReceiptFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPaymentsGetSavedInfo &paymentsGetSavedInfoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPaymentsSendPaymentForm &paymentsSendPaymentFormFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPaymentsValidateRequestedInfo &paymentsValidateRequestedInfoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneAcceptCall &phoneAcceptCallFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneConfirmCall &phoneConfirmCallFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneDiscardCall &phoneDiscardCallFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneGetCallConfig &phoneGetCallConfigFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneReceivedCall &phoneReceivedCallFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneRequestCall &phoneRequestCallFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneSaveCallDebug &phoneSaveCallDebugFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhoneSetCallRating &phoneSetCallRatingFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosDeletePhotos &photosDeletePhotosFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosGetUserPhotos &photosGetUserPhotosFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosUpdateProfilePhoto &photosUpdateProfilePhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLPhotosUploadProfilePhoto &photosUploadProfilePhotoFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLStickersAddStickerToSet &stickersAddStickerToSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLStickersChangeStickerPosition &stickersChangeStickerPositionFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLStickersCreateStickerSet &stickersCreateStickerSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLStickersRemoveStickerFromSet &stickersRemoveStickerFromSetFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUpdatesGetChannelDifference &updatesGetChannelDifferenceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUpdatesGetDifference &updatesGetDifferenceFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUpdatesGetState &updatesGetStateFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadGetCdnFile &uploadGetCdnFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadGetCdnFileHashes &uploadGetCdnFileHashesFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadGetFile &uploadGetFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadGetWebFile &uploadGetWebFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadReuploadCdnFile &uploadReuploadCdnFileFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadSaveBigFilePart &uploadSaveBigFilePartFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUploadSaveFilePart &uploadSaveFilePartFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUsersGetFullUser &usersGetFullUserFunction);
CTelegramStream &operator>>(CTelegramStream &stream, TLUsersGetUsers &usersGetUsersFunction);
// End of generated write operators

} // Telegram namespace

#endif // TELEGRAM_SERVER_FUNCTION_STREAM_OPERATORS_HPP
