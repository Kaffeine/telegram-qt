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

#ifndef CLIENT_DH_LAYER_HPP
#define CLIENT_DH_LAYER_HPP

#include "DhLayer.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class DhLayer : public Telegram::BaseDhLayer
{
    Q_OBJECT
public:
    explicit DhLayer(QObject *parent = nullptr);
    void init() override;

    PendingRpcOperation *requestPqAuthorization();
    void onPqAuthorizationAnswer(PendingRpcOperation *operation);
    bool acceptPqAuthorization(const QByteArray &payload);
    PendingRpcOperation *requestDhParameters();
    void onDhParametersAnswer(PendingRpcOperation*operation);
    bool acceptDhAnswer(const QByteArray &payload);
    bool processServerDHParamsOK(const QByteArray &encryptedAnswer);
//    bool processServerDHParamsFail(const QByteArray &encryptedAnswer);
    void generateDh();
    PendingRpcOperation *requestDhGenerationResult();
    void onDhGenerationResultAnswer(PendingRpcOperation *operation);
    bool processServerDhAnswer(const QByteArray &payload);

protected:
    PendingRpcOperation *sendPlainPackage(const QByteArray &payload);

    void processReceivedPacket(const QByteArray &payload) override;

    PendingRpcOperation *m_plainOperation = nullptr;
    QByteArray m_b; // Client side
};

} // Client

} // Telegram

#endif // CLIENT_DH_LAYER_HPP
