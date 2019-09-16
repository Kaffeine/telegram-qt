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

#ifndef UPDATES_OPERATION_FACTORY_HPP
#define UPDATES_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class UpdatesRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(UpdatesRpcOperation)
public:
    explicit UpdatesRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processGetChannelDifference(RpcProcessingContext &context);
    bool processGetDifference(RpcProcessingContext &context);
    bool processGetState(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runGetChannelDifference();
    void runGetDifference();
    void runGetState();
    // End of generated run methods

    using RunMethod = void (UpdatesRpcOperation::*)();
    using ProcessingMethod = bool (UpdatesRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLUpdatesGetChannelDifference m_getChannelDifference;
    MTProto::Functions::TLUpdatesGetDifference m_getDifference;
    MTProto::Functions::TLUpdatesGetState m_getState;
    // End of generated RPC members
};

class UpdatesOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // UPDATES_OPERATION_FACTORY_HPP
