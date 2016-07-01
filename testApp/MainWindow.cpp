/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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
#include "CTelegramCore.hpp"
#include "CContactModel.hpp"
#include "CMessagingModel.hpp"
#include "CChatInfoModel.hpp"

#include <QCompleter>
#include <QToolTip>
#include <QStringListModel>

#include <QDebug>

#ifdef CREATE_MEDIA_FILES
#include <QDir>
#endif

#include <QFile>
#include <QFileDialog>

#include <QPixmapCache>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_core(new CTelegramCore(this)),
    m_contactsModel(new CContactsModel(m_core, this)),
    m_messagingModel(new CMessagingModel(this)),
    m_chatContactsModel(new CContactsModel(m_core, this)),
    m_chatMessagingModel(new CMessagingModel(this)),
    m_chatInfoModel(new CChatInfoModel(this)),
    m_activeChatId(0),
    m_chatCreationMode(false),
    m_registered(false),
    m_appState(AppStateNone)
{
    ui->setupUi(this);
    ui->contactListTable->setModel(m_contactsModel);
    ui->messagingView->setModel(m_messagingModel);
    ui->groupChatContacts->setModel(m_chatContactsModel);
    ui->groupChatChatsList->setModel(m_chatInfoModel);
    ui->groupChatMessagingView->setModel(m_chatMessagingModel);
    ui->groupChatMessagingView->hideColumn(CMessagingModel::Direction);

    QCompleter *comp = new QCompleter(m_contactsModel, this);
    ui->messagingContactIdentifier->setCompleter(comp);
    ui->groupChatContactPhone->setCompleter(comp);

    connect(ui->secretOpenFile, SIGNAL(clicked()), SLOT(loadSecretFromBrowsedFile()));

    // Telepathy Morse app info
    CAppInformation appInfo;
    appInfo.setAppId(14617);
    appInfo.setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
    appInfo.setAppVersion(QLatin1String("0.1"));
    appInfo.setDeviceInfo(QLatin1String("pc"));
    appInfo.setOsInfo(QLatin1String("GNU/Linux"));
    appInfo.setLanguageCode(QLatin1String("en"));

    m_core->setAppInformation(&appInfo);
    m_core->setAutoReconnection(true);

    connect(m_core, SIGNAL(connectionStateChanged(TelegramNamespace::ConnectionState)),
            SLOT(whenConnectionStateChanged(TelegramNamespace::ConnectionState)));
    connect(m_core, SIGNAL(phoneStatusReceived(QString,bool)),
            SLOT(whenPhoneStatusReceived(QString,bool)));
    connect(m_core, SIGNAL(phoneCodeRequired()),
            SLOT(whenPhoneCodeRequested()));
    connect(m_core, SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)),
            SLOT(whenAuthSignErrorReceived(TelegramNamespace::AuthSignError,QString)));
    connect(m_core, SIGNAL(contactListChanged()),
            SLOT(whenContactListChanged()));
    connect(m_core, SIGNAL(contactProfileChanged(QString)),
            SLOT(whenContactProfileChanged(QString)));
    connect(m_core, SIGNAL(avatarReceived(QString,QByteArray,QString,QString)),
            SLOT(whenAvatarReceived(QString,QByteArray,QString)));
    connect(m_core, SIGNAL(messageMediaDataReceived(QString,quint32,QByteArray,QString,TelegramNamespace::MessageType,quint32,quint32)),
            SLOT(whenMessageMediaDataReceived(QString,quint32,QByteArray,QString,TelegramNamespace::MessageType,quint32,quint32)));
    connect(m_core, SIGNAL(messageReceived(TelegramNamespace::Message)),
            SLOT(whenMessageReceived(TelegramNamespace::Message)));
    connect(m_core, SIGNAL(contactChatTypingStatusChanged(quint32,QString,TelegramNamespace::MessageAction)),
            SLOT(whenContactChatTypingStatusChanged(quint32,QString,TelegramNamespace::MessageAction)));
    connect(m_core, SIGNAL(contactTypingStatusChanged(QString,TelegramNamespace::MessageAction)),
            SLOT(whenContactTypingStatusChanged(QString,TelegramNamespace::MessageAction)));
    connect(m_core, SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)),
            SLOT(whenContactStatusChanged(QString)));
    connect(m_core, SIGNAL(sentMessageStatusChanged(QString,quint64,TelegramNamespace::MessageDeliveryStatus)),
            m_messagingModel, SLOT(setMessageDeliveryStatus(QString,quint64,TelegramNamespace::MessageDeliveryStatus)));
    connect(m_core, SIGNAL(uploadingStatusUpdated(quint32,quint32,quint32)),
            SLOT(whenUploadingStatusUpdated(quint32,quint32,quint32)));

    connect(m_core, SIGNAL(chatAdded(quint32)), SLOT(whenChatAdded(quint32)));
    connect(m_core, SIGNAL(chatChanged(quint32)), SLOT(whenChatChanged(quint32)));

    ui->groupChatContacts->hideColumn(CContactsModel::Blocked);

    ui->mainSplitter->setSizes(QList<int>() << 0 << 100);
    ui->groupChatSplitter->setSizes(QList<int>() << 550 << 450 << 300);

    ui->groupChatChatsList->setColumnWidth(CChatInfoModel::Id, 30);

    ui->blockContact->hide();
    ui->unblockContact->hide();

    ui->groupChatLeaveChat->hide();

    QFile helpFile(QLatin1String(":/USAGE"));
    helpFile.open(QIODevice::ReadOnly);
    ui->helpView->setPlainText(helpFile.readAll());

    setAppState(AppStateNone);
    updateGroupChatAddContactButtonText();

    connect(ui->groupChatContactPhone, SIGNAL(textChanged(QString)), SLOT(updateGroupChatAddContactButtonText()));

