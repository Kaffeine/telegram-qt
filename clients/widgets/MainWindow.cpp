/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CAppInformation.hpp"
#include "AccountStorage.hpp"
#include "DataStorage.hpp"
#include "Debug.hpp"
#include "Client.hpp"

#include "ClientSettings.hpp"
#include "ContactsApi.hpp"
#include "ConnectionApi.hpp"
#include "MessagingApi.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/PendingContactsOperation.hpp"

#include "CContactModel.hpp"
#include "CContactsFilterModel.hpp"
#include "CDialogModel.hpp"
#include "CMessageModel.hpp"
#include "CChatInfoModel.hpp"
#include "CFileManager.hpp"

#include <QCompleter>
#include <QToolTip>
#include <QStringListModel>

#include <QMimeDatabase>
#include <QMimeType>
#include <QStandardPaths>

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QMetaEnum>

static const int c_peerPictureColumnWidth = 70;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_backend(new Telegram::Client::Client(this)),
    // m_fileManager(new CFileManager(m_backend, this)),
    m_contactsModel(new CContactModel(m_backend, this)),
    m_contactListModel(new CContactsFilterModel(this)),
    m_dialogModel(new CDialogModel(m_backend, this)),
    m_messagingModel(new CMessageModel(m_backend, this)),
    m_chatContactsModel(new CContactsFilterModel(this)),
    m_chatMessagingModel(new CMessageModel(m_backend, this)),
    // m_chatInfoModel(new CChatInfoModel(m_backend, this)),
    m_contactSearchResultModel(nullptr),
    m_activeChatId(0),
    m_chatCreationMode(false),
    m_workLikeAClient(true),
    m_appState(AppStateNone)
{
#if 0
    m_dialogModel->setFileManager(m_fileManager);
    m_contactsModel->setFileManager(m_fileManager);
    m_chatInfoModel->setFileManager(m_fileManager);
    m_messagingModel->setFileManager(m_fileManager);
    m_chatMessagingModel->setFileManager(m_fileManager);
#endif

    m_dialogModel->addSourceModel(m_contactsModel);
    m_dialogModel->addSourceModel(m_chatInfoModel);

    ui->setupUi(this);
    ui->workLikeClient->setChecked(m_workLikeAClient);
    connect(ui->workLikeClient, &QAbstractButton::toggled, this, &MainWindow::setWorkLikeAClient);
    m_contactListModel->setSourceModel(m_contactsModel);
    ui->contactListTable->setModel(m_contactListModel);
    ui->contactListTable->setColumnWidth(CContactModel::Avatar, c_peerPictureColumnWidth);
    ui->dialogList->setModel(m_dialogModel);
    ui->dialogList->setColumnWidth(static_cast<int>(CDialogModel::Column::Picture), c_peerPictureColumnWidth);
    ui->messagingView->setModel(m_messagingModel);
    m_chatContactsModel->setSourceModel(m_contactsModel);
    ui->groupChatContacts->setModel(m_chatContactsModel);
    ui->groupChatContacts->setColumnWidth(CContactModel::Avatar, c_peerPictureColumnWidth);
    ui->groupChatChatsList->setModel(m_chatInfoModel);
    ui->groupChatChatsList->setColumnWidth(CChatInfoModel::Picture, c_peerPictureColumnWidth);
    ui->groupChatMessagingView->setModel(m_chatMessagingModel);
    ui->groupChatMessagingView->hideColumn(CMessageModel::Direction);

    m_messagingModel->setContactsModel(m_contactsModel);
    m_chatMessagingModel->setContactsModel(m_contactsModel);

    QCompleter *comp = new QCompleter(m_contactsModel, this);
    comp->setCompletionColumn(CContactModel::Phone);
    ui->messagingContactIdentifier->setCompleter(comp);
    ui->groupChatContactPhone->setCompleter(comp);

    connect(ui->secretOpenFile, &QAbstractButton::clicked, this, &MainWindow::loadSecretFromBrowsedFile);
    connect(ui->getSecretInfo, &QAbstractButton::clicked, this, &MainWindow::getConnectionSecretInfo);

    m_backend->setAccountStorage(new Telegram::Client::AccountStorage(m_backend));
    m_backend->setDataStorage(new Telegram::Client::InMemoryDataStorage(m_backend));
    m_backend->setSettings(new Telegram::Client::Settings(m_backend));

    // Telepathy Morse app info
    CAppInformation *appInfo = new CAppInformation(this);
    appInfo->setAppId(14617);
    appInfo->setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
    appInfo->setAppVersion(QLatin1String("0.1"));
    appInfo->setDeviceInfo(QLatin1String("pc"));
    appInfo->setOsInfo(QLatin1String("GNU/Linux"));
    appInfo->setLanguageCode(QLatin1String("en"));

    m_backend->setAppInformation(appInfo);

    connect(m_backend->connectionApi(), &Telegram::Client::ConnectionApi::statusChanged,
            this, &MainWindow::onConnectionStateChanged);
    connect(m_backend, SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)),
            SLOT(onAuthSignErrorReceived(TelegramNamespace::AuthSignError,QString)));
    connect(m_backend, SIGNAL(contactListChanged()),
            SLOT(updateContactList()));
    connect(m_backend, SIGNAL(dialogsChanged(QVector<Telegram::Peer>,QVector<Telegram::Peer>)),
            m_dialogModel, SLOT(syncDialogs(QVector<Telegram::Peer>,QVector<Telegram::Peer>)));
    connect(m_backend->messagingApi(), &Telegram::Client::MessagingApi::messageReceived,
            this, &MainWindow::onMessageReceived);
    connect(m_backend, SIGNAL(contactChatMessageActionChanged(quint32,quint32,TelegramNamespace::MessageAction)),
            SLOT(onContactChatMessageActionChanged(quint32,quint32,TelegramNamespace::MessageAction)));
    connect(m_backend, SIGNAL(contactMessageActionChanged(quint32,TelegramNamespace::MessageAction)),
            SLOT(onContactMessageActionChanged(quint32,TelegramNamespace::MessageAction)));
    connect(m_backend, SIGNAL(createdChatIdReceived(quint64,quint32)),
            SLOT(onCreatedChatIdResolved(quint64,quint32)));
    connect(m_backend->contactsApi(), &Telegram::Client::ContactsApi::contactStatusChanged,
            this, &MainWindow::onContactStatusChanged);
    connect(m_backend, SIGNAL(filePartUploaded(quint32,quint32,quint32)),
            SLOT(onUploadingStatusUpdated(quint32,quint32,quint32)));
    connect(m_backend, SIGNAL(fileRequestFinished(quint32,Telegram::RemoteFile)),
            SLOT(onFileRequestFinished(quint32,Telegram::RemoteFile)));
    connect(m_backend, SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::UserNameStatus)),
            SLOT(onUserNameStatusUpdated(QString,TelegramNamespace::UserNameStatus)));

    // connect(m_backend, &CTelegramCore::userInfoReceived, m_contactsModel, &CContactModel::addContact);

