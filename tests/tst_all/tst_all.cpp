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

#include <QObject>

#include "AccountStorage.hpp"
#include "Client.hpp"
#include "ClientSettings.hpp"
#include "Utils.hpp"
#include "TelegramNamespace.hpp"
#include "CAppInformation.hpp"

#include "TelegramServer.hpp"
#include "TelegramServerClient.hpp"
#include "TelegramServerUser.hpp"
#include "CTelegramCore.hpp"

#include <QTest>
#include <QSignalSpy>
#include <QDebug>

#include "keys_data.hpp"

#define CLIENT_WORKS

using namespace Telegram;

CAppInformation *getAppInfo()
{
    static CAppInformation *appInfo = nullptr;
    if (!appInfo) {
        appInfo = new CAppInformation();
        appInfo->setAppId(14617);
        appInfo->setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
        appInfo->setAppVersion(QLatin1String("0.1"));
        appInfo->setDeviceInfo(QLatin1String("pc"));
        appInfo->setOsInfo(QLatin1String("GNU/Linux"));
        appInfo->setLanguageCode(QLatin1String("en"));
    }
    return appInfo;
}

class tst_all : public QObject
{
    Q_OBJECT
public:
    explicit tst_all(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testClientConnection();

};

tst_all::tst_all(QObject *parent) :
    QObject(parent)
{
}

void tst_all::initTestCase()
{
    QVERIFY(TestKeyData::initKeyFiles());
}

void tst_all::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

class TestServer : public Server::Server
{
    Q_OBJECT
public:
    QString sendAppCode(const QString &identifier) override
    {
        const QString hash = Server::Server::sendAppCode(identifier);
        const Telegram::Server::AuthCode c = m_sentCodeMap.value(identifier);
        emit authCodeSent(identifier, c.code);
        return hash;
    }

signals:
    void authCodeSent(const QString &identifier, const QString &code);
};

void tst_all::testClientConnection()
{
    const QString phoneNumber = QStringLiteral("123456");
    const QByteArray password = QByteArrayLiteral("mypassword");
    const QByteArray pwdSalt = QByteArrayLiteral("mysalt");
    const QByteArray pwdData = pwdSalt + password + pwdSalt;
    const QByteArray pwdHash = Utils::sha256(pwdData);

    TelegramNamespace::registerTypes();
    TestServer server;
    DcOption option;
    option.address = QStringLiteral("127.0.0.1");
    option.port = 11443;
    option.id = 1;
    const RsaKey privateKey = Utils::loadRsaPrivateKeyFromFile(TestKeyData::privateKeyFileName());
    QVERIFY2(privateKey.isValid(), "Unable to read private RSA key");
    server.setServerPrivateRsaKey(privateKey);
    server.setDcOption(option);
    Server::User *serverUser = server.addUser(phoneNumber);
    serverUser->setFirstName("First");
    serverUser->setLastName("Last");
    serverUser->setPassword(pwdSalt, pwdHash);
    QVERIFY(server.start());

    const RsaKey publicKey = Utils::loadRsaKeyFromFile(TestKeyData::publicKeyFileName());
    QVERIFY2(publicKey.isValid(), "Unable to read public RSA key");
#ifdef CLIENT_WORKS
    Client::Client client;
    Client::AccountStorage accountStorage;
    Client::Settings clientSettings;
    client.setAppInformation(getAppInfo());
    client.setSettings(&clientSettings);
    client.setAccountStorage(&accountStorage);
    accountStorage.setPhoneNumber(phoneNumber);
#else
    CTelegramCore client;
    client.setAppInformation(getAppInfo());
    CTelegramCore &clientSettings = client;
#endif
    QVERIFY(clientSettings.setServerConfiguration({DcOption(option.address, option.port, option.id)}));
    QVERIFY(clientSettings.setServerRsaKey(publicKey));

    // --- Connect ---
#ifdef CLIENT_WORKS
    PendingOperation *connectOperation = client.connectToServer();
    QTRY_VERIFY(connectOperation->isSucceeded());
    quint64 clientAuthId = accountStorage.authId();
#else
    quint64 clientAuthId = client.authKeyId();
    QVERIFY(client.connectToServer());
    QTRY_COMPARE_WITH_TIMEOUT(client.connectionState(), TelegramNamespace::ConnectionStateConnected, 500);
#endif
    QVERIFY(clientAuthId);

    QSet<Server::RemoteClientConnection*> clientConnections = server.getConnections();
    QCOMPARE(clientConnections.count(), 1);
    Server::RemoteClientConnection *remoteClientConnection = *clientConnections.cbegin();
    QCOMPARE(remoteClientConnection->authId(), clientAuthId);

    // --- Sign in ---
    Client::PendingAuthOperation *signInOperation = client.signIn();

    QSignalSpy serverAuthCodeSpy(&server, &TestServer::authCodeSent);

    QSignalSpy authCodeSpy(signInOperation, &Client::PendingAuthOperation::authCodeRequired);
    QTRY_VERIFY(!authCodeSpy.isEmpty());
    QCOMPARE(authCodeSpy.count(), 1);
    QCOMPARE(serverAuthCodeSpy.count(), 1);
    QList<QVariant> authCodeSentArguments = serverAuthCodeSpy.takeFirst();
    QCOMPARE(authCodeSentArguments.count(), 2);
    const QString authCode = authCodeSentArguments.at(1).toString();

    signInOperation->submitAuthCode(authCode);

    QSignalSpy authPasswordSpy(signInOperation, &Client::PendingAuthOperation::passwordRequired);
    QSignalSpy passwordCheckFailedSpy(signInOperation, &Client::PendingAuthOperation::passwordCheckFailed);
    QTRY_VERIFY(!authPasswordSpy.isEmpty());
    QCOMPARE(authPasswordSpy.count(), 1);
    QVERIFY(passwordCheckFailedSpy.isEmpty());

    PendingOperation *op = signInOperation->getPassword();
    QTRY_VERIFY(op->isFinished());

    signInOperation->submitPassword(password + QStringLiteral("invalid"));
    QTRY_VERIFY(!passwordCheckFailedSpy.isEmpty());
    QVERIFY(!signInOperation->isFinished());
    QCOMPARE(passwordCheckFailedSpy.count(), 1);

    signInOperation->submitPassword(password);
    QTRY_VERIFY(signInOperation->isSucceeded());
}

QTEST_GUILESS_MAIN(tst_all)

#include "tst_all.moc"
