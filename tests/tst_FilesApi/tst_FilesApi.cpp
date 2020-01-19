/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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
#include "CAppInformation.hpp"
#include "CTelegramTransport.hpp"
#include "Client.hpp"
#include "ClientSettings.hpp"
#include "ConnectionApi.hpp"
#include "ContactList.hpp"
#include "ContactsApi.hpp"
#include "DataStorage.hpp"
#include "DcConfiguration.hpp"
#include "DialogList.hpp"
#include "FilesApi.hpp"
#include "MessagingApi.hpp"
#include "RandomGenerator.hpp"
#include "TelegramNamespace.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/FileOperation.hpp"
#include "Operations/PendingContactsOperation.hpp"

// Server
#include "LocalCluster.hpp"
#include "MediaService.hpp"
#include "MessageService.hpp"
#include "RemoteClientConnection.hpp"
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

class tst_FilesApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_FilesApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();

    void getSelfAvatar();
    void getDialogListPictures();
    void downloadMultipartFile();

protected:
    Server::UploadDescriptor uploadFile(Server::AbstractServerApi *server);

};

tst_FilesApi::tst_FilesApi(QObject *parent) :
    QObject(parent)
{
}

Server::UploadDescriptor tst_FilesApi::uploadFile(Server::AbstractServerApi *server)
{
    quint64 fileId;
    Telegram::RandomGenerator::instance()->generate(&fileId);
    const QByteArray fileData = Telegram::RandomGenerator::instance()->generate(512);
    quint32 filePartId = 0;

    Server::IMediaService *mediaService = server->mediaService();
    mediaService->uploadFilePart(fileId, filePartId, fileData);
    return mediaService->getUploadedData(fileId);
}

void tst_FilesApi::initTestCase()
{
    qRegisterMetaType<UserData>();
    Telegram::initialize();
    QVERIFY(TestKeyData::initKeyFiles());
}

void tst_FilesApi::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_FilesApi::getSelfAvatar()
{
    // Generic test data
    const UserData user1Data = c_user1;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());

    // Prepare the server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user1 = tryAddUser(&cluster, user1Data);
    QVERIFY(user1);

    // Upload an image
    {
        Server::AbstractServerApi *server = cluster.getServerApiInstance(user1->dcId());
        QVERIFY(server);
        const Server::ImageDescriptor image = uploadUserImage(server);
        QVERIFY(image.isValid());
        user1->updateImage(image);
    }

    // Prepare clients
    Client::Client client1;
    {
        Test::setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation1 = nullptr;
        Test::signInHelper(&client1, user1Data, &authProvider, &signInOperation1);
        TRY_VERIFY2(signInOperation1->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client1.accountStorage()->phoneNumber(), user1Data.phoneNumber);
    }
    TRY_VERIFY(client1.isSignedIn());

    UserInfo selfUserInfo;
    client1.dataStorage()->getUserInfo(&selfUserInfo, client1.dataStorage()->selfUserId());
    FileInfo pictureFile;
    selfUserInfo.getPeerPicture(&pictureFile, PeerPictureSize::Small);
    QVERIFY(!pictureFile.getFileId().isEmpty());

    // Download by FileInfo
    {
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        Client::FilesApi *filesApi = client1.filesApi();
        Client::FileOperation *fileOp = filesApi->downloadFile(&pictureFile, &buffer);

        QVERIFY(fileOp);
        TRY_VERIFY(fileOp->isFinished());
        QVERIFY(fileOp->isSucceeded());
        QByteArray downloadedData = buffer.data();
        QVERIFY(!downloadedData.isEmpty());
    }

    // Download by QString FileId
    {
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        Client::FilesApi *filesApi = client1.filesApi();
        Client::FileOperation *fileOp = filesApi->downloadFile(pictureFile.getFileId(), &buffer);

        QVERIFY(fileOp);
        TRY_VERIFY(fileOp->isFinished());
        QVERIFY(fileOp->isSucceeded());
        QByteArray downloadedData = buffer.data();
        QVERIFY(!downloadedData.isEmpty());
    }
}

