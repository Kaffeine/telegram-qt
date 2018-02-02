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

#include "ClientRpcChannelsLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcChannelsCategory, "telegram.client.rpclayer.channels", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelsChannelParticipant *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLChannelsChannelParticipants *output);
// End of generated Telegram API reply template specializations

ChannelsRpcLayer::ChannelsRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *ChannelsRpcLayer::checkUsername(const TLInputChannel &channel, const QString &username)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << username;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsCheckUsername;
    outputStream << channel;
    outputStream << username;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::createChannel(quint32 flags, const QString &title, const QString &about)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << flags << title << about;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsCreateChannel;
    outputStream << flags;
    // (flags & 1 << 0) stands for broadcast "true" value
    // (flags & 1 << 1) stands for megagroup "true" value
    outputStream << title;
    outputStream << about;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::deleteChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteChannel;
    outputStream << channel;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::deleteMessages(const TLInputChannel &channel, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteMessages;
    outputStream << channel;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::deleteUserHistory(const TLInputChannel &channel, const TLInputUser &userId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsDeleteUserHistory;
    outputStream << channel;
    outputStream << userId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::editAbout(const TLInputChannel &channel, const QString &about)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << about;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsEditAbout;
    outputStream << channel;
    outputStream << about;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::editAdmin(const TLInputChannel &channel, const TLInputUser &userId, const TLChannelParticipantRole &role)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId << role;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsEditAdmin;
    outputStream << channel;
    outputStream << userId;
    outputStream << role;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::editPhoto(const TLInputChannel &channel, const TLInputChatPhoto &photo)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << photo;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsEditPhoto;
    outputStream << channel;
    outputStream << photo;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::editTitle(const TLInputChannel &channel, const QString &title)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << title;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsEditTitle;
    outputStream << channel;
    outputStream << title;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::exportInvite(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsExportInvite;
    outputStream << channel;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getChannels(const TLVector<TLInputChannel> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetChannels;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getDialogs(quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << offset << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetDialogs;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getFullChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetFullChannel;
    outputStream << channel;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getImportantHistory(const TLInputChannel &channel, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << offsetId << addOffset << limit << maxId << minId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetImportantHistory;
    outputStream << channel;
    outputStream << offsetId;
    outputStream << addOffset;
    outputStream << limit;
    outputStream << maxId;
    outputStream << minId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getMessages(const TLInputChannel &channel, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetMessages;
    outputStream << channel;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getParticipant(const TLInputChannel &channel, const TLInputUser &userId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetParticipant;
    outputStream << channel;
    outputStream << userId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::getParticipants(const TLInputChannel &channel, const TLChannelParticipantsFilter &filter, quint32 offset, quint32 limit)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << filter << offset << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsGetParticipants;
    outputStream << channel;
    outputStream << filter;
    outputStream << offset;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::inviteToChannel(const TLInputChannel &channel, const TLVector<TLInputUser> &users)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << users;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsInviteToChannel;
    outputStream << channel;
    outputStream << users;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::joinChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsJoinChannel;
    outputStream << channel;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::kickFromChannel(const TLInputChannel &channel, const TLInputUser &userId, bool kicked)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId << kicked;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsKickFromChannel;
    outputStream << channel;
    outputStream << userId;
    outputStream << kicked;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::leaveChannel(const TLInputChannel &channel)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsLeaveChannel;
    outputStream << channel;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::readHistory(const TLInputChannel &channel, quint32 maxId)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << maxId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsReadHistory;
    outputStream << channel;
    outputStream << maxId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::reportSpam(const TLInputChannel &channel, const TLInputUser &userId, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << userId << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsReportSpam;
    outputStream << channel;
    outputStream << userId;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::toggleComments(const TLInputChannel &channel, bool enabled)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << enabled;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsToggleComments;
    outputStream << channel;
    outputStream << enabled;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *ChannelsRpcLayer::updateUsername(const TLInputChannel &channel, const QString &username)
{
    qCDebug(c_clientRpcChannelsCategory) << Q_FUNC_INFO << channel << username;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::ChannelsUpdateUsername;
    outputStream << channel;
    outputStream << username;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
