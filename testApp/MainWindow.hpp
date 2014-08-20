#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "TelegramNamespace.hpp"

namespace Ui {
class MainWindow;
}

class CTelegramCore;
class CContactsModel;
class CMessagingModel;

class QModelIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void whenConnected();
    void whenPhoneStatusReceived(const QString &phone, bool registered, bool invited);
    void whenPhoneCodeRequested();
    void whenPhoneCodeIsInvalid();
    void whenAuthenticated();
    void whenContactListChanged();
    void whenAvatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);
    void whenMessageReceived(const QString &phone, const QString &message, quint32 messageId);
    void whenChatMessageReceived(quint32 chatId, const QString &phone, const QString &message);
    void whenContactChatTypingStatusChanged(quint32 chatId, const QString &phone, bool status);
    void whenContactTypingStatusChanged();
    void whenChatAdded(quint32 chatId);
    void whenChatChanged(quint32 chatId);

    void on_connectButton_clicked();
    void on_authButton_clicked();

    void on_signButton_clicked();

    void on_getContactList_clicked();

    void on_getSecretInfo_clicked();

    void on_addContact_clicked();
    void on_deleteContact_clicked();

    void on_contactListTable_doubleClicked(const QModelIndex &index);
    void on_messagingView_doubleClicked(const QModelIndex &index);

    void on_setStatusOnline_clicked();
    void on_setStatusOffline_clicked();

    void on_messagingSendButton_clicked();
    void on_messagingMessage_textChanged(const QString &arg1);
    void on_messagingContactPhone_textChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_groupChatCreateChat_clicked();
    void on_groupChatAddContact_clicked();
    void on_groupChatRemoveContact_clicked();

    void on_groupChatSendButton_clicked();

    void on_groupChatMessage_textChanged(const QString &arg1);

private:
    void setRegistered(bool newRegistered);

    Ui::MainWindow *ui;

    CContactsModel *m_contactsModel;
    CMessagingModel *m_messagingModel;

    CContactsModel *m_chatContactsModel;
    CMessagingModel *m_chatMessagingModel;

    quint32 m_chatId;

    CTelegramCore *m_core;

    bool m_registered;

};

#endif // MAINWINDOW_HPP
