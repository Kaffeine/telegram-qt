/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "CClientTcpTransport.hpp"

#include <QTcpSocket>

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

Q_LOGGING_CATEGORY(c_loggingTranport, "telegram.client.transport", QtWarningMsg)

TcpTransport::TcpTransport(QObject *parent) :
    CTcpTransport(parent)
{
    setSocket(new QTcpSocket(this));
}

bool TcpTransport::setProxy(const QNetworkProxy &proxy)
{
    if (m_socket->isOpen()) {
        qCWarning(c_loggingTranport) << Q_FUNC_INFO << "Unable to set proxy on open socket";
        return false;
    }
    m_socket->setProxy(proxy);
    return true;
}

void TcpTransport::writeEvent()
{
    if (Q_LIKELY(m_sessionType != Unknown)) {
        return;
    }
    qCDebug(c_loggingTranport()) << "Start session in Abridged format";
    m_socket->putChar(char(0xef));
    setSessionType(Abridged);
}

} // Client

} // Telegram
