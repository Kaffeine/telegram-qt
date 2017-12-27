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

#ifndef CTELEGRAMAUTHMODULE_HPP
#define CTELEGRAMAUTHMODULE_HPP

#include "CTelegramModule.hpp"

#include <QMap>

class CTelegramAuthModule : public CTelegramModule
{
    Q_OBJECT
public:
    explicit CTelegramAuthModule(QObject *parent = nullptr);

    Telegram::RsaKey defaultServerPublicRsaKey() const;
    Telegram::RsaKey serverPublicRsaKey() const;
    bool setServerPublicRsaKey(const Telegram::RsaKey &key);
    quint64 authKeyId() const;

    void clear() override;

    bool logOut();
    void requestPhoneStatus(const QString &phoneNumber);
    quint64 getPassword();
    void tryPassword(const QByteArray &salt, const QByteArray &password);
    void tryPassword(const QString &password);
    bool getPasswordData(Telegram::PasswordInfo *passwordInfo, quint64 requestId) const;
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    quint64 requestAuthCode(const QString &phoneNumber);

signals:
    void phoneStatusReceived(const QString &phone, bool registered);
    void phoneCodeRequired();
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void loggedOut(bool result);
    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);
    void passwordInfoReceived(quint64 requestId);

protected slots:
    void onUnauthorizedErrorReceived(TelegramNamespace::UnauthorizedError errorCode);
    void onPasswordReceived(const TLAccountPassword &password, quint64 requestId);

    void onWantedMainDcChanged(quint32 dc, const QString &dcForPhoneNumber);

protected:
    void onNewConnection(CTelegramConnection *connection) override;

private:
    QMap<quint64, TLAccountPassword> m_passwordInfo;
    QString m_requestedCodeForPhone;
    Telegram::RsaKey m_serverKey;

};

#endif // CTELEGRAMAUTHMODULE_HPP
