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

#include "RpcLayer.hpp"

#include "AbridgedLength.hpp"
#include "RandomGenerator.hpp"
#include "RawStream.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "MTProto/TLValues.hpp"

#include "MTProto/MessageHeader.hpp"
#include "MTProto/Stream.hpp"

#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_baseRpcLayerCategory, "telegram.base.rpclayer", QtWarningMsg)
Q_LOGGING_CATEGORY(c_baseRpcLayerCategoryIn, "telegram.base.rpclayer.in", QtWarningMsg)
Q_LOGGING_CATEGORY(c_baseRpcLayerCategoryOut, "telegram.base.rpclayer.out", QtWarningMsg)

namespace Telegram {

BaseRpcLayer::BaseRpcLayer(QObject *parent) :
    QObject(parent)
{
}

void BaseRpcLayer::setSendHelper(BaseMTProtoSendHelper *helper)
{
    m_sendHelper = helper;
}

bool BaseRpcLayer::processPacket(const QByteArray &package)
{
    if (package.size() < 24) {
        qCWarning(c_baseRpcLayerCategoryIn) << CALL_INFO
                                            << "Packet is too small:" << package.size() << " < 24";
        return false;
    }
    qCDebug(c_baseRpcLayerCategoryIn) << CALL_INFO
                                      << "Read" << package.length() << "bytes:";
    // Encrypted Message
#ifdef BASE_RPC_IO_DEBUG
    const quint64 *authKeyIdBytes = reinterpret_cast<const quint64*>(package.constData());
#endif
    const QByteArray messageKey = package.mid(8, 16);
    const QByteArray encryptedData = package.mid(24);
    const Crypto::AesKey key = getDecryptionAesKey(messageKey);
    const QByteArray decryptedData = Crypto::aesDecrypt(encryptedData, key).left(encryptedData.length());
#ifdef BASE_RPC_IO_DEBUG
    qCDebug(c_baseRpcLayerCategoryIn) << "authKeyId:" << hex << showbase << *authKeyIdBytes;
    qCDebug(c_baseRpcLayerCategoryIn) << "messageKey:" << messageKey.toHex();
    qCDebug(c_baseRpcLayerCategoryIn) << "encryptedData:" << encryptedData.toHex();
    qCDebug(c_baseRpcLayerCategoryIn) << "decryptedData:" << decryptedData.toHex();
#endif
    RawStream decryptedStream(decryptedData);

    MTProto::FullMessageHeader messageHeader;
    decryptedStream >> messageHeader;

#ifdef DEVELOPER_BUILD
    qCDebug(c_baseRpcLayerCategoryIn) << CALL_INFO << messageHeader;
#endif

    if (!processMessageHeader(messageHeader)) {
        qCWarning(c_baseRpcLayerCategoryIn) << CALL_INFO << "Unable to process message header";
        return false;
    }

    if (int(messageHeader.contentLength) > decryptedStream.bytesAvailable()) {
        qCWarning(c_baseRpcLayerCategoryIn) << CALL_INFO << "Expected more data than actually available."
                                            << "Actual:" << decryptedStream.bytesAvailable()
                                            << "Expected:" << messageHeader.contentLength;
        return false;
    }
#ifdef USE_MTProto_V1
    QByteArray expectedMessageKey = Utils::sha1(
                decryptedData.left(MTProto::FullMessageHeader::headerLength + messageHeader.contentLength)).mid(4);
#else // MTProto_V2
    QByteArray expectedMessageKey = Utils::sha256(getVerificationKeyPart() + decryptedData).mid(8, 16);
#endif

    if (messageKey != expectedMessageKey) {
        qCWarning(c_baseRpcLayerCategoryIn) << CALL_INFO << "Invalid message key";
        return false;
    }

    QByteArray innerData = decryptedStream.readBytes(messageHeader.contentLength);
    if (decryptedStream.error()) {
        qCWarning(c_baseRpcLayerCategoryIn) << CALL_INFO << "Decrypted content read error";
        return false;
    }
    MTProto::Message message(messageHeader, innerData);
    if (message.firstValue() == TLValue::GzipPacked) {
        qCDebug(c_baseRpcLayerCategoryIn) << CALL_INFO << "message is GzipPacked";
        QByteArray data;
        MTProto::Stream packedStream(innerData);
        TLValue gzipValue;
        packedStream >> gzipValue;
        packedStream >> data;
        data = Utils::unpackGZip(data);
        message.setData(data);
    }
    return processMTProtoMessage(message);
}

Crypto::AesKey BaseRpcLayer::generateAesKey(const QByteArray &messageKey, int x) const
{
    const QByteArray authKey = m_sendHelper->authKey();
#ifdef USE_MTProto_V1
    QByteArray sha1_a = Utils::sha1(messageKey + authKey.mid(x, 32));
    QByteArray sha1_b = Utils::sha1(authKey.mid(32 + x, 16) + messageKey + authKey.mid(48 + x, 16));
    QByteArray sha1_c = Utils::sha1(authKey.mid(64 + x, 32) + messageKey);
    QByteArray sha1_d = Utils::sha1(messageKey + authKey.mid(96 + x, 32));

    const QByteArray key = sha1_a.mid(0, 8) + sha1_b.mid(8, 12) + sha1_c.mid(4, 12);
    const QByteArray iv  = sha1_a.mid(8, 12) + sha1_b.left(8) + sha1_c.mid(16, 4) + sha1_d.left(8);
#else // MTProto_V2
    QByteArray sha256_a = Utils::sha256(messageKey + authKey.mid(x, 36));
    QByteArray sha256_b = Utils::sha256(authKey.mid(40 + x, 36) + messageKey);
    const QByteArray key = sha256_a.left(8) + sha256_b.mid(8, 16) + sha256_a.mid(24, 8);
    const QByteArray iv  = sha256_b.left(8) + sha256_a.mid(8, 16) + sha256_b.mid(24, 8);
#endif

    return Crypto::AesKey(key, iv);
}

quint32 BaseRpcLayer::contentRelatedMessagesNumber() const
{
    return m_contentRelatedMessages;
}

quint32 BaseRpcLayer::getNextMessageSequenceNumber(MessageType messageType)
{
    // https://core.telegram.org/mtproto/description#message-sequence-number-msg-seqno
    quint32 newNumber = m_contentRelatedMessages * 2;
    if (messageType == ContentRelatedMessage) {
        newNumber++;
        ++m_contentRelatedMessages;
    }
    return newNumber;
}

bool BaseRpcLayer::sendPacket(const MTProto::Message &message)
{
    if (!m_sendHelper->authId()) {
        qCCritical(c_baseRpcLayerCategoryOut) << CALL_INFO << "Auth key is not set!";
        return 0;
    }
    QByteArray encryptedPackage;
    QByteArray messageKey;
    constexpr int c_alignment = 16;
    constexpr int c_v2_minimumPadding = 12;
    {
        const MTProto::FullMessageHeader messageHeader(message, serverSalt(), sessionId());
#ifdef DEVELOPER_BUILD
        qCDebug(c_baseRpcLayerCategoryOut) << "RpcLayer::sendPackage():" << messageHeader;
#endif
        RawStream stream(RawStream::WriteOnly);
        stream << messageHeader;
        stream.writeBytes(message.data);

        int packageLength = stream.getData().length();
        int padding = AbridgedLength::paddingForAlignment(c_alignment, packageLength);
#ifdef USE_MTProto_V1
        if (padding) {
            QByteArray randomPadding(padding, Qt::Uninitialized);
             RandomGenerator::instance()->generate(&randomPadding);
            stream << randomPadding;
            packageLength += padding;
        }
        const QByteArray data = stream.getData();
        messageKey = Utils::sha1(data).mid(4);
#else // MTProto_V2
        if (padding < c_v2_minimumPadding) {
            padding += c_alignment;
        }
        {
            QByteArray randomPadding(padding, Qt::Uninitialized);
            RandomGenerator::instance()->generate(&randomPadding);
            stream << randomPadding;
            packageLength += padding;
        }
        const QByteArray decryptedData = stream.getData();
        messageKey = Utils::sha256(getEncryptionKeyPart() + decryptedData).mid(8, 16);
#endif
        const Crypto::AesKey key = getEncryptionAesKey(messageKey);
        encryptedPackage = Crypto::aesEncrypt(decryptedData, key).left(packageLength);

#ifdef BASE_RPC_IO_DEBUG
        qCDebug(c_baseRpcLayerCategoryOut) << "authKeyId:"
                                           << hex << showbase << m_sendHelper->authId();
        qCDebug(c_baseRpcLayerCategoryOut) << "messageKey:" << messageKey.toHex();
        qCDebug(c_baseRpcLayerCategoryOut) << "encryptedData:" << encryptedPackage.toHex();
        qCDebug(c_baseRpcLayerCategoryOut) << "decryptedData:" << decryptedData.toHex();
#endif
    }

    RawStream output(RawStream::WriteOnly);
    output << m_sendHelper->authId(); // keyId
    output << messageKey;
    output << encryptedPackage;
    m_sendHelper->sendPacket(output.getData());
    return true;
}

static QLatin1String getModeText(SendMode mode)
{
    switch (mode) {
    case SendMode::Client:
        return QLatin1String("Client");
    case SendMode::ServerInitiative:
        return QLatin1String("ServerInitiative");
    case SendMode::ServerReply:
        return QLatin1String("ServerReply");
    }
    Q_UNREACHABLE();
    return QLatin1String("Invalid");
}

quint64 BaseRpcLayer::sendPacket(const QByteArray &buffer, SendMode mode, MessageType messageType)
{
    MTProto::Message message;
    message.setData(buffer);

    if (!m_sendHelper->authId()) {
        qCCritical(c_baseRpcLayerCategoryOut) << CALL_INFO
                                              << "Auth key is not set!";
        return 0;
    }
    message.messageId = m_sendHelper->newMessageId(mode);
    message.sequenceNumber = getNextMessageSequenceNumber(messageType);

    qCDebug(c_baseRpcLayerCategoryOut) << CALL_INFO
            << "(" << getModeText(mode) << "):"
            << "message" << message.firstValue()
            << "with id" << message.messageId;

    if (!sendPacket(message)) {
        return 0;
    }
    return message.messageId;
}

bool BaseRpcLayer::processMsgContainer(const MTProto::Message &message)
{
    // https://core.telegram.org/mtproto/service_messages#simple-container
    quint32 itemsCount;
    RawStream stream(message.data);
    stream >> itemsCount;
    qCDebug(c_baseRpcLayerCategoryIn) << CALL_INFO << itemsCount << "items";

    bool processed = true;
    for (quint32 i = 0; i < itemsCount; ++i) {
        MTProto::MessageHeader header;
        stream >> header;
        QByteArray innerData = stream.readBytes(header.contentLength);
        MTProto::Message innerMessage(header, innerData);

        // There is no break and the 'processed' variable goes last,
        // so we process next messages even if something fails.
        processed = processMTProtoMessage(innerMessage) && processed;
    }
    return processed;
}

void BaseRpcLayer::onConnectionLost(const QVariantHash &details)
{
    Q_UNUSED(details)
}

} // Telegram namespace
