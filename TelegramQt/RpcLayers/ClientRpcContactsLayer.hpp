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
    using PendingContactsBlocked = PendingRpcResult<TLContactsBlocked *>;
    using PendingQuint32Vector = PendingRpcResult<TLVector<quint32> *>;
    using PendingContactsContacts = PendingRpcResult<TLContactsContacts *>;
    using PendingSavedContactVector = PendingRpcResult<TLVector<TLSavedContact> *>;
    using PendingContactStatusVector = PendingRpcResult<TLVector<TLContactStatus> *>;
    using PendingContactsTopPeers = PendingRpcResult<TLContactsTopPeers *>;
    using PendingContactsImportedContacts = PendingRpcResult<TLContactsImportedContacts *>;
    using PendingContactsResolvedPeer = PendingRpcResult<TLContactsResolvedPeer *>;
    using PendingContactsFound = PendingRpcResult<TLContactsFound *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *block(const TLInputUser &id);
    PendingBool *deleteByPhones(const TLVector<QString> &phones);
    PendingContactsLink *deleteContact(const TLInputUser &id);
    PendingBool *deleteContacts(const TLVector<TLInputUser> &id);
    PendingContactsBlocked *getBlocked(quint32 offset, quint32 limit);
    PendingQuint32Vector *getContactIDs(quint32 hash);
    PendingContactsContacts *getContacts(quint32 hash);
    PendingSavedContactVector *getSaved();
    PendingContactStatusVector *getStatuses();
    PendingContactsTopPeers *getTopPeers(quint32 flags, quint32 offset, quint32 limit, quint32 hash);
    PendingContactsImportedContacts *importContacts(const TLVector<TLInputContact> &contacts);
    PendingBool *resetSaved();
    PendingBool *resetTopPeerRating(const TLTopPeerCategory &category, const TLInputPeer &peer);
    PendingContactsResolvedPeer *resolveUsername(const QString &username);
    PendingContactsFound *search(const QString &q, quint32 limit);
    PendingBool *toggleTopPeers(bool enabled);
    PendingBool *unblock(const TLInputUser &id);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_CONTACTS_LAYER_HPP
