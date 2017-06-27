/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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
    CTelegramTransport(QObject *parent = 0) : QObject(parent) { }
    virtual void connectToHost(const QString &ipAddress, quint32 port) = 0;
    virtual void disconnectFromHost() = 0;
    virtual bool setProxy(const QNetworkProxy &proxy) = 0;

    virtual bool isConnected() const = 0;

    virtual QByteArray getPackage() = 0;

    QAbstractSocket::SocketError error() const { return m_error; }
    QAbstractSocket::SocketState state() const { return m_state; }

    // Method for testing
    virtual QByteArray lastPackage() const = 0;

signals:
    void error(QAbstractSocket::SocketError error);
    void stateChanged(QAbstractSocket::SocketState state);

    void readyRead();
    void timeout();

public slots:
    virtual void sendPackage(const QByteArray &package) = 0;

protected:
    void setError(QAbstractSocket::SocketError error);
    void setState(QAbstractSocket::SocketState state);

private:
    QAbstractSocket::SocketError m_error;
    QAbstractSocket::SocketState m_state;

};

inline void CTelegramTransport::setError(QAbstractSocket::SocketError e)
{
    m_error = e;
    emit error(e);
}

inline void CTelegramTransport::setState(QAbstractSocket::SocketState s)
{
    m_state = s;
    emit stateChanged(s);
}

#endif // CTELEGRAMTRANSPORT_HPP
