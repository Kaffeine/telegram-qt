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

#ifndef TELEGRAM_CLIENT_RPC_CHANNELS_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_CHANNELS_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class ChannelsRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit ChannelsRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingUpdates = PendingRpcResult<TLUpdates *>;
    using PendingMessagesAffectedMessages = PendingRpcResult<TLMessagesAffectedMessages *>;
    using PendingMessagesAffectedHistory = PendingRpcResult<TLMessagesAffectedHistory *>;
    using PendingExportedChatInvite = PendingRpcResult<TLExportedChatInvite *>;
    using PendingExportedMessageLink = PendingRpcResult<TLExportedMessageLink *>;
    using PendingChannelsAdminLogResults = PendingRpcResult<TLChannelsAdminLogResults *>;
    using PendingMessagesChats = PendingRpcResult<TLMessagesChats *>;
    using PendingMessagesChatFull = PendingRpcResult<TLMessagesChatFull *>;
    using PendingMessagesMessages = PendingRpcResult<TLMessagesMessages *>;
    using PendingChannelsChannelParticipant = PendingRpcResult<TLChannelsChannelParticipant *>;
    using PendingChannelsChannelParticipants = PendingRpcResult<TLChannelsChannelParticipants *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *checkUsername(const TLInputChannel &channel, const QString &username);
    PendingUpdates *createChannel(quint32 flags, const QString &title, const QString &about);
    PendingUpdates *deleteChannel(const TLInputChannel &channel);
    PendingBool *deleteHistory(const TLInputChannel &channel, quint32 maxId);
    PendingMessagesAffectedMessages *deleteMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingMessagesAffectedHistory *deleteUserHistory(const TLInputChannel &channel, const TLInputUser &userId);
    PendingBool *editAbout(const TLInputChannel &channel, const QString &about);
    PendingUpdates *editAdmin(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelAdminRights &adminRights);
    PendingUpdates *editBanned(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelBannedRights &bannedRights);
    PendingUpdates *editPhoto(const TLInputChannel &channel, const TLInputChatPhoto &photo);
    PendingUpdates *editTitle(const TLInputChannel &channel, const QString &title);
    PendingExportedChatInvite *exportInvite(const TLInputChannel &channel);
    PendingExportedMessageLink *exportMessageLink(const TLInputChannel &channel, quint32 id, bool grouped);
    PendingChannelsAdminLogResults *getAdminLog(quint32 flags, const TLInputChannel &channel, const QString &q, const TLChannelAdminLogEventsFilter &eventsFilter, const TLVector<TLInputUser> &admins, quint64 maxId, quint64 minId, quint32 limit);
    PendingMessagesChats *getAdminedPublicChannels();
    PendingMessagesChats *getChannels(const TLVector<TLInputChannel> &id);
    PendingMessagesChatFull *getFullChannel(const TLInputChannel &channel);
    PendingMessagesChats *getLeftChannels(quint32 offset);
    PendingMessagesMessages *getMessages(const TLInputChannel &channel, const TLVector<TLInputMessage> &id);
    PendingChannelsChannelParticipant *getParticipant(const TLInputChannel &channel, const TLInputUser &userId);
    PendingChannelsChannelParticipants *getParticipants(const TLInputChannel &channel, const TLChannelParticipantsFilter &filter, quint32 offset, quint32 limit, quint32 hash);
    PendingUpdates *inviteToChannel(const TLInputChannel &channel, const TLVector<TLInputUser> &users);
    PendingUpdates *joinChannel(const TLInputChannel &channel);
    PendingUpdates *leaveChannel(const TLInputChannel &channel);
    PendingBool *readHistory(const TLInputChannel &channel, quint32 maxId);
    PendingBool *readMessageContents(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingBool *reportSpam(const TLInputChannel &channel, const TLInputUser &userId, const TLVector<quint32> &id);
    PendingBool *setStickers(const TLInputChannel &channel, const TLInputStickerSet &stickerset);
    PendingUpdates *toggleInvites(const TLInputChannel &channel, bool enabled);
    PendingUpdates *togglePreHistoryHidden(const TLInputChannel &channel, bool enabled);
    PendingUpdates *toggleSignatures(const TLInputChannel &channel, bool enabled);
    PendingBool *updateUsername(const TLInputChannel &channel, const QString &username);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_CHANNELS_LAYER_HPP
