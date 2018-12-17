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

#include "CTelegramTransport.hpp"

namespace Telegram {

BaseTransport::BaseTransport(QObject *parent) :
    QObject(parent),
    m_error(QAbstractSocket::UnknownSocketError),
    m_state(QAbstractSocket::UnconnectedState)
{
}

quint64 BaseTransport::getNewMessageId(quint64 supposedId)
{
    // The doc says that client message identifiers are divisible by 4, server message identifiers
    // modulo 4 yield 1 if the message is a response to a client message, and 3 otherwise.
    // In fact, 'pong' messages from server yield 2.
    const quint8 moduleFour = supposedId % 4;
    quint64 result = supposedId;
    if (result <= m_lastMessageId) {
        result = (m_lastMessageId & ~3ull) | moduleFour;
        if (result <= m_lastMessageId) {
            result += 4;
        }
    }
    if (!(result & quint64(0xffffff))) {
        // The lower 32 bits of messageId passed by the client must not contain that many zeroes.
        result += quint64(0x1230);
    }
    m_lastMessageId = result;
    return m_lastMessageId;
}

void BaseTransport::sendPackage(const QByteArray &package)
{
    writeEvent();
    sendPackageImplementation(package);
    emit packageSent(package);
}

void BaseTransport::setError(QAbstractSocket::SocketError e, const QString &text)
{
    m_error = e;
    m_errorText = text;
    emit errorOccurred(e, text);
}

void BaseTransport::setState(QAbstractSocket::SocketState s)
{
    m_state = s;
    emit stateChanged(s);
}

} // Telegram namespace
