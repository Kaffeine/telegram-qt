/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QTimer;
QT_END_NAMESPACE

class CTcpTransport : public CTelegramTransport
{
    Q_OBJECT
public:
    explicit CTcpTransport(QObject *parent = 0);
    ~CTcpTransport();

    void connectToHost(const QString &ipAddress, quint32 port) override;
    void disconnectFromHost() override;
    bool setProxy(const QNetworkProxy &proxy) override;

    bool isConnected() const override;

    QByteArray getPackage() override { return m_receivedPackage; }

    // Method for testing
    QByteArray lastPackage() const override { return m_lastPackage; }

public slots:
    void sendPackage(const QByteArray &payload) override;

private slots:
    void onStateChanged(QAbstractSocket::SocketState newState);
    void onError(QAbstractSocket::SocketError error);
    void onReadyRead();
    void onTimeout();

private:
    quint32 m_packetNumber;
    quint32 m_expectedLength;

    QByteArray m_receivedPackage;
    QByteArray m_lastPackage;

    QTcpSocket *m_socket;
    QTimer *m_timeoutTimer;

    bool m_firstPackage;

};

#endif // CTCPTRANSPORT_HPP
