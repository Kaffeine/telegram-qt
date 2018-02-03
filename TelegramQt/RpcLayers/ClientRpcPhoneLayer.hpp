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
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class PhoneRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit PhoneRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *acceptCall(const TLInputPhoneCall &peer, const QByteArray &gB, const TLPhoneCallProtocol &protocol);
    PendingRpcOperation *confirmCall(const TLInputPhoneCall &peer, const QByteArray &gA, quint64 keyFingerprint, const TLPhoneCallProtocol &protocol);
    PendingRpcOperation *discardCall(const TLInputPhoneCall &peer, quint32 duration, const TLPhoneCallDiscardReason &reason, quint64 connectionId);
    PendingRpcOperation *getCallConfig();
    PendingRpcOperation *receivedCall(const TLInputPhoneCall &peer);
    PendingRpcOperation *requestCall(const TLInputUser &userId, quint32 randomId, const QByteArray &gAHash, const TLPhoneCallProtocol &protocol);
    PendingRpcOperation *saveCallDebug(const TLInputPhoneCall &peer, const TLDataJSON &debug);
    PendingRpcOperation *setCallRating(const TLInputPhoneCall &peer, quint32 rating, const QString &comment);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_PHONE_LAYER_HPP
