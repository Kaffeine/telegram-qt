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
#include "MessageService.hpp"
#include "TelegramServer.hpp"
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

#ifdef TEST_PRIVATE_API
#include "DataStorage_p.hpp"
#endif

using namespace Telegram;

static const UserData c_userWithPassword = []() {
    UserData userData = mkUserData(1, 1);
    userData.setPassword(QByteArrayLiteral("mypassword"), QByteArrayLiteral("mysalt"));
    return userData;
}();

static const UserData c_user1 = mkUserData(1000, 1);
static const UserData c_user2 = mkUserData(2000, 1);
static const UserData c_user3 = mkUserData(3000, 1);
static const UserData c_user4 = mkUserData(4000, 1);

Client::ContactsApi::ContactInfo toContactInfo(const Server::AbstractUser *user)
{
    Client::ContactsApi::ContactInfo info;
    info.phoneNumber = user->phoneNumber();
    info.firstName = user->firstName();
    info.lastName = user->lastName();
    return info;
}

class tst_MessagesApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_MessagesApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void getSelfUserDialog();
    void getDialogs();
    void getAllDialogs();
    void groupChatMessaging();
    void sendMessage_data();
    void sendMessage();
    void getHistory_data();
    void getHistory();
    void syncPeerDialogs();
    void messageAction();
};

tst_MessagesApi::tst_MessagesApi(QObject *parent) :
    QObject(parent)
{
}

void tst_MessagesApi::initTestCase()
{
    Telegram::initialize();
    qRegisterMetaType<UserData>();
    QVERIFY(TestKeyData::initKeyFiles());

    if (!qEnvironmentVariableIsSet(Client::MessagingApi::messageActionIntervalEnvironmentVariableName())) {
        qputenv(Client::MessagingApi::messageActionIntervalEnvironmentVariableName(), QByteArrayLiteral("50"));
    }
}

void tst_MessagesApi::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_MessagesApi::getSelfUserDialog()
{
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

    Server::LocalUser *user = tryAddUser(&cluster, c_user1);
    Server::AbstractServerApi *serverApi = cluster.getServerApiInstance(c_user1.dcId);
    QVERIFY(serverApi);

    const QString c_messageText = QStringLiteral("message to self");

    {
        Server::MessageData *data = serverApi->messageService()
                ->addMessage(user->userId(), user->toPeer(), c_messageText);
        cluster.sendMessage(data);
    }

    // Prepare client
    Client::Client client;
    client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
    client.messagingApi()->setSyncLimit(5);

    QSignalSpy syncedMessagesSpy(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);

    Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
    signInHelper(&client, c_user1, &authProvider);
    TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

    Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
    PendingOperation *dialogsReady = dialogList->becomeReady();
    TRY_VERIFY(dialogsReady->isFinished());
    QVERIFY(dialogsReady->isSucceeded());
    QCOMPARE(dialogList->peers().count(), 1);

    PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());
    TRY_VERIFY(syncOp->isFinished());
    QVERIFY(syncOp->isSucceeded());
    TRY_COMPARE(syncedMessagesSpy.count(), 1);

    // Check the message
    {
        QList<QVariant> receivedArgs = syncedMessagesSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        QCOMPARE(receivedArgs.takeFirst().value<Telegram::Peer>(), user->toPeer());

        QVector<quint32> clientMessages = receivedArgs.takeFirst().value< QVector<quint32> >();
        QCOMPARE(clientMessages.count(), 1);

        Telegram::Message message;
        client.dataStorage()->getMessage(&message, user->toPeer(), clientMessages.constFirst());
        QCOMPARE(message.id(), clientMessages.constFirst());
        QCOMPARE(message.peer(), user->toPeer());
        QCOMPARE(message.text(), c_messageText);
        QCOMPARE(message.fromUserId(), user->id());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
    }
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
        QCOMPARE(client2AsClient1Peer.type(), Telegram::Peer::User);
        UserInfo userInfo;
        QVERIFY(client1.dataStorage()->getUserInfo(&userInfo, client2AsClient1Peer.id()));
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

        Telegram::Message message;
        client1.dataStorage()->getMessage(&message, client2AsClient1Peer, client1Message1Id);
        QCOMPARE(message.id(), client1Message1Id);
        QCOMPARE(message.peer(), client2AsClient1Peer);
        QCOMPARE(message.text(), c_message1Text);
        QCOMPARE(message.fromUserId(), client1.dataStorage()->selfUserId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagOut);
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
        QCOMPARE(messageData.text(), c_message1Text);
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
        QCOMPARE(messageData.text(), c_message2Text);
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

