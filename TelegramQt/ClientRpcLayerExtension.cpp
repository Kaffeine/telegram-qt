/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "ClientRpcLayerExtension.hpp"
#include "CTelegramStream.hpp"
#include "PendingOperation.hpp"

namespace Telegram {

namespace Client {

BaseRpcLayerExtension::BaseRpcLayerExtension(QObject *parent) :
    QObject(parent)
{
}

void BaseRpcLayerExtension::prepareReplyStream(TelegramStream *stream, PendingRpcOperation *operation)
{
    // TODO: Implement static isValid(TLValue::Value) method for TLTypes and
    // add a generated check that TLType is valid type for the RPC request.
    // Probably it would be better to hide this method from subclasses by adding a processReply()
    // reimpl with type-specific code (check for TLType::isValid() and call this method)

    const QByteArray data = operation->replyData();
#ifdef DUMP_CLIENT_RPC_PACKETS
    qDebug() << "BaseRpcLayerExtension: Process answer for message" << operation->requestId();
    qDebug().noquote() << "BaseRpcLayerExtension: RPC Reply bytes:" << data.size() << data.toHex();
#endif
    stream->setData(data);
}

PendingRpcOperation *BaseRpcLayerExtension::sendEncryptedPackage(const QByteArray &payload)
{
    return m_sendMethod(payload);
}

} // Client namespace

} // Telegram namespace
