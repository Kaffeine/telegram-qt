/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "CTelegramStream.hpp"

RpcProcessingContext::RpcProcessingContext(CTelegramStream &stream, quint64 requestId, const QByteArray &requestData) :
    m_inputStream(stream),
    m_id(requestId),
    m_requestData(requestData),
    m_succeed(false)
{
    if (hasRequestData()) {
        m_requestMethodId = TLValue::firstFromArray(requestData);
    }
}

bool RpcProcessingContext::hasRequestData() const
{
    return !m_requestData.isEmpty();
}

TLValue RpcProcessingContext::requestType() const
{
    return m_requestMethodId;
}

void RpcProcessingContext::setSucceed(bool succeed)
{
    m_succeed = succeed;
}

void RpcProcessingContext::setReadCode(const TLValue code)
{
    m_code = code;
}

QString RpcProcessingContext::userNameFromRequest() const
{
    if (!hasRequestData()) {
        return QString();
    }

    CTelegramStream outputStream(requestData());

    TLValue requestType;
    outputStream >> requestType;

    switch (requestType) {
    case TLValue::AccountCheckUsername:
    case TLValue::AccountUpdateUsername:
    case TLValue::ContactsResolveUsername:
        break;
    default:
        return QString();
    }

    QString name;
    outputStream >> name;
    return name;
}
