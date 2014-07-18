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

    void on_connectButton_clicked();
    void on_authButton_clicked();

    void on_signInButton_clicked();

    void on_getContactList_clicked();

    void on_getSecretInfo_clicked();

private:
    Ui::MainWindow *ui;

    CTelegramCore *m_core;

};

#endif // MAINWINDOW_HPP
