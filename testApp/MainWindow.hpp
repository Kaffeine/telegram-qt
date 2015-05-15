/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
    void whenPhoneStatusReceived(const QString &phone, bool registered, bool invited);
    void whenPhoneCodeRequested();
    void whenAuthSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void whenContactListChanged();
    void whenAvatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);
    void whenMessageMediaDataReceived(const QString &contact, quint32 messageId, const QByteArray &data,
                                      const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);
    void whenMessageReceived(const QString &phone, const QString &message, TelegramNamespace::MessageType type, quint32 messageId, quint32 flags, quint32 timestamp);
    void whenChatMessageReceived(quint32 chatId, const QString &phone, const QString &message, TelegramNamespace::MessageType type, quint32 messageId, quint32 flags, quint32 timestamp);
    void whenContactChatTypingStatusChanged(quint32 chatId, const QString &phone, bool status);
    void whenContactTypingStatusChanged(const QString &contact, bool typingStatus);
    void whenContactStatusChanged(const QString &contact);
    void whenContactProfileChanged(const QString &contact);
    void whenChatAdded(quint32 chatId);
    void whenChatChanged(quint32 chatId);

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
    void on_messagingMessage_textChanged(const QString &arg1);
    void on_messagingContactPhone_textChanged(const QString &arg1);

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
