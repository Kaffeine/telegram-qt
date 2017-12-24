/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef CTCPTRANSPORT_HPP
#define CTCPTRANSPORT_HPP

#include "CTelegramTransport.hpp"

QT_FORWARD_DECLARE_CLASS(QTimer)

class CTcpTransport : public CTelegramTransport
{
    Q_OBJECT
public:
    enum SessionType {
        Unknown,
        Abridged, // char(0xef)
        FullSize
    };
    Q_ENUM(SessionType)

    explicit CTcpTransport(QObject *parent = nullptr);
    ~CTcpTransport();

    void connectToHost(const QString &ipAddress, quint32 port) override;
    void disconnectFromHost() override;

protected slots:
    void setState(QAbstractSocket::SocketState newState) override;
    void onReadyRead();
    void onTimeout();

protected:
    void setSocket(QAbstractSocket *socket);
    void sendPackageImplementation(const QByteArray &payload) override;

    void setSessionType(SessionType sessionType);

    quint32 m_packetNumber = 0;
    quint32 m_expectedLength = 0;
    SessionType m_sessionType = Unknown;

    QAbstractSocket *m_socket = nullptr;
    QTimer *m_timeoutTimer = nullptr;
};

#endif // CTCPTRANSPORT_HPP
