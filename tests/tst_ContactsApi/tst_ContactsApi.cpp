/*
   Copyright (C) 2020 Alexandr Akulich <akulichalexander@gmail.com>

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

// Client
#include "AccountStorage.hpp"
#include "Client.hpp"
#include "ConnectionApi.hpp"
#include "ContactList.hpp"
#include "ContactsApi.hpp"
#include "DataStorage.hpp"
#include "DcConfiguration.hpp"
#include "RandomGenerator.hpp"
#include "TelegramNamespace.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/PendingContactsOperation.hpp"

// Server
#include "LocalCluster.hpp"
#include "MessageService.hpp"
#include "ServerApi.hpp"
#include "ServerUtils.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"

// Test
#include "TestAuthProvider.hpp"
#include "TestClientUtils.hpp"
#include "TestServerUtils.hpp"
#include "TestUserData.hpp"
#include "TestUtils.hpp"
#include "keys_data.hpp"

#include <QCryptographicHash>
#include <QDebug>
#include <QRegularExpression>
#include <QSignalSpy>
#include <QTest>

using namespace Telegram;

static const UserData c_user1 = mkUserData(1000, 1);
static const UserData c_user2 = mkUserData(2000, 1);

class tst_ContactsApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_ContactsApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();

    void addContact();
};

tst_ContactsApi::tst_ContactsApi(QObject *parent) :
    QObject(parent)
{
}

void tst_ContactsApi::initTestCase()
{
    Telegram::initialize();
    QVERIFY(TestKeyData::initKeyFiles());
}

void tst_ContactsApi::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_ContactsApi::addContact()
{
    // Generic test data
    const UserData user1Data = c_user1;
    const UserData user2Data = c_user2;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());

    // Prepare the server
    Test::AuthProvider authProvider;
    Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user1 = tryAddUser(&cluster, user1Data);
    Server::LocalUser *user2 = tryAddUser(&cluster, user2Data);
    QVERIFY(user1 && user2);

    // Prepare clients
    Client::Client client1;
    {
        Test::setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation1 = nullptr;
        signInHelper(&client1, user1Data, &authProvider, &signInOperation1);
        TRY_VERIFY2(signInOperation1->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client1.accountStorage()->phoneNumber(), user1Data.phoneNumber);
    }
    TRY_VERIFY(client1.isSignedIn());

    Client::Client client2;
    {
        Test::setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation2 = nullptr;
        signInHelper(&client2, user2Data, &authProvider, &signInOperation2);
        TRY_VERIFY2(signInOperation2->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client2.accountStorage()->phoneNumber(), user2Data.phoneNumber);
    }
    TRY_VERIFY(client2.isSignedIn());

    Client::ContactList *client1ContactList = client1.contactsApi()->getContactList();
    {
        PendingOperation *contactListReadyOperation = client1ContactList->becomeReady();
        TRY_VERIFY(contactListReadyOperation->isFinished());
        QVERIFY(contactListReadyOperation->isSucceeded());
        QVERIFY(client1ContactList->list().isEmpty());
    }

    {
        QSignalSpy contactsSpy(client1ContactList, &Client::ContactList::listChanged);
        Client::ContactsApi::ContactInfo user2ContactInfo;
        user2ContactInfo.phoneNumber = user2->phoneNumber();
        user2ContactInfo.firstName   = user2->firstName();
        user2ContactInfo.lastName    = user2->lastName();
        Client::PendingContactsOperation *addContactOperation = client1.contactsApi()->addContacts({user2ContactInfo});
        TRY_VERIFY(addContactOperation->isFinished());
        QVERIFY(addContactOperation->isSucceeded());
        QCOMPARE(contactsSpy.count(), 1);

        QCOMPARE(client1.dataStorage()->contactList().count(), 1);

        QCOMPARE(client1ContactList->list().count(), 1);
        QCOMPARE(client1ContactList->list().first(), user2->id());
    }
}

QTEST_GUILESS_MAIN(tst_ContactsApi)

#include "tst_ContactsApi.moc"
