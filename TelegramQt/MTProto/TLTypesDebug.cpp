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
#include "TelegramNamespace.hpp"

#include <QDebugStateSaver>

namespace Telegram {

namespace Debug {
// Generated TLTypes flagsToString
template<>
QString flagsToString(const TLAccountPassword &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLAccountPassword::HasRecovery) {
        result << QLatin1String("HasRecovery");
    }
    if (flags & TLAccountPassword::HasSecureValues) {
        result << QLatin1String("HasSecureValues");
    }
    if (flags & TLAccountPassword::HasPassword) {
        result << QLatin1String("HasPassword");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLAuthorization &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLAuthorization::Current) {
        result << QLatin1String("Current");
    }
    if (flags & TLAuthorization::OfficialApp) {
        result << QLatin1String("OfficialApp");
    }
    if (flags & TLAuthorization::PasswordPending) {
        result << QLatin1String("PasswordPending");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChannelAdminLogEventsFilter &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChannelAdminLogEventsFilter::Join) {
        result << QLatin1String("Join");
    }
    if (flags & TLChannelAdminLogEventsFilter::Leave) {
        result << QLatin1String("Leave");
    }
    if (flags & TLChannelAdminLogEventsFilter::Invite) {
        result << QLatin1String("Invite");
    }
    if (flags & TLChannelAdminLogEventsFilter::Ban) {
        result << QLatin1String("Ban");
    }
    if (flags & TLChannelAdminLogEventsFilter::Unban) {
        result << QLatin1String("Unban");
    }
    if (flags & TLChannelAdminLogEventsFilter::Kick) {
        result << QLatin1String("Kick");
    }
    if (flags & TLChannelAdminLogEventsFilter::Unkick) {
        result << QLatin1String("Unkick");
    }
    if (flags & TLChannelAdminLogEventsFilter::Promote) {
        result << QLatin1String("Promote");
    }
    if (flags & TLChannelAdminLogEventsFilter::Demote) {
        result << QLatin1String("Demote");
    }
    if (flags & TLChannelAdminLogEventsFilter::Info) {
        result << QLatin1String("Info");
    }
    if (flags & TLChannelAdminLogEventsFilter::Settings) {
        result << QLatin1String("Settings");
    }
    if (flags & TLChannelAdminLogEventsFilter::Pinned) {
        result << QLatin1String("Pinned");
    }
    if (flags & TLChannelAdminLogEventsFilter::Edit) {
        result << QLatin1String("Edit");
    }
    if (flags & TLChannelAdminLogEventsFilter::Deleted) {
        result << QLatin1String("Deleted");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChannelAdminRights &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChannelAdminRights::ChangeInfo) {
        result << QLatin1String("ChangeInfo");
    }
    if (flags & TLChannelAdminRights::PostMessages) {
        result << QLatin1String("PostMessages");
    }
    if (flags & TLChannelAdminRights::EditMessages) {
        result << QLatin1String("EditMessages");
    }
    if (flags & TLChannelAdminRights::DeleteMessages) {
        result << QLatin1String("DeleteMessages");
    }
    if (flags & TLChannelAdminRights::BanUsers) {
        result << QLatin1String("BanUsers");
    }
    if (flags & TLChannelAdminRights::InviteUsers) {
        result << QLatin1String("InviteUsers");
    }
    if (flags & TLChannelAdminRights::InviteLink) {
        result << QLatin1String("InviteLink");
    }
    if (flags & TLChannelAdminRights::PinMessages) {
        result << QLatin1String("PinMessages");
    }
    if (flags & TLChannelAdminRights::AddAdmins) {
        result << QLatin1String("AddAdmins");
    }
    if (flags & TLChannelAdminRights::ManageCall) {
        result << QLatin1String("ManageCall");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChannelBannedRights &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChannelBannedRights::ViewMessages) {
        result << QLatin1String("ViewMessages");
    }
    if (flags & TLChannelBannedRights::SendMessages) {
        result << QLatin1String("SendMessages");
    }
    if (flags & TLChannelBannedRights::SendMedia) {
        result << QLatin1String("SendMedia");
    }
    if (flags & TLChannelBannedRights::SendStickers) {
        result << QLatin1String("SendStickers");
    }
    if (flags & TLChannelBannedRights::SendGifs) {
        result << QLatin1String("SendGifs");
    }
    if (flags & TLChannelBannedRights::SendGames) {
        result << QLatin1String("SendGames");
    }
    if (flags & TLChannelBannedRights::SendInline) {
        result << QLatin1String("SendInline");
    }
    if (flags & TLChannelBannedRights::EmbedLinks) {
        result << QLatin1String("EmbedLinks");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChannelMessagesFilter &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChannelMessagesFilter::ExcludeNewMessages) {
        result << QLatin1String("ExcludeNewMessages");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChannelParticipant &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChannelParticipant::CanEdit) {
        result << QLatin1String("CanEdit");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLDcOption &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLDcOption::Ipv6) {
        result << QLatin1String("Ipv6");
    }
    if (flags & TLDcOption::MediaOnly) {
        result << QLatin1String("MediaOnly");
    }
    if (flags & TLDcOption::TcpoOnly) {
        result << QLatin1String("TcpoOnly");
    }
    if (flags & TLDcOption::Cdn) {
        result << QLatin1String("Cdn");
    }
    if (flags & TLDcOption::IsStatic) {
        result << QLatin1String("IsStatic");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLDocumentAttribute &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLDocumentAttribute::RoundMessage) {
        result << QLatin1String("RoundMessage");
    }
    if (flags & TLDocumentAttribute::Mask) {
        result << QLatin1String("Mask");
    }
    if (flags & TLDocumentAttribute::Voice) {
        result << QLatin1String("Voice");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLDraftMessage &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLDraftMessage::NoWebpage) {
        result << QLatin1String("NoWebpage");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLHelpDeepLinkInfo &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLHelpDeepLinkInfo::UpdateApp) {
        result << QLatin1String("UpdateApp");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLHelpTermsOfService &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLHelpTermsOfService::Popup) {
        result << QLatin1String("Popup");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLInputPaymentCredentials &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLInputPaymentCredentials::Save) {
        result << QLatin1String("Save");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLInvoice &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLInvoice::Test) {
        result << QLatin1String("Test");
    }
    if (flags & TLInvoice::NameRequested) {
        result << QLatin1String("NameRequested");
    }
    if (flags & TLInvoice::PhoneRequested) {
        result << QLatin1String("PhoneRequested");
    }
    if (flags & TLInvoice::EmailRequested) {
        result << QLatin1String("EmailRequested");
    }
    if (flags & TLInvoice::ShippingAddressRequested) {
        result << QLatin1String("ShippingAddressRequested");
    }
    if (flags & TLInvoice::Flexible) {
        result << QLatin1String("Flexible");
    }
    if (flags & TLInvoice::PhoneToProvider) {
        result << QLatin1String("PhoneToProvider");
    }
    if (flags & TLInvoice::EmailToProvider) {
        result << QLatin1String("EmailToProvider");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLKeyboardButton &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLKeyboardButton::SamePeer) {
        result << QLatin1String("SamePeer");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLLangPackLanguage &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLLangPackLanguage::Official) {
        result << QLatin1String("Official");
    }
    if (flags & TLLangPackLanguage::Rtl) {
        result << QLatin1String("Rtl");
    }
    if (flags & TLLangPackLanguage::Beta) {
        result << QLatin1String("Beta");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessagesBotCallbackAnswer &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessagesBotCallbackAnswer::Alert) {
        result << QLatin1String("Alert");
    }
    if (flags & TLMessagesBotCallbackAnswer::HasUrl) {
        result << QLatin1String("HasUrl");
    }
    if (flags & TLMessagesBotCallbackAnswer::NativeUi) {
        result << QLatin1String("NativeUi");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessagesFilter &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessagesFilter::Missed) {
        result << QLatin1String("Missed");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessagesMessageEditData &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessagesMessageEditData::Caption) {
        result << QLatin1String("Caption");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPageTableCell &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPageTableCell::Header) {
        result << QLatin1String("Header");
    }
    if (flags & TLPageTableCell::AlignCenter) {
        result << QLatin1String("AlignCenter");
    }
    if (flags & TLPageTableCell::AlignRight) {
        result << QLatin1String("AlignRight");
    }
    if (flags & TLPageTableCell::ValignMiddle) {
        result << QLatin1String("ValignMiddle");
    }
    if (flags & TLPageTableCell::ValignBottom) {
        result << QLatin1String("ValignBottom");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPaymentsSavedInfo &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPaymentsSavedInfo::HasSavedCredentials) {
        result << QLatin1String("HasSavedCredentials");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPeerSettings &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPeerSettings::ReportSpam) {
        result << QLatin1String("ReportSpam");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPhoneCallProtocol &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPhoneCallProtocol::UdpP2p) {
        result << QLatin1String("UdpP2p");
    }
    if (flags & TLPhoneCallProtocol::UdpReflector) {
        result << QLatin1String("UdpReflector");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPhoto &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPhoto::HasStickers) {
        result << QLatin1String("HasStickers");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPoll &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPoll::Closed) {
        result << QLatin1String("Closed");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPollAnswerVoters &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPollAnswerVoters::Chosen) {
        result << QLatin1String("Chosen");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPollResults &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPollResults::Min) {
        result << QLatin1String("Min");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLReplyMarkup &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLReplyMarkup::Resize) {
        result << QLatin1String("Resize");
    }
    if (flags & TLReplyMarkup::SingleUse) {
        result << QLatin1String("SingleUse");
    }
    if (flags & TLReplyMarkup::Selective) {
        result << QLatin1String("Selective");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLSecureRequiredType &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLSecureRequiredType::NativeNames) {
        result << QLatin1String("NativeNames");
    }
    if (flags & TLSecureRequiredType::SelfieRequired) {
        result << QLatin1String("SelfieRequired");
    }
    if (flags & TLSecureRequiredType::TranslationRequired) {
        result << QLatin1String("TranslationRequired");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLStickerSet &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLStickerSet::Archived) {
        result << QLatin1String("Archived");
    }
    if (flags & TLStickerSet::Official) {
        result << QLatin1String("Official");
    }
    if (flags & TLStickerSet::Masks) {
        result << QLatin1String("Masks");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLUser &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLUser::Self) {
        result << QLatin1String("Self");
    }
    if (flags & TLUser::Contact) {
        result << QLatin1String("Contact");
    }
    if (flags & TLUser::MutualContact) {
        result << QLatin1String("MutualContact");
    }
    if (flags & TLUser::Deleted) {
        result << QLatin1String("Deleted");
    }
    if (flags & TLUser::Bot) {
        result << QLatin1String("Bot");
    }
    if (flags & TLUser::BotChatHistory) {
        result << QLatin1String("BotChatHistory");
    }
    if (flags & TLUser::BotNochats) {
        result << QLatin1String("BotNochats");
    }
    if (flags & TLUser::Verified) {
        result << QLatin1String("Verified");
    }
    if (flags & TLUser::Restricted) {
        result << QLatin1String("Restricted");
    }
    if (flags & TLUser::Min) {
        result << QLatin1String("Min");
    }
    if (flags & TLUser::BotInlineGeo) {
        result << QLatin1String("BotInlineGeo");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLAuthSentCode &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLAuthSentCode::PhoneRegistered) {
        result << QLatin1String("PhoneRegistered");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLBotInlineMessage &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLBotInlineMessage::NoWebpage) {
        result << QLatin1String("NoWebpage");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChat &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChat::Creator) {
        result << QLatin1String("Creator");
    }
    if (flags & TLChat::Kicked) {
        result << QLatin1String("Kicked");
    }
    if (flags & TLChat::Left) {
        result << QLatin1String("Left");
    }
    if (flags & TLChat::AdminsEnabled) {
        result << QLatin1String("AdminsEnabled");
    }
    if (flags & TLChat::Admin) {
        result << QLatin1String("Admin");
    }
    if (flags & TLChat::Deactivated) {
        result << QLatin1String("Deactivated");
    }
    if (flags & TLChat::Verified) {
        result << QLatin1String("Verified");
    }
    if (flags & TLChat::Megagroup) {
        result << QLatin1String("Megagroup");
    }
    if (flags & TLChat::Restricted) {
        result << QLatin1String("Restricted");
    }
    if (flags & TLChat::Democracy) {
        result << QLatin1String("Democracy");
    }
    if (flags & TLChat::Signatures) {
        result << QLatin1String("Signatures");
    }
    if (flags & TLChat::Min) {
        result << QLatin1String("Min");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChatFull &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChatFull::CanViewParticipants) {
        result << QLatin1String("CanViewParticipants");
    }
    if (flags & TLChatFull::CanSetUsername) {
        result << QLatin1String("CanSetUsername");
    }
    if (flags & TLChatFull::CanSetStickers) {
        result << QLatin1String("CanSetStickers");
    }
    if (flags & TLChatFull::HiddenPrehistory) {
        result << QLatin1String("HiddenPrehistory");
    }
    if (flags & TLChatFull::CanViewStats) {
        result << QLatin1String("CanViewStats");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLChatInvite &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLChatInvite::Channel) {
        result << QLatin1String("Channel");
    }
    if (flags & TLChatInvite::Broadcast) {
        result << QLatin1String("Broadcast");
    }
    if (flags & TLChatInvite::IsPublic) {
        result << QLatin1String("IsPublic");
    }
    if (flags & TLChatInvite::Megagroup) {
        result << QLatin1String("Megagroup");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLConfig &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLConfig::PhonecallsEnabled) {
        result << QLatin1String("PhonecallsEnabled");
    }
    if (flags & TLConfig::DefaultP2pContacts) {
        result << QLatin1String("DefaultP2pContacts");
    }
    if (flags & TLConfig::PreloadFeaturedStickers) {
        result << QLatin1String("PreloadFeaturedStickers");
    }
    if (flags & TLConfig::IgnorePhoneEntities) {
        result << QLatin1String("IgnorePhoneEntities");
    }
    if (flags & TLConfig::RevokePmInbox) {
        result << QLatin1String("RevokePmInbox");
    }
    if (flags & TLConfig::BlockedMode) {
        result << QLatin1String("BlockedMode");
    }
    if (flags & TLConfig::PfsEnabled) {
        result << QLatin1String("PfsEnabled");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLDialog &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLDialog::Pinned) {
        result << QLatin1String("Pinned");
    }
    if (flags & TLDialog::UnreadMark) {
        result << QLatin1String("UnreadMark");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLHelpAppUpdate &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLHelpAppUpdate::Popup) {
        result << QLatin1String("Popup");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLInputBotInlineMessage &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLInputBotInlineMessage::NoWebpage) {
        result << QLatin1String("NoWebpage");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLInputMedia &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLInputMedia::Stopped) {
        result << QLatin1String("Stopped");
    }
    if (flags & TLInputMedia::NosoundVideo) {
        result << QLatin1String("NosoundVideo");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPage &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPage::Part) {
        result << QLatin1String("Part");
    }
    if (flags & TLPage::Rtl) {
        result << QLatin1String("Rtl");
    }
    if (flags & TLPage::V2) {
        result << QLatin1String("V2");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPageBlock &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPageBlock::Autoplay) {
        result << QLatin1String("Autoplay");
    }
    if (flags & TLPageBlock::Loop) {
        result << QLatin1String("Loop");
    }
    if (flags & TLPageBlock::AllowScrolling) {
        result << QLatin1String("AllowScrolling");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPaymentsPaymentForm &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPaymentsPaymentForm::CanSaveCredentials) {
        result << QLatin1String("CanSaveCredentials");
    }
    if (flags & TLPaymentsPaymentForm::PasswordMissing) {
        result << QLatin1String("PasswordMissing");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLPhoneCall &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLPhoneCall::NeedRating) {
        result << QLatin1String("NeedRating");
    }
    if (flags & TLPhoneCall::NeedDebug) {
        result << QLatin1String("NeedDebug");
    }
    if (flags & TLPhoneCall::P2pAllowed) {
        result << QLatin1String("P2pAllowed");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLUserFull &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLUserFull::Blocked) {
        result << QLatin1String("Blocked");
    }
    if (flags & TLUserFull::PhoneCallsAvailable) {
        result << QLatin1String("PhoneCallsAvailable");
    }
    if (flags & TLUserFull::PhoneCallsPrivate) {
        result << QLatin1String("PhoneCallsPrivate");
    }
    if (flags & TLUserFull::CanPinMessage) {
        result << QLatin1String("CanPinMessage");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessageMedia &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessageMedia::ShippingAddressRequested) {
        result << QLatin1String("ShippingAddressRequested");
    }
    if (flags & TLMessageMedia::Test) {
        result << QLatin1String("Test");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessagesBotResults &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessagesBotResults::Gallery) {
        result << QLatin1String("Gallery");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessage &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessage::Out) {
        result << QLatin1String("Out");
    }
    if (flags & TLMessage::Mentioned) {
        result << QLatin1String("Mentioned");
    }
    if (flags & TLMessage::MediaUnread) {
        result << QLatin1String("MediaUnread");
    }
    if (flags & TLMessage::Silent) {
        result << QLatin1String("Silent");
    }
    if (flags & TLMessage::Post) {
        result << QLatin1String("Post");
    }
    if (flags & TLMessage::FromScheduled) {
        result << QLatin1String("FromScheduled");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLMessagesMessages &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLMessagesMessages::Inexact) {
        result << QLatin1String("Inexact");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLUpdate &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLUpdate::Popup) {
        result << QLatin1String("Popup");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLUpdates &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLUpdates::Out) {
        result << QLatin1String("Out");
    }
    if (flags & TLUpdates::Mentioned) {
        result << QLatin1String("Mentioned");
    }
    if (flags & TLUpdates::MediaUnread) {
        result << QLatin1String("MediaUnread");
    }
    if (flags & TLUpdates::Silent) {
        result << QLatin1String("Silent");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}

template<>
QString flagsToString(const TLUpdatesChannelDifference &instance)
{
    const quint32 flags = instance.flags;
    QStringList result;
    if (flags & TLUpdatesChannelDifference::Final) {
        result << QLatin1String("Final");
    }
    if (result.isEmpty()) {
        return QLatin1String("<no bool flags>");
    }
    return result.join(QLatin1Char('|'));
}
// End of generated TLTypes flagsToString

} // Debug namespace

} // Telegram namespace

