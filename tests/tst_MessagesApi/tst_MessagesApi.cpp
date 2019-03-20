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

// Client
#include "AccountStorage.hpp"
#include "CAppInformation.hpp"
#include "Client.hpp"
#include "ClientSettings.hpp"
#include "ConnectionApi.hpp"
#include "ContactList.hpp"
#include "ContactsApi.hpp"
#include "DataStorage.hpp"
#include "TelegramNamespace.hpp"
#include "DialogList.hpp"
#include "DcConfiguration.hpp"
#include "MessagingApi.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/PendingContactsOperation.hpp"
#include "Operations/PendingMessages.hpp"

// Server
#include "LocalCluster.hpp"
#include "ServerApi.hpp"
#include "Storage.hpp"
#include "TelegramServerUser.hpp"

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
    UserData userData = mkUserData(1, 1);
    userData.setPassword(QByteArrayLiteral("mypassword"), QByteArrayLiteral("mysalt"));
    return userData;
}();

static const UserData c_user2 = mkUserData(2, 1);

class tst_MessagesApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_MessagesApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void getDialogs();
    void getMessage();
    void getHistory_data();
    void getHistory();
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
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());

    // Prepare server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
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
        setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation1 = nullptr;
        signInHelper(&client1, user1Data, &authProvider, &signInOperation1);
        TRY_VERIFY2(signInOperation1->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client1.accountStorage()->phoneNumber(), user1Data.phoneNumber);
    }
    TRY_VERIFY(client1.isSignedIn());

    Client::Client client2;
    {
        setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation2 = nullptr;
        signInHelper(&client2, user2Data, &authProvider, &signInOperation2);
        TRY_VERIFY2(signInOperation2->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client2.accountStorage()->phoneNumber(), user2Data.phoneNumber);
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
        QCOMPARE(client2AsClient1Peer.type, Telegram::Peer::User);
        UserInfo userInfo;
        QVERIFY(client1.dataStorage()->getUserInfo(&userInfo, client2AsClient1Peer.id));
        QCOMPARE(userInfo.phone(), user2ContactInfo.phoneNumber);
        QVERIFY(userInfo.isContact());

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

    quint32 client1Message1Id = 0;
    quint32 client1Message2Id = 0;
    quint32 client2Message1Id = 0;
    quint32 client2Message2Id = 0;

    // Check sent by client 1
    {
        quint64 sentMessageId = client1.messagingApi()->sendMessage(client2AsClient1Peer, c_message1Text);
        TRY_COMPARE(client1MessageSentSpy.count(), 1);
        QList<QVariant> sentArgs = client1MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 3); // messageSent has 'peer', 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.takeFirst().value<Telegram::Peer>(), client2AsClient1Peer);
        QCOMPARE(sentArgs.takeFirst().value<quint64>(), sentMessageId);
        client1Message1Id = sentArgs.takeFirst().value<quint32>();
        QVERIFY(client1Message1Id);

        // The sent message should be received as proper TLMessage right after the messageSent() signal
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        QCOMPARE(receivedArgs.takeFirst().value<Telegram::Peer>(), client2AsClient1Peer);
        QCOMPARE(receivedArgs.takeFirst().value<quint32>(), client1Message1Id);
    }

    // Check received by client 2
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        client1AsClient2Peer = receivedArgs.first().value<Telegram::Peer>();
        QVERIFY(client2DialogList->peers().contains(client1AsClient2Peer));

        client2Message1Id = receivedArgs.last().toUInt();
        QVERIFY(client2Message1Id);
        Telegram::Message messageData;
        client2.dataStorage()->getMessage(&messageData, client1AsClient2Peer, client2Message1Id);
        QCOMPARE(messageData.text, c_message1Text);
    }

    // Check the dialog is added to the client 2 dialog list
    {
        QCOMPARE(client2DialogListChangedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2DialogListChangedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // listChanged has 'added' and 'removed' args
        Telegram::PeerList added = receivedArgs.first().value<Telegram::PeerList>();
        QCOMPARE(added.count(), 1);
        QCOMPARE(added.first(), client1AsClient2Peer);
        QVERIFY(client2DialogList->peers().contains(client1AsClient2Peer));
    }

    // Check sent by client 2
    {
        quint64 sentMessageId = client2.messagingApi()->sendMessage(client1AsClient2Peer, c_message2Text);
        TRY_COMPARE(client2MessageSentSpy.count(), 1);
        QList<QVariant> sentArgs = client2MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 3); // messageSent has 'peer', 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.takeFirst().value<Telegram::Peer>(), client1AsClient2Peer);
        QCOMPARE(sentArgs.takeFirst().value<quint64>(), sentMessageId);
        client2Message2Id = sentArgs.takeFirst().value<quint32>();
        QVERIFY(client2Message2Id);

        // The sent message should be received as proper TLMessage right after the messageSent() signal
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        QCOMPARE(receivedArgs.takeFirst().value<Telegram::Peer>(), client1AsClient2Peer);
        QCOMPARE(receivedArgs.takeFirst().value<quint32>(), client2Message2Id);
    }

    // Check received by client 1
    {
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Telegram::Peer fromPeer = receivedArgs.first().value<Telegram::Peer>();

        client1Message2Id = receivedArgs.last().toUInt();
        QVERIFY(client1Message2Id);
        Telegram::Message messageData;
        client1.dataStorage()->getMessage(&messageData, fromPeer, client1Message2Id);
        QCOMPARE(messageData.text, c_message2Text);
    }

    // Check client 1 history
    {
        Telegram::Client::PendingMessages *historyOperation = client1.messagingApi()->getHistory(client2AsClient1Peer, Telegram::Client::MessageFetchOptions::useLimit(5));
        TRY_VERIFY(historyOperation->isFinished());
        QVERIFY(historyOperation->isSucceeded());
        QCOMPARE(historyOperation->messages().count(), 2);
        QCOMPARE(historyOperation->messages().first(), client1Message2Id);
        QCOMPARE(historyOperation->messages().last(), client1Message1Id);
        QVERIFY(historyOperation->messages().first() > historyOperation->messages().last());
    }

    // Check client 2 history
    {
        Telegram::Client::PendingMessages *historyOperation = client2.messagingApi()->getHistory(client1AsClient2Peer, Telegram::Client::MessageFetchOptions::useLimit(5));
        TRY_VERIFY(historyOperation->isFinished());
        QVERIFY(historyOperation->isSucceeded());
        QCOMPARE(historyOperation->messages().count(), 2);
        QCOMPARE(historyOperation->messages().first(), client2Message2Id);
        QCOMPARE(historyOperation->messages().last(), client2Message1Id);
        QVERIFY(historyOperation->messages().first() > historyOperation->messages().last());
    }
}

