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

#ifndef CTESTCONNECTION_HPP
#define CTESTCONNECTION_HPP

#include "CTelegramConnection.hpp"

class CTestConnection : public CTelegramConnection
{
    Q_OBJECT
public:
    explicit CTestConnection(QObject *parent = nullptr);

    inline CTelegramTransport *transport() const { return m_transport; }

    void setClientNonce(TLNumber128 newClientNonce);
    void setServerNonce(TLNumber128 newServerNonce);
    void setNewNonce(TLNumber256 newNewNonce);
    void setAuthKey(const QByteArray &newKey);
    void setGA(const QByteArray &newGA);
    void setPrime(const QByteArray &newPrime);
    void setB(const QByteArray &newB);

    SAesKey testGenerateClientToServerAesKey(const QByteArray &messageKey) const;
    quint64 testNewMessageId();

};

#endif // CTESTCONNECTION_HPP
