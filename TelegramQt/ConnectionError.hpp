/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_CONNECTION_ERROR_HPP
#define TELEGRAM_CONNECTION_ERROR_HPP

#include "telegramqt_global.h"

#include <QObject>
#include <QByteArray>

namespace Telegram {

class TELEGRAMQT_EXPORT ConnectionError
{
    Q_GADGET
public:
    enum Code : qint32 {
        InvalidAuthKey = -404, // 6cfeffff in network byte order, Auth key id is not found in the server DB
        Flood = -429,
    };
    Q_ENUM(Code)

    ConnectionError() = default;
    explicit ConnectionError(const QByteArray &data);
    explicit ConnectionError(const qint32 code);

    static constexpr int packetSize() { return 4; }

    Q_REQUIRED_RESULT Code code() const;
    Q_REQUIRED_RESULT QByteArray toByteArray() const;
    Q_REQUIRED_RESULT QString description() const;

private:
    qint32 m_code = 0;
};

} // Telegram namespace

#endif // TELEGRAM_CONNECTION_ERROR_HPP