void tst_MessagesApi::getAllDialogs()
{
    const quint32 baseDate = 1500000000ul;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    const int dialogsCount = 60;

    // Prepare server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user = tryAddUser(&cluster, c_user1);
    Server::AbstractServerApi *serverApi = cluster.getServerApiInstance(c_user1.dcId);
    QVERIFY(serverApi);

    for (int i = 0; i < dialogsCount; ++i) {
        Server::LocalUser *dialogN = tryAddUser(&cluster, mkUserData(i, /* dc */ 1));
        QVERIFY(dialogN);
        Server::MessageData *data = serverApi->messageService()
                ->addMessage(dialogN->userId(), user->toPeer(), QStringLiteral("mgs%1").arg(i + 1));
        data->setDate(baseDate - dialogsCount + i);
        cluster.sendMessage(data);
    }

    // Prepare client
    Client::Client client;
    Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
    signInHelper(&client, c_user1, &authProvider);
    TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

    Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
    PendingOperation *dialogsReady = dialogList->becomeReady();
    TRY_VERIFY(dialogsReady->isFinished());
    QVERIFY(dialogsReady->isSucceeded());
    QCOMPARE(dialogList->peers().count(), dialogsCount);
}

void tst_MessagesApi::groupChatMessaging()
{
    const quint32 dc2 = 2;
    const UserData user1Data = c_user1;
    const UserData user2Data = c_user2;
    const UserData user3Data = mkUserData(3000, dc2);
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
    Server::LocalUser *user3 = tryAddUser(&cluster, user3Data);
    QVERIFY(user1 && user2 && user3);

    const Client::ContactsApi::ContactInfo user2ContactInfo = toContactInfo(user2);
    const Client::ContactsApi::ContactInfo user3ContactInfo = toContactInfo(user3);

    // Prepare clients
    Client::Client client1;
    {
        Test::setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation = nullptr;
        signInHelper(&client1, user1Data, &authProvider, &signInOperation);
        TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client1.accountStorage()->phoneNumber(), user1Data.phoneNumber);
    }
    TRY_VERIFY(client1.isSignedIn());

    Client::Client client2;
    {
        Test::setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation = nullptr;
        signInHelper(&client2, user2Data, &authProvider, &signInOperation);
        TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client2.accountStorage()->phoneNumber(), user2Data.phoneNumber);
    }
    TRY_VERIFY(client2.isSignedIn());

    Client::Client client3;
    {
        Test::setupClientHelper(&client3, user3Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation = nullptr;
        signInHelper(&client3, user3Data, &authProvider, &signInOperation);
        TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client3.accountStorage()->phoneNumber(), user3Data.phoneNumber);
    }
    TRY_VERIFY(client3.isSignedIn());

    QSignalSpy client1MessageReceivedSpy(client1.messagingApi(), &Client::MessagingApi::messageReceived);
    QSignalSpy client2MessageReceivedSpy(client2.messagingApi(), &Client::MessagingApi::messageReceived);
    QSignalSpy client3MessageReceivedSpy(client3.messagingApi(), &Client::MessagingApi::messageReceived);

    quint32 client1ExpectedMessageId = 0;
    quint32 client2ExpectedMessageId = 0;
    quint32 client3ExpectedMessageId = 0;

    Client::PendingContactsOperation *addContactOperation = client1.contactsApi()->addContacts({
                                                                                                   user2ContactInfo,
                                                                                                   user3ContactInfo,
                                                                                               });
    TRY_VERIFY(addContactOperation->isFinished());
    QVERIFY(addContactOperation->isSucceeded());
    QCOMPARE(addContactOperation->peers().count(), 2);
    const Telegram::Peer client2AsClient1Peer = addContactOperation->peers().constFirst();

    // Check sent by client 1
    {
        const QString c_message1Text = QStringLiteral("1:1 hello");
        QSignalSpy client1MessageSentSpy(client1.messagingApi(), &Client::MessagingApi::messageSent);
        client1.messagingApi()->sendMessage(client2AsClient1Peer, c_message1Text);
        TRY_COMPARE(client1MessageSentSpy.count(), 1);

        ++client1ExpectedMessageId;
        ++client2ExpectedMessageId;
    }

    // Check received back by client 1
    {
        // The sent message should be received as a proper Telegram::Message after the messageSent() signal
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        client1MessageReceivedSpy.clear();
    }

    // Check received by client 2
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        client2MessageReceivedSpy.clear();
    }

    const QString chatTitle = QLatin1String("new chat");
    const QVector<quint32> invitedChatMembers = { user2->id(), user3->id() };
    PendingOperation *createChatOperation = client1.messagingApi()->createChat(chatTitle, invitedChatMembers);
    TRY_VERIFY(createChatOperation->isFinished());
    QVERIFY(createChatOperation->isSucceeded());

    ++client1ExpectedMessageId;
    ++client2ExpectedMessageId;
    ++client3ExpectedMessageId;

    // Check received by client 1
    Peer groupChat1Peer;
    {
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        groupChat1Peer = groupChatPeer;

        QCOMPARE(client1ExpectedMessageId, messageId);
        Telegram::Message messageData;
        client2.dataStorage()->getMessage(&messageData, groupChatPeer, messageId);
        QCOMPARE(messageData.type(), Telegram::Namespace::MessageTypeService);
    }

    // Check received by client 2
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client2ExpectedMessageId, messageId);
        Telegram::Message messageData;
        client2.dataStorage()->getMessage(&messageData, groupChatPeer, messageId);
        QCOMPARE(messageData.type(), Telegram::Namespace::MessageTypeService);
    }

    // Check received by client 3
    {
        TRY_COMPARE(client3MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client3MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client3ExpectedMessageId, messageId);
        Telegram::Message messageData;
        client3.dataStorage()->getMessage(&messageData, groupChatPeer, messageId);

        qWarning() << messageData.text();
        QCOMPARE(messageData.type(), Telegram::Namespace::MessageTypeService);
    }

    // Checkpoint
    QCOMPARE(client1ExpectedMessageId, 2u);
    QCOMPARE(client2ExpectedMessageId, 2u);
    QCOMPARE(client3ExpectedMessageId, 1u);

    // Let the messaging begin
    const QString c_groupChatMessageText1 = QStringLiteral("1:N hello");

    // Check sent by client 1
    {
        QSignalSpy client1MessageSentSpy(client1.messagingApi(), &Client::MessagingApi::messageSent);
        quint64 sentMessageId = client1.messagingApi()->sendMessage(groupChat1Peer, c_groupChatMessageText1);
        TRY_COMPARE(client1MessageSentSpy.count(), 1);

        ++client1ExpectedMessageId;
        ++client2ExpectedMessageId;
        ++client3ExpectedMessageId;

        QList<QVariant> sentArgs = client1MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 3); // messageSent has 'peer', 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.takeFirst().value<Telegram::Peer>(), groupChat1Peer);
        QCOMPARE(sentArgs.takeFirst().value<quint64>(), sentMessageId);
        quint32 messageId = sentArgs.takeFirst().value<quint32>();
        QCOMPARE(messageId, client1ExpectedMessageId);
    }

    // Check received back by client 1
    {
        // The sent message should be received as a proper Telegram::Message after the messageSent() signal
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client1ExpectedMessageId, messageId);
        Telegram::Message message;
        client1.dataStorage()->getMessage(&message, groupChatPeer, messageId);
        QCOMPARE(message.id(), client1ExpectedMessageId);
        QCOMPARE(message.peer(), groupChatPeer);
        QCOMPARE(message.text(), c_groupChatMessageText1);
        QCOMPARE(message.fromUserId(), user1->userId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagOut);
        client1MessageReceivedSpy.clear();
    }

    // Check received by client 2
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client2ExpectedMessageId, messageId);
        Telegram::Message message;
        client2.dataStorage()->getMessage(&message, groupChatPeer, messageId);
        QCOMPARE(message.id(), messageId);
        QCOMPARE(message.peer(), groupChatPeer);
        QCOMPARE(message.text(), c_groupChatMessageText1);
        QCOMPARE(message.fromUserId(), user1->userId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
        client2MessageReceivedSpy.clear();
    }

    // Check received by client 3
    {
        TRY_COMPARE(client3MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client3MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client3ExpectedMessageId, messageId);
        Telegram::Message message;
        client3.dataStorage()->getMessage(&message, groupChatPeer, messageId);
        QCOMPARE(message.id(), messageId);
        QCOMPARE(message.peer(), groupChatPeer);
        QCOMPARE(message.text(), c_groupChatMessageText1);
        QCOMPARE(message.fromUserId(), user1->userId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
        client3MessageReceivedSpy.clear();
    }

    // Checkpoint
    QCOMPARE(client1ExpectedMessageId, 3u);
    QCOMPARE(client2ExpectedMessageId, 3u);
    QCOMPARE(client3ExpectedMessageId, 2u);

    // Message from an another DC user
    const QString c_groupChatMessageText2 = QStringLiteral("1:N hello cross DC");

    // Check sent by client 3
    {
        QSignalSpy client3MessageSentSpy(client3.messagingApi(), &Client::MessagingApi::messageSent);
        quint64 sentMessageId = client3.messagingApi()->sendMessage(groupChat1Peer, c_groupChatMessageText2);
        TRY_COMPARE(client3MessageSentSpy.count(), 1);

        ++client1ExpectedMessageId;
        ++client2ExpectedMessageId;
        ++client3ExpectedMessageId;

        QList<QVariant> sentArgs = client3MessageSentSpy.takeFirst();
        QCOMPARE(sentArgs.count(), 3); // messageSent has 'peer', 'random message id' and 'messageId' args
        QVERIFY(sentMessageId);
        QCOMPARE(sentArgs.takeFirst().value<Telegram::Peer>(), groupChat1Peer);
        QCOMPARE(sentArgs.takeFirst().value<quint64>(), sentMessageId);
        quint32 messageId = sentArgs.takeFirst().value<quint32>();
        QCOMPARE(messageId, client3ExpectedMessageId);
    }

    // Check received by client 1
    {
        // The sent message should be received as a proper Telegram::Message after the messageSent() signal
        TRY_COMPARE(client1MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client1MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client1ExpectedMessageId, messageId);
        Telegram::Message message;
        client1.dataStorage()->getMessage(&message, groupChatPeer, messageId);
        QCOMPARE(message.id(), messageId);
        QCOMPARE(message.peer(), groupChatPeer);
        QCOMPARE(message.text(), c_groupChatMessageText2);
        QCOMPARE(message.fromUserId(), user3->userId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
        client1MessageReceivedSpy.clear();
    }

    // Check received by client 2
    {
        TRY_COMPARE(client2MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client2MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client2ExpectedMessageId, messageId);
        Telegram::Message message;
        client2.dataStorage()->getMessage(&message, groupChatPeer, messageId);
        QCOMPARE(message.id(), messageId);
        QCOMPARE(message.peer(), groupChatPeer);
        QCOMPARE(message.text(), c_groupChatMessageText2);
        QCOMPARE(message.fromUserId(), user3->userId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
        client2MessageReceivedSpy.clear();
    }

    // Check received back by client 3
    {
        TRY_COMPARE(client3MessageReceivedSpy.count(), 1);
        QList<QVariant> receivedArgs = client3MessageReceivedSpy.takeFirst();
        QCOMPARE(receivedArgs.count(), 2); // messageReceived has 'peer' and 'messageId' args
        const Peer groupChatPeer = receivedArgs.first().value<Peer>();
        const quint32 messageId = receivedArgs.last().toUInt();
        QCOMPARE(client3ExpectedMessageId, messageId);
        Telegram::Message message;
        client3.dataStorage()->getMessage(&message, groupChatPeer, messageId);
        QCOMPARE(message.id(), messageId);
        QCOMPARE(message.peer(), groupChatPeer);
        QCOMPARE(message.text(), c_groupChatMessageText2);
        QCOMPARE(message.fromUserId(), user3->userId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagOut);
        client3MessageReceivedSpy.clear();
    }

    // Checkpoint
    QCOMPARE(client1ExpectedMessageId, 4u);
    QCOMPARE(client2ExpectedMessageId, 4u);
    QCOMPARE(client3ExpectedMessageId, 3u);
}

void tst_MessagesApi::sendMessage_data()
{
    QTest::addColumn<UserData>("user1Data");
    QTest::addColumn<UserData>("user2Data");

    const quint32 dc1 = 1;
    const quint32 dc2 = 2;

    QTest::newRow("Within a DC")
            << mkUserData(1, dc1)
            << mkUserData(2, dc1)
               ;

    QTest::newRow("Different DCs")
            << mkUserData(1, dc1)
            << mkUserData(2, dc2)
               ;
}

void tst_MessagesApi::sendMessage()
{
    QFETCH(UserData, user1Data);
    QFETCH(UserData, user2Data);

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
    Test::setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
    signInHelper(&client1, user1Data, &authProvider);
    Client::Client client2;
    Test::setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
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
        QVERIFY(client1.dataStorage()->getUserInfo(&userInfo, client2AsClient1Peer.id()));
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
        QCOMPARE(message.id(), client1Message1Id);
        QCOMPARE(message.peer(), client2AsClient1Peer);
        QCOMPARE(message.text(), c_message1Text);
        QCOMPARE(message.fromUserId(), client1.dataStorage()->selfUserId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagOut);
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
        QCOMPARE(message.id(), client2Message1Id);
        QCOMPARE(message.peer(), client1AsClient2Peer);
        QCOMPARE(message.text(), c_message1Text);
        QCOMPARE(message.fromUserId(), client1AsClient2Peer.id());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
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
    Server::AbstractUser *user2 = tryAddUser(&cluster, user2Data);
    QVERIFY(user1 && user2);

    Server::AbstractServerApi *server = cluster.getServerApiInstance(user1Data.dcId);
    QVERIFY(server);

    for (int i = 0; i < messagesCount; ++i) {
        Server::MessageData *messageData = server->messageService()->addMessage(
                    user2->id(), user1->toPeer(), QString::number(i + 1));
        messageData->setDate(static_cast<quint32>(baseDate + i));
        cluster.sendMessage(messageData);
    }

    // Prepare clients
    Client::Client client;
    Test::setupClientHelper(&client, user1Data, publicKey, clientDcOption);
    signInHelper(&client, user1Data, &authProvider);
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

void tst_MessagesApi::syncPeerDialogs()
{
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
    Server::AbstractUser *user3 = tryAddUser(&cluster, c_user3);
    Server::AbstractUser *user4 = tryAddUser(&cluster, c_user4);
    QVERIFY(user1 && user2 && user3 && user4);
    user1->importContact(user2->toContact());

    Server::Server *server = cluster.getServerInstance(c_user1.dcId);
    QVERIFY(server);

    const quint32 c_lastId1 = 5;
    MessageIdList messagesVol1;
    for (quint32 i = 0; i < c_lastId1; ++i) {
        Server::MessageData *messageData = server->messageService()->addMessage(
                    user2->id(), user1->toPeer(), QString::number(i + 1));
        cluster.sendMessage(messageData);
        messagesVol1.append(c_lastId1 - i);
    }

    // Part1. First sync, few messages in one dialog.
    QByteArray state1;
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(0);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 1);
        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());

        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId1);
        }
        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());

        TRY_COMPARE(syncMessages.count(), 1);
        QList<QVariant> firstSignal = syncMessages.takeFirst();
        QCOMPARE(firstSignal.count(), 2); // The signal has two arguments
        Peer p = firstSignal.constFirst().value<Peer>();
        MessageIdList messageIds = firstSignal.constLast().value<MessageIdList>();
        COMPARE_PEERS(p, user2->toPeer());
        qDebug() << messageIds;
        QCOMPARE(messageIds, messagesVol1);

        state1 = dataStorage->saveState();
    }

    // Part2. A dozen more messages in the same dialog.
    const quint32 c_lastId2 = 20;
    MessageIdList messagesVol2;
    for (quint32 i = 0; i < (c_lastId2 - c_lastId1); ++i) {
        Server::MessageData *messageData = server->messageService()->addMessage(
                    user2->id(), user1->toPeer(), QString::number(i + c_lastId1 + 1));
        cluster.sendMessage(messageData);
        messagesVol2.append(c_lastId2 - i);
    }

    QByteArray state2;
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        dataStorage->loadState(state1);
#ifdef TEST_PRIVATE_API
        Client::DataInternalApi *internalApi = Client::DataInternalApi::get(client.dataStorage());
        QCOMPARE(internalApi->getDialogState(user2->toPeer()).syncedMessageId, c_lastId1);
