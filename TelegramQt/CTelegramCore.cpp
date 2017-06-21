/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "CTelegramCore.hpp"

#include <QDebug>

#include "CAppInformation.hpp"
#include "CTelegramDispatcher.hpp"
#include "CTelegramAuthModule.hpp"
#include "CTelegramMediaModule.hpp"

class CTelegramCore::Private
{
public:
    Private() :
        m_dispatcher(nullptr),
        m_authModule(nullptr),
        m_mediaModule(nullptr),
        m_appInfo(nullptr)
    {
    }

    CTelegramDispatcher *m_dispatcher;
    CTelegramAuthModule *m_authModule;
    CTelegramMediaModule *m_mediaModule;
    CAppInformation *m_appInfo;
};

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_private(new Private())
{
    TelegramNamespace::registerTypes();

    m_private->m_dispatcher = new CTelegramDispatcher(this);
    m_private->m_authModule = new CTelegramAuthModule(this);
    m_private->m_dispatcher->plugModule(m_private->m_authModule);
    m_private->m_mediaModule = new CTelegramMediaModule(this);
    m_private->m_dispatcher->plugModule(m_private->m_mediaModule);

    connect(m_private->m_dispatcher, SIGNAL(connectionStateChanged(TelegramNamespace::ConnectionState)),
            SIGNAL(connectionStateChanged(TelegramNamespace::ConnectionState)));
    connect(m_private->m_dispatcher, SIGNAL(selfUserAvailable(quint32)),
            SIGNAL(selfUserAvailable(quint32)));
    connect(m_private->m_dispatcher, SIGNAL(userInfoReceived(quint32)),
            SIGNAL(userInfoReceived(quint32)));

    connect(m_private->m_authModule, SIGNAL(loggedOut(bool)),
            SIGNAL(loggedOut(bool)));
    connect(m_private->m_authModule, SIGNAL(phoneStatusReceived(QString,bool)),
            SIGNAL(phoneStatusReceived(QString,bool)));
    connect(m_private->m_authModule, SIGNAL(phoneCodeRequired()),
            SIGNAL(phoneCodeRequired()));
    connect(m_private->m_authModule, SIGNAL(passwordInfoReceived(quint64)),
            SIGNAL(passwordInfoReceived(quint64)));
    connect(m_private->m_authModule, SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)),
            SIGNAL(authSignErrorReceived(TelegramNamespace::AuthSignError,QString)));
    connect(m_private->m_authModule, SIGNAL(authorizationErrorReceived(TelegramNamespace::UnauthorizedError,QString)),
            SIGNAL(authorizationErrorReceived(TelegramNamespace::UnauthorizedError,QString)));

    connect(m_private->m_dispatcher, SIGNAL(contactListChanged()),
            SIGNAL(contactListChanged()));
    connect(m_private->m_dispatcher, SIGNAL(contactProfileChanged(quint32)),
            SIGNAL(contactProfileChanged(quint32)));
    connect(m_private->m_mediaModule, SIGNAL(avatarReceived(quint32,QByteArray,QString,QString)),
            SIGNAL(avatarReceived(quint32,QByteArray,QString,QString)));
    connect(m_private->m_mediaModule, SIGNAL(messageMediaDataReceived(Telegram::Peer,quint32,QByteArray,QString,TelegramNamespace::MessageType,quint32,quint32)),
            SIGNAL(messageMediaDataReceived(Telegram::Peer,quint32,QByteArray,QString,TelegramNamespace::MessageType,quint32,quint32)));
    connect(m_private->m_dispatcher, SIGNAL(messageReceived(Telegram::Message)),
            SIGNAL(messageReceived(Telegram::Message)));
    connect(m_private->m_dispatcher, SIGNAL(contactStatusChanged(quint32,TelegramNamespace::ContactStatus)),
            SIGNAL(contactStatusChanged(quint32,TelegramNamespace::ContactStatus)));
    connect(m_private->m_dispatcher, SIGNAL(contactMessageActionChanged(quint32,TelegramNamespace::MessageAction)),
            SIGNAL(contactMessageActionChanged(quint32,TelegramNamespace::MessageAction)));
    connect(m_private->m_dispatcher, SIGNAL(contactChatMessageActionChanged(quint32,quint32,TelegramNamespace::MessageAction)),
            SIGNAL(contactChatMessageActionChanged(quint32,quint32,TelegramNamespace::MessageAction)));
    connect(m_private->m_dispatcher, SIGNAL(sentMessageIdReceived(quint64,quint32)),
            SIGNAL(sentMessageIdReceived(quint64,quint32)));
    connect(m_private->m_dispatcher, SIGNAL(messageReadInbox(Telegram::Peer,quint32)),
            SIGNAL(messageReadInbox(Telegram::Peer,quint32)));
    connect(m_private->m_dispatcher, SIGNAL(messageReadOutbox(Telegram::Peer,quint32)),
            SIGNAL(messageReadOutbox(Telegram::Peer,quint32)));

    connect(m_private->m_dispatcher, SIGNAL(peerAdded(Telegram::Peer)),
            SIGNAL(peerAdded(Telegram::Peer)));
    connect(m_private->m_dispatcher, SIGNAL(createdChatIdReceived(quint64,quint32)),
            SIGNAL(createdChatIdReceived(quint64,quint32)));
    connect(m_private->m_dispatcher, SIGNAL(chatAdded(quint32)),
            SIGNAL(chatAdded(quint32)));
    connect(m_private->m_dispatcher, SIGNAL(chatChanged(quint32)),
            SIGNAL(chatChanged(quint32)));
    connect(m_private->m_dispatcher, SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::UserNameStatus)),
            SIGNAL(userNameStatusUpdated(QString,TelegramNamespace::UserNameStatus)));
    connect(m_private->m_mediaModule, SIGNAL(filePartReceived(quint32,QByteArray,QString,quint32,quint32)),
            SIGNAL(filePartReceived(quint32,QByteArray,QString,quint32,quint32)));
    connect(m_private->m_mediaModule, SIGNAL(filePartUploaded(quint32,quint32,quint32)),
            SIGNAL(filePartUploaded(quint32,quint32,quint32)));
    connect(m_private->m_mediaModule, SIGNAL(fileRequestFinished(quint32,Telegram::RemoteFile)),
            SIGNAL(fileRequestFinished(quint32,Telegram::RemoteFile)));
}

