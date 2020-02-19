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
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcUploadCategory, "telegram.client.rpclayer.upload", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUploadCdnFile *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUploadFile *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUploadWebFile *output);
// End of generated Telegram API reply template specializations

UploadRpcLayer::UploadRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
UploadRpcLayer::PendingUploadCdnFile *UploadRpcLayer::getCdnFile(const QByteArray &fileToken, quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileToken.toHex() << offset << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadGetCdnFile;
    outputStream << fileToken;
    outputStream << offset;
    outputStream << limit;
    PendingUploadCdnFile *op = new PendingUploadCdnFile(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingFileHashVector *UploadRpcLayer::getCdnFileHashes(const QByteArray &fileToken, quint32 offset)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileToken.toHex() << offset;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadGetCdnFileHashes;
    outputStream << fileToken;
    outputStream << offset;
    PendingFileHashVector *op = new PendingFileHashVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingUploadFile *UploadRpcLayer::getFile(const TLInputFileLocation &location, quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << location << offset << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadGetFile;
    outputStream << location;
    outputStream << offset;
    outputStream << limit;
    PendingUploadFile *op = new PendingUploadFile(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingFileHashVector *UploadRpcLayer::getFileHashes(const TLInputFileLocation &location, quint32 offset)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << location << offset;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadGetFileHashes;
    outputStream << location;
    outputStream << offset;
    PendingFileHashVector *op = new PendingFileHashVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingUploadWebFile *UploadRpcLayer::getWebFile(const TLInputWebFileLocation &location, quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << location << offset << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadGetWebFile;
    outputStream << location;
    outputStream << offset;
    outputStream << limit;
    PendingUploadWebFile *op = new PendingUploadWebFile(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingFileHashVector *UploadRpcLayer::reuploadCdnFile(const QByteArray &fileToken, const QByteArray &requestToken)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileToken.toHex() << requestToken.toHex();
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadReuploadCdnFile;
    outputStream << fileToken;
    outputStream << requestToken;
    PendingFileHashVector *op = new PendingFileHashVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingBool *UploadRpcLayer::saveBigFilePart(quint64 fileId, quint32 filePart, quint32 fileTotalParts, const QByteArray &bytes)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileId << filePart << fileTotalParts << bytes.toHex();
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadSaveBigFilePart;
    outputStream << fileId;
    outputStream << filePart;
    outputStream << fileTotalParts;
    outputStream << bytes;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UploadRpcLayer::PendingBool *UploadRpcLayer::saveFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes)
{
    qCDebug(c_clientRpcUploadCategory) << Q_FUNC_INFO << fileId << filePart << bytes.toHex();
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UploadSaveFilePart;
    outputStream << fileId;
    outputStream << filePart;
    outputStream << bytes;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
