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

#ifndef LANGPACK_OPERATION_FACTORY_HPP
#define LANGPACK_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class LangpackRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(LangpackRpcOperation)
public:
    explicit LangpackRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processGetDifference(RpcProcessingContext &context);
    bool processGetLangPack(RpcProcessingContext &context);
    bool processGetLanguage(RpcProcessingContext &context);
    bool processGetLanguages(RpcProcessingContext &context);
    bool processGetStrings(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runGetDifference();
    void runGetLangPack();
    void runGetLanguage();
    void runGetLanguages();
    void runGetStrings();
    // End of generated run methods

    using RunMethod = void (LangpackRpcOperation::*)();
    using ProcessingMethod = bool (LangpackRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);
    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLLangpackGetDifference m_getDifference;
    MTProto::Functions::TLLangpackGetLangPack m_getLangPack;
    MTProto::Functions::TLLangpackGetLanguage m_getLanguage;
    MTProto::Functions::TLLangpackGetLanguages m_getLanguages;
    MTProto::Functions::TLLangpackGetStrings m_getStrings;
    // End of generated RPC members
};

class LangpackOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
    bool needLocalUser() const override { return false; }
};

} // Server namespace

} // Telegram namespace

#endif // LANGPACK_OPERATION_FACTORY_HPP
