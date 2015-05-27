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

#include "TLTypesDebug.hpp"

// Generated TLTypes debug operators
QDebug operator<<(QDebug d, const TLAccountDaysTTL &type)
{
    d << "TLAccountDaysTTL(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AccountDaysTTL:
        d << "days:" << type.days;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountSentChangePhoneCode &type)
{
    d << "TLAccountSentChangePhoneCode(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AccountSentChangePhoneCode:
        d << "phoneCodeHash:" << type.phoneCodeHash;
        d << "sendCallTimeout:" << type.sendCallTimeout;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAudio &type)
{
    d << "TLAudio(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AudioEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::Audio:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "userId:" << type.userId;
        d << "date:" << type.date;
        d << "duration:" << type.duration;
        d << "mimeType:" << type.mimeType;
        d << "size:" << type.size;
        d << "dcId:" << type.dcId;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthCheckedPhone &type)
{
    d << "TLAuthCheckedPhone(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AuthCheckedPhone:
        d << "phoneRegistered:" << type.phoneRegistered;
        d << "phoneInvited:" << type.phoneInvited;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &type)
{
    d << "TLAuthExportedAuthorization(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AuthExportedAuthorization:
        d << "id:" << type.id;
        d << "bytes:" << type.bytes;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthSentCode &type)
{
    d << "TLAuthSentCode(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AuthSentCode:
        d << "phoneRegistered:" << type.phoneRegistered;
        d << "phoneCodeHash:" << type.phoneCodeHash;
        d << "sendCallTimeout:" << type.sendCallTimeout;
        d << "isPassword:" << type.isPassword;
        break;
    case TLValue::AuthSentAppCode:
        d << "phoneRegistered:" << type.phoneRegistered;
        d << "phoneCodeHash:" << type.phoneCodeHash;
        d << "sendCallTimeout:" << type.sendCallTimeout;
        d << "isPassword:" << type.isPassword;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatLocated &type)
{
    d << "TLChatLocated(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ChatLocated:
        d << "chatId:" << type.chatId;
        d << "distance:" << type.distance;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatParticipant &type)
{
    d << "TLChatParticipant(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ChatParticipant:
        d << "userId:" << type.userId;
        d << "inviterId:" << type.inviterId;
        d << "date:" << type.date;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatParticipants &type)
{
    d << "TLChatParticipants(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ChatParticipantsForbidden:
        d << "chatId:" << type.chatId;
        break;
    case TLValue::ChatParticipants:
        d << "chatId:" << type.chatId;
        d << "adminId:" << type.adminId;
        d << "participants:" << type.participants;
        d << "version:" << type.version;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContact &type)
{
    d << "TLContact(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::Contact:
        d << "userId:" << type.userId;
        d << "mutual:" << type.mutual;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactBlocked &type)
{
    d << "TLContactBlocked(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactBlocked:
        d << "userId:" << type.userId;
        d << "date:" << type.date;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactFound &type)
{
    d << "TLContactFound(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactFound:
        d << "userId:" << type.userId;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactSuggested &type)
{
    d << "TLContactSuggested(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactSuggested:
        d << "userId:" << type.userId;
        d << "mutualContacts:" << type.mutualContacts;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsForeignLink &type)
{
    d << "TLContactsForeignLink(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsForeignLinkUnknown:
        break;
    case TLValue::ContactsForeignLinkRequested:
        d << "hasPhone:" << type.hasPhone;
        break;
    case TLValue::ContactsForeignLinkMutual:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsMyLink &type)
{
    d << "TLContactsMyLink(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsMyLinkEmpty:
        break;
    case TLValue::ContactsMyLinkRequested:
        d << "contact:" << type.contact;
        break;
    case TLValue::ContactsMyLinkContact:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDcOption &type)
{
    d << "TLDcOption(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::DcOption:
        d << "id:" << type.id;
        d << "hostname:" << type.hostname;
        d << "ipAddress:" << type.ipAddress;
        d << "port:" << type.port;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDisabledFeature &type)
{
    d << "TLDisabledFeature(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::DisabledFeature:
        d << "feature:" << type.feature;
        d << "description:" << type.description;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDocumentAttribute &type)
{
    d << "TLDocumentAttribute(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::DocumentAttributeImageSize:
        d << "w:" << type.w;
        d << "h:" << type.h;
        break;
    case TLValue::DocumentAttributeAnimated:
        break;
    case TLValue::DocumentAttributeSticker:
        break;
    case TLValue::DocumentAttributeVideo:
        d << "duration:" << type.duration;
        d << "w:" << type.w;
        d << "h:" << type.h;
        break;
    case TLValue::DocumentAttributeAudio:
        d << "duration:" << type.duration;
        break;
    case TLValue::DocumentAttributeFilename:
        d << "fileName:" << type.fileName;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedChat &type)
{
    d << "TLEncryptedChat(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::EncryptedChatEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::EncryptedChatWaiting:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "date:" << type.date;
        d << "adminId:" << type.adminId;
        d << "participantId:" << type.participantId;
        break;
    case TLValue::EncryptedChatRequested:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "date:" << type.date;
        d << "adminId:" << type.adminId;
        d << "participantId:" << type.participantId;
        d << "gA:" << type.gA;
        break;
    case TLValue::EncryptedChat:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "date:" << type.date;
        d << "adminId:" << type.adminId;
        d << "participantId:" << type.participantId;
        d << "gAOrB:" << type.gAOrB;
        d << "keyFingerprint:" << type.keyFingerprint;
        break;
    case TLValue::EncryptedChatDiscarded:
        d << "id:" << type.id;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedFile &type)
{
    d << "TLEncryptedFile(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::EncryptedFileEmpty:
        break;
    case TLValue::EncryptedFile:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "size:" << type.size;
        d << "dcId:" << type.dcId;
        d << "keyFingerprint:" << type.keyFingerprint;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedMessage &type)
{
    d << "TLEncryptedMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::EncryptedMessage:
        d << "randomId:" << type.randomId;
        d << "chatId:" << type.chatId;
        d << "date:" << type.date;
        d << "bytes:" << type.bytes;
        d << "file:" << type.file;
        break;
    case TLValue::EncryptedMessageService:
        d << "randomId:" << type.randomId;
        d << "chatId:" << type.chatId;
        d << "date:" << type.date;
        d << "bytes:" << type.bytes;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLError &type)
{
    d << "TLError(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::Error:
        d << "code:" << type.code;
        d << "text:" << type.text;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFileLocation &type)
{
    d << "TLFileLocation(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::FileLocationUnavailable:
        d << "volumeId:" << type.volumeId;
        d << "localId:" << type.localId;
        d << "secret:" << type.secret;
        break;
    case TLValue::FileLocation:
        d << "dcId:" << type.dcId;
        d << "volumeId:" << type.volumeId;
        d << "localId:" << type.localId;
        d << "secret:" << type.secret;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGeoPoint &type)
{
    d << "TLGeoPoint(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::GeoPointEmpty:
        break;
    case TLValue::GeoPoint:
        d << "longitude:" << type.longitude;
        d << "latitude:" << type.latitude;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpAppUpdate &type)
{
    d << "TLHelpAppUpdate(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::HelpAppUpdate:
        d << "id:" << type.id;
        d << "critical:" << type.critical;
        d << "url:" << type.url;
        d << "text:" << type.text;
        break;
    case TLValue::HelpNoAppUpdate:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpInviteText &type)
{
    d << "TLHelpInviteText(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::HelpInviteText:
        d << "message:" << type.message;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLImportedContact &type)
{
    d << "TLImportedContact(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ImportedContact:
        d << "userId:" << type.userId;
        d << "clientId:" << type.clientId;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputAppEvent &type)
{
    d << "TLInputAppEvent(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputAppEvent:
        d << "time:" << type.time;
        d << "type:" << type.type;
        d << "peer:" << type.peer;
        d << "data:" << type.data;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputAudio &type)
{
    d << "TLInputAudio(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputAudioEmpty:
        break;
    case TLValue::InputAudio:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputContact &type)
{
    d << "TLInputContact(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPhoneContact:
        d << "clientId:" << type.clientId;
        d << "phone:" << type.phone;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputDocument &type)
{
    d << "TLInputDocument(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputDocumentEmpty:
        break;
    case TLValue::InputDocument:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputEncryptedChat &type)
{
    d << "TLInputEncryptedChat(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputEncryptedChat:
        d << "chatId:" << type.chatId;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputEncryptedFile &type)
{
    d << "TLInputEncryptedFile(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputEncryptedFileEmpty:
        break;
    case TLValue::InputEncryptedFileUploaded:
        d << "id:" << type.id;
        d << "parts:" << type.parts;
        d << "md5Checksum:" << type.md5Checksum;
        d << "keyFingerprint:" << type.keyFingerprint;
        break;
    case TLValue::InputEncryptedFile:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    case TLValue::InputEncryptedFileBigUploaded:
        d << "id:" << type.id;
        d << "parts:" << type.parts;
        d << "keyFingerprint:" << type.keyFingerprint;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputFile &type)
{
    d << "TLInputFile(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputFile:
        d << "id:" << type.id;
        d << "parts:" << type.parts;
        d << "name:" << type.name;
        d << "md5Checksum:" << type.md5Checksum;
        break;
    case TLValue::InputFileBig:
        d << "id:" << type.id;
        d << "parts:" << type.parts;
        d << "name:" << type.name;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputFileLocation &type)
{
    d << "TLInputFileLocation(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputFileLocation:
        d << "volumeId:" << type.volumeId;
        d << "localId:" << type.localId;
        d << "secret:" << type.secret;
        break;
    case TLValue::InputVideoFileLocation:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    case TLValue::InputEncryptedFileLocation:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    case TLValue::InputAudioFileLocation:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    case TLValue::InputDocumentFileLocation:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputGeoChat &type)
{
    d << "TLInputGeoChat(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputGeoChat:
        d << "chatId:" << type.chatId;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputGeoPoint &type)
{
    d << "TLInputGeoPoint(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputGeoPointEmpty:
        break;
    case TLValue::InputGeoPoint:
        d << "latitude:" << type.latitude;
        d << "longitude:" << type.longitude;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeer &type)
{
    d << "TLInputPeer(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPeerEmpty:
        break;
    case TLValue::InputPeerSelf:
        break;
    case TLValue::InputPeerContact:
        d << "userId:" << type.userId;
        break;
    case TLValue::InputPeerForeign:
        d << "userId:" << type.userId;
        d << "accessHash:" << type.accessHash;
        break;
    case TLValue::InputPeerChat:
        d << "chatId:" << type.chatId;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeerNotifyEvents &type)
{
    d << "TLInputPeerNotifyEvents(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPeerNotifyEventsEmpty:
        break;
    case TLValue::InputPeerNotifyEventsAll:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeerNotifySettings &type)
{
    d << "TLInputPeerNotifySettings(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPeerNotifySettings:
        d << "muteUntil:" << type.muteUntil;
        d << "sound:" << type.sound;
        d << "showPreviews:" << type.showPreviews;
        d << "eventsMask:" << type.eventsMask;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPhoto &type)
{
    d << "TLInputPhoto(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPhotoEmpty:
        break;
    case TLValue::InputPhoto:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPhotoCrop &type)
{
    d << "TLInputPhotoCrop(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPhotoCropAuto:
        break;
    case TLValue::InputPhotoCrop:
        d << "cropLeft:" << type.cropLeft;
        d << "cropTop:" << type.cropTop;
        d << "cropWidth:" << type.cropWidth;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPrivacyKey &type)
{
    d << "TLInputPrivacyKey(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputUser &type)
{
    d << "TLInputUser(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputUserEmpty:
        break;
    case TLValue::InputUserSelf:
        break;
    case TLValue::InputUserContact:
        d << "userId:" << type.userId;
        break;
    case TLValue::InputUserForeign:
        d << "userId:" << type.userId;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputVideo &type)
{
    d << "TLInputVideo(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputVideoEmpty:
        break;
    case TLValue::InputVideo:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesAffectedHistory &type)
{
    d << "TLMessagesAffectedHistory(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesAffectedHistory:
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        d << "offset:" << type.offset;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesDhConfig &type)
{
    d << "TLMessagesDhConfig(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesDhConfigNotModified:
        d << "random:" << type.random;
        break;
    case TLValue::MessagesDhConfig:
        d << "g:" << type.g;
        d << "p:" << type.p;
        d << "version:" << type.version;
        d << "random:" << type.random;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesFilter &type)
{
    d << "TLMessagesFilter(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputMessagesFilterEmpty:
        break;
    case TLValue::InputMessagesFilterPhotos:
        break;
    case TLValue::InputMessagesFilterVideo:
        break;
    case TLValue::InputMessagesFilterPhotoVideo:
        break;
    case TLValue::InputMessagesFilterPhotoVideoDocuments:
        break;
    case TLValue::InputMessagesFilterDocument:
        break;
    case TLValue::InputMessagesFilterAudio:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesSentEncryptedMessage &type)
{
    d << "TLMessagesSentEncryptedMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesSentEncryptedMessage:
        d << "date:" << type.date;
        break;
    case TLValue::MessagesSentEncryptedFile:
        d << "date:" << type.date;
        d << "file:" << type.file;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLNearestDc &type)
{
    d << "TLNearestDc(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::NearestDc:
        d << "country:" << type.country;
        d << "thisDc:" << type.thisDc;
        d << "nearestDc:" << type.nearestDc;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeer &type)
{
    d << "TLPeer(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PeerUser:
        d << "userId:" << type.userId;
        break;
    case TLValue::PeerChat:
        d << "chatId:" << type.chatId;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeerNotifyEvents &type)
{
    d << "TLPeerNotifyEvents(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PeerNotifyEventsEmpty:
        break;
    case TLValue::PeerNotifyEventsAll:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeerNotifySettings &type)
{
    d << "TLPeerNotifySettings(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PeerNotifySettingsEmpty:
        break;
    case TLValue::PeerNotifySettings:
        d << "muteUntil:" << type.muteUntil;
        d << "sound:" << type.sound;
        d << "showPreviews:" << type.showPreviews;
        d << "eventsMask:" << type.eventsMask;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhotoSize &type)
{
    d << "TLPhotoSize(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PhotoSizeEmpty:
        d << "type:" << type.type;
        break;
    case TLValue::PhotoSize:
        d << "type:" << type.type;
        d << "location:" << type.location;
        d << "w:" << type.w;
        d << "h:" << type.h;
        d << "size:" << type.size;
        break;
    case TLValue::PhotoCachedSize:
        d << "type:" << type.type;
        d << "location:" << type.location;
        d << "w:" << type.w;
        d << "h:" << type.h;
        d << "bytes:" << type.bytes;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPrivacyKey &type)
{
    d << "TLPrivacyKey(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPrivacyRule &type)
{
    d << "TLPrivacyRule(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PrivacyValueAllowContacts:
        break;
    case TLValue::PrivacyValueAllowAll:
        break;
    case TLValue::PrivacyValueAllowUsers:
        d << "users:" << type.users;
        break;
    case TLValue::PrivacyValueDisallowContacts:
        break;
    case TLValue::PrivacyValueDisallowAll:
        break;
    case TLValue::PrivacyValueDisallowUsers:
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSendMessageAction &type)
{
    d << "TLSendMessageAction(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::SendMessageTypingAction:
        break;
    case TLValue::SendMessageCancelAction:
        break;
    case TLValue::SendMessageRecordVideoAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
        break;
    case TLValue::SendMessageRecordAudioAction:
        break;
    case TLValue::SendMessageUploadAudioAction:
        break;
    case TLValue::SendMessageUploadPhotoAction:
        break;
    case TLValue::SendMessageUploadDocumentAction:
        break;
    case TLValue::SendMessageGeoLocationAction:
        break;
    case TLValue::SendMessageChooseContactAction:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStickerPack &type)
{
    d << "TLStickerPack(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::StickerPack:
        d << "emoticon:" << type.emoticon;
        d << "documents:" << type.documents;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStorageFileType &type)
{
    d << "TLStorageFileType(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::StorageFileUnknown:
        break;
    case TLValue::StorageFileJpeg:
        break;
    case TLValue::StorageFileGif:
        break;
    case TLValue::StorageFilePng:
        break;
    case TLValue::StorageFilePdf:
        break;
    case TLValue::StorageFileMp3:
        break;
    case TLValue::StorageFileMov:
        break;
    case TLValue::StorageFilePartial:
        break;
    case TLValue::StorageFileMp4:
        break;
    case TLValue::StorageFileWebp:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdatesState &type)
{
    d << "TLUpdatesState(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UpdatesState:
        d << "pts:" << type.pts;
        d << "qts:" << type.qts;
        d << "date:" << type.date;
        d << "seq:" << type.seq;
        d << "unreadCount:" << type.unreadCount;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUploadFile &type)
{
    d << "TLUploadFile(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UploadFile:
        d << "type:" << type.type;
        d << "mtime:" << type.mtime;
        d << "bytes:" << type.bytes;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserProfilePhoto &type)
{
    d << "TLUserProfilePhoto(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UserProfilePhotoEmpty:
        break;
    case TLValue::UserProfilePhoto:
        d << "photoId:" << type.photoId;
        d << "photoSmall:" << type.photoSmall;
        d << "photoBig:" << type.photoBig;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserStatus &type)
{
    d << "TLUserStatus(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UserStatusEmpty:
        break;
    case TLValue::UserStatusOnline:
        d << "expires:" << type.expires;
        break;
    case TLValue::UserStatusOffline:
        d << "wasOnline:" << type.wasOnline;
        break;
    case TLValue::UserStatusRecently:
        break;
    case TLValue::UserStatusLastWeek:
        break;
    case TLValue::UserStatusLastMonth:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLVideo &type)
{
    d << "TLVideo(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::VideoEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::Video:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "userId:" << type.userId;
        d << "date:" << type.date;
        d << "caption:" << type.caption;
        d << "duration:" << type.duration;
        d << "mimeType:" << type.mimeType;
        d << "size:" << type.size;
        d << "thumb:" << type.thumb;
        d << "dcId:" << type.dcId;
        d << "w:" << type.w;
        d << "h:" << type.h;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLWallPaper &type)
{
    d << "TLWallPaper(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::WallPaper:
        d << "id:" << type.id;
        d << "title:" << type.title;
        d << "sizes:" << type.sizes;
        d << "color:" << type.color;
        break;
    case TLValue::WallPaperSolid:
        d << "id:" << type.id;
        d << "title:" << type.title;
        d << "bgColor:" << type.bgColor;
        d << "color:" << type.color;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatPhoto &type)
{
    d << "TLChatPhoto(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ChatPhotoEmpty:
        break;
    case TLValue::ChatPhoto:
        d << "photoSmall:" << type.photoSmall;
        d << "photoBig:" << type.photoBig;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLConfig &type)
{
    d << "TLConfig(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::Config:
        d << "date:" << type.date;
        d << "expires:" << type.expires;
        d << "testMode:" << type.testMode;
        d << "thisDc:" << type.thisDc;
        d << "dcOptions:" << type.dcOptions;
        d << "chatBigSize:" << type.chatBigSize;
        d << "chatSizeMax:" << type.chatSizeMax;
        d << "broadcastSizeMax:" << type.broadcastSizeMax;
        d << "disabledFeatures:" << type.disabledFeatures;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactStatus &type)
{
    d << "TLContactStatus(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactStatus:
        d << "userId:" << type.userId;
        d << "status:" << type.status;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDialog &type)
{
    d << "TLDialog(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::Dialog:
        d << "peer:" << type.peer;
        d << "topMessage:" << type.topMessage;
        d << "unreadCount:" << type.unreadCount;
        d << "notifySettings:" << type.notifySettings;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDocument &type)
{
    d << "TLDocument(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::DocumentEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::Document:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "date:" << type.date;
        d << "mimeType:" << type.mimeType;
        d << "size:" << type.size;
        d << "thumb:" << type.thumb;
        d << "dcId:" << type.dcId;
        d << "attributes:" << type.attributes;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputChatPhoto &type)
{
    d << "TLInputChatPhoto(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        d << "file:" << type.file;
        d << "crop:" << type.crop;
        break;
    case TLValue::InputChatPhoto:
        d << "id:" << type.id;
        d << "crop:" << type.crop;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputMedia &type)
{
    d << "TLInputMedia(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        d << "file:" << type.file;
        break;
    case TLValue::InputMediaPhoto:
        d << "id:" << type.id;
        break;
    case TLValue::InputMediaGeoPoint:
        d << "geoPoint:" << type.geoPoint;
        break;
    case TLValue::InputMediaContact:
        d << "phoneNumber:" << type.phoneNumber;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        break;
    case TLValue::InputMediaUploadedVideo:
        d << "file:" << type.file;
        d << "duration:" << type.duration;
        d << "w:" << type.w;
        d << "h:" << type.h;
        d << "mimeType:" << type.mimeType;
        break;
    case TLValue::InputMediaUploadedThumbVideo:
        d << "file:" << type.file;
        d << "thumb:" << type.thumb;
        d << "duration:" << type.duration;
        d << "w:" << type.w;
        d << "h:" << type.h;
        d << "mimeType:" << type.mimeType;
        break;
    case TLValue::InputMediaVideo:
        d << "id:" << type.id;
        break;
    case TLValue::InputMediaUploadedAudio:
        d << "file:" << type.file;
        d << "duration:" << type.duration;
        d << "mimeType:" << type.mimeType;
        break;
    case TLValue::InputMediaAudio:
        d << "id:" << type.id;
        break;
    case TLValue::InputMediaUploadedDocument:
        d << "file:" << type.file;
        d << "mimeType:" << type.mimeType;
        d << "attributes:" << type.attributes;
        break;
    case TLValue::InputMediaUploadedThumbDocument:
        d << "file:" << type.file;
        d << "thumb:" << type.thumb;
        d << "mimeType:" << type.mimeType;
        d << "attributes:" << type.attributes;
        break;
    case TLValue::InputMediaDocument:
        d << "id:" << type.id;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputNotifyPeer &type)
{
    d << "TLInputNotifyPeer(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputNotifyPeer:
        d << "peer:" << type.peer;
        break;
    case TLValue::InputNotifyUsers:
        break;
    case TLValue::InputNotifyChats:
        break;
    case TLValue::InputNotifyAll:
        break;
    case TLValue::InputNotifyGeoChatPeer:
        d << "peer:" << type.peer;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPrivacyRule &type)
{
    d << "TLInputPrivacyRule(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
        break;
    case TLValue::InputPrivacyValueAllowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
        d << "users:" << type.users;
        break;
    case TLValue::InputPrivacyValueDisallowContacts:
        break;
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueDisallowUsers:
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesAllStickers &type)
{
    d << "TLMessagesAllStickers(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesAllStickersNotModified:
        break;
    case TLValue::MessagesAllStickers:
        d << "hash:" << type.hash;
        d << "packs:" << type.packs;
        d << "documents:" << type.documents;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStickers &type)
{
    d << "TLMessagesStickers(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesStickersNotModified:
        break;
    case TLValue::MessagesStickers:
        d << "hash:" << type.hash;
        d << "stickers:" << type.stickers;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLNotifyPeer &type)
{
    d << "TLNotifyPeer(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::NotifyPeer:
        d << "peer:" << type.peer;
        break;
    case TLValue::NotifyUsers:
        break;
    case TLValue::NotifyChats:
        break;
    case TLValue::NotifyAll:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoto &type)
{
    d << "TLPhoto(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PhotoEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::Photo:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "userId:" << type.userId;
        d << "date:" << type.date;
        d << "caption:" << type.caption;
        d << "geo:" << type.geo;
        d << "sizes:" << type.sizes;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUser &type)
{
    d << "TLUser(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UserEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::UserSelf:
        d << "id:" << type.id;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "username:" << type.username;
        d << "phone:" << type.phone;
        d << "photo:" << type.photo;
        d << "status:" << type.status;
        d << "inactive:" << type.inactive;
        break;
    case TLValue::UserContact:
        d << "id:" << type.id;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "username:" << type.username;
        d << "accessHash:" << type.accessHash;
        d << "phone:" << type.phone;
        d << "photo:" << type.photo;
        d << "status:" << type.status;
        break;
    case TLValue::UserRequest:
        d << "id:" << type.id;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "username:" << type.username;
        d << "accessHash:" << type.accessHash;
        d << "phone:" << type.phone;
        d << "photo:" << type.photo;
        d << "status:" << type.status;
        break;
    case TLValue::UserForeign:
        d << "id:" << type.id;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "username:" << type.username;
        d << "accessHash:" << type.accessHash;
        d << "photo:" << type.photo;
        d << "status:" << type.status;
        break;
    case TLValue::UserDeleted:
        d << "id:" << type.id;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "username:" << type.username;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPrivacyRules &type)
{
    d << "TLAccountPrivacyRules(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AccountPrivacyRules:
        d << "rules:" << type.rules;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthAuthorization &type)
{
    d << "TLAuthAuthorization(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::AuthAuthorization:
        d << "expires:" << type.expires;
        d << "user:" << type.user;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChat &type)
{
    d << "TLChat(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ChatEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::Chat:
        d << "id:" << type.id;
        d << "title:" << type.title;
        d << "photo:" << type.photo;
        d << "participantsCount:" << type.participantsCount;
        d << "date:" << type.date;
        d << "left:" << type.left;
        d << "version:" << type.version;
        break;
    case TLValue::ChatForbidden:
        d << "id:" << type.id;
        d << "title:" << type.title;
        d << "date:" << type.date;
        break;
    case TLValue::GeoChat:
        d << "id:" << type.id;
        d << "accessHash:" << type.accessHash;
        d << "title:" << type.title;
        d << "address:" << type.address;
        d << "venue:" << type.venue;
        d << "geo:" << type.geo;
        d << "photo:" << type.photo;
        d << "participantsCount:" << type.participantsCount;
        d << "date:" << type.date;
        d << "checkedIn:" << type.checkedIn;
        d << "version:" << type.version;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatFull &type)
{
    d << "TLChatFull(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ChatFull:
        d << "id:" << type.id;
        d << "participants:" << type.participants;
        d << "chatPhoto:" << type.chatPhoto;
        d << "notifySettings:" << type.notifySettings;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsBlocked &type)
{
    d << "TLContactsBlocked(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsBlocked:
        d << "blocked:" << type.blocked;
        d << "users:" << type.users;
        break;
    case TLValue::ContactsBlockedSlice:
        d << "count:" << type.count;
        d << "blocked:" << type.blocked;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsContacts &type)
{
    d << "TLContactsContacts(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        d << "contacts:" << type.contacts;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsFound &type)
{
    d << "TLContactsFound(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsFound:
        d << "results:" << type.results;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsImportedContacts &type)
{
    d << "TLContactsImportedContacts(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsImportedContacts:
        d << "imported:" << type.imported;
        d << "retryContacts:" << type.retryContacts;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsLink &type)
{
    d << "TLContactsLink(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsLink:
        d << "myLink:" << type.myLink;
        d << "foreignLink:" << type.foreignLink;
        d << "user:" << type.user;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsSuggested &type)
{
    d << "TLContactsSuggested(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::ContactsSuggested:
        d << "results:" << type.results;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpSupport &type)
{
    d << "TLHelpSupport(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::HelpSupport:
        d << "phoneNumber:" << type.phoneNumber;
        d << "user:" << type.user;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageAction &type)
{
    d << "TLMessageAction(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessageActionEmpty:
        break;
    case TLValue::MessageActionChatCreate:
        d << "title:" << type.title;
        d << "users:" << type.users;
        break;
    case TLValue::MessageActionChatEditTitle:
        d << "title:" << type.title;
        break;
    case TLValue::MessageActionChatEditPhoto:
        d << "photo:" << type.photo;
        break;
    case TLValue::MessageActionChatDeletePhoto:
        break;
    case TLValue::MessageActionChatAddUser:
        d << "userId:" << type.userId;
        break;
    case TLValue::MessageActionChatDeleteUser:
        d << "userId:" << type.userId;
        break;
    case TLValue::MessageActionGeoChatCreate:
        d << "title:" << type.title;
        d << "address:" << type.address;
        break;
    case TLValue::MessageActionGeoChatCheckin:
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageMedia &type)
{
    d << "TLMessageMedia(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessageMediaEmpty:
        break;
    case TLValue::MessageMediaPhoto:
        d << "photo:" << type.photo;
        break;
    case TLValue::MessageMediaVideo:
        d << "video:" << type.video;
        break;
    case TLValue::MessageMediaGeo:
        d << "geo:" << type.geo;
        break;
    case TLValue::MessageMediaContact:
        d << "phoneNumber:" << type.phoneNumber;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "userId:" << type.userId;
        break;
    case TLValue::MessageMediaUnsupported:
        d << "bytes:" << type.bytes;
        break;
    case TLValue::MessageMediaDocument:
        d << "document:" << type.document;
        break;
    case TLValue::MessageMediaAudio:
        d << "audio:" << type.audio;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesChatFull &type)
{
    d << "TLMessagesChatFull(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesChatFull:
        d << "fullChat:" << type.fullChat;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesChats &type)
{
    d << "TLMessagesChats(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesChats:
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesSentMessage &type)
{
    d << "TLMessagesSentMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesSentMessage:
        d << "id:" << type.id;
        d << "date:" << type.date;
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        break;
    case TLValue::MessagesSentMessageLink:
        d << "id:" << type.id;
        d << "date:" << type.date;
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        d << "links:" << type.links;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhotosPhoto &type)
{
    d << "TLPhotosPhoto(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PhotosPhoto:
        d << "photo:" << type.photo;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhotosPhotos &type)
{
    d << "TLPhotosPhotos(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::PhotosPhotos:
        d << "photos:" << type.photos;
        d << "users:" << type.users;
        break;
    case TLValue::PhotosPhotosSlice:
        d << "count:" << type.count;
        d << "photos:" << type.photos;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserFull &type)
{
    d << "TLUserFull(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UserFull:
        d << "user:" << type.user;
        d << "link:" << type.link;
        d << "profilePhoto:" << type.profilePhoto;
        d << "notifySettings:" << type.notifySettings;
        d << "blocked:" << type.blocked;
        d << "realFirstName:" << type.realFirstName;
        d << "realLastName:" << type.realLastName;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGeoChatMessage &type)
{
    d << "TLGeoChatMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::GeoChatMessageEmpty:
        d << "chatId:" << type.chatId;
        d << "id:" << type.id;
        break;
    case TLValue::GeoChatMessage:
        d << "chatId:" << type.chatId;
        d << "id:" << type.id;
        d << "fromId:" << type.fromId;
        d << "date:" << type.date;
        d << "message:" << type.message;
        d << "media:" << type.media;
        break;
    case TLValue::GeoChatMessageService:
        d << "chatId:" << type.chatId;
        d << "id:" << type.id;
        d << "fromId:" << type.fromId;
        d << "date:" << type.date;
        d << "action:" << type.action;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGeochatsLocated &type)
{
    d << "TLGeochatsLocated(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::GeochatsLocated:
        d << "results:" << type.results;
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGeochatsMessages &type)
{
    d << "TLGeochatsMessages(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::GeochatsMessages:
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    case TLValue::GeochatsMessagesSlice:
        d << "count:" << type.count;
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGeochatsStatedMessage &type)
{
    d << "TLGeochatsStatedMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::GeochatsStatedMessage:
        d << "message:" << type.message;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "seq:" << type.seq;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessage &type)
{
    d << "TLMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessageEmpty:
        d << "id:" << type.id;
        break;
    case TLValue::Message:
        d << "flags:" << type.flags;
        d << "id:" << type.id;
        d << "fromId:" << type.fromId;
        d << "toId:" << type.toId;
        d << "date:" << type.date;
        d << "message:" << type.message;
        d << "media:" << type.media;
        break;
    case TLValue::MessageForwarded:
        d << "flags:" << type.flags;
        d << "id:" << type.id;
        d << "fwdFromId:" << type.fwdFromId;
        d << "fwdDate:" << type.fwdDate;
        d << "fromId:" << type.fromId;
        d << "toId:" << type.toId;
        d << "date:" << type.date;
        d << "message:" << type.message;
        d << "media:" << type.media;
        break;
    case TLValue::MessageService:
        d << "flags:" << type.flags;
        d << "id:" << type.id;
        d << "fromId:" << type.fromId;
        d << "toId:" << type.toId;
        d << "date:" << type.date;
        d << "action:" << type.action;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesDialogs &type)
{
    d << "TLMessagesDialogs(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesDialogs:
        d << "dialogs:" << type.dialogs;
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    case TLValue::MessagesDialogsSlice:
        d << "count:" << type.count;
        d << "dialogs:" << type.dialogs;
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesMessages &type)
{
    d << "TLMessagesMessages(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesMessages:
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    case TLValue::MessagesMessagesSlice:
        d << "count:" << type.count;
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStatedMessage &type)
{
    d << "TLMessagesStatedMessage(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesStatedMessage:
        d << "message:" << type.message;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        break;
    case TLValue::MessagesStatedMessageLink:
        d << "message:" << type.message;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "links:" << type.links;
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStatedMessages &type)
{
    d << "TLMessagesStatedMessages(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::MessagesStatedMessages:
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        break;
    case TLValue::MessagesStatedMessagesLinks:
        d << "messages:" << type.messages;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "links:" << type.links;
        d << "pts:" << type.pts;
        d << "seq:" << type.seq;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdate &type)
{
    d << "TLUpdate(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UpdateNewMessage:
        d << "message:" << type.message;
        d << "pts:" << type.pts;
        break;
    case TLValue::UpdateMessageID:
        d << "id:" << type.id;
        d << "randomId:" << type.randomId;
        break;
    case TLValue::UpdateReadMessages:
        d << "messages:" << type.messages;
        d << "pts:" << type.pts;
        break;
    case TLValue::UpdateDeleteMessages:
        d << "messages:" << type.messages;
        d << "pts:" << type.pts;
        break;
    case TLValue::UpdateUserTyping:
        d << "userId:" << type.userId;
        d << "action:" << type.action;
        break;
    case TLValue::UpdateChatUserTyping:
        d << "chatId:" << type.chatId;
        d << "userId:" << type.userId;
        d << "action:" << type.action;
        break;
    case TLValue::UpdateChatParticipants:
        d << "participants:" << type.participants;
        break;
    case TLValue::UpdateUserStatus:
        d << "userId:" << type.userId;
        d << "status:" << type.status;
        break;
    case TLValue::UpdateUserName:
        d << "userId:" << type.userId;
        d << "firstName:" << type.firstName;
        d << "lastName:" << type.lastName;
        d << "username:" << type.username;
        break;
    case TLValue::UpdateUserPhoto:
        d << "userId:" << type.userId;
        d << "date:" << type.date;
        d << "photo:" << type.photo;
        d << "previous:" << type.previous;
        break;
    case TLValue::UpdateContactRegistered:
        d << "userId:" << type.userId;
        d << "date:" << type.date;
        break;
    case TLValue::UpdateContactLink:
        d << "userId:" << type.userId;
        d << "myLink:" << type.myLink;
        d << "foreignLink:" << type.foreignLink;
        break;
    case TLValue::UpdateNewAuthorization:
        d << "authKeyId:" << type.authKeyId;
        d << "date:" << type.date;
        d << "device:" << type.device;
        d << "location:" << type.location;
        break;
    case TLValue::UpdateNewGeoChatMessage:
        d << "message:" << type.message;
        break;
    case TLValue::UpdateNewEncryptedMessage:
        d << "message:" << type.message;
        d << "qts:" << type.qts;
        break;
    case TLValue::UpdateEncryptedChatTyping:
        d << "chatId:" << type.chatId;
        break;
    case TLValue::UpdateEncryption:
        d << "chat:" << type.chat;
        d << "date:" << type.date;
        break;
    case TLValue::UpdateEncryptedMessagesRead:
        d << "chatId:" << type.chatId;
        d << "maxDate:" << type.maxDate;
        d << "date:" << type.date;
        break;
    case TLValue::UpdateChatParticipantAdd:
        d << "chatId:" << type.chatId;
        d << "userId:" << type.userId;
        d << "inviterId:" << type.inviterId;
        d << "version:" << type.version;
        break;
    case TLValue::UpdateChatParticipantDelete:
        d << "chatId:" << type.chatId;
        d << "userId:" << type.userId;
        d << "version:" << type.version;
        break;
    case TLValue::UpdateDcOptions:
        d << "dcOptions:" << type.dcOptions;
        break;
    case TLValue::UpdateUserBlocked:
        d << "userId:" << type.userId;
        d << "blocked:" << type.blocked;
        break;
    case TLValue::UpdateNotifySettings:
        d << "peer:" << type.peer;
        d << "notifySettings:" << type.notifySettings;
        break;
    case TLValue::UpdateServiceNotification:
        d << "type:" << type.type;
        d << "message:" << type.message;
        d << "media:" << type.media;
        d << "popup:" << type.popup;
        break;
    case TLValue::UpdatePrivacy:
        d << "key:" << type.key;
        d << "rules:" << type.rules;
        break;
    case TLValue::UpdateUserPhone:
        d << "userId:" << type.userId;
        d << "phone:" << type.phone;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdates &type)
{
    d << "TLUpdates(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UpdatesTooLong:
        break;
    case TLValue::UpdateShortMessage:
        d << "id:" << type.id;
        d << "fromId:" << type.fromId;
        d << "message:" << type.message;
        d << "pts:" << type.pts;
        d << "date:" << type.date;
        d << "seq:" << type.seq;
        break;
    case TLValue::UpdateShortChatMessage:
        d << "id:" << type.id;
        d << "fromId:" << type.fromId;
        d << "chatId:" << type.chatId;
        d << "message:" << type.message;
        d << "pts:" << type.pts;
        d << "date:" << type.date;
        d << "seq:" << type.seq;
        break;
    case TLValue::UpdateShort:
        d << "update:" << type.update;
        d << "date:" << type.date;
        break;
    case TLValue::UpdatesCombined:
        d << "updates:" << type.updates;
        d << "users:" << type.users;
        d << "chats:" << type.chats;
        d << "date:" << type.date;
        d << "seqStart:" << type.seqStart;
        d << "seq:" << type.seq;
        break;
    case TLValue::Updates:
        d << "updates:" << type.updates;
        d << "users:" << type.users;
        d << "chats:" << type.chats;
        d << "date:" << type.date;
        d << "seq:" << type.seq;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdatesDifference &type)
{
    d << "TLUpdatesDifference(" << type.tlType.toString() << ") {";
    switch (type.tlType) {
    case TLValue::UpdatesDifferenceEmpty:
        d << "date:" << type.date;
        d << "seq:" << type.seq;
        break;
    case TLValue::UpdatesDifference:
        d << "newMessages:" << type.newMessages;
        d << "newEncryptedMessages:" << type.newEncryptedMessages;
        d << "otherUpdates:" << type.otherUpdates;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "state:" << type.state;
        break;
    case TLValue::UpdatesDifferenceSlice:
        d << "newMessages:" << type.newMessages;
        d << "newEncryptedMessages:" << type.newEncryptedMessages;
        d << "otherUpdates:" << type.otherUpdates;
        d << "chats:" << type.chats;
        d << "users:" << type.users;
        d << "intermediateState:" << type.intermediateState;
        break;
    default:
        break;
    }
    d << "}";

    return d;
}

// End of generated TLTypes debug operators
