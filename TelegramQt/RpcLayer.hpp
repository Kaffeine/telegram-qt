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

class BaseTransport;
class CTelegramStream;

namespace Telegram {

namespace MTProto {

struct FullMessageHeader;
struct Message;

using Stream = ::CTelegramStream;

} // MTProto

class BaseSendPackageHelper;
enum class SendMode : quint8;

class BaseRpcLayer : public QObject
{
    Q_OBJECT
public:
    enum MessageType {
        ContentRelatedMessage,
        NotContentRelatedMessage
    };
    explicit BaseRpcLayer(QObject *parent = nullptr);

    virtual quint64 sessionId() const = 0;
    virtual quint64 serverSalt() const = 0;
    quint32 contentRelatedMessagesNumber() const;
    void setSendPackageHelper(BaseSendPackageHelper *helper);

    bool processPackage(const QByteArray &package);
    virtual bool processDecryptedMessageHeader(const MTProto::FullMessageHeader &header) = 0;
    virtual bool processMTProtoMessage(const MTProto::Message &message) = 0;

    bool processMsgContainer(const MTProto::Message &message);

    virtual void onConnectionFailed() {}

protected:
    SAesKey generateAesKey(const QByteArray &messageKey, int x) const;
    SAesKey generateClientToServerAesKey(const QByteArray &messageKey) const { return generateAesKey(messageKey, 0); }
    SAesKey generateServerToClientAesKey(const QByteArray &messageKey) const { return generateAesKey(messageKey, 8); }
    virtual SAesKey getDecryptionAesKey(const QByteArray &messageKey) const = 0;
    virtual SAesKey getEncryptionAesKey(const QByteArray &messageKey) const = 0;

    virtual QByteArray getEncryptionKeyPart() const = 0;
    virtual QByteArray getVerificationKeyPart() const = 0;
    quint32 getNextMessageSequenceNumber(MessageType messageType);

    bool sendPackage(const MTProto::Message &message);
    quint64 sendPackage(const QByteArray &buffer, SendMode mode);

    BaseSendPackageHelper *m_sendHelper = nullptr;
    quint32 m_sequenceNumber = 0;
    quint32 m_contentRelatedMessages = 0;
};

} // Telegram namespace

#endif // TELEGRAM_RPC_LAYER_HPP
