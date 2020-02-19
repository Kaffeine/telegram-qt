/*
   Copyright (C) 2020 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "TLTypes.hpp"

// Generated TLTypes
bool TLAccountDaysTTL::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountDaysTTL:
        return true;
    default:
        return false;
    }
}

bool TLAccountDaysTTL::operator==(const TLAccountDaysTTL &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountDaysTTL:
        return days == v.days;
    default:
        return false;
    }
}

bool TLAccountSentEmailCode::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountSentEmailCode:
        return true;
    default:
        return false;
    }
}

bool TLAccountSentEmailCode::operator==(const TLAccountSentEmailCode &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountSentEmailCode:
        return true
                && emailPattern == v.emailPattern
                && length == v.length
                ;
    default:
        return false;
    }
}

bool TLAccountTakeout::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountTakeout:
        return true;
    default:
        return false;
    }
}

bool TLAccountTakeout::operator==(const TLAccountTakeout &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountTakeout:
        return id == v.id;
    default:
        return false;
    }
}

bool TLAccountTmpPassword::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountTmpPassword:
        return true;
    default:
        return false;
    }
}

bool TLAccountTmpPassword::operator==(const TLAccountTmpPassword &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountTmpPassword:
        return true
                && tmpPassword == v.tmpPassword
                && validUntil == v.validUntil
                ;
    default:
        return false;
    }
}

bool TLAuthCheckedPhone::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthCheckedPhone:
        return true;
    default:
        return false;
    }
}

bool TLAuthCheckedPhone::operator==(const TLAuthCheckedPhone &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthCheckedPhone:
        return phoneRegistered == v.phoneRegistered;
    default:
        return false;
    }
}

bool TLAuthCodeType::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthCodeTypeSms:
    case TLValue::AuthCodeTypeCall:
    case TLValue::AuthCodeTypeFlashCall:
        return true;
    default:
        return false;
    }
}

bool TLAuthCodeType::operator==(const TLAuthCodeType &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthCodeTypeSms:
    case TLValue::AuthCodeTypeCall:
    case TLValue::AuthCodeTypeFlashCall:
        return true;
    default:
        return false;
    }
}

bool TLAuthExportedAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthExportedAuthorization:
        return true;
    default:
        return false;
    }
}

bool TLAuthExportedAuthorization::operator==(const TLAuthExportedAuthorization &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthExportedAuthorization:
        return true
                && id == v.id
                && bytes == v.bytes
                ;
    default:
        return false;
    }
}

bool TLAuthPasswordRecovery::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthPasswordRecovery:
        return true;
    default:
        return false;
    }
}

bool TLAuthPasswordRecovery::operator==(const TLAuthPasswordRecovery &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthPasswordRecovery:
        return emailPattern == v.emailPattern;
    default:
        return false;
    }
}

bool TLAuthSentCodeType::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthSentCodeTypeApp:
    case TLValue::AuthSentCodeTypeSms:
    case TLValue::AuthSentCodeTypeCall:
    case TLValue::AuthSentCodeTypeFlashCall:
        return true;
    default:
        return false;
    }
}

bool TLAuthSentCodeType::operator==(const TLAuthSentCodeType &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthSentCodeTypeApp:
    case TLValue::AuthSentCodeTypeSms:
    case TLValue::AuthSentCodeTypeCall:
        return length == v.length;
    case TLValue::AuthSentCodeTypeFlashCall:
        return pattern == v.pattern;
    default:
        return false;
    }
}

bool TLBadMsgNotification::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::BadMsgNotification:
    case TLValue::BadServerSalt:
        return true;
    default:
        return false;
    }
}

bool TLBadMsgNotification::operator==(const TLBadMsgNotification &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::BadMsgNotification:
        return true
                && badMsgId == v.badMsgId
                && badMsgSeqno == v.badMsgSeqno
                && errorCode == v.errorCode
                ;
    case TLValue::BadServerSalt:
        return true
                && badMsgId == v.badMsgId
                && badMsgSeqno == v.badMsgSeqno
                && errorCode == v.errorCode
                && newServerSalt == v.newServerSalt
                ;
    default:
        return false;
    }
}

bool TLBotCommand::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::BotCommand:
        return true;
    default:
        return false;
    }
}

bool TLBotCommand::operator==(const TLBotCommand &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::BotCommand:
        return true
                && command == v.command
                && description == v.description
                ;
    default:
        return false;
    }
}

bool TLBotInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::BotInfo:
        return true;
    default:
        return false;
    }
}

bool TLBotInfo::operator==(const TLBotInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::BotInfo:
        return true
                && userId == v.userId
                && description == v.description
                && commands == v.commands
                ;
    default:
        return false;
    }
}

bool TLCdnPublicKey::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::CdnPublicKey:
        return true;
    default:
        return false;
    }
}

bool TLCdnPublicKey::operator==(const TLCdnPublicKey &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::CdnPublicKey:
        return true
                && dcId == v.dcId
                && publicKey == v.publicKey
                ;
    default:
        return false;
    }
}

bool TLChannelParticipantsFilter::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelParticipantsRecent:
    case TLValue::ChannelParticipantsAdmins:
    case TLValue::ChannelParticipantsKicked:
    case TLValue::ChannelParticipantsBots:
    case TLValue::ChannelParticipantsBanned:
    case TLValue::ChannelParticipantsSearch:
        return true;
    default:
        return false;
    }
}

bool TLChannelParticipantsFilter::operator==(const TLChannelParticipantsFilter &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelParticipantsRecent:
    case TLValue::ChannelParticipantsAdmins:
    case TLValue::ChannelParticipantsBots:
        return true;
    case TLValue::ChannelParticipantsKicked:
    case TLValue::ChannelParticipantsBanned:
    case TLValue::ChannelParticipantsSearch:
        return q == v.q;
    default:
        return false;
    }
}

bool TLChatOnlines::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatOnlines:
        return true;
    default:
        return false;
    }
}

bool TLChatOnlines::operator==(const TLChatOnlines &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatOnlines:
        return onlines == v.onlines;
    default:
        return false;
    }
}

bool TLChatParticipant::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatParticipant:
    case TLValue::ChatParticipantCreator:
    case TLValue::ChatParticipantAdmin:
        return true;
    default:
        return false;
    }
}

bool TLChatParticipant::operator==(const TLChatParticipant &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatParticipant:
    case TLValue::ChatParticipantAdmin:
        return true
                && userId == v.userId
                && inviterId == v.inviterId
                && date == v.date
                ;
    case TLValue::ChatParticipantCreator:
        return userId == v.userId;
    default:
        return false;
    }
}

bool TLChatParticipants::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatParticipantsForbidden:
    case TLValue::ChatParticipants:
        return true;
    default:
        return false;
    }
}

bool TLChatParticipants::operator==(const TLChatParticipants &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatParticipantsForbidden:
        return true
                && flags == v.flags
                && chatId == v.chatId
                && selfParticipant == v.selfParticipant
                ;
    case TLValue::ChatParticipants:
        return true
                && chatId == v.chatId
                && participants == v.participants
                && version == v.version
                ;
    default:
        return false;
    }
}

bool TLClientDHInnerData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ClientDHInnerData:
        return true;
    default:
        return false;
    }
}

bool TLClientDHInnerData::operator==(const TLClientDHInnerData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ClientDHInnerData:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && retryId == v.retryId
                && gB == v.gB
                ;
    default:
        return false;
    }
}

bool TLContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Contact:
        return true;
    default:
        return false;
    }
}

bool TLContact::operator==(const TLContact &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Contact:
        return true
                && userId == v.userId
                && mutual == v.mutual
                ;
    default:
        return false;
    }
}

bool TLContactBlocked::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactBlocked:
        return true;
    default:
        return false;
    }
}

bool TLContactBlocked::operator==(const TLContactBlocked &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactBlocked:
        return true
                && userId == v.userId
                && date == v.date
                ;
    default:
        return false;
    }
}

bool TLContactLink::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactLinkUnknown:
    case TLValue::ContactLinkNone:
    case TLValue::ContactLinkHasPhone:
    case TLValue::ContactLinkContact:
        return true;
    default:
        return false;
    }
}

bool TLContactLink::operator==(const TLContactLink &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactLinkUnknown:
    case TLValue::ContactLinkNone:
    case TLValue::ContactLinkHasPhone:
    case TLValue::ContactLinkContact:
        return true;
    default:
        return false;
    }
}

bool TLDataJSON::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DataJSON:
        return true;
    default:
        return false;
    }
}

bool TLDataJSON::operator==(const TLDataJSON &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DataJSON:
        return data == v.data;
    default:
        return false;
    }
}

bool TLDestroyAuthKeyRes::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DestroyAuthKeyOk:
    case TLValue::DestroyAuthKeyNone:
    case TLValue::DestroyAuthKeyFail:
        return true;
    default:
        return false;
    }
}

bool TLDestroyAuthKeyRes::operator==(const TLDestroyAuthKeyRes &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DestroyAuthKeyOk:
    case TLValue::DestroyAuthKeyNone:
    case TLValue::DestroyAuthKeyFail:
        return true;
    default:
        return false;
    }
}

bool TLDestroySessionRes::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DestroySessionOk:
    case TLValue::DestroySessionNone:
        return true;
    default:
        return false;
    }
}

bool TLDestroySessionRes::operator==(const TLDestroySessionRes &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DestroySessionOk:
    case TLValue::DestroySessionNone:
        return sessionId == v.sessionId;
    default:
        return false;
    }
}

bool TLEncryptedChat::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::EncryptedChatEmpty:
    case TLValue::EncryptedChatWaiting:
    case TLValue::EncryptedChatRequested:
    case TLValue::EncryptedChat:
    case TLValue::EncryptedChatDiscarded:
        return true;
    default:
        return false;
    }
}

bool TLEncryptedChat::operator==(const TLEncryptedChat &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::EncryptedChatEmpty:
    case TLValue::EncryptedChatDiscarded:
        return id == v.id;
    case TLValue::EncryptedChatWaiting:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                ;
    case TLValue::EncryptedChatRequested:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                && gA == v.gA
                ;
    case TLValue::EncryptedChat:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                && gAOrB == v.gAOrB
                && keyFingerprint == v.keyFingerprint
                ;
    default:
        return false;
    }
}

bool TLEncryptedFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::EncryptedFileEmpty:
    case TLValue::EncryptedFile:
        return true;
    default:
        return false;
    }
}

bool TLEncryptedFile::operator==(const TLEncryptedFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::EncryptedFileEmpty:
        return true;
    case TLValue::EncryptedFile:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && size == v.size
                && dcId == v.dcId
                && keyFingerprint == v.keyFingerprint
                ;
    default:
        return false;
    }
}

bool TLEncryptedMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::EncryptedMessage:
    case TLValue::EncryptedMessageService:
        return true;
    default:
        return false;
    }
}

bool TLEncryptedMessage::operator==(const TLEncryptedMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::EncryptedMessage:
        return true
                && randomId == v.randomId
                && chatId == v.chatId
                && date == v.date
                && bytes == v.bytes
                && file == v.file
                ;
    case TLValue::EncryptedMessageService:
        return true
                && randomId == v.randomId
                && chatId == v.chatId
                && date == v.date
                && bytes == v.bytes
                ;
    default:
        return false;
    }
}

bool TLError::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Error:
        return true;
    default:
        return false;
    }
}

bool TLError::operator==(const TLError &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Error:
        return true
                && code == v.code
                && text == v.text
                ;
    default:
        return false;
    }
}

bool TLExportedChatInvite::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatInviteEmpty:
    case TLValue::ChatInviteExported:
        return true;
    default:
        return false;
    }
}

bool TLExportedChatInvite::operator==(const TLExportedChatInvite &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatInviteEmpty:
        return true;
    case TLValue::ChatInviteExported:
        return link == v.link;
    default:
        return false;
    }
}

bool TLExportedMessageLink::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ExportedMessageLink:
        return true;
    default:
        return false;
    }
}

bool TLExportedMessageLink::operator==(const TLExportedMessageLink &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ExportedMessageLink:
        return true
                && link == v.link
                && html == v.html
                ;
    default:
        return false;
    }
}

bool TLFileHash::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::FileHash:
        return true;
    default:
        return false;
    }
}

bool TLFileHash::operator==(const TLFileHash &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::FileHash:
        return true
                && offset == v.offset
                && limit == v.limit
                && hash == v.hash
                ;
    default:
        return false;
    }
}

bool TLFileLocation::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::FileLocationUnavailable:
    case TLValue::FileLocation:
        return true;
    default:
        return false;
    }
}

bool TLFileLocation::operator==(const TLFileLocation &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::FileLocationUnavailable:
        return true
                && volumeId == v.volumeId
                && localId == v.localId
                && secret == v.secret
                ;
    case TLValue::FileLocation:
        return true
                && dcId == v.dcId
                && volumeId == v.volumeId
                && localId == v.localId
                && secret == v.secret
                && fileReference == v.fileReference
                ;
    default:
        return false;
    }
}

bool TLFutureSalt::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::FutureSalt:
        return true;
    default:
        return false;
    }
}

bool TLFutureSalt::operator==(const TLFutureSalt &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::FutureSalt:
        return true
                && validSince == v.validSince
                && validUntil == v.validUntil
                && salt == v.salt
                ;
    default:
        return false;
    }
}

bool TLFutureSalts::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::FutureSalts:
        return true;
    default:
        return false;
    }
}

bool TLFutureSalts::operator==(const TLFutureSalts &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::FutureSalts:
        return true
                && reqMsgId == v.reqMsgId
                && now == v.now
                && salts == v.salts
                ;
    default:
        return false;
    }
}

bool TLGeoPoint::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::GeoPointEmpty:
    case TLValue::GeoPoint:
        return true;
    default:
        return false;
    }
}

bool TLGeoPoint::operator==(const TLGeoPoint &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::GeoPointEmpty:
        return true;
    case TLValue::GeoPoint:
        return true
                && longitude == v.longitude
                && latitude == v.latitude
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLHelpInviteText::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpInviteText:
        return true;
    default:
        return false;
    }
}

bool TLHelpInviteText::operator==(const TLHelpInviteText &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpInviteText:
        return message == v.message;
    default:
        return false;
    }
}

bool TLHelpPassportConfig::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpPassportConfigNotModified:
    case TLValue::HelpPassportConfig:
        return true;
    default:
        return false;
    }
}

bool TLHelpPassportConfig::operator==(const TLHelpPassportConfig &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpPassportConfigNotModified:
        return true;
    case TLValue::HelpPassportConfig:
        return true
                && hash == v.hash
                && countriesLangs == v.countriesLangs
                ;
    default:
        return false;
    }
}

bool TLHelpSupportName::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpSupportName:
        return true;
    default:
        return false;
    }
}

bool TLHelpSupportName::operator==(const TLHelpSupportName &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpSupportName:
        return name == v.name;
    default:
        return false;
    }
}

bool TLHighScore::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HighScore:
        return true;
    default:
        return false;
    }
}

bool TLHighScore::operator==(const TLHighScore &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HighScore:
        return true
                && pos == v.pos
                && userId == v.userId
                && score == v.score
                ;
    default:
        return false;
    }
}

bool TLHttpWait::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HttpWait:
        return true;
    default:
        return false;
    }
}

bool TLHttpWait::operator==(const TLHttpWait &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HttpWait:
        return true
                && maxDelay == v.maxDelay
                && waitAfter == v.waitAfter
                && maxWait == v.maxWait
                ;
    default:
        return false;
    }
}

bool TLImportedContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ImportedContact:
        return true;
    default:
        return false;
    }
}

bool TLImportedContact::operator==(const TLImportedContact &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ImportedContact:
        return true
                && userId == v.userId
                && clientId == v.clientId
                ;
    default:
        return false;
    }
}

bool TLInlineBotSwitchPM::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InlineBotSwitchPM:
        return true;
    default:
        return false;
    }
}

bool TLInlineBotSwitchPM::operator==(const TLInlineBotSwitchPM &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InlineBotSwitchPM:
        return true
                && text == v.text
                && startParam == v.startParam
                ;
    default:
        return false;
    }
}

bool TLInputAppEvent::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputAppEvent:
        return true;
    default:
        return false;
    }
}

bool TLInputAppEvent::operator==(const TLInputAppEvent &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputAppEvent:
        return true
                && time == v.time
                && type == v.type
                && peer == v.peer
                && data == v.data
                ;
    default:
        return false;
    }
}

bool TLInputBotInlineMessageID::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputBotInlineMessageID:
        return true;
    default:
        return false;
    }
}

bool TLInputBotInlineMessageID::operator==(const TLInputBotInlineMessageID &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputBotInlineMessageID:
        return true
                && dcId == v.dcId
                && id == v.id
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputChannel::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputChannelEmpty:
    case TLValue::InputChannel:
        return true;
    default:
        return false;
    }
}

bool TLInputChannel::operator==(const TLInputChannel &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputChannelEmpty:
        return true;
    case TLValue::InputChannel:
        return true
                && channelId == v.channelId
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputCheckPasswordSRP::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputCheckPasswordEmpty:
    case TLValue::InputCheckPasswordSRP:
        return true;
    default:
        return false;
    }
}

bool TLInputCheckPasswordSRP::operator==(const TLInputCheckPasswordSRP &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputCheckPasswordEmpty:
        return true;
    case TLValue::InputCheckPasswordSRP:
        return true
                && srpId == v.srpId
                && A == v.A
                && M1 == v.M1
                ;
    default:
        return false;
    }
}

bool TLInputClientProxy::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputClientProxy:
        return true;
    default:
        return false;
    }
}

bool TLInputClientProxy::operator==(const TLInputClientProxy &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputClientProxy:
        return true
                && address == v.address
                && port == v.port
                ;
    default:
        return false;
    }
}

bool TLInputContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPhoneContact:
        return true;
    default:
        return false;
    }
}

bool TLInputContact::operator==(const TLInputContact &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPhoneContact:
        return true
                && clientId == v.clientId
                && phone == v.phone
                && firstName == v.firstName
                && lastName == v.lastName
                ;
    default:
        return false;
    }
}

bool TLInputDocument::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputDocumentEmpty:
    case TLValue::InputDocument:
        return true;
    default:
        return false;
    }
}

bool TLInputDocument::operator==(const TLInputDocument &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputDocumentEmpty:
        return true;
    case TLValue::InputDocument:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && fileReference == v.fileReference
                ;
    default:
        return false;
    }
}

bool TLInputEncryptedChat::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputEncryptedChat:
        return true;
    default:
        return false;
    }
}

bool TLInputEncryptedChat::operator==(const TLInputEncryptedChat &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputEncryptedChat:
        return true
                && chatId == v.chatId
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputEncryptedFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputEncryptedFileEmpty:
    case TLValue::InputEncryptedFileUploaded:
    case TLValue::InputEncryptedFile:
    case TLValue::InputEncryptedFileBigUploaded:
        return true;
    default:
        return false;
    }
}

bool TLInputEncryptedFile::operator==(const TLInputEncryptedFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputEncryptedFileEmpty:
        return true;
    case TLValue::InputEncryptedFileUploaded:
        return true
                && id == v.id
                && parts == v.parts
                && md5Checksum == v.md5Checksum
                && keyFingerprint == v.keyFingerprint
                ;
    case TLValue::InputEncryptedFile:
        return true
                && id == v.id
                && accessHash == v.accessHash
                ;
    case TLValue::InputEncryptedFileBigUploaded:
        return true
                && id == v.id
                && parts == v.parts
                && keyFingerprint == v.keyFingerprint
                ;
    default:
        return false;
    }
}

bool TLInputFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputFile:
    case TLValue::InputFileBig:
        return true;
    default:
        return false;
    }
}

bool TLInputFile::operator==(const TLInputFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputFile:
        return true
                && id == v.id
                && parts == v.parts
                && name == v.name
                && md5Checksum == v.md5Checksum
                ;
    case TLValue::InputFileBig:
        return true
                && id == v.id
                && parts == v.parts
                && name == v.name
                ;
    default:
        return false;
    }
}

bool TLInputFileLocation::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputFileLocation:
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputDocumentFileLocation:
    case TLValue::InputSecureFileLocation:
    case TLValue::InputTakeoutFileLocation:
        return true;
    default:
        return false;
    }
}

bool TLInputFileLocation::operator==(const TLInputFileLocation &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputFileLocation:
        return true
                && volumeId == v.volumeId
                && localId == v.localId
                && secret == v.secret
                && fileReference == v.fileReference
                ;
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputSecureFileLocation:
        return true
                && id == v.id
                && accessHash == v.accessHash
                ;
    case TLValue::InputDocumentFileLocation:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && fileReference == v.fileReference
                ;
    case TLValue::InputTakeoutFileLocation:
        return true;
    default:
        return false;
    }
}

bool TLInputGeoPoint::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputGeoPointEmpty:
    case TLValue::InputGeoPoint:
        return true;
    default:
        return false;
    }
}

bool TLInputGeoPoint::operator==(const TLInputGeoPoint &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputGeoPointEmpty:
        return true;
    case TLValue::InputGeoPoint:
        return true
                && latitude == v.latitude
                && longitude == v.longitude
                ;
    default:
        return false;
    }
}

bool TLInputMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputMessageID:
    case TLValue::InputMessageReplyTo:
    case TLValue::InputMessagePinned:
        return true;
    default:
        return false;
    }
}

bool TLInputMessage::operator==(const TLInputMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputMessageID:
    case TLValue::InputMessageReplyTo:
        return id == v.id;
    case TLValue::InputMessagePinned:
        return true;
    default:
        return false;
    }
}

bool TLInputPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
    case TLValue::InputPeerChat:
    case TLValue::InputPeerUser:
    case TLValue::InputPeerChannel:
        return true;
    default:
        return false;
    }
}

bool TLInputPeer::operator==(const TLInputPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
        return true;
    case TLValue::InputPeerChat:
        return chatId == v.chatId;
    case TLValue::InputPeerUser:
        return true
                && userId == v.userId
                && accessHash == v.accessHash
                ;
    case TLValue::InputPeerChannel:
        return true
                && channelId == v.channelId
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputPeerNotifySettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPeerNotifySettings:
        return true;
    default:
        return false;
    }
}

bool TLInputPeerNotifySettings::operator==(const TLInputPeerNotifySettings &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPeerNotifySettings:
        return true
                && flags == v.flags
                && showPreviews == v.showPreviews
                && silent == v.silent
                && muteUntil == v.muteUntil
                && sound == v.sound
                ;
    default:
        return false;
    }
}

bool TLInputPhoneCall::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPhoneCall:
        return true;
    default:
        return false;
    }
}

bool TLInputPhoneCall::operator==(const TLInputPhoneCall &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPhoneCall:
        return true
                && id == v.id
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputPhoto::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPhotoEmpty:
    case TLValue::InputPhoto:
        return true;
    default:
        return false;
    }
}

bool TLInputPhoto::operator==(const TLInputPhoto &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPhotoEmpty:
        return true;
    case TLValue::InputPhoto:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && fileReference == v.fileReference
                ;
    default:
        return false;
    }
}

bool TLInputPrivacyKey::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
    case TLValue::InputPrivacyKeyChatInvite:
    case TLValue::InputPrivacyKeyPhoneCall:
    case TLValue::InputPrivacyKeyPhoneP2P:
        return true;
    default:
        return false;
    }
}

bool TLInputPrivacyKey::operator==(const TLInputPrivacyKey &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
    case TLValue::InputPrivacyKeyChatInvite:
    case TLValue::InputPrivacyKeyPhoneCall:
    case TLValue::InputPrivacyKeyPhoneP2P:
        return true;
    default:
        return false;
    }
}

bool TLInputSecureFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputSecureFileUploaded:
    case TLValue::InputSecureFile:
        return true;
    default:
        return false;
    }
}

bool TLInputSecureFile::operator==(const TLInputSecureFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputSecureFileUploaded:
        return true
                && id == v.id
                && parts == v.parts
                && md5Checksum == v.md5Checksum
                && fileHash == v.fileHash
                && secret == v.secret
                ;
    case TLValue::InputSecureFile:
        return true
                && id == v.id
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputStickerSet::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputStickerSetEmpty:
    case TLValue::InputStickerSetID:
    case TLValue::InputStickerSetShortName:
        return true;
    default:
        return false;
    }
}

bool TLInputStickerSet::operator==(const TLInputStickerSet &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputStickerSetEmpty:
        return true;
    case TLValue::InputStickerSetID:
        return true
                && id == v.id
                && accessHash == v.accessHash
                ;
    case TLValue::InputStickerSetShortName:
        return shortName == v.shortName;
    default:
        return false;
    }
}

bool TLInputStickeredMedia::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputStickeredMediaPhoto:
    case TLValue::InputStickeredMediaDocument:
        return true;
    default:
        return false;
    }
}

bool TLInputStickeredMedia::operator==(const TLInputStickeredMedia &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputStickeredMediaPhoto:
        return inputPhotoId == v.inputPhotoId;
    case TLValue::InputStickeredMediaDocument:
        return inputDocumentId == v.inputDocumentId;
    default:
        return false;
    }
}

bool TLInputUser::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
    case TLValue::InputUser:
        return true;
    default:
        return false;
    }
}

bool TLInputUser::operator==(const TLInputUser &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
        return true;
    case TLValue::InputUser:
        return true
                && userId == v.userId
                && accessHash == v.accessHash
                ;
    default:
        return false;
    }
}

bool TLInputWebFileLocation::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputWebFileLocation:
    case TLValue::InputWebFileGeoPointLocation:
        return true;
    default:
        return false;
    }
}

bool TLInputWebFileLocation::operator==(const TLInputWebFileLocation &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputWebFileLocation:
        return true
                && url == v.url
                && accessHash == v.accessHash
                ;
    case TLValue::InputWebFileGeoPointLocation:
        return true
                && geoPoint == v.geoPoint
                && accessHash == v.accessHash
                && w == v.w
                && h == v.h
                && zoom == v.zoom
                && scale == v.scale
                ;
    default:
        return false;
    }
}

bool TLIpPort::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::IpPort:
    case TLValue::IpPortSecret:
        return true;
    default:
        return false;
    }
}

bool TLIpPort::operator==(const TLIpPort &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::IpPort:
        return true
                && ipv4 == v.ipv4
                && port == v.port
                ;
    case TLValue::IpPortSecret:
        return true
                && ipv4 == v.ipv4
                && port == v.port
                && secret == v.secret
                ;
    default:
        return false;
    }
}

bool TLJSONObjectValue::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::JsonObjectValue:
        return true;
    default:
        return false;
    }
}

bool TLJSONObjectValue::operator==(const TLJSONObjectValue &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::JsonObjectValue:
        return true
                && key == v.key
                && value == v.value
                ;
    default:
        return false;
    }
}

bool TLJSONValue::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::JsonNull:
    case TLValue::JsonBool:
    case TLValue::JsonNumber:
    case TLValue::JsonString:
    case TLValue::JsonArray:
    case TLValue::JsonObject:
        return true;
    default:
        return false;
    }
}

bool TLJSONValue::operator==(const TLJSONValue &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::JsonNull:
        return true;
    case TLValue::JsonBool:
        return boolValue == v.boolValue;
    case TLValue::JsonNumber:
        return doubleValue == v.doubleValue;
    case TLValue::JsonString:
        return stringValue == v.stringValue;
    case TLValue::JsonArray:
        return jSONValueVector == v.jSONValueVector;
    case TLValue::JsonObject:
        return jSONObjectValueVector == v.jSONObjectValueVector;
    default:
        return false;
    }
}

bool TLLabeledPrice::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::LabeledPrice:
        return true;
    default:
        return false;
    }
}

bool TLLabeledPrice::operator==(const TLLabeledPrice &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::LabeledPrice:
        return true
                && label == v.label
                && amount == v.amount
                ;
    default:
        return false;
    }
}

bool TLLangPackString::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::LangPackString:
    case TLValue::LangPackStringPluralized:
    case TLValue::LangPackStringDeleted:
        return true;
    default:
        return false;
    }
}

bool TLLangPackString::operator==(const TLLangPackString &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::LangPackString:
        return true
                && key == v.key
                && value == v.value
                ;
    case TLValue::LangPackStringPluralized:
        return true
                && flags == v.flags
                && key == v.key
                && zeroValue == v.zeroValue
                && oneValue == v.oneValue
                && twoValue == v.twoValue
                && fewValue == v.fewValue
                && manyValue == v.manyValue
                && otherValue == v.otherValue
                ;
    case TLValue::LangPackStringDeleted:
        return key == v.key;
    default:
        return false;
    }
}

bool TLMaskCoords::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MaskCoords:
        return true;
    default:
        return false;
    }
}

bool TLMaskCoords::operator==(const TLMaskCoords &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MaskCoords:
        return true
                && n == v.n
                && x == v.x
                && y == v.y
                && zoom == v.zoom
                ;
    default:
        return false;
    }
}

bool TLMessageEntity::hasType(const quint32 value)
{
    switch (value) {
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
    case TLValue::MessageEntityMentionName:
    case TLValue::InputMessageEntityMentionName:
    case TLValue::MessageEntityPhone:
    case TLValue::MessageEntityCashtag:
        return true;
    default:
        return false;
    }
}

bool TLMessageEntity::operator==(const TLMessageEntity &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

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
    case TLValue::MessageEntityPhone:
    case TLValue::MessageEntityCashtag:
        return true
                && offset == v.offset
                && length == v.length
                ;
    case TLValue::MessageEntityPre:
        return true
                && offset == v.offset
                && length == v.length
                && language == v.language
                ;
    case TLValue::MessageEntityTextUrl:
        return true
                && offset == v.offset
                && length == v.length
                && url == v.url
                ;
    case TLValue::MessageEntityMentionName:
        return true
                && offset == v.offset
                && length == v.length
                && userId == v.userId
                ;
    case TLValue::InputMessageEntityMentionName:
        return true
                && offset == v.offset
                && length == v.length
                && inputUserUserId == v.inputUserUserId
                ;
    default:
        return false;
    }
}

bool TLMessageRange::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessageRange:
        return true;
    default:
        return false;
    }
}

bool TLMessageRange::operator==(const TLMessageRange &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessageRange:
        return true
                && minId == v.minId
                && maxId == v.maxId
                ;
    default:
        return false;
    }
}

bool TLMessagesAffectedHistory::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesAffectedHistory:
        return true;
    default:
        return false;
    }
}

bool TLMessagesAffectedHistory::operator==(const TLMessagesAffectedHistory &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesAffectedHistory:
        return true
                && pts == v.pts
                && ptsCount == v.ptsCount
                && offset == v.offset
                ;
    default:
        return false;
    }
}

bool TLMessagesAffectedMessages::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesAffectedMessages:
        return true;
    default:
        return false;
    }
}

bool TLMessagesAffectedMessages::operator==(const TLMessagesAffectedMessages &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesAffectedMessages:
        return true
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    default:
        return false;
    }
}

bool TLMessagesDhConfig::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesDhConfigNotModified:
    case TLValue::MessagesDhConfig:
        return true;
    default:
        return false;
    }
}

bool TLMessagesDhConfig::operator==(const TLMessagesDhConfig &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesDhConfigNotModified:
        return random == v.random;
    case TLValue::MessagesDhConfig:
        return true
                && g == v.g
                && p == v.p
                && version == v.version
                && random == v.random
                ;
    default:
        return false;
    }
}

bool TLMessagesSentEncryptedMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesSentEncryptedMessage:
    case TLValue::MessagesSentEncryptedFile:
        return true;
    default:
        return false;
    }
}

bool TLMessagesSentEncryptedMessage::operator==(const TLMessagesSentEncryptedMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesSentEncryptedMessage:
        return date == v.date;
    case TLValue::MessagesSentEncryptedFile:
        return true
                && date == v.date
                && file == v.file
                ;
    default:
        return false;
    }
}

bool TLMsgDetailedInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgDetailedInfo:
    case TLValue::MsgNewDetailedInfo:
        return true;
    default:
        return false;
    }
}

bool TLMsgDetailedInfo::operator==(const TLMsgDetailedInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MsgDetailedInfo:
        return true
                && msgId == v.msgId
                && answerMsgId == v.answerMsgId
                && bytes == v.bytes
                && status == v.status
                ;
    case TLValue::MsgNewDetailedInfo:
        return true
                && answerMsgId == v.answerMsgId
                && bytes == v.bytes
                && status == v.status
                ;
    default:
        return false;
    }
}

bool TLMsgResendReq::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgResendReq:
        return true;
    default:
        return false;
    }
}

bool TLMsgResendReq::operator==(const TLMsgResendReq &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MsgResendReq:
        return msgIds == v.msgIds;
    default:
        return false;
    }
}

bool TLMsgsAck::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgsAck:
        return true;
    default:
        return false;
    }
}

bool TLMsgsAck::operator==(const TLMsgsAck &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MsgsAck:
        return msgIds == v.msgIds;
    default:
        return false;
    }
}

bool TLMsgsAllInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgsAllInfo:
        return true;
    default:
        return false;
    }
}

bool TLMsgsAllInfo::operator==(const TLMsgsAllInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MsgsAllInfo:
        return true
                && msgIds == v.msgIds
                && info == v.info
                ;
    default:
        return false;
    }
}

bool TLMsgsStateInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgsStateInfo:
        return true;
    default:
        return false;
    }
}

bool TLMsgsStateInfo::operator==(const TLMsgsStateInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MsgsStateInfo:
        return true
                && reqMsgId == v.reqMsgId
                && info == v.info
                ;
    default:
        return false;
    }
}

bool TLMsgsStateReq::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgsStateReq:
        return true;
    default:
        return false;
    }
}

bool TLMsgsStateReq::operator==(const TLMsgsStateReq &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MsgsStateReq:
        return msgIds == v.msgIds;
    default:
        return false;
    }
}

bool TLNearestDc::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::NearestDc:
        return true;
    default:
        return false;
    }
}

bool TLNearestDc::operator==(const TLNearestDc &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::NearestDc:
        return true
                && country == v.country
                && thisDc == v.thisDc
                && nearestDc == v.nearestDc
                ;
    default:
        return false;
    }
}

bool TLNewSession::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::NewSessionCreated:
        return true;
    default:
        return false;
    }
}

bool TLNewSession::operator==(const TLNewSession &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::NewSessionCreated:
        return true
                && firstMsgId == v.firstMsgId
                && uniqueId == v.uniqueId
                && serverSalt == v.serverSalt
                ;
    default:
        return false;
    }
}

bool TLPQInnerData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PQInnerData:
    case TLValue::PQInnerDataDc:
    case TLValue::PQInnerDataTemp:
    case TLValue::PQInnerDataTempDc:
        return true;
    default:
        return false;
    }
}

bool TLPQInnerData::operator==(const TLPQInnerData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PQInnerData:
        return true
                && pq == v.pq
                && p == v.p
                && q == v.q
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonce == v.newNonce
                ;
    case TLValue::PQInnerDataDc:
        return true
                && pq == v.pq
                && p == v.p
                && q == v.q
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonce == v.newNonce
                && dc == v.dc
                ;
    case TLValue::PQInnerDataTemp:
        return true
                && pq == v.pq
                && p == v.p
                && q == v.q
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonce == v.newNonce
                && expiresIn == v.expiresIn
                ;
    case TLValue::PQInnerDataTempDc:
        return true
                && pq == v.pq
                && p == v.p
                && q == v.q
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonce == v.newNonce
                && dc == v.dc
                && expiresIn == v.expiresIn
                ;
    default:
        return false;
    }
}

bool TLPageCaption::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageCaption:
        return true;
    default:
        return false;
    }
}

bool TLPageCaption::operator==(const TLPageCaption &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageCaption:
        return true
                && text == v.text
                && credit == v.credit
                ;
    default:
        return false;
    }
}

bool TLPageListItem::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageListItemText:
    case TLValue::PageListItemBlocks:
        return true;
    default:
        return false;
    }
}

bool TLPageListItem::operator==(const TLPageListItem &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageListItemText:
        return text == v.text;
    case TLValue::PageListItemBlocks:
        return blocks == v.blocks;
    default:
        return false;
    }
}

bool TLPageListOrderedItem::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageListOrderedItemText:
    case TLValue::PageListOrderedItemBlocks:
        return true;
    default:
        return false;
    }
}

bool TLPageListOrderedItem::operator==(const TLPageListOrderedItem &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageListOrderedItemText:
        return true
                && num == v.num
                && text == v.text
                ;
    case TLValue::PageListOrderedItemBlocks:
        return true
                && num == v.num
                && blocks == v.blocks
                ;
    default:
        return false;
    }
}

bool TLPageRelatedArticle::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageRelatedArticle:
        return true;
    default:
        return false;
    }
}

bool TLPageRelatedArticle::operator==(const TLPageRelatedArticle &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageRelatedArticle:
        return true
                && flags == v.flags
                && url == v.url
                && webpageId == v.webpageId
                && title == v.title
                && description == v.description
                && photoId == v.photoId
                && author == v.author
                && publishedDate == v.publishedDate
                ;
    default:
        return false;
    }
}

bool TLPasswordKdfAlgo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PasswordKdfAlgoUnknown:
    case TLValue::PasswordKdfAlgoSHA256SHA256PBKDF2HMACSHA512iter100000SHA256ModPow:
        return true;
    default:
        return false;
    }
}

bool TLPasswordKdfAlgo::operator==(const TLPasswordKdfAlgo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PasswordKdfAlgoUnknown:
        return true;
    case TLValue::PasswordKdfAlgoSHA256SHA256PBKDF2HMACSHA512iter100000SHA256ModPow:
        return true
                && salt1 == v.salt1
                && salt2 == v.salt2
                && g == v.g
                && p == v.p
                ;
    default:
        return false;
    }
}

bool TLPaymentCharge::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentCharge:
        return true;
    default:
        return false;
    }
}

bool TLPaymentCharge::operator==(const TLPaymentCharge &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentCharge:
        return true
                && id == v.id
                && providerChargeId == v.providerChargeId
                ;
    default:
        return false;
    }
}

bool TLPaymentSavedCredentials::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentSavedCredentialsCard:
        return true;
    default:
        return false;
    }
}

bool TLPaymentSavedCredentials::operator==(const TLPaymentSavedCredentials &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentSavedCredentialsCard:
        return true
                && id == v.id
                && title == v.title
                ;
    default:
        return false;
    }
}

bool TLPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PeerUser:
    case TLValue::PeerChat:
    case TLValue::PeerChannel:
        return true;
    default:
        return false;
    }
}

bool TLPeer::operator==(const TLPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PeerUser:
        return userId == v.userId;
    case TLValue::PeerChat:
        return chatId == v.chatId;
    case TLValue::PeerChannel:
        return channelId == v.channelId;
    default:
        return false;
    }
}

bool TLPeerNotifySettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PeerNotifySettings:
        return true;
    default:
        return false;
    }
}

bool TLPeerNotifySettings::operator==(const TLPeerNotifySettings &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PeerNotifySettings:
        return true
                && flags == v.flags
                && showPreviews == v.showPreviews
                && silent == v.silent
                && muteUntil == v.muteUntil
                && sound == v.sound
                ;
    default:
        return false;
    }
}

bool TLPhoneCallDiscardReason::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhoneCallDiscardReasonMissed:
    case TLValue::PhoneCallDiscardReasonDisconnect:
    case TLValue::PhoneCallDiscardReasonHangup:
    case TLValue::PhoneCallDiscardReasonBusy:
        return true;
    default:
        return false;
    }
}

bool TLPhoneCallDiscardReason::operator==(const TLPhoneCallDiscardReason &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhoneCallDiscardReasonMissed:
    case TLValue::PhoneCallDiscardReasonDisconnect:
    case TLValue::PhoneCallDiscardReasonHangup:
    case TLValue::PhoneCallDiscardReasonBusy:
        return true;
    default:
        return false;
    }
}

bool TLPhoneConnection::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhoneConnection:
        return true;
    default:
        return false;
    }
}

bool TLPhoneConnection::operator==(const TLPhoneConnection &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhoneConnection:
        return true
                && id == v.id
                && ip == v.ip
                && ipv6 == v.ipv6
                && port == v.port
                && peerTag == v.peerTag
                ;
    default:
        return false;
    }
}

bool TLPhotoSize::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhotoSizeEmpty:
    case TLValue::PhotoSize:
    case TLValue::PhotoCachedSize:
    case TLValue::PhotoStrippedSize:
        return true;
    default:
        return false;
    }
}

bool TLPhotoSize::operator==(const TLPhotoSize &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhotoSizeEmpty:
        return type == v.type;
    case TLValue::PhotoSize:
        return true
                && type == v.type
                && location == v.location
                && w == v.w
                && h == v.h
                && size == v.size
                ;
    case TLValue::PhotoCachedSize:
        return true
                && type == v.type
                && location == v.location
                && w == v.w
                && h == v.h
                && bytes == v.bytes
                ;
    case TLValue::PhotoStrippedSize:
        return true
                && type == v.type
                && bytes == v.bytes
                ;
    default:
        return false;
    }
}

bool TLPollAnswer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PollAnswer:
        return true;
    default:
        return false;
    }
}

bool TLPollAnswer::operator==(const TLPollAnswer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PollAnswer:
        return true
                && text == v.text
                && option == v.option
                ;
    default:
        return false;
    }
}

bool TLPong::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Pong:
        return true;
    default:
        return false;
    }
}

bool TLPong::operator==(const TLPong &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Pong:
        return true
                && msgId == v.msgId
                && pingId == v.pingId
                ;
    default:
        return false;
    }
}

bool TLPopularContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PopularContact:
        return true;
    default:
        return false;
    }
}

bool TLPopularContact::operator==(const TLPopularContact &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PopularContact:
        return true
                && clientId == v.clientId
                && importers == v.importers
                ;
    default:
        return false;
    }
}

bool TLPostAddress::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PostAddress:
        return true;
    default:
        return false;
    }
}

bool TLPostAddress::operator==(const TLPostAddress &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PostAddress:
        return true
                && streetLine1 == v.streetLine1
                && streetLine2 == v.streetLine2
                && city == v.city
                && state == v.state
                && countryIso2 == v.countryIso2
                && postCode == v.postCode
                ;
    default:
        return false;
    }
}

bool TLPrivacyKey::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PrivacyKeyStatusTimestamp:
    case TLValue::PrivacyKeyChatInvite:
    case TLValue::PrivacyKeyPhoneCall:
    case TLValue::PrivacyKeyPhoneP2P:
        return true;
    default:
        return false;
    }
}

bool TLPrivacyKey::operator==(const TLPrivacyKey &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
    case TLValue::PrivacyKeyChatInvite:
    case TLValue::PrivacyKeyPhoneCall:
    case TLValue::PrivacyKeyPhoneP2P:
        return true;
    default:
        return false;
    }
}

bool TLPrivacyRule::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PrivacyValueAllowContacts:
    case TLValue::PrivacyValueAllowAll:
    case TLValue::PrivacyValueAllowUsers:
    case TLValue::PrivacyValueDisallowContacts:
    case TLValue::PrivacyValueDisallowAll:
    case TLValue::PrivacyValueDisallowUsers:
        return true;
    default:
        return false;
    }
}

bool TLPrivacyRule::operator==(const TLPrivacyRule &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PrivacyValueAllowContacts:
    case TLValue::PrivacyValueAllowAll:
    case TLValue::PrivacyValueDisallowContacts:
    case TLValue::PrivacyValueDisallowAll:
        return true;
    case TLValue::PrivacyValueAllowUsers:
    case TLValue::PrivacyValueDisallowUsers:
        return users == v.users;
    default:
        return false;
    }
}

bool TLReceivedNotifyMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ReceivedNotifyMessage:
        return true;
    default:
        return false;
    }
}

bool TLReceivedNotifyMessage::operator==(const TLReceivedNotifyMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ReceivedNotifyMessage:
        return true
                && id == v.id
                && flags == v.flags
                ;
    default:
        return false;
    }
}

bool TLReportReason::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputReportReasonSpam:
    case TLValue::InputReportReasonViolence:
    case TLValue::InputReportReasonPornography:
    case TLValue::InputReportReasonChildAbuse:
    case TLValue::InputReportReasonOther:
    case TLValue::InputReportReasonCopyright:
        return true;
    default:
        return false;
    }
}

bool TLReportReason::operator==(const TLReportReason &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputReportReasonSpam:
    case TLValue::InputReportReasonViolence:
    case TLValue::InputReportReasonPornography:
    case TLValue::InputReportReasonChildAbuse:
    case TLValue::InputReportReasonCopyright:
        return true;
    case TLValue::InputReportReasonOther:
        return text == v.text;
    default:
        return false;
    }
}

bool TLResPQ::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ResPQ:
        return true;
    default:
        return false;
    }
}

bool TLResPQ::operator==(const TLResPQ &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ResPQ:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && pq == v.pq
                && serverPublicKeyFingerprints == v.serverPublicKeyFingerprints
                ;
    default:
        return false;
    }
}

bool TLRichText::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::TextEmpty:
    case TLValue::TextPlain:
    case TLValue::TextBold:
    case TLValue::TextItalic:
    case TLValue::TextUnderline:
    case TLValue::TextStrike:
    case TLValue::TextFixed:
    case TLValue::TextUrl:
    case TLValue::TextEmail:
    case TLValue::TextConcat:
    case TLValue::TextSubscript:
    case TLValue::TextSuperscript:
    case TLValue::TextMarked:
    case TLValue::TextPhone:
    case TLValue::TextImage:
    case TLValue::TextAnchor:
        return true;
    default:
        return false;
    }
}

bool TLRichText::operator==(const TLRichText &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::TextEmpty:
        return true;
    case TLValue::TextPlain:
        return stringText == v.stringText;
    case TLValue::TextBold:
    case TLValue::TextItalic:
    case TLValue::TextUnderline:
    case TLValue::TextStrike:
    case TLValue::TextFixed:
    case TLValue::TextSubscript:
    case TLValue::TextSuperscript:
    case TLValue::TextMarked:
        return richText == v.richText;
    case TLValue::TextUrl:
        return true
                && richText == v.richText
                && url == v.url
                && webpageId == v.webpageId
                ;
    case TLValue::TextEmail:
        return true
                && richText == v.richText
                && email == v.email
                ;
    case TLValue::TextConcat:
        return texts == v.texts;
    case TLValue::TextPhone:
        return true
                && richText == v.richText
                && phone == v.phone
                ;
    case TLValue::TextImage:
        return true
                && documentId == v.documentId
                && w == v.w
                && h == v.h
                ;
    case TLValue::TextAnchor:
        return true
                && richText == v.richText
                && name == v.name
                ;
    default:
        return false;
    }
}

bool TLRpcDropAnswer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::RpcAnswerUnknown:
    case TLValue::RpcAnswerDroppedRunning:
    case TLValue::RpcAnswerDropped:
        return true;
    default:
        return false;
    }
}

bool TLRpcDropAnswer::operator==(const TLRpcDropAnswer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::RpcAnswerUnknown:
    case TLValue::RpcAnswerDroppedRunning:
        return true;
    case TLValue::RpcAnswerDropped:
        return true
                && msgId == v.msgId
                && seqNo == v.seqNo
                && bytes == v.bytes
                ;
    default:
        return false;
    }
}

bool TLRpcError::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::RpcError:
        return true;
    default:
        return false;
    }
}

bool TLRpcError::operator==(const TLRpcError &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::RpcError:
        return true
                && errorCode == v.errorCode
                && errorMessage == v.errorMessage
                ;
    default:
        return false;
    }
}

bool TLSavedContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SavedPhoneContact:
        return true;
    default:
        return false;
    }
}

bool TLSavedContact::operator==(const TLSavedContact &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SavedPhoneContact:
        return true
                && phone == v.phone
                && firstName == v.firstName
                && lastName == v.lastName
                && date == v.date
                ;
    default:
        return false;
    }
}

bool TLSecureCredentialsEncrypted::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureCredentialsEncrypted:
        return true;
    default:
        return false;
    }
}

bool TLSecureCredentialsEncrypted::operator==(const TLSecureCredentialsEncrypted &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureCredentialsEncrypted:
        return true
                && data == v.data
                && hash == v.hash
                && secret == v.secret
                ;
    default:
        return false;
    }
}

bool TLSecureData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureData:
        return true;
    default:
        return false;
    }
}

bool TLSecureData::operator==(const TLSecureData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureData:
        return true
                && data == v.data
                && dataHash == v.dataHash
                && secret == v.secret
                ;
    default:
        return false;
    }
}

bool TLSecureFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureFileEmpty:
    case TLValue::SecureFile:
        return true;
    default:
        return false;
    }
}

bool TLSecureFile::operator==(const TLSecureFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureFileEmpty:
        return true;
    case TLValue::SecureFile:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && size == v.size
                && dcId == v.dcId
                && date == v.date
                && fileHash == v.fileHash
                && secret == v.secret
                ;
    default:
        return false;
    }
}

bool TLSecurePasswordKdfAlgo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecurePasswordKdfAlgoUnknown:
    case TLValue::SecurePasswordKdfAlgoPBKDF2HMACSHA512iter100000:
    case TLValue::SecurePasswordKdfAlgoSHA512:
        return true;
    default:
        return false;
    }
}

bool TLSecurePasswordKdfAlgo::operator==(const TLSecurePasswordKdfAlgo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecurePasswordKdfAlgoUnknown:
        return true;
    case TLValue::SecurePasswordKdfAlgoPBKDF2HMACSHA512iter100000:
    case TLValue::SecurePasswordKdfAlgoSHA512:
        return salt == v.salt;
    default:
        return false;
    }
}

bool TLSecurePlainData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecurePlainPhone:
    case TLValue::SecurePlainEmail:
        return true;
    default:
        return false;
    }
}

bool TLSecurePlainData::operator==(const TLSecurePlainData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecurePlainPhone:
        return phone == v.phone;
    case TLValue::SecurePlainEmail:
        return email == v.email;
    default:
        return false;
    }
}

bool TLSecureSecretSettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureSecretSettings:
        return true;
    default:
        return false;
    }
}

bool TLSecureSecretSettings::operator==(const TLSecureSecretSettings &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureSecretSettings:
        return true
                && secureAlgo == v.secureAlgo
                && secureSecret == v.secureSecret
                && secureSecretId == v.secureSecretId
                ;
    default:
        return false;
    }
}

bool TLSecureValueType::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureValueTypePersonalDetails:
    case TLValue::SecureValueTypePassport:
    case TLValue::SecureValueTypeDriverLicense:
    case TLValue::SecureValueTypeIdentityCard:
    case TLValue::SecureValueTypeInternalPassport:
    case TLValue::SecureValueTypeAddress:
    case TLValue::SecureValueTypeUtilityBill:
    case TLValue::SecureValueTypeBankStatement:
    case TLValue::SecureValueTypeRentalAgreement:
    case TLValue::SecureValueTypePassportRegistration:
    case TLValue::SecureValueTypeTemporaryRegistration:
    case TLValue::SecureValueTypePhone:
    case TLValue::SecureValueTypeEmail:
        return true;
    default:
        return false;
    }
}

bool TLSecureValueType::operator==(const TLSecureValueType &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureValueTypePersonalDetails:
    case TLValue::SecureValueTypePassport:
    case TLValue::SecureValueTypeDriverLicense:
    case TLValue::SecureValueTypeIdentityCard:
    case TLValue::SecureValueTypeInternalPassport:
    case TLValue::SecureValueTypeAddress:
    case TLValue::SecureValueTypeUtilityBill:
    case TLValue::SecureValueTypeBankStatement:
    case TLValue::SecureValueTypeRentalAgreement:
    case TLValue::SecureValueTypePassportRegistration:
    case TLValue::SecureValueTypeTemporaryRegistration:
    case TLValue::SecureValueTypePhone:
    case TLValue::SecureValueTypeEmail:
        return true;
    default:
        return false;
    }
}

bool TLSendMessageAction::hasType(const quint32 value)
{
    switch (value) {
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
    case TLValue::SendMessageGamePlayAction:
    case TLValue::SendMessageRecordRoundAction:
    case TLValue::SendMessageUploadRoundAction:
        return true;
    default:
        return false;
    }
}

bool TLSendMessageAction::operator==(const TLSendMessageAction &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SendMessageTypingAction:
    case TLValue::SendMessageCancelAction:
    case TLValue::SendMessageRecordVideoAction:
    case TLValue::SendMessageRecordAudioAction:
    case TLValue::SendMessageGeoLocationAction:
    case TLValue::SendMessageChooseContactAction:
    case TLValue::SendMessageGamePlayAction:
    case TLValue::SendMessageRecordRoundAction:
        return true;
    case TLValue::SendMessageUploadVideoAction:
    case TLValue::SendMessageUploadAudioAction:
    case TLValue::SendMessageUploadPhotoAction:
    case TLValue::SendMessageUploadDocumentAction:
    case TLValue::SendMessageUploadRoundAction:
        return progress == v.progress;
    default:
        return false;
    }
}

bool TLServerDHInnerData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ServerDHInnerData:
        return true;
    default:
        return false;
    }
}

bool TLServerDHInnerData::operator==(const TLServerDHInnerData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ServerDHInnerData:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && g == v.g
                && dhPrime == v.dhPrime
                && gA == v.gA
                && serverTime == v.serverTime
                ;
    default:
        return false;
    }
}

bool TLServerDHParams::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ServerDHParamsFail:
    case TLValue::ServerDHParamsOk:
        return true;
    default:
        return false;
    }
}

bool TLServerDHParams::operator==(const TLServerDHParams &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ServerDHParamsFail:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonceHash == v.newNonceHash
                ;
    case TLValue::ServerDHParamsOk:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && encryptedAnswer == v.encryptedAnswer
                ;
    default:
        return false;
    }
}

bool TLSetClientDHParamsAnswer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DhGenOk:
    case TLValue::DhGenRetry:
    case TLValue::DhGenFail:
        return true;
    default:
        return false;
    }
}

bool TLSetClientDHParamsAnswer::operator==(const TLSetClientDHParamsAnswer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DhGenOk:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonceHash1 == v.newNonceHash1
                ;
    case TLValue::DhGenRetry:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonceHash2 == v.newNonceHash2
                ;
    case TLValue::DhGenFail:
        return true
                && nonce == v.nonce
                && serverNonce == v.serverNonce
                && newNonceHash3 == v.newNonceHash3
                ;
    default:
        return false;
    }
}

bool TLShippingOption::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ShippingOption:
        return true;
    default:
        return false;
    }
}

bool TLShippingOption::operator==(const TLShippingOption &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ShippingOption:
        return true
                && id == v.id
                && title == v.title
                && prices == v.prices
                ;
    default:
        return false;
    }
}

bool TLStatsURL::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::StatsURL:
        return true;
    default:
        return false;
    }
}

bool TLStatsURL::operator==(const TLStatsURL &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::StatsURL:
        return url == v.url;
    default:
        return false;
    }
}

bool TLStickerPack::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::StickerPack:
        return true;
    default:
        return false;
    }
}

bool TLStickerPack::operator==(const TLStickerPack &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::StickerPack:
        return true
                && emoticon == v.emoticon
                && documents == v.documents
                ;
    default:
        return false;
    }
}

bool TLStorageFileType::hasType(const quint32 value)
{
    switch (value) {
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
        return true;
    default:
        return false;
    }
}

bool TLStorageFileType::operator==(const TLStorageFileType &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
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
        return true;
    default:
        return false;
    }
}

bool TLTopPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::TopPeer:
        return true;
    default:
        return false;
    }
}

bool TLTopPeer::operator==(const TLTopPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::TopPeer:
        return true
                && peer == v.peer
                && rating == v.rating
                ;
    default:
        return false;
    }
}

bool TLTopPeerCategory::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::TopPeerCategoryBotsPM:
    case TLValue::TopPeerCategoryBotsInline:
    case TLValue::TopPeerCategoryCorrespondents:
    case TLValue::TopPeerCategoryGroups:
    case TLValue::TopPeerCategoryChannels:
    case TLValue::TopPeerCategoryPhoneCalls:
        return true;
    default:
        return false;
    }
}

bool TLTopPeerCategory::operator==(const TLTopPeerCategory &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::TopPeerCategoryBotsPM:
    case TLValue::TopPeerCategoryBotsInline:
    case TLValue::TopPeerCategoryCorrespondents:
    case TLValue::TopPeerCategoryGroups:
    case TLValue::TopPeerCategoryChannels:
    case TLValue::TopPeerCategoryPhoneCalls:
        return true;
    default:
        return false;
    }
}

bool TLTopPeerCategoryPeers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::TopPeerCategoryPeers:
        return true;
    default:
        return false;
    }
}

bool TLTopPeerCategoryPeers::operator==(const TLTopPeerCategoryPeers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::TopPeerCategoryPeers:
        return true
                && category == v.category
                && count == v.count
                && peers == v.peers
                ;
    default:
        return false;
    }
}

bool TLUpdatesState::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UpdatesState:
        return true;
    default:
        return false;
    }
}

bool TLUpdatesState::operator==(const TLUpdatesState &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UpdatesState:
        return true
                && pts == v.pts
                && qts == v.qts
                && date == v.date
                && seq == v.seq
                && unreadCount == v.unreadCount
                ;
    default:
        return false;
    }
}

bool TLUploadCdnFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UploadCdnFileReuploadNeeded:
    case TLValue::UploadCdnFile:
        return true;
    default:
        return false;
    }
}

bool TLUploadCdnFile::operator==(const TLUploadCdnFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UploadCdnFileReuploadNeeded:
        return requestToken == v.requestToken;
    case TLValue::UploadCdnFile:
        return bytes == v.bytes;
    default:
        return false;
    }
}

bool TLUploadFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UploadFile:
    case TLValue::UploadFileCdnRedirect:
        return true;
    default:
        return false;
    }
}

bool TLUploadFile::operator==(const TLUploadFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UploadFile:
        return true
                && type == v.type
                && mtime == v.mtime
                && bytes == v.bytes
                ;
    case TLValue::UploadFileCdnRedirect:
        return true
                && dcId == v.dcId
                && fileToken == v.fileToken
                && encryptionKey == v.encryptionKey
                && encryptionIv == v.encryptionIv
                && fileHashes == v.fileHashes
                ;
    default:
        return false;
    }
}

bool TLUploadWebFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UploadWebFile:
        return true;
    default:
        return false;
    }
}

bool TLUploadWebFile::operator==(const TLUploadWebFile &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UploadWebFile:
        return true
                && size == v.size
                && mimeType == v.mimeType
                && fileType == v.fileType
                && mtime == v.mtime
                && bytes == v.bytes
                ;
    default:
        return false;
    }
}

bool TLUserProfilePhoto::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UserProfilePhotoEmpty:
    case TLValue::UserProfilePhoto:
        return true;
    default:
        return false;
    }
}

bool TLUserProfilePhoto::operator==(const TLUserProfilePhoto &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UserProfilePhotoEmpty:
        return true;
    case TLValue::UserProfilePhoto:
        return true
                && photoId == v.photoId
                && photoSmall == v.photoSmall
                && photoBig == v.photoBig
                ;
    default:
        return false;
    }
}

bool TLUserStatus::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UserStatusEmpty:
    case TLValue::UserStatusOnline:
    case TLValue::UserStatusOffline:
    case TLValue::UserStatusRecently:
    case TLValue::UserStatusLastWeek:
    case TLValue::UserStatusLastMonth:
        return true;
    default:
        return false;
    }
}

bool TLUserStatus::operator==(const TLUserStatus &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UserStatusEmpty:
    case TLValue::UserStatusRecently:
    case TLValue::UserStatusLastWeek:
    case TLValue::UserStatusLastMonth:
        return true;
    case TLValue::UserStatusOnline:
        return expires == v.expires;
    case TLValue::UserStatusOffline:
        return wasOnline == v.wasOnline;
    default:
        return false;
    }
}

bool TLWallPaper::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::WallPaper:
    case TLValue::WallPaperSolid:
        return true;
    default:
        return false;
    }
}

bool TLWallPaper::operator==(const TLWallPaper &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::WallPaper:
        return true
                && id == v.id
                && title == v.title
                && sizes == v.sizes
                && color == v.color
                ;
    case TLValue::WallPaperSolid:
        return true
                && id == v.id
                && title == v.title
                && bgColor == v.bgColor
                && color == v.color
                ;
    default:
        return false;
    }
}

bool TLWebAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::WebAuthorization:
        return true;
    default:
        return false;
    }
}

bool TLWebAuthorization::operator==(const TLWebAuthorization &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::WebAuthorization:
        return true
                && hash == v.hash
                && botId == v.botId
                && domain == v.domain
                && browser == v.browser
                && platform == v.platform
                && dateCreated == v.dateCreated
                && dateActive == v.dateActive
                && ip == v.ip
                && region == v.region
                ;
    default:
        return false;
    }
}

bool TLAccessPointRule::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccessPointRule:
        return true;
    default:
        return false;
    }
}

bool TLAccessPointRule::operator==(const TLAccessPointRule &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccessPointRule:
        return true
                && phonePrefixRules == v.phonePrefixRules
                && dcId == v.dcId
                && ips == v.ips
                ;
    default:
        return false;
    }
}

bool TLAccountPassword::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountPassword:
        return true;
    default:
        return false;
    }
}

bool TLAccountPassword::operator==(const TLAccountPassword &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountPassword:
        return true
                && flags == v.flags
                && currentAlgo == v.currentAlgo
                && srpB == v.srpB
                && srpId == v.srpId
                && hint == v.hint
                && emailUnconfirmedPattern == v.emailUnconfirmedPattern
                && newAlgo == v.newAlgo
                && newSecureAlgo == v.newSecureAlgo
                && secureRandom == v.secureRandom
                ;
    default:
        return false;
    }
}

bool TLAccountPasswordInputSettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountPasswordInputSettings:
        return true;
    default:
        return false;
    }
}

bool TLAccountPasswordInputSettings::operator==(const TLAccountPasswordInputSettings &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountPasswordInputSettings:
        return true
                && flags == v.flags
                && newAlgo == v.newAlgo
                && newPasswordHash == v.newPasswordHash
                && hint == v.hint
                && email == v.email
                && newSecureSettings == v.newSecureSettings
                ;
    default:
        return false;
    }
}

bool TLAccountPasswordSettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountPasswordSettings:
        return true;
    default:
        return false;
    }
}

bool TLAccountPasswordSettings::operator==(const TLAccountPasswordSettings &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountPasswordSettings:
        return true
                && flags == v.flags
                && email == v.email
                && secureSettings == v.secureSettings
                ;
    default:
        return false;
    }
}

bool TLAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Authorization:
        return true;
    default:
        return false;
    }
}

bool TLAuthorization::operator==(const TLAuthorization &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Authorization:
        return true
                && flags == v.flags
                && hash == v.hash
                && deviceModel == v.deviceModel
                && platform == v.platform
                && systemVersion == v.systemVersion
                && apiId == v.apiId
                && appName == v.appName
                && appVersion == v.appVersion
                && dateCreated == v.dateCreated
                && dateActive == v.dateActive
                && ip == v.ip
                && country == v.country
                && region == v.region
                ;
    default:
        return false;
    }
}

bool TLCdnConfig::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::CdnConfig:
        return true;
    default:
        return false;
    }
}

bool TLCdnConfig::operator==(const TLCdnConfig &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::CdnConfig:
        return publicKeys == v.publicKeys;
    default:
        return false;
    }
}

bool TLChannelAdminLogEventsFilter::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelAdminLogEventsFilter:
        return true;
    default:
        return false;
    }
}

bool TLChannelAdminLogEventsFilter::operator==(const TLChannelAdminLogEventsFilter &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelAdminLogEventsFilter:
        return true
                && flags == v.flags
                ;
    default:
        return false;
    }
}

bool TLChannelAdminRights::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelAdminRights:
        return true;
    default:
        return false;
    }
}

bool TLChannelAdminRights::operator==(const TLChannelAdminRights &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelAdminRights:
        return true
                && flags == v.flags
                ;
    default:
        return false;
    }
}

bool TLChannelBannedRights::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelBannedRights:
        return true;
    default:
        return false;
    }
}

bool TLChannelBannedRights::operator==(const TLChannelBannedRights &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelBannedRights:
        return true
                && flags == v.flags
                && untilDate == v.untilDate
                ;
    default:
        return false;
    }
}

bool TLChannelMessagesFilter::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelMessagesFilterEmpty:
    case TLValue::ChannelMessagesFilter:
        return true;
    default:
        return false;
    }
}

bool TLChannelMessagesFilter::operator==(const TLChannelMessagesFilter &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelMessagesFilterEmpty:
        return true;
    case TLValue::ChannelMessagesFilter:
        return true
                && flags == v.flags
                && ranges == v.ranges
                ;
    default:
        return false;
    }
}

bool TLChannelParticipant::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelParticipant:
    case TLValue::ChannelParticipantSelf:
    case TLValue::ChannelParticipantCreator:
    case TLValue::ChannelParticipantAdmin:
    case TLValue::ChannelParticipantBanned:
        return true;
    default:
        return false;
    }
}

bool TLChannelParticipant::operator==(const TLChannelParticipant &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelParticipant:
        return true
                && userId == v.userId
                && date == v.date
                ;
    case TLValue::ChannelParticipantSelf:
        return true
                && userId == v.userId
                && inviterId == v.inviterId
                && date == v.date
                ;
    case TLValue::ChannelParticipantCreator:
        return userId == v.userId;
    case TLValue::ChannelParticipantAdmin:
        return true
                && flags == v.flags
                && userId == v.userId
                && inviterId == v.inviterId
                && promotedBy == v.promotedBy
                && date == v.date
                && adminRights == v.adminRights
                ;
    case TLValue::ChannelParticipantBanned:
        return true
                && flags == v.flags
                && userId == v.userId
                && kickedBy == v.kickedBy
                && date == v.date
                && bannedRights == v.bannedRights
                ;
    default:
        return false;
    }
}

bool TLChatPhoto::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatPhotoEmpty:
    case TLValue::ChatPhoto:
        return true;
    default:
        return false;
    }
}

bool TLChatPhoto::operator==(const TLChatPhoto &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatPhotoEmpty:
        return true;
    case TLValue::ChatPhoto:
        return true
                && photoSmall == v.photoSmall
                && photoBig == v.photoBig
                ;
    default:
        return false;
    }
}

bool TLContactStatus::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactStatus:
        return true;
    default:
        return false;
    }
}

bool TLContactStatus::operator==(const TLContactStatus &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactStatus:
        return true
                && userId == v.userId
                && status == v.status
                ;
    default:
        return false;
    }
}

bool TLDcOption::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DcOption:
        return true;
    default:
        return false;
    }
}

bool TLDcOption::operator==(const TLDcOption &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DcOption:
        return true
                && flags == v.flags
                && id == v.id
                && ipAddress == v.ipAddress
                && port == v.port
                && secret == v.secret
                ;
    default:
        return false;
    }
}

bool TLDialogPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DialogPeer:
        return true;
    default:
        return false;
    }
}

bool TLDialogPeer::operator==(const TLDialogPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DialogPeer:
        return peer == v.peer;
    default:
        return false;
    }
}

bool TLDocumentAttribute::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DocumentAttributeImageSize:
    case TLValue::DocumentAttributeAnimated:
    case TLValue::DocumentAttributeSticker:
    case TLValue::DocumentAttributeVideo:
    case TLValue::DocumentAttributeAudio:
    case TLValue::DocumentAttributeFilename:
    case TLValue::DocumentAttributeHasStickers:
        return true;
    default:
        return false;
    }
}

bool TLDocumentAttribute::operator==(const TLDocumentAttribute &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DocumentAttributeImageSize:
        return true
                && w == v.w
                && h == v.h
                ;
    case TLValue::DocumentAttributeAnimated:
    case TLValue::DocumentAttributeHasStickers:
        return true;
    case TLValue::DocumentAttributeSticker:
        return true
                && flags == v.flags
                && alt == v.alt
                && stickerset == v.stickerset
                && maskCoords == v.maskCoords
                ;
    case TLValue::DocumentAttributeVideo:
        return true
                && flags == v.flags
                && duration == v.duration
                && w == v.w
                && h == v.h
                ;
    case TLValue::DocumentAttributeAudio:
        return true
                && flags == v.flags
                && duration == v.duration
                && title == v.title
                && performer == v.performer
                && waveform == v.waveform
                ;
    case TLValue::DocumentAttributeFilename:
        return fileName == v.fileName;
    default:
        return false;
    }
}

bool TLDraftMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DraftMessageEmpty:
    case TLValue::DraftMessage:
        return true;
    default:
        return false;
    }
}

bool TLDraftMessage::operator==(const TLDraftMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DraftMessageEmpty:
        return true
                && flags == v.flags
                && date == v.date
                ;
    case TLValue::DraftMessage:
        return true
                && flags == v.flags
                && replyToMsgId == v.replyToMsgId
                && message == v.message
                && entities == v.entities
                && date == v.date
                ;
    default:
        return false;
    }
}

bool TLHelpConfigSimple::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpConfigSimple:
        return true;
    default:
        return false;
    }
}

bool TLHelpConfigSimple::operator==(const TLHelpConfigSimple &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpConfigSimple:
        return true
                && date == v.date
                && expires == v.expires
                && rules == v.rules
                ;
    default:
        return false;
    }
}

bool TLHelpDeepLinkInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpDeepLinkInfoEmpty:
    case TLValue::HelpDeepLinkInfo:
        return true;
    default:
        return false;
    }
}

bool TLHelpDeepLinkInfo::operator==(const TLHelpDeepLinkInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpDeepLinkInfoEmpty:
        return true;
    case TLValue::HelpDeepLinkInfo:
        return true
                && flags == v.flags
                && message == v.message
                && entities == v.entities
                ;
    default:
        return false;
    }
}

bool TLHelpTermsOfService::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpTermsOfService:
        return true;
    default:
        return false;
    }
}

bool TLHelpTermsOfService::operator==(const TLHelpTermsOfService &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpTermsOfService:
        return true
                && flags == v.flags
                && id == v.id
                && text == v.text
                && entities == v.entities
                && minAgeConfirm == v.minAgeConfirm
                ;
    default:
        return false;
    }
}

bool TLHelpTermsOfServiceUpdate::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpTermsOfServiceUpdateEmpty:
    case TLValue::HelpTermsOfServiceUpdate:
        return true;
    default:
        return false;
    }
}

bool TLHelpTermsOfServiceUpdate::operator==(const TLHelpTermsOfServiceUpdate &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpTermsOfServiceUpdateEmpty:
        return expires == v.expires;
    case TLValue::HelpTermsOfServiceUpdate:
        return true
                && expires == v.expires
                && termsOfService == v.termsOfService
                ;
    default:
        return false;
    }
}

bool TLHelpUserInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpUserInfoEmpty:
    case TLValue::HelpUserInfo:
        return true;
    default:
        return false;
    }
}

bool TLHelpUserInfo::operator==(const TLHelpUserInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpUserInfoEmpty:
        return true;
    case TLValue::HelpUserInfo:
        return true
                && message == v.message
                && entities == v.entities
                && author == v.author
                && date == v.date
                ;
    default:
        return false;
    }
}

bool TLInputChatPhoto::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputChatPhotoEmpty:
    case TLValue::InputChatUploadedPhoto:
    case TLValue::InputChatPhoto:
        return true;
    default:
        return false;
    }
}

bool TLInputChatPhoto::operator==(const TLInputChatPhoto &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputChatPhotoEmpty:
        return true;
    case TLValue::InputChatUploadedPhoto:
        return file == v.file;
    case TLValue::InputChatPhoto:
        return id == v.id;
    default:
        return false;
    }
}

bool TLInputDialogPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputDialogPeer:
        return true;
    default:
        return false;
    }
}

bool TLInputDialogPeer::operator==(const TLInputDialogPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputDialogPeer:
        return peer == v.peer;
    default:
        return false;
    }
}

bool TLInputGame::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputGameID:
    case TLValue::InputGameShortName:
        return true;
    default:
        return false;
    }
}

bool TLInputGame::operator==(const TLInputGame &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputGameID:
        return true
                && id == v.id
                && accessHash == v.accessHash
                ;
    case TLValue::InputGameShortName:
        return true
                && botId == v.botId
                && shortName == v.shortName
                ;
    default:
        return false;
    }
}

bool TLInputNotifyPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputNotifyPeer:
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyBroadcasts:
        return true;
    default:
        return false;
    }
}

bool TLInputNotifyPeer::operator==(const TLInputNotifyPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputNotifyPeer:
        return peer == v.peer;
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyBroadcasts:
        return true;
    default:
        return false;
    }
}

bool TLInputPaymentCredentials::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPaymentCredentialsSaved:
    case TLValue::InputPaymentCredentials:
    case TLValue::InputPaymentCredentialsApplePay:
    case TLValue::InputPaymentCredentialsAndroidPay:
        return true;
    default:
        return false;
    }
}

bool TLInputPaymentCredentials::operator==(const TLInputPaymentCredentials &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPaymentCredentialsSaved:
        return true
                && id == v.id
                && tmpPassword == v.tmpPassword
                ;
    case TLValue::InputPaymentCredentials:
        return true
                && flags == v.flags
                && data == v.data
                ;
    case TLValue::InputPaymentCredentialsApplePay:
        return paymentData == v.paymentData;
    case TLValue::InputPaymentCredentialsAndroidPay:
        return true
                && paymentToken == v.paymentToken
                && googleTransactionId == v.googleTransactionId
                ;
    default:
        return false;
    }
}

bool TLInputPrivacyRule::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPrivacyValueAllowContacts:
    case TLValue::InputPrivacyValueAllowAll:
    case TLValue::InputPrivacyValueAllowUsers:
    case TLValue::InputPrivacyValueDisallowContacts:
    case TLValue::InputPrivacyValueDisallowAll:
    case TLValue::InputPrivacyValueDisallowUsers:
        return true;
    default:
        return false;
    }
}

bool TLInputPrivacyRule::operator==(const TLInputPrivacyRule &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
    case TLValue::InputPrivacyValueAllowAll:
    case TLValue::InputPrivacyValueDisallowContacts:
    case TLValue::InputPrivacyValueDisallowAll:
        return true;
    case TLValue::InputPrivacyValueAllowUsers:
    case TLValue::InputPrivacyValueDisallowUsers:
        return users == v.users;
    default:
        return false;
    }
}

bool TLInputSecureValue::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputSecureValue:
        return true;
    default:
        return false;
    }
}

bool TLInputSecureValue::operator==(const TLInputSecureValue &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputSecureValue:
        return true
                && flags == v.flags
                && type == v.type
                && data == v.data
                && frontSide == v.frontSide
                && reverseSide == v.reverseSide
                && selfie == v.selfie
                && translation == v.translation
                && files == v.files
                && plainData == v.plainData
                ;
    default:
        return false;
    }
}

bool TLInputStickerSetItem::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputStickerSetItem:
        return true;
    default:
        return false;
    }
}

bool TLInputStickerSetItem::operator==(const TLInputStickerSetItem &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputStickerSetItem:
        return true
                && flags == v.flags
                && document == v.document
                && emoji == v.emoji
                && maskCoords == v.maskCoords
                ;
    default:
        return false;
    }
}

bool TLInputWebDocument::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputWebDocument:
        return true;
    default:
        return false;
    }
}

bool TLInputWebDocument::operator==(const TLInputWebDocument &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputWebDocument:
        return true
                && url == v.url
                && size == v.size
                && mimeType == v.mimeType
                && attributes == v.attributes
                ;
    default:
        return false;
    }
}

bool TLInvoice::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Invoice:
        return true;
    default:
        return false;
    }
}

bool TLInvoice::operator==(const TLInvoice &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Invoice:
        return true
                && flags == v.flags
                && currency == v.currency
                && prices == v.prices
                ;
    default:
        return false;
    }
}

bool TLKeyboardButton::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::KeyboardButton:
    case TLValue::KeyboardButtonUrl:
    case TLValue::KeyboardButtonCallback:
    case TLValue::KeyboardButtonRequestPhone:
    case TLValue::KeyboardButtonRequestGeoLocation:
    case TLValue::KeyboardButtonSwitchInline:
    case TLValue::KeyboardButtonGame:
    case TLValue::KeyboardButtonBuy:
        return true;
    default:
        return false;
    }
}

bool TLKeyboardButton::operator==(const TLKeyboardButton &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::KeyboardButton:
    case TLValue::KeyboardButtonRequestPhone:
    case TLValue::KeyboardButtonRequestGeoLocation:
    case TLValue::KeyboardButtonGame:
    case TLValue::KeyboardButtonBuy:
        return text == v.text;
    case TLValue::KeyboardButtonUrl:
        return true
                && text == v.text
                && url == v.url
                ;
    case TLValue::KeyboardButtonCallback:
        return true
                && text == v.text
                && data == v.data
                ;
    case TLValue::KeyboardButtonSwitchInline:
        return true
                && flags == v.flags
                && text == v.text
                && query == v.query
                ;
    default:
        return false;
    }
}

bool TLKeyboardButtonRow::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::KeyboardButtonRow:
        return true;
    default:
        return false;
    }
}

bool TLKeyboardButtonRow::operator==(const TLKeyboardButtonRow &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::KeyboardButtonRow:
        return buttons == v.buttons;
    default:
        return false;
    }
}

bool TLLangPackDifference::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::LangPackDifference:
        return true;
    default:
        return false;
    }
}

bool TLLangPackDifference::operator==(const TLLangPackDifference &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::LangPackDifference:
        return true
                && langCode == v.langCode
                && fromVersion == v.fromVersion
                && version == v.version
                && strings == v.strings
                ;
    default:
        return false;
    }
}

bool TLLangPackLanguage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::LangPackLanguage:
        return true;
    default:
        return false;
    }
}

bool TLLangPackLanguage::operator==(const TLLangPackLanguage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::LangPackLanguage:
        return true
                && flags == v.flags
                && name == v.name
                && nativeName == v.nativeName
                && langCode == v.langCode
                && baseLangCode == v.baseLangCode
                && pluralCode == v.pluralCode
                && stringsCount == v.stringsCount
                && translatedCount == v.translatedCount
                && translationsUrl == v.translationsUrl
                ;
    default:
        return false;
    }
}

bool TLMessageFwdHeader::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessageFwdHeader:
        return true;
    default:
        return false;
    }
}

bool TLMessageFwdHeader::operator==(const TLMessageFwdHeader &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessageFwdHeader:
        return true
                && flags == v.flags
                && fromId == v.fromId
                && date == v.date
                && channelId == v.channelId
                && channelPost == v.channelPost
                && postAuthor == v.postAuthor
                && savedFromPeer == v.savedFromPeer
                && savedFromMsgId == v.savedFromMsgId
                ;
    default:
        return false;
    }
}

bool TLMessagesBotCallbackAnswer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesBotCallbackAnswer:
        return true;
    default:
        return false;
    }
}

bool TLMessagesBotCallbackAnswer::operator==(const TLMessagesBotCallbackAnswer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesBotCallbackAnswer:
        return true
                && flags == v.flags
                && message == v.message
                && url == v.url
                && cacheTime == v.cacheTime
                ;
    default:
        return false;
    }
}

bool TLMessagesFilter::hasType(const quint32 value)
{
    switch (value) {
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
    case TLValue::InputMessagesFilterPhoneCalls:
    case TLValue::InputMessagesFilterRoundVoice:
    case TLValue::InputMessagesFilterRoundVideo:
    case TLValue::InputMessagesFilterMyMentions:
    case TLValue::InputMessagesFilterGeo:
    case TLValue::InputMessagesFilterContacts:
        return true;
    default:
        return false;
    }
}

bool TLMessagesFilter::operator==(const TLMessagesFilter &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
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
        return true;
    case TLValue::InputMessagesFilterPhoneCalls:
        return true
                && flags == v.flags
                ;
    default:
        return false;
    }
}

bool TLMessagesMessageEditData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesMessageEditData:
        return true;
    default:
        return false;
    }
}

bool TLMessagesMessageEditData::operator==(const TLMessagesMessageEditData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesMessageEditData:
        return true
                && flags == v.flags
                ;
    default:
        return false;
    }
}

bool TLNotifyPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::NotifyPeer:
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyBroadcasts:
        return true;
    default:
        return false;
    }
}

bool TLNotifyPeer::operator==(const TLNotifyPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::NotifyPeer:
        return peer == v.peer;
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyBroadcasts:
        return true;
    default:
        return false;
    }
}

bool TLPageTableCell::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageTableCell:
        return true;
    default:
        return false;
    }
}

bool TLPageTableCell::operator==(const TLPageTableCell &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageTableCell:
        return true
                && flags == v.flags
                && text == v.text
                && colspan == v.colspan
                && rowspan == v.rowspan
                ;
    default:
        return false;
    }
}

bool TLPageTableRow::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageTableRow:
        return true;
    default:
        return false;
    }
}

bool TLPageTableRow::operator==(const TLPageTableRow &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageTableRow:
        return cells == v.cells;
    default:
        return false;
    }
}

bool TLPaymentRequestedInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentRequestedInfo:
        return true;
    default:
        return false;
    }
}

bool TLPaymentRequestedInfo::operator==(const TLPaymentRequestedInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentRequestedInfo:
        return true
                && flags == v.flags
                && name == v.name
                && phone == v.phone
                && email == v.email
                && shippingAddress == v.shippingAddress
                ;
    default:
        return false;
    }
}

bool TLPaymentsSavedInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsSavedInfo:
        return true;
    default:
        return false;
    }
}

bool TLPaymentsSavedInfo::operator==(const TLPaymentsSavedInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentsSavedInfo:
        return true
                && flags == v.flags
                && savedInfo == v.savedInfo
                ;
    default:
        return false;
    }
}

bool TLPaymentsValidatedRequestedInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsValidatedRequestedInfo:
        return true;
    default:
        return false;
    }
}

bool TLPaymentsValidatedRequestedInfo::operator==(const TLPaymentsValidatedRequestedInfo &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentsValidatedRequestedInfo:
        return true
                && flags == v.flags
                && id == v.id
                && shippingOptions == v.shippingOptions
                ;
    default:
        return false;
    }
}

bool TLPeerSettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PeerSettings:
        return true;
    default:
        return false;
    }
}

bool TLPeerSettings::operator==(const TLPeerSettings &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PeerSettings:
        return true
                && flags == v.flags
                ;
    default:
        return false;
    }
}

bool TLPhoneCallProtocol::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhoneCallProtocol:
        return true;
    default:
        return false;
    }
}

bool TLPhoneCallProtocol::operator==(const TLPhoneCallProtocol &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhoneCallProtocol:
        return true
                && flags == v.flags
                && minLayer == v.minLayer
                && maxLayer == v.maxLayer
                ;
    default:
        return false;
    }
}

bool TLPhoto::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhotoEmpty:
    case TLValue::Photo:
        return true;
    default:
        return false;
    }
}

bool TLPhoto::operator==(const TLPhoto &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhotoEmpty:
        return id == v.id;
    case TLValue::Photo:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && fileReference == v.fileReference
                && date == v.date
                && sizes == v.sizes
                ;
    default:
        return false;
    }
}

bool TLPoll::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Poll:
        return true;
    default:
        return false;
    }
}

bool TLPoll::operator==(const TLPoll &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Poll:
        return true
                && id == v.id
                && flags == v.flags
                && question == v.question
                && answers == v.answers
                ;
    default:
        return false;
    }
}

bool TLPollAnswerVoters::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PollAnswerVoters:
        return true;
    default:
        return false;
    }
}

bool TLPollAnswerVoters::operator==(const TLPollAnswerVoters &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PollAnswerVoters:
        return true
                && flags == v.flags
                && option == v.option
                && voters == v.voters
                ;
    default:
        return false;
    }
}

bool TLPollResults::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PollResults:
        return true;
    default:
        return false;
    }
}

bool TLPollResults::operator==(const TLPollResults &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PollResults:
        return true
                && flags == v.flags
                && results == v.results
                && totalVoters == v.totalVoters
                ;
    default:
        return false;
    }
}

bool TLReplyMarkup::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ReplyKeyboardHide:
    case TLValue::ReplyKeyboardForceReply:
    case TLValue::ReplyKeyboardMarkup:
    case TLValue::ReplyInlineMarkup:
        return true;
    default:
        return false;
    }
}

bool TLReplyMarkup::operator==(const TLReplyMarkup &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ReplyKeyboardHide:
    case TLValue::ReplyKeyboardForceReply:
        return true
                && flags == v.flags
                ;
    case TLValue::ReplyKeyboardMarkup:
        return true
                && flags == v.flags
                && rows == v.rows
                ;
    case TLValue::ReplyInlineMarkup:
        return rows == v.rows;
    default:
        return false;
    }
}

bool TLSecureRequiredType::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureRequiredType:
    case TLValue::SecureRequiredTypeOneOf:
        return true;
    default:
        return false;
    }
}

bool TLSecureRequiredType::operator==(const TLSecureRequiredType &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureRequiredType:
        return true
                && flags == v.flags
                && type == v.type
                ;
    case TLValue::SecureRequiredTypeOneOf:
        return types == v.types;
    default:
        return false;
    }
}

bool TLSecureValue::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureValue:
        return true;
    default:
        return false;
    }
}

bool TLSecureValue::operator==(const TLSecureValue &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureValue:
        return true
                && flags == v.flags
                && type == v.type
                && data == v.data
                && frontSide == v.frontSide
                && reverseSide == v.reverseSide
                && selfie == v.selfie
                && translation == v.translation
                && files == v.files
                && plainData == v.plainData
                && hash == v.hash
                ;
    default:
        return false;
    }
}

bool TLSecureValueError::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureValueErrorData:
    case TLValue::SecureValueErrorFrontSide:
    case TLValue::SecureValueErrorReverseSide:
    case TLValue::SecureValueErrorSelfie:
    case TLValue::SecureValueErrorFile:
    case TLValue::SecureValueErrorFiles:
    case TLValue::SecureValueError:
    case TLValue::SecureValueErrorTranslationFile:
    case TLValue::SecureValueErrorTranslationFiles:
        return true;
    default:
        return false;
    }
}

bool TLSecureValueError::operator==(const TLSecureValueError &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureValueErrorData:
        return true
                && type == v.type
                && dataHash == v.dataHash
                && field == v.field
                && text == v.text
                ;
    case TLValue::SecureValueErrorFrontSide:
    case TLValue::SecureValueErrorReverseSide:
    case TLValue::SecureValueErrorSelfie:
    case TLValue::SecureValueErrorFile:
    case TLValue::SecureValueErrorTranslationFile:
        return true
                && type == v.type
                && byteArrayFileHash == v.byteArrayFileHash
                && text == v.text
                ;
    case TLValue::SecureValueErrorFiles:
    case TLValue::SecureValueErrorTranslationFiles:
        return true
                && type == v.type
                && byteArrayFileHashVector == v.byteArrayFileHashVector
                && text == v.text
                ;
    case TLValue::SecureValueError:
        return true
                && type == v.type
                && hash == v.hash
                && text == v.text
                ;
    default:
        return false;
    }
}

bool TLSecureValueHash::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::SecureValueHash:
        return true;
    default:
        return false;
    }
}

bool TLSecureValueHash::operator==(const TLSecureValueHash &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::SecureValueHash:
        return true
                && type == v.type
                && hash == v.hash
                ;
    default:
        return false;
    }
}

bool TLStickerSet::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::StickerSet:
        return true;
    default:
        return false;
    }
}

bool TLStickerSet::operator==(const TLStickerSet &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::StickerSet:
        return true
                && flags == v.flags
                && installedDate == v.installedDate
                && id == v.id
                && accessHash == v.accessHash
                && title == v.title
                && shortName == v.shortName
                && count == v.count
                && hash == v.hash
                ;
    default:
        return false;
    }
}

bool TLUser::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UserEmpty:
    case TLValue::User:
        return true;
    default:
        return false;
    }
}

bool TLUser::operator==(const TLUser &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UserEmpty:
        return id == v.id;
    case TLValue::User:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && firstName == v.firstName
                && lastName == v.lastName
                && username == v.username
                && phone == v.phone
                && photo == v.photo
                && status == v.status
                && botInfoVersion == v.botInfoVersion
                && restrictionReason == v.restrictionReason
                && botInlinePlaceholder == v.botInlinePlaceholder
                && langCode == v.langCode
                ;
    default:
        return false;
    }
}

bool TLWebDocument::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::WebDocument:
    case TLValue::WebDocumentNoProxy:
        return true;
    default:
        return false;
    }
}

bool TLWebDocument::operator==(const TLWebDocument &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::WebDocument:
        return true
                && url == v.url
                && accessHash == v.accessHash
                && size == v.size
                && mimeType == v.mimeType
                && attributes == v.attributes
                ;
    case TLValue::WebDocumentNoProxy:
        return true
                && url == v.url
                && size == v.size
                && mimeType == v.mimeType
                && attributes == v.attributes
                ;
    default:
        return false;
    }
}

bool TLAccountAuthorizationForm::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountAuthorizationForm:
        return true;
    default:
        return false;
    }
}

bool TLAccountAuthorizationForm::operator==(const TLAccountAuthorizationForm &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountAuthorizationForm:
        return true
                && flags == v.flags
                && requiredTypes == v.requiredTypes
                && values == v.values
                && errors == v.errors
                && users == v.users
                && privacyPolicyUrl == v.privacyPolicyUrl
                ;
    default:
        return false;
    }
}

bool TLAccountAuthorizations::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountAuthorizations:
        return true;
    default:
        return false;
    }
}

bool TLAccountAuthorizations::operator==(const TLAccountAuthorizations &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountAuthorizations:
        return authorizations == v.authorizations;
    default:
        return false;
    }
}

bool TLAccountPrivacyRules::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountPrivacyRules:
        return true;
    default:
        return false;
    }
}

bool TLAccountPrivacyRules::operator==(const TLAccountPrivacyRules &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountPrivacyRules:
        return true
                && rules == v.rules
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLAccountWebAuthorizations::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountWebAuthorizations:
        return true;
    default:
        return false;
    }
}

bool TLAccountWebAuthorizations::operator==(const TLAccountWebAuthorizations &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AccountWebAuthorizations:
        return true
                && authorizations == v.authorizations
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLAuthAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthAuthorization:
        return true;
    default:
        return false;
    }
}

bool TLAuthAuthorization::operator==(const TLAuthAuthorization &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthAuthorization:
        return true
                && flags == v.flags
                && tmpSessions == v.tmpSessions
                && user == v.user
                ;
    default:
        return false;
    }
}

bool TLAuthSentCode::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthSentCode:
        return true;
    default:
        return false;
    }
}

bool TLAuthSentCode::operator==(const TLAuthSentCode &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::AuthSentCode:
        return true
                && flags == v.flags
                && type == v.type
                && phoneCodeHash == v.phoneCodeHash
                && nextType == v.nextType
                && timeout == v.timeout
                && termsOfService == v.termsOfService
                ;
    default:
        return false;
    }
}

bool TLBotInlineMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::BotInlineMessageMediaAuto:
    case TLValue::BotInlineMessageText:
    case TLValue::BotInlineMessageMediaGeo:
    case TLValue::BotInlineMessageMediaVenue:
    case TLValue::BotInlineMessageMediaContact:
        return true;
    default:
        return false;
    }
}

bool TLBotInlineMessage::operator==(const TLBotInlineMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::BotInlineMessageMediaAuto:
    case TLValue::BotInlineMessageText:
        return true
                && flags == v.flags
                && message == v.message
                && entities == v.entities
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::BotInlineMessageMediaGeo:
        return true
                && flags == v.flags
                && geo == v.geo
                && period == v.period
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::BotInlineMessageMediaVenue:
        return true
                && flags == v.flags
                && geo == v.geo
                && title == v.title
                && address == v.address
                && provider == v.provider
                && venueId == v.venueId
                && venueType == v.venueType
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::BotInlineMessageMediaContact:
        return true
                && flags == v.flags
                && phoneNumber == v.phoneNumber
                && firstName == v.firstName
                && lastName == v.lastName
                && vcard == v.vcard
                && replyMarkup == v.replyMarkup
                ;
    default:
        return false;
    }
}

bool TLChannelsChannelParticipant::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelsChannelParticipant:
        return true;
    default:
        return false;
    }
}

bool TLChannelsChannelParticipant::operator==(const TLChannelsChannelParticipant &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelsChannelParticipant:
        return true
                && participant == v.participant
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLChannelsChannelParticipants::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelsChannelParticipants:
    case TLValue::ChannelsChannelParticipantsNotModified:
        return true;
    default:
        return false;
    }
}

bool TLChannelsChannelParticipants::operator==(const TLChannelsChannelParticipants &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelsChannelParticipants:
        return true
                && count == v.count
                && participants == v.participants
                && users == v.users
                ;
    case TLValue::ChannelsChannelParticipantsNotModified:
        return true;
    default:
        return false;
    }
}

bool TLChat::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatEmpty:
    case TLValue::Chat:
    case TLValue::ChatForbidden:
    case TLValue::Channel:
    case TLValue::ChannelForbidden:
        return true;
    default:
        return false;
    }
}

bool TLChat::operator==(const TLChat &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatEmpty:
        return id == v.id;
    case TLValue::Chat:
        return true
                && flags == v.flags
                && id == v.id
                && title == v.title
                && photo == v.photo
                && participantsCount == v.participantsCount
                && date == v.date
                && version == v.version
                && migratedTo == v.migratedTo
                ;
    case TLValue::ChatForbidden:
        return true
                && id == v.id
                && title == v.title
                ;
    case TLValue::Channel:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && title == v.title
                && username == v.username
                && photo == v.photo
                && date == v.date
                && version == v.version
                && restrictionReason == v.restrictionReason
                && adminRights == v.adminRights
                && bannedRights == v.bannedRights
                && participantsCount == v.participantsCount
                ;
    case TLValue::ChannelForbidden:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && title == v.title
                && untilDate == v.untilDate
                ;
    default:
        return false;
    }
}

bool TLChatFull::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatFull:
    case TLValue::ChannelFull:
        return true;
    default:
        return false;
    }
}

bool TLChatFull::operator==(const TLChatFull &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatFull:
        return true
                && flags == v.flags
                && id == v.id
                && participants == v.participants
                && chatPhoto == v.chatPhoto
                && notifySettings == v.notifySettings
                && exportedInvite == v.exportedInvite
                && botInfo == v.botInfo
                && pinnedMsgId == v.pinnedMsgId
                ;
    case TLValue::ChannelFull:
        return true
                && flags == v.flags
                && id == v.id
                && about == v.about
                && participantsCount == v.participantsCount
                && adminsCount == v.adminsCount
                && kickedCount == v.kickedCount
                && bannedCount == v.bannedCount
                && onlineCount == v.onlineCount
                && readInboxMaxId == v.readInboxMaxId
                && readOutboxMaxId == v.readOutboxMaxId
                && unreadCount == v.unreadCount
                && chatPhoto == v.chatPhoto
                && notifySettings == v.notifySettings
                && exportedInvite == v.exportedInvite
                && botInfo == v.botInfo
                && migratedFromChatId == v.migratedFromChatId
                && migratedFromMaxId == v.migratedFromMaxId
                && pinnedMsgId == v.pinnedMsgId
                && stickerset == v.stickerset
                && availableMinId == v.availableMinId
                ;
    default:
        return false;
    }
}

bool TLChatInvite::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChatInviteAlready:
    case TLValue::ChatInvite:
        return true;
    default:
        return false;
    }
}

bool TLChatInvite::operator==(const TLChatInvite &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChatInviteAlready:
        return chat == v.chat;
    case TLValue::ChatInvite:
        return true
                && flags == v.flags
                && title == v.title
                && photo == v.photo
                && participantsCount == v.participantsCount
                && participants == v.participants
                ;
    default:
        return false;
    }
}

bool TLConfig::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Config:
        return true;
    default:
        return false;
    }
}

bool TLConfig::operator==(const TLConfig &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Config:
        return true
                && flags == v.flags
                && date == v.date
                && expires == v.expires
                && testMode == v.testMode
                && thisDc == v.thisDc
                && dcOptions == v.dcOptions
                && dcTxtDomainName == v.dcTxtDomainName
                && chatSizeMax == v.chatSizeMax
                && megagroupSizeMax == v.megagroupSizeMax
                && forwardedCountMax == v.forwardedCountMax
                && onlineUpdatePeriodMs == v.onlineUpdatePeriodMs
                && offlineBlurTimeoutMs == v.offlineBlurTimeoutMs
                && offlineIdleTimeoutMs == v.offlineIdleTimeoutMs
                && onlineCloudTimeoutMs == v.onlineCloudTimeoutMs
                && notifyCloudDelayMs == v.notifyCloudDelayMs
                && notifyDefaultDelayMs == v.notifyDefaultDelayMs
                && pushChatPeriodMs == v.pushChatPeriodMs
                && pushChatLimit == v.pushChatLimit
                && savedGifsLimit == v.savedGifsLimit
                && editTimeLimit == v.editTimeLimit
                && revokeTimeLimit == v.revokeTimeLimit
                && revokePmTimeLimit == v.revokePmTimeLimit
                && ratingEDecay == v.ratingEDecay
                && stickersRecentLimit == v.stickersRecentLimit
                && stickersFavedLimit == v.stickersFavedLimit
                && channelsReadMediaPeriod == v.channelsReadMediaPeriod
                && tmpSessions == v.tmpSessions
                && pinnedDialogsCountMax == v.pinnedDialogsCountMax
                && callReceiveTimeoutMs == v.callReceiveTimeoutMs
                && callRingTimeoutMs == v.callRingTimeoutMs
                && callConnectTimeoutMs == v.callConnectTimeoutMs
                && callPacketTimeoutMs == v.callPacketTimeoutMs
                && meUrlPrefix == v.meUrlPrefix
                && autoupdateUrlPrefix == v.autoupdateUrlPrefix
                && gifSearchUsername == v.gifSearchUsername
                && venueSearchUsername == v.venueSearchUsername
                && imgSearchUsername == v.imgSearchUsername
                && staticMapsProvider == v.staticMapsProvider
                && captionLengthMax == v.captionLengthMax
                && messageLengthMax == v.messageLengthMax
                && webfileDcId == v.webfileDcId
                && suggestedLangCode == v.suggestedLangCode
                && langPackVersion == v.langPackVersion
                && baseLangPackVersion == v.baseLangPackVersion
                ;
    default:
        return false;
    }
}

bool TLContactsBlocked::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsBlocked:
    case TLValue::ContactsBlockedSlice:
        return true;
    default:
        return false;
    }
}

bool TLContactsBlocked::operator==(const TLContactsBlocked &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsBlocked:
        return true
                && blocked == v.blocked
                && users == v.users
                ;
    case TLValue::ContactsBlockedSlice:
        return true
                && count == v.count
                && blocked == v.blocked
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLContactsContacts::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsContactsNotModified:
    case TLValue::ContactsContacts:
        return true;
    default:
        return false;
    }
}

bool TLContactsContacts::operator==(const TLContactsContacts &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsContactsNotModified:
        return true;
    case TLValue::ContactsContacts:
        return true
                && contacts == v.contacts
                && savedCount == v.savedCount
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLContactsFound::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsFound:
        return true;
    default:
        return false;
    }
}

bool TLContactsFound::operator==(const TLContactsFound &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsFound:
        return true
                && myResults == v.myResults
                && results == v.results
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLContactsImportedContacts::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsImportedContacts:
        return true;
    default:
        return false;
    }
}

bool TLContactsImportedContacts::operator==(const TLContactsImportedContacts &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsImportedContacts:
        return true
                && imported == v.imported
                && popularInvites == v.popularInvites
                && retryContacts == v.retryContacts
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLContactsLink::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsLink:
        return true;
    default:
        return false;
    }
}

bool TLContactsLink::operator==(const TLContactsLink &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsLink:
        return true
                && myLink == v.myLink
                && foreignLink == v.foreignLink
                && user == v.user
                ;
    default:
        return false;
    }
}

bool TLContactsResolvedPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsResolvedPeer:
        return true;
    default:
        return false;
    }
}

bool TLContactsResolvedPeer::operator==(const TLContactsResolvedPeer &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsResolvedPeer:
        return true
                && peer == v.peer
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLContactsTopPeers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsTopPeersNotModified:
    case TLValue::ContactsTopPeers:
    case TLValue::ContactsTopPeersDisabled:
        return true;
    default:
        return false;
    }
}

bool TLContactsTopPeers::operator==(const TLContactsTopPeers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ContactsTopPeersNotModified:
    case TLValue::ContactsTopPeersDisabled:
        return true;
    case TLValue::ContactsTopPeers:
        return true
                && categories == v.categories
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLDialog::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Dialog:
        return true;
    default:
        return false;
    }
}

bool TLDialog::operator==(const TLDialog &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Dialog:
        return true
                && flags == v.flags
                && peer == v.peer
                && topMessage == v.topMessage
                && readInboxMaxId == v.readInboxMaxId
                && readOutboxMaxId == v.readOutboxMaxId
                && unreadCount == v.unreadCount
                && unreadMentionsCount == v.unreadMentionsCount
                && notifySettings == v.notifySettings
                && pts == v.pts
                && draft == v.draft
                ;
    default:
        return false;
    }
}

bool TLDocument::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DocumentEmpty:
    case TLValue::Document:
        return true;
    default:
        return false;
    }
}

bool TLDocument::operator==(const TLDocument &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::DocumentEmpty:
        return id == v.id;
    case TLValue::Document:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && fileReference == v.fileReference
                && date == v.date
                && mimeType == v.mimeType
                && size == v.size
                && thumb == v.thumb
                && dcId == v.dcId
                && attributes == v.attributes
                ;
    default:
        return false;
    }
}

bool TLFoundGif::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::FoundGif:
    case TLValue::FoundGifCached:
        return true;
    default:
        return false;
    }
}

bool TLFoundGif::operator==(const TLFoundGif &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::FoundGif:
        return true
                && url == v.url
                && thumbUrl == v.thumbUrl
                && contentUrl == v.contentUrl
                && contentType == v.contentType
                && w == v.w
                && h == v.h
                ;
    case TLValue::FoundGifCached:
        return true
                && url == v.url
                && photo == v.photo
                && document == v.document
                ;
    default:
        return false;
    }
}

bool TLGame::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Game:
        return true;
    default:
        return false;
    }
}

bool TLGame::operator==(const TLGame &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Game:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && shortName == v.shortName
                && title == v.title
                && description == v.description
                && photo == v.photo
                && document == v.document
                ;
    default:
        return false;
    }
}

bool TLHelpAppUpdate::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpAppUpdate:
    case TLValue::HelpNoAppUpdate:
        return true;
    default:
        return false;
    }
}

bool TLHelpAppUpdate::operator==(const TLHelpAppUpdate &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpAppUpdate:
        return true
                && flags == v.flags
                && id == v.id
                && version == v.version
                && text == v.text
                && entities == v.entities
                && document == v.document
                && url == v.url
                ;
    case TLValue::HelpNoAppUpdate:
        return true;
    default:
        return false;
    }
}

bool TLHelpProxyData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpProxyDataEmpty:
    case TLValue::HelpProxyDataPromo:
        return true;
    default:
        return false;
    }
}

bool TLHelpProxyData::operator==(const TLHelpProxyData &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpProxyDataEmpty:
        return expires == v.expires;
    case TLValue::HelpProxyDataPromo:
        return true
                && expires == v.expires
                && peer == v.peer
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLHelpSupport::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpSupport:
        return true;
    default:
        return false;
    }
}

bool TLHelpSupport::operator==(const TLHelpSupport &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpSupport:
        return true
                && phoneNumber == v.phoneNumber
                && user == v.user
                ;
    default:
        return false;
    }
}

bool TLInputBotInlineMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputBotInlineMessageMediaAuto:
    case TLValue::InputBotInlineMessageText:
    case TLValue::InputBotInlineMessageMediaGeo:
    case TLValue::InputBotInlineMessageMediaVenue:
    case TLValue::InputBotInlineMessageMediaContact:
    case TLValue::InputBotInlineMessageGame:
        return true;
    default:
        return false;
    }
}

bool TLInputBotInlineMessage::operator==(const TLInputBotInlineMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputBotInlineMessageMediaAuto:
    case TLValue::InputBotInlineMessageText:
        return true
                && flags == v.flags
                && message == v.message
                && entities == v.entities
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::InputBotInlineMessageMediaGeo:
        return true
                && flags == v.flags
                && geoPoint == v.geoPoint
                && period == v.period
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::InputBotInlineMessageMediaVenue:
        return true
                && flags == v.flags
                && geoPoint == v.geoPoint
                && title == v.title
                && address == v.address
                && provider == v.provider
                && venueId == v.venueId
                && venueType == v.venueType
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::InputBotInlineMessageMediaContact:
        return true
                && flags == v.flags
                && phoneNumber == v.phoneNumber
                && firstName == v.firstName
                && lastName == v.lastName
                && vcard == v.vcard
                && replyMarkup == v.replyMarkup
                ;
    case TLValue::InputBotInlineMessageGame:
        return true
                && flags == v.flags
                && replyMarkup == v.replyMarkup
                ;
    default:
        return false;
    }
}

bool TLInputBotInlineResult::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputBotInlineResult:
    case TLValue::InputBotInlineResultPhoto:
    case TLValue::InputBotInlineResultDocument:
    case TLValue::InputBotInlineResultGame:
        return true;
    default:
        return false;
    }
}

bool TLInputBotInlineResult::operator==(const TLInputBotInlineResult &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputBotInlineResult:
        return true
                && flags == v.flags
                && id == v.id
                && type == v.type
                && title == v.title
                && description == v.description
                && url == v.url
                && thumb == v.thumb
                && content == v.content
                && sendMessage == v.sendMessage
                ;
    case TLValue::InputBotInlineResultPhoto:
        return true
                && id == v.id
                && type == v.type
                && photo == v.photo
                && sendMessage == v.sendMessage
                ;
    case TLValue::InputBotInlineResultDocument:
        return true
                && flags == v.flags
                && id == v.id
                && type == v.type
                && title == v.title
                && description == v.description
                && document == v.document
                && sendMessage == v.sendMessage
                ;
    case TLValue::InputBotInlineResultGame:
        return true
                && id == v.id
                && shortName == v.shortName
                && sendMessage == v.sendMessage
                ;
    default:
        return false;
    }
}

bool TLInputMedia::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputMediaEmpty:
    case TLValue::InputMediaUploadedPhoto:
    case TLValue::InputMediaPhoto:
    case TLValue::InputMediaGeoPoint:
    case TLValue::InputMediaContact:
    case TLValue::InputMediaUploadedDocument:
    case TLValue::InputMediaDocument:
    case TLValue::InputMediaVenue:
    case TLValue::InputMediaGifExternal:
    case TLValue::InputMediaPhotoExternal:
    case TLValue::InputMediaDocumentExternal:
    case TLValue::InputMediaGame:
    case TLValue::InputMediaInvoice:
    case TLValue::InputMediaGeoLive:
    case TLValue::InputMediaPoll:
        return true;
    default:
        return false;
    }
}

bool TLInputMedia::operator==(const TLInputMedia &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputMediaEmpty:
        return true;
    case TLValue::InputMediaUploadedPhoto:
        return true
                && flags == v.flags
                && file == v.file
                && stickers == v.stickers
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::InputMediaPhoto:
        return true
                && flags == v.flags
                && inputPhotoId == v.inputPhotoId
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::InputMediaGeoPoint:
        return geoPoint == v.geoPoint;
    case TLValue::InputMediaContact:
        return true
                && phoneNumber == v.phoneNumber
                && firstName == v.firstName
                && lastName == v.lastName
                && vcard == v.vcard
                ;
    case TLValue::InputMediaUploadedDocument:
        return true
                && flags == v.flags
                && file == v.file
                && thumb == v.thumb
                && mimeType == v.mimeType
                && attributes == v.attributes
                && stickers == v.stickers
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::InputMediaDocument:
        return true
                && flags == v.flags
                && inputDocumentId == v.inputDocumentId
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::InputMediaVenue:
        return true
                && geoPoint == v.geoPoint
                && title == v.title
                && address == v.address
                && provider == v.provider
                && venueId == v.venueId
                && venueType == v.venueType
                ;
    case TLValue::InputMediaGifExternal:
        return true
                && url == v.url
                && q == v.q
                ;
    case TLValue::InputMediaPhotoExternal:
    case TLValue::InputMediaDocumentExternal:
        return true
                && flags == v.flags
                && url == v.url
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::InputMediaGame:
        return inputGameId == v.inputGameId;
    case TLValue::InputMediaInvoice:
        return true
                && flags == v.flags
                && title == v.title
                && description == v.description
                && photo == v.photo
                && invoice == v.invoice
                && payload == v.payload
                && provider == v.provider
                && providerData == v.providerData
                && startParam == v.startParam
                ;
    case TLValue::InputMediaGeoLive:
        return true
                && flags == v.flags
                && geoPoint == v.geoPoint
                && period == v.period
                ;
    case TLValue::InputMediaPoll:
        return poll == v.poll;
    default:
        return false;
    }
}

bool TLInputSingleMedia::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputSingleMedia:
        return true;
    default:
        return false;
    }
}

bool TLInputSingleMedia::operator==(const TLInputSingleMedia &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::InputSingleMedia:
        return true
                && flags == v.flags
                && media == v.media
                && randomId == v.randomId
                && message == v.message
                && entities == v.entities
                ;
    default:
        return false;
    }
}

bool TLMessageAction::hasType(const quint32 value)
{
    switch (value) {
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
    case TLValue::MessageActionPinMessage:
    case TLValue::MessageActionHistoryClear:
    case TLValue::MessageActionGameScore:
    case TLValue::MessageActionPaymentSentMe:
    case TLValue::MessageActionPaymentSent:
    case TLValue::MessageActionPhoneCall:
    case TLValue::MessageActionScreenshotTaken:
    case TLValue::MessageActionCustomAction:
    case TLValue::MessageActionBotAllowed:
    case TLValue::MessageActionSecureValuesSentMe:
    case TLValue::MessageActionSecureValuesSent:
    case TLValue::MessageActionContactSignUp:
        return true;
    default:
        return false;
    }
}

bool TLMessageAction::operator==(const TLMessageAction &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessageActionEmpty:
    case TLValue::MessageActionChatDeletePhoto:
    case TLValue::MessageActionPinMessage:
    case TLValue::MessageActionHistoryClear:
    case TLValue::MessageActionScreenshotTaken:
    case TLValue::MessageActionContactSignUp:
        return true;
    case TLValue::MessageActionChatCreate:
        return true
                && title == v.title
                && users == v.users
                ;
    case TLValue::MessageActionChatEditTitle:
    case TLValue::MessageActionChannelCreate:
        return title == v.title;
    case TLValue::MessageActionChatEditPhoto:
        return photo == v.photo;
    case TLValue::MessageActionChatAddUser:
        return users == v.users;
    case TLValue::MessageActionChatDeleteUser:
        return userId == v.userId;
    case TLValue::MessageActionChatJoinedByLink:
        return inviterId == v.inviterId;
    case TLValue::MessageActionChatMigrateTo:
        return channelId == v.channelId;
    case TLValue::MessageActionChannelMigrateFrom:
        return true
                && title == v.title
                && chatId == v.chatId
                ;
    case TLValue::MessageActionGameScore:
        return true
                && gameId == v.gameId
                && score == v.score
                ;
    case TLValue::MessageActionPaymentSentMe:
        return true
                && flags == v.flags
                && currency == v.currency
                && totalAmount == v.totalAmount
                && payload == v.payload
                && info == v.info
                && shippingOptionId == v.shippingOptionId
                && charge == v.charge
                ;
    case TLValue::MessageActionPaymentSent:
        return true
                && currency == v.currency
                && totalAmount == v.totalAmount
                ;
    case TLValue::MessageActionPhoneCall:
        return true
                && flags == v.flags
                && callId == v.callId
                && reason == v.reason
                && duration == v.duration
                ;
    case TLValue::MessageActionCustomAction:
        return message == v.message;
    case TLValue::MessageActionBotAllowed:
        return domain == v.domain;
    case TLValue::MessageActionSecureValuesSentMe:
        return true
                && values == v.values
                && credentials == v.credentials
                ;
    case TLValue::MessageActionSecureValuesSent:
        return types == v.types;
    default:
        return false;
    }
}

bool TLMessagesAllStickers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesAllStickersNotModified:
    case TLValue::MessagesAllStickers:
        return true;
    default:
        return false;
    }
}

bool TLMessagesAllStickers::operator==(const TLMessagesAllStickers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesAllStickersNotModified:
        return true;
    case TLValue::MessagesAllStickers:
        return true
                && hash == v.hash
                && sets == v.sets
                ;
    default:
        return false;
    }
}

bool TLMessagesChatFull::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesChatFull:
        return true;
    default:
        return false;
    }
}

bool TLMessagesChatFull::operator==(const TLMessagesChatFull &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesChatFull:
        return true
                && fullChat == v.fullChat
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLMessagesChats::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesChats:
    case TLValue::MessagesChatsSlice:
        return true;
    default:
        return false;
    }
}

bool TLMessagesChats::operator==(const TLMessagesChats &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesChats:
        return chats == v.chats;
    case TLValue::MessagesChatsSlice:
        return true
                && count == v.count
                && chats == v.chats
                ;
    default:
        return false;
    }
}

bool TLMessagesFavedStickers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesFavedStickersNotModified:
    case TLValue::MessagesFavedStickers:
        return true;
    default:
        return false;
    }
}

bool TLMessagesFavedStickers::operator==(const TLMessagesFavedStickers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesFavedStickersNotModified:
        return true;
    case TLValue::MessagesFavedStickers:
        return true
                && hash == v.hash
                && packs == v.packs
                && stickers == v.stickers
                ;
    default:
        return false;
    }
}

bool TLMessagesFoundGifs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesFoundGifs:
        return true;
    default:
        return false;
    }
}

bool TLMessagesFoundGifs::operator==(const TLMessagesFoundGifs &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesFoundGifs:
        return true
                && nextOffset == v.nextOffset
                && results == v.results
                ;
    default:
        return false;
    }
}

bool TLMessagesHighScores::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesHighScores:
        return true;
    default:
        return false;
    }
}

bool TLMessagesHighScores::operator==(const TLMessagesHighScores &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesHighScores:
        return true
                && scores == v.scores
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLMessagesRecentStickers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesRecentStickersNotModified:
    case TLValue::MessagesRecentStickers:
        return true;
    default:
        return false;
    }
}

bool TLMessagesRecentStickers::operator==(const TLMessagesRecentStickers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesRecentStickersNotModified:
        return true;
    case TLValue::MessagesRecentStickers:
        return true
                && hash == v.hash
                && packs == v.packs
                && stickers == v.stickers
                && dates == v.dates
                ;
    default:
        return false;
    }
}

bool TLMessagesSavedGifs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesSavedGifsNotModified:
    case TLValue::MessagesSavedGifs:
        return true;
    default:
        return false;
    }
}

bool TLMessagesSavedGifs::operator==(const TLMessagesSavedGifs &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesSavedGifsNotModified:
        return true;
    case TLValue::MessagesSavedGifs:
        return true
                && hash == v.hash
                && gifs == v.gifs
                ;
    default:
        return false;
    }
}

bool TLMessagesStickerSet::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesStickerSet:
        return true;
    default:
        return false;
    }
}

bool TLMessagesStickerSet::operator==(const TLMessagesStickerSet &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesStickerSet:
        return true
                && set == v.set
                && packs == v.packs
                && documents == v.documents
                ;
    default:
        return false;
    }
}

bool TLMessagesStickers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesStickersNotModified:
    case TLValue::MessagesStickers:
        return true;
    default:
        return false;
    }
}

bool TLMessagesStickers::operator==(const TLMessagesStickers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesStickersNotModified:
        return true;
    case TLValue::MessagesStickers:
        return true
                && hash == v.hash
                && stickers == v.stickers
                ;
    default:
        return false;
    }
}

bool TLPage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Page:
        return true;
    default:
        return false;
    }
}

bool TLPage::operator==(const TLPage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::Page:
        return true
                && flags == v.flags
                && url == v.url
                && blocks == v.blocks
                && photos == v.photos
                && documents == v.documents
                ;
    default:
        return false;
    }
}

bool TLPageBlock::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PageBlockUnsupported:
    case TLValue::PageBlockTitle:
    case TLValue::PageBlockSubtitle:
    case TLValue::PageBlockAuthorDate:
    case TLValue::PageBlockHeader:
    case TLValue::PageBlockSubheader:
    case TLValue::PageBlockParagraph:
    case TLValue::PageBlockPreformatted:
    case TLValue::PageBlockFooter:
    case TLValue::PageBlockDivider:
    case TLValue::PageBlockAnchor:
    case TLValue::PageBlockList:
    case TLValue::PageBlockBlockquote:
    case TLValue::PageBlockPullquote:
    case TLValue::PageBlockPhoto:
    case TLValue::PageBlockVideo:
    case TLValue::PageBlockCover:
    case TLValue::PageBlockEmbed:
    case TLValue::PageBlockEmbedPost:
    case TLValue::PageBlockCollage:
    case TLValue::PageBlockSlideshow:
    case TLValue::PageBlockChannel:
    case TLValue::PageBlockAudio:
    case TLValue::PageBlockKicker:
    case TLValue::PageBlockTable:
    case TLValue::PageBlockOrderedList:
    case TLValue::PageBlockDetails:
    case TLValue::PageBlockRelatedArticles:
    case TLValue::PageBlockMap:
        return true;
    default:
        return false;
    }
}

bool TLPageBlock::operator==(const TLPageBlock &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PageBlockUnsupported:
    case TLValue::PageBlockDivider:
        return true;
    case TLValue::PageBlockTitle:
    case TLValue::PageBlockSubtitle:
    case TLValue::PageBlockHeader:
    case TLValue::PageBlockSubheader:
    case TLValue::PageBlockParagraph:
    case TLValue::PageBlockFooter:
    case TLValue::PageBlockKicker:
        return text == v.text;
    case TLValue::PageBlockAuthorDate:
        return true
                && richTextAuthor == v.richTextAuthor
                && publishedDate == v.publishedDate
                ;
    case TLValue::PageBlockPreformatted:
        return true
                && text == v.text
                && language == v.language
                ;
    case TLValue::PageBlockAnchor:
        return name == v.name;
    case TLValue::PageBlockList:
        return pageListItemItemsVector == v.pageListItemItemsVector;
    case TLValue::PageBlockBlockquote:
    case TLValue::PageBlockPullquote:
        return true
                && text == v.text
                && richTextCaption == v.richTextCaption
                ;
    case TLValue::PageBlockPhoto:
        return true
                && flags == v.flags
                && photoId == v.photoId
                && pageCaption == v.pageCaption
                && url == v.url
                && webpageId == v.webpageId
                ;
    case TLValue::PageBlockVideo:
        return true
                && flags == v.flags
                && videoId == v.videoId
                && pageCaption == v.pageCaption
                ;
    case TLValue::PageBlockCover:
        return cover == v.cover;
    case TLValue::PageBlockEmbed:
        return true
                && flags == v.flags
                && url == v.url
                && html == v.html
                && posterPhotoId == v.posterPhotoId
                && w == v.w
                && h == v.h
                && pageCaption == v.pageCaption
                ;
    case TLValue::PageBlockEmbedPost:
        return true
                && url == v.url
                && webpageId == v.webpageId
                && authorPhotoId == v.authorPhotoId
                && stringAuthor == v.stringAuthor
                && date == v.date
                && blocks == v.blocks
                && pageCaption == v.pageCaption
                ;
    case TLValue::PageBlockCollage:
    case TLValue::PageBlockSlideshow:
        return true
                && pageBlockItemsVector == v.pageBlockItemsVector
                && pageCaption == v.pageCaption
                ;
    case TLValue::PageBlockChannel:
        return channel == v.channel;
    case TLValue::PageBlockAudio:
        return true
                && audioId == v.audioId
                && pageCaption == v.pageCaption
                ;
    case TLValue::PageBlockTable:
        return true
                && flags == v.flags
                && title == v.title
                && rows == v.rows
                ;
    case TLValue::PageBlockOrderedList:
        return pageListOrderedItemItemsVector == v.pageListOrderedItemItemsVector;
    case TLValue::PageBlockDetails:
        return true
                && flags == v.flags
                && blocks == v.blocks
                && title == v.title
                ;
    case TLValue::PageBlockRelatedArticles:
        return true
                && title == v.title
                && articles == v.articles
                ;
    case TLValue::PageBlockMap:
        return true
                && geo == v.geo
                && zoom == v.zoom
                && w == v.w
                && h == v.h
                && pageCaption == v.pageCaption
                ;
    default:
        return false;
    }
}

bool TLPaymentsPaymentForm::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsPaymentForm:
        return true;
    default:
        return false;
    }
}

bool TLPaymentsPaymentForm::operator==(const TLPaymentsPaymentForm &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentsPaymentForm:
        return true
                && flags == v.flags
                && botId == v.botId
                && invoice == v.invoice
                && providerId == v.providerId
                && url == v.url
                && nativeProvider == v.nativeProvider
                && nativeParams == v.nativeParams
                && savedInfo == v.savedInfo
                && savedCredentials == v.savedCredentials
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLPaymentsPaymentReceipt::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsPaymentReceipt:
        return true;
    default:
        return false;
    }
}

bool TLPaymentsPaymentReceipt::operator==(const TLPaymentsPaymentReceipt &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentsPaymentReceipt:
        return true
                && flags == v.flags
                && date == v.date
                && botId == v.botId
                && invoice == v.invoice
                && providerId == v.providerId
                && info == v.info
                && shipping == v.shipping
                && currency == v.currency
                && totalAmount == v.totalAmount
                && credentialsTitle == v.credentialsTitle
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLPhoneCall::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhoneCallEmpty:
    case TLValue::PhoneCallWaiting:
    case TLValue::PhoneCallRequested:
    case TLValue::PhoneCallAccepted:
    case TLValue::PhoneCall:
    case TLValue::PhoneCallDiscarded:
        return true;
    default:
        return false;
    }
}

bool TLPhoneCall::operator==(const TLPhoneCall &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhoneCallEmpty:
        return id == v.id;
    case TLValue::PhoneCallWaiting:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                && protocol == v.protocol
                && receiveDate == v.receiveDate
                ;
    case TLValue::PhoneCallRequested:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                && gAHash == v.gAHash
                && protocol == v.protocol
                ;
    case TLValue::PhoneCallAccepted:
        return true
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                && gB == v.gB
                && protocol == v.protocol
                ;
    case TLValue::PhoneCall:
        return true
                && flags == v.flags
                && id == v.id
                && accessHash == v.accessHash
                && date == v.date
                && adminId == v.adminId
                && participantId == v.participantId
                && gAOrB == v.gAOrB
                && keyFingerprint == v.keyFingerprint
                && protocol == v.protocol
                && connection == v.connection
                && alternativeConnections == v.alternativeConnections
                && startDate == v.startDate
                ;
    case TLValue::PhoneCallDiscarded:
        return true
                && flags == v.flags
                && id == v.id
                && reason == v.reason
                && duration == v.duration
                ;
    default:
        return false;
    }
}

bool TLPhonePhoneCall::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhonePhoneCall:
        return true;
    default:
        return false;
    }
}

bool TLPhonePhoneCall::operator==(const TLPhonePhoneCall &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhonePhoneCall:
        return true
                && phoneCall == v.phoneCall
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLPhotosPhoto::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhotosPhoto:
        return true;
    default:
        return false;
    }
}

bool TLPhotosPhoto::operator==(const TLPhotosPhoto &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhotosPhoto:
        return true
                && photo == v.photo
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLPhotosPhotos::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhotosPhotos:
    case TLValue::PhotosPhotosSlice:
        return true;
    default:
        return false;
    }
}

bool TLPhotosPhotos::operator==(const TLPhotosPhotos &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PhotosPhotos:
        return true
                && photos == v.photos
                && users == v.users
                ;
    case TLValue::PhotosPhotosSlice:
        return true
                && count == v.count
                && photos == v.photos
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLStickerSetCovered::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::StickerSetCovered:
    case TLValue::StickerSetMultiCovered:
        return true;
    default:
        return false;
    }
}

bool TLStickerSetCovered::operator==(const TLStickerSetCovered &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::StickerSetCovered:
        return true
                && set == v.set
                && cover == v.cover
                ;
    case TLValue::StickerSetMultiCovered:
        return true
                && set == v.set
                && covers == v.covers
                ;
    default:
        return false;
    }
}

bool TLUserFull::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UserFull:
        return true;
    default:
        return false;
    }
}

bool TLUserFull::operator==(const TLUserFull &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UserFull:
        return true
                && flags == v.flags
                && user == v.user
                && about == v.about
                && link == v.link
                && profilePhoto == v.profilePhoto
                && notifySettings == v.notifySettings
                && botInfo == v.botInfo
                && pinnedMsgId == v.pinnedMsgId
                && commonChatsCount == v.commonChatsCount
                ;
    default:
        return false;
    }
}

bool TLWebPage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::WebPageEmpty:
    case TLValue::WebPagePending:
    case TLValue::WebPage:
    case TLValue::WebPageNotModified:
        return true;
    default:
        return false;
    }
}

bool TLWebPage::operator==(const TLWebPage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::WebPageEmpty:
        return id == v.id;
    case TLValue::WebPagePending:
        return true
                && id == v.id
                && date == v.date
                ;
    case TLValue::WebPage:
        return true
                && flags == v.flags
                && id == v.id
                && url == v.url
                && displayUrl == v.displayUrl
                && hash == v.hash
                && type == v.type
                && siteName == v.siteName
                && title == v.title
                && description == v.description
                && photo == v.photo
                && embedUrl == v.embedUrl
                && embedType == v.embedType
                && embedWidth == v.embedWidth
                && embedHeight == v.embedHeight
                && duration == v.duration
                && author == v.author
                && document == v.document
                && cachedPage == v.cachedPage
                ;
    case TLValue::WebPageNotModified:
        return true;
    default:
        return false;
    }
}

bool TLBotInlineResult::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::BotInlineResult:
    case TLValue::BotInlineMediaResult:
        return true;
    default:
        return false;
    }
}

bool TLBotInlineResult::operator==(const TLBotInlineResult &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::BotInlineResult:
        return true
                && flags == v.flags
                && id == v.id
                && type == v.type
                && title == v.title
                && description == v.description
                && url == v.url
                && thumb == v.thumb
                && content == v.content
                && sendMessage == v.sendMessage
                ;
    case TLValue::BotInlineMediaResult:
        return true
                && flags == v.flags
                && id == v.id
                && type == v.type
                && photo == v.photo
                && document == v.document
                && title == v.title
                && description == v.description
                && sendMessage == v.sendMessage
                ;
    default:
        return false;
    }
}

bool TLMessageMedia::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaPhoto:
    case TLValue::MessageMediaGeo:
    case TLValue::MessageMediaContact:
    case TLValue::MessageMediaUnsupported:
    case TLValue::MessageMediaDocument:
    case TLValue::MessageMediaWebPage:
    case TLValue::MessageMediaVenue:
    case TLValue::MessageMediaGame:
    case TLValue::MessageMediaInvoice:
    case TLValue::MessageMediaGeoLive:
    case TLValue::MessageMediaPoll:
        return true;
    default:
        return false;
    }
}

bool TLMessageMedia::operator==(const TLMessageMedia &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaUnsupported:
        return true;
    case TLValue::MessageMediaPhoto:
        return true
                && flags == v.flags
                && photo == v.photo
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::MessageMediaGeo:
        return geo == v.geo;
    case TLValue::MessageMediaContact:
        return true
                && phoneNumber == v.phoneNumber
                && firstName == v.firstName
                && lastName == v.lastName
                && vcard == v.vcard
                && userId == v.userId
                ;
    case TLValue::MessageMediaDocument:
        return true
                && flags == v.flags
                && document == v.document
                && ttlSeconds == v.ttlSeconds
                ;
    case TLValue::MessageMediaWebPage:
        return webpage == v.webpage;
    case TLValue::MessageMediaVenue:
        return true
                && geo == v.geo
                && title == v.title
                && address == v.address
                && provider == v.provider
                && venueId == v.venueId
                && venueType == v.venueType
                ;
    case TLValue::MessageMediaGame:
        return game == v.game;
    case TLValue::MessageMediaInvoice:
        return true
                && flags == v.flags
                && title == v.title
                && description == v.description
                && webDocumentPhoto == v.webDocumentPhoto
                && receiptMsgId == v.receiptMsgId
                && currency == v.currency
                && totalAmount == v.totalAmount
                && startParam == v.startParam
                ;
    case TLValue::MessageMediaGeoLive:
        return true
                && geo == v.geo
                && period == v.period
                ;
    case TLValue::MessageMediaPoll:
        return true
                && poll == v.poll
                && results == v.results
                ;
    default:
        return false;
    }
}

bool TLMessagesArchivedStickers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesArchivedStickers:
        return true;
    default:
        return false;
    }
}

bool TLMessagesArchivedStickers::operator==(const TLMessagesArchivedStickers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesArchivedStickers:
        return true
                && count == v.count
                && sets == v.sets
                ;
    default:
        return false;
    }
}

bool TLMessagesBotResults::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesBotResults:
        return true;
    default:
        return false;
    }
}

bool TLMessagesBotResults::operator==(const TLMessagesBotResults &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesBotResults:
        return true
                && flags == v.flags
                && queryId == v.queryId
                && nextOffset == v.nextOffset
                && switchPm == v.switchPm
                && results == v.results
                && cacheTime == v.cacheTime
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLMessagesFeaturedStickers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesFeaturedStickersNotModified:
    case TLValue::MessagesFeaturedStickers:
        return true;
    default:
        return false;
    }
}

bool TLMessagesFeaturedStickers::operator==(const TLMessagesFeaturedStickers &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesFeaturedStickersNotModified:
        return true;
    case TLValue::MessagesFeaturedStickers:
        return true
                && hash == v.hash
                && sets == v.sets
                && unread == v.unread
                ;
    default:
        return false;
    }
}

bool TLMessagesFoundStickerSets::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesFoundStickerSetsNotModified:
    case TLValue::MessagesFoundStickerSets:
        return true;
    default:
        return false;
    }
}

bool TLMessagesFoundStickerSets::operator==(const TLMessagesFoundStickerSets &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesFoundStickerSetsNotModified:
        return true;
    case TLValue::MessagesFoundStickerSets:
        return true
                && hash == v.hash
                && sets == v.sets
                ;
    default:
        return false;
    }
}

bool TLMessagesStickerSetInstallResult::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesStickerSetInstallResultSuccess:
    case TLValue::MessagesStickerSetInstallResultArchive:
        return true;
    default:
        return false;
    }
}

bool TLMessagesStickerSetInstallResult::operator==(const TLMessagesStickerSetInstallResult &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesStickerSetInstallResultSuccess:
        return true;
    case TLValue::MessagesStickerSetInstallResultArchive:
        return sets == v.sets;
    default:
        return false;
    }
}

bool TLRecentMeUrl::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::RecentMeUrlUnknown:
    case TLValue::RecentMeUrlUser:
    case TLValue::RecentMeUrlChat:
    case TLValue::RecentMeUrlChatInvite:
    case TLValue::RecentMeUrlStickerSet:
        return true;
    default:
        return false;
    }
}

bool TLRecentMeUrl::operator==(const TLRecentMeUrl &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::RecentMeUrlUnknown:
        return url == v.url;
    case TLValue::RecentMeUrlUser:
        return true
                && url == v.url
                && userId == v.userId
                ;
    case TLValue::RecentMeUrlChat:
        return true
                && url == v.url
                && chatId == v.chatId
                ;
    case TLValue::RecentMeUrlChatInvite:
        return true
                && url == v.url
                && chatInvite == v.chatInvite
                ;
    case TLValue::RecentMeUrlStickerSet:
        return true
                && url == v.url
                && set == v.set
                ;
    default:
        return false;
    }
}

bool TLHelpRecentMeUrls::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpRecentMeUrls:
        return true;
    default:
        return false;
    }
}

bool TLHelpRecentMeUrls::operator==(const TLHelpRecentMeUrls &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::HelpRecentMeUrls:
        return true
                && urls == v.urls
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessageEmpty:
    case TLValue::Message:
    case TLValue::MessageService:
        return true;
    default:
        return false;
    }
}

bool TLMessage::operator==(const TLMessage &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessageEmpty:
        return id == v.id;
    case TLValue::Message:
        return true
                && flags == v.flags
                && id == v.id
                && fromId == v.fromId
                && toId == v.toId
                && fwdFrom == v.fwdFrom
                && viaBotId == v.viaBotId
                && replyToMsgId == v.replyToMsgId
                && date == v.date
                && message == v.message
                && media == v.media
                && replyMarkup == v.replyMarkup
                && entities == v.entities
                && views == v.views
                && editDate == v.editDate
                && postAuthor == v.postAuthor
                && groupedId == v.groupedId
                ;
    case TLValue::MessageService:
        return true
                && flags == v.flags
                && id == v.id
                && fromId == v.fromId
                && toId == v.toId
                && replyToMsgId == v.replyToMsgId
                && date == v.date
                && action == v.action
                ;
    default:
        return false;
    }
}

bool TLMessagesDialogs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesDialogs:
    case TLValue::MessagesDialogsSlice:
    case TLValue::MessagesDialogsNotModified:
        return true;
    default:
        return false;
    }
}

bool TLMessagesDialogs::operator==(const TLMessagesDialogs &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesDialogs:
        return true
                && dialogs == v.dialogs
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                ;
    case TLValue::MessagesDialogsSlice:
        return true
                && count == v.count
                && dialogs == v.dialogs
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                ;
    case TLValue::MessagesDialogsNotModified:
        return count == v.count;
    default:
        return false;
    }
}

bool TLMessagesMessages::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesMessages:
    case TLValue::MessagesMessagesSlice:
    case TLValue::MessagesChannelMessages:
    case TLValue::MessagesMessagesNotModified:
        return true;
    default:
        return false;
    }
}

bool TLMessagesMessages::operator==(const TLMessagesMessages &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesMessages:
        return true
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                ;
    case TLValue::MessagesMessagesSlice:
        return true
                && flags == v.flags
                && count == v.count
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                ;
    case TLValue::MessagesChannelMessages:
        return true
                && flags == v.flags
                && pts == v.pts
                && count == v.count
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                ;
    case TLValue::MessagesMessagesNotModified:
        return count == v.count;
    default:
        return false;
    }
}

bool TLMessagesPeerDialogs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesPeerDialogs:
        return true;
    default:
        return false;
    }
}

bool TLMessagesPeerDialogs::operator==(const TLMessagesPeerDialogs &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::MessagesPeerDialogs:
        return true
                && dialogs == v.dialogs
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                && state == v.state
                ;
    default:
        return false;
    }
}

bool TLUpdate::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateMessageID:
    case TLValue::UpdateDeleteMessages:
    case TLValue::UpdateUserTyping:
    case TLValue::UpdateChatUserTyping:
    case TLValue::UpdateChatParticipants:
    case TLValue::UpdateUserStatus:
    case TLValue::UpdateUserName:
    case TLValue::UpdateUserPhoto:
    case TLValue::UpdateContactLink:
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
    case TLValue::UpdateBotInlineSend:
    case TLValue::UpdateEditChannelMessage:
    case TLValue::UpdateChannelPinnedMessage:
    case TLValue::UpdateBotCallbackQuery:
    case TLValue::UpdateEditMessage:
    case TLValue::UpdateInlineBotCallbackQuery:
    case TLValue::UpdateReadChannelOutbox:
    case TLValue::UpdateDraftMessage:
    case TLValue::UpdateReadFeaturedStickers:
    case TLValue::UpdateRecentStickers:
    case TLValue::UpdateConfig:
    case TLValue::UpdatePtsChanged:
    case TLValue::UpdateChannelWebPage:
    case TLValue::UpdateDialogPinned:
    case TLValue::UpdatePinnedDialogs:
    case TLValue::UpdateBotWebhookJSON:
    case TLValue::UpdateBotWebhookJSONQuery:
    case TLValue::UpdateBotShippingQuery:
    case TLValue::UpdateBotPrecheckoutQuery:
    case TLValue::UpdatePhoneCall:
    case TLValue::UpdateLangPackTooLong:
    case TLValue::UpdateLangPack:
    case TLValue::UpdateFavedStickers:
    case TLValue::UpdateChannelReadMessagesContents:
    case TLValue::UpdateContactsReset:
    case TLValue::UpdateChannelAvailableMessages:
    case TLValue::UpdateDialogUnreadMark:
    case TLValue::UpdateUserPinnedMessage:
    case TLValue::UpdateChatPinnedMessage:
    case TLValue::UpdateMessagePoll:
        return true;
    default:
        return false;
    }
}

bool TLUpdate::operator==(const TLUpdate &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
    case TLValue::UpdateEditChannelMessage:
    case TLValue::UpdateEditMessage:
        return true
                && message == v.message
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    case TLValue::UpdateMessageID:
        return true
                && quint32Id == v.quint32Id
                && randomId == v.randomId
                ;
    case TLValue::UpdateDeleteMessages:
    case TLValue::UpdateReadMessagesContents:
        return true
                && messages == v.messages
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    case TLValue::UpdateUserTyping:
        return true
                && userId == v.userId
                && action == v.action
                ;
    case TLValue::UpdateChatUserTyping:
        return true
                && chatId == v.chatId
                && userId == v.userId
                && action == v.action
                ;
    case TLValue::UpdateChatParticipants:
        return participants == v.participants;
    case TLValue::UpdateUserStatus:
        return true
                && userId == v.userId
                && status == v.status
                ;
    case TLValue::UpdateUserName:
        return true
                && userId == v.userId
                && firstName == v.firstName
                && lastName == v.lastName
                && username == v.username
                ;
    case TLValue::UpdateUserPhoto:
        return true
                && userId == v.userId
                && date == v.date
                && photo == v.photo
                && previous == v.previous
                ;
    case TLValue::UpdateContactLink:
        return true
                && userId == v.userId
                && myLink == v.myLink
                && foreignLink == v.foreignLink
                ;
    case TLValue::UpdateNewEncryptedMessage:
        return true
                && encryptedMessage == v.encryptedMessage
                && qts == v.qts
                ;
    case TLValue::UpdateEncryptedChatTyping:
        return chatId == v.chatId;
    case TLValue::UpdateEncryption:
        return true
                && chat == v.chat
                && date == v.date
                ;
    case TLValue::UpdateEncryptedMessagesRead:
        return true
                && chatId == v.chatId
                && maxDate == v.maxDate
                && date == v.date
                ;
    case TLValue::UpdateChatParticipantAdd:
        return true
                && chatId == v.chatId
                && userId == v.userId
                && inviterId == v.inviterId
                && date == v.date
                && version == v.version
                ;
    case TLValue::UpdateChatParticipantDelete:
        return true
                && chatId == v.chatId
                && userId == v.userId
                && version == v.version
                ;
    case TLValue::UpdateDcOptions:
        return dcOptions == v.dcOptions;
    case TLValue::UpdateUserBlocked:
        return true
                && userId == v.userId
                && blocked == v.blocked
                ;
    case TLValue::UpdateNotifySettings:
        return true
                && notifyPeer == v.notifyPeer
                && notifySettings == v.notifySettings
                ;
    case TLValue::UpdateServiceNotification:
        return true
                && flags == v.flags
                && inboxDate == v.inboxDate
                && type == v.type
                && stringMessage == v.stringMessage
                && media == v.media
                && entities == v.entities
                ;
    case TLValue::UpdatePrivacy:
        return true
                && key == v.key
                && rules == v.rules
                ;
    case TLValue::UpdateUserPhone:
        return true
                && userId == v.userId
                && phone == v.phone
                ;
    case TLValue::UpdateReadHistoryInbox:
    case TLValue::UpdateReadHistoryOutbox:
        return true
                && peer == v.peer
                && maxId == v.maxId
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    case TLValue::UpdateWebPage:
        return true
                && webpage == v.webpage
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    case TLValue::UpdateChannelTooLong:
        return true
                && flags == v.flags
                && channelId == v.channelId
                && pts == v.pts
                ;
    case TLValue::UpdateChannel:
        return channelId == v.channelId;
    case TLValue::UpdateReadChannelInbox:
    case TLValue::UpdateReadChannelOutbox:
        return true
                && channelId == v.channelId
                && maxId == v.maxId
                ;
    case TLValue::UpdateDeleteChannelMessages:
        return true
                && channelId == v.channelId
                && messages == v.messages
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    case TLValue::UpdateChannelMessageViews:
        return true
                && channelId == v.channelId
                && quint32Id == v.quint32Id
                && views == v.views
                ;
    case TLValue::UpdateChatAdmins:
        return true
                && chatId == v.chatId
                && enabled == v.enabled
                && version == v.version
                ;
    case TLValue::UpdateChatParticipantAdmin:
        return true
                && chatId == v.chatId
                && userId == v.userId
                && isAdmin == v.isAdmin
                && version == v.version
                ;
    case TLValue::UpdateNewStickerSet:
        return stickerset == v.stickerset;
    case TLValue::UpdateStickerSetsOrder:
        return true
                && flags == v.flags
                && quint64OrderVector == v.quint64OrderVector
                ;
    case TLValue::UpdateStickerSets:
    case TLValue::UpdateSavedGifs:
    case TLValue::UpdateReadFeaturedStickers:
    case TLValue::UpdateRecentStickers:
    case TLValue::UpdateConfig:
    case TLValue::UpdatePtsChanged:
    case TLValue::UpdateFavedStickers:
    case TLValue::UpdateContactsReset:
        return true;
    case TLValue::UpdateBotInlineQuery:
        return true
                && flags == v.flags
                && queryId == v.queryId
                && userId == v.userId
                && query == v.query
                && geo == v.geo
                && offset == v.offset
                ;
    case TLValue::UpdateBotInlineSend:
        return true
                && flags == v.flags
                && userId == v.userId
                && query == v.query
                && geo == v.geo
                && stringId == v.stringId
                && inputBotInlineMessageIDMsgId == v.inputBotInlineMessageIDMsgId
                ;
    case TLValue::UpdateChannelPinnedMessage:
        return true
                && channelId == v.channelId
                && quint32Id == v.quint32Id
                ;
    case TLValue::UpdateBotCallbackQuery:
        return true
                && flags == v.flags
                && queryId == v.queryId
                && userId == v.userId
                && peer == v.peer
                && msgId == v.msgId
                && chatInstance == v.chatInstance
                && byteArrayData == v.byteArrayData
                && gameShortName == v.gameShortName
                ;
    case TLValue::UpdateInlineBotCallbackQuery:
        return true
                && flags == v.flags
                && queryId == v.queryId
                && userId == v.userId
                && inputBotInlineMessageIDMsgId == v.inputBotInlineMessageIDMsgId
                && chatInstance == v.chatInstance
                && byteArrayData == v.byteArrayData
                && gameShortName == v.gameShortName
                ;
    case TLValue::UpdateDraftMessage:
        return true
                && peer == v.peer
                && draft == v.draft
                ;
    case TLValue::UpdateChannelWebPage:
        return true
                && channelId == v.channelId
                && webpage == v.webpage
                && pts == v.pts
                && ptsCount == v.ptsCount
                ;
    case TLValue::UpdateDialogPinned:
    case TLValue::UpdateDialogUnreadMark:
        return true
                && flags == v.flags
                && dialogPeer == v.dialogPeer
                ;
    case TLValue::UpdatePinnedDialogs:
        return true
                && flags == v.flags
                && dialogPeerOrderVector == v.dialogPeerOrderVector
                ;
    case TLValue::UpdateBotWebhookJSON:
        return jSONData == v.jSONData;
    case TLValue::UpdateBotWebhookJSONQuery:
        return true
                && queryId == v.queryId
                && jSONData == v.jSONData
                && timeout == v.timeout
                ;
    case TLValue::UpdateBotShippingQuery:
        return true
                && queryId == v.queryId
                && userId == v.userId
                && payload == v.payload
                && shippingAddress == v.shippingAddress
                ;
    case TLValue::UpdateBotPrecheckoutQuery:
        return true
                && flags == v.flags
                && queryId == v.queryId
                && userId == v.userId
                && payload == v.payload
                && info == v.info
                && shippingOptionId == v.shippingOptionId
                && currency == v.currency
                && totalAmount == v.totalAmount
                ;
    case TLValue::UpdatePhoneCall:
        return phoneCall == v.phoneCall;
    case TLValue::UpdateLangPackTooLong:
        return langCode == v.langCode;
    case TLValue::UpdateLangPack:
        return difference == v.difference;
    case TLValue::UpdateChannelReadMessagesContents:
        return true
                && channelId == v.channelId
                && messages == v.messages
                ;
    case TLValue::UpdateChannelAvailableMessages:
        return true
                && channelId == v.channelId
                && availableMinId == v.availableMinId
                ;
    case TLValue::UpdateUserPinnedMessage:
        return true
                && userId == v.userId
                && quint32Id == v.quint32Id
                ;
    case TLValue::UpdateChatPinnedMessage:
        return true
                && chatId == v.chatId
                && quint32Id == v.quint32Id
                ;
    case TLValue::UpdateMessagePoll:
        return true
                && flags == v.flags
                && pollId == v.pollId
                && poll == v.poll
                && results == v.results
                ;
    default:
        return false;
    }
}

bool TLUpdates::hasType(const quint32 value)
{
    switch (value) {
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
    }
}

bool TLUpdates::operator==(const TLUpdates &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UpdatesTooLong:
        return true;
    case TLValue::UpdateShortMessage:
        return true
                && flags == v.flags
                && id == v.id
                && userId == v.userId
                && message == v.message
                && pts == v.pts
                && ptsCount == v.ptsCount
                && date == v.date
                && fwdFrom == v.fwdFrom
                && viaBotId == v.viaBotId
                && replyToMsgId == v.replyToMsgId
                && entities == v.entities
                ;
    case TLValue::UpdateShortChatMessage:
        return true
                && flags == v.flags
                && id == v.id
                && fromId == v.fromId
                && chatId == v.chatId
                && message == v.message
                && pts == v.pts
                && ptsCount == v.ptsCount
                && date == v.date
                && fwdFrom == v.fwdFrom
                && viaBotId == v.viaBotId
                && replyToMsgId == v.replyToMsgId
                && entities == v.entities
                ;
    case TLValue::UpdateShort:
        return true
                && update == v.update
                && date == v.date
                ;
    case TLValue::UpdatesCombined:
        return true
                && updates == v.updates
                && users == v.users
                && chats == v.chats
                && date == v.date
                && seqStart == v.seqStart
                && seq == v.seq
                ;
    case TLValue::Updates:
        return true
                && updates == v.updates
                && users == v.users
                && chats == v.chats
                && date == v.date
                && seq == v.seq
                ;
    case TLValue::UpdateShortSentMessage:
        return true
                && flags == v.flags
                && id == v.id
                && pts == v.pts
                && ptsCount == v.ptsCount
                && date == v.date
                && media == v.media
                && entities == v.entities
                ;
    default:
        return false;
    }
}

bool TLUpdatesChannelDifference::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UpdatesChannelDifferenceEmpty:
    case TLValue::UpdatesChannelDifferenceTooLong:
    case TLValue::UpdatesChannelDifference:
        return true;
    default:
        return false;
    }
}

bool TLUpdatesChannelDifference::operator==(const TLUpdatesChannelDifference &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UpdatesChannelDifferenceEmpty:
        return true
                && flags == v.flags
                && pts == v.pts
                && timeout == v.timeout
                ;
    case TLValue::UpdatesChannelDifferenceTooLong:
        return true
                && flags == v.flags
                && pts == v.pts
                && timeout == v.timeout
                && topMessage == v.topMessage
                && readInboxMaxId == v.readInboxMaxId
                && readOutboxMaxId == v.readOutboxMaxId
                && unreadCount == v.unreadCount
                && unreadMentionsCount == v.unreadMentionsCount
                && messages == v.messages
                && chats == v.chats
                && users == v.users
                ;
    case TLValue::UpdatesChannelDifference:
        return true
                && flags == v.flags
                && pts == v.pts
                && timeout == v.timeout
                && newMessages == v.newMessages
                && otherUpdates == v.otherUpdates
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}

bool TLUpdatesDifference::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UpdatesDifferenceEmpty:
    case TLValue::UpdatesDifference:
    case TLValue::UpdatesDifferenceSlice:
    case TLValue::UpdatesDifferenceTooLong:
        return true;
    default:
        return false;
    }
}

bool TLUpdatesDifference::operator==(const TLUpdatesDifference &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::UpdatesDifferenceEmpty:
        return true
                && date == v.date
                && seq == v.seq
                ;
    case TLValue::UpdatesDifference:
        return true
                && newMessages == v.newMessages
                && newEncryptedMessages == v.newEncryptedMessages
                && otherUpdates == v.otherUpdates
                && chats == v.chats
                && users == v.users
                && state == v.state
                ;
    case TLValue::UpdatesDifferenceSlice:
        return true
                && newMessages == v.newMessages
                && newEncryptedMessages == v.newEncryptedMessages
                && otherUpdates == v.otherUpdates
                && chats == v.chats
                && users == v.users
                && intermediateState == v.intermediateState
                ;
    case TLValue::UpdatesDifferenceTooLong:
        return pts == v.pts;
    default:
        return false;
    }
}

bool TLChannelAdminLogEventAction::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelAdminLogEventActionChangeTitle:
    case TLValue::ChannelAdminLogEventActionChangeAbout:
    case TLValue::ChannelAdminLogEventActionChangeUsername:
    case TLValue::ChannelAdminLogEventActionChangePhoto:
    case TLValue::ChannelAdminLogEventActionToggleInvites:
    case TLValue::ChannelAdminLogEventActionToggleSignatures:
    case TLValue::ChannelAdminLogEventActionUpdatePinned:
    case TLValue::ChannelAdminLogEventActionEditMessage:
    case TLValue::ChannelAdminLogEventActionDeleteMessage:
    case TLValue::ChannelAdminLogEventActionParticipantJoin:
    case TLValue::ChannelAdminLogEventActionParticipantLeave:
    case TLValue::ChannelAdminLogEventActionParticipantInvite:
    case TLValue::ChannelAdminLogEventActionParticipantToggleBan:
    case TLValue::ChannelAdminLogEventActionParticipantToggleAdmin:
    case TLValue::ChannelAdminLogEventActionChangeStickerSet:
    case TLValue::ChannelAdminLogEventActionTogglePreHistoryHidden:
        return true;
    default:
        return false;
    }
}

bool TLChannelAdminLogEventAction::operator==(const TLChannelAdminLogEventAction &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelAdminLogEventActionChangeTitle:
    case TLValue::ChannelAdminLogEventActionChangeAbout:
    case TLValue::ChannelAdminLogEventActionChangeUsername:
        return true
                && prevValue == v.prevValue
                && stringNewValue == v.stringNewValue
                ;
    case TLValue::ChannelAdminLogEventActionChangePhoto:
        return true
                && prevPhoto == v.prevPhoto
                && newPhoto == v.newPhoto
                ;
    case TLValue::ChannelAdminLogEventActionToggleInvites:
    case TLValue::ChannelAdminLogEventActionToggleSignatures:
    case TLValue::ChannelAdminLogEventActionTogglePreHistoryHidden:
        return boolNewValue == v.boolNewValue;
    case TLValue::ChannelAdminLogEventActionUpdatePinned:
    case TLValue::ChannelAdminLogEventActionDeleteMessage:
        return message == v.message;
    case TLValue::ChannelAdminLogEventActionEditMessage:
        return true
                && prevMessage == v.prevMessage
                && newMessage == v.newMessage
                ;
    case TLValue::ChannelAdminLogEventActionParticipantJoin:
    case TLValue::ChannelAdminLogEventActionParticipantLeave:
        return true;
    case TLValue::ChannelAdminLogEventActionParticipantInvite:
        return participant == v.participant;
    case TLValue::ChannelAdminLogEventActionParticipantToggleBan:
    case TLValue::ChannelAdminLogEventActionParticipantToggleAdmin:
        return true
                && prevParticipant == v.prevParticipant
                && newParticipant == v.newParticipant
                ;
    case TLValue::ChannelAdminLogEventActionChangeStickerSet:
        return true
                && prevStickerset == v.prevStickerset
                && newStickerset == v.newStickerset
                ;
    default:
        return false;
    }
}

bool TLPaymentsPaymentResult::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsPaymentResult:
    case TLValue::PaymentsPaymentVerficationNeeded:
        return true;
    default:
        return false;
    }
}

bool TLPaymentsPaymentResult::operator==(const TLPaymentsPaymentResult &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::PaymentsPaymentResult:
        return updates == v.updates;
    case TLValue::PaymentsPaymentVerficationNeeded:
        return url == v.url;
    default:
        return false;
    }
}

bool TLChannelAdminLogEvent::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelAdminLogEvent:
        return true;
    default:
        return false;
    }
}

bool TLChannelAdminLogEvent::operator==(const TLChannelAdminLogEvent &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelAdminLogEvent:
        return true
                && id == v.id
                && date == v.date
                && userId == v.userId
                && action == v.action
                ;
    default:
        return false;
    }
}

bool TLChannelsAdminLogResults::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelsAdminLogResults:
        return true;
    default:
        return false;
    }
}

bool TLChannelsAdminLogResults::operator==(const TLChannelsAdminLogResults &v) const
{
    if (tlType != v.tlType) {
        return false;
    }

    switch (tlType) {
    case TLValue::ChannelsAdminLogResults:
        return true
                && events == v.events
                && chats == v.chats
                && users == v.users
                ;
    default:
        return false;
    }
}
// End of generated TLTypes
