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
    qCDebug(c_baseRpcLayerCategory) << metaObject()->className()<< "processPackage(): Read" << package.length() << "bytes:";
#ifdef BASE_RPC_IO_DEBUG
    qCDebug(c_baseRpcLayerCategory) << package.toHex();
#endif
    // Encrypted Message
    const QByteArray messageKey = package.mid(8, 16);
    const QByteArray data = package.mid(24);
    const SAesKey key = getDecryptionAesKey(messageKey);
    const QByteArray decryptedData = Utils::aesDecrypt(data, key).left(data.length());
#ifdef BASE_RPC_IO_DEBUG
    qCDebug(c_baseRpcLayerCategory) << "messageKey:" << messageKey.toHex();
    qCDebug(c_baseRpcLayerCategory) << "data:" << data.toHex();
    qCDebug(c_baseRpcLayerCategory) << "decryptedData:" << decryptedData.toHex();
#endif
    CRawStream decryptedStream(decryptedData);
    MTProto::FullMessageHeader messageHeader;
    decryptedStream >> messageHeader;

    if (!processDecryptedMessageHeader(messageHeader)) {
        return false;
    }

    if (int(messageHeader.contentLength) > decryptedStream.bytesAvailable()) {
        qCDebug(c_baseRpcLayerCategory) << Q_FUNC_INFO << "Expected more data than actually available.";
        return false;
    }
#ifdef USE_MTProto_V1
    QByteArray expectedMessageKey = Utils::sha1(
                decryptedData.left(MTProto::FullMessageHeader::headerLength + messageHeader.contentLength)).mid(4);
#else // MTProto_V2
    QByteArray expectedMessageKey = Utils::sha256(getVerificationKeyPart() + decryptedData).mid(8, 16);
#endif

    if (messageKey != expectedMessageKey) {
        qCWarning(c_baseRpcLayerCategory) << Q_FUNC_INFO << "Invalid message key";
        return false;
    }

    QByteArray innerData = decryptedStream.readBytes(messageHeader.contentLength);
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

quint64 BaseRpcLayer::sendPackage(const QByteArray &buffer, SendMode mode)
{
    if (!m_sendHelper->authId()) {
        qCCritical(c_baseRpcLayerCategory) << Q_FUNC_INFO << "Auth key is not set!";
        return 0;
    }
    QByteArray encryptedPackage;
    QByteArray messageKey;
    quint64 messageId = m_sendHelper->newMessageId(mode);
    qCDebug(c_baseRpcLayerCategory) << "sendPackage(" << static_cast<int>(mode) << "):"
                                    << "Send message" << TLValue::firstFromArray(buffer) << "with id" << messageId;
    constexpr int c_alignment = 16;
    constexpr int c_v2_minimumPadding = 12;
    {
        m_sequenceNumber = m_contentRelatedMessages * 2 + 1;
        ++m_contentRelatedMessages;
        CRawStream stream(CRawStream::WriteOnly);

        stream << m_sendHelper->serverSalt();
        stream << sessionId();
        stream << messageId;
        stream << m_sequenceNumber;
        stream << static_cast<quint32>(buffer.length());
        stream << buffer;

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
        const QByteArray data = stream.getData();
        messageKey = Utils::sha256(getEncryptionKeyPart() + data).mid(8, 16);
#endif
        const SAesKey key = getEncryptionAesKey(messageKey);
        encryptedPackage = Utils::aesEncrypt(data, key).left(packageLength);
    }

    CRawStream output(CRawStream::WriteOnly);
    output << m_sendHelper->authId(); // keyId
    output << messageKey;
    output << encryptedPackage;
    m_sendHelper->sendPackage(output.getData());
    return messageId;
}

bool BaseRpcLayer::processMsgContainer(const MTProto::Message &message)
{
    // https://core.telegram.org/mtproto/service_messages#simple-container
    quint32 itemsCount;
    MTProto::Stream stream(message.data);
    stream >> itemsCount;
    qCDebug(c_baseRpcLayerCategory) << "processContainer(stream)" << itemsCount;

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
