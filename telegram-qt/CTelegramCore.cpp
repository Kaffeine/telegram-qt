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

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_dispatcher(new CTelegramDispatcher(this)),
    m_appInfo(0)
{
    TelegramNamespace::registerTypes();

    connect(m_dispatcher, SIGNAL(connectionStateChanged(TelegramNamespace::ConnectionState)),
            SIGNAL(connectionStateChanged(TelegramNamespace::ConnectionState)));
    connect(m_dispatcher, SIGNAL(loggedOut(bool)),
            SIGNAL(loggedOut(bool)));
    connect(m_dispatcher, SIGNAL(phoneStatusReceived(QString,bool)),
            SIGNAL(phoneStatusReceived(QString,bool)));
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
    connect(m_dispatcher, SIGNAL(messageMediaDataReceived(QString,quint32,QByteArray,QString,TelegramNamespace::MessageType,quint32,quint32)),
            SIGNAL(messageMediaDataReceived(QString,quint32,QByteArray,QString,TelegramNamespace::MessageType,quint32,quint32)));

    connect(m_dispatcher, SIGNAL(messageReceived(TelegramNamespace::Message)),
            SIGNAL(messageReceived(TelegramNamespace::Message)));

#ifndef TELEGRAMQT_NO_DEPRECATED
    connect(m_dispatcher, SIGNAL(phoneStatusReceived(QString,bool,bool)),
            SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(m_dispatcher, SIGNAL(messageReceived(QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)),
            SIGNAL(messageReceived(QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)));
    connect(m_dispatcher, SIGNAL(chatMessageReceived(quint32,QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)),
            SIGNAL(chatMessageReceived(quint32,QString,QString,TelegramNamespace::MessageType,quint32,quint32,quint32)));
#endif
    connect(m_dispatcher, SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)),
            SIGNAL(contactStatusChanged(QString,TelegramNamespace::ContactStatus)));
    connect(m_dispatcher, SIGNAL(contactTypingStatusChanged(QString,TelegramNamespace::MessageAction)),
            SIGNAL(contactTypingStatusChanged(QString,TelegramNamespace::MessageAction)));
    connect(m_dispatcher, SIGNAL(contactChatTypingStatusChanged(quint32,QString,TelegramNamespace::MessageAction)),
            SIGNAL(contactChatTypingStatusChanged(quint32,QString,TelegramNamespace::MessageAction)));
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
    connect(m_dispatcher, SIGNAL(uploadingStatusUpdated(quint32,quint32,quint32)),
            SIGNAL(uploadingStatusUpdated(quint32,quint32,quint32)));
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

QVector<TelegramNamespace::DcOption> CTelegramCore::builtInDcs()
{
    return CTelegramDispatcher::builtInDcs();
}

quint32 CTelegramCore::defaultPingInterval()
{
    return CTelegramDispatcher::defaultPingInterval();
}

QByteArray CTelegramCore::connectionSecretInfo() const
{
    return m_dispatcher->connectionSecretInfo();
}

TelegramNamespace::ConnectionState CTelegramCore::connectionState() const
{
    return m_dispatcher->connectionState();
}

bool CTelegramCore::initConnection(const QVector<TelegramNamespace::DcOption> &dcs)
{
    if (!m_appInfo || !m_appInfo->isValid()) {
        qDebug() << "CTelegramCore: Can not init connection: App information is null or is not valid.";
        return false;
    }

    m_dispatcher->setAppInformation(m_appInfo);
    m_dispatcher->initConnection(dcs);

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

bool CTelegramCore::requestHistory(const QString &identifier, int offset, int limit)
{
    return m_dispatcher->requestHistory(identifier, offset, limit);
}

//quint32 CTelegramCore::uploadFile(const QByteArray &fileContent, const QString &fileName)
//{
//    return m_dispatcher->uploadFile(fileContent, fileName);
//}

//quint32 CTelegramCore::uploadFile(QIODevice *source, const QString &fileName)
//{
//    return m_dispatcher->uploadFile(source, fileName);
//}

QStringList CTelegramCore::contactList() const
{
    return m_dispatcher->contactList();
}

QList<quint32> CTelegramCore::chatList() const
{
    return m_dispatcher->publicChatIdList().toList();
}

TelegramNamespace::ContactStatus CTelegramCore::contactStatus(const QString &contact) const
{
    return m_dispatcher->contactStatus(contact);
}

/*! \fn quint32 CTelegramCore::contactLastOnline(const QString &contact) const
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

bool CTelegramCore::getMessageMediaInfo(TelegramNamespace::MessageMediaInfo *messageInfo, quint32 messageId) const
{
    return m_dispatcher->getMessageMediaInfo(messageInfo, messageId);
}

void CTelegramCore::setMessageReceivingFilter(TelegramNamespace::MessageFlags flags)
{
    return m_dispatcher->setMessageReceivingFilter(flags);
}

void CTelegramCore::setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types)
{
    return m_dispatcher->setAcceptableMessageTypes(types);
}

void CTelegramCore::setAutoReconnection(bool enable)
{
    return m_dispatcher->setAutoReconnection(enable);
}

void CTelegramCore::setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionTime)
{
    return m_dispatcher->setPingInterval(interval, serverDisconnectionAdditionTime);
}

void CTelegramCore::setMediaDataBufferSize(quint32 size)
{
    m_dispatcher->setMediaDataBufferSize(size);
}

QString CTelegramCore::selfPhone() const
{
    return m_dispatcher->selfPhone();
}

quint64 CTelegramCore::sendMessage(const QString &identifier, const QString &message)
{
    return m_dispatcher->sendMessage(identifier, message);
}

quint64 CTelegramCore::forwardMessage(const QString &identifier, quint32 messageId)
{
    return m_dispatcher->forwardMessage(identifier, messageId);
}

quint64 CTelegramCore::sendMedia(const QString &identifier, const TelegramNamespace::MessageMediaInfo &messageInfo)
{
    return m_dispatcher->sendMedia(identifier, messageInfo);
}

void CTelegramCore::setTyping(const QString &contact, TelegramNamespace::MessageAction action)
{
    m_dispatcher->setTyping(contact, action);
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
