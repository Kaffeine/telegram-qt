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

#ifndef CTELEGRAMDISPATCHER_HPP
#define CTELEGRAMDISPATCHER_HPP

#include <QObject>

#include <QMap>
#include <QMultiMap>
#include <QPair>
#include <QStringList>
#include <QVector>

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

class QTimer;
class QCryptographicHash;
class QIODevice;

class CAppInformation;
class CTelegramConnection;

class FileRequestDescriptor
{
public:
    enum Type {
        Invalid,
        Avatar,
        MessageMediaData,
        Upload
    };

    FileRequestDescriptor();

    static FileRequestDescriptor uploadRequest(const QByteArray &data, const QString &fileName, quint32 dc);
    static FileRequestDescriptor avatarRequest(const TLUser *user);
    static FileRequestDescriptor messageMediaDataRequest(const TLMessage &message);

    Type type() const { return m_type; }

    quint32 dcId() const { return m_dcId; }
    bool isValid() const { return m_type != Invalid; }

    TLInputFileLocation inputLocation() const { return m_inputLocation; }

    quint32 userId() const { return m_userId; }
    quint32 messageId() const { return m_messageId; }
    quint32 size() const { return m_size; }
    quint32 offset() const { return m_offset; }

    void setOffset(quint32 newOffset) { m_offset = newOffset; }

    /* Upload stuff */
    TLInputFile inputFile() const;
    quint32 part() const { return m_part; }
    quint32 parts() const;
    QByteArray md5Sum() const { return m_md5Sum; }
    quint64 fileId() const { return m_fileId; }

    bool isBigFile() const;
    bool finished() const;
    void bumpPart();

    QByteArray data() const;

    quint32 chunkSize() const;

protected:
    void setupLocation(const TLFileLocation &fileLocation);
    Type m_type;
    quint32 m_userId;
    quint32 m_messageId;
    quint32 m_size;
    quint32 m_offset;
    quint32 m_part;
    QByteArray m_data;
    QByteArray m_md5Sum;
    QString m_fileName;
    quint64 m_fileId;
    QCryptographicHash *m_hash;

    TLInputFileLocation m_inputLocation;
    quint32 m_dcId;

};

class CTelegramDispatcher : public QObject
{
    Q_OBJECT
public:
    enum InitializationStep {
        StepFirst           = 0,
        StepDcConfiguration = 1 << 0,
        StepSignIn          = 1 << 1,
        StepKnowSelf        = 1 << 2,
        StepContactList     = 1 << 3,
        StepChatInfo        = 1 << 4,
        StepUpdates         = 1 << 5,
        StepDone            = StepUpdates | (StepUpdates - 1)
    };

#if defined(DEVELOPER_BUILD) && QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(InitializationStep)
#endif

    explicit CTelegramDispatcher(QObject *parent = 0);
    ~CTelegramDispatcher();

    static QVector<TelegramNamespace::DcOption> builtInDcs();
    static quint32 defaultPingInterval();

    void setAppInformation(const CAppInformation *newAppInfo);

    static qint32 localTypingRecommendedRepeatInterval();

    TelegramNamespace::ConnectionState connectionState() const { return m_connectionState; }

    QString selfPhone() const;
    quint32 selfId() const;

    QVector<quint32> contactIdList() const;
    QVector<quint32> chatIdList() const;

    void addContacts(const QStringList &phoneNumbers, bool replace = false);
    void deleteContacts(const QVector<quint32> &userIds);

    QByteArray connectionSecretInfo() const;

    quint32 messageReceivingFilterFlags() const { return m_messageReceivingFilterFlags; }
    void setMessageReceivingFilter(TelegramNamespace::MessageFlags flags);
    void setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types);
    void setAutoReconnection(bool enable);
    void setPingInterval(quint32 ms, quint32 serverDisconnectionAdditionTime);
    void setMediaDataBufferSize(quint32 size);

    bool initConnection(const QVector<TelegramNamespace::DcOption> &dcs);
    bool restoreConnection(const QByteArray &secret);
    void closeConnection();
    bool logOut();

    void requestPhoneStatus(const QString &phoneNumber);
    quint64 getPassword();
    void tryPassword(const QByteArray &salt, const QByteArray &password);
    bool getPasswordData(TelegramNamespace::PasswordInfo *passwordInfo, quint64 requestId);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void requestPhoneCode(const QString &phoneNumber);
    void requestContactAvatar(quint32 userId);
    bool requestMessageMediaData(quint32 messageId);
    bool getMessageMediaInfo(TelegramNamespace::MessageMediaInfo *messageInfo, quint32 messageId) const;

    bool requestHistory(const TelegramNamespace::Peer &peer, quint32 offset, quint32 limit);
    quint32 resolveUsername(const QString &userName);

    quint32 uploadFile(const QByteArray &fileContent, const QString &fileName);
    quint32 uploadFile(QIODevice *source, const QString &fileName);

    quint64 sendMessage(const TelegramNamespace::Peer &peer, const QString &message);
    quint64 sendMedia(const TelegramNamespace::Peer &peer, const TelegramNamespace::MessageMediaInfo &messageInfo);
    quint64 forwardMessage(const TelegramNamespace::Peer &peer, quint32 messageId);

    void setTyping(const TelegramNamespace::Peer &peer, TelegramNamespace::MessageAction publicAction);
    void setMessageRead(const TelegramNamespace::Peer &peer, quint32 messageId);

    quint64 createChat(const QVector<quint32> &userIds, const QString chatName);
    bool addChatUser(quint32 chatId, quint32 userId, quint32 forwardMessages);

    void setOnlineStatus(bool onlineStatus);
    void checkUserName(const QString &userName);
    void setUserName(const QString &newUserName);

    QString contactAvatarToken(quint32 userId) const;

    QString chatTitle(quint32 chatId) const;

    bool getUserInfo(TelegramNamespace::UserInfo *userInfo, quint32 userId) const;
    bool getChatInfo(TelegramNamespace::GroupChat *outputChat, quint32 chatId) const;
    bool getChatParticipants(QVector<quint32> *participants, quint32 chatId);

