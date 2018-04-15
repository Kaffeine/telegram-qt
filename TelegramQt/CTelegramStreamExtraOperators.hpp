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

#include "TLTypes.hpp"

class CTelegramStream;

//namespace Telegram {

// Generated write operators
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPassword &accountPasswordValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPasswordSettings &accountPasswordSettingsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountSentChangePhoneCode &accountSentChangePhoneCodeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAudio &audioValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthCheckedPhone &authCheckedPhoneValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthExportedAuthorization &authExportedAuthorizationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthPasswordRecovery &authPasswordRecoveryValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthSentCode &authSentCodeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthorization &authorizationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotCommand &botCommandValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInfo &botInfoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelParticipant &channelParticipantValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatParticipant &chatParticipantValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatParticipants &chatParticipantsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContact &contactValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactBlocked &contactBlockedValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactLink &contactLinkValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactSuggested &contactSuggestedValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDisabledFeature &disabledFeatureValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedChat &encryptedChatValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedFile &encryptedFileValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedMessage &encryptedMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLError &errorValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLExportedChatInvite &exportedChatInviteValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLFileLocation &fileLocationValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLGeoPoint &geoPointValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpAppChangelog &helpAppChangelogValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpAppUpdate &helpAppUpdateValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpInviteText &helpInviteTextValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpTermsOfService &helpTermsOfServiceValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLImportedContact &importedContactValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLInputPeerNotifyEvents &inputPeerNotifyEventsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageGroup &messageGroupValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAffectedHistory &messagesAffectedHistoryValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAffectedMessages &messagesAffectedMessagesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesDhConfig &messagesDhConfigValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLNearestDc &nearestDcValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeer &peerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerNotifyEvents &peerNotifyEventsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerNotifySettings &peerNotifySettingsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotoSize &photoSizeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPrivacyKey &privacyKeyValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPrivacyRule &privacyRuleValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLReceivedNotifyMessage &receivedNotifyMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerPack &stickerPackValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStorageFileType &storageFileTypeValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesState &updatesStateValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUploadFile &uploadFileValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUserProfilePhoto &userProfilePhotoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUserStatus &userStatusValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLVideo &videoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLWallPaper &wallPaperValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountAuthorizations &accountAuthorizationsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInlineMessage &botInlineMessageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLChatPhoto &chatPhotoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactStatus &contactStatusValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDcOption &dcOptionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDialog &dialogValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLNotifyPeer &notifyPeerValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhoto &photoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerSet &stickerSetValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUser &userValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPrivacyRules &accountPrivacyRulesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthAuthorization &authAuthorizationValue);
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
CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsSuggested &contactsSuggestedValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLDocument &documentValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLFoundGif &foundGifValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpSupport &helpSupportValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageAction &messageActionValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAllStickers &messagesAllStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesChatFull &messagesChatFullValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesChats &messagesChatsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesFoundGifs &messagesFoundGifsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesSavedGifs &messagesSavedGifsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickerSet &messagesStickerSetValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickers &messagesStickersValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotosPhoto &photosPhotoValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotosPhotos &photosPhotosValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUserFull &userFullValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLWebPage &webPageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInlineResult &botInlineResultValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageMedia &messageMediaValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesBotResults &messagesBotResultsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessage &messageValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesDialogs &messagesDialogsValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesMessages &messagesMessagesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdate &updateValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdates &updatesValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesChannelDifference &updatesChannelDifferenceValue);
CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesDifference &updatesDifferenceValue);
// End of generated write operators

//} // Telegram

#endif // CTELEGRAM_STREAM_EXTRAS_HPP
