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

#include "Peer.hpp"
#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

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
    bool processDeleteByPhones(RpcProcessingContext &context);
    bool processDeleteContact(RpcProcessingContext &context);
    bool processDeleteContacts(RpcProcessingContext &context);
    bool processGetBlocked(RpcProcessingContext &context);
    bool processGetContactIDs(RpcProcessingContext &context);
    bool processGetContacts(RpcProcessingContext &context);
    bool processGetSaved(RpcProcessingContext &context);
    bool processGetStatuses(RpcProcessingContext &context);
    bool processGetTopPeers(RpcProcessingContext &context);
    bool processImportContacts(RpcProcessingContext &context);
    bool processResetSaved(RpcProcessingContext &context);
    bool processResetTopPeerRating(RpcProcessingContext &context);
    bool processResolveUsername(RpcProcessingContext &context);
    bool processSearch(RpcProcessingContext &context);
    bool processToggleTopPeers(RpcProcessingContext &context);
    bool processUnblock(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runBlock();
    void runDeleteByPhones();
    void runDeleteContact();
    void runDeleteContacts();
    void runGetBlocked();
    void runGetContactIDs();
    void runGetContacts();
    void runGetSaved();
    void runGetStatuses();
    void runGetTopPeers();
    void runImportContacts();
    void runResetSaved();
    void runResetTopPeerRating();
    void runResolveUsername();
    void runSearch();
    void runToggleTopPeers();
    void runUnblock();
    // End of generated run methods

    using RunMethod = void (ContactsRpcOperation::*)();
    using ProcessingMethod = bool (ContactsRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    void onContactsSearchFinished();

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLContactsBlock m_block;
    MTProto::Functions::TLContactsDeleteByPhones m_deleteByPhones;
    MTProto::Functions::TLContactsDeleteContact m_deleteContact;
    MTProto::Functions::TLContactsDeleteContacts m_deleteContacts;
    MTProto::Functions::TLContactsGetBlocked m_getBlocked;
    MTProto::Functions::TLContactsGetContactIDs m_getContactIDs;
    MTProto::Functions::TLContactsGetContacts m_getContacts;
    MTProto::Functions::TLContactsGetSaved m_getSaved;
    MTProto::Functions::TLContactsGetStatuses m_getStatuses;
    MTProto::Functions::TLContactsGetTopPeers m_getTopPeers;
    MTProto::Functions::TLContactsImportContacts m_importContacts;
    MTProto::Functions::TLContactsResetSaved m_resetSaved;
    MTProto::Functions::TLContactsResetTopPeerRating m_resetTopPeerRating;
    MTProto::Functions::TLContactsResolveUsername m_resolveUsername;
    MTProto::Functions::TLContactsSearch m_search;
    MTProto::Functions::TLContactsToggleTopPeers m_toggleTopPeers;
    MTProto::Functions::TLContactsUnblock m_unblock;
    // End of generated RPC members

    QVector<Peer> m_searchResult;
};

class ContactsOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // CONTACTS_OPERATION_FACTORY_HPP
