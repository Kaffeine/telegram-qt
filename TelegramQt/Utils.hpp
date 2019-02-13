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

#include "crypto-aes.hpp"
#include "RsaKey.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Utils {

enum BitsOrder64 {
    Higher64Bits,
    Lower64Bits,
};

int randomBytes(QByteArray *array);

template <typename T>
T randomBytes();

template <typename T>
int randomBytes(T *number);

int randomBytes(void *buffer, int count);

QByteArray getRandomBytes(int count);

quint64 greatestCommonOddDivisor(quint64 a, quint64 b);
quint64 findDivider(quint64 number);
QByteArray sha1(const QByteArray &data);
QByteArray sha256(const QByteArray &data);
quint64 getFingerprints(const QByteArray &data, const BitsOrder64 order);
QByteArray binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp);
QByteArray rsa(const QByteArray &data, const Telegram::RsaKey &key);
QByteArray aesDecrypt(const QByteArray &data, const SAesKey &key);
QByteArray aesEncrypt(const QByteArray &data, const SAesKey &key);
QByteArray packGZip(const QByteArray &data);
QByteArray unpackGZip(const QByteArray &data);

constexpr quint32 c_gzipBufferSize = 1024;

}

inline int Utils::randomBytes(QByteArray *array)
{
    return randomBytes(array->data(), array->size());
}

template<typename T>
int Utils::randomBytes(T *number)
{
    return randomBytes(number, sizeof(T));
}

template <typename T>
inline T Utils::randomBytes()
{
    T result;
    randomBytes(&result);
    return result;
}

inline QByteArray Utils::rsa(const QByteArray &data, const Telegram::RsaKey &key)
{
    return binaryNumberModExp(data, key.modulus, key.exponent);
}

} // Telegram namespace

#endif // UTILS_HPP
