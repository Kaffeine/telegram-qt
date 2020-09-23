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

#ifndef TELEGRAM_CLIENT_BASE_RPC_LAYER_EXTENSION_PRIVATE_HPP
#define TELEGRAM_CLIENT_BASE_RPC_LAYER_EXTENSION_PRIVATE_HPP

#include "ClientRpcLayerExtension.hpp"

#include "MTProto/Stream.hpp"
#include "PendingOperation.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#ifndef DUMP_CLIENT_RPC_PACKETS
#define DUMP_CLIENT_RPC_PACKETS
#endif

#ifdef DUMP_CLIENT_RPC_PACKETS
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(c_clientRpcDumpPackageCategory)
#endif

namespace Telegram {

namespace Client {

template <typename TLType>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLType *output)
{
    MTProto::Stream stream;
    prepareReplyStream(&stream, operation);
    stream >> *output;
#ifdef DEVELOPER_BUILD
    qCDebug(c_clientRpcDumpPackageCategory) << *output;
#else
    qCDebug(c_clientRpcDumpPackageCategory) << Q_FUNC_INFO << output->tlType;
#endif
    return output->isValid() && !stream.error();
}

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_BASE_RPC_LAYER_EXTENSION_PRIVATE_HPP

