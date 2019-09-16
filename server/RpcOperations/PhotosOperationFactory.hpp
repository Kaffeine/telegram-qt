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

#ifndef PHOTOS_OPERATION_FACTORY_HPP
#define PHOTOS_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class PhotosRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(PhotosRpcOperation)
public:
    explicit PhotosRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processDeletePhotos(RpcProcessingContext &context);
    bool processGetUserPhotos(RpcProcessingContext &context);
    bool processUpdateProfilePhoto(RpcProcessingContext &context);
    bool processUploadProfilePhoto(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runDeletePhotos();
    void runGetUserPhotos();
    void runUpdateProfilePhoto();
    void runUploadProfilePhoto();
    // End of generated run methods

    using RunMethod = void (PhotosRpcOperation::*)();
    using ProcessingMethod = bool (PhotosRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLPhotosDeletePhotos m_deletePhotos;
    MTProto::Functions::TLPhotosGetUserPhotos m_getUserPhotos;
    MTProto::Functions::TLPhotosUpdateProfilePhoto m_updateProfilePhoto;
    MTProto::Functions::TLPhotosUploadProfilePhoto m_uploadProfilePhoto;
    // End of generated RPC members
};

class PhotosOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // PHOTOS_OPERATION_FACTORY_HPP
