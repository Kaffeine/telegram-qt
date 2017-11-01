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

#ifndef TLTYPES_HPP
#define TLTYPES_HPP

#include "TLValues.hpp"

#include <QMetaType>
#include <QVector>

template <typename T>
class TLVector : public QVector<T>
{
public:
    TLVector() : QVector<T>(), tlType(TLValue::Vector) { }
    explicit TLVector(int size) : QVector<T>(size), tlType(TLValue::Vector) { }
    TLVector(int size, const T &t) : QVector<T>(size, t), tlType(TLValue::Vector) { }
    TLVector(const TLVector<T> &v) : QVector<T>(v), tlType(v.tlType) { }
    TLVector(const QVector<T> &v) : QVector<T>(v), tlType(TLValue::Vector) { }
    TLVector(std::initializer_list<T> args) : QVector<T>(args) { }

    template<typename T2>
    auto optionalIsValid(const T2 &obj) const -> decltype(obj.isValid())
    {
        return obj.isValid();
    }
    auto optionalIsValid(...) const -> bool
    {
        return true;
    }

    bool isValid() const {
        if (tlType != TLValue::Vector) {
            return false;
        }
        for (int i = 0; i < QVector<T>::size(); ++i) {
            if (!optionalIsValid(QVector<T>::at(i))) {
                return false;
            }
        }
        return true;
    }

    TLVector &operator=(const TLVector &v) {
        tlType = v.tlType;
        QVector<T>::operator =(v);
        return *this;
    }

    TLValue tlType;
};

// Generated TLTypes
struct TLAccountDaysTTL {
    TLAccountDaysTTL() :
        days(0),
        tlType(TLValue::AccountDaysTTL) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountDaysTTL:
            return true;
        default:
            return false;
        };
    }
    quint32 days;
    TLValue tlType;
};

struct TLAccountPassword {
    TLAccountPassword() :
        hasRecovery(false),
        tlType(TLValue::AccountNoPassword) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountNoPassword:
        case TLValue::AccountPassword:
            return true;
        default:
            return false;
        };
    }
    QByteArray newSalt;
    QString emailUnconfirmedPattern;
    QByteArray currentSalt;
    QString hint;
    bool hasRecovery;
    TLValue tlType;
};

struct TLAccountPasswordInputSettings {
    TLAccountPasswordInputSettings() :
        flags(0),
        tlType(TLValue::AccountPasswordInputSettings) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountPasswordInputSettings:
            return true;
        default:
            return false;
        };
    }
    quint32 flags;
    QByteArray newSalt;
    QByteArray newPasswordHash;
    QString hint;
    QString email;
    TLValue tlType;
};

struct TLAccountPasswordSettings {
    TLAccountPasswordSettings() :
        tlType(TLValue::AccountPasswordSettings) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountPasswordSettings:
            return true;
        default:
            return false;
        };
    }
    QString email;
    TLValue tlType;
};

struct TLAccountSentChangePhoneCode {
    TLAccountSentChangePhoneCode() :
        sendCallTimeout(0),
        tlType(TLValue::AccountSentChangePhoneCode) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountSentChangePhoneCode:
            return true;
        default:
            return false;
        };
    }
    QString phoneCodeHash;
    quint32 sendCallTimeout;
    TLValue tlType;
};

struct TLAudio {
    TLAudio() :
        id(0),
        accessHash(0),
        date(0),
        duration(0),
        size(0),
        dcId(0),
        tlType(TLValue::AudioEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AudioEmpty:
        case TLValue::Audio:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 date;
    quint32 duration;
    QString mimeType;
    quint32 size;
    quint32 dcId;
    TLValue tlType;
};

struct TLAuthCheckedPhone {
    TLAuthCheckedPhone() :
        phoneRegistered(false),
        tlType(TLValue::AuthCheckedPhone) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthCheckedPhone:
            return true;
        default:
            return false;
        };
    }
    bool phoneRegistered;
    TLValue tlType;
};

struct TLAuthExportedAuthorization {
    TLAuthExportedAuthorization() :
        id(0),
        tlType(TLValue::AuthExportedAuthorization) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthExportedAuthorization:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    QByteArray bytes;
    TLValue tlType;
};

struct TLAuthPasswordRecovery {
    TLAuthPasswordRecovery() :
        tlType(TLValue::AuthPasswordRecovery) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthPasswordRecovery:
            return true;
        default:
            return false;
        };
    }
    QString emailPattern;
    TLValue tlType;
};

struct TLAuthSentCode {
    TLAuthSentCode() :
        phoneRegistered(false),
        sendCallTimeout(0),
        isPassword(false),
        tlType(TLValue::AuthSentCode) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthSentCode:
        case TLValue::AuthSentAppCode:
            return true;
        default:
            return false;
        };
    }
    bool phoneRegistered;
    QString phoneCodeHash;
    quint32 sendCallTimeout;
    bool isPassword;
    TLValue tlType;
};

struct TLAuthorization {
    TLAuthorization() :
        hash(0),
        flags(0),
        apiId(0),
        dateCreated(0),
        dateActive(0),
        tlType(TLValue::Authorization) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Authorization:
            return true;
        default:
            return false;
        };
    }
    quint64 hash;
    quint32 flags;
    QString deviceModel;
    QString platform;
    QString systemVersion;
    quint32 apiId;
    QString appName;
    QString appVersion;
    quint32 dateCreated;
    quint32 dateActive;
    QString ip;
    QString country;
    QString region;
    TLValue tlType;
};

struct TLBotCommand {
    TLBotCommand() :
        tlType(TLValue::BotCommand) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::BotCommand:
            return true;
        default:
            return false;
        };
    }
    QString command;
    QString description;
    TLValue tlType;
};

