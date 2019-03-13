/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef SERVER_DH_LAYER_HPP
#define SERVER_DH_LAYER_HPP

#include "DhLayer.hpp"

namespace Telegram {

namespace Server {

class DhLayer : public Telegram::BaseDhLayer
{
    Q_OBJECT
public:
    explicit DhLayer(QObject *parent = nullptr);
    void init() override;

    bool processRequestPQ(const QByteArray &data);
    bool sendResultPQ();
    bool processRequestDHParams(const QByteArray &data);
    bool acceptDhParams();
    bool declineDhParams();
    bool processSetClientDHParams(const QByteArray &data);

    quint64 sendReplyPackage(const QByteArray &payload);

protected:
    void processReceivedPacket(const QByteArray &payload) override;

    QByteArray m_a;
};

} // Server namespace

} // Telegram namespace

#endif // SERVER_DH_LAYER_HPP
