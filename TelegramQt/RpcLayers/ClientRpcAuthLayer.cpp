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

#include "ClientRpcAuthLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcAuthCategory, "telegram.client.rpclayer.auth", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthAuthorization *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthCheckedPhone *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthCodeType *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthExportedAuthorization *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthPasswordRecovery *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthSentCode *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthSentCodeType *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthorization *output);
// End of generated Telegram API reply template specializations

AuthRpcLayer::AuthRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
AuthRpcLayer::PendingBool *AuthRpcLayer::bindTempAuthKey(quint64 permAuthKeyId, quint64 nonce, quint32 expiresAt, const QByteArray &encryptedMessage)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << permAuthKeyId << nonce << expiresAt << encryptedMessage.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthBindTempAuthKey;
    outputStream << permAuthKeyId;
    outputStream << nonce;
    outputStream << expiresAt;
    outputStream << encryptedMessage;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingBool *AuthRpcLayer::cancelCode(const QString &phoneNumber, const QString &phoneCodeHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthCancelCode;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthAuthorization *AuthRpcLayer::checkPassword(const QByteArray &passwordHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << passwordHash.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthCheckPassword;
    outputStream << passwordHash;
    PendingAuthAuthorization *op = new PendingAuthAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthCheckedPhone *AuthRpcLayer::checkPhone(const QString &phoneNumber)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthCheckPhone;
    outputStream << phoneNumber;
    PendingAuthCheckedPhone *op = new PendingAuthCheckedPhone(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingBool *AuthRpcLayer::dropTempAuthKeys(const TLVector<quint64> &exceptAuthKeys)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << exceptAuthKeys;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthDropTempAuthKeys;
    outputStream << exceptAuthKeys;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthExportedAuthorization *AuthRpcLayer::exportAuthorization(quint32 dcId)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << dcId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthExportAuthorization;
    outputStream << dcId;
    PendingAuthExportedAuthorization *op = new PendingAuthExportedAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthAuthorization *AuthRpcLayer::importAuthorization(quint32 id, const QByteArray &bytes)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << id << bytes.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthImportAuthorization;
    outputStream << id;
    outputStream << bytes;
    PendingAuthAuthorization *op = new PendingAuthAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthAuthorization *AuthRpcLayer::importBotAuthorization(quint32 flags, quint32 apiId, const QString &apiHash, const QString &botAuthToken)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << flags << apiId << apiHash << botAuthToken;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthImportBotAuthorization;
    outputStream << flags;
    outputStream << apiId;
    outputStream << apiHash;
    outputStream << botAuthToken;
    PendingAuthAuthorization *op = new PendingAuthAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingBool *AuthRpcLayer::logOut()
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthLogOut;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthAuthorization *AuthRpcLayer::recoverPassword(const QString &code)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << code;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthRecoverPassword;
    outputStream << code;
    PendingAuthAuthorization *op = new PendingAuthAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthPasswordRecovery *AuthRpcLayer::requestPasswordRecovery()
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthRequestPasswordRecovery;
    PendingAuthPasswordRecovery *op = new PendingAuthPasswordRecovery(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthSentCode *AuthRpcLayer::resendCode(const QString &phoneNumber, const QString &phoneCodeHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthResendCode;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    PendingAuthSentCode *op = new PendingAuthSentCode(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingBool *AuthRpcLayer::resetAuthorizations()
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthResetAuthorizations;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthSentCode *AuthRpcLayer::sendCode(quint32 flags, const QString &phoneNumber, bool currentNumber, quint32 apiId, const QString &apiHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << flags << phoneNumber << currentNumber << apiId << apiHash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSendCode;
    outputStream << flags;
    // (flags & 1 << 0) stands for allowFlashcall "true" value
    outputStream << phoneNumber;
    if (flags & 1 << 0) {
        outputStream << currentNumber;
    }
    outputStream << apiId;
    outputStream << apiHash;
    PendingAuthSentCode *op = new PendingAuthSentCode(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingBool *AuthRpcLayer::sendInvites(const TLVector<QString> &phoneNumbers, const QString &message)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumbers << message;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSendInvites;
    outputStream << phoneNumbers;
    outputStream << message;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthAuthorization *AuthRpcLayer::signIn(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSignIn;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    PendingAuthAuthorization *op = new PendingAuthAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AuthRpcLayer::PendingAuthAuthorization *AuthRpcLayer::signUp(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode, const QString &firstName, const QString &lastName)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode << firstName << lastName;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSignUp;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    outputStream << firstName;
    outputStream << lastName;
    PendingAuthAuthorization *op = new PendingAuthAuthorization(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

AuthRpcLayer::PendingAuthSentCode *AuthRpcLayer::sendCode(const QString &phoneNumber, quint32 apiId, const QString &apiHash)
{
    return sendCode(0, phoneNumber, false, apiId, apiHash);
}

} // Client namespace

} // Telegram namespace