struct TLBotInfo {
    TLBotInfo() :
        userId(0),
        version(0),
        tlType(TLValue::BotInfoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::BotInfoEmpty:
        case TLValue::BotInfo:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 version;
    QString shareText;
    QString description;
    TLVector<TLBotCommand> commands;
    TLValue tlType;
};

struct TLChannelParticipant {
    TLChannelParticipant() :
        userId(0),
        date(0),
        inviterId(0),
        kickedBy(0),
        tlType(TLValue::ChannelParticipant) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelParticipant:
        case TLValue::ChannelParticipantSelf:
        case TLValue::ChannelParticipantModerator:
        case TLValue::ChannelParticipantEditor:
        case TLValue::ChannelParticipantKicked:
        case TLValue::ChannelParticipantCreator:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 date;
    quint32 inviterId;
    quint32 kickedBy;
    TLValue tlType;
};

struct TLChannelParticipantRole {
    TLChannelParticipantRole() :
        tlType(TLValue::ChannelRoleEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelRoleEmpty:
        case TLValue::ChannelRoleModerator:
        case TLValue::ChannelRoleEditor:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLChannelParticipantsFilter {
    TLChannelParticipantsFilter() :
        tlType(TLValue::ChannelParticipantsRecent) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelParticipantsRecent:
        case TLValue::ChannelParticipantsAdmins:
        case TLValue::ChannelParticipantsKicked:
        case TLValue::ChannelParticipantsBots:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLChatParticipant {
    TLChatParticipant() :
        userId(0),
        inviterId(0),
        date(0),
        tlType(TLValue::ChatParticipant) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatParticipant:
        case TLValue::ChatParticipantCreator:
        case TLValue::ChatParticipantAdmin:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 inviterId;
    quint32 date;
    TLValue tlType;
};

struct TLChatParticipants {
    TLChatParticipants() :
        flags(0),
        chatId(0),
        version(0),
        tlType(TLValue::ChatParticipantsForbidden) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatParticipantsForbidden:
        case TLValue::ChatParticipants:
            return true;
        default:
            return false;
        };
    }
    quint32 flags;
    quint32 chatId;
    TLChatParticipant selfParticipant;
    TLVector<TLChatParticipant> participants;
    quint32 version;
    TLValue tlType;
};

struct TLContact {
    TLContact() :
        userId(0),
        mutual(false),
        tlType(TLValue::Contact) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Contact:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    bool mutual;
    TLValue tlType;
};

struct TLContactBlocked {
    TLContactBlocked() :
        userId(0),
        date(0),
        tlType(TLValue::ContactBlocked) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactBlocked:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 date;
    TLValue tlType;
};

struct TLContactLink {
    TLContactLink() :
        tlType(TLValue::ContactLinkUnknown) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactLinkUnknown:
        case TLValue::ContactLinkNone:
        case TLValue::ContactLinkHasPhone:
        case TLValue::ContactLinkContact:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLContactSuggested {
    TLContactSuggested() :
        userId(0),
        mutualContacts(0),
        tlType(TLValue::ContactSuggested) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactSuggested:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 mutualContacts;
    TLValue tlType;
};

struct TLDisabledFeature {
    TLDisabledFeature() :
        tlType(TLValue::DisabledFeature) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DisabledFeature:
            return true;
        default:
            return false;
        };
    }
    QString feature;
    QString description;
    TLValue tlType;
};

struct TLEncryptedChat {
    TLEncryptedChat() :
        id(0),
        accessHash(0),
        date(0),
        adminId(0),
        participantId(0),
        keyFingerprint(0),
        tlType(TLValue::EncryptedChatEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::EncryptedChatEmpty:
        case TLValue::EncryptedChatWaiting:
        case TLValue::EncryptedChatRequested:
        case TLValue::EncryptedChat:
        case TLValue::EncryptedChatDiscarded:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    quint64 accessHash;
    quint32 date;
    quint32 adminId;
    quint32 participantId;
    QByteArray gA;
    QByteArray gAOrB;
    quint64 keyFingerprint;
    TLValue tlType;
};

struct TLEncryptedFile {
    TLEncryptedFile() :
        id(0),
        accessHash(0),
        size(0),
        dcId(0),
        keyFingerprint(0),
        tlType(TLValue::EncryptedFileEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::EncryptedFileEmpty:
        case TLValue::EncryptedFile:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 size;
    quint32 dcId;
    quint32 keyFingerprint;
    TLValue tlType;
};

struct TLEncryptedMessage {
    TLEncryptedMessage() :
        randomId(0),
        chatId(0),
        date(0),
        tlType(TLValue::EncryptedMessage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::EncryptedMessage:
        case TLValue::EncryptedMessageService:
            return true;
        default:
            return false;
        };
    }
    quint64 randomId;
    quint32 chatId;
    quint32 date;
    QByteArray bytes;
    TLEncryptedFile file;
    TLValue tlType;
};

struct TLError {
    TLError() :
        code(0),
        tlType(TLValue::Error) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Error:
            return true;
        default:
            return false;
        };
    }
    quint32 code;
    QString text;
    TLValue tlType;
};

struct TLExportedChatInvite {
    TLExportedChatInvite() :
        tlType(TLValue::ChatInviteEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatInviteEmpty:
        case TLValue::ChatInviteExported:
            return true;
        default:
            return false;
        };
    }
    QString link;
    TLValue tlType;
};

struct TLFileLocation {
    TLFileLocation() :
        volumeId(0),
        localId(0),
        secret(0),
        dcId(0),
        tlType(TLValue::FileLocationUnavailable) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::FileLocationUnavailable:
        case TLValue::FileLocation:
            return true;
        default:
            return false;
        };
    }
    quint64 volumeId;
    quint32 localId;
    quint64 secret;
    quint32 dcId;
    TLValue tlType;
};

struct TLGeoPoint {
    TLGeoPoint() :
        longitude(0),
        latitude(0),
        tlType(TLValue::GeoPointEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::GeoPointEmpty:
        case TLValue::GeoPoint:
            return true;
        default:
            return false;
        };
    }
    double longitude;
    double latitude;
    TLValue tlType;
};

struct TLHelpAppChangelog {
    TLHelpAppChangelog() :
        tlType(TLValue::HelpAppChangelogEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpAppChangelogEmpty:
        case TLValue::HelpAppChangelog:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType;
};

struct TLHelpAppUpdate {
    TLHelpAppUpdate() :
        id(0),
        critical(false),
        tlType(TLValue::HelpAppUpdate) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpAppUpdate:
        case TLValue::HelpNoAppUpdate:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    bool critical;
    QString url;
    QString text;
    TLValue tlType;
};

struct TLHelpInviteText {
    TLHelpInviteText() :
        tlType(TLValue::HelpInviteText) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpInviteText:
            return true;
        default:
            return false;
        };
    }
    QString message;
    TLValue tlType;
};

struct TLHelpTermsOfService {
    TLHelpTermsOfService() :
        tlType(TLValue::HelpTermsOfService) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpTermsOfService:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType;
};

struct TLImportedContact {
    TLImportedContact() :
        userId(0),
        clientId(0),
        tlType(TLValue::ImportedContact) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ImportedContact:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint64 clientId;
    TLValue tlType;
};

struct TLInputAppEvent {
    TLInputAppEvent() :
        time(0),
        peer(0),
        tlType(TLValue::InputAppEvent) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputAppEvent:
            return true;
        default:
            return false;
        };
    }
    double time;
    QString type;
    quint64 peer;
    QString data;
    TLValue tlType;
};

