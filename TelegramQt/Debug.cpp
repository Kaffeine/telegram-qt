/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "Debug_p.hpp"

QDebug operator<<(QDebug d, const TLValue &v)
{
    d << v.toString();
    return d;
}

QDebug operator<<(QDebug d, const Telegram::Peer &peer)
{
    switch (peer.type) {
    case Telegram::Peer::User:
        d << "Telegram::Peer(User, " << peer.id << ")";
        break;
    case Telegram::Peer::Chat:
        d << "Telegram::Peer(Chat, " << peer.id << ")";
        break;
    case Telegram::Peer::Channel:
        d << "Telegram::Peer(Channel, " << peer.id << ")";
        break;
    default:
        d << "Telegram::Peer(Invalid:" << peer.type << ", " << peer.id << ")";
        break;
    }
    return d;
}

template <int Size>
QDebug operator<<(QDebug d, const TLNumber<Size> &n)
{
    d << QByteArray::fromRawData(n.data, n.size()).toHex();
    return d;
}

template QDebug operator<<(QDebug d, const TLNumber<128> &n);
template QDebug operator<<(QDebug d, const TLNumber<256> &n);
