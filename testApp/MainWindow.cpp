#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CTelegramCore.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_core = new CTelegramCore(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whenConnected()
{
    ui->connectionState->setText(tr("Connected"));
}

void MainWindow::on_connectButton_clicked()
{
    if (ui->mainDcRadio->isChecked()) {
        // MainDC
        m_core->initialConnection("173.240.5.1", 443);
    } else {
        // TestingDC
        m_core->initialConnection("173.240.5.253", 443);
    }
}

void MainWindow::on_authButton_clicked()
{
//    m_core->requestAuthCode(ui->phoneNumber->text());
}
