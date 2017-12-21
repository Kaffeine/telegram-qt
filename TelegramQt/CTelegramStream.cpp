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

#include "CTelegramStream_p.hpp"

#include <QtEndian>

#include <QIODevice>
#include <QDebug>

template CTelegramStream &CTelegramStream::operator>>(TLVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<quint64> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<QString> &v);

template CTelegramStream &CTelegramStream::operator<<(const TLVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<quint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<QString> &v);

template CTelegramStream &CTelegramStream::operator>>(TLNumber128 &v);
template CTelegramStream &CTelegramStream::operator>>(TLNumber256 &v);

template CTelegramStream &CTelegramStream::operator<<(const TLNumber128 &v);
template CTelegramStream &CTelegramStream::operator<<(const TLNumber256 &v);

// Generated vector read templates instancing
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLAuthorization> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLWallPaper> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactBlocked> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactStatus> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactSuggested> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLImportedContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChat> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPeer> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDcOption> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDisabledFeature> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessageEntity> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUpdate> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLStickerSet> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDialog> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDocumentAttribute> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessageGroup> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLBotInlineResult> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDocument> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLStickerPack> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLReceivedNotifyMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLFoundGif> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLEncryptedMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLBotCommand> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChatParticipant> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLKeyboardButton> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPhotoSize> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessageRange> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLKeyboardButtonRow> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChannelParticipant> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLBotInfo> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPhoto> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputChannel> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputAppEvent> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputBotInlineResult> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputPhoto> &v);
// End of generated vector read templates instancing

// Generated vector write templates instancing
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputChannel> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputUser> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputContact> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputAppEvent> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLMessageEntity> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputBotInlineResult> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputPhoto> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLDocumentAttribute> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLKeyboardButtonRow> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLMessageRange> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLKeyboardButton> &v);
// End of generated vector write templates instancing
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLDcOption> &v);

template <int Size>
CTelegramStream &CTelegramStream::operator>>(TLNumber<Size> &n)
{
    read(n.data, Size / 8);
    return *this;
}

template <int Size>
CTelegramStream &CTelegramStream::operator<<(const TLNumber<Size> &n)
{
    write(n.data, Size / 8);
    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLDcOption &dcOption)
{
    *this << dcOption.tlType;
    *this << dcOption.flags;
    *this << dcOption.id;
    *this << dcOption.ipAddress;
    *this << dcOption.port;

    return *this;
}

