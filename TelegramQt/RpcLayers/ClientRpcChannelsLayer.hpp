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
    PendingRpcOperation *deleteMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingRpcOperation *deleteUserHistory(const TLInputChannel &channel, const TLInputUser &userId);
    PendingRpcOperation *editAbout(const TLInputChannel &channel, const QString &about);
    PendingRpcOperation *editAdmin(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelParticipantRole &role);
    PendingRpcOperation *editPhoto(const TLInputChannel &channel, const TLInputChatPhoto &photo);
    PendingRpcOperation *editTitle(const TLInputChannel &channel, const QString &title);
    PendingRpcOperation *exportInvite(const TLInputChannel &channel);
    PendingRpcOperation *getChannels(const TLVector<TLInputChannel> &id);
    PendingRpcOperation *getDialogs(quint32 offset, quint32 limit);
    PendingRpcOperation *getFullChannel(const TLInputChannel &channel);
    PendingRpcOperation *getImportantHistory(const TLInputChannel &channel, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    PendingRpcOperation *getMessages(const TLInputChannel &channel, const TLVector<quint32> &id);
    PendingRpcOperation *getParticipant(const TLInputChannel &channel, const TLInputUser &userId);
    PendingRpcOperation *getParticipants(const TLInputChannel &channel, const TLChannelParticipantsFilter &filter, quint32 offset, quint32 limit);
    PendingRpcOperation *inviteToChannel(const TLInputChannel &channel, const TLVector<TLInputUser> &users);
    PendingRpcOperation *joinChannel(const TLInputChannel &channel);
    PendingRpcOperation *kickFromChannel(const TLInputChannel &channel, const TLInputUser &userId, bool kicked);
    PendingRpcOperation *leaveChannel(const TLInputChannel &channel);
    PendingRpcOperation *readHistory(const TLInputChannel &channel, quint32 maxId);
    PendingRpcOperation *reportSpam(const TLInputChannel &channel, const TLInputUser &userId, const TLVector<quint32> &id);
    PendingRpcOperation *toggleComments(const TLInputChannel &channel, bool enabled);
    PendingRpcOperation *updateUsername(const TLInputChannel &channel, const QString &username);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_CHANNELS_LAYER_HPP