//    connect(m_chatInfoModel, SIGNAL(chatAdded(quint32)), SLOT(onChatAdded(quint32)));
    connect(m_chatInfoModel, SIGNAL(chatChanged(quint32)), SLOT(onChatChanged(quint32)));

    ui->groupChatContacts->hideColumn(CContactModel::Blocked);

    ui->mainSplitter->setStretchFactor(1, 1);
    ui->mainSplitter->setSizes(QList<int>() << 0 << 100);
    ui->groupChatSplitter->setSizes(QList<int>() << 550 << 450 << 300);
    ui->contactsSplitter->setSizes(QList<int>() << 100 << 0);

    ui->groupChatChatsList->setColumnWidth(CChatInfoModel::Id, 30);

    ui->blockContact->hide();
    ui->unblockContact->hide();

    ui->groupChatLeaveChat->hide();

    QFile helpFile(QLatin1String(":/USAGE"));
    helpFile.open(QIODevice::ReadOnly);
    ui->helpView->setPlainText(helpFile.readAll());

    setUiProxyEnabled(false);
    setAppState(AppStateDisconnected);
    updateGroupChatAddContactButtonText();

    connect(ui->groupChatContactPhone, SIGNAL(textChanged(QString)), SLOT(updateGroupChatAddContactButtonText()));

    connect(ui->messagingView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomMenuRequested(QPoint)));
    connect(ui->contactSearchResult, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onSearchCustomMenuRequested(QPoint)));
    connect(ui->settingsProxyEnable, SIGNAL(toggled(bool)), this, SLOT(setUiProxyEnabled(bool)));

    ui->groupChatAddContactForwardMessages->hide();
    updateClientUi();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectionStateChanged(Telegram::Client::ConnectionApi::Status status)
{
    switch (status) {
    case Telegram::Client::ConnectionApi::StatusDisconnected:
        setAppState(AppStateDisconnected);
        break;
    case Telegram::Client::ConnectionApi::StatusWaitForAuthentication:
        setAppState(AppStateAuthRequired);
        break;
    case Telegram::Client::ConnectionApi::StatusConnected:
        setAppState(AppStateSignedIn);
        break;
    case Telegram::Client::ConnectionApi::StatusReady:
        setAppState(AppStateReady);
        break;
    default:
        break;
    }
}

void MainWindow::onAuthOperationFailed(Telegram::PendingOperation *operation, const QVariantHash &details)
{
    Q_UNUSED(operation)
    qWarning() << Q_FUNC_INFO << details;
}

void MainWindow::onLoggedOut(bool result)
{
    qDebug() << Q_FUNC_INFO << result;
    setAppState(AppStateLoggedOut);
}

void MainWindow::onAuthPhoneCodeRequired()
{
    setAppState(AppStateCodeRequired);

    //m_backend->requestPhoneStatus(ui->phoneNumber->text());
}

void MainWindow::onAuthRegisteredChanged(bool registered)
{
    QString registeredText = registered ? tr("Registered") : tr("Not registered");
    ui->phoneStatus->setText(registeredText);
    setRegistered(registered);
}

void MainWindow::onAuthPasswordRequested()
{
    setAppState(AppStatePasswordRequired);
}

void MainWindow::onAuthSignErrorReceived(TelegramNamespace::AuthenticationError errorCode, const QString &errorMessage)
{
    switch (errorCode) {
    case TelegramNamespace::AuthenticationErrorPhoneNumberInvalid:
        QToolTip::showText(ui->phoneNumber->mapToGlobal(QPoint(0, 0)), tr("Phone number is not valid"));
        break;
    case TelegramNamespace::AuthenticationErrorPhoneCodeExpired:
        QToolTip::showText(ui->confirmationCode->mapToGlobal(QPoint(0, 0)), tr("Phone code is expired"));
        break;
    case TelegramNamespace::AuthenticationErrorPhoneCodeInvalid:
        QToolTip::showText(ui->confirmationCode->mapToGlobal(QPoint(0, 0)), tr("Phone code is invalid"));
        break;
    default:
        qDebug() << "Unknown auth sign error:" << errorMessage;
        return;
    }

    ui->confirmationCode->setFocus();
}

void MainWindow::updateContactList()
{
    QVector<quint32> idList = Telegram::Utils::toIdList(m_backend->dataStorage()->contactList());
    m_contactListModel->setFilterList(idList);
}

