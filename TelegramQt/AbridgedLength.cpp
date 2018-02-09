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

#include "AbridgedLength.hpp"

namespace Telegram {

quint32 AbridgedLength::paddingForAlignment(quint32 alignment) const
{
    const quint32 totalSize = m_value + packedSize();
    const quint32 overhungBytes = totalSize % alignment;
    if (Q_LIKELY(overhungBytes)) {
        return alignment - overhungBytes;
    }
    return 0;
}

} // Telegram
