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
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcLangpackCategory, "telegram.client.rpclayer.langpack", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
// End of generated Telegram API reply template specializations

LangpackRpcLayer::LangpackRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *LangpackRpcLayer::getDifference(quint32 fromVersion)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << fromVersion;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::LangpackGetDifference;
    outputStream << fromVersion;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *LangpackRpcLayer::getLangPack(const QString &langCode)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langCode;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::LangpackGetLangPack;
    outputStream << langCode;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *LangpackRpcLayer::getLanguages()
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::LangpackGetLanguages;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *LangpackRpcLayer::getStrings(const QString &langCode, const TLVector<QString> &keys)
{
    qCDebug(c_clientRpcLangpackCategory) << Q_FUNC_INFO << langCode << keys;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::LangpackGetStrings;
    outputStream << langCode;
    outputStream << keys;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
