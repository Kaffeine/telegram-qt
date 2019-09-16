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

#include "PhoneOperationFactory.hpp"

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
bool PhoneRpcOperation::processAcceptCall(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runAcceptCall);
    context.inputStream() >> m_acceptCall;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processConfirmCall(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runConfirmCall);
    context.inputStream() >> m_confirmCall;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processDiscardCall(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runDiscardCall);
    context.inputStream() >> m_discardCall;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processGetCallConfig(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runGetCallConfig);
    context.inputStream() >> m_getCallConfig;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processReceivedCall(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runReceivedCall);
    context.inputStream() >> m_receivedCall;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processRequestCall(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runRequestCall);
    context.inputStream() >> m_requestCall;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processSaveCallDebug(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runSaveCallDebug);
    context.inputStream() >> m_saveCallDebug;
    return !context.inputStream().error();
}

bool PhoneRpcOperation::processSetCallRating(RpcProcessingContext &context)
{
    setRunMethod(&PhoneRpcOperation::runSetCallRating);
    context.inputStream() >> m_setCallRating;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void PhoneRpcOperation::runAcceptCall()
{
    // MTProto::Functions::TLPhoneAcceptCall &arguments = m_acceptCall;
    if (processNotImplementedMethod(TLValue::PhoneAcceptCall)) {
        return;
    }
    TLPhonePhoneCall result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runConfirmCall()
{
    // MTProto::Functions::TLPhoneConfirmCall &arguments = m_confirmCall;
    if (processNotImplementedMethod(TLValue::PhoneConfirmCall)) {
        return;
    }
    TLPhonePhoneCall result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runDiscardCall()
{
    // MTProto::Functions::TLPhoneDiscardCall &arguments = m_discardCall;
    if (processNotImplementedMethod(TLValue::PhoneDiscardCall)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runGetCallConfig()
{
    if (processNotImplementedMethod(TLValue::PhoneGetCallConfig)) {
        return;
    }
    TLDataJSON result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runReceivedCall()
{
    // MTProto::Functions::TLPhoneReceivedCall &arguments = m_receivedCall;
    if (processNotImplementedMethod(TLValue::PhoneReceivedCall)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runRequestCall()
{
    // MTProto::Functions::TLPhoneRequestCall &arguments = m_requestCall;
    if (processNotImplementedMethod(TLValue::PhoneRequestCall)) {
        return;
    }
    TLPhonePhoneCall result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runSaveCallDebug()
{
    // MTProto::Functions::TLPhoneSaveCallDebug &arguments = m_saveCallDebug;
    if (processNotImplementedMethod(TLValue::PhoneSaveCallDebug)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void PhoneRpcOperation::runSetCallRating()
{
    // MTProto::Functions::TLPhoneSetCallRating &arguments = m_setCallRating;
    if (processNotImplementedMethod(TLValue::PhoneSetCallRating)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}
// End of generated run methods

void PhoneRpcOperation::setRunMethod(PhoneRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

PhoneRpcOperation::ProcessingMethod PhoneRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::PhoneAcceptCall:
        return &PhoneRpcOperation::processAcceptCall;
    case TLValue::PhoneConfirmCall:
        return &PhoneRpcOperation::processConfirmCall;
    case TLValue::PhoneDiscardCall:
        return &PhoneRpcOperation::processDiscardCall;
    case TLValue::PhoneGetCallConfig:
        return &PhoneRpcOperation::processGetCallConfig;
    case TLValue::PhoneReceivedCall:
        return &PhoneRpcOperation::processReceivedCall;
    case TLValue::PhoneRequestCall:
        return &PhoneRpcOperation::processRequestCall;
    case TLValue::PhoneSaveCallDebug:
        return &PhoneRpcOperation::processSaveCallDebug;
    case TLValue::PhoneSetCallRating:
        return &PhoneRpcOperation::processSetCallRating;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *PhoneOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<PhoneRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
