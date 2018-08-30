/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_CLIENT_RPC_HPP
#define TELEGRAM_CLIENT_RPC_HPP

#include "RpcLayer.hpp"

#include <QHash>

class CAppInformation;

namespace Telegram {

class AppInformation;
class PendingRpcOperation;

namespace Client {

class AuthOperation;

class RpcLayer : public Telegram::BaseRpcLayer
{
    Q_OBJECT
public:
    explicit RpcLayer(QObject *parent = nullptr);

    CAppInformation *appInformation() const { return m_appInfo; }
    void setAppInformation(CAppInformation *appInfo);

    quint64 sessionId() const override { return m_sessionId; }
    void setSessionId(quint64 newSessionId);

    bool processRpcQuery(const QByteArray &data);

    PendingRpcOperation *sendEncryptedPackage(const QByteArray &payload);
    static PendingRpcOperation *sendEncryptedPackage(RpcLayer *layer, const QByteArray &payload) { return layer->sendEncryptedPackage(payload); }

protected:
    bool processDecryptedPackage(const QByteArray &package) override;
    SAesKey getDecryptionAesKey(const QByteArray &messageKey) const final { return generateServerToClientAesKey(messageKey); }
    SAesKey getEncryptionAesKey(const QByteArray &messageKey) const final { return generateClientToServerAesKey(messageKey); }

    QByteArray getInitConnection() const;

    CAppInformation *m_appInfo = nullptr;
    AuthOperation *m_pendingAuthOperation = nullptr;
    QHash<quint64, PendingRpcOperation*> m_operations; // request message id, operation
    quint64 m_sessionId = 0;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_HPP
