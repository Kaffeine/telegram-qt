/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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
#ifndef TELEGRAMQT_TEST_TRANSPORT_HPP
#define TELEGRAMQT_TEST_TRANSPORT_HPP

#include "CTelegramTransport.hpp"

namespace Telegram {

namespace Test {

class Transport : public BaseTransport
{
    Q_OBJECT
public:
    explicit Transport(QObject *parent = nullptr)
        : BaseTransport(parent)
    {
    }

public:
    void connectToHost(const QString &, quint16 ) override { }
    void disconnectFromHost() override { }
    QString remoteAddress() const override { return QString(); }

protected:
    void sendPacketImplementation(const QByteArray &) override { }
};

} // Test namespace

} // Telegram namespace

#endif // TELEGRAMQT_TEST_TRANSPORT_HPP
