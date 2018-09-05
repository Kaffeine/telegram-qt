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

#include "UsersOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"
#include "Utils.hpp"

#include "CTelegramStreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool UsersRpcOperation::processGetFullUser(RpcProcessingContext &context)
{
    setRunMethod(&UsersRpcOperation::runGetFullUser);
    context.inputStream() >> m_getFullUser;
    return !context.inputStream().error();
}

bool UsersRpcOperation::processGetUsers(RpcProcessingContext &context)
{
    setRunMethod(&UsersRpcOperation::runGetUsers);
    context.inputStream() >> m_getUsers;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void UsersRpcOperation::runGetFullUser()
{
    if (processNotImplementedMethod(TLValue::UsersGetFullUser)) {
        return;
    }
    TLUserFull result;
    sendRpcReply(result);
}

void UsersRpcOperation::runGetUsers()
{
    if (processNotImplementedMethod(TLValue::UsersGetUsers)) {
        return;
    }
    TLVector<TLUser> result;
    sendRpcReply(result);
}
// End of generated run methods

void UsersRpcOperation::setRunMethod(UsersRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

UsersRpcOperation::ProcessingMethod UsersRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::UsersGetFullUser:
        return &UsersRpcOperation::processGetFullUser;
    case TLValue::UsersGetUsers:
        return &UsersRpcOperation::processGetUsers;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *UsersOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<UsersRpcOperation>(layer, context);
}

} // Server

} // Telegram
