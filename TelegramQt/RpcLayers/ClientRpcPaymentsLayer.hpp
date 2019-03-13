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

#ifndef TELEGRAM_CLIENT_RPC_PAYMENTS_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_PAYMENTS_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "PendingRpcResult.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class PaymentsRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit PaymentsRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingPaymentsPaymentForm = PendingRpcResult<TLPaymentsPaymentForm *>;
    using PendingPaymentsPaymentReceipt = PendingRpcResult<TLPaymentsPaymentReceipt *>;
    using PendingPaymentsSavedInfo = PendingRpcResult<TLPaymentsSavedInfo *>;
    using PendingPaymentsPaymentResult = PendingRpcResult<TLPaymentsPaymentResult *>;
    using PendingPaymentsValidatedRequestedInfo = PendingRpcResult<TLPaymentsValidatedRequestedInfo *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *clearSavedInfo(quint32 flags);
    PendingPaymentsPaymentForm *getPaymentForm(quint32 msgId);
    PendingPaymentsPaymentReceipt *getPaymentReceipt(quint32 msgId);
    PendingPaymentsSavedInfo *getSavedInfo();
    PendingPaymentsPaymentResult *sendPaymentForm(quint32 flags, quint32 msgId, const QString &requestedInfoId, const QString &shippingOptionId, const TLInputPaymentCredentials &credentials);
    PendingPaymentsValidatedRequestedInfo *validateRequestedInfo(quint32 flags, quint32 msgId, const TLPaymentRequestedInfo &info);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_PAYMENTS_LAYER_HPP
