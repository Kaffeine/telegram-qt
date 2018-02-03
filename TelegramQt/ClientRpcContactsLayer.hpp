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

#ifndef TELEGRAM_CLIENT_RPC_CONTACTS_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_CONTACTS_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class ContactsRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit ContactsRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *block(const TLInputUser &id);
    PendingRpcOperation *deleteContact(const TLInputUser &id);
    PendingRpcOperation *deleteContacts(const TLVector<TLInputUser> &id);
    PendingRpcOperation *exportCard();
    PendingRpcOperation *getBlocked(quint32 offset, quint32 limit);
    PendingRpcOperation *getContacts(quint32 hash);
    PendingRpcOperation *getStatuses();
    PendingRpcOperation *getTopPeers(quint32 flags, quint32 offset, quint32 limit, quint32 hash);
    PendingRpcOperation *importCard(const TLVector<quint32> &exportCard);
    PendingRpcOperation *importContacts(const TLVector<TLInputContact> &contacts);
    PendingRpcOperation *resetSaved();
    PendingRpcOperation *resetTopPeerRating(const TLTopPeerCategory &category, const TLInputPeer &peer);
    PendingRpcOperation *resolveUsername(const QString &username);
    PendingRpcOperation *search(const QString &q, quint32 limit);
    PendingRpcOperation *unblock(const TLInputUser &id);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_CONTACTS_LAYER_HPP
