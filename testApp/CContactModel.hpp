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
#include <QSet>

#include "TelegramNamespace.hpp"

class CTelegramCore;
class CFileManager;

struct SContact : Telegram::UserInfo {
    SContact() :
        Telegram::UserInfo(),
        typing(TelegramNamespace::MessageActionNone),
        blocked(false)
    { }

    TelegramNamespace::MessageAction typing;
    bool blocked;
    QPixmap m_picture;
    QString m_pictureToken;
};

class CContactModel : public QAbstractTableModel
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

    explicit CContactModel(CTelegramCore *backend, QObject *parent = 0);

    void setFileManager(CFileManager *manager);

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

    QVector<quint32> contacts() const;
    QString contactAt(int index, bool addName) const;

    static QString formatName(const Telegram::UserInfo &info);
    static QString getContactName(const Telegram::UserInfo &contact);
    static QString getContactIdentifier(const Telegram::UserInfo &contact);

public slots:
    void addContact(quint32 id);
    bool removeContact(quint32 id);
    void setContactList(const QVector<quint32> &newContactList);
    void setTypingStatus(quint32 id, TelegramNamespace::MessageAction action);

    void clear();

protected slots:
    void onContactProfileChanged(quint32 id);
    void onContactStatusChanged(quint32 id);
    void onFileRequestComplete(const QString &uniqueId);

private:
    void addContactId(quint32 id);
    QString getPictureCacheToken(const Telegram::Peer &peer) const;
    QString getPictureCacheToken(const QString &key) const;
    QString contactStatusStr(const SContact &contact) const;

    CTelegramCore *m_backend;
    CFileManager *m_fileManager;
    QSet<QString> m_requests;

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
