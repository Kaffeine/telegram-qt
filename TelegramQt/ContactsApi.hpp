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

#ifndef TELEGRAMQT_CLIENT_CONTACTS_API_HPP
#define TELEGRAMQT_CLIENT_CONTACTS_API_HPP

#include "ClientApi.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

class PendingOperation;

namespace Client {

class PendingContactsOperation;
class ContactsApiPrivate;
class ContactList;

class TELEGRAMQT_EXPORT ContactsApi : public ClientApi
{
    Q_OBJECT
public:
    explicit ContactsApi(QObject *parent = nullptr);

    struct ContactInfo
    {
        QString phoneNumber;
        QString firstName;
        QString lastName;
    };

    using ContactInfoList = QVector<ContactInfo>;

    ContactList *getContactList();

    QString selfPhone() const;
    quint32 selfContactId() const;

    PendingContactsOperation *addContacts(const ContactInfoList &contacts);

    PendingOperation *deleteContacts(const QVector<quint32> &ids);
    PendingOperation *blockContact(quint32 contactId);
    PendingOperation *unblockContact(quint32 contactId);
    PendingContactsOperation *getBlockedContacts();

    PendingContactsOperation *search(const QString &query, int limit = 10);
    PendingContactsOperation *resolveUsername(const QString &username);
    PendingContactsOperation *exportCard();
    PendingContactsOperation *importCard(const QByteArray &cardInfo);

Q_SIGNALS:
    void contactStatusChanged(quint32 userId, TelegramNamespace::ContactStatus status);

protected:
    Q_DECLARE_PRIVATE_D(d, ContactsApi)
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_MESSAGING_API_HPP
