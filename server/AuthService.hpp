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

#ifndef TELEGRAM_QT_SERVER_AUTH_SERVICE_HPP
#define TELEGRAM_QT_SERVER_AUTH_SERVICE_HPP

#include "ServerNamespace.hpp"

#include <QHash>
#include <QObject>

namespace Telegram {

namespace Server {

class AuthorizedUser;
class LocalUser;

namespace Authorization {

class Provider;

} // Authorization namespace

struct PasswordInfo
{
    bool hasPassword() const { return !currentSalt.isEmpty(); }
    QByteArray newSalt;
    QString emailUnconfirmedPattern;
    QByteArray currentSalt;
    QString hint;
    bool hasRecovery = false;
};

class ServerImportApi;

class AuthService : public QObject
{
    Q_OBJECT
public:
    explicit AuthService(QObject *parent = nullptr);

    Authorization::Provider *getAuthorizationProvider() const { return m_authProvider; }
    void setAuthorizationProvider(Authorization::Provider *provider);

    PasswordInfo getPassword(const LocalUser *user);
    bool checkPassword(const LocalUser *user, const QByteArray &hash);

    QByteArray getAuthKeyById(quint64 authId) const;
    quint32 getUserIdByAuthId(quint64 authId) const;

    void registerAuthKey(quint64 authId, const QByteArray &authKey);

    void addUserAuthorization(AuthorizedUser *user, quint64 authKeyId);

protected:
    QHash<quint64, QByteArray> m_authorizations; // Auth id to auth key
    QHash<quint64, quint32> m_authToUserId;
    Authorization::Provider *m_authProvider = nullptr;

    friend class ServerImportApi;
};

} // Server namespaceMediaService

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_AUTH_SERVICE_HPP
