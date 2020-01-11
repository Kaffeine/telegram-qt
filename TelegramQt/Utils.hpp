/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QByteArray>

#include "RsaKey.hpp"

namespace Telegram {

namespace Utils {

enum BitsOrder64 {
    Higher64Bits,
    Lower64Bits,
};

TELEGRAMQT_INTERNAL_EXPORT quint64 greatestCommonOddDivisor(quint64 a, quint64 b);
TELEGRAMQT_INTERNAL_EXPORT quint64 findDivider(quint64 number);
TELEGRAMQT_INTERNAL_EXPORT QByteArray sha1(const QByteArray &data);
TELEGRAMQT_INTERNAL_EXPORT QByteArray sha256(const QByteArray &data);
TELEGRAMQT_INTERNAL_EXPORT quint64 getFingerprints(const QByteArray &data, const BitsOrder64 order);
TELEGRAMQT_INTERNAL_EXPORT QByteArray binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp);
TELEGRAMQT_INTERNAL_EXPORT QByteArray rsa(const QByteArray &data, const Telegram::RsaKey &key);
TELEGRAMQT_INTERNAL_EXPORT QByteArray packGZip(const QByteArray &data);
TELEGRAMQT_INTERNAL_EXPORT QByteArray unpackGZip(const QByteArray &data);

constexpr quint32 c_gzipBufferSize = 1024;

} // Utils

inline QByteArray Utils::rsa(const QByteArray &data, const Telegram::RsaKey &key)
{
    return binaryNumberModExp(data, key.modulus, key.exponent);
}

} // Telegram namespace

#endif // UTILS_HPP
