#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CAppInformation.hpp"
#include "CTelegramCore.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Telepathy Morse app info
    CAppInformation appInfo;
    appInfo.setAppId(14617);
    appInfo.setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
    appInfo.setAppVersion(QLatin1String("0.1"));
    appInfo.setDeviceInfo(QLatin1String("pc"));
    appInfo.setOsInfo(QLatin1String("GNU/Linux"));
    appInfo.setLanguageCode(QLatin1String("en"));

    m_core = new CTelegramCore(this);
    m_core->setAppInformation(&appInfo);

    connect(m_core, SIGNAL(dcConfigurationObtained()), SLOT(whenConnected()));
    connect(m_core, SIGNAL(needsAuthCode()), SLOT(whenNeedsAuthCode()));
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
    ui->phoneNumber->setFocus();
    ui->signInButton->setEnabled(true);
}

void MainWindow::whenNeedsAuthCode()
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
    QByteArray key  = QByteArray::fromHex(ui->authKey->toPlainText().toLatin1());
    QByteArray salt = QByteArray::fromHex(ui->serverSalt->text().toLatin1());

    if (ui->mainDcRadio->isChecked()) {
        // MainDC

        if (key.isEmpty() || salt.isEmpty())
            m_core->initialConnection("173.240.5.1", 443);
        else {
            m_core->initialConnection("173.240.5.1", 443, key, salt);
        }

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

void MainWindow::on_getAuthKey_clicked()
{
    ui->authKey->setPlainText(m_core->activeAuthKey().toHex());
    ui->serverSalt->setText(m_core->activeServerSalt().toHex());
}
