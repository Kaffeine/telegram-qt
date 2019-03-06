/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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
#include "ConnectionApi.hpp"
#include "DataStorage.hpp"
#include "Utils.hpp"
#include "TelegramNamespace.hpp"
#include "CAppInformation.hpp"

#include "Operations/ClientAuthOperation.hpp"

#include "ContactsApi.hpp"
#include "CTcpTransport.hpp"
#include "CTelegramTransport.hpp"
#include "DcConfiguration.hpp"

// Server
#include "TelegramServer.hpp"
#include "RemoteClientConnection.hpp"
#include "TelegramServerUser.hpp"
#include "ServerRpcLayer.hpp"
#include "Session.hpp"
#include "LocalCluster.hpp"

#include <QTest>
#include <QSignalSpy>
#include <QDebug>
#include <QRegularExpression>

#include "keys_data.hpp"
#include "TestAuthProvider.hpp"
#include "TestClientUtils.hpp"
#include "TestServerUtils.hpp"
#include "TestUserData.hpp"
#include "TestUtils.hpp"

using namespace Telegram;

static const UserData c_userWithPassword = []() {
    UserData userData;
    userData.dcId = 1;
    userData.setName(QStringLiteral("First"), QStringLiteral("Last"));
    userData.phoneNumber = QStringLiteral("123456");
    userData.password = QByteArrayLiteral("mypassword");
    userData.setPasswordSalt(QByteArrayLiteral("mysalt"));
    return userData;
}();

class tst_ConnectionApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_ConnectionApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testClientConnection_data();
    void testClientConnection();
    void reconnect();
};

tst_ConnectionApi::tst_ConnectionApi(QObject *parent) :
    QObject(parent)
{
}

void tst_ConnectionApi::initTestCase()
{
    qRegisterMetaType<UserData>();
    QVERIFY(TestKeyData::initKeyFiles());

    if (!qEnvironmentVariableIsSet(BaseTcpTransport::timeoutEnvironmentVariableName())) {
        qputenv(BaseTcpTransport::timeoutEnvironmentVariableName(), QByteArrayLiteral("50"));
    }
    if (!qEnvironmentVariableIsSet(Client::ConnectionApi::reconnectionIntervalsEnvironmentVariableName())) {
        qputenv(Client::ConnectionApi::reconnectionIntervalsEnvironmentVariableName(), QByteArrayLiteral("0,5,5,30,30,60"));
    }
}

void tst_ConnectionApi::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_ConnectionApi::testClientConnection_data()
{
    QTest::addColumn<Telegram::Client::Settings::SessionType>("sessionType");
    QTest::addColumn<UserData>("userData");
    QTest::addColumn<DcOption>("clientDcOption");
    QTest::addColumn<bool>("waitForPhoneRequest");
    UserData userOnDc1 = c_userWithPassword;
    userOnDc1.dcId = 1;
    UserData userOnDc2 = c_userWithPassword;
    userOnDc2.dcId = 2;
    UserData user2OnDc2 = c_userWithPassword;
    user2OnDc2.unsetPassword();
    user2OnDc2.dcId = 2;
    constexpr bool c_waitForPhoneRequest = true;
    constexpr bool c_dontWaitForPhoneRequest = false;

    DcOption opt = c_localDcOptions.first();

    QTest::newRow("Abridged")
            << Client::Settings::SessionType::Abridged
            << userOnDc1
            << opt
            << c_dontWaitForPhoneRequest;

    QTest::newRow("Obfuscated")
            << Client::Settings::SessionType::Obfuscated
            << userOnDc1
            << opt
            << c_dontWaitForPhoneRequest;

    QTest::newRow("Abridged with migration")
            << Client::Settings::SessionType::Abridged
            << userOnDc2
            << opt
            << c_dontWaitForPhoneRequest;

    QTest::newRow("Abridged with migration (wait for phone requested)")
            << Client::Settings::SessionType::Abridged
            << userOnDc2
            << opt
            << c_waitForPhoneRequest;

    QTest::newRow("Obfuscated with migration")
            << Client::Settings::SessionType::Obfuscated
            << userOnDc2
            << opt
            << c_dontWaitForPhoneRequest;

    opt.id = 0;
    QTest::newRow("Migration from unknown dc (with password)")
            << Client::Settings::SessionType::Obfuscated
            << userOnDc2
            << opt
            << c_dontWaitForPhoneRequest;

    QTest::newRow("Migration from unknown dc, no password")
            << Client::Settings::SessionType::Obfuscated
            << user2OnDc2
            << opt
            << c_dontWaitForPhoneRequest;
}

