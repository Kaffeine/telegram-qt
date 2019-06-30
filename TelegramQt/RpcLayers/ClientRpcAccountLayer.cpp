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
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcAccountCategory, "telegram.client.rpclayer.account", QtWarningMsg)

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
AccountRpcLayer::PendingUser *AccountRpcLayer::changePhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountChangePhone;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    PendingUser *op = new PendingUser(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::checkUsername(const QString &username)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << username;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountCheckUsername;
    outputStream << username;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::confirmPhone(const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << phoneCodeHash << phoneCode;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountConfirmPhone;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::deleteAccount(const QString &reason)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << reason;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountDeleteAccount;
    outputStream << reason;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountDaysTTL *AccountRpcLayer::getAccountTTL()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetAccountTTL;
    PendingAccountDaysTTL *op = new PendingAccountDaysTTL(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountAuthorizations *AccountRpcLayer::getAuthorizations()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetAuthorizations;
    PendingAccountAuthorizations *op = new PendingAccountAuthorizations(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingPeerNotifySettings *AccountRpcLayer::getNotifySettings(const TLInputNotifyPeer &peer)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << peer;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetNotifySettings;
    outputStream << peer;
    PendingPeerNotifySettings *op = new PendingPeerNotifySettings(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountPassword *AccountRpcLayer::getPassword()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetPassword;
    PendingAccountPassword *op = new PendingAccountPassword(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountPasswordSettings *AccountRpcLayer::getPasswordSettings(const QByteArray &currentPasswordHash)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << currentPasswordHash.toHex();
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetPasswordSettings;
    outputStream << currentPasswordHash;
    PendingAccountPasswordSettings *op = new PendingAccountPasswordSettings(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountPrivacyRules *AccountRpcLayer::getPrivacy(const TLInputPrivacyKey &key)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << key;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetPrivacy;
    outputStream << key;
    PendingAccountPrivacyRules *op = new PendingAccountPrivacyRules(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountTmpPassword *AccountRpcLayer::getTmpPassword(const QByteArray &passwordHash, quint32 period)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << passwordHash.toHex() << period;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetTmpPassword;
    outputStream << passwordHash;
    outputStream << period;
    PendingAccountTmpPassword *op = new PendingAccountTmpPassword(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingWallPaperVector *AccountRpcLayer::getWallPapers()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetWallPapers;
    PendingWallPaperVector *op = new PendingWallPaperVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::registerDevice(quint32 tokenType, const QString &token)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << tokenType << token;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountRegisterDevice;
    outputStream << tokenType;
    outputStream << token;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::reportPeer(const TLInputPeer &peer, const TLReportReason &reason)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << peer << reason;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountReportPeer;
    outputStream << peer;
    outputStream << reason;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::resetAuthorization(quint64 hash)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountResetAuthorization;
    outputStream << hash;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::resetNotifySettings()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountResetNotifySettings;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAuthSentCode *AccountRpcLayer::sendChangePhoneCode(quint32 flags, const QString &phoneNumber, bool currentNumber)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << phoneNumber << currentNumber;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSendChangePhoneCode;
    outputStream << flags;
    // (flags & 1 << 0) stands for allowFlashcall "true" value
    outputStream << phoneNumber;
    if (flags & 1 << 0) {
        outputStream << currentNumber;
    }
    PendingAuthSentCode *op = new PendingAuthSentCode(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAuthSentCode *AccountRpcLayer::sendConfirmPhoneCode(quint32 flags, const QString &hash, bool currentNumber)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << hash << currentNumber;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSendConfirmPhoneCode;
    outputStream << flags;
    // (flags & 1 << 0) stands for allowFlashcall "true" value
    outputStream << hash;
    if (flags & 1 << 0) {
        outputStream << currentNumber;
    }
    PendingAuthSentCode *op = new PendingAuthSentCode(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::setAccountTTL(const TLAccountDaysTTL &ttl)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << ttl;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSetAccountTTL;
    outputStream << ttl;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountPrivacyRules *AccountRpcLayer::setPrivacy(const TLInputPrivacyKey &key, const TLVector<TLInputPrivacyRule> &rules)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << key << rules;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSetPrivacy;
    outputStream << key;
    outputStream << rules;
    PendingAccountPrivacyRules *op = new PendingAccountPrivacyRules(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::unregisterDevice(quint32 tokenType, const QString &token)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << tokenType << token;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUnregisterDevice;
    outputStream << tokenType;
    outputStream << token;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::updateDeviceLocked(quint32 period)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << period;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUpdateDeviceLocked;
    outputStream << period;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::updateNotifySettings(const TLInputNotifyPeer &peer, const TLInputPeerNotifySettings &settings)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << peer << settings;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUpdateNotifySettings;
    outputStream << peer;
    outputStream << settings;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::updatePasswordSettings(const QByteArray &currentPasswordHash, const TLAccountPasswordInputSettings &newSettings)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << currentPasswordHash.toHex() << newSettings;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUpdatePasswordSettings;
    outputStream << currentPasswordHash;
    outputStream << newSettings;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingUser *AccountRpcLayer::updateProfile(quint32 flags, const QString &firstName, const QString &lastName, const QString &about)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << firstName << lastName << about;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
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
    PendingUser *op = new PendingUser(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::updateStatus(bool offline)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << offline;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUpdateStatus;
    outputStream << offline;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingUser *AccountRpcLayer::updateUsername(const QString &username)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << username;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUpdateUsername;
    outputStream << username;
    PendingUser *op = new PendingUser(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
