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

#ifndef AUTH_OPERATION_FACTORY_HPP
#define AUTH_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class AuthRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(AuthRpcOperation)
public:
    explicit AuthRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processCheckPhone(RpcProcessingContext &context);
    bool processSendCode(RpcProcessingContext &context);
    bool processSignUp(RpcProcessingContext &context);
    bool processSignIn(RpcProcessingContext &context);
    bool processCheckPassword(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runCheckPhone();
    void runSendCode();
    void runSignUp();
    void runSignIn();
    void runCheckPassword();
    // End of generated run methods

    bool verifyAuthCode(const QString &phoneNumber, const QString &hash, const QString &code);

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (AuthRpcOperation::*)();
    using ProcessingMethod = bool (AuthRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLAuthCheckPhone m_checkPhone;
    TLFunctions::TLAuthSendCode m_sendCode;
    TLFunctions::TLAuthSignIn m_signIn;
    TLFunctions::TLAuthSignUp m_signUp;
    TLFunctions::TLAuthCheckPassword m_checkPassword;
    // End of generated RPC members
};

class AuthOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // RPC_OPERATION_FACTORY_HPP
