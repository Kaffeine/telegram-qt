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

#include "telegramqt_global.h"
#include "TelegramNamespace.hpp"

#include <QObject>
#include <QNetworkProxy>
#include <QVector>
#include <QStringList>

class CAppInformation;

QT_FORWARD_DECLARE_CLASS(QIODevice)

class TELEGRAMQT_EXPORT CTelegramCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray connectionSecretData READ connectionSecretInfo)
    Q_PROPERTY(bool updatesEnabled READ updatesEnabled WRITE setUpdatesEnabled)
    Q_PROPERTY(CAppInformation *applicationInformation READ appInformation WRITE setAppInformation)
    Q_PROPERTY(TelegramNamespace::ConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)
public:
    explicit CTelegramCore(QObject *parent = 0);
    ~CTelegramCore();

    CAppInformation *appInformation() const;
    bool updatesEnabled() const;

    QNetworkProxy proxy() const;
    void setProxy(const QNetworkProxy &proxy);

    Q_INVOKABLE void setAppInformation(CAppInformation *newAppInfo);
    Q_INVOKABLE void setAppInformation(const CAppInformation *newAppInfo);

    Q_INVOKABLE static QVector<Telegram::DcOption> builtInDcs();
    Q_INVOKABLE static quint32 defaultPingInterval();

    QByteArray connectionSecretInfo() const;

    Q_INVOKABLE TelegramNamespace::ConnectionState connectionState() const;
    Q_INVOKABLE QString selfPhone() const;
    Q_INVOKABLE quint32 selfId() const;
    // maxMessageId is an id of the last sent or received message. Updated *after* messageReceived and sentMessageIdReceived signal emission.
    Q_INVOKABLE quint32 maxMessageId() const;
    Q_INVOKABLE QVector<quint32> contactList() const;
    Q_INVOKABLE QVector<quint32> chatList() const;

    Q_INVOKABLE QString contactAvatarToken(quint32 userId) const;
    Q_INVOKABLE QString chatTitle(quint32 chatId) const;

    static qint32 localTypingRecommendedRepeatInterval(); // Recommended application local typing state re-set interval.

    bool getUserInfo(Telegram::UserInfo *info, quint32 userId) const;
    bool getChatInfo(Telegram::GroupChat *chatInfo, quint32 chatId) const;
    bool getChatParticipants(QVector<quint32> *participants, quint32 chatId);

    bool getMessageMediaInfo(Telegram::MessageMediaInfo *messageInfo, quint32 messageId) const;
    bool getPasswordInfo(Telegram::PasswordInfo *passwordInfo, quint64 requestId) const;
    Q_INVOKABLE Telegram::PasswordInfo getPasswordData() const;

public Q_SLOTS:
    void setMessageReceivingFilter(TelegramNamespace::MessageFlags flags); // Messages with at least one of the passed flags will be filtered out.
    void setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types);
    void setAutoReconnection(bool enable);
    void setUpdatesEnabled(bool enable);

    // By default, the app would ping server every 15 000 ms and instruct the server to close connection after 10 000 more ms. Pass interval = 0 to disable ping.
    void setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionTime = 10000);
    void setMediaDataBufferSize(quint32 size);

    bool initConnection(const QVector<Telegram::DcOption> &dcs = QVector<Telegram::DcOption>()); // Uses builtin dc options by default
    bool restoreConnection(const QByteArray &secret);
    void closeConnection();
    bool logOut();

    void requestPhoneStatus(const QString &phoneNumber);
    void requestPhoneCode(const QString &phoneNumber);
    quint64 getPassword();
    void tryPassword(const QByteArray &salt, const QString &password);
    void tryPassword(const QByteArray &salt, const QByteArray &password);
    void tryPassword(const QString &password);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void addContact(const QString &phoneNumber);
    void addContacts(const QStringList &phoneNumbers);

    void deleteContact(quint32 userId);
    void deleteContacts(const QVector<quint32> &userIds);

    void requestContactAvatar(quint32 userId);
    void requestMessageMediaData(quint32 messageId);
    quint32 requestFile(const Telegram::RemoteFile *file);

    bool requestHistory(const Telegram::Peer &peer, int offset, int limit);

    quint32 resolveUsername(const QString &userName);

    // Does not work yet
    quint32 uploadFile(const QByteArray &fileContent, const QString &fileName);
    quint32 uploadFile(QIODevice *source, const QString &fileName);

    quint64 sendMessage(const Telegram::Peer &peer, const QString &message); // Message id is a random number
    quint64 sendMedia(const Telegram::Peer &peer, const Telegram::MessageMediaInfo &messageInfo);
    quint64 forwardMessage(const Telegram::Peer &peer, quint32 messageId);
    /* Typing status is valid for 6 seconds. It is recommended to repeat typing status with localTypingRecommendedRepeatInterval() interval. */
    void setTyping(const Telegram::Peer &peer, TelegramNamespace::MessageAction action);
    void setMessageRead(const Telegram::Peer &peer, quint32 messageId);

    // Set visible (not actual) online status.
    void setOnlineStatus(bool onlineStatus);

    // Both methods result in userNameStatusUpdated() emission
    void checkUserName(const QString &userName);
    void setUserName(const QString &newUserName);

    // Returns unique 64-bit id for the request. Null id means that the request is not valid.
    quint64 createChat(const QVector<quint32> &userIds, const QString &title);
    bool addChatUser(quint32 chatId, quint32 userId, quint32 forwardMessages = 0);

    // Methods without "chat" word can be used instead. See methods implementation for details.
    quint64 sendChatMessage(quint32 chatId, const QString &message); // Message id is random number
    void setChatTyping(quint32 chatId, TelegramNamespace::MessageAction action);
    void setChatMessageRead(const quint32 &chatId, quint32 messageId);

