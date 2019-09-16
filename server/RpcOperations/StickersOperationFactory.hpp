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

#ifndef STICKERS_OPERATION_FACTORY_HPP
#define STICKERS_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class StickersRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(StickersRpcOperation)
public:
    explicit StickersRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processAddStickerToSet(RpcProcessingContext &context);
    bool processChangeStickerPosition(RpcProcessingContext &context);
    bool processCreateStickerSet(RpcProcessingContext &context);
    bool processRemoveStickerFromSet(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAddStickerToSet();
    void runChangeStickerPosition();
    void runCreateStickerSet();
    void runRemoveStickerFromSet();
    // End of generated run methods

    using RunMethod = void (StickersRpcOperation::*)();
    using ProcessingMethod = bool (StickersRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLStickersAddStickerToSet m_addStickerToSet;
    MTProto::Functions::TLStickersChangeStickerPosition m_changeStickerPosition;
    MTProto::Functions::TLStickersCreateStickerSet m_createStickerSet;
    MTProto::Functions::TLStickersRemoveStickerFromSet m_removeStickerFromSet;
    // End of generated RPC members
};

class StickersOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // STICKERS_OPERATION_FACTORY_HPP