CTelegramCore::~CTelegramCore()
{
    delete m_private->m_dispatcher;
    delete m_private->m_authModule;
    delete m_private;
}

CAppInformation *CTelegramCore::appInformation() const
{
    return m_private->m_appInfo;
}

bool CTelegramCore::updatesEnabled() const
{
    return m_private->m_dispatcher->updatesEnabled();
}

QNetworkProxy CTelegramCore::proxy() const
{
    return m_private->m_dispatcher->proxy();
}

void CTelegramCore::setProxy(const QNetworkProxy &proxy)
{
    return m_private->m_dispatcher->setProxy(proxy);
}

void CTelegramCore::setAppInformation(CAppInformation *newAppInfo)
{
    m_private->m_appInfo = newAppInfo;
}

void CTelegramCore::setAppInformation(const CAppInformation *newAppInfo)
{
    CAppInformation *variableAppInfo = new CAppInformation(newAppInfo, this);
    setAppInformation(variableAppInfo);
}

QVector<Telegram::DcOption> CTelegramCore::builtInDcs()
{
    return CTelegramDispatcher::builtInDcs();
}

quint32 CTelegramCore::defaultPingInterval()
{
    return CTelegramDispatcher::defaultPingInterval();
}

QByteArray CTelegramCore::connectionSecretInfo() const
{
    return m_private->m_dispatcher->connectionSecretInfo();
}

TelegramNamespace::ConnectionState CTelegramCore::connectionState() const
{
    return m_private->m_dispatcher->connectionState();
}

bool CTelegramCore::initConnection(const QVector<Telegram::DcOption> &dcs)
{
    if (!m_private->m_appInfo || !m_private->m_appInfo->isValid()) {
        qDebug() << "CTelegramCore: Can not init connection: App information is null or is not valid.";
        return false;
    }

    m_private->m_dispatcher->setAppInformation(m_private->m_appInfo);
    m_private->m_dispatcher->initConnection(dcs);

    return true;
}

void CTelegramCore::closeConnection()
{
    return m_private->m_dispatcher->closeConnection();
}

bool CTelegramCore::restoreConnection(const QByteArray &secret)
{
    m_private->m_dispatcher->setAppInformation(appInformation());
    return m_private->m_dispatcher->restoreConnection(secret);
}

bool CTelegramCore::logOut()
{
    return m_private->m_authModule->logOut();
}

void CTelegramCore::requestPhoneStatus(const QString &phoneNumber)
{
    m_private->m_authModule->requestPhoneStatus(phoneNumber);
}

