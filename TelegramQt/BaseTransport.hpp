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

#ifndef TELEGRAM_BASE_TRANSPORT_HPP
#define TELEGRAM_BASE_TRANSPORT_HPP

#include "telegramqt_global.h"

#include <QObject>

#include <QByteArray>
#include <QAbstractSocket>

namespace Telegram {

class TELEGRAMQT_INTERNAL_EXPORT BaseTransport : public QObject
{
    Q_OBJECT
public:
    explicit BaseTransport(QObject *parent = nullptr);
    virtual void connectToHost(const QString &ipAddress, quint16 port) = 0;
    virtual void disconnectFromHost() = 0;
    quint64 getNewMessageId(quint64 supposedId);

    virtual QString remoteAddress() const = 0;

    QAbstractSocket::SocketError error() const { return m_error; }
    QAbstractSocket::SocketState state() const { return m_state; }

signals:
    void errorOccurred(QAbstractSocket::SocketError error, const QString &text);
    void stateChanged(QAbstractSocket::SocketState state);

    void timeout();

    void packetReceived(const QByteArray &payload);
    void packetSent(const QByteArray &payload);

public slots:
    void sendPacket(const QByteArray &payload);

protected slots:
    void setError(QAbstractSocket::SocketError error, const QString &text);
    virtual void setState(QAbstractSocket::SocketState state);

protected:
    virtual void sendPacketImplementation(const QByteArray &payload) = 0;
    virtual void readEvent() {}
    virtual void writeEvent() {}

private:
    QAbstractSocket::SocketError m_error;
    QAbstractSocket::SocketState m_state;
    quint64 m_lastMessageId = 0;
    QString m_errorText;

};

} // Telegram namespace

#endif // TELEGRAM_BASE_TRANSPORT_HPP
