/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CTelegramCore.hpp"

#include <QDebug>

#include "CAppInformation.hpp"
#include "CTelegramDispatcher.hpp"

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_dispatcher(new CTelegramDispatcher(this)),
    m_appInfo(0)
{
    TelegramNamespace::registerTypes();

    connect(m_dispatcher, SIGNAL(connected()), SIGNAL(connected()));
    connect(m_dispatcher, SIGNAL(authenticated()), SIGNAL(authenticated()));
    connect(m_dispatcher, SIGNAL(initializated()), SIGNAL(initializated()));
    connect(m_dispatcher, SIGNAL(phoneStatusReceived(QString,bool,bool)), SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(m_dispatcher, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(m_dispatcher, SIGNAL(phoneCodeIsInvalid()), SIGNAL(phoneCodeIsInvalid()));
    connect(m_dispatcher, SIGNAL(contactListChanged()), SIGNAL(contactListChanged()));
    connect(m_dispatcher, SIGNAL(avatarReceived(QString,QByteArray,QString,QString)), SIGNAL(avatarReceived(QString,QByteArray,QString,QString)));
    connect(m_dispatcher, SIGNAL(messageReceived(QString,QString,quint32)), SIGNAL(messageReceived(QString,QString,quint32)));
    connect(m_dispatcher, SIGNAL(chatMessageReceived(quint32,QString,QString)), SIGNAL(chatMessageReceived(quint32,QString,QString)));
    connect(m_dispatcher, SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)), SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)));
    connect(m_dispatcher, SIGNAL(contactTypingStatusChanged(QString,bool)), SIGNAL(contactTypingStatusChanged(QString,bool)));
    connect(m_dispatcher, SIGNAL(contactChatTypingStatusChanged(quint32,QString,bool)), SIGNAL(contactChatTypingStatusChanged(quint32,QString,bool)));
    connect(m_dispatcher, SIGNAL(sentMessageStatusChanged(QString,quint64,TelegramNamespace::MessageDeliveryStatus)), SIGNAL(sentMessageStatusChanged(QString,quint64,TelegramNamespace::MessageDeliveryStatus)));
    connect(m_dispatcher, SIGNAL(chatAdded(quint32)), SIGNAL(chatAdded(quint32)));
    connect(m_dispatcher, SIGNAL(chatChanged(quint32)), SIGNAL(chatChanged(quint32)));
    connect(m_dispatcher, SIGNAL(authorizationErrorReceived()), SIGNAL(authorizationErrorReceived()));
}

CTelegramCore::~CTelegramCore()
{
    delete m_appInfo;
}

void CTelegramCore::setAppInformation(const CAppInformation *newAppInfo)
{
    if (!newAppInfo) {
        return;
    }

    if (m_appInfo) {
        delete m_appInfo;
    }

    m_appInfo = new CAppInformation(newAppInfo);
}

QByteArray CTelegramCore::connectionSecretInfo() const
{
    return m_dispatcher->connectionSecretInfo();
}

bool CTelegramCore::isAuthenticated()
{
    return m_dispatcher->isAuthenticated();
}

bool CTelegramCore::initConnection(const QString &address, quint32 port)
{
    if (!m_appInfo || !m_appInfo->isValid()) {
        qDebug() << "CTelegramCore: Can not init connection: App information is null or is not valid.";
        return false;
    }

    m_dispatcher->setAppInformation(m_appInfo);
    m_dispatcher->initConnection(address, port);

    return true;
}

void CTelegramCore::closeConnection()
{
    return m_dispatcher->closeConnection();
}

bool CTelegramCore::restoreConnection(const QByteArray &secret)
{
    m_dispatcher->setAppInformation(m_appInfo);
    return m_dispatcher->restoreConnection(secret);
}

void CTelegramCore::requestPhoneStatus(const QString &phoneNumber)
{
    m_dispatcher->requestPhoneStatus(phoneNumber);
}

void CTelegramCore::requestPhoneCode(const QString &phoneNumber)
{
    m_dispatcher->requestPhoneCode(phoneNumber);
}

void CTelegramCore::signIn(const QString &phoneNumber, const QString &authCode)
{
    m_dispatcher->signIn(phoneNumber, authCode);
}

void CTelegramCore::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    m_dispatcher->signUp(phoneNumber, authCode, firstName, lastName);
}

void CTelegramCore::addContacts(const QStringList &phoneNumbers)
{
    m_dispatcher->addContacts(phoneNumbers);
}

void CTelegramCore::deleteContacts(const QStringList &phoneNumbers)
{
    m_dispatcher->deleteContacts(phoneNumbers);
}

void CTelegramCore::requestContactAvatar(const QString &contact)
{
    m_dispatcher->requestContactAvatar(contact);
}

QStringList CTelegramCore::contactList() const
{
    return m_dispatcher->contactList();
}

TelegramNamespace::ContactStatus CTelegramCore::contactStatus(const QString &phone) const
{
    return m_dispatcher->contactStatus(phone);
}

QString CTelegramCore::contactFirstName(const QString &phone) const
{
    return m_dispatcher->contactFirstName(phone);
}

QString CTelegramCore::contactLastName(const QString &phone) const
{
    return m_dispatcher->contactLastName(phone);
}

QString CTelegramCore::contactAvatarToken(const QString &phone) const
{
    return m_dispatcher->contactAvatarToken(phone);
}

QStringList CTelegramCore::chatParticipants(quint32 publicChatId) const
{
    return m_dispatcher->chatParticipants(publicChatId);
}

QString CTelegramCore::selfPhone() const
{
    return m_dispatcher->selfPhone();
}

quint64 CTelegramCore::sendMessage(const QString &phone, const QString &message)
{
    return m_dispatcher->sendMessageToContact(phone, message);
}

quint64 CTelegramCore::sendChatMessage(quint32 chatId, const QString &message)
{
    return m_dispatcher->sendMessageToChat(chatId, message);
}

void CTelegramCore::setTyping(const QString &phone, bool typingStatus)
{
    m_dispatcher->setTyping(phone, typingStatus);
}

void CTelegramCore::setChatTyping(quint32 chatId, bool typingStatus)
{
    m_dispatcher->setChatTyping(chatId, typingStatus);
}

void CTelegramCore::setMessageRead(const QString &phone, quint32 messageId)
{
    m_dispatcher->setMessageRead(phone, messageId);
}

void CTelegramCore::setOnlineStatus(bool onlineStatus)
{
    m_dispatcher->setOnlineStatus(onlineStatus);
}

quint32 CTelegramCore::createChat(const QStringList &phones, const QString chatName)
{
    return m_dispatcher->createChat(phones, chatName);
}
