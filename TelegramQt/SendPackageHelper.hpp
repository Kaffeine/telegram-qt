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

#ifndef TELEGRAM_SEND_HELPER_HPP
#define TELEGRAM_SEND_HELPER_HPP

#include "telegramqt_global.h"

#include <QObject>

namespace Telegram {

class BaseConnection;

enum class SendMode : quint8 {
    Client,
    ServerInitiative,
    ServerReply,
};

class TELEGRAMQT_INTERNAL_EXPORT BaseMTProtoSendHelper
{
public:
    virtual ~BaseMTProtoSendHelper() = default;
    virtual quint64 newMessageId(SendMode mode) = 0;
    BaseConnection *getConnection() const { return m_connection; }

    virtual void sendPacket(const QByteArray &package) = 0;

    qint32 deltaTime() const { return m_deltaTime; }
    void setDeltaTime(const qint32 newDt);

    quint64 authId() const { return m_authId; }
    QByteArray getServerKeyPart() const { return m_authKey.mid(96, 32); }
    QByteArray getClientKeyPart() const { return m_authKey.mid(88, 32); }
    QByteArray authKey() const { return m_authKey; }
    void setAuthKey(const QByteArray &authKey);

protected:
    BaseConnection *m_connection = nullptr;
    quint64 m_lastMessageId = 0;

    quint64 m_authId = 0;
    QByteArray m_authKey;
    qint32 m_deltaTime = 0;
};

} // Telegram namespace

#endif // TELEGRAM_SEND_HELPER_HPP
