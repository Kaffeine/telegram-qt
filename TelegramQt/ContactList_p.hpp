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

#ifndef TELEGRAMQT_CLIENT_CONTACT_LIST_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_CONTACT_LIST_PRIVATE_HPP

#include "ContactList.hpp"

namespace Telegram {

namespace Client {

class ContactListPrivate
{
public:
    static ContactList *create(ContactsApi *api);
    static ContactListPrivate *get(ContactList *parent);

    void addUserIds(const QVector<quint32> &ids);
    void setUserIds(const QVector<quint32> &ids);

    ContactList *q_func() const { return m_q; }

    QVector<quint32> m_userIds;
    ContactList *m_q = nullptr;
    ContactsApi *m_api = nullptr;
    PendingOperation *m_readyOperation = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_CONTACT_LIST_PRIVATE_HPP
