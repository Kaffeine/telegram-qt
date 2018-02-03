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

#ifndef PAYMENTS_OPERATION_FACTORY_HPP
#define PAYMENTS_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class PaymentsRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(PaymentsRpcOperation)
public:
    explicit PaymentsRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processClearSavedInfo(RpcProcessingContext &context);
    bool processGetPaymentForm(RpcProcessingContext &context);
    bool processGetPaymentReceipt(RpcProcessingContext &context);
    bool processGetSavedInfo(RpcProcessingContext &context);
    bool processSendPaymentForm(RpcProcessingContext &context);
    bool processValidateRequestedInfo(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runClearSavedInfo();
    void runGetPaymentForm();
    void runGetPaymentReceipt();
    void runGetSavedInfo();
    void runSendPaymentForm();
    void runValidateRequestedInfo();
    // End of generated run methods

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (PaymentsRpcOperation::*)();
    using ProcessingMethod = bool (PaymentsRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLPaymentsClearSavedInfo m_clearSavedInfo;
    TLFunctions::TLPaymentsGetPaymentForm m_getPaymentForm;
    TLFunctions::TLPaymentsGetPaymentReceipt m_getPaymentReceipt;
    TLFunctions::TLPaymentsGetSavedInfo m_getSavedInfo;
    TLFunctions::TLPaymentsSendPaymentForm m_sendPaymentForm;
    TLFunctions::TLPaymentsValidateRequestedInfo m_validateRequestedInfo;
    // End of generated RPC members
};

class PaymentsOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // PAYMENTS_OPERATION_FACTORY_HPP
