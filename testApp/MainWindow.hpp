#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class CTelegramCore;

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
    void whenMessageReceived(const QString &phone, const QString &message);

    void on_connectButton_clicked();
    void on_authButton_clicked();

    void on_signButton_clicked();

    void on_getContactList_clicked();

    void on_getSecretInfo_clicked();

    void on_addContact_clicked();

    void on_messagingSendButton_clicked();

private:
    Ui::MainWindow *ui;

    CTelegramCore *m_core;

    void setRegistered(bool newRegistered);

    bool m_registered;

};

#endif // MAINWINDOW_HPP
