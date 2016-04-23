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

#ifndef CTELEGRAMSTREAM_HPP
#define CTELEGRAMSTREAM_HPP

#include <QVector>
#include <QString>

#include "CRawStream.hpp"
#include "TLTypes.hpp"

class CTelegramStream : public CRawStream
{
public:
    explicit CTelegramStream(QByteArray *data, bool write);
    explicit CTelegramStream(const QByteArray &data);

    explicit CTelegramStream(QIODevice *d = 0);

    using CRawStream::operator <<;
    using CRawStream::operator >>;

    CTelegramStream &operator>>(QByteArray &data);
    CTelegramStream &operator>>(QString &str);

    CTelegramStream &operator>>(bool &data);

    template <typename T>
    CTelegramStream &operator>>(TLVector<T> &v);

    // Generated read operators
    CTelegramStream &operator>>(TLAccountDaysTTL &accountDaysTTL);
    CTelegramStream &operator>>(TLAccountPassword &accountPassword);
    CTelegramStream &operator>>(TLAccountPasswordInputSettings &accountPasswordInputSettings);
    CTelegramStream &operator>>(TLAccountPasswordSettings &accountPasswordSettings);
    CTelegramStream &operator>>(TLAccountSentChangePhoneCode &accountSentChangePhoneCode);
    CTelegramStream &operator>>(TLAudio &audio);
    CTelegramStream &operator>>(TLAuthCheckedPhone &authCheckedPhone);
    CTelegramStream &operator>>(TLAuthExportedAuthorization &authExportedAuthorization);
    CTelegramStream &operator>>(TLAuthPasswordRecovery &authPasswordRecovery);
    CTelegramStream &operator>>(TLAuthSentCode &authSentCode);
    CTelegramStream &operator>>(TLAuthorization &authorization);
    CTelegramStream &operator>>(TLChatLocated &chatLocated);
    CTelegramStream &operator>>(TLChatParticipant &chatParticipant);
    CTelegramStream &operator>>(TLChatParticipants &chatParticipants);
    CTelegramStream &operator>>(TLContact &contact);
    CTelegramStream &operator>>(TLContactBlocked &contactBlocked);
    CTelegramStream &operator>>(TLContactFound &contactFound);
    CTelegramStream &operator>>(TLContactLink &contactLink);
    CTelegramStream &operator>>(TLContactSuggested &contactSuggested);
    CTelegramStream &operator>>(TLDcOption &dcOption);
    CTelegramStream &operator>>(TLDisabledFeature &disabledFeature);
    CTelegramStream &operator>>(TLEncryptedChat &encryptedChat);
    CTelegramStream &operator>>(TLEncryptedFile &encryptedFile);
    CTelegramStream &operator>>(TLEncryptedMessage &encryptedMessage);
    CTelegramStream &operator>>(TLError &error);
    CTelegramStream &operator>>(TLExportedChatInvite &exportedChatInvite);
    CTelegramStream &operator>>(TLFileLocation &fileLocation);
    CTelegramStream &operator>>(TLGeoPoint &geoPoint);
    CTelegramStream &operator>>(TLHelpAppUpdate &helpAppUpdate);
    CTelegramStream &operator>>(TLHelpInviteText &helpInviteText);
    CTelegramStream &operator>>(TLImportedContact &importedContact);
    CTelegramStream &operator>>(TLInputAppEvent &inputAppEvent);
    CTelegramStream &operator>>(TLInputAudio &inputAudio);
    CTelegramStream &operator>>(TLInputContact &inputContact);
    CTelegramStream &operator>>(TLInputDocument &inputDocument);
    CTelegramStream &operator>>(TLInputEncryptedChat &inputEncryptedChat);
    CTelegramStream &operator>>(TLInputEncryptedFile &inputEncryptedFile);
    CTelegramStream &operator>>(TLInputFile &inputFile);
    CTelegramStream &operator>>(TLInputFileLocation &inputFileLocation);
    CTelegramStream &operator>>(TLInputGeoChat &inputGeoChat);
    CTelegramStream &operator>>(TLInputGeoPoint &inputGeoPoint);
    CTelegramStream &operator>>(TLInputPeer &inputPeer);
    CTelegramStream &operator>>(TLInputPeerNotifyEvents &inputPeerNotifyEvents);
    CTelegramStream &operator>>(TLInputPeerNotifySettings &inputPeerNotifySettings);
    CTelegramStream &operator>>(TLInputPhoto &inputPhoto);
    CTelegramStream &operator>>(TLInputPhotoCrop &inputPhotoCrop);
    CTelegramStream &operator>>(TLInputPrivacyKey &inputPrivacyKey);
    CTelegramStream &operator>>(TLInputStickerSet &inputStickerSet);
    CTelegramStream &operator>>(TLInputUser &inputUser);
    CTelegramStream &operator>>(TLInputVideo &inputVideo);
    CTelegramStream &operator>>(TLMessagesAffectedHistory &messagesAffectedHistory);
    CTelegramStream &operator>>(TLMessagesAffectedMessages &messagesAffectedMessages);
    CTelegramStream &operator>>(TLMessagesDhConfig &messagesDhConfig);
    CTelegramStream &operator>>(TLMessagesFilter &messagesFilter);
    CTelegramStream &operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessage);
    CTelegramStream &operator>>(TLNearestDc &nearestDc);
    CTelegramStream &operator>>(TLPeer &peer);
    CTelegramStream &operator>>(TLPeerNotifyEvents &peerNotifyEvents);
    CTelegramStream &operator>>(TLPeerNotifySettings &peerNotifySettings);
    CTelegramStream &operator>>(TLPhotoSize &photoSize);
    CTelegramStream &operator>>(TLPrivacyKey &privacyKey);
    CTelegramStream &operator>>(TLPrivacyRule &privacyRule);
    CTelegramStream &operator>>(TLReceivedNotifyMessage &receivedNotifyMessage);
    CTelegramStream &operator>>(TLSendMessageAction &sendMessageAction);
    CTelegramStream &operator>>(TLStickerPack &stickerPack);
    CTelegramStream &operator>>(TLStickerSet &stickerSet);
    CTelegramStream &operator>>(TLStorageFileType &storageFileType);
    CTelegramStream &operator>>(TLUpdatesState &updatesState);
    CTelegramStream &operator>>(TLUploadFile &uploadFile);
    CTelegramStream &operator>>(TLUserProfilePhoto &userProfilePhoto);
    CTelegramStream &operator>>(TLUserStatus &userStatus);
    CTelegramStream &operator>>(TLVideo &video);
    CTelegramStream &operator>>(TLWallPaper &wallPaper);
    CTelegramStream &operator>>(TLAccountAuthorizations &accountAuthorizations);
    CTelegramStream &operator>>(TLChatPhoto &chatPhoto);
    CTelegramStream &operator>>(TLConfig &config);
    CTelegramStream &operator>>(TLContactStatus &contactStatus);
    CTelegramStream &operator>>(TLDialog &dialog);
    CTelegramStream &operator>>(TLDocumentAttribute &documentAttribute);
    CTelegramStream &operator>>(TLInputChatPhoto &inputChatPhoto);
    CTelegramStream &operator>>(TLInputMedia &inputMedia);
    CTelegramStream &operator>>(TLInputNotifyPeer &inputNotifyPeer);
    CTelegramStream &operator>>(TLInputPrivacyRule &inputPrivacyRule);
    CTelegramStream &operator>>(TLNotifyPeer &notifyPeer);
    CTelegramStream &operator>>(TLPhoto &photo);
    CTelegramStream &operator>>(TLUser &user);
    CTelegramStream &operator>>(TLWebPage &webPage);
    CTelegramStream &operator>>(TLAccountPrivacyRules &accountPrivacyRules);
    CTelegramStream &operator>>(TLAuthAuthorization &authAuthorization);
    CTelegramStream &operator>>(TLChat &chat);
    CTelegramStream &operator>>(TLChatFull &chatFull);
    CTelegramStream &operator>>(TLChatInvite &chatInvite);
    CTelegramStream &operator>>(TLContactsBlocked &contactsBlocked);
    CTelegramStream &operator>>(TLContactsContacts &contactsContacts);
    CTelegramStream &operator>>(TLContactsFound &contactsFound);
    CTelegramStream &operator>>(TLContactsImportedContacts &contactsImportedContacts);
    CTelegramStream &operator>>(TLContactsLink &contactsLink);
    CTelegramStream &operator>>(TLContactsSuggested &contactsSuggested);
    CTelegramStream &operator>>(TLDocument &document);
    CTelegramStream &operator>>(TLHelpSupport &helpSupport);
    CTelegramStream &operator>>(TLMessageAction &messageAction);
    CTelegramStream &operator>>(TLMessageMedia &messageMedia);
    CTelegramStream &operator>>(TLMessagesAllStickers &messagesAllStickers);
    CTelegramStream &operator>>(TLMessagesChatFull &messagesChatFull);
    CTelegramStream &operator>>(TLMessagesChats &messagesChats);
    CTelegramStream &operator>>(TLMessagesSentMessage &messagesSentMessage);
    CTelegramStream &operator>>(TLMessagesStickerSet &messagesStickerSet);
    CTelegramStream &operator>>(TLMessagesStickers &messagesStickers);
    CTelegramStream &operator>>(TLPhotosPhoto &photosPhoto);
    CTelegramStream &operator>>(TLPhotosPhotos &photosPhotos);
    CTelegramStream &operator>>(TLUserFull &userFull);
    CTelegramStream &operator>>(TLGeoChatMessage &geoChatMessage);
    CTelegramStream &operator>>(TLGeochatsLocated &geochatsLocated);
    CTelegramStream &operator>>(TLGeochatsMessages &geochatsMessages);
    CTelegramStream &operator>>(TLGeochatsStatedMessage &geochatsStatedMessage);
    CTelegramStream &operator>>(TLMessage &message);
    CTelegramStream &operator>>(TLMessagesDialogs &messagesDialogs);
    CTelegramStream &operator>>(TLMessagesMessages &messagesMessages);
    CTelegramStream &operator>>(TLUpdate &update);
    CTelegramStream &operator>>(TLUpdates &updates);
    CTelegramStream &operator>>(TLUpdatesDifference &updatesDifference);
    // End of generated read operators

    CTelegramStream &operator<<(const QByteArray &data);
    CTelegramStream &operator<<(const QString &str);

    CTelegramStream &operator<<(const bool &data);

    CTelegramStream &operator<<(const TLDcOption &dcOption);

    // Generated write operators
    CTelegramStream &operator<<(const TLAccountDaysTTL &accountDaysTTL);
    CTelegramStream &operator<<(const TLAccountPasswordInputSettings &accountPasswordInputSettings);
    CTelegramStream &operator<<(const TLInputAppEvent &inputAppEvent);
    CTelegramStream &operator<<(const TLInputAudio &inputAudio);
    CTelegramStream &operator<<(const TLInputContact &inputContact);
    CTelegramStream &operator<<(const TLInputDocument &inputDocument);
    CTelegramStream &operator<<(const TLInputEncryptedChat &inputEncryptedChat);
    CTelegramStream &operator<<(const TLInputEncryptedFile &inputEncryptedFile);
    CTelegramStream &operator<<(const TLInputFile &inputFile);
    CTelegramStream &operator<<(const TLInputFileLocation &inputFileLocation);
    CTelegramStream &operator<<(const TLInputGeoChat &inputGeoChat);
    CTelegramStream &operator<<(const TLInputGeoPoint &inputGeoPoint);
    CTelegramStream &operator<<(const TLInputPeer &inputPeer);
    CTelegramStream &operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettings);
    CTelegramStream &operator<<(const TLInputPhoto &inputPhoto);
    CTelegramStream &operator<<(const TLInputPhotoCrop &inputPhotoCrop);
    CTelegramStream &operator<<(const TLInputPrivacyKey &inputPrivacyKey);
    CTelegramStream &operator<<(const TLInputStickerSet &inputStickerSet);
    CTelegramStream &operator<<(const TLInputUser &inputUser);
    CTelegramStream &operator<<(const TLInputVideo &inputVideo);
    CTelegramStream &operator<<(const TLMessagesFilter &messagesFilter);
    CTelegramStream &operator<<(const TLSendMessageAction &sendMessageAction);
    CTelegramStream &operator<<(const TLDocumentAttribute &documentAttribute);
    CTelegramStream &operator<<(const TLInputChatPhoto &inputChatPhoto);
    CTelegramStream &operator<<(const TLInputMedia &inputMedia);
    CTelegramStream &operator<<(const TLInputNotifyPeer &inputNotifyPeer);
    CTelegramStream &operator<<(const TLInputPrivacyRule &inputPrivacyRule);
    // End of generated write operators

    template <typename T>
    CTelegramStream &operator<<(const TLVector<T> &v);

};

inline CTelegramStream &CTelegramStream::operator>>(QString &str)
{
    QByteArray data;
    *this >> data;
    str = QString::fromUtf8(data);
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

inline CTelegramStream &CTelegramStream::operator<<(const QString &str)
{
    return *this << str.toUtf8();
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

#endif // CTELEGRAMSTREAM_HPP
