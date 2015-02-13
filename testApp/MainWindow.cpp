/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CAppInformation.hpp"
#include "CTelegramCore.hpp"
#include "CContactModel.hpp"
#include "CMessagingModel.hpp"
#include "CChatInfoModel.hpp"

#include <QCompleter>
#include <QToolTip>
#include <QStringListModel>

#include <QDebug>

#include <QDir>
#include <QFile>

#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_contactsModel(new CContactsModel(this)),
    m_messagingModel(new CMessagingModel(this)),
    m_chatContactsModel(new CContactsModel(this)),
    m_chatMessagingModel(new CMessagingModel(this)),
    m_chatInfoModel(new CChatInfoModel(this)),
    m_activeChatId(0),
    m_core(new CTelegramCore(this))
{
    ui->setupUi(this);
    ui->contactListTable->setModel(m_contactsModel);
    ui->messagingView->setModel(m_messagingModel);
    ui->groupChatContacts->setModel(m_chatContactsModel);
    ui->groupChatContacts->hideColumn(CContactsModel::Avatar);
    ui->groupChatChatsList->setModel(m_chatInfoModel);
    ui->groupChatMessagingView->setModel(m_chatMessagingModel);

    QCompleter *comp = new QCompleter(m_contactsModel, this);
    ui->messagingContactPhone->setCompleter(comp);
    ui->groupChatContactPhone->setCompleter(comp);

    // Telepathy Morse app info
    CAppInformation appInfo;
    appInfo.setAppId(14617);
    appInfo.setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
    appInfo.setAppVersion(QLatin1String("0.1"));
    appInfo.setDeviceInfo(QLatin1String("pc"));
    appInfo.setOsInfo(QLatin1String("GNU/Linux"));
    appInfo.setLanguageCode(QLatin1String("en"));

    m_core->setAppInformation(&appInfo);

    connect(m_core, SIGNAL(connected()), SLOT(whenConnected()));
    connect(m_core, SIGNAL(phoneStatusReceived(QString,bool,bool)), SLOT(whenPhoneStatusReceived(QString,bool,bool)));
    connect(m_core, SIGNAL(phoneCodeRequired()), SLOT(whenPhoneCodeRequested()));
    connect(m_core, SIGNAL(phoneCodeIsInvalid()), SLOT(whenPhoneCodeIsInvalid()));
    connect(m_core, SIGNAL(authenticated()), SLOT(whenAuthenticated()));
    connect(m_core, SIGNAL(contactListChanged()), SLOT(whenContactListChanged()));
    connect(m_core, SIGNAL(avatarReceived(QString,QByteArray,QString,QString)), SLOT(whenAvatarReceived(QString,QByteArray,QString)));
    connect(m_core, SIGNAL(messageReceived(QString,QString,quint32,quint32,quint32)), SLOT(whenMessageReceived(QString,QString,quint32,quint32,quint32)));
    connect(m_core, SIGNAL(chatMessageReceived(quint32,QString,QString,quint32,quint32,quint32)), SLOT(whenChatMessageReceived(quint32,QString,QString)));
    connect(m_core, SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)), m_contactsModel, SLOT(setContactStatus(QString,TelegramNamespace::ContactStatus)));
    connect(m_core, SIGNAL(contactTypingStatusChanged(QString,bool)), m_contactsModel, SLOT(setTypingStatus(QString,bool)));
    connect(m_core, SIGNAL(contactChatTypingStatusChanged(quint32,QString,bool)), SLOT(whenContactChatTypingStatusChanged(quint32,QString,bool)));
    connect(m_core, SIGNAL(contactTypingStatusChanged(QString,bool)), this, SLOT(whenContactTypingStatusChanged()));
    connect(m_core, SIGNAL(sentMessageStatusChanged(QString,quint64,TelegramNamespace::MessageDeliveryStatus)),
            m_messagingModel, SLOT(setMessageDeliveryStatus(QString,quint64,TelegramNamespace::MessageDeliveryStatus)));

    connect(m_core, SIGNAL(chatAdded(quint32)), SLOT(whenChatAdded(quint32)));
    connect(m_core, SIGNAL(chatChanged(quint32)), SLOT(whenChatChanged(quint32)));

    ui->groupChatContacts->hideColumn(CContactsModel::Blocked);

    ui->mainSplitter->setSizes(QList<int>() << 0 << 100);
    ui->groupChatSplitter->setSizes(QList<int>() << 550 << 450 << 300);

    ui->groupChatChatsList->setColumnWidth(CChatInfoModel::Id, 30);

    ui->blockContact->hide();
    ui->unblockContact->hide();

    QFile helpFile(QLatin1String(":/USAGE"));
    helpFile.open(QIODevice::ReadOnly);
    ui->helpView->setPlainText(helpFile.readAll());
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
    ui->connectionState->setText(tr("Signed in"));

    ui->authButton->setEnabled(false);
    ui->signButton->setEnabled(false);
    ui->phoneNumber->setText(m_core->selfPhone());

    if (ui->workLikeClient->isChecked()) {
        m_core->setOnlineStatus(true);
    }
}

