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

#ifndef TELEGRAM_CLIENT_RPC_USERS_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_USERS_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class UsersRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit UsersRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingUserFull = PendingRpcResult<TLUserFull *>;
    using PendingUserVector = PendingRpcResult<TLVector<TLUser> *>;
    using PendingBool = PendingRpcResult<TLBool *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingUserFull *getFullUser(const TLInputUser &id);
    PendingUserVector *getUsers(const TLVector<TLInputUser> &id);
    PendingBool *setSecureValueErrors(const TLInputUser &id, const TLVector<TLSecureValueError> &errors);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_USERS_LAYER_HPP
