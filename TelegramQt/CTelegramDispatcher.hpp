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

#include <QHash>
#include <QNetworkProxy>
#include <QPair>
#include <QStringList>
#include <QVector>

#include "FileRequestDescriptor.hpp"
#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

class QTimer;
class QCryptographicHash;
class QIODevice;

class CAppInformation;
class CTelegramConnection;
class CTelegramModule;

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
        StepDialogs         = 1 << 6,
        StepDone            = StepDialogs | (StepDialogs - 1)
    };

#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(InitializationStep)
#endif
    Q_DECLARE_FLAGS(InitializationStepFlags, InitializationStep)

    explicit CTelegramDispatcher(QObject *parent = 0);
    ~CTelegramDispatcher();

    void plugModule(CTelegramModule *module);

    static QVector<Telegram::DcOption> builtInDcs();
    static quint32 defaultPingInterval();

    bool updatesEnabled() const;
    void setUpdatesEnabled(bool enable);

    QNetworkProxy proxy() const;
    void setProxy(const QNetworkProxy &proxy);

    void setAppInformation(const CAppInformation *newAppInfo);

    static qint32 localTypingRecommendedRepeatInterval();

    TelegramNamespace::ConnectionState connectionState() const { return m_connectionState; }

    QString selfPhone() const;
    quint32 selfId() const;

    quint32 maxMessageId() const;
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

    bool initConnection(const QVector<Telegram::DcOption> &dcs);
    bool restoreConnection(const QByteArray &secret);
    void closeConnection();

    bool requestHistory(const Telegram::Peer &peer, quint32 offset, quint32 limit);
    quint32 resolveUsername(const QString &userName);

    quint64 sendMessage(const Telegram::Peer &peer, const QString &message);
    quint64 sendMedia(const Telegram::Peer &peer, const TLInputMedia &inputMedia);
    quint64 forwardMessage(const Telegram::Peer &peer, quint32 messageId);

    void setTyping(const Telegram::Peer &peer, TelegramNamespace::MessageAction publicAction);
    void setMessageRead(const Telegram::Peer &peer, quint32 messageId);

    quint64 createChat(const QVector<quint32> &userIds, const QString chatName);
    bool addChatUser(quint32 chatId, quint32 userId, quint32 forwardMessages);

    void setOnlineStatus(bool onlineStatus);
    void checkUserName(const QString &userName);
    void setUserName(const QString &newUserName);

    QString chatTitle(quint32 chatId) const;

    // Connections API

    bool setWantedDc(quint32 dc);
    CTelegramConnection *activeConnection() const { return m_mainConnection; }
    CTelegramConnection *getExtraConnection(quint32 dc);

    CTelegramConnection *createConnection(const TLDcOption &dcInfo);
    void ensureSignedConnection(CTelegramConnection *connection);
    void clearMainConnection();
    void clearExtraConnections();
    void ensureMainConnectToWantedDc();

    TLDcOption dcInfoById(quint32 dc) const;

    // Getters
    const TLUser *getUser(quint32 userId) const;
    const TLMessage *getMessage(quint32 messageId) const;

    bool getUserInfo(Telegram::UserInfo *userInfo, quint32 userId) const;
    bool getChatInfo(Telegram::GroupChat *outputChat, quint32 chatId) const;
    bool getChatParticipants(QVector<quint32> *participants, quint32 chatId);

    // Common
    TLInputPeer toInputPeer(const Telegram::Peer &peer) const;
    Telegram::Peer toPublicPeer(const TLInputPeer &inputPeer) const;
    Telegram::Peer toPublicPeer(const TLPeer &peer) const;
    Telegram::Peer toPublicPeer(const TLUser &user) const;
    Telegram::Peer toPublicPeer(const TLChat &chat) const;
    TLPeer toTLPeer(const Telegram::Peer &peer) const;
    TLInputUser toInputUser(quint32 id) const;

signals:
    void connectionStateChanged(TelegramNamespace::ConnectionState status);
    void selfUserAvailable(quint32 userId);
    void userInfoReceived(quint32 userId);

    void userNameStatusUpdated(const QString &userName, TelegramNamespace::UserNameStatus status);
    void contactListChanged();
    void contactProfileChanged(quint32 userId);

    void messageReceived(const Telegram::Message &message);

    void contactStatusChanged(quint32 userId, TelegramNamespace::ContactStatus status);
    void contactMessageActionChanged(quint32 userId, TelegramNamespace::MessageAction action);
    void contactChatMessageActionChanged(quint32 chatId, quint32 userId, TelegramNamespace::MessageAction action);

    void sentMessageIdReceived(quint64 randomId, quint32 resolvedId);
    void messageReadInbox(Telegram::Peer peer, quint32 messageId);
    void messageReadOutbox(Telegram::Peer peer, quint32 messageId);

    void createdChatIdReceived(quint64 randomId, quint32 resolvedId);
    void chatAdded(quint32 chatId);
    void chatChanged(quint32 chatId);

