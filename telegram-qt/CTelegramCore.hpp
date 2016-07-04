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

#ifndef CTELEGRAMCORE_HPP
#define CTELEGRAMCORE_HPP

#include "telegramqt_export.h"
#include "TelegramNamespace.hpp"

#include <QObject>
#include <QVector>
#include <QStringList>

class CAppInformation;
class CTelegramDispatcher;

class TELEGRAMQT_EXPORT CTelegramCore : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramCore(QObject *parent = 0);
    ~CTelegramCore();

    inline const CAppInformation *appInfo() { return m_appInfo; }
    void setAppInformation(const CAppInformation *newAppInfo);

    Q_INVOKABLE static QVector<TelegramNamespace::DcOption> builtInDcs();
    Q_INVOKABLE static quint32 defaultPingInterval();

    QByteArray connectionSecretInfo() const;

    Q_INVOKABLE TelegramNamespace::ConnectionState connectionState() const;
    Q_INVOKABLE QString selfPhone() const;
    Q_INVOKABLE quint32 selfId() const;
    Q_INVOKABLE QVector<quint32> contactList() const;
    Q_INVOKABLE QVector<quint32> chatList() const;

    Q_INVOKABLE QString contactAvatarToken(const QString &contact) const;
    Q_INVOKABLE QString chatTitle(quint32 chatId) const;
    Q_INVOKABLE static quint32 identifierToChatId(const QString &identifier);

    static qint32 localTypingRecommendedRepeatInterval(); // Recommended application local typing state re-set interval.

    bool getUserInfo(TelegramNamespace::UserInfo *info, quint32 userId) const;
    bool getChatInfo(TelegramNamespace::GroupChat *chatInfo, quint32 chatId) const;
    bool getChatParticipants(QStringList *participants, quint32 chatId);

    bool getMessageMediaInfo(TelegramNamespace::MessageMediaInfo *messageInfo, quint32 messageId) const;

public Q_SLOTS:
    void setMessageReceivingFilter(TelegramNamespace::MessageFlags flags); // Messages with at least one of the passed flags will be filtered out.
    void setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types);
    void setAutoReconnection(bool enable);

    // By default, the app would ping server every 15 000 ms and instruct the server to close connection after 10 000 more ms. Pass interval = 0 to disable ping.
    void setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionTime = 10000);
    void setMediaDataBufferSize(quint32 size);

    bool initConnection(const QVector<TelegramNamespace::DcOption> &dcs = QVector<TelegramNamespace::DcOption>()); // Uses builtin dc options by default
    bool restoreConnection(const QByteArray &secret);
    void closeConnection();
    bool logOut();

    void requestPhoneStatus(const QString &phoneNumber);
    void requestPhoneCode(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void addContact(const QString &phoneNumber);
    void addContacts(const QStringList &phoneNumbers);

    void deleteContact(const QString &phoneNumber);
    void deleteContacts(const QStringList &phoneNumbers);

    void requestContactAvatar(const QString &contact);
    void requestMessageMediaData(quint32 messageId);

    bool requestHistory(const TelegramNamespace::Peer &peer, int offset, int limit);

    // Does not work yet
//    quint32 uploadFile(const QByteArray &fileContent, const QString &fileName);
//    quint32 uploadFile(QIODevice *source, const QString &fileName);

    quint64 sendMessage(const TelegramNamespace::Peer &peer, const QString &message); // Message id is a random number
    quint64 sendMedia(const TelegramNamespace::Peer &peer, const TelegramNamespace::MessageMediaInfo &messageInfo);
    quint64 forwardMessage(const TelegramNamespace::Peer &peer, quint32 messageId);
    /* Typing status is valid for 6 seconds. It is recommended to repeat typing status with localTypingRecommendedRepeatInterval() interval. */
    void setTyping(const TelegramNamespace::Peer &peer, TelegramNamespace::MessageAction action);
    void setMessageRead(const TelegramNamespace::Peer &peer, quint32 messageId);

    // Set visible (not actual) online status.
    void setOnlineStatus(bool onlineStatus);

    // Both methods result in userNameStatusUpdated() emission
    void checkUserName(const QString &userName);
    void setUserName(const QString &newUserName);

    // ChatId should starts with 1. The null id means that the chat is not valid.
    quint32 createChat(const QStringList &phones, const QString &title);
    bool addChatUser(quint32 chatId, const QString &contact, quint32 forwardMessages = 0);

    // Methods without "chat" word can be used instead. See methods implementation for details.
    quint64 sendChatMessage(quint32 chatId, const QString &message); // Message id is random number
    void setChatTyping(quint32 chatId, TelegramNamespace::MessageAction action);
    void setChatMessageRead(const quint32 &chatId, quint32 messageId);

Q_SIGNALS:
    void connectionStateChanged(TelegramNamespace::ConnectionState status);

    void phoneCodeRequired();
    void loggedOut(bool result);
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage); // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void contactListChanged();
    void contactProfileChanged(quint32 userId); // First, last or user name was changed
    void phoneStatusReceived(const QString &phone, bool registered);

    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType, const QString &avatarToken);
    void messageMediaDataReceived(const QString &contact, quint32 messageId, const QByteArray &data,
                                  const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);

    void messageReceived(const TelegramNamespace::Message &message);

    void contactStatusChanged(quint32 userId, TelegramNamespace::ContactStatus status);
    void contactTypingStatusChanged(const QString &contact, TelegramNamespace::MessageAction action);
    void contactChatTypingStatusChanged(quint32 chatId, const QString &contact, TelegramNamespace::MessageAction action);

    void sentMessageStatusChanged(const QString &contact, quint64 messageId, TelegramNamespace::MessageDeliveryStatus status); // Message id is random number

    void chatAdded(quint32 publichChatId);
    void chatChanged(quint32 publichChatId);

    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);

    void userNameStatusUpdated(const QString &userName, TelegramNamespace::AccountUserNameStatus status);
    void uploadingStatusUpdated(quint32 requestId, quint32 currentOffset, quint32 size);

private:
    CTelegramDispatcher *m_dispatcher;

    const CAppInformation *m_appInfo;

};

inline quint32 CTelegramCore::identifierToChatId(const QString &identifier)
{
    if (identifier.startsWith(QLatin1String("chat"))) {
        return identifier.section(QLatin1String("chat"), 1).toUInt();
    }
    return 0;
}

inline void CTelegramCore::addContact(const QString &phoneNumber)
{
    addContacts(QStringList() << phoneNumber);
}

inline void CTelegramCore::deleteContact(const QString &phoneNumber)
{
    deleteContacts(QStringList() << phoneNumber);
}

inline quint64 CTelegramCore::sendChatMessage(quint32 chatId, const QString &message)
{
    return sendMessage(TelegramNamespace::Peer(chatId, TelegramNamespace::Peer::Chat), message);
}

inline void CTelegramCore::setChatTyping(quint32 chatId, TelegramNamespace::MessageAction action)
{
    setTyping(TelegramNamespace::Peer(chatId, TelegramNamespace::Peer::Chat), action);
}

inline void CTelegramCore::setChatMessageRead(const quint32 &chatId, quint32 messageId)
{
    setMessageRead(TelegramNamespace::Peer(chatId, TelegramNamespace::Peer::Chat), messageId);
}

#endif // CTELECORE_HPP
