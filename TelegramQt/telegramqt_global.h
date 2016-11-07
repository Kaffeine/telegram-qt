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

#define TELEGRAMQT_MAJOR_VERSION 0
#define TELEGRAMQT_MINOR_VERSION 2
#define TELEGRAMQT_MICRO_VERSION 0
#define TELEGRAMQT_VERSION ((TP_QT_MAJOR_VERSION<<16)|(TP_QT_MINOR_VERSION<<8)|(TP_QT_MICRO_VERSION))

/**
 * @def TELEGRAMQT_VERSION_CHECK
 * @ingroup macros
 *
 * The TELEGRAMQT_VERSION_CHECK macro can be used to do condition compilation
 * in TelegramQt-based applications and libraries.
 *
 * \code
 * #if (TELEGRAMQT_VERSION < TELEGRAMQT_VERSION_CHECK(0, 2, 0))
 *     m_core->setAcceptableMessageTypes(TelegramNamespace::MessageTypeText|TelegramNamespace::MessageTypePhoto);
 * #else
 *     m_core->setAcceptableMessageTypes(TelegramNamespace::MessageTypeAll);
 * #endif
 * \endcode
 */
#define TELEGRAMQT_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#if defined(TELEGRAMQT_LIBRARY)
#define TELEGRAMQT_EXPORT Q_DECL_EXPORT
#else
#define TELEGRAMQT_EXPORT Q_DECL_IMPORT
#endif

#endif // TELEGRAMQT_GLOBAL_H
