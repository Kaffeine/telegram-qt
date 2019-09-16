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

#include "StickersOperationFactory.hpp"

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
bool StickersRpcOperation::processAddStickerToSet(RpcProcessingContext &context)
{
    setRunMethod(&StickersRpcOperation::runAddStickerToSet);
    context.inputStream() >> m_addStickerToSet;
    return !context.inputStream().error();
}

bool StickersRpcOperation::processChangeStickerPosition(RpcProcessingContext &context)
{
    setRunMethod(&StickersRpcOperation::runChangeStickerPosition);
    context.inputStream() >> m_changeStickerPosition;
    return !context.inputStream().error();
}

bool StickersRpcOperation::processCreateStickerSet(RpcProcessingContext &context)
{
    setRunMethod(&StickersRpcOperation::runCreateStickerSet);
    context.inputStream() >> m_createStickerSet;
    return !context.inputStream().error();
}

bool StickersRpcOperation::processRemoveStickerFromSet(RpcProcessingContext &context)
{
    setRunMethod(&StickersRpcOperation::runRemoveStickerFromSet);
    context.inputStream() >> m_removeStickerFromSet;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void StickersRpcOperation::runAddStickerToSet()
{
    // MTProto::Functions::TLStickersAddStickerToSet &arguments = m_addStickerToSet;
    if (processNotImplementedMethod(TLValue::StickersAddStickerToSet)) {
        return;
    }
    TLMessagesStickerSet result;
    sendRpcReply(result);
}

void StickersRpcOperation::runChangeStickerPosition()
{
    // MTProto::Functions::TLStickersChangeStickerPosition &arguments = m_changeStickerPosition;
    if (processNotImplementedMethod(TLValue::StickersChangeStickerPosition)) {
        return;
    }
    TLMessagesStickerSet result;
    sendRpcReply(result);
}

void StickersRpcOperation::runCreateStickerSet()
{
    // MTProto::Functions::TLStickersCreateStickerSet &arguments = m_createStickerSet;
    if (processNotImplementedMethod(TLValue::StickersCreateStickerSet)) {
        return;
    }
    TLMessagesStickerSet result;
    sendRpcReply(result);
}

void StickersRpcOperation::runRemoveStickerFromSet()
{
    // MTProto::Functions::TLStickersRemoveStickerFromSet &arguments = m_removeStickerFromSet;
    if (processNotImplementedMethod(TLValue::StickersRemoveStickerFromSet)) {
        return;
    }
    TLMessagesStickerSet result;
    sendRpcReply(result);
}
// End of generated run methods

void StickersRpcOperation::setRunMethod(StickersRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

StickersRpcOperation::ProcessingMethod StickersRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::StickersAddStickerToSet:
        return &StickersRpcOperation::processAddStickerToSet;
    case TLValue::StickersChangeStickerPosition:
        return &StickersRpcOperation::processChangeStickerPosition;
    case TLValue::StickersCreateStickerSet:
        return &StickersRpcOperation::processCreateStickerSet;
    case TLValue::StickersRemoveStickerFromSet:
        return &StickersRpcOperation::processRemoveStickerFromSet;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *StickersOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<StickersRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
