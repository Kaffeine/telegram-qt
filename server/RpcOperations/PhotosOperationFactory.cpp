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

#include "PhotosOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "ServerUtils.hpp"
#include "Storage.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "CTelegramStreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool PhotosRpcOperation::processDeletePhotos(RpcProcessingContext &context)
{
    setRunMethod(&PhotosRpcOperation::runDeletePhotos);
    context.inputStream() >> m_deletePhotos;
    return !context.inputStream().error();
}

bool PhotosRpcOperation::processGetUserPhotos(RpcProcessingContext &context)
{
    setRunMethod(&PhotosRpcOperation::runGetUserPhotos);
    context.inputStream() >> m_getUserPhotos;
    return !context.inputStream().error();
}

bool PhotosRpcOperation::processUpdateProfilePhoto(RpcProcessingContext &context)
{
    setRunMethod(&PhotosRpcOperation::runUpdateProfilePhoto);
    context.inputStream() >> m_updateProfilePhoto;
    return !context.inputStream().error();
}

bool PhotosRpcOperation::processUploadProfilePhoto(RpcProcessingContext &context)
{
    setRunMethod(&PhotosRpcOperation::runUploadProfilePhoto);
    context.inputStream() >> m_uploadProfilePhoto;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void PhotosRpcOperation::runDeletePhotos()
{
    // TLFunctions::TLPhotosDeletePhotos &arguments = m_deletePhotos;
    if (processNotImplementedMethod(TLValue::PhotosDeletePhotos)) {
        return;
    }
    TLVector<quint64> result;
    sendRpcReply(result);
}

void PhotosRpcOperation::runGetUserPhotos()
{
    // TLFunctions::TLPhotosGetUserPhotos &arguments = m_getUserPhotos;
    if (processNotImplementedMethod(TLValue::PhotosGetUserPhotos)) {
        return;
    }
    TLPhotosPhotos result;
    sendRpcReply(result);
}

void PhotosRpcOperation::runUpdateProfilePhoto()
{
    // TLFunctions::TLPhotosUpdateProfilePhoto &arguments = m_updateProfilePhoto;
    if (processNotImplementedMethod(TLValue::PhotosUpdateProfilePhoto)) {
        return;
    }
    TLUserProfilePhoto result;
    sendRpcReply(result);
}

void PhotosRpcOperation::runUploadProfilePhoto()
{
    TLFunctions::TLPhotosUploadProfilePhoto &arguments = m_uploadProfilePhoto;
    const FileDescriptor desc = api()->storage()->getFileDescriptor(arguments.file.id, arguments.file.parts);

    if (!desc.isValid()) {
        sendRpcError(RpcError());
    }

    const ImageDescriptor image = api()->storage()->processImageFile(desc, arguments.file.name);

    LocalUser *self = layer()->getUser();

    self->updateImage(image);

    TLPhotosPhoto result;
    Utils::setupTLPhoto(&result.photo, image);
    result.users.resize(1);
    Utils::setupTLUser(&result.users[0], self, self);

    sendRpcReply(result);
}
// End of generated run methods

void PhotosRpcOperation::setRunMethod(PhotosRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

PhotosRpcOperation::ProcessingMethod PhotosRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::PhotosDeletePhotos:
        return &PhotosRpcOperation::processDeletePhotos;
    case TLValue::PhotosGetUserPhotos:
        return &PhotosRpcOperation::processGetUserPhotos;
    case TLValue::PhotosUpdateProfilePhoto:
        return &PhotosRpcOperation::processUpdateProfilePhoto;
    case TLValue::PhotosUploadProfilePhoto:
        return &PhotosRpcOperation::processUploadProfilePhoto;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *PhotosOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<PhotosRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
