/*
   Copyright (C) 2018 

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

#ifndef TELEGRAM_CLIENT_RPC_PHONE_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_PHONE_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "PendingRpcResult.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class PhoneRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit PhoneRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingPhonePhoneCall = PendingRpcResult<TLPhonePhoneCall *>;
    using PendingUpdates = PendingRpcResult<TLUpdates *>;
    using PendingDataJSON = PendingRpcResult<TLDataJSON *>;
    using PendingBool = PendingRpcResult<TLBool *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingPhonePhoneCall *acceptCall(const TLInputPhoneCall &peer, const QByteArray &gB, const TLPhoneCallProtocol &protocol);
    PendingPhonePhoneCall *confirmCall(const TLInputPhoneCall &peer, const QByteArray &gA, quint64 keyFingerprint, const TLPhoneCallProtocol &protocol);
    PendingUpdates *discardCall(const TLInputPhoneCall &peer, quint32 duration, const TLPhoneCallDiscardReason &reason, quint64 connectionId);
    PendingDataJSON *getCallConfig();
    PendingBool *receivedCall(const TLInputPhoneCall &peer);
    PendingPhonePhoneCall *requestCall(const TLInputUser &userId, quint32 randomId, const QByteArray &gAHash, const TLPhoneCallProtocol &protocol);
    PendingBool *saveCallDebug(const TLInputPhoneCall &peer, const TLDataJSON &debug);
    PendingUpdates *setCallRating(const TLInputPhoneCall &peer, quint32 rating, const QString &comment);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_PHONE_LAYER_HPP
