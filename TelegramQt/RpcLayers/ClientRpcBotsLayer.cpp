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

#include "ClientRpcBotsLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcBotsCategory, "telegram.client.rpclayer.bots", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
// End of generated Telegram API reply template specializations

BotsRpcLayer::BotsRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *BotsRpcLayer::answerWebhookJSONQuery(quint64 queryId, const TLDataJSON &data)
{
    qCDebug(c_clientRpcBotsCategory) << Q_FUNC_INFO << queryId << data;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::BotsAnswerWebhookJSONQuery;
    outputStream << queryId;
    outputStream << data;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *BotsRpcLayer::sendCustomRequest(const QString &customMethod, const TLDataJSON &params)
{
    qCDebug(c_clientRpcBotsCategory) << Q_FUNC_INFO << customMethod << params;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::BotsSendCustomRequest;
    outputStream << customMethod;
    outputStream << params;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