void tst_FilesApi::getDialogListPictures()
{
    const quint32 baseDate = 1500000000ul;
    const UserData userData = c_user1;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    const int dialogsCount = 30;

    // Prepare server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user = tryAddUser(&cluster, userData);
    Server::AbstractServerApi *serverApi = cluster.getServerApiInstance(c_user1.dcId);
    QVERIFY(serverApi);

    // Prepare dialogs with avatars
    {
        Server::AbstractServerApi *server = cluster.getServerApiInstance(user->dcId());
        QVERIFY(server);
        const int dcCount = cluster.serverConfiguration().dcCount();
        QVERIFY(dcCount > 1);
        for (int i = 0; i < dialogsCount; ++i) {
            Server::LocalUser *dialogN = tryAddUser(&cluster,
                                                    // Add users to different DCs
                                                    mkUserData(i, static_cast<quint32>((i % dcCount) + 1)));
            QVERIFY(dialogN);
            Server::AbstractServerApi *contactServer = cluster.getServerApiInstance(dialogN->dcId());

            Server::MessageData *data = serverApi->messageService()
                    ->addMessage(dialogN->userId(), user->toPeer(), QStringLiteral("mgs%1").arg(i + 1));
            data->setDate32(baseDate - dialogsCount + i);
            cluster.processMessage(data);

            // Upload an image
            const Server::ImageDescriptor image = uploadUserImage(contactServer);
            QVERIFY(image.isValid());
            dialogN->updateImage(image);
        }
    }

    // Prepare the client
    Client::Client client;
    {
        Test::setupClientHelper(&client, userData, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation = nullptr;
        Test::signInHelper(&client, userData, &authProvider, &signInOperation);
        TRY_VERIFY2(signInOperation->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client.accountStorage()->phoneNumber(), userData.phoneNumber);
    }
    TRY_VERIFY(client.isSignedIn());

    Telegram::Client::DialogList *dialogList = client.messagingApi()->getDialogList();
    PendingOperation *dialogsReady = dialogList->becomeReady();
    TRY_VERIFY(dialogsReady->isFinished());
    QVERIFY(dialogsReady->isSucceeded());
    QCOMPARE(dialogList->peers().count(), dialogsCount);

    Client::FilesApi *filesApi = client.filesApi();
    QSet<Telegram::Client::FileOperation *> fetchOperations;

    qWarning() << "START DOWNLOAD";
    for (const Telegram::Peer &dialog : dialogList->peers()) {
        FileInfo pictureFile;
        if (dialog.type() == Telegram::Peer::User) {
            UserInfo userInfo;
            client.dataStorage()->getUserInfo(&userInfo, dialog.id());
            userInfo.getPeerPicture(&pictureFile, PeerPictureSize::Small);
            QVERIFY(!pictureFile.getFileId().isEmpty());
        }

        // Download by QString FileId
        Client::FileOperation *fileOp = filesApi->downloadFile(pictureFile.getFileId());
        QVERIFY(fileOp);
        fetchOperations.insert(fileOp);

        connect(fileOp, &Client::FileOperation::finished, this, [&fetchOperations, fileOp]() {
            QVERIFY(fileOp->isFinished());
            if (!fileOp->isSucceeded()) {
                qWarning() << fileOp->errorDetails();
            }
            QVERIFY(fileOp->isSucceeded());
            QVERIFY(fileOp->fileInfo()->isValid());
            QVERIFY(fileOp->device());
            const QByteArray data = fileOp->device()->readAll();
            QVERIFY(!data.isEmpty());
            fetchOperations.remove(fileOp);
        });
    }

    int count = fetchOperations.count();
    while (count) {
        TRY_VERIFY(fetchOperations.count() != count);
        count = fetchOperations.count();
    }
}

void tst_FilesApi::downloadMultipartFile()
{
    // Generic test data
    const UserData user1Data = c_user1;
    const DcOption clientDcOption = c_localDcOptions.first();
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());

    const int partsCount = 8;
    const int partSize = 1024 * 32;
    const int totalSize = partsCount * partSize;

    // Prepare the server
    Test::AuthProvider authProvider;
    Telegram::Server::LocalCluster cluster;
    cluster.setAuthorizationProvider(&authProvider);
    cluster.setServerPrivateRsaKey(privateKey);
    cluster.setServerConfiguration(c_localDcConfiguration);
    QVERIFY(cluster.start());

    Server::LocalUser *user = tryAddUser(&cluster, user1Data);
    QVERIFY(user);

    QByteArray fileHash;
    QString clientFileId;
    // Upload a multipart file
    {
        QCryptographicHash fileMd5Hash(QCryptographicHash::Md5);
        Server::AbstractServerApi *server = cluster.getServerApiInstance(user->dcId());
        QVERIFY(server);

        quint64 fileId;
        Telegram::RandomGenerator::instance()->generate(&fileId);
        Telegram::Server::IMediaService *mediaService = server->mediaService();
        for (int filePartId = 0; filePartId < partsCount; ++filePartId) {
            QByteArray filePartData(partSize, 'a');
            fileMd5Hash.addData(filePartData);
            mediaService->uploadFilePart(fileId, filePartId, filePartData);
        }
        fileHash = fileMd5Hash.result();

        const Telegram::Server::UploadDescriptor upload = mediaService->getUploadedData(fileId);
        // QCOMPARE(desc.md5Checksum, fileMd5Hash);
        const Telegram::Server::FileDescriptor fileDescriptor = mediaService->saveDocumentFile(upload, QLatin1String("a-parts.bin"), QLatin1String("bin"));

        FileInfo clientFileInfo;
        {
            TLFileLocation location;
            Telegram::Server::Utils::setupTLFileLocation(&location, fileDescriptor);
            FileInfo::Private *p = FileInfo::Private::get(&clientFileInfo);
            p->setFileLocation(&location);
            p->m_size = fileDescriptor.size;
            p->m_name = fileDescriptor.name;
        }
        clientFileId = clientFileInfo.getFileId();
    }

    // Prepare clients
    Client::Client client1;
    {
        Test::setupClientHelper(&client1, user1Data, publicKey, clientDcOption);
        Client::AuthOperation *signInOperation1 = nullptr;
        Test::signInHelper(&client1, user1Data, &authProvider, &signInOperation1);
        TRY_VERIFY2(signInOperation1->isSucceeded(), "Unexpected sign in fail");
        QCOMPARE(client1.accountStorage()->phoneNumber(), user1Data.phoneNumber);
    }
    TRY_VERIFY(client1.isSignedIn());

    {
        Client::FileOperation *fileOp = client1.filesApi()->downloadFile(clientFileId);
        quint32 totalDownloaded = 0;
        forever {
            TRY_VERIFY(totalDownloaded != fileOp->bytesTransferred());
            totalDownloaded = fileOp->bytesTransferred();
            if (fileOp->isFinished()) {
                break;
            }
        }

        QVERIFY(fileOp->isFinished());
        if (!fileOp->isSucceeded()) {
            qWarning() << fileOp->errorDetails();
        }
        QVERIFY(fileOp->isSucceeded());
        QVERIFY(fileOp->device());
        const QByteArray data = fileOp->device()->readAll();
        QCOMPARE(data.size(), totalSize);
    }

    QCOMPARE(user->activeSessions().count(), 2);
    Server::Session *activeMediaSession = user->activeSessions().last();
    QVERIFY(activeMediaSession);
    Telegram::BaseTransport *serverSideTransport = activeMediaSession->getConnection()->transport();
    QVERIFY(serverSideTransport);
    QVERIFY(serverSideTransport->state() == QAbstractSocket::ConnectedState);

    // Brutal disconnect from server side
    serverSideTransport->disconnectFromHost();

    {
        Client::FileOperation *fileOp = client1.filesApi()->downloadFile(clientFileId);
        quint32 totalDownloaded = 0;
        forever {
            TRY_VERIFY(totalDownloaded != fileOp->bytesTransferred());
            totalDownloaded = fileOp->bytesTransferred();
            if (fileOp->isFinished()) {
                break;
            }
        }

        QVERIFY(fileOp->isFinished());
        if (!fileOp->isSucceeded()) {
            qWarning() << fileOp->errorDetails();
        }
        QVERIFY(fileOp->isSucceeded());
        QVERIFY(fileOp->device());
        const QByteArray data = fileOp->device()->readAll();
        QCOMPARE(data.size(), totalSize);
    }
}

QTEST_GUILESS_MAIN(tst_FilesApi)

#include "tst_FilesApi.moc"
