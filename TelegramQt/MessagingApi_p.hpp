/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_CLIENT_MESSAGING_API_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_MESSAGING_API_PRIVATE_HPP

#include "ClientApi_p.hpp"
#include "MessagingApi.hpp"

#include "RpcLayers/ClientRpcChannelsLayer.hpp"
#include "RpcLayers/ClientRpcMessagesLayer.hpp"

QT_FORWARD_DECLARE_CLASS(QTimer)

namespace Telegram {

class PendingOperation;

namespace Client {

class DialogList;
class DialogState;
class PendingMessages;
class MessagesRpcLayer;

struct UserMessageAction : public MessageAction
{
    UserMessageAction() = default;
    UserMessageAction(Peer p, quint32 user)
        : peer(p)
        , userId(user)
    {
    }

    static int findInVector(const QVector<UserMessageAction> &vector,
                            Peer p,
                            quint32 id)
    {
        for (int i = 0; i < vector.count(); ++i) {
            const UserMessageAction &a = vector.at(i);
            if ((a.peer == p) && (a.userId == id)) {
                return i;
            }
        }
        return -1;
    }

    Peer peer;
    quint32 userId = 0;
    int remainingTime = 0; // (ms)
};

class MessagingApiPrivate : public ClientApiPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(MessagingApi)
public:
    enum class SyncState {
        NotStarted,
        InProgress,
        Finished,
    };
    explicit MessagingApiPrivate(MessagingApi *parent = nullptr);
    static MessagingApiPrivate *get(MessagingApi *parent);

    static quint32 getMessageRepeatInterval();
    static const char *messageActionIntervalVarName();

    quint64 sendMessage(const Telegram::Peer peer, const QString &message, const MessagingApi::SendOptions &options);
    void setMessageRead(const Telegram::Peer peer, quint32 messageId);

    void setMessageAction(const Peer peer, const Telegram::MessageAction &action);
    void processMessageAction(const Peer peer, quint32 userId, const MessageAction &action);

    void onChatCreatedResult(MessagesRpcLayer::PendingUpdates *rpcOperation);
    void onSendMessageResult(quint64 randomMessageId, MessagesRpcLayer::PendingUpdates *rpcOperation);
    void onShortSentMessage(quint32 messageId);
    void onSentMessageIdResolved(quint64 randomMessageId, quint32 messageId);

    void onMessageReceived(const TLMessage &message);
    void onMessageInboxRead(const Telegram::Peer peer, quint32 messageId);
    void onMessageOutboxRead(const Telegram::Peer peer, quint32 messageId);
    void onUserActionChanged(quint32 userId, const TLSendMessageAction &action);
    void onChatUserActionChanged(const Telegram::Peer peer, quint32 userId, const TLSendMessageAction &action);

    PendingOperation *syncPeers(const Telegram::PeerList &peers);
    void syncMorePeerMessages(const Peer &peer, const DialogState *state);
    void checkIfSyncFinished();
    void onPeerSyncFinished(const Peer &peer, DialogState *state);
    bool syncAndFilterMessage(const Peer &peer, quint32 messageId);
    DialogState *ensureDialogSyncState(const Peer &peer);

    PendingOperation *getDialogs();
    PendingMessages *getHistory(const Telegram::Peer peer, const MessageFetchOptions &options);
    PendingOperation *createChat(const QString &title, const QVector<quint32> &contacts);

    MessagesRpcLayer *messagesLayer();
    ChannelsRpcLayer *channelsLayer();

protected slots:
    void onGetDialogsFinished(PendingOperation *operation, MessagesRpcLayer::PendingMessagesDialogs *rpcOperation);
    void onGetHistoryFinished(PendingMessages *operation, MessagesRpcLayer::PendingMessagesMessages *rpcOperation);
    void onReadHistoryFinished(const Peer peer, quint32 messageId, MessagesRpcLayer::PendingMessagesAffectedMessages *rpcOperation);
    void onReadChannelHistoryFinished(const Peer peer, quint32 messageId, ChannelsRpcLayer::PendingBool *rpcOperation);
    void onHistoryReadSucceeded(const Peer peer, quint32 messageId);
    void onSyncHistoryReceived(PendingMessages *operation);

    void processNewSyncMessages(const Telegram::Peer &peer, const QVector<quint32> &messages);
    void onMessageActionTimerTimeout();

protected:
    QVector<UserMessageAction> m_currentMessageActions;
    QTimer *m_messageActionTimer = nullptr;
    DialogList *m_dialogList = nullptr;
    MessagesRpcLayer *m_messagesLayer = nullptr;
    quint64 m_expectedRandomMessageId = 0;

    PendingOperation *m_syncOperation = nullptr;
    int m_syncJobs = 0;
    quint32 m_syncLimit = 0;
    MessagingApi::SyncMode m_syncMode = MessagingApi::NoSync;
    SyncState m_syncState = SyncState::NotStarted;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_MESSAGING_API_PRIVATE_HPP