struct TLInputAudio {
    TLInputAudio() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputAudioEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputAudioEmpty:
        case TLValue::InputAudio:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputChannel {
    TLInputChannel() :
        channelId(0),
        accessHash(0),
        tlType(TLValue::InputChannelEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputChannelEmpty:
        case TLValue::InputChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 channelId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputContact {
    TLInputContact() :
        clientId(0),
        tlType(TLValue::InputPhoneContact) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPhoneContact:
            return true;
        default:
            return false;
        };
    }
    quint64 clientId;
    QString phone;
    QString firstName;
    QString lastName;
    TLValue tlType;
};

struct TLInputDocument {
    TLInputDocument() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputDocumentEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputDocumentEmpty:
        case TLValue::InputDocument:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputEncryptedChat {
    TLInputEncryptedChat() :
        chatId(0),
        accessHash(0),
        tlType(TLValue::InputEncryptedChat) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputEncryptedChat:
            return true;
        default:
            return false;
        };
    }
    quint32 chatId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputEncryptedFile {
    TLInputEncryptedFile() :
        id(0),
        parts(0),
        keyFingerprint(0),
        accessHash(0),
        tlType(TLValue::InputEncryptedFileEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputEncryptedFileEmpty:
        case TLValue::InputEncryptedFileUploaded:
        case TLValue::InputEncryptedFile:
        case TLValue::InputEncryptedFileBigUploaded:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint32 parts;
    QString md5Checksum;
    quint32 keyFingerprint;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputFile {
    TLInputFile() :
        id(0),
        parts(0),
        tlType(TLValue::InputFile) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputFile:
        case TLValue::InputFileBig:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint32 parts;
    QString name;
    QString md5Checksum;
    TLValue tlType;
};

struct TLInputFileLocation {
    TLInputFileLocation() :
        volumeId(0),
        localId(0),
        secret(0),
        id(0),
        accessHash(0),
        tlType(TLValue::InputFileLocation) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputFileLocation:
        case TLValue::InputVideoFileLocation:
        case TLValue::InputEncryptedFileLocation:
        case TLValue::InputAudioFileLocation:
        case TLValue::InputDocumentFileLocation:
            return true;
        default:
            return false;
        };
    }
    quint64 volumeId;
    quint32 localId;
    quint64 secret;
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputGeoPoint {
    TLInputGeoPoint() :
        latitude(0),
        longitude(0),
        tlType(TLValue::InputGeoPointEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputGeoPointEmpty:
        case TLValue::InputGeoPoint:
            return true;
        default:
            return false;
        };
    }
    double latitude;
    double longitude;
    TLValue tlType;
};

struct TLInputPeer {
    TLInputPeer() :
        chatId(0),
        userId(0),
        accessHash(0),
        channelId(0),
        tlType(TLValue::InputPeerEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPeerEmpty:
        case TLValue::InputPeerSelf:
        case TLValue::InputPeerChat:
        case TLValue::InputPeerUser:
        case TLValue::InputPeerChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 chatId;
    quint32 userId;
    quint64 accessHash;
    quint32 channelId;
    TLValue tlType;
};

struct TLInputPeerNotifyEvents {
    TLInputPeerNotifyEvents() :
        tlType(TLValue::InputPeerNotifyEventsEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPeerNotifyEventsEmpty:
        case TLValue::InputPeerNotifyEventsAll:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLInputPeerNotifySettings {
    TLInputPeerNotifySettings() :
        muteUntil(0),
        showPreviews(false),
        eventsMask(0),
        tlType(TLValue::InputPeerNotifySettings) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPeerNotifySettings:
            return true;
        default:
            return false;
        };
    }
    quint32 muteUntil;
    QString sound;
    bool showPreviews;
    quint32 eventsMask;
    TLValue tlType;
};

struct TLInputPhoto {
    TLInputPhoto() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputPhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPhotoEmpty:
        case TLValue::InputPhoto:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputPhotoCrop {
    TLInputPhotoCrop() :
        cropLeft(0),
        cropTop(0),
        cropWidth(0),
        tlType(TLValue::InputPhotoCropAuto) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPhotoCropAuto:
        case TLValue::InputPhotoCrop:
            return true;
        default:
            return false;
        };
    }
    double cropLeft;
    double cropTop;
    double cropWidth;
    TLValue tlType;
};

struct TLInputPrivacyKey {
    TLInputPrivacyKey() :
        tlType(TLValue::InputPrivacyKeyStatusTimestamp) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPrivacyKeyStatusTimestamp:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLInputStickerSet {
    TLInputStickerSet() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputStickerSetEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputStickerSetEmpty:
        case TLValue::InputStickerSetID:
        case TLValue::InputStickerSetShortName:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    QString shortName;
    TLValue tlType;
};

struct TLInputUser {
    TLInputUser() :
        userId(0),
        accessHash(0),
        tlType(TLValue::InputUserEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputUserEmpty:
        case TLValue::InputUserSelf:
        case TLValue::InputUser:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputVideo {
    TLInputVideo() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputVideoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputVideoEmpty:
        case TLValue::InputVideo:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLKeyboardButton {
    TLKeyboardButton() :
        tlType(TLValue::KeyboardButton) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::KeyboardButton:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType;
};

struct TLKeyboardButtonRow {
    TLKeyboardButtonRow() :
        tlType(TLValue::KeyboardButtonRow) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::KeyboardButtonRow:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLKeyboardButton> buttons;
    TLValue tlType;
};

struct TLMessageEntity {
    TLMessageEntity() :
        offset(0),
        length(0),
        tlType(TLValue::MessageEntityUnknown) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessageEntityUnknown:
        case TLValue::MessageEntityMention:
        case TLValue::MessageEntityHashtag:
        case TLValue::MessageEntityBotCommand:
        case TLValue::MessageEntityUrl:
        case TLValue::MessageEntityEmail:
        case TLValue::MessageEntityBold:
        case TLValue::MessageEntityItalic:
        case TLValue::MessageEntityCode:
        case TLValue::MessageEntityPre:
        case TLValue::MessageEntityTextUrl:
            return true;
        default:
            return false;
        };
    }
    quint32 offset;
    quint32 length;
    QString language;
    QString url;
    TLValue tlType;
};

struct TLMessageGroup {
    TLMessageGroup() :
        minId(0),
        maxId(0),
        count(0),
        date(0),
        tlType(TLValue::MessageGroup) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessageGroup:
            return true;
        default:
            return false;
        };
    }
    quint32 minId;
    quint32 maxId;
    quint32 count;
    quint32 date;
    TLValue tlType;
};

struct TLMessageRange {
    TLMessageRange() :
        minId(0),
        maxId(0),
        tlType(TLValue::MessageRange) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessageRange:
            return true;
        default:
            return false;
        };
    }
    quint32 minId;
    quint32 maxId;
    TLValue tlType;
};

struct TLMessagesAffectedHistory {
    TLMessagesAffectedHistory() :
        pts(0),
        ptsCount(0),
        offset(0),
        tlType(TLValue::MessagesAffectedHistory) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesAffectedHistory:
            return true;
        default:
            return false;
        };
    }
    quint32 pts;
    quint32 ptsCount;
    quint32 offset;
    TLValue tlType;
};

struct TLMessagesAffectedMessages {
    TLMessagesAffectedMessages() :
        pts(0),
        ptsCount(0),
        tlType(TLValue::MessagesAffectedMessages) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesAffectedMessages:
            return true;
        default:
            return false;
        };
    }
    quint32 pts;
    quint32 ptsCount;
    TLValue tlType;
};

struct TLMessagesDhConfig {
    TLMessagesDhConfig() :
        g(0),
        version(0),
        tlType(TLValue::MessagesDhConfigNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesDhConfigNotModified:
        case TLValue::MessagesDhConfig:
            return true;
        default:
            return false;
        };
    }
    QByteArray random;
    quint32 g;
    QByteArray p;
    quint32 version;
    TLValue tlType;
};

struct TLMessagesFilter {
    TLMessagesFilter() :
        tlType(TLValue::InputMessagesFilterEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputMessagesFilterEmpty:
        case TLValue::InputMessagesFilterPhotos:
        case TLValue::InputMessagesFilterVideo:
        case TLValue::InputMessagesFilterPhotoVideo:
        case TLValue::InputMessagesFilterPhotoVideoDocuments:
        case TLValue::InputMessagesFilterDocument:
        case TLValue::InputMessagesFilterAudio:
        case TLValue::InputMessagesFilterAudioDocuments:
        case TLValue::InputMessagesFilterUrl:
        case TLValue::InputMessagesFilterGif:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLMessagesSentEncryptedMessage {
    TLMessagesSentEncryptedMessage() :
        date(0),
        tlType(TLValue::MessagesSentEncryptedMessage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesSentEncryptedMessage:
        case TLValue::MessagesSentEncryptedFile:
            return true;
        default:
            return false;
        };
    }
    quint32 date;
    TLEncryptedFile file;
    TLValue tlType;
};

struct TLNearestDc {
    TLNearestDc() :
        thisDc(0),
        nearestDc(0),
        tlType(TLValue::NearestDc) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::NearestDc:
            return true;
        default:
            return false;
        };
    }
    QString country;
    quint32 thisDc;
    quint32 nearestDc;
    TLValue tlType;
};

struct TLPeer {
    TLPeer() :
        userId(0),
        chatId(0),
        channelId(0),
        tlType(TLValue::PeerUser) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PeerUser:
        case TLValue::PeerChat:
        case TLValue::PeerChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 chatId;
    quint32 channelId;
    TLValue tlType;
};