void tst_MessagesApi::getMessage()
{
    const UserData user1Data = c_userWithPassword;
    const UserData user2Data = c_user2;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    QVERIFY(publicKey.isValid() && privateKey.isPrivate()); // Sanity check

    // Prepare server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user1 = tryAddUser(&cluster, user1Data);
    Server::LocalUser *user2 = tryAddUser(&cluster, user2Data);
    QVERIFY(user1 && user2);

    // Prepare clients
    Client::Client client1;
    setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
    signInHelper(&client1, user1Data, &authProvider);
    Client::Client client2;
    setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
    signInHelper(&client2, user2Data, &authProvider);
    TRY_VERIFY2(client1.isSignedIn() && client2.isSignedIn(), "Unexpected sign in fail");

    Telegram::Peer client2AsClient1Peer;
    Telegram::Peer client1AsClient2Peer;

    // Everyone is online. Setup contacts
    Telegram::Client::ContactList *client1ContactList = client1.contactsApi()->getContactList();
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
        UserInfo userInfo;
        QVERIFY(client1.dataStorage()->getUserInfo(&userInfo, client2AsClient1Peer.id));
        QCOMPARE(userInfo.phone(), user2ContactInfo.phoneNumber);

        PendingOperation *contactListReadyOperation = client1ContactList->becomeReady();
        TRY_VERIFY(contactListReadyOperation->isFinished());
        QVERIFY(contactListReadyOperation->isSucceeded());
        QCOMPARE(client1ContactList->peers().count(), 1);
    }

    const QString c_message1Text = QStringLiteral("Hello");

    QSignalSpy client1MessageSentSpy(client1.messagingApi(), &Client::MessagingApi::messageSent);
    QSignalSpy client1MessageReceivedSpy(client1.messagingApi(), &Client::MessagingApi::messageReceived);
    QSignalSpy client2MessageReceivedSpy(client2.messagingApi(), &Client::MessagingApi::messageReceived);

    quint32 client1Message1Id = 0;
    quint32 client2Message1Id = 0;

    // Check sent by client 1
    {
        quint64 sentMessageId = client1.messagingApi()->sendMessage(client2AsClient1Peer, c_message1Text);
        TRY_COMPARE(client1MessageSentSpy.count(), 1);
        QList<QVariant> sentArgs = client1MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 3); // messageSent has 'peer', 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.takeFirst().value<Telegram::Peer>(), client2AsClient1Peer);
        QCOMPARE(sentArgs.takeFirst().value<quint64>(), sentMessageId);
        client1Message1Id = sentArgs.takeFirst().value<quint32>();
        QVERIFY(client1Message1Id);
    }

    // Check received back by client1
    {
        // The sent message should be received as proper TLMessage right after the messageSent() signal
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        QCOMPARE(receivedArgs.takeFirst().value<Telegram::Peer>(), client2AsClient1Peer);
        QCOMPARE(receivedArgs.takeFirst().value<quint32>(), client1Message1Id);
        Telegram::Message message;
        client1.dataStorage()->getMessage(&message, client2AsClient1Peer, client1Message1Id);
        QCOMPARE(message.id, client1Message1Id);
        QCOMPARE(message.peer(), client2AsClient1Peer);
        QCOMPARE(message.text, c_message1Text);
        QCOMPARE(message.fromId, client1.dataStorage()->selfUserId());
        QCOMPARE(message.forwardContactId, 0u);
        QCOMPARE(message.fwdTimestamp, 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type, TelegramNamespace::MessageTypeText);
        QCOMPARE(message.flags, TelegramNamespace::MessageFlagOut);
    }

    // Check received by client 2
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        client1AsClient2Peer = receivedArgs.first().value<Telegram::Peer>();

        client2Message1Id = receivedArgs.last().toUInt();
        QVERIFY(client2Message1Id);
        Telegram::Message message;
        client2.dataStorage()->getMessage(&message, client1AsClient2Peer, client2Message1Id);
        QCOMPARE(message.id, client2Message1Id);
        QCOMPARE(message.peer(), client1AsClient2Peer);
        QCOMPARE(message.text, c_message1Text);
        QCOMPARE(message.fromId, client1AsClient2Peer.id);
        QCOMPARE(message.forwardContactId, 0u);
        QCOMPARE(message.fwdTimestamp, 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type, TelegramNamespace::MessageTypeText);
        QCOMPARE(message.flags, TelegramNamespace::MessageFlagNone);
    }

    QSignalSpy client1MessageReadSpy(client1.messagingApi(), &Client::MessagingApi::messageReadOutbox);

    client2.messagingApi()->readHistory(client1AsClient2Peer, client2Message1Id);

    // Check message marked read for client 1
    {
        TRY_COMPARE(client1MessageReadSpy.count(), 1);
    }
}

