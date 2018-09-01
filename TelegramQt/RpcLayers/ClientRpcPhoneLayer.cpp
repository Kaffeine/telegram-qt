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
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcPhoneCategory, "telegram.client.rpclayer.phone", QtDebugMsg)

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
PendingRpcOperation *PhoneRpcLayer::acceptCall(const TLInputPhoneCall &peer, const QByteArray &gB, const TLPhoneCallProtocol &protocol)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << gB.toHex() << protocol;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneAcceptCall;
    outputStream << peer;
    outputStream << gB;
    outputStream << protocol;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::confirmCall(const TLInputPhoneCall &peer, const QByteArray &gA, quint64 keyFingerprint, const TLPhoneCallProtocol &protocol)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << gA.toHex() << keyFingerprint << protocol;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneConfirmCall;
    outputStream << peer;
    outputStream << gA;
    outputStream << keyFingerprint;
    outputStream << protocol;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::discardCall(const TLInputPhoneCall &peer, quint32 duration, const TLPhoneCallDiscardReason &reason, quint64 connectionId)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << duration << reason << connectionId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneDiscardCall;
    outputStream << peer;
    outputStream << duration;
    outputStream << reason;
    outputStream << connectionId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::getCallConfig()
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneGetCallConfig;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::receivedCall(const TLInputPhoneCall &peer)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneReceivedCall;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::requestCall(const TLInputUser &userId, quint32 randomId, const QByteArray &gAHash, const TLPhoneCallProtocol &protocol)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << userId << randomId << gAHash.toHex() << protocol;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneRequestCall;
    outputStream << userId;
    outputStream << randomId;
    outputStream << gAHash;
    outputStream << protocol;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::saveCallDebug(const TLInputPhoneCall &peer, const TLDataJSON &debug)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << debug;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneSaveCallDebug;
    outputStream << peer;
    outputStream << debug;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PhoneRpcLayer::setCallRating(const TLInputPhoneCall &peer, quint32 rating, const QString &comment)
{
    qCDebug(c_clientRpcPhoneCategory) << Q_FUNC_INFO << peer << rating << comment;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PhoneSetCallRating;
    outputStream << peer;
    outputStream << rating;
    outputStream << comment;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
