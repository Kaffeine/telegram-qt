/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#include "ClientRpcChannelsLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcChannelsCategory, "telegram.client.rpclayer.channels", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelAdminLogEvent *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelAdminLogEventAction *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelAdminLogEventsFilter *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelAdminRights *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelBannedRights *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelMessagesFilter *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelParticipant *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelParticipantsFilter *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelsAdminLogResults *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelsChannelParticipant *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelsChannelParticipants *output);
// End of generated Telegram API reply template specializations

ChannelsRpcLayer::ChannelsRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::checkUsername(const TLInputChannel &channel, const QString &username)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << username;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsCheckUsername;
    outputStream << channel;
    outputStream << username;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::createChannel(quint32 flags, const QString &title, const QString &about)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << flags << title << about;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsCreateChannel;
    outputStream << flags;
    // (flags & 1 << 0) stands for broadcast "true" value
    // (flags & 1 << 1) stands for megagroup "true" value
    outputStream << title;
    outputStream << about;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::deleteChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteChannel;
    outputStream << channel;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::deleteHistory(const TLInputChannel &channel, quint32 maxId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << maxId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteHistory;
    outputStream << channel;
    outputStream << maxId;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesAffectedMessages *ChannelsRpcLayer::deleteMessages(const TLInputChannel &channel, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteMessages;
    outputStream << channel;
    outputStream << id;
    PendingMessagesAffectedMessages *op = new PendingMessagesAffectedMessages(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesAffectedHistory *ChannelsRpcLayer::deleteUserHistory(const TLInputChannel &channel, const TLInputUser &userId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteUserHistory;
    outputStream << channel;
    outputStream << userId;
    PendingMessagesAffectedHistory *op = new PendingMessagesAffectedHistory(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::editAbout(const TLInputChannel &channel, const QString &about)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << about;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsEditAbout;
    outputStream << channel;
    outputStream << about;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::editAdmin(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelAdminRights &adminRights)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId << adminRights;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsEditAdmin;
    outputStream << channel;
    outputStream << userId;
    outputStream << adminRights;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::editBanned(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelBannedRights &bannedRights)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId << bannedRights;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsEditBanned;
    outputStream << channel;
    outputStream << userId;
    outputStream << bannedRights;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::editPhoto(const TLInputChannel &channel, const TLInputChatPhoto &photo)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << photo;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsEditPhoto;
    outputStream << channel;
    outputStream << photo;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::editTitle(const TLInputChannel &channel, const QString &title)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << title;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsEditTitle;
    outputStream << channel;
    outputStream << title;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingExportedChatInvite *ChannelsRpcLayer::exportInvite(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsExportInvite;
    outputStream << channel;
    PendingExportedChatInvite *op = new PendingExportedChatInvite(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingExportedMessageLink *ChannelsRpcLayer::exportMessageLink(const TLInputChannel &channel, quint32 id, bool grouped)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << id << grouped;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsExportMessageLink;
    outputStream << channel;
    outputStream << id;
    outputStream << grouped;
    PendingExportedMessageLink *op = new PendingExportedMessageLink(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingChannelsAdminLogResults *ChannelsRpcLayer::getAdminLog(quint32 flags, const TLInputChannel &channel, const QString &q, const TLChannelAdminLogEventsFilter &eventsFilter, const TLVector<TLInputUser> &admins, quint64 maxId, quint64 minId, quint32 limit)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << flags << channel << q << eventsFilter << admins << maxId << minId << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetAdminLog;
    outputStream << flags;
    outputStream << channel;
    outputStream << q;
    if (flags & 1 << 0) {
        outputStream << eventsFilter;
    }
    if (flags & 1 << 1) {
        outputStream << admins;
    }
    outputStream << maxId;
    outputStream << minId;
    outputStream << limit;
    PendingChannelsAdminLogResults *op = new PendingChannelsAdminLogResults(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesChats *ChannelsRpcLayer::getAdminedPublicChannels()
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetAdminedPublicChannels;
    PendingMessagesChats *op = new PendingMessagesChats(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesChats *ChannelsRpcLayer::getChannels(const TLVector<TLInputChannel> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetChannels;
    outputStream << id;
    PendingMessagesChats *op = new PendingMessagesChats(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesChatFull *ChannelsRpcLayer::getFullChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetFullChannel;
    outputStream << channel;
    PendingMessagesChatFull *op = new PendingMessagesChatFull(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesChats *ChannelsRpcLayer::getLeftChannels(quint32 offset)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << offset;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetLeftChannels;
    outputStream << offset;
    PendingMessagesChats *op = new PendingMessagesChats(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingMessagesMessages *ChannelsRpcLayer::getMessages(const TLInputChannel &channel, const TLVector<TLInputMessage> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetMessages;
    outputStream << channel;
    outputStream << id;
    PendingMessagesMessages *op = new PendingMessagesMessages(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingChannelsChannelParticipant *ChannelsRpcLayer::getParticipant(const TLInputChannel &channel, const TLInputUser &userId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetParticipant;
    outputStream << channel;
    outputStream << userId;
    PendingChannelsChannelParticipant *op = new PendingChannelsChannelParticipant(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingChannelsChannelParticipants *ChannelsRpcLayer::getParticipants(const TLInputChannel &channel, const TLChannelParticipantsFilter &filter, quint32 offset, quint32 limit, quint32 hash)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << filter << offset << limit << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsGetParticipants;
    outputStream << channel;
    outputStream << filter;
    outputStream << offset;
    outputStream << limit;
    outputStream << hash;
    PendingChannelsChannelParticipants *op = new PendingChannelsChannelParticipants(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::inviteToChannel(const TLInputChannel &channel, const TLVector<TLInputUser> &users)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << users;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsInviteToChannel;
    outputStream << channel;
    outputStream << users;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::joinChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsJoinChannel;
    outputStream << channel;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::leaveChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsLeaveChannel;
    outputStream << channel;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::readHistory(const TLInputChannel &channel, quint32 maxId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << maxId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsReadHistory;
    outputStream << channel;
    outputStream << maxId;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::readMessageContents(const TLInputChannel &channel, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsReadMessageContents;
    outputStream << channel;
    outputStream << id;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::reportSpam(const TLInputChannel &channel, const TLInputUser &userId, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsReportSpam;
    outputStream << channel;
    outputStream << userId;
    outputStream << id;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::setStickers(const TLInputChannel &channel, const TLInputStickerSet &stickerset)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << stickerset;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsSetStickers;
    outputStream << channel;
    outputStream << stickerset;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::toggleInvites(const TLInputChannel &channel, bool enabled)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << enabled;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsToggleInvites;
    outputStream << channel;
    outputStream << enabled;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::togglePreHistoryHidden(const TLInputChannel &channel, bool enabled)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << enabled;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsTogglePreHistoryHidden;
    outputStream << channel;
    outputStream << enabled;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingUpdates *ChannelsRpcLayer::toggleSignatures(const TLInputChannel &channel, bool enabled)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << enabled;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsToggleSignatures;
    outputStream << channel;
    outputStream << enabled;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ChannelsRpcLayer::PendingBool *ChannelsRpcLayer::updateUsername(const TLInputChannel &channel, const QString &username)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << username;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ChannelsUpdateUsername;
    outputStream << channel;
    outputStream << username;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
