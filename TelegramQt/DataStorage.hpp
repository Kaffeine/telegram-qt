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

#ifndef TELEGRAMQT_DATA_STORAGE_HPP
#define TELEGRAMQT_DATA_STORAGE_HPP

#include <QObject>
#include <QHash>

#include "DcConfiguration.hpp"
#include "TelegramNamespace.hpp"

#include "TLTypes.hpp"


namespace Telegram {

class PendingOperation;

namespace Client {

class DataStoragePrivate;

class DataInternalApi : public QObject
{
    Q_OBJECT
public:
    explicit DataInternalApi(QObject *parent = nullptr);
    ~DataInternalApi() override;

    const TLUser *getSelfUser() const;

    void processData(const TLVector<TLUser> &users);
    void processData(const TLUser &user);
    void processData(const TLAuthAuthorization &authorization);

    void setContactList(const TLVector<TLContact> &contacts);

    quint32 selfUserId() const { return m_selfUserId; }

    TLVector<TLContact> contactList() const { return m_contactList; }

    quint32 m_selfUserId = 0;
    QHash<quint32, TLUser *> m_users;
    TLVector<TLContact> m_contactList;
};

class DataStorage : public QObject
{
    Q_OBJECT
public:
    explicit DataStorage(QObject *parent = nullptr);

    DataInternalApi *internalApi();

    DcConfiguration serverConfiguration() const;
    void setServerConfiguration(const DcConfiguration &configuration);

    QVector<Telegram::Peer> contactList() const;

    quint32 selfUserId() const;
    bool getUserInfo(UserInfo *info, quint32 userId) const;

protected:
    DataStorage(DataStoragePrivate *d, QObject *parent);
    DataStoragePrivate *d_ptr;
    Q_DECLARE_PRIVATE(DataStorage)

};

class InMemoryDataStorage : public DataStorage
{
    Q_OBJECT
public:
    explicit InMemoryDataStorage(QObject *parent = nullptr);
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DATA_STORAGE_HPP
