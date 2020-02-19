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

#ifndef UPLOAD_OPERATION_FACTORY_HPP
#define UPLOAD_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class UploadRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(UploadRpcOperation)
public:
    explicit UploadRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processGetCdnFile(RpcProcessingContext &context);
    bool processGetCdnFileHashes(RpcProcessingContext &context);
    bool processGetFile(RpcProcessingContext &context);
    bool processGetFileHashes(RpcProcessingContext &context);
    bool processGetWebFile(RpcProcessingContext &context);
    bool processReuploadCdnFile(RpcProcessingContext &context);
    bool processSaveBigFilePart(RpcProcessingContext &context);
    bool processSaveFilePart(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runGetCdnFile();
    void runGetCdnFileHashes();
    void runGetFile();
    void runGetFileHashes();
    void runGetWebFile();
    void runReuploadCdnFile();
    void runSaveBigFilePart();
    void runSaveFilePart();
    // End of generated run methods

    using RunMethod = void (UploadRpcOperation::*)();
    using ProcessingMethod = bool (UploadRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLUploadGetCdnFile m_getCdnFile;
    MTProto::Functions::TLUploadGetCdnFileHashes m_getCdnFileHashes;
    MTProto::Functions::TLUploadGetFile m_getFile;
    MTProto::Functions::TLUploadGetFileHashes m_getFileHashes;
    MTProto::Functions::TLUploadGetWebFile m_getWebFile;
    MTProto::Functions::TLUploadReuploadCdnFile m_reuploadCdnFile;
    MTProto::Functions::TLUploadSaveBigFilePart m_saveBigFilePart;
    MTProto::Functions::TLUploadSaveFilePart m_saveFilePart;
    // End of generated RPC members
};

class UploadOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
    bool needLocalUser() const override { return false; }
};

} // Server namespace

} // Telegram namespace

#endif // UPLOAD_OPERATION_FACTORY_HPP
