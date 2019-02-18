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

#ifndef TELEGRAM_CLIENT_RPC_AUTH_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_AUTH_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "PendingRpcResult.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Client {

class AuthRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit AuthRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingAuthAuthorization = PendingRpcResult<TLAuthAuthorization *>;
    using PendingAuthCheckedPhone = PendingRpcResult<TLAuthCheckedPhone *>;
    using PendingAuthExportedAuthorization = PendingRpcResult<TLAuthExportedAuthorization *>;
    using PendingAuthPasswordRecovery = PendingRpcResult<TLAuthPasswordRecovery *>;
    using PendingAuthSentCode = PendingRpcResult<TLAuthSentCode *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingBool *bindTempAuthKey(quint64 permAuthKeyId, quint64 nonce, quint32 expiresAt, const QByteArray &encryptedMessage);
    PendingBool *cancelCode(const QString &phoneNumber, const QString &phoneCodeHash);
    PendingAuthAuthorization *checkPassword(const QByteArray &passwordHash);
    PendingAuthCheckedPhone *checkPhone(const QString &phoneNumber);
    PendingBool *dropTempAuthKeys(const TLVector<quint64> &exceptAuthKeys);
    PendingAuthExportedAuthorization *exportAuthorization(quint32 dcId);
    PendingAuthAuthorization *importAuthorization(quint32 id, const QByteArray &bytes);
    PendingAuthAuthorization *importBotAuthorization(quint32 flags, quint32 apiId, const QString &apiHash, const QString &botAuthToken);
    PendingBool *logOut();
    PendingAuthAuthorization *recoverPassword(const QString &code);
    PendingAuthPasswordRecovery *requestPasswordRecovery();
    PendingAuthSentCode *resendCode(const QString &phoneNumber, const QString &phoneCodeHash);
    PendingBool *resetAuthorizations();
    PendingAuthSentCode *sendCode(quint32 flags, const QString &phoneNumber, bool currentNumber, quint32 apiId, const QString &apiHash);
    PendingBool *sendInvites(const TLVector<QString> &phoneNumbers, const QString &message);
    PendingAuthAuthorization *signIn(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    PendingAuthAuthorization *signUp(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode, const QString &firstName, const QString &lastName);
    // End of generated Telegram API declarations
    PendingAuthSentCode *sendCode(const QString &phoneNumber, quint32 apiId, const QString &apiHash);
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_AUTH_LAYER_HPP
