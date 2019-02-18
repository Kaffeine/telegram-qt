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

#include "PendingRpcResult.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class AccountRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit AccountRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingUser = PendingRpcResult<TLUser *>;
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingAccountDaysTTL = PendingRpcResult<TLAccountDaysTTL *>;
    using PendingAccountAuthorizations = PendingRpcResult<TLAccountAuthorizations *>;
    using PendingPeerNotifySettings = PendingRpcResult<TLPeerNotifySettings *>;
    using PendingAccountPassword = PendingRpcResult<TLAccountPassword *>;
    using PendingAccountPasswordSettings = PendingRpcResult<TLAccountPasswordSettings *>;
    using PendingAccountPrivacyRules = PendingRpcResult<TLAccountPrivacyRules *>;
    using PendingAccountTmpPassword = PendingRpcResult<TLAccountTmpPassword *>;
    using PendingWallPaperVector = PendingRpcResult<TLVector<TLWallPaper> *>;
    using PendingAuthSentCode = PendingRpcResult<TLAuthSentCode *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingUser *changePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    PendingBool *checkUsername(const QString &username);
    PendingBool *confirmPhone(const QString &phoneCodeHash, const QString &phoneCode);
    PendingBool *deleteAccount(const QString &reason);
    PendingAccountDaysTTL *getAccountTTL();
    PendingAccountAuthorizations *getAuthorizations();
    PendingPeerNotifySettings *getNotifySettings(const TLInputNotifyPeer &peer);
    PendingAccountPassword *getPassword();
    PendingAccountPasswordSettings *getPasswordSettings(const QByteArray &currentPasswordHash);
    PendingAccountPrivacyRules *getPrivacy(const TLInputPrivacyKey &key);
    PendingAccountTmpPassword *getTmpPassword(const QByteArray &passwordHash, quint32 period);
    PendingWallPaperVector *getWallPapers();
    PendingBool *registerDevice(quint32 tokenType, const QString &token);
    PendingBool *reportPeer(const TLInputPeer &peer, const TLReportReason &reason);
    PendingBool *resetAuthorization(quint64 hash);
    PendingBool *resetNotifySettings();
    PendingAuthSentCode *sendChangePhoneCode(quint32 flags, const QString &phoneNumber, bool currentNumber);
    PendingAuthSentCode *sendConfirmPhoneCode(quint32 flags, const QString &hash, bool currentNumber);
    PendingBool *setAccountTTL(const TLAccountDaysTTL &ttl);
    PendingAccountPrivacyRules *setPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules);
    PendingBool *unregisterDevice(quint32 tokenType, const QString &token);
    PendingBool *updateDeviceLocked(quint32 period);
    PendingBool *updateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings);
    PendingBool *updatePasswordSettings(const QByteArray &currentPasswordHash, const TLAccountPasswordInputSettings &newSettings);
    PendingUser *updateProfile(quint32 flags, const QString &firstName, const QString &lastName, const QString &about);
    PendingBool *updateStatus(bool offline);
    PendingUser *updateUsername(const QString &username);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_ACCOUNT_LAYER_HPP