struct TLPeerNotifyEvents {
    TLPeerNotifyEvents() :
        tlType(TLValue::PeerNotifyEventsEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PeerNotifyEventsEmpty:
        case TLValue::PeerNotifyEventsAll:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLPeerNotifySettings {
    TLPeerNotifySettings() :
        muteUntil(0),
        showPreviews(false),
        eventsMask(0),
        tlType(TLValue::PeerNotifySettingsEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PeerNotifySettingsEmpty:
        case TLValue::PeerNotifySettings:
            return true;
        default:
            return false;
        };
    }
    quint32 muteUntil;
    QString sound;
    bool showPreviews;
    quint32 eventsMask;
    TLValue tlType;
};

struct TLPhotoSize {
    TLPhotoSize() :
        w(0),
        h(0),
        size(0),
        tlType(TLValue::PhotoSizeEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhotoSizeEmpty:
        case TLValue::PhotoSize:
        case TLValue::PhotoCachedSize:
            return true;
        default:
            return false;
        };
    }
    QString type;
    TLFileLocation location;
    quint32 w;
    quint32 h;
    quint32 size;
    QByteArray bytes;
    TLValue tlType;
};

struct TLPrivacyKey {
    TLPrivacyKey() :
        tlType(TLValue::PrivacyKeyStatusTimestamp) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PrivacyKeyStatusTimestamp:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLPrivacyRule {
    TLPrivacyRule() :
        tlType(TLValue::PrivacyValueAllowContacts) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PrivacyValueAllowContacts:
        case TLValue::PrivacyValueAllowAll:
        case TLValue::PrivacyValueAllowUsers:
        case TLValue::PrivacyValueDisallowContacts:
        case TLValue::PrivacyValueDisallowAll:
        case TLValue::PrivacyValueDisallowUsers:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint32> users;
    TLValue tlType;
};

struct TLReceivedNotifyMessage {
    TLReceivedNotifyMessage() :
        id(0),
        flags(0),
        tlType(TLValue::ReceivedNotifyMessage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ReceivedNotifyMessage:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    quint32 flags;
    TLValue tlType;
};

struct TLReportReason {
    TLReportReason() :
        tlType(TLValue::InputReportReasonSpam) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputReportReasonSpam:
        case TLValue::InputReportReasonViolence:
        case TLValue::InputReportReasonPornography:
        case TLValue::InputReportReasonOther:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType;
};

struct TLSendMessageAction {
    TLSendMessageAction() :
        progress(0),
        tlType(TLValue::SendMessageTypingAction) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::SendMessageTypingAction:
        case TLValue::SendMessageCancelAction:
        case TLValue::SendMessageRecordVideoAction:
        case TLValue::SendMessageUploadVideoAction:
        case TLValue::SendMessageRecordAudioAction:
        case TLValue::SendMessageUploadAudioAction:
        case TLValue::SendMessageUploadPhotoAction:
        case TLValue::SendMessageUploadDocumentAction:
        case TLValue::SendMessageGeoLocationAction:
        case TLValue::SendMessageChooseContactAction:
            return true;
        default:
            return false;
        };
    }
    quint32 progress;
    TLValue tlType;
};

struct TLStickerPack {
    TLStickerPack() :
        tlType(TLValue::StickerPack) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::StickerPack:
            return true;
        default:
            return false;
        };
    }
    QString emoticon;
    TLVector<quint64> documents;
    TLValue tlType;
};

struct TLStorageFileType {
    TLStorageFileType() :
        tlType(TLValue::StorageFileUnknown) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::StorageFileUnknown:
        case TLValue::StorageFileJpeg:
        case TLValue::StorageFileGif:
        case TLValue::StorageFilePng:
        case TLValue::StorageFilePdf:
        case TLValue::StorageFileMp3:
        case TLValue::StorageFileMov:
        case TLValue::StorageFilePartial:
        case TLValue::StorageFileMp4:
        case TLValue::StorageFileWebp:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLTrue {
    TLTrue() :
        tlType(TLValue::True) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::True:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLUpdatesState {
    TLUpdatesState() :
        pts(0),
        qts(0),
        date(0),
        seq(0),
        unreadCount(0),
        tlType(TLValue::UpdatesState) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UpdatesState:
            return true;
        default:
            return false;
        };
    }
    quint32 pts;
    quint32 qts;
    quint32 date;
    quint32 seq;
    quint32 unreadCount;
    TLValue tlType;
};

struct TLUploadFile {
    TLUploadFile() :
        mtime(0),
        tlType(TLValue::UploadFile) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UploadFile:
            return true;
        default:
            return false;
        };
    }
    TLStorageFileType type;
    quint32 mtime;
    QByteArray bytes;
    TLValue tlType;
};

struct TLUserProfilePhoto {
    TLUserProfilePhoto() :
        photoId(0),
        tlType(TLValue::UserProfilePhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UserProfilePhotoEmpty:
        case TLValue::UserProfilePhoto:
            return true;
        default:
            return false;
        };
    }
    quint64 photoId;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLUserStatus {
    TLUserStatus() :
        expires(0),
        wasOnline(0),
        tlType(TLValue::UserStatusEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UserStatusEmpty:
        case TLValue::UserStatusOnline:
        case TLValue::UserStatusOffline:
        case TLValue::UserStatusRecently:
        case TLValue::UserStatusLastWeek:
        case TLValue::UserStatusLastMonth:
            return true;
        default:
            return false;
        };
    }
    quint32 expires;
    quint32 wasOnline;
    TLValue tlType;
};

struct TLVideo {
    TLVideo() :
        id(0),
        accessHash(0),
        date(0),
        duration(0),
        size(0),
        dcId(0),
        w(0),
        h(0),
        tlType(TLValue::VideoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::VideoEmpty:
        case TLValue::Video:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 date;
    quint32 duration;
    QString mimeType;
    quint32 size;
    TLPhotoSize thumb;
    quint32 dcId;
    quint32 w;
    quint32 h;
    TLValue tlType;
};

struct TLWallPaper {
    TLWallPaper() :
        id(0),
        color(0),
        bgColor(0),
        tlType(TLValue::WallPaper) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::WallPaper:
        case TLValue::WallPaperSolid:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    QString title;
    TLVector<TLPhotoSize> sizes;
    quint32 color;
    quint32 bgColor;
    TLValue tlType;
};

struct TLAccountAuthorizations {
    TLAccountAuthorizations() :
        tlType(TLValue::AccountAuthorizations) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountAuthorizations:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLAuthorization> authorizations;
    TLValue tlType;
};

struct TLBotInlineMessage {
    TLBotInlineMessage() :
        flags(0),
        tlType(TLValue::BotInlineMessageMediaAuto) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::BotInlineMessageMediaAuto:
        case TLValue::BotInlineMessageText:
            return true;
        default:
            return false;
        };
    }
    bool noWebpage() const { return flags & 1 << 0; }
    QString caption;
    quint32 flags;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLValue tlType;
};

struct TLChannelMessagesFilter {
    TLChannelMessagesFilter() :
        flags(0),
        tlType(TLValue::ChannelMessagesFilterEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelMessagesFilterEmpty:
        case TLValue::ChannelMessagesFilter:
        case TLValue::ChannelMessagesFilterCollapsed:
            return true;
        default:
            return false;
        };
    }
    bool importantOnly() const { return flags & 1 << 0; }
    bool excludeNewMessages() const { return flags & 1 << 1; }
    quint32 flags;
    TLVector<TLMessageRange> ranges;
    TLValue tlType;
};

struct TLChatPhoto {
    TLChatPhoto() :
        tlType(TLValue::ChatPhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatPhotoEmpty:
        case TLValue::ChatPhoto:
            return true;
        default:
            return false;
        };
    }
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLContactStatus {
    TLContactStatus() :
        userId(0),
        tlType(TLValue::ContactStatus) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactStatus:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    TLUserStatus status;
    TLValue tlType;
};

