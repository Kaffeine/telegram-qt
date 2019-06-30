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

#ifndef TELEGRAM_SERVER_RPC_PROCESSING_CONTEXT_HPP
#define TELEGRAM_SERVER_RPC_PROCESSING_CONTEXT_HPP

#include <QtGlobal>

#include "MTProto/TLValues.hpp"

class CTelegramStream;

namespace Telegram {

namespace MTProto {

using Stream = ::CTelegramStream;

} // MTProto namespace

namespace Server {

class RpcProcessingContext
{
public:
    RpcProcessingContext(MTProto::Stream &inputStream, quint64 requestId);

    MTProto::Stream &inputStream() { return m_inputStream; }

    quint64 requestId() const { return m_id; }

    TLValue readCode() const { return m_code; }
    void setReadCode(const TLValue code);

protected:
    MTProto::Stream &m_inputStream;
    quint64 m_id;
    TLValue m_code;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_RPC_PROCESSING_CONTEXT_HPP
