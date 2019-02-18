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

#ifndef TELEGRAMQT_CLIENT_MESSAGING_API_HPP
#define TELEGRAMQT_CLIENT_MESSAGING_API_HPP

#include "ClientApi.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

class PendingOperation;

namespace Client {

class DialogList;
class MessagesOperation;

class MessagingApiPrivate;

struct TELEGRAMQT_EXPORT MessageFetchOptions
{
    quint32 offsetId = 0;
    quint32 offsetDate = 0;
    quint32 addOffset = 0;
    quint32 limit = 0;
    quint32 maxId = 0;
    quint32 minId = 0;
    quint32 hash = 0;

    static MessageFetchOptions useLimit(quint32 limit)
    {
        MessageFetchOptions result;
        result.limit = limit;
        return result;
    }
};

class TELEGRAMQT_EXPORT MessagingApi : public ClientApi
{
    Q_OBJECT
public:
    explicit MessagingApi(QObject *parent = nullptr);

    static quint32 messageActionValidPeriod();
    static quint32 messageActionRepeatInterval();

    struct SendOptions {
        SendOptions();

        bool clearDraft() const { return m_clearDraft; }
        void setClearDraft(bool clear) { m_clearDraft = clear; }

        quint32 replyToMessageId() const { return m_replyMessageId; }
        void setReplyToMessageId(quint32 id) { m_replyMessageId = id; }

    protected:
        quint32 m_replyMessageId;
        bool m_clearDraft;
        // Message entities

        // (flags & 1 << 0) enables replyToMsgId
        // (flags & 1 << 1) stands for noWebpage "true" value
        // (flags & 1 << 2) enables replyMarkup
        // (flags & 1 << 3) enables entities
        // (flags & 1 << 5) stands for silent "true" value
        // (flags & 1 << 6) stands for background "true" value
        // (flags & 1 << 7) stands for clearDraft "true" value
    };

    DialogList *getDialogList();
    MessagesOperation *getHistory(const Telegram::Peer peer, const MessageFetchOptions &options);

public slots:
    void setDraftMessage(const Telegram::Peer peer, const QString &text);

    quint64 sendMessage(const Telegram::Peer peer, const QString &message, const SendOptions &options = SendOptions()); // Message id is a random number
    //    quint64 forwardMessage(const Telegram::Peer &peer, quint32 messageId);
    //    /* Typing status is valid for 6 seconds. It is recommended to repeat typing status with localTypingRecommendedRepeatInterval() interval. */
    void setMessageAction(const Telegram::Peer peer, TelegramNamespace::MessageAction action);
    void readHistory(const Telegram::Peer peer, quint32 messageId);

Q_SIGNALS:
    void messageReceived(const Telegram::Peer peer, quint32 messageId);
    void messageSent(const Telegram::Peer peer, quint64 messageRandomId, quint32 messageId);
    // We read an incoming message(s)
    void messageReadInbox(const Telegram::Peer peer, quint32 messageId);
    // Our outgoing message(s) was read
    void messageReadOutbox(const Telegram::Peer peer, quint32 messageId);

    void messageActionChanged(const Telegram::Peer &peer, quint32 contactId, TelegramNamespace::MessageAction action);

protected:
    Q_DECLARE_PRIVATE_D(d, MessagingApi)
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_MESSAGING_API_HPP
