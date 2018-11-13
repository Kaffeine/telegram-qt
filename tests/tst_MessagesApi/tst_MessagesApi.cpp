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
#include "Operations/PendingContactsOperation.hpp"

#include "ContactList.hpp"
#include "ContactsApi.hpp"
#include "DialogList.hpp"
#include "TelegramServerClient.hpp"
#include "TelegramServerUser.hpp"
#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "DcConfiguration.hpp"
#include "LocalCluster.hpp"
#include "MessagingApi.hpp"

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

static const UserData c_user2 = []() {
    UserData userData;
    userData.dcId = 1;
    userData.setName(QStringLiteral("First2"), QStringLiteral("Last2"));
    userData.phoneNumber = QStringLiteral("123457");
    return userData;
}();

class tst_MessagesApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_MessagesApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void getDialogs();
};

tst_MessagesApi::tst_MessagesApi(QObject *parent) :
    QObject(parent)
{
}

void tst_MessagesApi::initTestCase()
{
    qRegisterMetaType<UserData>();
    QVERIFY(TestKeyData::initKeyFiles());
}

void tst_MessagesApi::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_MessagesApi::getDialogs()
{
    const UserData user1Data = c_userWithPassword;
    const UserData user2Data = c_user2;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = Utils::loadRsaKeyFromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = Utils::loadRsaPrivateKeyFromFile(TestKeyData::privateKeyFileName());

    // Prepare server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::ServerApi *server = cluster.getServerApiInstance(user1Data.dcId);
    QVERIFY(server);

    Server::User *user1 = tryAddUser(&cluster, user1Data);
    Server::User *user2 = tryAddUser(&cluster, user2Data);
    QVERIFY(user1 && user2);

    // Prepare clients
    Client::Client client1;
    {
        setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation1 = nullptr;
        signInHelper(&client1, user1Data, &authProvider, &signInOperation1);
        TRY_VERIFY2(signInOperation1->isSucceeded(), "Unexpected sign in fail");
        quint64 client1AuthId = client1.accountStorage()->authId();
        QVERIFY(client1AuthId);
        Server::Session *serverSession1 = server->getSessionByAuthId(client1AuthId);
        QVERIFY(serverSession1);
        QCOMPARE(client1.accountStorage()->phoneNumber(), user1Data.phoneNumber);
        QCOMPARE(client1.accountStorage()->dcInfo().id, server->dcId());
    }
    TRY_VERIFY(client1.isSignedIn());

    Client::Client client2;
    {
        setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation2 = nullptr;
        signInHelper(&client2, user2Data, &authProvider, &signInOperation2);
        TRY_VERIFY2(signInOperation2->isSucceeded(), "Unexpected sign in fail");
        quint64 client2AuthId = client2.accountStorage()->authId();
        QVERIFY(client2AuthId);
        Server::Session *serverSession2 = server->getSessionByAuthId(client2AuthId);
        QVERIFY(serverSession2);
        QCOMPARE(client2.accountStorage()->phoneNumber(), user2Data.phoneNumber);
        QCOMPARE(client2.accountStorage()->dcInfo().id, server->dcId());
    }
    TRY_VERIFY(client2.isSignedIn());

    Telegram::Peer client2AsClient1Peer;
    Telegram::Peer client1AsClient2Peer;

    // Everyone is online. Setup contacts
    Telegram::Client::ContactList *client1ContactList = client1.contactsApi()->getContactList();
    Telegram::Client::DialogList *client2DialogList = client2.messagingApi()->getDialogList();
    {
        Telegram::Client::ContactsApi::ContactInfo user2ContactInfo;
        user2ContactInfo.phoneNumber = user2->phoneNumber();
        user2ContactInfo.firstName   = user2->firstName();
        user2ContactInfo.lastName    = user2->lastName();
        Telegram::Client::PendingContactsOperation *addContactOperation = client1.contactsApi()->addContacts({user2ContactInfo});
        TRY_VERIFY(addContactOperation->isFinished());
        QVERIFY(addContactOperation->isSucceeded());

        QCOMPARE(addContactOperation->peers().count(), 1);
        client2AsClient1Peer = addContactOperation->peers().first();
        QVERIFY(client2AsClient1Peer.isValid());
        PendingOperation *contactListReadyOperation = client1ContactList->becomeReady();
        TRY_VERIFY(contactListReadyOperation->isFinished());
        QVERIFY(contactListReadyOperation->isSucceeded());
        QCOMPARE(client1ContactList->peers().count(), 1);
        QCOMPARE(client1ContactList->peers().first().toString(), client2AsClient1Peer.toString());
    }
    {
        PendingOperation *dialogListReadyOperation = client2DialogList->becomeReady();
        TRY_VERIFY(dialogListReadyOperation->isFinished());
        QVERIFY(dialogListReadyOperation->isSucceeded());
    }

    const QString c_message1Text = QStringLiteral("Hello");
    const QString c_message2Text = QStringLiteral("Hi back");

    QSignalSpy client1MessageSentSpy(client1.messagingApi(), &Client::MessagingApi::messageSent);
    QSignalSpy client2MessageSentSpy(client2.messagingApi(), &Client::MessagingApi::messageSent);
    QSignalSpy client1MessageReceivedSpy(client1.messagingApi(), &Client::MessagingApi::messageReceived);
    QSignalSpy client2MessageReceivedSpy(client2.messagingApi(), &Client::MessagingApi::messageReceived);
    QSignalSpy client2DialogListChangedSpy(client2DialogList, &Client::DialogList::listChanged);

    // Check sent
    {
        quint64 sentMessageId = client1.messagingApi()->sendMessage(client2AsClient1Peer, c_message1Text);
        TRY_COMPARE(client1MessageSentSpy.count(), 1);
        QList<QVariant> sentArgs = client1MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 2); // messageSent has 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.first().value<quint64>(), sentMessageId);
        QVERIFY(sentArgs.last().value<quint32>());
    }

    // Check received
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        client1AsClient2Peer = receivedArgs.first().value<Telegram::Peer>();

        quint32 receivedMessageId = receivedArgs.last().toUInt();
        QVERIFY(receivedMessageId);
        Telegram::Message messageData;
        client2.dataStorage()->getMessage(&messageData, client1AsClient2Peer, receivedMessageId);
        QCOMPARE(messageData.text, c_message1Text);
    }

    // Check dialog added
    {
        TRY_COMPARE(client2DialogListChangedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2DialogListChangedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // listChanged has 'added' and 'removed' args
        Telegram::PeerList added = receivedArgs.first().value<Telegram::PeerList>();
        QCOMPARE(added.count(), 1);
        QCOMPARE(added.first(), client1AsClient2Peer);
    }

    // Check sent
    {
        quint64 sentMessageId = client2.messagingApi()->sendMessage(client1AsClient2Peer, c_message2Text);
        TRY_COMPARE(client2MessageSentSpy.count(), 1);
        QList<QVariant> sentArgs = client2MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 2); // messageSent has 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.first().value<quint64>(), sentMessageId);
        QVERIFY(sentArgs.last().value<quint32>());
    }

    // Check received
    {
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Telegram::Peer fromPeer = receivedArgs.first().value<Telegram::Peer>();

        quint32 receivedMessageId = receivedArgs.last().toUInt();
        QVERIFY(receivedMessageId);
        Telegram::Message messageData;
        client1.dataStorage()->getMessage(&messageData, fromPeer, receivedMessageId);
        QCOMPARE(messageData.text, c_message2Text);
    }
}

QTEST_GUILESS_MAIN(tst_MessagesApi)

#include "tst_MessagesApi.moc"
