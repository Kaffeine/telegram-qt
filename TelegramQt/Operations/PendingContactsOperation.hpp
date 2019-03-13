/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_CLIENT_PENDING_CONTACTS_OPERATION_HPP
#define TELEGRAMQT_CLIENT_PENDING_CONTACTS_OPERATION_HPP

#include "../PendingOperation.hpp"
#include "../TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class PendingContactsOperationPrivate;

class TELEGRAMQT_EXPORT PendingContactsOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingContactsOperation(QObject *parent = nullptr);
    ~PendingContactsOperation() override;

    QVector<quint32> contacts() const;
    Telegram::PeerList peers() const;

protected:
    Q_DECLARE_PRIVATE_D(d, PendingContactsOperation)
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_PENDING_CONTACTS_OPERATION_HPP
