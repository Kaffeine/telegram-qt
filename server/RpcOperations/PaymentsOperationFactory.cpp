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

#include "PaymentsOperationFactory.hpp"

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
bool PaymentsRpcOperation::processClearSavedInfo(RpcProcessingContext &context)
{
    setRunMethod(&PaymentsRpcOperation::runClearSavedInfo);
    context.inputStream() >> m_clearSavedInfo;
    return !context.inputStream().error();
}

bool PaymentsRpcOperation::processGetPaymentForm(RpcProcessingContext &context)
{
    setRunMethod(&PaymentsRpcOperation::runGetPaymentForm);
    context.inputStream() >> m_getPaymentForm;
    return !context.inputStream().error();
}

bool PaymentsRpcOperation::processGetPaymentReceipt(RpcProcessingContext &context)
{
    setRunMethod(&PaymentsRpcOperation::runGetPaymentReceipt);
    context.inputStream() >> m_getPaymentReceipt;
    return !context.inputStream().error();
}

bool PaymentsRpcOperation::processGetSavedInfo(RpcProcessingContext &context)
{
    setRunMethod(&PaymentsRpcOperation::runGetSavedInfo);
    context.inputStream() >> m_getSavedInfo;
    return !context.inputStream().error();
}

bool PaymentsRpcOperation::processSendPaymentForm(RpcProcessingContext &context)
{
    setRunMethod(&PaymentsRpcOperation::runSendPaymentForm);
    context.inputStream() >> m_sendPaymentForm;
    return !context.inputStream().error();
}

bool PaymentsRpcOperation::processValidateRequestedInfo(RpcProcessingContext &context)
{
    setRunMethod(&PaymentsRpcOperation::runValidateRequestedInfo);
    context.inputStream() >> m_validateRequestedInfo;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void PaymentsRpcOperation::runClearSavedInfo()
{
    // MTProto::Functions::TLPaymentsClearSavedInfo &arguments = m_clearSavedInfo;
    if (processNotImplementedMethod(TLValue::PaymentsClearSavedInfo)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void PaymentsRpcOperation::runGetPaymentForm()
{
    // MTProto::Functions::TLPaymentsGetPaymentForm &arguments = m_getPaymentForm;
    if (processNotImplementedMethod(TLValue::PaymentsGetPaymentForm)) {
        return;
    }
    TLPaymentsPaymentForm result;
    sendRpcReply(result);
}

void PaymentsRpcOperation::runGetPaymentReceipt()
{
    // MTProto::Functions::TLPaymentsGetPaymentReceipt &arguments = m_getPaymentReceipt;
    if (processNotImplementedMethod(TLValue::PaymentsGetPaymentReceipt)) {
        return;
    }
    TLPaymentsPaymentReceipt result;
    sendRpcReply(result);
}

void PaymentsRpcOperation::runGetSavedInfo()
{
    if (processNotImplementedMethod(TLValue::PaymentsGetSavedInfo)) {
        return;
    }
    TLPaymentsSavedInfo result;
    sendRpcReply(result);
}

void PaymentsRpcOperation::runSendPaymentForm()
{
    // MTProto::Functions::TLPaymentsSendPaymentForm &arguments = m_sendPaymentForm;
    if (processNotImplementedMethod(TLValue::PaymentsSendPaymentForm)) {
        return;
    }
    TLPaymentsPaymentResult result;
    sendRpcReply(result);
}

void PaymentsRpcOperation::runValidateRequestedInfo()
{
    // MTProto::Functions::TLPaymentsValidateRequestedInfo &arguments = m_validateRequestedInfo;
    if (processNotImplementedMethod(TLValue::PaymentsValidateRequestedInfo)) {
        return;
    }
    TLPaymentsValidatedRequestedInfo result;
    sendRpcReply(result);
}
// End of generated run methods

void PaymentsRpcOperation::setRunMethod(PaymentsRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

PaymentsRpcOperation::ProcessingMethod PaymentsRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::PaymentsClearSavedInfo:
        return &PaymentsRpcOperation::processClearSavedInfo;
    case TLValue::PaymentsGetPaymentForm:
        return &PaymentsRpcOperation::processGetPaymentForm;
    case TLValue::PaymentsGetPaymentReceipt:
        return &PaymentsRpcOperation::processGetPaymentReceipt;
    case TLValue::PaymentsGetSavedInfo:
        return &PaymentsRpcOperation::processGetSavedInfo;
    case TLValue::PaymentsSendPaymentForm:
        return &PaymentsRpcOperation::processSendPaymentForm;
    case TLValue::PaymentsValidateRequestedInfo:
        return &PaymentsRpcOperation::processValidateRequestedInfo;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *PaymentsOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<PaymentsRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
