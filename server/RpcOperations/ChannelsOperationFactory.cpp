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

bool ChannelsRpcOperation::processGetChannels(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetChannels);
    context.inputStream() >> m_getChannels;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetDialogs(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetDialogs);
    context.inputStream() >> m_getDialogs;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetFullChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetFullChannel);
    context.inputStream() >> m_getFullChannel;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processGetImportantHistory(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runGetImportantHistory);
    context.inputStream() >> m_getImportantHistory;
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

bool ChannelsRpcOperation::processKickFromChannel(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runKickFromChannel);
    context.inputStream() >> m_kickFromChannel;
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

bool ChannelsRpcOperation::processReportSpam(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runReportSpam);
    context.inputStream() >> m_reportSpam;
    return !context.inputStream().error();
}

bool ChannelsRpcOperation::processToggleComments(RpcProcessingContext &context)
{
    setRunMethod(&ChannelsRpcOperation::runToggleComments);
    context.inputStream() >> m_toggleComments;
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
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runCreateChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteMessages()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesAffectedMessages result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runDeleteUserHistory()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesAffectedHistory result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditAbout()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditAdmin()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditPhoto()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runEditTitle()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runExportInvite()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLExportedChatInvite result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetChannels()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesChats result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetDialogs()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesDialogs result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetFullChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesChatFull result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetImportantHistory()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesMessages result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetMessages()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLMessagesMessages result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetParticipant()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLChannelsChannelParticipant result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runGetParticipants()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLChannelsChannelParticipants result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runInviteToChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runJoinChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runKickFromChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runLeaveChannel()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runReadHistory()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runReportSpam()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runToggleComments()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUpdates result;
    sendRpcReply(result);
}

void ChannelsRpcOperation::runUpdateUsername()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
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
    case TLValue::ChannelsDeleteMessages:
        return &ChannelsRpcOperation::processDeleteMessages;
    case TLValue::ChannelsDeleteUserHistory:
        return &ChannelsRpcOperation::processDeleteUserHistory;
    case TLValue::ChannelsEditAbout:
        return &ChannelsRpcOperation::processEditAbout;
    case TLValue::ChannelsEditAdmin:
        return &ChannelsRpcOperation::processEditAdmin;
    case TLValue::ChannelsEditPhoto:
        return &ChannelsRpcOperation::processEditPhoto;
    case TLValue::ChannelsEditTitle:
        return &ChannelsRpcOperation::processEditTitle;
    case TLValue::ChannelsExportInvite:
        return &ChannelsRpcOperation::processExportInvite;
    case TLValue::ChannelsGetChannels:
        return &ChannelsRpcOperation::processGetChannels;
    case TLValue::ChannelsGetDialogs:
        return &ChannelsRpcOperation::processGetDialogs;
    case TLValue::ChannelsGetFullChannel:
        return &ChannelsRpcOperation::processGetFullChannel;
    case TLValue::ChannelsGetImportantHistory:
        return &ChannelsRpcOperation::processGetImportantHistory;
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
    case TLValue::ChannelsKickFromChannel:
        return &ChannelsRpcOperation::processKickFromChannel;
    case TLValue::ChannelsLeaveChannel:
        return &ChannelsRpcOperation::processLeaveChannel;
    case TLValue::ChannelsReadHistory:
        return &ChannelsRpcOperation::processReadHistory;
    case TLValue::ChannelsReportSpam:
        return &ChannelsRpcOperation::processReportSpam;
    case TLValue::ChannelsToggleComments:
        return &ChannelsRpcOperation::processToggleComments;
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
