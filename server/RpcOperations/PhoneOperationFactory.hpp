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

#ifndef PHONE_OPERATION_FACTORY_HPP
#define PHONE_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class PhoneRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneRpcOperation)
public:
    explicit PhoneRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processAcceptCall(RpcProcessingContext &context);
    bool processConfirmCall(RpcProcessingContext &context);
    bool processDiscardCall(RpcProcessingContext &context);
    bool processGetCallConfig(RpcProcessingContext &context);
    bool processReceivedCall(RpcProcessingContext &context);
    bool processRequestCall(RpcProcessingContext &context);
    bool processSaveCallDebug(RpcProcessingContext &context);
    bool processSetCallRating(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAcceptCall();
    void runConfirmCall();
    void runDiscardCall();
    void runGetCallConfig();
    void runReceivedCall();
    void runRequestCall();
    void runSaveCallDebug();
    void runSetCallRating();
    // End of generated run methods

    using RunMethod = void (PhoneRpcOperation::*)();
    using ProcessingMethod = bool (PhoneRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLPhoneAcceptCall m_acceptCall;
    MTProto::Functions::TLPhoneConfirmCall m_confirmCall;
    MTProto::Functions::TLPhoneDiscardCall m_discardCall;
    MTProto::Functions::TLPhoneGetCallConfig m_getCallConfig;
    MTProto::Functions::TLPhoneReceivedCall m_receivedCall;
    MTProto::Functions::TLPhoneRequestCall m_requestCall;
    MTProto::Functions::TLPhoneSaveCallDebug m_saveCallDebug;
    MTProto::Functions::TLPhoneSetCallRating m_setCallRating;
    // End of generated RPC members
};

class PhoneOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // PHONE_OPERATION_FACTORY_HPP
