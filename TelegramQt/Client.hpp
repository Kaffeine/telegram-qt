/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

class AppInformation;
class PendingOperation;

namespace Client {

class Settings;
class DataStorage;
class AccountStorage;
class AuthOperation;

//class LegacyCredentialsStorage : public CredentialsStorage
//{
//public:
//    QByteArray connectionSecretInfo() const;
//    bool setSecretInfo(const QByteArray &secret)
//    {
//        CRawStreamEx inputStream(secret);

//        quint32 format;
//        inputStream >> format;

//        if (format > secretFormatVersion) {
//            qWarning() << Q_FUNC_INFO << "Unknown format version" << format;
//            return false;
//        } else {
//            qDebug() << Q_FUNC_INFO << "Format version:" << format;
//        }

//        qint32 deltaTime = 0;
//        inputStream >> deltaTime;

//        if (format < 4) {
//            quint32 legacyDcInfoTlType;
//            inputStream >> legacyDcInfoTlType;

//            if (legacyDcInfoTlType != s_legacyDcInfoTlType) {
//                qWarning() << Q_FUNC_INFO << "Unexpected dataversion" << format;
//                return false;
//            }
//        }

//        TLDcOption dcInfo;
//        inputStream >> dcInfo.id;
//        if (format < 4) {
//            QByteArray legacyDcHostName;
//            inputStream >> legacyDcHostName;
//        }
//        QByteArray dcIpAddress;
//        inputStream >> dcIpAddress;
//        dcInfo.ipAddress = QString::fromLatin1(dcIpAddress);
//        inputStream >> dcInfo.port;

//        qDebug() << Q_FUNC_INFO << dcInfo.ipAddress;

//        if (format < 3) {
//            QByteArray legacySelfPhone;
//            inputStream >> legacySelfPhone;
//        }

//        QByteArray authKey;
//        inputStream >> authKey;

//        if (authKey.isEmpty()) {
//            qDebug() << Q_FUNC_INFO << "Empty auth key data.";
//            return false;
//        }

//        quint64 authId;
//        inputStream >> authId;
//        quint64 serverSalt;
//        inputStream >> serverSalt;

//        const quint64 expectedAuthId = Utils::getFingersprint(authKey);
//        if (authId != expectedAuthId) {
//            qDebug() << Q_FUNC_INFO << "The auth key data is not valid.";
//            return false;
//        }

//        if (inputStream.error()) {
//            qWarning() << Q_FUNC_INFO << "Read error occurred.";
//            return false;
//        }

//        if (format >= 1) {
//            inputStream >> m_updatesState.pts;
//            inputStream >> m_updatesState.qts;
//            inputStream >> m_updatesState.date;
//        }

//        if (format >= 4) {
//            quint32 dialogsCount = 0;
//            inputStream >> dialogsCount;
//            QHash<Telegram::Peer,TLDialog> dialogs;
//            dialogs.reserve(dialogsCount + 5);
//            for (quint32 i = 0; i < dialogsCount; ++i) {
//                TLDialog dialog;
//                quint8 dialogType = 0;
//                inputStream >> dialogType;

//                switch (dialogType) {
//                case DialogTypeDialog:
//                    dialog.tlType = TLValue::Dialog;
//                    break;
//                case DialogTypeChannel:
//                    dialog.tlType = TLValue::DialogChannel;
//                    break;
//                default:
//                    qWarning() << Q_FUNC_INFO << "Read invalid dialog type";
//                    return false;
//                    break;
//                }

//                quint8 peerType = 0;
//                quint32 peerId = 0;
//                inputStream >> peerType >> peerId;
//                Telegram::Peer peer(peerId, static_cast<Telegram::Peer::Type>(peerType));
//                if (!peer.isValid()) {
//                    qWarning() << "Session data contains invalid peer";
//                    return false;
//                }
//                dialog.peer = toTLPeer(peer);
//                inputStream >> dialog.readInboxMaxId;
//                inputStream >> dialog.unreadCount;

//                if (dialogType == DialogTypeChannel) {
//                    inputStream >> dialog.pts;
//                }
//                dialogs.insert(peer, dialog);
//            }
//            // Do not apply loaded dialogs, because we can not clean them up properly on dialogs received
//        } else if (format >= 2) {
//            quint32 legacyVectorTlType;
//            quint32 chatIdsVectorSize = 0;

//            inputStream >> legacyVectorTlType;
//            inputStream >> chatIdsVectorSize;
//            if (legacyVectorTlType != s_legacyVectorTlType) {
//                qWarning() << "Unexpected type value";
//                return false;
//            }

//            m_chatIds.resize(chatIdsVectorSize);

//            for (int i = 0; i < m_chatIds.count(); ++i) {
//                inputStream >> m_chatIds[i];
//            }
//        }

//        setDeltaTime(deltaTime);
//        setDcInfo(dcInfo);
//        setAuthKey(authKey);
//        return true;
//    }
//};

class ClientPrivate;

class TELEGRAMQT_EXPORT Client : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(AppInformation *applicationInformation READ appInformation WRITE setAppInformation)
    Q_PROPERTY(CAppInformation *applicationInformation READ appInformation WRITE setAppInformation)
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    bool isSignedIn() const;

    CAppInformation *appInformation() const;
    Q_INVOKABLE void setAppInformation(CAppInformation *newAppInfo);

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
    PendingOperation *connectToServer(); // Establish low-level TCP connection
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
