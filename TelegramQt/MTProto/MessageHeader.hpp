/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_QT_MTPROTO_MESSAGE_HEADER_HPP
#define TELEGRAM_QT_MTPROTO_MESSAGE_HEADER_HPP

#include "telegramqt_global.h"
#include "TLValues.hpp"

#include "CRawStream.hpp"

#include <QByteArray>

namespace Telegram {

namespace MTProto {

struct TELEGRAMQT_EXPORT MessageHeader {
    quint64 messageId;
    quint32 sequenceNumber;
    quint32 contentLength;

    static constexpr int headerLength = sizeof(quint64) + sizeof(quint32) + sizeof(quint32);
};

struct TELEGRAMQT_EXPORT FullMessageHeader : public MessageHeader
{
    FullMessageHeader() = default;
    FullMessageHeader(const MessageHeader &header, quint64 salt, quint64 session) :
        MessageHeader(header),
        serverSalt(salt),
        sessionId(session)
    {
    }

    quint64 serverSalt = 0;
    quint64 sessionId = 0;

    static constexpr int headerLength = sizeof(quint64) + sizeof(quint64)
            + sizeof(quint64) + sizeof(quint32) + sizeof(quint32);
};

struct TELEGRAMQT_EXPORT Message : public MessageHeader {
    Message() = default;
    Message(const MessageHeader &header, const QByteArray &data) :
        MessageHeader(header),
        data(data)
    {
    }

    Message(const Message &message) = default;

    void setData(const QByteArray &data);

    Q_REQUIRED_RESULT TLValue firstValue() const { return TLValue::firstFromArray(data); }
    Q_REQUIRED_RESULT Message skipTLValue() const { return skipBytes(4); }
    Q_REQUIRED_RESULT Message skipBytes(int bytes) const;

    QByteArray data;
};

inline void Message::setData(const QByteArray &newData)
{
    data = newData;
    contentLength = static_cast<quint32>(newData.size());
}

CRawStream &operator>>(CRawStream &stream, MessageHeader &message);
CRawStream &operator<<(CRawStream &stream, const MessageHeader &message);

CRawStream &operator>>(CRawStream &stream, FullMessageHeader &header);
CRawStream &operator<<(CRawStream &stream, const FullMessageHeader &header);

} // MTProto

} // Telegram namespace

#endif // TELEGRAM_QT_RPC_MESSAGE_DESCRIPTOR_HPP
