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

class Spacer
{
public:
    Spacer() :
        m_hasInnerCalls(false)
    {
        m_spacing += m_step;
    }
    ~Spacer()
    {
        m_spacing -= m_step;
    }

    QString innerSpaces()
    {
        if (!m_hasInnerCalls) {
            m_hasInnerCalls = true;
            return QLatin1Char('\n') + QString(m_spacing, QLatin1Char(' '));
        }
        return QString(m_spacing, QLatin1Char(' '));
    }

    QString outerSpaces()
    {
        if (m_hasInnerCalls) {
            return QString(m_spacing - m_step, QLatin1Char(' '));
        } else {
            return QStringLiteral(" ");
        }
    }

private:
    static int m_spacing;
    static const int m_step = 4;
    bool m_hasInnerCalls;
};

int Spacer::m_spacing = 0;

// Generated TLTypes debug operators
QDebug operator<<(QDebug d, const TLAccountDaysTTL &type)
{
    d.noquote().nospace();
    d << "TLAccountDaysTTL(" << type.tlType.toString() << ") {";
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
    d << "TLAccountPassword(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountNoPassword:
        d << spacer.innerSpaces() << "newSalt: " << type.newSalt <<"\n";
        d << spacer.innerSpaces() << "emailUnconfirmedPattern: " << type.emailUnconfirmedPattern <<"\n";
        break;
    case TLValue::AccountPassword:
        d << spacer.innerSpaces() << "currentSalt: " << type.currentSalt <<"\n";
        d << spacer.innerSpaces() << "newSalt: " << type.newSalt <<"\n";
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
    d << "TLAccountPasswordInputSettings(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPasswordInputSettings:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "newSalt: " << type.newSalt <<"\n";
        }
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "newPasswordHash: " << type.newPasswordHash <<"\n";
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
    d << "TLAccountPasswordSettings(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLAccountSentChangePhoneCode &type)
{
    d.noquote().nospace();
    d << "TLAccountSentChangePhoneCode(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountSentChangePhoneCode:
        d << spacer.innerSpaces() << "phoneCodeHash: " << type.phoneCodeHash <<"\n";
        d << spacer.innerSpaces() << "sendCallTimeout: " << type.sendCallTimeout <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAudio &type)
{
    d.noquote().nospace();
    d << "TLAudio(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AudioEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Audio:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
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
    d << "TLAuthCheckedPhone(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &type)
{
    d.noquote().nospace();
    d << "TLAuthExportedAuthorization(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthExportedAuthorization:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
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
    d << "TLAuthPasswordRecovery(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLAuthSentCode &type)
{
    d.noquote().nospace();
    d << "TLAuthSentCode(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthSentCode:
        d << spacer.innerSpaces() << "phoneRegistered: " << type.phoneRegistered <<"\n";
        d << spacer.innerSpaces() << "phoneCodeHash: " << type.phoneCodeHash <<"\n";
        d << spacer.innerSpaces() << "sendCallTimeout: " << type.sendCallTimeout <<"\n";
        d << spacer.innerSpaces() << "isPassword: " << type.isPassword <<"\n";
        break;
    case TLValue::AuthSentAppCode:
        d << spacer.innerSpaces() << "phoneRegistered: " << type.phoneRegistered <<"\n";
        d << spacer.innerSpaces() << "phoneCodeHash: " << type.phoneCodeHash <<"\n";
        d << spacer.innerSpaces() << "sendCallTimeout: " << type.sendCallTimeout <<"\n";
        d << spacer.innerSpaces() << "isPassword: " << type.isPassword <<"\n";
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
    d << "TLAuthorization(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLBotCommand &type)
{
    d.noquote().nospace();
    d << "TLBotCommand(" << type.tlType.toString() << ") {";
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
    d << "TLBotInfo(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInfoEmpty:
        break;
    case TLValue::BotInfo:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        d << spacer.innerSpaces() << "shareText: " << type.shareText <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        d << spacer.innerSpaces() << "commands: " << type.commands <<"\n";
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
    d << "TLChannelParticipant(" << type.tlType.toString() << ") {";
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
    case TLValue::ChannelParticipantModerator:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantEditor:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantKicked:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "kickedBy: " << type.kickedBy <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantCreator:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelParticipantRole &type)
{
    d.noquote().nospace();
    d << "TLChannelParticipantRole(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelRoleEmpty:
        break;
    case TLValue::ChannelRoleModerator:
        break;
    case TLValue::ChannelRoleEditor:
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
    d << "TLChannelParticipantsFilter(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelParticipantsRecent:
        break;
    case TLValue::ChannelParticipantsAdmins:
        break;
    case TLValue::ChannelParticipantsKicked:
        break;
    case TLValue::ChannelParticipantsBots:
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
    d << "TLChatParticipant(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatParticipant:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChatParticipantCreator:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::ChatParticipantAdmin:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
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
    d << "TLChatParticipants(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLContact &type)
{
    d.noquote().nospace();
    d << "TLContact(" << type.tlType.toString() << ") {";
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
    d << "TLContactBlocked(" << type.tlType.toString() << ") {";
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
    d << "TLContactLink(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactLinkUnknown:
        break;
    case TLValue::ContactLinkNone:
        break;
    case TLValue::ContactLinkHasPhone:
        break;
    case TLValue::ContactLinkContact:
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactSuggested &type)
{
    d.noquote().nospace();
    d << "TLContactSuggested(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactSuggested:
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "mutualContacts: " << type.mutualContacts <<"\n";
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
    d << "TLDisabledFeature(" << type.tlType.toString() << ") {";
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
    d << "TLEncryptedChat(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedChatEmpty:
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
        d << spacer.innerSpaces() << "gA: " << type.gA <<"\n";
        break;
    case TLValue::EncryptedChat:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gAOrB: " << type.gAOrB <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        break;
    case TLValue::EncryptedChatDiscarded:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
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
    d << "TLEncryptedFile(" << type.tlType.toString() << ") {";
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
    d << "TLEncryptedMessage(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedMessage:
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        break;
    case TLValue::EncryptedMessageService:
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
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
    d << "TLError(" << type.tlType.toString() << ") {";
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
    d << "TLExportedChatInvite(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLFileLocation &type)
{
    d.noquote().nospace();
    d << "TLFileLocation(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLGeoPoint &type)
{
    d.noquote().nospace();
    d << "TLGeoPoint(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLHelpAppChangelog &type)
{
    d.noquote().nospace();
    d << "TLHelpAppChangelog(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpAppChangelogEmpty:
        break;
    case TLValue::HelpAppChangelog:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
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
    d << "TLHelpAppUpdate(" << type.tlType.toString() << ") {";
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
    d << "TLHelpInviteText(" << type.tlType.toString() << ") {";
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
    d << "TLHelpTermsOfService(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLImportedContact &type)
{
    d.noquote().nospace();
    d << "TLImportedContact(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLInputAppEvent &type)
{
    d.noquote().nospace();
    d << "TLInputAppEvent(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLInputAudio &type)
{
    d.noquote().nospace();
    d << "TLInputAudio(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputAudioEmpty:
        break;
    case TLValue::InputAudio:
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
    d << "TLInputChannel(" << type.tlType.toString() << ") {";
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
    d << "TLInputContact(" << type.tlType.toString() << ") {";
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
    d << "TLInputDocument(" << type.tlType.toString() << ") {";
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
    d << "TLInputEncryptedChat(" << type.tlType.toString() << ") {";
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
    d << "TLInputEncryptedFile(" << type.tlType.toString() << ") {";
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
    d << "TLInputFile(" << type.tlType.toString() << ") {";
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
    d << "TLInputFileLocation(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputFileLocation:
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        break;
    case TLValue::InputVideoFileLocation:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputEncryptedFileLocation:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputAudioFileLocation:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        break;
    case TLValue::InputDocumentFileLocation:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
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
    d << "TLInputGeoPoint(" << type.tlType.toString() << ") {";
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
    d << "TLInputPeer(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerEmpty:
        break;
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
    d << "TLInputPeerNotifyEvents(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerNotifyEventsEmpty:
        break;
    case TLValue::InputPeerNotifyEventsAll:
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
    d << "TLInputPeerNotifySettings(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerNotifySettings:
        d << spacer.innerSpaces() << "muteUntil: " << type.muteUntil <<"\n";
        d << spacer.innerSpaces() << "sound: " << type.sound <<"\n";
        d << spacer.innerSpaces() << "showPreviews: " << type.showPreviews <<"\n";
        d << spacer.innerSpaces() << "eventsMask: " << type.eventsMask <<"\n";
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
    d << "TLInputPhoto(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLInputPhotoCrop &type)
{
    d.noquote().nospace();
    d << "TLInputPhotoCrop(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhotoCropAuto:
        break;
    case TLValue::InputPhotoCrop:
        d << spacer.innerSpaces() << "cropLeft: " << type.cropLeft <<"\n";
        d << spacer.innerSpaces() << "cropTop: " << type.cropTop <<"\n";
        d << spacer.innerSpaces() << "cropWidth: " << type.cropWidth <<"\n";
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
    d << "TLInputPrivacyKey(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
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
    d << "TLInputStickerSet(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLInputUser &type)
{
    d.noquote().nospace();
    d << "TLInputUser(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputUserEmpty:
        break;
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

QDebug operator<<(QDebug d, const TLInputVideo &type)
{
    d.noquote().nospace();
    d << "TLInputVideo(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputVideoEmpty:
        break;
    case TLValue::InputVideo:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
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
    d << "TLKeyboardButton(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::KeyboardButton:
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
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
    d << "TLKeyboardButtonRow(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLMessageEntity &type)
{
    d.noquote().nospace();
    d << "TLMessageEntity(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageEntityUnknown:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityMention:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityHashtag:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityBotCommand:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityUrl:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityEmail:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityBold:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityItalic:
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
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
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageGroup &type)
{
    d.noquote().nospace();
    d << "TLMessageGroup(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageGroup:
        d << spacer.innerSpaces() << "minId: " << type.minId <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
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
    d << "TLMessageRange(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesAffectedHistory(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesAffectedMessages(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesDhConfig(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesDhConfigNotModified:
        d << spacer.innerSpaces() << "random: " << type.random <<"\n";
        break;
    case TLValue::MessagesDhConfig:
        d << spacer.innerSpaces() << "g: " << type.g <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        d << spacer.innerSpaces() << "random: " << type.random <<"\n";
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
    d << "TLMessagesFilter(" << type.tlType.toString() << ") {";
    Spacer spacer;
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
    case TLValue::InputMessagesFilterAudioDocuments:
        break;
    case TLValue::InputMessagesFilterUrl:
        break;
    case TLValue::InputMessagesFilterGif:
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
    d << "TLMessagesSentEncryptedMessage(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLNearestDc &type)
{
    d.noquote().nospace();
    d << "TLNearestDc(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLPeer &type)
{
    d.noquote().nospace();
    d << "TLPeer(" << type.tlType.toString() << ") {";
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
    d << "TLPeerNotifyEvents(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerNotifyEventsEmpty:
        break;
    case TLValue::PeerNotifyEventsAll:
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
    d << "TLPeerNotifySettings(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerNotifySettingsEmpty:
        break;
    case TLValue::PeerNotifySettings:
        d << spacer.innerSpaces() << "muteUntil: " << type.muteUntil <<"\n";
        d << spacer.innerSpaces() << "sound: " << type.sound <<"\n";
        d << spacer.innerSpaces() << "showPreviews: " << type.showPreviews <<"\n";
        d << spacer.innerSpaces() << "eventsMask: " << type.eventsMask <<"\n";
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
    d << "TLPhotoSize(" << type.tlType.toString() << ") {";
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
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
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
    d << "TLPrivacyKey(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
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
    d << "TLPrivacyRule(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PrivacyValueAllowContacts:
        break;
    case TLValue::PrivacyValueAllowAll:
        break;
    case TLValue::PrivacyValueAllowUsers:
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::PrivacyValueDisallowContacts:
        break;
    case TLValue::PrivacyValueDisallowAll:
        break;
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
    d << "TLReceivedNotifyMessage(" << type.tlType.toString() << ") {";
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
    d << "TLReportReason(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputReportReasonSpam:
        break;
    case TLValue::InputReportReasonViolence:
        break;
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

QDebug operator<<(QDebug d, const TLSendMessageAction &type)
{
    d.noquote().nospace();
    d << "TLSendMessageAction(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SendMessageTypingAction:
        break;
    case TLValue::SendMessageCancelAction:
        break;
    case TLValue::SendMessageRecordVideoAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
        d << spacer.innerSpaces() << "progress: " << type.progress <<"\n";
        break;
    case TLValue::SendMessageRecordAudioAction:
        break;
    case TLValue::SendMessageUploadAudioAction:
        d << spacer.innerSpaces() << "progress: " << type.progress <<"\n";
        break;
    case TLValue::SendMessageUploadPhotoAction:
        d << spacer.innerSpaces() << "progress: " << type.progress <<"\n";
        break;
    case TLValue::SendMessageUploadDocumentAction:
        d << spacer.innerSpaces() << "progress: " << type.progress <<"\n";
        break;
    case TLValue::SendMessageGeoLocationAction:
        break;
    case TLValue::SendMessageChooseContactAction:
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
    d << "TLStickerPack(" << type.tlType.toString() << ") {";
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
    d << "TLStorageFileType(" << type.tlType.toString() << ") {";
    Spacer spacer;
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
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLTrue &type)
{
    d.noquote().nospace();
    d << "TLTrue(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::True:
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
    d << "TLUpdatesState(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLUploadFile &type)
{
    d.noquote().nospace();
    d << "TLUploadFile(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadFile:
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "mtime: " << type.mtime <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
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
    d << "TLUserProfilePhoto(" << type.tlType.toString() << ") {";
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
    d << "TLUserStatus(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserStatusEmpty:
        break;
    case TLValue::UserStatusOnline:
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        break;
    case TLValue::UserStatusOffline:
        d << spacer.innerSpaces() << "wasOnline: " << type.wasOnline <<"\n";
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
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLVideo &type)
{
    d.noquote().nospace();
    d << "TLVideo(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::VideoEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Video:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
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
    d << "TLWallPaper(" << type.tlType.toString() << ") {";
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
    d << "TLAccountAuthorizations(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLBotInlineMessage &type)
{
    d.noquote().nospace();
    d << "TLBotInlineMessage(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInlineMessageMediaAuto:
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::BotInlineMessageText:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
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
    d << "TLChannelMessagesFilter(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelMessagesFilterEmpty:
        break;
    case TLValue::ChannelMessagesFilter:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "ranges: " << type.ranges <<"\n";
        break;
    case TLValue::ChannelMessagesFilterCollapsed:
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
    d << "TLChatPhoto(" << type.tlType.toString() << ") {";
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
    d << "TLContactStatus(" << type.tlType.toString() << ") {";
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
    d << "TLDcOption(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLDialog &type)
{
    d.noquote().nospace();
    d << "TLDialog(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Dialog:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "topMessage: " << type.topMessage <<"\n";
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        break;
    case TLValue::DialogChannel:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "topMessage: " << type.topMessage <<"\n";
        d << spacer.innerSpaces() << "topImportantMessage: " << type.topImportantMessage <<"\n";
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "unreadImportantCount: " << type.unreadImportantCount <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
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
    d << "TLDocumentAttribute(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DocumentAttributeImageSize:
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::DocumentAttributeAnimated:
        break;
    case TLValue::DocumentAttributeSticker:
        d << spacer.innerSpaces() << "alt: " << type.alt <<"\n";
        d << spacer.innerSpaces() << "stickerset: " << type.stickerset <<"\n";
        break;
    case TLValue::DocumentAttributeVideo:
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::DocumentAttributeAudio:
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "performer: " << type.performer <<"\n";
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

QDebug operator<<(QDebug d, const TLInputBotInlineMessage &type)
{
    d.noquote().nospace();
    d << "TLInputBotInlineMessage(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineMessageMediaAuto:
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputBotInlineMessageText:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
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
    d << "TLInputBotInlineResult(" << type.tlType.toString() << ") {";
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
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputChatPhoto &type)
{
    d.noquote().nospace();
    d << "TLInputChatPhoto(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "crop: " << type.crop <<"\n";
        break;
    case TLValue::InputChatPhoto:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "crop: " << type.crop <<"\n";
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
    d << "TLInputMedia(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaPhoto:
        d << spacer.innerSpaces() << "idInputPhoto: " << type.idInputPhoto <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaGeoPoint:
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        break;
    case TLValue::InputMediaContact:
        d << spacer.innerSpaces() << "phoneNumber: " << type.phoneNumber <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        break;
    case TLValue::InputMediaUploadedVideo:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaUploadedThumbVideo:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaVideo:
        d << spacer.innerSpaces() << "idInputVideo: " << type.idInputVideo <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaUploadedAudio:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        break;
    case TLValue::InputMediaAudio:
        d << spacer.innerSpaces() << "idInputAudio: " << type.idInputAudio <<"\n";
        break;
    case TLValue::InputMediaUploadedDocument:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaUploadedThumbDocument:
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaDocument:
        d << spacer.innerSpaces() << "idInputDocument: " << type.idInputDocument <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::InputMediaVenue:
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        break;
    case TLValue::InputMediaGifExternal:
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
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
    d << "TLInputNotifyPeer(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputNotifyPeer:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    case TLValue::InputNotifyUsers:
        break;
    case TLValue::InputNotifyChats:
        break;
    case TLValue::InputNotifyAll:
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
    d << "TLInputPrivacyRule(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
        break;
    case TLValue::InputPrivacyValueAllowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::InputPrivacyValueDisallowContacts:
        break;
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueDisallowUsers:
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
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
    d << "TLNotifyPeer(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NotifyPeer:
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
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
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoto &type)
{
    d.noquote().nospace();
    d << "TLPhoto(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotoEmpty:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Photo:
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
    d << "TLReplyMarkup(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ReplyKeyboardHide:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    case TLValue::ReplyKeyboardForceReply:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        break;
    case TLValue::ReplyKeyboardMarkup:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
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
    d << "TLStickerSet(" << type.tlType.toString() << ") {";
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
    d << "TLUser(" << type.tlType.toString() << ") {";
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
    d << "TLAccountPrivacyRules(" << type.tlType.toString() << ") {";
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
    d << "TLAuthAuthorization(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthAuthorization:
        d << spacer.innerSpaces() << "user: " << type.user <<"\n";
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
    d << "TLChannelsChannelParticipant(" << type.tlType.toString() << ") {";
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
    d << "TLChannelsChannelParticipants(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsChannelParticipants:
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
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
    d << "TLChat(" << type.tlType.toString() << ") {";
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
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
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
        break;
    case TLValue::ChannelForbidden:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << type.accessHash <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
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
    d << "TLChatFull(" << type.tlType.toString() << ") {";
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
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "unreadImportantCount: " << type.unreadImportantCount <<"\n";
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
    d << "TLChatInvite(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatInviteAlready:
        d << spacer.innerSpaces() << "chat: " << type.chat <<"\n";
        break;
    case TLValue::ChatInvite:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
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
    d << "TLConfig(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Config:
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
    d << "TLContactsBlocked(" << type.tlType.toString() << ") {";
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
    d << "TLContactsContacts(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        d << spacer.innerSpaces() << "contacts: " << type.contacts <<"\n";
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
    d << "TLContactsFound(" << type.tlType.toString() << ") {";
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
    d << "TLContactsImportedContacts(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsImportedContacts:
        d << spacer.innerSpaces() << "imported: " << type.imported <<"\n";
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
    d << "TLContactsLink(" << type.tlType.toString() << ") {";
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
    d << "TLContactsResolvedPeer(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLContactsSuggested &type)
{
    d.noquote().nospace();
    d << "TLContactsSuggested(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsSuggested:
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
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
    d << "TLDocument(" << type.tlType.toString() << ") {";
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
    d << "TLFoundGif(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLHelpSupport &type)
{
    d.noquote().nospace();
    d << "TLHelpSupport(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLMessageAction &type)
{
    d.noquote().nospace();
    d << "TLMessageAction(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageActionEmpty:
        break;
    case TLValue::MessageActionChatCreate:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessageActionChatEditTitle:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    case TLValue::MessageActionChatEditPhoto:
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        break;
    case TLValue::MessageActionChatDeletePhoto:
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
    case TLValue::MessageActionChannelCreate:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    case TLValue::MessageActionChatMigrateTo:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::MessageActionChannelMigrateFrom:
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
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
    d << "TLMessagesAllStickers(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesChatFull(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesChats(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesChats:
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
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
    d << "TLMessagesFoundGifs(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLMessagesSavedGifs &type)
{
    d.noquote().nospace();
    d << "TLMessagesSavedGifs(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesStickerSet(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesStickers(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLPhotosPhoto &type)
{
    d.noquote().nospace();
    d << "TLPhotosPhoto(" << type.tlType.toString() << ") {";
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
    d << "TLPhotosPhotos(" << type.tlType.toString() << ") {";
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

QDebug operator<<(QDebug d, const TLUserFull &type)
{
    d.noquote().nospace();
    d << "TLUserFull(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserFull:
        d << spacer.innerSpaces() << "user: " << type.user <<"\n";
        d << spacer.innerSpaces() << "link: " << type.link <<"\n";
        d << spacer.innerSpaces() << "profilePhoto: " << type.profilePhoto <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        d << spacer.innerSpaces() << "blocked: " << type.blocked <<"\n";
        d << spacer.innerSpaces() << "botInfo: " << type.botInfo <<"\n";
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
    d << "TLWebPage(" << type.tlType.toString() << ") {";
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
    d << "TLBotInlineResult(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInlineMediaResultDocument:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::BotInlineMediaResultPhoto:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
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
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageMedia &type)
{
    d.noquote().nospace();
    d << "TLMessageMedia(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageMediaEmpty:
        break;
    case TLValue::MessageMediaPhoto:
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::MessageMediaVideo:
        d << spacer.innerSpaces() << "video: " << type.video <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
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
    case TLValue::MessageMediaUnsupported:
        break;
    case TLValue::MessageMediaDocument:
        d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        d << spacer.innerSpaces() << "caption: " << type.caption <<"\n";
        break;
    case TLValue::MessageMediaAudio:
        d << spacer.innerSpaces() << "audio: " << type.audio <<"\n";
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
    d << "TLMessagesBotResults(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesBotResults:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "nextOffset: " << type.nextOffset <<"\n";
        }
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
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
    d << "TLMessage(" << type.tlType.toString() << ") {";
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
            d << spacer.innerSpaces() << "fwdFromId: " << type.fwdFromId <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "fwdDate: " << type.fwdDate <<"\n";
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
        break;
    case TLValue::MessageService:
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 8) {
            d << spacer.innerSpaces() << "fromId: " << type.fromId <<"\n";
        }
        d << spacer.innerSpaces() << "toId: " << type.toId <<"\n";
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
    d << "TLMessagesDialogs(" << type.tlType.toString() << ") {";
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
    d << "TLMessagesMessages(" << type.tlType.toString() << ") {";
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
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "collapsed: " << type.collapsed <<"\n";
        }
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
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
    d << "TLUpdate(" << type.tlType.toString() << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdateNewMessage:
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateMessageID:
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        break;
    case TLValue::UpdateDeleteMessages:
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
    case TLValue::UpdateNewAuthorization:
        d << spacer.innerSpaces() << "authKeyId: " << type.authKeyId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "device: " << type.device <<"\n";
        d << spacer.innerSpaces() << "location: " << type.location <<"\n";
        break;
    case TLValue::UpdateNewEncryptedMessage:
        d << spacer.innerSpaces() << "messageEncrypted: " << type.messageEncrypted <<"\n";
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
        d << spacer.innerSpaces() << "peerNotify: " << type.peerNotify <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        break;
    case TLValue::UpdateServiceNotification:
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "messageString: " << type.messageString <<"\n";
        d << spacer.innerSpaces() << "media: " << type.media <<"\n";
        d << spacer.innerSpaces() << "popup: " << type.popup <<"\n";
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
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
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
    case TLValue::UpdateReadMessagesContents:
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateChannelTooLong:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::UpdateChannel:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::UpdateChannelGroup:
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "group: " << type.group <<"\n";
        break;
    case TLValue::UpdateNewChannelMessage:
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateReadChannelInbox:
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
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
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
        d << spacer.innerSpaces() << "order: " << type.order <<"\n";
        break;
    case TLValue::UpdateStickerSets:
        break;
    case TLValue::UpdateSavedGifs:
        break;
    case TLValue::UpdateBotInlineQuery:
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "query: " << type.query <<"\n";
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
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
    d << "TLUpdates(" << type.tlType.toString() << ") {";
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
            d << spacer.innerSpaces() << "fwdFromId: " << type.fwdFromId <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "fwdDate: " << type.fwdDate <<"\n";
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
            d << spacer.innerSpaces() << "fwdFromId: " << type.fwdFromId <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "fwdDate: " << type.fwdDate <<"\n";
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
    d << "TLUpdatesChannelDifference(" << type.tlType.toString() << ") {";
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
        d << spacer.innerSpaces() << "topImportantMessage: " << type.topImportantMessage <<"\n";
        d << spacer.innerSpaces() << "readInboxMaxId: " << type.readInboxMaxId <<"\n";
        d << spacer.innerSpaces() << "unreadCount: " << type.unreadCount <<"\n";
        d << spacer.innerSpaces() << "unreadImportantCount: " << type.unreadImportantCount <<"\n";
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
    d << "TLUpdatesDifference(" << type.tlType.toString() << ") {";
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
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

// End of generated TLTypes debug operators
