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

#include "UploadOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "IMediaService.hpp"
#include "LocalServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_serverUploadRpcCategory, "telegram.server.rpc.upload", QtWarningMsg)

namespace Telegram {

namespace Server {

// Generated process methods
bool UploadRpcOperation::processGetCdnFile(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runGetCdnFile);
    context.inputStream() >> m_getCdnFile;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processGetCdnFileHashes(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runGetCdnFileHashes);
    context.inputStream() >> m_getCdnFileHashes;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processGetFile(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runGetFile);
    context.inputStream() >> m_getFile;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processGetFileHashes(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runGetFileHashes);
    context.inputStream() >> m_getFileHashes;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processGetWebFile(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runGetWebFile);
    context.inputStream() >> m_getWebFile;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processReuploadCdnFile(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runReuploadCdnFile);
    context.inputStream() >> m_reuploadCdnFile;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processSaveBigFilePart(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runSaveBigFilePart);
    context.inputStream() >> m_saveBigFilePart;
    return !context.inputStream().error();
}

bool UploadRpcOperation::processSaveFilePart(RpcProcessingContext &context)
{
    setRunMethod(&UploadRpcOperation::runSaveFilePart);
    context.inputStream() >> m_saveFilePart;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void UploadRpcOperation::runGetCdnFile()
{
    // MTProto::Functions::TLUploadGetCdnFile &arguments = m_getCdnFile;
    if (processNotImplementedMethod(TLValue::UploadGetCdnFile)) {
        return;
    }
    TLUploadCdnFile result;
    sendRpcReply(result);
}

void UploadRpcOperation::runGetCdnFileHashes()
{
    // MTProto::Functions::TLUploadGetCdnFileHashes &arguments = m_getCdnFileHashes;
    if (processNotImplementedMethod(TLValue::UploadGetCdnFileHashes)) {
        return;
    }
    //TLVector<TLCdnFileHash> result;
    //sendRpcReply(result);
    sendRpcError(RpcError::UnknownReason);
}

void UploadRpcOperation::runGetFile()
{
    MTProto::Functions::TLUploadGetFile &arguments = m_getFile;
    const TLInputFileLocation &location = arguments.location;

    if (arguments.offset % 1024) {
        sendRpcError(RpcError::OffsetInvalid);
        return;
    }
    if (arguments.limit % 1024) {
        sendRpcError(RpcError::LimitInvalid);
        return;
    }

    FileDescriptor descriptor;

    switch (arguments.location.tlType) {
    case TLValue::InputFileLocation:
        if (!location.isValid() || !location.volumeId || !location.localId || !location.secret) {
            sendRpcError(RpcError::LocationInvalid);
            return;
        }
        descriptor = api()->mediaService()->getSecretFileDescriptor(
                    location.volumeId,
                    location.localId,
                    location.secret
                    );
        break;
    case TLValue::InputDocumentFileLocation:
        if (!location.isValid() || !location.id || !location.accessHash) {
            sendRpcError(RpcError::LocationInvalid);
            return;
        }
        descriptor = api()->mediaService()->getDocumentFileDescriptor(
                    location.id,
                    location.accessHash
                    );
        break;
    default:
        qCWarning(c_serverUploadRpcCategory) << CALL_INFO << "Not implemented" << location.tlType.toString();
        sendRpcError(RpcError::UnknownReason);
        return;
    }

    if (!descriptor.isValid()) {
        qCWarning(c_serverUploadRpcCategory) << CALL_INFO << "Invalid descriptor";
        sendRpcError(RpcError::LocationInvalid);
        return;
    }

    QIODevice *file = api()->mediaService()->beginReadFile(descriptor);
    if (!file) {
        qCWarning(c_serverUploadRpcCategory) << CALL_INFO << "Unable to read file";
        sendRpcError(RpcError::UnknownReason);
        return;
    }
    file->seek(arguments.offset);

    TLUploadFile result;
    result.tlType = TLValue::UploadFile;
    result.type.tlType = TLValue::StorageFilePng;
    result.mtime = descriptor.date;
    result.bytes = file->read(arguments.limit);
    api()->mediaService()->endReadFile(file);

    sendRpcReply(result);
}

void UploadRpcOperation::runGetFileHashes()
{
    // MTProto::Functions::TLUploadGetFileHashes &arguments = m_getFileHashes;
    if (processNotImplementedMethod(TLValue::UploadGetFileHashes)) {
        return;
    }
    TLVector<TLFileHash> result;
    sendRpcReply(result);
}

void UploadRpcOperation::runGetWebFile()
{
    // MTProto::Functions::TLUploadGetWebFile &arguments = m_getWebFile;
    if (processNotImplementedMethod(TLValue::UploadGetWebFile)) {
        return;
    }
    TLUploadWebFile result;
    sendRpcReply(result);
}

void UploadRpcOperation::runReuploadCdnFile()
{
    // MTProto::Functions::TLUploadReuploadCdnFile &arguments = m_reuploadCdnFile;
    if (processNotImplementedMethod(TLValue::UploadReuploadCdnFile)) {
        return;
    }
    // TLVector<TLCdnFileHash> result;
    // sendRpcReply(result);
    sendRpcError(RpcError::UnknownReason);
}

void UploadRpcOperation::runSaveBigFilePart()
{
    // MTProto::Functions::TLUploadSaveBigFilePart &arguments = m_saveBigFilePart;
    if (processNotImplementedMethod(TLValue::UploadSaveBigFilePart)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void UploadRpcOperation::runSaveFilePart()
{
    MTProto::Functions::TLUploadSaveFilePart &arguments = m_saveFilePart;
    bool result = api()->mediaService()->uploadFilePart(arguments.fileId, arguments.filePart, arguments.bytes);
    sendRpcReply(result);
}
// End of generated run methods

void UploadRpcOperation::setRunMethod(UploadRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

UploadRpcOperation::ProcessingMethod UploadRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::UploadGetCdnFile:
        return &UploadRpcOperation::processGetCdnFile;
    case TLValue::UploadGetCdnFileHashes:
        return &UploadRpcOperation::processGetCdnFileHashes;
    case TLValue::UploadGetFile:
        return &UploadRpcOperation::processGetFile;
    case TLValue::UploadGetFileHashes:
        return &UploadRpcOperation::processGetFileHashes;
    case TLValue::UploadGetWebFile:
        return &UploadRpcOperation::processGetWebFile;
    case TLValue::UploadReuploadCdnFile:
        return &UploadRpcOperation::processReuploadCdnFile;
    case TLValue::UploadSaveBigFilePart:
        return &UploadRpcOperation::processSaveBigFilePart;
    case TLValue::UploadSaveFilePart:
        return &UploadRpcOperation::processSaveFilePart;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *UploadOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<UploadRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
