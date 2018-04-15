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
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthExportedAuthorization *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthPasswordRecovery *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthSentCode *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthorization *output);
// End of generated Telegram API reply template specializations

AuthRpcLayer::AuthRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *AuthRpcLayer::bindTempAuthKey(quint64 permAuthKeyId, quint64 nonce, quint32 expiresAt, const QByteArray &encryptedMessage)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << permAuthKeyId << nonce << expiresAt << encryptedMessage.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthBindTempAuthKey;
    outputStream << permAuthKeyId;
    outputStream << nonce;
    outputStream << expiresAt;
    outputStream << encryptedMessage;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::checkPassword(const QByteArray &passwordHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << passwordHash.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthCheckPassword;
    outputStream << passwordHash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::checkPhone(const QString &phoneNumber)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthCheckPhone;
    outputStream << phoneNumber;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::exportAuthorization(quint32 dcId)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << dcId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthExportAuthorization;
    outputStream << dcId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::importAuthorization(quint32 id, const QByteArray &bytes)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << id << bytes.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthImportAuthorization;
    outputStream << id;
    outputStream << bytes;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::importBotAuthorization(quint32 flags, quint32 apiId, const QString &apiHash, const QString &botAuthToken)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << flags << apiId << apiHash << botAuthToken;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthImportBotAuthorization;
    outputStream << flags;
    outputStream << apiId;
    outputStream << apiHash;
    outputStream << botAuthToken;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::logOut()
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthLogOut;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::recoverPassword(const QString &code)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << code;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthRecoverPassword;
    outputStream << code;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::requestPasswordRecovery()
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthRequestPasswordRecovery;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::resetAuthorizations()
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthResetAuthorizations;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::sendCall(const QString &phoneNumber, const QString &phoneCodeHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSendCall;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::sendCode(const QString &phoneNumber, quint32 smsType, quint32 apiId, const QString &apiHash, const QString &langCode)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << smsType << apiId << apiHash << langCode;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSendCode;
    outputStream << phoneNumber;
    outputStream << smsType;
    outputStream << apiId;
    outputStream << apiHash;
    outputStream << langCode;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::sendInvites(const TLVector<QString> &phoneNumbers, const QString &message)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumbers << message;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSendInvites;
    outputStream << phoneNumbers;
    outputStream << message;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::sendSms(const QString &phoneNumber, const QString &phoneCodeHash)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSendSms;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::signIn(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSignIn;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AuthRpcLayer::signUp(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode, const QString &firstName, const QString &lastName)
{
    qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode << firstName << lastName;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AuthSignUp;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    outputStream << firstName;
    outputStream << lastName;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
