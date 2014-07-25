#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CAppInformation.hpp"
#include "CTelegramCore.hpp"
#include "CContactModel.hpp"

#include <QCompleter>
#include <QToolTip>
#include <QStringListModel>

#include <QDebug>

#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_contactsModel(new CContactsModel(this))
{
    ui->setupUi(this);
    ui->contactListTable->setModel(m_contactsModel);

    QCompleter *comp = new QCompleter(m_contactsModel, this);
    ui->messagingContactPhone->setCompleter(comp);

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
    connect(m_core, SIGNAL(messageReceived(QString,QString)), SLOT(whenMessageReceived(QString,QString)));
    connect(m_core, SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)), m_contactsModel, SLOT(setContactStatus(QString,TelegramNamespace::ContactStatus)));
    connect(m_core, SIGNAL(contactTypingStatusChanged(QString,bool)), m_contactsModel, SLOT(setTypingStatus(QString,bool)));
    connect(m_core, SIGNAL(contactTypingStatusChanged(QString,bool)), this, SLOT(whenContactTypingStatusChanged()));
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
    ui->signButton->setEnabled(true);
}

void MainWindow::whenPhoneStatusReceived(const QString &phone, bool registered, bool invited)
{
    if (phone == ui->phoneNumber->text()) {
        QString registeredText = registered ? tr("Registered") : tr("Not registered");
        QString invitedText = invited ? tr("invited") : tr("not invited");
        ui->phoneStatus->setText(QString(QLatin1String("%1, %2")).arg(registeredText).arg(invitedText));

        setRegistered(registered);
        ui->signButton->setEnabled(true);
    } else {
        qDebug() << "Warning: Received status for different phone number" << phone << registered << invited;
    }
}

void MainWindow::whenPhoneCodeRequested()
{
    ui->authButton->setEnabled(false);

    ui->confirmationCode->setEnabled(true);
    ui->confirmationCode->setFocus();
}

void MainWindow::whenPhoneCodeIsInvalid()
{
    ui->confirmationCode->setFocus();

    QToolTip::showText(ui->confirmationCode->mapToGlobal(QPoint(0, 0)), tr("Phone code is invalid"));
}

void MainWindow::whenAuthenticated()
{
    ui->signButton->setEnabled(false);

    ui->getContactList->setEnabled(true);
}

void MainWindow::whenContactListChanged()
{
    m_contactsModel->setContactList(m_core->contactList());

    foreach (const QString &contact, m_core->contactList()) {
        m_core->requestContactAvatar(contact);
        m_contactsModel->setContactStatus(contact, m_core->contactStatus(contact));
    }

    for (int i = 0; i < ui->contactListTable->model()->rowCount(); ++i) {
        ui->contactListTable->setRowHeight(i, 64);
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

    m_contactsModel->setContactAvatar(contact, avatarFile.fileName());
}

void MainWindow::whenMessageReceived(const QString &phone, const QString &message)
{
    ui->messagingLogs->appendPlainText(QString(QLatin1String("From %1: %2\n")).arg(phone).arg(message));
}

void MainWindow::whenContactTypingStatusChanged()
{
    ui->messagingContactTypingStatus->setText(m_contactsModel->data(ui->messagingContactPhone->text(), CContactsModel::TypingStatus).toString());
}

void MainWindow::on_connectButton_clicked()
{
    QByteArray secretInfo = QByteArray::fromHex(ui->secretInfo->toPlainText().toLatin1());

    QString serverIp = ui->mainDcRadio->isChecked() ? QLatin1String("173.240.5.1") : QLatin1String("173.240.5.253");

    if (secretInfo.isEmpty())
        m_core->initConnection(serverIp, 443);
    else {
        m_core->restoreConnection(secretInfo);
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

void MainWindow::on_signButton_clicked()
{
    if (m_registered) {
        m_core->signIn(ui->phoneNumber->text(), ui->confirmationCode->text());
    } else {
        m_core->signUp(ui->phoneNumber->text(), ui->confirmationCode->text(), ui->firstName->text(), ui->lastName->text());
    }
}

void MainWindow::on_getContactList_clicked()
{
    m_core->requestContactList();
}

void MainWindow::on_getSecretInfo_clicked()
{
    ui->secretInfo->setPlainText(m_core->connectionSecretInfo().toHex());
}

void MainWindow::setRegistered(bool newRegistered)
{
    m_registered = newRegistered;

    ui->firstName->setDisabled(m_registered);
    ui->firstNameLabel->setDisabled(m_registered);
    ui->lastName->setDisabled(m_registered);
    ui->lastNameLabel->setDisabled(m_registered);

    if (m_registered) {
        ui->signButton->setText(tr("Sign in"));
    } else {
        ui->signButton->setText(tr("Sign up"));
    }
}

void MainWindow::on_addContact_clicked()
{
    m_core->addContact(ui->newContact->text());
    ui->newContact->clear();
}

void MainWindow::on_messagingSendButton_clicked()
{
    m_core->sendMessage(ui->messagingContactPhone->text(), ui->messagingMessage->text());

    ui->messagingLogs->appendPlainText(QString(QLatin1String("To %1: %2\n")).arg(ui->messagingContactPhone->text()).arg(ui->messagingMessage->text()));

    ui->messagingMessage->clear();
}

void MainWindow::on_messagingMessage_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    m_core->setTyping(ui->messagingContactPhone->text(), true);
}

void MainWindow::on_messagingContactPhone_textChanged(const QString &arg1)
{
    ui->messagingContactTypingStatus->setText(m_contactsModel->data(arg1, CContactsModel::TypingStatus).toString());
}

void MainWindow::on_setStatusOnline_clicked()
{
    m_core->setOnlineStatus(/* online */ true);
}

void MainWindow::on_setStatusOffline_clicked()
{
    m_core->setOnlineStatus(/* online */ false);
}
