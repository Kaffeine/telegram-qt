/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "RpcProcessingContext.hpp"

#include "MTProto/Stream.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLRpcDebug.hpp"
#endif

namespace Telegram {

namespace Server {

RpcProcessingContext::RpcProcessingContext(MTProto::Stream &stream, quint64 messageId) :
    m_inputStream(stream),
    m_messageId(messageId)
{
#ifdef DEVELOPER_BUILD
    MTProto::Stream debugStream(stream.getData());
    MTProto::dumpRpc(debugStream);
#endif
}

void RpcProcessingContext::setReadCode(const TLValue code)
{
    m_code = code;
}

} // Server namespace

} // Telegram namespace
