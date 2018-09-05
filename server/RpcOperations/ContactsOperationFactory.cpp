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

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"
#include "Utils.hpp"

#include "CTelegramStreamExtraOperators.hpp"
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
    if (processNotImplementedMethod(TLValue::ContactsGetBlocked)) {
        return;
    }
    TLContactsBlocked result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetContacts()
{
    if (processNotImplementedMethod(TLValue::ContactsGetContacts)) {
        return;
    }
    TLContactsContacts result;
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
    if (processNotImplementedMethod(TLValue::ContactsGetTopPeers)) {
        return;
    }
    TLContactsTopPeers result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runImportCard()
{
    if (processNotImplementedMethod(TLValue::ContactsImportCard)) {
        return;
    }
    TLUser result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runImportContacts()
{
    if (processNotImplementedMethod(TLValue::ContactsImportContacts)) {
        return;
    }
    TLContactsImportedContacts result;
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
    if (processNotImplementedMethod(TLValue::ContactsResetTopPeerRating)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runResolveUsername()
{
    if (processNotImplementedMethod(TLValue::ContactsResolveUsername)) {
        return;
    }
    TLContactsResolvedPeer result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runSearch()
{
    if (processNotImplementedMethod(TLValue::ContactsSearch)) {
        return;
    }
    TLContactsFound result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runUnblock()
{
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

} // Server

} // Telegram
