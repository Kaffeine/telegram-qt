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

#include "ClientRpcPhotosLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcPhotosCategory, "telegram.client.rpclayer.photos", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhoto *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhotoSize *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhotosPhoto *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhotosPhotos *output);
// End of generated Telegram API reply template specializations

PhotosRpcLayer::PhotosRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PhotosRpcLayer::PendingQuint64Vector *PhotosRpcLayer::deletePhotos(const TLVector<TLInputPhoto> &id)
{
    qCDebug(c_clientRpcPhotosCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhotosDeletePhotos;
    outputStream << id;
    PendingQuint64Vector *op = new PendingQuint64Vector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhotosRpcLayer::PendingPhotosPhotos *PhotosRpcLayer::getUserPhotos(const TLInputUser &userId, quint32 offset, quint64 maxId, quint32 limit)
{
    qCDebug(c_clientRpcPhotosCategory) << Q_FUNC_INFO << userId << offset << maxId << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhotosGetUserPhotos;
    outputStream << userId;
    outputStream << offset;
    outputStream << maxId;
    outputStream << limit;
    PendingPhotosPhotos *op = new PendingPhotosPhotos(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhotosRpcLayer::PendingUserProfilePhoto *PhotosRpcLayer::updateProfilePhoto(const TLInputPhoto &id)
{
    qCDebug(c_clientRpcPhotosCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhotosUpdateProfilePhoto;
    outputStream << id;
    PendingUserProfilePhoto *op = new PendingUserProfilePhoto(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhotosRpcLayer::PendingPhotosPhoto *PhotosRpcLayer::uploadProfilePhoto(const TLInputFile &file)
{
    qCDebug(c_clientRpcPhotosCategory) << Q_FUNC_INFO << file;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhotosUploadProfilePhoto;
    outputStream << file;
    PendingPhotosPhoto *op = new PendingPhotosPhoto(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
