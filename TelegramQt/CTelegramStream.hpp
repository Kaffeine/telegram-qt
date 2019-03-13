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

#ifndef CTELEGRAMSTREAM_HPP
#define CTELEGRAMSTREAM_HPP

#include <QVector>
#include <QString>

#include "CRawStream.hpp"
#include "TLNumbers.hpp"
#include "TLTypes.hpp"

class TELEGRAMQT_INTERNAL_EXPORT CTelegramStream : public CRawStreamEx
{
public:
    using CRawStreamEx::CRawStreamEx;
    using CRawStreamEx::operator <<;
    using CRawStreamEx::operator >>;

    CTelegramStream &operator>>(TLValue::Value &v);
    CTelegramStream &operator<<(const TLValue::Value v);

    CTelegramStream &operator>>(TLValue &v);
    CTelegramStream &operator<<(const TLValue v);

    CTelegramStream &operator>>(QString &str);
    CTelegramStream &operator<<(const QString &str);

    CTelegramStream &operator>>(bool &data);
    CTelegramStream &operator<<(const bool &data);

    CTelegramStream &operator>>(TLBool &b);
    CTelegramStream &operator<<(const TLBool &b);

    template <typename T>
    CTelegramStream &operator>>(TLVector<T> &v);
    template <typename T>
    CTelegramStream &operator>>(TLVector<T*> &v);
    template <typename T>
    CTelegramStream &operator<<(const TLVector<T> &v);
    template <typename T>
    CTelegramStream &operator<<(const TLVector<T*> &v);

    template <int Size>
    CTelegramStream &operator<<(const TLNumber<Size> &n);
    template <int Size>
    CTelegramStream &operator>>(TLNumber<Size> &n);