void MainWindow::onMessageReceived(const Telegram::Peer peer, quint32 messageId)
{
    bool groupChatMessage = peer.type != Telegram::Peer::User;
    if (groupChatMessage) {
        if (peer.id != m_activeChatId) {
            return;
        }
    }

    Telegram::Message message;
    m_backend->dataStorage()->getMessage(&message, peer, messageId);
    if (groupChatMessage) {
        m_chatMessagingModel->addMessage(message);
    } else {
        m_messagingModel->addMessage(message);
        if (!(message.flags & TelegramNamespace::MessageFlagOut) && (m_contactLastMessageList.value(peer.id) < peer.id)) {
            m_contactLastMessageList.insert(peer.id, peer.id);

            if (ui->settingsReadMessages->isChecked()) {
                if (ui->tabWidget->currentWidget() == ui->tabMessaging) {
                    m_backend->messagingApi()->readHistory(peer.id, peer.id);
                }
            }
        }
    }
}

void MainWindow::onContactChatMessageActionChanged(quint32 chatId, quint32 userId, TelegramNamespace::MessageAction action)
{
    if (m_activeChatId != chatId) {
        return;
    }

    m_contactsModel->setTypingStatus(userId, action);
}

void MainWindow::onContactMessageActionChanged(quint32 userId, TelegramNamespace::MessageAction action)
{
    m_contactsModel->setTypingStatus(userId, action);
    updateMessagingContactAction();
}

void MainWindow::onContactStatusChanged(quint32 contact)
{
    if (contact == m_activeContactId) {
        updateMessagingContactStatus();
    }
}

#if 0
void MainWindow::onCreatedChatIdResolved(quint64 requestId, quint32 chatId)
{
    if (requestId == m_pendingChatId) {
        qDebug() << "Expected chat id received" << requestId << chatId;
        m_pendingChatId = 0;
    } else {
        qDebug() << "Unexpected chat id received" << requestId << chatId;
    }

    setActiveChat(chatId);
}

void MainWindow::onChatChanged(quint32 chatId)
{
    if (chatId == m_activeChatId) {
        updateActiveChat();
    }
}

void MainWindow::updateActiveChat()
{
    const Telegram::ChatInfo *chat = m_chatInfoModel->chatById(m_activeChatId);

    if (!chat) {
        ui->groupChatName->setText(tr("Processing..."));
        return;
    }

    ui->groupChatName->setText(chat->title());

    QVector<quint32> participants;
    if (!m_backend->getChatParticipants(&participants, m_activeChatId)) {
        qDebug() << Q_FUNC_INFO << "Unable to get chat participants. Invalid chat?";
    }

    m_chatContactsModel->setFilterList(participants);
    updateGroupChatAddContactButtonText();
}

void MainWindow::onUploadingStatusUpdated(quint32 requestId, quint32 currentOffset, quint32 size)
{
    qDebug() << Q_FUNC_INFO << requestId << currentOffset << size;
    statusBar()->showMessage(tr("Request %1 status updated (%2/%3).").arg(requestId).arg(currentOffset).arg(size));
}

void MainWindow::onFileRequestFinished(quint32 requestId, Telegram::RemoteFile info)
{
    qDebug() << Q_FUNC_INFO << requestId;

    if (info.type() != Telegram::RemoteFile::Upload) {
        return;
    }

    if (!m_uploadingRequests.contains(requestId)) {
        return;
    }

    const Telegram::Peer peer = m_uploadingRequests.take(requestId);

    Telegram::MessageMediaInfo mediaInfo;

    const QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForFile(info.fileName(), QMimeDatabase::MatchExtension);
    if (!mimeType.isValid()) {
        qDebug() << Q_FUNC_INFO << "Unable to determine mime type. Transfer aborted.";
        return;
    }

    if (mimeType.inherits(QLatin1String("image/jpeg"))) {
        mediaInfo.setUploadFile(TelegramNamespace::MessageTypePhoto, info);
    } else {
        mediaInfo.setUploadFile(TelegramNamespace::MessageTypeDocument, info);
        mediaInfo.setMimeType(mimeType.name());
        mediaInfo.setDocumentFileName(info.fileName());
    }
//    mediaInfo.setCaption(tr("Media %1").arg(requestId));

    CMessageModel::SMessage m;
    m.type = mediaInfo.type();
    m.text = mediaInfo.caption();
    m.flags = TelegramNamespace::MessageFlagOut;
    m.id64 = m_backend->sendMedia(peer, mediaInfo);
    m.setPeer(peer);
    m.fromId = m_backend->selfId();

    if (peer.type == Telegram::Peer::User) {
        m_messagingModel->addMessage(m);
    } else {
        m_chatMessagingModel->addMessage(m);
    }
}
#endif

void MainWindow::onUserNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status)
{
    if (userName == m_searchQuery) {
        if (status == TelegramNamespace::UserNameStatusResolved) {
            searchByUsername();
        }
    }
}

void MainWindow::onCustomMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->messagingView->currentIndex();
    if (!index.isValid()) {
        return;
    }

    static QMenu *menu = 0;
    static QMenu *resendMenu = 0;
    static QMenu *forwardMenu = 0;

    if (!menu) {
        menu = new QMenu(this);
        resendMenu = menu->addMenu(tr("Resend media"));
        forwardMenu = menu->addMenu(tr("Forward message"));
    }

    resendMenu->clear();
    forwardMenu->clear();

    const CMessageModel::SMessage *message = m_messagingModel->messageAt(static_cast<quint32>(index.row()));

