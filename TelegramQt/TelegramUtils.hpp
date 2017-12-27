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

#ifndef CTELEGRAMUTILS_HPP
#define CTELEGRAMUTILS_HPP

#include "TelegramNamespace.hpp"
#include "TLValues.hpp"

namespace TelegramUtils
{
    QString mimeTypeByStorageFileType(TLValue type);
    TelegramNamespace::MessageType telegramMessageTypeToPublicMessageType(TLValue type);
    TLValue::Value publicMessageTypeToTelegramMessageType(TelegramNamespace::MessageType type);
    TelegramNamespace::MessageAction telegramMessageActionToPublicAction(TLValue action);
    TLValue::Value publicMessageActionToTelegramAction(TelegramNamespace::MessageAction action);

    enum TelegramMessageFlags {
        TelegramMessageFlagNone    = 0,
        TelegramMessageFlagUnread  = 1 << 0,
        TelegramMessageFlagOut     = 1 << 1,
        TelegramMessageFlagForward = 1 << 2,
        TelegramMessageFlagReply   = 1 << 3,
    };

quint64 formatTimeStamp(qint64 timeInMs);
quint64 timeStampToMSecsSinceEpoch(quint64 ts);

}

#endif // CTELEGRAMUTILS_HPP
