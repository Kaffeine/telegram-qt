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

#ifndef CCONTACTSMODEL_HPP
#define CCONTACTSMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include <QPixmap>

#include "TelegramNamespace.hpp"

struct SContact {
    SContact(const QString &p = QString(), TelegramNamespace::ContactStatus s = TelegramNamespace::ContactStatusUnknown) :
        phone(p),
        status(s),
        wasOnline(0),
        typing(TelegramNamespace::MessageActionNone),
        blocked(false)
    { }

    QString phone;
    QString fullName;
    TelegramNamespace::ContactStatus status;
    quint32 wasOnline;
    TelegramNamespace::MessageAction typing;
    bool blocked;
    QPixmap avatar;
};

class CContactsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Phone,
        FullName,
        Status,
        TypingStatus,
        Avatar,
        Blocked,
        ColumnsCount
    };

    explicit CContactsModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant data(const QString &phone, int column) const;
    QVariant rawData(const QString &phone, int column) const;

    int indexOfContact(const QString &phone) const;

    QStringList contacts() const;
    QString contactAt(int index, bool addName) const;

public slots:
    void addContact(const QString &phone);
    bool removeContact(const QString &phone);
    void setContactList(const QStringList &list);
    void setContactStatus(const QString &contact, TelegramNamespace::ContactStatus status);
    void setContactLastOnline(const QString &contact, quint32 onlineDate);
    void setTypingStatus(const QString &contact, TelegramNamespace::MessageAction action);
    void setContactAvatar(const QString &contact, const QPixmap &avatar);
    void setContactFullName(const QString &contact, const QString &fullName);

    void clear();

private:
    QString contactStatusStr(const SContact &contact) const;

    QList<SContact> m_contacts;

};

inline int CContactsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_contacts.count();
}

#endif // CCONTACTSMODEL_HPP
