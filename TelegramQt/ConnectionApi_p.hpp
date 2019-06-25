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

QT_FORWARD_DECLARE_CLASS(QTimer)

namespace Telegram {

namespace Client {

class Connection;
class ConnectOperation;
class PingOperation;

class ConnectionApiPrivate : public ClientApiPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(ConnectionApi)
public:
    enum SetConnectionOption {
        DestroyOldConnection,
        KeepOldConnection,
    };

    explicit ConnectionApiPrivate(ConnectionApi *parent = nullptr);
    static ConnectionApiPrivate *get(ConnectionApi *parent);

    bool isSignedIn() const;

    void disconnectFromServer();

    // Internal API
    PendingOperation *connectToDc(quint32 dcId);
    PendingOperation *connectToServer(const QVector<DcOption> &dcOptions);

    AuthOperation *getAuthenticationOperation() const { return m_authOperation; }
    AuthOperation *startAuthentication();
    AuthOperation *checkIn();
    ConnectionApi::Status status() const { return m_status; }

    QVariantHash getBackendSetupErrorDetails() const;

public:
    // Internal TelegramQt API
    Connection *createConnection(const DcOption &dcOption);
    Connection *ensureConnection(const ConnectionSpec &connectionSpec);

    Connection *getDefaultConnection();
    Connection *mainConnection();
    void setMainConnection(Connection *connection, SetConnectionOption option = KeepOldConnection);
    void setInitialConnection(Connection *connection, SetConnectionOption option = KeepOldConnection);

protected slots:
    void connectToNextServer();
    void queueConnectToNextServer();

    void onReconnectOperationFinished(PendingOperation *operation);
    void onInitialConnectionStatusChanged(BaseConnection::Status status, BaseConnection::StatusReason reason);
    void onGotDcConfig(PendingOperation *operation);
    void onCheckInFinished(PendingOperation *operation);
    void onNewAuthenticationFinished(PendingOperation *operation);
    void onAuthCodeRequired();
    void onConnectionStatusChanged(BaseConnection::Status status, BaseConnection::StatusReason reason);
    void onMainConnectionStatusChanged(BaseConnection::Status status, BaseConnection::StatusReason reason);
    void onMainConnectionLost();
    void onMainConnectionRestored();
    void onSyncFinished(PendingOperation *operation);
    void onPingFailed();
    void onConnectionError(const QByteArray &errorBytes);

protected:
    void setStatus(ConnectionApi::Status status, ConnectionApi::StatusReason reason);

    QHash<ConnectionSpec, Connection *> m_connections;
    Connection *m_mainConnection = nullptr;
    Connection *m_initialConnection = nullptr;
    PendingOperation *m_initialConnectOperation = nullptr;
    AuthOperation *m_authOperation = nullptr;
    PingOperation *m_pingOperation = nullptr;

    ConnectionApi::Status m_status = ConnectionApi::StatusDisconnected;
    QVector<DcOption> m_serverConfiguration;
    int m_nextServerAddressIndex = 0;
    int m_connectionAttemptNumber = 0;
    bool m_connectionQueued = false;
    QTimer *m_queuedConnectionTimer = nullptr;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_CONTACTS_API_PRIVATE_HPP
