/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_CLIENT_CONNECTION_API_HPP
#define TELEGRAMQT_CLIENT_CONNECTION_API_HPP

#include "ClientApi.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

class PendingOperation;

namespace Client {

class AuthOperation;
class ConnectionApiPrivate;

class TELEGRAMQT_EXPORT ConnectionApi : public ClientApi
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
public:
    explicit ConnectionApi(QObject *parent = nullptr);

    enum Status {
        StatusDisconnected,
        StatusDisconnecting,
        StatusWaitForConnection,
        StatusConnecting,
        StatusWaitForAuthentication,
        StatusConnected,
        StatusReady
    };
    Q_ENUM(Status)

    enum StatusReason {
        StatusReasonNone,
        StatusReasonLocal,
        StatusReasonError,
    };
    Q_ENUM(StatusReason)

    bool isSignedIn() const;
    Status status() const;

    Q_INVOKABLE int remainingTimeToConnect() const;

    AuthOperation *startAuthentication();
    AuthOperation *checkIn();

public Q_SLOTS:
    void disconnectFromServer();
    bool connectRightNow();

Q_SIGNALS:
    void statusChanged(Telegram::Client::ConnectionApi::Status status,
                       Telegram::Client::ConnectionApi::StatusReason reason);

protected:
    Q_DECLARE_PRIVATE_D(d, ConnectionApi)

public:
    static const char *reconnectionIntervalsEnvironmentVariableName();
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_CONNECTION_API_HPP
