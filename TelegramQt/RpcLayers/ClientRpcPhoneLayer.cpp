/*
   Copyright (C) 2018 

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

#include "ClientRpcPhoneLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcPhoneCategory, "telegram.client.rpclayer.phone", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhoneCall *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhoneCallDiscardReason *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhoneCallProtocol *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhoneConnection *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPhonePhoneCall *output);
// End of generated Telegram API reply template specializations

PhoneRpcLayer::PhoneRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PhoneRpcLayer::PendingPhonePhoneCall *PhoneRpcLayer::acceptCall(const TLInputPhoneCall &peer, const QByteArray &gB, const TLPhoneCallProtocol &protocol)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << gB.toHex() << protocol;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneAcceptCall;
    outputStream << peer;
    outputStream << gB;
    outputStream << protocol;
    PendingPhonePhoneCall *op = new PendingPhonePhoneCall(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingPhonePhoneCall *PhoneRpcLayer::confirmCall(const TLInputPhoneCall &peer, const QByteArray &gA, quint64 keyFingerprint, const TLPhoneCallProtocol &protocol)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << gA.toHex() << keyFingerprint << protocol;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneConfirmCall;
    outputStream << peer;
    outputStream << gA;
    outputStream << keyFingerprint;
    outputStream << protocol;
    PendingPhonePhoneCall *op = new PendingPhonePhoneCall(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingUpdates *PhoneRpcLayer::discardCall(const TLInputPhoneCall &peer, quint32 duration, const TLPhoneCallDiscardReason &reason, quint64 connectionId)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << duration << reason << connectionId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneDiscardCall;
    outputStream << peer;
    outputStream << duration;
    outputStream << reason;
    outputStream << connectionId;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingDataJSON *PhoneRpcLayer::getCallConfig()
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneGetCallConfig;
    PendingDataJSON *op = new PendingDataJSON(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingBool *PhoneRpcLayer::receivedCall(const TLInputPhoneCall &peer)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneReceivedCall;
    outputStream << peer;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingPhonePhoneCall *PhoneRpcLayer::requestCall(const TLInputUser &userId, quint32 randomId, const QByteArray &gAHash, const TLPhoneCallProtocol &protocol)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << userId << randomId << gAHash.toHex() << protocol;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneRequestCall;
    outputStream << userId;
    outputStream << randomId;
    outputStream << gAHash;
    outputStream << protocol;
    PendingPhonePhoneCall *op = new PendingPhonePhoneCall(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingBool *PhoneRpcLayer::saveCallDebug(const TLInputPhoneCall &peer, const TLDataJSON &debug)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << debug;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneSaveCallDebug;
    outputStream << peer;
    outputStream << debug;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PhoneRpcLayer::PendingUpdates *PhoneRpcLayer::setCallRating(const TLInputPhoneCall &peer, quint32 rating, const QString &comment)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << rating << comment;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PhoneSetCallRating;
    outputStream << peer;
    outputStream << rating;
    outputStream << comment;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