void MainWindow::whenContactListChanged()
{
    m_contactsModel->setContactList(m_core->contactList());

    foreach (const QString &contact, m_core->contactList()) {
        m_core->requestContactAvatar(contact);
        m_contactsModel->setContactStatus(contact, m_core->contactStatus(contact));
        m_contactsModel->setContactFullName(contact, m_core->contactFirstName(contact) + QLatin1Char(' ') + m_core->contactLastName(contact));
    }

    for (int i = 0; i < ui->contactListTable->model()->rowCount(); ++i) {
        ui->contactListTable->setRowHeight(i, 64);
    }
}

void MainWindow::whenAvatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType)
{
    Q_UNUSED(mimeType);

    qDebug() << mimeType;
    QDir dir;
    dir.mkdir("avatars");

    QFile avatarFile(QString("avatars/%1.jpg").arg(contact));
    avatarFile.open(QIODevice::WriteOnly);
    avatarFile.write(data);
    avatarFile.close();

    m_contactsModel->setContactAvatar(contact, avatarFile.fileName());
}

void MainWindow::whenMessageReceived(const QString &phone, const QString &message, quint32 messageId, quint32 flags, quint32 timestamp)
{
    m_messagingModel->addMessage(phone, message, flags & TelegramNamespace::MessageFlagOut, messageId, timestamp);
}

void MainWindow::whenChatMessageReceived(quint32 chatId, const QString &phone, const QString &message)
{
    if (m_activeChatId != chatId) {
        return;
    }

    m_chatMessagingModel->addMessage(phone, message, /* outgoing */ false);
}

void MainWindow::whenContactChatTypingStatusChanged(quint32 chatId, const QString &phone, bool status)
{
    if (m_activeChatId != chatId) {
        return;
    }

    m_chatContactsModel->setTypingStatus(phone, status);
}

void MainWindow::whenContactTypingStatusChanged()
{
    ui->messagingContactTypingStatus->setText(m_contactsModel->data(ui->messagingContactPhone->text(), CContactsModel::TypingStatus).toString());
}

void MainWindow::whenChatAdded(quint32 chatId)
{
    m_chatInfoModel->addChat(chatId);
    setActiveChat(chatId);
    whenChatChanged(chatId);
}

void MainWindow::whenChatChanged(quint32 chatId)
{
    if (!m_chatInfoModel->haveChat(chatId)) {
        // Workaround for temporary TelegramQt issues
        m_chatInfoModel->addChat(chatId);
    }

    TelegramNamespace::GroupChat chat;
    if (m_core->getChatInfo(&chat, chatId)) {
        m_chatInfoModel->setChat(chat);
    }

    if (chatId != m_activeChatId) {
        return;
    }

    m_chatContactsModel->setContactList(m_core->chatParticipants(chatId));
}

