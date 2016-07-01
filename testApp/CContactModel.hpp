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

class CTelegramCore;

struct SContact : TelegramNamespace::UserInfo {
    SContact() :
        status(TelegramNamespace::ContactStatusUnknown),
        wasOnline(0),
        typing(TelegramNamespace::MessageActionNone),
        blocked(false)
    { }

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

    explicit CContactsModel(CTelegramCore *backend, QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant data(const QString &phone, Column column) const;
    QVariant data(quint32 id, Column column) const;
    QVariant data(int contactIndex, Column column) const;

    int indexOfContact(quint32 id) const;
    int indexOfContact(const QString &phone) const;

    QStringList contacts() const;
    QString contactAt(int index, bool addName) const;

public slots:
    void addContact(quint32 id);
    bool removeContact(quint32 id);
    void setContactList(const QVector<quint32> &newContactList);
    void setContactStatus(quint32 id, TelegramNamespace::ContactStatus status);
    void setContactLastOnline(quint32 id, quint32 onlineDate);
    void setTypingStatus(quint32 id, TelegramNamespace::MessageAction action);
    void setContactAvatar(quint32 id, const QPixmap &avatar);

    void clear();

protected slots:
    void whenContactProfileChanged(quint32 id);

private:
    QString contactStatusStr(const SContact &contact) const;

    CTelegramCore *m_backend;

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
