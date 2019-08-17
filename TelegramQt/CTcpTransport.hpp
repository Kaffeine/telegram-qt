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

#ifndef CTCPTRANSPORT_HPP
#define CTCPTRANSPORT_HPP

#include "CTelegramTransport.hpp"

namespace Telegram {

namespace Crypto {

class AesCtrContext;

} // Crypto namespace

class TELEGRAMQT_INTERNAL_EXPORT BaseTcpTransport : public BaseTransport
{
    Q_OBJECT
public:
    enum SessionType {
        Unknown,
        Abridged, // char(0xef)
        FullSize,
        Obfuscated,
        Default = Unknown,
    };
    Q_ENUM(SessionType)
    enum SourceRevertion {
        DirectIsWriteReversedIsRead,
        DirectIsReadReversedIsWrite,
    };

    explicit BaseTcpTransport(QObject *parent = nullptr);
    ~BaseTcpTransport() override;

    static int connectionTimeout();

    QString remoteAddress() const override;

    void disconnectFromHost() override;

    SessionType sessionType() const;

protected slots:
    void setState(QAbstractSocket::SocketState newState) override;
    void onReadyRead();

    void onSocketErrorOccurred(QAbstractSocket::SocketError error);

protected:
    void setSocket(QAbstractSocket *socket);
    void sendPacketImplementation(const QByteArray &payload) override;

    void setSessionType(SessionType sessionType);
    void resetCryptoKeys();
    void setCryptoKeysSourceData(const QByteArray &source, SourceRevertion revertion);

    quint32 m_packetNumber = 0;
    quint32 m_expectedLength = 0;
    SessionType m_sessionType = Unknown;

    QAbstractSocket *m_socket = nullptr;
    QByteArray m_readBuffer;
    Telegram::Crypto::AesCtrContext *m_readAesContext = nullptr;
    Telegram::Crypto::AesCtrContext *m_writeAesContext = nullptr;

public:
    static const char *timeoutEnvironmentVariableName();
};

} // Telegram namespace

#endif // CTCPTRANSPORT_HPP
