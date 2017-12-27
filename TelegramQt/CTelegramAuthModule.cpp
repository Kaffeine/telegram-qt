/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "CTelegramAuthModule.hpp"

#include "CTelegramConnection.hpp"
#include "TelegramNamespace_p.hpp"
#include "Utils.hpp"

#include <QDebug>

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

using namespace Telegram;

CTelegramAuthModule::CTelegramAuthModule(QObject *parent) :
    CTelegramModule(parent),
    m_serverKey(defaultServerPublicRsaKey())
{
}

Telegram::RsaKey CTelegramAuthModule::defaultServerPublicRsaKey() const
{
    return Utils::loadHardcodedKey();
}

Telegram::RsaKey CTelegramAuthModule::serverPublicRsaKey() const
{
    return m_serverKey;
}

bool CTelegramAuthModule::setServerPublicRsaKey(const Telegram::RsaKey &key)
{
    m_serverKey = key;
    return true;
}

quint64 CTelegramAuthModule::authKeyId() const
{
    if (!mainConnection()) {
        return 0;
    }
    return mainConnection()->authId();
}

void CTelegramAuthModule::clear()
{
    m_passwordInfo.clear();
}

bool CTelegramAuthModule::logOut()
{
    if (!mainConnection()) {
        return false;
    }

    mainConnection()->authLogOut();
    return true;
}

void CTelegramAuthModule::requestPhoneStatus(const QString &phoneNumber)
{
    if (!mainConnection()) {
        return;
    }
    mainConnection()->authCheckPhone(phoneNumber);
}

quint64 CTelegramAuthModule::getPassword()
{
    if (!mainConnection()) {
        return 0;
    }

    m_passwordInfo.clear();

    return mainConnection()->accountGetPassword();
}

void CTelegramAuthModule::tryPassword(const QByteArray &salt, const QByteArray &password)
{
    if (!mainConnection()) {
        return;
    }

    const QByteArray pwdData = salt + password + salt;
    const QByteArray pwdHash = Utils::sha256(pwdData);

    mainConnection()->authCheckPassword(pwdHash);
}

void CTelegramAuthModule::tryPassword(const QString &password)
{
    if (m_passwordInfo.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "There is no known salts to try password. Get it by getPassword() call.";
        return;
    }
    tryPassword(m_passwordInfo.first().currentSalt, password.toUtf8());
}

void CTelegramAuthModule::signIn(const QString &phoneNumber, const QString &authCode)
{
    if (!mainConnection()) {
        return;
    }
    mainConnection()->signIn(phoneNumber, authCode);
}

void CTelegramAuthModule::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    if (!mainConnection()) {
        return;
    }
    mainConnection()->signUp(phoneNumber, authCode, firstName, lastName);
}

quint64 CTelegramAuthModule::requestAuthCode(const QString &phoneNumber)
{
    if (!mainConnection()) {
        qWarning() << Q_FUNC_INFO << "Unable to request a phone code without an active connection.";
        return 0;
    }
//    if (m_dcConfiguration.isEmpty()) {
//        qWarning() << Q_FUNC_INFO << "Can't request phone code: DC Configuration is unknown.";
//        return;
//    }
    if (phoneNumber.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Unable to request a phone code without a phone number.";
        return 0;
    }
    m_requestedCodeForPhone = phoneNumber;
    return mainConnection()->requestPhoneCode(phoneNumber);
}

void CTelegramAuthModule::onUnauthorizedErrorReceived(TelegramNamespace::UnauthorizedError errorCode)
{
    switch (errorCode) {
    case TelegramNamespace::UnauthorizedSessionPasswordNeeded:
        mainConnection()->accountGetPassword();
        break;
    default:
        break;
    }
}

void CTelegramAuthModule::onPasswordReceived(const TLAccountPassword &password, quint64 requestId)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << password << requestId;
#else
    qDebug() << Q_FUNC_INFO << requestId;
#endif

    m_passwordInfo.insert(requestId, password);
    emit passwordInfoReceived(requestId);
}

void CTelegramAuthModule::onWantedMainDcChanged(quint32 dc, const QString &dcForPhoneNumber)
{
    qDebug() << Q_FUNC_INFO << dc << "for phone number" << Telegram::Utils::maskPhoneNumber(dcForPhoneNumber);
    setWantedDc(dc);
}

void CTelegramAuthModule::onNewConnection(CTelegramConnection *connection)
{
    connect(connection, &CTelegramConnection::passwordReceived, this, &CTelegramAuthModule::onPasswordReceived);
    connect(connection, &CTelegramConnection::phoneCodeRequired, this, &CTelegramAuthModule::phoneCodeRequired);
    connect(connection, &CTelegramConnection::authSignErrorReceived, this, &CTelegramAuthModule::authSignErrorReceived);
    connect(connection, &CTelegramConnection::authorizationErrorReceived, this, &CTelegramAuthModule::authorizationErrorReceived);
    connect(connection, &CTelegramConnection::phoneStatusReceived, this, &CTelegramAuthModule::phoneStatusReceived);
    connect(connection, &CTelegramConnection::wantedMainDcChanged, this, &CTelegramAuthModule::onWantedMainDcChanged);

    // Should be done only for the main connection, but probably it is safe to connect to all connections for now
    connect(connection, &CTelegramConnection::loggedOut, this, &CTelegramAuthModule::loggedOut);

    connection->setServerRsaKey(m_serverKey);
}

bool CTelegramAuthModule::getPasswordData(Telegram::PasswordInfo *passwordInfo, quint64 requestId) const
{
    qDebug() << Q_FUNC_INFO << requestId;
    if (m_passwordInfo.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "No password data";
        return false;
    }
    if (requestId == 0) {
        requestId = m_passwordInfo.keys().first();
        qDebug() << Q_FUNC_INFO << "Zero call mapped to " << requestId;
    }
    if (!m_passwordInfo.contains(requestId)) {
        qWarning() << Q_FUNC_INFO << "Password data not found for id" << requestId;
        return false;
    }

    TLAccountPassword &data = *passwordInfo->d;
    data = m_passwordInfo.value(requestId);
    return true;
}
