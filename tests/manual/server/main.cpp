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

#include "DcConfiguration.hpp"
#include "DefaultAuthorizationProvider.hpp"
#include "JsonDataImporter.hpp"
#include "LocalCluster.hpp"
#include "ServerApi.hpp"
#include "IMediaService.hpp"
#include "MessageService.hpp"
#include "RandomGenerator.hpp"
#include "Session.hpp"
#include "TelegramServerConfig.hpp"
#include "TelegramServerUser.hpp"
#include "Utils.hpp"

// Test
#include "TestServerUtils.hpp"
#include "TestUserData.hpp"
#include "keys_data.hpp"

#include <QBuffer>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QStandardPaths>
#include <QTimer>

using namespace Telegram::Server;

class ConstantAuthCodeProvider : public Authorization::DefaultProvider
{
public:
    static QString s_code;
protected:
    Authorization::Code generateCode(Session *session, const QString &identifier) override;
};

QString ConstantAuthCodeProvider::s_code = QStringLiteral("11111");

Authorization::Code ConstantAuthCodeProvider::generateCode(Session *session, const QString &identifier)
{
    Authorization::Code code;
    code.hash = Telegram::RandomGenerator::instance()->generate(8).toHex();
    code.code = s_code;
    code.type = Authorization::Code::Type::Default;
    qInfo().nospace().noquote() << "sendAppCode(" << identifier << '/' << session->id() << "):"
                                << " hash: " << code.hash
                                << " code: " << code.code;
    return code;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName(QLatin1String("TelegramQt"));
    a.setApplicationName(QLatin1String("TelegramTestServer"));
    const QString persistentKeyFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation)
            + QLatin1Literal("/TelegramTestServer.pem");

    Telegram::initialize();
    if (!TestKeyData::initKeyFiles()) {
        qCritical() << "Unable to init RSA key files.";
        return -1;
    }

    const Telegram::RsaKey privateKey = Telegram::RsaKey::fromFile(TestKeyData::privateKeyFileName());
    if (!privateKey.isValid()) {
        qCritical() << "Unable to read RSA key.";
        return -1;
    }

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption ipAddressOption(QStringList({ QLatin1String("a"), QLatin1String("address") }));
    ipAddressOption.setValueName(QLatin1String("ip"));
    ipAddressOption.setDefaultValue(QLatin1String("127.0.0.1"));
    parser.addOption(ipAddressOption);

    QCommandLineOption portOption(QStringList({ QLatin1String("p"), QLatin1String("port") }));
    portOption.setDescription(QLatin1String("first port"));
    portOption.setValueName(QLatin1String("port"));
    portOption.setDefaultValue(QLatin1String("10443"));
    parser.addOption(portOption);

    parser.process(a);

    Telegram::DcConfiguration dcConfig = Config().serverConfiguration();
    dcConfig.dcOptions.clear();

    for (quint32 i = 0; i < 3; ++i) {
        Telegram::DcOption dcOption;
        dcOption.id = i + 1;
        // A DC that does not accepts any transport considered as invalid in some client.
        // dcOption.flags = Telegram::DcOption::TcpOnly;
        dcOption.address = parser.value(ipAddressOption);
        dcOption.port = static_cast<quint16>(parser.value(portOption).toUInt() + i);
        dcConfig.dcOptions.append(dcOption);
    }

    LocalCluster cluster;
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(dcConfig);

    ConstantAuthCodeProvider authProvider;
    cluster.setAuthorizationProvider(&authProvider);
    qInfo() << "Custom auth code provider enabled. The code:" << ConstantAuthCodeProvider::s_code;
    qInfo() << "Start server with unsafe (not secret) encryption RSA key:";
    qInfo() << "    Private:" << TestKeyData::privateKeyFileName();
    qInfo() << "    Public PKCS1:" << TestKeyData::publicKeyPkcs1FileName();
    qInfo() << "    Public PKCS8:" << TestKeyData::publicKeyPkcs8FileName();

    QFile::remove(persistentKeyFilePath);
    if (QFile::copy(TestKeyData::publicKeyPkcs1FileName(), persistentKeyFilePath)) {
        qInfo() << "    Persistent file location:" << persistentKeyFilePath;
    } else {
        qWarning() << "Unable to save the RSA key in a persistent location.";
    }

    if (!cluster.start()) {
        return -2;
    }

    JsonDataImporter importer;
    importer.setBaseDirectory(QLatin1String("TelegramServer/io"));
    importer.setTarget(&cluster);
    importer.loadData();

    QTimer saveTimer;
    saveTimer.setInterval(30000);
    saveTimer.setSingleShot(false);
    QObject::connect(&saveTimer, &QTimer::timeout, [&importer]() {
        qInfo() << "Sync server data";
        importer.saveData();
    });
    saveTimer.start();

    LocalUser *user = cluster.addUser(QStringLiteral("123456789"), /* dc */ 1);
    user->setFirstName(QStringLiteral("Dc1User1"));
    user->setLastName(QStringLiteral("Dc1"));
    AbstractServerApi *serverApi = cluster.getServerApiInstance(user->dcId());

    const int dcCount = cluster.serverConfiguration().dcCount();
    const int dialogsCount = 3;

    for (int i = 0; i < dialogsCount; ++i) {
        LocalUser *dialogN = tryAddUser(&cluster,
                                        // Add users to different DCs
                                        mkUserData(i, static_cast<quint32>((i % dcCount) + 1)));
        AbstractServerApi *contactServer = cluster.getServerApiInstance(dialogN->dcId());

        MessageData *data = serverApi->messageService()
                ->addMessage(dialogN->userId(), user->toPeer(), QStringLiteral("mgs%1").arg(i + 1));
        data->setDate32(data->date() - 60);
        cluster.processMessage(data);

        // Upload an image
        const ImageDescriptor image = uploadUserImage(contactServer);
        dialogN->updateImage(image);
    }

    int retCode = a.exec();
    cluster.stop();

    importer.saveData();

    TestKeyData::cleanupKeyFiles();
    return retCode;
}