void MainWindow::on_connectButton_clicked()
{
    QByteArray secretInfo = QByteArray::fromHex(ui->secretInfo->toPlainText().toLatin1());

    QString serverIp = ui->mainDcRadio->isChecked() ? QLatin1String("173.240.5.1") : QLatin1String("173.240.5.253");

    quint32 flags = 0;
    if (ui->settingsReceivingFilterOnlyUnreadMessages->isChecked()) {
        flags |= TelegramNamespace::MessageFlagUnread;
    }
    if (ui->settingsReceivingFilterOutMessages->isChecked()) {
        flags |= TelegramNamespace::MessageFlagOut;
    }
    m_core->setMessageReceivingFilterFlags(flags);

    if (secretInfo.isEmpty())
        m_core->initConnection(serverIp, 443);
    else {
        m_core->restoreConnection(secretInfo);
    }
}

void MainWindow::on_secondConnectButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabMain);
    on_connectButton_clicked();
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
    m_core->addContact(ui->currentContact->text());
    ui->currentContact->clear();
}

void MainWindow::on_deleteContact_clicked()
{
    m_core->deleteContact(ui->currentContact->text());
    ui->currentContact->clear();
}

void MainWindow::on_messagingSendButton_clicked()
{
    quint64 id = m_core->sendMessage(ui->messagingContactPhone->text(), ui->messagingMessage->text());

    m_messagingModel->addMessage(ui->messagingContactPhone->text(), ui->messagingMessage->text(), /* outgoing */ true, id);

    ui->messagingMessage->clear();
}

void MainWindow::on_messagingMessage_textChanged(const QString &arg1)
{
    m_core->setTyping(ui->messagingContactPhone->text(), !arg1.isEmpty());
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

void MainWindow::on_contactListTable_doubleClicked(const QModelIndex &index)
{
    const QModelIndex phoneIndex = m_contactsModel->index(index.row(), CContactsModel::Phone);

    ui->messagingContactPhone->setText(m_contactsModel->data(phoneIndex).toString());
    ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    ui->messagingMessage->setFocus();
}

void MainWindow::on_messagingView_doubleClicked(const QModelIndex &index)
{
    const QModelIndex phoneIndex = m_messagingModel->index(index.row(), CMessagingModel::Phone);

    ui->messagingContactPhone->setText(m_messagingModel->data(phoneIndex).toString());
    ui->tabWidget->setCurrentWidget(ui->tabMessaging);
    ui->messagingMessage->setFocus();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);

    if (ui->tabWidget->currentWidget() == ui->tabMessaging) {
        // TODO: Read messages
    }
}

void MainWindow::on_groupChatCreateChat_clicked()
{
    m_activeChatId = m_core->createChat(m_chatContactsModel->contacts(), ui->groupChatName->text());
    m_chatContactsModel->addContact(m_core->selfPhone());

    ui->groupChatCreateChat->setText(tr("Leave chat"));
    ui->groupChatCreateChat->setEnabled(false);
}

void MainWindow::on_groupChatAddContact_clicked()
{
    m_chatContactsModel->addContact(ui->groupChatContactPhone->text());
    ui->groupChatContactPhone->clear();
}

void MainWindow::on_groupChatRemoveContact_clicked()
{
    m_chatContactsModel->removeContact(ui->groupChatContactPhone->text());
    ui->groupChatContactPhone->clear();
}

void MainWindow::on_groupChatSendButton_clicked()
{
    m_core->sendChatMessage(1, ui->groupChatMessage->text());

    m_chatMessagingModel->addMessage(m_core->selfPhone(), ui->groupChatMessage->text(), /* outgoing */ true);
    ui->groupChatMessage->clear();
}

void MainWindow::on_groupChatMessage_textChanged(const QString &arg1)
{
    m_core->setChatTyping(m_activeChatId, !arg1.isEmpty());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    if (ui->workLikeClient->isChecked()) {
        m_core->setOnlineStatus(false);
    }
}

void MainWindow::on_contactListTable_clicked(const QModelIndex &index)
{
    const QModelIndex correctIndex = m_contactsModel->index(index.row(), CContactsModel::Phone);
    ui->currentContact->setText(correctIndex.data().toString());
}

void MainWindow::on_secretSaveAs_clicked()
{
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save secret info..."));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    file.write(ui->secretInfo->toPlainText().toLatin1());
}

void MainWindow::on_secretOpenFile_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Load secret info..."));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    ui->secretInfo->setPlainText(file.readAll());
}

void MainWindow::setActiveChat(quint32 id)
{
    m_activeChatId = id;
}
