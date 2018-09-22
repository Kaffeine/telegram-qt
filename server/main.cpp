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

#include "TelegramServer.hpp"
#include "TelegramServerUser.hpp"
#include "DcConfiguration.hpp"
#include "LocalCluster.hpp"
#include "Session.hpp"

#include "Utils.hpp"
#include <QCoreApplication>
#include <QDebug>
#include <QStandardPaths>

using namespace Telegram::Server;

#ifdef USE_DBUS_NOTIFIER
#include <QDBusConnection>
#include <QDBusMessage>

#include "ServerApi.hpp"
#include "DefaultAuthorizationProvider.hpp"

class DBusCodeAuthProvider : public Authorization::DefaultProvider
{
protected:
    Authorization::Code generateCode(Session *session, const QString &identifier) override;
};

Authorization::Code DBusCodeAuthProvider::generateCode(Session *session, const QString &identifier)
{
    Authorization::Code code = DefaultProvider::generateCode(session, identifier);
    QDBusMessage message = QDBusMessage::createMethodCall(QStringLiteral("org.freedesktop.Notifications"),
                                                          QStringLiteral("/org/freedesktop/Notifications"),
                                                          QStringLiteral("org.freedesktop.Notifications"),
                                                          QStringLiteral("Notify"));
    message.setArguments({
                             QCoreApplication::applicationName(),
                             QVariant::fromValue(0u),
                             QString(),
                             QStringLiteral("New auth code request"),
                             QStringLiteral("Auth code for account %1 is %2. Peer IP: %3").arg(identifier, code.code, session->ip),
                             QStringList(),
                             QVariantMap(),
                             3000
                         });

    // QString app_name, uint replaces_id, QString app_icon, QString summary,
    // QString body, QStringList actions, QVariantMap hints, int timeout
    QDBusConnection::sessionBus().send(message);
    return code;
}
#endif // USE_DBUS_NOTIFIER

User *tryAddUser(LocalCluster *cluster,
                 const QString &identifier, quint32 dcId,
                 const QString &firstName, const QString &lastName,
                 const QString &password = QString()
        )
{
    User *u = cluster->addUser(identifier, dcId);
    if (u) {
        u->setFirstName(firstName);
        u->setLastName(lastName);
        u->setPlainPassword(password);
    } else {
        qCritical() << "Unable to add a user";
    }
    return u;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName(QStringLiteral("TelegramQt Server"));
    Telegram::initialize();

    Telegram::DcConfiguration configuration;
    const QVector<Telegram::DcOption> dcOptions = {
        Telegram::DcOption(QStringLiteral("127.0.0.1"), 11441, 1),
        Telegram::DcOption(QStringLiteral("127.0.0.2"), 11442, 2),
        Telegram::DcOption(QStringLiteral("127.0.0.3"), 11443, 3),
    };
    configuration.dcOptions = dcOptions;

    const Telegram::RsaKey key = Telegram::Utils::loadRsaPrivateKeyFromFile(
                QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first()
                + QStringLiteral("/TelegramServer/private_key.pem"));
    if (!key.isValid()) {
        qCritical() << "Unable to read RSA key";
        return -1;
    }

    LocalCluster cluster;
    cluster.setServerPrivateRsaKey(key);
    cluster.setServerConfiguration(configuration);
#ifdef USE_DBUS_NOTIFIER
    DBusCodeAuthProvider authProvider;
    cluster.setAuthorizationProvider(&authProvider);
    qInfo() << "DBus auth code provider enabled";
#endif
    cluster.start();

    tryAddUser(&cluster, QStringLiteral("5432101"), /* dc */ 1,
               QStringLiteral("Telegram"), QStringLiteral("Qt"),
               QStringLiteral("mypassword")
               );

    tryAddUser(&cluster, QStringLiteral("5432102"), /* dc */ 2,
               QStringLiteral("Telegram2"), QStringLiteral("Qt2")
               );

    tryAddUser(&cluster, QStringLiteral("5432103"), /* dc */ 3,
               QStringLiteral("Telegram3"), QStringLiteral("Qt3"),
               QStringLiteral("hispassword")
               );
    return a.exec();
}
