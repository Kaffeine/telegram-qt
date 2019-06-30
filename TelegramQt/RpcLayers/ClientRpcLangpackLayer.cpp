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

#include "ClientRpcLangpackLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcLangpackCategory, "telegram.client.rpclayer.langpack", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
// End of generated Telegram API reply template specializations

LangpackRpcLayer::LangpackRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
LangpackRpcLayer::PendingLangPackDifference *LangpackRpcLayer::getDifference(quint32 fromVersion)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << fromVersion;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetDifference;
    outputStream << fromVersion;
    PendingLangPackDifference *op = new PendingLangPackDifference(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackDifference *LangpackRpcLayer::getLangPack(const QString &langCode)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langCode;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetLangPack;
    outputStream << langCode;
    PendingLangPackDifference *op = new PendingLangPackDifference(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackLanguageVector *LangpackRpcLayer::getLanguages()
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetLanguages;
    PendingLangPackLanguageVector *op = new PendingLangPackLanguageVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackStringVector *LangpackRpcLayer::getStrings(const QString &langCode, const TLVector<QString> &keys)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langCode << keys;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetStrings;
    outputStream << langCode;
    outputStream << keys;
    PendingLangPackStringVector *op = new PendingLangPackStringVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
