/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "RemoteClientConnectionHelper.hpp"

#include "ApiUtils.hpp"
#include "Connection.hpp"
#include "CTelegramTransport.hpp"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(loggingCategoryRemoteClientConnection)

namespace Telegram {

namespace Server {

MTProtoSendHelper::MTProtoSendHelper(BaseConnection *connection) :
    BaseMTProtoSendHelper()
{
    m_connection = connection;
}

quint64 MTProtoSendHelper::newMessageId(SendMode mode)
{
    quint64 ts = Telegram::Utils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch());
    if (mode == SendMode::ServerReply) {
        ts &= ~quint64(3);
        ts |= 1;
    } else if (mode == SendMode::ServerInitiative) {
        ts |= 3;
    } else {
        qCWarning(loggingCategoryRemoteClientConnection) << Q_FUNC_INFO << "Invalid mode";
    }
    return m_connection->transport()->getNewMessageId(ts);
}

void MTProtoSendHelper::sendPacket(const QByteArray &package)
{
    return m_connection->transport()->sendPacket(package);
}

RemoteClientConnection *MTProtoSendHelper::getRemoteClientConnection() const
{
    return reinterpret_cast<RemoteClientConnection *>(m_connection);
}

} // Server namespace

} // Telegram namespace