#if 0
    if (message->type == TelegramNamespace::MessageTypeText) {
        resendMenu->setDisabled(true);
    } else {
        resendMenu->setEnabled(true);
        for (int i = 0; i < m_contactsModel->rowCount(); ++i) {
            const SContact *contact = m_contactsModel->contactAt(i);

            QAction *a = resendMenu->addAction(CContactModel::getContactName(*contact));
            connect(a, &QAction::triggered, [=]() {
                Telegram::MessageMediaInfo info;
                m_backend->getMessageMediaInfo(&info, messageId, Telegram::Peer(contact->id(), Telegram::Peer::User));
                m_backend->sendMedia(contact->id(), info);
            });
        }
    }
#endif

    for (int i = 0; i < m_contactsModel->rowCount(); ++i) {
        const SContact *contact = m_contactsModel->contactAt(i);
        QAction *a = forwardMenu->addAction(CContactModel::getContactName(*contact));
        connect(a, &QAction::triggered, [=]() {
            m_backend->messagingApi()->forwardMessage(contact->id(), message->peer(), message->id);
        });
    }

    menu->popup(ui->messagingView->mapToGlobal(pos));
}

void MainWindow::onSearchCustomMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->contactSearchResult->currentIndex();
    if (!index.isValid()) {
        return;
    }

    static QMenu *menu = nullptr;

    if (!menu) {
        menu = new QMenu(this);
    }

    menu->clear();

    const SContact *contact = searchResultModel()->contactAt(index.row());

    if (!contact) {
        return;
    }

    QAction *a = menu->addAction(tr("Send a message"));
    connect(a, &QAction::triggered, [=]() {
        setActiveContact(contact->id());
        ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    });

    menu->popup(ui->contactSearchResult->mapToGlobal(pos));
}

void MainWindow::on_actionShowSettings_triggered(bool checked)
{
    if (checked) {
        ui->mainSplitter->setSizes(QList<int>() << 10 << 100);
    } else {
        ui->mainSplitter->setSizes(QList<int>() << 0 << 100);
    }
}

void MainWindow::on_mainSplitter_splitterMoved(int pos, int index)
{
    Q_UNUSED(index)
    ui->actionShowSettings->setChecked(pos > 0);
}

void MainWindow::on_connectionStepButton_clicked()
{
    switch (m_appState) {
    case AppStateNone:
        break;
    case AppStateDisconnected:
        initStartConnection();
        break;
    case AppStateConnected: // Not used by TelegramQt ATM
        break;
    case AppStateAuthRequired:
        authSubmitPhoneNumber();
        break;
    case AppStateCodeRequired:
        authSubmitCode();
        break;
    case AppStateCodeSubmitted:
        break;
    case AppStatePasswordRequired:
        authSubmitPassword();
        break;
    case AppStatePasswordProvided:
    case AppStateSignedIn:
    case AppStateReady:
    case AppStateLoggedOut:
        break;
    }
}

void MainWindow::initStartConnection()
{
    TelegramNamespace::MessageFlags flags = TelegramNamespace::MessageFlagNone;
    if (ui->settingsReceivingFilterReadMessages->isChecked()) {
        flags |= TelegramNamespace::MessageFlagRead;
    }
    if (ui->settingsReceivingFilterOutMessages->isChecked()) {
        flags |= TelegramNamespace::MessageFlagOut;
    }
    if (ui->settingsReceivingFilterForwardedMessages->isChecked()) {
        flags |= TelegramNamespace::MessageFlagForwarded;
    }
//    m_backend->setMessageReceivingFilter(flags);
    if (ui->settingsProxyEnable->isChecked()) {
        QNetworkProxy proxySettings;
        proxySettings.setType(QNetworkProxy::Socks5Proxy);
        proxySettings.setUser(ui->settingsProxyUser->text());
        proxySettings.setPassword(ui->settingsProxyPassword->text());
        proxySettings.setHostName(ui->settingsProxyHost->text());
        proxySettings.setPort(ui->settingsProxyPort->value());
        m_backend->settings()->setProxy(proxySettings);
    }
//    m_backend->setUpdatesEnabled(ui->settingsUpdatesEnabled->isChecked());

    if (ui->testingDcRadio->isChecked()) {
        m_backend->settings()->setServerConfiguration({Telegram::DcOption(QLatin1String("149.154.175.10"), 443)});
    }
//    const QByteArray secretInfo = QByteArray::fromHex(ui->secretInfo->toPlainText().toLatin1());
//    if (!secretInfo.isEmpty()) {
//        m_backend->setSecretInfo(secretInfo);
//    }
    m_backend->settings()->setServerConfiguration({Telegram::DcOption(QStringLiteral("127.0.0.1"), 11443)});
    m_backend->settings()->setServerConfiguration({Telegram::DcOption(QStringLiteral("192.168.2.8"), 11443)});
    const Telegram::RsaKey key = Telegram::RsaKey::fromFile(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first() + QStringLiteral("/TelegramServer/public_key.pem"));
//    const Telegram::RsaKey key = m_backend->defaultServerPublicRsaKey();
    if (!key.isValid()) {
        qCritical() << "Unable to read RSA key";
    }
    m_backend->settings()->setServerRsaKey(key);

    Telegram::Client::AuthOperation *operation = m_backend->connectionApi()->startAuthentication();
    connect(operation, &Telegram::Client::AuthOperation::failed,
            this, &MainWindow::onAuthOperationFailed);

    connect(operation, &Telegram::Client::AuthOperation::phoneNumberRequired,
            this, &MainWindow::authSubmitPhoneNumber);
    connect(operation, &Telegram::Client::AuthOperation::authCodeRequired,
            this, &MainWindow::onAuthPhoneCodeRequired);
    connect(operation, &Telegram::Client::AuthOperation::registeredChanged,
            this, &MainWindow::onAuthRegisteredChanged);
    connect(operation, &Telegram::Client::AuthOperation::passwordRequired,
            this, &MainWindow::onAuthPasswordRequested);
}

