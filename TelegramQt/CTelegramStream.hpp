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

class CTelegramStream : public CRawStreamEx
{
public:
    using CRawStreamEx::CRawStreamEx;
    using CRawStreamEx::operator <<;
    using CRawStreamEx::operator >>;

    CTelegramStream &operator>>(TLValue &v);
    CTelegramStream &operator<<(TLValue v);

    CTelegramStream &operator>>(QString &str);
    CTelegramStream &operator<<(const QString &str);

    CTelegramStream &operator>>(bool &data);
    CTelegramStream &operator<<(const bool &data);

    CTelegramStream &operator<<(const TLDcOption &dcOption);

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
    CTelegramStream &operator>>(TLAccountSentChangePhoneCode &accountSentChangePhoneCodeValue);
    CTelegramStream &operator>>(TLAudio &audioValue);
    CTelegramStream &operator>>(TLAuthCheckedPhone &authCheckedPhoneValue);
    CTelegramStream &operator>>(TLAuthExportedAuthorization &authExportedAuthorizationValue);
    CTelegramStream &operator>>(TLAuthPasswordRecovery &authPasswordRecoveryValue);
    CTelegramStream &operator>>(TLAuthSentCode &authSentCodeValue);
    CTelegramStream &operator>>(TLAuthorization &authorizationValue);
    CTelegramStream &operator>>(TLBotCommand &botCommandValue);
    CTelegramStream &operator>>(TLBotInfo &botInfoValue);
    CTelegramStream &operator>>(TLChannelParticipant &channelParticipantValue);
    CTelegramStream &operator>>(TLChannelParticipantRole &channelParticipantRoleValue);
    CTelegramStream &operator>>(TLChannelParticipantsFilter &channelParticipantsFilterValue);
    CTelegramStream &operator>>(TLChatParticipant &chatParticipantValue);
    CTelegramStream &operator>>(TLChatParticipants &chatParticipantsValue);
    CTelegramStream &operator>>(TLContact &contactValue);
    CTelegramStream &operator>>(TLContactBlocked &contactBlockedValue);
    CTelegramStream &operator>>(TLContactLink &contactLinkValue);
    CTelegramStream &operator>>(TLContactSuggested &contactSuggestedValue);
    CTelegramStream &operator>>(TLDisabledFeature &disabledFeatureValue);
    CTelegramStream &operator>>(TLEncryptedChat &encryptedChatValue);
    CTelegramStream &operator>>(TLEncryptedFile &encryptedFileValue);
    CTelegramStream &operator>>(TLEncryptedMessage &encryptedMessageValue);
    CTelegramStream &operator>>(TLError &errorValue);
    CTelegramStream &operator>>(TLExportedChatInvite &exportedChatInviteValue);
    CTelegramStream &operator>>(TLFileLocation &fileLocationValue);
    CTelegramStream &operator>>(TLGeoPoint &geoPointValue);
    CTelegramStream &operator>>(TLHelpAppChangelog &helpAppChangelogValue);
    CTelegramStream &operator>>(TLHelpAppUpdate &helpAppUpdateValue);
    CTelegramStream &operator>>(TLHelpInviteText &helpInviteTextValue);
    CTelegramStream &operator>>(TLHelpTermsOfService &helpTermsOfServiceValue);
    CTelegramStream &operator>>(TLImportedContact &importedContactValue);
    CTelegramStream &operator>>(TLInputAppEvent &inputAppEventValue);
    CTelegramStream &operator>>(TLInputAudio &inputAudioValue);
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
    CTelegramStream &operator>>(TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
    CTelegramStream &operator>>(TLInputPhoto &inputPhotoValue);
    CTelegramStream &operator>>(TLInputPhotoCrop &inputPhotoCropValue);
    CTelegramStream &operator>>(TLInputPrivacyKey &inputPrivacyKeyValue);
    CTelegramStream &operator>>(TLInputStickerSet &inputStickerSetValue);
    CTelegramStream &operator>>(TLInputUser &inputUserValue);
    CTelegramStream &operator>>(TLInputVideo &inputVideoValue);
    CTelegramStream &operator>>(TLKeyboardButton &keyboardButtonValue);
    CTelegramStream &operator>>(TLKeyboardButtonRow &keyboardButtonRowValue);
    CTelegramStream &operator>>(TLMessageEntity &messageEntityValue);
    CTelegramStream &operator>>(TLMessageGroup &messageGroupValue);
    CTelegramStream &operator>>(TLMessageRange &messageRangeValue);
    CTelegramStream &operator>>(TLMessagesAffectedHistory &messagesAffectedHistoryValue);
    CTelegramStream &operator>>(TLMessagesAffectedMessages &messagesAffectedMessagesValue);
    CTelegramStream &operator>>(TLMessagesDhConfig &messagesDhConfigValue);
    CTelegramStream &operator>>(TLMessagesFilter &messagesFilterValue);
    CTelegramStream &operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
    CTelegramStream &operator>>(TLNearestDc &nearestDcValue);
    CTelegramStream &operator>>(TLPeer &peerValue);
    CTelegramStream &operator>>(TLPeerNotifyEvents &peerNotifyEventsValue);
    CTelegramStream &operator>>(TLPeerNotifySettings &peerNotifySettingsValue);
    CTelegramStream &operator>>(TLPhotoSize &photoSizeValue);
    CTelegramStream &operator>>(TLPrivacyKey &privacyKeyValue);
    CTelegramStream &operator>>(TLPrivacyRule &privacyRuleValue);
    CTelegramStream &operator>>(TLReceivedNotifyMessage &receivedNotifyMessageValue);
    CTelegramStream &operator>>(TLReportReason &reportReasonValue);
    CTelegramStream &operator>>(TLSendMessageAction &sendMessageActionValue);
    CTelegramStream &operator>>(TLStickerPack &stickerPackValue);
    CTelegramStream &operator>>(TLStorageFileType &storageFileTypeValue);
    CTelegramStream &operator>>(TLUpdatesState &updatesStateValue);
    CTelegramStream &operator>>(TLUploadFile &uploadFileValue);
    CTelegramStream &operator>>(TLUserProfilePhoto &userProfilePhotoValue);
    CTelegramStream &operator>>(TLUserStatus &userStatusValue);
    CTelegramStream &operator>>(TLVideo &videoValue);
    CTelegramStream &operator>>(TLWallPaper &wallPaperValue);
    CTelegramStream &operator>>(TLAccountAuthorizations &accountAuthorizationsValue);
    CTelegramStream &operator>>(TLBotInlineMessage &botInlineMessageValue);
    CTelegramStream &operator>>(TLChannelMessagesFilter &channelMessagesFilterValue);
    CTelegramStream &operator>>(TLChatPhoto &chatPhotoValue);
    CTelegramStream &operator>>(TLContactStatus &contactStatusValue);
    CTelegramStream &operator>>(TLDcOption &dcOptionValue);
    CTelegramStream &operator>>(TLDialog &dialogValue);
    CTelegramStream &operator>>(TLDocumentAttribute &documentAttributeValue);
    CTelegramStream &operator>>(TLInputBotInlineMessage &inputBotInlineMessageValue);
    CTelegramStream &operator>>(TLInputBotInlineResult &inputBotInlineResultValue);
    CTelegramStream &operator>>(TLInputChatPhoto &inputChatPhotoValue);
    CTelegramStream &operator>>(TLInputMedia &inputMediaValue);
    CTelegramStream &operator>>(TLInputNotifyPeer &inputNotifyPeerValue);
    CTelegramStream &operator>>(TLInputPrivacyRule &inputPrivacyRuleValue);
    CTelegramStream &operator>>(TLNotifyPeer &notifyPeerValue);
    CTelegramStream &operator>>(TLPhoto &photoValue);
    CTelegramStream &operator>>(TLReplyMarkup &replyMarkupValue);
    CTelegramStream &operator>>(TLStickerSet &stickerSetValue);
    CTelegramStream &operator>>(TLUser &userValue);
    CTelegramStream &operator>>(TLAccountPrivacyRules &accountPrivacyRulesValue);
    CTelegramStream &operator>>(TLAuthAuthorization &authAuthorizationValue);
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
    CTelegramStream &operator>>(TLContactsSuggested &contactsSuggestedValue);
    CTelegramStream &operator>>(TLDocument &documentValue);
    CTelegramStream &operator>>(TLFoundGif &foundGifValue);
    CTelegramStream &operator>>(TLHelpSupport &helpSupportValue);
    CTelegramStream &operator>>(TLMessageAction &messageActionValue);
    CTelegramStream &operator>>(TLMessagesAllStickers &messagesAllStickersValue);
    CTelegramStream &operator>>(TLMessagesChatFull &messagesChatFullValue);
    CTelegramStream &operator>>(TLMessagesChats &messagesChatsValue);
    CTelegramStream &operator>>(TLMessagesFoundGifs &messagesFoundGifsValue);
    CTelegramStream &operator>>(TLMessagesSavedGifs &messagesSavedGifsValue);
    CTelegramStream &operator>>(TLMessagesStickerSet &messagesStickerSetValue);
    CTelegramStream &operator>>(TLMessagesStickers &messagesStickersValue);
    CTelegramStream &operator>>(TLPhotosPhoto &photosPhotoValue);
    CTelegramStream &operator>>(TLPhotosPhotos &photosPhotosValue);
    CTelegramStream &operator>>(TLUserFull &userFullValue);
    CTelegramStream &operator>>(TLWebPage &webPageValue);
    CTelegramStream &operator>>(TLBotInlineResult &botInlineResultValue);
    CTelegramStream &operator>>(TLMessageMedia &messageMediaValue);
    CTelegramStream &operator>>(TLMessagesBotResults &messagesBotResultsValue);
    CTelegramStream &operator>>(TLMessage &messageValue);
    CTelegramStream &operator>>(TLMessagesDialogs &messagesDialogsValue);
    CTelegramStream &operator>>(TLMessagesMessages &messagesMessagesValue);
    CTelegramStream &operator>>(TLUpdate &updateValue);
    CTelegramStream &operator>>(TLUpdates &updatesValue);
    CTelegramStream &operator>>(TLUpdatesChannelDifference &updatesChannelDifferenceValue);
    CTelegramStream &operator>>(TLUpdatesDifference &updatesDifferenceValue);
    // End of generated read operators

    // Generated write operators
    CTelegramStream &operator<<(const TLAccountDaysTTL &accountDaysTTLValue);
    CTelegramStream &operator<<(const TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
    CTelegramStream &operator<<(const TLChannelParticipantRole &channelParticipantRoleValue);
    CTelegramStream &operator<<(const TLChannelParticipantsFilter &channelParticipantsFilterValue);
    CTelegramStream &operator<<(const TLInputAppEvent &inputAppEventValue);
    CTelegramStream &operator<<(const TLInputAudio &inputAudioValue);
    CTelegramStream &operator<<(const TLInputChannel &inputChannelValue);
    CTelegramStream &operator<<(const TLInputContact &inputContactValue);
    CTelegramStream &operator<<(const TLInputDocument &inputDocumentValue);
    CTelegramStream &operator<<(const TLInputEncryptedChat &inputEncryptedChatValue);
    CTelegramStream &operator<<(const TLInputEncryptedFile &inputEncryptedFileValue);
    CTelegramStream &operator<<(const TLInputFile &inputFileValue);
    CTelegramStream &operator<<(const TLInputFileLocation &inputFileLocationValue);
    CTelegramStream &operator<<(const TLInputGeoPoint &inputGeoPointValue);
    CTelegramStream &operator<<(const TLInputPeer &inputPeerValue);
    CTelegramStream &operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
    CTelegramStream &operator<<(const TLInputPhoto &inputPhotoValue);
    CTelegramStream &operator<<(const TLInputPhotoCrop &inputPhotoCropValue);
    CTelegramStream &operator<<(const TLInputPrivacyKey &inputPrivacyKeyValue);
    CTelegramStream &operator<<(const TLInputStickerSet &inputStickerSetValue);
    CTelegramStream &operator<<(const TLInputUser &inputUserValue);
    CTelegramStream &operator<<(const TLInputVideo &inputVideoValue);
    CTelegramStream &operator<<(const TLKeyboardButton &keyboardButtonValue);
    CTelegramStream &operator<<(const TLKeyboardButtonRow &keyboardButtonRowValue);
    CTelegramStream &operator<<(const TLMessageEntity &messageEntityValue);
    CTelegramStream &operator<<(const TLMessageRange &messageRangeValue);
    CTelegramStream &operator<<(const TLMessagesFilter &messagesFilterValue);
    CTelegramStream &operator<<(const TLReportReason &reportReasonValue);
    CTelegramStream &operator<<(const TLSendMessageAction &sendMessageActionValue);
    CTelegramStream &operator<<(const TLChannelMessagesFilter &channelMessagesFilterValue);
    CTelegramStream &operator<<(const TLDocumentAttribute &documentAttributeValue);
    CTelegramStream &operator<<(const TLInputBotInlineMessage &inputBotInlineMessageValue);
    CTelegramStream &operator<<(const TLInputBotInlineResult &inputBotInlineResultValue);
    CTelegramStream &operator<<(const TLInputChatPhoto &inputChatPhotoValue);
    CTelegramStream &operator<<(const TLInputMedia &inputMediaValue);
    CTelegramStream &operator<<(const TLInputNotifyPeer &inputNotifyPeerValue);
    CTelegramStream &operator<<(const TLInputPrivacyRule &inputPrivacyRuleValue);
    CTelegramStream &operator<<(const TLReplyMarkup &replyMarkupValue);
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
    TLValue val;
    *this >> val;

    if (val == TLValue::BoolTrue) {
        data = true;
    } else if (val == TLValue::BoolFalse) {
        data = false;
    }

    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const bool &data)
{
    if (data) {
        *this << TLValue::BoolTrue;
    } else {
        *this << TLValue::BoolFalse;
    }

    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(TLValue &v)
{
    quint32 i;
    *this >> i;
    v = TLValue(i);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(TLValue v)
{
    *this << quint32(v);
    return *this;
}

#endif // CTELEGRAMSTREAM_HPP
