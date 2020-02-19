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

#include "LangpackOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "LocalServerApi.hpp"
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
bool LangpackRpcOperation::processGetDifference(RpcProcessingContext &context)
{
    setRunMethod(&LangpackRpcOperation::runGetDifference);
    context.inputStream() >> m_getDifference;
    return !context.inputStream().error();
}

bool LangpackRpcOperation::processGetLangPack(RpcProcessingContext &context)
{
    setRunMethod(&LangpackRpcOperation::runGetLangPack);
    context.inputStream() >> m_getLangPack;
    return !context.inputStream().error();
}

bool LangpackRpcOperation::processGetLanguage(RpcProcessingContext &context)
{
    setRunMethod(&LangpackRpcOperation::runGetLanguage);
    context.inputStream() >> m_getLanguage;
    return !context.inputStream().error();
}

bool LangpackRpcOperation::processGetLanguages(RpcProcessingContext &context)
{
    setRunMethod(&LangpackRpcOperation::runGetLanguages);
    context.inputStream() >> m_getLanguages;
    return !context.inputStream().error();
}

bool LangpackRpcOperation::processGetStrings(RpcProcessingContext &context)
{
    setRunMethod(&LangpackRpcOperation::runGetStrings);
    context.inputStream() >> m_getStrings;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void LangpackRpcOperation::runGetDifference()
{
    // MTProto::Functions::TLLangpackGetDifference &arguments = m_getDifference;
    if (processNotImplementedMethod(TLValue::LangpackGetDifference)) {
        return;
    }
    TLLangPackDifference result;
    sendRpcReply(result);
}

void LangpackRpcOperation::runGetLangPack()
{
    // MTProto::Functions::TLLangpackGetLangPack &arguments = m_getLangPack;
    if (processNotImplementedMethod(TLValue::LangpackGetLangPack)) {
        return;
    }
    TLLangPackDifference result;
    sendRpcReply(result);
}

void LangpackRpcOperation::runGetLanguage()
{
    // MTProto::Functions::TLLangpackGetLanguage &arguments = m_getLanguage;
    if (processNotImplementedMethod(TLValue::LangpackGetLanguage)) {
        return;
    }
    TLLangPackLanguage result;
    sendRpcReply(result);
}

void LangpackRpcOperation::runGetLanguages()
{
    if (processNotImplementedMethod(TLValue::LangpackGetLanguages)) {
        return;
    }
    TLVector<TLLangPackLanguage> result;
    sendRpcReply(result);
}

void LangpackRpcOperation::runGetStrings()
{
    // MTProto::Functions::TLLangpackGetStrings &arguments = m_getStrings;
    if (processNotImplementedMethod(TLValue::LangpackGetStrings)) {
        return;
    }
    TLVector<TLLangPackString> result;
    sendRpcReply(result);
}
// End of generated run methods

void LangpackRpcOperation::setRunMethod(LangpackRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

LangpackRpcOperation::ProcessingMethod LangpackRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::LangpackGetDifference:
        return &LangpackRpcOperation::processGetDifference;
    case TLValue::LangpackGetLangPack:
        return &LangpackRpcOperation::processGetLangPack;
    case TLValue::LangpackGetLanguage:
        return &LangpackRpcOperation::processGetLanguage;
    case TLValue::LangpackGetLanguages:
        return &LangpackRpcOperation::processGetLanguages;
    case TLValue::LangpackGetStrings:
        return &LangpackRpcOperation::processGetStrings;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *LangpackOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<LangpackRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