void MainWindow::on_secondConnectButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabMain);
    on_connectionStepButton_clicked();
}

void MainWindow::authSubmitPhoneNumber()
{
    Telegram::Client::AuthOperation *op = m_backend->connectionApi()->getAuthenticationOperation();
    op->submitPhoneNumber(ui->phoneNumber->text());
}

void MainWindow::authSubmitCode()
{
    Telegram::Client::AuthOperation *op = m_backend->connectionApi()->getAuthenticationOperation();
    if (!m_registered) {
        op->submitName(ui->firstName->text(), ui->lastName->text());
    }
    op->submitAuthCode(ui->confirmationCode->text());
    setAppState(AppStateCodeSubmitted);
}

void MainWindow::authSubmitPassword()
{
    Telegram::Client::AuthOperation *op = m_backend->connectionApi()->getAuthenticationOperation();
    if (m_appState == AppStatePasswordRequired) {
        op->submitPassword(ui->password->text());
        setAppState(AppStatePasswordProvided);
    } else {
        qWarning() << Q_FUNC_INFO << "Password is not required";
    }
}

void MainWindow::initLogout()
{
    if (m_appState >= AppStateSignedIn) {
        // m_backend->logOut();
    } else {
        qWarning() << Q_FUNC_INFO << "Not signed in to logout";
    }
}

void MainWindow::onContactOperationFinished(Telegram::Client::PendingContactsOperation *operation)
{
    if (operation->isSucceeded()) {
        m_contactsModel->addContacts(operation->contacts());
    }
}

void MainWindow::onContactSearchOperationFinished(Telegram::Client::PendingContactsOperation *operation)
{
    if (operation->isFailed()) {
        return;
    }

    const QVector<quint32> addedContacts = Telegram::Utils::toIdList(operation->peers());
    searchResultModel()->setContactList(operation->contacts());
}

void MainWindow::getConnectionSecretInfo()
{
    // ui->secretInfo->setPlainText(m_backend->connectionSecretInfo().toHex());
}

void MainWindow::setRegistered(bool newRegistered)
{
    m_registered = newRegistered;

    ui->firstName->setDisabled(m_registered);
    ui->firstNameLabel->setDisabled(m_registered);
    ui->lastName->setDisabled(m_registered);
    ui->lastNameLabel->setDisabled(m_registered);

//    if (m_registered) {
//        ui->signButton->setText(tr("Sign in"));
//    } else {
//        ui->signButton->setText(tr("Sign up"));
//    }
}

void MainWindow::setChatCreationMode()
{
    if (m_chatCreationMode) {
        return;
    }

    m_chatCreationMode = true;

    ui->groupChatCreateChat->setText(tr("Actually create chat"));
    ui->groupChatLeaveChat->setText(tr("Abort"));
    ui->groupChatLeaveChat->show();
    ui->groupChatName->clear();

    ui->groupChatAddContactForwardMessages->hide();

    m_chatContactsModel->setFilterList(QVector<quint32>());
    updateGroupChatAddContactButtonText();
}

void MainWindow::unsetChatCreationMode()
{
    if (m_chatCreationMode) {
        m_chatCreationMode = false;

        ui->groupChatCreateChat->setText(tr("Create chat"));
        ui->groupChatLeaveChat->setText(tr("Leave chat"));
        ui->groupChatLeaveChat->hide(); // Hide as not implemented yet

        ui->groupChatAddContactForwardMessages->show();
    }
}

void MainWindow::setAppState(MainWindow::AppState newState)
{
    const auto formatName = [](const AppState state) {
        static const QMetaEnum appStateEnum = QMetaEnum::fromType<AppState>();
        return appStateEnum.key(state);
    };
    qDebug() << "Change app state from" << formatName(m_appState) << "to" << formatName(newState);
    m_appState = newState;

    ui->confirmationCode->setEnabled(m_appState == AppStateCodeRequired);
    ui->password->setEnabled(m_appState == AppStatePasswordRequired);

    ui->setStatusOnline->setVisible((m_appState >= AppStateSignedIn) && !m_workLikeAClient);
    ui->setStatusOffline->setVisible((m_appState >= AppStateSignedIn) && !m_workLikeAClient);

    ui->phoneNumber->setEnabled(m_appState < AppStateCodeRequired);
    ui->connectionStepButton->setVisible(m_appState < AppStateSignedIn);
    ui->restoreSession->setVisible(m_appState == AppStateDisconnected);

    ui->logoutButton->setVisible((m_appState == AppStateSignedIn) || (m_appState == AppStateReady));
    ui->disconnectButton->setVisible(m_appState >= AppStateConnected);

    switch (m_appState) {
    case AppStateNone:
        // Fall throught
    case AppStateDisconnected:
        ui->connectionState->setText(tr("Disconnected"));
        ui->connectionStepButton->setText(tr("Connect"));
        ui->connectionStepButton->setEnabled(true);
        ui->phoneNumber->setEnabled(true);
        ui->phoneNumber->setFocus();
        break;
    case AppStateConnected: // Not used by TelegramQT ATM
    case AppStateAuthRequired:
        ui->connectionState->setText(tr("Connected..."));
        ui->connectionStepButton->setText(tr("Send the phone number"));
        ui->connectionStepButton->setEnabled(true);
        if (m_phoneNumberSubmitted) {
            authSubmitPhoneNumber();
        } else {
            ui->phoneNumber->setFocus();
        }
        break;
    case AppStateCodeRequired:
        ui->connectionState->setText(tr("Auth code required..."));
        ui->connectionState->setText(tr("The auth code is sent..."));
        ui->connectionStepButton->setText(tr("Try the auth code"));
        ui->confirmationCode->setFocus();
        break;
    case AppStateCodeSubmitted:
        ui->connectionState->setText(tr("Trying the auth code..."));
        ui->connectionStepButton->setEnabled(false);
        ui->confirmationCode->setFocus();
        break;
    case AppStatePasswordRequired:
        ui->connectionState->setText(tr("Password required"));
        ui->connectionStepButton->setText(tr("Try the password"));
        ui->connectionStepButton->setEnabled(true);
        ui->password->setFocus();
        break;
    case AppStatePasswordProvided:
        ui->connectionStepButton->setEnabled(false);
        ui->connectionState->setText(tr("Trying the password..."));
        ui->connectionStepButton->setEnabled(false);
        break;
    case AppStateSignedIn:
        ui->connectionState->setText(tr("Signed in..."));
        if (m_workLikeAClient) {
            // TODO: m_backend->setOnlineStatus(true);
        }
        break;
    case AppStateReady:
        ui->connectionState->setText(tr("Ready"));
        // TODO: // ui->phoneNumber->setText(m_backend->selfPhone());
        updateContactList();
    {
        Telegram::UserInfo selfInfo;
        m_backend->dataStorage()->getUserInfo(&selfInfo, m_backend->dataStorage()->selfUserId());
        ui->firstName->setText(selfInfo.firstName());
        ui->lastName->setText(selfInfo.lastName());

        m_contactsModel->addContact(selfInfo.id());
    }
        break;
    case AppStateLoggedOut:
        ui->connectionState->setText(tr("Logged out"));
        break;
    default:
        break;
    }
}