signals:
    void connectionStateChanged(TelegramNamespace::ConnectionState status);
    void selfUserAvailable(quint32 userId);
    void userInfoReceived(quint32 userId);

    void phoneCodeRequired();
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void loggedOut(bool result);
    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);
    void userNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status);
    void uploadingStatusUpdated(quint32 requestId, quint32 offset, quint32 size);
    void uploadFinished(quint32 requestId, TelegramNamespace::UploadInfo uploadInfo);

    void contactListChanged();
    void contactProfileChanged(quint32 userId);
    void phoneStatusReceived(const QString &phone, bool registered);
    void passwordInfoReceived(quint64 requestId);

    void avatarReceived(quint32 userId, const QByteArray &data, const QString &mimeType, const QString &avatarToken);
    void messageMediaDataReceived(TelegramNamespace::Peer peer, quint32 messageId, const QByteArray &data, const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);

    void messageReceived(const TelegramNamespace::Message &message);

    void contactStatusChanged(quint32 userId, TelegramNamespace::ContactStatus status);
    void contactMessageActionChanged(quint32 userId, TelegramNamespace::MessageAction action);
    void contactChatMessageActionChanged(quint32 chatId, quint32 userId, TelegramNamespace::MessageAction action);

    void sentMessageIdReceived(quint64 randomId, quint32 resolvedId);
    void messageReadInbox(TelegramNamespace::Peer peer, quint32 messageId);
    void messageReadOutbox(TelegramNamespace::Peer peer, quint32 messageId);

    void createdChatIdReceived(quint64 randomId, quint32 resolvedId);
    void chatAdded(quint32 chatId);
    void chatChanged(quint32 chatId);

protected slots:
    void onConnectionAuthChanged(int newState, quint32 dc);
    void onConnectionStatusChanged(int newStatus, int reason, quint32 dc);
    void onDcConfigurationUpdated();
    void onConnectionDcIdUpdated(quint32 connectionId, quint32 newDcId);
    void onPackageRedirected(const QByteArray &data, quint32 dc);
    void onWantedMainDcChanged(quint32 dc, const QString &dcForPhoneNumber);

    void onUnauthorizedErrorReceived(TelegramNamespace::UnauthorizedError errorCode);
    void onPasswordReceived(const TLAccountPassword &password, quint64 requestId);

    void whenFileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset);
    void whenFileDataUploaded(quint32 requestId);
    void onUpdatesReceived(const TLUpdates &updates, quint64 id);
    void whenAuthExportedAuthorizationReceived(quint32 dc, quint32 id, const QByteArray &data);

    void onUsersReceived(const QVector<TLUser> &users);

    void whenContactListReceived(const QVector<quint32> &contactIdList);
    void whenContactListChanged(const QVector<quint32> &added, const QVector<quint32> &removed);
    void messageActionTimerTimeout();

    void whenMessageSentInfoReceived(quint64 randomId, TLMessagesSentMessage info);
    void whenMessagesHistoryReceived(const TLMessagesMessages &messages);
    void onMessagesDialogsReceived(const TLMessagesDialogs &dialogs, quint32 offset, quint32 maxId, quint32 limit);

    void getDcConfiguration();
    void getContacts();
    void getChatsInfo();
    void getUpdatesState();
    void whenUpdatesStateReceived(const TLUpdatesState &updatesState);

    void getDifference();
    void whenUpdatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

    void onChatsReceived(const QVector<TLChat> &chats);
    void whenMessagesFullChatReceived(const TLChatFull &chat, const QVector<TLChat> &chats, const QVector<TLUser> &users);