#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
    connect(ui->messagingView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(whenCustomMenuRequested(QPoint)));
#endif

    ui->groupChatAddContactForwardMessages->hide();

    ui->messagingAttachButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whenConnectionStateChanged(TelegramNamespace::ConnectionState state)
{
    switch (state) {
    case TelegramNamespace::ConnectionStateConnected:
        setAppState(AppStateConnected);
        break;
    case TelegramNamespace::ConnectionStateAuthRequired:
        setAppState(AppStateCodeRequired);
        ui->phoneNumber->setFocus();
        break;
    case TelegramNamespace::ConnectionStateAuthenticated:
        setAppState(AppStateSignedIn);

        if (ui->workLikeClient->isChecked()) {
            m_core->setOnlineStatus(true);
        }
        break;
    case TelegramNamespace::ConnectionStateReady:
        setAppState(AppStateReady);

        ui->phoneNumber->setText(m_core->selfPhone());
        ui->firstName->setText(m_core->contactFirstName(m_core->selfPhone()));
        ui->lastName->setText(m_core->contactLastName(m_core->selfPhone()));
        break;
    case TelegramNamespace::ConnectionStateDisconnected:
        setAppState(AppStateDisconnected);
        break;
    default:
        break;
    }
}

void MainWindow::whenLoggedOut(bool result)
{
    qDebug() << Q_FUNC_INFO << result;
    setAppState(AppStateLoggedOut);
}

void MainWindow::whenPhoneStatusReceived(const QString &phone, bool registered)
{
    if (phone == ui->phoneNumber->text()) {
        QString registeredText = registered ? tr("Registered") : tr("Not registered");
        ui->phoneStatus->setText(QString(QLatin1String("%1, %2")).arg(registeredText));

        setRegistered(registered);
    } else {
        qDebug() << "Warning: Received status for different phone number" << phone << registered;
    }
}

void MainWindow::whenPhoneCodeRequested()
{
    setAppState(AppStateCodeSent);
}

