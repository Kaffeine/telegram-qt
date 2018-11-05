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

#ifndef TELEGRAMQT_CLIENT_CONNECTION_API_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_CONNECTION_API_PRIVATE_HPP

#include "ClientApi_p.hpp"
#include "Connection.hpp"
#include "ConnectionApi.hpp"

#include "DcConfiguration.hpp"

#include <QHash>

namespace Telegram {

namespace Client {

class Connection;
class ConnectOperation;
class ConnectionApi;
class ConnectionApiPrivate : public ClientApiPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(ConnectionApi)
public:
    using Status = ConnectionApi::Status;

    explicit ConnectionApiPrivate(ConnectionApi *parent = nullptr);
    static ConnectionApiPrivate *get(ConnectionApi *parent);

    bool isSignedIn() const;

    // Public API implementation
    PendingOperation *connectToServer(const QVector<DcOption> &dcOptions);
    AuthOperation *signIn();
    AuthOperation *checkIn();
    Status status() const { return m_status; }

public:
    // Internal TelegramQt API
    Connection *createConnection(const DcOption &dcOption);
    Connection *ensureConnection(const ConnectionSpec &dcSpec);

    Connection *getDefaultConnection();
    Connection *mainConnection();
    void setMainConnection(Connection *connection);

protected slots:
    void onConnectOperationFinished(PendingOperation *operation);
    void onUpcomingConnectionStatusChanged(BaseConnection::Status status, BaseConnection::StatusReason reason);
    void onAuthFinished(PendingOperation *operation);
    void onAuthCodeRequired();
    void onMainConnectionStatusChanged();
    void onSyncFinished(PendingOperation *operation);

protected:
    void setStatus(Status newStatus);

    QHash<ConnectionSpec, Connection *> m_connections;
    Connection *m_mainConnection = nullptr;
    ConnectOperation *m_connectToServerOperation = nullptr;
    AuthOperation *m_authOperation = nullptr;

    Status m_status = Status::StatusDisconnected;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_CONTACTS_API_PRIVATE_HPP