void CTelegramCore::requestPhoneCode(const QString &phoneNumber)
{
    m_private->m_authModule->requestPhoneCode(phoneNumber);
}

quint64 CTelegramCore::getPassword()
{
    return m_private->m_authModule->getPassword();
}

void CTelegramCore::tryPassword(const QByteArray &salt, const QByteArray &password)
{
    m_private->m_authModule->tryPassword(salt, password);
}

void CTelegramCore::tryPassword(const QString &password)
{
    m_private->m_authModule->tryPassword(password);
}

void CTelegramCore::signIn(const QString &phoneNumber, const QString &authCode)
{
    m_private->m_authModule->signIn(phoneNumber, authCode);
}

void CTelegramCore::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    m_private->m_authModule->signUp(phoneNumber, authCode, firstName, lastName);
}

void CTelegramCore::addContacts(const QStringList &phoneNumbers)
{
    m_private->m_dispatcher->addContacts(phoneNumbers);
}

void CTelegramCore::deleteContacts(const QVector<quint32> &userIds)
{
    m_private->m_dispatcher->deleteContacts(userIds);
}

quint32 CTelegramCore::requestPeerPicture(const Telegram::Peer &peer, const Telegram::PeerPictureSize size) const
{
    return m_private->m_mediaModule->requestPeerPicture(peer, size);
}

void CTelegramCore::requestContactAvatar(quint32 userId)
{
    quint32 requestId = m_private->m_mediaModule->requestPeerPicture(Telegram::Peer(userId, Telegram::Peer::User), Telegram::PeerPictureSize::Small);
    Q_UNUSED(requestId)
}

void CTelegramCore::requestMessageMediaData(quint32 messageId)
{
    m_private->m_mediaModule->requestMessageMediaData(messageId);
}

quint32 CTelegramCore::requestFile(const Telegram::RemoteFile *file)
{
    return m_private->m_mediaModule->requestFile(file);
}

bool CTelegramCore::requestHistory(const Telegram::Peer &peer, int offset, int limit)
{
    return m_private->m_dispatcher->requestHistory(peer, offset, limit);
}

quint32 CTelegramCore::resolveUsername(const QString &userName)
{
    return m_private->m_dispatcher->resolveUsername(userName);
}

quint64 CTelegramCore::sendMessage(const Telegram::Peer &peer, const QString &message)
{
    return m_private->m_dispatcher->sendMessage(peer, message);
}

quint32 CTelegramCore::uploadFile(const QByteArray &fileContent, const QString &fileName)
{
    return m_private->m_mediaModule->uploadFile(fileContent, fileName);
}

quint32 CTelegramCore::uploadFile(QIODevice *source, const QString &fileName)
{
    return m_private->m_mediaModule->uploadFile(source, fileName);
}

QVector<quint32> CTelegramCore::contactList() const
{
    return m_private->m_dispatcher->contactIdList();
}

QVector<quint32> CTelegramCore::chatList() const
{
    return m_private->m_dispatcher->chatIdList();
}

QVector<Telegram::Peer> CTelegramCore::dialogs() const
{
    return m_private->m_dispatcher->dialogs();
}

QString CTelegramCore::peerPictureToken(const Telegram::Peer &peer, const Telegram::PeerPictureSize size) const
{
    return m_private->m_mediaModule->peerPictureToken(peer, size);
}

QString CTelegramCore::contactAvatarToken(quint32 userId) const
{
    return m_private->m_mediaModule->peerPictureToken(Telegram::Peer(userId, Telegram::Peer::User), Telegram::PeerPictureSize::Small);
}

QString CTelegramCore::chatTitle(quint32 chatId) const
{
    return m_private->m_dispatcher->chatTitle(chatId);
}

qint32 CTelegramCore::localTypingRecommendedRepeatInterval()
{
    return CTelegramDispatcher::localTypingRecommendedRepeatInterval();
}

/*! \fn quint32 Telegram::UserInfo::lastOnline() const
  Return seconds since epoch for last online time.

  If user is online, this method return time when online expires,
  return the time, when contact was online otherwise.

  Depending on the contact privacy, the method can return some special values:

  TelegramNamespace::ContactLastOnlineUnknown - User last online time is not known.
  TelegramNamespace::ContactLastOnlineRecently - User hides exact online time, but was online recently.
  TelegramNamespace::ContactLastOnlineLastWeek - User hides exact online time, but was online last week.
  TelegramNamespace::ContactLastOnlineLastMonth - User hides exact online time, but was online last month.

  The TelegramNamespace::ContactLastOnlineMask can be used to determine if there is special value:
  if ((contactLastOnline(contact) & TelegramNamespace::ContactLastOnlineMask) == contactLastOnline(contact)) {
      qDebug() << "Special value";
  } else {
      qDebug() << "Seconds since epoch";
  }
*/