void MainWindow::whenAuthSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage)
{
    switch (errorCode) {
    case TelegramNamespace::AuthSignErrorPhoneNumberIsInvalid:
        if (m_appState == AppStateCodeRequested) {
            QToolTip::showText(ui->phoneNumber->mapToGlobal(QPoint(0, 0)), tr("Phone number is not valid"));
            setAppState(AppStateNone);
        }
        break;
    case TelegramNamespace::AuthSignErrorPhoneCodeIsExpired:
        QToolTip::showText(ui->confirmationCode->mapToGlobal(QPoint(0, 0)), tr("Phone code is expired"));
        break;
    case TelegramNamespace::AuthSignErrorPhoneCodeIsInvalid:
        QToolTip::showText(ui->confirmationCode->mapToGlobal(QPoint(0, 0)), tr("Phone code is invalid"));
        break;
    default:
        qDebug() << "Unknown auth sign error:" << errorMessage;
        return;
    }

    ui->confirmationCode->setFocus();
}

void MainWindow::whenContactListChanged()
{
    setContactList(m_contactsModel, m_core->contactList());
    for (int i = 0; i < ui->contactListTable->model()->rowCount(); ++i) {
        ui->contactListTable->setRowHeight(i, 64);
    }
}

void MainWindow::whenAvatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType)
{
    qDebug() << Q_FUNC_INFO << mimeType;

#ifdef CREATE_MEDIA_FILES
    QDir dir;
    dir.mkdir("avatars");

    QFile avatarFile(QString("avatars/%1.jpg").arg(contact));
    avatarFile.open(QIODevice::WriteOnly);
    avatarFile.write(data);
    avatarFile.close();
#endif

    QPixmap avatar = QPixmap::fromImage(QImage::fromData(data));

    if (avatar.isNull()) {
        return;
    }

    avatar = avatar.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmapCache::insert(m_core->contactAvatarToken(contact), avatar);

    updateAvatar(contact);
}

void MainWindow::whenMessageMediaDataReceived(const QString &contact, quint32 messageId, const QByteArray &data, const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size)
{
    qDebug() << Q_FUNC_INFO << mimeType;

    Q_UNUSED(type)

#ifdef CREATE_MEDIA_FILES
    QDir dir;
    dir.mkdir("messagesData");

    QFile mediaFile(QString("messagesData/%1-%2.%3").arg(contact)
                    .arg(messageId, 10, 10, QLatin1Char('0'))
                    .arg(mimeType.section(QLatin1Char('/'), 1, 1)));

    if (offset == 0) {
        mediaFile.open(QIODevice::WriteOnly);
    } else {
        mediaFile.open(QIODevice::Append);
    }
    mediaFile.write(data);
    mediaFile.close();

    if (mediaFile.size() != size) {
        return;
    }
    const QPixmap photo = QPixmap(mediaFile.fileName());
#else
    Q_UNUSED(contact);

    if (size > 1024 * 1024 * 1024) {
        qDebug() << "Ignore file with size more, than 1 Gb.";
        return;
    }

    QByteArray finalData;

    if (data.size() == int(size)) {
        finalData = data;
    } else {
        // Part of content
        if (offset == 0) {
            m_messageDataParts.insert(messageId, data);
        } else if (offset + data.size() == size) {
            finalData = m_messageDataParts.take(messageId);
            finalData.append(data);
        } else {
            m_messageDataParts[messageId].append(data);
        }
    }

    if (finalData.isEmpty()) {
        return;
    }

    const QPixmap photo = QPixmap::fromImage(QImage::fromData(finalData));
#endif

    if (photo.isNull()) {
        return;
    }

    int row = m_messagingModel->setMessageMediaData(messageId, photo);
    if (row >= 0) {
        ui->messagingView->setColumnWidth(CMessagingModel::Message, photo.width());
        ui->messagingView->setRowHeight(row, photo.height());
    } else {
        row = m_chatMessagingModel->setMessageMediaData(messageId, photo);
        if (row >= 0) {
            ui->groupChatMessagingView->setColumnWidth(CMessagingModel::Message, photo.width());
            ui->groupChatMessagingView->setRowHeight(row, photo.height());
        }
    }
}