// Generated read operators implementation
CTelegramStream &CTelegramStream::operator>>(TLAccountDaysTTL &accountDaysTTLValue)
{
    TLAccountDaysTTL result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountDaysTTL:
        *this >> result.days;
        break;
    default:
        break;
    }

    accountDaysTTLValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountPassword &accountPasswordValue)
{
    TLAccountPassword result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountNoPassword:
        *this >> result.newSalt;
        *this >> result.emailUnconfirmedPattern;
        break;
    case TLValue::AccountPassword:
        *this >> result.currentSalt;
        *this >> result.newSalt;
        *this >> result.hint;
        *this >> result.hasRecovery;
        *this >> result.emailUnconfirmedPattern;
        break;
    default:
        break;
    }

    accountPasswordValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountPasswordInputSettings &accountPasswordInputSettingsValue)
{
    TLAccountPasswordInputSettings result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountPasswordInputSettings:
        *this >> result.flags;
        if (result.flags & 1 << 0) {
            *this >> result.newSalt;
        }
        if (result.flags & 1 << 0) {
            *this >> result.newPasswordHash;
        }
        if (result.flags & 1 << 0) {
            *this >> result.hint;
        }
        if (result.flags & 1 << 1) {
            *this >> result.email;
        }
        break;
    default:
        break;
    }

    accountPasswordInputSettingsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountPasswordSettings &accountPasswordSettingsValue)
{
    TLAccountPasswordSettings result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountPasswordSettings:
        *this >> result.email;
        break;
    default:
        break;
    }

    accountPasswordSettingsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountSentChangePhoneCode &accountSentChangePhoneCodeValue)
{
    TLAccountSentChangePhoneCode result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountSentChangePhoneCode:
        *this >> result.phoneCodeHash;
        *this >> result.sendCallTimeout;
        break;
    default:
        break;
    }

    accountSentChangePhoneCodeValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAudio &audioValue)
{
    TLAudio result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AudioEmpty:
        *this >> result.id;
        break;
    case TLValue::Audio:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.duration;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.dcId;
        break;
    default:
        break;
    }

    audioValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthCheckedPhone &authCheckedPhoneValue)
{
    TLAuthCheckedPhone result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AuthCheckedPhone:
        *this >> result.phoneRegistered;
        break;
    default:
        break;
    }

    authCheckedPhoneValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthExportedAuthorization &authExportedAuthorizationValue)
{
    TLAuthExportedAuthorization result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AuthExportedAuthorization:
        *this >> result.id;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    authExportedAuthorizationValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthPasswordRecovery &authPasswordRecoveryValue)
{
    TLAuthPasswordRecovery result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AuthPasswordRecovery:
        *this >> result.emailPattern;
        break;
    default:
        break;
    }

    authPasswordRecoveryValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthSentCode &authSentCodeValue)
{
    TLAuthSentCode result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AuthSentCode:
    case TLValue::AuthSentAppCode:
        *this >> result.phoneRegistered;
        *this >> result.phoneCodeHash;
        *this >> result.sendCallTimeout;
        *this >> result.isPassword;
        break;
    default:
        break;
    }

    authSentCodeValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthorization &authorizationValue)
{
    TLAuthorization result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::Authorization:
        *this >> result.hash;
        *this >> result.flags;
        *this >> result.deviceModel;
        *this >> result.platform;
        *this >> result.systemVersion;
        *this >> result.apiId;
        *this >> result.appName;
        *this >> result.appVersion;
        *this >> result.dateCreated;
        *this >> result.dateActive;
        *this >> result.ip;
        *this >> result.country;
        *this >> result.region;
        break;
    default:
        break;
    }

    authorizationValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLBotCommand &botCommandValue)
{
    TLBotCommand result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::BotCommand:
        *this >> result.command;
        *this >> result.description;
        break;
    default:
        break;
    }

    botCommandValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLBotInfo &botInfoValue)
{
    TLBotInfo result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::BotInfoEmpty:
        break;
    case TLValue::BotInfo:
        *this >> result.userId;
        *this >> result.version;
        *this >> result.shareText;
        *this >> result.description;
        *this >> result.commands;
        break;
    default:
        break;
    }

    botInfoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChannelParticipant &channelParticipantValue)
{
    TLChannelParticipant result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChannelParticipant:
        *this >> result.userId;
        *this >> result.date;
        break;
    case TLValue::ChannelParticipantSelf:
    case TLValue::ChannelParticipantModerator:
    case TLValue::ChannelParticipantEditor:
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.date;
        break;
    case TLValue::ChannelParticipantKicked:
        *this >> result.userId;
        *this >> result.kickedBy;
        *this >> result.date;
        break;
    case TLValue::ChannelParticipantCreator:
        *this >> result.userId;
        break;
    default:
        break;
    }

    channelParticipantValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChannelParticipantRole &channelParticipantRoleValue)
{
    TLChannelParticipantRole result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChannelRoleEmpty:
    case TLValue::ChannelRoleModerator:
    case TLValue::ChannelRoleEditor:
        break;
    default:
        break;
    }

    channelParticipantRoleValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChannelParticipantsFilter &channelParticipantsFilterValue)
{
    TLChannelParticipantsFilter result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChannelParticipantsRecent:
    case TLValue::ChannelParticipantsAdmins:
    case TLValue::ChannelParticipantsKicked:
    case TLValue::ChannelParticipantsBots:
        break;
    default:
        break;
    }

    channelParticipantsFilterValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatParticipant &chatParticipantValue)
{
    TLChatParticipant result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatParticipant:
    case TLValue::ChatParticipantAdmin:
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.date;
        break;
    case TLValue::ChatParticipantCreator:
        *this >> result.userId;
        break;
    default:
        break;
    }

    chatParticipantValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatParticipants &chatParticipantsValue)
{
    TLChatParticipants result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatParticipantsForbidden:
        *this >> result.flags;
        *this >> result.chatId;
        if (result.flags & 1 << 0) {
            *this >> result.selfParticipant;
        }
        break;
    case TLValue::ChatParticipants:
        *this >> result.chatId;
        *this >> result.participants;
        *this >> result.version;
        break;
    default:
        break;
    }

    chatParticipantsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContact &contactValue)
{
    TLContact result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::Contact:
        *this >> result.userId;
        *this >> result.mutual;
        break;
    default:
        break;
    }

    contactValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactBlocked &contactBlockedValue)
{
    TLContactBlocked result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactBlocked:
        *this >> result.userId;
        *this >> result.date;
        break;
    default:
        break;
    }

    contactBlockedValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactLink &contactLinkValue)
{
    TLContactLink result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactLinkUnknown:
    case TLValue::ContactLinkNone:
    case TLValue::ContactLinkHasPhone:
    case TLValue::ContactLinkContact:
        break;
    default:
        break;
    }

    contactLinkValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactSuggested &contactSuggestedValue)
{
    TLContactSuggested result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactSuggested:
        *this >> result.userId;
        *this >> result.mutualContacts;
        break;
    default:
        break;
    }

    contactSuggestedValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDisabledFeature &disabledFeatureValue)
{
    TLDisabledFeature result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::DisabledFeature:
        *this >> result.feature;
        *this >> result.description;
        break;
    default:
        break;
    }

    disabledFeatureValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedChat &encryptedChatValue)
{
    TLEncryptedChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::EncryptedChatEmpty:
    case TLValue::EncryptedChatDiscarded:
        *this >> result.id;
        break;
    case TLValue::EncryptedChatWaiting:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        break;
    case TLValue::EncryptedChatRequested:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        *this >> result.gA;
        break;
    case TLValue::EncryptedChat:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        *this >> result.gAOrB;
        *this >> result.keyFingerprint;
        break;
    default:
        break;
    }

    encryptedChatValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedFile &encryptedFileValue)
{
    TLEncryptedFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::EncryptedFileEmpty:
        break;
    case TLValue::EncryptedFile:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.size;
        *this >> result.dcId;
        *this >> result.keyFingerprint;
        break;
    default:
        break;
    }

    encryptedFileValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedMessage &encryptedMessageValue)
{
    TLEncryptedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::EncryptedMessage:
        *this >> result.randomId;
        *this >> result.chatId;
        *this >> result.date;
        *this >> result.bytes;
        *this >> result.file;
        break;
    case TLValue::EncryptedMessageService:
        *this >> result.randomId;
        *this >> result.chatId;
        *this >> result.date;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    encryptedMessageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLError &errorValue)
{
    TLError result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::Error:
        *this >> result.code;
        *this >> result.text;
        break;
    default:
        break;
    }

    errorValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLExportedChatInvite &exportedChatInviteValue)
{
    TLExportedChatInvite result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatInviteEmpty:
        break;
    case TLValue::ChatInviteExported:
        *this >> result.link;
        break;
    default:
        break;
    }

    exportedChatInviteValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLFileLocation &fileLocationValue)
{
    TLFileLocation result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::FileLocationUnavailable:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case TLValue::FileLocation:
        *this >> result.dcId;
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    default:
        break;
    }

    fileLocationValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeoPoint &geoPointValue)
{
    TLGeoPoint result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::GeoPointEmpty:
        break;
    case TLValue::GeoPoint:
        *this >> result.longitude;
        *this >> result.latitude;
        break;
    default:
        break;
    }

    geoPointValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpAppChangelog &helpAppChangelogValue)
{
    TLHelpAppChangelog result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::HelpAppChangelogEmpty:
        break;
    case TLValue::HelpAppChangelog:
        *this >> result.text;
        break;
    default:
        break;
    }

    helpAppChangelogValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpAppUpdate &helpAppUpdateValue)
{
    TLHelpAppUpdate result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::HelpAppUpdate:
        *this >> result.id;
        *this >> result.critical;
        *this >> result.url;
        *this >> result.text;
        break;
    case TLValue::HelpNoAppUpdate:
        break;
    default:
        break;
    }

    helpAppUpdateValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpInviteText &helpInviteTextValue)
{
    TLHelpInviteText result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::HelpInviteText:
        *this >> result.message;
        break;
    default:
        break;
    }

    helpInviteTextValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpTermsOfService &helpTermsOfServiceValue)
{
    TLHelpTermsOfService result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::HelpTermsOfService:
        *this >> result.text;
        break;
    default:
        break;
    }

    helpTermsOfServiceValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLImportedContact &importedContactValue)
{
    TLImportedContact result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ImportedContact:
        *this >> result.userId;
        *this >> result.clientId;
        break;
    default:
        break;
    }

    importedContactValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputAppEvent &inputAppEventValue)
{
    TLInputAppEvent result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputAppEvent:
        *this >> result.time;
        *this >> result.type;
        *this >> result.peer;
        *this >> result.data;
        break;
    default:
        break;
    }

    inputAppEventValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputAudio &inputAudioValue)
{
    TLInputAudio result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputAudioEmpty:
        break;
    case TLValue::InputAudio:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputAudioValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputChannel &inputChannelValue)
{
    TLInputChannel result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputChannelEmpty:
        break;
    case TLValue::InputChannel:
        *this >> result.channelId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputChannelValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputContact &inputContactValue)
{
    TLInputContact result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPhoneContact:
        *this >> result.clientId;
        *this >> result.phone;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    default:
        break;
    }

    inputContactValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputDocument &inputDocumentValue)
{
    TLInputDocument result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputDocumentEmpty:
        break;
    case TLValue::InputDocument:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputDocumentValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputEncryptedChat &inputEncryptedChatValue)
{
    TLInputEncryptedChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputEncryptedChat:
        *this >> result.chatId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputEncryptedChatValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputEncryptedFile &inputEncryptedFileValue)
{
    TLInputEncryptedFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputEncryptedFileEmpty:
        break;
    case TLValue::InputEncryptedFileUploaded:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.md5Checksum;
        *this >> result.keyFingerprint;
        break;
    case TLValue::InputEncryptedFile:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case TLValue::InputEncryptedFileBigUploaded:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.keyFingerprint;
        break;
    default:
        break;
    }

    inputEncryptedFileValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputFile &inputFileValue)
{
    TLInputFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputFile:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.name;
        *this >> result.md5Checksum;
        break;
    case TLValue::InputFileBig:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.name;
        break;
    default:
        break;
    }

    inputFileValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputFileLocation &inputFileLocationValue)
{
    TLInputFileLocation result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputFileLocation:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case TLValue::InputVideoFileLocation:
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputAudioFileLocation:
    case TLValue::InputDocumentFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputFileLocationValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputGeoPoint &inputGeoPointValue)
{
    TLInputGeoPoint result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputGeoPointEmpty:
        break;
    case TLValue::InputGeoPoint:
        *this >> result.latitude;
        *this >> result.longitude;
        break;
    default:
        break;
    }

    inputGeoPointValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeer &inputPeerValue)
{
    TLInputPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
        break;
    case TLValue::InputPeerChat:
        *this >> result.chatId;
        break;
    case TLValue::InputPeerUser:
        *this >> result.userId;
        *this >> result.accessHash;
        break;
    case TLValue::InputPeerChannel:
        *this >> result.channelId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputPeerValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeerNotifyEvents &inputPeerNotifyEventsValue)
{
    TLInputPeerNotifyEvents result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPeerNotifyEventsEmpty:
    case TLValue::InputPeerNotifyEventsAll:
        break;
    default:
        break;
    }

    inputPeerNotifyEventsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeerNotifySettings &inputPeerNotifySettingsValue)
{
    TLInputPeerNotifySettings result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPeerNotifySettings:
        *this >> result.muteUntil;
        *this >> result.sound;
        *this >> result.showPreviews;
        *this >> result.eventsMask;
        break;
    default:
        break;
    }

    inputPeerNotifySettingsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPhoto &inputPhotoValue)
{
    TLInputPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPhotoEmpty:
        break;
    case TLValue::InputPhoto:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputPhotoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPhotoCrop &inputPhotoCropValue)
{
    TLInputPhotoCrop result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPhotoCropAuto:
        break;
    case TLValue::InputPhotoCrop:
        *this >> result.cropLeft;
        *this >> result.cropTop;
        *this >> result.cropWidth;
        break;
    default:
        break;
    }

    inputPhotoCropValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPrivacyKey &inputPrivacyKeyValue)
{
    TLInputPrivacyKey result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }

    inputPrivacyKeyValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputStickerSet &inputStickerSetValue)
{
    TLInputStickerSet result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputStickerSetEmpty:
        break;
    case TLValue::InputStickerSetID:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case TLValue::InputStickerSetShortName:
        *this >> result.shortName;
        break;
    default:
        break;
    }

    inputStickerSetValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputUser &inputUserValue)
{
    TLInputUser result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
        break;
    case TLValue::InputUser:
        *this >> result.userId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputUserValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputVideo &inputVideoValue)
{
    TLInputVideo result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputVideoEmpty:
        break;
    case TLValue::InputVideo:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputVideoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLKeyboardButton &keyboardButtonValue)
{
    TLKeyboardButton result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::KeyboardButton:
        *this >> result.text;
        break;
    default:
        break;
    }

    keyboardButtonValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLKeyboardButtonRow &keyboardButtonRowValue)
{
    TLKeyboardButtonRow result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::KeyboardButtonRow:
        *this >> result.buttons;
        break;
    default:
        break;
    }

    keyboardButtonRowValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageEntity &messageEntityValue)
{
    TLMessageEntity result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessageEntityUnknown:
    case TLValue::MessageEntityMention:
    case TLValue::MessageEntityHashtag:
    case TLValue::MessageEntityBotCommand:
    case TLValue::MessageEntityUrl:
    case TLValue::MessageEntityEmail:
    case TLValue::MessageEntityBold:
    case TLValue::MessageEntityItalic:
    case TLValue::MessageEntityCode:
        *this >> result.offset;
        *this >> result.length;
        break;
    case TLValue::MessageEntityPre:
        *this >> result.offset;
        *this >> result.length;
        *this >> result.language;
        break;
    case TLValue::MessageEntityTextUrl:
        *this >> result.offset;
        *this >> result.length;
        *this >> result.url;
        break;
    default:
        break;
    }

    messageEntityValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageGroup &messageGroupValue)
{
    TLMessageGroup result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessageGroup:
        *this >> result.minId;
        *this >> result.maxId;
        *this >> result.count;
        *this >> result.date;
        break;
    default:
        break;
    }

    messageGroupValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageRange &messageRangeValue)
{
    TLMessageRange result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessageRange:
        *this >> result.minId;
        *this >> result.maxId;
        break;
    default:
        break;
    }

    messageRangeValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesAffectedHistory &messagesAffectedHistoryValue)
{
    TLMessagesAffectedHistory result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesAffectedHistory:
        *this >> result.pts;
        *this >> result.ptsCount;
        *this >> result.offset;
        break;
    default:
        break;
    }

    messagesAffectedHistoryValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesAffectedMessages &messagesAffectedMessagesValue)
{
    TLMessagesAffectedMessages result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesAffectedMessages:
        *this >> result.pts;
        *this >> result.ptsCount;
        break;
    default:
        break;
    }

    messagesAffectedMessagesValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesDhConfig &messagesDhConfigValue)
{
    TLMessagesDhConfig result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesDhConfigNotModified:
        *this >> result.random;
        break;
    case TLValue::MessagesDhConfig:
        *this >> result.g;
        *this >> result.p;
        *this >> result.version;
        *this >> result.random;
        break;
    default:
        break;
    }

    messagesDhConfigValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesFilter &messagesFilterValue)
{
    TLMessagesFilter result;

    *this >> result.tlType;

    switch (result.tlType) {
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
        break;
    default:
        break;
    }

    messagesFilterValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue)
{
    TLMessagesSentEncryptedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesSentEncryptedMessage:
        *this >> result.date;
        break;
    case TLValue::MessagesSentEncryptedFile:
        *this >> result.date;
        *this >> result.file;
        break;
    default:
        break;
    }

    messagesSentEncryptedMessageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNearestDc &nearestDcValue)
{
    TLNearestDc result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::NearestDc:
        *this >> result.country;
        *this >> result.thisDc;
        *this >> result.nearestDc;
        break;
    default:
        break;
    }

    nearestDcValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeer &peerValue)
{
    TLPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PeerUser:
        *this >> result.userId;
        break;
    case TLValue::PeerChat:
        *this >> result.chatId;
        break;
    case TLValue::PeerChannel:
        *this >> result.channelId;
        break;
    default:
        break;
    }

    peerValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeerNotifyEvents &peerNotifyEventsValue)
{
    TLPeerNotifyEvents result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PeerNotifyEventsEmpty:
    case TLValue::PeerNotifyEventsAll:
        break;
    default:
        break;
    }

    peerNotifyEventsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeerNotifySettings &peerNotifySettingsValue)
{
    TLPeerNotifySettings result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PeerNotifySettingsEmpty:
        break;
    case TLValue::PeerNotifySettings:
        *this >> result.muteUntil;
        *this >> result.sound;
        *this >> result.showPreviews;
        *this >> result.eventsMask;
        break;
    default:
        break;
    }

    peerNotifySettingsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotoSize &photoSizeValue)
{
    TLPhotoSize result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PhotoSizeEmpty:
        *this >> result.type;
        break;
    case TLValue::PhotoSize:
        *this >> result.type;
        *this >> result.location;
        *this >> result.w;
        *this >> result.h;
        *this >> result.size;
        break;
    case TLValue::PhotoCachedSize:
        *this >> result.type;
        *this >> result.location;
        *this >> result.w;
        *this >> result.h;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    photoSizeValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPrivacyKey &privacyKeyValue)
{
    TLPrivacyKey result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }

    privacyKeyValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPrivacyRule &privacyRuleValue)
{
    TLPrivacyRule result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PrivacyValueAllowContacts:
    case TLValue::PrivacyValueAllowAll:
    case TLValue::PrivacyValueDisallowContacts:
    case TLValue::PrivacyValueDisallowAll:
        break;
    case TLValue::PrivacyValueAllowUsers:
    case TLValue::PrivacyValueDisallowUsers:
        *this >> result.users;
        break;
    default:
        break;
    }

    privacyRuleValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLReceivedNotifyMessage &receivedNotifyMessageValue)
{
    TLReceivedNotifyMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ReceivedNotifyMessage:
        *this >> result.id;
        *this >> result.flags;
        break;
    default:
        break;
    }

    receivedNotifyMessageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLReportReason &reportReasonValue)
{
    TLReportReason result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputReportReasonSpam:
    case TLValue::InputReportReasonViolence:
    case TLValue::InputReportReasonPornography:
        break;
    case TLValue::InputReportReasonOther:
        *this >> result.text;
        break;
    default:
        break;
    }

    reportReasonValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLSendMessageAction &sendMessageActionValue)
{
    TLSendMessageAction result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::SendMessageTypingAction:
    case TLValue::SendMessageCancelAction:
    case TLValue::SendMessageRecordVideoAction:
    case TLValue::SendMessageRecordAudioAction:
    case TLValue::SendMessageGeoLocationAction:
    case TLValue::SendMessageChooseContactAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
    case TLValue::SendMessageUploadAudioAction:
    case TLValue::SendMessageUploadPhotoAction:
    case TLValue::SendMessageUploadDocumentAction:
        *this >> result.progress;
        break;
    default:
        break;
    }

    sendMessageActionValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStickerPack &stickerPackValue)
{
    TLStickerPack result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::StickerPack:
        *this >> result.emoticon;
        *this >> result.documents;
        break;
    default:
        break;
    }

    stickerPackValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStorageFileType &storageFileTypeValue)
{
    TLStorageFileType result;

    *this >> result.tlType;

    switch (result.tlType) {
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
        break;
    default:
        break;
    }

    storageFileTypeValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesState &updatesStateValue)
{
    TLUpdatesState result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UpdatesState:
        *this >> result.pts;
        *this >> result.qts;
        *this >> result.date;
        *this >> result.seq;
        *this >> result.unreadCount;
        break;
    default:
        break;
    }

    updatesStateValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUploadFile &uploadFileValue)
{
    TLUploadFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UploadFile:
        *this >> result.type;
        *this >> result.mtime;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    uploadFileValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserProfilePhoto &userProfilePhotoValue)
{
    TLUserProfilePhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UserProfilePhotoEmpty:
        break;
    case TLValue::UserProfilePhoto:
        *this >> result.photoId;
        *this >> result.photoSmall;
        *this >> result.photoBig;
        break;
    default:
        break;
    }

    userProfilePhotoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserStatus &userStatusValue)
{
    TLUserStatus result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UserStatusEmpty:
    case TLValue::UserStatusRecently:
    case TLValue::UserStatusLastWeek:
    case TLValue::UserStatusLastMonth:
        break;
    case TLValue::UserStatusOnline:
        *this >> result.expires;
        break;
    case TLValue::UserStatusOffline:
        *this >> result.wasOnline;
        break;
    default:
        break;
    }

    userStatusValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLVideo &videoValue)
{
    TLVideo result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::VideoEmpty:
        *this >> result.id;
        break;
    case TLValue::Video:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.duration;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.thumb;
        *this >> result.dcId;
        *this >> result.w;
        *this >> result.h;
        break;
    default:
        break;
    }

    videoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLWallPaper &wallPaperValue)
{
    TLWallPaper result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::WallPaper:
        *this >> result.id;
        *this >> result.title;
        *this >> result.sizes;
        *this >> result.color;
        break;
    case TLValue::WallPaperSolid:
        *this >> result.id;
        *this >> result.title;
        *this >> result.bgColor;
        *this >> result.color;
        break;
    default:
        break;
    }

    wallPaperValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountAuthorizations &accountAuthorizationsValue)
{
    TLAccountAuthorizations result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountAuthorizations:
        *this >> result.authorizations;
        break;
    default:
        break;
    }

    accountAuthorizationsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLBotInlineMessage &botInlineMessageValue)
{
    TLBotInlineMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::BotInlineMessageMediaAuto:
        *this >> result.caption;
        break;
    case TLValue::BotInlineMessageText:
        *this >> result.flags;
        *this >> result.message;
        if (result.flags & 1 << 1) {
            *this >> result.entities;
        }
        break;
    default:
        break;
    }

    botInlineMessageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChannelMessagesFilter &channelMessagesFilterValue)
{
    TLChannelMessagesFilter result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChannelMessagesFilterEmpty:
    case TLValue::ChannelMessagesFilterCollapsed:
        break;
    case TLValue::ChannelMessagesFilter:
        *this >> result.flags;
        *this >> result.ranges;
        break;
    default:
        break;
    }

    channelMessagesFilterValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatPhoto &chatPhotoValue)
{
    TLChatPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatPhotoEmpty:
        break;
    case TLValue::ChatPhoto:
        *this >> result.photoSmall;
        *this >> result.photoBig;
        break;
    default:
        break;
    }

    chatPhotoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactStatus &contactStatusValue)
{
    TLContactStatus result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactStatus:
        *this >> result.userId;
        *this >> result.status;
        break;
    default:
        break;
    }

    contactStatusValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDcOption &dcOptionValue)
{
    TLDcOption result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::DcOption:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.ipAddress;
        *this >> result.port;
        break;
    default:
        break;
    }

    dcOptionValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDialog &dialogValue)
{
    TLDialog result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::Dialog:
        *this >> result.peer;
        *this >> result.topMessage;
        *this >> result.readInboxMaxId;
        *this >> result.unreadCount;
        *this >> result.notifySettings;
        break;
    case TLValue::DialogChannel:
        *this >> result.peer;
        *this >> result.topMessage;
        *this >> result.topImportantMessage;
        *this >> result.readInboxMaxId;
        *this >> result.unreadCount;
        *this >> result.unreadImportantCount;
        *this >> result.notifySettings;
        *this >> result.pts;
        break;
    default:
        break;
    }

    dialogValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDocumentAttribute &documentAttributeValue)
{
    TLDocumentAttribute result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::DocumentAttributeImageSize:
        *this >> result.w;
        *this >> result.h;
        break;
    case TLValue::DocumentAttributeAnimated:
        break;
    case TLValue::DocumentAttributeSticker:
        *this >> result.alt;
        *this >> result.stickerset;
        break;
    case TLValue::DocumentAttributeVideo:
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        break;
    case TLValue::DocumentAttributeAudio:
        *this >> result.duration;
        *this >> result.title;
        *this >> result.performer;
        break;
    case TLValue::DocumentAttributeFilename:
        *this >> result.fileName;
        break;
    default:
        break;
    }

    documentAttributeValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputBotInlineMessage &inputBotInlineMessageValue)
{
    TLInputBotInlineMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputBotInlineMessageMediaAuto:
        *this >> result.caption;
        break;
    case TLValue::InputBotInlineMessageText:
        *this >> result.flags;
        *this >> result.message;
        if (result.flags & 1 << 1) {
            *this >> result.entities;
        }
        break;
    default:
        break;
    }

    inputBotInlineMessageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputBotInlineResult &inputBotInlineResultValue)
{
    TLInputBotInlineResult result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputBotInlineResult:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.type;
        if (result.flags & 1 << 1) {
            *this >> result.title;
        }
        if (result.flags & 1 << 2) {
            *this >> result.description;
        }
        if (result.flags & 1 << 3) {
            *this >> result.url;
        }
        if (result.flags & 1 << 4) {
            *this >> result.thumbUrl;
        }
        if (result.flags & 1 << 5) {
            *this >> result.contentUrl;
        }
        if (result.flags & 1 << 5) {
            *this >> result.contentType;
        }
        if (result.flags & 1 << 6) {
            *this >> result.w;
        }
        if (result.flags & 1 << 6) {
            *this >> result.h;
        }
        if (result.flags & 1 << 7) {
            *this >> result.duration;
        }
        *this >> result.sendMessage;
        break;
    default:
        break;
    }

    inputBotInlineResultValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputChatPhoto &inputChatPhotoValue)
{
    TLInputChatPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        *this >> result.file;
        *this >> result.crop;
        break;
    case TLValue::InputChatPhoto:
        *this >> result.id;
        *this >> result.crop;
        break;
    default:
        break;
    }

    inputChatPhotoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputMedia &inputMediaValue)
{
    TLInputMedia result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        *this >> result.file;
        *this >> result.caption;
        break;
    case TLValue::InputMediaPhoto:
        *this >> result.inputPhotoId;
        *this >> result.caption;
        break;
    case TLValue::InputMediaGeoPoint:
        *this >> result.geoPoint;
        break;
    case TLValue::InputMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    case TLValue::InputMediaUploadedVideo:
        *this >> result.file;
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        *this >> result.mimeType;
        *this >> result.caption;
        break;
    case TLValue::InputMediaUploadedThumbVideo:
        *this >> result.file;
        *this >> result.thumb;
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        *this >> result.mimeType;
        *this >> result.caption;
        break;
    case TLValue::InputMediaVideo:
        *this >> result.inputVideoId;
        *this >> result.caption;
        break;
    case TLValue::InputMediaUploadedAudio:
        *this >> result.file;
        *this >> result.duration;
        *this >> result.mimeType;
        break;
    case TLValue::InputMediaAudio:
        *this >> result.inputAudioId;
        break;
    case TLValue::InputMediaUploadedDocument:
        *this >> result.file;
        *this >> result.mimeType;
        *this >> result.attributes;
        *this >> result.caption;
        break;
    case TLValue::InputMediaUploadedThumbDocument:
        *this >> result.file;
        *this >> result.thumb;
        *this >> result.mimeType;
        *this >> result.attributes;
        *this >> result.caption;
        break;
    case TLValue::InputMediaDocument:
        *this >> result.inputDocumentId;
        *this >> result.caption;
        break;
    case TLValue::InputMediaVenue:
        *this >> result.geoPoint;
        *this >> result.title;
        *this >> result.address;
        *this >> result.provider;
        *this >> result.venueId;
        break;
    case TLValue::InputMediaGifExternal:
        *this >> result.url;
        *this >> result.q;
        break;
    default:
        break;
    }

    inputMediaValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputNotifyPeer &inputNotifyPeerValue)
{
    TLInputNotifyPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputNotifyPeer:
        *this >> result.peer;
        break;
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyAll:
        break;
    default:
        break;
    }

    inputNotifyPeerValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPrivacyRule &inputPrivacyRuleValue)
{
    TLInputPrivacyRule result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
    case TLValue::InputPrivacyValueAllowAll:
    case TLValue::InputPrivacyValueDisallowContacts:
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
    case TLValue::InputPrivacyValueDisallowUsers:
        *this >> result.users;
        break;
    default:
        break;
    }

    inputPrivacyRuleValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNotifyPeer &notifyPeerValue)
{
    TLNotifyPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::NotifyPeer:
        *this >> result.peer;
        break;
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyAll:
        break;
    default:
        break;
    }

    notifyPeerValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhoto &photoValue)
{
    TLPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PhotoEmpty:
        *this >> result.id;
        break;
    case TLValue::Photo:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.sizes;
        break;
    default:
        break;
    }

    photoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLReplyMarkup &replyMarkupValue)
{
    TLReplyMarkup result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ReplyKeyboardHide:
    case TLValue::ReplyKeyboardForceReply:
        *this >> result.flags;
        break;
    case TLValue::ReplyKeyboardMarkup:
        *this >> result.flags;
        *this >> result.rows;
        break;
    default:
        break;
    }

    replyMarkupValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStickerSet &stickerSetValue)
{
    TLStickerSet result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::StickerSet:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.title;
        *this >> result.shortName;
        *this >> result.count;
        *this >> result.hash;
        break;
    default:
        break;
    }

    stickerSetValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUser &userValue)
{
    TLUser result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UserEmpty:
        *this >> result.id;
        break;
    case TLValue::User:
        *this >> result.flags;
        *this >> result.id;
        if (result.flags & 1 << 0) {
            *this >> result.accessHash;
        }
        if (result.flags & 1 << 1) {
            *this >> result.firstName;
        }
        if (result.flags & 1 << 2) {
            *this >> result.lastName;
        }
        if (result.flags & 1 << 3) {
            *this >> result.username;
        }
        if (result.flags & 1 << 4) {
            *this >> result.phone;
        }
        if (result.flags & 1 << 5) {
            *this >> result.photo;
        }
        if (result.flags & 1 << 6) {
            *this >> result.status;
        }
        if (result.flags & 1 << 14) {
            *this >> result.botInfoVersion;
        }
        if (result.flags & 1 << 18) {
            *this >> result.restrictionReason;
        }
        if (result.flags & 1 << 19) {
            *this >> result.botInlinePlaceholder;
        }
        break;
    default:
        break;
    }

    userValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountPrivacyRules &accountPrivacyRulesValue)
{
    TLAccountPrivacyRules result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountPrivacyRules:
        *this >> result.rules;
        *this >> result.users;
        break;
    default:
        break;
    }

    accountPrivacyRulesValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthAuthorization &authAuthorizationValue)
{
    TLAuthAuthorization result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AuthAuthorization:
        *this >> result.user;
        break;
    default:
        break;
    }

    authAuthorizationValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChannelsChannelParticipant &channelsChannelParticipantValue)
{
    TLChannelsChannelParticipant result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChannelsChannelParticipant:
        *this >> result.participant;
        *this >> result.users;
        break;
    default:
        break;
    }

    channelsChannelParticipantValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChannelsChannelParticipants &channelsChannelParticipantsValue)
{
    TLChannelsChannelParticipants result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChannelsChannelParticipants:
        *this >> result.count;
        *this >> result.participants;
        *this >> result.users;
        break;
    default:
        break;
    }

    channelsChannelParticipantsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChat &chatValue)
{
    TLChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatEmpty:
        *this >> result.id;
        break;
    case TLValue::Chat:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.title;
        *this >> result.photo;
        *this >> result.participantsCount;
        *this >> result.date;
        *this >> result.version;
        if (result.flags & 1 << 6) {
            *this >> result.migratedTo;
        }
        break;
    case TLValue::ChatForbidden:
        *this >> result.id;
        *this >> result.title;
        break;
    case TLValue::Channel:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.title;
        if (result.flags & 1 << 6) {
            *this >> result.username;
        }
        *this >> result.photo;
        *this >> result.date;
        *this >> result.version;
        if (result.flags & 1 << 9) {
            *this >> result.restrictionReason;
        }
        break;
    case TLValue::ChannelForbidden:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.title;
        break;
    default:
        break;
    }

    chatValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatFull &chatFullValue)
{
    TLChatFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatFull:
        *this >> result.id;
        *this >> result.participants;
        *this >> result.chatPhoto;
        *this >> result.notifySettings;
        *this >> result.exportedInvite;
        *this >> result.botInfo;
        break;
    case TLValue::ChannelFull:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.about;
        if (result.flags & 1 << 0) {
            *this >> result.participantsCount;
        }
        if (result.flags & 1 << 1) {
            *this >> result.adminsCount;
        }
        if (result.flags & 1 << 2) {
            *this >> result.kickedCount;
        }
        *this >> result.readInboxMaxId;
        *this >> result.unreadCount;
        *this >> result.unreadImportantCount;
        *this >> result.chatPhoto;
        *this >> result.notifySettings;
        *this >> result.exportedInvite;
        *this >> result.botInfo;
        if (result.flags & 1 << 4) {
            *this >> result.migratedFromChatId;
        }
        if (result.flags & 1 << 4) {
            *this >> result.migratedFromMaxId;
        }
        break;
    default:
        break;
    }

    chatFullValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatInvite &chatInviteValue)
{
    TLChatInvite result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ChatInviteAlready:
        *this >> result.chat;
        break;
    case TLValue::ChatInvite:
        *this >> result.flags;
        *this >> result.title;
        break;
    default:
        break;
    }

    chatInviteValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLConfig &configValue)
{
    TLConfig result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::Config:
        *this >> result.date;
        *this >> result.expires;
        *this >> result.testMode;
        *this >> result.thisDc;
        *this >> result.dcOptions;
        *this >> result.chatSizeMax;
        *this >> result.megagroupSizeMax;
        *this >> result.forwardedCountMax;
        *this >> result.onlineUpdatePeriodMs;
        *this >> result.offlineBlurTimeoutMs;
        *this >> result.offlineIdleTimeoutMs;
        *this >> result.onlineCloudTimeoutMs;
        *this >> result.notifyCloudDelayMs;
        *this >> result.notifyDefaultDelayMs;
        *this >> result.chatBigSize;
        *this >> result.pushChatPeriodMs;
        *this >> result.pushChatLimit;
        *this >> result.savedGifsLimit;
        *this >> result.disabledFeatures;
        break;
    default:
        break;
    }

    configValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsBlocked &contactsBlockedValue)
{
    TLContactsBlocked result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsBlocked:
        *this >> result.blocked;
        *this >> result.users;
        break;
    case TLValue::ContactsBlockedSlice:
        *this >> result.count;
        *this >> result.blocked;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsBlockedValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsContacts &contactsContactsValue)
{
    TLContactsContacts result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        *this >> result.contacts;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsContactsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsFound &contactsFoundValue)
{
    TLContactsFound result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsFound:
        *this >> result.results;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsFoundValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsImportedContacts &contactsImportedContactsValue)
{
    TLContactsImportedContacts result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsImportedContacts:
        *this >> result.imported;
        *this >> result.retryContacts;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsImportedContactsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsLink &contactsLinkValue)
{
    TLContactsLink result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsLink:
        *this >> result.myLink;
        *this >> result.foreignLink;
        *this >> result.user;
        break;
    default:
        break;
    }

    contactsLinkValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsResolvedPeer &contactsResolvedPeerValue)
{
    TLContactsResolvedPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsResolvedPeer:
        *this >> result.peer;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsResolvedPeerValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsSuggested &contactsSuggestedValue)
{
    TLContactsSuggested result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactsSuggested:
        *this >> result.results;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsSuggestedValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDocument &documentValue)
{
    TLDocument result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::DocumentEmpty:
        *this >> result.id;
        break;
    case TLValue::Document:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.thumb;
        *this >> result.dcId;
        *this >> result.attributes;
        break;
    default:
        break;
    }

    documentValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLFoundGif &foundGifValue)
{
    TLFoundGif result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::FoundGif:
        *this >> result.url;
        *this >> result.thumbUrl;
        *this >> result.contentUrl;
        *this >> result.contentType;
        *this >> result.w;
        *this >> result.h;
        break;
    case TLValue::FoundGifCached:
        *this >> result.url;
        *this >> result.photo;
        *this >> result.document;
        break;
    default:
        break;
    }

    foundGifValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpSupport &helpSupportValue)
{
    TLHelpSupport result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::HelpSupport:
        *this >> result.phoneNumber;
        *this >> result.user;
        break;
    default:
        break;
    }

    helpSupportValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageAction &messageActionValue)
{
    TLMessageAction result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessageActionEmpty:
    case TLValue::MessageActionChatDeletePhoto:
        break;
    case TLValue::MessageActionChatCreate:
        *this >> result.title;
        *this >> result.users;
        break;
    case TLValue::MessageActionChatEditTitle:
    case TLValue::MessageActionChannelCreate:
        *this >> result.title;
        break;
    case TLValue::MessageActionChatEditPhoto:
        *this >> result.photo;
        break;
    case TLValue::MessageActionChatAddUser:
        *this >> result.users;
        break;
    case TLValue::MessageActionChatDeleteUser:
        *this >> result.userId;
        break;
    case TLValue::MessageActionChatJoinedByLink:
        *this >> result.inviterId;
        break;
    case TLValue::MessageActionChatMigrateTo:
        *this >> result.channelId;
        break;
    case TLValue::MessageActionChannelMigrateFrom:
        *this >> result.title;
        *this >> result.chatId;
        break;
    default:
        break;
    }

    messageActionValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesAllStickers &messagesAllStickersValue)
{
    TLMessagesAllStickers result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesAllStickersNotModified:
        break;
    case TLValue::MessagesAllStickers:
        *this >> result.hash;
        *this >> result.sets;
        break;
    default:
        break;
    }

    messagesAllStickersValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChatFull &messagesChatFullValue)
{
    TLMessagesChatFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesChatFull:
        *this >> result.fullChat;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesChatFullValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChats &messagesChatsValue)
{
    TLMessagesChats result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesChats:
        *this >> result.chats;
        break;
    default:
        break;
    }

    messagesChatsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesFoundGifs &messagesFoundGifsValue)
{
    TLMessagesFoundGifs result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesFoundGifs:
        *this >> result.nextOffset;
        *this >> result.results;
        break;
    default:
        break;
    }

    messagesFoundGifsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesSavedGifs &messagesSavedGifsValue)
{
    TLMessagesSavedGifs result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesSavedGifsNotModified:
        break;
    case TLValue::MessagesSavedGifs:
        *this >> result.hash;
        *this >> result.gifs;
        break;
    default:
        break;
    }

    messagesSavedGifsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStickerSet &messagesStickerSetValue)
{
    TLMessagesStickerSet result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesStickerSet:
        *this >> result.set;
        *this >> result.packs;
        *this >> result.documents;
        break;
    default:
        break;
    }

    messagesStickerSetValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStickers &messagesStickersValue)
{
    TLMessagesStickers result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesStickersNotModified:
        break;
    case TLValue::MessagesStickers:
        *this >> result.hash;
        *this >> result.stickers;
        break;
    default:
        break;
    }

    messagesStickersValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotosPhoto &photosPhotoValue)
{
    TLPhotosPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PhotosPhoto:
        *this >> result.photo;
        *this >> result.users;
        break;
    default:
        break;
    }

    photosPhotoValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotosPhotos &photosPhotosValue)
{
    TLPhotosPhotos result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PhotosPhotos:
        *this >> result.photos;
        *this >> result.users;
        break;
    case TLValue::PhotosPhotosSlice:
        *this >> result.count;
        *this >> result.photos;
        *this >> result.users;
        break;
    default:
        break;
    }

    photosPhotosValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserFull &userFullValue)
{
    TLUserFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UserFull:
        *this >> result.user;
        *this >> result.link;
        *this >> result.profilePhoto;
        *this >> result.notifySettings;
        *this >> result.blocked;
        *this >> result.botInfo;
        break;
    default:
        break;
    }

    userFullValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLWebPage &webPageValue)
{
    TLWebPage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::WebPageEmpty:
        *this >> result.id;
        break;
    case TLValue::WebPagePending:
        *this >> result.id;
        *this >> result.date;
        break;
    case TLValue::WebPage:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.url;
        *this >> result.displayUrl;
        if (result.flags & 1 << 0) {
            *this >> result.type;
        }
        if (result.flags & 1 << 1) {
            *this >> result.siteName;
        }
        if (result.flags & 1 << 2) {
            *this >> result.title;
        }
        if (result.flags & 1 << 3) {
            *this >> result.description;
        }
        if (result.flags & 1 << 4) {
            *this >> result.photo;
        }
        if (result.flags & 1 << 5) {
            *this >> result.embedUrl;
        }
        if (result.flags & 1 << 5) {
            *this >> result.embedType;
        }
        if (result.flags & 1 << 6) {
            *this >> result.embedWidth;
        }
        if (result.flags & 1 << 6) {
            *this >> result.embedHeight;
        }
        if (result.flags & 1 << 7) {
            *this >> result.duration;
        }
        if (result.flags & 1 << 8) {
            *this >> result.author;
        }
        if (result.flags & 1 << 9) {
            *this >> result.document;
        }
        break;
    default:
        break;
    }

    webPageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLBotInlineResult &botInlineResultValue)
{
    TLBotInlineResult result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::BotInlineMediaResultDocument:
        *this >> result.id;
        *this >> result.type;
        *this >> result.document;
        *this >> result.sendMessage;
        break;
    case TLValue::BotInlineMediaResultPhoto:
        *this >> result.id;
        *this >> result.type;
        *this >> result.photo;
        *this >> result.sendMessage;
        break;
    case TLValue::BotInlineResult:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.type;
        if (result.flags & 1 << 1) {
            *this >> result.title;
        }
        if (result.flags & 1 << 2) {
            *this >> result.description;
        }
        if (result.flags & 1 << 3) {
            *this >> result.url;
        }
        if (result.flags & 1 << 4) {
            *this >> result.thumbUrl;
        }
        if (result.flags & 1 << 5) {
            *this >> result.contentUrl;
        }
        if (result.flags & 1 << 5) {
            *this >> result.contentType;
        }
        if (result.flags & 1 << 6) {
            *this >> result.w;
        }
        if (result.flags & 1 << 6) {
            *this >> result.h;
        }
        if (result.flags & 1 << 7) {
            *this >> result.duration;
        }
        *this >> result.sendMessage;
        break;
    default:
        break;
    }

    botInlineResultValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageMedia &messageMediaValue)
{
    TLMessageMedia result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaUnsupported:
        break;
    case TLValue::MessageMediaPhoto:
        *this >> result.photo;
        *this >> result.caption;
        break;
    case TLValue::MessageMediaVideo:
        *this >> result.video;
        *this >> result.caption;
        break;
    case TLValue::MessageMediaGeo:
        *this >> result.geo;
        break;
    case TLValue::MessageMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.userId;
        break;
    case TLValue::MessageMediaDocument:
        *this >> result.document;
        *this >> result.caption;
        break;
    case TLValue::MessageMediaAudio:
        *this >> result.audio;
        break;
    case TLValue::MessageMediaWebPage:
        *this >> result.webpage;
        break;
    case TLValue::MessageMediaVenue:
        *this >> result.geo;
        *this >> result.title;
        *this >> result.address;
        *this >> result.provider;
        *this >> result.venueId;
        break;
    default:
        break;
    }

    messageMediaValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesBotResults &messagesBotResultsValue)
{
    TLMessagesBotResults result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesBotResults:
        *this >> result.flags;
        *this >> result.queryId;
        if (result.flags & 1 << 1) {
            *this >> result.nextOffset;
        }
        *this >> result.results;
        break;
    default:
        break;
    }

    messagesBotResultsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessage &messageValue)
{
    TLMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessageEmpty:
        *this >> result.id;
        break;
    case TLValue::Message:
        *this >> result.flags;
        *this >> result.id;
        if (result.flags & 1 << 8) {
            *this >> result.fromId;
        }
        *this >> result.toId;
        if (result.flags & 1 << 2) {
            *this >> result.fwdFromId;
        }
        if (result.flags & 1 << 2) {
            *this >> result.fwdDate;
        }
        if (result.flags & 1 << 11) {
            *this >> result.viaBotId;
        }
        if (result.flags & 1 << 3) {
            *this >> result.replyToMsgId;
        }
        *this >> result.date;
        *this >> result.message;
        if (result.flags & 1 << 9) {
            *this >> result.media;
        }
        if (result.flags & 1 << 6) {
            *this >> result.replyMarkup;
        }
        if (result.flags & 1 << 7) {
            *this >> result.entities;
        }
        if (result.flags & 1 << 10) {
            *this >> result.views;
        }
        break;
    case TLValue::MessageService:
        *this >> result.flags;
        *this >> result.id;
        if (result.flags & 1 << 8) {
            *this >> result.fromId;
        }
        *this >> result.toId;
        *this >> result.date;
        *this >> result.action;
        break;
    default:
        break;
    }

    messageValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesDialogs &messagesDialogsValue)
{
    TLMessagesDialogs result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesDialogs:
        *this >> result.dialogs;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::MessagesDialogsSlice:
        *this >> result.count;
        *this >> result.dialogs;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesDialogsValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesMessages &messagesMessagesValue)
{
    TLMessagesMessages result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::MessagesMessagesSlice:
        *this >> result.count;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::MessagesChannelMessages:
        *this >> result.flags;
        *this >> result.pts;
        *this >> result.count;
        *this >> result.messages;
        if (result.flags & 1 << 0) {
            *this >> result.collapsed;
        }
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesMessagesValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdate &updateValue)
{
    TLUpdate result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
        *this >> result.message;
        *this >> result.pts;
        *this >> result.ptsCount;
        break;
    case TLValue::UpdateMessageID:
        *this >> result.id;
        *this >> result.randomId;
        break;
    case TLValue::UpdateDeleteMessages:
    case TLValue::UpdateReadMessagesContents:
        *this >> result.messages;
        *this >> result.pts;
        *this >> result.ptsCount;
        break;
    case TLValue::UpdateUserTyping:
        *this >> result.userId;
        *this >> result.action;
        break;
    case TLValue::UpdateChatUserTyping:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.action;
        break;
    case TLValue::UpdateChatParticipants:
        *this >> result.participants;
        break;
    case TLValue::UpdateUserStatus:
        *this >> result.userId;
        *this >> result.status;
        break;
    case TLValue::UpdateUserName:
        *this >> result.userId;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        break;
    case TLValue::UpdateUserPhoto:
        *this >> result.userId;
        *this >> result.date;
        *this >> result.photo;
        *this >> result.previous;
        break;
    case TLValue::UpdateContactRegistered:
        *this >> result.userId;
        *this >> result.date;
        break;
    case TLValue::UpdateContactLink:
        *this >> result.userId;
        *this >> result.myLink;
        *this >> result.foreignLink;
        break;
    case TLValue::UpdateNewAuthorization:
        *this >> result.authKeyId;
        *this >> result.date;
        *this >> result.device;
        *this >> result.location;
        break;
    case TLValue::UpdateNewEncryptedMessage:
        *this >> result.encryptedMessage;
        *this >> result.qts;
        break;
    case TLValue::UpdateEncryptedChatTyping:
        *this >> result.chatId;
        break;
    case TLValue::UpdateEncryption:
        *this >> result.chat;
        *this >> result.date;
        break;
    case TLValue::UpdateEncryptedMessagesRead:
        *this >> result.chatId;
        *this >> result.maxDate;
        *this >> result.date;
        break;
    case TLValue::UpdateChatParticipantAdd:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.date;
        *this >> result.version;
        break;
    case TLValue::UpdateChatParticipantDelete:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.version;
        break;
    case TLValue::UpdateDcOptions:
        *this >> result.dcOptions;
        break;
    case TLValue::UpdateUserBlocked:
        *this >> result.userId;
        *this >> result.blocked;
        break;
    case TLValue::UpdateNotifySettings:
        *this >> result.notifyPeer;
        *this >> result.notifySettings;
        break;
    case TLValue::UpdateServiceNotification:
        *this >> result.type;
        *this >> result.stringMessage;
        *this >> result.media;
        *this >> result.popup;
        break;
    case TLValue::UpdatePrivacy:
        *this >> result.key;
        *this >> result.rules;
        break;
    case TLValue::UpdateUserPhone:
        *this >> result.userId;
        *this >> result.phone;
        break;
    case TLValue::UpdateReadHistoryInbox:
    case TLValue::UpdateReadHistoryOutbox:
        *this >> result.peer;
        *this >> result.maxId;
        *this >> result.pts;
        *this >> result.ptsCount;
        break;
    case TLValue::UpdateWebPage:
        *this >> result.webpage;
        *this >> result.pts;
        *this >> result.ptsCount;
        break;
    case TLValue::UpdateChannelTooLong:
    case TLValue::UpdateChannel:
        *this >> result.channelId;
        break;
    case TLValue::UpdateChannelGroup:
        *this >> result.channelId;
        *this >> result.group;
        break;
    case TLValue::UpdateReadChannelInbox:
        *this >> result.channelId;
        *this >> result.maxId;
        break;
    case TLValue::UpdateDeleteChannelMessages:
        *this >> result.channelId;
        *this >> result.messages;
        *this >> result.pts;
        *this >> result.ptsCount;
        break;
    case TLValue::UpdateChannelMessageViews:
        *this >> result.channelId;
        *this >> result.id;
        *this >> result.views;
        break;
    case TLValue::UpdateChatAdmins:
        *this >> result.chatId;
        *this >> result.enabled;
        *this >> result.version;
        break;
    case TLValue::UpdateChatParticipantAdmin:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.isAdmin;
        *this >> result.version;
        break;
    case TLValue::UpdateNewStickerSet:
        *this >> result.stickerset;
        break;
    case TLValue::UpdateStickerSetsOrder:
        *this >> result.order;
        break;
    case TLValue::UpdateStickerSets:
    case TLValue::UpdateSavedGifs:
        break;
    case TLValue::UpdateBotInlineQuery:
        *this >> result.queryId;
        *this >> result.userId;
        *this >> result.query;
        *this >> result.offset;
        break;
    default:
        break;
    }

    updateValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdates &updatesValue)
{
    TLUpdates result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UpdatesTooLong:
        break;
    case TLValue::UpdateShortMessage:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.userId;
        *this >> result.message;
        *this >> result.pts;
        *this >> result.ptsCount;
        *this >> result.date;
        if (result.flags & 1 << 2) {
            *this >> result.fwdFromId;
        }
        if (result.flags & 1 << 2) {
            *this >> result.fwdDate;
        }
        if (result.flags & 1 << 11) {
            *this >> result.viaBotId;
        }
        if (result.flags & 1 << 3) {
            *this >> result.replyToMsgId;
        }
        if (result.flags & 1 << 7) {
            *this >> result.entities;
        }
        break;
    case TLValue::UpdateShortChatMessage:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.chatId;
        *this >> result.message;
        *this >> result.pts;
        *this >> result.ptsCount;
        *this >> result.date;
        if (result.flags & 1 << 2) {
            *this >> result.fwdFromId;
        }
        if (result.flags & 1 << 2) {
            *this >> result.fwdDate;
        }
        if (result.flags & 1 << 11) {
            *this >> result.viaBotId;
        }
        if (result.flags & 1 << 3) {
            *this >> result.replyToMsgId;
        }
        if (result.flags & 1 << 7) {
            *this >> result.entities;
        }
        break;
    case TLValue::UpdateShort:
        *this >> result.update;
        *this >> result.date;
        break;
    case TLValue::UpdatesCombined:
        *this >> result.updates;
        *this >> result.users;
        *this >> result.chats;
        *this >> result.date;
        *this >> result.seqStart;
        *this >> result.seq;
        break;
    case TLValue::Updates:
        *this >> result.updates;
        *this >> result.users;
        *this >> result.chats;
        *this >> result.date;
        *this >> result.seq;
        break;
    case TLValue::UpdateShortSentMessage:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.pts;
        *this >> result.ptsCount;
        *this >> result.date;
        if (result.flags & 1 << 9) {
            *this >> result.media;
        }
        if (result.flags & 1 << 7) {
            *this >> result.entities;
        }
        break;
    default:
        break;
    }

    updatesValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesChannelDifference &updatesChannelDifferenceValue)
{
    TLUpdatesChannelDifference result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UpdatesChannelDifferenceEmpty:
        *this >> result.flags;
        *this >> result.pts;
        if (result.flags & 1 << 1) {
            *this >> result.timeout;
        }
        break;
    case TLValue::UpdatesChannelDifferenceTooLong:
        *this >> result.flags;
        *this >> result.pts;
        if (result.flags & 1 << 1) {
            *this >> result.timeout;
        }
        *this >> result.topMessage;
        *this >> result.topImportantMessage;
        *this >> result.readInboxMaxId;
        *this >> result.unreadCount;
        *this >> result.unreadImportantCount;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::UpdatesChannelDifference:
        *this >> result.flags;
        *this >> result.pts;
        if (result.flags & 1 << 1) {
            *this >> result.timeout;
        }
        *this >> result.newMessages;
        *this >> result.otherUpdates;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    updatesChannelDifferenceValue = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesDifference &updatesDifferenceValue)
{
    TLUpdatesDifference result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::UpdatesDifferenceEmpty:
        *this >> result.date;
        *this >> result.seq;
        break;
    case TLValue::UpdatesDifference:
        *this >> result.newMessages;
        *this >> result.newEncryptedMessages;
        *this >> result.otherUpdates;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.state;
        break;
    case TLValue::UpdatesDifferenceSlice:
        *this >> result.newMessages;
        *this >> result.newEncryptedMessages;
        *this >> result.otherUpdates;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.intermediateState;
        break;
    default:
        break;
    }

    updatesDifferenceValue = result;

    return *this;
}