struct TLDcOption {
    TLDcOption() :
        flags(0),
        id(0),
        port(0),
        tlType(TLValue::DcOption) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DcOption:
            return true;
        default:
            return false;
        };
    }
    bool ipv6() const { return flags & 1 << 0; }
    bool mediaOnly() const { return flags & 1 << 1; }
    quint32 flags;
    quint32 id;
    QString ipAddress;
    quint32 port;
    TLValue tlType;
};

struct TLDialog {
    TLDialog() :
        topMessage(0),
        readInboxMaxId(0),
        unreadCount(0),
        topImportantMessage(0),
        unreadImportantCount(0),
        pts(0),
        tlType(TLValue::Dialog) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Dialog:
        case TLValue::DialogChannel:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    quint32 topMessage;
    quint32 readInboxMaxId;
    quint32 unreadCount;
    TLPeerNotifySettings notifySettings;
    quint32 topImportantMessage;
    quint32 unreadImportantCount;
    quint32 pts;
    TLValue tlType;
};

struct TLDocumentAttribute {
    TLDocumentAttribute() :
        w(0),
        h(0),
        duration(0),
        tlType(TLValue::DocumentAttributeImageSize) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DocumentAttributeImageSize:
        case TLValue::DocumentAttributeAnimated:
        case TLValue::DocumentAttributeSticker:
        case TLValue::DocumentAttributeVideo:
        case TLValue::DocumentAttributeAudio:
        case TLValue::DocumentAttributeFilename:
            return true;
        default:
            return false;
        };
    }
    quint32 w;
    quint32 h;
    QString alt;
    TLInputStickerSet stickerset;
    quint32 duration;
    QString title;
    QString performer;
    QString fileName;
    TLValue tlType;
};

struct TLInputBotInlineMessage {
    TLInputBotInlineMessage() :
        flags(0),
        tlType(TLValue::InputBotInlineMessageMediaAuto) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputBotInlineMessageMediaAuto:
        case TLValue::InputBotInlineMessageText:
            return true;
        default:
            return false;
        };
    }
    bool noWebpage() const { return flags & 1 << 0; }
    QString caption;
    quint32 flags;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLValue tlType;
};

struct TLInputBotInlineResult {
    TLInputBotInlineResult() :
        flags(0),
        w(0),
        h(0),
        duration(0),
        tlType(TLValue::InputBotInlineResult) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputBotInlineResult:
            return true;
        default:
            return false;
        };
    }
    quint32 flags;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w;
    quint32 h;
    quint32 duration;
    TLInputBotInlineMessage sendMessage;
    TLValue tlType;
};

struct TLInputChatPhoto {
    TLInputChatPhoto() :
        tlType(TLValue::InputChatPhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputChatPhotoEmpty:
        case TLValue::InputChatUploadedPhoto:
        case TLValue::InputChatPhoto:
            return true;
        default:
            return false;
        };
    }
    TLInputFile file;
    TLInputPhotoCrop crop;
    TLInputPhoto id;
    TLValue tlType;
};

struct TLInputMedia {
    TLInputMedia() :
        duration(0),
        w(0),
        h(0),
        tlType(TLValue::InputMediaEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputMediaEmpty:
        case TLValue::InputMediaUploadedPhoto:
        case TLValue::InputMediaPhoto:
        case TLValue::InputMediaGeoPoint:
        case TLValue::InputMediaContact:
        case TLValue::InputMediaUploadedVideo:
        case TLValue::InputMediaUploadedThumbVideo:
        case TLValue::InputMediaVideo:
        case TLValue::InputMediaUploadedAudio:
        case TLValue::InputMediaAudio:
        case TLValue::InputMediaUploadedDocument:
        case TLValue::InputMediaUploadedThumbDocument:
        case TLValue::InputMediaDocument:
        case TLValue::InputMediaVenue:
        case TLValue::InputMediaGifExternal:
            return true;
        default:
            return false;
        };
    }
    TLInputFile file;
    QString caption;
    TLInputPhoto idInputPhoto;
    TLInputGeoPoint geoPoint;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 duration;
    quint32 w;
    quint32 h;
    QString mimeType;
    TLInputFile thumb;
    TLInputVideo idInputVideo;
    TLInputAudio idInputAudio;
    TLVector<TLDocumentAttribute> attributes;
    TLInputDocument idInputDocument;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString url;
    QString q;
    TLValue tlType;
};

struct TLInputNotifyPeer {
    TLInputNotifyPeer() :
        tlType(TLValue::InputNotifyPeer) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputNotifyPeer:
        case TLValue::InputNotifyUsers:
        case TLValue::InputNotifyChats:
        case TLValue::InputNotifyAll:
            return true;
        default:
            return false;
        };
    }
    TLInputPeer peer;
    TLValue tlType;
};

struct TLInputPrivacyRule {
    TLInputPrivacyRule() :
        tlType(TLValue::InputPrivacyValueAllowContacts) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPrivacyValueAllowContacts:
        case TLValue::InputPrivacyValueAllowAll:
        case TLValue::InputPrivacyValueAllowUsers:
        case TLValue::InputPrivacyValueDisallowContacts:
        case TLValue::InputPrivacyValueDisallowAll:
        case TLValue::InputPrivacyValueDisallowUsers:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLInputUser> users;
    TLValue tlType;
};

struct TLNotifyPeer {
    TLNotifyPeer() :
        tlType(TLValue::NotifyPeer) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::NotifyPeer:
        case TLValue::NotifyUsers:
        case TLValue::NotifyChats:
        case TLValue::NotifyAll:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    TLValue tlType;
};

struct TLPhoto {
    TLPhoto() :
        id(0),
        accessHash(0),
        date(0),
        tlType(TLValue::PhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhotoEmpty:
        case TLValue::Photo:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 date;
    TLVector<TLPhotoSize> sizes;
    TLValue tlType;
};

struct TLReplyMarkup {
    TLReplyMarkup() :
        flags(0),
        tlType(TLValue::ReplyKeyboardHide) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ReplyKeyboardHide:
        case TLValue::ReplyKeyboardForceReply:
        case TLValue::ReplyKeyboardMarkup:
            return true;
        default:
            return false;
        };
    }
    bool selective() const { return flags & 1 << 2; }
    bool singleUse() const { return flags & 1 << 1; }
    bool resize() const { return flags & 1 << 0; }
    quint32 flags;
    TLVector<TLKeyboardButtonRow> rows;
    TLValue tlType;
};

struct TLStickerSet {
    TLStickerSet() :
        flags(0),
        id(0),
        accessHash(0),
        count(0),
        hash(0),
        tlType(TLValue::StickerSet) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::StickerSet:
            return true;
        default:
            return false;
        };
    }
    bool installed() const { return flags & 1 << 0; }
    bool disabled() const { return flags & 1 << 1; }
    bool official() const { return flags & 1 << 2; }
    quint32 flags;
    quint64 id;
    quint64 accessHash;
    QString title;
    QString shortName;
    quint32 count;
    quint32 hash;
    TLValue tlType;
};

struct TLUser {
    TLUser() :
        id(0),
        flags(0),
        accessHash(0),
        botInfoVersion(0),
        tlType(TLValue::UserEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UserEmpty:
        case TLValue::User:
            return true;
        default:
            return false;
        };
    }
    bool self() const { return flags & 1 << 10; }
    bool contact() const { return flags & 1 << 11; }
    bool mutualContact() const { return flags & 1 << 12; }
    bool deleted() const { return flags & 1 << 13; }
    bool bot() const { return flags & 1 << 14; }
    bool botChatHistory() const { return flags & 1 << 15; }
    bool botNochats() const { return flags & 1 << 16; }
    bool verified() const { return flags & 1 << 17; }
    bool restricted() const { return flags & 1 << 18; }
    quint32 id;
    quint32 flags;
    quint64 accessHash;
    QString firstName;
    QString lastName;
    QString username;
    QString phone;
    TLUserProfilePhoto photo;
    TLUserStatus status;
    quint32 botInfoVersion;
    QString restrictionReason;
    QString botInlinePlaceholder;
    TLValue tlType;
};

