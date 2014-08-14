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
    void whenContactTypingStatusChanged();

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

private:
    void setRegistered(bool newRegistered);

    Ui::MainWindow *ui;

    CContactsModel *m_contactsModel;
    CMessagingModel *m_messagingModel;
    CTelegramCore *m_core;

    bool m_registered;

};

#endif // MAINWINDOW_HPP
