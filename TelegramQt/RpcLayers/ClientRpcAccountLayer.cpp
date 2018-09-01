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

#include "ClientRpcAccountLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcAccountCategory, "telegram.client.rpclayer.account", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountAuthorizations *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountDaysTTL *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPassword *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPasswordInputSettings *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPasswordSettings *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPrivacyRules *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountTmpPassword *output);
// End of generated Telegram API reply template specializations

AccountRpcLayer::AccountRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *AccountRpcLayer::changePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountChangePhone;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::checkUsername(const QString &username)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << username;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountCheckUsername;
    outputStream << username;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::confirmPhone(const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << phoneCodeHash << phoneCode;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountConfirmPhone;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::deleteAccount(const QString &reason)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << reason;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountDeleteAccount;
    outputStream << reason;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getAccountTTL()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetAccountTTL;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getAuthorizations()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetAuthorizations;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getNotifySettings(const TLInputNotifyPeer &peer)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetNotifySettings;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getPassword()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetPassword;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getPasswordSettings(const QByteArray &currentPasswordHash)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << currentPasswordHash.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetPasswordSettings;
    outputStream << currentPasswordHash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getPrivacy(const TLInputPrivacyKey &key)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << key;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetPrivacy;
    outputStream << key;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getTmpPassword(const QByteArray &passwordHash, quint32 period)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << passwordHash.toHex() << period;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetTmpPassword;
    outputStream << passwordHash;
    outputStream << period;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::getWallPapers()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountGetWallPapers;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::registerDevice(quint32 tokenType, const QString &token)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << tokenType << token;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountRegisterDevice;
    outputStream << tokenType;
    outputStream << token;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::reportPeer(const TLInputPeer &peer, const TLReportReason &reason)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << peer << reason;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountReportPeer;
    outputStream << peer;
    outputStream << reason;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::resetAuthorization(quint64 hash)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountResetAuthorization;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::resetNotifySettings()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountResetNotifySettings;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::sendChangePhoneCode(quint32 flags, const QString &phoneNumber, bool currentNumber)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << phoneNumber << currentNumber;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountSendChangePhoneCode;
    outputStream << flags;
    // (flags & 1 << 0) stands for allowFlashcall "true" value
    outputStream << phoneNumber;
    if (flags & 1 << 0) {
        outputStream << currentNumber;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::sendConfirmPhoneCode(quint32 flags, const QString &hash, bool currentNumber)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << hash << currentNumber;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountSendConfirmPhoneCode;
    outputStream << flags;
    // (flags & 1 << 0) stands for allowFlashcall "true" value
    outputStream << hash;
    if (flags & 1 << 0) {
        outputStream << currentNumber;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::setAccountTTL(const TLAccountDaysTTL &ttl)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << ttl;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountSetAccountTTL;
    outputStream << ttl;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::setPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << key << rules;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountSetPrivacy;
    outputStream << key;
    outputStream << rules;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::unregisterDevice(quint32 tokenType, const QString &token)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << tokenType << token;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUnregisterDevice;
    outputStream << tokenType;
    outputStream << token;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::updateDeviceLocked(quint32 period)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << period;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUpdateDeviceLocked;
    outputStream << period;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::updateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << peer << settings;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUpdateNotifySettings;
    outputStream << peer;
    outputStream << settings;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::updatePasswordSettings(const QByteArray &currentPasswordHash, const TLAccountPasswordInputSettings &newSettings)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << currentPasswordHash.toHex() << newSettings;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUpdatePasswordSettings;
    outputStream << currentPasswordHash;
    outputStream << newSettings;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::updateProfile(quint32 flags, const QString &firstName, const QString &lastName, const QString &about)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << firstName << lastName << about;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUpdateProfile;
    outputStream << flags;
    if (flags & 1 << 0) {
        outputStream << firstName;
    }
    if (flags & 1 << 1) {
        outputStream << lastName;
    }
    if (flags & 1 << 2) {
        outputStream << about;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::updateStatus(bool offline)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << offline;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUpdateStatus;
    outputStream << offline;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *AccountRpcLayer::updateUsername(const QString &username)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << username;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::AccountUpdateUsername;
    outputStream << username;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
