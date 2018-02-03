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

#ifndef CONTACTS_OPERATION_FACTORY_HPP
#define CONTACTS_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class ContactsRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(ContactsRpcOperation)
public:
    explicit ContactsRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processBlock(RpcProcessingContext &context);
    bool processDeleteContact(RpcProcessingContext &context);
    bool processDeleteContacts(RpcProcessingContext &context);
    bool processExportCard(RpcProcessingContext &context);
    bool processGetBlocked(RpcProcessingContext &context);
    bool processGetContacts(RpcProcessingContext &context);
    bool processGetStatuses(RpcProcessingContext &context);
    bool processGetTopPeers(RpcProcessingContext &context);
    bool processImportCard(RpcProcessingContext &context);
    bool processImportContacts(RpcProcessingContext &context);
    bool processResetSaved(RpcProcessingContext &context);
    bool processResetTopPeerRating(RpcProcessingContext &context);
    bool processResolveUsername(RpcProcessingContext &context);
    bool processSearch(RpcProcessingContext &context);
    bool processUnblock(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runBlock();
    void runDeleteContact();
    void runDeleteContacts();
    void runExportCard();
    void runGetBlocked();
    void runGetContacts();
    void runGetStatuses();
    void runGetTopPeers();
    void runImportCard();
    void runImportContacts();
    void runResetSaved();
    void runResetTopPeerRating();
    void runResolveUsername();
    void runSearch();
    void runUnblock();
    // End of generated run methods

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (ContactsRpcOperation::*)();
    using ProcessingMethod = bool (ContactsRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLContactsBlock m_block;
    TLFunctions::TLContactsDeleteContact m_deleteContact;
    TLFunctions::TLContactsDeleteContacts m_deleteContacts;
    TLFunctions::TLContactsExportCard m_exportCard;
    TLFunctions::TLContactsGetBlocked m_getBlocked;
    TLFunctions::TLContactsGetContacts m_getContacts;
    TLFunctions::TLContactsGetStatuses m_getStatuses;
    TLFunctions::TLContactsGetTopPeers m_getTopPeers;
    TLFunctions::TLContactsImportCard m_importCard;
    TLFunctions::TLContactsImportContacts m_importContacts;
    TLFunctions::TLContactsResetSaved m_resetSaved;
    TLFunctions::TLContactsResetTopPeerRating m_resetTopPeerRating;
    TLFunctions::TLContactsResolveUsername m_resolveUsername;
    TLFunctions::TLContactsSearch m_search;
    TLFunctions::TLContactsUnblock m_unblock;
    // End of generated RPC members
};

class ContactsOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // CONTACTS_OPERATION_FACTORY_HPP
