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

#ifndef RPC_PROCESSING_CONTEXT_HPP
#define RPC_PROCESSING_CONTEXT_HPP

#include <QtGlobal>

#include "TLValues.hpp"

class CTelegramStream;
//#include "CTelegramStream.hpp"

class RpcProcessingContext
{
public:
    RpcProcessingContext(CTelegramStream &inputStream, quint64 requestId = 0, const QByteArray &requestData = QByteArray());

    CTelegramStream &inputStream() { return m_inputStream; }

    quint64 requestId() const { return m_id; }
    bool hasRequestData() const;
    QByteArray requestData() const { return m_requestData; }
    TLValue requestType() const;

    bool isSucceed() const { return m_succeed; }
    void setSucceed(bool isSucceed);

    TLValue readCode() const { return m_code; }
    void setReadCode(const TLValue code);

//    template <typename T>
//    bool readRpcResult(T *result);

    // Extra API
    QString userNameFromRequest() const;

protected:
    CTelegramStream &m_inputStream;
    quint64 m_id;
    QByteArray m_requestData;
    bool m_succeed;
    TLValue m_code;
    TLValue m_requestMethodId;
};

//template<typename T>
//inline bool RpcProcessingContext::readRpcResult(T *result)
//{
//    inputStream() >> *result;
//    m_code = result->tlType;
//    m_succeed = result->isValid() && !inputStream().error();
//    return m_succeed;
//}


#endif // RPC_PROCESSING_CONTEXT_HPP
