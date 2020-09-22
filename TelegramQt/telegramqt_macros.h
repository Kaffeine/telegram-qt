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

#ifndef TELEGRAMQT_MACROS_H
#define TELEGRAMQT_MACROS_H

#include <QtGlobal>

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
#define TELEGRAMQT_HEX_SHOWBASE hex << showbase
#define TELEGRAMQT_ENDL endl
#else
#define TELEGRAMQT_HEX_SHOWBASE Qt::hex << Qt::showbase
#define TELEGRAMQT_ENDL Qt::endl
#endif

#endif // TELEGRAMQT_MACROS_H
