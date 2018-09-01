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
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcPaymentsCategory, "telegram.client.rpclayer.payments", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
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
PendingRpcOperation *PaymentsRpcLayer::clearSavedInfo(quint32 flags)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << flags;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PaymentsClearSavedInfo;
    outputStream << flags;
    // (flags & 1 << 0) stands for credentials "true" value
    // (flags & 1 << 1) stands for info "true" value
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PaymentsRpcLayer::getPaymentForm(quint32 msgId)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << msgId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PaymentsGetPaymentForm;
    outputStream << msgId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PaymentsRpcLayer::getPaymentReceipt(quint32 msgId)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << msgId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PaymentsGetPaymentReceipt;
    outputStream << msgId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PaymentsRpcLayer::getSavedInfo()
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PaymentsGetSavedInfo;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PaymentsRpcLayer::sendPaymentForm(quint32 flags, quint32 msgId, const QString &requestedInfoId, const QString &shippingOptionId, const TLInputPaymentCredentials &credentials)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << flags << msgId << requestedInfoId << shippingOptionId << credentials;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
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
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *PaymentsRpcLayer::validateRequestedInfo(quint32 flags, quint32 msgId, const TLPaymentRequestedInfo &info)
{
    qCDebug(c_clientRpcPaymentsCategory) << Q_FUNC_INFO << flags << msgId << info;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::PaymentsValidateRequestedInfo;
    outputStream << flags;
    // (flags & 1 << 0) stands for save "true" value
    outputStream << msgId;
    outputStream << info;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
