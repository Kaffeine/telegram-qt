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

#include "TelegramServerConfig.hpp"
#include "TelegramServerUser.hpp"
#include "DcConfiguration.hpp"
#include "LocalCluster.hpp"
#include "PluginsLoader.hpp"
#include "Session.hpp"

#include "Utils.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QStandardPaths>
#include <QCommandLineParser>

using namespace Telegram::Server;

#ifdef USE_DBUS_NOTIFIER
#include <QDBusConnection>
#include <QDBusMessage>
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName(QStringLiteral("TelegramQt"));
    a.setApplicationName(QStringLiteral("TelegramQt Server"));

    Telegram::initialize();

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption configFileOption(QStringList{ QStringLiteral("c"), QStringLiteral("config") });
    configFileOption.setDescription(QStringLiteral("Path to config file"));
    configFileOption.setValueName(QStringLiteral("configFilePath"));
    configFileOption.setDefaultValue(Config::defaultFileName());
    parser.addOption(configFileOption);

    QCommandLineOption generateConfigOption(QStringList{ QStringLiteral("g"), QStringLiteral("generate") });
    generateConfigOption.setDescription(QStringLiteral("Generate a config file"));
    parser.addOption(generateConfigOption);

    parser.process(a);

    // Load config
    Config config(parser.value(configFileOption));
    if (!config.load()) {
        // create "default" config file to ease editing
        config.save();
    }

    if (parser.isSet(generateConfigOption)) {
        return 0;
    }

    const Telegram::RsaKey key = Telegram::RsaKey::fromFile(config.privateKeyFile());
    if (!key.isValid()) {
        qCritical() << "Unable to read RSA key. Please read README.md for more information.";
        return -1;
    }

    LocalCluster cluster;
    cluster.setServerPrivateRsaKey(key);
    cluster.setServerConfiguration(config.serverConfiguration());
    cluster.setListenAddress(QHostAddress::Any);

    for (FederalizationApi *api : PluginsLoader::federalizationApis()) {
        cluster.addFederalization(api);
    }

#ifdef USE_DBUS_NOTIFIER
    DBusCodeAuthProvider authProvider;
    cluster.setAuthorizationProvider(&authProvider);
    qInfo() << "DBus auth code provider enabled";
#endif

    if (!cluster.start()) {
        return -2;
    }

    int retCode = a.exec();
    cluster.stop();

    return retCode;
}
