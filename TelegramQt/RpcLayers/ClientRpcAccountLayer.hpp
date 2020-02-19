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

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class AccountRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit AccountRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingUser = PendingRpcResult<TLUser *>;
    using PendingAccountDaysTTL = PendingRpcResult<TLAccountDaysTTL *>;
    using PendingSecureValueVector = PendingRpcResult<TLVector<TLSecureValue> *>;
    using PendingAccountAuthorizationForm = PendingRpcResult<TLAccountAuthorizationForm *>;
    using PendingAccountAuthorizations = PendingRpcResult<TLAccountAuthorizations *>;
    using PendingUpdates = PendingRpcResult<TLUpdates *>;
    using PendingPeerNotifySettings = PendingRpcResult<TLPeerNotifySettings *>;
    using PendingAccountPassword = PendingRpcResult<TLAccountPassword *>;
    using PendingAccountPasswordSettings = PendingRpcResult<TLAccountPasswordSettings *>;
    using PendingAccountPrivacyRules = PendingRpcResult<TLAccountPrivacyRules *>;
    using PendingAccountTmpPassword = PendingRpcResult<TLAccountTmpPassword *>;
    using PendingWallPaperVector = PendingRpcResult<TLVector<TLWallPaper> *>;
    using PendingAccountWebAuthorizations = PendingRpcResult<TLAccountWebAuthorizations *>;
    using PendingAccountTakeout = PendingRpcResult<TLAccountTakeout *>;
    using PendingSecureValue = PendingRpcResult<TLSecureValue *>;
    using PendingAuthSentCode = PendingRpcResult<TLAuthSentCode *>;
    using PendingAccountSentEmailCode = PendingRpcResult<TLAccountSentEmailCode *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *acceptAuthorization(quint32 botId, const QString &scope, const QString &publicKey, const TLVector<TLSecureValueHash> &valueHashes, const TLSecureCredentialsEncrypted &credentials);
    PendingBool *cancelPasswordEmail();
    PendingUser *changePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    PendingBool *checkUsername(const QString &username);
    PendingBool *confirmPasswordEmail(const QString &code);
    PendingBool *confirmPhone(const QString &phoneCodeHash, const QString &phoneCode);
    PendingBool *deleteAccount(const QString &reason);
    PendingBool *deleteSecureValue(const TLVector<TLSecureValueType> &types);
    PendingBool *finishTakeoutSession(quint32 flags);
    PendingAccountDaysTTL *getAccountTTL();
    PendingSecureValueVector *getAllSecureValues();
    PendingAccountAuthorizationForm *getAuthorizationForm(quint32 botId, const QString &scope, const QString &publicKey);
    PendingAccountAuthorizations *getAuthorizations();
    PendingBool *getContactSignUpNotification();
    PendingUpdates *getNotifyExceptions(quint32 flags, const TLInputNotifyPeer &peer);
    PendingPeerNotifySettings *getNotifySettings(const TLInputNotifyPeer &peer);
    PendingAccountPassword *getPassword();
    PendingAccountPasswordSettings *getPasswordSettings(const TLInputCheckPasswordSRP &password);
    PendingAccountPrivacyRules *getPrivacy(const TLInputPrivacyKey &key);
    PendingSecureValueVector *getSecureValue(const TLVector<TLSecureValueType> &types);
    PendingAccountTmpPassword *getTmpPassword(const TLInputCheckPasswordSRP &password, quint32 period);
    PendingWallPaperVector *getWallPapers();
    PendingAccountWebAuthorizations *getWebAuthorizations();
    PendingAccountTakeout *initTakeoutSession(quint32 flags, quint32 fileMaxSize);
    PendingBool *registerDevice(quint32 tokenType, const QString &token, bool appSandbox, const QByteArray &secret, const TLVector<quint32> &otherUids);
    PendingBool *reportPeer(const TLInputPeer &peer, const TLReportReason &reason);
    PendingBool *resendPasswordEmail();
    PendingBool *resetAuthorization(quint64 hash);
    PendingBool *resetNotifySettings();
    PendingBool *resetWebAuthorization(quint64 hash);
    PendingBool *resetWebAuthorizations();
    PendingSecureValue *saveSecureValue(const TLInputSecureValue &value, quint64 secureSecretId);
    PendingAuthSentCode *sendChangePhoneCode(quint32 flags, const QString &phoneNumber, bool currentNumber);
    PendingAuthSentCode *sendConfirmPhoneCode(quint32 flags, const QString &hash, bool currentNumber);
    PendingAccountSentEmailCode *sendVerifyEmailCode(const QString &email);
    PendingAuthSentCode *sendVerifyPhoneCode(quint32 flags, const QString &phoneNumber, bool currentNumber);
    PendingBool *setAccountTTL(const TLAccountDaysTTL &ttl);
    PendingBool *setContactSignUpNotification(bool silent);
    PendingAccountPrivacyRules *setPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules);
    PendingBool *unregisterDevice(quint32 tokenType, const QString &token, const TLVector<quint32> &otherUids);
    PendingBool *updateDeviceLocked(quint32 period);
    PendingBool *updateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings);
    PendingBool *updatePasswordSettings(const TLInputCheckPasswordSRP &password, const TLAccountPasswordInputSettings &newSettings);
    PendingUser *updateProfile(quint32 flags, const QString &firstName, const QString &lastName, const QString &about);
    PendingBool *updateStatus(bool offline);
    PendingUser *updateUsername(const QString &username);
    PendingBool *verifyEmail(const QString &email, const QString &code);
    PendingBool *verifyPhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_ACCOUNT_LAYER_HPP
