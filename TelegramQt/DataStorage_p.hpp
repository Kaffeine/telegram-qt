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

#ifndef TELEGRAMQT_DATA_STORAGE_P_HPP
#define TELEGRAMQT_DATA_STORAGE_P_HPP

#include "DataStorage.hpp"

#include "MTProto/TLTypes.hpp"
#include "TelegramNamespace_p.hpp"

#include <QHash>
#include <QQueue>

namespace Telegram {

namespace Client {

class DataInternalApi;

class DialogState {
public:
    bool isValid() const { return syncedMessageId || !pendingIds.isEmpty() || synced; }
    // The most recent message id we ever know for this dialog
    // The last message id that we sent to Telepathy Client for this dialog
    quint32 syncedMessageId = 0;
    QVector<quint32> pendingIds;

    // This dialog is synced
    bool synced = false;
};

class TELEGRAMQT_INTERNAL_EXPORT DataStoragePrivate
{
public:
    static DataStoragePrivate *get(DataStorage *parent);
    static DataStoragePrivate *get(const DataStorage *parent);

    DataInternalApi *internalApi() { return m_api; }
    const DataInternalApi *internalApi() const { return m_api; }

    DcConfiguration m_serverConfig;
    DataInternalApi *m_api = nullptr;
};

class TELEGRAMQT_INTERNAL_EXPORT DataInternalApi : public QObject
{
    Q_OBJECT
public:
    explicit DataInternalApi(QObject *parent = nullptr);
    ~DataInternalApi() override;

    struct SentMessage {
        QString text;
        Peer peer;
        quint64 randomId;
        quint32 replyToMsgId;
    };

    static DataInternalApi *get(DataStorage *parent) { return DataStoragePrivate::get(parent)->internalApi(); }
    static DataInternalApi *get(const DataStorage *parent) { return DataStoragePrivate::get(parent)->internalApi(); }

    const TLUser *getSelfUser() const;
    const TLMessage *getMessage(const Telegram::Peer &peer, quint32 messageId) const;

    bool processNewMessage(const TLMessage &message, quint32 pts);
    void processData(const TLMessage &message);
    void processData(const TLVector<TLChat> &chats);
    void processData(const TLChat &chat);
    void processData(const TLVector<TLUser> &users);
    void processData(const TLUser &user);
    void processData(const TLAuthAuthorization &authorization);
    void processData(const TLMessagesDialogs &dialogs);
    void processData(const TLMessagesMessages &messages);

    void setContactList(const TLVector<TLContact> &contacts);
    void clearPinnedDialogs();

    quint64 enqueueMessage(const Peer peer, const QString &message, quint32 replyToMsgId);
    SentMessage getQueuedMessage(quint64 randomMessageId) const;
    SentMessage dequeueMessage(quint64 messageRandomId, quint32 messageId);
    QVector<quint64> getPostedMessages() const;
    void enqueueMessageRead(const Peer peer, quint32 messageId);
    void dequeueMessageRead(const Peer peer, quint32 messageId);
    bool updateInboxRead(const Peer peer, quint32 maxId);
    bool updateOutboxRead(const Peer peer, quint32 maxId);
    bool updateUserPhoto(quint32 userId, const TLUserProfilePhoto &photo);

    quint32 selfUserId() const { return m_selfUserId; }

    TLInputPeer toInputPeer(const TLPeer &peer) const;
    TLInputPeer toInputPeer(const Telegram::Peer &peer) const;
    TLInputUser toInputUser(quint32 userId) const;
    TLInputChannel toInputChannel(quint32 channelId) const;

    static quint64 channelMessageToKey(quint32 channelId, quint32 messageId);

    TLVector<TLContact> contactList() const { return m_contactList; }
    const QHash<quint32, TLUser *> &users() const { return m_users; }
    const QHash<quint32, TLChat *> &chats() const { return m_chats; }
    const TLVector<UserDialog *> &dialogs() const { return m_dialogs; }
    const QVector<Peer> &pinnedDialogs() const { return m_pinnedDialogs; }
    UserDialog *getDialog(const Peer &peer) const;
    UserDialog *ensureDialog(const Peer &peer);

    const QHash<Peer, DialogState> *dialogStates() const { return &m_dialogStates; }
    QHash<Peer, DialogState> *dialogStates() { return &m_dialogStates; }

    // For testing:
    const DialogState getDialogState(const Peer peer) const;

protected:
    void updateDialogsOrder();

    QHash<Telegram::Peer, DialogState> m_dialogStates;

    QHash<quint32, TLUser *> m_users;
    QHash<quint32, TLChat *> m_chats;
    QHash<quint32, TLMessage *> m_clientMessages;
    QHash<quint64, TLMessage *> m_channelMessages;
    TLVector<UserDialog *> m_dialogs;
    QVector<Peer> m_pinnedDialogs;
    TLVector<TLContact> m_contactList;
    QQueue<SentMessage> m_queuedMessages;
    quint32 m_selfUserId = 0;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DATA_STORAGE_P_HPP
