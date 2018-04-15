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
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class AuthRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit AuthRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *bindTempAuthKey(quint64 permAuthKeyId, quint64 nonce, quint32 expiresAt, const QByteArray &encryptedMessage);
    PendingRpcOperation *checkPassword(const QByteArray &passwordHash);
    PendingRpcOperation *checkPhone(const QString &phoneNumber);
    PendingRpcOperation *exportAuthorization(quint32 dcId);
    PendingRpcOperation *importAuthorization(quint32 id, const QByteArray &bytes);
    PendingRpcOperation *importBotAuthorization(quint32 flags, quint32 apiId, const QString &apiHash, const QString &botAuthToken);
    PendingRpcOperation *logOut();
    PendingRpcOperation *recoverPassword(const QString &code);
    PendingRpcOperation *requestPasswordRecovery();
    PendingRpcOperation *resetAuthorizations();
    PendingRpcOperation *sendCall(const QString &phoneNumber, const QString &phoneCodeHash);
    PendingRpcOperation *sendCode(const QString &phoneNumber, quint32 smsType, quint32 apiId, const QString &apiHash, const QString &langCode);
    PendingRpcOperation *sendInvites(const TLVector<QString> &phoneNumbers, const QString &message);
    PendingRpcOperation *sendSms(const QString &phoneNumber, const QString &phoneCodeHash);
    PendingRpcOperation *signIn(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode);
    PendingRpcOperation *signUp(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode, const QString &firstName, const QString &lastName);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_AUTH_LAYER_HPP
