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
    bool processDeleteHistory(RpcProcessingContext &context);
    bool processDeleteMessages(RpcProcessingContext &context);
    bool processDeleteUserHistory(RpcProcessingContext &context);
    bool processEditAbout(RpcProcessingContext &context);
    bool processEditAdmin(RpcProcessingContext &context);
    bool processEditBanned(RpcProcessingContext &context);
    bool processEditPhoto(RpcProcessingContext &context);
    bool processEditTitle(RpcProcessingContext &context);
    bool processExportInvite(RpcProcessingContext &context);
    bool processExportMessageLink(RpcProcessingContext &context);
    bool processGetAdminLog(RpcProcessingContext &context);
    bool processGetAdminedPublicChannels(RpcProcessingContext &context);
    bool processGetChannels(RpcProcessingContext &context);
    bool processGetFullChannel(RpcProcessingContext &context);
    bool processGetLeftChannels(RpcProcessingContext &context);
    bool processGetMessages(RpcProcessingContext &context);
    bool processGetParticipant(RpcProcessingContext &context);
    bool processGetParticipants(RpcProcessingContext &context);
    bool processInviteToChannel(RpcProcessingContext &context);
    bool processJoinChannel(RpcProcessingContext &context);
    bool processLeaveChannel(RpcProcessingContext &context);
    bool processReadHistory(RpcProcessingContext &context);
    bool processReadMessageContents(RpcProcessingContext &context);
    bool processReportSpam(RpcProcessingContext &context);
    bool processSetStickers(RpcProcessingContext &context);
    bool processToggleInvites(RpcProcessingContext &context);
    bool processTogglePreHistoryHidden(RpcProcessingContext &context);
    bool processToggleSignatures(RpcProcessingContext &context);
    bool processUpdateUsername(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runCheckUsername();
    void runCreateChannel();
    void runDeleteChannel();
    void runDeleteHistory();
    void runDeleteMessages();
    void runDeleteUserHistory();
    void runEditAbout();
    void runEditAdmin();
    void runEditBanned();
    void runEditPhoto();
    void runEditTitle();
    void runExportInvite();
    void runExportMessageLink();
    void runGetAdminLog();
    void runGetAdminedPublicChannels();
    void runGetChannels();
    void runGetFullChannel();
    void runGetLeftChannels();
    void runGetMessages();
    void runGetParticipant();
    void runGetParticipants();
    void runInviteToChannel();
    void runJoinChannel();
    void runLeaveChannel();
    void runReadHistory();
    void runReadMessageContents();
    void runReportSpam();
    void runSetStickers();
    void runToggleInvites();
    void runTogglePreHistoryHidden();
    void runToggleSignatures();
    void runUpdateUsername();
    // End of generated run methods

    using RunMethod = void (ChannelsRpcOperation::*)();
    using ProcessingMethod = bool (ChannelsRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLChannelsCheckUsername m_checkUsername;
    MTProto::Functions::TLChannelsCreateChannel m_createChannel;
    MTProto::Functions::TLChannelsDeleteChannel m_deleteChannel;
    MTProto::Functions::TLChannelsDeleteHistory m_deleteHistory;
    MTProto::Functions::TLChannelsDeleteMessages m_deleteMessages;
    MTProto::Functions::TLChannelsDeleteUserHistory m_deleteUserHistory;
    MTProto::Functions::TLChannelsEditAbout m_editAbout;
    MTProto::Functions::TLChannelsEditAdmin m_editAdmin;
    MTProto::Functions::TLChannelsEditBanned m_editBanned;
    MTProto::Functions::TLChannelsEditPhoto m_editPhoto;
    MTProto::Functions::TLChannelsEditTitle m_editTitle;
    MTProto::Functions::TLChannelsExportInvite m_exportInvite;
    MTProto::Functions::TLChannelsExportMessageLink m_exportMessageLink;
    MTProto::Functions::TLChannelsGetAdminLog m_getAdminLog;
    MTProto::Functions::TLChannelsGetAdminedPublicChannels m_getAdminedPublicChannels;
    MTProto::Functions::TLChannelsGetChannels m_getChannels;
    MTProto::Functions::TLChannelsGetFullChannel m_getFullChannel;
    MTProto::Functions::TLChannelsGetLeftChannels m_getLeftChannels;
    MTProto::Functions::TLChannelsGetMessages m_getMessages;
    MTProto::Functions::TLChannelsGetParticipant m_getParticipant;
    MTProto::Functions::TLChannelsGetParticipants m_getParticipants;
    MTProto::Functions::TLChannelsInviteToChannel m_inviteToChannel;
    MTProto::Functions::TLChannelsJoinChannel m_joinChannel;
    MTProto::Functions::TLChannelsLeaveChannel m_leaveChannel;
    MTProto::Functions::TLChannelsReadHistory m_readHistory;
    MTProto::Functions::TLChannelsReadMessageContents m_readMessageContents;
    MTProto::Functions::TLChannelsReportSpam m_reportSpam;
    MTProto::Functions::TLChannelsSetStickers m_setStickers;
    MTProto::Functions::TLChannelsToggleInvites m_toggleInvites;
    MTProto::Functions::TLChannelsTogglePreHistoryHidden m_togglePreHistoryHidden;
    MTProto::Functions::TLChannelsToggleSignatures m_toggleSignatures;
    MTProto::Functions::TLChannelsUpdateUsername m_updateUsername;
    // End of generated RPC members
};

class ChannelsOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // CHANNELS_OPERATION_FACTORY_HPP