#endif
        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(0);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 1);
        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());

        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId2);
        }
        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());

        TRY_COMPARE(syncMessages.count(), 1);
        QList<QVariant> firstSignal = syncMessages.takeFirst();
        QCOMPARE(firstSignal.count(), 2); // The signal has two arguments
        Peer p = firstSignal.constFirst().value<Peer>();
        MessageIdList messageIds = firstSignal.constLast().value<MessageIdList>();
        COMPARE_PEERS(p, user2->toPeer());
        qDebug() << messageIds;
        QCOMPARE(messageIds, messagesVol2);

        state2 = dataStorage->saveState();
    }

    // Part3. Sync without initial data and with sync limit.
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(5);
        QCOMPARE(client.messagingApi()->syncLimit(), 5u);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 1);
        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());

        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId2);
        }
        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());

        TRY_COMPARE(syncMessages.count(), 1);
        QList<QVariant> firstSignal = syncMessages.takeFirst();
        QCOMPARE(firstSignal.count(), 2); // The signal has two arguments
        Peer p = firstSignal.constFirst().value<Peer>();
        MessageIdList messageIds = firstSignal.constLast().value<MessageIdList>();
        COMPARE_PEERS(p, user2->toPeer());
        qDebug() << messageIds;
        qDebug() << messagesVol2;
        QCOMPARE(static_cast<quint32>(messageIds.count()), client.messagingApi()->syncLimit());

        QByteArray limitedSyncData = dataStorage->saveState();
        // Currently the sync data will be same regardless of the limit.
        QCOMPARE(state2, limitedSyncData);
    }

    // Part4. New sync without initial data, no limit.
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(0);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 1);
        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());

        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId2);
        }
        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());

        TRY_COMPARE(syncMessages.count(), 1);
        QList<QVariant> firstSignal = syncMessages.takeFirst();
        QCOMPARE(firstSignal.count(), 2); // The signal has two arguments
        Peer p = firstSignal.constFirst().value<Peer>();
        MessageIdList messageIds = firstSignal.constLast().value<MessageIdList>();
        COMPARE_PEERS(p, user2->toPeer());
        qDebug() << messageIds;
        QCOMPARE(messageIds, messagesVol2 + messagesVol1);

        QByteArray unlimitedSyncData = dataStorage->saveState();
        // Currently the sync data will be same regardless of the limit.
        QCOMPARE(state2, unlimitedSyncData);
    }

    // Part5. A new dialog with a dozen messages and dozen more messages in the first dialog.
    const quint32 c_lastId3 = 50;
    MessageIdList messagesVol3_1;
    MessageIdList messagesVol3_2;
    for (quint32 i = 0; i < (c_lastId3 - c_lastId2); ++i) {
        const quint32 fromId = i %2 ? user2->id() : user3->id();
        Server::MessageData *messageData = server->messageService()->addMessage(
                    fromId, user1->toPeer(), QString::number(i + c_lastId2 + 1));
        cluster.sendMessage(messageData);

        if (i % 2) {
            messagesVol3_1.append(c_lastId3 - i);
        } else {
            messagesVol3_2.append(c_lastId3 - i);
        }
    }
    QHash<Peer, MessageIdList> expectedMessages3 = {
        { user2->toPeer(), messagesVol3_2 },
        { user3->toPeer(), messagesVol3_1 },
    };

    QByteArray state5;
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        dataStorage->loadState(state2);
#ifdef TEST_PRIVATE_API
        Client::DataInternalApi *internalApi = Client::DataInternalApi::get(client.dataStorage());
        QCOMPARE(internalApi->getDialogState(user2->toPeer()).syncedMessageId, c_lastId2);
