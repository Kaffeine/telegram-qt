/*
   Copyright (C) 2018 

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

#include "BotsOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
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
bool BotsRpcOperation::processAnswerWebhookJSONQuery(RpcProcessingContext &context)
{
    setRunMethod(&BotsRpcOperation::runAnswerWebhookJSONQuery);
    context.inputStream() >> m_answerWebhookJSONQuery;
    return !context.inputStream().error();
}

bool BotsRpcOperation::processSendCustomRequest(RpcProcessingContext &context)
{
    setRunMethod(&BotsRpcOperation::runSendCustomRequest);
    context.inputStream() >> m_sendCustomRequest;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void BotsRpcOperation::runAnswerWebhookJSONQuery()
{
    // MTProto::Functions::TLBotsAnswerWebhookJSONQuery &arguments = m_answerWebhookJSONQuery;
    if (processNotImplementedMethod(TLValue::BotsAnswerWebhookJSONQuery)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void BotsRpcOperation::runSendCustomRequest()
{
    // MTProto::Functions::TLBotsSendCustomRequest &arguments = m_sendCustomRequest;
    if (processNotImplementedMethod(TLValue::BotsSendCustomRequest)) {
        return;
    }
    TLDataJSON result;
    sendRpcReply(result);
}
// End of generated run methods

void BotsRpcOperation::setRunMethod(BotsRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

BotsRpcOperation::ProcessingMethod BotsRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::BotsAnswerWebhookJSONQuery:
        return &BotsRpcOperation::processAnswerWebhookJSONQuery;
    case TLValue::BotsSendCustomRequest:
        return &BotsRpcOperation::processSendCustomRequest;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *BotsOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<BotsRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