protected slots:
    void onConnectionAuthChanged(int newState, quint32 dc);
    void onConnectionStatusChanged(int newStatus, int reason, quint32 dc);
    void onDcConfigurationUpdated();
    void onConnectionDcIdUpdated(quint32 connectionId, quint32 newDcId);
    void onPackageRedirected(const QByteArray &data, quint32 dc);

    void onUpdatesReceived(const TLUpdates &updates, quint64 id);
    void onAuthExportedAuthorizationReceived(quint32 dc, quint32 id, const QByteArray &data);

    void onSelfUserReceived(const TLUser &selfUser);
    void onUsersReceived(const QVector<TLUser> &users);

    void onContactListReceived(const QVector<quint32> &contactIdList);
    void onContactListChanged(const QVector<quint32> &added, const QVector<quint32> &removed);
    void messageActionTimerTimeout();

    void onMessagesHistoryReceived(const TLMessagesMessages &messages);
    void onMessagesDialogsReceived(const TLMessagesDialogs &dialogs, quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit);
    void onMessagesAffectedMessagesReceived(const TLMessagesAffectedMessages &affectedMessages);

    void getDcConfiguration();
    void getContacts();
    void getChatsInfo();
    void getUpdatesState();
    void onUpdatesStateReceived(const TLUpdatesState &updatesState);

    void getDifference();
    void onUpdatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

    void onChatsReceived(const QVector<TLChat> &chats);
    void onMessagesFullChatReceived(const TLChatFull &chat, const QVector<TLChat> &chats, const QVector<TLUser> &users);

protected:
    void setConnectionState(TelegramNamespace::ConnectionState state);

    void processUpdate(const TLUpdate &update);

    void processMessageReceived(const TLMessage &message);
    void internalProcessMessageReceived(const TLMessage &message);

    void emitChatChanged(quint32 id);
    void updateChat(const TLChat &newChat);
    void updateFullChat(const TLChatFull &newChat);

    void initConnectionSharedClear();
    void initConnectionSharedFinal();

    void getInitialUsers();
    void getInitialDialogs();

    bool filterReceivedMessage(quint32 messageFlags) const;

    void ensureTypingUpdateTimer(int interval);
    void ensureUpdateState(quint32 pts = 0, quint32 seq = 0, quint32 date = 0);
    void setUpdateState(quint32 pts, quint32 seq, quint32 date);

    void ensureMaxMessageId(quint32 id);

    void addSentMessageId(quint64 rpcMessagesId, quint64 randomId);
    void updateShortSentMessageId(quint64 rpcId, quint32 resolvedId);
    void updateSentMessageId(quint64 randomId, quint32 resolvedId);

    void checkStateAndCallGetDifference();
    void tryNextDcAddress();

    void continueInitialization(InitializationStep justDone);

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

    QNetworkProxy m_proxy;
    const CAppInformation *m_appInformation;
    bool m_updatesEnabled;

    qint32 m_deltaTime;

    TelegramNamespace::MessageFlags m_messageReceivingFilterFlags;
    TelegramNamespace::MessageTypeFlags m_acceptableMessageTypes;
    bool m_autoReconnectionEnabled;
    quint32 m_pingInterval;
    quint32 m_pingServerAdditionDisconnectionTime;

    InitializationStepFlags m_initializationState;
    InitializationStepFlags m_requestedSteps;

    quint32 m_wantedActiveDc;
    int m_autoConnectionDcIndex;

    QVector<Telegram::DcOption> m_connectionAddresses;
    QVector<TLDcOption> m_dcConfiguration;
    CTelegramConnection *m_mainConnection;
    QVector<CTelegramConnection *> m_extraConnections;
    QString m_requestedCodeForPhone;

    quint64 m_updateRequestId;
    TLUpdatesState m_updatesState; // Current application update state (may be older than actual server-side message box state)
    TLUpdatesState m_actualState; // State reported by server as actual
    bool m_updatesStateIsLocked; // True if we are (going to) getting updatesDifference.
    bool m_emitOnlyIncomingUnreadMessages;

    QHash<quint32, QPair<quint32,QByteArray> > m_exportedAuthentications; // dc, <id, auth data>
    QHash<quint32, QByteArray> m_delayedPackages; // dc, package data
    QHash<quint32, TLUser*> m_users;
    QVector<quint32> m_askedUserIds;

    QHash<quint32, TLMessage*> m_knownMediaMessages; // message id, message

    quint32 m_selfUserId;
    quint32 m_maxMessageId;

    QVector<quint32> m_contactIdList;

    // fileId is program-specific handler, not related to Telegram.
    QHash<quint64,quint64> m_rpcIdToMessageRandomIdMap; // RPC Id, Random Id

    QTimer *m_typingUpdateTimer;
    QVector<TypingStatus> m_contactsMessageActions;
    QVector<TypingStatus> m_localMessageActions;

    TLVector<quint32> m_chatIds; // Telegram chat ids vector. Index is "public chat id".

    QHash<quint32, TLChat*> m_chatInfo; // Telegram chat id to Chat map
    QHash<quint32, TLChatFull> m_chatFullInfo; // Telegram chat id to ChatFull map

    QVector<CTelegramModule*> m_modules;

};

#endif // CTELEGRAMDISPATCHER_HPP
