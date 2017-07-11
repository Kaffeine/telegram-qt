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

#include "crypto-rsa.hpp"
#include "crypto-aes.hpp"

class Utils
{
public:
    static int randomBytes(QByteArray *array);
    static int randomBytes(quint64 *number);
    static int randomBytes(char *buffer, int count);
    static quint64 greatestCommonOddDivisor(quint64 a, quint64 b);
    static quint64 findDivider(quint64 number);
    static QByteArray sha1(const QByteArray &data);
    static QByteArray sha256(const QByteArray &data);
    static quint64 getFingersprint(const QByteArray &data, bool lowerOrderBits = true);
    static SRsaKey loadHardcodedKey();
    static SRsaKey loadRsaKey();
    static QByteArray binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp);
    static QByteArray rsa(const QByteArray &data, const SRsaKey &key);
    static QByteArray aesDecrypt(const QByteArray &data, const SAesKey &key);
    static QByteArray aesEncrypt(const QByteArray &data, const SAesKey &key);
    static QByteArray unpackGZip(const QByteArray &data);

};

inline int Utils::randomBytes(QByteArray *array)
{
    return randomBytes(array->data(), array->size());
}

inline int Utils::randomBytes(quint64 *number)
{
    return randomBytes((char *) number, 8);
}

inline QByteArray Utils::rsa(const QByteArray &data, const SRsaKey &key)
{
    return binaryNumberModExp(data, key.key, key.exp);
}

#endif // UTILS_HPP
