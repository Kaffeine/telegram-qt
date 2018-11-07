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

#include "DataStorage_p.hpp"

#include "ApiUtils.hpp"
#include "TLTypesDebug.hpp"
#include "Debug.hpp"

#include "TelegramNamespace_p.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

/*!
    \class Telegram::Client::DataStorage
    \brief The DataStorage class provides a basic interface for session
           data management
    \inmodule TelegramQt
    \ingroup Client

    \sa AccountStorage
*/

DataStorage::DataStorage(QObject *parent) :
    DataStorage(new DataStoragePrivate(), parent)
{
    Q_D(DataStorage);
    d->m_api = new DataInternalApi(this);
}

DataInternalApi *DataStorage::internalApi()
{
    Q_D(DataStorage);
    return d->m_api;
}

DcConfiguration DataStorage::serverConfiguration() const
{
    Q_D(const DataStorage);
    return d->m_serverConfig;
}

void DataStorage::setServerConfiguration(const DcConfiguration &configuration)
{
    Q_D(DataStorage);
    d->m_serverConfig = configuration;
}

quint32 DataStorage::selfUserId() const
{
    Q_D(const DataStorage);
    return d->m_api->selfUserId();
}

bool DataStorage::getUserInfo(UserInfo *info, quint32 userId) const
{
    Q_D(const DataStorage);
    const auto &users = d->m_api->m_users;
    if (!users.contains(userId)) {
        qDebug() << Q_FUNC_INFO << "Unknown user" << userId;
        return false;
    }

    const TLUser *user = users.value(userId);
    TLUser *infoData = Telegram::UserInfo::Private::get(info);
    *infoData = *user;
    return true;
}

DataStorage::DataStorage(DataStoragePrivate *d, QObject *parent)
    : QObject(parent),
      d_ptr(d)
{
}

InMemoryDataStorage::InMemoryDataStorage(QObject *parent) :
    DataStorage(parent)
{
}

DataInternalApi::DataInternalApi(QObject *parent) :
    QObject(parent)
{
}

DataInternalApi::~DataInternalApi()
{
}

const TLUser *DataInternalApi::getSelfUser() const
{
    if (!m_selfUserId) {
        return nullptr;
    }
    return m_users.value(m_selfUserId);
}

void DataInternalApi::processData(const TLUser &user)
{
    TLUser *existsUser = m_users.value(user.id);
    if (existsUser) {
        *existsUser = user;
    } else {
        m_users.insert(user.id, new TLUser(user));
    }
    if (user.self()) {
        if (m_selfUserId && (m_selfUserId != user.id)) {
            qWarning() << "Got self user with different id.";
        }
        m_selfUserId = user.id;
    }
}

void DataInternalApi::processData(const TLAuthAuthorization &authorization)
{
    processData(authorization.user);
}

} // Client namespace

} // Telegram namespace
