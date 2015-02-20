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

    connect(m_dispatcher, SIGNAL(connected()),
            SIGNAL(connected()));
    connect(m_dispatcher, SIGNAL(authenticated()),
            SIGNAL(authenticated()));
    connect(m_dispatcher, SIGNAL(initializated()),
            SIGNAL(initializated()));
    connect(m_dispatcher, SIGNAL(loggedOut(bool)),
            SIGNAL(loggedOut(bool)));
    connect(m_dispatcher, SIGNAL(phoneStatusReceived(QString,bool,bool)),
            SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(m_dispatcher, SIGNAL(phoneCodeRequired()),
            SIGNAL(phoneCodeRequired()));
    connect(m_dispatcher, SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)),
            SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)));
    connect(m_dispatcher, SIGNAL(contactListChanged()),
            SIGNAL(contactListChanged()));
    connect(m_dispatcher, SIGNAL(contactProfileChanged(QString)),
            SIGNAL(contactProfileChanged(QString)));
    connect(m_dispatcher, SIGNAL(avatarReceived(QString,QByteArray,QString,QString)),
            SIGNAL(avatarReceived(QString,QByteArray,QString,QString)));
    connect(m_dispatcher, SIGNAL(messageMediaDataReceived(QString,quint32,QByteArray,QString,TelegramNamespace::MessageType)),
            SIGNAL(messageMediaDataReceived(QString,quint32,QByteArray,QString,TelegramNamespace::MessageType)));
    connect(m_dispatcher, SIGNAL(messageReceived(QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)),
            SIGNAL(messageReceived(QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)));
    connect(m_dispatcher, SIGNAL(chatMessageReceived(quint32,QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)),
            SIGNAL(chatMessageReceived(quint32,QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)));
    connect(m_dispatcher, SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)),
            SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)));
    connect(m_dispatcher, SIGNAL(contactTypingStatusChanged(QString,bool)),
            SIGNAL(contactTypingStatusChanged(QString,bool)));
    connect(m_dispatcher, SIGNAL(contactChatTypingStatusChanged(quint32,QString,bool)),
            SIGNAL(contactChatTypingStatusChanged(quint32,QString,bool)));
    connect(m_dispatcher, SIGNAL(sentMessageStatusChanged(QString,quint64,TelegramNamespace::MessageDeliveryStatus)),
            SIGNAL(sentMessageStatusChanged(QString,quint64,TelegramNamespace::MessageDeliveryStatus)));
    connect(m_dispatcher, SIGNAL(chatAdded(quint32)),
            SIGNAL(chatAdded(quint32)));
    connect(m_dispatcher, SIGNAL(chatChanged(quint32)),
            SIGNAL(chatChanged(quint32)));
    connect(m_dispatcher, SIGNAL(authorizationErrorReceived()),
            SIGNAL(authorizationErrorReceived()));
    connect(m_dispatcher, SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::AccountUserNameStatus)),
            SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::AccountUserNameStatus)));
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

bool CTelegramCore::logOut()
{
    return m_dispatcher->logOut();
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

void CTelegramCore::requestMessageMediaData(quint32 messageId)
{
    m_dispatcher->requestMessageMediaData(messageId);
}

QStringList CTelegramCore::contactList() const
{
    return m_dispatcher->contactList();
}

TelegramNamespace::ContactStatus CTelegramCore::contactStatus(const QString &contact) const
{
    return m_dispatcher->contactStatus(contact);
}

quint32 CTelegramCore::contactLastOnline(const QString &contact) const
{
    return m_dispatcher->contactLastOnline(contact);
}

QString CTelegramCore::contactFirstName(const QString &phone) const
{
    return m_dispatcher->contactFirstName(phone);
}

QString CTelegramCore::contactLastName(const QString &phone) const
{
    return m_dispatcher->contactLastName(phone);
}

QString CTelegramCore::contactUserName(const QString &contact) const
{
    return m_dispatcher->contactUserName(contact);
}

QString CTelegramCore::contactAvatarToken(const QString &phone) const
{
    return m_dispatcher->contactAvatarToken(phone);
}

QString CTelegramCore::chatTitle(quint32 chatId) const
{
    return m_dispatcher->chatTitle(chatId);
}

qint32 CTelegramCore::localTypingRecommendedRepeatInterval()
{
    return CTelegramDispatcher::localTypingRecommendedRepeatInterval();
}

bool CTelegramCore::getChatInfo(TelegramNamespace::GroupChat *chatInfo, quint32 chatId) const
{
    return m_dispatcher->getChatInfo(chatInfo, chatId);
}

bool CTelegramCore::getChatParticipants(QStringList *participants, quint32 chatId)
{
    return m_dispatcher->getChatParticipants(participants, chatId);
}

void CTelegramCore::setMessageReceivingFilterFlags(quint32 flags)
{
    return m_dispatcher->setMessageReceivingFilterFlags(flags);
}

void CTelegramCore::setAcceptableMessageTypes(quint32 types)
{
    return m_dispatcher->setAcceptableMessageTypes(types);
}

QString CTelegramCore::selfPhone() const
{
    return m_dispatcher->selfPhone();
}

quint64 CTelegramCore::sendMessage(const QString &contact, const QString &message)
{
    return m_dispatcher->sendMessageToContact(contact, message);
}

quint64 CTelegramCore::sendChatMessage(quint32 chatId, const QString &message)
{
    return m_dispatcher->sendMessageToChat(chatId, message);
}

void CTelegramCore::setTyping(const QString &contact, bool typingStatus)
{
    m_dispatcher->setTyping(contact, typingStatus);
}

void CTelegramCore::setChatTyping(quint32 chatId, bool typingStatus)
{
    m_dispatcher->setChatTyping(chatId, typingStatus);
}

void CTelegramCore::setMessageRead(const QString &contact, quint32 messageId)
{
    m_dispatcher->setMessageRead(contact, messageId);
}

void CTelegramCore::setOnlineStatus(bool onlineStatus)
{
    m_dispatcher->setOnlineStatus(onlineStatus);
}

void CTelegramCore::checkUserName(const QString &userName)
{
    m_dispatcher->checkUserName(userName);
}

void CTelegramCore::setUserName(const QString &newUserName)
{
    m_dispatcher->setUserName(newUserName);
}

quint32 CTelegramCore::createChat(const QStringList &phones, const QString &title)
{
    return m_dispatcher->createChat(phones, title);
}

bool CTelegramCore::addChatUser(quint32 chatId, const QString &contact, quint32 forwardMessages)
{
    return m_dispatcher->addChatUser(chatId, contact, forwardMessages);
}
