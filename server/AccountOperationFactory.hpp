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

#ifndef ACCOUNT_OPERATION_FACTORY_HPP
#define ACCOUNT_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class AccountRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(AccountRpcOperation)
public:
    explicit AccountRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processGetPassword(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runGetPassword();
    // End of generated run methods

    bool verifyAuthCode(const QString &phoneNumber, const QString &hash, const QString &code);

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (AccountRpcOperation::*)();
    using ProcessingMethod = bool (AccountRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLAuthCheckPhone m_checkPhone;
    TLFunctions::TLAuthSendCode m_sendCode;
    TLFunctions::TLAuthSignIn m_signIn;
    TLFunctions::TLAuthSignUp m_signUp;
    // End of generated RPC members
};

class AccountOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // ACCOUNT_OPERATION_FACTORY_HPP