void MainWindow::whenMessageReceived(const TelegramNamespace::Message &message)
{
    bool groupChatMessage = message.peer.startsWith(QLatin1String("chat"));
    if (groupChatMessage) {
        if (message.peer != QString("chat%1").arg(m_activeChatId)) {
            return;
        }
    }

    TelegramNamespace::Message processedMessage = message;

    switch (processedMessage.type) {
    case TelegramNamespace::MessageTypePhoto:
    case TelegramNamespace::MessageTypeVideo:
        m_core->requestMessageMediaData(processedMessage.id);
        break;
    case TelegramNamespace::MessageTypeGeo: {
        TelegramNamespace::MessageMediaInfo info;
        m_core->getMessageMediaInfo(&info, processedMessage.id);
        processedMessage.text = QString("%1%2, %3%4").arg(info.latitude()).arg(QChar(0x00b0)).arg(info.longitude()).arg(QChar(0x00b0));
    }
        break;
    default:
        break;
    }

    if (groupChatMessage) {
        m_chatMessagingModel->addMessage(processedMessage);
    } else {
        m_messagingModel->addMessage(processedMessage);

        if (!(processedMessage.flags & TelegramNamespace::MessageFlagOut) && (m_contactLastMessageList.value(processedMessage.contact) < processedMessage.id)) {
            m_contactLastMessageList.insert(processedMessage.contact, processedMessage.id);

            if (ui->settingsReadMessages->isChecked()) {
                if (ui->tabWidget->currentWidget() == ui->tabMessaging) {
                    m_core->setMessageRead(processedMessage.contact, processedMessage.id);
                }
            }
        }
    }
}

void MainWindow::whenContactChatTypingStatusChanged(quint32 chatId, const QString &phone, TelegramNamespace::MessageAction action)
{
    if (m_activeChatId != chatId) {
        return;
    }

    m_chatContactsModel->setTypingStatus(phone, action);
}

void MainWindow::whenContactTypingStatusChanged(const QString &contact, TelegramNamespace::MessageAction action)
{
    m_contactsModel->setTypingStatus(contact, action);
    updateMessagingContactAction();
}

void MainWindow::whenContactStatusChanged(const QString &contact)
{
    m_contactsModel->setContactStatus(contact, m_core->contactStatus(contact));
    m_contactsModel->setContactLastOnline(contact, m_core->contactLastOnline(contact));
    m_chatContactsModel->setContactStatus(contact, m_core->contactStatus(contact));
    m_chatContactsModel->setContactLastOnline(contact, m_core->contactLastOnline(contact));

    if (contact == ui->messagingContactIdentifier->text()) {
        updateMessagingContactStatus();
    }
}

void MainWindow::whenContactProfileChanged(const QString &contact)
{
    m_contactsModel->setContactFullName(contact, m_core->contactFirstName(contact) + QLatin1Char(' ') + m_core->contactLastName(contact));
    m_contactsModel->setContactUserName(contact, m_core->contactUserName(contact));
    m_chatContactsModel->setContactFullName(contact, m_core->contactFirstName(contact) + QLatin1Char(' ') + m_core->contactLastName(contact));
    m_chatContactsModel->setContactUserName(contact, m_core->contactUserName(contact));

    if (contact == ui->messagingContactIdentifier->text()) {
        updateMessagingContactName();
    }
}

void MainWindow::whenChatAdded(quint32 chatId)
{
    m_chatInfoModel->addChat(chatId);
    setActiveChat(chatId);
//    whenChatChanged(chatId);
}

void MainWindow::whenChatChanged(quint32 chatId)
{
    if (!m_chatInfoModel->haveChat(chatId)) {
        // Workaround for temporary TelegramQt issues
        m_chatInfoModel->addChat(chatId);
    }

    TelegramNamespace::GroupChat chat;
    if (m_core->getChatInfo(&chat, chatId)) {
        m_chatInfoModel->setChat(chat);
    }

    if (chatId != m_activeChatId) {
        return;
    }

    ui->groupChatName->setText(chat.title);

    QStringList participants;
    if (!m_core->getChatParticipants(&participants, chatId)) {
        qDebug() << Q_FUNC_INFO << "Unable to get chat participants. Invalid chat?";
    }

    setContactList(m_chatContactsModel, participants);
    for (int i = 0; i < participants.count(); ++i) {
        ui->groupChatContacts->setRowHeight(i, 64);
    }
    updateGroupChatAddContactButtonText();
}