void MainWindow::setUiProxyEnabled(bool enabled)
{
    ui->settingsProxyEnable->setChecked(enabled);
    ui->settingsProxyUser->setEnabled(enabled);
    ui->settingsProxyPassword->setEnabled(enabled);
    ui->settingsProxyHost->setEnabled(enabled);
    ui->settingsProxyPort->setEnabled(enabled);
}

void MainWindow::setWorkLikeAClient(bool enabled)
{
    if (m_workLikeAClient == enabled) {
        return;
    }
    m_workLikeAClient = enabled;
    updateClientUi();
}

void MainWindow::updateClientUi()
{
    ui->setStatusOffline->setVisible(!m_workLikeAClient);
    ui->setStatusOnline->setVisible(!m_workLikeAClient);
}

CContactModel *MainWindow::searchResultModel()
{
    if (!m_contactSearchResultModel) {
        m_contactSearchResultModel = new CContactModel(m_backend, this);
        ui->contactSearchResult->setModel(m_contactSearchResultModel);
    }

    return m_contactSearchResultModel;
}

void MainWindow::on_findContact_clicked()
{
    m_searchQuery = ui->currentContact->text();
    ui->contactsSplitter->setSizes(QList<int>() << 100 << 100);
    searchByUsername();
}

void MainWindow::searchByUsername()
{
    Telegram::Client::PendingContactsOperation *operation = m_backend->contactsApi()->resolveUsername(m_searchQuery);
    operation->connectToFinished(this, &MainWindow::onContactSearchOperationFinished, operation);
    searchResultModel()->clear();
}

void MainWindow::on_addContact_clicked()
{
    Telegram::Client::ContactsApi::ContactInfo info;
    info.phoneNumber = ui->currentContact->text();
    Telegram::Client::PendingContactsOperation *operation = m_backend->contactsApi()->addContacts({info});
    operation->connectToFinished(this, &MainWindow::onContactOperationFinished, operation);
    ui->currentContact->clear();
}

void MainWindow::on_deleteContact_clicked()
{
//    for (quint32 userId : m_backend->contactsApi()->contactList()) {
//        Telegram::UserInfo info;
//        m_backend->getUserInfo(&info, userId);

//        if (info.phone() == ui->currentContact->text()) {
//            m_backend->deleteContact(userId);
//            ui->currentContact->clear();
//        }
//    }
}

void MainWindow::on_dialogList_doubleClicked(const QModelIndex &index)
{
    qDebug() << Q_FUNC_INFO;
    const Telegram::Peer peer = m_dialogModel->getPeer(index);
    if (!peer.isValid()) {
        return;
    }

    qDebug() << Q_FUNC_INFO << peer;
    showDialog(peer);
}

void MainWindow::on_messagingSendButton_clicked()
{
    CMessageModel::SMessage m;
    m.setPeer(Telegram::Peer::fromUserId(m_activeContactId)); //ui->messagingContactIdentifier->text();
    m.type = TelegramNamespace::MessageTypeText;
    m.text = ui->messagingMessage->text();
    m.flags = TelegramNamespace::MessageFlagOut;
    m.id64 = m_backend->messagingApi()->sendMessage(m.peer(), m.text);

    ui->messagingMessage->clear();

    m_messagingModel->addMessage(m);
}

void MainWindow::on_messagingAttachButton_clicked()
{
    sendMedia(Telegram::Peer::fromUserId(m_activeContactId));
}

void MainWindow::on_groupChatAttachButton_clicked()
{
    sendMedia(Telegram::Peer::fromChatId(m_activeChatId));
}

void MainWindow::on_messagingMessage_textChanged(const QString &arg1)
{
    Telegram::Peer peer = Telegram::Peer::fromUserId(m_activeContactId);
    if (!arg1.isEmpty()) {
        m_backend->messagingApi()->setMessageAction(peer, TelegramNamespace::MessageActionTyping);
    } else {
        m_backend->messagingApi()->setMessageAction(peer, TelegramNamespace::MessageActionNone);
    }
}

