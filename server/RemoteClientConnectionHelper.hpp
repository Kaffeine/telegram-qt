/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "SendPackageHelper.hpp"

namespace Telegram {

namespace Server {

class RemoteClientConnection;

class MTProtoSendHelper : public BaseMTProtoSendHelper
{
public:
    explicit MTProtoSendHelper(BaseConnection *connection);

    quint64 newMessageId(SendMode mode) override;
    void sendPacket(const QByteArray &package) override;

    RemoteClientConnection *getRemoteClientConnection() const;
};

} // Server namespace

} // Telegram namespace