void MainWindow::whenUploadingStatusUpdated(quint32 requestId, quint32 currentOffset, quint32 size)
{
    if (currentOffset == size) {
        statusBar()->showMessage(tr("Request %1 completed.").arg(requestId).arg(currentOffset).arg(size));

//        quint64 id = m_core->sendMedia(m_uploadingRequests.value(requestId), requestId, TelegramNamespace::MessageTypePhoto);
//        m_messagingModel->addMessage(ui->messagingContactIdentifier->text(), tr("Photo %1").arg(requestId), TelegramNamespace::MessageTypePhoto, /* outgoing */ true, id);
    } else {
        statusBar()->showMessage(tr("Request %1 status updated (%2/%3).").arg(requestId).arg(currentOffset).arg(size));
    }
}

void MainWindow::whenCustomMenuRequested(const QPoint &pos)
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

    quint32 row = index.row();
    quint32 messageId = m_messagingModel->rowData(row, CMessagingModel::MessageId).toUInt();
    if (m_messagingModel->messageAt(row)->type == TelegramNamespace::MessageTypeText) {
        resendMenu->setDisabled(true);
    } else {
        resendMenu->setEnabled(true);
        for (int i = 0; i < m_contactsModel->rowCount(); ++i) {
            QAction *a = resendMenu->addAction(m_contactsModel->contactAt(i, /* addName */ true));
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
            connect(a, &QAction::triggered, [=]() {
                TelegramNamespace::MessageMediaInfo info;
                m_core->getMessageMediaInfo(&info, messageId);
                m_core->sendMedia(m_contactsModel->contactAt(i, false), info);
            });
#endif
        }
    }

    for (int i = 0; i < m_contactsModel->rowCount(); ++i) {
        QAction *a = forwardMenu->addAction(m_contactsModel->contactAt(i, /* addName */ true));
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
        connect(a, &QAction::triggered, [=]() { m_core->forwardMessage(m_contactsModel->contactAt(i, false), messageId); });
#endif
    }

    menu->popup(ui->messagingView->mapToGlobal(pos));
}

void MainWindow::on_connectButton_clicked()
{
    QByteArray secretInfo = QByteArray::fromHex(ui->secretInfo->toPlainText().toLatin1());

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
    m_core->setMessageReceivingFilter(flags);
    m_core->setAcceptableMessageTypes(TelegramNamespace::MessageTypeText|TelegramNamespace::MessageTypePhoto|TelegramNamespace::MessageTypeGeo);

    QVector<TelegramNamespace::DcOption> testServers;
    testServers << TelegramNamespace::DcOption(QLatin1String("149.154.175.10"), 443);

    if (secretInfo.isEmpty())
        if (ui->mainDcRadio->isChecked()) {
            m_core->initConnection();
        } else {
            m_core->initConnection(testServers);
        }
    else {
        m_core->restoreConnection(secretInfo);
    }
}

void MainWindow::on_secondConnectButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabMain);
    on_connectButton_clicked();
}

void MainWindow::on_requestCode_clicked()
{
    if (ui->phoneNumber->text().isEmpty()) {
        return;
    }

    m_core->requestPhoneStatus(ui->phoneNumber->text());
    m_core->requestPhoneCode(ui->phoneNumber->text());

    m_appState = AppStateCodeRequested;
}

void MainWindow::on_signButton_clicked()
{
    if (m_appState >= AppStateSignedIn) {
        m_core->logOut();
    } else {
        if (m_registered) {
            m_core->signIn(ui->phoneNumber->text(), ui->confirmationCode->text());
        } else {
            m_core->signUp(ui->phoneNumber->text(), ui->confirmationCode->text(), ui->firstName->text(), ui->lastName->text());
        }
    }
}

void MainWindow::on_getSecretInfo_clicked()
{
    ui->secretInfo->setPlainText(m_core->connectionSecretInfo().toHex());
}

void MainWindow::setRegistered(bool newRegistered)
{
    m_registered = newRegistered;

    ui->firstName->setDisabled(m_registered);
    ui->firstNameLabel->setDisabled(m_registered);
    ui->lastName->setDisabled(m_registered);
    ui->lastNameLabel->setDisabled(m_registered);

    if (m_registered) {
        ui->signButton->setText(tr("Sign in"));
    } else {
        ui->signButton->setText(tr("Sign up"));
    }
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

    m_chatContactsModel->clear();
    updateGroupChatAddContactButtonText();
}