void tst_MessagesApi::getHistory_data()
{
    QTest::addColumn<Telegram::Client::MessageFetchOptions>("fetchOptions");
    QTest::addColumn<Telegram::MessageIdList>("messageIds");
    QTest::addColumn<int>("messagesCount");
    QTest::addColumn<quint32>("baseDate");

    quint32 baseDate = 1500000000ul;

    {
        int messagesCount = 50;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.limit = 10;
        MessageIdList list;
        for (quint32 i = 0; i < fetchOptions.limit; ++i) {
            list.append(static_cast<quint32>(messagesCount) - i);
        }
        QTest::newRow("Limit")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }

    {
        int messagesCount = 50;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.limit = 5;
        fetchOptions.offsetId = messagesCount - 4;
        MessageIdList list;
        for (quint32 i = 0; i < fetchOptions.limit; ++i) {
            // The -1 is needed because 'offsetId is not included'
            list.append(fetchOptions.offsetId - i - 1);
        }
        QTest::newRow("OffsetId")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }

    {
        int messagesCount = 50;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.limit = 5;
        fetchOptions.offsetId = messagesCount - 4;
        fetchOptions.addOffset = 15;
        MessageIdList list;
        for (quint32 i = 0; i < fetchOptions.limit; ++i) {
            // The -1 is needed because 'offsetId is not included'
            list.append(fetchOptions.offsetId - fetchOptions.addOffset - i - 1);
        }
        QTest::newRow("offsetId + addOffset")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }

    {
        constexpr int messagesCount = 50;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.limit = 5;
        fetchOptions.offsetId = messagesCount - 4; // 46
        fetchOptions.addOffset = 10; // from 31
        fetchOptions.maxId = messagesCount - 6; // Remove messages newer than 44 (no effect)
        MessageIdList list;
        for (quint32 i = 0; i < fetchOptions.limit; ++i) {
            // The -1 is needed because 'offsetId is not included'
             // - fetchOptions.offsetId
            list.append(fetchOptions.offsetId - fetchOptions.addOffset - i - 1);
        }
        // (50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, ..
        //                  ^^   \__||______________________________/    |___|___|___|___|
        //                offset    ^^      addOffset (10 messages)      result (5 messages)
        //                         maxId
        QTest::newRow("addOffset + maxId (no effect)")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }

    {
        constexpr int messagesCount = 50;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.limit = 5;
        fetchOptions.offsetId = messagesCount - 4; // 46
        fetchOptions.addOffset = 3; // from 31
        fetchOptions.maxId = fetchOptions.offsetId - fetchOptions.addOffset - 3; // 40
        MessageIdList list = { 39, 38 };
        // (50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, ..
        //                  ^^   \______/    |_x_|_x_||___|___|
        //                offset addOffset    result (5 messages)
        //                         maxId           maxId

        QTest::newRow("addOffset + maxId")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }

    {
        constexpr int messagesCount = 30;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.offsetDate = baseDate; // id 12
        MessageIdList list = {1};

        QTest::newRow("offsetDate")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }

    {
        constexpr int messagesCount = 30;
        Client::MessageFetchOptions fetchOptions;
        fetchOptions.limit = 4;
        fetchOptions.offsetDate = baseDate + 12; // id 13
        fetchOptions.addOffset = 3;
        MessageIdList list = { 10, 9, 8, 7 };

        QTest::newRow("offsetDate + addOffset")
                << fetchOptions
                << list
                << messagesCount
                << baseDate;
    }
}

