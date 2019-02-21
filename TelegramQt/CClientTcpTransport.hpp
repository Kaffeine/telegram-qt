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

#ifndef CCLIENTTCPTRANSPORT_HPP
#define CCLIENTTCPTRANSPORT_HPP

#include "CTcpTransport.hpp"

QT_FORWARD_DECLARE_CLASS(QTimer)

namespace Telegram {

namespace Client {

class TcpTransport : public BaseTcpTransport
{
    Q_OBJECT
public:
    explicit TcpTransport(QObject *parent = nullptr);
    ~TcpTransport() override;

    void connectToHost(const QString &ipAddress, quint16 port) override;

    SessionType preferredSessionType() const { return m_preferedSessionType; }
    void setPreferedSessionType(const SessionType sessionType);

    void startObfuscatedSession();
    void startAbridgedSession();
    bool setProxy(const QNetworkProxy &proxy);

protected:
    void setState(QAbstractSocket::SocketState newState) override;

    void onTimeout();
    void writeEvent() final;

    QTimer *m_timeoutTimer = nullptr;
    SessionType m_preferedSessionType = Default;
};

} // Client namespace

} // Telegram namespace

#endif // CCLIENTTCPTRANSPORT_HPP
