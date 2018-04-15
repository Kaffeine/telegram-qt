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

bool ContactsRpcOperation::processGetSuggested(RpcProcessingContext &context)
{
    setRunMethod(&ContactsRpcOperation::runGetSuggested);
    context.inputStream() >> m_getSuggested;
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
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
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
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runExportCard()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLVector<quint32> result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetBlocked()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLContactsBlocked result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetContacts()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLContactsContacts result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetStatuses()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLVector<TLContactStatus> result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runGetSuggested()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLContactsSuggested result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runImportCard()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUser result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runImportContacts()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLContactsImportedContacts result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runResolveUsername()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLContactsResolvedPeer result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runSearch()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLContactsFound result;
    sendRpcReply(result);
}

void ContactsRpcOperation::runUnblock()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
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
    case TLValue::ContactsGetSuggested:
        return &ContactsRpcOperation::processGetSuggested;
    case TLValue::ContactsImportCard:
        return &ContactsRpcOperation::processImportCard;
    case TLValue::ContactsImportContacts:
        return &ContactsRpcOperation::processImportContacts;
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
