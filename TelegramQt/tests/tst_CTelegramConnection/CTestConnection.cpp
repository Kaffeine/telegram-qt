/*
   Copyright (C) 2015-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "CTestConnection.hpp"

CTestConnection::CTestConnection(QObject *parent) :
    CTelegramConnection(0, parent)
{
}

void CTestConnection::setClientNonce(TLNumber128 newClientNonce)
{
    m_clientNonce = newClientNonce;
}

void CTestConnection::setServerNonce(TLNumber128 newServerNonce)
{
    m_serverNonce = newServerNonce;
}

void CTestConnection::setNewNonce(TLNumber256 newNewNonce)
{
    m_newNonce = newNewNonce;
}

void CTestConnection::setAuthKey(const QByteArray &newKey)
{
    m_authKey = newKey;
}

void CTestConnection::setGA(const QByteArray &newGA)
{
    m_gA = newGA;
}

void CTestConnection::setPrime(const QByteArray &newPrime)
{
    m_dhPrime = newPrime;
}

void CTestConnection::setB(const QByteArray &newB)
{
    m_b = newB;
}

SAesKey CTestConnection::testGenerateClientToServerAesKey(const QByteArray &messageKey) const
{
    return generateClientToServerAesKey(messageKey);
}

quint64 CTestConnection::testNewMessageId()
{
    return newMessageId();
}
