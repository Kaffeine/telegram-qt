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

namespace Telegram {

namespace MTProto {

class Stream;

using namespace Functions;

MTProto::Stream &operator>>(MTProto::Stream &stream, TLPing &ping);
// Generated write operators
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountAcceptAuthorization &accountAcceptAuthorizationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountCancelPasswordEmail &accountCancelPasswordEmailFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountChangePhone &accountChangePhoneFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountCheckUsername &accountCheckUsernameFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountConfirmPasswordEmail &accountConfirmPasswordEmailFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountConfirmPhone &accountConfirmPhoneFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountDeleteAccount &accountDeleteAccountFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountDeleteSecureValue &accountDeleteSecureValueFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountFinishTakeoutSession &accountFinishTakeoutSessionFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetAccountTTL &accountGetAccountTTLFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetAllSecureValues &accountGetAllSecureValuesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetAuthorizationForm &accountGetAuthorizationFormFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetAuthorizations &accountGetAuthorizationsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetContactSignUpNotification &accountGetContactSignUpNotificationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetNotifyExceptions &accountGetNotifyExceptionsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetNotifySettings &accountGetNotifySettingsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetPassword &accountGetPasswordFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetPasswordSettings &accountGetPasswordSettingsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetPrivacy &accountGetPrivacyFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetSecureValue &accountGetSecureValueFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetTmpPassword &accountGetTmpPasswordFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetWallPapers &accountGetWallPapersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountGetWebAuthorizations &accountGetWebAuthorizationsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountInitTakeoutSession &accountInitTakeoutSessionFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountRegisterDevice &accountRegisterDeviceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountReportPeer &accountReportPeerFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountResendPasswordEmail &accountResendPasswordEmailFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountResetAuthorization &accountResetAuthorizationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountResetNotifySettings &accountResetNotifySettingsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountResetWebAuthorization &accountResetWebAuthorizationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountResetWebAuthorizations &accountResetWebAuthorizationsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSaveSecureValue &accountSaveSecureValueFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSendChangePhoneCode &accountSendChangePhoneCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSendConfirmPhoneCode &accountSendConfirmPhoneCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSendVerifyEmailCode &accountSendVerifyEmailCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSendVerifyPhoneCode &accountSendVerifyPhoneCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSetAccountTTL &accountSetAccountTTLFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSetContactSignUpNotification &accountSetContactSignUpNotificationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountSetPrivacy &accountSetPrivacyFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUnregisterDevice &accountUnregisterDeviceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUpdateDeviceLocked &accountUpdateDeviceLockedFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUpdateNotifySettings &accountUpdateNotifySettingsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUpdatePasswordSettings &accountUpdatePasswordSettingsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUpdateProfile &accountUpdateProfileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUpdateStatus &accountUpdateStatusFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountUpdateUsername &accountUpdateUsernameFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountVerifyEmail &accountVerifyEmailFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAccountVerifyPhone &accountVerifyPhoneFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthBindTempAuthKey &authBindTempAuthKeyFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthCancelCode &authCancelCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthCheckPassword &authCheckPasswordFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthDropTempAuthKeys &authDropTempAuthKeysFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthExportAuthorization &authExportAuthorizationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthImportAuthorization &authImportAuthorizationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthImportBotAuthorization &authImportBotAuthorizationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthLogOut &authLogOutFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthRecoverPassword &authRecoverPasswordFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthRequestPasswordRecovery &authRequestPasswordRecoveryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthResendCode &authResendCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthResetAuthorizations &authResetAuthorizationsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthSendCode &authSendCodeFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthSignIn &authSignInFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLAuthSignUp &authSignUpFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLBotsAnswerWebhookJSONQuery &botsAnswerWebhookJSONQueryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLBotsSendCustomRequest &botsSendCustomRequestFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsCheckUsername &channelsCheckUsernameFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsCreateChannel &channelsCreateChannelFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsDeleteChannel &channelsDeleteChannelFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsDeleteHistory &channelsDeleteHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsDeleteMessages &channelsDeleteMessagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsDeleteUserHistory &channelsDeleteUserHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsEditAbout &channelsEditAboutFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsEditAdmin &channelsEditAdminFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsEditBanned &channelsEditBannedFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsEditPhoto &channelsEditPhotoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsEditTitle &channelsEditTitleFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsExportInvite &channelsExportInviteFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsExportMessageLink &channelsExportMessageLinkFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetAdminLog &channelsGetAdminLogFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetAdminedPublicChannels &channelsGetAdminedPublicChannelsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetChannels &channelsGetChannelsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetFullChannel &channelsGetFullChannelFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetLeftChannels &channelsGetLeftChannelsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetMessages &channelsGetMessagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetParticipant &channelsGetParticipantFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsGetParticipants &channelsGetParticipantsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsInviteToChannel &channelsInviteToChannelFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsJoinChannel &channelsJoinChannelFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsLeaveChannel &channelsLeaveChannelFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsReadHistory &channelsReadHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsReadMessageContents &channelsReadMessageContentsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsReportSpam &channelsReportSpamFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsSetStickers &channelsSetStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsToggleInvites &channelsToggleInvitesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsTogglePreHistoryHidden &channelsTogglePreHistoryHiddenFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsToggleSignatures &channelsToggleSignaturesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLChannelsUpdateUsername &channelsUpdateUsernameFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsBlock &contactsBlockFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsDeleteByPhones &contactsDeleteByPhonesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsDeleteContact &contactsDeleteContactFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsDeleteContacts &contactsDeleteContactsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsGetBlocked &contactsGetBlockedFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsGetContactIDs &contactsGetContactIDsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsGetContacts &contactsGetContactsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsGetSaved &contactsGetSavedFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsGetStatuses &contactsGetStatusesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsGetTopPeers &contactsGetTopPeersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsImportContacts &contactsImportContactsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsResetSaved &contactsResetSavedFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsResetTopPeerRating &contactsResetTopPeerRatingFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsResolveUsername &contactsResolveUsernameFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsSearch &contactsSearchFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsToggleTopPeers &contactsToggleTopPeersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLContactsUnblock &contactsUnblockFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpAcceptTermsOfService &helpAcceptTermsOfServiceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpEditUserInfo &helpEditUserInfoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetAppChangelog &helpGetAppChangelogFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetAppConfig &helpGetAppConfigFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetAppUpdate &helpGetAppUpdateFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetCdnConfig &helpGetCdnConfigFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetConfig &helpGetConfigFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetDeepLinkInfo &helpGetDeepLinkInfoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetInviteText &helpGetInviteTextFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetNearestDc &helpGetNearestDcFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetPassportConfig &helpGetPassportConfigFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetProxyData &helpGetProxyDataFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetRecentMeUrls &helpGetRecentMeUrlsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetSupport &helpGetSupportFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetSupportName &helpGetSupportNameFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetTermsOfServiceUpdate &helpGetTermsOfServiceUpdateFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpGetUserInfo &helpGetUserInfoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpSaveAppLog &helpSaveAppLogFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLHelpSetBotUpdatesStatus &helpSetBotUpdatesStatusFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLLangpackGetDifference &langpackGetDifferenceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLLangpackGetLangPack &langpackGetLangPackFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLLangpackGetLanguage &langpackGetLanguageFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLLangpackGetLanguages &langpackGetLanguagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLLangpackGetStrings &langpackGetStringsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesAcceptEncryption &messagesAcceptEncryptionFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesAddChatUser &messagesAddChatUserFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesCheckChatInvite &messagesCheckChatInviteFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesClearAllDrafts &messagesClearAllDraftsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesClearRecentStickers &messagesClearRecentStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesCreateChat &messagesCreateChatFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesDeleteChatUser &messagesDeleteChatUserFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesDeleteHistory &messagesDeleteHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesDeleteMessages &messagesDeleteMessagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesDiscardEncryption &messagesDiscardEncryptionFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesEditChatAdmin &messagesEditChatAdminFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesEditChatPhoto &messagesEditChatPhotoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesEditChatTitle &messagesEditChatTitleFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesEditInlineBotMessage &messagesEditInlineBotMessageFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesEditMessage &messagesEditMessageFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesExportChatInvite &messagesExportChatInviteFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesFaveSticker &messagesFaveStickerFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesForwardMessages &messagesForwardMessagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetAllChats &messagesGetAllChatsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetAllDrafts &messagesGetAllDraftsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetAllStickers &messagesGetAllStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetArchivedStickers &messagesGetArchivedStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetAttachedStickers &messagesGetAttachedStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetBotCallbackAnswer &messagesGetBotCallbackAnswerFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetChats &messagesGetChatsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetCommonChats &messagesGetCommonChatsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetDhConfig &messagesGetDhConfigFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetDialogUnreadMarks &messagesGetDialogUnreadMarksFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetDialogs &messagesGetDialogsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetDocumentByHash &messagesGetDocumentByHashFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetFavedStickers &messagesGetFavedStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetFeaturedStickers &messagesGetFeaturedStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetFullChat &messagesGetFullChatFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetGameHighScores &messagesGetGameHighScoresFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetHistory &messagesGetHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetInlineBotResults &messagesGetInlineBotResultsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetInlineGameHighScores &messagesGetInlineGameHighScoresFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetMaskStickers &messagesGetMaskStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetMessageEditData &messagesGetMessageEditDataFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetMessages &messagesGetMessagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetMessagesViews &messagesGetMessagesViewsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetOnlines &messagesGetOnlinesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetPeerDialogs &messagesGetPeerDialogsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetPeerSettings &messagesGetPeerSettingsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetPinnedDialogs &messagesGetPinnedDialogsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetPollResults &messagesGetPollResultsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetRecentLocations &messagesGetRecentLocationsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetRecentStickers &messagesGetRecentStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetSavedGifs &messagesGetSavedGifsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetSplitRanges &messagesGetSplitRangesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetStatsURL &messagesGetStatsURLFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetStickerSet &messagesGetStickerSetFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetStickers &messagesGetStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetUnreadMentions &messagesGetUnreadMentionsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetWebPage &messagesGetWebPageFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesGetWebPagePreview &messagesGetWebPagePreviewFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesHideReportSpam &messagesHideReportSpamFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesImportChatInvite &messagesImportChatInviteFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesInstallStickerSet &messagesInstallStickerSetFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesMarkDialogUnread &messagesMarkDialogUnreadFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesMigrateChat &messagesMigrateChatFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReadEncryptedHistory &messagesReadEncryptedHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReadFeaturedStickers &messagesReadFeaturedStickersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReadHistory &messagesReadHistoryFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReadMentions &messagesReadMentionsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReadMessageContents &messagesReadMessageContentsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReceivedMessages &messagesReceivedMessagesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReceivedQueue &messagesReceivedQueueFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReorderPinnedDialogs &messagesReorderPinnedDialogsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReorderStickerSets &messagesReorderStickerSetsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReport &messagesReportFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReportEncryptedSpam &messagesReportEncryptedSpamFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesReportSpam &messagesReportSpamFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesRequestEncryption &messagesRequestEncryptionFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSaveDraft &messagesSaveDraftFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSaveGif &messagesSaveGifFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSaveRecentSticker &messagesSaveRecentStickerFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSearch &messagesSearchFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSearchGifs &messagesSearchGifsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSearchGlobal &messagesSearchGlobalFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSearchStickerSets &messagesSearchStickerSetsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendEncrypted &messagesSendEncryptedFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendEncryptedFile &messagesSendEncryptedFileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendEncryptedService &messagesSendEncryptedServiceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendInlineBotResult &messagesSendInlineBotResultFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendMedia &messagesSendMediaFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendMessage &messagesSendMessageFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendMultiMedia &messagesSendMultiMediaFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendScreenshotNotification &messagesSendScreenshotNotificationFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSendVote &messagesSendVoteFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetBotCallbackAnswer &messagesSetBotCallbackAnswerFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetBotPrecheckoutResults &messagesSetBotPrecheckoutResultsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetBotShippingResults &messagesSetBotShippingResultsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetEncryptedTyping &messagesSetEncryptedTypingFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetGameScore &messagesSetGameScoreFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetInlineBotResults &messagesSetInlineBotResultsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetInlineGameScore &messagesSetInlineGameScoreFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesSetTyping &messagesSetTypingFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesStartBot &messagesStartBotFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesToggleChatAdmins &messagesToggleChatAdminsFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesToggleDialogPin &messagesToggleDialogPinFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesUninstallStickerSet &messagesUninstallStickerSetFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesUpdatePinnedMessage &messagesUpdatePinnedMessageFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesUploadEncryptedFile &messagesUploadEncryptedFileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLMessagesUploadMedia &messagesUploadMediaFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPaymentsClearSavedInfo &paymentsClearSavedInfoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPaymentsGetPaymentForm &paymentsGetPaymentFormFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPaymentsGetPaymentReceipt &paymentsGetPaymentReceiptFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPaymentsGetSavedInfo &paymentsGetSavedInfoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPaymentsSendPaymentForm &paymentsSendPaymentFormFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPaymentsValidateRequestedInfo &paymentsValidateRequestedInfoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneAcceptCall &phoneAcceptCallFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneConfirmCall &phoneConfirmCallFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneDiscardCall &phoneDiscardCallFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneGetCallConfig &phoneGetCallConfigFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneReceivedCall &phoneReceivedCallFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneRequestCall &phoneRequestCallFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneSaveCallDebug &phoneSaveCallDebugFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhoneSetCallRating &phoneSetCallRatingFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhotosDeletePhotos &photosDeletePhotosFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhotosGetUserPhotos &photosGetUserPhotosFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhotosUpdateProfilePhoto &photosUpdateProfilePhotoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLPhotosUploadProfilePhoto &photosUploadProfilePhotoFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLStickersAddStickerToSet &stickersAddStickerToSetFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLStickersChangeStickerPosition &stickersChangeStickerPositionFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLStickersCreateStickerSet &stickersCreateStickerSetFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLStickersRemoveStickerFromSet &stickersRemoveStickerFromSetFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUpdatesGetChannelDifference &updatesGetChannelDifferenceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUpdatesGetDifference &updatesGetDifferenceFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUpdatesGetState &updatesGetStateFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadGetCdnFile &uploadGetCdnFileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadGetCdnFileHashes &uploadGetCdnFileHashesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadGetFile &uploadGetFileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadGetFileHashes &uploadGetFileHashesFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadGetWebFile &uploadGetWebFileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadReuploadCdnFile &uploadReuploadCdnFileFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadSaveBigFilePart &uploadSaveBigFilePartFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUploadSaveFilePart &uploadSaveFilePartFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUsersGetFullUser &usersGetFullUserFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUsersGetUsers &usersGetUsersFunction);
MTProto::Stream &operator>>(MTProto::Stream &stream, TLUsersSetSecureValueErrors &usersSetSecureValueErrorsFunction);
// End of generated write operators

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_FUNCTION_STREAM_OPERATORS_HPP