#endif
        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(0);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 2);
        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());

        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId3);

            client.dataStorage()->getDialogInfo(&dialogInfo, user3->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId3 - 1);
        }
        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());

        TRY_COMPARE(syncMessages.count(), expectedMessages3.count());
        for (const QList<QVariant> &syncSignal : syncMessages) {
            Peer p = syncSignal.constFirst().value<Peer>();
            QVERIFY(expectedMessages3.contains(p));

            MessageIdList messageIds = syncSignal.constLast().value<MessageIdList>();
            MessageIdList expectedIds = expectedMessages3.take(p);
            QCOMPARE(messageIds, expectedIds);
        }

        state5 = dataStorage->saveState();
    }

    // Part4. More messages in the same two dialogs and new messages in both dialogs during the sync
    const quint32 c_lastId4 = 100;
    MessageIdList messagesVol4_1;
    MessageIdList messagesVol4_2;
    for (quint32 i = 0; i < (c_lastId4 - c_lastId3); ++i) {
        const quint32 fromId = i %2 ? user2->id() : user3->id();
        Server::MessageData *messageData = server->messageService()->addMessage(
                    fromId, user1->toPeer(), QString::number(i + c_lastId3 + 1));
        cluster.sendMessage(messageData);

        if (i % 2) {
            messagesVol4_1.append(c_lastId4 - i);
        } else {
            messagesVol4_2.append(c_lastId4 - i);
        }
    }
    QHash<Peer, MessageIdList> expectedMessages4 = {
        { user2->toPeer(), messagesVol4_2 },
        { user3->toPeer(), messagesVol4_1 },
    };

    QByteArray state6;
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        dataStorage->loadState(state5);
#ifdef TEST_PRIVATE_API
        Client::DataInternalApi *internalApi = Client::DataInternalApi::get(client.dataStorage());
        QCOMPARE(internalApi->getDialogState(user2->toPeer()).syncedMessageId, c_lastId3);
        QCOMPARE(internalApi->getDialogState(user3->toPeer()).syncedMessageId, c_lastId3 - 1);
