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
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class PhotosRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit PhotosRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *deletePhotos(const TLVector<TLInputPhoto> &id);
    PendingRpcOperation *getUserPhotos(const TLInputUser &userId, quint32 offset, quint64 maxId, quint32 limit);
    PendingRpcOperation *updateProfilePhoto(const TLInputPhoto &id);
    PendingRpcOperation *uploadProfilePhoto(const TLInputFile &file);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_PHOTOS_LAYER_HPP
