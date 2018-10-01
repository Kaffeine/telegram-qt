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

namespace Telegram {

namespace Utils {

TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLInputPeer &inputPeer, quint32 selfId);
TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLPeer &peer);
TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLUser &user);
TELEGRAMQT_EXPORT Telegram::Peer toPublicPeer(const TLChat *chat);

TELEGRAMQT_EXPORT TLPeer toTLPeer(const Telegram::Peer &peer);

} // Utils namespace

} // Telegram namespace

#endif // TELEGRAM_QT_API_UTILS_HPP
