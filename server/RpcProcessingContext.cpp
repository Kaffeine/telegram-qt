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

namespace Telegram {

namespace Server {

RpcProcessingContext::RpcProcessingContext(MTProto::Stream &stream, quint64 requestId) :
    m_inputStream(stream),
    m_id(requestId)
{
}

void RpcProcessingContext::setReadCode(const TLValue code)
{
    m_code = code;
}

} // Server namespace

} // Telegram namespace
