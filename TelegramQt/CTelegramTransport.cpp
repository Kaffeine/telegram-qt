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

CTelegramTransport::CTelegramTransport(QObject *parent) :
    QObject(parent)
{
}

void CTelegramTransport::sendPackage(const QByteArray &package)
{
    writeEvent();
    sendPackageImplementation(package);
    emit packageSent(package);
}

void CTelegramTransport::setError(QAbstractSocket::SocketError e)
{
    m_error = e;
    emit error(e);
}

void CTelegramTransport::setState(QAbstractSocket::SocketState s)
{
    m_state = s;
    emit stateChanged(s);
}