Q_SIGNALS:
    void connectionStateChanged(TelegramNamespace::ConnectionState state);
    void selfUserAvailable(quint32 userId);
    void userInfoReceived(quint32 userId);

    void phoneCodeRequired();
    void loggedOut(bool result);
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage); // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void contactListChanged();
    void contactProfileChanged(quint32 userId); // First, last or user name was changed
    void phoneStatusReceived(const QString &phone, bool registered);
    void passwordInfoReceived(quint64 requestId);

    void avatarReceived(quint32 userId, const QByteArray &data, const QString &mimeType, const QString &avatarToken);
    void messageMediaDataReceived(Telegram::Peer peer, quint32 messageId, const QByteArray &data,
                                  const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);

    void messageReceived(const Telegram::Message &message);

    void contactStatusChanged(quint32 userId, TelegramNamespace::ContactStatus status);
    void contactMessageActionChanged(quint32 userId, TelegramNamespace::MessageAction action);
    void contactChatMessageActionChanged(quint32 chatId, quint32 userId, TelegramNamespace::MessageAction action);

    void sentMessageIdReceived(quint64 randomId, quint32 resolvedId);
    void messageReadInbox(Telegram::Peer peer, quint32 messageId);
    void messageReadOutbox(Telegram::Peer peer, quint32 messageId);

    void createdChatIdReceived(quint64 randomId, quint32 resolvedId); // Signal chatAdded(resolvedId) would be emitted after this signal.
    void chatAdded(quint32 chatId);
    void chatChanged(quint32 chatId);

    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);

    void userNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status);

    void filePartReceived(quint32 requestId, const QByteArray &data, const QString &mimeType, quint32 offset, quint32 totalSize);
    void filePartUploaded(quint32 requestId, quint32 offset, quint32 totalSize);
    void fileRequestFinished(quint32 requestId, Telegram::RemoteFile requestResult);

private:
    class Private;
    friend class Private;
    Private *m_private;

};

inline void CTelegramCore::tryPassword(const QByteArray &salt, const QString &password)
{
    return tryPassword(salt, password.toUtf8());
}

inline void CTelegramCore::addContact(const QString &phoneNumber)
{
    addContacts(QStringList() << phoneNumber);
}

inline void CTelegramCore::deleteContact(quint32 userId)
{
    deleteContacts(QVector<quint32>() << userId);
}

inline quint64 CTelegramCore::sendChatMessage(quint32 chatId, const QString &message)
{
    return sendMessage(Telegram::Peer(chatId, Telegram::Peer::Chat), message);
}

inline void CTelegramCore::setChatTyping(quint32 chatId, TelegramNamespace::MessageAction action)
{
    setTyping(Telegram::Peer(chatId, Telegram::Peer::Chat), action);
}

inline void CTelegramCore::setChatMessageRead(const quint32 &chatId, quint32 messageId)
{
    setMessageRead(Telegram::Peer(chatId, Telegram::Peer::Chat), messageId);
}

#endif // CTELECORE_HPP