protected:
    void setConnectionState(TelegramNamespace::ConnectionState state);

    quint32 requestFile(const FileRequestDescriptor &descriptor);
    void processFileRequestForConnection(CTelegramConnection *connection, quint32 requestId);
    void processUpdate(const TLUpdate &update);

    void processMessageReceived(const TLMessage &message);

    void emitChatChanged(quint32 id);
    void updateChat(const TLChat &newChat);
    void updateFullChat(const TLChatFull &newChat);

    void initConnectionSharedClear();
    void initConnectionSharedFinal();

    void getUser(quint32 id);
    void getInitialUsers();

    bool filterReceivedMessage(quint32 messageFlags) const;

    TLInputPeer publicPeerToInputPeer(const TelegramNamespace::Peer &peer) const;
    TelegramNamespace::Peer peerToPublicPeer(const TLInputPeer &inputPeer) const;
    TelegramNamespace::Peer peerToPublicPeer(const TLPeer &peer) const;
    TLInputUser userIdToInputUser(quint32 id) const;

    QString userAvatarToken(const TLUser *user) const;

    CTelegramConnection *activeConnection() const { return m_mainConnection; }
    CTelegramConnection *getExtraConnection(quint32 dc);

    CTelegramConnection *createConnection(const TLDcOption &dcInfo);
    void ensureSignedConnection(CTelegramConnection *connection);
    void clearMainConnection();
    void clearExtraConnections();
    void ensureMainConnectToWantedDc();

    TLDcOption dcInfoById(quint32 dc) const;

    void ensureTypingUpdateTimer(int interval);
    void ensureUpdateState(quint32 pts = 0, quint32 seq = 0, quint32 date = 0);
    void setUpdateState(quint32 pts, quint32 seq, quint32 date);

    void checkStateAndCallGetDifference();
    void tryNextDcAddress();

    void continueInitialization(InitializationStep justDone);

    quint32 insertTelegramChatId(quint32 telegramChatId);

    TelegramNamespace::MessageFlags getPublicMessageFlags(quint32 flags);

    struct TypingStatus {
        TypingStatus() : chatId(0), userId(0),
            typingTime(0), action(TelegramNamespace::MessageActionNone) { }

        quint32 chatId;
        quint32 userId;
        int typingTime; // (ms)
        TelegramNamespace::MessageAction action;

        static int indexForUser(const QVector<TypingStatus> &statusVector, quint32 userId) {
            for (int i = 0; i < statusVector.count(); ++i) {
                if (statusVector.at(i).chatId) {
                    continue;
                }

                if (statusVector.at(i).userId == userId) {
                    return i;
                }
            }

            return -1;
        }

        static int indexForChatAndUser(const QVector<TypingStatus> &statusVector, quint32 chatId, quint32 userId = 0) {
            for (int i = 0; i < statusVector.count(); ++i) {
                if ((statusVector.at(i).chatId == chatId) && (statusVector.at(i).userId == userId)) {
                    return i;
                }
            }

            return -1;
        }
    };

    TelegramNamespace::ConnectionState m_connectionState;

    const CAppInformation *m_appInformation;

    qint32 m_deltaTime;

    quint32 m_messageReceivingFilterFlags;
    quint32 m_acceptableMessageTypes;
    bool m_autoReconnectionEnabled;
    quint32 m_pingInterval;
    quint32 m_pingServerAdditionDisconnectionTime;
    quint32 m_mediaDataBufferSize;

    quint32 m_initializationState; // InitializationStep flags
    quint32 m_requestedSteps; // InitializationStep flags

    quint32 m_wantedActiveDc;
    int m_autoConnectionDcIndex;

    QVector<TelegramNamespace::DcOption> m_connectionAddresses;
    QVector<TLDcOption> m_dcConfiguration;
    CTelegramConnection *m_mainConnection;
    QVector<CTelegramConnection *> m_extraConnections;
    QString m_requestedCodeForPhone;

    quint64 m_updateRequestId;
    TLUpdatesState m_updatesState; // Current application update state (may be older than actual server-side message box state)
    TLUpdatesState m_actualState; // State reported by server as actual
    bool m_updatesStateIsLocked; // True if we are (going to) getting updatesDifference.
    bool m_emitOnlyIncomingUnreadMessages;

    QMap<quint32, QPair<quint32,QByteArray> > m_exportedAuthentications; // dc, <id, auth data>
    QMap<quint32, QByteArray> m_delayedPackages; // dc, package data
    QMap<quint32, TLUser*> m_users;
    QVector<quint32> m_askedUserIds;

    QMap<quint32, TLMessage> m_knownMediaMessages; // message id, message

    quint32 m_selfUserId;

    QVector<quint32> m_contactIdList;

    // fileId is program-specific handler, not related to Telegram.
    QMap<quint32, FileRequestDescriptor> m_requestedFileDescriptors; // fileId, file request descriptor
    quint32 m_fileRequestCounter;

    QTimer *m_typingUpdateTimer;
    QVector<TypingStatus> m_contactsMessageActions;
    QVector<TypingStatus> m_localMessageActions;

    TLVector<quint32> m_chatIds; // Telegram chat ids vector. Index is "public chat id".

    QMap<quint32, TLChat> m_chatInfo; // Telegram chat id to Chat map
    QMap<quint32, TLChatFull> m_chatFullInfo; // Telegram chat id to ChatFull map
    QMap<quint64, TLAccountPassword> m_passwordInfo;

};

#endif // CTELEGRAMDISPATCHER_HPP
