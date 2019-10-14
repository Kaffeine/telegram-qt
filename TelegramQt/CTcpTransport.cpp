/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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
#include "CTcpTransport.hpp"
#include "Debug_p.hpp"
#include "RawStream.hpp"

#include <QHostAddress>

#include <QLoggingCategory>

#ifndef Q_FALLTHROUGH
#define Q_FALLTHROUGH() (void)0
#endif

Q_LOGGING_CATEGORY(c_loggingTcpTransport, "telegram.transport.tcp", QtWarningMsg)

static const quint32 c_defaultConnectionTimeout = 15 * 1000;

namespace Telegram {

BaseTcpTransport::BaseTcpTransport(QObject *parent) :
    BaseTransport(parent),
    m_socket(nullptr)
{
}

BaseTcpTransport::~BaseTcpTransport()
{
    if (m_socket && m_socket->isWritable() && m_socket->isOpen()
            && m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->waitForBytesWritten(100);
        qCDebug(c_loggingTcpTransport) << CALL_INFO << "close socket" << m_socket;
        m_socket->disconnectFromHost();
    }
    delete m_readAesContext;
    delete m_writeAesContext;
}

int BaseTcpTransport::connectionTimeout()
{
    static const int connectionTimeout =
            qEnvironmentVariableIntValue(timeoutEnvironmentVariableName());
    if (connectionTimeout > 0) {
        return connectionTimeout;
    }
    return c_defaultConnectionTimeout;
}

QString BaseTcpTransport::remoteAddress() const
{
    return m_socket ? m_socket->peerAddress().toString() : QString();
}

void BaseTcpTransport::disconnectFromHost()
{
    qCDebug(c_loggingTcpTransport) << CALL_INFO;
    if (m_socket) {
        qCDebug(c_loggingTcpTransport) << CALL_INFO << "close socket" << m_socket;
        m_socket->disconnectFromHost();
    }
    m_readBuffer.clear();
    m_packetNumber = 0;
    m_expectedLength = 0;
    m_sessionType = Unknown;
}

BaseTcpTransport::SessionType BaseTcpTransport::sessionType() const
{
    return m_sessionType;
}

void BaseTcpTransport::sendPacketImplementation(const QByteArray &payload)
{
    qCDebug(c_loggingTcpTransport) << CALL_INFO << payload.size();

    // quint32 length (included length itself + packet number
    //                 + crc32 + payload (MUST be divisible by 4)
    // quint32 packet number
    // quint32 CRC32 (length, quint32 packet number, payload)
    // Payload

    // Abridged version:
    // quint8: 0xef
    // DataLength / 4 < 0x7f ?
    //      (quint8: Packet length / 4) :
    //      (quint8: 0x7f, quint24: Packet length / 4)
    // Payload

    if (payload.length() % 4) {
        qCCritical(c_loggingTcpTransport) << CALL_INFO
                                          << "Invalid outgoing packet! "
                                             "The payload size is not divisible by four!";
    }

    QByteArray packet;
    packet.reserve(payload.size() + 4);
    const quint32 length = payload.length() / 4;
    if (length < 0x7f) {
        packet.append(char(length));
    } else {
        packet.append(char(0x7f));
        packet.append(reinterpret_cast<const char *>(&length), 3);
    }
    packet.append(payload);

    if (m_writeAesContext && m_writeAesContext->hasKey()) {
        packet = m_writeAesContext->crypt(packet);
    }

    m_socket->write(packet);
}

void BaseTcpTransport::setSessionType(BaseTcpTransport::SessionType sessionType)
{
    m_sessionType = sessionType;
}

void BaseTcpTransport::resetCryptoKeys()
{
    delete m_readAesContext;
    m_readAesContext = nullptr;
    delete m_writeAesContext;
    m_writeAesContext = nullptr;
}

void BaseTcpTransport::setCryptoKeysSourceData(const QByteArray &source, SourceRevertion revertion)
{
    if (source.size() != (Crypto::AesCtrContext::KeySize + Crypto::AesCtrContext::IvecSize)) {
        qCWarning(c_loggingTcpTransport) << CALL_INFO << "Invalid input data (size mismatch)";
        return;
    }
    QByteArray reversed = source;
    std::reverse(reversed.begin(), reversed.end());
    const auto setSourceData = [](const QByteArray &source, Crypto::AesCtrContext **context) {
        Crypto::AesCtrContext *&localContext = *context;

        if (!localContext) {
            localContext = new Crypto::AesCtrContext();
        }
        localContext->setKey(source.left(Crypto::AesCtrContext::KeySize));
        localContext->setIVec(source.mid(Crypto::AesCtrContext::KeySize));
    };
    if (revertion == DirectIsReadReversedIsWrite) {
        setSourceData(source, &m_readAesContext);
        setSourceData(reversed, &m_writeAesContext);
    } else { // Server, DirectIsWriteReversedIsRead
        setSourceData(source, &m_writeAesContext);
        setSourceData(reversed, &m_readAesContext);
    }
    const char *className = metaObject()->className();
    if (strstr(className, "Server")) {
        m_readAesContext->setDescription(QByteArrayLiteral("server read"));
        m_writeAesContext->setDescription(QByteArrayLiteral("server write"));
    } else if (strstr(className, "Client")) {
        m_readAesContext->setDescription(QByteArrayLiteral("client read"));
        m_writeAesContext->setDescription(QByteArrayLiteral("client write"));
    }
}

const char *BaseTcpTransport::timeoutEnvironmentVariableName()
{
    return "TELEGRAM_CONNECTION_TIMEOUT";
}

void BaseTcpTransport::setState(QAbstractSocket::SocketState newState)
{
    qCDebug(c_loggingTcpTransport) << CALL_INFO << newState;
    if (newState == QAbstractSocket::ConnectedState) {
        m_expectedLength = 0;
        setSessionType(Unknown);
    }
    BaseTransport::setState(newState);
}

void BaseTcpTransport::onReadyRead()
{
    qCDebug(c_loggingTcpTransport) << CALL_INFO << m_socket->bytesAvailable();
    readEvent();
    if (m_sessionType == Unknown) {
        qCCritical(c_loggingTcpTransport) << this << "Unknown session type!";
        return;
    }
    if (m_socket->bytesAvailable() > 0) {
        QByteArray allData = m_socket->readAll();
        if (m_readAesContext) {
            allData = m_readAesContext->crypt(allData);
        }
        m_readBuffer.append(allData);
    }
    while (m_readBuffer.size() >= 4) {
        if (m_expectedLength == 0) {
            const quint8 *data = reinterpret_cast<const quint8*>(m_readBuffer.constData());
            quint8 length_t1 = data[0];
            if (length_t1 < 0x7fu) {
                m_expectedLength = length_t1 * 4;
                m_readBuffer = m_readBuffer.mid(1);
            } else if (length_t1 == 0x7fu) {
                m_expectedLength = data[1] + data[2] * 256 + data[3] * 256 * 256;
                m_expectedLength *= 4;
                m_readBuffer = m_readBuffer.mid(4);
            } else {
                qCWarning(c_loggingTcpTransport) << CALL_INFO << "Invalid packet size byte"
                                                 << hex << showbase << length_t1;
                setError(QAbstractSocket::UnknownSocketError, QLatin1String("Invalid read operation"));
                disconnectFromHost();
                return;
            }
        }
        if (m_readBuffer.size() < static_cast<int>(m_expectedLength)) {
            qCDebug(c_loggingTcpTransport) << CALL_INFO << "Ready read, but only "
                                           << m_readBuffer.size() << "bytes available ("
                                           << m_expectedLength << "bytes expected)";
            return;
        }
        const QByteArray payload = m_readBuffer.left(static_cast<int>(m_expectedLength));
        m_readBuffer = m_readBuffer.mid(static_cast<int>(m_expectedLength));
        m_expectedLength = 0;
        qCDebug(c_loggingTcpTransport) << CALL_INFO
                                       << "Received a packet (" << payload.size() << " bytes)";
        emit packetReceived(payload);
    }
}

void BaseTcpTransport::onSocketErrorOccurred(QAbstractSocket::SocketError error)
{
    setError(error, m_socket->errorString());
}

void BaseTcpTransport::setSocket(QAbstractSocket *socket)
{
    if (m_socket) {
        qCCritical(c_loggingTcpTransport()) << CALL_INFO << "An attempt to set a socket twice";
    }
    m_socket = socket;
    connect(m_socket, &QAbstractSocket::stateChanged, this, &BaseTcpTransport::setState);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(onSocketErrorOccurred(QAbstractSocket::SocketError)));
    connect(m_socket, &QIODevice::readyRead, this, &BaseTcpTransport::onReadyRead);
}

} // Telegram namespace
