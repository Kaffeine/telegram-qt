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

#include "TLTypes.hpp"

#include <QHash>

namespace Telegram {

namespace Client {

class DataInternalApi;

class DataStoragePrivate
{
public:
    static DataStoragePrivate *get(DataStorage *parent);

    DataInternalApi *internalApi() { return m_api; }

    DcConfiguration m_serverConfig;
    DataInternalApi *m_api = nullptr;
};

class DataInternalApi : public QObject
{
    Q_OBJECT
public:
    explicit DataInternalApi(QObject *parent = nullptr);
    ~DataInternalApi() override;

    static DataInternalApi *get(DataStorage *parent) { return DataStoragePrivate::get(parent)->internalApi(); }

    const TLUser *getSelfUser() const;
    const TLMessage *getMessage(const Telegram::Peer &peer, quint32 messageId) const;

    void processData(const TLMessage &message);
    void processData(const TLVector<TLChat> &chats);
    void processData(const TLChat &chat);
    void processData(const TLVector<TLUser> &users);
    void processData(const TLUser &user);
    void processData(const TLAuthAuthorization &authorization);
    void processData(const TLMessagesDialogs &dialogs);
    void processData(const TLMessagesMessages &messages);

    void setContactList(const TLVector<TLContact> &contacts);

    quint32 selfUserId() const { return m_selfUserId; }

    TLInputPeer toInputPeer(const Telegram::Peer &peer) const;

    static quint64 channelMessageToKey(quint32 channelId, quint32 messageId);

    TLVector<TLContact> contactList() const { return m_contactList; }

    quint32 m_selfUserId = 0;
    QHash<quint32, TLUser *> m_users;
    QHash<quint32, TLChat *> m_chats;
    QHash<quint32, TLMessage *> m_clientMessages;
    QHash<quint64, TLMessage *> m_channelMessages;
    TLMessagesDialogs m_dialogs;
    TLVector<TLContact> m_contactList;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DATA_STORAGE_P_HPP