void tst_MessagesApi::getHistory()
{
    QFETCH(Telegram::Client::MessageFetchOptions, fetchOptions);
    QFETCH(Telegram::MessageIdList, messageIds);
    QFETCH(int, messagesCount);
    QFETCH(quint32, baseDate);

    const UserData c_user1 = c_userWithPassword;

    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());

    // Prepare server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user1 = tryAddUser(&cluster, c_user1);
    Server::AbstractUser *user2 = tryAddUser(&cluster, c_user2);
    QVERIFY(user1 && user2);

    Server::ServerApi *server = cluster.getServerApiInstance(c_user1.dcId);
    QVERIFY(server);

    for (int i = 0; i < messagesCount; ++i) {
        Server::MessageData *messageData = server->storage()->addMessage(
                    user2->id(), user1->toPeer(), QString::number(i + 1));
        messageData->setDate(static_cast<quint32>(baseDate + i));
        server->processMessage(messageData);
    }

    // Prepare clients
    Client::Client client;
    setupClientHelper(&client, c_user1, publicKey, clientDcOption);
    signInHelper(&client, c_user1, &authProvider);
    TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");
    TRY_COMPARE(client.connectionApi()->status(), Telegram::Client::ConnectionApi::StatusReady);

    Client::MessagingApi *messagingApi = client.messagingApi();
    Telegram::Client::DialogList *dialogList = messagingApi->getDialogList();
    {
        PendingOperation *dialogsReady = dialogList->becomeReady();
        TRY_VERIFY(dialogsReady->isFinished());
        QVERIFY(dialogsReady->isSucceeded());
    }
    QCOMPARE(dialogList->peers().count(), 1);
    COMPARE_PEERS(dialogList->peers().constFirst(), user2->toPeer());
    const Peer dialogPeer = user2->toPeer();

    DialogInfo dialogInfo;
    client.dataStorage()->getDialogInfo(&dialogInfo, dialogPeer);
    QCOMPARE(static_cast<int>(dialogInfo.lastMessageId()), messagesCount);

    Client::PendingMessages *op = messagingApi->getHistory(dialogPeer, fetchOptions);
    TRY_VERIFY(op->isFinished());
    QVERIFY(op->isSucceeded());
    COMPARE_PEERS(op->peer(), dialogPeer);
    QVector<quint32> ids = op->messages();

    qDebug() << ids;
    QCOMPARE(ids.count(), messageIds.count());

    for (int i = 0; i < ids.count(); ++i) {
        QCOMPARE(ids.at(i), messageIds.at(i));
    }
}

QTEST_GUILESS_MAIN(tst_MessagesApi)

#include "tst_MessagesApi.moc"
