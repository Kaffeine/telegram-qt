/*
   Copyright (C) 2020 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_COMPAT_LAYER_HPP
#define TELEGRAMQT_COMPAT_LAYER_HPP

#include "telegramqt_global.h"

#include <QString>

#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
#define TELEGRAMQT_PUBLIC_SLOTS public Q_SLOTS
#else
#define TELEGRAMQT_PUBLIC_SLOTS public
#endif

#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
#define TELEGRAMQT_PROTECTED_SLOTS protected Q_SLOTS
#else
#define TELEGRAMQT_PROTECTED_SLOTS protected
#endif

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
#define TELEGRAMQT_HEX_SHOWBASE hex << showbase
#define TELEGRAMQT_ENDL endl
#define TELEGRAMQT_FLUSH flush
#else
#define TELEGRAMQT_HEX_SHOWBASE Qt::hex << Qt::showbase
#define TELEGRAMQT_ENDL Qt::endl
#define TELEGRAMQT_FLUSH Qt::flush
#endif

namespace Telegram {

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
inline QStringView getStringMidView(const QString &string, qsizetype pos, qsizetype n = -1)
{
    return QStringView(string).mid(pos, n);
}
#else
inline QStringRef getStringMidView(const QString &string, int pos, int n = -1)
{
    return string.midRef(pos, n);
}
#endif

} // Telegram namespace

#endif // TELEGRAMQT_COMPAT_LAYER_HPP