#endif

        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(0);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        QSignalSpy receivedMessages(client.messagingApi(), &Client::MessagingApi::messageReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 2);
        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());
        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId4);

            client.dataStorage()->getDialogInfo(&dialogInfo, user3->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId4 - 1);
        }
        QVERIFY2(!syncOp->isFinished(), "We need to check new messages during sync");

        Server::MessageData *message1Data = server->messageService()->addMessage(
                    user2->id(), user1->toPeer(), QString::number(c_lastId4 + 1));
        Server::MessageData *message2Data = server->messageService()->addMessage(
                    user3->id(), user1->toPeer(), QString::number(c_lastId4 + 2));
        Server::MessageData *message3Data = server->messageService()->addMessage(
                    user4->id(), user1->toPeer(), QString::number(c_lastId4 + 3));

        QCOMPARE(receivedMessages.count(), 0);
        cluster.sendMessage(message1Data);
        cluster.sendMessage(message2Data);
        cluster.sendMessage(message3Data);

        expectedMessages4[user2->toPeer()].prepend(c_lastId4 + 1);
        expectedMessages4[user3->toPeer()].prepend(c_lastId4 + 2);

        TRY_COMPARE(receivedMessages.count(), 1);
        {
            const QList<QVariant> receivedMessage = receivedMessages.takeFirst();
            Peer p = receivedMessage.constFirst().value<Peer>();
            COMPARE_PEERS(p, user4->toPeer());

            QCOMPARE(receivedMessage.constLast().value<quint32>(), c_lastId4 + 3);
        }

        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());

        TRY_COMPARE(syncMessages.count(), expectedMessages4.count());
        for (const QList<QVariant> &syncSignal : syncMessages) {
            Peer p = syncSignal.constFirst().value<Peer>();
            QVERIFY(expectedMessages4.contains(p));

            MessageIdList messageIds = syncSignal.constLast().value<MessageIdList>();
            MessageIdList expectedIds = expectedMessages4.take(p);
            qDebug() << messageIds;
            qDebug() << expectedIds;
            QCOMPARE(messageIds, expectedIds);
        }

        QCOMPARE(receivedMessages.count(), 0);

        Server::MessageData *message4Data = server->messageService()->addMessage(
                    user2->id(), user1->toPeer(), QString::number(c_lastId4 + 4));
        Server::MessageData *message5Data = server->messageService()->addMessage(
                    user3->id(), user1->toPeer(), QString::number(c_lastId4 + 5));
        cluster.sendMessage(message4Data);
        cluster.sendMessage(message5Data);
        TRY_COMPARE(receivedMessages.count(), 2);

        state6 = dataStorage->saveState();
    }
    const quint32 c_lastId5 = c_lastId4 + 5;

    QByteArray state7;
    {
        // Prepare client
        Client::Client client;
        Test::setupClientHelper(&client, c_user1, publicKey, clientDcOption);
        Client::InMemoryDataStorage *dataStorage = static_cast<Client::InMemoryDataStorage *>(client.dataStorage());
        dataStorage->loadState(state6);
#ifdef TEST_PRIVATE_API
        Client::DataInternalApi *internalApi = Client::DataInternalApi::get(client.dataStorage());
        QCOMPARE(internalApi->getDialogState(user3->toPeer()).syncedMessageId, c_lastId5);
        QCOMPARE(internalApi->getDialogState(user2->toPeer()).syncedMessageId, c_lastId5 - 1);
        QCOMPARE(internalApi->getDialogState(user4->toPeer()).syncedMessageId, c_lastId5 - 2);
#endif
        client.messagingApi()->setSyncMode(Client::MessagingApi::ManualSync);
        client.messagingApi()->setSyncLimit(0);

        QSignalSpy syncMessages(client.messagingApi(), &Client::MessagingApi::syncMessagesReceived);
        QSignalSpy receivedMessages(client.messagingApi(), &Client::MessagingApi::messageReceived);
        signInHelper(&client, c_user1, &authProvider);
        TRY_VERIFY2(client.isSignedIn(), "Unexpected sign in fail");

        Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
        {
            PendingOperation *dialogsReady = dialogList->becomeReady();
            TRY_VERIFY(dialogsReady->isFinished());
            QVERIFY(dialogsReady->isSucceeded());
        }
        QCOMPARE(dialogList->peers().count(), 3);
        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId5 - 1);
            client.dataStorage()->getDialogInfo(&dialogInfo, user3->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId5);
            client.dataStorage()->getDialogInfo(&dialogInfo, user4->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId5 - 2);
        }

        PendingOperation *syncOp = client.messagingApi()->syncPeers(dialogList->peers());
        TRY_VERIFY(syncOp->isFinished());
        QVERIFY(syncOp->isSucceeded());
        TRY_COMPARE(syncMessages.count(), expectedMessages3.count());

        QCOMPARE(receivedMessages.count(), 0);
        Server::MessageData *messageData = server->messageService()->addMessage(
                    user4->id(), user1->toPeer(), QString::number(c_lastId5 + 1));
        cluster.sendMessage(messageData);

        TRY_COMPARE(receivedMessages.count(), 1);
        {
            DialogInfo dialogInfo;
            client.dataStorage()->getDialogInfo(&dialogInfo, user2->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId5 - 1);
            client.dataStorage()->getDialogInfo(&dialogInfo, user3->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId5);
            client.dataStorage()->getDialogInfo(&dialogInfo, user4->toPeer());
            QCOMPARE(dialogInfo.lastMessageId(), c_lastId5 + 1);
        }

        state7 = dataStorage->saveState();
    }
}

