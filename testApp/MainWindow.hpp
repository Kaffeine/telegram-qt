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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>

#include "TelegramNamespace.hpp"

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

//#define CREATE_MEDIA_FILES

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum AppState {
        AppStateNone,
        AppStateConnected,
        AppStateCodeRequired,
        AppStateCodeRequested,
        AppStateCodeSent,
        AppStatePasswordRequired,
        AppStateSignedIn,
        AppStateReady,
        AppStateLoggedOut,
        AppStateDisconnected
    };

protected slots:
    void onConnectionStateChanged(TelegramNamespace::ConnectionState state);
    void onLoggedOut(bool result);
    void onPhoneStatusReceived(const QString &phone, bool registered);
    void onPhoneCodeRequested();
    void onPasswordInfoReceived(quint64 requestId);
    void onUnauthorizedErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);
    void onAuthSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void updateContactList();
    void onMessageReceived(const Telegram::Message &message);
    void onContactChatMessageActionChanged(quint32 chatId, quint32 userId, TelegramNamespace::MessageAction action);
    void onContactMessageActionChanged(quint32 userId, TelegramNamespace::MessageAction action);
    void onContactStatusChanged(quint32 contact);
    void onCreatedChatIdResolved(quint64 requestId, quint32 chatId);
    void onChatChanged(quint32 chatId);
    void updateActiveChat();

    void onUploadingStatusUpdated(quint32 requestId, quint32 currentOffset, quint32 size);
    void onFileRequestFinished(quint32 requestId, Telegram::RemoteFile info);
    void onUserNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status);

    void onCustomMenuRequested(const QPoint &pos);
    void onSearchCustomMenuRequested(const QPoint &pos);

    void on_connectButton_clicked();
    void on_secondConnectButton_clicked();
    void on_requestCode_clicked();

    void on_signButton_clicked();

    void getConnectionSecretInfo();

    void on_addContact_clicked();
    void on_deleteContact_clicked();

    void on_dialogList_doubleClicked(const QModelIndex &index);
    void on_contactListTable_doubleClicked(const QModelIndex &index);
    void on_messagingView_doubleClicked(const QModelIndex &index);
    void on_groupChatChatsList_doubleClicked(const QModelIndex &index);

    void on_setStatusOnline_clicked();
    void on_setStatusOffline_clicked();

    void on_messagingSendButton_clicked();
    void on_messagingAttachButton_clicked();
    void on_groupChatAttachButton_clicked();
    void on_messagingMessage_textChanged(const QString &arg1);
    void on_messagingContactIdentifier_textChanged(const QString &arg1);
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

private slots:
    void on_restoreSession_clicked();

    void loadSecretFromBrowsedFile();

    void updateGroupChatAddContactButtonText();

    void on_groupChatLeaveChat_clicked();

    void on_findContact_clicked();
    void setUiProxyEnabled(bool enabled);

private:
    void searchByUsername();
    void setRegistered(bool newRegistered);
    void setChatCreationMode();
    void unsetChatCreationMode();

    void setAppState(AppState newState);

    CContactModel *searchResultModel();

    Ui::MainWindow *ui;

    CTelegramCore *m_core;

    Telegram::PasswordInfo *m_passwordInfo;
    QMap<quint32,quint64> m_contactLastMessageList;
    QMap<quint32, Telegram::Peer> m_uploadingRequests;

    CFileManager *m_fileManager;
    CContactModel *m_contactsModel;
    CContactsFilterModel *m_contactListModel;
    CDialogModel *m_dialogModel;
    CMessageModel *m_messagingModel;

    CContactsFilterModel *m_chatContactsModel;
    CMessageModel *m_chatMessagingModel;

    CChatInfoModel *m_chatInfoModel;
    CContactModel *m_contactSearchResultModel;
    QString m_searchQuery;

    quint32 m_activeContactId;
    quint32 m_activeChatId;
    quint64 m_pendingChatId;
    bool m_chatCreationMode;

    bool m_registered;

    AppState m_appState;

#ifndef CREATE_MEDIA_FILES
    QMap<quint32,QByteArray> m_messageDataParts;
#endif

};

#endif // MAINWINDOW_HPP