    // Generated read operators
    CTelegramStream &operator>>(TLAccountDaysTTL &accountDaysTTLValue);
    CTelegramStream &operator>>(TLAccountPassword &accountPasswordValue);
    CTelegramStream &operator>>(TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
    CTelegramStream &operator>>(TLAccountPasswordSettings &accountPasswordSettingsValue);
    CTelegramStream &operator>>(TLAccountTmpPassword &accountTmpPasswordValue);
    CTelegramStream &operator>>(TLAuthCheckedPhone &authCheckedPhoneValue);
    CTelegramStream &operator>>(TLAuthCodeType &authCodeTypeValue);
    CTelegramStream &operator>>(TLAuthExportedAuthorization &authExportedAuthorizationValue);
    CTelegramStream &operator>>(TLAuthPasswordRecovery &authPasswordRecoveryValue);
    CTelegramStream &operator>>(TLAuthSentCodeType &authSentCodeTypeValue);
    CTelegramStream &operator>>(TLAuthorization &authorizationValue);
    CTelegramStream &operator>>(TLBadMsgNotification &badMsgNotificationValue);
    CTelegramStream &operator>>(TLBotCommand &botCommandValue);
    CTelegramStream &operator>>(TLBotInfo &botInfoValue);
    CTelegramStream &operator>>(TLCdnFileHash &cdnFileHashValue);
    CTelegramStream &operator>>(TLCdnPublicKey &cdnPublicKeyValue);
    CTelegramStream &operator>>(TLChannelParticipantsFilter &channelParticipantsFilterValue);
    CTelegramStream &operator>>(TLChatParticipant &chatParticipantValue);
    CTelegramStream &operator>>(TLChatParticipants &chatParticipantsValue);
    CTelegramStream &operator>>(TLClientDHInnerData &clientDHInnerDataValue);
    CTelegramStream &operator>>(TLContact &contactValue);
    CTelegramStream &operator>>(TLContactBlocked &contactBlockedValue);
    CTelegramStream &operator>>(TLContactLink &contactLinkValue);
    CTelegramStream &operator>>(TLDataJSON &dataJSONValue);
    CTelegramStream &operator>>(TLDestroyAuthKeyRes &destroyAuthKeyResValue);
    CTelegramStream &operator>>(TLDestroySessionRes &destroySessionResValue);
    CTelegramStream &operator>>(TLDisabledFeature &disabledFeatureValue);
    CTelegramStream &operator>>(TLEncryptedChat &encryptedChatValue);
    CTelegramStream &operator>>(TLEncryptedFile &encryptedFileValue);
    CTelegramStream &operator>>(TLEncryptedMessage &encryptedMessageValue);
    CTelegramStream &operator>>(TLError &errorValue);
    CTelegramStream &operator>>(TLExportedChatInvite &exportedChatInviteValue);
    CTelegramStream &operator>>(TLExportedMessageLink &exportedMessageLinkValue);
    CTelegramStream &operator>>(TLFileLocation &fileLocationValue);
    CTelegramStream &operator>>(TLFutureSalt &futureSaltValue);
    CTelegramStream &operator>>(TLFutureSalts &futureSaltsValue);
    CTelegramStream &operator>>(TLGeoPoint &geoPointValue);
    CTelegramStream &operator>>(TLHelpAppUpdate &helpAppUpdateValue);
    CTelegramStream &operator>>(TLHelpInviteText &helpInviteTextValue);
    CTelegramStream &operator>>(TLHelpTermsOfService &helpTermsOfServiceValue);
    CTelegramStream &operator>>(TLHighScore &highScoreValue);
    CTelegramStream &operator>>(TLHttpWait &httpWaitValue);
    CTelegramStream &operator>>(TLImportedContact &importedContactValue);
    CTelegramStream &operator>>(TLInlineBotSwitchPM &inlineBotSwitchPMValue);
    CTelegramStream &operator>>(TLInputAppEvent &inputAppEventValue);
    CTelegramStream &operator>>(TLInputBotInlineMessageID &inputBotInlineMessageIDValue);
    CTelegramStream &operator>>(TLInputChannel &inputChannelValue);
    CTelegramStream &operator>>(TLInputContact &inputContactValue);
    CTelegramStream &operator>>(TLInputDocument &inputDocumentValue);
    CTelegramStream &operator>>(TLInputEncryptedChat &inputEncryptedChatValue);
    CTelegramStream &operator>>(TLInputEncryptedFile &inputEncryptedFileValue);
    CTelegramStream &operator>>(TLInputFile &inputFileValue);
    CTelegramStream &operator>>(TLInputFileLocation &inputFileLocationValue);
    CTelegramStream &operator>>(TLInputGeoPoint &inputGeoPointValue);
    CTelegramStream &operator>>(TLInputPeer &inputPeerValue);
    CTelegramStream &operator>>(TLInputPeerNotifyEvents &inputPeerNotifyEventsValue);
    CTelegramStream &operator>>(TLInputPhoneCall &inputPhoneCallValue);
    CTelegramStream &operator>>(TLInputPhoto &inputPhotoValue);
    CTelegramStream &operator>>(TLInputPrivacyKey &inputPrivacyKeyValue);
    CTelegramStream &operator>>(TLInputStickerSet &inputStickerSetValue);
    CTelegramStream &operator>>(TLInputStickeredMedia &inputStickeredMediaValue);
    CTelegramStream &operator>>(TLInputUser &inputUserValue);
    CTelegramStream &operator>>(TLInputWebFileLocation &inputWebFileLocationValue);
    CTelegramStream &operator>>(TLIpPort &ipPortValue);
    CTelegramStream &operator>>(TLLabeledPrice &labeledPriceValue);
    CTelegramStream &operator>>(TLLangPackLanguage &langPackLanguageValue);
    CTelegramStream &operator>>(TLLangPackString &langPackStringValue);
    CTelegramStream &operator>>(TLMaskCoords &maskCoordsValue);
    CTelegramStream &operator>>(TLMessageEntity &messageEntityValue);
    CTelegramStream &operator>>(TLMessageFwdHeader &messageFwdHeaderValue);
    CTelegramStream &operator>>(TLMessageRange &messageRangeValue);
    CTelegramStream &operator>>(TLMessagesAffectedHistory &messagesAffectedHistoryValue);
    CTelegramStream &operator>>(TLMessagesAffectedMessages &messagesAffectedMessagesValue);
    CTelegramStream &operator>>(TLMessagesDhConfig &messagesDhConfigValue);
    CTelegramStream &operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
    CTelegramStream &operator>>(TLMsgDetailedInfo &msgDetailedInfoValue);
    CTelegramStream &operator>>(TLMsgResendReq &msgResendReqValue);
    CTelegramStream &operator>>(TLMsgsAck &msgsAckValue);
    CTelegramStream &operator>>(TLMsgsAllInfo &msgsAllInfoValue);
    CTelegramStream &operator>>(TLMsgsStateInfo &msgsStateInfoValue);
    CTelegramStream &operator>>(TLMsgsStateReq &msgsStateReqValue);
    CTelegramStream &operator>>(TLNearestDc &nearestDcValue);
    CTelegramStream &operator>>(TLNewSession &newSessionValue);
    CTelegramStream &operator>>(TLPQInnerData &pQInnerDataValue);
    CTelegramStream &operator>>(TLPaymentCharge &paymentChargeValue);
    CTelegramStream &operator>>(TLPaymentSavedCredentials &paymentSavedCredentialsValue);
    CTelegramStream &operator>>(TLPeer &peerValue);
    CTelegramStream &operator>>(TLPeerNotifyEvents &peerNotifyEventsValue);
    CTelegramStream &operator>>(TLPhoneCallDiscardReason &phoneCallDiscardReasonValue);
    CTelegramStream &operator>>(TLPhoneConnection &phoneConnectionValue);
    CTelegramStream &operator>>(TLPhotoSize &photoSizeValue);
    CTelegramStream &operator>>(TLPong &pongValue);
    CTelegramStream &operator>>(TLPopularContact &popularContactValue);
    CTelegramStream &operator>>(TLPostAddress &postAddressValue);
    CTelegramStream &operator>>(TLPrivacyKey &privacyKeyValue);
    CTelegramStream &operator>>(TLPrivacyRule &privacyRuleValue);
    CTelegramStream &operator>>(TLReceivedNotifyMessage &receivedNotifyMessageValue);
    CTelegramStream &operator>>(TLReportReason &reportReasonValue);
    CTelegramStream &operator>>(TLResPQ &resPQValue);
    CTelegramStream &operator>>(TLRichText &richTextValue);
    CTelegramStream &operator>>(TLRpcDropAnswer &rpcDropAnswerValue);
    CTelegramStream &operator>>(TLRpcError &rpcErrorValue);
    CTelegramStream &operator>>(TLSendMessageAction &sendMessageActionValue);
    CTelegramStream &operator>>(TLServerDHInnerData &serverDHInnerDataValue);
    CTelegramStream &operator>>(TLServerDHParams &serverDHParamsValue);
    CTelegramStream &operator>>(TLSetClientDHParamsAnswer &setClientDHParamsAnswerValue);
    CTelegramStream &operator>>(TLShippingOption &shippingOptionValue);
    CTelegramStream &operator>>(TLStickerPack &stickerPackValue);
    CTelegramStream &operator>>(TLStorageFileType &storageFileTypeValue);
    CTelegramStream &operator>>(TLTopPeer &topPeerValue);
    CTelegramStream &operator>>(TLTopPeerCategory &topPeerCategoryValue);
    CTelegramStream &operator>>(TLTopPeerCategoryPeers &topPeerCategoryPeersValue);
    CTelegramStream &operator>>(TLUpdatesState &updatesStateValue);
    CTelegramStream &operator>>(TLUploadCdnFile &uploadCdnFileValue);
    CTelegramStream &operator>>(TLUploadFile &uploadFileValue);
    CTelegramStream &operator>>(TLUploadWebFile &uploadWebFileValue);
    CTelegramStream &operator>>(TLUserProfilePhoto &userProfilePhotoValue);
    CTelegramStream &operator>>(TLUserStatus &userStatusValue);
    CTelegramStream &operator>>(TLWallPaper &wallPaperValue);
    CTelegramStream &operator>>(TLAccountAuthorizations &accountAuthorizationsValue);
    CTelegramStream &operator>>(TLAuthSentCode &authSentCodeValue);
    CTelegramStream &operator>>(TLCdnConfig &cdnConfigValue);
    CTelegramStream &operator>>(TLChannelAdminLogEventsFilter &channelAdminLogEventsFilterValue);
    CTelegramStream &operator>>(TLChannelAdminRights &channelAdminRightsValue);
    CTelegramStream &operator>>(TLChannelBannedRights &channelBannedRightsValue);
    CTelegramStream &operator>>(TLChannelMessagesFilter &channelMessagesFilterValue);
    CTelegramStream &operator>>(TLChannelParticipant &channelParticipantValue);
    CTelegramStream &operator>>(TLChatPhoto &chatPhotoValue);
    CTelegramStream &operator>>(TLContactStatus &contactStatusValue);
    CTelegramStream &operator>>(TLDcOption &dcOptionValue);
    CTelegramStream &operator>>(TLDocumentAttribute &documentAttributeValue);
    CTelegramStream &operator>>(TLDraftMessage &draftMessageValue);
    CTelegramStream &operator>>(TLHelpConfigSimple &helpConfigSimpleValue);
    CTelegramStream &operator>>(TLInputChatPhoto &inputChatPhotoValue);
    CTelegramStream &operator>>(TLInputGame &inputGameValue);
    CTelegramStream &operator>>(TLInputNotifyPeer &inputNotifyPeerValue);
    CTelegramStream &operator>>(TLInputPaymentCredentials &inputPaymentCredentialsValue);
    CTelegramStream &operator>>(TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
    CTelegramStream &operator>>(TLInputPrivacyRule &inputPrivacyRuleValue);
    CTelegramStream &operator>>(TLInputStickerSetItem &inputStickerSetItemValue);
    CTelegramStream &operator>>(TLInputWebDocument &inputWebDocumentValue);
    CTelegramStream &operator>>(TLInvoice &invoiceValue);
    CTelegramStream &operator>>(TLKeyboardButton &keyboardButtonValue);
    CTelegramStream &operator>>(TLKeyboardButtonRow &keyboardButtonRowValue);
    CTelegramStream &operator>>(TLLangPackDifference &langPackDifferenceValue);
    CTelegramStream &operator>>(TLMessagesBotCallbackAnswer &messagesBotCallbackAnswerValue);
    CTelegramStream &operator>>(TLMessagesFilter &messagesFilterValue);
    CTelegramStream &operator>>(TLMessagesMessageEditData &messagesMessageEditDataValue);
    CTelegramStream &operator>>(TLNotifyPeer &notifyPeerValue);
    CTelegramStream &operator>>(TLPaymentRequestedInfo &paymentRequestedInfoValue);
    CTelegramStream &operator>>(TLPaymentsSavedInfo &paymentsSavedInfoValue);
    CTelegramStream &operator>>(TLPaymentsValidatedRequestedInfo &paymentsValidatedRequestedInfoValue);
    CTelegramStream &operator>>(TLPeerNotifySettings &peerNotifySettingsValue);
    CTelegramStream &operator>>(TLPeerSettings &peerSettingsValue);
    CTelegramStream &operator>>(TLPhoneCallProtocol &phoneCallProtocolValue);
    CTelegramStream &operator>>(TLPhoto &photoValue);
    CTelegramStream &operator>>(TLReplyMarkup &replyMarkupValue);
    CTelegramStream &operator>>(TLStickerSet &stickerSetValue);
    CTelegramStream &operator>>(TLUser &userValue);
    CTelegramStream &operator>>(TLWebDocument &webDocumentValue);
    CTelegramStream &operator>>(TLAccountPrivacyRules &accountPrivacyRulesValue);
    CTelegramStream &operator>>(TLAuthAuthorization &authAuthorizationValue);
    CTelegramStream &operator>>(TLBotInlineMessage &botInlineMessageValue);
    CTelegramStream &operator>>(TLChannelsChannelParticipant &channelsChannelParticipantValue);
    CTelegramStream &operator>>(TLChannelsChannelParticipants &channelsChannelParticipantsValue);
    CTelegramStream &operator>>(TLChat &chatValue);
    CTelegramStream &operator>>(TLChatFull &chatFullValue);
    CTelegramStream &operator>>(TLChatInvite &chatInviteValue);
    CTelegramStream &operator>>(TLConfig &configValue);
    CTelegramStream &operator>>(TLContactsBlocked &contactsBlockedValue);
    CTelegramStream &operator>>(TLContactsContacts &contactsContactsValue);
    CTelegramStream &operator>>(TLContactsFound &contactsFoundValue);
    CTelegramStream &operator>>(TLContactsImportedContacts &contactsImportedContactsValue);
    CTelegramStream &operator>>(TLContactsLink &contactsLinkValue);
    CTelegramStream &operator>>(TLContactsResolvedPeer &contactsResolvedPeerValue);
    CTelegramStream &operator>>(TLContactsTopPeers &contactsTopPeersValue);
    CTelegramStream &operator>>(TLDialog &dialogValue);
    CTelegramStream &operator>>(TLDocument &documentValue);
    CTelegramStream &operator>>(TLFoundGif &foundGifValue);
    CTelegramStream &operator>>(TLGame &gameValue);
    CTelegramStream &operator>>(TLHelpSupport &helpSupportValue);
    CTelegramStream &operator>>(TLInputBotInlineMessage &inputBotInlineMessageValue);
    CTelegramStream &operator>>(TLInputBotInlineResult &inputBotInlineResultValue);
    CTelegramStream &operator>>(TLInputMedia &inputMediaValue);
    CTelegramStream &operator>>(TLMessageAction &messageActionValue);
    CTelegramStream &operator>>(TLMessagesAllStickers &messagesAllStickersValue);
    CTelegramStream &operator>>(TLMessagesChatFull &messagesChatFullValue);
    CTelegramStream &operator>>(TLMessagesChats &messagesChatsValue);
    CTelegramStream &operator>>(TLMessagesFavedStickers &messagesFavedStickersValue);
    CTelegramStream &operator>>(TLMessagesFoundGifs &messagesFoundGifsValue);
    CTelegramStream &operator>>(TLMessagesHighScores &messagesHighScoresValue);
    CTelegramStream &operator>>(TLMessagesRecentStickers &messagesRecentStickersValue);
    CTelegramStream &operator>>(TLMessagesSavedGifs &messagesSavedGifsValue);
    CTelegramStream &operator>>(TLMessagesStickerSet &messagesStickerSetValue);
    CTelegramStream &operator>>(TLMessagesStickers &messagesStickersValue);
    CTelegramStream &operator>>(TLPageBlock &pageBlockValue);
    CTelegramStream &operator>>(TLPaymentsPaymentForm &paymentsPaymentFormValue);
    CTelegramStream &operator>>(TLPaymentsPaymentReceipt &paymentsPaymentReceiptValue);
    CTelegramStream &operator>>(TLPhoneCall &phoneCallValue);
    CTelegramStream &operator>>(TLPhonePhoneCall &phonePhoneCallValue);
    CTelegramStream &operator>>(TLPhotosPhoto &photosPhotoValue);
    CTelegramStream &operator>>(TLPhotosPhotos &photosPhotosValue);
    CTelegramStream &operator>>(TLStickerSetCovered &stickerSetCoveredValue);
    CTelegramStream &operator>>(TLUserFull &userFullValue);
    CTelegramStream &operator>>(TLBotInlineResult &botInlineResultValue);
    CTelegramStream &operator>>(TLMessagesArchivedStickers &messagesArchivedStickersValue);
    CTelegramStream &operator>>(TLMessagesBotResults &messagesBotResultsValue);
    CTelegramStream &operator>>(TLMessagesFeaturedStickers &messagesFeaturedStickersValue);
    CTelegramStream &operator>>(TLMessagesStickerSetInstallResult &messagesStickerSetInstallResultValue);
    CTelegramStream &operator>>(TLPage &pageValue);
    CTelegramStream &operator>>(TLRecentMeUrl &recentMeUrlValue);
    CTelegramStream &operator>>(TLWebPage &webPageValue);
    CTelegramStream &operator>>(TLHelpRecentMeUrls &helpRecentMeUrlsValue);
    CTelegramStream &operator>>(TLMessageMedia &messageMediaValue);
    CTelegramStream &operator>>(TLMessage &messageValue);
    CTelegramStream &operator>>(TLMessagesDialogs &messagesDialogsValue);
    CTelegramStream &operator>>(TLMessagesMessages &messagesMessagesValue);
    CTelegramStream &operator>>(TLMessagesPeerDialogs &messagesPeerDialogsValue);
    CTelegramStream &operator>>(TLUpdate &updateValue);
    CTelegramStream &operator>>(TLUpdates &updatesValue);
    CTelegramStream &operator>>(TLUpdatesChannelDifference &updatesChannelDifferenceValue);
    CTelegramStream &operator>>(TLUpdatesDifference &updatesDifferenceValue);
    CTelegramStream &operator>>(TLChannelAdminLogEventAction &channelAdminLogEventActionValue);
    CTelegramStream &operator>>(TLPaymentsPaymentResult &paymentsPaymentResultValue);
    CTelegramStream &operator>>(TLChannelAdminLogEvent &channelAdminLogEventValue);
    CTelegramStream &operator>>(TLChannelsAdminLogResults &channelsAdminLogResultsValue);
    // End of generated read operators

    // Generated write operators
    CTelegramStream &operator<<(const TLAccountDaysTTL &accountDaysTTLValue);
    CTelegramStream &operator<<(const TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
    CTelegramStream &operator<<(const TLChannelParticipantsFilter &channelParticipantsFilterValue);
    CTelegramStream &operator<<(const TLDataJSON &dataJSONValue);
    CTelegramStream &operator<<(const TLInlineBotSwitchPM &inlineBotSwitchPMValue);
    CTelegramStream &operator<<(const TLInputAppEvent &inputAppEventValue);
    CTelegramStream &operator<<(const TLInputBotInlineMessageID &inputBotInlineMessageIDValue);
    CTelegramStream &operator<<(const TLInputChannel &inputChannelValue);
    CTelegramStream &operator<<(const TLInputContact &inputContactValue);
    CTelegramStream &operator<<(const TLInputDocument &inputDocumentValue);
    CTelegramStream &operator<<(const TLInputEncryptedChat &inputEncryptedChatValue);
    CTelegramStream &operator<<(const TLInputEncryptedFile &inputEncryptedFileValue);
    CTelegramStream &operator<<(const TLInputFile &inputFileValue);
    CTelegramStream &operator<<(const TLInputFileLocation &inputFileLocationValue);
    CTelegramStream &operator<<(const TLInputGeoPoint &inputGeoPointValue);
    CTelegramStream &operator<<(const TLInputPeer &inputPeerValue);
    CTelegramStream &operator<<(const TLInputPhoneCall &inputPhoneCallValue);
    CTelegramStream &operator<<(const TLInputPhoto &inputPhotoValue);
    CTelegramStream &operator<<(const TLInputPrivacyKey &inputPrivacyKeyValue);
    CTelegramStream &operator<<(const TLInputStickerSet &inputStickerSetValue);
    CTelegramStream &operator<<(const TLInputStickeredMedia &inputStickeredMediaValue);
    CTelegramStream &operator<<(const TLInputUser &inputUserValue);
    CTelegramStream &operator<<(const TLInputWebFileLocation &inputWebFileLocationValue);
    CTelegramStream &operator<<(const TLLabeledPrice &labeledPriceValue);
    CTelegramStream &operator<<(const TLMaskCoords &maskCoordsValue);
    CTelegramStream &operator<<(const TLMessageEntity &messageEntityValue);
    CTelegramStream &operator<<(const TLMessageRange &messageRangeValue);
    CTelegramStream &operator<<(const TLPhoneCallDiscardReason &phoneCallDiscardReasonValue);
    CTelegramStream &operator<<(const TLPostAddress &postAddressValue);
    CTelegramStream &operator<<(const TLReportReason &reportReasonValue);
    CTelegramStream &operator<<(const TLSendMessageAction &sendMessageActionValue);
    CTelegramStream &operator<<(const TLShippingOption &shippingOptionValue);
    CTelegramStream &operator<<(const TLTopPeerCategory &topPeerCategoryValue);
    CTelegramStream &operator<<(const TLChannelAdminLogEventsFilter &channelAdminLogEventsFilterValue);
    CTelegramStream &operator<<(const TLChannelAdminRights &channelAdminRightsValue);
    CTelegramStream &operator<<(const TLChannelBannedRights &channelBannedRightsValue);
    CTelegramStream &operator<<(const TLChannelMessagesFilter &channelMessagesFilterValue);
    CTelegramStream &operator<<(const TLDocumentAttribute &documentAttributeValue);
    CTelegramStream &operator<<(const TLInputChatPhoto &inputChatPhotoValue);
    CTelegramStream &operator<<(const TLInputGame &inputGameValue);
    CTelegramStream &operator<<(const TLInputNotifyPeer &inputNotifyPeerValue);
    CTelegramStream &operator<<(const TLInputPaymentCredentials &inputPaymentCredentialsValue);
    CTelegramStream &operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
    CTelegramStream &operator<<(const TLInputPrivacyRule &inputPrivacyRuleValue);
    CTelegramStream &operator<<(const TLInputStickerSetItem &inputStickerSetItemValue);
    CTelegramStream &operator<<(const TLInputWebDocument &inputWebDocumentValue);
    CTelegramStream &operator<<(const TLInvoice &invoiceValue);
    CTelegramStream &operator<<(const TLKeyboardButton &keyboardButtonValue);
    CTelegramStream &operator<<(const TLKeyboardButtonRow &keyboardButtonRowValue);
    CTelegramStream &operator<<(const TLMessagesFilter &messagesFilterValue);
    CTelegramStream &operator<<(const TLPaymentRequestedInfo &paymentRequestedInfoValue);
    CTelegramStream &operator<<(const TLPhoneCallProtocol &phoneCallProtocolValue);
    CTelegramStream &operator<<(const TLReplyMarkup &replyMarkupValue);
    CTelegramStream &operator<<(const TLInputBotInlineMessage &inputBotInlineMessageValue);
    CTelegramStream &operator<<(const TLInputBotInlineResult &inputBotInlineResultValue);
    CTelegramStream &operator<<(const TLInputMedia &inputMediaValue);
    // End of generated write operators
};

inline CTelegramStream &CTelegramStream::operator>>(QString &str)
{
    QByteArray data;
    *this >> data;
    str = QString::fromUtf8(data);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const QString &str)
{
    *this << str.toUtf8();
    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(bool &data)
{
    TLBool val;
    *this >> val;
    data = val;
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const bool &data)
{
    TLBool val = data;
    *this << val;
    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(TLBool &data)
{
    *this >> data.tlType;
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const TLBool &data)
{
    *this << data.tlType;
    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(TLValue::Value &v)
{
    quint32 i;
    *this >> i;
    v = TLValue::Value(i);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const TLValue::Value v)
{
    *this << quint32(v);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(TLValue &v)
{
    quint32 i;
    *this >> i;
    v = TLValue(i);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const TLValue v)
{
    *this << quint32(v);
    return *this;
}

#endif // CTELEGRAMSTREAM_HPP
