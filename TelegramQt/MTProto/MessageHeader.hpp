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
#include <QByteArray>

class CRawStream;

namespace Telegram {

namespace MTProto {

struct TELEGRAMQT_EXPORT MessageHeader {
    quint64 messageId;
    quint32 sequenceNumber;
    quint32 contentLength;

    static constexpr int headerLength = sizeof(messageId) + sizeof(sequenceNumber) + sizeof(contentLength);
};

struct TELEGRAMQT_EXPORT FullMessageHeader : public MessageHeader
{
    quint64 serverSalt = 0;
    quint64 sessionId = 0;

    static constexpr int headerLength = sizeof(serverSalt) + sizeof(sessionId)
            + sizeof(messageId) + sizeof(sequenceNumber) + sizeof(contentLength);
};

CRawStream &operator>>(CRawStream &stream, MessageHeader &message);
CRawStream &operator<<(CRawStream &stream, const MessageHeader &message);

CRawStream &operator>>(CRawStream &stream, FullMessageHeader &header);
CRawStream &operator<<(CRawStream &stream, const FullMessageHeader &header);

} // MTProto

} // Telegram namespace

#endif // TELEGRAM_QT_RPC_MESSAGE_DESCRIPTOR_HPP
