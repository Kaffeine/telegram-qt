/*
   Copyright (C) 2018-2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_QT_MTPROTO_STREAM_EXTRA_HPP
#define TELEGRAM_QT_MTPROTO_STREAM_EXTRA_HPP

#include "telegramqt_global.h"

#include "TLTypes.hpp"

namespace Telegram {

namespace MTProto {

class Stream;

// Generated write operators
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountSentEmailCode &accountSentEmailCodeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountTakeout &accountTakeoutValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountTmpPassword &accountTmpPasswordValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthCheckedPhone &authCheckedPhoneValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthCodeType &authCodeTypeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthExportedAuthorization &authExportedAuthorizationValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthPasswordRecovery &authPasswordRecoveryValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthSentCodeType &authSentCodeTypeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLBadMsgNotification &badMsgNotificationValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLBotCommand &botCommandValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLBotInfo &botInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLCdnPublicKey &cdnPublicKeyValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChatOnlines &chatOnlinesValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChatParticipant &chatParticipantValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChatParticipants &chatParticipantsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLClientDHInnerData &clientDHInnerDataValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContact &contactValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactBlocked &contactBlockedValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactLink &contactLinkValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDestroyAuthKeyRes &destroyAuthKeyResValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDestroySessionRes &destroySessionResValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLEncryptedChat &encryptedChatValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLEncryptedFile &encryptedFileValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLEncryptedMessage &encryptedMessageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLError &errorValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLExportedChatInvite &exportedChatInviteValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLExportedMessageLink &exportedMessageLinkValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLFileHash &fileHashValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLFileLocation &fileLocationValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLFutureSalt &futureSaltValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLFutureSalts &futureSaltsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLGeoPoint &geoPointValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpInviteText &helpInviteTextValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpPassportConfig &helpPassportConfigValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpSupportName &helpSupportNameValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHighScore &highScoreValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHttpWait &httpWaitValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLImportedContact &importedContactValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLInputClientProxy &inputClientProxyValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLIpPort &ipPortValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLLangPackString &langPackStringValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesAffectedHistory &messagesAffectedHistoryValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesAffectedMessages &messagesAffectedMessagesValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesDhConfig &messagesDhConfigValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMsgDetailedInfo &msgDetailedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMsgResendReq &msgResendReqValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMsgsAck &msgsAckValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMsgsAllInfo &msgsAllInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMsgsStateInfo &msgsStateInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMsgsStateReq &msgsStateReqValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLNearestDc &nearestDcValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLNewSession &newSessionValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPQInnerData &pQInnerDataValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageCaption &pageCaptionValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageListItem &pageListItemValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageListOrderedItem &pageListOrderedItemValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageRelatedArticle &pageRelatedArticleValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentCharge &paymentChargeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentSavedCredentials &paymentSavedCredentialsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPeer &peerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPeerNotifySettings &peerNotifySettingsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhoneConnection &phoneConnectionValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhotoSize &photoSizeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPong &pongValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPopularContact &popularContactValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPrivacyKey &privacyKeyValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPrivacyRule &privacyRuleValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLReceivedNotifyMessage &receivedNotifyMessageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLResPQ &resPQValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLRichText &richTextValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLRpcDropAnswer &rpcDropAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLRpcError &rpcErrorValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLSavedContact &savedContactValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLSecureFile &secureFileValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLServerDHInnerData &serverDHInnerDataValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLServerDHParams &serverDHParamsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLSetClientDHParamsAnswer &setClientDHParamsAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLStatsURL &statsURLValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLStickerPack &stickerPackValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLStorageFileType &storageFileTypeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLTopPeer &topPeerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLTopPeerCategoryPeers &topPeerCategoryPeersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUpdatesState &updatesStateValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUploadCdnFile &uploadCdnFileValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUploadFile &uploadFileValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUploadWebFile &uploadWebFileValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUserProfilePhoto &userProfilePhotoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUserStatus &userStatusValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLWallPaper &wallPaperValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLWebAuthorization &webAuthorizationValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccessPointRule &accessPointRuleValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountPassword &accountPasswordValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountPasswordSettings &accountPasswordSettingsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthorization &authorizationValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLCdnConfig &cdnConfigValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChannelParticipant &channelParticipantValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChatPhoto &chatPhotoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactStatus &contactStatusValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDcOption &dcOptionValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDialogPeer &dialogPeerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDraftMessage &draftMessageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpConfigSimple &helpConfigSimpleValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpDeepLinkInfo &helpDeepLinkInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpTermsOfService &helpTermsOfServiceValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpTermsOfServiceUpdate &helpTermsOfServiceUpdateValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpUserInfo &helpUserInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLLangPackDifference &langPackDifferenceValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLLangPackLanguage &langPackLanguageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessageFwdHeader &messageFwdHeaderValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesBotCallbackAnswer &messagesBotCallbackAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesMessageEditData &messagesMessageEditDataValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLNotifyPeer &notifyPeerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageTableCell &pageTableCellValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageTableRow &pageTableRowValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentsSavedInfo &paymentsSavedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentsValidatedRequestedInfo &paymentsValidatedRequestedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPeerSettings &peerSettingsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhoto &photoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPollAnswerVoters &pollAnswerVotersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPollResults &pollResultsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLSecureRequiredType &secureRequiredTypeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLSecureValue &secureValueValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLStickerSet &stickerSetValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUser &userValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLWebDocument &webDocumentValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountAuthorizationForm &accountAuthorizationFormValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountAuthorizations &accountAuthorizationsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountPrivacyRules &accountPrivacyRulesValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAccountWebAuthorizations &accountWebAuthorizationsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthAuthorization &authAuthorizationValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLAuthSentCode &authSentCodeValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLBotInlineMessage &botInlineMessageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChannelsChannelParticipant &channelsChannelParticipantValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChannelsChannelParticipants &channelsChannelParticipantsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChat &chatValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChatFull &chatFullValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChatInvite &chatInviteValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLConfig &configValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsBlocked &contactsBlockedValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsContacts &contactsContactsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsFound &contactsFoundValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsImportedContacts &contactsImportedContactsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsLink &contactsLinkValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsResolvedPeer &contactsResolvedPeerValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLContactsTopPeers &contactsTopPeersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDialog &dialogValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLDocument &documentValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLFoundGif &foundGifValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLGame &gameValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpAppUpdate &helpAppUpdateValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpProxyData &helpProxyDataValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpSupport &helpSupportValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessageAction &messageActionValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesAllStickers &messagesAllStickersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesChatFull &messagesChatFullValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesChats &messagesChatsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesFavedStickers &messagesFavedStickersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesFoundGifs &messagesFoundGifsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesHighScores &messagesHighScoresValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesRecentStickers &messagesRecentStickersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesSavedGifs &messagesSavedGifsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesStickerSet &messagesStickerSetValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesStickers &messagesStickersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPage &pageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPageBlock &pageBlockValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentsPaymentForm &paymentsPaymentFormValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentsPaymentReceipt &paymentsPaymentReceiptValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhoneCall &phoneCallValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhonePhoneCall &phonePhoneCallValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhotosPhoto &photosPhotoValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPhotosPhotos &photosPhotosValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLStickerSetCovered &stickerSetCoveredValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUserFull &userFullValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLWebPage &webPageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLBotInlineResult &botInlineResultValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessageMedia &messageMediaValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesArchivedStickers &messagesArchivedStickersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesBotResults &messagesBotResultsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesFeaturedStickers &messagesFeaturedStickersValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesFoundStickerSets &messagesFoundStickerSetsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesStickerSetInstallResult &messagesStickerSetInstallResultValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLRecentMeUrl &recentMeUrlValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLHelpRecentMeUrls &helpRecentMeUrlsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessage &messageValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesDialogs &messagesDialogsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesMessages &messagesMessagesValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLMessagesPeerDialogs &messagesPeerDialogsValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUpdate &updateValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUpdates &updatesValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUpdatesChannelDifference &updatesChannelDifferenceValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLUpdatesDifference &updatesDifferenceValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChannelAdminLogEventAction &channelAdminLogEventActionValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLPaymentsPaymentResult &paymentsPaymentResultValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChannelAdminLogEvent &channelAdminLogEventValue);
TELEGRAMQT_INTERNAL_EXPORT Stream &operator<<(Stream &stream, const TLChannelsAdminLogResults &channelsAdminLogResultsValue);
// End of generated write operators

} // MTProto namespace

} // Telegram namespace

#endif // CTELEGRAM_STREAM_EXTRAS_HPP
