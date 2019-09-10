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

#include "ContactsOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ApiUtils.hpp"
#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "ServerUtils.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool ContactsRpcOperation::processBlock(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runBlock);
    context.inputStream() >> m_block;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processDeleteContact(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runDeleteContact);
    context.inputStream() >> m_deleteContact;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processDeleteContacts(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runDeleteContacts);
    context.inputStream() >> m_deleteContacts;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processExportCard(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runExportCard);
    context.inputStream() >> m_exportCard;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processGetBlocked(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runGetBlocked);
    context.inputStream() >> m_getBlocked;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processGetContacts(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runGetContacts);
    context.inputStream() >> m_getContacts;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processGetStatuses(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runGetStatuses);
    context.inputStream() >> m_getStatuses;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processGetTopPeers(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runGetTopPeers);
    context.inputStream() >> m_getTopPeers;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processImportCard(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runImportCard);
    context.inputStream() >> m_importCard;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processImportContacts(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runImportContacts);
    context.inputStream() >> m_importContacts;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processResetSaved(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runResetSaved);
    context.inputStream() >> m_resetSaved;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processResetTopPeerRating(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runResetTopPeerRating);
    context.inputStream() >> m_resetTopPeerRating;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processResolveUsername(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runResolveUsername);
    context.inputStream() >> m_resolveUsername;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processSearch(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runSearch);
    context.inputStream() >> m_search;
    return !context.inputStream().error();
}