void tst_MessagesApi::messageAction()
{
    const UserData user1Data = c_user1;
    const UserData user2Data = c_user2;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    QVERIFY(publicKey.isValid() && privateKey.isPrivate()); // Sanity check

    // Prepare server
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
    Test::setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
    signInHelper(&client1, user1Data, &authProvider);
    Client::Client client2;
    Test::setupClientHelper(&client2, user2Data, publicKey, clientDcOption);
    signInHelper(&client2, user2Data, &authProvider);
    TRY_VERIFY2(client1.isSignedIn() && client2.isSignedIn(), "Unexpected sign in fail");

    // Everyone is online. Setup contacts
    Peer client2AsClient1Peer;
    Peer client1AsClient2Peer;
    Client::ContactList *client1ContactList = client1.contactsApi()->getContactList();
    {
        const Client::ContactsApi::ContactInfo user2ContactInfo = toContactInfo(user2);
        Client::PendingContactsOperation *addContactOperation = client1.contactsApi()->addContacts({user2ContactInfo});
        TRY_VERIFY(addContactOperation->isFinished());
        QVERIFY(addContactOperation->isSucceeded());

        QCOMPARE(addContactOperation->peers().count(), 1);
        client2AsClient1Peer = addContactOperation->peers().first();
        UserInfo userInfo;
        QVERIFY(client1.dataStorage()->getUserInfo(&userInfo, client2AsClient1Peer.id()));
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
        QCOMPARE(message.id(), client1Message1Id);
        QCOMPARE(message.peer(), client2AsClient1Peer);
        QCOMPARE(message.text(), c_message1Text);
        QCOMPARE(message.fromUserId(), client1.dataStorage()->selfUserId());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagOut);
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
        QCOMPARE(message.id(), client2Message1Id);
        QCOMPARE(message.peer(), client1AsClient2Peer);
        QCOMPARE(message.text(), c_message1Text);
        QCOMPARE(message.fromUserId(), client1AsClient2Peer.id());
        QCOMPARE(message.forwardTimestamp(), 0u);
        QCOMPARE(message.forwardFromPeer(), Peer());
        QCOMPARE(message.type(), Namespace::MessageTypeText);
        QCOMPARE(message.flags(), Namespace::MessageFlagNone);
    }

    // Check message actions
    QSignalSpy client1MessageActionsSpy(client1.messagingApi(), &Client::MessagingApi::messageActionChanged);
    QSignalSpy client2MessageActionsSpy(client2.messagingApi(), &Client::MessagingApi::messageActionChanged);
    client2.messagingApi()->setMessageAction(client1AsClient2Peer, Telegram::MessageAction::Type::Typing);
    TRY_VERIFY(!client1MessageActionsSpy.isEmpty());
    QCOMPARE(client1MessageActionsSpy.count(), 1);
    {
        QList<QVariant> receivedArgs = client1MessageActionsSpy.takeFirst();
        const Peer peer = receivedArgs.first().value<Telegram::Peer>();
        COMPARE_PEERS(peer, client2AsClient1Peer);
    }

    // Wait for the status invalidation (should happen in about 6 seconds in real application)
    TRY_VERIFY(!client1MessageActionsSpy.isEmpty());
    QCOMPARE(client1MessageActionsSpy.count(), 1);
    {
        QList<QVariant> receivedArgs = client1MessageActionsSpy.takeFirst();
        const Peer peer = receivedArgs.first().value<Telegram::Peer>();
        COMPARE_PEERS(peer, client2AsClient1Peer);
    }
}

QTEST_GUILESS_MAIN(tst_MessagesApi)

#include "tst_MessagesApi.moc"
