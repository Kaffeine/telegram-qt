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

#include "AccountOperationFactory.hpp"

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

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool AccountRpcOperation::processGetPassword(RpcProcessingContext &context)
{
    Q_UNUSED(context)
    setRunMethod(&AccountRpcOperation::runGetPassword);
    return true;
}
// End of generated process methods

// Generated run methods
void AccountRpcOperation::runGetPassword()
{
    User *user = layer()->getUser();
    PasswordInfo info = api()->getPassword(user->phoneNumber());

    TLAccountPassword result;
    if (info.hasPassword()) {
        result.tlType = TLValue::AccountPassword;
        result.currentSalt = info.currentSalt;
        result.hint = info.hint;
    } else {
        result.tlType = TLValue::AccountNoPassword;
    }
    sendRpcReply(result);
}
// End of generated run methods


void AccountRpcOperation::setRunMethod(AccountRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

AccountRpcOperation::ProcessingMethod AccountRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::AccountGetPassword:
        return &AccountRpcOperation::processGetPassword;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *AccountOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<AccountRpcOperation>(layer, context);
}

} // Server

} // Telegram
