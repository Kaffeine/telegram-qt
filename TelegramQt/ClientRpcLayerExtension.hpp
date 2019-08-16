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

#ifndef TELEGRAM_CLIENT_BASE_RPC_LAYER_EXTENSION_HPP
#define TELEGRAM_CLIENT_BASE_RPC_LAYER_EXTENSION_HPP

#include <QObject>
#include <QHash>

#include <functional>

class CTelegramStream;

namespace Telegram {

namespace MTProto {

class Stream;

} // MTProto namespace

namespace Client {

class PendingRpcOperation;

class BaseRpcLayerExtension : public QObject
{
    Q_OBJECT
public:
    explicit BaseRpcLayerExtension(QObject *parent = nullptr);

    using RpcProcessingMethod = std::function<void (PendingRpcOperation *)>;

    RpcProcessingMethod rpcProcessingMethod() const { return m_processingMethod; }
    void setRpcProcessingMethod(RpcProcessingMethod sendMethod);

    template <typename TLType>
    bool processReply(PendingRpcOperation *operation, TLType *output);

    void prepareReplyStream(MTProto::Stream *stream, PendingRpcOperation *operation);

protected:
    void processRpcCall(PendingRpcOperation *operation);
    RpcProcessingMethod m_processingMethod = nullptr;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_BASE_RPC_LAYER_EXTENSION_HPP

