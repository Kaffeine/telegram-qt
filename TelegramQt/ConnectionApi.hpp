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
public:
    explicit ConnectionApi(QObject *parent = nullptr);

    enum Status {
        StatusDisconnected,
        StatusDisconnecting,
        StatusWaitForConnection, // Wait for some time before the try to connect
        StatusConnecting,
        StatusWaitForAuthentication, // Has active DH connection and has DC config
        StatusConnected,
        StatusReady // Authenticated and got initial data
    };
    Q_ENUM(Status)

    enum StatusReason {
        StatusReasonNone,
        StatusReasonLocal,
        StatusReasonRemote,
        StatusReasonTimeout
    };
    Q_ENUM(StatusReason)

    bool isSignedIn() const;
    Status status() const;

    AuthOperation *startAuthentication();
    AuthOperation *checkIn();
    void disconnectFromServer();

Q_SIGNALS:
    void statusChanged(Telegram::Client::ConnectionApi::Status status, Telegram::Client::ConnectionApi::StatusReason reason);

protected:
    Q_DECLARE_PRIVATE_D(d, ConnectionApi)

public:
    static const char *reconnectionIntervalsEnvironmentVariableName();
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_CONNECTION_API_HPP
