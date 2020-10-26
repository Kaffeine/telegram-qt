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

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class ContactsRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit ContactsRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingContactsLink = PendingRpcResult<TLContactsLink *>;
    using PendingQuint32Vector = PendingRpcResult<QVector<quint32> *>;
    using PendingContactsBlocked = PendingRpcResult<TLContactsBlocked *>;
    using PendingContactsContacts = PendingRpcResult<TLContactsContacts *>;
    using PendingContactStatusVector = PendingRpcResult<QVector<TLContactStatus> *>;
    using PendingContactsTopPeers = PendingRpcResult<TLContactsTopPeers *>;
    using PendingUser = PendingRpcResult<TLUser *>;
    using PendingContactsImportedContacts = PendingRpcResult<TLContactsImportedContacts *>;
    using PendingContactsResolvedPeer = PendingRpcResult<TLContactsResolvedPeer *>;
    using PendingContactsFound = PendingRpcResult<TLContactsFound *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *block(const TLInputUser &id);
    PendingContactsLink *deleteContact(const TLInputUser &id);
    PendingBool *deleteContacts(const QVector<TLInputUser> &id);
    PendingQuint32Vector *exportCard();
    PendingContactsBlocked *getBlocked(quint32 offset, quint32 limit);
    PendingContactsContacts *getContacts(quint32 hash);
    PendingContactStatusVector *getStatuses();
    PendingContactsTopPeers *getTopPeers(quint32 flags, quint32 offset, quint32 limit, quint32 hash);
    PendingUser *importCard(const QVector<quint32> &exportCard);
    PendingContactsImportedContacts *importContacts(const QVector<TLInputContact> &contacts);
    PendingBool *resetSaved();
    PendingBool *resetTopPeerRating(const TLTopPeerCategory &category, const TLInputPeer &peer);
    PendingContactsResolvedPeer *resolveUsername(const QString &username);
    PendingContactsFound *search(const QString &q, quint32 limit);
    PendingBool *unblock(const TLInputUser &id);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_CONTACTS_LAYER_HPP
