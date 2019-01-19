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

#include "ClientRpcMessagesLayer.hpp"

namespace Telegram {

class PendingOperation;

namespace Client {

class DataStorage;
class DialogList;
class MessagesOperation;
class MessagesRpcLayer;

class MessagingApiPrivate : public ClientApiPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(MessagingApi)
public:
    explicit MessagingApiPrivate(MessagingApi *parent = nullptr);
    static MessagingApiPrivate *get(MessagingApi *parent);

    quint64 sendMessage(const Telegram::Peer peer, const QString &message, const MessagingApi::SendOptions &options);

    void onMessageSendResult(quint64 randomMessageId, MessagesRpcLayer::PendingUpdates *rpcOperation);

    void onMessageReceived(const TLMessage &message);

    PendingOperation *getDialogs();
    MessagesOperation *getHistory(const Telegram::Peer peer, const MessageFetchOptions &options);

    DataStorage *dataStorage();
    MessagesRpcLayer *messagesLayer();

    DialogList *m_dialogList = nullptr;
    MessagesRpcLayer *m_messagesLayer = nullptr;

protected slots:
    void onGetDialogsFinished(PendingOperation *operation, MessagesRpcLayer::PendingMessagesDialogs *rpcOperation);
    void onGetHistoryFinished(MessagesOperation *operation, MessagesRpcLayer::PendingMessagesMessages *rpcOperation);
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_MESSAGING_API_PRIVATE_HPP
