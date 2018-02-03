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
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class ChannelsRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit ChannelsRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *checkUsername(const TLInputChannel &channel, const QString &username);
    PendingRpcOperation *createChannel(quint32 flags, const QString &title, const QString &about);
    PendingRpcOperation *deleteChannel(const TLInputChannel &channel);
    PendingRpcOperation *deleteHistory(const TLInputChannel &channel, quint32 maxId);
    PendingRpcOperation *deleteMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingRpcOperation *deleteUserHistory(const TLInputChannel &channel, const TLInputUser &userId);
    PendingRpcOperation *editAbout(const TLInputChannel &channel, const QString &about);
    PendingRpcOperation *editAdmin(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelAdminRights &adminRights);
    PendingRpcOperation *editBanned(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelBannedRights &bannedRights);
    PendingRpcOperation *editPhoto(const TLInputChannel &channel, const TLInputChatPhoto &photo);
    PendingRpcOperation *editTitle(const TLInputChannel &channel, const QString &title);
    PendingRpcOperation *exportInvite(const TLInputChannel &channel);
    PendingRpcOperation *exportMessageLink(const TLInputChannel &channel, quint32 id);
    PendingRpcOperation *getAdminLog(quint32 flags, const TLInputChannel &channel, const QString &q, const TLChannelAdminLogEventsFilter &eventsFilter, const TLVector<TLInputUser> &admins, quint64 maxId, quint64 minId, quint32 limit);
    PendingRpcOperation *getAdminedPublicChannels();
    PendingRpcOperation *getChannels(const TLVector<TLInputChannel> &id);
    PendingRpcOperation *getFullChannel(const TLInputChannel &channel);
    PendingRpcOperation *getMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingRpcOperation *getParticipant(const TLInputChannel &channel, const TLInputUser &userId);
    PendingRpcOperation *getParticipants(const TLInputChannel &channel, const TLChannelParticipantsFilter &filter, quint32 offset, quint32 limit, quint32 hash);
    PendingRpcOperation *inviteToChannel(const TLInputChannel &channel, const TLVector<TLInputUser> &users);
    PendingRpcOperation *joinChannel(const TLInputChannel &channel);
    PendingRpcOperation *leaveChannel(const TLInputChannel &channel);
    PendingRpcOperation *readHistory(const TLInputChannel &channel, quint32 maxId);
    PendingRpcOperation *readMessageContents(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingRpcOperation *reportSpam(const TLInputChannel &channel, const TLInputUser &userId, const TLVector<quint32> &id);
    PendingRpcOperation *setStickers(const TLInputChannel &channel, const TLInputStickerSet &stickerset);
    PendingRpcOperation *toggleInvites(const TLInputChannel &channel, bool enabled);
    PendingRpcOperation *togglePreHistoryHidden(const TLInputChannel &channel, bool enabled);
    PendingRpcOperation *toggleSignatures(const TLInputChannel &channel, bool enabled);
    PendingRpcOperation *updatePinnedMessage(quint32 flags, const TLInputChannel &channel, quint32 id);
    PendingRpcOperation *updateUsername(const TLInputChannel &channel, const QString &username);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_CHANNELS_LAYER_HPP