bool CTelegramCore::getUserInfo(Telegram::UserInfo *info, quint32 userId) const
{
    return m_private->m_dispatcher->getUserInfo(info, userId);
}

bool CTelegramCore::getChatInfo(Telegram::ChatInfo *info, const Telegram::Peer peer) const
{
    return m_private->m_dispatcher->getChatInfo(info, peer);

}

bool CTelegramCore::getChatParticipants(QVector<quint32> *participants, quint32 chatId)
{
    return m_private->m_dispatcher->getChatParticipants(participants, chatId);
}

bool CTelegramCore::getMessageMediaInfo(Telegram::MessageMediaInfo *messageInfo, quint32 messageId) const
{
    return m_private->m_mediaModule->getMessageMediaInfo(messageInfo, messageId);
}

bool CTelegramCore::getPasswordInfo(Telegram::PasswordInfo *passwordInfo, quint64 requestId) const
{
    return m_private->m_authModule->getPasswordData(passwordInfo, requestId);
}

Telegram::PasswordInfo CTelegramCore::getPasswordData() const
{
    Telegram::PasswordInfo info;
    getPasswordInfo(&info, 0);
    return info;
}

void CTelegramCore::setMessageReceivingFilter(TelegramNamespace::MessageFlags flags)
{
    return m_private->m_dispatcher->setMessageReceivingFilter(flags);
}

void CTelegramCore::setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types)
{
    return m_private->m_dispatcher->setAcceptableMessageTypes(types);
}

void CTelegramCore::setAutoReconnection(bool enable)
{
    return m_private->m_dispatcher->setAutoReconnection(enable);
}

void CTelegramCore::setUpdatesEnabled(bool enable)
{
    return m_private->m_dispatcher->setUpdatesEnabled(enable);
}

void CTelegramCore::setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionTime)
{
    return m_private->m_dispatcher->setPingInterval(interval, serverDisconnectionAdditionTime);
}

void CTelegramCore::setMediaDataBufferSize(quint32 size)
{
    m_private->m_mediaModule->setMediaDataBufferSize(size);
}

QString CTelegramCore::selfPhone() const
{
    return m_private->m_dispatcher->selfPhone();
}

quint32 CTelegramCore::selfId() const
{
    return m_private->m_dispatcher->selfId();
}

quint32 CTelegramCore::maxMessageId() const
{
    return m_private->m_dispatcher->maxMessageId();
}

quint64 CTelegramCore::forwardMessage(const Telegram::Peer &peer, quint32 messageId)
{
    return m_private->m_dispatcher->forwardMessage(peer, messageId);
}

quint64 CTelegramCore::sendMedia(const Telegram::Peer &peer, const Telegram::MessageMediaInfo &messageInfo)
{
    return m_private->m_mediaModule->sendMedia(peer, messageInfo);
}

void CTelegramCore::setTyping(const Telegram::Peer &peer, TelegramNamespace::MessageAction action)
{
    m_private->m_dispatcher->setTyping(peer, action);
}

void CTelegramCore::setMessageRead(const Telegram::Peer &peer, quint32 messageId)
{
    m_private->m_dispatcher->setMessageRead(peer, messageId);
}

void CTelegramCore::setOnlineStatus(bool onlineStatus)
{
    m_private->m_dispatcher->setOnlineStatus(onlineStatus);
}

void CTelegramCore::checkUserName(const QString &userName)
{
    m_private->m_dispatcher->checkUserName(userName);
}

void CTelegramCore::setUserName(const QString &newUserName)
{
    m_private->m_dispatcher->setUserName(newUserName);
}

quint64 CTelegramCore::createChat(const QVector<quint32> &userIds, const QString &title)
{
    return m_private->m_dispatcher->createChat(userIds, title);
}

bool CTelegramCore::addChatUser(quint32 chatId, quint32 userId, quint32 forwardMessages)
{
    return m_private->m_dispatcher->addChatUser(chatId, userId, forwardMessages);
}
