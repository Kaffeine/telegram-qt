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

#ifndef CRYPTOAES_HPP
#define CRYPTOAES_HPP

#include <QByteArray>

struct SAesKey {
    QByteArray key;
    QByteArray iv;

    SAesKey(const QByteArray &initialKey = QByteArray(), const QByteArray &initialIV = QByteArray()) :
        key(initialKey), iv(initialIV) { }

    SAesKey &operator=(const SAesKey &anotherKey)
    {
        key = anotherKey.key;
        iv  = anotherKey.iv;
        return *this;
    }
};

#endif // CRYPTOAES_HPP