void tst_ConnectionApi::testClientConnection()
{
    QFETCH(Telegram::Client::Settings::SessionType, sessionType);
    QFETCH(UserData, userData);
    QFETCH(DcOption, clientDcOption);
    QFETCH(bool, waitForPhoneRequest);

    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    QVERIFY2(publicKey.isValid(), "Unable to read public RSA key");
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    QVERIFY2(privateKey.isPrivate(), "Unable to read private RSA key");

    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::ServerApi *server = cluster.getServerApiInstance(userData.dcId);
    QVERIFY(server);

    Server::LocalUser *user = tryAddUser(&cluster, userData);
    QVERIFY(user);

    Client::Client client;
    setupClientHelper(&client, userData, publicKey, clientDcOption, sessionType);
    Client::ConnectionApi *connectionApi = client.connectionApi();

    QSignalSpy clientConnectionStatusSpy(connectionApi, &Client::ConnectionApi::statusChanged);
    QCOMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusDisconnected);

    // --- Sign in ---
    Client::AuthOperation *signInOperation = connectionApi->startAuthentication();
    {
        QSignalSpy serverAuthCodeSpy(&authProvider, &Test::AuthProvider::codeSent);
        QSignalSpy authPhoneSpy(signInOperation, &Client::AuthOperation::phoneNumberRequired);
        QSignalSpy authCodeSpy(signInOperation, &Client::AuthOperation::authCodeRequired);

        if (waitForPhoneRequest) {
            TRY_VERIFY(!authPhoneSpy.isEmpty());
            QCOMPARE(authPhoneSpy.count(), 1);
            signInOperation->submitPhoneNumber(userData.phoneNumber);
            QCOMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusWaitForAuthentication);
        } else {
            signInOperation->setPhoneNumber(userData.phoneNumber);
            TRY_COMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusWaitForAuthentication);
        }

        QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusWaitForConnection));
        QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnecting));
        QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusWaitForAuthentication));

        TRY_COMPARE(client.dataStorage()->serverConfiguration().dcOptions, cluster.serverConfiguration().dcOptions);
        TRY_VERIFY(!authCodeSpy.isEmpty());
        QCOMPARE(authCodeSpy.count(), 1);
        QCOMPARE(serverAuthCodeSpy.count(), 1);
        QList<QVariant> authCodeSentArguments = serverAuthCodeSpy.takeFirst();
        QCOMPARE(authCodeSentArguments.count(), 2);
        const QString authCode = authCodeSentArguments.at(1).toString();

        if (!waitForPhoneRequest) {
            QVERIFY(authPhoneSpy.isEmpty());
        }

        clientConnectionStatusSpy.clear();
        signInOperation->submitAuthCode(authCode);
    }

    if (!userData.password.isEmpty()) {
        QSignalSpy authPasswordSpy(signInOperation, &Client::AuthOperation::passwordRequired);
        QSignalSpy passwordCheckFailedSpy(signInOperation, &Client::AuthOperation::passwordCheckFailed);
        TRY_VERIFY2(!authPasswordSpy.isEmpty(), "The user has a password-protection, "
                                                 "but there are no passwordRequired signals on the client side");
        QCOMPARE(authPasswordSpy.count(), 1);
        QVERIFY(passwordCheckFailedSpy.isEmpty());

        signInOperation->submitPassword(userData.password + QStringLiteral("invalid"));
        TRY_VERIFY2(!passwordCheckFailedSpy.isEmpty(), "The submitted password is not valid, "
                                                        "but there are not signals on the client side");
        QVERIFY(!signInOperation->isFinished());
        QCOMPARE(passwordCheckFailedSpy.count(), 1);

        signInOperation->submitPassword(userData.password);
    }
    TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");

    TRY_VERIFY(!clientConnectionStatusSpy.isEmpty());
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnected));

    TRY_VERIFY(!clientConnectionStatusSpy.isEmpty());
    QCOMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusReady);
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusReady));
    QVERIFY(clientConnectionStatusSpy.isEmpty());

    QCOMPARE(client.accountStorage()->phoneNumber(), userData.phoneNumber);
    QCOMPARE(client.accountStorage()->dcInfo().id, server->dcId());
    QCOMPARE(client.accountStorage()->dcInfo().id, userData.dcId);
    QVERIFY(client.contactsApi()->selfContactId());
}

