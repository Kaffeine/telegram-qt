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
class CContactsModel;
class CMessagingModel;
class CChatInfoModel;

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
        AppStateSignedIn,
        AppStateReady,
        AppStateLoggedOut,
        AppStateDisconnected
    };

protected slots:
    void whenConnectionStateChanged(TelegramNamespace::ConnectionState state);
    void whenLoggedOut(bool result);
    void whenPhoneStatusReceived(const QString &phone, bool registered);
    void whenPhoneCodeRequested();
    void whenAuthSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void whenContactListChanged();
    void whenAvatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);
    void whenMessageMediaDataReceived(const QString &contact, quint32 messageId, const QByteArray &data,
                                      const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);
    void whenMessageReceived(const TelegramNamespace::Message &message);
    void whenContactChatTypingStatusChanged(quint32 chatId, const QString &phone, TelegramNamespace::MessageAction action);
    void whenContactTypingStatusChanged(const QString &contact, TelegramNamespace::MessageAction action);
    void whenContactStatusChanged(const QString &contact);
    void whenContactProfileChanged(const QString &contact);
    void whenChatAdded(quint32 chatId);
    void whenChatChanged(quint32 chatId);

    void whenUploadingStatusUpdated(quint32 requestId, quint32 currentOffset, quint32 size);

    void whenCustomMenuRequested(const QPoint &pos);

    void on_connectButton_clicked();
    void on_secondConnectButton_clicked();
    void on_requestCode_clicked();

    void on_signButton_clicked();

    void on_getSecretInfo_clicked();

    void on_addContact_clicked();
    void on_deleteContact_clicked();

    void on_contactListTable_doubleClicked(const QModelIndex &index);
    void on_messagingView_doubleClicked(const QModelIndex &index);
    void on_groupChatChatsList_doubleClicked(const QModelIndex &index);

    void on_setStatusOnline_clicked();
    void on_setStatusOffline_clicked();

    void on_messagingSendButton_clicked();
    void on_messagingAttachButton_clicked();
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

    void setActiveChat(quint32 id);

protected:
    void closeEvent(QCloseEvent *event);

    void readAllMessages();

    void setContactList(CContactsModel *contactsModel, const QStringList &newContactList);

    void getAvatar(const QString &contact);
    void updateAvatar(const QString &contact);

    void setMessagingTabContact(const QString &contact);
    void updateMessagingContactName();
    void updateMessagingContactStatus();
    void updateMessagingContactAction();

private slots:
    void on_restoreSession_clicked();

    void loadSecretFromBrowsedFile();

    void updateGroupChatAddContactButtonText();

    void on_groupChatLeaveChat_clicked();

private:
    void setRegistered(bool newRegistered);
    void setChatCreationMode();
    void unsetChatCreationMode(quint32 newActiveChat);

    void setAppState(AppState newState);

    Ui::MainWindow *ui;

    QMap<QString,quint64> m_contactLastMessageList;
    QMap<quint32, QString> m_uploadingRequests;

    CContactsModel *m_contactsModel;
    CMessagingModel *m_messagingModel;

    CContactsModel *m_chatContactsModel;
    CMessagingModel *m_chatMessagingModel;

    CChatInfoModel *m_chatInfoModel;

    quint32 m_activeChatId;
    bool m_chatCreationMode;

    CTelegramCore *m_core;

    bool m_registered;

    AppState m_appState;

#ifndef CREATE_MEDIA_FILES
    QMap<quint32,QByteArray> m_messageDataParts;
#endif

};

#endif // MAINWINDOW_HPP