void MainWindow::unsetChatCreationMode(quint32 newActiveChat)
{
    if (m_chatCreationMode) {
        m_chatCreationMode = false;

        ui->groupChatCreateChat->setText(tr("Create chat"));
        ui->groupChatLeaveChat->setText(tr("Leave chat"));
        ui->groupChatLeaveChat->hide(); // Hide as not implemented yet

        ui->groupChatAddContactForwardMessages->show();
    }
    setActiveChat(newActiveChat);
}

void MainWindow::setAppState(MainWindow::AppState newState)
{
    m_appState = newState;

    ui->confirmationCode->setEnabled(m_appState == AppStateCodeSent);

    ui->setStatusOnline->setVisible(m_appState >= AppStateSignedIn);
    ui->setStatusOffline->setVisible(m_appState >= AppStateSignedIn);

    ui->phoneNumber->setEnabled(m_appState < AppStateCodeSent);

    if (m_appState > AppStateSignedIn) {
        ui->signButton->setText(tr("Log out"));
        ui->signButton->setToolTip(tr("Destroy current auth session."));
    } else {
        setRegistered(m_registered);
    }

    switch (m_appState) {
    case AppStateDisconnected:
        ui->connectionState->setText(tr("Disconnected"));
        // Fall throught
    case AppStateNone:
        ui->connectButton->setVisible(true);
        ui->restoreSession->setVisible(true);

        ui->phoneNumber->setEnabled(true);

        ui->requestCode->setVisible(false);
        ui->signButton->setVisible(false);
        break;
    case AppStateConnected:
        ui->connectionState->setText(tr("Connected..."));
        break;
    case AppStateCodeRequired:
        ui->connectionState->setText(tr("Auth required"));
        ui->connectButton->setVisible(false);
        ui->restoreSession->setVisible(false);
        ui->requestCode->setVisible(true);
        ui->signButton->setVisible(true);
        break;
    case AppStateCodeSent:
        ui->connectionState->setText(tr("Code sent..."));
        ui->confirmationCode->setFocus();
        break;
    case AppStateSignedIn:
        ui->connectionState->setText(tr("Signed in..."));
        ui->requestCode->setVisible(false);
        ui->signButton->setVisible(true); // Logout button

        ui->phoneNumber->setEnabled(false);
        break;
    case AppStateReady:
        ui->connectionState->setText(tr("Ready"));
        ui->requestCode->setVisible(false);
        ui->signButton->setVisible(true); // Logout button

        ui->phoneNumber->setEnabled(false);
        break;
    case AppStateLoggedOut:
        ui->connectionState->setText(tr("Logged out"));
        break;
    default:
        break;
    }
}

void MainWindow::on_addContact_clicked()
{
    m_core->addContact(ui->currentContact->text());
    ui->currentContact->clear();
}

void MainWindow::on_deleteContact_clicked()
{
    m_core->deleteContact(ui->currentContact->text());
    ui->currentContact->clear();
}

void MainWindow::on_messagingSendButton_clicked()
{
    quint64 id = m_core->sendMessage(ui->messagingContactIdentifier->text(), ui->messagingMessage->text());

    CMessagingModel::SMessage m;
    m.peer = ui->messagingContactIdentifier->text();
    m.contact = ui->messagingContactIdentifier->text();
    m.type = TelegramNamespace::MessageTypeText;
    m.text = ui->messagingMessage->text();
    m.flags = TelegramNamespace::MessageFlagOut;
    m.id64 = id;

    ui->messagingMessage->clear();

    m_messagingModel->addMessage(m);
}

void MainWindow::on_messagingAttachButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Attach file..."));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);

    quint32 id = 0; //m_core->uploadFile(file.readAll(), info.completeBaseName());

    if (!id) {
        qDebug() << Q_FUNC_INFO << "Unable to upload file" << fileName;
    }

    m_uploadingRequests.insert(id, ui->messagingContactIdentifier->text());
}

