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

#ifndef TELEGRAM_QT_API_UTILS_HPP
#define TELEGRAM_QT_API_UTILS_HPP

#include "telegramqt_global.h"

#include "TelegramNamespace.hpp"
#include "TLTypes.hpp"

#include <QDateTime>

namespace Telegram {

namespace Utils {

TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLInputPeer &inputPeer, quint32 selfId);
TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLPeer &peer);
TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLUser &user);
TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLChat *chat);

TELEGRAMQT_EXPORT TLPeer toTLPeer(const Telegram::Peer &peer);

TELEGRAMQT_EXPORT Telegram::Peer getMessageDialogPeer(const TLMessage &message, quint32 applicantUserId);

TELEGRAMQT_EXPORT QString mimeTypeByStorageFileType(TLValue type);
TELEGRAMQT_EXPORT TelegramNamespace::MessageType getPublicMessageType(const TLMessageMedia &media);
TELEGRAMQT_EXPORT TLValue::Value toTLValue(TelegramNamespace::MessageType type);
TELEGRAMQT_EXPORT TelegramNamespace::MessageAction toPublicMessageAction(TLValue action);
TELEGRAMQT_EXPORT TLValue::Value toTLValue(TelegramNamespace::MessageAction action);

TELEGRAMQT_EXPORT quint64 formatTimeStamp(qint64 timeInMs);
TELEGRAMQT_EXPORT quint64 timeStampToMSecsSinceEpoch(quint64 ts);

TELEGRAMQT_EXPORT quint32 getCurrentTime();

} // Utils namespace

} // Telegram namespace

inline quint32 Telegram::Utils::getCurrentTime()
{
#if QT_VERSION > QT_VERSION_CHECK(5, 8, 0)
    qint64 timestamp = QDateTime::currentSecsSinceEpoch();
#else
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
#endif
    return static_cast<quint32>(timestamp);
}

#endif // TELEGRAM_QT_API_UTILS_HPP
