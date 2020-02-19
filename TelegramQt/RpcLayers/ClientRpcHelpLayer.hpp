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

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class HelpRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit HelpRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingHelpUserInfo = PendingRpcResult<TLHelpUserInfo *>;
    using PendingUpdates = PendingRpcResult<TLUpdates *>;
    using PendingJSONValue = PendingRpcResult<TLJSONValue *>;
    using PendingHelpAppUpdate = PendingRpcResult<TLHelpAppUpdate *>;
    using PendingCdnConfig = PendingRpcResult<TLCdnConfig *>;
    using PendingConfig = PendingRpcResult<TLConfig *>;
    using PendingHelpDeepLinkInfo = PendingRpcResult<TLHelpDeepLinkInfo *>;
    using PendingHelpInviteText = PendingRpcResult<TLHelpInviteText *>;
    using PendingNearestDc = PendingRpcResult<TLNearestDc *>;
    using PendingHelpPassportConfig = PendingRpcResult<TLHelpPassportConfig *>;
    using PendingHelpProxyData = PendingRpcResult<TLHelpProxyData *>;
    using PendingHelpRecentMeUrls = PendingRpcResult<TLHelpRecentMeUrls *>;
    using PendingHelpSupport = PendingRpcResult<TLHelpSupport *>;
    using PendingHelpSupportName = PendingRpcResult<TLHelpSupportName *>;
    using PendingHelpTermsOfServiceUpdate = PendingRpcResult<TLHelpTermsOfServiceUpdate *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *acceptTermsOfService(const TLDataJSON &id);
    PendingHelpUserInfo *editUserInfo(const TLInputUser &userId, const QString &message, const TLVector<TLMessageEntity> &entities);
    PendingUpdates *getAppChangelog(const QString &prevAppVersion);
    PendingJSONValue *getAppConfig();
    PendingHelpAppUpdate *getAppUpdate(const QString &source);
    PendingCdnConfig *getCdnConfig();
    PendingConfig *getConfig();
    PendingHelpDeepLinkInfo *getDeepLinkInfo(const QString &path);
    PendingHelpInviteText *getInviteText();
    PendingNearestDc *getNearestDc();
    PendingHelpPassportConfig *getPassportConfig(quint32 hash);
    PendingHelpProxyData *getProxyData();
    PendingHelpRecentMeUrls *getRecentMeUrls(const QString &referer);
    PendingHelpSupport *getSupport();
    PendingHelpSupportName *getSupportName();
    PendingHelpTermsOfServiceUpdate *getTermsOfServiceUpdate();
    PendingHelpUserInfo *getUserInfo(const TLInputUser &userId);
    PendingBool *saveAppLog(const TLVector<TLInputAppEvent> &events);
    PendingBool *setBotUpdatesStatus(quint32 pendingUpdatesCount, const QString &message);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_HELP_LAYER_HPP
