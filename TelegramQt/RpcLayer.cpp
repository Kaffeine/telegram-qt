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
#include "CRawStream.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "TLValues.hpp"

#include "MTProto/MessageHeader.hpp"
#include "MTProto/Stream.hpp"

#ifdef DEVELOPER_BUILD
#include "Debug_p.hpp"
#endif

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_baseRpcLayerCategory, "telegram.base.rpclayer", QtWarningMsg)
Q_LOGGING_CATEGORY(c_baseRpcLayerCategoryIn, "telegram.base.rpclayer.in", QtWarningMsg)
Q_LOGGING_CATEGORY(c_baseRpcLayerCategoryOut, "telegram.base.rpclayer.out", QtWarningMsg)

namespace Telegram {

BaseRpcLayer::BaseRpcLayer(QObject *parent) :
    QObject(parent)
{
}

void BaseRpcLayer::setSendPackageHelper(BaseSendPackageHelper *helper)
{
    m_sendHelper = helper;
}

bool BaseRpcLayer::processPackage(const QByteArray &package)
{
    if (package.size() < 24) {
        return false;
    }
    qCDebug(c_baseRpcLayerCategoryIn) << metaObject()->className()
                                      << "processPackage(): Read" << package.length() << "bytes:";
    // Encrypted Message
    const quint64 *authKeyIdBytes = reinterpret_cast<const quint64*>(package.constData());
    const QByteArray messageKey = package.mid(8, 16);
    const QByteArray encryptedData = package.mid(24);
    const SAesKey key = getDecryptionAesKey(messageKey);
    const QByteArray decryptedData = Utils::aesDecrypt(encryptedData, key).left(encryptedData.length());
#ifdef BASE_RPC_IO_DEBUG
    qCDebug(c_baseRpcLayerCategoryIn) << "authKeyId:" << hex << showbase << *authKeyIdBytes;
    qCDebug(c_baseRpcLayerCategoryIn) << "messageKey:" << messageKey.toHex();
    qCDebug(c_baseRpcLayerCategoryIn) << "encryptedData:" << encryptedData.toHex();
    qCDebug(c_baseRpcLayerCategoryIn) << "decryptedData:" << decryptedData.toHex();
#endif
    CRawStream decryptedStream(decryptedData);

    MTProto::FullMessageHeader messageHeader;
    decryptedStream >> messageHeader;

#ifdef DEVELOPER_BUILD
    qCDebug(c_baseRpcLayerCategoryIn) << "RpcLayer::processPackage():";
    qCDebug(c_baseRpcLayerCategoryIn) << "salt:" << messageHeader.serverSalt;
    qCDebug(c_baseRpcLayerCategoryIn) << "sessionId:" << messageHeader.sessionId;
    qCDebug(c_baseRpcLayerCategoryIn) << "messageId:" << messageHeader.messageId;
    qCDebug(c_baseRpcLayerCategoryIn) << "sequenceNumber:" << messageHeader.sequenceNumber;
    qCDebug(c_baseRpcLayerCategoryIn) << "contentLength:" << messageHeader.contentLength;
#endif

    if (!processDecryptedMessageHeader(messageHeader)) {
        return false;
    }

    if (int(messageHeader.contentLength) > decryptedStream.bytesAvailable()) {
        qCWarning(c_baseRpcLayerCategoryIn) << Q_FUNC_INFO << "Expected more data than actually available."
                                            << messageHeader.contentLength << "(expected)"
                                            << decryptedStream.bytesAvailable() << "(actual)";
        return false;
    }
#ifdef USE_MTProto_V1
    QByteArray expectedMessageKey = Utils::sha1(
                decryptedData.left(MTProto::FullMessageHeader::headerLength + messageHeader.contentLength)).mid(4);
#else // MTProto_V2
    QByteArray expectedMessageKey = Utils::sha256(getVerificationKeyPart() + decryptedData).mid(8, 16);
#endif

    if (messageKey != expectedMessageKey) {
        qCWarning(c_baseRpcLayerCategoryIn) << Q_FUNC_INFO << "Invalid message key";
        return false;
    }

    QByteArray innerData = decryptedStream.readBytes(messageHeader.contentLength);
    if (decryptedStream.error()) {
        return false;
    }
    MTProto::Message message(messageHeader, innerData);
    return processMTProtoMessage(message);
}

SAesKey BaseRpcLayer::generateAesKey(const QByteArray &messageKey, int x) const
{
    const QByteArray authKey = m_sendHelper->authKey();
#ifdef USE_MTProto_V1
    QByteArray sha1_a = Utils::sha1(messageKey + authKey.mid(x, 32));
    QByteArray sha1_b = Utils::sha1(authKey.mid(32 + x, 16) + messageKey + authKey.mid(48 + x, 16));
    QByteArray sha1_c = Utils::sha1(authKey.mid(64 + x, 32) + messageKey);
    QByteArray sha1_d = Utils::sha1(messageKey + authKey.mid(96 + x, 32));

    const QByteArray key = sha1_a.mid(0, 8) + sha1_b.mid(8, 12) + sha1_c.mid(4, 12);
    const QByteArray iv  = sha1_a.mid(8, 12) + sha1_b.mid(0, 8) + sha1_c.mid(16, 4) + sha1_d.mid(0, 8);
#else // MTProto_V2
    QByteArray sha256_a = Utils::sha256(messageKey + authKey.mid(x, 36));
    QByteArray sha256_b = Utils::sha256(authKey.mid(40 + x, 36) + messageKey);
    const QByteArray key = sha256_a.left(8) + sha256_b.mid(8, 16) + sha256_a.mid(24, 8);
    const QByteArray iv  = sha256_b.left(8) + sha256_a.mid(8, 16) + sha256_b.mid(24, 8);
#endif

    return SAesKey(key, iv);
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

bool BaseRpcLayer::sendPackage(const MTProto::Message &message)
{
    if (!m_sendHelper->authId()) {
        qCCritical(c_baseRpcLayerCategoryOut) << Q_FUNC_INFO << "Auth key is not set!";
        return 0;
    }
    QByteArray encryptedPackage;
    QByteArray messageKey;
    constexpr int c_alignment = 16;
    constexpr int c_v2_minimumPadding = 12;
    {
        CRawStream stream(CRawStream::WriteOnly);

        const MTProto::FullMessageHeader messageHeader(message,
                                                       m_sendHelper->serverSalt(),
                                                       sessionId());
        stream << messageHeader;

#ifdef DEVELOPER_BUILD
        qCDebug(c_baseRpcLayerCategoryOut) << "RpcLayer::sendPackage():";
        qCDebug(c_baseRpcLayerCategoryOut) << "salt:" << messageHeader.serverSalt;
        qCDebug(c_baseRpcLayerCategoryOut) << "sessionId:" << messageHeader.sessionId;
        qCDebug(c_baseRpcLayerCategoryOut) << "messageId:" << messageHeader.messageId;
        qCDebug(c_baseRpcLayerCategoryOut) << "sequenceNumber:" << messageHeader.sequenceNumber;
        qCDebug(c_baseRpcLayerCategoryOut) << "contentLength:" << messageHeader.contentLength;
#endif

        stream.writeBytes(message.data);

        int packageLength = stream.getData().length();
        int padding = AbridgedLength::paddingForAlignment(c_alignment, packageLength);
#ifdef USE_MTProto_V1
        if (padding) {
            QByteArray randomPadding(padding, Qt::Uninitialized);
            Utils::randomBytes(&randomPadding);
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
            Utils::randomBytes(&randomPadding);
            stream << randomPadding;
            packageLength += padding;
        }
        const QByteArray decryptedData = stream.getData();
        messageKey = Utils::sha256(getEncryptionKeyPart() + decryptedData).mid(8, 16);
#endif
        const SAesKey key = getEncryptionAesKey(messageKey);
        encryptedPackage = Utils::aesEncrypt(decryptedData, key).left(packageLength);

#ifdef BASE_RPC_IO_DEBUG
        qCDebug(c_baseRpcLayerCategoryOut) << "authKeyId:" << hex << showbase << m_sendHelper->authId();
        qCDebug(c_baseRpcLayerCategoryOut) << "messageKey:" << messageKey.toHex();
        qCDebug(c_baseRpcLayerCategoryOut) << "encryptedData:" << encryptedPackage.toHex();
        qCDebug(c_baseRpcLayerCategoryOut) << "decryptedData:" << decryptedData.toHex();
#endif
    }

    CRawStream output(CRawStream::WriteOnly);
    output << m_sendHelper->authId(); // keyId
    output << messageKey;
    output << encryptedPackage;
    m_sendHelper->sendPackage(output.getData());
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
    return QLatin1String();
}

quint64 BaseRpcLayer::sendPackage(const QByteArray &buffer, SendMode mode)
{
    MTProto::Message message;
    message.setData(buffer);

    if (!m_sendHelper->authId()) {
        qCCritical(c_baseRpcLayerCategoryOut) << Q_FUNC_INFO << "Auth key is not set!";
        return 0;
    }
    message.messageId = m_sendHelper->newMessageId(mode);
    message.sequenceNumber = getNextMessageSequenceNumber(ContentRelatedMessage);

    qCDebug(c_baseRpcLayerCategoryOut)
            << "sendPackage(" << getModeText(mode) << "):"
            << "message" << message.firstValue()
            << "with id" << message.messageId;

    if (!sendPackage(message)) {
        return 0;
    }
    return message.messageId;
}

bool BaseRpcLayer::processMsgContainer(const MTProto::Message &message)
{
    // https://core.telegram.org/mtproto/service_messages#simple-container
    quint32 itemsCount;
    MTProto::Stream stream(message.data);
    stream >> itemsCount;
    qCDebug(c_baseRpcLayerCategoryIn) << "processContainer(stream)" << itemsCount;

    bool processed = true;
    for (quint32 i = 0; i < itemsCount; ++i) {
        MTProto::MessageHeader header;
        stream >> header;
        QByteArray innerData = stream.readBytes(header.contentLength);
        MTProto::Message innerMessage(header, innerData);

        // There is no break and 'processed' variable goes last, so we process next messages even if something fails.
        processed = processMTProtoMessage(innerMessage) && processed;
    }
    return processed;
}

} // Telegram namespace
