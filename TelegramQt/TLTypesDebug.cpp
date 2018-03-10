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

#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

using namespace Telegram::Debug;

// Generated TLTypes debug operators
QDebug operator<<(QDebug d, const TLAccountDaysTTL &type)
{
    d.noquote().nospace();
    d << "TLAccountDaysTTL(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountDaysTTL:
        d << spacer.innerSpaces() << "days: " << type.days <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPassword &type)
{
    d.noquote().nospace();
    d << "TLAccountPassword(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountNoPassword:
        d << spacer.innerSpaces() << "newSalt: " << type.newSalt.toHex() <<"\n";
        d << spacer.innerSpaces() << "emailUnconfirmedPattern: " << type.emailUnconfirmedPattern <<"\n";
        break;
    case TLValue::AccountPassword:
        d << spacer.innerSpaces() << "currentSalt: " << type.currentSalt.toHex() <<"\n";
        d << spacer.innerSpaces() << "newSalt: " << type.newSalt.toHex() <<"\n";
        d << spacer.innerSpaces() << "hint: " << type.hint <<"\n";
        d << spacer.innerSpaces() << "hasRecovery: " << type.hasRecovery <<"\n";
        d << spacer.innerSpaces() << "emailUnconfirmedPattern: " << type.emailUnconfirmedPattern <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPasswordInputSettings &type)
{
    d.noquote().nospace();
    d << "TLAccountPasswordInputSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPasswordInputSettings:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "newSalt: " << type.newSalt.toHex() <<"\n";
        }
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "newPasswordHash: " << type.newPasswordHash.toHex() <<"\n";
        }
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "hint: " << type.hint <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPasswordSettings &type)
{
    d.noquote().nospace();
    d << "TLAccountPasswordSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPasswordSettings:
        d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountTmpPassword &type)
{
    d.noquote().nospace();
    d << "TLAccountTmpPassword(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountTmpPassword:
        d << spacer.innerSpaces() << "tmpPassword: " << type.tmpPassword.toHex() <<"\n";
        d << spacer.innerSpaces() << "validUntil: " << type.validUntil <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthCheckedPhone &type)
{
    d.noquote().nospace();
    d << "TLAuthCheckedPhone(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthCheckedPhone:
        d << spacer.innerSpaces() << "phoneRegistered: " << type.phoneRegistered <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthCodeType &type)
{
    d.noquote().nospace();
    d << "TLAuthCodeType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthCodeTypeSms:
    case TLValue::AuthCodeTypeCall:
    case TLValue::AuthCodeTypeFlashCall:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &type)
{
    d.noquote().nospace();
    d << "TLAuthExportedAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthExportedAuthorization:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthPasswordRecovery &type)
{
    d.noquote().nospace();
    d << "TLAuthPasswordRecovery(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthPasswordRecovery:
        d << spacer.innerSpaces() << "emailPattern: " << type.emailPattern <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthSentCodeType &type)
{
    d.noquote().nospace();
    d << "TLAuthSentCodeType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthSentCodeTypeApp:
    case TLValue::AuthSentCodeTypeSms:
    case TLValue::AuthSentCodeTypeCall:
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::AuthSentCodeTypeFlashCall:
        d << spacer.innerSpaces() << "pattern: " << type.pattern <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthorization &type)
{
    d.noquote().nospace();
    d << "TLAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Authorization:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "deviceModel: " << type.deviceModel <<"\n";
        d << spacer.innerSpaces() << "platform: " << type.platform <<"\n";
        d << spacer.innerSpaces() << "systemVersion: " << type.systemVersion <<"\n";
        d << spacer.innerSpaces() << "apiId: " << type.apiId <<"\n";
        d << spacer.innerSpaces() << "appName: " << type.appName <<"\n";
        d << spacer.innerSpaces() << "appVersion: " << type.appVersion <<"\n";
        d << spacer.innerSpaces() << "dateCreated: " << type.dateCreated <<"\n";
        d << spacer.innerSpaces() << "dateActive: " << type.dateActive <<"\n";
        d << spacer.innerSpaces() << "ip: " << type.ip <<"\n";
        d << spacer.innerSpaces() << "country: " << type.country <<"\n";
        d << spacer.innerSpaces() << "region: " << type.region <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBadMsgNotification &type)
{
    d.noquote().nospace();
    d << "TLBadMsgNotification(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BadMsgNotification:
        d << spacer.innerSpaces() << "badMsgId: " << type.badMsgId <<"\n";
        d << spacer.innerSpaces() << "badMsgSeqno: " << type.badMsgSeqno <<"\n";
        d << spacer.innerSpaces() << "errorCode: " << type.errorCode <<"\n";
        break;
    case TLValue::BadServerSalt:
        d << spacer.innerSpaces() << "badMsgId: " << type.badMsgId <<"\n";
        d << spacer.innerSpaces() << "badMsgSeqno: " << type.badMsgSeqno <<"\n";
        d << spacer.innerSpaces() << "errorCode: " << type.errorCode <<"\n";
        d << spacer.innerSpaces() << "newServerSalt: " << type.newServerSalt <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBotCommand &type)
{
    d.noquote().nospace();
    d << "TLBotCommand(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotCommand:
        d << spacer.innerSpaces() << "command: " << type.command <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBotInfo &type)
{
    d.noquote().nospace();
    d << "TLBotInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInfo:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        d << spacer.innerSpaces() << "commands: " << type.commands <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLCdnFileHash &type)
{
    d.noquote().nospace();
    d << "TLCdnFileHash(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::CdnFileHash:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "limit: " << type.limit <<"\n";
        d << spacer.innerSpaces() << "hash: " << type.hash.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLCdnPublicKey &type)
{
    d.noquote().nospace();
    d << "TLCdnPublicKey(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::CdnPublicKey:
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "publicKey: " << type.publicKey <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelParticipantsFilter &type)
{
    d.noquote().nospace();
    d << "TLChannelParticipantsFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelParticipantsRecent:
    case TLValue::ChannelParticipantsAdmins:
    case TLValue::ChannelParticipantsBots:
        break;
    case TLValue::ChannelParticipantsKicked:
    case TLValue::ChannelParticipantsBanned:
    case TLValue::ChannelParticipantsSearch:
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatParticipant &type)
{
    d.noquote().nospace();
    d << "TLChatParticipant(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatParticipant:
    case TLValue::ChatParticipantAdmin:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChatParticipantCreator:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatParticipants &type)
{
    d.noquote().nospace();
    d << "TLChatParticipants(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatParticipantsForbidden:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "selfParticipant: " << type.selfParticipant <<"\n";
        }
        break;
    case TLValue::ChatParticipants:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLClientDHInnerData &type)
{
    d.noquote().nospace();
    d << "TLClientDHInnerData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ClientDHInnerData:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "retryId: " << type.retryId <<"\n";
        d << spacer.innerSpaces() << "gB: " << type.gB <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContact &type)
{
    d.noquote().nospace();
    d << "TLContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Contact:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "mutual: " << type.mutual <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactBlocked &type)
{
    d.noquote().nospace();
    d << "TLContactBlocked(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactBlocked:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactLink &type)
{
    d.noquote().nospace();
    d << "TLContactLink(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactLinkUnknown:
    case TLValue::ContactLinkNone:
    case TLValue::ContactLinkHasPhone:
    case TLValue::ContactLinkContact:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDataJSON &type)
{
    d.noquote().nospace();
    d << "TLDataJSON(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DataJSON:
        d << spacer.innerSpaces() << "data: " << type.data <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDestroyAuthKeyRes &type)
{
    d.noquote().nospace();
    d << "TLDestroyAuthKeyRes(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DestroyAuthKeyOk:
    case TLValue::DestroyAuthKeyNone:
    case TLValue::DestroyAuthKeyFail:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDestroySessionRes &type)
{
    d.noquote().nospace();
    d << "TLDestroySessionRes(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DestroySessionOk:
    case TLValue::DestroySessionNone:
        d << spacer.innerSpaces() << "sessionId: " << type.sessionId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDisabledFeature &type)
{
    d.noquote().nospace();
    d << "TLDisabledFeature(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DisabledFeature:
        d << spacer.innerSpaces() << "feature: " << type.feature <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedChat &type)
{
    d.noquote().nospace();
    d << "TLEncryptedChat(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedChatEmpty:
    case TLValue::EncryptedChatDiscarded:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::EncryptedChatWaiting:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        break;
    case TLValue::EncryptedChatRequested:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gA: " << type.gA.toHex() <<"\n";
        break;
    case TLValue::EncryptedChat:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gAOrB: " << type.gAOrB.toHex() <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedFile &type)
{
    d.noquote().nospace();
    d << "TLEncryptedFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedFileEmpty:
        break;
    case TLValue::EncryptedFile:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedMessage &type)
{
    d.noquote().nospace();
    d << "TLEncryptedMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedMessage:
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        break;
    case TLValue::EncryptedMessageService:
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLError &type)
{
    d.noquote().nospace();
    d << "TLError(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Error:
        d << spacer.innerSpaces() << "code: " << type.code <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLExportedChatInvite &type)
{
    d.noquote().nospace();
    d << "TLExportedChatInvite(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatInviteEmpty:
        break;
    case TLValue::ChatInviteExported:
        d << spacer.innerSpaces() << "link: " << type.link <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLExportedMessageLink &type)
{
    d.noquote().nospace();
    d << "TLExportedMessageLink(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ExportedMessageLink:
        d << spacer.innerSpaces() << "link: " << type.link <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFileLocation &type)
{
    d.noquote().nospace();
    d << "TLFileLocation(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FileLocationUnavailable:
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        break;
    case TLValue::FileLocation:
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFutureSalt &type)
{
    d.noquote().nospace();
    d << "TLFutureSalt(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FutureSalt:
        d << spacer.innerSpaces() << "validSince: " << type.validSince <<"\n";
        d << spacer.innerSpaces() << "validUntil: " << type.validUntil <<"\n";
        d << spacer.innerSpaces() << "salt: " << type.salt <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFutureSalts &type)
{
    d.noquote().nospace();
    d << "TLFutureSalts(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FutureSalts:
        d << spacer.innerSpaces() << "reqMsgId: " << type.reqMsgId <<"\n";
        d << spacer.innerSpaces() << "now: " << type.now <<"\n";
        d << spacer.innerSpaces() << "salts: " << type.salts <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGeoPoint &type)
{
    d.noquote().nospace();
    d << "TLGeoPoint(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::GeoPointEmpty:
        break;
    case TLValue::GeoPoint:
        d << spacer.innerSpaces() << "longitude: " << type.longitude <<"\n";
        d << spacer.innerSpaces() << "latitude: " << type.latitude <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpAppUpdate &type)
{
    d.noquote().nospace();
    d << "TLHelpAppUpdate(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpAppUpdate:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "critical: " << type.critical <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::HelpNoAppUpdate:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpInviteText &type)
{
    d.noquote().nospace();
    d << "TLHelpInviteText(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpInviteText:
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpTermsOfService &type)
{
    d.noquote().nospace();
    d << "TLHelpTermsOfService(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpTermsOfService:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHighScore &type)
{
    d.noquote().nospace();
    d << "TLHighScore(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HighScore:
        d << spacer.innerSpaces() << "pos: " << type.pos <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "score: " << type.score <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHttpWait &type)
{
    d.noquote().nospace();
    d << "TLHttpWait(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HttpWait:
        d << spacer.innerSpaces() << "maxDelay: " << type.maxDelay <<"\n";
        d << spacer.innerSpaces() << "waitAfter: " << type.waitAfter <<"\n";
        d << spacer.innerSpaces() << "maxWait: " << type.maxWait <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLImportedContact &type)
{
    d.noquote().nospace();
    d << "TLImportedContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ImportedContact:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "clientId: " << type.clientId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInlineBotSwitchPM &type)
{
    d.noquote().nospace();
    d << "TLInlineBotSwitchPM(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InlineBotSwitchPM:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "startParam: " << type.startParam <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputAppEvent &type)
{
    d.noquote().nospace();
    d << "TLInputAppEvent(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputAppEvent:
        d << spacer.innerSpaces() << "time: " << type.time <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "data: " << type.data <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputBotInlineMessageID &type)
{
    d.noquote().nospace();
    d << "TLInputBotInlineMessageID(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineMessageID:
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputChannel &type)
{
    d.noquote().nospace();
    d << "TLInputChannel(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputChannelEmpty:
        break;
    case TLValue::InputChannel:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputContact &type)
{
    d.noquote().nospace();
    d << "TLInputContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhoneContact:
        d << spacer.innerSpaces() << "clientId: " << type.clientId <<"\n";
        d << spacer.innerSpaces() << "phone: " << type.phone <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputDocument &type)
{
    d.noquote().nospace();
    d << "TLInputDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputDocumentEmpty:
        break;
    case TLValue::InputDocument:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputEncryptedChat &type)
{
    d.noquote().nospace();
    d << "TLInputEncryptedChat(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputEncryptedChat:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputEncryptedFile &type)
{
    d.noquote().nospace();
    d << "TLInputEncryptedFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputEncryptedFileEmpty:
        break;
    case TLValue::InputEncryptedFileUploaded:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "md5Checksum: " << type.md5Checksum <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        break;
    case TLValue::InputEncryptedFile:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputEncryptedFileBigUploaded:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputFile &type)
{
    d.noquote().nospace();
    d << "TLInputFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputFile:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        d << spacer.innerSpaces() << "md5Checksum: " << type.md5Checksum <<"\n";
        break;
    case TLValue::InputFileBig:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputFileLocation &type)
{
    d.noquote().nospace();
    d << "TLInputFileLocation(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputFileLocation:
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        break;
    case TLValue::InputEncryptedFileLocation:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputDocumentFileLocation:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputGeoPoint &type)
{
    d.noquote().nospace();
    d << "TLInputGeoPoint(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputGeoPointEmpty:
        break;
    case TLValue::InputGeoPoint:
        d << spacer.innerSpaces() << "latitude: " << type.latitude <<"\n";
        d << spacer.innerSpaces() << "longitude: " << type.longitude <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeer &type)
{
    d.noquote().nospace();
    d << "TLInputPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
        break;
    case TLValue::InputPeerChat:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::InputPeerUser:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputPeerChannel:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeerNotifyEvents &type)
{
    d.noquote().nospace();
    d << "TLInputPeerNotifyEvents(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerNotifyEventsEmpty:
    case TLValue::InputPeerNotifyEventsAll:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPhoneCall &type)
{
    d.noquote().nospace();
    d << "TLInputPhoneCall(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhoneCall:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPhoto &type)
{
    d.noquote().nospace();
    d << "TLInputPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhotoEmpty:
        break;
    case TLValue::InputPhoto:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPrivacyKey &type)
{
    d.noquote().nospace();
    d << "TLInputPrivacyKey(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
    case TLValue::InputPrivacyKeyChatInvite:
    case TLValue::InputPrivacyKeyPhoneCall:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputStickerSet &type)
{
    d.noquote().nospace();
    d << "TLInputStickerSet(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputStickerSetEmpty:
        break;
    case TLValue::InputStickerSetID:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputStickerSetShortName:
        d << spacer.innerSpaces() << "shortName: " << type.shortName <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputStickeredMedia &type)
{
    d.noquote().nospace();
    d << "TLInputStickeredMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputStickeredMediaPhoto:
        d << spacer.innerSpaces() << "inputPhotoId: " << type.inputPhotoId <<"\n";
        break;
    case TLValue::InputStickeredMediaDocument:
        d << spacer.innerSpaces() << "inputDocumentId: " << type.inputDocumentId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputUser &type)
{
    d.noquote().nospace();
    d << "TLInputUser(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
        break;
    case TLValue::InputUser:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputWebFileLocation &type)
{
    d.noquote().nospace();
    d << "TLInputWebFileLocation(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputWebFileLocation:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLIpPort &type)
{
    d.noquote().nospace();
    d << "TLIpPort(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::IpPort:
        d << spacer.innerSpaces() << "ipv4: " << type.ipv4 <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLLabeledPrice &type)
{
    d.noquote().nospace();
    d << "TLLabeledPrice(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LabeledPrice:
        d << spacer.innerSpaces() << "label: " << type.label <<"\n";
        d << spacer.innerSpaces() << "amount: " << type.amount <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLLangPackLanguage &type)
{
    d.noquote().nospace();
    d << "TLLangPackLanguage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LangPackLanguage:
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        d << spacer.innerSpaces() << "nativeName: " << type.nativeName <<"\n";
        d << spacer.innerSpaces() << "langCode: " << type.langCode <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLLangPackString &type)
{
    d.noquote().nospace();
    d << "TLLangPackString(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LangPackString:
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        d << spacer.innerSpaces() << "value: " << type.value <<"\n";
        break;
    case TLValue::LangPackStringPluralized:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "zeroValue: " << type.zeroValue <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "oneValue: " << type.oneValue <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "twoValue: " << type.twoValue <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "fewValue: " << type.fewValue <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "manyValue: " << type.manyValue <<"\n";
        }
        d << spacer.innerSpaces() << "otherValue: " << type.otherValue <<"\n";
        break;
    case TLValue::LangPackStringDeleted:
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMaskCoords &type)
{
    d.noquote().nospace();
    d << "TLMaskCoords(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MaskCoords:
        d << spacer.innerSpaces() << "n: " << type.n <<"\n";
        d << spacer.innerSpaces() << "x: " << type.x <<"\n";
        d << spacer.innerSpaces() << "y: " << type.y <<"\n";
        d << spacer.innerSpaces() << "zoom: " << type.zoom <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageEntity &type)
{
    d.noquote().nospace();
    d << "TLMessageEntity(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageEntityUnknown:
    case TLValue::MessageEntityMention:
    case TLValue::MessageEntityHashtag:
    case TLValue::MessageEntityBotCommand:
    case TLValue::MessageEntityUrl:
    case TLValue::MessageEntityEmail:
    case TLValue::MessageEntityBold:
    case TLValue::MessageEntityItalic:
    case TLValue::MessageEntityCode:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityPre:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "language: " << type.language <<"\n";
        break;
    case TLValue::MessageEntityTextUrl:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    case TLValue::MessageEntityMentionName:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "quint32UserId: " << type.quint32UserId <<"\n";
        break;
    case TLValue::InputMessageEntityMentionName:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "inputUserUserId: " << type.inputUserUserId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageFwdHeader &type)
{
    d.noquote().nospace();
    d << "TLMessageFwdHeader(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageFwdHeader:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "fromId: " << type.fromId <<"\n";
        }
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "channelPost: " << type.channelPost <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "postAuthor: " << type.postAuthor <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageRange &type)
{
    d.noquote().nospace();
    d << "TLMessageRange(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageRange:
        d << spacer.innerSpaces() << "minId: " << type.minId <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesAffectedHistory &type)
{
    d.noquote().nospace();
    d << "TLMessagesAffectedHistory(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesAffectedHistory:
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesAffectedMessages &type)
{
    d.noquote().nospace();
    d << "TLMessagesAffectedMessages(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesAffectedMessages:
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesDhConfig &type)
{
    d.noquote().nospace();
    d << "TLMessagesDhConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesDhConfigNotModified:
        d << spacer.innerSpaces() << "random: " << type.random.toHex() <<"\n";
        break;
    case TLValue::MessagesDhConfig:
        d << spacer.innerSpaces() << "g: " << type.g <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p.toHex() <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        d << spacer.innerSpaces() << "random: " << type.random.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesSentEncryptedMessage &type)
{
    d.noquote().nospace();
    d << "TLMessagesSentEncryptedMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesSentEncryptedMessage:
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::MessagesSentEncryptedFile:
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMsgDetailedInfo &type)
{
    d.noquote().nospace();
    d << "TLMsgDetailedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgDetailedInfo:
        d << spacer.innerSpaces() << "msgId: " << type.msgId <<"\n";
        d << spacer.innerSpaces() << "answerMsgId: " << type.answerMsgId <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
        d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        break;
    case TLValue::MsgNewDetailedInfo:
        d << spacer.innerSpaces() << "answerMsgId: " << type.answerMsgId <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
        d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMsgResendReq &type)
{
    d.noquote().nospace();
    d << "TLMsgResendReq(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgResendReq:
        d << spacer.innerSpaces() << "msgIds: " << type.msgIds <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMsgsAck &type)
{
    d.noquote().nospace();
    d << "TLMsgsAck(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsAck:
        d << spacer.innerSpaces() << "msgIds: " << type.msgIds <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMsgsAllInfo &type)
{
    d.noquote().nospace();
    d << "TLMsgsAllInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsAllInfo:
        d << spacer.innerSpaces() << "msgIds: " << type.msgIds <<"\n";
        d << spacer.innerSpaces() << "info: " << type.info <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMsgsStateInfo &type)
{
    d.noquote().nospace();
    d << "TLMsgsStateInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsStateInfo:
        d << spacer.innerSpaces() << "reqMsgId: " << type.reqMsgId <<"\n";
        d << spacer.innerSpaces() << "info: " << type.info <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMsgsStateReq &type)
{
    d.noquote().nospace();
    d << "TLMsgsStateReq(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsStateReq:
        d << spacer.innerSpaces() << "msgIds: " << type.msgIds <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLNearestDc &type)
{
    d.noquote().nospace();
    d << "TLNearestDc(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NearestDc:
        d << spacer.innerSpaces() << "country: " << type.country <<"\n";
        d << spacer.innerSpaces() << "thisDc: " << type.thisDc <<"\n";
        d << spacer.innerSpaces() << "nearestDc: " << type.nearestDc <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLNewSession &type)
{
    d.noquote().nospace();
    d << "TLNewSession(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NewSessionCreated:
        d << spacer.innerSpaces() << "firstMsgId: " << type.firstMsgId <<"\n";
        d << spacer.innerSpaces() << "uniqueId: " << type.uniqueId <<"\n";
        d << spacer.innerSpaces() << "serverSalt: " << type.serverSalt <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPQInnerData &type)
{
    d.noquote().nospace();
    d << "TLPQInnerData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PQInnerData:
        d << spacer.innerSpaces() << "pq: " << type.pq <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonce: " << type.newNonce <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentCharge &type)
{
    d.noquote().nospace();
    d << "TLPaymentCharge(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentCharge:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "providerChargeId: " << type.providerChargeId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentSavedCredentials &type)
{
    d.noquote().nospace();
    d << "TLPaymentSavedCredentials(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentSavedCredentialsCard:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeer &type)
{
    d.noquote().nospace();
    d << "TLPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerUser:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::PeerChat:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::PeerChannel:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeerNotifyEvents &type)
{
    d.noquote().nospace();
    d << "TLPeerNotifyEvents(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerNotifyEventsEmpty:
    case TLValue::PeerNotifyEventsAll:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneCallDiscardReason &type)
{
    d.noquote().nospace();
    d << "TLPhoneCallDiscardReason(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneCallDiscardReasonMissed:
    case TLValue::PhoneCallDiscardReasonDisconnect:
    case TLValue::PhoneCallDiscardReasonHangup:
    case TLValue::PhoneCallDiscardReasonBusy:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneConnection &type)
{
    d.noquote().nospace();
    d << "TLPhoneConnection(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneConnection:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "ip: " << type.ip <<"\n";
        d << spacer.innerSpaces() << "ipv6: " << type.ipv6 <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        d << spacer.innerSpaces() << "peerTag: " << type.peerTag.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhotoSize &type)
{
    d.noquote().nospace();
    d << "TLPhotoSize(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotoSizeEmpty:
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        break;
    case TLValue::PhotoSize:
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "location: " << type.location <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        break;
    case TLValue::PhotoCachedSize:
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "location: " << type.location <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPong &type)
{
    d.noquote().nospace();
    d << "TLPong(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Pong:
        d << spacer.innerSpaces() << "msgId: " << type.msgId <<"\n";
        d << spacer.innerSpaces() << "pingId: " << type.pingId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPopularContact &type)
{
    d.noquote().nospace();
    d << "TLPopularContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PopularContact:
        d << spacer.innerSpaces() << "clientId: " << type.clientId <<"\n";
        d << spacer.innerSpaces() << "importers: " << type.importers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPostAddress &type)
{
    d.noquote().nospace();
    d << "TLPostAddress(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PostAddress:
        d << spacer.innerSpaces() << "streetLine1: " << type.streetLine1 <<"\n";
        d << spacer.innerSpaces() << "streetLine2: " << type.streetLine2 <<"\n";
        d << spacer.innerSpaces() << "city: " << type.city <<"\n";
        d << spacer.innerSpaces() << "state: " << type.state <<"\n";
        d << spacer.innerSpaces() << "countryIso2: " << type.countryIso2 <<"\n";
        d << spacer.innerSpaces() << "postCode: " << type.postCode <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPrivacyKey &type)
{
    d.noquote().nospace();
    d << "TLPrivacyKey(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
    case TLValue::PrivacyKeyChatInvite:
    case TLValue::PrivacyKeyPhoneCall:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPrivacyRule &type)
{
    d.noquote().nospace();
    d << "TLPrivacyRule(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PrivacyValueAllowContacts:
    case TLValue::PrivacyValueAllowAll:
    case TLValue::PrivacyValueDisallowContacts:
    case TLValue::PrivacyValueDisallowAll:
        break;
    case TLValue::PrivacyValueAllowUsers:
    case TLValue::PrivacyValueDisallowUsers:
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLReceivedNotifyMessage &type)
{
    d.noquote().nospace();
    d << "TLReceivedNotifyMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ReceivedNotifyMessage:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLReportReason &type)
{
    d.noquote().nospace();
    d << "TLReportReason(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputReportReasonSpam:
    case TLValue::InputReportReasonViolence:
    case TLValue::InputReportReasonPornography:
        break;
    case TLValue::InputReportReasonOther:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLResPQ &type)
{
    d.noquote().nospace();
    d << "TLResPQ(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ResPQ:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "pq: " << type.pq <<"\n";
        d << spacer.innerSpaces() << "serverPublicKeyFingerprints: " << type.serverPublicKeyFingerprints <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLRichText &type)
{
    d.noquote().nospace();
    d << "TLRichText(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TextEmpty:
        break;
    case TLValue::TextPlain:
        d << spacer.innerSpaces() << "stringText: " << type.stringText <<"\n";
        break;
    case TLValue::TextBold:
    case TLValue::TextItalic:
    case TLValue::TextUnderline:
    case TLValue::TextStrike:
    case TLValue::TextFixed:
        d << spacer.innerSpaces() << "richText: " << type.richText <<"\n";
        break;
    case TLValue::TextUrl:
        d << spacer.innerSpaces() << "richText: " << type.richText <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "webpageId: " << type.webpageId <<"\n";
        break;
    case TLValue::TextEmail:
        d << spacer.innerSpaces() << "richText: " << type.richText <<"\n";
        d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        break;
    case TLValue::TextConcat:
        d << spacer.innerSpaces() << "texts: " << type.texts <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLRpcDropAnswer &type)
{
    d.noquote().nospace();
    d << "TLRpcDropAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::RpcAnswerUnknown:
    case TLValue::RpcAnswerDroppedRunning:
        break;
    case TLValue::RpcAnswerDropped:
        d << spacer.innerSpaces() << "msgId: " << type.msgId <<"\n";
        d << spacer.innerSpaces() << "seqNo: " << type.seqNo <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLRpcError &type)
{
    d.noquote().nospace();
    d << "TLRpcError(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::RpcError:
        d << spacer.innerSpaces() << "errorCode: " << type.errorCode <<"\n";
        d << spacer.innerSpaces() << "errorMessage: " << type.errorMessage <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSendMessageAction &type)
{
    d.noquote().nospace();
    d << "TLSendMessageAction(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SendMessageTypingAction:
    case TLValue::SendMessageCancelAction:
    case TLValue::SendMessageRecordVideoAction:
    case TLValue::SendMessageRecordAudioAction:
    case TLValue::SendMessageGeoLocationAction:
    case TLValue::SendMessageChooseContactAction:
    case TLValue::SendMessageGamePlayAction:
    case TLValue::SendMessageRecordRoundAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
    case TLValue::SendMessageUploadAudioAction:
    case TLValue::SendMessageUploadPhotoAction:
    case TLValue::SendMessageUploadDocumentAction:
    case TLValue::SendMessageUploadRoundAction:
        d << spacer.innerSpaces() << "progress: " << type.progress <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLServerDHInnerData &type)
{
    d.noquote().nospace();
    d << "TLServerDHInnerData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ServerDHInnerData:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "g: " << type.g <<"\n";
        d << spacer.innerSpaces() << "dhPrime: " << type.dhPrime <<"\n";
        d << spacer.innerSpaces() << "gA: " << type.gA <<"\n";
        d << spacer.innerSpaces() << "serverTime: " << type.serverTime <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLServerDHParams &type)
{
    d.noquote().nospace();
    d << "TLServerDHParams(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ServerDHParamsFail:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash: " << type.newNonceHash <<"\n";
        break;
    case TLValue::ServerDHParamsOk:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "encryptedAnswer: " << type.encryptedAnswer <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSetClientDHParamsAnswer &type)
{
    d.noquote().nospace();
    d << "TLSetClientDHParamsAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DhGenOk:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash1: " << type.newNonceHash1 <<"\n";
        break;
    case TLValue::DhGenRetry:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash2: " << type.newNonceHash2 <<"\n";
        break;
    case TLValue::DhGenFail:
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash3: " << type.newNonceHash3 <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLShippingOption &type)
{
    d.noquote().nospace();
    d << "TLShippingOption(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ShippingOption:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "prices: " << type.prices <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStickerPack &type)
{
    d.noquote().nospace();
    d << "TLStickerPack(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StickerPack:
        d << spacer.innerSpaces() << "emoticon: " << type.emoticon <<"\n";
        d << spacer.innerSpaces() << "documents: " << type.documents <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStorageFileType &type)
{
    d.noquote().nospace();
    d << "TLStorageFileType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StorageFileUnknown:
    case TLValue::StorageFilePartial:
    case TLValue::StorageFileJpeg:
    case TLValue::StorageFileGif:
    case TLValue::StorageFilePng:
    case TLValue::StorageFilePdf:
    case TLValue::StorageFileMp3:
    case TLValue::StorageFileMov:
    case TLValue::StorageFileMp4:
    case TLValue::StorageFileWebp:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLTopPeer &type)
{
    d.noquote().nospace();
    d << "TLTopPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TopPeer:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "rating: " << type.rating <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLTopPeerCategory &type)
{
    d.noquote().nospace();
    d << "TLTopPeerCategory(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TopPeerCategoryBotsPM:
    case TLValue::TopPeerCategoryBotsInline:
    case TLValue::TopPeerCategoryCorrespondents:
    case TLValue::TopPeerCategoryGroups:
    case TLValue::TopPeerCategoryChannels:
    case TLValue::TopPeerCategoryPhoneCalls:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLTopPeerCategoryPeers &type)
{
    d.noquote().nospace();
    d << "TLTopPeerCategoryPeers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TopPeerCategoryPeers:
        d << spacer.innerSpaces() << "category: " << type.category <<"\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "peers: " << type.peers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdatesState &type)
{
    d.noquote().nospace();
    d << "TLUpdatesState(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesState:
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "qts: " << type.qts <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUploadCdnFile &type)
{
    d.noquote().nospace();
    d << "TLUploadCdnFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadCdnFileReuploadNeeded:
        d << spacer.innerSpaces() << "requestToken: " << type.requestToken.toHex() <<"\n";
        break;
    case TLValue::UploadCdnFile:
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUploadFile &type)
{
    d.noquote().nospace();
    d << "TLUploadFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadFile:
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "mtime: " << type.mtime <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        break;
    case TLValue::UploadFileCdnRedirect:
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "fileToken: " << type.fileToken.toHex() <<"\n";
        d << spacer.innerSpaces() << "encryptionKey: " << type.encryptionKey.toHex() <<"\n";
        d << spacer.innerSpaces() << "encryptionIv: " << type.encryptionIv.toHex() <<"\n";
        d << spacer.innerSpaces() << "cdnFileHashes: " << type.cdnFileHashes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUploadWebFile &type)
{
    d.noquote().nospace();
    d << "TLUploadWebFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadWebFile:
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "fileType: " << type.fileType <<"\n";
        d << spacer.innerSpaces() << "mtime: " << type.mtime <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserProfilePhoto &type)
{
    d.noquote().nospace();
    d << "TLUserProfilePhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserProfilePhotoEmpty:
        break;
    case TLValue::UserProfilePhoto:
        d << spacer.innerSpaces() << "photoId: " << type.photoId <<"\n";
        d << spacer.innerSpaces() << "photoSmall: " << type.photoSmall <<"\n";
        d << spacer.innerSpaces() << "photoBig: " << type.photoBig <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserStatus &type)
{
    d.noquote().nospace();
    d << "TLUserStatus(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserStatusEmpty:
    case TLValue::UserStatusRecently:
    case TLValue::UserStatusLastWeek:
    case TLValue::UserStatusLastMonth:
        break;
    case TLValue::UserStatusOnline:
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        break;
    case TLValue::UserStatusOffline:
        d << spacer.innerSpaces() << "wasOnline: " << type.wasOnline <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLWallPaper &type)
{
    d.noquote().nospace();
    d << "TLWallPaper(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WallPaper:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "sizes: " << type.sizes <<"\n";
        d << spacer.innerSpaces() << "color: " << type.color <<"\n";
        break;
    case TLValue::WallPaperSolid:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "bgColor: " << type.bgColor <<"\n";
        d << spacer.innerSpaces() << "color: " << type.color <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountAuthorizations &type)
{
    d.noquote().nospace();
    d << "TLAccountAuthorizations(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountAuthorizations:
        d << spacer.innerSpaces() << "authorizations: " << type.authorizations <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthSentCode &type)
{
    d.noquote().nospace();
    d << "TLAuthSentCode(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthSentCode:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "phoneCodeHash: " << type.phoneCodeHash <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "nextType: " << type.nextType <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLCdnConfig &type)
{
    d.noquote().nospace();
    d << "TLCdnConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::CdnConfig:
        d << spacer.innerSpaces() << "publicKeys: " << type.publicKeys <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelAdminLogEventsFilter &type)
{
    d.noquote().nospace();
    d << "TLChannelAdminLogEventsFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminLogEventsFilter:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelAdminRights &type)
{
    d.noquote().nospace();
    d << "TLChannelAdminRights(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminRights:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelBannedRights &type)
{
    d.noquote().nospace();
    d << "TLChannelBannedRights(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelBannedRights:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "untilDate: " << type.untilDate <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelMessagesFilter &type)
{
    d.noquote().nospace();
    d << "TLChannelMessagesFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelMessagesFilterEmpty:
        break;
    case TLValue::ChannelMessagesFilter:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "ranges: " << type.ranges <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelParticipant &type)
{
    d.noquote().nospace();
    d << "TLChannelParticipant(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelParticipant:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantSelf:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantCreator:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::ChannelParticipantAdmin:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "promotedBy: " << type.promotedBy <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminRights: " << type.adminRights <<"\n";
        break;
    case TLValue::ChannelParticipantBanned:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "kickedBy: " << type.kickedBy <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bannedRights: " << type.bannedRights <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatPhoto &type)
{
    d.noquote().nospace();
    d << "TLChatPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatPhotoEmpty:
        break;
    case TLValue::ChatPhoto:
        d << spacer.innerSpaces() << "photoSmall: " << type.photoSmall <<"\n";
        d << spacer.innerSpaces() << "photoBig: " << type.photoBig <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactStatus &type)
{
    d.noquote().nospace();
    d << "TLContactStatus(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactStatus:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDcOption &type)
{
    d.noquote().nospace();
    d << "TLDcOption(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DcOption:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "ipAddress: " << type.ipAddress <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDocumentAttribute &type)
{
    d.noquote().nospace();
    d << "TLDocumentAttribute(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DocumentAttributeImageSize:
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::DocumentAttributeAnimated:
    case TLValue::DocumentAttributeHasStickers:
        break;
    case TLValue::DocumentAttributeSticker:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "alt: " << type.alt <<"\n";
        d << spacer.innerSpaces() << "stickerset: " << type.stickerset <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "maskCoords: " << type.maskCoords <<"\n";
        }
        break;
    case TLValue::DocumentAttributeVideo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::DocumentAttributeAudio:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "performer: " << type.performer <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "waveform: " << type.waveform.toHex() <<"\n";
        }
        break;
    case TLValue::DocumentAttributeFilename:
        d << spacer.innerSpaces() << "fileName: " << type.fileName <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDraftMessage &type)
{
    d.noquote().nospace();
    d << "TLDraftMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DraftMessageEmpty:
        break;
    case TLValue::DraftMessage:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "replyToMsgId: " << type.replyToMsgId <<"\n";
        }
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpConfigSimple &type)
{
    d.noquote().nospace();
    d << "TLHelpConfigSimple(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpConfigSimple:
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "ipPortList: " << type.ipPortList <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputChatPhoto &type)
{
    d.noquote().nospace();
    d << "TLInputChatPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        break;
    case TLValue::InputChatPhoto:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputGame &type)
{
    d.noquote().nospace();
    d << "TLInputGame(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputGameID:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputGameShortName:
        d << spacer.innerSpaces() << "botId: " << type.botId <<"\n";
        d << spacer.innerSpaces() << "shortName: " << type.shortName <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputNotifyPeer &type)
{
    d.noquote().nospace();
    d << "TLInputNotifyPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputNotifyPeer:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyAll:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPaymentCredentials &type)
{
    d.noquote().nospace();
    d << "TLInputPaymentCredentials(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPaymentCredentialsSaved:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "tmpPassword: " << type.tmpPassword.toHex() <<"\n";
        break;
    case TLValue::InputPaymentCredentials:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "data: " << type.data <<"\n";
        break;
    case TLValue::InputPaymentCredentialsApplePay:
        d << spacer.innerSpaces() << "paymentData: " << type.paymentData <<"\n";
        break;
    case TLValue::InputPaymentCredentialsAndroidPay:
        d << spacer.innerSpaces() << "paymentToken: " << type.paymentToken <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeerNotifySettings &type)
{
    d.noquote().nospace();
    d << "TLInputPeerNotifySettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerNotifySettings:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "muteUntil: " << type.muteUntil <<"\n";
        d << spacer.innerSpaces() << "sound: " << type.sound <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPrivacyRule &type)
{
    d.noquote().nospace();
    d << "TLInputPrivacyRule(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
    case TLValue::InputPrivacyValueAllowAll:
    case TLValue::InputPrivacyValueDisallowContacts:
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
    case TLValue::InputPrivacyValueDisallowUsers:
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputStickerSetItem &type)
{
    d.noquote().nospace();
    d << "TLInputStickerSetItem(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputStickerSetItem:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        d << spacer.innerSpaces() << "emoji: " << type.emoji <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "maskCoords: " << type.maskCoords <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputWebDocument &type)
{
    d.noquote().nospace();
    d << "TLInputWebDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputWebDocument:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInvoice &type)
{
    d.noquote().nospace();
    d << "TLInvoice(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Invoice:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "prices: " << type.prices <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLKeyboardButton &type)
{
    d.noquote().nospace();
    d << "TLKeyboardButton(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::KeyboardButton:
    case TLValue::KeyboardButtonRequestPhone:
    case TLValue::KeyboardButtonRequestGeoLocation:
    case TLValue::KeyboardButtonGame:
    case TLValue::KeyboardButtonBuy:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::KeyboardButtonUrl:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    case TLValue::KeyboardButtonCallback:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "data: " << type.data.toHex() <<"\n";
        break;
    case TLValue::KeyboardButtonSwitchInline:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "query: " << type.query <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLKeyboardButtonRow &type)
{
    d.noquote().nospace();
    d << "TLKeyboardButtonRow(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::KeyboardButtonRow:
        d << spacer.innerSpaces() << "buttons: " << type.buttons <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLLangPackDifference &type)
{
    d.noquote().nospace();
    d << "TLLangPackDifference(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LangPackDifference:
        d << spacer.innerSpaces() << "langCode: " << type.langCode <<"\n";
        d << spacer.innerSpaces() << "fromVersion: " << type.fromVersion <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        d << spacer.innerSpaces() << "strings: " << type.strings <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesBotCallbackAnswer &type)
{
    d.noquote().nospace();
    d << "TLMessagesBotCallbackAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesBotCallbackAnswer:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        d << spacer.innerSpaces() << "cacheTime: " << type.cacheTime <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesFilter &type)
{
    d.noquote().nospace();
    d << "TLMessagesFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputMessagesFilterEmpty:
    case TLValue::InputMessagesFilterPhotos:
    case TLValue::InputMessagesFilterVideo:
    case TLValue::InputMessagesFilterPhotoVideo:
    case TLValue::InputMessagesFilterDocument:
    case TLValue::InputMessagesFilterUrl:
    case TLValue::InputMessagesFilterGif:
    case TLValue::InputMessagesFilterVoice:
    case TLValue::InputMessagesFilterMusic:
    case TLValue::InputMessagesFilterChatPhotos:
    case TLValue::InputMessagesFilterRoundVoice:
    case TLValue::InputMessagesFilterRoundVideo:
    case TLValue::InputMessagesFilterMyMentions:
    case TLValue::InputMessagesFilterGeo:
    case TLValue::InputMessagesFilterContacts:
        break;
    case TLValue::InputMessagesFilterPhoneCalls:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesMessageEditData &type)
{
    d.noquote().nospace();
    d << "TLMessagesMessageEditData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesMessageEditData:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLNotifyPeer &type)
{
    d.noquote().nospace();
    d << "TLNotifyPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NotifyPeer:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyAll:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentRequestedInfo &type)
{
    d.noquote().nospace();
    d << "TLPaymentRequestedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentRequestedInfo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "phone: " << type.phone <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "shippingAddress: " << type.shippingAddress <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentsSavedInfo &type)
{
    d.noquote().nospace();
    d << "TLPaymentsSavedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsSavedInfo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "savedInfo: " << type.savedInfo <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentsValidatedRequestedInfo &type)
{
    d.noquote().nospace();
    d << "TLPaymentsValidatedRequestedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsValidatedRequestedInfo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "shippingOptions: " << type.shippingOptions <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeerNotifySettings &type)
{
    d.noquote().nospace();
    d << "TLPeerNotifySettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerNotifySettingsEmpty:
        break;
    case TLValue::PeerNotifySettings:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "muteUntil: " << type.muteUntil <<"\n";
        d << spacer.innerSpaces() << "sound: " << type.sound <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeerSettings &type)
{
    d.noquote().nospace();
    d << "TLPeerSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerSettings:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneCallProtocol &type)
{
    d.noquote().nospace();
    d << "TLPhoneCallProtocol(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneCallProtocol:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "minLayer: " << type.minLayer <<"\n";
        d << spacer.innerSpaces() << "maxLayer: " << type.maxLayer <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoto &type)
{
    d.noquote().nospace();
    d << "TLPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotoEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Photo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "sizes: " << type.sizes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLReplyMarkup &type)
{
    d.noquote().nospace();
    d << "TLReplyMarkup(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ReplyKeyboardHide:
    case TLValue::ReplyKeyboardForceReply:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    case TLValue::ReplyKeyboardMarkup:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "rows: " << type.rows <<"\n";
        break;
    case TLValue::ReplyInlineMarkup:
        d << spacer.innerSpaces() << "rows: " << type.rows <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStickerSet &type)
{
    d.noquote().nospace();
    d << "TLStickerSet(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StickerSet:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "shortName: " << type.shortName <<"\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUser &type)
{
    d.noquote().nospace();
    d << "TLUser(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::User:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "username: " << type.username <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "phone: " << type.phone <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        }
        if (type.flags & 1 << 14) {
            d << spacer.innerSpaces() << "botInfoVersion: " << type.botInfoVersion <<"\n";
        }
        if (type.flags & 1 << 18) {
            d << spacer.innerSpaces() << "restrictionReason: " << type.restrictionReason <<"\n";
        }
        if (type.flags & 1 << 19) {
            d << spacer.innerSpaces() << "botInlinePlaceholder: " << type.botInlinePlaceholder <<"\n";
        }
        if (type.flags & 1 << 22) {
            d << spacer.innerSpaces() << "langCode: " << type.langCode <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLWebDocument &type)
{
    d.noquote().nospace();
    d << "TLWebDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WebDocument:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPrivacyRules &type)
{
    d.noquote().nospace();
    d << "TLAccountPrivacyRules(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPrivacyRules:
        d << spacer.innerSpaces() << "rules: " << type.rules <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthAuthorization &type)
{
    d.noquote().nospace();
    d << "TLAuthAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthAuthorization:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "tmpSessions: " << type.tmpSessions <<"\n";
        }
        d << spacer.innerSpaces() << "user: " << type.user <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBotInlineMessage &type)
{
    d.noquote().nospace();
    d << "TLBotInlineMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInlineMessageMediaAuto:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageText:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageMediaGeo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageMediaVenue:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageMediaContact:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "phoneNumber: " << type.phoneNumber <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelsChannelParticipant &type)
{
    d.noquote().nospace();
    d << "TLChannelsChannelParticipant(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsChannelParticipant:
        d << spacer.innerSpaces() << "participant: " << type.participant <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelsChannelParticipants &type)
{
    d.noquote().nospace();
    d << "TLChannelsChannelParticipants(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsChannelParticipants:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::ChannelsChannelParticipantsNotModified:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChat &type)
{
    d.noquote().nospace();
    d << "TLChat(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Chat:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "participantsCount: " << type.participantsCount <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "migratedTo: " << type.migratedTo <<"\n";
        }
        break;
    case TLValue::ChatForbidden:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    case TLValue::Channel:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 13) {
            d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        }
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "username: " << type.username <<"\n";
        }
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        if (type.flags & 1 << 9) {
            d << spacer.innerSpaces() << "restrictionReason: " << type.restrictionReason <<"\n";
        }
        if (type.flags & 1 << 14) {
            d << spacer.innerSpaces() << "adminRights: " << type.adminRights <<"\n";
        }
        if (type.flags & 1 << 15) {
            d << spacer.innerSpaces() << "bannedRights: " << type.bannedRights <<"\n";
        }
        break;
    case TLValue::ChannelForbidden:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        if (type.flags & 1 << 16) {
            d << spacer.innerSpaces() << "untilDate: " << type.untilDate <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatFull &type)
{
    d.noquote().nospace();
    d << "TLChatFull(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatFull:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        d << spacer.innerSpaces() << "chatPhoto: " << type.chatPhoto <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        d << spacer.innerSpaces() << "exportedInvite: " << type.exportedInvite <<"\n";
        d << spacer.innerSpaces() << "botInfo: " << type.botInfo <<"\n";
        break;
    case TLValue::ChannelFull:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "about: " << type.about <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "participantsCount: " << type.participantsCount <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "adminsCount: " << type.adminsCount <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "kickedCount: " << type.kickedCount <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "bannedCount: " << type.bannedCount <<"\n";
        }
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "readOutboxMaxId: " << type.readOutboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "chatPhoto: " << type.chatPhoto <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        d << spacer.innerSpaces() << "exportedInvite: " << type.exportedInvite <<"\n";
        d << spacer.innerSpaces() << "botInfo: " << type.botInfo <<"\n";
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "migratedFromChatId: " << type.migratedFromChatId <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "migratedFromMaxId: " << type.migratedFromMaxId <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "pinnedMsgId: " << type.pinnedMsgId <<"\n";
        }
        if (type.flags & 1 << 8) {
            d << spacer.innerSpaces() << "stickerset: " << type.stickerset <<"\n";
        }
        if (type.flags & 1 << 9) {
            d << spacer.innerSpaces() << "availableMinId: " << type.availableMinId <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatInvite &type)
{
    d.noquote().nospace();
    d << "TLChatInvite(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatInviteAlready:
        d << spacer.innerSpaces() << "chat: " << type.chat <<"\n";
        break;
    case TLValue::ChatInvite:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "participantsCount: " << type.participantsCount <<"\n";
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLConfig &type)
{
    d.noquote().nospace();
    d << "TLConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Config:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        d << spacer.innerSpaces() << "testMode: " << type.testMode <<"\n";
        d << spacer.innerSpaces() << "thisDc: " << type.thisDc <<"\n";
        d << spacer.innerSpaces() << "dcOptions: " << type.dcOptions <<"\n";
        d << spacer.innerSpaces() << "chatSizeMax: " << type.chatSizeMax <<"\n";
        d << spacer.innerSpaces() << "megagroupSizeMax: " << type.megagroupSizeMax <<"\n";
        d << spacer.innerSpaces() << "forwardedCountMax: " << type.forwardedCountMax <<"\n";
        d << spacer.innerSpaces() << "onlineUpdatePeriodMs: " << type.onlineUpdatePeriodMs <<"\n";
        d << spacer.innerSpaces() << "offlineBlurTimeoutMs: " << type.offlineBlurTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "offlineIdleTimeoutMs: " << type.offlineIdleTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "onlineCloudTimeoutMs: " << type.onlineCloudTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "notifyCloudDelayMs: " << type.notifyCloudDelayMs <<"\n";
        d << spacer.innerSpaces() << "notifyDefaultDelayMs: " << type.notifyDefaultDelayMs <<"\n";
        d << spacer.innerSpaces() << "chatBigSize: " << type.chatBigSize <<"\n";
        d << spacer.innerSpaces() << "pushChatPeriodMs: " << type.pushChatPeriodMs <<"\n";
        d << spacer.innerSpaces() << "pushChatLimit: " << type.pushChatLimit <<"\n";
        d << spacer.innerSpaces() << "savedGifsLimit: " << type.savedGifsLimit <<"\n";
        d << spacer.innerSpaces() << "editTimeLimit: " << type.editTimeLimit <<"\n";
        d << spacer.innerSpaces() << "ratingEDecay: " << type.ratingEDecay <<"\n";
        d << spacer.innerSpaces() << "stickersRecentLimit: " << type.stickersRecentLimit <<"\n";
        d << spacer.innerSpaces() << "stickersFavedLimit: " << type.stickersFavedLimit <<"\n";
        d << spacer.innerSpaces() << "channelsReadMediaPeriod: " << type.channelsReadMediaPeriod <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "tmpSessions: " << type.tmpSessions <<"\n";
        }
        d << spacer.innerSpaces() << "pinnedDialogsCountMax: " << type.pinnedDialogsCountMax <<"\n";
        d << spacer.innerSpaces() << "callReceiveTimeoutMs: " << type.callReceiveTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "callRingTimeoutMs: " << type.callRingTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "callConnectTimeoutMs: " << type.callConnectTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "callPacketTimeoutMs: " << type.callPacketTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "meUrlPrefix: " << type.meUrlPrefix <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "suggestedLangCode: " << type.suggestedLangCode <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "langPackVersion: " << type.langPackVersion <<"\n";
        }
        d << spacer.innerSpaces() << "disabledFeatures: " << type.disabledFeatures <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsBlocked &type)
{
    d.noquote().nospace();
    d << "TLContactsBlocked(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsBlocked:
        d << spacer.innerSpaces() << "blocked: " << type.blocked <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::ContactsBlockedSlice:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "blocked: " << type.blocked <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsContacts &type)
{
    d.noquote().nospace();
    d << "TLContactsContacts(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        d << spacer.innerSpaces() << "contacts: " << type.contacts <<"\n";
        d << spacer.innerSpaces() << "savedCount: " << type.savedCount <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsFound &type)
{
    d.noquote().nospace();
    d << "TLContactsFound(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsFound:
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsImportedContacts &type)
{
    d.noquote().nospace();
    d << "TLContactsImportedContacts(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsImportedContacts:
        d << spacer.innerSpaces() << "imported: " << type.imported <<"\n";
        d << spacer.innerSpaces() << "popularInvites: " << type.popularInvites <<"\n";
        d << spacer.innerSpaces() << "retryContacts: " << type.retryContacts <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsLink &type)
{
    d.noquote().nospace();
    d << "TLContactsLink(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsLink:
        d << spacer.innerSpaces() << "myLink: " << type.myLink <<"\n";
        d << spacer.innerSpaces() << "foreignLink: " << type.foreignLink <<"\n";
        d << spacer.innerSpaces() << "user: " << type.user <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsResolvedPeer &type)
{
    d.noquote().nospace();
    d << "TLContactsResolvedPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsResolvedPeer:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsTopPeers &type)
{
    d.noquote().nospace();
    d << "TLContactsTopPeers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsTopPeersNotModified:
        break;
    case TLValue::ContactsTopPeers:
        d << spacer.innerSpaces() << "categories: " << type.categories <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDialog &type)
{
    d.noquote().nospace();
    d << "TLDialog(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Dialog:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "topMessage: " << type.topMessage <<"\n";
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "readOutboxMaxId: " << type.readOutboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "unreadMentionsCount: " << type.unreadMentionsCount <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "draft: " << type.draft <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDocument &type)
{
    d.noquote().nospace();
    d << "TLDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DocumentEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Document:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFoundGif &type)
{
    d.noquote().nospace();
    d << "TLFoundGif(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FoundGif:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "thumbUrl: " << type.thumbUrl <<"\n";
        d << spacer.innerSpaces() << "contentUrl: " << type.contentUrl <<"\n";
        d << spacer.innerSpaces() << "contentType: " << type.contentType <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::FoundGifCached:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLGame &type)
{
    d.noquote().nospace();
    d << "TLGame(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Game:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "shortName: " << type.shortName <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpSupport &type)
{
    d.noquote().nospace();
    d << "TLHelpSupport(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpSupport:
        d << spacer.innerSpaces() << "phoneNumber: " << type.phoneNumber <<"\n";
        d << spacer.innerSpaces() << "user: " << type.user <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputBotInlineMessage &type)
{
    d.noquote().nospace();
    d << "TLInputBotInlineMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineMessageMediaAuto:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageText:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageMediaGeo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageMediaVenue:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageMediaContact:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "phoneNumber: " << type.phoneNumber <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageGame:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputBotInlineResult &type)
{
    d.noquote().nospace();
    d << "TLInputBotInlineResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineResult:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "thumbUrl: " << type.thumbUrl <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "contentUrl: " << type.contentUrl <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "contentType: " << type.contentType <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        }
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::InputBotInlineResultPhoto:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::InputBotInlineResultDocument:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        }
        d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::InputBotInlineResultGame:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "shortName: " << type.shortName <<"\n";
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputMedia &type)
{
    d.noquote().nospace();
    d << "TLInputMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaPhoto:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "inputPhotoId: " << type.inputPhotoId <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaGeoPoint:
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        break;
    case TLValue::InputMediaContact:
        d << spacer.innerSpaces() << "phoneNumber: " << type.phoneNumber <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        break;
    case TLValue::InputMediaUploadedDocument:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        }
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaDocument:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "inputDocumentId: " << type.inputDocumentId <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaVenue:
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        d << spacer.innerSpaces() << "venueType: " << type.venueType <<"\n";
        break;
    case TLValue::InputMediaGifExternal:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        break;
    case TLValue::InputMediaPhotoExternal:
    case TLValue::InputMediaDocumentExternal:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaGame:
        d << spacer.innerSpaces() << "inputGameId: " << type.inputGameId <<"\n";
        break;
    case TLValue::InputMediaInvoice:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        d << spacer.innerSpaces() << "invoice: " << type.invoice <<"\n";
        d << spacer.innerSpaces() << "payload: " << type.payload.toHex() <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "startParam: " << type.startParam <<"\n";
        break;
    case TLValue::InputMediaGeoLive:
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageAction &type)
{
    d.noquote().nospace();
    d << "TLMessageAction(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageActionEmpty:
    case TLValue::MessageActionChatDeletePhoto:
    case TLValue::MessageActionPinMessage:
    case TLValue::MessageActionHistoryClear:
    case TLValue::MessageActionScreenshotTaken:
        break;
    case TLValue::MessageActionChatCreate:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessageActionChatEditTitle:
    case TLValue::MessageActionChannelCreate:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    case TLValue::MessageActionChatEditPhoto:
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        break;
    case TLValue::MessageActionChatAddUser:
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessageActionChatDeleteUser:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::MessageActionChatJoinedByLink:
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        break;
    case TLValue::MessageActionChatMigrateTo:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::MessageActionChannelMigrateFrom:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::MessageActionGameScore:
        d << spacer.innerSpaces() << "gameId: " << type.gameId <<"\n";
        d << spacer.innerSpaces() << "score: " << type.score <<"\n";
        break;
    case TLValue::MessageActionPaymentSentMe:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "totalAmount: " << type.totalAmount <<"\n";
        d << spacer.innerSpaces() << "payload: " << type.payload.toHex() <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "info: " << type.info <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "shippingOptionId: " << type.shippingOptionId <<"\n";
        }
        d << spacer.innerSpaces() << "charge: " << type.charge <<"\n";
        break;
    case TLValue::MessageActionPaymentSent:
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "totalAmount: " << type.totalAmount <<"\n";
        break;
    case TLValue::MessageActionPhoneCall:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "callId: " << type.callId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "reason: " << type.reason <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        }
        break;
    case TLValue::MessageActionCustomAction:
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesAllStickers &type)
{
    d.noquote().nospace();
    d << "TLMessagesAllStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesAllStickersNotModified:
        break;
    case TLValue::MessagesAllStickers:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "sets: " << type.sets <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesChatFull &type)
{
    d.noquote().nospace();
    d << "TLMessagesChatFull(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesChatFull:
        d << spacer.innerSpaces() << "fullChat: " << type.fullChat <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesChats &type)
{
    d.noquote().nospace();
    d << "TLMessagesChats(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesChats:
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        break;
    case TLValue::MessagesChatsSlice:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesFavedStickers &type)
{
    d.noquote().nospace();
    d << "TLMessagesFavedStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFavedStickersNotModified:
        break;
    case TLValue::MessagesFavedStickers:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "packs: " << type.packs <<"\n";
        d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesFoundGifs &type)
{
    d.noquote().nospace();
    d << "TLMessagesFoundGifs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFoundGifs:
        d << spacer.innerSpaces() << "nextOffset: " << type.nextOffset <<"\n";
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesHighScores &type)
{
    d.noquote().nospace();
    d << "TLMessagesHighScores(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesHighScores:
        d << spacer.innerSpaces() << "scores: " << type.scores <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesRecentStickers &type)
{
    d.noquote().nospace();
    d << "TLMessagesRecentStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesRecentStickersNotModified:
        break;
    case TLValue::MessagesRecentStickers:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesSavedGifs &type)
{
    d.noquote().nospace();
    d << "TLMessagesSavedGifs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesSavedGifsNotModified:
        break;
    case TLValue::MessagesSavedGifs:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "gifs: " << type.gifs <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStickerSet &type)
{
    d.noquote().nospace();
    d << "TLMessagesStickerSet(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesStickerSet:
        d << spacer.innerSpaces() << "set: " << type.set <<"\n";
        d << spacer.innerSpaces() << "packs: " << type.packs <<"\n";
        d << spacer.innerSpaces() << "documents: " << type.documents <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStickers &type)
{
    d.noquote().nospace();
    d << "TLMessagesStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesStickersNotModified:
        break;
    case TLValue::MessagesStickers:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageBlock &type)
{
    d.noquote().nospace();
    d << "TLPageBlock(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageBlockUnsupported:
    case TLValue::PageBlockDivider:
        break;
    case TLValue::PageBlockTitle:
    case TLValue::PageBlockSubtitle:
    case TLValue::PageBlockHeader:
    case TLValue::PageBlockSubheader:
    case TLValue::PageBlockParagraph:
    case TLValue::PageBlockFooter:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::PageBlockAuthorDate:
        d << spacer.innerSpaces() << "richTextAuthor: " << type.richTextAuthor <<"\n";
        d << spacer.innerSpaces() << "publishedDate: " << type.publishedDate <<"\n";
        break;
    case TLValue::PageBlockPreformatted:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "language: " << type.language <<"\n";
        break;
    case TLValue::PageBlockAnchor:
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        break;
    case TLValue::PageBlockList:
        d << spacer.innerSpaces() << "ordered: " << type.ordered <<"\n";
        d << spacer.innerSpaces() << "richTextItemsVector: " << type.richTextItemsVector <<"\n";
        break;
    case TLValue::PageBlockBlockquote:
    case TLValue::PageBlockPullquote:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::PageBlockPhoto:
        d << spacer.innerSpaces() << "photoId: " << type.photoId <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::PageBlockVideo:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "videoId: " << type.videoId <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::PageBlockCover:
        d << spacer.innerSpaces() << "cover: " << type.cover <<"\n";
        break;
    case TLValue::PageBlockEmbed:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "html: " << type.html <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "posterPhotoId: " << type.posterPhotoId <<"\n";
        }
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::PageBlockEmbedPost:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "webpageId: " << type.webpageId <<"\n";
        d << spacer.innerSpaces() << "authorPhotoId: " << type.authorPhotoId <<"\n";
        d << spacer.innerSpaces() << "stringAuthor: " << type.stringAuthor <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "blocks: " << type.blocks <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::PageBlockCollage:
    case TLValue::PageBlockSlideshow:
        d << spacer.innerSpaces() << "pageBlockItemsVector: " << type.pageBlockItemsVector <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::PageBlockChannel:
        d << spacer.innerSpaces() << "channel: " << type.channel <<"\n";
        break;
    case TLValue::PageBlockAudio:
        d << spacer.innerSpaces() << "audioId: " << type.audioId <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentsPaymentForm &type)
{
    d.noquote().nospace();
    d << "TLPaymentsPaymentForm(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsPaymentForm:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "botId: " << type.botId <<"\n";
        d << spacer.innerSpaces() << "invoice: " << type.invoice <<"\n";
        d << spacer.innerSpaces() << "providerId: " << type.providerId <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "nativeProvider: " << type.nativeProvider <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "nativeParams: " << type.nativeParams <<"\n";
        }
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "savedInfo: " << type.savedInfo <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "savedCredentials: " << type.savedCredentials <<"\n";
        }
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentsPaymentReceipt &type)
{
    d.noquote().nospace();
    d << "TLPaymentsPaymentReceipt(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsPaymentReceipt:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "botId: " << type.botId <<"\n";
        d << spacer.innerSpaces() << "invoice: " << type.invoice <<"\n";
        d << spacer.innerSpaces() << "providerId: " << type.providerId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "info: " << type.info <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "shipping: " << type.shipping <<"\n";
        }
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "totalAmount: " << type.totalAmount <<"\n";
        d << spacer.innerSpaces() << "credentialsTitle: " << type.credentialsTitle <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneCall &type)
{
    d.noquote().nospace();
    d << "TLPhoneCall(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneCallEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::PhoneCallWaiting:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "receiveDate: " << type.receiveDate <<"\n";
        }
        break;
    case TLValue::PhoneCallRequested:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gAHash: " << type.gAHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        break;
    case TLValue::PhoneCallAccepted:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gB: " << type.gB.toHex() <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        break;
    case TLValue::PhoneCall:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gAOrB: " << type.gAOrB.toHex() <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        d << spacer.innerSpaces() << "connection: " << type.connection <<"\n";
        d << spacer.innerSpaces() << "alternativeConnections: " << type.alternativeConnections <<"\n";
        d << spacer.innerSpaces() << "startDate: " << type.startDate <<"\n";
        break;
    case TLValue::PhoneCallDiscarded:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "reason: " << type.reason <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhonePhoneCall &type)
{
    d.noquote().nospace();
    d << "TLPhonePhoneCall(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhonePhoneCall:
        d << spacer.innerSpaces() << "phoneCall: " << type.phoneCall <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhotosPhoto &type)
{
    d.noquote().nospace();
    d << "TLPhotosPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotosPhoto:
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhotosPhotos &type)
{
    d.noquote().nospace();
    d << "TLPhotosPhotos(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotosPhotos:
        d << spacer.innerSpaces() << "photos: " << type.photos <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::PhotosPhotosSlice:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "photos: " << type.photos <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStickerSetCovered &type)
{
    d.noquote().nospace();
    d << "TLStickerSetCovered(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StickerSetCovered:
        d << spacer.innerSpaces() << "set: " << type.set <<"\n";
        d << spacer.innerSpaces() << "cover: " << type.cover <<"\n";
        break;
    case TLValue::StickerSetMultiCovered:
        d << spacer.innerSpaces() << "set: " << type.set <<"\n";
        d << spacer.innerSpaces() << "covers: " << type.covers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserFull &type)
{
    d.noquote().nospace();
    d << "TLUserFull(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserFull:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "user: " << type.user <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "about: " << type.about <<"\n";
        }
        d << spacer.innerSpaces() << "link: " << type.link <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "profilePhoto: " << type.profilePhoto <<"\n";
        }
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "botInfo: " << type.botInfo <<"\n";
        }
        d << spacer.innerSpaces() << "commonChatsCount: " << type.commonChatsCount <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBotInlineResult &type)
{
    d.noquote().nospace();
    d << "TLBotInlineResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInlineResult:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "thumbUrl: " << type.thumbUrl <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "contentUrl: " << type.contentUrl <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "contentType: " << type.contentType <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        }
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::BotInlineMediaResult:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        }
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesArchivedStickers &type)
{
    d.noquote().nospace();
    d << "TLMessagesArchivedStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesArchivedStickers:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "sets: " << type.sets <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesBotResults &type)
{
    d.noquote().nospace();
    d << "TLMessagesBotResults(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesBotResults:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "nextOffset: " << type.nextOffset <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "switchPm: " << type.switchPm <<"\n";
        }
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        d << spacer.innerSpaces() << "cacheTime: " << type.cacheTime <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesFeaturedStickers &type)
{
    d.noquote().nospace();
    d << "TLMessagesFeaturedStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFeaturedStickersNotModified:
        break;
    case TLValue::MessagesFeaturedStickers:
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "sets: " << type.sets <<"\n";
        d << spacer.innerSpaces() << "unread: " << type.unread <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStickerSetInstallResult &type)
{
    d.noquote().nospace();
    d << "TLMessagesStickerSetInstallResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesStickerSetInstallResultSuccess:
        break;
    case TLValue::MessagesStickerSetInstallResultArchive:
        d << spacer.innerSpaces() << "sets: " << type.sets <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPage &type)
{
    d.noquote().nospace();
    d << "TLPage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PagePart:
    case TLValue::PageFull:
        d << spacer.innerSpaces() << "blocks: " << type.blocks <<"\n";
        d << spacer.innerSpaces() << "photos: " << type.photos <<"\n";
        d << spacer.innerSpaces() << "documents: " << type.documents <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLRecentMeUrl &type)
{
    d.noquote().nospace();
    d << "TLRecentMeUrl(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::RecentMeUrlUnknown:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    case TLValue::RecentMeUrlUser:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::RecentMeUrlChat:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::RecentMeUrlChatInvite:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "chatInvite: " << type.chatInvite <<"\n";
        break;
    case TLValue::RecentMeUrlStickerSet:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "set: " << type.set <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLWebPage &type)
{
    d.noquote().nospace();
    d << "TLWebPage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WebPageEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::WebPagePending:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::WebPage:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "displayUrl: " << type.displayUrl <<"\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "siteName: " << type.siteName <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "embedUrl: " << type.embedUrl <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "embedType: " << type.embedType <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "embedWidth: " << type.embedWidth <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "embedHeight: " << type.embedHeight <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        }
        if (type.flags & 1 << 8) {
            d << spacer.innerSpaces() << "author: " << type.author <<"\n";
        }
        if (type.flags & 1 << 9) {
            d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        }
        if (type.flags & 1 << 10) {
            d << spacer.innerSpaces() << "cachedPage: " << type.cachedPage <<"\n";
        }
        break;
    case TLValue::WebPageNotModified:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpRecentMeUrls &type)
{
    d.noquote().nospace();
    d << "TLHelpRecentMeUrls(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpRecentMeUrls:
        d << spacer.innerSpaces() << "urls: " << type.urls <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageMedia &type)
{
    d.noquote().nospace();
    d << "TLMessageMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaUnsupported:
        break;
    case TLValue::MessageMediaPhoto:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::MessageMediaGeo:
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        break;
    case TLValue::MessageMediaContact:
        d << spacer.innerSpaces() << "phoneNumber: " << type.phoneNumber <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::MessageMediaDocument:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::MessageMediaWebPage:
        d << spacer.innerSpaces() << "webpage: " << type.webpage <<"\n";
        break;
    case TLValue::MessageMediaVenue:
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        d << spacer.innerSpaces() << "venueType: " << type.venueType <<"\n";
        break;
    case TLValue::MessageMediaGame:
        d << spacer.innerSpaces() << "game: " << type.game <<"\n";
        break;
    case TLValue::MessageMediaInvoice:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "webDocumentPhoto: " << type.webDocumentPhoto <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "receiptMsgId: " << type.receiptMsgId <<"\n";
        }
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "totalAmount: " << type.totalAmount <<"\n";
        d << spacer.innerSpaces() << "startParam: " << type.startParam <<"\n";
        break;
    case TLValue::MessageMediaGeoLive:
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessage &type)
{
    d.noquote().nospace();
    d << "TLMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Message:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 8) {
            d << spacer.innerSpaces() << "fromId: " << type.fromId <<"\n";
        }
        d << spacer.innerSpaces() << "toId: " << type.toId <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "fwdFrom: " << type.fwdFrom <<"\n";
        }
        if (type.flags & 1 << 11) {
            d << spacer.innerSpaces() << "viaBotId: " << type.viaBotId <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "replyToMsgId: " << type.replyToMsgId <<"\n";
        }
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 9) {
            d << spacer.innerSpaces() << "media: " << type.media <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 10) {
            d << spacer.innerSpaces() << "views: " << type.views <<"\n";
        }
        if (type.flags & 1 << 15) {
            d << spacer.innerSpaces() << "editDate: " << type.editDate <<"\n";
        }
        if (type.flags & 1 << 16) {
            d << spacer.innerSpaces() << "postAuthor: " << type.postAuthor <<"\n";
        }
        break;
    case TLValue::MessageService:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 8) {
            d << spacer.innerSpaces() << "fromId: " << type.fromId <<"\n";
        }
        d << spacer.innerSpaces() << "toId: " << type.toId <<"\n";
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "replyToMsgId: " << type.replyToMsgId <<"\n";
        }
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "action: " << type.action <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesDialogs &type)
{
    d.noquote().nospace();
    d << "TLMessagesDialogs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesDialogs:
        d << spacer.innerSpaces() << "dialogs: " << type.dialogs <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesDialogsSlice:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "dialogs: " << type.dialogs <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesMessages &type)
{
    d.noquote().nospace();
    d << "TLMessagesMessages(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesMessages:
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesMessagesSlice:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesChannelMessages:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesMessagesNotModified:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesPeerDialogs &type)
{
    d.noquote().nospace();
    d << "TLMessagesPeerDialogs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesPeerDialogs:
        d << spacer.innerSpaces() << "dialogs: " << type.dialogs <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "state: " << type.state <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdate &type)
{
    d.noquote().nospace();
    d << "TLUpdate(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
    case TLValue::UpdateEditChannelMessage:
    case TLValue::UpdateEditMessage:
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateMessageID:
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        break;
    case TLValue::UpdateDeleteMessages:
    case TLValue::UpdateReadMessagesContents:
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateUserTyping:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "action: " << type.action <<"\n";
        break;
    case TLValue::UpdateChatUserTyping:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "action: " << type.action <<"\n";
        break;
    case TLValue::UpdateChatParticipants:
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        break;
    case TLValue::UpdateUserStatus:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        break;
    case TLValue::UpdateUserName:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "username: " << type.username <<"\n";
        break;
    case TLValue::UpdateUserPhoto:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "previous: " << type.previous <<"\n";
        break;
    case TLValue::UpdateContactRegistered:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdateContactLink:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "myLink: " << type.myLink <<"\n";
        d << spacer.innerSpaces() << "foreignLink: " << type.foreignLink <<"\n";
        break;
    case TLValue::UpdateNewEncryptedMessage:
        d << spacer.innerSpaces() << "encryptedMessage: " << type.encryptedMessage <<"\n";
        d << spacer.innerSpaces() << "qts: " << type.qts <<"\n";
        break;
    case TLValue::UpdateEncryptedChatTyping:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::UpdateEncryption:
        d << spacer.innerSpaces() << "chat: " << type.chat <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdateEncryptedMessagesRead:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "maxDate: " << type.maxDate <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdateChatParticipantAdd:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateChatParticipantDelete:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateDcOptions:
        d << spacer.innerSpaces() << "dcOptions: " << type.dcOptions <<"\n";
        break;
    case TLValue::UpdateUserBlocked:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "blocked: " << type.blocked <<"\n";
        break;
    case TLValue::UpdateNotifySettings:
        d << spacer.innerSpaces() << "notifyPeer: " << type.notifyPeer <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        break;
    case TLValue::UpdateServiceNotification:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "inboxDate: " << type.inboxDate <<"\n";
        }
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "stringMessage: " << type.stringMessage <<"\n";
        d << spacer.innerSpaces() << "media: " << type.media <<"\n";
        d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        break;
    case TLValue::UpdatePrivacy:
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        d << spacer.innerSpaces() << "rules: " << type.rules <<"\n";
        break;
    case TLValue::UpdateUserPhone:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "phone: " << type.phone <<"\n";
        break;
    case TLValue::UpdateReadHistoryInbox:
    case TLValue::UpdateReadHistoryOutbox:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateWebPage:
        d << spacer.innerSpaces() << "webpage: " << type.webpage <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateChannelTooLong:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        }
        break;
    case TLValue::UpdateChannel:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::UpdateReadChannelInbox:
    case TLValue::UpdateReadChannelOutbox:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        break;
    case TLValue::UpdateDeleteChannelMessages:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateChannelMessageViews:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        d << spacer.innerSpaces() << "views: " << type.views <<"\n";
        break;
    case TLValue::UpdateChatAdmins:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "enabled: " << type.enabled <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateChatParticipantAdmin:
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "isAdmin: " << type.isAdmin <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateNewStickerSet:
        d << spacer.innerSpaces() << "stickerset: " << type.stickerset <<"\n";
        break;
    case TLValue::UpdateStickerSetsOrder:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "quint64OrderVector: " << type.quint64OrderVector <<"\n";
        break;
    case TLValue::UpdateStickerSets:
    case TLValue::UpdateSavedGifs:
    case TLValue::UpdateReadFeaturedStickers:
    case TLValue::UpdateRecentStickers:
    case TLValue::UpdateConfig:
    case TLValue::UpdatePtsChanged:
    case TLValue::UpdateLangPackTooLong:
    case TLValue::UpdateFavedStickers:
    case TLValue::UpdateContactsReset:
        break;
    case TLValue::UpdateBotInlineQuery:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "query: " << type.query <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        }
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        break;
    case TLValue::UpdateBotInlineSend:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "query: " << type.query <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        }
        d << spacer.innerSpaces() << "stringId: " << type.stringId <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "inputBotInlineMessageIDMsgId: " << type.inputBotInlineMessageIDMsgId <<"\n";
        }
        break;
    case TLValue::UpdateChannelPinnedMessage:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        break;
    case TLValue::UpdateBotCallbackQuery:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "quint32MsgId: " << type.quint32MsgId <<"\n";
        d << spacer.innerSpaces() << "chatInstance: " << type.chatInstance <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "byteArrayData: " << type.byteArrayData.toHex() <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "gameShortName: " << type.gameShortName <<"\n";
        }
        break;
    case TLValue::UpdateInlineBotCallbackQuery:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inputBotInlineMessageIDMsgId: " << type.inputBotInlineMessageIDMsgId <<"\n";
        d << spacer.innerSpaces() << "chatInstance: " << type.chatInstance <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "byteArrayData: " << type.byteArrayData.toHex() <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "gameShortName: " << type.gameShortName <<"\n";
        }
        break;
    case TLValue::UpdateDraftMessage:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "draft: " << type.draft <<"\n";
        break;
    case TLValue::UpdateChannelWebPage:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "webpage: " << type.webpage <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateDialogPinned:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    case TLValue::UpdatePinnedDialogs:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "peerOrderVector: " << type.peerOrderVector <<"\n";
        }
        break;
    case TLValue::UpdateBotWebhookJSON:
        d << spacer.innerSpaces() << "jSONData: " << type.jSONData <<"\n";
        break;
    case TLValue::UpdateBotWebhookJSONQuery:
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "jSONData: " << type.jSONData <<"\n";
        d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        break;
    case TLValue::UpdateBotShippingQuery:
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "payload: " << type.payload.toHex() <<"\n";
        d << spacer.innerSpaces() << "shippingAddress: " << type.shippingAddress <<"\n";
        break;
    case TLValue::UpdateBotPrecheckoutQuery:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "payload: " << type.payload.toHex() <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "info: " << type.info <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "shippingOptionId: " << type.shippingOptionId <<"\n";
        }
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "totalAmount: " << type.totalAmount <<"\n";
        break;
    case TLValue::UpdatePhoneCall:
        d << spacer.innerSpaces() << "phoneCall: " << type.phoneCall <<"\n";
        break;
    case TLValue::UpdateLangPack:
        d << spacer.innerSpaces() << "difference: " << type.difference <<"\n";
        break;
    case TLValue::UpdateChannelReadMessagesContents:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        break;
    case TLValue::UpdateChannelAvailableMessages:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "availableMinId: " << type.availableMinId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdates &type)
{
    d.noquote().nospace();
    d << "TLUpdates(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesTooLong:
        break;
    case TLValue::UpdateShortMessage:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "fwdFrom: " << type.fwdFrom <<"\n";
        }
        if (type.flags & 1 << 11) {
            d << spacer.innerSpaces() << "viaBotId: " << type.viaBotId <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "replyToMsgId: " << type.replyToMsgId <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        break;
    case TLValue::UpdateShortChatMessage:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "fromId: " << type.fromId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "fwdFrom: " << type.fwdFrom <<"\n";
        }
        if (type.flags & 1 << 11) {
            d << spacer.innerSpaces() << "viaBotId: " << type.viaBotId <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "replyToMsgId: " << type.replyToMsgId <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        break;
    case TLValue::UpdateShort:
        d << spacer.innerSpaces() << "update: " << type.update <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdatesCombined:
        d << spacer.innerSpaces() << "updates: " << type.updates <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seqStart: " << type.seqStart <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        break;
    case TLValue::Updates:
        d << spacer.innerSpaces() << "updates: " << type.updates <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        break;
    case TLValue::UpdateShortSentMessage:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        if (type.flags & 1 << 9) {
            d << spacer.innerSpaces() << "media: " << type.media <<"\n";
        }
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdatesChannelDifference &type)
{
    d.noquote().nospace();
    d << "TLUpdatesChannelDifference(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesChannelDifferenceEmpty:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        }
        break;
    case TLValue::UpdatesChannelDifferenceTooLong:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        }
        d << spacer.innerSpaces() << "topMessage: " << type.topMessage <<"\n";
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "readOutboxMaxId: " << type.readOutboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "unreadMentionsCount: " << type.unreadMentionsCount <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::UpdatesChannelDifference:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        }
        d << spacer.innerSpaces() << "newMessages: " << type.newMessages <<"\n";
        d << spacer.innerSpaces() << "otherUpdates: " << type.otherUpdates <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdatesDifference &type)
{
    d.noquote().nospace();
    d << "TLUpdatesDifference(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesDifferenceEmpty:
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        break;
    case TLValue::UpdatesDifference:
        d << spacer.innerSpaces() << "newMessages: " << type.newMessages <<"\n";
        d << spacer.innerSpaces() << "newEncryptedMessages: " << type.newEncryptedMessages <<"\n";
        d << spacer.innerSpaces() << "otherUpdates: " << type.otherUpdates <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "state: " << type.state <<"\n";
        break;
    case TLValue::UpdatesDifferenceSlice:
        d << spacer.innerSpaces() << "newMessages: " << type.newMessages <<"\n";
        d << spacer.innerSpaces() << "newEncryptedMessages: " << type.newEncryptedMessages <<"\n";
        d << spacer.innerSpaces() << "otherUpdates: " << type.otherUpdates <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "intermediateState: " << type.intermediateState <<"\n";
        break;
    case TLValue::UpdatesDifferenceTooLong:
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelAdminLogEventAction &type)
{
    d.noquote().nospace();
    d << "TLChannelAdminLogEventAction(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminLogEventActionChangeTitle:
    case TLValue::ChannelAdminLogEventActionChangeAbout:
    case TLValue::ChannelAdminLogEventActionChangeUsername:
        d << spacer.innerSpaces() << "prevValue: " << type.prevValue <<"\n";
        d << spacer.innerSpaces() << "stringNewValue: " << type.stringNewValue <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionChangePhoto:
        d << spacer.innerSpaces() << "prevPhoto: " << type.prevPhoto <<"\n";
        d << spacer.innerSpaces() << "newPhoto: " << type.newPhoto <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionToggleInvites:
    case TLValue::ChannelAdminLogEventActionToggleSignatures:
    case TLValue::ChannelAdminLogEventActionTogglePreHistoryHidden:
        d << spacer.innerSpaces() << "boolNewValue: " << type.boolNewValue <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionUpdatePinned:
    case TLValue::ChannelAdminLogEventActionDeleteMessage:
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionEditMessage:
        d << spacer.innerSpaces() << "prevMessage: " << type.prevMessage <<"\n";
        d << spacer.innerSpaces() << "newMessage: " << type.newMessage <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionParticipantJoin:
    case TLValue::ChannelAdminLogEventActionParticipantLeave:
        break;
    case TLValue::ChannelAdminLogEventActionParticipantInvite:
        d << spacer.innerSpaces() << "participant: " << type.participant <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionParticipantToggleBan:
    case TLValue::ChannelAdminLogEventActionParticipantToggleAdmin:
        d << spacer.innerSpaces() << "prevParticipant: " << type.prevParticipant <<"\n";
        d << spacer.innerSpaces() << "newParticipant: " << type.newParticipant <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionChangeStickerSet:
        d << spacer.innerSpaces() << "prevStickerset: " << type.prevStickerset <<"\n";
        d << spacer.innerSpaces() << "newStickerset: " << type.newStickerset <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentsPaymentResult &type)
{
    d.noquote().nospace();
    d << "TLPaymentsPaymentResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsPaymentResult:
        d << spacer.innerSpaces() << "updates: " << type.updates <<"\n";
        break;
    case TLValue::PaymentsPaymentVerficationNeeded:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelAdminLogEvent &type)
{
    d.noquote().nospace();
    d << "TLChannelAdminLogEvent(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminLogEvent:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "action: " << type.action <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelsAdminLogResults &type)
{
    d.noquote().nospace();
    d << "TLChannelsAdminLogResults(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsAdminLogResults:
        d << spacer.innerSpaces() << "events: " << type.events <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}
// End of generated TLTypes debug operators
