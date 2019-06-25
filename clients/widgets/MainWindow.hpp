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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>

#include "TelegramNamespace.hpp"
#include "ConnectionApi.hpp"

namespace Ui {
class MainWindow;
}

class CTelegramCore;
class CContactModel;
class CDialogModel;
class CMessageModel;
class CContactsFilterModel;
class CChatInfoModel;
class CFileManager;

class QModelIndex;

namespace Telegram {

namespace Client {

class Client;
class PendingContactsOperation;

} // Client namespace

} // Telegram namespace

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum AppState {
        AppStateNone,
        AppStateDisconnected,
        AppStateConnected,
        AppStateAuthRequired,
        AppStateCodeRequired,
        AppStateCodeSubmitted,
        AppStatePasswordRequired,
        AppStatePasswordProvided,
        AppStateSignedIn,
        AppStateReady,
        AppStateLoggedOut,
    };
    Q_ENUM(AppState)

protected slots:
    void onConnectionStateChanged(Telegram::Client::ConnectionApi::Status status);
    void onAuthOperationFailed(Telegram::PendingOperation *operation, const QVariantHash &details);
    void onLoggedOut(bool result);
    void onAuthPhoneCodeRequired();
    void onAuthRegisteredChanged(bool registered);
    void onAuthPasswordRequested();
    void onAuthSignErrorReceived(TelegramNamespace::AuthenticationError errorCode, const QString &errorMessage);
    void updateContactList();
    void onMessageReceived(const Telegram::Peer peer, quint32 messageId);
    void onContactChatMessageActionChanged(quint32 chatId, quint32 userId, TelegramNamespace::MessageAction action);
    void onContactMessageActionChanged(quint32 userId, TelegramNamespace::MessageAction action);
    void onContactStatusChanged(quint32 contact);
#if 0
    void onCreatedChatIdResolved(quint64 requestId, quint32 chatId);
    void onChatChanged(quint32 chatId);
    void updateActiveChat();

    void onUploadingStatusUpdated(quint32 requestId, quint32 currentOffset, quint32 size);
    void onFileRequestFinished(quint32 requestId, Telegram::RemoteFile info);
#endif
    void onUserNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status);

    void onCustomMenuRequested(const QPoint &pos);
    void onSearchCustomMenuRequested(const QPoint &pos);

    void on_actionShowSettings_triggered(bool checked);
    void on_mainSplitter_splitterMoved(int pos, int index);
    void on_connectionStepButton_clicked();
    void on_secondConnectButton_clicked();

    void getConnectionSecretInfo();

    void on_addContact_clicked();
    void on_deleteContact_clicked();

    void on_dialogList_doubleClicked(const QModelIndex &index);
    void on_contactListTable_doubleClicked(const QModelIndex &index);
    void on_messagingView_doubleClicked(const QModelIndex &index);
    void on_groupChatChatsList_doubleClicked(const QModelIndex &index);

    void on_phoneNumber_returnPressed();
    void on_confirmationCode_returnPressed();
    void on_password_returnPressed();
    void on_setStatusOnline_clicked();
    void on_setStatusOffline_clicked();
    void on_logoutButton_clicked();
    void on_disconnectButton_clicked();

    void on_messagingSendButton_clicked();
    void on_messagingAttachButton_clicked();
    void on_groupChatAttachButton_clicked();
    void on_messagingMessage_textChanged(const QString &arg1);
    void on_messagingContactIdentifier_textChanged(const QString &identifier);
    void on_messagingGetHistoryRequest_clicked();
    void on_groupChatGetHistoryRequest_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_groupChatCreateChat_clicked();
    void on_groupChatAddContact_clicked();

    void on_groupChatSendButton_clicked();

    void on_groupChatMessage_textChanged(const QString &arg1);

    void on_contactListTable_clicked(const QModelIndex &index);

    void on_secretSaveAs_clicked();

protected:
    void closeEvent(QCloseEvent *event);

    void readAllMessages();

    void showDialog(const Telegram::Peer &peer);
    void setActiveContact(quint32 userId);
    void setActiveChat(quint32 chatId);
    void updateMessagingContactName();
    void updateMessagingContactStatus();
    void updateMessagingContactAction();

    void sendMedia(const Telegram::Peer peer);

    void initStartConnection();
    void authSubmitPhoneNumber();
    void authSubmitCode();
    void authSubmitPassword();
    void initLogout();

    void onContactOperationFinished(Telegram::Client::PendingContactsOperation *operation);
    void onContactSearchOperationFinished(Telegram::Client::PendingContactsOperation *operation);

private slots:
    void on_restoreSession_clicked();

    void loadSecretFromBrowsedFile();

    void updateGroupChatAddContactButtonText();

    void on_groupChatLeaveChat_clicked();

    void on_findContact_clicked();
    void setUiProxyEnabled(bool enabled);
    void setWorkLikeAClient(bool enabled);
    void updateClientUi();

private:
    void searchByUsername();
    void setRegistered(bool newRegistered);
    void setChatCreationMode();
    void unsetChatCreationMode();

    void setAppState(AppState newState);

    CContactModel *searchResultModel();

    Ui::MainWindow *ui = nullptr;

    Telegram::Client::Client *m_backend = nullptr;

    QMap<quint32,quint64> m_contactLastMessageList;
    QMap<quint32, Telegram::Peer> m_uploadingRequests;

    CFileManager *m_fileManager = nullptr;
    CContactModel *m_contactsModel = nullptr;
    CContactsFilterModel *m_contactListModel = nullptr;
    CDialogModel *m_dialogModel = nullptr;
    CMessageModel *m_messagingModel = nullptr;

    CContactsFilterModel *m_chatContactsModel = nullptr;
    CMessageModel *m_chatMessagingModel = nullptr;

    CChatInfoModel *m_chatInfoModel = nullptr;
    CContactModel *m_contactSearchResultModel = nullptr;
    QString m_searchQuery;

    quint32 m_activeContactId;
    quint32 m_activeChatId;
    quint64 m_pendingChatId;
    bool m_chatCreationMode;

    bool m_registered = false;
    bool m_workLikeAClient;
    bool m_phoneNumberSubmitted = false;

    AppState m_appState;

};

#endif // MAINWINDOW_HPP
