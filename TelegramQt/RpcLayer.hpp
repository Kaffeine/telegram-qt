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

#ifndef TELEGRAM_RPC_LAYER_HPP
#define TELEGRAM_RPC_LAYER_HPP

#include <QObject>

#include "crypto-aes.hpp"

class CTelegramTransport;

namespace Telegram {

class BaseSendPackageHelper;
enum class SendMode : quint8;

class BaseRpcLayer : public QObject
{
    Q_OBJECT
public:
    explicit BaseRpcLayer(QObject *parent = nullptr);

    quint64 sessionId() const { return m_sessionId; }

    void setSendPackageHelper(BaseSendPackageHelper *helper);

    bool processPackage(const QByteArray &package);
    virtual bool processDecryptedPackage(const QByteArray &package) = 0;

protected:
    SAesKey generateAesKey(const QByteArray &messageKey, int x) const;
    SAesKey generateClientToServerAesKey(const QByteArray &messageKey) const { return generateAesKey(messageKey, 0); }
    SAesKey generateServerToClientAesKey(const QByteArray &messageKey) const { return generateAesKey(messageKey, 8); }
    virtual SAesKey getDecryptionAesKey(const QByteArray &messageKey) const = 0;
    virtual SAesKey getEncryptionAesKey(const QByteArray &messageKey) const = 0;

    quint64 sendPackage(const QByteArray &buffer, SendMode mode);

    BaseSendPackageHelper *m_sendHelper = nullptr;
    quint32 m_sequenceNumber = 0;
    quint32 m_contentRelatedMessages = 0;

    quint64 m_receivedServerSalt = 0;
    quint64 m_sessionId = 0;
};

} // Telegram namespace

#endif // TELEGRAM_RPC_LAYER_HPP
