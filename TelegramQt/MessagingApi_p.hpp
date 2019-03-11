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

#include "ClientRpcChannelsLayer.hpp"
#include "ClientRpcMessagesLayer.hpp"

namespace Telegram {

class PendingOperation;

namespace Client {

class DataInternalApi;
class DataStorage;
class DialogList;
class PendingMessages;
class MessagesRpcLayer;

class MessagingApiPrivate : public ClientApiPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(MessagingApi)
public:
    explicit MessagingApiPrivate(MessagingApi *parent = nullptr);
    static MessagingApiPrivate *get(MessagingApi *parent);

    quint64 sendMessage(const Telegram::Peer peer, const QString &message, const MessagingApi::SendOptions &options);
    void setMessageRead(const Telegram::Peer peer, quint32 messageId);

    void onMessageSendResult(quint64 randomMessageId, MessagesRpcLayer::PendingUpdates *rpcOperation);
    void onSentMessageIdResolved(quint64 randomMessageId, quint32 messageId);

    void onMessageReceived(const TLMessage &message);
    void onMessageInboxRead(const Telegram::Peer peer, quint32 messageId);
    void onMessageOutboxRead(const Telegram::Peer peer, quint32 messageId);

    PendingOperation *getDialogs();
    PendingMessages *getHistory(const Telegram::Peer peer, const MessageFetchOptions &options);

    DataStorage *dataStorage();
    DataInternalApi *dataInternalApi();
    MessagesRpcLayer *messagesLayer();
    ChannelsRpcLayer *channelsLayer();

    DialogList *m_dialogList = nullptr;
    MessagesRpcLayer *m_messagesLayer = nullptr;
    quint64 m_expectedRandomMessageId = 0;

protected slots:
    void onGetDialogsFinished(PendingOperation *operation, MessagesRpcLayer::PendingMessagesDialogs *rpcOperation);
    void onGetHistoryFinished(PendingMessages *operation, MessagesRpcLayer::PendingMessagesMessages *rpcOperation);
    void onReadHistoryFinished(const Peer peer, quint32 messageId, MessagesRpcLayer::PendingMessagesAffectedMessages *rpcOperation);
    void onReadChannelHistoryFinished(const Peer peer, quint32 messageId, ChannelsRpcLayer::PendingBool *rpcOperation);
    void onHistoryReadSucceeded(const Peer peer, quint32 messageId);
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_MESSAGING_API_PRIVATE_HPP
