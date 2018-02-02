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

#ifndef TELEGRAM_CLIENT_RPC_ACCOUNT_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_ACCOUNT_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class AccountRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit AccountRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *changePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    PendingRpcOperation *checkUsername(const QString &username);
    PendingRpcOperation *deleteAccount(const QString &reason);
    PendingRpcOperation *getAccountTTL();
    PendingRpcOperation *getAuthorizations();
    PendingRpcOperation *getNotifySettings(const TLInputNotifyPeer &peer);
    PendingRpcOperation *getPassword();
    PendingRpcOperation *getPasswordSettings(const QByteArray &currentPasswordHash);
    PendingRpcOperation *getPrivacy(const TLInputPrivacyKey &key);
    PendingRpcOperation *getWallPapers();
    PendingRpcOperation *registerDevice(quint32 tokenType, const QString &token, const QString &deviceModel, const QString &systemVersion, const QString &appVersion, bool appSandbox, const QString &langCode);
    PendingRpcOperation *reportPeer(const TLInputPeer &peer, const TLReportReason &reason);
    PendingRpcOperation *resetAuthorization(quint64 hash);
    PendingRpcOperation *resetNotifySettings();
    PendingRpcOperation *sendChangePhoneCode(const QString &phoneNumber);
    PendingRpcOperation *setAccountTTL(const TLAccountDaysTTL &ttl);
    PendingRpcOperation *setPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules);
    PendingRpcOperation *unregisterDevice(quint32 tokenType, const QString &token);
    PendingRpcOperation *updateDeviceLocked(quint32 period);
    PendingRpcOperation *updateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings);
    PendingRpcOperation *updatePasswordSettings(const QByteArray &currentPasswordHash, const TLAccountPasswordInputSettings &newSettings);
    PendingRpcOperation *updateProfile(const QString &firstName, const QString &lastName);
    PendingRpcOperation *updateStatus(bool offline);
    PendingRpcOperation *updateUsername(const QString &username);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_ACCOUNT_LAYER_HPP