void MainWindow::on_messagingMessage_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) {
        m_core->setTyping(ui->messagingContactIdentifier->text(), TelegramNamespace::MessageActionTyping);
    } else {
        m_core->setTyping(ui->messagingContactIdentifier->text(), TelegramNamespace::MessageActionNone);
    }
}

void MainWindow::on_messagingContactIdentifier_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    updateMessagingContactName();
    updateMessagingContactStatus();
    updateMessagingContactAction();
}

void MainWindow::on_messagingGetHistoryRequest_clicked()
{
    m_core->requestHistory(ui->messagingContactIdentifier->text(), ui->messagingGetHistoryOffset->value(), ui->messagingGetHistoryLimit->value());
}

void MainWindow::on_groupChatGetHistoryRequest_clicked()
{
    const QString peer = QString(QLatin1String("chat%1")).arg(m_activeChatId);
    m_core->requestHistory(peer, ui->groupChatGetHistoryOffset->value(), ui->groupChatGetHistoryLimit->value());
}

void MainWindow::on_setStatusOnline_clicked()
{
    m_core->setOnlineStatus(/* online */ true);
}

void MainWindow::on_setStatusOffline_clicked()
{
    m_core->setOnlineStatus(/* online */ false);
}

void MainWindow::on_contactListTable_doubleClicked(const QModelIndex &index)
{
    const QModelIndex phoneIndex = m_contactsModel->index(index.row(), CContactsModel::Phone);

    setMessagingTabContact(m_contactsModel->data(phoneIndex).toString());
    ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    ui->messagingMessage->setFocus();
}

void MainWindow::on_messagingView_doubleClicked(const QModelIndex &index)
{
    const QModelIndex phoneIndex = m_messagingModel->index(index.row(), CMessagingModel::Contact);

    setMessagingTabContact(m_messagingModel->data(phoneIndex).toString());
    ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    ui->messagingMessage->setFocus();
}

void MainWindow::on_groupChatChatsList_doubleClicked(const QModelIndex &index)
{
    const quint32 clickedChat = m_chatInfoModel->index(index.row(), CChatInfoModel::Id).data().toUInt();
    unsetChatCreationMode(clickedChat); // Double click on chat list cancels chat creation.
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
        unsetChatCreationMode(m_core->createChat(m_chatContactsModel->contacts(), ui->groupChatName->text()));
    } else {
        setChatCreationMode();
    }
}

void MainWindow::on_groupChatAddContact_clicked()
{
    const QString contact = ui->groupChatContactPhone->text();

    if (contact.isEmpty()) {
        return;
    }

    bool add = m_chatContactsModel->indexOfContact(contact) < 0;

    if (m_chatCreationMode) {
        if (add) {
            m_chatContactsModel->addContact(contact);
        } else {
            m_chatContactsModel->removeContact(contact);
        }
    } else {
        if (add) {
            m_core->addChatUser(m_activeChatId, contact, ui->groupChatAddContactForwardMessages->value());
        } else {
//            m_core->removeChatUser(m_activeChatId, contact);
        }
    }

    ui->groupChatContactPhone->clear();
    updateGroupChatAddContactButtonText();
}

void MainWindow::on_groupChatSendButton_clicked()
{
    CMessagingModel::SMessage m;
    m.peer = QString("chat%1").arg(m_activeChatId);
    m.contact = m_core->selfPhone();
    m.type = TelegramNamespace::MessageTypeText;
    m.text = ui->groupChatMessage->text();
    m.flags = TelegramNamespace::MessageFlagOut;
    m.id64 = m_core->sendMessage(m.peer, m.text);

    m_chatMessagingModel->addMessage(m);
    ui->groupChatMessage->clear();
}

void MainWindow::on_groupChatMessage_textChanged(const QString &arg1)
{
    m_core->setChatTyping(m_activeChatId, !arg1.isEmpty());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    if (ui->workLikeClient->isChecked()) {
        m_core->setOnlineStatus(false);
    }
}

void MainWindow::readAllMessages()
{
    foreach (const QString &contact, m_contactLastMessageList.keys()) {
        m_core->setMessageRead(contact, m_contactLastMessageList.value(contact));
    }
}

