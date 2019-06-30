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

#ifndef TELEGRAM_CLIENT_RPC_PHOTOS_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_PHOTOS_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class PhotosRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit PhotosRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingQuint64Vector = PendingRpcResult<TLVector<quint64> *>;
    using PendingPhotosPhotos = PendingRpcResult<TLPhotosPhotos *>;
    using PendingUserProfilePhoto = PendingRpcResult<TLUserProfilePhoto *>;
    using PendingPhotosPhoto = PendingRpcResult<TLPhotosPhoto *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingQuint64Vector *deletePhotos(const TLVector<TLInputPhoto> &id);
    PendingPhotosPhotos *getUserPhotos(const TLInputUser &userId, quint32 offset, quint64 maxId, quint32 limit);
    PendingUserProfilePhoto *updateProfilePhoto(const TLInputPhoto &id);
    PendingPhotosPhoto *uploadProfilePhoto(const TLInputFile &file);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_PHOTOS_LAYER_HPP
