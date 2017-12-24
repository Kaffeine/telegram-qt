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

#include "CTelegramTransportModule.hpp"

#include "CTelegramConnection.hpp"
#include "CClientTcpTransport.hpp"

static const quint32 s_defaultPingInterval = 15000; // 15 sec
static const quint32 s_minimalPingAdditionalInterval = 1000; // 1 sec

using namespace Telegram;

CTelegramTransportModule::CTelegramTransportModule(QObject *parent) :
    CTelegramModule(parent),
    m_pingInterval(s_defaultPingInterval),
    m_pingServerAdditionDisconnectionTime(s_minimalPingAdditionalInterval)
{
}

QNetworkProxy CTelegramTransportModule::proxy() const
{
    return m_proxy;
}

void CTelegramTransportModule::setProxy(const QNetworkProxy &proxy)
{
    m_proxy = proxy;
}

quint32 CTelegramTransportModule::defaultPingInterval()
{
    return s_defaultPingInterval;
}

void CTelegramTransportModule::setPingInterval(quint32 ms, quint32 serverDisconnectionAdditionalTime)
{
    m_pingInterval = ms;
    if (serverDisconnectionAdditionalTime < s_minimalPingAdditionalInterval) {
        serverDisconnectionAdditionalTime = s_minimalPingAdditionalInterval;
    }
    m_pingServerAdditionDisconnectionTime = serverDisconnectionAdditionalTime;
}

void CTelegramTransportModule::onNewConnection(CTelegramConnection *connection)
{
    Client::TcpTransport *transport = new Client::TcpTransport(connection);
    transport->setProxy(m_proxy);
    connection->setTransport(transport);
}

void CTelegramTransportModule::onConnectionStateChanged(TelegramNamespace::ConnectionState newConnectionState)
{
    if (newConnectionState == TelegramNamespace::ConnectionStateReady) {
        if (!mainConnection()) {
            qCritical() << Q_FUNC_INFO << "Internal inconsistency: the Telegram connection state is \"Ready\", but the mainConnection() is not available!";
            return;
        }
        mainConnection()->setKeepAliveSettings(m_pingInterval, m_pingServerAdditionDisconnectionTime);
    }
}