struct TLAccountPrivacyRules {
    TLAccountPrivacyRules() :
        tlType(TLValue::AccountPrivacyRules) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountPrivacyRules:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPrivacyRule> rules;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLAuthAuthorization {
    TLAuthAuthorization() :
        tlType(TLValue::AuthAuthorization) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthAuthorization:
            return true;
        default:
            return false;
        };
    }
    TLUser user;
    TLValue tlType;
};

struct TLChannelsChannelParticipant {
    TLChannelsChannelParticipant() :
        tlType(TLValue::ChannelsChannelParticipant) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelsChannelParticipant:
            return true;
        default:
            return false;
        };
    }
    TLChannelParticipant participant;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLChannelsChannelParticipants {
    TLChannelsChannelParticipants() :
        count(0),
        tlType(TLValue::ChannelsChannelParticipants) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelsChannelParticipants:
            return true;
        default:
            return false;
        };
    }
    quint32 count;
    TLVector<TLChannelParticipant> participants;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLChat {
    TLChat() :
        id(0),
        flags(0),
        participantsCount(0),
        date(0),
        version(0),
        accessHash(0),
        tlType(TLValue::ChatEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatEmpty:
        case TLValue::Chat:
        case TLValue::ChatForbidden:
        case TLValue::Channel:
        case TLValue::ChannelForbidden:
            return true;
        default:
            return false;
        };
    }
    bool creator() const { return flags & 1 << 0; }
    bool kicked() const { return flags & 1 << 1; }
    bool left() const { return flags & 1 << 2; }
    bool adminsEnabled() const { return flags & 1 << 3; }
    bool admin() const { return flags & 1 << 4; }
    bool deactivated() const { return flags & 1 << 5; }
    bool editor() const { return flags & 1 << 3; }
    bool moderator() const { return flags & 1 << 4; }
    bool broadcast() const { return flags & 1 << 5; }
    bool verified() const { return flags & 1 << 7; }
    bool megagroup() const { return flags & 1 << 8; }
    bool restricted() const { return flags & 1 << 9; }
    quint32 id;
    quint32 flags;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount;
    quint32 date;
    quint32 version;
    TLInputChannel migratedTo;
    quint64 accessHash;
    QString username;
    QString restrictionReason;
    TLValue tlType;
};

struct TLChatFull {
    TLChatFull() :
        id(0),
        flags(0),
        participantsCount(0),
        adminsCount(0),
        kickedCount(0),
        readInboxMaxId(0),
        unreadCount(0),
        unreadImportantCount(0),
        migratedFromChatId(0),
        migratedFromMaxId(0),
        tlType(TLValue::ChatFull) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatFull:
        case TLValue::ChannelFull:
            return true;
        default:
            return false;
        };
    }
    bool canViewParticipants() const { return flags & 1 << 3; }
    quint32 id;
    TLChatParticipants participants;
    TLPhoto chatPhoto;
    TLPeerNotifySettings notifySettings;
    TLExportedChatInvite exportedInvite;
    TLVector<TLBotInfo> botInfo;
    quint32 flags;
    QString about;
    quint32 participantsCount;
    quint32 adminsCount;
    quint32 kickedCount;
    quint32 readInboxMaxId;
    quint32 unreadCount;
    quint32 unreadImportantCount;
    quint32 migratedFromChatId;
    quint32 migratedFromMaxId;
    TLValue tlType;
};

struct TLChatInvite {
    TLChatInvite() :
        flags(0),
        tlType(TLValue::ChatInviteAlready) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatInviteAlready:
        case TLValue::ChatInvite:
            return true;
        default:
            return false;
        };
    }
    bool channel() const { return flags & 1 << 0; }
    bool broadcast() const { return flags & 1 << 1; }
    bool isPublic() const { return flags & 1 << 2; }
    bool megagroup() const { return flags & 1 << 3; }
    TLChat chat;
    quint32 flags;
    QString title;
    TLValue tlType;
};

struct TLConfig {
    TLConfig() :
        date(0),
        expires(0),
        testMode(false),
        thisDc(0),
        chatSizeMax(0),
        megagroupSizeMax(0),
        forwardedCountMax(0),
        onlineUpdatePeriodMs(0),
        offlineBlurTimeoutMs(0),
        offlineIdleTimeoutMs(0),
        onlineCloudTimeoutMs(0),
        notifyCloudDelayMs(0),
        notifyDefaultDelayMs(0),
        chatBigSize(0),
        pushChatPeriodMs(0),
        pushChatLimit(0),
        savedGifsLimit(0),
        tlType(TLValue::Config) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Config:
            return true;
        default:
            return false;
        };
    }
    quint32 date;
    quint32 expires;
    bool testMode;
    quint32 thisDc;
    TLVector<TLDcOption> dcOptions;
    quint32 chatSizeMax;
    quint32 megagroupSizeMax;
    quint32 forwardedCountMax;
    quint32 onlineUpdatePeriodMs;
    quint32 offlineBlurTimeoutMs;
    quint32 offlineIdleTimeoutMs;
    quint32 onlineCloudTimeoutMs;
    quint32 notifyCloudDelayMs;
    quint32 notifyDefaultDelayMs;
    quint32 chatBigSize;
    quint32 pushChatPeriodMs;
    quint32 pushChatLimit;
    quint32 savedGifsLimit;
    TLVector<TLDisabledFeature> disabledFeatures;
    TLValue tlType;
};

