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
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountAuthorizationForm *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountAuthorizations *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountDaysTTL *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPassword *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPasswordInputSettings *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPasswordSettings *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPrivacyRules *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountSentEmailCode *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountTakeout *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountTmpPassword *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountWebAuthorizations *output);
// End of generated Telegram API reply template specializations

AccountRpcLayer::AccountRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
AccountRpcLayer::PendingBool *AccountRpcLayer::acceptAuthorization(quint32 botId, const QString &scope, const QString &publicKey, const TLVector<TLSecureValueHash> &valueHashes, const TLSecureCredentialsEncrypted &credentials)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << botId << scope << publicKey << valueHashes << credentials;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountAcceptAuthorization;
    outputStream << botId;
    outputStream << scope;
    outputStream << publicKey;
    outputStream << valueHashes;
    outputStream << credentials;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::cancelPasswordEmail()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountCancelPasswordEmail;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

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

AccountRpcLayer::PendingBool *AccountRpcLayer::confirmPasswordEmail(const QString &code)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << code;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountConfirmPasswordEmail;
    outputStream << code;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::deleteSecureValue(const TLVector<TLSecureValueType> &types)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << types;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountDeleteSecureValue;
    outputStream << types;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::finishTakeoutSession(quint32 flags)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountFinishTakeoutSession;
    outputStream << flags;
    // (flags & 1 << 0) stands for success "true" value
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

AccountRpcLayer::PendingSecureValueVector *AccountRpcLayer::getAllSecureValues()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetAllSecureValues;
    PendingSecureValueVector *op = new PendingSecureValueVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountAuthorizationForm *AccountRpcLayer::getAuthorizationForm(quint32 botId, const QString &scope, const QString &publicKey)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << botId << scope << publicKey;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetAuthorizationForm;
    outputStream << botId;
    outputStream << scope;
    outputStream << publicKey;
    PendingAccountAuthorizationForm *op = new PendingAccountAuthorizationForm(this, outputStream.getData());
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

AccountRpcLayer::PendingBool *AccountRpcLayer::getContactSignUpNotification()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetContactSignUpNotification;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingUpdates *AccountRpcLayer::getNotifyExceptions(quint32 flags, const TLInputNotifyPeer &peer)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << peer;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetNotifyExceptions;
    outputStream << flags;
    // (flags & 1 << 1) stands for compareSound "true" value
    if (flags & 1 << 0) {
        outputStream << peer;
    }
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
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

AccountRpcLayer::PendingAccountPasswordSettings *AccountRpcLayer::getPasswordSettings(const TLInputCheckPasswordSRP &password)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << password;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetPasswordSettings;
    outputStream << password;
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

AccountRpcLayer::PendingSecureValueVector *AccountRpcLayer::getSecureValue(const TLVector<TLSecureValueType> &types)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << types;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetSecureValue;
    outputStream << types;
    PendingSecureValueVector *op = new PendingSecureValueVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountTmpPassword *AccountRpcLayer::getTmpPassword(const TLInputCheckPasswordSRP &password, quint32 period)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << password << period;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetTmpPassword;
    outputStream << password;
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

AccountRpcLayer::PendingAccountWebAuthorizations *AccountRpcLayer::getWebAuthorizations()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountGetWebAuthorizations;
    PendingAccountWebAuthorizations *op = new PendingAccountWebAuthorizations(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAccountTakeout *AccountRpcLayer::initTakeoutSession(quint32 flags, quint32 fileMaxSize)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << fileMaxSize;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountInitTakeoutSession;
    outputStream << flags;
    // (flags & 1 << 0) stands for contacts "true" value
    // (flags & 1 << 1) stands for messageUsers "true" value
    // (flags & 1 << 2) stands for messageChats "true" value
    // (flags & 1 << 3) stands for messageMegagroups "true" value
    // (flags & 1 << 4) stands for messageChannels "true" value
    // (flags & 1 << 5) stands for files "true" value
    if (flags & 1 << 5) {
        outputStream << fileMaxSize;
    }
    PendingAccountTakeout *op = new PendingAccountTakeout(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::registerDevice(quint32 tokenType, const QString &token, bool appSandbox, const QByteArray &secret, const TLVector<quint32> &otherUids)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << tokenType << token << appSandbox << secret.toHex() << otherUids;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountRegisterDevice;
    outputStream << tokenType;
    outputStream << token;
    outputStream << appSandbox;
    outputStream << secret;
    outputStream << otherUids;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::resendPasswordEmail()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountResendPasswordEmail;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::resetWebAuthorization(quint64 hash)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountResetWebAuthorization;
    outputStream << hash;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::resetWebAuthorizations()
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountResetWebAuthorizations;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingSecureValue *AccountRpcLayer::saveSecureValue(const TLInputSecureValue &value, quint64 secureSecretId)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << value << secureSecretId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSaveSecureValue;
    outputStream << value;
    outputStream << secureSecretId;
    PendingSecureValue *op = new PendingSecureValue(this, outputStream.getData());
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

AccountRpcLayer::PendingAccountSentEmailCode *AccountRpcLayer::sendVerifyEmailCode(const QString &email)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << email;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSendVerifyEmailCode;
    outputStream << email;
    PendingAccountSentEmailCode *op = new PendingAccountSentEmailCode(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingAuthSentCode *AccountRpcLayer::sendVerifyPhoneCode(quint32 flags, const QString &phoneNumber, bool currentNumber)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << flags << phoneNumber << currentNumber;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSendVerifyPhoneCode;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::setContactSignUpNotification(bool silent)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << silent;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountSetContactSignUpNotification;
    outputStream << silent;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::unregisterDevice(quint32 tokenType, const QString &token, const TLVector<quint32> &otherUids)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << tokenType << token << otherUids;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUnregisterDevice;
    outputStream << tokenType;
    outputStream << token;
    outputStream << otherUids;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::updatePasswordSettings(const TLInputCheckPasswordSRP &password, const TLAccountPasswordInputSettings &newSettings)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << password << newSettings;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountUpdatePasswordSettings;
    outputStream << password;
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

AccountRpcLayer::PendingBool *AccountRpcLayer::verifyEmail(const QString &email, const QString &code)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << email << code;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountVerifyEmail;
    outputStream << email;
    outputStream << code;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

AccountRpcLayer::PendingBool *AccountRpcLayer::verifyPhone(const QString &phoneNumber, const QString &phoneCodeHash, const QString &phoneCode)
{
    qCDebug(c_clientRpcAccountCategory) << Q_FUNC_INFO << phoneNumber << phoneCodeHash << phoneCode;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::AccountVerifyPhone;
    outputStream << phoneNumber;
    outputStream << phoneCodeHash;
    outputStream << phoneCode;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
