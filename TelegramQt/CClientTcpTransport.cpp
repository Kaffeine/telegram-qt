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

#include "Crypto/AesCtr.hpp"
#include "CClientTcpTransport.hpp"
#include "Debug_p.hpp"
#include "RandomGenerator.hpp"
#include "RawStream.hpp"
#include "TelegramNamespace.hpp"

#include <QNetworkProxy>
#include <QTcpSocket>
#include <QTimer>

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

Q_LOGGING_CATEGORY(c_loggingTranport, "telegram.client.transport", QtWarningMsg)

static const quint8 c_abridgedVersionByte = 0xef;
static const quint32 c_intermediateVersionBytes = 0xeeeeeeeeu;
static const quint32 c_obfucsatedProcotolIdentifier = 0xefefefefu;

TcpTransport::TcpTransport(QObject *parent) :
    BaseTcpTransport(parent),
    m_timeoutTimer(new QTimer(this))
{
    setSocket(new QTcpSocket(this));
    m_timeoutTimer->setInterval(connectionTimeout());
    connect(m_timeoutTimer, &QTimer::timeout, this, &TcpTransport::onTimeout);
}

TcpTransport::~TcpTransport()
{
    qCDebug(c_loggingTranport) << CALL_INFO;
}

void TcpTransport::connectToHost(const QString &ipAddress, quint16 port)
{
    const QNetworkProxy proxy = m_socket->proxy();
    QString proxyStr;
    if (proxy.hostName().isEmpty()) {
        proxyStr = QLatin1String("(none)");
    } else {
        proxyStr = proxy.hostName() + QLatin1String(":") + QString::number(proxy.port());
        if (!proxy.user().isEmpty()) {
            proxyStr = Telegram::Utils::maskString(proxy.user())
                    + QLatin1Char(':') + Telegram::Utils::maskString(proxy.password())
                    + QLatin1Char('@') + proxyStr;
        }
    }
    qCDebug(c_loggingTranport).noquote().nospace() << CALL_INFO
                                                   << '(' << ipAddress << ':' << port << ") "
                                                   << "proxy: " << proxyStr;

    m_socket->connectToHost(ipAddress, port);
}

void TcpTransport::setPreferedSessionType(const BaseTcpTransport::SessionType sessionType)
{
    m_preferedSessionType = sessionType;
}

void TcpTransport::startObfuscatedSession()
{
    qCDebug(c_loggingTranport) << CALL_INFO << "Start the session in Obfuscated format";
    // prepare random part
    const QVector<quint32> headerFirstWordBlackList = {
        0x44414548u, 0x54534f50u, 0x20544547u, 0x20544547u, c_intermediateVersionBytes,
    };
    const QVector<quint32> headerSecondWordBlackList = {
        0x0,
    };

    quint32 first4Bytes;
    // The first word must not concide with any of the previously known session first bytes
    do {
        first4Bytes = RandomGenerator::instance()->generate<quint32>();
    } while (headerFirstWordBlackList.contains(first4Bytes)
             || ((first4Bytes & 0xffu) == c_abridgedVersionByte)
             );

    quint32 next4Bytes;
    // The same about the second word.
    do {
        next4Bytes = RandomGenerator::instance()->generate<quint32>();
    } while (headerSecondWordBlackList.contains(next4Bytes));

    const QByteArray aesSourceData = RandomGenerator::instance()->generate(48);
    setCryptoKeysSourceData(aesSourceData, DirectIsWriteReversedIsRead);

    // first, next,       AES (key + Ivec),     protocol id, random 4 bytes; 64 bytes in total
    //      4      8                          56            60    64
    // xxxx | xxxx | xxxx ... xxxx (48 bytes) | 0xefefefefU | xxxx |
    const quint32 trailingRandom = RandomGenerator::instance()->generate<quint32>();

    RawStream raw(RawStream::WriteOnly);
    raw << first4Bytes;
    raw << next4Bytes;
    raw << aesSourceData;
    m_socket->write(raw.getData());
    raw << c_obfucsatedProcotolIdentifier;
    raw << trailingRandom;
    QByteArray encrypted = m_writeAesContext->crypt(raw.getData());
    m_socket->write(encrypted.mid(56, 8));
    setSessionType(Obfuscated);
}

void TcpTransport::startAbridgedSession()
{
    qCDebug(c_loggingTranport) << "Start the session in Abridged format";
    m_socket->putChar(c_abridgedVersionByte);
    setSessionType(Abridged);
}

bool TcpTransport::setProxy(const QNetworkProxy &proxy)
{
    if (m_socket->isOpen()) {
        qCWarning(c_loggingTranport) << CALL_INFO << "Unable to set proxy on open socket";
        return false;
    }
    m_socket->setProxy(proxy);
    return true;
}

void TcpTransport::setState(QAbstractSocket::SocketState newState)
{
    switch (newState) {
    case QAbstractSocket::HostLookupState:
    case QAbstractSocket::ConnectingState:
        qCDebug(c_loggingTranport) << this << "start connection timer";
        m_timeoutTimer->start();
        break;
    default:
        qCDebug(c_loggingTranport) << this << "stop connection timer";
        m_timeoutTimer->stop();
        break;
    }
    BaseTcpTransport::setState(newState);
}

void TcpTransport::onTimeout()
{
    qCDebug(c_loggingTranport) << CALL_INFO
                               << "socket state:" << m_socket->state()
                               << "peer:" << m_socket->peerName() << m_socket->peerPort()
                               << "local port:" << m_socket->localPort();
    emit timeout();
    qCDebug(c_loggingTranport) << CALL_INFO << "close socket" << m_socket;
    m_socket->disconnectFromHost();
}

void TcpTransport::writeEvent()
{
    if (Q_LIKELY(m_sessionType != Unknown)) {
        return;
    }
    switch (m_preferedSessionType) {
    case Default:
    case Obfuscated:
        startObfuscatedSession();
        break;
    case Abridged:
        startAbridgedSession();
        break;
    default:
        qCCritical(c_loggingTranport) << CALL_INFO
                                      << "The selected session type"
                                      << m_preferedSessionType
                                      << "is not supported";
        break;
    }
}

} // Client

} // Telegram
