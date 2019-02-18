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

#ifndef TELEGRAM_CLIENT_RPC_HELP_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_HELP_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "PendingRpcResult.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class HelpRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit HelpRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingUpdates = PendingRpcResult<TLUpdates *>;
    using PendingHelpAppUpdate = PendingRpcResult<TLHelpAppUpdate *>;
    using PendingCdnConfig = PendingRpcResult<TLCdnConfig *>;
    using PendingConfig = PendingRpcResult<TLConfig *>;
    using PendingHelpInviteText = PendingRpcResult<TLHelpInviteText *>;
    using PendingNearestDc = PendingRpcResult<TLNearestDc *>;
    using PendingHelpRecentMeUrls = PendingRpcResult<TLHelpRecentMeUrls *>;
    using PendingHelpSupport = PendingRpcResult<TLHelpSupport *>;
    using PendingHelpTermsOfService = PendingRpcResult<TLHelpTermsOfService *>;
    using PendingBool = PendingRpcResult<TLBool *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingUpdates *getAppChangelog(const QString &prevAppVersion);
    PendingHelpAppUpdate *getAppUpdate();
    PendingCdnConfig *getCdnConfig();
    PendingConfig *getConfig();
    PendingHelpInviteText *getInviteText();
    PendingNearestDc *getNearestDc();
    PendingHelpRecentMeUrls *getRecentMeUrls(const QString &referer);
    PendingHelpSupport *getSupport();
    PendingHelpTermsOfService *getTermsOfService();
    PendingBool *saveAppLog(const TLVector<TLInputAppEvent> &events);
    PendingBool *setBotUpdatesStatus(quint32 pendingUpdatesCount, const QString &message);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_HELP_LAYER_HPP
