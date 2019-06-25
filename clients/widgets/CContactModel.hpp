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

#ifndef CCONTACTSMODEL_HPP
#define CCONTACTSMODEL_HPP

#include <QList>
#include <QStringList>
#include <QSet>

#include "CPeerModel.hpp"

namespace Telegram {

namespace Client {

class ContactList;

} // Client namespace

} // Telegram namespace


struct SContact : Telegram::UserInfo {
    SContact() :
        Telegram::UserInfo(),
        typing(TelegramNamespace::MessageActionNone),
        blocked(false)
    { }

    TelegramNamespace::MessageAction typing;
    bool blocked;
    PeerPicture m_picture;
};

class CContactModel : public CPeerModel
{
    Q_OBJECT
public:
    enum Column {
        Id,
        Phone,
        UserName,
        FullName,
        Status,
        TypingStatus,
        Avatar,
        Blocked,
        ColumnsCount
    };

    explicit CContactModel(Telegram::Client::Client *backend, QObject *parent = nullptr);

    bool hasPeer(const Telegram::Peer peer) const override;
    QString getName(const Telegram::Peer peer) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant data(const QString &phone, Column column) const;
    QVariant data(quint32 id, Column column) const;
    QVariant data(int contactIndex, Column column) const;

    int indexOfContact(quint32 id) const;
    int indexOfContact(const QString &phone) const;

    bool hasContact(quint32 contactId) const;
    const SContact *contactAt(int index) const;
    const SContact *getContact(quint32 id) const;
    const SContact *getContact(const QString &phone) const;

    QVector<quint32> contacts() const;
    QString contactAt(int index, bool addName) const;

    static QString formatName(const Telegram::UserInfo &info);
    static QString getContactName(const Telegram::UserInfo &contact);
    static QString getContactIdentifier(const Telegram::UserInfo &contact);

public slots:
    void addContact(quint32 id);
    void addContacts(const QVector<quint32> &ids);
    bool removeContact(quint32 id);
    void setContactList(const QVector<quint32> &newContactList);
    void setTypingStatus(quint32 id, TelegramNamespace::MessageAction action);

    void clear();

protected slots:
    void onContactProfileChanged(quint32 id);
    void onContactStatusChanged(quint32 id);

protected:
    void updatePeerPicture(const PeerPicture &picture) override;

private:
    void addContactId(quint32 id);
    QString contactStatusStr(const SContact &contact) const;

    Telegram::Client::ContactList *m_contactList = nullptr;
    QList<SContact> m_contacts;
};

inline int CContactModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_contacts.count();
}

#endif // CCONTACTSMODEL_HPP
