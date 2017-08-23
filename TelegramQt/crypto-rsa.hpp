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

#ifndef CRYPTO_RSA_HPP
#define CRYPTO_RSA_HPP

#include <QByteArray>

struct SRsaKey {
    QByteArray key;
    QByteArray exp;
    quint64 fingersprint;

    SRsaKey(const QByteArray &initialKey = QByteArray(), const QByteArray &initialExp = QByteArray(), const quint64 initialFingersprint = 0) :
        key(initialKey), exp(initialExp), fingersprint(initialFingersprint) { }

    SRsaKey &operator=(const SRsaKey &anotherKey)
    {
        key = anotherKey.key;
        exp = anotherKey.exp;
        fingersprint = anotherKey.fingersprint;
        return *this;
    }
};

#endif // CRYPTO_RSA_HPP
