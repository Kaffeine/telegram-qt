/*
   Copyright (C) 2014-2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_AES_KEY_HPP
#define TELEGRAM_AES_KEY_HPP

#include "telegramqt_global.h"

#include <QByteArray>

namespace Telegram {

namespace Crypto {

// Internal class
struct TELEGRAMQT_INTERNAL_EXPORT AesKey {
    QByteArray key;
    QByteArray iv;

    AesKey() = default;
    AesKey(const QByteArray &initialKey, const QByteArray &initialIV) :
        key(initialKey), iv(initialIV) { }

    AesKey &operator=(const AesKey &anotherKey)
    {
        key = anotherKey.key;
        iv  = anotherKey.iv;
        return *this;
    }
};

TELEGRAMQT_INTERNAL_EXPORT QByteArray aesDecrypt(const QByteArray &data, const AesKey &key);
TELEGRAMQT_INTERNAL_EXPORT QByteArray aesEncrypt(const QByteArray &data, const AesKey &key);

} // Crypto namespace

} // Telegram namespace

#endif // TELEGRAM_AES_KEY_HPP
