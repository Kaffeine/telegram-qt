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
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcContactsCategory, "telegram.client.rpclayer.contacts", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsBlocked *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsContacts *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsFound *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsImportedContacts *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsLink *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsResolvedPeer *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLContactsSuggested *output);
// End of generated Telegram API reply template specializations

ContactsRpcLayer::ContactsRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *ContactsRpcLayer::block(const TLInputUser &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsBlock;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::deleteContact(const TLInputUser &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsDeleteContact;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::deleteContacts(const TLVector<TLInputUser> &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsDeleteContacts;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::exportCard()
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsExportCard;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::getBlocked(quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << offset << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsGetBlocked;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::getContacts(const QString &hash)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsGetContacts;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::getStatuses()
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsGetStatuses;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::getSuggested(quint32 limit)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsGetSuggested;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::importCard(const TLVector<quint32> &exportCard)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << exportCard;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsImportCard;
    outputStream << exportCard;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::importContacts(const TLVector<TLInputContact> &contacts, bool replace)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << contacts << replace;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsImportContacts;
    outputStream << contacts;
    outputStream << replace;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::resolveUsername(const QString &username)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << username;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsResolveUsername;
    outputStream << username;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::search(const QString &q, quint32 limit)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << q << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsSearch;
    outputStream << q;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ContactsRpcLayer::unblock(const TLInputUser &id)
{
    qCDebug(c_clientRpcContactsCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ContactsUnblock;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
