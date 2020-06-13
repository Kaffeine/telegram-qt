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

class DhSession
{
public:
    enum State {
        Initial,
        PqReplied,
    };

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;
    TLNumber256 newNonce;
    quint64 pq = 0;
    quint32 p = 0;
    quint32 q = 0;

    quint32 expiresIn = 0;
    quint32 g = 0;
    QByteArray dhPrime;
    QByteArray gA;
    QByteArray a;

    void generateKey();
    bool isTemporary() const { return expiresIn; }

    Crypto::AesKey tmpAesKey;

    State state = Initial;
};

namespace Server {

class DhLayer : public Telegram::BaseDhLayer
{
    Q_OBJECT
public:
    explicit DhLayer(QObject *parent = nullptr);
    void init() override;

    bool processRequestPQ(const QByteArray &data);
    void sendResultPQ(const DhSession *session);
    bool processRequestDHParams(const QByteArray &data);
    void initiateDhParams(DhSession *session);
    bool acceptDhParams(const DhSession *session);
    bool declineDhParams();
    bool processSetClientDHParams(const QByteArray &data);

    quint64 sendReplyPackage(const QByteArray &payload);

protected:
    void processReceivedPacket(const QByteArray &payload) override;

    DhSession *ensureSession(const TLNumber128 &clientNonce);

    QByteArray m_a;
};

} // Server namespace

} // Telegram namespace

#endif // SERVER_DH_LAYER_HPP
