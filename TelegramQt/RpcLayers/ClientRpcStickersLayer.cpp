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

#include "ClientRpcStickersLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcStickersCategory, "telegram.client.rpclayer.stickers", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
// End of generated Telegram API reply template specializations

StickersRpcLayer::StickersRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *StickersRpcLayer::addStickerToSet(const TLInputStickerSet &stickerset, const TLInputStickerSetItem &sticker)
{
    qCDebug(c_clientRpcStickersCategory) << Q_FUNC_INFO << stickerset << sticker;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::StickersAddStickerToSet;
    outputStream << stickerset;
    outputStream << sticker;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *StickersRpcLayer::changeStickerPosition(const TLInputDocument &sticker, quint32 position)
{
    qCDebug(c_clientRpcStickersCategory) << Q_FUNC_INFO << sticker << position;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::StickersChangeStickerPosition;
    outputStream << sticker;
    outputStream << position;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *StickersRpcLayer::createStickerSet(quint32 flags, const TLInputUser &userId, const QString &title, const QString &shortName, const TLVector<TLInputStickerSetItem> &stickers)
{
    qCDebug(c_clientRpcStickersCategory) << Q_FUNC_INFO << flags << userId << title << shortName << stickers;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::StickersCreateStickerSet;
    outputStream << flags;
    // (flags & 1 << 0) stands for masks "true" value
    outputStream << userId;
    outputStream << title;
    outputStream << shortName;
    outputStream << stickers;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *StickersRpcLayer::removeStickerFromSet(const TLInputDocument &sticker)
{
    qCDebug(c_clientRpcStickersCategory) << Q_FUNC_INFO << sticker;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::StickersRemoveStickerFromSet;
    outputStream << sticker;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
