/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#include "ClientRpcUpdatesLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcUpdatesCategory, "telegram.client.rpclayer.updates", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUpdates *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUpdatesChannelDifference *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUpdatesDifference *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUpdatesState *output);
// End of generated Telegram API reply template specializations

UpdatesRpcLayer::UpdatesRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *UpdatesRpcLayer::getChannelDifference(quint32 flags, const TLInputChannel &channel, const TLChannelMessagesFilter &filter, quint32 pts, quint32 limit)
{
    qCDebug(c_clientRpcUpdatesCategory) << Q_FUNC_INFO << flags << channel << filter << pts << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::UpdatesGetChannelDifference;
    outputStream << flags;
    // (flags & 1 << 0) stands for force "true" value
    outputStream << channel;
    outputStream << filter;
    outputStream << pts;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *UpdatesRpcLayer::getDifference(quint32 flags, quint32 pts, quint32 ptsTotalLimit, quint32 date, quint32 qts)
{
    qCDebug(c_clientRpcUpdatesCategory) << Q_FUNC_INFO << flags << pts << ptsTotalLimit << date << qts;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::UpdatesGetDifference;
    outputStream << flags;
    outputStream << pts;
    if (flags & 1 << 0) {
        outputStream << ptsTotalLimit;
    }
    outputStream << date;
    outputStream << qts;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *UpdatesRpcLayer::getState()
{
    qCDebug(c_clientRpcUpdatesCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::UpdatesGetState;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
