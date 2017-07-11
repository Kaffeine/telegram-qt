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

// Generated TLTypes debug operators
QDebug operator<<(QDebug d, const TLAccountDaysTTL &accountDaysTTLValue);
QDebug operator<<(QDebug d, const TLAccountPassword &accountPasswordValue);
QDebug operator<<(QDebug d, const TLAccountPasswordInputSettings &accountPasswordInputSettingsValue);
QDebug operator<<(QDebug d, const TLAccountPasswordSettings &accountPasswordSettingsValue);
QDebug operator<<(QDebug d, const TLAccountSentChangePhoneCode &accountSentChangePhoneCodeValue);
QDebug operator<<(QDebug d, const TLAudio &audioValue);
QDebug operator<<(QDebug d, const TLAuthCheckedPhone &authCheckedPhoneValue);
QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &authExportedAuthorizationValue);
QDebug operator<<(QDebug d, const TLAuthPasswordRecovery &authPasswordRecoveryValue);
QDebug operator<<(QDebug d, const TLAuthSentCode &authSentCodeValue);
QDebug operator<<(QDebug d, const TLAuthorization &authorizationValue);
QDebug operator<<(QDebug d, const TLBotCommand &botCommandValue);
QDebug operator<<(QDebug d, const TLBotInfo &botInfoValue);
QDebug operator<<(QDebug d, const TLChannelParticipant &channelParticipantValue);
QDebug operator<<(QDebug d, const TLChannelParticipantRole &channelParticipantRoleValue);
QDebug operator<<(QDebug d, const TLChannelParticipantsFilter &channelParticipantsFilterValue);
QDebug operator<<(QDebug d, const TLChatParticipant &chatParticipantValue);
QDebug operator<<(QDebug d, const TLChatParticipants &chatParticipantsValue);
QDebug operator<<(QDebug d, const TLContact &contactValue);
QDebug operator<<(QDebug d, const TLContactBlocked &contactBlockedValue);
QDebug operator<<(QDebug d, const TLContactLink &contactLinkValue);
QDebug operator<<(QDebug d, const TLContactSuggested &contactSuggestedValue);
QDebug operator<<(QDebug d, const TLDisabledFeature &disabledFeatureValue);
QDebug operator<<(QDebug d, const TLEncryptedChat &encryptedChatValue);
QDebug operator<<(QDebug d, const TLEncryptedFile &encryptedFileValue);
QDebug operator<<(QDebug d, const TLEncryptedMessage &encryptedMessageValue);
QDebug operator<<(QDebug d, const TLError &errorValue);
QDebug operator<<(QDebug d, const TLExportedChatInvite &exportedChatInviteValue);
QDebug operator<<(QDebug d, const TLFileLocation &fileLocationValue);
QDebug operator<<(QDebug d, const TLGeoPoint &geoPointValue);
QDebug operator<<(QDebug d, const TLHelpAppChangelog &helpAppChangelogValue);
QDebug operator<<(QDebug d, const TLHelpAppUpdate &helpAppUpdateValue);
QDebug operator<<(QDebug d, const TLHelpInviteText &helpInviteTextValue);
QDebug operator<<(QDebug d, const TLHelpTermsOfService &helpTermsOfServiceValue);
QDebug operator<<(QDebug d, const TLImportedContact &importedContactValue);
QDebug operator<<(QDebug d, const TLInputAppEvent &inputAppEventValue);
QDebug operator<<(QDebug d, const TLInputAudio &inputAudioValue);
QDebug operator<<(QDebug d, const TLInputChannel &inputChannelValue);
QDebug operator<<(QDebug d, const TLInputContact &inputContactValue);
QDebug operator<<(QDebug d, const TLInputDocument &inputDocumentValue);
QDebug operator<<(QDebug d, const TLInputEncryptedChat &inputEncryptedChatValue);
QDebug operator<<(QDebug d, const TLInputEncryptedFile &inputEncryptedFileValue);
QDebug operator<<(QDebug d, const TLInputFile &inputFileValue);
QDebug operator<<(QDebug d, const TLInputFileLocation &inputFileLocationValue);
QDebug operator<<(QDebug d, const TLInputGeoPoint &inputGeoPointValue);
QDebug operator<<(QDebug d, const TLInputPeer &inputPeerValue);
QDebug operator<<(QDebug d, const TLInputPeerNotifyEvents &inputPeerNotifyEventsValue);
QDebug operator<<(QDebug d, const TLInputPeerNotifySettings &inputPeerNotifySettingsValue);
QDebug operator<<(QDebug d, const TLInputPhoto &inputPhotoValue);
QDebug operator<<(QDebug d, const TLInputPhotoCrop &inputPhotoCropValue);
QDebug operator<<(QDebug d, const TLInputPrivacyKey &inputPrivacyKeyValue);
QDebug operator<<(QDebug d, const TLInputStickerSet &inputStickerSetValue);
QDebug operator<<(QDebug d, const TLInputUser &inputUserValue);
QDebug operator<<(QDebug d, const TLInputVideo &inputVideoValue);
QDebug operator<<(QDebug d, const TLKeyboardButton &keyboardButtonValue);
QDebug operator<<(QDebug d, const TLKeyboardButtonRow &keyboardButtonRowValue);
QDebug operator<<(QDebug d, const TLMessageEntity &messageEntityValue);
QDebug operator<<(QDebug d, const TLMessageGroup &messageGroupValue);
QDebug operator<<(QDebug d, const TLMessageRange &messageRangeValue);
QDebug operator<<(QDebug d, const TLMessagesAffectedHistory &messagesAffectedHistoryValue);
QDebug operator<<(QDebug d, const TLMessagesAffectedMessages &messagesAffectedMessagesValue);
QDebug operator<<(QDebug d, const TLMessagesDhConfig &messagesDhConfigValue);
QDebug operator<<(QDebug d, const TLMessagesFilter &messagesFilterValue);
QDebug operator<<(QDebug d, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
QDebug operator<<(QDebug d, const TLNearestDc &nearestDcValue);
QDebug operator<<(QDebug d, const TLPeer &peerValue);
QDebug operator<<(QDebug d, const TLPeerNotifyEvents &peerNotifyEventsValue);
QDebug operator<<(QDebug d, const TLPeerNotifySettings &peerNotifySettingsValue);
QDebug operator<<(QDebug d, const TLPhotoSize &photoSizeValue);
QDebug operator<<(QDebug d, const TLPrivacyKey &privacyKeyValue);
QDebug operator<<(QDebug d, const TLPrivacyRule &privacyRuleValue);
QDebug operator<<(QDebug d, const TLReceivedNotifyMessage &receivedNotifyMessageValue);
QDebug operator<<(QDebug d, const TLReportReason &reportReasonValue);
QDebug operator<<(QDebug d, const TLSendMessageAction &sendMessageActionValue);
QDebug operator<<(QDebug d, const TLStickerPack &stickerPackValue);
QDebug operator<<(QDebug d, const TLStorageFileType &storageFileTypeValue);
QDebug operator<<(QDebug d, const TLTrue &trueValue);
QDebug operator<<(QDebug d, const TLUpdatesState &updatesStateValue);
QDebug operator<<(QDebug d, const TLUploadFile &uploadFileValue);
QDebug operator<<(QDebug d, const TLUserProfilePhoto &userProfilePhotoValue);
QDebug operator<<(QDebug d, const TLUserStatus &userStatusValue);
QDebug operator<<(QDebug d, const TLVideo &videoValue);
QDebug operator<<(QDebug d, const TLWallPaper &wallPaperValue);
QDebug operator<<(QDebug d, const TLAccountAuthorizations &accountAuthorizationsValue);
QDebug operator<<(QDebug d, const TLBotInlineMessage &botInlineMessageValue);
QDebug operator<<(QDebug d, const TLChannelMessagesFilter &channelMessagesFilterValue);
QDebug operator<<(QDebug d, const TLChatPhoto &chatPhotoValue);
QDebug operator<<(QDebug d, const TLContactStatus &contactStatusValue);
QDebug operator<<(QDebug d, const TLDcOption &dcOptionValue);
QDebug operator<<(QDebug d, const TLDialog &dialogValue);
QDebug operator<<(QDebug d, const TLDocumentAttribute &documentAttributeValue);
QDebug operator<<(QDebug d, const TLInputBotInlineMessage &inputBotInlineMessageValue);
QDebug operator<<(QDebug d, const TLInputBotInlineResult &inputBotInlineResultValue);
QDebug operator<<(QDebug d, const TLInputChatPhoto &inputChatPhotoValue);
QDebug operator<<(QDebug d, const TLInputMedia &inputMediaValue);
QDebug operator<<(QDebug d, const TLInputNotifyPeer &inputNotifyPeerValue);
QDebug operator<<(QDebug d, const TLInputPrivacyRule &inputPrivacyRuleValue);
QDebug operator<<(QDebug d, const TLNotifyPeer &notifyPeerValue);
QDebug operator<<(QDebug d, const TLPhoto &photoValue);
QDebug operator<<(QDebug d, const TLReplyMarkup &replyMarkupValue);
QDebug operator<<(QDebug d, const TLStickerSet &stickerSetValue);
QDebug operator<<(QDebug d, const TLUser &userValue);
QDebug operator<<(QDebug d, const TLAccountPrivacyRules &accountPrivacyRulesValue);
QDebug operator<<(QDebug d, const TLAuthAuthorization &authAuthorizationValue);
QDebug operator<<(QDebug d, const TLChannelsChannelParticipant &channelsChannelParticipantValue);
QDebug operator<<(QDebug d, const TLChannelsChannelParticipants &channelsChannelParticipantsValue);
QDebug operator<<(QDebug d, const TLChat &chatValue);
QDebug operator<<(QDebug d, const TLChatFull &chatFullValue);
QDebug operator<<(QDebug d, const TLChatInvite &chatInviteValue);
QDebug operator<<(QDebug d, const TLConfig &configValue);
QDebug operator<<(QDebug d, const TLContactsBlocked &contactsBlockedValue);
QDebug operator<<(QDebug d, const TLContactsContacts &contactsContactsValue);
QDebug operator<<(QDebug d, const TLContactsFound &contactsFoundValue);
QDebug operator<<(QDebug d, const TLContactsImportedContacts &contactsImportedContactsValue);
QDebug operator<<(QDebug d, const TLContactsLink &contactsLinkValue);
QDebug operator<<(QDebug d, const TLContactsResolvedPeer &contactsResolvedPeerValue);
QDebug operator<<(QDebug d, const TLContactsSuggested &contactsSuggestedValue);
QDebug operator<<(QDebug d, const TLDocument &documentValue);
QDebug operator<<(QDebug d, const TLFoundGif &foundGifValue);
QDebug operator<<(QDebug d, const TLHelpSupport &helpSupportValue);
QDebug operator<<(QDebug d, const TLMessageAction &messageActionValue);
QDebug operator<<(QDebug d, const TLMessagesAllStickers &messagesAllStickersValue);
QDebug operator<<(QDebug d, const TLMessagesChatFull &messagesChatFullValue);
QDebug operator<<(QDebug d, const TLMessagesChats &messagesChatsValue);
QDebug operator<<(QDebug d, const TLMessagesFoundGifs &messagesFoundGifsValue);
QDebug operator<<(QDebug d, const TLMessagesSavedGifs &messagesSavedGifsValue);
QDebug operator<<(QDebug d, const TLMessagesStickerSet &messagesStickerSetValue);
QDebug operator<<(QDebug d, const TLMessagesStickers &messagesStickersValue);
QDebug operator<<(QDebug d, const TLPhotosPhoto &photosPhotoValue);
QDebug operator<<(QDebug d, const TLPhotosPhotos &photosPhotosValue);
QDebug operator<<(QDebug d, const TLUserFull &userFullValue);
QDebug operator<<(QDebug d, const TLWebPage &webPageValue);
QDebug operator<<(QDebug d, const TLBotInlineResult &botInlineResultValue);
QDebug operator<<(QDebug d, const TLMessageMedia &messageMediaValue);
QDebug operator<<(QDebug d, const TLMessagesBotResults &messagesBotResultsValue);
QDebug operator<<(QDebug d, const TLMessage &messageValue);
QDebug operator<<(QDebug d, const TLMessagesDialogs &messagesDialogsValue);
QDebug operator<<(QDebug d, const TLMessagesMessages &messagesMessagesValue);
QDebug operator<<(QDebug d, const TLUpdate &updateValue);
QDebug operator<<(QDebug d, const TLUpdates &updatesValue);
QDebug operator<<(QDebug d, const TLUpdatesChannelDifference &updatesChannelDifferenceValue);
QDebug operator<<(QDebug d, const TLUpdatesDifference &updatesDifferenceValue);
// End of generated TLTypes debug operators

#endif // TLTYPESDEBUG_HPP
