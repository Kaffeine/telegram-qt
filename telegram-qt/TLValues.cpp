/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "TLValues.hpp"

#include <QMetaEnum>

QString TLValue::toString() const
{
    static const int index = staticMetaObject.indexOfEnumerator("Value");
    static const QMetaEnum enumerator = staticMetaObject.enumerator(index);

    const char *value = enumerator.valueToKey(m_value);
    if (value) {
        return QString::fromLatin1(value);
    } else {
        return QString(QLatin1String("%1")).arg(m_value, 8, 16, QLatin1Char('0'));
    }
}

#ifdef DEVELOPER_BUILD
TLValue TLValue::firstFromArray(const QByteArray &data)
{
    if (data.length() >= 4) {
        quint32 *v = (quint32 *) data.constData();
        return TLValue(*v);
    }
    return TLValue();
}
#endif
