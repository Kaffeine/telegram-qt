/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_CLIENT_UPDATES_API_P_HPP
#define TELEGRAMQT_CLIENT_UPDATES_API_P_HPP

#include <QObject>

#include "MTProto/TLTypes.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class Backend;
class ContactsApiPrivate;
class DataStorage;
class DataInternalApi;
class MessagingApiPrivate;

class UpdatesInternalApi : public QObject
{
    Q_OBJECT
public:
    explicit UpdatesInternalApi(QObject *parent = nullptr);

    void setBackend(Backend *backend);

    bool processUpdates(const TLUpdates &updates);
    bool processUpdate(const TLUpdate &update);
    void processReadInbox(const Telegram::Peer peer, quint32 maxId);
    void processReadOutbox(const Telegram::Peer peer, quint32 maxId);

protected:
    MessagingApiPrivate *messagingApi();
    ContactsApiPrivate *contactsApi();
    DataStorage *dataStorage();
    DataInternalApi *dataInternalApi();

    Backend *m_backend = nullptr;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_UPDATES_API_P_HPP
