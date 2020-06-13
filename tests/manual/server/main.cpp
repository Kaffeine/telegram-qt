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
#include "Debug.hpp"
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

enum class ExitCode {
    Ok = 0,
    UnknownError,
    RsaKeyError,
    UnableToStartServer,
    InvalidArgumentFormat,
};

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

void generateDialogs(LocalCluster *cluster, const QString &userPhone, const int dialogsNumber, const int messagesNumber)
{
    qInfo() << "Generate" << dialogsNumber << "dialogs"
            << "with" << messagesNumber << "messages"
            << "for user" << userPhone;
    LocalUser *user = cluster->getUser(userPhone);
    if (!user) {
        user = cluster->addUser(userPhone, /* dc */ 1);
        user->setFirstName(user->toPeer().toString());
        user->setLastName(QStringLiteral("Dc%1").arg(user->dcId()));
    }

    AbstractServerApi *serverApi = cluster->getServerApiInstance(user->dcId());

    const int dcCount = cluster->serverConfiguration().dcCount();

    int startId = 0;
    while (cluster->getUser(phoneNumberForIdNumber(startId))) {
        ++startId;
    }

    for (int dialogIndex = 0; dialogIndex < dialogsNumber; ++dialogIndex) {
        // Add users to different DCs
        const quint32 userDcId = static_cast<quint32>((dialogIndex % dcCount) + 1);
        LocalUser *dialogN = tryAddUser(cluster, mkUserData(startId + dialogIndex, userDcId));
        qInfo() << "    Add dialog" << dialogN->toPeer();
        AbstractServerApi *contactServer = cluster->getServerApiInstance(dialogN->dcId());
        // Upload an image
        const ImageDescriptor image = uploadUserImage(contactServer);
        dialogN->updateImage(image);

        // Generate the messages
        for (int messageIndex = 0; messageIndex < messagesNumber; ++ messageIndex) {
            const QString text = QStringLiteral("mgs%1 (d%2)").arg(messageIndex + 1).arg(dialogIndex);
            MessageData *data = serverApi->messageService()->addMessage(dialogN->userId(), user->toPeer(), text);
            data->setDate(data->date() - 60);
            cluster->sendMessage(data);
        }
    }
}

ExitCode internalMain(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName(QLatin1String("TelegramQt"));
    a.setApplicationName(QLatin1String("TelegramTestServer"));
    const QString persistentKeyFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation)
            + QLatin1Literal("/TelegramTestServer.pem");

    Telegram::initialize();
    if (!TestKeyData::initKeyFiles()) {
        qCritical() << "Unable to init RSA key files.";
        return ExitCode::RsaKeyError;
    }

    const Telegram::RsaKey privateKey = Telegram::RsaKey::fromFile(TestKeyData::privateKeyFileName());
    if (!privateKey.isValid()) {
        qCritical() << "Unable to read RSA key.";
        return ExitCode::RsaKeyError;
    }

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption configAddressOption(QStringList({ QLatin1String("a"), QLatin1String("address") }));
    configAddressOption.setValueName(QLatin1String("ip"));
    configAddressOption.setDefaultValue(QLatin1String("127.0.0.1"));
    parser.addOption(configAddressOption);

    QCommandLineOption configPortOption(QStringList({ QLatin1String("p"), QLatin1String("port") }));
    configPortOption.setDescription(QLatin1String("first port"));
    configPortOption.setValueName(QLatin1String("port"));
    configPortOption.setDefaultValue(QLatin1String("10443"));
    parser.addOption(configPortOption);

    QCommandLineOption generateDataOption(QStringList({ QLatin1String("g"), QLatin1String("generate") }));
    generateDataOption.setDescription(QLatin1String("Generate some data"));
    parser.addOption(generateDataOption);

    QCommandLineOption dialogsNumberOption(QStringList({ QLatin1String("dialogs-number") }));
    dialogsNumberOption.setDescription(QLatin1String("The number of dialogs"));
    dialogsNumberOption.setValueName(QLatin1String("number"));
    dialogsNumberOption.setDefaultValue(QLatin1String("10"));
    parser.addOption(dialogsNumberOption);

    QCommandLineOption messagesNumberOption(QStringList({ QLatin1String("messages-number") }));
    messagesNumberOption.setDescription(QLatin1String("The number of messages"));
    messagesNumberOption.setValueName(QLatin1String("number"));
    messagesNumberOption.setDefaultValue(QLatin1String("10"));
    parser.addOption(messagesNumberOption);

    QCommandLineOption userOption(QStringList({ QLatin1String("u"), QLatin1String("user") }));
    userOption.setValueName(QLatin1String("phone number"));
    userOption.setDefaultValue(QLatin1String("123456789"));
    parser.addOption(userOption);

    parser.process(a);

    {
        // Validate arguments
        bool ok;
        parser.value(dialogsNumberOption).toInt(&ok);
        if (!ok) {
            qCritical() << "Invalid dialogs number";
            return ExitCode::InvalidArgumentFormat;
        }
        parser.value(messagesNumberOption).toInt(&ok);
        if (!ok) {
            qCritical() << "Invalid messages number";
            return ExitCode::InvalidArgumentFormat;
        }
    }

    Telegram::DcConfiguration dcConfig = Config().serverConfiguration();
    dcConfig.dcOptions.clear();

    for (quint32 i = 0; i < 3; ++i) {
        Telegram::DcOption dcOption;
        dcOption.id = i + 1;
        // Do not raise this TcpOnly flag, because config should have info for all transports
        // (otherwise it is considered invalid in some clients).

        // dcOption.flags = Telegram::DcOption::TcpOnly;
        dcOption.address = parser.value(configAddressOption);
        dcOption.port = static_cast<quint16>(parser.value(configPortOption).toUInt() + i);
        dcConfig.dcOptions.append(dcOption);
    }

    LocalCluster cluster;
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(dcConfig);
    //cluster.setListenAddress(QHostAddress::Any);

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
        return ExitCode::UnableToStartServer;
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

    if (parser.isSet(generateDataOption)) {
        QString userPhone = parser.value(userOption);
        const int dialogsNumber = parser.value(dialogsNumberOption).toInt();
        const int messagesNumber = parser.value(messagesNumberOption).toInt();
        generateDialogs(&cluster, userPhone, dialogsNumber, messagesNumber);
    }

    int retCode = a.exec();
    cluster.stop();

    TestKeyData::cleanupKeyFiles();
    if (retCode) {
        qCritical() << "Internal return code:" << retCode;
        return ExitCode::UnknownError;
    }

    importer.saveData();

    return ExitCode::Ok;
}

int main(int argc, char *argv[])
{
    ExitCode code = internalMain(argc, argv);
    return static_cast<int>(code);
}
