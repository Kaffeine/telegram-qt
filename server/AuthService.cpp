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

#include "AuthService.hpp"

#include "ApiUtils.hpp"
#include "Debug_p.hpp"
#include "RandomGenerator.hpp"
#include "TelegramServerUser.hpp"

#include <QDateTime>
#include <QDir>
#include <QImage>
#include <QLoggingCategory>

namespace Telegram {

namespace Server {

AuthService::AuthService(QObject *parent) :
    QObject(parent)
{
}

void AuthService::setAuthorizationProvider(Authorization::Provider *provider)
{
    m_authProvider = provider;
}

PasswordInfo AuthService::getPassword(const LocalUser *user)
{
    PasswordInfo result;
    if (user && user->hasPassword()) {
        result.currentSalt = user->passwordSalt();
        result.hint = user->passwordHint();
    }
    return result;
}

bool AuthService::checkPassword(const LocalUser *user, const QByteArray &hash)
{
    if (user && user->hasPassword()) {
        return user->passwordHash() == hash;
    }
    return false;
}

void AuthService::registerAuthKey(quint64 authId, const QByteArray &authKey)
{
    m_authorizations.insert(authId, authKey);
}

QByteArray AuthService::getAuthKeyById(quint64 authId) const
{
    return m_authorizations.value(authId);
}

quint32 AuthService::getUserIdByAuthId(quint64 authId) const
{
    return m_authToUserId.value(authId);
}

void AuthService::addUserAuthorization(AuthorizedUser *user, quint64 authKeyId)
{
    m_authToUserId.insert(authKeyId, user->userId());
    user->addAuthKey(authKeyId);
}

} // Server namespace

} // Telegram namespace
