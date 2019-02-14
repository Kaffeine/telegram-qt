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

#ifndef CTELEGRAM_STREAM_EXTRAS_HPP
#define CTELEGRAM_STREAM_EXTRAS_HPP

#include "telegramqt_global.h"

#include "TLTypes.hpp"

class CTelegramStream;

//namespace Telegram {

// Generated write operators
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPassword &accountPasswordValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPasswordSettings &accountPasswordSettingsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountTmpPassword &accountTmpPasswordValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthCheckedPhone &authCheckedPhoneValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthCodeType &authCodeTypeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthExportedAuthorization &authExportedAuthorizationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthPasswordRecovery &authPasswordRecoveryValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthSentCodeType &authSentCodeTypeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthorization &authorizationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBadMsgNotification &badMsgNotificationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotCommand &botCommandValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInfo &botInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLCdnFileHash &cdnFileHashValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLCdnPublicKey &cdnPublicKeyValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatParticipant &chatParticipantValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatParticipants &chatParticipantsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLClientDHInnerData &clientDHInnerDataValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContact &contactValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactBlocked &contactBlockedValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactLink &contactLinkValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDestroyAuthKeyRes &destroyAuthKeyResValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDestroySessionRes &destroySessionResValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDisabledFeature &disabledFeatureValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedChat &encryptedChatValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedFile &encryptedFileValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedMessage &encryptedMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLError &errorValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLExportedChatInvite &exportedChatInviteValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLExportedMessageLink &exportedMessageLinkValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLFileLocation &fileLocationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLFutureSalt &futureSaltValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLFutureSalts &futureSaltsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLGeoPoint &geoPointValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpAppUpdate &helpAppUpdateValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpInviteText &helpInviteTextValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpTermsOfService &helpTermsOfServiceValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHighScore &highScoreValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHttpWait &httpWaitValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLImportedContact &importedContactValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLInputPeerNotifyEvents &inputPeerNotifyEventsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLIpPort &ipPortValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLLangPackLanguage &langPackLanguageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLLangPackString &langPackStringValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageFwdHeader &messageFwdHeaderValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAffectedHistory &messagesAffectedHistoryValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAffectedMessages &messagesAffectedMessagesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesDhConfig &messagesDhConfigValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMsgDetailedInfo &msgDetailedInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMsgResendReq &msgResendReqValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMsgsAck &msgsAckValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMsgsAllInfo &msgsAllInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMsgsStateInfo &msgsStateInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMsgsStateReq &msgsStateReqValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLNearestDc &nearestDcValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLNewSession &newSessionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPQInnerData &pQInnerDataValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentCharge &paymentChargeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentSavedCredentials &paymentSavedCredentialsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeer &peerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerNotifyEvents &peerNotifyEventsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhoneConnection &phoneConnectionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotoSize &photoSizeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPong &pongValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPopularContact &popularContactValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPrivacyKey &privacyKeyValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPrivacyRule &privacyRuleValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLReceivedNotifyMessage &receivedNotifyMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLResPQ &resPQValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLRichText &richTextValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLRpcDropAnswer &rpcDropAnswerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLRpcError &rpcErrorValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLServerDHInnerData &serverDHInnerDataValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLServerDHParams &serverDHParamsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLSetClientDHParamsAnswer &setClientDHParamsAnswerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerPack &stickerPackValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStorageFileType &storageFileTypeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLTopPeer &topPeerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLTopPeerCategoryPeers &topPeerCategoryPeersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesState &updatesStateValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUploadCdnFile &uploadCdnFileValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUploadFile &uploadFileValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUploadWebFile &uploadWebFileValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUserProfilePhoto &userProfilePhotoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUserStatus &userStatusValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLWallPaper &wallPaperValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountAuthorizations &accountAuthorizationsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthSentCode &authSentCodeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLCdnConfig &cdnConfigValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelParticipant &channelParticipantValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatPhoto &chatPhotoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactStatus &contactStatusValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDcOption &dcOptionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDraftMessage &draftMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpConfigSimple &helpConfigSimpleValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLLangPackDifference &langPackDifferenceValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesBotCallbackAnswer &messagesBotCallbackAnswerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesMessageEditData &messagesMessageEditDataValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLNotifyPeer &notifyPeerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentsSavedInfo &paymentsSavedInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentsValidatedRequestedInfo &paymentsValidatedRequestedInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerNotifySettings &peerNotifySettingsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerSettings &peerSettingsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhoto &photoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerSet &stickerSetValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUser &userValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLWebDocument &webDocumentValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPrivacyRules &accountPrivacyRulesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthAuthorization &authAuthorizationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInlineMessage &botInlineMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelsChannelParticipant &channelsChannelParticipantValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelsChannelParticipants &channelsChannelParticipantsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChat &chatValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatFull &chatFullValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatInvite &chatInviteValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLConfig &configValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsBlocked &contactsBlockedValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsContacts &contactsContactsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsFound &contactsFoundValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsImportedContacts &contactsImportedContactsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsLink &contactsLinkValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsResolvedPeer &contactsResolvedPeerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsTopPeers &contactsTopPeersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDialog &dialogValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDocument &documentValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLFoundGif &foundGifValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLGame &gameValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpSupport &helpSupportValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageAction &messageActionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAllStickers &messagesAllStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesChatFull &messagesChatFullValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesChats &messagesChatsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesFavedStickers &messagesFavedStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesFoundGifs &messagesFoundGifsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesHighScores &messagesHighScoresValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesRecentStickers &messagesRecentStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesSavedGifs &messagesSavedGifsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickerSet &messagesStickerSetValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickers &messagesStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPageBlock &pageBlockValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentsPaymentForm &paymentsPaymentFormValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentsPaymentReceipt &paymentsPaymentReceiptValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhoneCall &phoneCallValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhonePhoneCall &phonePhoneCallValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotosPhoto &photosPhotoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotosPhotos &photosPhotosValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerSetCovered &stickerSetCoveredValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUserFull &userFullValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInlineResult &botInlineResultValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesArchivedStickers &messagesArchivedStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesBotResults &messagesBotResultsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesFeaturedStickers &messagesFeaturedStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickerSetInstallResult &messagesStickerSetInstallResultValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPage &pageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLRecentMeUrl &recentMeUrlValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLWebPage &webPageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpRecentMeUrls &helpRecentMeUrlsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageMedia &messageMediaValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessage &messageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesDialogs &messagesDialogsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesMessages &messagesMessagesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesPeerDialogs &messagesPeerDialogsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdate &updateValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdates &updatesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesChannelDifference &updatesChannelDifferenceValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesDifference &updatesDifferenceValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelAdminLogEventAction &channelAdminLogEventActionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPaymentsPaymentResult &paymentsPaymentResultValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelAdminLogEvent &channelAdminLogEventValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelsAdminLogResults &channelsAdminLogResultsValue);
// End of generated write operators

//} // Telegram

#endif // CTELEGRAM_STREAM_EXTRAS_HPP