void MainWindow::setContactList(CContactsModel *contactsModel, const QStringList &newContactList)
{
    contactsModel->setContactList(newContactList);

    foreach (const QString &contact, newContactList) {
        updateAvatar(contact);
        contactsModel->setContactStatus(contact, m_core->contactStatus(contact));
        contactsModel->setContactLastOnline(contact, m_core->contactLastOnline(contact));
        contactsModel->setContactUserName(contact, m_core->contactUserName(contact));
        contactsModel->setContactFullName(contact, m_core->contactFirstName(contact) + QLatin1Char(' ') + m_core->contactLastName(contact));
    }
}

void MainWindow::updateAvatar(const QString &contact)
{
    const QString token = m_core->contactAvatarToken(contact);
    QPixmap avatar;

    if (QPixmapCache::find(token, &avatar)) {
        m_contactsModel->setContactAvatar(contact, avatar);
        m_chatContactsModel->setContactAvatar(contact, avatar);
    } else {
        m_core->requestContactAvatar(contact);
    }
}

void MainWindow::setMessagingTabContact(const QString &contact)
{
    ui->messagingContactIdentifier->setText(contact);
    updateMessagingContactName();
    updateMessagingContactStatus();
}

void MainWindow::updateMessagingContactName()
{
    const QString contact = ui->messagingContactIdentifier->text();
    QString name = m_core->contactUserName(contact);
    if (name.isEmpty()) {
        name = m_core->contactFirstName(contact) + m_core->contactLastName(contact);
    }

    if (name.simplified().isEmpty()) {
        name = tr("Unknown name");
    }

    ui->messagingContactName->setText(name);
}

void MainWindow::updateMessagingContactStatus()
{
    const QString contact = ui->messagingContactIdentifier->text();
    QString status;
    switch (m_core->contactStatus(contact)) {
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
    const QString contact = ui->messagingContactIdentifier->text();
    const QModelIndex index = m_contactsModel->index(m_contactsModel->indexOfContact(contact), CContactsModel::TypingStatus);
    ui->messagingContactAction->setText(QLatin1Char('(') + index.data().toString().toLower() + QLatin1Char(')'));
}

void MainWindow::on_contactListTable_clicked(const QModelIndex &index)
{
    const QModelIndex correctIndex = m_contactsModel->index(index.row(), CContactsModel::Phone);
    ui->currentContact->setText(correctIndex.data().toString());
}

void MainWindow::on_secretSaveAs_clicked()
{
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save secret info..."), QString(), tr("Telegram secret files (*.tgsecret)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    file.write(ui->secretInfo->toPlainText().toLatin1());
}

void MainWindow::setActiveChat(quint32 id)
{
    m_activeChatId = id;

    TelegramNamespace::GroupChat chat;
    m_core->getChatInfo(&chat, id);
    ui->groupChatName->setText(chat.title);

    QStringList participants;
    if (!m_core->getChatParticipants(&participants, id)) {
        qDebug() << Q_FUNC_INFO << "Unable to get chat participants. Invalid chat?";
    }

    setContactList(m_chatContactsModel, participants);
    for (int i = 0; i < m_chatContactsModel->rowCount(); ++i) {
        ui->groupChatContacts->setRowHeight(i, 64);
    }
    updateGroupChatAddContactButtonText();
}

void MainWindow::on_restoreSession_clicked()
{
    loadSecretFromBrowsedFile();

    if (ui->secretInfo->toPlainText().isEmpty()) {
        return;
    }

    on_connectButton_clicked();
}

void MainWindow::loadSecretFromBrowsedFile()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Load secret info..."), QString(), tr("Telegram secret files (*.tgsecret);;All files (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    ui->secretInfo->setPlainText(file.readAll());
}

void MainWindow::updateGroupChatAddContactButtonText()
{
    const QString contact = ui->groupChatContactPhone->text();

    bool add = contact.isEmpty() || m_chatContactsModel->indexOfContact(contact) < 0;

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
        unsetChatCreationMode(m_activeChatId);
    }
}
