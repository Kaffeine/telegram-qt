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

#include "telegramqt_global.h"

#include <QObject>

#include "Crypto/Aes.hpp"

namespace Telegram {

namespace MTProto {

class Stream;
struct FullMessageHeader;
struct Message;

} // MTProto namespace

class BaseMTProtoSendHelper;
enum class SendMode : quint8;

class TELEGRAMQT_INTERNAL_EXPORT BaseRpcLayer : public QObject
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
    void setSendHelper(BaseMTProtoSendHelper *helper);

    bool processPacket(const QByteArray &package);
    virtual bool processMessageHeader(const MTProto::FullMessageHeader &header) = 0;
    virtual bool processMTProtoMessage(const MTProto::Message &message) = 0;

    bool processMsgContainer(const MTProto::Message &message);

    virtual void onConnectionLost(const QVariantHash &details);

protected:
    Crypto::AesKey generateAesKey(const QByteArray &messageKey, int x) const;
    Crypto::AesKey generateClientToServerAesKey(const QByteArray &messageKey) const { return generateAesKey(messageKey, 0); }
    Crypto::AesKey generateServerToClientAesKey(const QByteArray &messageKey) const { return generateAesKey(messageKey, 8); }
    virtual Crypto::AesKey getDecryptionAesKey(const QByteArray &messageKey) const = 0;
    virtual Crypto::AesKey getEncryptionAesKey(const QByteArray &messageKey) const = 0;

    virtual QByteArray getEncryptionKeyPart() const = 0;
    virtual QByteArray getVerificationKeyPart() const = 0;
    quint32 getNextMessageSequenceNumber(MessageType messageType);

    bool sendPacket(const MTProto::Message &message);
    quint64 sendPacket(const QByteArray &buffer, SendMode mode, MessageType messageType);

    BaseMTProtoSendHelper *m_sendHelper = nullptr;
    quint32 m_sequenceNumber = 0;
    quint32 m_contentRelatedMessages = 0;
};

} // Telegram namespace

#endif // TELEGRAM_RPC_LAYER_HPP
