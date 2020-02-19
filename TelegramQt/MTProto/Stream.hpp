/*
   Copyright (C) 2014-2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_QT_MTPROTO_STREAM_HPP
#define TELEGRAM_QT_MTPROTO_STREAM_HPP

#include <QVector>
#include <QString>

#include "RawStream.hpp"
#include "TLNumbers.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace MTProto {

class TELEGRAMQT_INTERNAL_EXPORT Stream : public RawStreamEx
{
public:
    using RawStreamEx::RawStreamEx;
    using RawStreamEx::operator <<;
    using RawStreamEx::operator >>;

    Stream &operator>>(TLValue::Value &v);
    Stream &operator<<(const TLValue::Value v);

    Stream &operator>>(TLValue &v);
    Stream &operator<<(const TLValue v);

    Stream &operator>>(QString &str);
    Stream &operator<<(const QString &str);

    Stream &operator>>(bool &data);
    Stream &operator<<(const bool &data);

    Stream &operator>>(TLBool &b);
    Stream &operator<<(const TLBool &b);

    template <typename T>
    Stream &operator>>(TLVector<T> &v);
    template <typename T>
    Stream &operator>>(TLVector<T*> &v);
    template <typename T>
    Stream &operator<<(const TLVector<T> &v);
    template <typename T>
    Stream &operator<<(const TLVector<T*> &v);

    template <int Size>
    Stream &operator<<(const TLNumber<Size> &n);
    template <int Size>
    Stream &operator>>(TLNumber<Size> &n);

    template <typename T>
    Stream &operator<<(const TLPtr<T> &v);
    template <typename T>
    Stream &operator>>(TLPtr<T> &v);

    // Generated read operators
    Stream &operator>>(TLAccountDaysTTL &accountDaysTTLValue);
    Stream &operator>>(TLAccountSentEmailCode &accountSentEmailCodeValue);
    Stream &operator>>(TLAccountTakeout &accountTakeoutValue);
    Stream &operator>>(TLAccountTmpPassword &accountTmpPasswordValue);
    Stream &operator>>(TLAuthCheckedPhone &authCheckedPhoneValue);
    Stream &operator>>(TLAuthCodeType &authCodeTypeValue);
    Stream &operator>>(TLAuthExportedAuthorization &authExportedAuthorizationValue);
    Stream &operator>>(TLAuthPasswordRecovery &authPasswordRecoveryValue);
    Stream &operator>>(TLAuthSentCodeType &authSentCodeTypeValue);
    Stream &operator>>(TLBadMsgNotification &badMsgNotificationValue);
    Stream &operator>>(TLBotCommand &botCommandValue);
    Stream &operator>>(TLBotInfo &botInfoValue);
    Stream &operator>>(TLCdnPublicKey &cdnPublicKeyValue);
    Stream &operator>>(TLChannelParticipantsFilter &channelParticipantsFilterValue);
    Stream &operator>>(TLChatOnlines &chatOnlinesValue);
    Stream &operator>>(TLChatParticipant &chatParticipantValue);
    Stream &operator>>(TLChatParticipants &chatParticipantsValue);
    Stream &operator>>(TLClientDHInnerData &clientDHInnerDataValue);
    Stream &operator>>(TLContact &contactValue);
    Stream &operator>>(TLContactBlocked &contactBlockedValue);
    Stream &operator>>(TLContactLink &contactLinkValue);
    Stream &operator>>(TLDataJSON &dataJSONValue);
    Stream &operator>>(TLDestroyAuthKeyRes &destroyAuthKeyResValue);
    Stream &operator>>(TLDestroySessionRes &destroySessionResValue);
    Stream &operator>>(TLEncryptedChat &encryptedChatValue);
    Stream &operator>>(TLEncryptedFile &encryptedFileValue);
    Stream &operator>>(TLEncryptedMessage &encryptedMessageValue);
    Stream &operator>>(TLError &errorValue);
    Stream &operator>>(TLExportedChatInvite &exportedChatInviteValue);
    Stream &operator>>(TLExportedMessageLink &exportedMessageLinkValue);
    Stream &operator>>(TLFileHash &fileHashValue);
    Stream &operator>>(TLFileLocation &fileLocationValue);
    Stream &operator>>(TLFutureSalt &futureSaltValue);
    Stream &operator>>(TLFutureSalts &futureSaltsValue);
    Stream &operator>>(TLGeoPoint &geoPointValue);
    Stream &operator>>(TLHelpInviteText &helpInviteTextValue);
    Stream &operator>>(TLHelpPassportConfig &helpPassportConfigValue);
    Stream &operator>>(TLHelpSupportName &helpSupportNameValue);
    Stream &operator>>(TLHighScore &highScoreValue);
    Stream &operator>>(TLHttpWait &httpWaitValue);
    Stream &operator>>(TLImportedContact &importedContactValue);
    Stream &operator>>(TLInlineBotSwitchPM &inlineBotSwitchPMValue);
    Stream &operator>>(TLInputAppEvent &inputAppEventValue);
    Stream &operator>>(TLInputBotInlineMessageID &inputBotInlineMessageIDValue);
    Stream &operator>>(TLInputChannel &inputChannelValue);
    Stream &operator>>(TLInputCheckPasswordSRP &inputCheckPasswordSRPValue);
    Stream &operator>>(TLInputClientProxy &inputClientProxyValue);
    Stream &operator>>(TLInputContact &inputContactValue);
    Stream &operator>>(TLInputDocument &inputDocumentValue);
    Stream &operator>>(TLInputEncryptedChat &inputEncryptedChatValue);
    Stream &operator>>(TLInputEncryptedFile &inputEncryptedFileValue);
    Stream &operator>>(TLInputFile &inputFileValue);
    Stream &operator>>(TLInputFileLocation &inputFileLocationValue);
    Stream &operator>>(TLInputGeoPoint &inputGeoPointValue);
    Stream &operator>>(TLInputMessage &inputMessageValue);
    Stream &operator>>(TLInputPeer &inputPeerValue);
    Stream &operator>>(TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
    Stream &operator>>(TLInputPhoneCall &inputPhoneCallValue);
    Stream &operator>>(TLInputPhoto &inputPhotoValue);
    Stream &operator>>(TLInputPrivacyKey &inputPrivacyKeyValue);
    Stream &operator>>(TLInputSecureFile &inputSecureFileValue);
    Stream &operator>>(TLInputStickerSet &inputStickerSetValue);
    Stream &operator>>(TLInputStickeredMedia &inputStickeredMediaValue);
    Stream &operator>>(TLInputUser &inputUserValue);
    Stream &operator>>(TLInputWebFileLocation &inputWebFileLocationValue);
    Stream &operator>>(TLIpPort &ipPortValue);
    Stream &operator>>(TLJSONObjectValue &jSONObjectValueValue);
    Stream &operator>>(TLJSONValue &jSONValueValue);
    Stream &operator>>(TLLabeledPrice &labeledPriceValue);
    Stream &operator>>(TLLangPackString &langPackStringValue);
    Stream &operator>>(TLMaskCoords &maskCoordsValue);
    Stream &operator>>(TLMessageEntity &messageEntityValue);
    Stream &operator>>(TLMessageRange &messageRangeValue);
    Stream &operator>>(TLMessagesAffectedHistory &messagesAffectedHistoryValue);
    Stream &operator>>(TLMessagesAffectedMessages &messagesAffectedMessagesValue);
    Stream &operator>>(TLMessagesDhConfig &messagesDhConfigValue);
    Stream &operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
    Stream &operator>>(TLMsgDetailedInfo &msgDetailedInfoValue);
    Stream &operator>>(TLMsgResendReq &msgResendReqValue);
    Stream &operator>>(TLMsgsAck &msgsAckValue);
    Stream &operator>>(TLMsgsAllInfo &msgsAllInfoValue);
    Stream &operator>>(TLMsgsStateInfo &msgsStateInfoValue);
    Stream &operator>>(TLMsgsStateReq &msgsStateReqValue);
    Stream &operator>>(TLNearestDc &nearestDcValue);
    Stream &operator>>(TLNewSession &newSessionValue);
    Stream &operator>>(TLPQInnerData &pQInnerDataValue);
    Stream &operator>>(TLPageCaption &pageCaptionValue);
    Stream &operator>>(TLPageListItem &pageListItemValue);
    Stream &operator>>(TLPageListOrderedItem &pageListOrderedItemValue);
    Stream &operator>>(TLPageRelatedArticle &pageRelatedArticleValue);
    Stream &operator>>(TLPasswordKdfAlgo &passwordKdfAlgoValue);
    Stream &operator>>(TLPaymentCharge &paymentChargeValue);
    Stream &operator>>(TLPaymentSavedCredentials &paymentSavedCredentialsValue);
    Stream &operator>>(TLPeer &peerValue);
    Stream &operator>>(TLPeerNotifySettings &peerNotifySettingsValue);
    Stream &operator>>(TLPhoneCallDiscardReason &phoneCallDiscardReasonValue);
    Stream &operator>>(TLPhoneConnection &phoneConnectionValue);
    Stream &operator>>(TLPhotoSize &photoSizeValue);
    Stream &operator>>(TLPollAnswer &pollAnswerValue);
    Stream &operator>>(TLPong &pongValue);
    Stream &operator>>(TLPopularContact &popularContactValue);
    Stream &operator>>(TLPostAddress &postAddressValue);
    Stream &operator>>(TLPrivacyKey &privacyKeyValue);
    Stream &operator>>(TLPrivacyRule &privacyRuleValue);
    Stream &operator>>(TLReceivedNotifyMessage &receivedNotifyMessageValue);
    Stream &operator>>(TLReportReason &reportReasonValue);
    Stream &operator>>(TLResPQ &resPQValue);
    Stream &operator>>(TLRichText &richTextValue);
    Stream &operator>>(TLRpcDropAnswer &rpcDropAnswerValue);
    Stream &operator>>(TLRpcError &rpcErrorValue);
    Stream &operator>>(TLSavedContact &savedContactValue);
    Stream &operator>>(TLSecureCredentialsEncrypted &secureCredentialsEncryptedValue);
    Stream &operator>>(TLSecureData &secureDataValue);
    Stream &operator>>(TLSecureFile &secureFileValue);
    Stream &operator>>(TLSecurePasswordKdfAlgo &securePasswordKdfAlgoValue);
    Stream &operator>>(TLSecurePlainData &securePlainDataValue);
    Stream &operator>>(TLSecureSecretSettings &secureSecretSettingsValue);
    Stream &operator>>(TLSecureValueType &secureValueTypeValue);
    Stream &operator>>(TLSendMessageAction &sendMessageActionValue);
    Stream &operator>>(TLServerDHInnerData &serverDHInnerDataValue);
    Stream &operator>>(TLServerDHParams &serverDHParamsValue);
    Stream &operator>>(TLSetClientDHParamsAnswer &setClientDHParamsAnswerValue);
    Stream &operator>>(TLShippingOption &shippingOptionValue);
    Stream &operator>>(TLStatsURL &statsURLValue);
    Stream &operator>>(TLStickerPack &stickerPackValue);
    Stream &operator>>(TLStorageFileType &storageFileTypeValue);
    Stream &operator>>(TLTopPeer &topPeerValue);
    Stream &operator>>(TLTopPeerCategory &topPeerCategoryValue);
    Stream &operator>>(TLTopPeerCategoryPeers &topPeerCategoryPeersValue);
    Stream &operator>>(TLUpdatesState &updatesStateValue);
    Stream &operator>>(TLUploadCdnFile &uploadCdnFileValue);
    Stream &operator>>(TLUploadFile &uploadFileValue);
    Stream &operator>>(TLUploadWebFile &uploadWebFileValue);
    Stream &operator>>(TLUserProfilePhoto &userProfilePhotoValue);
    Stream &operator>>(TLUserStatus &userStatusValue);
    Stream &operator>>(TLWallPaper &wallPaperValue);
    Stream &operator>>(TLWebAuthorization &webAuthorizationValue);
    Stream &operator>>(TLAccessPointRule &accessPointRuleValue);
    Stream &operator>>(TLAccountPassword &accountPasswordValue);
    Stream &operator>>(TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
    Stream &operator>>(TLAccountPasswordSettings &accountPasswordSettingsValue);
    Stream &operator>>(TLAuthorization &authorizationValue);
    Stream &operator>>(TLCdnConfig &cdnConfigValue);
    Stream &operator>>(TLChannelAdminLogEventsFilter &channelAdminLogEventsFilterValue);
    Stream &operator>>(TLChannelAdminRights &channelAdminRightsValue);
    Stream &operator>>(TLChannelBannedRights &channelBannedRightsValue);
    Stream &operator>>(TLChannelMessagesFilter &channelMessagesFilterValue);
    Stream &operator>>(TLChannelParticipant &channelParticipantValue);
    Stream &operator>>(TLChatPhoto &chatPhotoValue);
    Stream &operator>>(TLContactStatus &contactStatusValue);
    Stream &operator>>(TLDcOption &dcOptionValue);
    Stream &operator>>(TLDialogPeer &dialogPeerValue);
    Stream &operator>>(TLDocumentAttribute &documentAttributeValue);
    Stream &operator>>(TLDraftMessage &draftMessageValue);
    Stream &operator>>(TLHelpConfigSimple &helpConfigSimpleValue);
    Stream &operator>>(TLHelpDeepLinkInfo &helpDeepLinkInfoValue);
    Stream &operator>>(TLHelpTermsOfService &helpTermsOfServiceValue);
    Stream &operator>>(TLHelpTermsOfServiceUpdate &helpTermsOfServiceUpdateValue);
    Stream &operator>>(TLHelpUserInfo &helpUserInfoValue);
    Stream &operator>>(TLInputChatPhoto &inputChatPhotoValue);
    Stream &operator>>(TLInputDialogPeer &inputDialogPeerValue);
    Stream &operator>>(TLInputGame &inputGameValue);
    Stream &operator>>(TLInputNotifyPeer &inputNotifyPeerValue);
    Stream &operator>>(TLInputPaymentCredentials &inputPaymentCredentialsValue);
    Stream &operator>>(TLInputPrivacyRule &inputPrivacyRuleValue);
    Stream &operator>>(TLInputSecureValue &inputSecureValueValue);
    Stream &operator>>(TLInputStickerSetItem &inputStickerSetItemValue);
    Stream &operator>>(TLInputWebDocument &inputWebDocumentValue);
    Stream &operator>>(TLInvoice &invoiceValue);
    Stream &operator>>(TLKeyboardButton &keyboardButtonValue);
    Stream &operator>>(TLKeyboardButtonRow &keyboardButtonRowValue);
    Stream &operator>>(TLLangPackDifference &langPackDifferenceValue);
    Stream &operator>>(TLLangPackLanguage &langPackLanguageValue);
    Stream &operator>>(TLMessageFwdHeader &messageFwdHeaderValue);
    Stream &operator>>(TLMessagesBotCallbackAnswer &messagesBotCallbackAnswerValue);
    Stream &operator>>(TLMessagesFilter &messagesFilterValue);
    Stream &operator>>(TLMessagesMessageEditData &messagesMessageEditDataValue);
    Stream &operator>>(TLNotifyPeer &notifyPeerValue);
    Stream &operator>>(TLPageTableCell &pageTableCellValue);
    Stream &operator>>(TLPageTableRow &pageTableRowValue);
    Stream &operator>>(TLPaymentRequestedInfo &paymentRequestedInfoValue);
    Stream &operator>>(TLPaymentsSavedInfo &paymentsSavedInfoValue);
    Stream &operator>>(TLPaymentsValidatedRequestedInfo &paymentsValidatedRequestedInfoValue);
    Stream &operator>>(TLPeerSettings &peerSettingsValue);
    Stream &operator>>(TLPhoneCallProtocol &phoneCallProtocolValue);
    Stream &operator>>(TLPhoto &photoValue);
    Stream &operator>>(TLPoll &pollValue);
    Stream &operator>>(TLPollAnswerVoters &pollAnswerVotersValue);
    Stream &operator>>(TLPollResults &pollResultsValue);
    Stream &operator>>(TLReplyMarkup &replyMarkupValue);
    Stream &operator>>(TLSecureRequiredType &secureRequiredTypeValue);
    Stream &operator>>(TLSecureValue &secureValueValue);
    Stream &operator>>(TLSecureValueError &secureValueErrorValue);
    Stream &operator>>(TLSecureValueHash &secureValueHashValue);
    Stream &operator>>(TLStickerSet &stickerSetValue);
    Stream &operator>>(TLUser &userValue);
    Stream &operator>>(TLWebDocument &webDocumentValue);
    Stream &operator>>(TLAccountAuthorizationForm &accountAuthorizationFormValue);
    Stream &operator>>(TLAccountAuthorizations &accountAuthorizationsValue);
    Stream &operator>>(TLAccountPrivacyRules &accountPrivacyRulesValue);
    Stream &operator>>(TLAccountWebAuthorizations &accountWebAuthorizationsValue);
    Stream &operator>>(TLAuthAuthorization &authAuthorizationValue);
    Stream &operator>>(TLAuthSentCode &authSentCodeValue);
    Stream &operator>>(TLBotInlineMessage &botInlineMessageValue);
    Stream &operator>>(TLChannelsChannelParticipant &channelsChannelParticipantValue);
    Stream &operator>>(TLChannelsChannelParticipants &channelsChannelParticipantsValue);
    Stream &operator>>(TLChat &chatValue);
    Stream &operator>>(TLChatFull &chatFullValue);
    Stream &operator>>(TLChatInvite &chatInviteValue);
    Stream &operator>>(TLConfig &configValue);
    Stream &operator>>(TLContactsBlocked &contactsBlockedValue);
    Stream &operator>>(TLContactsContacts &contactsContactsValue);
    Stream &operator>>(TLContactsFound &contactsFoundValue);
    Stream &operator>>(TLContactsImportedContacts &contactsImportedContactsValue);
    Stream &operator>>(TLContactsLink &contactsLinkValue);
    Stream &operator>>(TLContactsResolvedPeer &contactsResolvedPeerValue);
    Stream &operator>>(TLContactsTopPeers &contactsTopPeersValue);
    Stream &operator>>(TLDialog &dialogValue);
    Stream &operator>>(TLDocument &documentValue);
    Stream &operator>>(TLFoundGif &foundGifValue);
    Stream &operator>>(TLGame &gameValue);
    Stream &operator>>(TLHelpAppUpdate &helpAppUpdateValue);
    Stream &operator>>(TLHelpProxyData &helpProxyDataValue);
    Stream &operator>>(TLHelpSupport &helpSupportValue);
    Stream &operator>>(TLInputBotInlineMessage &inputBotInlineMessageValue);
    Stream &operator>>(TLInputBotInlineResult &inputBotInlineResultValue);
    Stream &operator>>(TLInputMedia &inputMediaValue);
    Stream &operator>>(TLInputSingleMedia &inputSingleMediaValue);
    Stream &operator>>(TLMessageAction &messageActionValue);
    Stream &operator>>(TLMessagesAllStickers &messagesAllStickersValue);
    Stream &operator>>(TLMessagesChatFull &messagesChatFullValue);
    Stream &operator>>(TLMessagesChats &messagesChatsValue);
    Stream &operator>>(TLMessagesFavedStickers &messagesFavedStickersValue);
    Stream &operator>>(TLMessagesFoundGifs &messagesFoundGifsValue);
    Stream &operator>>(TLMessagesHighScores &messagesHighScoresValue);
    Stream &operator>>(TLMessagesRecentStickers &messagesRecentStickersValue);
    Stream &operator>>(TLMessagesSavedGifs &messagesSavedGifsValue);
    Stream &operator>>(TLMessagesStickerSet &messagesStickerSetValue);
    Stream &operator>>(TLMessagesStickers &messagesStickersValue);
    Stream &operator>>(TLPage &pageValue);
    Stream &operator>>(TLPageBlock &pageBlockValue);
    Stream &operator>>(TLPaymentsPaymentForm &paymentsPaymentFormValue);
    Stream &operator>>(TLPaymentsPaymentReceipt &paymentsPaymentReceiptValue);
    Stream &operator>>(TLPhoneCall &phoneCallValue);
    Stream &operator>>(TLPhonePhoneCall &phonePhoneCallValue);
    Stream &operator>>(TLPhotosPhoto &photosPhotoValue);
    Stream &operator>>(TLPhotosPhotos &photosPhotosValue);
    Stream &operator>>(TLStickerSetCovered &stickerSetCoveredValue);
    Stream &operator>>(TLUserFull &userFullValue);
    Stream &operator>>(TLWebPage &webPageValue);
    Stream &operator>>(TLBotInlineResult &botInlineResultValue);
    Stream &operator>>(TLMessageMedia &messageMediaValue);
    Stream &operator>>(TLMessagesArchivedStickers &messagesArchivedStickersValue);
    Stream &operator>>(TLMessagesBotResults &messagesBotResultsValue);
    Stream &operator>>(TLMessagesFeaturedStickers &messagesFeaturedStickersValue);
    Stream &operator>>(TLMessagesFoundStickerSets &messagesFoundStickerSetsValue);
    Stream &operator>>(TLMessagesStickerSetInstallResult &messagesStickerSetInstallResultValue);
    Stream &operator>>(TLRecentMeUrl &recentMeUrlValue);
    Stream &operator>>(TLHelpRecentMeUrls &helpRecentMeUrlsValue);
    Stream &operator>>(TLMessage &messageValue);
    Stream &operator>>(TLMessagesDialogs &messagesDialogsValue);
    Stream &operator>>(TLMessagesMessages &messagesMessagesValue);
    Stream &operator>>(TLMessagesPeerDialogs &messagesPeerDialogsValue);
    Stream &operator>>(TLUpdate &updateValue);
    Stream &operator>>(TLUpdates &updatesValue);
    Stream &operator>>(TLUpdatesChannelDifference &updatesChannelDifferenceValue);
    Stream &operator>>(TLUpdatesDifference &updatesDifferenceValue);
    Stream &operator>>(TLChannelAdminLogEventAction &channelAdminLogEventActionValue);
    Stream &operator>>(TLPaymentsPaymentResult &paymentsPaymentResultValue);
    Stream &operator>>(TLChannelAdminLogEvent &channelAdminLogEventValue);
    Stream &operator>>(TLChannelsAdminLogResults &channelsAdminLogResultsValue);
    // End of generated read operators

    // Generated write operators
    Stream &operator<<(const TLAccountDaysTTL &accountDaysTTLValue);
    Stream &operator<<(const TLChannelParticipantsFilter &channelParticipantsFilterValue);
    Stream &operator<<(const TLDataJSON &dataJSONValue);
    Stream &operator<<(const TLInlineBotSwitchPM &inlineBotSwitchPMValue);
    Stream &operator<<(const TLInputAppEvent &inputAppEventValue);
    Stream &operator<<(const TLInputBotInlineMessageID &inputBotInlineMessageIDValue);
    Stream &operator<<(const TLInputChannel &inputChannelValue);
    Stream &operator<<(const TLInputCheckPasswordSRP &inputCheckPasswordSRPValue);
    Stream &operator<<(const TLInputContact &inputContactValue);
    Stream &operator<<(const TLInputDocument &inputDocumentValue);
    Stream &operator<<(const TLInputEncryptedChat &inputEncryptedChatValue);
    Stream &operator<<(const TLInputEncryptedFile &inputEncryptedFileValue);
    Stream &operator<<(const TLInputFile &inputFileValue);
    Stream &operator<<(const TLInputFileLocation &inputFileLocationValue);
    Stream &operator<<(const TLInputGeoPoint &inputGeoPointValue);
    Stream &operator<<(const TLInputMessage &inputMessageValue);
    Stream &operator<<(const TLInputPeer &inputPeerValue);
    Stream &operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
    Stream &operator<<(const TLInputPhoneCall &inputPhoneCallValue);
    Stream &operator<<(const TLInputPhoto &inputPhotoValue);
    Stream &operator<<(const TLInputPrivacyKey &inputPrivacyKeyValue);
    Stream &operator<<(const TLInputSecureFile &inputSecureFileValue);
    Stream &operator<<(const TLInputStickerSet &inputStickerSetValue);
    Stream &operator<<(const TLInputStickeredMedia &inputStickeredMediaValue);
    Stream &operator<<(const TLInputUser &inputUserValue);
    Stream &operator<<(const TLInputWebFileLocation &inputWebFileLocationValue);
    Stream &operator<<(const TLJSONObjectValue &jSONObjectValueValue);
    Stream &operator<<(const TLJSONValue &jSONValueValue);
    Stream &operator<<(const TLLabeledPrice &labeledPriceValue);
    Stream &operator<<(const TLMaskCoords &maskCoordsValue);
    Stream &operator<<(const TLMessageEntity &messageEntityValue);
    Stream &operator<<(const TLMessageRange &messageRangeValue);
    Stream &operator<<(const TLPasswordKdfAlgo &passwordKdfAlgoValue);
    Stream &operator<<(const TLPhoneCallDiscardReason &phoneCallDiscardReasonValue);
    Stream &operator<<(const TLPollAnswer &pollAnswerValue);
    Stream &operator<<(const TLPostAddress &postAddressValue);
    Stream &operator<<(const TLReportReason &reportReasonValue);
    Stream &operator<<(const TLSecureCredentialsEncrypted &secureCredentialsEncryptedValue);
    Stream &operator<<(const TLSecureData &secureDataValue);
    Stream &operator<<(const TLSecurePasswordKdfAlgo &securePasswordKdfAlgoValue);
    Stream &operator<<(const TLSecurePlainData &securePlainDataValue);
    Stream &operator<<(const TLSecureSecretSettings &secureSecretSettingsValue);
    Stream &operator<<(const TLSecureValueType &secureValueTypeValue);
    Stream &operator<<(const TLSendMessageAction &sendMessageActionValue);
    Stream &operator<<(const TLShippingOption &shippingOptionValue);
    Stream &operator<<(const TLTopPeerCategory &topPeerCategoryValue);
    Stream &operator<<(const TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
    Stream &operator<<(const TLChannelAdminLogEventsFilter &channelAdminLogEventsFilterValue);
    Stream &operator<<(const TLChannelAdminRights &channelAdminRightsValue);
    Stream &operator<<(const TLChannelBannedRights &channelBannedRightsValue);
    Stream &operator<<(const TLChannelMessagesFilter &channelMessagesFilterValue);
    Stream &operator<<(const TLDocumentAttribute &documentAttributeValue);
    Stream &operator<<(const TLInputChatPhoto &inputChatPhotoValue);
    Stream &operator<<(const TLInputDialogPeer &inputDialogPeerValue);
    Stream &operator<<(const TLInputGame &inputGameValue);
    Stream &operator<<(const TLInputNotifyPeer &inputNotifyPeerValue);
    Stream &operator<<(const TLInputPaymentCredentials &inputPaymentCredentialsValue);
    Stream &operator<<(const TLInputPrivacyRule &inputPrivacyRuleValue);
    Stream &operator<<(const TLInputSecureValue &inputSecureValueValue);
    Stream &operator<<(const TLInputStickerSetItem &inputStickerSetItemValue);
    Stream &operator<<(const TLInputWebDocument &inputWebDocumentValue);
    Stream &operator<<(const TLInvoice &invoiceValue);
    Stream &operator<<(const TLKeyboardButton &keyboardButtonValue);
    Stream &operator<<(const TLKeyboardButtonRow &keyboardButtonRowValue);
    Stream &operator<<(const TLMessagesFilter &messagesFilterValue);
    Stream &operator<<(const TLPaymentRequestedInfo &paymentRequestedInfoValue);
    Stream &operator<<(const TLPhoneCallProtocol &phoneCallProtocolValue);
    Stream &operator<<(const TLPoll &pollValue);
    Stream &operator<<(const TLReplyMarkup &replyMarkupValue);
    Stream &operator<<(const TLSecureValueError &secureValueErrorValue);
    Stream &operator<<(const TLSecureValueHash &secureValueHashValue);
    Stream &operator<<(const TLInputBotInlineMessage &inputBotInlineMessageValue);
    Stream &operator<<(const TLInputBotInlineResult &inputBotInlineResultValue);
    Stream &operator<<(const TLInputMedia &inputMediaValue);
    Stream &operator<<(const TLInputSingleMedia &inputSingleMediaValue);
    // End of generated write operators
};

inline Stream &Stream::operator>>(QString &str)
{
    QByteArray data;
    *this >> data;
    str = QString::fromUtf8(data);
    return *this;
}

inline Stream &Stream::operator<<(const QString &str)
{
    *this << str.toUtf8();
    return *this;
}

inline Stream &Stream::operator>>(bool &data)
{
    TLBool val;
    *this >> val;
    data = val;
    return *this;
}

inline Stream &Stream::operator<<(const bool &data)
{
    TLBool val = data;
    *this << val;
    return *this;
}

inline Stream &Stream::operator>>(TLBool &data)
{
    *this >> data.tlType;
    return *this;
}

inline Stream &Stream::operator<<(const TLBool &data)
{
    *this << data.tlType;
    return *this;
}

inline Stream &Stream::operator>>(TLValue::Value &v)
{
    quint32 i;
    *this >> i;
    v = TLValue::Value(i);
    return *this;
}

inline Stream &Stream::operator<<(const TLValue::Value v)
{
    *this << quint32(v);
    return *this;
}

inline Stream &Stream::operator>>(TLValue &v)
{
    quint32 i;
    *this >> i;
    v = TLValue(i);
    return *this;
}

inline Stream &Stream::operator<<(const TLValue v)
{
    *this << quint32(v);
    return *this;
}

} // MTProto namespace

} // Telegram namespace

#endif // TELEGRAM_QT_MTPROTO_STREAM_HPP
