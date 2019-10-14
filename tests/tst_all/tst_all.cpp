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
#include "ConnectionApi.hpp"
#include "ConnectionError.hpp"
#include "ContactsApi.hpp"
#include "DataStorage.hpp"
#include "Utils.hpp"
#include "TelegramNamespace.hpp"
#include "CAppInformation.hpp"

#include "Operations/ClientAuthOperation.hpp"

#include "ContactList.hpp"
#include "ContactsApi.hpp"
#include "AuthService.hpp"
#include "DefaultAuthorizationProvider.hpp"
#include "TelegramServer.hpp"
#include "RemoteClientConnection.hpp"
#include "TelegramServerUser.hpp"
#include "ServerRpcLayer.hpp"
#include "Session.hpp"
#include "DcConfiguration.hpp"
#include "LocalCluster.hpp"

#include <QLoggingCategory>
#include <QTest>
#include <QSignalSpy>
#include <QRegularExpression>
#include <QTemporaryFile>

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

class tst_all : public QObject
{
    Q_OBJECT
public:
    explicit tst_all(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSignIn_data();
    void testSignIn();
    void testCheckInSignIn();
    void testSignInCheckIn();
    void testSignUp_data();
    void testSignUp();
};

tst_all::tst_all(QObject *parent) :
    QObject(parent)
{
}

void tst_all::initTestCase()
{
    qRegisterMetaType<UserData>();
    Telegram::initialize();
    QVERIFY(TestKeyData::initKeyFiles());
    QLoggingCategory::setFilterRules("telegram.server.rpclayer.dump.debug=true");
}

void tst_all::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_all::testSignIn_data()
{
    QTest::addColumn<Telegram::Client::Settings::SessionType>("sessionType");
    QTest::addColumn<UserData>("userData");
    QTest::addColumn<DcOption>("clientDcOption");
    UserData userOnDc1 = c_userWithPassword;
    userOnDc1.dcId = 1;
    UserData userOnDc2 = c_userWithPassword;
    userOnDc2.dcId = 2;
    UserData user2OnDc2 = c_userWithPassword;
    user2OnDc2.unsetPassword();
    user2OnDc2.dcId = 2;

    DcOption opt = c_localDcOptions.first();

    QTest::newRow("Abridged")   << Client::Settings::SessionType::Abridged
                                << userOnDc1
                                << opt;
    QTest::newRow("Obfuscated") << Client::Settings::SessionType::Obfuscated
                                << userOnDc1
                                << opt;
    QTest::newRow("Abridged with migration")   << Client::Settings::SessionType::Abridged
                                               << userOnDc2
                                               << opt;
    QTest::newRow("Obfuscated with migration") << Client::Settings::SessionType::Obfuscated
                                               << userOnDc2
                                               << opt;

    opt.id = 0;
    QTest::newRow("Migration from unknown dc (with password)") << Client::Settings::SessionType::Obfuscated
                                               << userOnDc2
                                               << opt;
    QTest::newRow("Migration from unknown dc, no password") << Client::Settings::SessionType::Obfuscated
                                               << user2OnDc2
                                               << opt;
}

void tst_all::testSignIn()
{
    QFETCH(Telegram::Client::Settings::SessionType, sessionType);
    QFETCH(UserData, userData);
    QFETCH(DcOption, clientDcOption);

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

    Server::Server *server = cluster.getServerInstance(userData.dcId);
    QVERIFY(server);

    Server::LocalUser *user = tryAddUser(&cluster, userData);
    QVERIFY(user);

    Client::Client client;
    Test::setupClientHelper(&client, userData, publicKey, clientDcOption, sessionType);

    Client::AccountStorage *accountStorage = client.accountStorage();
    Client::DataStorage *dataStorage = client.dataStorage();

    QTest::ignoreMessage(QtDebugMsg,
                         QRegularExpression(QString::fromLatin1(Server::RpcLayer::gzipPackMessage())
                                            + QStringLiteral(" .* \"Config\"")));

    // --- Sign in ---
    QSignalSpy accountStorageSynced(accountStorage, &Client::AccountStorage::synced);
    Client::AuthOperation *signInOperation = client.connectionApi()->startAuthentication();
    signInOperation->setPhoneNumber(userData.phoneNumber);
    QSignalSpy serverAuthCodeSpy(&authProvider, &Test::AuthProvider::codeSent);
    QSignalSpy authCodeSpy(signInOperation, &Client::AuthOperation::authCodeRequired);
    TRY_COMPARE(client.connectionApi()->status(), Client::ConnectionApi::StatusWaitForAuthentication);
    TRY_COMPARE(dataStorage->serverConfiguration().dcOptions, cluster.serverConfiguration().dcOptions);
    TRY_VERIFY(!authCodeSpy.isEmpty());
    QCOMPARE(signInOperation->isRegistered(), true);
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
    TRY_VERIFY(!accountStorageSynced.isEmpty());

    quint64 clientAuthId = accountStorage->authId();
    QVERIFY(clientAuthId);
    QSet<Server::RemoteClientConnection*> clientConnections = server->getConnections();
    QCOMPARE(clientConnections.count(), 1);
    Server::RemoteClientConnection *remoteClientConnection = *clientConnections.cbegin();
    QCOMPARE(remoteClientConnection->authId(), clientAuthId);
    QVERIFY(remoteClientConnection->session());
    Server::Session *serverSession = server->getSessionById(remoteClientConnection->session()->id());
    QCOMPARE(remoteClientConnection->session(), serverSession);
    QVERIFY(serverSession);
    QVERIFY(serverSession->userId());
    QCOMPARE(accountStorage->phoneNumber(), userData.phoneNumber);
    QCOMPARE(accountStorage->dcInfo().id, server->dcId());
    TRY_VERIFY(client.isSignedIn());
}

void tst_all::testCheckInSignIn()
{
    const Telegram::Client::Settings::SessionType sessionType = Telegram::Client::Settings::SessionType::Obfuscated;
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

    Server::Server *server = qobject_cast<Server::Server*>(cluster.getServerInstance(userData.dcId));
    QVERIFY(server);

    Server::LocalUser *user = tryAddUser(&cluster, userData);
    QVERIFY(user);

    Client::Client client;
    Test::setupClientHelper(&client, userData, publicKey, clientDcOption, sessionType);

    Client::AccountStorage *accountStorage = client.accountStorage();
    Client::DataStorage *dataStorage = client.dataStorage();

    const QByteArray c_authKey = QByteArrayLiteral("some_auth_key_data_123456789_abcdefghijklmnopqrstuvwxyz");
    const quint64 c_authId = Utils::getFingerprints(c_authKey, Utils::Lower64Bits);

    accountStorage->setAuthKey(c_authKey);
    accountStorage->setAuthId(c_authId);
    accountStorage->setSessionId(c_authId);
    accountStorage->setPhoneNumber(userData.phoneNumber);
    accountStorage->setDcInfo(clientDcOption);
    QVERIFY(accountStorage->hasMinimalDataSet());

    // --- Check in ---
    QSignalSpy accountStorageSynced(accountStorage, &Client::AccountStorage::synced);

    static const QString errorText = ConnectionError(ConnectionError::InvalidAuthKey).description();
    QTest::ignoreMessage(QtWarningMsg, QRegularExpression(errorText));

    Client::AuthOperation *checkInOperation = client.connectionApi()->checkIn();
    QSignalSpy checkInFinishedSpy(checkInOperation, &Client::AuthOperation::finished);
    QSignalSpy checkInFailedSpy(checkInOperation, &Client::AuthOperation::failed);
    TRY_COMPARE(checkInFinishedSpy.count(), 1);
    TRY_COMPARE(checkInFailedSpy.count(), 1);

    Client::AuthOperation *signInOperation = client.connectionApi()->startAuthentication();
    QSignalSpy authErrorSpy(signInOperation, &Client::AuthOperation::errorOccurred);
    QSignalSpy serverAuthCodeSpy(&authProvider, &Test::AuthProvider::codeSent);
    QSignalSpy authCodeSpy(signInOperation, &Client::AuthOperation::authCodeRequired);

    signInOperation->setPhoneNumber(userData.phoneNumber);
    // Check whether the server configuration is synced to the client data storage
    TRY_VERIFY(!dataStorage->serverConfiguration().dcOptions.isEmpty());
    TRY_COMPARE(dataStorage->serverConfiguration().dcOptions, cluster.serverConfiguration().dcOptions);
    TRY_VERIFY(!authCodeSpy.isEmpty());
    QCOMPARE(authCodeSpy.count(), 1);
    QCOMPARE(serverAuthCodeSpy.count(), 1);
    QList<QVariant> authCodeSentArguments = serverAuthCodeSpy.takeFirst();
    QCOMPARE(authCodeSentArguments.count(), 2);
    const QString authCode = authCodeSentArguments.at(1).toString();

    QCOMPARE(authErrorSpy.count(), 0);
    signInOperation->submitAuthCode(QString(authCode.size(), QLatin1Char('0')));
    TRY_VERIFY(!authErrorSpy.isEmpty());
    QCOMPARE(authErrorSpy.count(), 1);
    QCOMPARE(authErrorSpy.takeFirst().constFirst().value<Namespace::AuthenticationError>(),
             Namespace::AuthenticationErrorPhoneCodeInvalid);

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
    TRY_VERIFY(!accountStorageSynced.isEmpty());

    quint64 clientAuthId = accountStorage->authId();
    QVERIFY(clientAuthId);
    const quint32 clientUserId = server->authService()->getUserIdByAuthId(clientAuthId);
    QVERIFY(clientUserId);

    Telegram::Server::LocalUser *serverSideUser = server->getUser(clientUserId);
    QVERIFY(serverSideUser);
    QCOMPARE(serverSideUser->phoneNumber(), userData.phoneNumber);
    QCOMPARE(accountStorage->phoneNumber(), userData.phoneNumber);
    QCOMPARE(accountStorage->dcInfo().id, server->dcId());
    TRY_VERIFY(client.isSignedIn());
}

void tst_all::testSignInCheckIn()
{
    const Telegram::Client::Settings::SessionType sessionType = Telegram::Client::Settings::SessionType::Obfuscated;
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

    Server::LocalUser *serversideUser = tryAddUser(&cluster, userData);
    QVERIFY(serversideUser);

    Client::AccountStorage accountStorage;
    accountStorage.setPhoneNumber(userData.phoneNumber);
    accountStorage.setDcInfo(clientDcOption);

    {
        Client::Client client;
        Test::setupClientHelper(&client, userData, publicKey, clientDcOption, sessionType);
        client.setAccountStorage(&accountStorage);

        Client::AuthOperation *signInOperation = nullptr;
        signInHelper(&client, userData, &authProvider, &signInOperation);
        TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");

        QSet<Server::RemoteClientConnection*> clientConnections = server->getConnections();
        QCOMPARE(clientConnections.count(), 1);
//        PendingOperation *discOp = client.connectionApi()->disconnectFromHost();
//        TRY_VERIFY(discOp->isFinished());
//        QCOMPARE(discOp->isSucceeded(), true);

        TRY_COMPARE(client.connectionApi()->status(), Client::ConnectionApi::StatusReady);
        QVERIFY(client.contactsApi()->selfUserId());
        QCOMPARE(client.contactsApi()->selfUserId(), serversideUser->id());
    }

    TRY_VERIFY(server->getConnections().isEmpty());

    // Reconnect
    {
        Client::Client client;
        Test::setupClientHelper(&client, userData, publicKey, clientDcOption, sessionType);
        client.setAccountStorage(&accountStorage);

        Client::AuthOperation *checkInOperation = client.connectionApi()->checkIn();
        TRY_VERIFY2(checkInOperation->isFinished(), "checkIn() not finished");
        QVERIFY2(checkInOperation->isSucceeded(), "checkIn() failed");

        TRY_COMPARE(client.connectionApi()->status(), Client::ConnectionApi::StatusReady);
        QVERIFY(client.contactsApi()->selfUserId());
        QCOMPARE(client.contactsApi()->selfUserId(), serversideUser->id());
    }
}

void tst_all::testSignUp_data()
{
    QTest::addColumn<UserData>("userData");

    UserData user2OnDc2 = c_userWithPassword;
    user2OnDc2.unsetPassword();
    user2OnDc2.dcId = 2;

    QTest::newRow("Valid user") << user2OnDc2;
}

void tst_all::testSignUp()
{
    QFETCH(UserData, userData);
    const DcOption clientDcOption = c_localDcOptions.first();

    const Telegram::Client::Settings::SessionType sessionType = Telegram::Client::Settings::SessionType::Obfuscated;
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

    Server::Server *server = qobject_cast<Server::Server*>(cluster.getServerInstance(1));
    QVERIFY(server);

    Client::Client client;
    Test::setupClientHelper(&client, userData, publicKey, clientDcOption, sessionType);

    Client::AccountStorage *accountStorage = client.accountStorage();
    Client::DataStorage *dataStorage = client.dataStorage();

    QTest::ignoreMessage(QtDebugMsg,
                         QRegularExpression(QString::fromLatin1(Server::RpcLayer::gzipPackMessage())
                                            + QStringLiteral(" .* \"Config\"")));

    // --- Sign up ---
    QSignalSpy accountStorageSynced(accountStorage, &Client::AccountStorage::synced);
    Client::AuthOperation *signUpOperation = client.connectionApi()->startAuthentication();
    signUpOperation->setPhoneNumber(userData.phoneNumber);
    QSignalSpy serverAuthCodeSpy(&authProvider, &Test::AuthProvider::codeSent);
    QSignalSpy authCodeSpy(signUpOperation, &Client::AuthOperation::authCodeRequired);
    QSignalSpy registrationStatusSpy(signUpOperation, &Client::AuthOperation::registeredChanged);
    TRY_COMPARE(dataStorage->serverConfiguration().dcOptions, cluster.serverConfiguration().dcOptions);
    TRY_VERIFY(!authCodeSpy.isEmpty());
    QCOMPARE(authCodeSpy.count(), 1);
    QCOMPARE(serverAuthCodeSpy.count(), 1);
    QCOMPARE(registrationStatusSpy.count(), 1);
    QCOMPARE(signUpOperation->isRegistered(), false);
    QCOMPARE(registrationStatusSpy.takeFirst().first().toBool(), false);
    QList<QVariant> authCodeSentArguments = serverAuthCodeSpy.takeFirst();
    QCOMPARE(authCodeSentArguments.count(), 2);
    const QString authCode = authCodeSentArguments.at(1).toString();

    signUpOperation->submitName(userData.firstName, userData.lastName);
    signUpOperation->submitAuthCode(authCode);
    TRY_VERIFY2(signUpOperation->isSucceeded(), "Unexpected sign in fail");
    TRY_VERIFY(!accountStorageSynced.isEmpty());

    quint64 clientAuthId = accountStorage->authId();
    QVERIFY(clientAuthId);
    QSet<Server::RemoteClientConnection*> clientConnections = server->getConnections();
    QCOMPARE(clientConnections.count(), 1);
    Server::RemoteClientConnection *remoteClientConnection = *clientConnections.cbegin();
    QCOMPARE(remoteClientConnection->authId(), clientAuthId);
    quint32 clientUserId = server->authService()->getUserIdByAuthId(clientAuthId);
    QVERIFY(clientUserId);
    Telegram::Server::LocalUser *serverSideUser = server->getUser(clientUserId);
    QVERIFY(serverSideUser);
    QCOMPARE(serverSideUser->firstName(), userData.firstName);
    QCOMPARE(serverSideUser->lastName(), userData.lastName);
    QCOMPARE(serverSideUser->phoneNumber(), userData.phoneNumber);
    QCOMPARE(accountStorage->phoneNumber(), userData.phoneNumber);
    QCOMPARE(accountStorage->dcInfo().id, server->dcId());
    TRY_VERIFY(client.isSignedIn());
}

QTEST_GUILESS_MAIN(tst_all)

#include "tst_all.moc"
