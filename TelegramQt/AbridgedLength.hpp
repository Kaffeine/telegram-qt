/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#ifndef ABRIDGED_LENGTH_HPP
#define ABRIDGED_LENGTH_HPP

#include "telegramqt_global.h"

namespace Telegram {

class TELEGRAMQT_EXPORT AbridgedLength
{
public:
    constexpr explicit AbridgedLength(quint32 value = 0) : m_value(value) { }
    constexpr operator quint32() const { return m_value; }
    AbridgedLength &operator=(quint32 value) { m_value = value; return *this; }
    constexpr quint32 packedSize() const { return m_value < 0xfe ? 1: 4; }
    quint32 paddingForAlignment(quint32 alignment) const;
    static quint32 paddingForAlignment(quint32 alignment, quint32 size);
private:
    quint32 m_value = 0;
};

} // Telegram

#endif // ABRIDGED_LENGTH_HPP
