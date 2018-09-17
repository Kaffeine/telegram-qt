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

#ifndef TELEGRAM_CLIENT_RPC_UPDATES_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_UPDATES_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "PendingRpcResult.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class UpdatesRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit UpdatesRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingUpdatesChannelDifference = PendingRpcResult<TLUpdatesChannelDifference *>;
    using PendingUpdatesDifference = PendingRpcResult<TLUpdatesDifference *>;
    using PendingUpdatesState = PendingRpcResult<TLUpdatesState *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingUpdatesChannelDifference *getChannelDifference(quint32 flags, const TLInputChannel &channel, const TLChannelMessagesFilter &filter, quint32 pts, quint32 limit);
    PendingUpdatesDifference *getDifference(quint32 flags, quint32 pts, quint32 ptsTotalLimit, quint32 date, quint32 qts);
    PendingUpdatesState *getState();
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_UPDATES_LAYER_HPP
