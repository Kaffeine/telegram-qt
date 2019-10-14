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

#ifndef TELEGRAMQT_DATA_STORAGE_HPP
#define TELEGRAMQT_DATA_STORAGE_HPP

#include <QObject>

#include "DcConfiguration.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class DataStoragePrivate;

class TELEGRAMQT_EXPORT DataStorage : public QObject
{
    Q_OBJECT
public:
    ~DataStorage() override;
    DcConfiguration serverConfiguration() const;
    void setServerConfiguration(const DcConfiguration &configuration);

    QVector<Telegram::Peer> dialogs() const;
    QVector<Telegram::Peer> pinnedDialogs() const;
    QVector<Telegram::Peer> contactList() const;

    quint32 selfUserId() const;
    bool getDialogInfo(DialogInfo *info, const Telegram::Peer &peer) const;
    bool getUserInfo(UserInfo *info, quint32 userId) const;
    bool getChatInfo(ChatInfo *info, const Telegram::Peer &peer) const;
    Namespace::ChatType getChatType(const Peer &peer) const;

    bool getMessage(Message *message, const Telegram::Peer &peer, quint32 messageId);
    bool getMessageMediaInfo(MessageMediaInfo *info, const Telegram::Peer &peer, quint32 messageId);

protected:
    explicit DataStorage(QObject *parent = nullptr);

    DataStorage(DataStoragePrivate *priv, QObject *parent);
    DataStoragePrivate *d = nullptr;
    Q_DECLARE_PRIVATE_D(d, DataStorage)

};

class TELEGRAMQT_EXPORT InMemoryDataStorage : public DataStorage
{
    Q_OBJECT
public:
    explicit InMemoryDataStorage(QObject *parent = nullptr);

    QByteArray saveState() const;
    void loadState(const QByteArray &data);
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DATA_STORAGE_HPP