void MainWindow::on_messagingContactIdentifier_textChanged(const QString &identifier)
{
    const SContact *contact = m_contactsModel->getContact(identifier);
    if (!contact) {
        return;
    }
    setActiveContact(contact->id());
}

void MainWindow::on_messagingGetHistoryRequest_clicked()
{
    Telegram::Client::MessageFetchOptions options;
    // options.offset = ui->groupChatGetHistoryOffset->value();
    options.limit = static_cast<quint32>(ui->groupChatGetHistoryLimit->value());
    m_backend->messagingApi()->getHistory(Telegram::Peer::fromUserId(m_activeContactId), options);
}

void MainWindow::on_groupChatGetHistoryRequest_clicked()
{
#if 0
    const Telegram::Peer chatPeer = m_chatInfoModel->getPeer(m_activeChatId);
    Telegram::Client::MessageFetchOptions options;
    // options.offset = ui->messagingGetHistoryOffset->value();
    options.limit = ui->messagingGetHistoryLimit->value();
    m_backend->messagingApi()->getHistory(chatPeer, options);
#endif
}

void MainWindow::on_phoneNumber_returnPressed()
{
    m_phoneNumberSubmitted = !ui->phoneNumber->text().isEmpty();
    if (m_appState == AppStateDisconnected) {
        initStartConnection();
    } else if (m_appState == AppStateAuthRequired) {
        authSubmitPhoneNumber();
    }
}

void MainWindow::on_confirmationCode_returnPressed()
{
    if (m_appState != AppStateCodeRequired) {
        return;
    }
    authSubmitCode();
}

void MainWindow::on_password_returnPressed()
{
    if (m_appState != AppStatePasswordRequired) {
        return;
    }
    authSubmitPassword();
}

void MainWindow::on_setStatusOnline_clicked()
{
    // m_backend->setOnlineStatus(/* online */ true);
}

void MainWindow::on_setStatusOffline_clicked()
{
    // m_backend->setOnlineStatus(/* online */ false);
}

void MainWindow::on_logoutButton_clicked()
{
    initLogout();
}

void MainWindow::on_disconnectButton_clicked()
{
    m_backend->connectionApi()->disconnectFromServer();
    // m_backend->resetConnectionData();
}

void MainWindow::on_contactListTable_doubleClicked(const QModelIndex &index)
{
    int row = m_contactListModel->mapToSource(index).row();
    const QModelIndex idIndex = m_contactsModel->index(row, CContactModel::Id);

    setActiveContact(m_contactsModel->data(idIndex).toUInt());
    ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    ui->messagingMessage->setFocus();
}

void MainWindow::on_messagingView_doubleClicked(const QModelIndex &index)
{
    const QModelIndex phoneIndex = m_messagingModel->index(index.row(), CMessageModel::Peer);

    Telegram::Peer peer = phoneIndex.data().value<Telegram::Peer>();
    setActiveContact(peer.id);
    ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    ui->messagingMessage->setFocus();
}

void MainWindow::on_groupChatChatsList_doubleClicked(const QModelIndex &index)
{
    const quint32 clickedChat = m_chatInfoModel->index(index.row(), CChatInfoModel::Id).data().toUInt();
    unsetChatCreationMode(); // Double click on chat list cancels chat creation.
    setActiveChat(clickedChat);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);

    if (ui->tabWidget->currentWidget() == ui->tabMessaging) {
        if (ui->settingsReadMessages->isChecked()) {
            readAllMessages();
        }
    }
}

void MainWindow::on_groupChatCreateChat_clicked()
{
    if (m_chatCreationMode) {
        // m_pendingChatId = m_backend->createChat(m_chatContactsModel->filter(), ui->groupChatName->text());
        qDebug() << Q_FUNC_INFO << "pending id:" << m_pendingChatId;
        unsetChatCreationMode();
        setActiveChat(0);
    } else {
        setChatCreationMode();
    }
}

void MainWindow::on_groupChatAddContact_clicked()
{
    const QString contactPhone = ui->groupChatContactPhone->text();

    if (contactPhone.isEmpty()) {
        return;
    }

    int index = m_contactsModel->indexOfContact(contactPhone);

    if (index < 0) {
        qDebug() << Q_FUNC_INFO << "Unknown contact" << contactPhone;
        return;
    }

    quint32 contactId = m_contactsModel->data(index, CContactModel::Id).toUInt();

    if (m_chatCreationMode) {
        if (m_chatContactsModel->hasContact(contactId)) {
            m_chatContactsModel->addContact(contactId);
        } else {
            m_chatContactsModel->removeContact(contactId);
        }
    } else {
        if (m_chatContactsModel->hasContact(contactId)) {
            // m_backend->addChatUser(m_activeChatId, contactId, ui->groupChatAddContactForwardMessages->value());
        } else {
//            m_core->removeChatUser(m_activeChatId, contact);
        }
    }

    ui->groupChatContactPhone->clear();
    updateGroupChatAddContactButtonText();
}

void MainWindow::on_groupChatSendButton_clicked()
{
#if 0
    CMessageModel::SMessage m;
    const Telegram::Peer peer = m_chatInfoModel->getPeer(m_activeChatId);
    m.setPeer(peer);
    // m.fromId = m_backend->selfId();
    m.type = TelegramNamespace::MessageTypeText;
    m.text = ui->groupChatMessage->text();
    m.flags = TelegramNamespace::MessageFlagOut;
    m.id64 = m_backend->messagingApi()->sendMessage(peer, m.text);

    m_chatMessagingModel->addMessage(m);
#endif
    ui->groupChatMessage->clear();
}

