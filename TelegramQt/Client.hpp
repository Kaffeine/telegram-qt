/*
   Copyright (C) 2014-2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_CLIENT_HPP
#define TELEGRAM_CLIENT_HPP

#include "telegramqt_global.h"
#include "TelegramNamespace.hpp"

#include <QObject>
#include <QVector>
#include <QStringList>

QT_FORWARD_DECLARE_CLASS(QIODevice)

class CAppInformation;

namespace Telegram {

class PendingOperation;

namespace Client {

class Settings;
class DataStorage;
class AccountStorage;
using AppInformation = ::CAppInformation;
class AuthOperation;

class ClientPrivate;

class TELEGRAMQT_EXPORT Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    bool isSignedIn() const;

    AppInformation *appInformation() const;
    void setAppInformation(AppInformation *newAppInfo);

    Settings *settings();
    const Settings *settings() const;
    void setSettings(Settings *settings);

    AccountStorage *accountStorage() const;
    void setAccountStorage(AccountStorage *storage);

    DataStorage *dataStorage() const;
    void setDataStorage(DataStorage *storage);

//    Q_INVOKABLE TelegramNamespace::ConnectionState connectionState() const;
//    Q_INVOKABLE QString selfPhone() const;
//    Q_INVOKABLE quint32 selfId() const;
//    // maxMessageId is an id of the last sent or received message. Updated *after* messageReceived and sentMessageIdReceived signal emission.
//    Q_INVOKABLE quint32 maxMessageId() const;
//    Q_INVOKABLE QVector<quint32> contactList() const;
//    Q_INVOKABLE QVector<Telegram::Peer> dialogs() const;

//    Q_INVOKABLE QString peerPictureToken(const Telegram::Peer &peer, const Telegram::PeerPictureSize size = Telegram::PeerPictureSize::Small) const;

//    static qint32 localTypingRecommendedRepeatInterval(); // Recommended application local typing state re-set interval.

//    bool getDialogInfo(Telegram::DialogInfo *info, const Telegram::Peer &peer) const;
//    bool getUserInfo(Telegram::UserInfo *info, quint32 userId) const;
//    bool getChatInfo(Telegram::ChatInfo *info, const Telegram::Peer peer) const;
//    bool getChatParticipants(QVector<quint32> *participants, quint32 chatId);

//    bool getMessageMediaInfo(Telegram::MessageMediaInfo *messageInfo, quint32 messageId, const Telegram::Peer &peer) const;

public Q_SLOTS:
//    void setMessageReceivingFilter(TelegramNamespace::MessageFlags flags); // Messages with at least one of the passed flags will be filtered out.
//    void setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types);
//    void setAutoReconnection(bool enable);
//    void setUpdatesEnabled(bool enable);

    // Low-level methods (needed mostly for debug and testing)
//    void disconnectFromServer();
//    PendingAuthOperation *checkPhoneNumber();
    AuthOperation *signIn();

//    void resetConnectionData();
//    bool setSecretInfo(const QByteArray &secret);

//    bool logOut();

//    void requestPhoneStatus(const QString &phoneNumber);
//    bool requestAuthCode(const QString &phoneNumber);
//    quint64 getPassword();
//    void tryPassword(const QByteArray &salt, const QString &password);
//    void tryPassword(const QByteArray &salt, const QByteArray &password);
//    void tryPassword(const QString &password);
//    void signIn(const QString &phoneNumber, const QString &authCode);
//    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

//    void addContact(const QString &phoneNumber);
//    void addContacts(const QStringList &phoneNumbers);

//    void deleteContact(quint32 userId);
//    void deleteContacts(const QVector<quint32> &userIds);

//    PendingOperation *requestFile(const RemoteFile *file);
//    PendingOperation *requestHistory(const Peer &peer, int offset, int limit);
//    PendingOperation *resolveUsername(const QString &userName);
//    PendingOperation *uploadFile(const QByteArray &fileContent, const QString &fileName);
//    PendingOperation *uploadFile(QIODevice *source, const QString &fileName);

//    quint64 sendMessage(const Telegram::Peer &peer, const QString &message); // Message id is a random number
//    quint64 sendMedia(const Telegram::Peer &peer, const Telegram::MessageMediaInfo &messageInfo);
//    quint64 forwardMessage(const Telegram::Peer &peer, quint32 messageId);
//    /* Typing status is valid for 6 seconds. It is recommended to repeat typing status with localTypingRecommendedRepeatInterval() interval. */
//    void setTyping(const Telegram::Peer &peer, TelegramNamespace::MessageAction action);
//    void setMessageRead(const Telegram::Peer &peer, quint32 messageId);

    // Set visible (not actual) online status.
//    void setOnlineStatus(bool onlineStatus);

    // Both methods result in userNameStatusUpdated() emission
//    void checkUserName(const QString &userName);
//    Telegram::PendingOperation *getUserName(const QString &userName);
//    void setUserName(const QString &newUserName);
//    Telegram::PendingOperation *createBroadcast(const QString &name, const QString &description = QString());
    // Returns unique 64-bit id for the request. Null id means that the request is not valid.
//    quint64 createChat(const QVector<quint32> &userIds, const QString &title);
//    bool addChatUser(quint32 chatId, quint32 userId, quint32 forwardMessages = 0);

//Q_SIGNALS:
//    void connectionStateChanged(TelegramNamespace::ConnectionState state);
//    void selfUserAvailable(quint32 userId);

Q_SIGNALS:
    void signedInChanged(bool signedIn);

private:
    ClientPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Client)
};

} // Client

} // Telegram

#endif // TELEGRAM_CLIENT_HPP
