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

#ifndef CTELEGRAMTRANSPORTMODULE_HPP
#define CTELEGRAMTRANSPORTMODULE_HPP

#include "CTelegramModule.hpp"

#include <QNetworkProxy>

class CTelegramTransportModule : public CTelegramModule
{
    Q_OBJECT
public:
    explicit CTelegramTransportModule(QObject *parent = nullptr);

    QNetworkProxy proxy() const;
    void setProxy(const QNetworkProxy &proxy);

    static quint32 defaultPingInterval();
    void setPingInterval(quint32 ms, quint32 serverDisconnectionAdditionalTime);

    void onNewConnection(CTelegramConnection *connection) override;

protected:
    void onConnectionStateChanged(TelegramNamespace::ConnectionState newConnectionState) override;

    QNetworkProxy m_proxy;

    quint32 m_pingInterval;
    quint32 m_pingServerAdditionDisconnectionTime;

};

#endif // CTELEGRAMTRANSPORTMODULE_HPP