struct TLContactsBlocked {
    TLContactsBlocked() :
        count(0),
        tlType(TLValue::ContactsBlocked) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsBlocked:
        case TLValue::ContactsBlockedSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContactBlocked> blocked;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLContactsContacts {
    TLContactsContacts() :
        tlType(TLValue::ContactsContactsNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsContactsNotModified:
        case TLValue::ContactsContacts:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContact> contacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsFound {
    TLContactsFound() :
        tlType(TLValue::ContactsFound) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsFound:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPeer> results;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsImportedContacts {
    TLContactsImportedContacts() :
        tlType(TLValue::ContactsImportedContacts) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsImportedContacts:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLImportedContact> imported;
    TLVector<quint64> retryContacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsLink {
    TLContactsLink() :
        tlType(TLValue::ContactsLink) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsLink:
            return true;
        default:
            return false;
        };
    }
    TLContactLink myLink;
    TLContactLink foreignLink;
    TLUser user;
    TLValue tlType;
};

struct TLContactsResolvedPeer {
    TLContactsResolvedPeer() :
        tlType(TLValue::ContactsResolvedPeer) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsResolvedPeer:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsSuggested {
    TLContactsSuggested() :
        tlType(TLValue::ContactsSuggested) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsSuggested:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContactSuggested> results;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLDocument {
    TLDocument() :
        id(0),
        accessHash(0),
        date(0),
        size(0),
        dcId(0),
        tlType(TLValue::DocumentEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DocumentEmpty:
        case TLValue::Document:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 date;
    QString mimeType;
    quint32 size;
    TLPhotoSize thumb;
    quint32 dcId;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType;
};

struct TLFoundGif {
    TLFoundGif() :
        w(0),
        h(0),
        tlType(TLValue::FoundGif) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::FoundGif:
        case TLValue::FoundGifCached:
            return true;
        default:
            return false;
        };
    }
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w;
    quint32 h;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType;
};

struct TLHelpSupport {
    TLHelpSupport() :
        tlType(TLValue::HelpSupport) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpSupport:
            return true;
        default:
            return false;
        };
    }
    QString phoneNumber;
    TLUser user;
    TLValue tlType;
};

struct TLMessageAction {
    TLMessageAction() :
        userId(0),
        inviterId(0),
        channelId(0),
        chatId(0),
        tlType(TLValue::MessageActionEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessageActionEmpty:
        case TLValue::MessageActionChatCreate:
        case TLValue::MessageActionChatEditTitle:
        case TLValue::MessageActionChatEditPhoto:
        case TLValue::MessageActionChatDeletePhoto:
        case TLValue::MessageActionChatAddUser:
        case TLValue::MessageActionChatDeleteUser:
        case TLValue::MessageActionChatJoinedByLink:
        case TLValue::MessageActionChannelCreate:
        case TLValue::MessageActionChatMigrateTo:
        case TLValue::MessageActionChannelMigrateFrom:
            return true;
        default:
            return false;
        };
    }
    QString title;
    TLVector<quint32> users;
    TLPhoto photo;
    quint32 userId;
    quint32 inviterId;
    quint32 channelId;
    quint32 chatId;
    TLValue tlType;
};

struct TLMessagesAllStickers {
    TLMessagesAllStickers() :
        hash(0),
        tlType(TLValue::MessagesAllStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesAllStickersNotModified:
        case TLValue::MessagesAllStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLStickerSet> sets;
    TLValue tlType;
};

struct TLMessagesChatFull {
    TLMessagesChatFull() :
        tlType(TLValue::MessagesChatFull) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesChatFull:
            return true;
        default:
            return false;
        };
    }
    TLChatFull fullChat;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesChats {
    TLMessagesChats() :
        tlType(TLValue::MessagesChats) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesChats:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLChat> chats;
    TLValue tlType;
};

struct TLMessagesFoundGifs {
    TLMessagesFoundGifs() :
        nextOffset(0),
        tlType(TLValue::MessagesFoundGifs) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesFoundGifs:
            return true;
        default:
            return false;
        };
    }
    quint32 nextOffset;
    TLVector<TLFoundGif> results;
    TLValue tlType;
};

struct TLMessagesSavedGifs {
    TLMessagesSavedGifs() :
        hash(0),
        tlType(TLValue::MessagesSavedGifsNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesSavedGifsNotModified:
        case TLValue::MessagesSavedGifs:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLDocument> gifs;
    TLValue tlType;
};

struct TLMessagesStickerSet {
    TLMessagesStickerSet() :
        tlType(TLValue::MessagesStickerSet) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesStickerSet:
            return true;
        default:
            return false;
        };
    }
    TLStickerSet set;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> documents;
    TLValue tlType;
};

struct TLMessagesStickers {
    TLMessagesStickers() :
        tlType(TLValue::MessagesStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesStickersNotModified:
        case TLValue::MessagesStickers:
            return true;
        default:
            return false;
        };
    }
    QString hash;
    TLVector<TLDocument> stickers;
    TLValue tlType;
};

struct TLPhotosPhoto {
    TLPhotosPhoto() :
        tlType(TLValue::PhotosPhoto) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhotosPhoto:
            return true;
        default:
            return false;
        };
    }
    TLPhoto photo;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPhotosPhotos {
    TLPhotosPhotos() :
        count(0),
        tlType(TLValue::PhotosPhotos) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhotosPhotos:
        case TLValue::PhotosPhotosSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPhoto> photos;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLUserFull {
    TLUserFull() :
        blocked(false),
        tlType(TLValue::UserFull) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UserFull:
            return true;
        default:
            return false;
        };
    }
    TLUser user;
    TLContactsLink link;
    TLPhoto profilePhoto;
    TLPeerNotifySettings notifySettings;
    bool blocked;
    TLBotInfo botInfo;
    TLValue tlType;
};

struct TLWebPage {
    TLWebPage() :
        id(0),
        date(0),
        flags(0),
        embedWidth(0),
        embedHeight(0),
        duration(0),
        tlType(TLValue::WebPageEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::WebPageEmpty:
        case TLValue::WebPagePending:
        case TLValue::WebPage:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint32 date;
    quint32 flags;
    QString url;
    QString displayUrl;
    QString type;
    QString siteName;
    QString title;
    QString description;
    TLPhoto photo;
    QString embedUrl;
    QString embedType;
    quint32 embedWidth;
    quint32 embedHeight;
    quint32 duration;
    QString author;
    TLDocument document;
    TLValue tlType;
};

struct TLBotInlineResult {
    TLBotInlineResult() :
        flags(0),
        w(0),
        h(0),
        duration(0),
        tlType(TLValue::BotInlineMediaResultDocument) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::BotInlineMediaResultDocument:
        case TLValue::BotInlineMediaResultPhoto:
        case TLValue::BotInlineResult:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString type;
    TLDocument document;
    TLBotInlineMessage sendMessage;
    TLPhoto photo;
    quint32 flags;
    QString title;
    QString description;
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w;
    quint32 h;
    quint32 duration;
    TLValue tlType;
};

struct TLMessageMedia {
    TLMessageMedia() :
        userId(0),
        tlType(TLValue::MessageMediaEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessageMediaEmpty:
        case TLValue::MessageMediaPhoto:
        case TLValue::MessageMediaVideo:
        case TLValue::MessageMediaGeo:
        case TLValue::MessageMediaContact:
        case TLValue::MessageMediaUnsupported:
        case TLValue::MessageMediaDocument:
        case TLValue::MessageMediaAudio:
        case TLValue::MessageMediaWebPage:
        case TLValue::MessageMediaVenue:
            return true;
        default:
            return false;
        };
    }
    TLPhoto photo;
    QString caption;
    TLVideo video;
    TLGeoPoint geo;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 userId;
    TLDocument document;
    TLAudio audio;
    TLWebPage webpage;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    TLValue tlType;
};

struct TLMessagesBotResults {
    TLMessagesBotResults() :
        flags(0),
        queryId(0),
        tlType(TLValue::MessagesBotResults) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesBotResults:
            return true;
        default:
            return false;
        };
    }
    bool gallery() const { return flags & 1 << 0; }
    quint32 flags;
    quint64 queryId;
    QString nextOffset;
    TLVector<TLBotInlineResult> results;
    TLValue tlType;
};

struct TLMessage {
    TLMessage() :
        id(0),
        flags(0),
        fromId(0),
        fwdDate(0),
        viaBotId(0),
        replyToMsgId(0),
        date(0),
        views(0),
        tlType(TLValue::MessageEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessageEmpty:
        case TLValue::Message:
        case TLValue::MessageService:
            return true;
        default:
            return false;
        };
    }
    bool unread() const { return flags & 1 << 0; }
    bool out() const { return flags & 1 << 1; }
    bool mentioned() const { return flags & 1 << 4; }
    bool mediaUnread() const { return flags & 1 << 5; }
    quint32 id;
    quint32 flags;
    quint32 fromId;
    TLPeer toId;
    TLPeer fwdFromId;
    quint32 fwdDate;
    quint32 viaBotId;
    quint32 replyToMsgId;
    quint32 date;
    QString message;
    TLMessageMedia media;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
    quint32 views;
    TLMessageAction action;
    TLValue tlType;
};

