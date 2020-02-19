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

#ifndef TELEGRAM_CLIENT_RPC_LANGPACK_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_LANGPACK_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class LangpackRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit LangpackRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingLangPackDifference = PendingRpcResult<TLLangPackDifference *>;
    using PendingLangPackLanguage = PendingRpcResult<TLLangPackLanguage *>;
    using PendingLangPackLanguageVector = PendingRpcResult<TLVector<TLLangPackLanguage> *>;
    using PendingLangPackStringVector = PendingRpcResult<TLVector<TLLangPackString> *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingLangPackDifference *getDifference(const QString &langCode, quint32 fromVersion);
    PendingLangPackDifference *getLangPack(const QString &langPack, const QString &langCode);
    PendingLangPackLanguage *getLanguage(const QString &langPack, const QString &langCode);
    PendingLangPackLanguageVector *getLanguages(const QString &langPack);
    PendingLangPackStringVector *getStrings(const QString &langPack, const QString &langCode, const TLVector<QString> &keys);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_LANGPACK_LAYER_HPP