void MainWindow::on_groupChatMessage_textChanged(const QString &arg1)
{
    TelegramNamespace::MessageAction action = TelegramNamespace::MessageActionNone;
    if (!arg1.isEmpty()) {
        action = TelegramNamespace::MessageActionTyping;
    }
    m_backend->messagingApi()->setMessageAction(Telegram::Peer(m_activeChatId, Telegram::Peer::Chat), action);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

//    if (m_workLikeAClient) {
//        m_backend->setOnlineStatus(false);
//    }
}

void MainWindow::readAllMessages()
{
//    foreach (quint32 contactId, m_contactLastMessageList.keys()) {
//        m_backend->setMessageRead(contactId, m_contactLastMessageList.value(contactId));
//    }
}

void MainWindow::showDialog(const Telegram::Peer &peer)
{
    switch (peer.type) {
    case Telegram::Peer::User:
        setActiveContact(peer.id);
        ui->tabWidget->setCurrentWidget(ui->tabMessaging);
        break;
    case Telegram::Peer::Chat:
    case Telegram::Peer::Channel:
        setActiveChat(peer.id);
        ui->tabWidget->setCurrentWidget(ui->tabChats);
        break;
    default:
        return;
    }
}

void MainWindow::setActiveContact(quint32 userId)
{
    if (m_activeContactId == userId) {
        return;
    }
    m_activeContactId = userId;

    SContact userInfo;
    m_backend->dataStorage()->getUserInfo(&userInfo, m_activeContactId);

    ui->messagingContactIdentifier->setText(CContactModel::getContactIdentifier(userInfo));

    updateMessagingContactName();
    updateMessagingContactStatus();
    updateMessagingContactAction();
}

void MainWindow::setActiveChat(quint32 chatId)
{
    if (m_activeChatId == chatId) {
        return;
    }

    m_activeChatId = chatId;
    m_chatMessagingModel->clear();
    //updateActiveChat();
}

void MainWindow::updateMessagingContactName()
{
    SContact userInfo;
    m_backend->dataStorage()->getUserInfo(&userInfo, m_activeContactId);
    ui->messagingContactName->setText(CContactModel::getContactName(userInfo));
}

void MainWindow::updateMessagingContactStatus()
{
    SContact userInfo;
    m_backend->dataStorage()->getUserInfo(&userInfo, m_activeContactId);

    QString status;
    switch (userInfo.status()) {
    default:
    case TelegramNamespace::ContactStatusUnknown:
        status = tr("(unknown status)");
        break;
    case TelegramNamespace::ContactStatusOnline:
        status = (tr("(online)"));
        break;
    case TelegramNamespace::ContactStatusOffline:
        status = tr("(offline)");
        break;
    }

    ui->messagingContactStatus->setText(status);
}

void MainWindow::updateMessagingContactAction()
{
    const QModelIndex index = m_contactsModel->index(m_contactsModel->indexOfContact(m_activeContactId), CContactModel::TypingStatus);
    ui->messagingContactAction->setText(QLatin1Char('(') + index.data().toString().toLower() + QLatin1Char(')'));
}

void MainWindow::sendMedia(const Telegram::Peer peer)
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Attach file..."));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);

    quint32 id = 0; //m_backend->uploadFile(file.readAll(), info.fileName());

    if (!id) {
        qDebug() << Q_FUNC_INFO << "Unable to upload file" << fileName << info.fileName();
    }

    m_uploadingRequests.insert(id, peer);
}

void MainWindow::on_contactListTable_clicked(const QModelIndex &index)
{
    const QModelIndex correctIndex = m_contactsModel->index(index.row(), CContactModel::Phone);
    ui->currentContact->setText(correctIndex.data().toString());
}

static const auto c_hexSecretFileNameExtension = QStringLiteral(".tgsecret");

void MainWindow::on_secretSaveAs_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save secret info..."), QString(), tr("Telegram secret files (*%1);;Binary secret file (*)").arg(c_hexSecretFileNameExtension));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    if (ui->secretInfo->toPlainText().isEmpty()) {
        getConnectionSecretInfo();
    }

    QByteArray data = ui->secretInfo->toPlainText().toLatin1();
    if (!fileName.endsWith(c_hexSecretFileNameExtension)) {
        data = QByteArray::fromHex(data);
    }
    file.write(data);
}

void MainWindow::on_restoreSession_clicked()
{
    loadSecretFromBrowsedFile();

    if (ui->secretInfo->toPlainText().isEmpty()) {
        return;
    }

    on_connectionStepButton_clicked();
}

void MainWindow::loadSecretFromBrowsedFile()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Load secret info..."), QString(), tr("Telegram secret files (*%1);;All files (*)").arg(c_hexSecretFileNameExtension));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    if (!fileName.endsWith(c_hexSecretFileNameExtension)) {
        data = data.toHex();
    }

    ui->secretInfo->setPlainText(data);
}

void MainWindow::updateGroupChatAddContactButtonText()
{
    const QString contact = ui->groupChatContactPhone->text();
    const int index = m_contactsModel->indexOfContact(contact);
    const bool add = contact.isEmpty() || (index < 0);

    if (add) {
        ui->groupChatAddContact->setText(tr("Add contact"));
    } else {
        ui->groupChatAddContact->setText(tr("Remove contact"));
    }

    ui->groupChatAddContact->setEnabled(!contact.isEmpty());
}

void MainWindow::on_groupChatLeaveChat_clicked()
{
    if (m_chatCreationMode) {
        unsetChatCreationMode();
        setActiveChat(m_activeChatId);
    }
}
