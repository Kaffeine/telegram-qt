/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TLTYPESDEBUG_HPP
#define TLTYPESDEBUG_HPP

#include <QDebug>
#include "TLTypes.hpp"

namespace Telegram {

namespace Debug {

template <typename Type>
QString flagsToString(const Type &instance);

} // Debug namespace

} // Telegram namespace

// Generated TLTypes debug operators
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountDaysTTL &accountDaysTTLValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountSentEmailCode &accountSentEmailCodeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountTakeout &accountTakeoutValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountTmpPassword &accountTmpPasswordValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthCheckedPhone &authCheckedPhoneValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthCodeType &authCodeTypeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &authExportedAuthorizationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthPasswordRecovery &authPasswordRecoveryValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthSentCodeType &authSentCodeTypeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLBadMsgNotification &badMsgNotificationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLBotCommand &botCommandValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLBotInfo &botInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLCdnPublicKey &cdnPublicKeyValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelParticipantsFilter &channelParticipantsFilterValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChatOnlines &chatOnlinesValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChatParticipant &chatParticipantValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChatParticipants &chatParticipantsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLClientDHInnerData &clientDHInnerDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContact &contactValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactBlocked &contactBlockedValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactLink &contactLinkValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDataJSON &dataJSONValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDestroyAuthKeyRes &destroyAuthKeyResValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDestroySessionRes &destroySessionResValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLEncryptedChat &encryptedChatValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLEncryptedFile &encryptedFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLEncryptedMessage &encryptedMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLError &errorValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLExportedChatInvite &exportedChatInviteValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLExportedMessageLink &exportedMessageLinkValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLFileHash &fileHashValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLFileLocation &fileLocationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLFutureSalt &futureSaltValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLFutureSalts &futureSaltsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLGeoPoint &geoPointValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpInviteText &helpInviteTextValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpPassportConfig &helpPassportConfigValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpSupportName &helpSupportNameValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHighScore &highScoreValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHttpWait &httpWaitValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLImportedContact &importedContactValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInlineBotSwitchPM &inlineBotSwitchPMValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputAppEvent &inputAppEventValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputBotInlineMessageID &inputBotInlineMessageIDValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputChannel &inputChannelValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputCheckPasswordSRP &inputCheckPasswordSRPValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputClientProxy &inputClientProxyValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputContact &inputContactValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputDocument &inputDocumentValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputEncryptedChat &inputEncryptedChatValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputEncryptedFile &inputEncryptedFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputFile &inputFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputFileLocation &inputFileLocationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputGeoPoint &inputGeoPointValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputMessage &inputMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPeer &inputPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPhoneCall &inputPhoneCallValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPhoto &inputPhotoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPrivacyKey &inputPrivacyKeyValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputSecureFile &inputSecureFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputStickerSet &inputStickerSetValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputStickeredMedia &inputStickeredMediaValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputUser &inputUserValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputWebFileLocation &inputWebFileLocationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLIpPort &ipPortValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLJSONObjectValue &jSONObjectValueValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLJSONValue &jSONValueValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLLabeledPrice &labeledPriceValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLLangPackString &langPackStringValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMaskCoords &maskCoordsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessageEntity &messageEntityValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessageRange &messageRangeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesAffectedHistory &messagesAffectedHistoryValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesAffectedMessages &messagesAffectedMessagesValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesDhConfig &messagesDhConfigValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMsgDetailedInfo &msgDetailedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMsgResendReq &msgResendReqValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMsgsAck &msgsAckValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMsgsAllInfo &msgsAllInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMsgsStateInfo &msgsStateInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMsgsStateReq &msgsStateReqValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLNearestDc &nearestDcValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLNewSession &newSessionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPQInnerData &pQInnerDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageCaption &pageCaptionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageListItem &pageListItemValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageListOrderedItem &pageListOrderedItemValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageRelatedArticle &pageRelatedArticleValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPasswordKdfAlgo &passwordKdfAlgoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentCharge &paymentChargeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentSavedCredentials &paymentSavedCredentialsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPeer &peerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPeerNotifySettings &peerNotifySettingsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhoneCallDiscardReason &phoneCallDiscardReasonValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhoneConnection &phoneConnectionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhotoSize &photoSizeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPollAnswer &pollAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPong &pongValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPopularContact &popularContactValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPostAddress &postAddressValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPrivacyKey &privacyKeyValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPrivacyRule &privacyRuleValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLReceivedNotifyMessage &receivedNotifyMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLReportReason &reportReasonValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLResPQ &resPQValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLRichText &richTextValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLRpcDropAnswer &rpcDropAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLRpcError &rpcErrorValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSavedContact &savedContactValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureCredentialsEncrypted &secureCredentialsEncryptedValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureData &secureDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureFile &secureFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecurePasswordKdfAlgo &securePasswordKdfAlgoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecurePlainData &securePlainDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureSecretSettings &secureSecretSettingsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureValueType &secureValueTypeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSendMessageAction &sendMessageActionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLServerDHInnerData &serverDHInnerDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLServerDHParams &serverDHParamsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSetClientDHParamsAnswer &setClientDHParamsAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLShippingOption &shippingOptionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLStatsURL &statsURLValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLStickerPack &stickerPackValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLStorageFileType &storageFileTypeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLTopPeer &topPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLTopPeerCategory &topPeerCategoryValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLTopPeerCategoryPeers &topPeerCategoryPeersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUpdatesState &updatesStateValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUploadCdnFile &uploadCdnFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUploadFile &uploadFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUploadWebFile &uploadWebFileValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUserProfilePhoto &userProfilePhotoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUserStatus &userStatusValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLWallPaper &wallPaperValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLWebAuthorization &webAuthorizationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccessPointRule &accessPointRuleValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountPassword &accountPasswordValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountPasswordSettings &accountPasswordSettingsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthorization &authorizationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLCdnConfig &cdnConfigValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelAdminLogEventsFilter &channelAdminLogEventsFilterValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelAdminRights &channelAdminRightsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelBannedRights &channelBannedRightsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelMessagesFilter &channelMessagesFilterValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelParticipant &channelParticipantValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChatPhoto &chatPhotoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactStatus &contactStatusValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDcOption &dcOptionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDialogPeer &dialogPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDocumentAttribute &documentAttributeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDraftMessage &draftMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpConfigSimple &helpConfigSimpleValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpDeepLinkInfo &helpDeepLinkInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpTermsOfService &helpTermsOfServiceValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpTermsOfServiceUpdate &helpTermsOfServiceUpdateValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpUserInfo &helpUserInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputChatPhoto &inputChatPhotoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputDialogPeer &inputDialogPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputGame &inputGameValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputNotifyPeer &inputNotifyPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPaymentCredentials &inputPaymentCredentialsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputPrivacyRule &inputPrivacyRuleValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputSecureValue &inputSecureValueValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputStickerSetItem &inputStickerSetItemValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputWebDocument &inputWebDocumentValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInvoice &invoiceValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLKeyboardButton &keyboardButtonValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLKeyboardButtonRow &keyboardButtonRowValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLLangPackDifference &langPackDifferenceValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLLangPackLanguage &langPackLanguageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessageFwdHeader &messageFwdHeaderValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesBotCallbackAnswer &messagesBotCallbackAnswerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesFilter &messagesFilterValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesMessageEditData &messagesMessageEditDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLNotifyPeer &notifyPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageTableCell &pageTableCellValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageTableRow &pageTableRowValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentRequestedInfo &paymentRequestedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentsSavedInfo &paymentsSavedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentsValidatedRequestedInfo &paymentsValidatedRequestedInfoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPeerSettings &peerSettingsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhoneCallProtocol &phoneCallProtocolValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhoto &photoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPoll &pollValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPollAnswerVoters &pollAnswerVotersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPollResults &pollResultsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLReplyMarkup &replyMarkupValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureRequiredType &secureRequiredTypeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureValue &secureValueValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureValueError &secureValueErrorValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLSecureValueHash &secureValueHashValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLStickerSet &stickerSetValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUser &userValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLWebDocument &webDocumentValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountAuthorizationForm &accountAuthorizationFormValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountAuthorizations &accountAuthorizationsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountPrivacyRules &accountPrivacyRulesValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAccountWebAuthorizations &accountWebAuthorizationsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthAuthorization &authAuthorizationValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLAuthSentCode &authSentCodeValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLBotInlineMessage &botInlineMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelsChannelParticipant &channelsChannelParticipantValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelsChannelParticipants &channelsChannelParticipantsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChat &chatValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChatFull &chatFullValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChatInvite &chatInviteValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLConfig &configValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsBlocked &contactsBlockedValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsContacts &contactsContactsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsFound &contactsFoundValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsImportedContacts &contactsImportedContactsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsLink &contactsLinkValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsResolvedPeer &contactsResolvedPeerValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLContactsTopPeers &contactsTopPeersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDialog &dialogValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLDocument &documentValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLFoundGif &foundGifValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLGame &gameValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpAppUpdate &helpAppUpdateValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpProxyData &helpProxyDataValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpSupport &helpSupportValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputBotInlineMessage &inputBotInlineMessageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputBotInlineResult &inputBotInlineResultValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputMedia &inputMediaValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLInputSingleMedia &inputSingleMediaValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessageAction &messageActionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesAllStickers &messagesAllStickersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesChatFull &messagesChatFullValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesChats &messagesChatsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesFavedStickers &messagesFavedStickersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesFoundGifs &messagesFoundGifsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesHighScores &messagesHighScoresValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesRecentStickers &messagesRecentStickersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesSavedGifs &messagesSavedGifsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesStickerSet &messagesStickerSetValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesStickers &messagesStickersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPage &pageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPageBlock &pageBlockValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentsPaymentForm &paymentsPaymentFormValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentsPaymentReceipt &paymentsPaymentReceiptValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhoneCall &phoneCallValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhonePhoneCall &phonePhoneCallValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhotosPhoto &photosPhotoValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPhotosPhotos &photosPhotosValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLStickerSetCovered &stickerSetCoveredValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUserFull &userFullValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLWebPage &webPageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLBotInlineResult &botInlineResultValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessageMedia &messageMediaValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesArchivedStickers &messagesArchivedStickersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesBotResults &messagesBotResultsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesFeaturedStickers &messagesFeaturedStickersValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesFoundStickerSets &messagesFoundStickerSetsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesStickerSetInstallResult &messagesStickerSetInstallResultValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLRecentMeUrl &recentMeUrlValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLHelpRecentMeUrls &helpRecentMeUrlsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessage &messageValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesDialogs &messagesDialogsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesMessages &messagesMessagesValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLMessagesPeerDialogs &messagesPeerDialogsValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUpdate &updateValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUpdates &updatesValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUpdatesChannelDifference &updatesChannelDifferenceValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLUpdatesDifference &updatesDifferenceValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelAdminLogEventAction &channelAdminLogEventActionValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLPaymentsPaymentResult &paymentsPaymentResultValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelAdminLogEvent &channelAdminLogEventValue);
TELEGRAMQT_INTERNAL_EXPORT QDebug operator<<(QDebug d, const TLChannelsAdminLogResults &channelsAdminLogResultsValue);
// End of generated TLTypes debug operators

#endif // TLTYPESDEBUG_HPP