void tst_ConnectionApi::reconnect()
{
    const UserData userData = c_userWithPassword;
    const DcOption clientDcOption = c_localDcOptions.first();

    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    QVERIFY2(publicKey.isValid(), "Unable to read public RSA key");
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    QVERIFY2(privateKey.isValid(), "Unable to read private RSA key");

    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::Server *server = cluster.getServerInstance(userData.dcId);
    QVERIFY(server);

    Server::LocalUser *user = tryAddUser(&cluster, userData);
    QVERIFY(user);

    Client::Client client;
    setupClientHelper(&client, userData, publicKey, clientDcOption);
    Client::ConnectionApi *connectionApi = client.connectionApi();

    QSignalSpy clientConnectionStatusSpy(connectionApi, &Client::ConnectionApi::statusChanged);
    QCOMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusDisconnected);

    // --- Sign in ---
    Client::AuthOperation *signInOperation = connectionApi->startAuthentication();
    signInOperation->setPhoneNumber(userData.phoneNumber);
    QSignalSpy serverAuthCodeSpy(&authProvider, &Test::AuthProvider::codeSent);
    QSignalSpy authCodeSpy(signInOperation, &Client::AuthOperation::authCodeRequired);

    TRY_COMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusWaitForAuthentication);
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusWaitForConnection));
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnecting));
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusWaitForAuthentication));

    TRY_COMPARE(client.dataStorage()->serverConfiguration().dcOptions, cluster.serverConfiguration().dcOptions);
    TRY_VERIFY(!authCodeSpy.isEmpty());
    QCOMPARE(authCodeSpy.count(), 1);
    QCOMPARE(serverAuthCodeSpy.count(), 1);
    QList<QVariant> authCodeSentArguments = serverAuthCodeSpy.takeFirst();
    QCOMPARE(authCodeSentArguments.count(), 2);
    const QString authCode = authCodeSentArguments.at(1).toString();

    signInOperation->submitAuthCode(authCode);

    if (!userData.password.isEmpty()) {
        QSignalSpy authPasswordSpy(signInOperation, &Client::AuthOperation::passwordRequired);
        QSignalSpy passwordCheckFailedSpy(signInOperation, &Client::AuthOperation::passwordCheckFailed);
        TRY_VERIFY2(!authPasswordSpy.isEmpty(), "The user has a password-protection, "
                                                 "but there are no passwordRequired signals on the client side");
        QCOMPARE(authPasswordSpy.count(), 1);
        QVERIFY(passwordCheckFailedSpy.isEmpty());

        signInOperation->submitPassword(userData.password + QStringLiteral("invalid"));
        TRY_VERIFY2(!passwordCheckFailedSpy.isEmpty(), "The submitted password is not valid, "
                                                        "but there are not signals on the client side");
        QVERIFY(!signInOperation->isFinished());
        QCOMPARE(passwordCheckFailedSpy.count(), 1);

        signInOperation->submitPassword(userData.password);
    }
    TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");

    TRY_VERIFY(!clientConnectionStatusSpy.isEmpty());
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnected));

    TRY_VERIFY(!clientConnectionStatusSpy.isEmpty());
    QCOMPARE(connectionApi->status(), Telegram::Client::ConnectionApi::StatusReady);
    QCOMPARE(clientConnectionStatusSpy.takeFirst().first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusReady));
    QVERIFY(clientConnectionStatusSpy.isEmpty());

    QCOMPARE(client.accountStorage()->phoneNumber(), userData.phoneNumber);
    QCOMPARE(client.accountStorage()->dcInfo().id, server->dcId());
    QCOMPARE(client.accountStorage()->dcInfo().id, userData.dcId);
    QCOMPARE(user->activeSessions().count(), 1);
    Server::Session *activeSession = user->activeSessions().first();
    QVERIFY(activeSession);
    Telegram::BaseTransport *serverSideTransport = activeSession->getConnection()->transport();
    QVERIFY(serverSideTransport);

    QVERIFY(clientConnectionStatusSpy.isEmpty());
    // Brutal disconnect from server side
    serverSideTransport->disconnectFromHost();

    TRY_VERIFY(!clientConnectionStatusSpy.isEmpty());
    {
        QVariantList firstSignal = clientConnectionStatusSpy.takeFirst();
        QCOMPARE(firstSignal.first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnecting));
        //QCOMPARE(firstSignal.last().value<int>(), static_cast<int>(Client::ConnectionApi::StatusReasonRemote));
    }

    TRY_COMPARE(connectionApi->status(), Client::ConnectionApi::StatusReady);
    QVERIFY(!clientConnectionStatusSpy.isEmpty());
    {
        QVariantList interestingSignal = clientConnectionStatusSpy.takeLast();
        QCOMPARE(interestingSignal.first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusReady));
        interestingSignal = clientConnectionStatusSpy.takeLast();
        QCOMPARE(interestingSignal.first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnected));
        clientConnectionStatusSpy.clear();
    }

    server->stop();

    constexpr int c_minReconnectSignals = 4;
    TRY_VERIFY(clientConnectionStatusSpy.count() >= c_minReconnectSignals);
    {
        qDebug() << clientConnectionStatusSpy.mid(clientConnectionStatusSpy.count() - c_minReconnectSignals);

        QVariantList firstSignal = clientConnectionStatusSpy.takeFirst();
        QCOMPARE(firstSignal.first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnecting));
        QCOMPARE(firstSignal.last().value<int>(), static_cast<int>(Client::ConnectionApi::StatusReasonRemote));
        clientConnectionStatusSpy.clear();
    }

    QVERIFY(server->start());

    TRY_COMPARE(connectionApi->status(), Client::ConnectionApi::StatusReady);
    QVERIFY(!clientConnectionStatusSpy.isEmpty());
    {
        QVariantList interestingSignal = clientConnectionStatusSpy.takeLast();
        QCOMPARE(interestingSignal.first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusReady));
        interestingSignal = clientConnectionStatusSpy.takeLast();
        QCOMPARE(interestingSignal.first().value<int>(), static_cast<int>(Client::ConnectionApi::StatusConnected));
        clientConnectionStatusSpy.clear();
    }
}

QTEST_GUILESS_MAIN(tst_ConnectionApi)

#include "tst_ConnectionApi.moc"
