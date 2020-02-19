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

#ifndef USERS_OPERATION_FACTORY_HPP
#define USERS_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class UsersRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(UsersRpcOperation)
public:
    explicit UsersRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processGetFullUser(RpcProcessingContext &context);
    bool processGetUsers(RpcProcessingContext &context);
    bool processSetSecureValueErrors(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runGetFullUser();
    void runGetUsers();
    void runSetSecureValueErrors();
    // End of generated run methods

    using RunMethod = void (UsersRpcOperation::*)();
    using ProcessingMethod = bool (UsersRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLUsersGetFullUser m_getFullUser;
    MTProto::Functions::TLUsersGetUsers m_getUsers;
    MTProto::Functions::TLUsersSetSecureValueErrors m_setSecureValueErrors;
    // End of generated RPC members
};

class UsersOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // USERS_OPERATION_FACTORY_HPP
