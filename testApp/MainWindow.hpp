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
    void whenPqReceived();
    void whenAuthChanged();

    void on_connectButton_clicked();
    void on_authButton_clicked();

    void on_dcHelpButton_clicked();

private:
    Ui::MainWindow *ui;

    CTelegramCore *m_core;

};

#endif // MAINWINDOW_HPP
