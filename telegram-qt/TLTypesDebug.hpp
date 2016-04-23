/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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
QDebug operator<<(QDebug d, const TLAccountDaysTTL &accountDaysTTL);
QDebug operator<<(QDebug d, const TLAccountPassword &accountPassword);
QDebug operator<<(QDebug d, const TLAccountPasswordInputSettings &accountPasswordInputSettings);
QDebug operator<<(QDebug d, const TLAccountPasswordSettings &accountPasswordSettings);
QDebug operator<<(QDebug d, const TLAccountSentChangePhoneCode &accountSentChangePhoneCode);
QDebug operator<<(QDebug d, const TLAudio &audio);
QDebug operator<<(QDebug d, const TLAuthCheckedPhone &authCheckedPhone);
QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &authExportedAuthorization);
QDebug operator<<(QDebug d, const TLAuthPasswordRecovery &authPasswordRecovery);
QDebug operator<<(QDebug d, const TLAuthSentCode &authSentCode);
QDebug operator<<(QDebug d, const TLAuthorization &authorization);
QDebug operator<<(QDebug d, const TLChatLocated &chatLocated);
QDebug operator<<(QDebug d, const TLChatParticipant &chatParticipant);
QDebug operator<<(QDebug d, const TLChatParticipants &chatParticipants);
QDebug operator<<(QDebug d, const TLContact &contact);
QDebug operator<<(QDebug d, const TLContactBlocked &contactBlocked);
QDebug operator<<(QDebug d, const TLContactFound &contactFound);
QDebug operator<<(QDebug d, const TLContactLink &contactLink);
QDebug operator<<(QDebug d, const TLContactSuggested &contactSuggested);
QDebug operator<<(QDebug d, const TLDcOption &dcOption);
QDebug operator<<(QDebug d, const TLDisabledFeature &disabledFeature);
QDebug operator<<(QDebug d, const TLEncryptedChat &encryptedChat);
QDebug operator<<(QDebug d, const TLEncryptedFile &encryptedFile);
QDebug operator<<(QDebug d, const TLEncryptedMessage &encryptedMessage);
QDebug operator<<(QDebug d, const TLError &error);
QDebug operator<<(QDebug d, const TLExportedChatInvite &exportedChatInvite);
QDebug operator<<(QDebug d, const TLFileLocation &fileLocation);
QDebug operator<<(QDebug d, const TLGeoPoint &geoPoint);
QDebug operator<<(QDebug d, const TLHelpAppUpdate &helpAppUpdate);
QDebug operator<<(QDebug d, const TLHelpInviteText &helpInviteText);
QDebug operator<<(QDebug d, const TLImportedContact &importedContact);
QDebug operator<<(QDebug d, const TLInputAppEvent &inputAppEvent);
QDebug operator<<(QDebug d, const TLInputAudio &inputAudio);
QDebug operator<<(QDebug d, const TLInputContact &inputContact);
QDebug operator<<(QDebug d, const TLInputDocument &inputDocument);
QDebug operator<<(QDebug d, const TLInputEncryptedChat &inputEncryptedChat);
QDebug operator<<(QDebug d, const TLInputEncryptedFile &inputEncryptedFile);
QDebug operator<<(QDebug d, const TLInputFile &inputFile);
QDebug operator<<(QDebug d, const TLInputFileLocation &inputFileLocation);
QDebug operator<<(QDebug d, const TLInputGeoChat &inputGeoChat);
QDebug operator<<(QDebug d, const TLInputGeoPoint &inputGeoPoint);
QDebug operator<<(QDebug d, const TLInputPeer &inputPeer);
QDebug operator<<(QDebug d, const TLInputPeerNotifyEvents &inputPeerNotifyEvents);
QDebug operator<<(QDebug d, const TLInputPeerNotifySettings &inputPeerNotifySettings);
QDebug operator<<(QDebug d, const TLInputPhoto &inputPhoto);
QDebug operator<<(QDebug d, const TLInputPhotoCrop &inputPhotoCrop);
QDebug operator<<(QDebug d, const TLInputPrivacyKey &inputPrivacyKey);
QDebug operator<<(QDebug d, const TLInputStickerSet &inputStickerSet);
QDebug operator<<(QDebug d, const TLInputUser &inputUser);
QDebug operator<<(QDebug d, const TLInputVideo &inputVideo);
QDebug operator<<(QDebug d, const TLMessagesAffectedHistory &messagesAffectedHistory);
QDebug operator<<(QDebug d, const TLMessagesAffectedMessages &messagesAffectedMessages);
QDebug operator<<(QDebug d, const TLMessagesDhConfig &messagesDhConfig);
QDebug operator<<(QDebug d, const TLMessagesFilter &messagesFilter);
QDebug operator<<(QDebug d, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessage);
QDebug operator<<(QDebug d, const TLNearestDc &nearestDc);
QDebug operator<<(QDebug d, const TLPeer &peer);
QDebug operator<<(QDebug d, const TLPeerNotifyEvents &peerNotifyEvents);
QDebug operator<<(QDebug d, const TLPeerNotifySettings &peerNotifySettings);
QDebug operator<<(QDebug d, const TLPhotoSize &photoSize);
QDebug operator<<(QDebug d, const TLPrivacyKey &privacyKey);
QDebug operator<<(QDebug d, const TLPrivacyRule &privacyRule);
QDebug operator<<(QDebug d, const TLReceivedNotifyMessage &receivedNotifyMessage);
QDebug operator<<(QDebug d, const TLSendMessageAction &sendMessageAction);
QDebug operator<<(QDebug d, const TLStickerPack &stickerPack);
QDebug operator<<(QDebug d, const TLStickerSet &stickerSet);
QDebug operator<<(QDebug d, const TLStorageFileType &storageFileType);
QDebug operator<<(QDebug d, const TLUpdatesState &updatesState);
QDebug operator<<(QDebug d, const TLUploadFile &uploadFile);
QDebug operator<<(QDebug d, const TLUserProfilePhoto &userProfilePhoto);
QDebug operator<<(QDebug d, const TLUserStatus &userStatus);
QDebug operator<<(QDebug d, const TLVideo &video);
QDebug operator<<(QDebug d, const TLWallPaper &wallPaper);
QDebug operator<<(QDebug d, const TLAccountAuthorizations &accountAuthorizations);
QDebug operator<<(QDebug d, const TLChatPhoto &chatPhoto);
QDebug operator<<(QDebug d, const TLConfig &config);
QDebug operator<<(QDebug d, const TLContactStatus &contactStatus);
QDebug operator<<(QDebug d, const TLDialog &dialog);
QDebug operator<<(QDebug d, const TLDocumentAttribute &documentAttribute);
QDebug operator<<(QDebug d, const TLInputChatPhoto &inputChatPhoto);
QDebug operator<<(QDebug d, const TLInputMedia &inputMedia);
QDebug operator<<(QDebug d, const TLInputNotifyPeer &inputNotifyPeer);
QDebug operator<<(QDebug d, const TLInputPrivacyRule &inputPrivacyRule);
QDebug operator<<(QDebug d, const TLNotifyPeer &notifyPeer);
QDebug operator<<(QDebug d, const TLPhoto &photo);
QDebug operator<<(QDebug d, const TLUser &user);
QDebug operator<<(QDebug d, const TLWebPage &webPage);
QDebug operator<<(QDebug d, const TLAccountPrivacyRules &accountPrivacyRules);
QDebug operator<<(QDebug d, const TLAuthAuthorization &authAuthorization);
QDebug operator<<(QDebug d, const TLChat &chat);
QDebug operator<<(QDebug d, const TLChatFull &chatFull);
QDebug operator<<(QDebug d, const TLChatInvite &chatInvite);
QDebug operator<<(QDebug d, const TLContactsBlocked &contactsBlocked);
QDebug operator<<(QDebug d, const TLContactsContacts &contactsContacts);
QDebug operator<<(QDebug d, const TLContactsFound &contactsFound);
QDebug operator<<(QDebug d, const TLContactsImportedContacts &contactsImportedContacts);
QDebug operator<<(QDebug d, const TLContactsLink &contactsLink);
QDebug operator<<(QDebug d, const TLContactsSuggested &contactsSuggested);
QDebug operator<<(QDebug d, const TLDocument &document);
QDebug operator<<(QDebug d, const TLHelpSupport &helpSupport);
QDebug operator<<(QDebug d, const TLMessageAction &messageAction);
QDebug operator<<(QDebug d, const TLMessageMedia &messageMedia);
QDebug operator<<(QDebug d, const TLMessagesAllStickers &messagesAllStickers);
QDebug operator<<(QDebug d, const TLMessagesChatFull &messagesChatFull);
QDebug operator<<(QDebug d, const TLMessagesChats &messagesChats);
QDebug operator<<(QDebug d, const TLMessagesSentMessage &messagesSentMessage);
QDebug operator<<(QDebug d, const TLMessagesStickerSet &messagesStickerSet);
QDebug operator<<(QDebug d, const TLMessagesStickers &messagesStickers);
QDebug operator<<(QDebug d, const TLPhotosPhoto &photosPhoto);
QDebug operator<<(QDebug d, const TLPhotosPhotos &photosPhotos);
QDebug operator<<(QDebug d, const TLUserFull &userFull);
QDebug operator<<(QDebug d, const TLGeoChatMessage &geoChatMessage);
QDebug operator<<(QDebug d, const TLGeochatsLocated &geochatsLocated);
QDebug operator<<(QDebug d, const TLGeochatsMessages &geochatsMessages);
QDebug operator<<(QDebug d, const TLGeochatsStatedMessage &geochatsStatedMessage);
QDebug operator<<(QDebug d, const TLMessage &message);
QDebug operator<<(QDebug d, const TLMessagesDialogs &messagesDialogs);
QDebug operator<<(QDebug d, const TLMessagesMessages &messagesMessages);
QDebug operator<<(QDebug d, const TLUpdate &update);
QDebug operator<<(QDebug d, const TLUpdates &updates);
QDebug operator<<(QDebug d, const TLUpdatesDifference &updatesDifference);
// End of generated TLTypes debug operators

#endif // TLTYPESDEBUG_HPP
