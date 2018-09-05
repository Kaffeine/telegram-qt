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

#include "ChannelsOperationFactory.hpp"

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
bool ChannelsRpcOperation::processCheckUsername(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runCheckUsername);
    context.inputStream() >> m_checkUsername;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processCreateChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runCreateChannel);
    context.inputStream() >> m_createChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processDeleteChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runDeleteChannel);
    context.inputStream() >> m_deleteChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processDeleteHistory(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runDeleteHistory);
    context.inputStream() >> m_deleteHistory;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processDeleteMessages(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runDeleteMessages);
    context.inputStream() >> m_deleteMessages;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processDeleteUserHistory(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runDeleteUserHistory);
    context.inputStream() >> m_deleteUserHistory;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processEditAbout(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runEditAbout);
    context.inputStream() >> m_editAbout;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processEditAdmin(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runEditAdmin);
    context.inputStream() >> m_editAdmin;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processEditBanned(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runEditBanned);
    context.inputStream() >> m_editBanned;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processEditPhoto(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runEditPhoto);
    context.inputStream() >> m_editPhoto;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processEditTitle(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runEditTitle);
    context.inputStream() >> m_editTitle;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processExportInvite(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runExportInvite);
    context.inputStream() >> m_exportInvite;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processExportMessageLink(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runExportMessageLink);
    context.inputStream() >> m_exportMessageLink;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetAdminLog(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetAdminLog);
    context.inputStream() >> m_getAdminLog;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetAdminedPublicChannels(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetAdminedPublicChannels);
    context.inputStream() >> m_getAdminedPublicChannels;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetChannels(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetChannels);
    context.inputStream() >> m_getChannels;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetFullChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetFullChannel);
    context.inputStream() >> m_getFullChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetMessages(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetMessages);
    context.inputStream() >> m_getMessages;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetParticipant(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetParticipant);
    context.inputStream() >> m_getParticipant;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetParticipants(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetParticipants);
    context.inputStream() >> m_getParticipants;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processInviteToChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runInviteToChannel);
    context.inputStream() >> m_inviteToChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processJoinChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runJoinChannel);
    context.inputStream() >> m_joinChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processLeaveChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runLeaveChannel);
    context.inputStream() >> m_leaveChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processReadHistory(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runReadHistory);
    context.inputStream() >> m_readHistory;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processReadMessageContents(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runReadMessageContents);
    context.inputStream() >> m_readMessageContents;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processReportSpam(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runReportSpam);
    context.inputStream() >> m_reportSpam;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processSetStickers(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runSetStickers);
    context.inputStream() >> m_setStickers;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processToggleInvites(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runToggleInvites);
    context.inputStream() >> m_toggleInvites;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processTogglePreHistoryHidden(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runTogglePreHistoryHidden);
    context.inputStream() >> m_togglePreHistoryHidden;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processToggleSignatures(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runToggleSignatures);
    context.inputStream() >> m_toggleSignatures;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processUpdatePinnedMessage(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runUpdatePinnedMessage);
    context.inputStream() >> m_updatePinnedMessage;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processUpdateUsername(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runUpdateUsername);
    context.inputStream() >> m_updateUsername;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void ChannelsRpcOperation::runCheckUsername()
{
    if (processNotImplementedMethod(TLValue::ChannelsCheckUsername)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runCreateChannel()
{
    if (processNotImplementedMethod(TLValue::ChannelsCreateChannel)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteChannel()
{
    if (processNotImplementedMethod(TLValue::ChannelsDeleteChannel)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteHistory()
{
    if (processNotImplementedMethod(TLValue::ChannelsDeleteHistory)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteMessages()
{
    if (processNotImplementedMethod(TLValue::ChannelsDeleteMessages)) {
        return;
    }
    TLMessagesAffectedMessages result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteUserHistory()
{
    if (processNotImplementedMethod(TLValue::ChannelsDeleteUserHistory)) {
        return;
    }
    TLMessagesAffectedHistory result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditAbout()
{
    if (processNotImplementedMethod(TLValue::ChannelsEditAbout)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditAdmin()
{
    if (processNotImplementedMethod(TLValue::ChannelsEditAdmin)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditBanned()
{
    if (processNotImplementedMethod(TLValue::ChannelsEditBanned)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditPhoto()
{
    if (processNotImplementedMethod(TLValue::ChannelsEditPhoto)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditTitle()
{
    if (processNotImplementedMethod(TLValue::ChannelsEditTitle)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runExportInvite()
{
    if (processNotImplementedMethod(TLValue::ChannelsExportInvite)) {
        return;
    }
    TLExportedChatInvite result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runExportMessageLink()
{
    if (processNotImplementedMethod(TLValue::ChannelsExportMessageLink)) {
        return;
    }
    TLExportedMessageLink result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetAdminLog()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetAdminLog)) {
        return;
    }
    TLChannelsAdminLogResults result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetAdminedPublicChannels()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetAdminedPublicChannels)) {
        return;
    }
    TLMessagesChats result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetChannels()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetChannels)) {
        return;
    }
    TLMessagesChats result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetFullChannel()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetFullChannel)) {
        return;
    }
    TLMessagesChatFull result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetMessages()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetMessages)) {
        return;
    }
    TLMessagesMessages result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetParticipant()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetParticipant)) {
        return;
    }
    TLChannelsChannelParticipant result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetParticipants()
{
    if (processNotImplementedMethod(TLValue::ChannelsGetParticipants)) {
        return;
    }
    TLChannelsChannelParticipants result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runInviteToChannel()
{
    if (processNotImplementedMethod(TLValue::ChannelsInviteToChannel)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runJoinChannel()
{
    if (processNotImplementedMethod(TLValue::ChannelsJoinChannel)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runLeaveChannel()
{
    if (processNotImplementedMethod(TLValue::ChannelsLeaveChannel)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runReadHistory()
{
    if (processNotImplementedMethod(TLValue::ChannelsReadHistory)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runReadMessageContents()
{
    if (processNotImplementedMethod(TLValue::ChannelsReadMessageContents)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runReportSpam()
{
    if (processNotImplementedMethod(TLValue::ChannelsReportSpam)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runSetStickers()
{
    if (processNotImplementedMethod(TLValue::ChannelsSetStickers)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runToggleInvites()
{
    if (processNotImplementedMethod(TLValue::ChannelsToggleInvites)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runTogglePreHistoryHidden()
{
    if (processNotImplementedMethod(TLValue::ChannelsTogglePreHistoryHidden)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runToggleSignatures()
{
    if (processNotImplementedMethod(TLValue::ChannelsToggleSignatures)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runUpdatePinnedMessage()
{
    if (processNotImplementedMethod(TLValue::ChannelsUpdatePinnedMessage)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runUpdateUsername()
{
    if (processNotImplementedMethod(TLValue::ChannelsUpdateUsername)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}
// End of generated run methods

void ChannelsRpcOperation::setRunMethod(ChannelsRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

ChannelsRpcOperation::ProcessingMethod ChannelsRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::ChannelsCheckUsername:
        return &ChannelsRpcOperation::processCheckUsername;
    case TLValue::ChannelsCreateChannel:
        return &ChannelsRpcOperation::processCreateChannel;
    case TLValue::ChannelsDeleteChannel:
        return &ChannelsRpcOperation::processDeleteChannel;
    case TLValue::ChannelsDeleteHistory:
        return &ChannelsRpcOperation::processDeleteHistory;
    case TLValue::ChannelsDeleteMessages:
        return &ChannelsRpcOperation::processDeleteMessages;
    case TLValue::ChannelsDeleteUserHistory:
        return &ChannelsRpcOperation::processDeleteUserHistory;
    case TLValue::ChannelsEditAbout:
        return &ChannelsRpcOperation::processEditAbout;
    case TLValue::ChannelsEditAdmin:
        return &ChannelsRpcOperation::processEditAdmin;
    case TLValue::ChannelsEditBanned:
        return &ChannelsRpcOperation::processEditBanned;
    case TLValue::ChannelsEditPhoto:
        return &ChannelsRpcOperation::processEditPhoto;
    case TLValue::ChannelsEditTitle:
        return &ChannelsRpcOperation::processEditTitle;
    case TLValue::ChannelsExportInvite:
        return &ChannelsRpcOperation::processExportInvite;
    case TLValue::ChannelsExportMessageLink:
        return &ChannelsRpcOperation::processExportMessageLink;
    case TLValue::ChannelsGetAdminLog:
        return &ChannelsRpcOperation::processGetAdminLog;
    case TLValue::ChannelsGetAdminedPublicChannels:
        return &ChannelsRpcOperation::processGetAdminedPublicChannels;
    case TLValue::ChannelsGetChannels:
        return &ChannelsRpcOperation::processGetChannels;
    case TLValue::ChannelsGetFullChannel:
        return &ChannelsRpcOperation::processGetFullChannel;
    case TLValue::ChannelsGetMessages:
        return &ChannelsRpcOperation::processGetMessages;
    case TLValue::ChannelsGetParticipant:
        return &ChannelsRpcOperation::processGetParticipant;
    case TLValue::ChannelsGetParticipants:
        return &ChannelsRpcOperation::processGetParticipants;
    case TLValue::ChannelsInviteToChannel:
        return &ChannelsRpcOperation::processInviteToChannel;
    case TLValue::ChannelsJoinChannel:
        return &ChannelsRpcOperation::processJoinChannel;
    case TLValue::ChannelsLeaveChannel:
        return &ChannelsRpcOperation::processLeaveChannel;
    case TLValue::ChannelsReadHistory:
        return &ChannelsRpcOperation::processReadHistory;
    case TLValue::ChannelsReadMessageContents:
        return &ChannelsRpcOperation::processReadMessageContents;
    case TLValue::ChannelsReportSpam:
        return &ChannelsRpcOperation::processReportSpam;
    case TLValue::ChannelsSetStickers:
        return &ChannelsRpcOperation::processSetStickers;
    case TLValue::ChannelsToggleInvites:
        return &ChannelsRpcOperation::processToggleInvites;
    case TLValue::ChannelsTogglePreHistoryHidden:
        return &ChannelsRpcOperation::processTogglePreHistoryHidden;
    case TLValue::ChannelsToggleSignatures:
        return &ChannelsRpcOperation::processToggleSignatures;
    case TLValue::ChannelsUpdatePinnedMessage:
        return &ChannelsRpcOperation::processUpdatePinnedMessage;
    case TLValue::ChannelsUpdateUsername:
        return &ChannelsRpcOperation::processUpdateUsername;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *ChannelsOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<ChannelsRpcOperation>(layer, context);
}

} // Server

} // Telegram
