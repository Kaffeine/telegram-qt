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

#ifndef TLNUMBERS_HPP
#define TLNUMBERS_HPP

#include <qglobal.h>

template <int Size> union TLNumber {
    char data[Size / 8];
    quint64 parts[Size / 8 / 8];

    static constexpr int size() { return Size / 8; }

    Q_DECL_RELAXED_CONSTEXPR TLNumber() {
        for (int i = 0; i < Size / 8 / 8; ++i) {
            parts[i] = 0;
        }
    }

    Q_DECL_RELAXED_CONSTEXPR TLNumber &operator=(const TLNumber &anotherTLNumber) {
        for (int i = 0; i < Size / 8 / 8; ++i)
            parts[i] = anotherTLNumber.parts[i];

        return *this;
    }

    Q_DECL_RELAXED_CONSTEXPR bool operator ==(const TLNumber &anotherTLNumber) const {
        for (int i = 0; i < Size / 8 / 8; ++i) {
            if (parts[i] != anotherTLNumber.parts[i]) {
                return false;
            }
        }
        return true;
    }

    Q_DECL_RELAXED_CONSTEXPR bool operator !=(const TLNumber &anotherTLNumber) const {
        for (int i = 0; i < Size / 8 / 8; ++i) {
            if (parts[i] != anotherTLNumber.parts[i]) {
                return true;
            }
        }
        return false;
    }
};

using TLNumber128 = TLNumber<128>;
using TLNumber256 = TLNumber<256>;

#endif // TLNUMBERS_HPP
