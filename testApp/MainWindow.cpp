#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CAppInformation.hpp"
#include "CTelegramCore.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CAppInformation appInfo;
    appInfo.setAppId(0);
    appInfo.setAppHash(QLatin1String(""));
    appInfo.setAppVersion(QLatin1String("0"));
    appInfo.setDeviceInfo(QLatin1String("pc"));
    appInfo.setOsInfo(QLatin1String("GNU/Linux"));
    appInfo.setLanguageCode(QLatin1String("en"));

    m_core = new CTelegramCore(this);
    m_core->setAppInformation(&appInfo);

    connect(m_core, SIGNAL(dcConfigurationObtained()), SLOT(whenConnected()));
    connect(m_core, SIGNAL(needsAuthCode()), SLOT(whenNeedCode()));
    connect(m_core, SIGNAL(authenticated()), SLOT(whenAuthenticated()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whenConnected()
{
    ui->connectButton->setEnabled(false);

    ui->connectionState->setText(tr("Connected"));
    ui->authButton->setEnabled(true);
}

void MainWindow::whenNeedCode()
{
    ui->authButton->setEnabled(false);

    ui->confirmationCode->setEnabled(true);
    ui->confirmationCode->setFocus();
    ui->signInButton->setEnabled(true);
}

void MainWindow::whenAuthenticated()
{
    ui->signInButton->setEnabled(false);

    ui->contactList->setEnabled(true);
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
    if (ui->phoneNumber->text().isEmpty()) {
        return;
    }

    m_core->requestAuthCode(ui->phoneNumber->text());
}

void MainWindow::on_signInButton_clicked()
{
    m_core->signIn(ui->phoneNumber->text(), ui->confirmationCode->text());
}

void MainWindow::on_contactList_clicked()
{
    m_core->getContacts();
}