using namespace Telegram::Debug;

// Generated TLTypes debug operators
QDebug operator<<(QDebug d, const TLAccountDaysTTL &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountDaysTTL(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountDaysTTL:
        d << "\n";
        d << spacer.innerSpaces() << "days: " << type.days <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountSentEmailCode &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountSentEmailCode(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountSentEmailCode:
        d << "\n";
        d << spacer.innerSpaces() << "emailPattern: " << type.emailPattern <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountTakeout &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountTakeout(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountTakeout:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountTmpPassword &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountTmpPassword(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountTmpPassword:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthCheckedPhone(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthCheckedPhone:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthCodeType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthCodeTypeSms:
    case TLValue::AuthCodeTypeCall:
    case TLValue::AuthCodeTypeFlashCall:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthExportedAuthorization &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthExportedAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthExportedAuthorization:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthPasswordRecovery &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthPasswordRecovery(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthPasswordRecovery:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthSentCodeType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthSentCodeTypeApp:
    case TLValue::AuthSentCodeTypeSms:
    case TLValue::AuthSentCodeTypeCall:
        d << "\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::AuthSentCodeTypeFlashCall:
        d << "\n";
        d << spacer.innerSpaces() << "pattern: " << type.pattern <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBadMsgNotification &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLBadMsgNotification(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BadMsgNotification:
        d << "\n";
        d << spacer.innerSpaces() << "badMsgId: " << type.badMsgId <<"\n";
        d << spacer.innerSpaces() << "badMsgSeqno: " << type.badMsgSeqno <<"\n";
        d << spacer.innerSpaces() << "errorCode: " << type.errorCode <<"\n";
        break;
    case TLValue::BadServerSalt:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLBotCommand(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotCommand:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLBotInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInfo:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLCdnPublicKey &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLCdnPublicKey(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::CdnPublicKey:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelParticipantsFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelParticipantsRecent:
    case TLValue::ChannelParticipantsAdmins:
    case TLValue::ChannelParticipantsBots:
        d << " }";
        return d;
    case TLValue::ChannelParticipantsKicked:
    case TLValue::ChannelParticipantsBanned:
    case TLValue::ChannelParticipantsSearch:
        d << "\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatOnlines &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChatOnlines(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatOnlines:
        d << "\n";
        d << spacer.innerSpaces() << "onlines: " << type.onlines <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChatParticipant &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChatParticipant(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatParticipant:
    case TLValue::ChatParticipantAdmin:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChatParticipantCreator:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChatParticipants(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatParticipantsForbidden:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "selfParticipant: " << type.selfParticipant <<"\n";
        }
        break;
    case TLValue::ChatParticipants:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLClientDHInnerData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ClientDHInnerData:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Contact:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactBlocked(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactBlocked:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactLink(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactLinkUnknown:
    case TLValue::ContactLinkNone:
    case TLValue::ContactLinkHasPhone:
    case TLValue::ContactLinkContact:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDataJSON &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDataJSON(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DataJSON:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDestroyAuthKeyRes(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DestroyAuthKeyOk:
    case TLValue::DestroyAuthKeyNone:
    case TLValue::DestroyAuthKeyFail:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDestroySessionRes &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDestroySessionRes(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DestroySessionOk:
    case TLValue::DestroySessionNone:
        d << "\n";
        d << spacer.innerSpaces() << "sessionId: " << type.sessionId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLEncryptedChat &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLEncryptedChat(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedChatEmpty:
    case TLValue::EncryptedChatDiscarded:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::EncryptedChatWaiting:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        break;
    case TLValue::EncryptedChatRequested:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gA: " << type.gA.toHex() <<"\n";
        break;
    case TLValue::EncryptedChat:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLEncryptedFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedFileEmpty:
        d << " }";
        return d;
    case TLValue::EncryptedFile:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLEncryptedMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::EncryptedMessage:
        d << "\n";
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        break;
    case TLValue::EncryptedMessageService:
        d << "\n";
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLError &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLError(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Error:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLExportedChatInvite(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatInviteEmpty:
        d << " }";
        return d;
    case TLValue::ChatInviteExported:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLExportedMessageLink(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ExportedMessageLink:
        d << "\n";
        d << spacer.innerSpaces() << "link: " << type.link <<"\n";
        d << spacer.innerSpaces() << "html: " << type.html <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFileHash &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLFileHash(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FileHash:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLFileLocation &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLFileLocation(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FileLocationUnavailable:
        d << "\n";
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        break;
    case TLValue::FileLocation:
        d << "\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLFutureSalt &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLFutureSalt(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FutureSalt:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLFutureSalts(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FutureSalts:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLGeoPoint(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::GeoPointEmpty:
        d << " }";
        return d;
    case TLValue::GeoPoint:
        d << "\n";
        d << spacer.innerSpaces() << "longitude: " << type.longitude <<"\n";
        d << spacer.innerSpaces() << "latitude: " << type.latitude <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpInviteText &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpInviteText(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpInviteText:
        d << "\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpPassportConfig &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpPassportConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpPassportConfigNotModified:
        d << " }";
        return d;
    case TLValue::HelpPassportConfig:
        d << "\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "countriesLangs: " << type.countriesLangs <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpSupportName &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpSupportName(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpSupportName:
        d << "\n";
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHighScore &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHighScore(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HighScore:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHttpWait(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HttpWait:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLImportedContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ImportedContact:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInlineBotSwitchPM(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InlineBotSwitchPM:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputAppEvent(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputAppEvent:
        d << "\n";
        d << spacer.innerSpaces() << "time: " << type.time <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "data: " << *type.data <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputBotInlineMessageID &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputBotInlineMessageID(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineMessageID:
        d << "\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputChannel &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputChannel(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputChannelEmpty:
        d << " }";
        return d;
    case TLValue::InputChannel:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputCheckPasswordSRP &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputCheckPasswordSRP(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputCheckPasswordEmpty:
        d << " }";
        return d;
    case TLValue::InputCheckPasswordSRP:
        d << "\n";
        d << spacer.innerSpaces() << "srpId: " << type.srpId <<"\n";
        d << spacer.innerSpaces() << "A: " << type.A.toHex() <<"\n";
        d << spacer.innerSpaces() << "M1: " << type.M1.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputClientProxy &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputClientProxy(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputClientProxy:
        d << "\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputContact &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhoneContact:
        d << "\n";
        d << spacer.innerSpaces() << "clientId: " << type.clientId <<"\n";
        d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputDocumentEmpty:
        d << " }";
        return d;
    case TLValue::InputDocument:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputEncryptedChat &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputEncryptedChat(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputEncryptedChat:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputEncryptedFile &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputEncryptedFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputEncryptedFileEmpty:
        d << " }";
        return d;
    case TLValue::InputEncryptedFileUploaded:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "md5Checksum: " << type.md5Checksum <<"\n";
        d << spacer.innerSpaces() << "keyFingerprint: " << type.keyFingerprint <<"\n";
        break;
    case TLValue::InputEncryptedFile:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    case TLValue::InputEncryptedFileBigUploaded:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputFile:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        d << spacer.innerSpaces() << "md5Checksum: " << type.md5Checksum <<"\n";
        break;
    case TLValue::InputFileBig:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputFileLocation(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputFileLocation:
        d << "\n";
        d << spacer.innerSpaces() << "volumeId: " << type.volumeId <<"\n";
        d << spacer.innerSpaces() << "localId: " << type.localId <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
        break;
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputSecureFileLocation:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    case TLValue::InputDocumentFileLocation:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
        break;
    case TLValue::InputTakeoutFileLocation:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputGeoPoint &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputGeoPoint(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputGeoPointEmpty:
        d << " }";
        return d;
    case TLValue::InputGeoPoint:
        d << "\n";
        d << spacer.innerSpaces() << "latitude: " << type.latitude <<"\n";
        d << spacer.innerSpaces() << "longitude: " << type.longitude <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputMessage &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputMessageID:
    case TLValue::InputMessageReplyTo:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::InputMessagePinned:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
        d << " }";
        return d;
    case TLValue::InputPeerChat:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::InputPeerUser:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    case TLValue::InputPeerChannel:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPeerNotifySettings &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPeerNotifySettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPeerNotifySettings:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "showPreviews: " << type.showPreviews <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "silent: " << type.silent <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "muteUntil: " << type.muteUntil <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "sound: " << type.sound <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPhoneCall &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPhoneCall(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhoneCall:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPhoto &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPhotoEmpty:
        d << " }";
        return d;
    case TLValue::InputPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPrivacyKey &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPrivacyKey(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
    case TLValue::InputPrivacyKeyChatInvite:
    case TLValue::InputPrivacyKeyPhoneCall:
    case TLValue::InputPrivacyKeyPhoneP2P:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputSecureFile &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputSecureFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputSecureFileUploaded:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "parts: " << type.parts <<"\n";
        d << spacer.innerSpaces() << "md5Checksum: " << type.md5Checksum <<"\n";
        d << spacer.innerSpaces() << "fileHash: " << type.fileHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret.toHex() <<"\n";
        break;
    case TLValue::InputSecureFile:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputStickerSet &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputStickerSet(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputStickerSetEmpty:
        d << " }";
        return d;
    case TLValue::InputStickerSetID:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    case TLValue::InputStickerSetShortName:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputStickeredMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputStickeredMediaPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "inputPhotoId: " << type.inputPhotoId <<"\n";
        break;
    case TLValue::InputStickeredMediaDocument:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputUser(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputUserEmpty:
    case TLValue::InputUserSelf:
        d << " }";
        return d;
    case TLValue::InputUser:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputWebFileLocation &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputWebFileLocation(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputWebFileLocation:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    case TLValue::InputWebFileGeoPointLocation:
        d << "\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "zoom: " << type.zoom <<"\n";
        d << spacer.innerSpaces() << "scale: " << type.scale <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLIpPort &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLIpPort(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::IpPort:
        d << "\n";
        d << spacer.innerSpaces() << "ipv4: " << type.ipv4 <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        break;
    case TLValue::IpPortSecret:
        d << "\n";
        d << spacer.innerSpaces() << "ipv4: " << type.ipv4 <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLJSONObjectValue &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLJSONObjectValue(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::JsonObjectValue:
        d << "\n";
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        d << spacer.innerSpaces() << "value: " << *type.value <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLJSONValue &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLJSONValue(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::JsonNull:
        d << " }";
        return d;
    case TLValue::JsonBool:
        d << "\n";
        d << spacer.innerSpaces() << "boolValue: " << type.boolValue <<"\n";
        break;
    case TLValue::JsonNumber:
        d << "\n";
        d << spacer.innerSpaces() << "doubleValue: " << type.doubleValue <<"\n";
        break;
    case TLValue::JsonString:
        d << "\n";
        d << spacer.innerSpaces() << "stringValue: " << type.stringValue <<"\n";
        break;
    case TLValue::JsonArray:
        d << "\n";
        d << spacer.innerSpaces() << "jSONValueVector: " << type.jSONValueVector <<"\n";
        break;
    case TLValue::JsonObject:
        d << "\n";
        d << spacer.innerSpaces() << "jSONObjectValueVector: " << type.jSONObjectValueVector <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLLabeledPrice &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLLabeledPrice(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LabeledPrice:
        d << "\n";
        d << spacer.innerSpaces() << "label: " << type.label <<"\n";
        d << spacer.innerSpaces() << "amount: " << type.amount <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLLangPackString &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLLangPackString(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LangPackString:
        d << "\n";
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        d << spacer.innerSpaces() << "value: " << type.value <<"\n";
        break;
    case TLValue::LangPackStringPluralized:
        d << "\n";
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
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMaskCoords(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MaskCoords:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
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
    case TLValue::MessageEntityPhone:
    case TLValue::MessageEntityCashtag:
        d << "\n";
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        break;
    case TLValue::MessageEntityPre:
        d << "\n";
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "language: " << type.language <<"\n";
        break;
    case TLValue::MessageEntityTextUrl:
        d << "\n";
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    case TLValue::MessageEntityMentionName:
        d << "\n";
        d << spacer.innerSpaces() << "offset: " << type.offset <<"\n";
        d << spacer.innerSpaces() << "length: " << type.length <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::InputMessageEntityMentionName:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLMessageRange &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessageRange(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageRange:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesAffectedHistory(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesAffectedHistory:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesAffectedMessages(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesAffectedMessages:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesDhConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesDhConfigNotModified:
        d << "\n";
        d << spacer.innerSpaces() << "random: " << type.random.toHex() <<"\n";
        break;
    case TLValue::MessagesDhConfig:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesSentEncryptedMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesSentEncryptedMessage:
        d << "\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::MessagesSentEncryptedFile:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMsgDetailedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgDetailedInfo:
        d << "\n";
        d << spacer.innerSpaces() << "msgId: " << type.msgId <<"\n";
        d << spacer.innerSpaces() << "answerMsgId: " << type.answerMsgId <<"\n";
        d << spacer.innerSpaces() << "bytes: " << type.bytes <<"\n";
        d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        break;
    case TLValue::MsgNewDetailedInfo:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMsgResendReq(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgResendReq:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMsgsAck(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsAck:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMsgsAllInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsAllInfo:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMsgsStateInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsStateInfo:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMsgsStateReq(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MsgsStateReq:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLNearestDc(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NearestDc:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLNewSession(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NewSessionCreated:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPQInnerData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PQInnerData:
        d << "\n";
        d << spacer.innerSpaces() << "pq: " << type.pq <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonce: " << type.newNonce <<"\n";
        break;
    case TLValue::PQInnerDataDc:
        d << "\n";
        d << spacer.innerSpaces() << "pq: " << type.pq <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonce: " << type.newNonce <<"\n";
        d << spacer.innerSpaces() << "dc: " << type.dc <<"\n";
        break;
    case TLValue::PQInnerDataTemp:
        d << "\n";
        d << spacer.innerSpaces() << "pq: " << type.pq <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonce: " << type.newNonce <<"\n";
        d << spacer.innerSpaces() << "expiresIn: " << type.expiresIn <<"\n";
        break;
    case TLValue::PQInnerDataTempDc:
        d << "\n";
        d << spacer.innerSpaces() << "pq: " << type.pq <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonce: " << type.newNonce <<"\n";
        d << spacer.innerSpaces() << "dc: " << type.dc <<"\n";
        d << spacer.innerSpaces() << "expiresIn: " << type.expiresIn <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageCaption &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageCaption(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageCaption:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << *type.text <<"\n";
        d << spacer.innerSpaces() << "credit: " << *type.credit <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageListItem &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageListItem(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageListItemText:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << *type.text <<"\n";
        break;
    case TLValue::PageListItemBlocks:
        d << "\n";
        d << spacer.innerSpaces() << "blocks: " << type.blocks <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageListOrderedItem &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageListOrderedItem(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageListOrderedItemText:
        d << "\n";
        d << spacer.innerSpaces() << "num: " << type.num <<"\n";
        d << spacer.innerSpaces() << "text: " << *type.text <<"\n";
        break;
    case TLValue::PageListOrderedItemBlocks:
        d << "\n";
        d << spacer.innerSpaces() << "num: " << type.num <<"\n";
        d << spacer.innerSpaces() << "blocks: " << type.blocks <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageRelatedArticle &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageRelatedArticle(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageRelatedArticle:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "webpageId: " << type.webpageId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "photoId: " << type.photoId <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "author: " << type.author <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "publishedDate: " << type.publishedDate <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPasswordKdfAlgo &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPasswordKdfAlgo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PasswordKdfAlgoUnknown:
        d << " }";
        return d;
    case TLValue::PasswordKdfAlgoSHA256SHA256PBKDF2HMACSHA512iter100000SHA256ModPow:
        d << "\n";
        d << spacer.innerSpaces() << "salt1: " << type.salt1.toHex() <<"\n";
        d << spacer.innerSpaces() << "salt2: " << type.salt2.toHex() <<"\n";
        d << spacer.innerSpaces() << "g: " << type.g <<"\n";
        d << spacer.innerSpaces() << "p: " << type.p.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentCharge &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentCharge(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentCharge:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentSavedCredentials(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentSavedCredentialsCard:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerUser:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::PeerChat:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::PeerChannel:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPeerNotifySettings &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPeerNotifySettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerNotifySettings:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "showPreviews: " << type.showPreviews <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "silent: " << type.silent <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "muteUntil: " << type.muteUntil <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "sound: " << type.sound <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneCallDiscardReason &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhoneCallDiscardReason(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneCallDiscardReasonMissed:
    case TLValue::PhoneCallDiscardReasonDisconnect:
    case TLValue::PhoneCallDiscardReasonHangup:
    case TLValue::PhoneCallDiscardReasonBusy:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneConnection &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhoneConnection(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneConnection:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhotoSize(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotoSizeEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        break;
    case TLValue::PhotoSize:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "location: " << type.location <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        break;
    case TLValue::PhotoCachedSize:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "location: " << type.location <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    case TLValue::PhotoStrippedSize:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPollAnswer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPollAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PollAnswer:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "option: " << type.option.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPong &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPong(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Pong:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPopularContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PopularContact:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPostAddress(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PostAddress:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPrivacyKey(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
    case TLValue::PrivacyKeyChatInvite:
    case TLValue::PrivacyKeyPhoneCall:
    case TLValue::PrivacyKeyPhoneP2P:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPrivacyRule &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPrivacyRule(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PrivacyValueAllowContacts:
    case TLValue::PrivacyValueAllowAll:
    case TLValue::PrivacyValueDisallowContacts:
    case TLValue::PrivacyValueDisallowAll:
        d << " }";
        return d;
    case TLValue::PrivacyValueAllowUsers:
    case TLValue::PrivacyValueDisallowUsers:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLReceivedNotifyMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ReceivedNotifyMessage:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLReportReason(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputReportReasonSpam:
    case TLValue::InputReportReasonViolence:
    case TLValue::InputReportReasonPornography:
    case TLValue::InputReportReasonChildAbuse:
    case TLValue::InputReportReasonCopyright:
        d << " }";
        return d;
    case TLValue::InputReportReasonOther:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLResPQ(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ResPQ:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLRichText(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TextEmpty:
        d << " }";
        return d;
    case TLValue::TextPlain:
        d << "\n";
        d << spacer.innerSpaces() << "stringText: " << type.stringText <<"\n";
        break;
    case TLValue::TextBold:
    case TLValue::TextItalic:
    case TLValue::TextUnderline:
    case TLValue::TextStrike:
    case TLValue::TextFixed:
    case TLValue::TextSubscript:
    case TLValue::TextSuperscript:
    case TLValue::TextMarked:
        d << "\n";
        d << spacer.innerSpaces() << "richText: " << *type.richText <<"\n";
        break;
    case TLValue::TextUrl:
        d << "\n";
        d << spacer.innerSpaces() << "richText: " << *type.richText <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "webpageId: " << type.webpageId <<"\n";
        break;
    case TLValue::TextEmail:
        d << "\n";
        d << spacer.innerSpaces() << "richText: " << *type.richText <<"\n";
        d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        break;
    case TLValue::TextConcat:
        d << "\n";
        d << spacer.innerSpaces() << "texts: " << type.texts <<"\n";
        break;
    case TLValue::TextPhone:
        d << "\n";
        d << spacer.innerSpaces() << "richText: " << *type.richText <<"\n";
        d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
        break;
    case TLValue::TextImage:
        d << "\n";
        d << spacer.innerSpaces() << "documentId: " << type.documentId <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::TextAnchor:
        d << "\n";
        d << spacer.innerSpaces() << "richText: " << *type.richText <<"\n";
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLRpcDropAnswer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLRpcDropAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::RpcAnswerUnknown:
    case TLValue::RpcAnswerDroppedRunning:
        d << " }";
        return d;
    case TLValue::RpcAnswerDropped:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLRpcError(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::RpcError:
        d << "\n";
        d << spacer.innerSpaces() << "errorCode: " << type.errorCode <<"\n";
        d << spacer.innerSpaces() << "errorMessage: " << type.errorMessage <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSavedContact &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSavedContact(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SavedPhoneContact:
        d << "\n";
        d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureCredentialsEncrypted &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureCredentialsEncrypted(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureCredentialsEncrypted:
        d << "\n";
        d << spacer.innerSpaces() << "data: " << type.data.toHex() <<"\n";
        d << spacer.innerSpaces() << "hash: " << type.hash.toHex() <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureData &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureData:
        d << "\n";
        d << spacer.innerSpaces() << "data: " << type.data.toHex() <<"\n";
        d << spacer.innerSpaces() << "dataHash: " << type.dataHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureFile &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureFileEmpty:
        d << " }";
        return d;
    case TLValue::SecureFile:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "fileHash: " << type.fileHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "secret: " << type.secret.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecurePasswordKdfAlgo &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecurePasswordKdfAlgo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecurePasswordKdfAlgoUnknown:
        d << " }";
        return d;
    case TLValue::SecurePasswordKdfAlgoPBKDF2HMACSHA512iter100000:
    case TLValue::SecurePasswordKdfAlgoSHA512:
        d << "\n";
        d << spacer.innerSpaces() << "salt: " << type.salt.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecurePlainData &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecurePlainData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecurePlainPhone:
        d << "\n";
        d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
        break;
    case TLValue::SecurePlainEmail:
        d << "\n";
        d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureSecretSettings &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureSecretSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureSecretSettings:
        d << "\n";
        d << spacer.innerSpaces() << "secureAlgo: " << type.secureAlgo <<"\n";
        d << spacer.innerSpaces() << "secureSecret: " << type.secureSecret.toHex() <<"\n";
        d << spacer.innerSpaces() << "secureSecretId: " << type.secureSecretId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureValueType &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureValueType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
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
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSendMessageAction &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
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
        d << " }";
        return d;
    case TLValue::SendMessageUploadVideoAction:
    case TLValue::SendMessageUploadAudioAction:
    case TLValue::SendMessageUploadPhotoAction:
    case TLValue::SendMessageUploadDocumentAction:
    case TLValue::SendMessageUploadRoundAction:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLServerDHInnerData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ServerDHInnerData:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLServerDHParams(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ServerDHParamsFail:
        d << "\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash: " << type.newNonceHash <<"\n";
        break;
    case TLValue::ServerDHParamsOk:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSetClientDHParamsAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DhGenOk:
        d << "\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash1: " << type.newNonceHash1 <<"\n";
        break;
    case TLValue::DhGenRetry:
        d << "\n";
        d << spacer.innerSpaces() << "nonce: " << type.nonce <<"\n";
        d << spacer.innerSpaces() << "serverNonce: " << type.serverNonce <<"\n";
        d << spacer.innerSpaces() << "newNonceHash2: " << type.newNonceHash2 <<"\n";
        break;
    case TLValue::DhGenFail:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLShippingOption(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ShippingOption:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLStatsURL &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLStatsURL(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StatsURL:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStickerPack &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLStickerPack(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StickerPack:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
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
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLTopPeer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLTopPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TopPeer:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLTopPeerCategory(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TopPeerCategoryBotsPM:
    case TLValue::TopPeerCategoryBotsInline:
    case TLValue::TopPeerCategoryCorrespondents:
    case TLValue::TopPeerCategoryGroups:
    case TLValue::TopPeerCategoryChannels:
    case TLValue::TopPeerCategoryPhoneCalls:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLTopPeerCategoryPeers &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLTopPeerCategoryPeers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::TopPeerCategoryPeers:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUpdatesState(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesState:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUploadCdnFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadCdnFileReuploadNeeded:
        d << "\n";
        d << spacer.innerSpaces() << "requestToken: " << type.requestToken.toHex() <<"\n";
        break;
    case TLValue::UploadCdnFile:
        d << "\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUploadFile &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUploadFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadFile:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "mtime: " << type.mtime <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    case TLValue::UploadFileCdnRedirect:
        d << "\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "fileToken: " << type.fileToken.toHex() <<"\n";
        d << spacer.innerSpaces() << "encryptionKey: " << type.encryptionKey.toHex() <<"\n";
        d << spacer.innerSpaces() << "encryptionIv: " << type.encryptionIv.toHex() <<"\n";
        d << spacer.innerSpaces() << "fileHashes: " << type.fileHashes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUploadWebFile &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUploadWebFile(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UploadWebFile:
        d << "\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "fileType: " << type.fileType <<"\n";
        d << spacer.innerSpaces() << "mtime: " << type.mtime <<"\n";
        d << spacer.innerSpaces() << "bytes: " << printBytes(type.bytes) <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUserProfilePhoto &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUserProfilePhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserProfilePhotoEmpty:
        d << " }";
        return d;
    case TLValue::UserProfilePhoto:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUserStatus(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserStatusEmpty:
    case TLValue::UserStatusRecently:
    case TLValue::UserStatusLastWeek:
    case TLValue::UserStatusLastMonth:
        d << " }";
        return d;
    case TLValue::UserStatusOnline:
        d << "\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        break;
    case TLValue::UserStatusOffline:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLWallPaper(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WallPaper:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "sizes: " << type.sizes <<"\n";
        d << spacer.innerSpaces() << "color: " << type.color <<"\n";
        break;
    case TLValue::WallPaperSolid:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLWebAuthorization &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLWebAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WebAuthorization:
        d << "\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "botId: " << type.botId <<"\n";
        d << spacer.innerSpaces() << "domain: " << type.domain <<"\n";
        d << spacer.innerSpaces() << "browser: " << type.browser <<"\n";
        d << spacer.innerSpaces() << "platform: " << type.platform <<"\n";
        d << spacer.innerSpaces() << "dateCreated: " << type.dateCreated <<"\n";
        d << spacer.innerSpaces() << "dateActive: " << type.dateActive <<"\n";
        d << spacer.innerSpaces() << "ip: " << type.ip <<"\n";
        d << spacer.innerSpaces() << "region: " << type.region <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccessPointRule &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccessPointRule(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccessPointRule:
        d << "\n";
        d << spacer.innerSpaces() << "phonePrefixRules: " << type.phonePrefixRules <<"\n";
        d << spacer.innerSpaces() << "dcId: " << type.dcId <<"\n";
        d << spacer.innerSpaces() << "ips: " << type.ips <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPassword &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountPassword(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPassword:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "currentAlgo: " << type.currentAlgo <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "srpB: " << type.srpB.toHex() <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "srpId: " << type.srpId <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "hint: " << type.hint <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "emailUnconfirmedPattern: " << type.emailUnconfirmedPattern <<"\n";
        }
        d << spacer.innerSpaces() << "newAlgo: " << type.newAlgo <<"\n";
        d << spacer.innerSpaces() << "newSecureAlgo: " << type.newSecureAlgo <<"\n";
        d << spacer.innerSpaces() << "secureRandom: " << type.secureRandom.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPasswordInputSettings &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountPasswordInputSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPasswordInputSettings:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "newAlgo: " << type.newAlgo <<"\n";
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
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "newSecureSettings: " << type.newSecureSettings <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountPasswordSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPasswordSettings:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "email: " << type.email <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "secureSettings: " << type.secureSettings <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAuthorization &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Authorization:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
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

QDebug operator<<(QDebug d, const TLCdnConfig &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLCdnConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::CdnConfig:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelAdminLogEventsFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminLogEventsFilter:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelAdminRights &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelAdminRights(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminRights:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChannelBannedRights &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelBannedRights(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelBannedRights:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelMessagesFilter(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelMessagesFilterEmpty:
        d << " }";
        return d;
    case TLValue::ChannelMessagesFilter:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelParticipant(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelParticipant:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantSelf:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::ChannelParticipantCreator:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::ChannelParticipantAdmin:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "promotedBy: " << type.promotedBy <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminRights: " << type.adminRights <<"\n";
        break;
    case TLValue::ChannelParticipantBanned:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChatPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatPhotoEmpty:
        d << " }";
        return d;
    case TLValue::ChatPhoto:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactStatus(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactStatus:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDcOption(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DcOption:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "ipAddress: " << type.ipAddress <<"\n";
        d << spacer.innerSpaces() << "port: " << type.port <<"\n";
        if (type.flags & 1 << 10) {
            d << spacer.innerSpaces() << "secret: " << type.secret.toHex() <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDialogPeer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDialogPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DialogPeer:
        d << "\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLDocumentAttribute &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDocumentAttribute(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DocumentAttributeImageSize:
        d << "\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::DocumentAttributeAnimated:
    case TLValue::DocumentAttributeHasStickers:
        d << " }";
        return d;
    case TLValue::DocumentAttributeSticker:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "alt: " << type.alt <<"\n";
        d << spacer.innerSpaces() << "stickerset: " << type.stickerset <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "maskCoords: " << type.maskCoords <<"\n";
        }
        break;
    case TLValue::DocumentAttributeVideo:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "duration: " << type.duration <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::DocumentAttributeAudio:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDraftMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DraftMessageEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        }
        break;
    case TLValue::DraftMessage:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpConfigSimple(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpConfigSimple:
        d << "\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        d << spacer.innerSpaces() << "rules: " << type.rules <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpDeepLinkInfo &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpDeepLinkInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpDeepLinkInfoEmpty:
        d << " }";
        return d;
    case TLValue::HelpDeepLinkInfo:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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

QDebug operator<<(QDebug d, const TLHelpTermsOfService &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpTermsOfService(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpTermsOfService:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "minAgeConfirm: " << type.minAgeConfirm <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpTermsOfServiceUpdate &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpTermsOfServiceUpdate(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpTermsOfServiceUpdateEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        break;
    case TLValue::HelpTermsOfServiceUpdate:
        d << "\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        d << spacer.innerSpaces() << "termsOfService: " << type.termsOfService <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpUserInfo &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpUserInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpUserInfoEmpty:
        d << " }";
        return d;
    case TLValue::HelpUserInfo:
        d << "\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        d << spacer.innerSpaces() << "author: " << type.author <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputChatPhoto &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputChatPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputChatPhotoEmpty:
        d << " }";
        return d;
    case TLValue::InputChatUploadedPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        break;
    case TLValue::InputChatPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputDialogPeer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputDialogPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputDialogPeer:
        d << "\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputGame &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputGame(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputGameID:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        break;
    case TLValue::InputGameShortName:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputNotifyPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputNotifyPeer:
        d << "\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    case TLValue::InputNotifyUsers:
    case TLValue::InputNotifyChats:
    case TLValue::InputNotifyBroadcasts:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPaymentCredentials &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPaymentCredentials(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPaymentCredentialsSaved:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "tmpPassword: " << type.tmpPassword.toHex() <<"\n";
        break;
    case TLValue::InputPaymentCredentials:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "data: " << type.data <<"\n";
        break;
    case TLValue::InputPaymentCredentialsApplePay:
        d << "\n";
        d << spacer.innerSpaces() << "paymentData: " << type.paymentData <<"\n";
        break;
    case TLValue::InputPaymentCredentialsAndroidPay:
        d << "\n";
        d << spacer.innerSpaces() << "paymentToken: " << type.paymentToken <<"\n";
        d << spacer.innerSpaces() << "googleTransactionId: " << type.googleTransactionId <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputPrivacyRule &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputPrivacyRule(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
    case TLValue::InputPrivacyValueAllowAll:
    case TLValue::InputPrivacyValueDisallowContacts:
    case TLValue::InputPrivacyValueDisallowAll:
        d << " }";
        return d;
    case TLValue::InputPrivacyValueAllowUsers:
    case TLValue::InputPrivacyValueDisallowUsers:
        d << "\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputSecureValue &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputSecureValue(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputSecureValue:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "data: " << type.data <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "frontSide: " << type.frontSide <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "reverseSide: " << type.reverseSide <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "selfie: " << type.selfie <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "translation: " << type.translation <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "files: " << type.files <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "plainData: " << type.plainData <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputStickerSetItem &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputStickerSetItem(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputStickerSetItem:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputWebDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputWebDocument:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInvoice(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Invoice:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLKeyboardButton(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::KeyboardButton:
    case TLValue::KeyboardButtonRequestPhone:
    case TLValue::KeyboardButtonRequestGeoLocation:
    case TLValue::KeyboardButtonGame:
    case TLValue::KeyboardButtonBuy:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::KeyboardButtonUrl:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    case TLValue::KeyboardButtonCallback:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "data: " << type.data.toHex() <<"\n";
        break;
    case TLValue::KeyboardButtonSwitchInline:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLKeyboardButtonRow(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::KeyboardButtonRow:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLLangPackDifference(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LangPackDifference:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLLangPackLanguage &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLLangPackLanguage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::LangPackLanguage:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        d << spacer.innerSpaces() << "nativeName: " << type.nativeName <<"\n";
        d << spacer.innerSpaces() << "langCode: " << type.langCode <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "baseLangCode: " << type.baseLangCode <<"\n";
        }
        d << spacer.innerSpaces() << "pluralCode: " << type.pluralCode <<"\n";
        d << spacer.innerSpaces() << "stringsCount: " << type.stringsCount <<"\n";
        d << spacer.innerSpaces() << "translatedCount: " << type.translatedCount <<"\n";
        d << spacer.innerSpaces() << "translationsUrl: " << type.translationsUrl <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageFwdHeader &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessageFwdHeader(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageFwdHeader:
        d << "\n";
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
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "savedFromPeer: " << type.savedFromPeer <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "savedFromMsgId: " << type.savedFromMsgId <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesBotCallbackAnswer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesBotCallbackAnswer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesBotCallbackAnswer:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
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
        d << " }";
        return d;
    case TLValue::InputMessagesFilterPhoneCalls:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesMessageEditData &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesMessageEditData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesMessageEditData:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLNotifyPeer &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLNotifyPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::NotifyPeer:
        d << "\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        break;
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyBroadcasts:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageTableCell &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageTableCell(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageTableCell:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "colspan: " << type.colspan <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "rowspan: " << type.rowspan <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPageTableRow &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageTableRow(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageTableRow:
        d << "\n";
        d << spacer.innerSpaces() << "cells: " << type.cells <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentRequestedInfo &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentRequestedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentRequestedInfo:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentsSavedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsSavedInfo:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentsValidatedRequestedInfo(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsValidatedRequestedInfo:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLPeerSettings &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPeerSettings(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PeerSettings:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPhoneCallProtocol &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhoneCallProtocol(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneCallProtocol:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotoEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Photo:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "sizes: " << type.sizes <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPoll &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPoll(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Poll:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "question: " << type.question <<"\n";
        d << spacer.innerSpaces() << "answers: " << type.answers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPollAnswerVoters &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPollAnswerVoters(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PollAnswerVoters:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "option: " << type.option.toHex() <<"\n";
        d << spacer.innerSpaces() << "voters: " << type.voters <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPollResults &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPollResults(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PollResults:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "totalVoters: " << type.totalVoters <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLReplyMarkup &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLReplyMarkup(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ReplyKeyboardHide:
    case TLValue::ReplyKeyboardForceReply:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        break;
    case TLValue::ReplyKeyboardMarkup:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "rows: " << type.rows <<"\n";
        break;
    case TLValue::ReplyInlineMarkup:
        d << "\n";
        d << spacer.innerSpaces() << "rows: " << type.rows <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureRequiredType &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureRequiredType(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureRequiredType:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        break;
    case TLValue::SecureRequiredTypeOneOf:
        d << "\n";
        d << spacer.innerSpaces() << "types: " << type.types <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureValue &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureValue(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureValue:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "data: " << type.data <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "frontSide: " << type.frontSide <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "reverseSide: " << type.reverseSide <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "selfie: " << type.selfie <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "translation: " << type.translation <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "files: " << type.files <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "plainData: " << type.plainData <<"\n";
        }
        d << spacer.innerSpaces() << "hash: " << type.hash.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureValueError &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureValueError(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureValueErrorData:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "dataHash: " << type.dataHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "field: " << type.field <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::SecureValueErrorFrontSide:
    case TLValue::SecureValueErrorReverseSide:
    case TLValue::SecureValueErrorSelfie:
    case TLValue::SecureValueErrorFile:
    case TLValue::SecureValueErrorTranslationFile:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "byteArrayFileHash: " << type.byteArrayFileHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::SecureValueErrorFiles:
    case TLValue::SecureValueErrorTranslationFiles:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "byteArrayFileHashVector: " << type.byteArrayFileHashVector <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    case TLValue::SecureValueError:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "hash: " << type.hash.toHex() <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLSecureValueHash &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLSecureValueHash(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::SecureValueHash:
        d << "\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "hash: " << type.hash.toHex() <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLStickerSet &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLStickerSet(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StickerSet:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "installedDate: " << type.installedDate <<"\n";
        }
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUser(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::User:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
            d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLWebDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WebDocument:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "size: " << type.size <<"\n";
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        break;
    case TLValue::WebDocumentNoProxy:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLAccountAuthorizationForm &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountAuthorizationForm(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountAuthorizationForm:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "requiredTypes: " << type.requiredTypes <<"\n";
        d << spacer.innerSpaces() << "values: " << type.values <<"\n";
        d << spacer.innerSpaces() << "errors: " << type.errors <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "privacyPolicyUrl: " << type.privacyPolicyUrl <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountAuthorizations &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountAuthorizations(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountAuthorizations:
        d << "\n";
        d << spacer.innerSpaces() << "authorizations: " << type.authorizations <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountPrivacyRules &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountPrivacyRules(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountPrivacyRules:
        d << "\n";
        d << spacer.innerSpaces() << "rules: " << type.rules <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLAccountWebAuthorizations &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAccountWebAuthorizations(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AccountWebAuthorizations:
        d << "\n";
        d << spacer.innerSpaces() << "authorizations: " << type.authorizations <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthAuthorization(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthAuthorization:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLAuthSentCode &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLAuthSentCode(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::AuthSentCode:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "phoneCodeHash: " << type.phoneCodeHash <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "nextType: " << type.nextType <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        }
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "termsOfService: " << type.termsOfService <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBotInlineMessage &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLBotInlineMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInlineMessageMediaAuto:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageText:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageMediaGeo:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageMediaVenue:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        d << spacer.innerSpaces() << "venueType: " << type.venueType <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::BotInlineMessageMediaContact:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "phoneNumber: " << Telegram::Utils::maskPhoneNumber(type.phoneNumber) <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "vcard: " << type.vcard <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelsChannelParticipant(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsChannelParticipant:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelsChannelParticipants(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsChannelParticipants:
        d << "\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::ChannelsChannelParticipantsNotModified:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLChat &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChat(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Chat:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    case TLValue::Channel:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        if (type.flags & 1 << 13) {
            d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
        if (type.flags & 1 << 17) {
            d << spacer.innerSpaces() << "participantsCount: " << type.participantsCount <<"\n";
        }
        break;
    case TLValue::ChannelForbidden:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChatFull(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatFull:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "chatPhoto: " << type.chatPhoto <<"\n";
        }
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        d << spacer.innerSpaces() << "exportedInvite: " << type.exportedInvite <<"\n";
        if (type.flags & 1 << 3) {
            d << spacer.innerSpaces() << "botInfo: " << type.botInfo <<"\n";
        }
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "pinnedMsgId: " << type.pinnedMsgId <<"\n";
        }
        break;
    case TLValue::ChannelFull:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        if (type.flags & 1 << 13) {
            d << spacer.innerSpaces() << "onlineCount: " << type.onlineCount <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChatInvite(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChatInviteAlready:
        d << "\n";
        d << spacer.innerSpaces() << "chat: " << type.chat <<"\n";
        break;
    case TLValue::ChatInvite:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLConfig(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Config:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        d << spacer.innerSpaces() << "testMode: " << type.testMode <<"\n";
        d << spacer.innerSpaces() << "thisDc: " << type.thisDc <<"\n";
        d << spacer.innerSpaces() << "dcOptions: " << type.dcOptions <<"\n";
        d << spacer.innerSpaces() << "dcTxtDomainName: " << type.dcTxtDomainName <<"\n";
        d << spacer.innerSpaces() << "chatSizeMax: " << type.chatSizeMax <<"\n";
        d << spacer.innerSpaces() << "megagroupSizeMax: " << type.megagroupSizeMax <<"\n";
        d << spacer.innerSpaces() << "forwardedCountMax: " << type.forwardedCountMax <<"\n";
        d << spacer.innerSpaces() << "onlineUpdatePeriodMs: " << type.onlineUpdatePeriodMs <<"\n";
        d << spacer.innerSpaces() << "offlineBlurTimeoutMs: " << type.offlineBlurTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "offlineIdleTimeoutMs: " << type.offlineIdleTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "onlineCloudTimeoutMs: " << type.onlineCloudTimeoutMs <<"\n";
        d << spacer.innerSpaces() << "notifyCloudDelayMs: " << type.notifyCloudDelayMs <<"\n";
        d << spacer.innerSpaces() << "notifyDefaultDelayMs: " << type.notifyDefaultDelayMs <<"\n";
        d << spacer.innerSpaces() << "pushChatPeriodMs: " << type.pushChatPeriodMs <<"\n";
        d << spacer.innerSpaces() << "pushChatLimit: " << type.pushChatLimit <<"\n";
        d << spacer.innerSpaces() << "savedGifsLimit: " << type.savedGifsLimit <<"\n";
        d << spacer.innerSpaces() << "editTimeLimit: " << type.editTimeLimit <<"\n";
        d << spacer.innerSpaces() << "revokeTimeLimit: " << type.revokeTimeLimit <<"\n";
        d << spacer.innerSpaces() << "revokePmTimeLimit: " << type.revokePmTimeLimit <<"\n";
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
        if (type.flags & 1 << 7) {
            d << spacer.innerSpaces() << "autoupdateUrlPrefix: " << type.autoupdateUrlPrefix <<"\n";
        }
        if (type.flags & 1 << 9) {
            d << spacer.innerSpaces() << "gifSearchUsername: " << type.gifSearchUsername <<"\n";
        }
        if (type.flags & 1 << 10) {
            d << spacer.innerSpaces() << "venueSearchUsername: " << type.venueSearchUsername <<"\n";
        }
        if (type.flags & 1 << 11) {
            d << spacer.innerSpaces() << "imgSearchUsername: " << type.imgSearchUsername <<"\n";
        }
        if (type.flags & 1 << 12) {
            d << spacer.innerSpaces() << "staticMapsProvider: " << type.staticMapsProvider <<"\n";
        }
        d << spacer.innerSpaces() << "captionLengthMax: " << type.captionLengthMax <<"\n";
        d << spacer.innerSpaces() << "messageLengthMax: " << type.messageLengthMax <<"\n";
        d << spacer.innerSpaces() << "webfileDcId: " << type.webfileDcId <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "suggestedLangCode: " << type.suggestedLangCode <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "langPackVersion: " << type.langPackVersion <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "baseLangPackVersion: " << type.baseLangPackVersion <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLContactsBlocked &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsBlocked(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsBlocked:
        d << "\n";
        d << spacer.innerSpaces() << "blocked: " << type.blocked <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::ContactsBlockedSlice:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsContacts(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsContactsNotModified:
        d << " }";
        return d;
    case TLValue::ContactsContacts:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsFound(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsFound:
        d << "\n";
        d << spacer.innerSpaces() << "myResults: " << type.myResults <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsImportedContacts(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsImportedContacts:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsLink(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsLink:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsResolvedPeer(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsResolvedPeer:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLContactsTopPeers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ContactsTopPeersNotModified:
    case TLValue::ContactsTopPeersDisabled:
        d << " }";
        return d;
    case TLValue::ContactsTopPeers:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDialog(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Dialog:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLDocument(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::DocumentEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Document:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "fileReference: " << type.fileReference.toHex() <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLFoundGif(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::FoundGif:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "thumbUrl: " << type.thumbUrl <<"\n";
        d << spacer.innerSpaces() << "contentUrl: " << type.contentUrl <<"\n";
        d << spacer.innerSpaces() << "contentType: " << type.contentType <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        break;
    case TLValue::FoundGifCached:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLGame(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Game:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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

QDebug operator<<(QDebug d, const TLHelpAppUpdate &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpAppUpdate(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpAppUpdate:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        d << spacer.innerSpaces() << "text: " << type.text <<"\n";
        d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        break;
    case TLValue::HelpNoAppUpdate:
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpProxyData &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpProxyData(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpProxyDataEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
        break;
    case TLValue::HelpProxyDataPromo:
        d << "\n";
        d << spacer.innerSpaces() << "expires: " << type.expires <<"\n";
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

QDebug operator<<(QDebug d, const TLHelpSupport &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpSupport(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpSupport:
        d << "\n";
        d << spacer.innerSpaces() << "phoneNumber: " << Telegram::Utils::maskPhoneNumber(type.phoneNumber) <<"\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputBotInlineMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineMessageMediaAuto:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageText:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageMediaGeo:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageMediaVenue:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        d << spacer.innerSpaces() << "venueType: " << type.venueType <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageMediaContact:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "phoneNumber: " << Telegram::Utils::maskPhoneNumber(type.phoneNumber) <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "vcard: " << type.vcard <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "replyMarkup: " << type.replyMarkup <<"\n";
        }
        break;
    case TLValue::InputBotInlineMessageGame:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputBotInlineResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputBotInlineResult:
        d << "\n";
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
            d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "content: " << type.content <<"\n";
        }
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::InputBotInlineResultPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::InputBotInlineResultDocument:
        d << "\n";
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
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputMediaEmpty:
        d << " }";
        return d;
    case TLValue::InputMediaUploadedPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "inputPhotoId: " << type.inputPhotoId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaGeoPoint:
        d << "\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        break;
    case TLValue::InputMediaContact:
        d << "\n";
        d << spacer.innerSpaces() << "phoneNumber: " << Telegram::Utils::maskPhoneNumber(type.phoneNumber) <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "vcard: " << type.vcard <<"\n";
        break;
    case TLValue::InputMediaUploadedDocument:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "file: " << type.file <<"\n";
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        }
        d << spacer.innerSpaces() << "mimeType: " << type.mimeType <<"\n";
        d << spacer.innerSpaces() << "attributes: " << type.attributes <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaDocument:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "inputDocumentId: " << type.inputDocumentId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaVenue:
        d << "\n";
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        d << spacer.innerSpaces() << "venueType: " << type.venueType <<"\n";
        break;
    case TLValue::InputMediaGifExternal:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "q: " << type.q <<"\n";
        break;
    case TLValue::InputMediaPhotoExternal:
    case TLValue::InputMediaDocumentExternal:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::InputMediaGame:
        d << "\n";
        d << spacer.innerSpaces() << "inputGameId: " << type.inputGameId <<"\n";
        break;
    case TLValue::InputMediaInvoice:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "description: " << type.description <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        d << spacer.innerSpaces() << "invoice: " << type.invoice <<"\n";
        d << spacer.innerSpaces() << "payload: " << type.payload.toHex() <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "providerData: " << type.providerData <<"\n";
        d << spacer.innerSpaces() << "startParam: " << type.startParam <<"\n";
        break;
    case TLValue::InputMediaGeoLive:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "geoPoint: " << type.geoPoint <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        }
        break;
    case TLValue::InputMediaPoll:
        d << "\n";
        d << spacer.innerSpaces() << "poll: " << type.poll <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLInputSingleMedia &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLInputSingleMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::InputSingleMedia:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "media: " << type.media <<"\n";
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        }
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessageAction &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessageAction(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageActionEmpty:
    case TLValue::MessageActionChatDeletePhoto:
    case TLValue::MessageActionPinMessage:
    case TLValue::MessageActionHistoryClear:
    case TLValue::MessageActionScreenshotTaken:
    case TLValue::MessageActionContactSignUp:
        d << " }";
        return d;
    case TLValue::MessageActionChatCreate:
        d << "\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessageActionChatEditTitle:
    case TLValue::MessageActionChannelCreate:
        d << "\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        break;
    case TLValue::MessageActionChatEditPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        break;
    case TLValue::MessageActionChatAddUser:
        d << "\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessageActionChatDeleteUser:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::MessageActionChatJoinedByLink:
        d << "\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        break;
    case TLValue::MessageActionChatMigrateTo:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::MessageActionChannelMigrateFrom:
        d << "\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::MessageActionGameScore:
        d << "\n";
        d << spacer.innerSpaces() << "gameId: " << type.gameId <<"\n";
        d << spacer.innerSpaces() << "score: " << type.score <<"\n";
        break;
    case TLValue::MessageActionPaymentSentMe:
        d << "\n";
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
        d << "\n";
        d << spacer.innerSpaces() << "currency: " << type.currency <<"\n";
        d << spacer.innerSpaces() << "totalAmount: " << type.totalAmount <<"\n";
        break;
    case TLValue::MessageActionPhoneCall:
        d << "\n";
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
        d << "\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        break;
    case TLValue::MessageActionBotAllowed:
        d << "\n";
        d << spacer.innerSpaces() << "domain: " << type.domain <<"\n";
        break;
    case TLValue::MessageActionSecureValuesSentMe:
        d << "\n";
        d << spacer.innerSpaces() << "values: " << type.values <<"\n";
        d << spacer.innerSpaces() << "credentials: " << type.credentials <<"\n";
        break;
    case TLValue::MessageActionSecureValuesSent:
        d << "\n";
        d << spacer.innerSpaces() << "types: " << type.types <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesAllStickers &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesAllStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesAllStickersNotModified:
        d << " }";
        return d;
    case TLValue::MessagesAllStickers:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesChatFull(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesChatFull:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesChats(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesChats:
        d << "\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        break;
    case TLValue::MessagesChatsSlice:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesFavedStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFavedStickersNotModified:
        d << " }";
        return d;
    case TLValue::MessagesFavedStickers:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesFoundGifs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFoundGifs:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesHighScores(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesHighScores:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesRecentStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesRecentStickersNotModified:
        d << " }";
        return d;
    case TLValue::MessagesRecentStickers:
        d << "\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "packs: " << type.packs <<"\n";
        d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        d << spacer.innerSpaces() << "dates: " << type.dates <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesSavedGifs &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesSavedGifs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesSavedGifsNotModified:
        d << " }";
        return d;
    case TLValue::MessagesSavedGifs:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesStickerSet(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesStickerSet:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesStickersNotModified:
        d << " }";
        return d;
    case TLValue::MessagesStickers:
        d << "\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "stickers: " << type.stickers <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPage &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::Page:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
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

QDebug operator<<(QDebug d, const TLPageBlock &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPageBlock(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PageBlockUnsupported:
    case TLValue::PageBlockDivider:
        d << " }";
        return d;
    case TLValue::PageBlockTitle:
    case TLValue::PageBlockSubtitle:
    case TLValue::PageBlockHeader:
    case TLValue::PageBlockSubheader:
    case TLValue::PageBlockParagraph:
    case TLValue::PageBlockFooter:
    case TLValue::PageBlockKicker:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << *type.text <<"\n";
        break;
    case TLValue::PageBlockAuthorDate:
        d << "\n";
        d << spacer.innerSpaces() << "richTextAuthor: " << *type.richTextAuthor <<"\n";
        d << spacer.innerSpaces() << "publishedDate: " << type.publishedDate <<"\n";
        break;
    case TLValue::PageBlockPreformatted:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << *type.text <<"\n";
        d << spacer.innerSpaces() << "language: " << type.language <<"\n";
        break;
    case TLValue::PageBlockAnchor:
        d << "\n";
        d << spacer.innerSpaces() << "name: " << type.name <<"\n";
        break;
    case TLValue::PageBlockList:
        d << "\n";
        d << spacer.innerSpaces() << "pageListItemItemsVector: " << type.pageListItemItemsVector <<"\n";
        break;
    case TLValue::PageBlockBlockquote:
    case TLValue::PageBlockPullquote:
        d << "\n";
        d << spacer.innerSpaces() << "text: " << *type.text <<"\n";
        d << spacer.innerSpaces() << "richTextCaption: " << *type.richTextCaption <<"\n";
        break;
    case TLValue::PageBlockPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "photoId: " << type.photoId <<"\n";
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "webpageId: " << type.webpageId <<"\n";
        }
        break;
    case TLValue::PageBlockVideo:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "videoId: " << type.videoId <<"\n";
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        break;
    case TLValue::PageBlockCover:
        d << "\n";
        d << spacer.innerSpaces() << "cover: " << *type.cover <<"\n";
        break;
    case TLValue::PageBlockEmbed:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "html: " << type.html <<"\n";
        }
        if (type.flags & 1 << 4) {
            d << spacer.innerSpaces() << "posterPhotoId: " << type.posterPhotoId <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        }
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        break;
    case TLValue::PageBlockEmbedPost:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "webpageId: " << type.webpageId <<"\n";
        d << spacer.innerSpaces() << "authorPhotoId: " << type.authorPhotoId <<"\n";
        d << spacer.innerSpaces() << "stringAuthor: " << type.stringAuthor <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "blocks: " << type.blocks <<"\n";
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        break;
    case TLValue::PageBlockCollage:
    case TLValue::PageBlockSlideshow:
        d << "\n";
        d << spacer.innerSpaces() << "pageBlockItemsVector: " << type.pageBlockItemsVector <<"\n";
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        break;
    case TLValue::PageBlockChannel:
        d << "\n";
        d << spacer.innerSpaces() << "channel: " << type.channel <<"\n";
        break;
    case TLValue::PageBlockAudio:
        d << "\n";
        d << spacer.innerSpaces() << "audioId: " << type.audioId <<"\n";
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        break;
    case TLValue::PageBlockTable:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "title: " << *type.title <<"\n";
        d << spacer.innerSpaces() << "rows: " << type.rows <<"\n";
        break;
    case TLValue::PageBlockOrderedList:
        d << "\n";
        d << spacer.innerSpaces() << "pageListOrderedItemItemsVector: " << type.pageListOrderedItemItemsVector <<"\n";
        break;
    case TLValue::PageBlockDetails:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "blocks: " << type.blocks <<"\n";
        d << spacer.innerSpaces() << "title: " << *type.title <<"\n";
        break;
    case TLValue::PageBlockRelatedArticles:
        d << "\n";
        d << spacer.innerSpaces() << "title: " << *type.title <<"\n";
        d << spacer.innerSpaces() << "articles: " << type.articles <<"\n";
        break;
    case TLValue::PageBlockMap:
        d << "\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "zoom: " << type.zoom <<"\n";
        d << spacer.innerSpaces() << "w: " << type.w <<"\n";
        d << spacer.innerSpaces() << "h: " << type.h <<"\n";
        d << spacer.innerSpaces() << "pageCaption: " << type.pageCaption <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLPaymentsPaymentForm &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentsPaymentForm(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsPaymentForm:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentsPaymentReceipt(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsPaymentReceipt:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhoneCall(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhoneCallEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::PhoneCallWaiting:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "receiveDate: " << type.receiveDate <<"\n";
        }
        break;
    case TLValue::PhoneCallRequested:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gAHash: " << type.gAHash.toHex() <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        break;
    case TLValue::PhoneCallAccepted:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "adminId: " << type.adminId <<"\n";
        d << spacer.innerSpaces() << "participantId: " << type.participantId <<"\n";
        d << spacer.innerSpaces() << "gB: " << type.gB.toHex() <<"\n";
        d << spacer.innerSpaces() << "protocol: " << type.protocol <<"\n";
        break;
    case TLValue::PhoneCall:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "accessHash: " << Telegram::Utils::maskNumber(type.accessHash) <<"\n";
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
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhonePhoneCall(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhonePhoneCall:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhotosPhoto(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotosPhoto:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPhotosPhotos(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PhotosPhotos:
        d << "\n";
        d << spacer.innerSpaces() << "photos: " << type.photos <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::PhotosPhotosSlice:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLStickerSetCovered(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::StickerSetCovered:
        d << "\n";
        d << spacer.innerSpaces() << "set: " << type.set <<"\n";
        d << spacer.innerSpaces() << "cover: " << type.cover <<"\n";
        break;
    case TLValue::StickerSetMultiCovered:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUserFull(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UserFull:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        if (type.flags & 1 << 6) {
            d << spacer.innerSpaces() << "pinnedMsgId: " << type.pinnedMsgId <<"\n";
        }
        d << spacer.innerSpaces() << "commonChatsCount: " << type.commonChatsCount <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLWebPage &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLWebPage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::WebPageEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::WebPagePending:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::WebPage:
        d << "\n";
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
        d << " }";
        return d;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLBotInlineResult &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLBotInlineResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::BotInlineResult:
        d << "\n";
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
            d << spacer.innerSpaces() << "thumb: " << type.thumb <<"\n";
        }
        if (type.flags & 1 << 5) {
            d << spacer.innerSpaces() << "content: " << type.content <<"\n";
        }
        d << spacer.innerSpaces() << "sendMessage: " << type.sendMessage <<"\n";
        break;
    case TLValue::BotInlineMediaResult:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLMessageMedia &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessageMedia(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaUnsupported:
        d << " }";
        return d;
    case TLValue::MessageMediaPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::MessageMediaGeo:
        d << "\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        break;
    case TLValue::MessageMediaContact:
        d << "\n";
        d << spacer.innerSpaces() << "phoneNumber: " << Telegram::Utils::maskPhoneNumber(type.phoneNumber) <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "vcard: " << type.vcard <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::MessageMediaDocument:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "document: " << type.document <<"\n";
        }
        if (type.flags & 1 << 2) {
            d << spacer.innerSpaces() << "ttlSeconds: " << type.ttlSeconds <<"\n";
        }
        break;
    case TLValue::MessageMediaWebPage:
        d << "\n";
        d << spacer.innerSpaces() << "webpage: " << type.webpage <<"\n";
        break;
    case TLValue::MessageMediaVenue:
        d << "\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "title: " << type.title <<"\n";
        d << spacer.innerSpaces() << "address: " << type.address <<"\n";
        d << spacer.innerSpaces() << "provider: " << type.provider <<"\n";
        d << spacer.innerSpaces() << "venueId: " << type.venueId <<"\n";
        d << spacer.innerSpaces() << "venueType: " << type.venueType <<"\n";
        break;
    case TLValue::MessageMediaGame:
        d << "\n";
        d << spacer.innerSpaces() << "game: " << type.game <<"\n";
        break;
    case TLValue::MessageMediaInvoice:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        d << "\n";
        d << spacer.innerSpaces() << "geo: " << type.geo <<"\n";
        d << spacer.innerSpaces() << "period: " << type.period <<"\n";
        break;
    case TLValue::MessageMediaPoll:
        d << "\n";
        d << spacer.innerSpaces() << "poll: " << type.poll <<"\n";
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesArchivedStickers &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesArchivedStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesArchivedStickers:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesBotResults(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesBotResults:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesFeaturedStickers(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFeaturedStickersNotModified:
        d << " }";
        return d;
    case TLValue::MessagesFeaturedStickers:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLMessagesFoundStickerSets &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesFoundStickerSets(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesFoundStickerSetsNotModified:
        d << " }";
        return d;
    case TLValue::MessagesFoundStickerSets:
        d << "\n";
        d << spacer.innerSpaces() << "hash: " << type.hash <<"\n";
        d << spacer.innerSpaces() << "sets: " << type.sets <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesStickerSetInstallResult &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesStickerSetInstallResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesStickerSetInstallResultSuccess:
        d << " }";
        return d;
    case TLValue::MessagesStickerSetInstallResultArchive:
        d << "\n";
        d << spacer.innerSpaces() << "sets: " << type.sets <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLRecentMeUrl &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLRecentMeUrl(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::RecentMeUrlUnknown:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        break;
    case TLValue::RecentMeUrlUser:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        break;
    case TLValue::RecentMeUrlChat:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::RecentMeUrlChatInvite:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "chatInvite: " << type.chatInvite <<"\n";
        break;
    case TLValue::RecentMeUrlStickerSet:
        d << "\n";
        d << spacer.innerSpaces() << "url: " << type.url <<"\n";
        d << spacer.innerSpaces() << "set: " << type.set <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLHelpRecentMeUrls &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLHelpRecentMeUrls(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::HelpRecentMeUrls:
        d << "\n";
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

QDebug operator<<(QDebug d, const TLMessage &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessage(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessageEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "id: " << type.id <<"\n";
        break;
    case TLValue::Message:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        if (type.flags & 1 << 17) {
            d << spacer.innerSpaces() << "groupedId: " << type.groupedId <<"\n";
        }
        break;
    case TLValue::MessageService:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesDialogs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesDialogs:
        d << "\n";
        d << spacer.innerSpaces() << "dialogs: " << type.dialogs <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesDialogsSlice:
        d << "\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "dialogs: " << type.dialogs <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesDialogsNotModified:
        d << "\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLMessagesMessages &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesMessages(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesMessages:
        d << "\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesMessagesSlice:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesChannelMessages:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "count: " << type.count <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        break;
    case TLValue::MessagesMessagesNotModified:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLMessagesPeerDialogs(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::MessagesPeerDialogs:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUpdate(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
    case TLValue::UpdateEditChannelMessage:
    case TLValue::UpdateEditMessage:
        d << "\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateMessageID:
        d << "\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        d << spacer.innerSpaces() << "randomId: " << type.randomId <<"\n";
        break;
    case TLValue::UpdateDeleteMessages:
    case TLValue::UpdateReadMessagesContents:
        d << "\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateUserTyping:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "action: " << type.action <<"\n";
        break;
    case TLValue::UpdateChatUserTyping:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "action: " << type.action <<"\n";
        break;
    case TLValue::UpdateChatParticipants:
        d << "\n";
        d << spacer.innerSpaces() << "participants: " << type.participants <<"\n";
        break;
    case TLValue::UpdateUserStatus:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "status: " << type.status <<"\n";
        break;
    case TLValue::UpdateUserName:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "firstName: " << type.firstName <<"\n";
        d << spacer.innerSpaces() << "lastName: " << type.lastName <<"\n";
        d << spacer.innerSpaces() << "username: " << type.username <<"\n";
        break;
    case TLValue::UpdateUserPhoto:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "photo: " << type.photo <<"\n";
        d << spacer.innerSpaces() << "previous: " << type.previous <<"\n";
        break;
    case TLValue::UpdateContactLink:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "myLink: " << type.myLink <<"\n";
        d << spacer.innerSpaces() << "foreignLink: " << type.foreignLink <<"\n";
        break;
    case TLValue::UpdateNewEncryptedMessage:
        d << "\n";
        d << spacer.innerSpaces() << "encryptedMessage: " << type.encryptedMessage <<"\n";
        d << spacer.innerSpaces() << "qts: " << type.qts <<"\n";
        break;
    case TLValue::UpdateEncryptedChatTyping:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        break;
    case TLValue::UpdateEncryption:
        d << "\n";
        d << spacer.innerSpaces() << "chat: " << type.chat <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdateEncryptedMessagesRead:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "maxDate: " << type.maxDate <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdateChatParticipantAdd:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "inviterId: " << type.inviterId <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateChatParticipantDelete:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateDcOptions:
        d << "\n";
        d << spacer.innerSpaces() << "dcOptions: " << type.dcOptions <<"\n";
        break;
    case TLValue::UpdateUserBlocked:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "blocked: " << type.blocked <<"\n";
        break;
    case TLValue::UpdateNotifySettings:
        d << "\n";
        d << spacer.innerSpaces() << "notifyPeer: " << type.notifyPeer <<"\n";
        d << spacer.innerSpaces() << "notifySettings: " << type.notifySettings <<"\n";
        break;
    case TLValue::UpdateServiceNotification:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "inboxDate: " << type.inboxDate <<"\n";
        }
        d << spacer.innerSpaces() << "type: " << type.type <<"\n";
        d << spacer.innerSpaces() << "stringMessage: " << type.stringMessage <<"\n";
        d << spacer.innerSpaces() << "media: " << type.media <<"\n";
        d << spacer.innerSpaces() << "entities: " << type.entities <<"\n";
        break;
    case TLValue::UpdatePrivacy:
        d << "\n";
        d << spacer.innerSpaces() << "key: " << type.key <<"\n";
        d << spacer.innerSpaces() << "rules: " << type.rules <<"\n";
        break;
    case TLValue::UpdateUserPhone:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "phone: " << Telegram::Utils::maskPhoneNumber(type.phone) <<"\n";
        break;
    case TLValue::UpdateReadHistoryInbox:
    case TLValue::UpdateReadHistoryOutbox:
        d << "\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateWebPage:
        d << "\n";
        d << spacer.innerSpaces() << "webpage: " << type.webpage <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateChannelTooLong:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        }
        break;
    case TLValue::UpdateChannel:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        break;
    case TLValue::UpdateReadChannelInbox:
    case TLValue::UpdateReadChannelOutbox:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "maxId: " << type.maxId <<"\n";
        break;
    case TLValue::UpdateDeleteChannelMessages:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateChannelMessageViews:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        d << spacer.innerSpaces() << "views: " << type.views <<"\n";
        break;
    case TLValue::UpdateChatAdmins:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "enabled: " << type.enabled <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateChatParticipantAdmin:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "isAdmin: " << type.isAdmin <<"\n";
        d << spacer.innerSpaces() << "version: " << type.version <<"\n";
        break;
    case TLValue::UpdateNewStickerSet:
        d << "\n";
        d << spacer.innerSpaces() << "stickerset: " << type.stickerset <<"\n";
        break;
    case TLValue::UpdateStickerSetsOrder:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "quint64OrderVector: " << type.quint64OrderVector <<"\n";
        break;
    case TLValue::UpdateStickerSets:
    case TLValue::UpdateSavedGifs:
    case TLValue::UpdateReadFeaturedStickers:
    case TLValue::UpdateRecentStickers:
    case TLValue::UpdateConfig:
    case TLValue::UpdatePtsChanged:
    case TLValue::UpdateFavedStickers:
    case TLValue::UpdateContactsReset:
        d << " }";
        return d;
    case TLValue::UpdateBotInlineQuery:
        d << "\n";
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
        d << "\n";
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
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        break;
    case TLValue::UpdateBotCallbackQuery:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "msgId: " << type.msgId <<"\n";
        d << spacer.innerSpaces() << "chatInstance: " << type.chatInstance <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "byteArrayData: " << type.byteArrayData.toHex() <<"\n";
        }
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "gameShortName: " << type.gameShortName <<"\n";
        }
        break;
    case TLValue::UpdateInlineBotCallbackQuery:
        d << "\n";
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
        d << "\n";
        d << spacer.innerSpaces() << "peer: " << type.peer <<"\n";
        d << spacer.innerSpaces() << "draft: " << type.draft <<"\n";
        break;
    case TLValue::UpdateChannelWebPage:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "webpage: " << type.webpage <<"\n";
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        d << spacer.innerSpaces() << "ptsCount: " << type.ptsCount <<"\n";
        break;
    case TLValue::UpdateDialogPinned:
    case TLValue::UpdateDialogUnreadMark:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "dialogPeer: " << type.dialogPeer <<"\n";
        break;
    case TLValue::UpdatePinnedDialogs:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "dialogPeerOrderVector: " << type.dialogPeerOrderVector <<"\n";
        }
        break;
    case TLValue::UpdateBotWebhookJSON:
        d << "\n";
        d << spacer.innerSpaces() << "jSONData: " << type.jSONData <<"\n";
        break;
    case TLValue::UpdateBotWebhookJSONQuery:
        d << "\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "jSONData: " << type.jSONData <<"\n";
        d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        break;
    case TLValue::UpdateBotShippingQuery:
        d << "\n";
        d << spacer.innerSpaces() << "queryId: " << type.queryId <<"\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "payload: " << type.payload.toHex() <<"\n";
        d << spacer.innerSpaces() << "shippingAddress: " << type.shippingAddress <<"\n";
        break;
    case TLValue::UpdateBotPrecheckoutQuery:
        d << "\n";
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
        d << "\n";
        d << spacer.innerSpaces() << "phoneCall: " << type.phoneCall <<"\n";
        break;
    case TLValue::UpdateLangPackTooLong:
        d << "\n";
        d << spacer.innerSpaces() << "langCode: " << type.langCode <<"\n";
        break;
    case TLValue::UpdateLangPack:
        d << "\n";
        d << spacer.innerSpaces() << "difference: " << type.difference <<"\n";
        break;
    case TLValue::UpdateChannelReadMessagesContents:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "messages: " << type.messages <<"\n";
        break;
    case TLValue::UpdateChannelAvailableMessages:
        d << "\n";
        d << spacer.innerSpaces() << "channelId: " << type.channelId <<"\n";
        d << spacer.innerSpaces() << "availableMinId: " << type.availableMinId <<"\n";
        break;
    case TLValue::UpdateUserPinnedMessage:
        d << "\n";
        d << spacer.innerSpaces() << "userId: " << type.userId <<"\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        break;
    case TLValue::UpdateChatPinnedMessage:
        d << "\n";
        d << spacer.innerSpaces() << "chatId: " << type.chatId <<"\n";
        d << spacer.innerSpaces() << "quint32Id: " << type.quint32Id <<"\n";
        break;
    case TLValue::UpdateMessagePoll:
        d << "\n";
        d << spacer.innerSpaces() << "flags: " << type.flags <<"\n";
        d << spacer.innerSpaces() << "pollId: " << type.pollId <<"\n";
        if (type.flags & 1 << 0) {
            d << spacer.innerSpaces() << "poll: " << type.poll <<"\n";
        }
        d << spacer.innerSpaces() << "results: " << type.results <<"\n";
        break;
    default:
        break;
    }
    d << spacer.outerSpaces() << "}";

    return d;
}

QDebug operator<<(QDebug d, const TLUpdates &type)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUpdates(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesTooLong:
        d << " }";
        return d;
    case TLValue::UpdateShortMessage:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        d << "\n";
        d << spacer.innerSpaces() << "update: " << type.update <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        break;
    case TLValue::UpdatesCombined:
        d << "\n";
        d << spacer.innerSpaces() << "updates: " << type.updates <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seqStart: " << type.seqStart <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        break;
    case TLValue::Updates:
        d << "\n";
        d << spacer.innerSpaces() << "updates: " << type.updates <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        break;
    case TLValue::UpdateShortSentMessage:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUpdatesChannelDifference(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesChannelDifferenceEmpty:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
        d << spacer.innerSpaces() << "pts: " << type.pts <<"\n";
        if (type.flags & 1 << 1) {
            d << spacer.innerSpaces() << "timeout: " << type.timeout <<"\n";
        }
        break;
    case TLValue::UpdatesChannelDifferenceTooLong:
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
        d << "\n";
        d.noquote() << spacer.innerSpaces() << "flags: " << type.flags << " (" << flagsToString(type) <<")\n";
        d.quote();
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLUpdatesDifference(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::UpdatesDifferenceEmpty:
        d << "\n";
        d << spacer.innerSpaces() << "date: " << type.date <<"\n";
        d << spacer.innerSpaces() << "seq: " << type.seq <<"\n";
        break;
    case TLValue::UpdatesDifference:
        d << "\n";
        d << spacer.innerSpaces() << "newMessages: " << type.newMessages <<"\n";
        d << spacer.innerSpaces() << "newEncryptedMessages: " << type.newEncryptedMessages <<"\n";
        d << spacer.innerSpaces() << "otherUpdates: " << type.otherUpdates <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "state: " << type.state <<"\n";
        break;
    case TLValue::UpdatesDifferenceSlice:
        d << "\n";
        d << spacer.innerSpaces() << "newMessages: " << type.newMessages <<"\n";
        d << spacer.innerSpaces() << "newEncryptedMessages: " << type.newEncryptedMessages <<"\n";
        d << spacer.innerSpaces() << "otherUpdates: " << type.otherUpdates <<"\n";
        d << spacer.innerSpaces() << "chats: " << type.chats <<"\n";
        d << spacer.innerSpaces() << "users: " << type.users <<"\n";
        d << spacer.innerSpaces() << "intermediateState: " << type.intermediateState <<"\n";
        break;
    case TLValue::UpdatesDifferenceTooLong:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelAdminLogEventAction(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminLogEventActionChangeTitle:
    case TLValue::ChannelAdminLogEventActionChangeAbout:
    case TLValue::ChannelAdminLogEventActionChangeUsername:
        d << "\n";
        d << spacer.innerSpaces() << "prevValue: " << type.prevValue <<"\n";
        d << spacer.innerSpaces() << "stringNewValue: " << type.stringNewValue <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionChangePhoto:
        d << "\n";
        d << spacer.innerSpaces() << "prevPhoto: " << type.prevPhoto <<"\n";
        d << spacer.innerSpaces() << "newPhoto: " << type.newPhoto <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionToggleInvites:
    case TLValue::ChannelAdminLogEventActionToggleSignatures:
    case TLValue::ChannelAdminLogEventActionTogglePreHistoryHidden:
        d << "\n";
        d << spacer.innerSpaces() << "boolNewValue: " << type.boolNewValue <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionUpdatePinned:
    case TLValue::ChannelAdminLogEventActionDeleteMessage:
        d << "\n";
        d << spacer.innerSpaces() << "message: " << type.message <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionEditMessage:
        d << "\n";
        d << spacer.innerSpaces() << "prevMessage: " << type.prevMessage <<"\n";
        d << spacer.innerSpaces() << "newMessage: " << type.newMessage <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionParticipantJoin:
    case TLValue::ChannelAdminLogEventActionParticipantLeave:
        d << " }";
        return d;
    case TLValue::ChannelAdminLogEventActionParticipantInvite:
        d << "\n";
        d << spacer.innerSpaces() << "participant: " << type.participant <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionParticipantToggleBan:
    case TLValue::ChannelAdminLogEventActionParticipantToggleAdmin:
        d << "\n";
        d << spacer.innerSpaces() << "prevParticipant: " << type.prevParticipant <<"\n";
        d << spacer.innerSpaces() << "newParticipant: " << type.newParticipant <<"\n";
        break;
    case TLValue::ChannelAdminLogEventActionChangeStickerSet:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLPaymentsPaymentResult(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::PaymentsPaymentResult:
        d << "\n";
        d << spacer.innerSpaces() << "updates: " << type.updates <<"\n";
        break;
    case TLValue::PaymentsPaymentVerficationNeeded:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelAdminLogEvent(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelAdminLogEvent:
        d << "\n";
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
    QDebugStateSaver saver(d);
    d.nospace();
    d << "TLChannelsAdminLogResults(" << type.tlType << ") {";
    Spacer spacer;
    switch (type.tlType) {
    case TLValue::ChannelsAdminLogResults:
        d << "\n";
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