struct TLMessagesDialogs {
    TLMessagesDialogs() :
        count(0),
        tlType(TLValue::MessagesDialogs) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesDialogs:
        case TLValue::MessagesDialogsSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLDialog> dialogs;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLMessagesMessages {
    TLMessagesMessages() :
        count(0),
        flags(0),
        pts(0),
        tlType(TLValue::MessagesMessages) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesMessages:
        case TLValue::MessagesMessagesSlice:
        case TLValue::MessagesChannelMessages:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    quint32 flags;
    quint32 pts;
    TLVector<TLMessageGroup> collapsed;
    TLValue tlType;
};

struct TLUpdate {
    TLUpdate() :
        pts(0),
        ptsCount(0),
        id(0),
        randomId(0),
        userId(0),
        chatId(0),
        date(0),
        previous(false),
        authKeyId(0),
        qts(0),
        maxDate(0),
        inviterId(0),
        version(0),
        blocked(false),
        popup(false),
        maxId(0),
        channelId(0),
        views(0),
        enabled(false),
        isAdmin(false),
        queryId(0),
        tlType(TLValue::UpdateNewMessage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UpdateNewMessage:
        case TLValue::UpdateMessageID:
        case TLValue::UpdateDeleteMessages:
        case TLValue::UpdateUserTyping:
        case TLValue::UpdateChatUserTyping:
        case TLValue::UpdateChatParticipants:
        case TLValue::UpdateUserStatus:
        case TLValue::UpdateUserName:
        case TLValue::UpdateUserPhoto:
        case TLValue::UpdateContactRegistered:
        case TLValue::UpdateContactLink:
        case TLValue::UpdateNewAuthorization:
        case TLValue::UpdateNewEncryptedMessage:
        case TLValue::UpdateEncryptedChatTyping:
        case TLValue::UpdateEncryption:
        case TLValue::UpdateEncryptedMessagesRead:
        case TLValue::UpdateChatParticipantAdd:
        case TLValue::UpdateChatParticipantDelete:
        case TLValue::UpdateDcOptions:
        case TLValue::UpdateUserBlocked:
        case TLValue::UpdateNotifySettings:
        case TLValue::UpdateServiceNotification:
        case TLValue::UpdatePrivacy:
        case TLValue::UpdateUserPhone:
        case TLValue::UpdateReadHistoryInbox:
        case TLValue::UpdateReadHistoryOutbox:
        case TLValue::UpdateWebPage:
        case TLValue::UpdateReadMessagesContents:
        case TLValue::UpdateChannelTooLong:
        case TLValue::UpdateChannel:
        case TLValue::UpdateChannelGroup:
        case TLValue::UpdateNewChannelMessage:
        case TLValue::UpdateReadChannelInbox:
        case TLValue::UpdateDeleteChannelMessages:
        case TLValue::UpdateChannelMessageViews:
        case TLValue::UpdateChatAdmins:
        case TLValue::UpdateChatParticipantAdmin:
        case TLValue::UpdateNewStickerSet:
        case TLValue::UpdateStickerSetsOrder:
        case TLValue::UpdateStickerSets:
        case TLValue::UpdateSavedGifs:
        case TLValue::UpdateBotInlineQuery:
            return true;
        default:
            return false;
        };
    }
    TLMessage message;
    quint32 pts;
    quint32 ptsCount;
    quint32 id;
    quint64 randomId;
    TLVector<quint32> messages;
    quint32 userId;
    TLSendMessageAction action;
    quint32 chatId;
    TLChatParticipants participants;
    TLUserStatus status;
    QString firstName;
    QString lastName;
    QString username;
    quint32 date;
    TLUserProfilePhoto photo;
    bool previous;
    TLContactLink myLink;
    TLContactLink foreignLink;
    quint64 authKeyId;
    QString device;
    QString location;
    TLEncryptedMessage messageEncrypted;
    quint32 qts;
    TLEncryptedChat chat;
    quint32 maxDate;
    quint32 inviterId;
    quint32 version;
    TLVector<TLDcOption> dcOptions;
    bool blocked;
    TLNotifyPeer peerNotify;
    TLPeerNotifySettings notifySettings;
    QString type;
    QString messageString;
    TLMessageMedia media;
    bool popup;
    TLPrivacyKey key;
    TLVector<TLPrivacyRule> rules;
    QString phone;
    TLPeer peer;
    quint32 maxId;
    TLWebPage webpage;
    quint32 channelId;
    TLMessageGroup group;
    quint32 views;
    bool enabled;
    bool isAdmin;
    TLMessagesStickerSet stickerset;
    TLVector<quint64> order;
    quint64 queryId;
    QString query;
    QString offset;
    TLValue tlType;
};

struct TLUpdates {
    TLUpdates() :
        flags(0),
        id(0),
        userId(0),
        pts(0),
        ptsCount(0),
        date(0),
        fwdDate(0),
        viaBotId(0),
        replyToMsgId(0),
        fromId(0),
        chatId(0),
        seqStart(0),
        seq(0),
        tlType(TLValue::UpdatesTooLong) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UpdatesTooLong:
        case TLValue::UpdateShortMessage:
        case TLValue::UpdateShortChatMessage:
        case TLValue::UpdateShort:
        case TLValue::UpdatesCombined:
        case TLValue::Updates:
        case TLValue::UpdateShortSentMessage:
            return true;
        default:
            return false;
        };
    }
    bool unread() const { return flags & 1 << 0; }
    bool out() const { return flags & 1 << 1; }
    bool mentioned() const { return flags & 1 << 4; }
    bool mediaUnread() const { return flags & 1 << 5; }
    quint32 flags;
    quint32 id;
    quint32 userId;
    QString message;
    quint32 pts;
    quint32 ptsCount;
    quint32 date;
    TLPeer fwdFromId;
    quint32 fwdDate;
    quint32 viaBotId;
    quint32 replyToMsgId;
    TLVector<TLMessageEntity> entities;
    quint32 fromId;
    quint32 chatId;
    TLUpdate update;
    TLVector<TLUpdate> updates;
    TLVector<TLUser> users;
    TLVector<TLChat> chats;
    quint32 seqStart;
    quint32 seq;
    TLMessageMedia media;
    TLValue tlType;
};

struct TLUpdatesChannelDifference {
    TLUpdatesChannelDifference() :
        flags(0),
        pts(0),
        timeout(0),
        topMessage(0),
        topImportantMessage(0),
        readInboxMaxId(0),
        unreadCount(0),
        unreadImportantCount(0),
        tlType(TLValue::UpdatesChannelDifferenceEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UpdatesChannelDifferenceEmpty:
        case TLValue::UpdatesChannelDifferenceTooLong:
        case TLValue::UpdatesChannelDifference:
            return true;
        default:
            return false;
        };
    }
    bool final() const { return flags & 1 << 0; }
    quint32 flags;
    quint32 pts;
    quint32 timeout;
    quint32 topMessage;
    quint32 topImportantMessage;
    quint32 readInboxMaxId;
    quint32 unreadCount;
    quint32 unreadImportantCount;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLVector<TLMessage> newMessages;
    TLVector<TLUpdate> otherUpdates;
    TLValue tlType;
};

struct TLUpdatesDifference {
    TLUpdatesDifference() :
        date(0),
        seq(0),
        tlType(TLValue::UpdatesDifferenceEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UpdatesDifferenceEmpty:
        case TLValue::UpdatesDifference:
        case TLValue::UpdatesDifferenceSlice:
            return true;
        default:
            return false;
        };
    }
    quint32 date;
    quint32 seq;
    TLVector<TLMessage> newMessages;
    TLVector<TLEncryptedMessage> newEncryptedMessages;
    TLVector<TLUpdate> otherUpdates;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLUpdatesState state;
    TLUpdatesState intermediateState;
    TLValue tlType;
};

// End of generated TLTypes

Q_DECLARE_METATYPE(TLUploadFile)
Q_DECLARE_METATYPE(QVector<TLUser>)
Q_DECLARE_METATYPE(TLUpdates)

#endif // TLTYPES_HPP
