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

#ifndef TELEGRAMQT_CLIENT_AUTH_OPERATION_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_AUTH_OPERATION_PRIVATE_HPP

#include "PendingOperation_p.hpp"
#include "ClientAuthOperation.hpp"

#include <QVector>

struct TLAuthAuthorization;

namespace Telegram {

class RpcError;

namespace Client {

class AccountRpcLayer;
class AuthRpcLayer;

class AuthOperation;
class Backend;
class Connection;
class PendingRpcOperation;

class AuthOperationPrivate : public QObject, public PendingOperationPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(AuthOperation)
public:
    explicit AuthOperationPrivate(AuthOperation *parent);

    static AuthOperationPrivate *get(AuthOperation *parent);
    static const AuthOperationPrivate *get(const AuthOperation *parent);
    QObject *toQObject() override { return this; }
    const QObject *toQObject() const override { return this; }

    void setBackend(Backend *backend);

    AccountRpcLayer *accountLayer() const;
    AuthRpcLayer *authLayer() const;

    using RunMethod = void (AuthOperationPrivate::*)();
    void setRunMethod(RunMethod method);

    void checkAuthorization();
    void requestAuthCode();

    PendingOperation *submitAuthCode(const QString &code);
    PendingOperation *submitPassword(const QString &password);

    Backend *m_backend = nullptr;

    RunMethod m_runMethod = nullptr;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_passwordHint;
    QString m_authCodeHash;
    QByteArray m_passwordCurrentSalt;
    bool m_hasRecovery;
    bool m_registered = false;
    Connection *m_authenticatedConnection = nullptr;

protected slots:
    // Implementation:
    PendingOperation *getPassword();

    void onRequestAuthCodeFinished(PendingRpcOperation *rpcOperation);
    void onAuthenticationRpcError(const RpcError *error);
    void onSignInRpcFinished(PendingRpcOperation *rpcOperation, PendingOperation *submitAuthCodeOperation);
    void onSignUpRpcFinished(PendingRpcOperation *rpcOperation, PendingOperation *submitAuthCodeOperation);
    void onPasswordRequestFinished(PendingRpcOperation *operation);
    void onCheckPasswordFinished(PendingRpcOperation *operation);
    void onGotAuthorization(PendingRpcOperation *operation, const TLAuthAuthorization &authorization);

    void onAccountStatusUpdateFinished(PendingRpcOperation *operation);

    void onConnectionError(const QByteArray &errorBytes);
    void onRedirectedConnectFinished(PendingOperation *operation);

protected:
    void setPasswordCurrentSalt(const QByteArray &salt);
    void setPasswordHint(const QString &hint);
    void setRegistered(bool registered);
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_AUTH_OPERATION_PRIVATE_HPP
