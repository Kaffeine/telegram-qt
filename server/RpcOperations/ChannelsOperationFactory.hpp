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

#ifndef CHANNELS_OPERATION_FACTORY_HPP
#define CHANNELS_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class ChannelsRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(ChannelsRpcOperation)
public:
    explicit ChannelsRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processCheckUsername(RpcProcessingContext &context);
    bool processCreateChannel(RpcProcessingContext &context);
    bool processDeleteChannel(RpcProcessingContext &context);
    bool processDeleteMessages(RpcProcessingContext &context);
    bool processDeleteUserHistory(RpcProcessingContext &context);
    bool processEditAbout(RpcProcessingContext &context);
    bool processEditAdmin(RpcProcessingContext &context);
    bool processEditPhoto(RpcProcessingContext &context);
    bool processEditTitle(RpcProcessingContext &context);
    bool processExportInvite(RpcProcessingContext &context);
    bool processGetChannels(RpcProcessingContext &context);
    bool processGetDialogs(RpcProcessingContext &context);
    bool processGetFullChannel(RpcProcessingContext &context);
    bool processGetImportantHistory(RpcProcessingContext &context);
    bool processGetMessages(RpcProcessingContext &context);
    bool processGetParticipant(RpcProcessingContext &context);
    bool processGetParticipants(RpcProcessingContext &context);
    bool processInviteToChannel(RpcProcessingContext &context);
    bool processJoinChannel(RpcProcessingContext &context);
    bool processKickFromChannel(RpcProcessingContext &context);
    bool processLeaveChannel(RpcProcessingContext &context);
    bool processReadHistory(RpcProcessingContext &context);
    bool processReportSpam(RpcProcessingContext &context);
    bool processToggleComments(RpcProcessingContext &context);
    bool processUpdateUsername(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runCheckUsername();
    void runCreateChannel();
    void runDeleteChannel();
    void runDeleteMessages();
    void runDeleteUserHistory();
    void runEditAbout();
    void runEditAdmin();
    void runEditPhoto();
    void runEditTitle();
    void runExportInvite();
    void runGetChannels();
    void runGetDialogs();
    void runGetFullChannel();
    void runGetImportantHistory();
    void runGetMessages();
    void runGetParticipant();
    void runGetParticipants();
    void runInviteToChannel();
    void runJoinChannel();
    void runKickFromChannel();
    void runLeaveChannel();
    void runReadHistory();
    void runReportSpam();
    void runToggleComments();
    void runUpdateUsername();
    // End of generated run methods

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (ChannelsRpcOperation::*)();
    using ProcessingMethod = bool (ChannelsRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLChannelsCheckUsername m_checkUsername;
    TLFunctions::TLChannelsCreateChannel m_createChannel;
    TLFunctions::TLChannelsDeleteChannel m_deleteChannel;
    TLFunctions::TLChannelsDeleteMessages m_deleteMessages;
    TLFunctions::TLChannelsDeleteUserHistory m_deleteUserHistory;
    TLFunctions::TLChannelsEditAbout m_editAbout;
    TLFunctions::TLChannelsEditAdmin m_editAdmin;
    TLFunctions::TLChannelsEditPhoto m_editPhoto;
    TLFunctions::TLChannelsEditTitle m_editTitle;
    TLFunctions::TLChannelsExportInvite m_exportInvite;
    TLFunctions::TLChannelsGetChannels m_getChannels;
    TLFunctions::TLChannelsGetDialogs m_getDialogs;
    TLFunctions::TLChannelsGetFullChannel m_getFullChannel;
    TLFunctions::TLChannelsGetImportantHistory m_getImportantHistory;
    TLFunctions::TLChannelsGetMessages m_getMessages;
    TLFunctions::TLChannelsGetParticipant m_getParticipant;
    TLFunctions::TLChannelsGetParticipants m_getParticipants;
    TLFunctions::TLChannelsInviteToChannel m_inviteToChannel;
    TLFunctions::TLChannelsJoinChannel m_joinChannel;
    TLFunctions::TLChannelsKickFromChannel m_kickFromChannel;
    TLFunctions::TLChannelsLeaveChannel m_leaveChannel;
    TLFunctions::TLChannelsReadHistory m_readHistory;
    TLFunctions::TLChannelsReportSpam m_reportSpam;
    TLFunctions::TLChannelsToggleComments m_toggleComments;
    TLFunctions::TLChannelsUpdateUsername m_updateUsername;
    // End of generated RPC members
};

class ChannelsOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // CHANNELS_OPERATION_FACTORY_HPP
