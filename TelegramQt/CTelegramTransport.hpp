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

#ifndef CTELEGRAMTRANSPORT_HPP
#define CTELEGRAMTRANSPORT_HPP

#include <QObject>

#include <QByteArray>
#include <QAbstractSocket>

class CTelegramTransport : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramTransport(QObject *parent = nullptr);
    virtual void connectToHost(const QString &ipAddress, quint32 port) = 0;
    virtual void disconnectFromHost() = 0;
    quint64 getNewMessageId(quint64 supposedId);

    QAbstractSocket::SocketError error() const { return m_error; }
    QAbstractSocket::SocketState state() const { return m_state; }
signals:
    void error(QAbstractSocket::SocketError error);
    void stateChanged(QAbstractSocket::SocketState state);

    void timeout();

    void packageReceived(const QByteArray &package);
    void packageSent(const QByteArray &package);

public slots:
    void sendPackage(const QByteArray &package);

protected slots:
    void setError(QAbstractSocket::SocketError error);
    virtual void setState(QAbstractSocket::SocketState state);

protected:
    virtual void sendPackageImplementation(const QByteArray &package) = 0;
    virtual void readEvent() {}
    virtual void writeEvent() {}

private:
    QAbstractSocket::SocketError m_error;
    QAbstractSocket::SocketState m_state;
    quint64 m_lastMessageId = 0;

};

#endif // CTELEGRAMTRANSPORT_HPP
