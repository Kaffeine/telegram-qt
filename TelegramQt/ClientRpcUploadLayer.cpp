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

#include "ClientRpcUploadLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcUploadCategory, "telegram.client.rpclayer.upload", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUploadFile *output);
// End of generated Telegram API reply template specializations

UploadRpcLayer::UploadRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *UploadRpcLayer::getFile(const TLInputFileLocation &location, quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << location << offset << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::UploadGetFile;
    outputStream << location;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *UploadRpcLayer::saveBigFilePart(quint64 fileId, quint32 filePart, quint32 fileTotalParts, const QByteArray &bytes)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileId << filePart << fileTotalParts << bytes.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::UploadSaveBigFilePart;
    outputStream << fileId;
    outputStream << filePart;
    outputStream << fileTotalParts;
    outputStream << bytes;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *UploadRpcLayer::saveFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileId << filePart << bytes.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::UploadSaveFilePart;
    outputStream << fileId;
    outputStream << filePart;
    outputStream << bytes;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
