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

#include "ClientRpcPaymentsLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcPaymentsCategory, "telegram.client.rpclayer.payments", QtWarningMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentCharge *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentRequestedInfo *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentSavedCredentials *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentsPaymentForm *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentsPaymentReceipt *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentsPaymentResult *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentsSavedInfo *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLPaymentsValidatedRequestedInfo *output);
// End of generated Telegram API reply template specializations

PaymentsRpcLayer::PaymentsRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PaymentsRpcLayer::PendingBool *PaymentsRpcLayer::clearSavedInfo(quint32 flags)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << flags;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PaymentsClearSavedInfo;
    outputStream << flags;
    // (flags & 1 << 0) stands for credentials "true" value
    // (flags & 1 << 1) stands for info "true" value
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PaymentsRpcLayer::PendingPaymentsPaymentForm *PaymentsRpcLayer::getPaymentForm(quint32 msgId)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << msgId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PaymentsGetPaymentForm;
    outputStream << msgId;
    PendingPaymentsPaymentForm *op = new PendingPaymentsPaymentForm(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PaymentsRpcLayer::PendingPaymentsPaymentReceipt *PaymentsRpcLayer::getPaymentReceipt(quint32 msgId)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << msgId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PaymentsGetPaymentReceipt;
    outputStream << msgId;
    PendingPaymentsPaymentReceipt *op = new PendingPaymentsPaymentReceipt(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PaymentsRpcLayer::PendingPaymentsSavedInfo *PaymentsRpcLayer::getSavedInfo()
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PaymentsGetSavedInfo;
    PendingPaymentsSavedInfo *op = new PendingPaymentsSavedInfo(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PaymentsRpcLayer::PendingPaymentsPaymentResult *PaymentsRpcLayer::sendPaymentForm(quint32 flags, quint32 msgId, const QString &requestedInfoId, const QString &shippingOptionId, const TLInputPaymentCredentials &credentials)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << flags << msgId << requestedInfoId << shippingOptionId << credentials;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PaymentsSendPaymentForm;
    outputStream << flags;
    outputStream << msgId;
    if (flags & 1 << 0) {
        outputStream << requestedInfoId;
    }
    if (flags & 1 << 1) {
        outputStream << shippingOptionId;
    }
    outputStream << credentials;
    PendingPaymentsPaymentResult *op = new PendingPaymentsPaymentResult(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

PaymentsRpcLayer::PendingPaymentsValidatedRequestedInfo *PaymentsRpcLayer::validateRequestedInfo(quint32 flags, quint32 msgId, const TLPaymentRequestedInfo &info)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << flags << msgId << info;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::PaymentsValidateRequestedInfo;
    outputStream << flags;
    // (flags & 1 << 0) stands for save "true" value
    outputStream << msgId;
    outputStream << info;
    PendingPaymentsValidatedRequestedInfo *op = new PendingPaymentsValidatedRequestedInfo(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
