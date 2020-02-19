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

#include "ClientRpcContactsLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcContactsCategory, "telegram.client.rpclayer.contacts", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContact *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactBlocked *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactLink *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactStatus *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsBlocked *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsContacts *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsFound *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsImportedContacts *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsLink *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsResolvedPeer *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsTopPeers *output);
// End of generated Telegram API reply template specializations

ContactsRpcLayer::ContactsRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
ContactsRpcLayer::PendingBool *ContactsRpcLayer::block(const TLInputUser &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsBlock;
    outputStream << id;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingBool *ContactsRpcLayer::deleteByPhones(const TLVector<QString> &phones)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << phones;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsDeleteByPhones;
    outputStream << phones;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsLink *ContactsRpcLayer::deleteContact(const TLInputUser &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsDeleteContact;
    outputStream << id;
    PendingContactsLink *op = new PendingContactsLink(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingBool *ContactsRpcLayer::deleteContacts(const TLVector<TLInputUser> &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsDeleteContacts;
    outputStream << id;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsBlocked *ContactsRpcLayer::getBlocked(quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << offset << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsGetBlocked;
    outputStream << offset;
    outputStream << limit;
    PendingContactsBlocked *op = new PendingContactsBlocked(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingQuint32Vector *ContactsRpcLayer::getContactIDs(quint32 hash)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsGetContactIDs;
    outputStream << hash;
    PendingQuint32Vector *op = new PendingQuint32Vector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsContacts *ContactsRpcLayer::getContacts(quint32 hash)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsGetContacts;
    outputStream << hash;
    PendingContactsContacts *op = new PendingContactsContacts(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingSavedContactVector *ContactsRpcLayer::getSaved()
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsGetSaved;
    PendingSavedContactVector *op = new PendingSavedContactVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactStatusVector *ContactsRpcLayer::getStatuses()
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsGetStatuses;
    PendingContactStatusVector *op = new PendingContactStatusVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsTopPeers *ContactsRpcLayer::getTopPeers(quint32 flags, quint32 offset, quint32 limit, quint32 hash)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << flags << offset << limit << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsGetTopPeers;
    outputStream << flags;
    // (flags & 1 << 0) stands for correspondents "true" value
    // (flags & 1 << 1) stands for botsPm "true" value
    // (flags & 1 << 2) stands for botsInline "true" value
    // (flags & 1 << 3) stands for phoneCalls "true" value
    // (flags & 1 << 10) stands for groups "true" value
    // (flags & 1 << 15) stands for channels "true" value
    outputStream << offset;
    outputStream << limit;
    outputStream << hash;
    PendingContactsTopPeers *op = new PendingContactsTopPeers(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsImportedContacts *ContactsRpcLayer::importContacts(const TLVector<TLInputContact> &contacts)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << contacts;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsImportContacts;
    outputStream << contacts;
    PendingContactsImportedContacts *op = new PendingContactsImportedContacts(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingBool *ContactsRpcLayer::resetSaved()
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsResetSaved;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingBool *ContactsRpcLayer::resetTopPeerRating(const TLTopPeerCategory &category, const TLInputPeer &peer)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << category << peer;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsResetTopPeerRating;
    outputStream << category;
    outputStream << peer;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsResolvedPeer *ContactsRpcLayer::resolveUsername(const QString &username)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << username;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsResolveUsername;
    outputStream << username;
    PendingContactsResolvedPeer *op = new PendingContactsResolvedPeer(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingContactsFound *ContactsRpcLayer::search(const QString &q, quint32 limit)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << q << limit;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsSearch;
    outputStream << q;
    outputStream << limit;
    PendingContactsFound *op = new PendingContactsFound(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingBool *ContactsRpcLayer::toggleTopPeers(bool enabled)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << enabled;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsToggleTopPeers;
    outputStream << enabled;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

ContactsRpcLayer::PendingBool *ContactsRpcLayer::unblock(const TLInputUser &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ContactsUnblock;
    outputStream << id;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
