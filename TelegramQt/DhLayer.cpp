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

#include "DhLayer.hpp"

#include "MTProto/Stream.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "Debug_p.hpp"
#include "DhSession.hpp"

#include <QDateTime>
#include <QLoggingCategory>

#ifdef NETWORK_LOGGING
#include "CompatibilityLayer.hpp"

#include <QDir>
#include <QFile>
#include <QTextStream>

const int valFieldWidth = 32;
QString formatTLValue(const TLValue &val)
{
    const QString text = val.toString();
    return QString(valFieldWidth - text.length(), QLatin1Char(' ')) + text;
}
#endif

Q_LOGGING_CATEGORY(c_baseDhLayerCategory, "telegram.base.dhlayer", QtWarningMsg)

namespace Telegram {

BaseDhLayer::BaseDhLayer(QObject *parent) :
    QObject(parent)
{
}

void BaseDhLayer::setSendPackageHelper(BaseMTProtoSendHelper *helper)
{
    m_sendHelper = helper;
}

void BaseDhLayer::setServerRsaKey(const RsaKey &key)
{
    qCDebug(c_baseDhLayerCategory) << CALL_INFO << "Set server key:"
                                   << key.modulus.toHex() << key.exponent.toHex()
                                   << key.secretExponent.toHex() << key.fingerprint;
    m_rsaKey = key;
}

Crypto::AesKey BaseDhLayer::generateTmpAesKey(const BaseDhSession *session)
{
    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << session->serverNonce << session->newNonce;
    QByteArray newNonceAndServerNonce;
    newNonceAndServerNonce.append(session->newNonce.data, session->newNonce.size());
    newNonceAndServerNonce.append(session->serverNonce.data, session->serverNonce.size());
    QByteArray serverNonceAndNewNonce;
    serverNonceAndNewNonce.append(session->serverNonce.data, session->serverNonce.size());
    serverNonceAndNewNonce.append(session->newNonce.data, session->newNonce.size());
    QByteArray newNonceAndNewNonce;
    newNonceAndNewNonce.append(session->newNonce.data, session->newNonce.size());
    newNonceAndNewNonce.append(session->newNonce.data, session->newNonce.size());

    const QByteArray key = Utils::sha1(newNonceAndServerNonce)
            + Utils::sha1(serverNonceAndNewNonce).mid(0, 12);
    const QByteArray iv  = Utils::sha1(serverNonceAndNewNonce).mid(12, 8)
            + Utils::sha1(newNonceAndNewNonce)
            + QByteArray(session->newNonce.data, 4);

    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << "key:" << key.toHex() << "iv:" << iv.toHex();

    return Crypto::AesKey(key, iv);
}

bool BaseDhLayer::checkClientServerNonse(MTProto::Stream &stream) const
{
    TLNumber128 nonce;
    stream >> nonce;
    if (nonce != m_session->clientNonce) {
        qCDebug(c_baseDhLayerCategory) << CALL_INFO
                                       << "Error: Client nonce in the incoming package"
                                          " is different from the local one.";
        return false;
    }

    stream >> nonce;
    if (nonce != m_session->serverNonce) {
        qCDebug(c_baseDhLayerCategory) << CALL_INFO
                                       << "Error: Server nonce in the incoming package"
                                          " is different from the local one.";
        return false;
    }
    return true;
}

quint64 BaseDhLayer::sendPlainPackage(const QByteArray &payload, SendMode mode)
{
    const quint64 authKeyId = 0;
    const quint64 messageId = m_sendHelper->newMessageId(mode);
    const quint32 messageLength = payload.length();
    constexpr int headerSize = sizeof(authKeyId) + sizeof(messageId) + sizeof(messageLength);

    QByteArray output;
    output.reserve(headerSize + payload.size());
    RawStream outputStream(&output, /* write */ true);

    outputStream << authKeyId;
    outputStream << messageId;
    outputStream << messageLength;
    outputStream << payload;

    qCDebug(c_baseDhLayerCategory) << CALL_INFO
                                   << output.left(8).toHex()
                                   << output.mid(8).toHex();

#ifdef NETWORK_LOGGING
    {
        MTProto::Stream readBack(payload);
        TLValue val1;
        readBack >> val1;

        QTextStream str(getLogFile());

        str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz"))
            << QLatin1Char('|');
        str << QLatin1String("pln|");
        str << QString(QLatin1String("size: %1|")).arg(payload.length(), 4, 10, QLatin1Char('0'));
        str << formatTLValue(val1) << QLatin1Char('|');
        str << payload.toHex();
        str << TELEGRAMQT_ENDL;
    }
#endif

    m_sendHelper->sendPacket(output);
    return messageId;
}

bool BaseDhLayer::processPlainPackage(const QByteArray &buffer)
{
    RawStream inputStream(buffer);

#ifdef NETWORK_LOGGING
    {
        QTextStream str(getLogFile());
        str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz"))
            << QLatin1Char('|');
        str << QLatin1String("pln|");
        str << QString(QLatin1String("size: %1|")).arg(buffer.length(), 4, 10, QLatin1Char('0'));
        str << QLatin1Char('|');
        str << buffer.toHex();
        str << TELEGRAMQT_ENDL;
    }
#endif

    // Plain Message
    quint64 authKeyId = 0;
    quint64 messageId = 0;
    quint32 messageLength = 0;
    QByteArray payload;

    inputStream >> authKeyId;
    inputStream >> messageId;
    inputStream >> messageLength;

    qCDebug(c_baseDhLayerCategory) << CALL_INFO
                                   << buffer.left(8).toHex()
                                   << buffer.mid(8).toHex();
    if (inputStream.error()) {
        qCWarning(c_baseDhLayerCategory) << CALL_INFO << "Unable to read header";
        return false;
    }

    if (inputStream.bytesAvailable() != int(messageLength)) {
        qCWarning(c_baseDhLayerCategory) << CALL_INFO
                                         << "Unable to read packet data. The specified"
                                            " length does not equal to the actually available";
        return false;
    }

    payload = inputStream.readBytes(messageLength);
    qCDebug(c_baseDhLayerCategory) << "read payload:" << messageLength;
#ifdef DEVELOPER_BUILD
    qCDebug(c_baseDhLayerCategory) << CALL_INFO << "new plain package in auth state"
                                   << m_state
                                   << "payload:" << TLValue::firstFromArray(payload);
#endif
    processReceivedPacket(payload);
    return true;
}

bool BaseDhLayer::hasKey() const
{
    return m_state == State::HasKey;
}

void BaseDhLayer::setState(BaseDhLayer::State state)
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_baseDhLayerCategory) << CALL_INFO << state;
#endif
    if (m_state == state) {
        return;
    }
    m_state = state;
    emit stateChanged(state);
}

#ifdef NETWORK_LOGGING
QFile *BaseDhLayer::getLogFile()
{
    if (!m_logFile) {
        QDir dir;
        dir.mkdir(QLatin1String("network"));

        m_logFile = new QFile(QStringLiteral("network/%1.log").arg(ulong(this), 0, 0x10));
        m_logFile->open(QIODevice::WriteOnly);
    }
    //qDebug() << CALL_INFO << m_dcInfo.id << m_dcInfo.ipAddress << m_transport->state();
    return  m_logFile;
}
#endif

} // Telegram
