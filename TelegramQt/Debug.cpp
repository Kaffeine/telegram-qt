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
#include "TelegramNamespace.hpp"

#include "MTProto/MessageHeader.hpp"
#include "IgnoredMessageNotification.hpp"

static const QByteArray c_spaces = QByteArray(24, ' ');

const char *getSpaces(int count)
{
    int position = c_spaces.count() - count;
    if (position < 0) {
        position = 0;
    }
    return c_spaces.constData() + position;
}

namespace Telegram {

namespace Debug {

int Spacer::m_spacing = 0;

Spacer::Spacer()
{
    m_spacing += m_step;
}

Spacer::~Spacer()
{
    m_spacing -= m_step;
}

const char *Spacer::innerSpaces()
{
    if (!m_hasInnerCalls) {
        m_hasInnerCalls = true;
    }
    return getSpaces(m_spacing);
}

const char *Spacer::outerSpaces()
{
    if (m_hasInnerCalls) {
        return getSpaces(m_spacing - m_step);
    } else {
        return " ";
    }
}

} // Debug namespace

} // Telegram namespace

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

// Extra debug methods
QDebug operator<<(QDebug d, const Telegram::MTProto::FullMessageHeader &messageHeader)
{
    Telegram::Debug::Spacer spacer;
    d.noquote().nospace();
    d << hex << showbase;
    d << "MessageHeader {";
    d << spacer.innerSpaces() << "salt: " << messageHeader.serverSalt << endl;
    d << spacer.innerSpaces() << "sessionId: " << messageHeader.sessionId << endl;
    d << spacer.innerSpaces() << "messageId: " << messageHeader.messageId << endl;
    d << spacer.innerSpaces() << "sequenceNumber: " << messageHeader.sequenceNumber << endl;
    d << spacer.innerSpaces() << "contentLength: " << messageHeader.contentLength << endl;
    d << "}";
    return d;
}

QDebug operator<<(QDebug d, const Telegram::MTProto::IgnoredMessageNotification &notification)
{
    Telegram::Debug::Spacer spacer;
    d.noquote().nospace();
    d << hex << showbase;
    d << "IgnoredMessageNotification {";
    d << spacer.innerSpaces() << "messageId: " << notification.messageId << endl;
    d << spacer.innerSpaces() << "seqNo:" << notification.seqNo << endl;
    d << spacer.innerSpaces() << "errorCode: " << notification.errorCode << endl;
    d << "}";
    return d;
}