bool ContactsRpcOperation::processUnblock(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runUnblock);
    context.inputStream() >> m_unblock;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void ContactsRpcOperation::runBlock()
{
    // MTProto::Functions::TLContactsBlock &arguments = m_block;
    if (processNotImplementedMethod(TLValue::ContactsBlock)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runDeleteContact()
{
    qWarning() << Q_FUNC_INFO << "The method implemented!";
    TLContactsLink result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runDeleteContacts()
{
    // MTProto::Functions::TLContactsDeleteContacts &arguments = m_deleteContacts;
    if (processNotImplementedMethod(TLValue::ContactsDeleteContacts)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runExportCard()
{
    if (processNotImplementedMethod(TLValue::ContactsExportCard)) {
        return;
    }
    TLVector<quint32> result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetBlocked()
{
    // MTProto::Functions::TLContactsGetBlocked &arguments = m_getBlocked;
    if (processNotImplementedMethod(TLValue::ContactsGetBlocked)) {
        return;
    }
    TLContactsBlocked result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetContacts()
{
    TLContactsContacts result;
    result.tlType = TLValue::ContactsContacts;

    const LocalUser *selfUser = layer()->getUser();

    const QVector<UserContact> importedContacts = selfUser->importedContacts();
    result.contacts.reserve(importedContacts.size());
    result.users.reserve(importedContacts.size());

    TLUser userInfo;
    TLContact outputContact;
    for (const UserContact &contact : importedContacts) {
        if (contact.id) {
            const AbstractUser *contactUser = api()->getAbstractUser(contact.id);
            Utils::setupTLUser(&userInfo, contactUser, selfUser);
            result.users.append(userInfo);

            outputContact.userId = contact.id;
            outputContact.mutual = userInfo.flags & TLUser::MutualContact;
            result.contacts.append(outputContact);
        } else {
            ++result.savedCount;
        }
    }

    sendRpcReply(result);
}

void ContactsRpcOperation::runGetStatuses()
{
    if (processNotImplementedMethod(TLValue::ContactsGetStatuses)) {
        return;
    }
    TLVector<TLContactStatus> result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetTopPeers()
{
    // MTProto::Functions::TLContactsGetTopPeers &arguments = m_getTopPeers;
    if (processNotImplementedMethod(TLValue::ContactsGetTopPeers)) {
        return;
    }
    TLContactsTopPeers result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runImportCard()
{
    // MTProto::Functions::TLContactsImportCard &arguments = m_importCard;
    if (processNotImplementedMethod(TLValue::ContactsImportCard)) {
        return;
    }
    TLUser result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runImportContacts()
{
    qDebug() << Q_FUNC_INFO;
    TLContactsImportedContacts result;

    LocalUser *selfUser = layer()->getUser();

    for (const TLInputContact &c : m_importContacts.contacts) {
        UserContact contact;
        contact.phone = api()->normalizeIdentifier(c.phone);
        contact.firstName = c.firstName;
        contact.lastName = c.lastName;

        AbstractUser *contactUser = api()->importUserContact(selfUser, contact);
        if (contactUser) {
            result.users.append(TLUser());
            Utils::setupTLUser(&result.users.last(), contactUser, selfUser);

            TLImportedContact imported;
            imported.clientId = c.clientId;
            imported.userId = contact.id;
            result.imported.append(imported);
        } else {
            // TODO: Check if this is correct.
            result.retryContacts.append(c.clientId);
        }
    }

    sendRpcReply(result);
}

void ContactsRpcOperation::runResetSaved()
{
    if (processNotImplementedMethod(TLValue::ContactsResetSaved)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runResetTopPeerRating()
{
    // MTProto::Functions::TLContactsResetTopPeerRating &arguments = m_resetTopPeerRating;
    if (processNotImplementedMethod(TLValue::ContactsResetTopPeerRating)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runResolveUsername()
{
    MTProto::Functions::TLContactsResolveUsername &arguments = m_resolveUsername;
    if (!api()->usernameIsValid(arguments.username)) {
        sendRpcError(RpcError::UsernameInvalid);
        return;
    }
    TLContactsResolvedPeer result;
    const Peer peer = api()->getPeerByUserName(arguments.username);
    result.peer = Telegram::Utils::toTLPeer(peer);
    Utils::setupTLPeers(&result, { peer }, api(), layer()->getUser());
    sendRpcReply(result);
}

void ContactsRpcOperation::runSearch()
{
    // MTProto::Functions::TLContactsSearch &arguments = m_search;
    if (processNotImplementedMethod(TLValue::ContactsSearch)) {
        return;
    }
    TLContactsFound result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runUnblock()
{
    // MTProto::Functions::TLContactsUnblock &arguments = m_unblock;
    if (processNotImplementedMethod(TLValue::ContactsUnblock)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}
// End of generated run methods

void ContactsRpcOperation::setRunMethod(ContactsRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

ContactsRpcOperation::ProcessingMethod ContactsRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::ContactsBlock:
        return &ContactsRpcOperation::processBlock;
    case TLValue::ContactsDeleteContact:
        return &ContactsRpcOperation::processDeleteContact;
    case TLValue::ContactsDeleteContacts:
        return &ContactsRpcOperation::processDeleteContacts;
    case TLValue::ContactsExportCard:
        return &ContactsRpcOperation::processExportCard;
    case TLValue::ContactsGetBlocked:
        return &ContactsRpcOperation::processGetBlocked;
    case TLValue::ContactsGetContacts:
        return &ContactsRpcOperation::processGetContacts;
    case TLValue::ContactsGetStatuses:
        return &ContactsRpcOperation::processGetStatuses;
    case TLValue::ContactsGetTopPeers:
        return &ContactsRpcOperation::processGetTopPeers;
    case TLValue::ContactsImportCard:
        return &ContactsRpcOperation::processImportCard;
    case TLValue::ContactsImportContacts:
        return &ContactsRpcOperation::processImportContacts;
    case TLValue::ContactsResetSaved:
        return &ContactsRpcOperation::processResetSaved;
    case TLValue::ContactsResetTopPeerRating:
        return &ContactsRpcOperation::processResetTopPeerRating;
    case TLValue::ContactsResolveUsername:
        return &ContactsRpcOperation::processResolveUsername;
    case TLValue::ContactsSearch:
        return &ContactsRpcOperation::processSearch;
    case TLValue::ContactsUnblock:
        return &ContactsRpcOperation::processUnblock;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *ContactsOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<ContactsRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
