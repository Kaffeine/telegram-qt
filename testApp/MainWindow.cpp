#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CAppInformation.hpp"
#include "CTelegramCore.hpp"

#include <QToolTip>
#include <QStringListModel>

#include <QDebug>

#include <QDir>
#include <QFile>

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

    connect(m_core, SIGNAL(connected()), SLOT(whenConnected()));
    connect(m_core, SIGNAL(phoneStatusReceived(QString,bool,bool)), SLOT(whenPhoneStatusReceived(QString,bool,bool)));
    connect(m_core, SIGNAL(phoneCodeRequired()), SLOT(whenPhoneCodeRequested()));
    connect(m_core, SIGNAL(phoneCodeIsInvalid()), SLOT(whenPhoneCodeIsInvalid()));
    connect(m_core, SIGNAL(authenticated()), SLOT(whenAuthenticated()));
    connect(m_core, SIGNAL(contactListChanged()), SLOT(whenContactListChanged()));
    connect(m_core, SIGNAL(avatarReceived(QString,QByteArray,QString)), SLOT(whenAvatarReceived(QString,QByteArray,QString)));
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

void MainWindow::whenPhoneStatusReceived(const QString &phone, bool registered, bool invited)
{
    if (phone == ui->phoneNumber->text()) {
        QString registeredText = registered ? tr("Registered") : tr("Not registered");
        QString invitedText = invited ? tr("invited") : tr("not invited");
        ui->phoneStatus->setText(QString(QLatin1String("%1, %2")).arg(registeredText).arg(invitedText));
    } else {
        qDebug() << "Warning: Received status for different phone number" << phone << registered << invited;
    }
}

void MainWindow::whenPhoneCodeRequested()
{
    ui->authButton->setEnabled(false);

    ui->confirmationCode->setEnabled(true);
    ui->confirmationCode->setFocus();
    ui->signInButton->setEnabled(true);
}

void MainWindow::whenPhoneCodeIsInvalid()
{
    ui->confirmationCode->setFocus();

    QToolTip::showText(ui->confirmationCode->mapToGlobal(QPoint(0, 0)), tr("Phone code is invalid"));
}

void MainWindow::whenAuthenticated()
{
    ui->signInButton->setEnabled(false);

    ui->getContactList->setEnabled(true);
}

void MainWindow::whenContactListChanged()
{
    QStringListModel *model = new QStringListModel(m_core->contactList(), ui->contactListTable);
    ui->contactListTable->setModel(model);

    foreach (const QString &contact, m_core->contactList()) {
        m_core->requestContactAvatar(contact);
    }
}

void MainWindow::whenAvatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType)
{
    Q_UNUSED(mimeType);

    QDir dir;
    dir.mkdir("avatars");

    QFile avatarFile(QString("avatars/%1.jpg").arg(contact));
    avatarFile.open(QIODevice::WriteOnly);
    avatarFile.write(data);
    avatarFile.close();
}

void MainWindow::on_connectButton_clicked()
{
    QByteArray secretInfo = QByteArray::fromHex(ui->secretInfo->toPlainText().toLatin1());

    if (ui->mainDcRadio->isChecked()) {
        // MainDC

        if (secretInfo.isEmpty())
            m_core->initConnection("173.240.5.1", 443);
        else {
            m_core->restoreConnection(secretInfo);
        }

    } else {
        // TestingDC
        m_core->initConnection("173.240.5.253", 443);
    }
}

void MainWindow::on_authButton_clicked()
{
    if (ui->phoneNumber->text().isEmpty()) {
        return;
    }

    m_core->requestPhoneStatus(ui->phoneNumber->text());
    m_core->requestPhoneCode(ui->phoneNumber->text());
}

void MainWindow::on_signInButton_clicked()
{
    m_core->signIn(ui->phoneNumber->text(), ui->confirmationCode->text());
}

void MainWindow::on_getContactList_clicked()
{
    m_core->requestContactList();
}

void MainWindow::on_getSecretInfo_clicked()
{
    ui->secretInfo->setPlainText(m_core->connectionSecretInfo().toHex());
}
