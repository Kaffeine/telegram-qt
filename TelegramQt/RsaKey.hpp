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

#ifndef TELEGRAM_RSA_KEY_HPP
#define TELEGRAM_RSA_KEY_HPP

#include "telegramqt_global.h"

#include <QByteArray>

namespace Telegram {

struct TELEGRAMQT_EXPORT RsaKey
{
    QByteArray modulus;
    QByteArray exponent;
    QByteArray secretExponent;
    quint64 fingerprint = 0;

    RsaKey() = default;
    RsaKey(const QByteArray &initialModulus, const QByteArray &initialExponent, const quint64 initialFingersprint = 0) :
        modulus(initialModulus), exponent(initialExponent), fingerprint(initialFingersprint)
    {
    }

    RsaKey &operator=(const RsaKey &otherKey)
    {
        modulus = otherKey.modulus;
        exponent = otherKey.exponent;
        secretExponent = otherKey.secretExponent;
        fingerprint = otherKey.fingerprint;
        return *this;
    }

    void updateFingersprint();
    bool isValid() const;
    bool isPrivate() const;

    void loadFromFile(const QString &fileName);

    static quint64 getFingerprint(const RsaKey &key);
    static RsaKey fromFile(const QString &fileName);
    static RsaKey defaultKey(); // official Telegram server key
};

} // Telegram namespace

#endif // TELEGRAM_RSA_KEY_HPP
