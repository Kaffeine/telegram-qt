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
    void whenNeedsAuthCode();
    void whenPhoneCodeIsInvalid();
    void whenAuthenticated();

    void on_connectButton_clicked();
    void on_authButton_clicked();

    void on_signInButton_clicked();

    void on_contactList_clicked();

    void on_getAuthKey_clicked();

private:
    Ui::MainWindow *ui;

    CTelegramCore *m_core;

};

#endif // MAINWINDOW_HPP
