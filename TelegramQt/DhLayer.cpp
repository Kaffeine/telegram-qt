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

#include "CTelegramStream.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "Debug_p.hpp"

#include <QtEndian>
#include <QDateTime>
#include <QLoggingCategory>

#ifdef NETWORK_LOGGING
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

void BaseDhLayer::setSendPackageHelper(BaseSendPackageHelper *helper)
{
    m_sendHelper = helper;
}

void BaseDhLayer::setServerRsaKey(const RsaKey &key)
{
    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << "Set server key:"
                                   << key.modulus.toHex() << key.exponent.toHex()
                                   << key.secretExponent.toHex() << key.fingerprint;
    m_rsaKey = key;
}

SAesKey BaseDhLayer::generateTmpAesKey() const
{
    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << m_serverNonce << m_newNonce;
    QByteArray newNonceAndServerNonce;
    newNonceAndServerNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndServerNonce.append(m_serverNonce.data, m_serverNonce.size());
    QByteArray serverNonceAndNewNonce;
    serverNonceAndNewNonce.append(m_serverNonce.data, m_serverNonce.size());
    serverNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    QByteArray newNonceAndNewNonce;
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());

    const QByteArray key = Utils::sha1(newNonceAndServerNonce)
            + Utils::sha1(serverNonceAndNewNonce).mid(0, 12);
    const QByteArray iv  = Utils::sha1(serverNonceAndNewNonce).mid(12, 8)
            + Utils::sha1(newNonceAndNewNonce)
            + QByteArray(m_newNonce.data, 4);

    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << "key:" << key.toHex() << "iv:" << iv.toHex();

    return SAesKey(key, iv);
}

bool BaseDhLayer::checkClientServerNonse(CTelegramStream &stream) const
{
    TLNumber128 nonce;
    stream >> nonce;
    if (nonce != m_clientNonce) {
        qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    stream >> nonce;
    if (nonce != m_serverNonce) {
        qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << "Error: Client nonce in incoming package is different from our own.";
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
    CRawStream outputStream(&output, /* write */ true);

    outputStream << authKeyId;
    outputStream << messageId;
    outputStream << messageLength;
    outputStream << payload;

    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << output.mid(0, 8).toHex() << output.mid(8).toHex();

#ifdef NETWORK_LOGGING
    {
        CTelegramStream readBack(payload);
        TLValue val1;
        readBack >> val1;

        QTextStream str(getLogFile());

        str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz")) << QLatin1Char('|');
        str << QLatin1String("pln|");
        str << QString(QLatin1String("size: %1|")).arg(payload.length(), 4, 10, QLatin1Char('0'));
        str << formatTLValue(val1) << QLatin1Char('|');
        str << payload.toHex();
        str << endl;
    }
#endif

    m_sendHelper->sendPackage(output);
    return messageId;
}

bool BaseDhLayer::processPlainPackage(const QByteArray &buffer)
{
    CRawStream inputStream(buffer);

#ifdef NETWORK_LOGGING
    {
        QTextStream str(getLogFile());
        str << QDateTime::currentDateTime().toString(QLatin1String("yyyyMMdd HH:mm:ss:zzz")) << QLatin1Char('|');
        str << QLatin1String("pln|");
        str << QString(QLatin1String("size: %1|")).arg(buffer.length(), 4, 10, QLatin1Char('0'));
        str << QLatin1Char('|');
        str << buffer.toHex();
        str << endl;
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

    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << buffer.mid(0, 8).toHex() << buffer.mid(8).toHex();
    if (inputStream.error()) {
        qCWarning(c_baseDhLayerCategory) << Q_FUNC_INFO << "Corrupted package (unable to read header)";
        return false;
    }

    if (inputStream.bytesAvailable() != int(messageLength)) {
        qCWarning(c_baseDhLayerCategory) << QStringLiteral("%1::processPlainPackage(): Corrupted package. "
                                                           "Specified length does not equal to the"
                                                           " actually available")
                                            .arg(QString::fromLatin1(metaObject()->className()));
        return false;
    }

    payload = inputStream.readBytes(messageLength);
    qCDebug(c_baseDhLayerCategory) << "read payload:" << messageLength;
#ifdef DEVELOPER_BUILD
    qCDebug(c_baseDhLayerCategory) << Q_FUNC_INFO << "new plain package in auth state" << m_state
                                   << "payload:" << TLValue::firstFromArray(payload);
#endif
    processReceivedPacket(payload);
    return true;
}

void BaseDhLayer::setState(BaseDhLayer::State state)
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_baseDhLayerCategory) << QString::fromLatin1(metaObject()->className())
                                      + QStringLiteral("::setState(") << state << ")";
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

        m_logFile = new QFile(QLatin1String("network/") + QString::number(long(this), 0x10) + QLatin1String(".log"));
        m_logFile->open(QIODevice::WriteOnly);
    }
    //qDebug() << Q_FUNC_INFO << m_dcInfo.id << m_dcInfo.ipAddress << m_transport->state();
    return  m_logFile;
}
#endif

} // Telegram
