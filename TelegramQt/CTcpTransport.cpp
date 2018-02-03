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

#include "CTcpTransport.hpp"

#include <QTimer>

#include <QLoggingCategory>

#ifndef Q_FALLTHROUGH
#define Q_FALLTHROUGH() (void)0
#endif

Q_LOGGING_CATEGORY(c_loggingTcpTransport, "telegram.transport.tcp", QtDebugMsg)

static const quint32 tcpTimeout = 15 * 1000;

CTcpTransport::CTcpTransport(QObject *parent) :
    CTelegramTransport(parent),
    m_socket(nullptr),
    m_timeoutTimer(new QTimer(this))
{
    m_timeoutTimer->setInterval(tcpTimeout);
    connect(m_timeoutTimer, &QTimer::timeout, this, &CTcpTransport::onTimeout);
}

CTcpTransport::~CTcpTransport()
{
    if (m_socket && m_socket->isWritable()) {
        m_socket->waitForBytesWritten(100);
        m_socket->disconnectFromHost();
    }
}

void CTcpTransport::connectToHost(const QString &ipAddress, quint32 port)
{
    qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO << ipAddress << port;
    m_socket->connectToHost(ipAddress, port);
}

void CTcpTransport::disconnectFromHost()
{
    qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO;
    if (m_socket) {
        m_socket->disconnectFromHost();
    }
}

void CTcpTransport::sendPackageImplementation(const QByteArray &payload)
{
    // quint32 length (included length itself + packet number + crc32 + payload (MUST be divisible by 4)
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
        qCCritical(c_loggingTcpTransport()) << Q_FUNC_INFO
                                            << "Invalid outgoing package! "
                                               "The payload size is not divisible by four!";
    }

    QByteArray package;
    package.reserve(payload.size() + 4);
    const quint32 length = payload.length() / 4;
    if (length < 0x7f) {
        package.append(char(length));
    } else {
        package.append(char(0x7f));
        package.append(reinterpret_cast<const char *>(&length), 3);
    }
    package.append(payload);
    m_socket->write(package);
    emit packageSent(package);
}

void CTcpTransport::setSessionType(CTcpTransport::SessionType sessionType)
{
    m_sessionType = sessionType;
}

void CTcpTransport::setState(QAbstractSocket::SocketState newState)
{
    qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO << newState;
    switch (newState) {
    case QAbstractSocket::HostLookupState:
    case QAbstractSocket::ConnectingState:
        m_timeoutTimer->start();
        break;
    case QAbstractSocket::ConnectedState:
        m_expectedLength = 0;
        setSessionType(Unknown);
        Q_FALLTHROUGH();
    default:
        m_timeoutTimer->stop();
        break;
    }
    CTelegramTransport::setState(newState);
}

void CTcpTransport::onReadyRead()
{
    readEvent();
    while (m_socket->bytesAvailable() > 0) {
        if (m_expectedLength == 0) {
            if (m_socket->bytesAvailable() < 4) {
                qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO
                                                 << "Ready read, but less, than a four bytes available.";
                return;
            }
            char length;
            m_socket->getChar(&length);

            if (length < char(0x7f)) {
                m_expectedLength = length * 4;
            } else if (length == char(0x7f)) {
                m_socket->read((char *) &m_expectedLength, 3);
                m_expectedLength *= 4;
            } else {
                qCWarning(c_loggingTcpTransport()) << "Incorrect TCP package!";
            }
        }

        if (m_socket->bytesAvailable() < m_expectedLength) {
            qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO << "Ready read, but only "
                                             << m_socket->bytesAvailable() << "bytes available ("
                                             << m_expectedLength << "bytes expected.";
            return;
        }

        const QByteArray readPackage = m_socket->read(m_expectedLength);
        m_expectedLength = 0;
        qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO
                                         << "Received a package (" << readPackage.size() << " bytes)";
        emit packageReceived(readPackage);
    }
}

void CTcpTransport::onTimeout()
{
    qCDebug(c_loggingTcpTransport()) << Q_FUNC_INFO << m_socket->peerName() << m_socket->peerPort();
    emit timeout();
    m_socket->disconnectFromHost();
}

void CTcpTransport::setSocket(QAbstractSocket *socket)
{
    if (m_socket) {
        qCCritical(c_loggingTcpTransport()) << Q_FUNC_INFO << "An attempt to set a socket twice";
    }
    m_socket = socket;
    connect(m_socket, &QAbstractSocket::stateChanged, this, &CTcpTransport::setState);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(setError(QAbstractSocket::SocketError)));
    connect(m_socket, &QIODevice::readyRead, this, &CTcpTransport::onReadyRead);
}
