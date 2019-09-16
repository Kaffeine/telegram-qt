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

#include "UpdatesOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "ServerUtils.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool UpdatesRpcOperation::processGetChannelDifference(RpcProcessingContext &context)
{
    setRunMethod(&UpdatesRpcOperation::runGetChannelDifference);
    context.inputStream() >> m_getChannelDifference;
    return !context.inputStream().error();
}

bool UpdatesRpcOperation::processGetDifference(RpcProcessingContext &context)
{
    setRunMethod(&UpdatesRpcOperation::runGetDifference);
    context.inputStream() >> m_getDifference;
    return !context.inputStream().error();
}

bool UpdatesRpcOperation::processGetState(RpcProcessingContext &context)
{
    setRunMethod(&UpdatesRpcOperation::runGetState);
    context.inputStream() >> m_getState;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void UpdatesRpcOperation::runGetChannelDifference()
{
    // MTProto::Functions::TLUpdatesGetChannelDifference &arguments = m_getChannelDifference;
    if (processNotImplementedMethod(TLValue::UpdatesGetChannelDifference)) {
        return;
    }
    TLUpdatesChannelDifference result;
    sendRpcReply(result);
}

void UpdatesRpcOperation::runGetDifference()
{
    // MTProto::Functions::TLUpdatesGetDifference &arguments = m_getDifference;
    if (processNotImplementedMethod(TLValue::UpdatesGetDifference)) {
        return;
    }
    TLUpdatesDifference result;
    sendRpcReply(result);
}

void UpdatesRpcOperation::runGetState()
{
    TLUpdatesState result;
    const LocalUser *selfUser = layer()->getUser();
    Utils::setupTLUpdatesState(&result, selfUser);
    sendRpcReply(result);
}
// End of generated run methods

void UpdatesRpcOperation::setRunMethod(UpdatesRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

UpdatesRpcOperation::ProcessingMethod UpdatesRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::UpdatesGetChannelDifference:
        return &UpdatesRpcOperation::processGetChannelDifference;
    case TLValue::UpdatesGetDifference:
        return &UpdatesRpcOperation::processGetDifference;
    case TLValue::UpdatesGetState:
        return &UpdatesRpcOperation::processGetState;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *UpdatesOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<UpdatesRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
