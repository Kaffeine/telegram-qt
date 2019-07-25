/*
   Copyright (C) 2014-2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_CLIENT_HPP
#define TELEGRAM_CLIENT_HPP

#include "telegramqt_global.h"

#include <QObject>
#include <QVector>
#include <QStringList>

namespace Telegram {

namespace Client {

class AppInformation;
class Settings;
class DataStorage;
class AccountStorage;

class AccountApi;
class ConnectionApi;
class ContactsApi;
class MessagingApi;
class FilesApi;

class ClientPrivate;

class TELEGRAMQT_EXPORT Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    bool isSignedIn() const;

    AppInformation *appInformation() const;
    void setAppInformation(AppInformation *newAppInfo);

    Settings *settings();
    const Settings *settings() const;
    void setSettings(Settings *settings);

    AccountStorage *accountStorage() const;
    void setAccountStorage(AccountStorage *storage);

    DataStorage *dataStorage() const;
    void setDataStorage(DataStorage *storage);

    AccountApi *accountApi() const;
    ConnectionApi *connectionApi() const;
    ContactsApi *contactsApi() const;
    MessagingApi *messagingApi() const;
    FilesApi *filesApi() const;

Q_SIGNALS:
    void signedInChanged(bool signedIn);

private:
    ClientPrivate *d = nullptr;
    Q_DECLARE_PRIVATE_D(d, Client)
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_HPP