// End of generated read operators implementation

// Generated write operators implementation
CTelegramStream &CTelegramStream::operator<<(const TLAccountDaysTTL &accountDaysTTLValue)
{
    *this << accountDaysTTLValue.tlType;

    switch (accountDaysTTLValue.tlType) {
    case TLValue::AccountDaysTTL:
        *this << accountDaysTTLValue.days;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLAccountPasswordInputSettings &accountPasswordInputSettingsValue)
{
    *this << accountPasswordInputSettingsValue.tlType;

    switch (accountPasswordInputSettingsValue.tlType) {
    case TLValue::AccountPasswordInputSettings:
        *this << accountPasswordInputSettingsValue.flags;
        if (accountPasswordInputSettingsValue.flags & 1 << 0) {
            *this << accountPasswordInputSettingsValue.newSalt;
        }
        if (accountPasswordInputSettingsValue.flags & 1 << 0) {
            *this << accountPasswordInputSettingsValue.newPasswordHash;
        }
        if (accountPasswordInputSettingsValue.flags & 1 << 0) {
            *this << accountPasswordInputSettingsValue.hint;
        }
        if (accountPasswordInputSettingsValue.flags & 1 << 1) {
            *this << accountPasswordInputSettingsValue.email;
        }
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLChannelParticipantRole &channelParticipantRoleValue)
{
    *this << channelParticipantRoleValue.tlType;

    switch (channelParticipantRoleValue.tlType) {
    case TLValue::ChannelRoleEmpty:
    case TLValue::ChannelRoleModerator:
    case TLValue::ChannelRoleEditor:
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLChannelParticipantsFilter &channelParticipantsFilterValue)
{
    *this << channelParticipantsFilterValue.tlType;

    switch (channelParticipantsFilterValue.tlType) {
    case TLValue::ChannelParticipantsRecent:
    case TLValue::ChannelParticipantsAdmins:
    case TLValue::ChannelParticipantsKicked:
    case TLValue::ChannelParticipantsBots:
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputAppEvent &inputAppEventValue)
{
    *this << inputAppEventValue.tlType;

    switch (inputAppEventValue.tlType) {
    case TLValue::InputAppEvent:
        *this << inputAppEventValue.time;
        *this << inputAppEventValue.type;
        *this << inputAppEventValue.peer;
        *this << inputAppEventValue.data;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputAudio &inputAudioValue)
{
    *this << inputAudioValue.tlType;

    switch (inputAudioValue.tlType) {
    case TLValue::InputAudioEmpty:
        break;
    case TLValue::InputAudio:
        *this << inputAudioValue.id;
        *this << inputAudioValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputChannel &inputChannelValue)
{
    *this << inputChannelValue.tlType;

    switch (inputChannelValue.tlType) {
    case TLValue::InputChannelEmpty:
        break;
    case TLValue::InputChannel:
        *this << inputChannelValue.channelId;
        *this << inputChannelValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputContact &inputContactValue)
{
    *this << inputContactValue.tlType;

    switch (inputContactValue.tlType) {
    case TLValue::InputPhoneContact:
        *this << inputContactValue.clientId;
        *this << inputContactValue.phone;
        *this << inputContactValue.firstName;
        *this << inputContactValue.lastName;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputDocument &inputDocumentValue)
{
    *this << inputDocumentValue.tlType;

    switch (inputDocumentValue.tlType) {
    case TLValue::InputDocumentEmpty:
        break;
    case TLValue::InputDocument:
        *this << inputDocumentValue.id;
        *this << inputDocumentValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputEncryptedChat &inputEncryptedChatValue)
{
    *this << inputEncryptedChatValue.tlType;

    switch (inputEncryptedChatValue.tlType) {
    case TLValue::InputEncryptedChat:
        *this << inputEncryptedChatValue.chatId;
        *this << inputEncryptedChatValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputEncryptedFile &inputEncryptedFileValue)
{
    *this << inputEncryptedFileValue.tlType;

    switch (inputEncryptedFileValue.tlType) {
    case TLValue::InputEncryptedFileEmpty:
        break;
    case TLValue::InputEncryptedFileUploaded:
        *this << inputEncryptedFileValue.id;
        *this << inputEncryptedFileValue.parts;
        *this << inputEncryptedFileValue.md5Checksum;
        *this << inputEncryptedFileValue.keyFingerprint;
        break;
    case TLValue::InputEncryptedFile:
        *this << inputEncryptedFileValue.id;
        *this << inputEncryptedFileValue.accessHash;
        break;
    case TLValue::InputEncryptedFileBigUploaded:
        *this << inputEncryptedFileValue.id;
        *this << inputEncryptedFileValue.parts;
        *this << inputEncryptedFileValue.keyFingerprint;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputFile &inputFileValue)
{
    *this << inputFileValue.tlType;

    switch (inputFileValue.tlType) {
    case TLValue::InputFile:
        *this << inputFileValue.id;
        *this << inputFileValue.parts;
        *this << inputFileValue.name;
        *this << inputFileValue.md5Checksum;
        break;
    case TLValue::InputFileBig:
        *this << inputFileValue.id;
        *this << inputFileValue.parts;
        *this << inputFileValue.name;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputFileLocation &inputFileLocationValue)
{
    *this << inputFileLocationValue.tlType;

    switch (inputFileLocationValue.tlType) {
    case TLValue::InputFileLocation:
        *this << inputFileLocationValue.volumeId;
        *this << inputFileLocationValue.localId;
        *this << inputFileLocationValue.secret;
        break;
    case TLValue::InputVideoFileLocation:
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputAudioFileLocation:
    case TLValue::InputDocumentFileLocation:
        *this << inputFileLocationValue.id;
        *this << inputFileLocationValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputGeoPoint &inputGeoPointValue)
{
    *this << inputGeoPointValue.tlType;

    switch (inputGeoPointValue.tlType) {
    case TLValue::InputGeoPointEmpty:
        break;
    case TLValue::InputGeoPoint:
        *this << inputGeoPointValue.latitude;
        *this << inputGeoPointValue.longitude;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPeer &inputPeerValue)
{
    *this << inputPeerValue.tlType;

    switch (inputPeerValue.tlType) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
        break;
    case TLValue::InputPeerChat:
        *this << inputPeerValue.chatId;
        break;
    case TLValue::InputPeerUser:
        *this << inputPeerValue.userId;
        *this << inputPeerValue.accessHash;
        break;
    case TLValue::InputPeerChannel:
        *this << inputPeerValue.channelId;
        *this << inputPeerValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettingsValue)
{
    *this << inputPeerNotifySettingsValue.tlType;

    switch (inputPeerNotifySettingsValue.tlType) {
    case TLValue::InputPeerNotifySettings:
        *this << inputPeerNotifySettingsValue.muteUntil;
        *this << inputPeerNotifySettingsValue.sound;
        *this << inputPeerNotifySettingsValue.showPreviews;
        *this << inputPeerNotifySettingsValue.eventsMask;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPhoto &inputPhotoValue)
{
    *this << inputPhotoValue.tlType;

    switch (inputPhotoValue.tlType) {
    case TLValue::InputPhotoEmpty:
        break;
    case TLValue::InputPhoto:
        *this << inputPhotoValue.id;
        *this << inputPhotoValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPhotoCrop &inputPhotoCropValue)
{
    *this << inputPhotoCropValue.tlType;

    switch (inputPhotoCropValue.tlType) {
    case TLValue::InputPhotoCropAuto:
        break;
    case TLValue::InputPhotoCrop:
        *this << inputPhotoCropValue.cropLeft;
        *this << inputPhotoCropValue.cropTop;
        *this << inputPhotoCropValue.cropWidth;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPrivacyKey &inputPrivacyKeyValue)
{
    *this << inputPrivacyKeyValue.tlType;

    switch (inputPrivacyKeyValue.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputStickerSet &inputStickerSetValue)
{
    *this << inputStickerSetValue.tlType;

    switch (inputStickerSetValue.tlType) {
    case TLValue::InputStickerSetEmpty:
        break;
    case TLValue::InputStickerSetID:
        *this << inputStickerSetValue.id;
        *this << inputStickerSetValue.accessHash;
        break;
    case TLValue::InputStickerSetShortName:
        *this << inputStickerSetValue.shortName;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputUser &inputUserValue)
{
    *this << inputUserValue.tlType;

    switch (inputUserValue.tlType) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
        break;
    case TLValue::InputUser:
        *this << inputUserValue.userId;
        *this << inputUserValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputVideo &inputVideoValue)
{
    *this << inputVideoValue.tlType;

    switch (inputVideoValue.tlType) {
    case TLValue::InputVideoEmpty:
        break;
    case TLValue::InputVideo:
        *this << inputVideoValue.id;
        *this << inputVideoValue.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLKeyboardButton &keyboardButtonValue)
{
    *this << keyboardButtonValue.tlType;

    switch (keyboardButtonValue.tlType) {
    case TLValue::KeyboardButton:
        *this << keyboardButtonValue.text;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLKeyboardButtonRow &keyboardButtonRowValue)
{
    *this << keyboardButtonRowValue.tlType;

    switch (keyboardButtonRowValue.tlType) {
    case TLValue::KeyboardButtonRow:
        *this << keyboardButtonRowValue.buttons;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLMessageEntity &messageEntityValue)
{
    *this << messageEntityValue.tlType;

    switch (messageEntityValue.tlType) {
    case TLValue::MessageEntityUnknown:
    case TLValue::MessageEntityMention:
    case TLValue::MessageEntityHashtag:
    case TLValue::MessageEntityBotCommand:
    case TLValue::MessageEntityUrl:
    case TLValue::MessageEntityEmail:
    case TLValue::MessageEntityBold:
    case TLValue::MessageEntityItalic:
    case TLValue::MessageEntityCode:
        *this << messageEntityValue.offset;
        *this << messageEntityValue.length;
        break;
    case TLValue::MessageEntityPre:
        *this << messageEntityValue.offset;
        *this << messageEntityValue.length;
        *this << messageEntityValue.language;
        break;
    case TLValue::MessageEntityTextUrl:
        *this << messageEntityValue.offset;
        *this << messageEntityValue.length;
        *this << messageEntityValue.url;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLMessageRange &messageRangeValue)
{
    *this << messageRangeValue.tlType;

    switch (messageRangeValue.tlType) {
    case TLValue::MessageRange:
        *this << messageRangeValue.minId;
        *this << messageRangeValue.maxId;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLMessagesFilter &messagesFilterValue)
{
    *this << messagesFilterValue.tlType;

    switch (messagesFilterValue.tlType) {
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
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLReportReason &reportReasonValue)
{
    *this << reportReasonValue.tlType;

    switch (reportReasonValue.tlType) {
    case TLValue::InputReportReasonSpam:
    case TLValue::InputReportReasonViolence:
    case TLValue::InputReportReasonPornography:
        break;
    case TLValue::InputReportReasonOther:
        *this << reportReasonValue.text;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLSendMessageAction &sendMessageActionValue)
{
    *this << sendMessageActionValue.tlType;

    switch (sendMessageActionValue.tlType) {
    case TLValue::SendMessageTypingAction:
    case TLValue::SendMessageCancelAction:
    case TLValue::SendMessageRecordVideoAction:
    case TLValue::SendMessageRecordAudioAction:
    case TLValue::SendMessageGeoLocationAction:
    case TLValue::SendMessageChooseContactAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
    case TLValue::SendMessageUploadAudioAction:
    case TLValue::SendMessageUploadPhotoAction:
    case TLValue::SendMessageUploadDocumentAction:
        *this << sendMessageActionValue.progress;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLChannelMessagesFilter &channelMessagesFilterValue)
{
    *this << channelMessagesFilterValue.tlType;

    switch (channelMessagesFilterValue.tlType) {
    case TLValue::ChannelMessagesFilterEmpty:
    case TLValue::ChannelMessagesFilterCollapsed:
        break;
    case TLValue::ChannelMessagesFilter:
        *this << channelMessagesFilterValue.flags;
        *this << channelMessagesFilterValue.ranges;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLDocumentAttribute &documentAttributeValue)
{
    *this << documentAttributeValue.tlType;

    switch (documentAttributeValue.tlType) {
    case TLValue::DocumentAttributeImageSize:
        *this << documentAttributeValue.w;
        *this << documentAttributeValue.h;
        break;
    case TLValue::DocumentAttributeAnimated:
        break;
    case TLValue::DocumentAttributeSticker:
        *this << documentAttributeValue.alt;
        *this << documentAttributeValue.stickerset;
        break;
    case TLValue::DocumentAttributeVideo:
        *this << documentAttributeValue.duration;
        *this << documentAttributeValue.w;
        *this << documentAttributeValue.h;
        break;
    case TLValue::DocumentAttributeAudio:
        *this << documentAttributeValue.duration;
        *this << documentAttributeValue.title;
        *this << documentAttributeValue.performer;
        break;
    case TLValue::DocumentAttributeFilename:
        *this << documentAttributeValue.fileName;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputBotInlineMessage &inputBotInlineMessageValue)
{
    *this << inputBotInlineMessageValue.tlType;

    switch (inputBotInlineMessageValue.tlType) {
    case TLValue::InputBotInlineMessageMediaAuto:
        *this << inputBotInlineMessageValue.caption;
        break;
    case TLValue::InputBotInlineMessageText:
        *this << inputBotInlineMessageValue.flags;
        *this << inputBotInlineMessageValue.message;
        if (inputBotInlineMessageValue.flags & 1 << 1) {
            *this << inputBotInlineMessageValue.entities;
        }
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputBotInlineResult &inputBotInlineResultValue)
{
    *this << inputBotInlineResultValue.tlType;

    switch (inputBotInlineResultValue.tlType) {
    case TLValue::InputBotInlineResult:
        *this << inputBotInlineResultValue.flags;
        *this << inputBotInlineResultValue.id;
        *this << inputBotInlineResultValue.type;
        if (inputBotInlineResultValue.flags & 1 << 1) {
            *this << inputBotInlineResultValue.title;
        }
        if (inputBotInlineResultValue.flags & 1 << 2) {
            *this << inputBotInlineResultValue.description;
        }
        if (inputBotInlineResultValue.flags & 1 << 3) {
            *this << inputBotInlineResultValue.url;
        }
        if (inputBotInlineResultValue.flags & 1 << 4) {
            *this << inputBotInlineResultValue.thumbUrl;
        }
        if (inputBotInlineResultValue.flags & 1 << 5) {
            *this << inputBotInlineResultValue.contentUrl;
        }
        if (inputBotInlineResultValue.flags & 1 << 5) {
            *this << inputBotInlineResultValue.contentType;
        }
        if (inputBotInlineResultValue.flags & 1 << 6) {
            *this << inputBotInlineResultValue.w;
        }
        if (inputBotInlineResultValue.flags & 1 << 6) {
            *this << inputBotInlineResultValue.h;
        }
        if (inputBotInlineResultValue.flags & 1 << 7) {
            *this << inputBotInlineResultValue.duration;
        }
        *this << inputBotInlineResultValue.sendMessage;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputChatPhoto &inputChatPhotoValue)
{
    *this << inputChatPhotoValue.tlType;

    switch (inputChatPhotoValue.tlType) {
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        *this << inputChatPhotoValue.file;
        *this << inputChatPhotoValue.crop;
        break;
    case TLValue::InputChatPhoto:
        *this << inputChatPhotoValue.id;
        *this << inputChatPhotoValue.crop;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputMedia &inputMediaValue)
{
    *this << inputMediaValue.tlType;

    switch (inputMediaValue.tlType) {
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        *this << inputMediaValue.file;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaPhoto:
        *this << inputMediaValue.inputPhotoId;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaGeoPoint:
        *this << inputMediaValue.geoPoint;
        break;
    case TLValue::InputMediaContact:
        *this << inputMediaValue.phoneNumber;
        *this << inputMediaValue.firstName;
        *this << inputMediaValue.lastName;
        break;
    case TLValue::InputMediaUploadedVideo:
        *this << inputMediaValue.file;
        *this << inputMediaValue.duration;
        *this << inputMediaValue.w;
        *this << inputMediaValue.h;
        *this << inputMediaValue.mimeType;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaUploadedThumbVideo:
        *this << inputMediaValue.file;
        *this << inputMediaValue.thumb;
        *this << inputMediaValue.duration;
        *this << inputMediaValue.w;
        *this << inputMediaValue.h;
        *this << inputMediaValue.mimeType;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaVideo:
        *this << inputMediaValue.inputVideoId;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaUploadedAudio:
        *this << inputMediaValue.file;
        *this << inputMediaValue.duration;
        *this << inputMediaValue.mimeType;
        break;
    case TLValue::InputMediaAudio:
        *this << inputMediaValue.inputAudioId;
        break;
    case TLValue::InputMediaUploadedDocument:
        *this << inputMediaValue.file;
        *this << inputMediaValue.mimeType;
        *this << inputMediaValue.attributes;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaUploadedThumbDocument:
        *this << inputMediaValue.file;
        *this << inputMediaValue.thumb;
        *this << inputMediaValue.mimeType;
        *this << inputMediaValue.attributes;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaDocument:
        *this << inputMediaValue.inputDocumentId;
        *this << inputMediaValue.caption;
        break;
    case TLValue::InputMediaVenue:
        *this << inputMediaValue.geoPoint;
        *this << inputMediaValue.title;
        *this << inputMediaValue.address;
        *this << inputMediaValue.provider;
        *this << inputMediaValue.venueId;
        break;
    case TLValue::InputMediaGifExternal:
        *this << inputMediaValue.url;
        *this << inputMediaValue.q;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputNotifyPeer &inputNotifyPeerValue)
{
    *this << inputNotifyPeerValue.tlType;

    switch (inputNotifyPeerValue.tlType) {
    case TLValue::InputNotifyPeer:
        *this << inputNotifyPeerValue.peer;
        break;
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyAll:
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPrivacyRule &inputPrivacyRuleValue)
{
    *this << inputPrivacyRuleValue.tlType;

    switch (inputPrivacyRuleValue.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
    case TLValue::InputPrivacyValueAllowAll:
    case TLValue::InputPrivacyValueDisallowContacts:
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
    case TLValue::InputPrivacyValueDisallowUsers:
        *this << inputPrivacyRuleValue.users;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLReplyMarkup &replyMarkupValue)
{
    *this << replyMarkupValue.tlType;

    switch (replyMarkupValue.tlType) {
    case TLValue::ReplyKeyboardHide:
    case TLValue::ReplyKeyboardForceReply:
        *this << replyMarkupValue.flags;
        break;
    case TLValue::ReplyKeyboardMarkup:
        *this << replyMarkupValue.flags;
        *this << replyMarkupValue.rows;
        break;
    default:
        break;
    }

    return *this;
}

// End of generated write operators implementation
