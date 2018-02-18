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

#ifdef DEVELOPER_BUILD
#include "AbridgedLength.hpp"
#include "Debug_p.hpp"
#endif

#include <QLoggingCategory>

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
#ifdef BASE_RPC_IO_DEBUG
    qDebug() << Q_FUNC_INFO << "Read" << package.length() << "bytes:";
    qDebug() << package.toHex();
#endif
    const quint64 *authKeyIdBytes = reinterpret_cast<const quint64*>(package.constData());
    const quint64 authKeyId = *authKeyIdBytes;
    if (!verifyAuthKey(authKeyId)) {
        qDebug() << Q_FUNC_INFO << "Incorrect auth id.";
#ifdef NETWORK_LOGGING
        QTextStream str(m_logFile);
        str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz")) << QLatin1Char('|');
        str << QLatin1String("pln|");
        str << QString(QLatin1String("size: %1|")).arg(input.length(), 4, 10, QLatin1Char('0'));
        str << QLatin1Char('|');
        str << package.toHex();
        str << endl;
        str.flush();
#endif
        return false;
    }
    // Encrypted Message
    const QByteArray messageKey = package.mid(8, 16);
    const QByteArray data = package.mid(24);
    const SAesKey key = getDecryptionAesKey(messageKey);
    const QByteArray decryptedData = Utils::aesDecrypt(data, key).left(data.length());
#ifdef BASE_RPC_IO_DEBUG
    qDebug() << "messageKey:" << messageKey.toHex();
    qDebug() << "data:" << data.toHex();
    qDebug() << "decryptedData:" << decryptedData.toHex();
#endif
    return processDecryptedPackage(decryptedData);
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

bool BaseRpcLayer::verifyAuthKey(quint64 authKeyId)
{
    return authKeyId == m_sendHelper->authId();
}

quint64 BaseRpcLayer::sendPackage(const QByteArray &buffer, SendMode mode)
{
    if (!m_sendHelper->authId()) {
        qCritical() << Q_FUNC_INFO << "Auth key is not set!";
        return 0;
    }
    QByteArray encryptedPackage;
    QByteArray messageKey;
    quint64 messageId = m_sendHelper->newMessageId(mode);
    qDebug() << Q_FUNC_INFO << "Send message" << TLValue::firstFromArray(buffer) << "with id" << messageId;
    {
        m_sequenceNumber = m_contentRelatedMessages * 2 + 1;
        ++m_contentRelatedMessages;
        CRawStream stream(CRawStream::WriteOnly);
        const quint32 contentLength = buffer.length();

        stream << m_sendHelper->serverSalt();
        stream << m_sessionId;
        stream << messageId;
        stream << m_sequenceNumber;
        stream << contentLength;
        stream << buffer;
        quint32 packageLength = stream.getData().length();
        const quint32 padding = AbridgedLength::paddingForAlignment(16, packageLength);
        if (padding) {
            QByteArray randomPadding(padding, Qt::Uninitialized);
            Utils::randomBytes(&randomPadding);
            stream << randomPadding;
            packageLength += padding;
        }
        const QByteArray data = stream.getData();
        messageKey = Utils::sha1(data).mid(4);
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

} // Telegram namespace
