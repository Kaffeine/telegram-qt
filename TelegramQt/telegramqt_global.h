/*
   Copyright (C) 2014-2016 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_GLOBAL_H
#define TELEGRAMQT_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(TELEGRAMQT_LIBRARY)
#define TELEGRAMQT_EXPORT Q_DECL_EXPORT
#else
#define TELEGRAMQT_EXPORT Q_DECL_IMPORT
#endif

#endif // TELEGRAMQT_GLOBAL_H
