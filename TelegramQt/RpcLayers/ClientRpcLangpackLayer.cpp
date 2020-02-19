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
LangpackRpcLayer::PendingLangPackDifference *LangpackRpcLayer::getDifference(const QString &langCode, quint32 fromVersion)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langCode << fromVersion;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetDifference;
    outputStream << langCode;
    outputStream << fromVersion;
    PendingLangPackDifference *op = new PendingLangPackDifference(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackDifference *LangpackRpcLayer::getLangPack(const QString &langPack, const QString &langCode)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langPack << langCode;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetLangPack;
    outputStream << langPack;
    outputStream << langCode;
    PendingLangPackDifference *op = new PendingLangPackDifference(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackLanguage *LangpackRpcLayer::getLanguage(const QString &langPack, const QString &langCode)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langPack << langCode;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetLanguage;
    outputStream << langPack;
    outputStream << langCode;
    PendingLangPackLanguage *op = new PendingLangPackLanguage(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackLanguageVector *LangpackRpcLayer::getLanguages(const QString &langPack)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langPack;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetLanguages;
    outputStream << langPack;
    PendingLangPackLanguageVector *op = new PendingLangPackLanguageVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

LangpackRpcLayer::PendingLangPackStringVector *LangpackRpcLayer::getStrings(const QString &langPack, const QString &langCode, const TLVector<QString> &keys)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langPack << langCode << keys;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::LangpackGetStrings;
    outputStream << langPack;
    outputStream << langCode;
    outputStream << keys;
    PendingLangPackStringVector *op = new PendingLangPackStringVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
