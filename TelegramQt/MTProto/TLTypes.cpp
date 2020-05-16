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

bool operator==(const TLPeer &left, const TLPeer &right) {
    if (left.tlType != right.tlType) {
        return false;
    }
    switch (left.tlType) {
    case TLValue::PeerUser:
        return left.userId == right.userId;
    case TLValue::PeerChat:
        return left.chatId == right.chatId;
    case TLValue::PeerChannel:
        return left.channelId == right.channelId;
    }
    // Object is not valid
    return false;
}

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

bool TLAccountPassword::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountNoPassword:
    case TLValue::AccountPassword:
        return true;
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

bool TLAccountPasswordSettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountPasswordSettings:
        return true;
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

bool TLAuthCheckedPhone::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthCheckedPhone:
        return true;
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

bool TLAuthExportedAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthExportedAuthorization:
        return true;
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

bool TLAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Authorization:
        return true;
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

bool TLBotCommand::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::BotCommand:
        return true;
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

bool TLCdnFileHash::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::CdnFileHash:
        return true;
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

bool TLClientDHInnerData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ClientDHInnerData:
        return true;
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

bool TLContactBlocked::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactBlocked:
        return true;
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

bool TLDataJSON::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DataJSON:
        return true;
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

bool TLDisabledFeature::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::DisabledFeature:
        return true;
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

bool TLError::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Error:
        return true;
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

bool TLExportedMessageLink::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ExportedMessageLink:
        return true;
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

bool TLFutureSalt::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::FutureSalt:
        return true;
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

bool TLHelpInviteText::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpInviteText:
        return true;
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

bool TLHighScore::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HighScore:
        return true;
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

bool TLImportedContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ImportedContact:
        return true;
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

bool TLInputAppEvent::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputAppEvent:
        return true;
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

bool TLInputContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPhoneContact:
        return true;
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

bool TLInputEncryptedChat::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputEncryptedChat:
        return true;
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

bool TLInputFileLocation::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputFileLocation:
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputDocumentFileLocation:
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

bool TLInputPeerNotifyEvents::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPeerNotifyEventsEmpty:
    case TLValue::InputPeerNotifyEventsAll:
        return true;
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

bool TLInputPrivacyKey::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
    case TLValue::InputPrivacyKeyChatInvite:
    case TLValue::InputPrivacyKeyPhoneCall:
        return true;
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

bool TLInputWebFileLocation::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputWebFileLocation:
        return true;
    default:
        return false;
    }
}

bool TLIpPort::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::IpPort:
        return true;
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

bool TLLangPackLanguage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::LangPackLanguage:
        return true;
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

bool TLMaskCoords::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MaskCoords:
        return true;
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
        return true;
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

bool TLMessageRange::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessageRange:
        return true;
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

bool TLMessagesAffectedMessages::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesAffectedMessages:
        return true;
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

bool TLMsgResendReq::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgResendReq:
        return true;
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

bool TLMsgsAllInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgsAllInfo:
        return true;
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

bool TLMsgsStateReq::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MsgsStateReq:
        return true;
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

bool TLNewSession::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::NewSessionCreated:
        return true;
    default:
        return false;
    }
}

bool TLPQInnerData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PQInnerData:
        return true;
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

bool TLPaymentSavedCredentials::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentSavedCredentialsCard:
        return true;
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

bool TLPeerNotifyEvents::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PeerNotifyEventsEmpty:
    case TLValue::PeerNotifyEventsAll:
        return true;
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

bool TLPhoneConnection::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhoneConnection:
        return true;
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
        return true;
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

bool TLPopularContact::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PopularContact:
        return true;
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

bool TLPrivacyKey::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PrivacyKeyStatusTimestamp:
    case TLValue::PrivacyKeyChatInvite:
    case TLValue::PrivacyKeyPhoneCall:
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

bool TLReceivedNotifyMessage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ReceivedNotifyMessage:
        return true;
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
    case TLValue::InputReportReasonOther:
        return true;
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
        return true;
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

bool TLRpcError::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::RpcError:
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

bool TLServerDHInnerData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ServerDHInnerData:
        return true;
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

bool TLShippingOption::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ShippingOption:
        return true;
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

bool TLTopPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::TopPeer:
        return true;
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

bool TLTopPeerCategoryPeers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::TopPeerCategoryPeers:
        return true;
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

bool TLUploadWebFile::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UploadWebFile:
        return true;
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

bool TLAccountAuthorizations::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AccountAuthorizations:
        return true;
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

bool TLCdnConfig::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::CdnConfig:
        return true;
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

bool TLChannelAdminRights::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelAdminRights:
        return true;
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

bool TLContactStatus::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactStatus:
        return true;
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

bool TLHelpConfigSimple::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpConfigSimple:
        return true;
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

bool TLInputNotifyPeer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputNotifyPeer:
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyAll:
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

bool TLInputPeerNotifySettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputPeerNotifySettings:
        return true;
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

bool TLInputStickerSetItem::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::InputStickerSetItem:
        return true;
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

bool TLInvoice::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Invoice:
        return true;
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

bool TLKeyboardButtonRow::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::KeyboardButtonRow:
        return true;
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

bool TLMessagesBotCallbackAnswer::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesBotCallbackAnswer:
        return true;
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

bool TLMessagesMessageEditData::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesMessageEditData:
        return true;
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
    case TLValue::NotifyAll:
        return true;
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

bool TLPaymentsSavedInfo::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsSavedInfo:
        return true;
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

bool TLPeerNotifySettings::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PeerNotifySettingsEmpty:
    case TLValue::PeerNotifySettings:
        return true;
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

bool TLPhoneCallProtocol::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhoneCallProtocol:
        return true;
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

bool TLStickerSet::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::StickerSet:
        return true;
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

bool TLWebDocument::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::WebDocument:
        return true;
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

bool TLAuthAuthorization::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::AuthAuthorization:
        return true;
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

bool TLChannelsChannelParticipant::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelsChannelParticipant:
        return true;
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

bool TLConfig::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Config:
        return true;
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

bool TLContactsFound::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsFound:
        return true;
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

bool TLContactsLink::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsLink:
        return true;
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

bool TLContactsTopPeers::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ContactsTopPeersNotModified:
    case TLValue::ContactsTopPeers:
        return true;
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

bool TLGame::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::Game:
        return true;
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
        return true;
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
        return true;
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

bool TLMessagesChatFull::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesChatFull:
        return true;
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

bool TLMessagesFoundGifs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesFoundGifs:
        return true;
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

bool TLMessagesStickerSet::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesStickerSet:
        return true;
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

bool TLPage::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PagePart:
    case TLValue::PageFull:
        return true;
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
        return true;
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

bool TLPaymentsPaymentReceipt::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PaymentsPaymentReceipt:
        return true;
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

bool TLPhonePhoneCall::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::PhonePhoneCall:
        return true;
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

bool TLUserFull::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::UserFull:
        return true;
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
        return true;
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

bool TLMessagesBotResults::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesBotResults:
        return true;
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

bool TLHelpRecentMeUrls::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::HelpRecentMeUrls:
        return true;
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

bool TLMessagesDialogs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesDialogs:
    case TLValue::MessagesDialogsSlice:
        return true;
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

bool TLMessagesPeerDialogs::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::MessagesPeerDialogs:
        return true;
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
    case TLValue::UpdateContactRegistered:
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
        return true;
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

bool TLChannelAdminLogEvent::hasType(const quint32 value)
{
    switch (value) {
    case TLValue::ChannelAdminLogEvent:
        return true;
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
// End of generated TLTypes
