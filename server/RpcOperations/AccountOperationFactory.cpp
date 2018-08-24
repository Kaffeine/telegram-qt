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

#include "AccountOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"
#include "Utils.hpp"

#include "CTelegramStreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool AccountRpcOperation::processChangePhone(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runChangePhone);
    context.inputStream() >> m_changePhone;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processCheckUsername(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runCheckUsername);
    context.inputStream() >> m_checkUsername;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processConfirmPhone(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runConfirmPhone);
    context.inputStream() >> m_confirmPhone;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processDeleteAccount(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runDeleteAccount);
    context.inputStream() >> m_deleteAccount;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetAccountTTL(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetAccountTTL);
    context.inputStream() >> m_getAccountTTL;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetAuthorizations(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetAuthorizations);
    context.inputStream() >> m_getAuthorizations;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetNotifySettings(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetNotifySettings);
    context.inputStream() >> m_getNotifySettings;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetPassword(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetPassword);
    context.inputStream() >> m_getPassword;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetPasswordSettings(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetPasswordSettings);
    context.inputStream() >> m_getPasswordSettings;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetPrivacy(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetPrivacy);
    context.inputStream() >> m_getPrivacy;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetTmpPassword(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetTmpPassword);
    context.inputStream() >> m_getTmpPassword;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetWallPapers(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetWallPapers);
    context.inputStream() >> m_getWallPapers;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processRegisterDevice(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runRegisterDevice);
    context.inputStream() >> m_registerDevice;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processReportPeer(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runReportPeer);
    context.inputStream() >> m_reportPeer;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processResetAuthorization(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runResetAuthorization);
    context.inputStream() >> m_resetAuthorization;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processResetNotifySettings(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runResetNotifySettings);
    context.inputStream() >> m_resetNotifySettings;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSendChangePhoneCode(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSendChangePhoneCode);
    context.inputStream() >> m_sendChangePhoneCode;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSendConfirmPhoneCode(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSendConfirmPhoneCode);
    context.inputStream() >> m_sendConfirmPhoneCode;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSetAccountTTL(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSetAccountTTL);
    context.inputStream() >> m_setAccountTTL;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSetPrivacy(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSetPrivacy);
    context.inputStream() >> m_setPrivacy;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUnregisterDevice(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUnregisterDevice);
    context.inputStream() >> m_unregisterDevice;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUpdateDeviceLocked(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUpdateDeviceLocked);
    context.inputStream() >> m_updateDeviceLocked;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUpdateNotifySettings(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUpdateNotifySettings);
    context.inputStream() >> m_updateNotifySettings;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUpdatePasswordSettings(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUpdatePasswordSettings);
    context.inputStream() >> m_updatePasswordSettings;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUpdateProfile(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUpdateProfile);
    context.inputStream() >> m_updateProfile;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUpdateStatus(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUpdateStatus);
    context.inputStream() >> m_updateStatus;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processUpdateUsername(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runUpdateUsername);
    context.inputStream() >> m_updateUsername;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void AccountRpcOperation::runChangePhone()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUser result;
    sendRpcReply(result);
}

void AccountRpcOperation::runCheckUsername()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runConfirmPhone()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runDeleteAccount()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetAccountTTL()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAccountDaysTTL result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetAuthorizations()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAccountAuthorizations result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetNotifySettings()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLPeerNotifySettings result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetPassword()
{
    if (!verifyHasUserOrWantedUser()) {
        return;
    }
    User *user = layer()->session()->userOrWantedUser();
    PasswordInfo info = api()->getPassword(user->phoneNumber());

    TLAccountPassword result;
    if (info.hasPassword()) {
        result.tlType = TLValue::AccountPassword;
        result.currentSalt = info.currentSalt;
        result.hint = info.hint;
    } else {
        result.tlType = TLValue::AccountNoPassword;
    }
    sendRpcReply(result);
}

void AccountRpcOperation::runGetPasswordSettings()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAccountPasswordSettings result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetPrivacy()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAccountPrivacyRules result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetTmpPassword()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAccountTmpPassword result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetWallPapers()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLVector<TLWallPaper> result;
    sendRpcReply(result);
}

void AccountRpcOperation::runRegisterDevice()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runReportPeer()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResetAuthorization()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResetNotifySettings()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSendChangePhoneCode()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSendConfirmPhoneCode()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSetAccountTTL()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSetPrivacy()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAccountPrivacyRules result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUnregisterDevice()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateDeviceLocked()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateNotifySettings()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdatePasswordSettings()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateProfile()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUser result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateStatus()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateUsername()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLUser result;
    sendRpcReply(result);
}
// End of generated run methods


void AccountRpcOperation::setRunMethod(AccountRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

AccountRpcOperation::ProcessingMethod AccountRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::AccountChangePhone:
        return &AccountRpcOperation::processChangePhone;
    case TLValue::AccountCheckUsername:
        return &AccountRpcOperation::processCheckUsername;
    case TLValue::AccountConfirmPhone:
        return &AccountRpcOperation::processConfirmPhone;
    case TLValue::AccountDeleteAccount:
        return &AccountRpcOperation::processDeleteAccount;
    case TLValue::AccountGetAccountTTL:
        return &AccountRpcOperation::processGetAccountTTL;
    case TLValue::AccountGetAuthorizations:
        return &AccountRpcOperation::processGetAuthorizations;
    case TLValue::AccountGetNotifySettings:
        return &AccountRpcOperation::processGetNotifySettings;
    case TLValue::AccountGetPassword:
        return &AccountRpcOperation::processGetPassword;
    case TLValue::AccountGetPasswordSettings:
        return &AccountRpcOperation::processGetPasswordSettings;
    case TLValue::AccountGetPrivacy:
        return &AccountRpcOperation::processGetPrivacy;
    case TLValue::AccountGetTmpPassword:
        return &AccountRpcOperation::processGetTmpPassword;
    case TLValue::AccountGetWallPapers:
        return &AccountRpcOperation::processGetWallPapers;
    case TLValue::AccountRegisterDevice:
        return &AccountRpcOperation::processRegisterDevice;
    case TLValue::AccountReportPeer:
        return &AccountRpcOperation::processReportPeer;
    case TLValue::AccountResetAuthorization:
        return &AccountRpcOperation::processResetAuthorization;
    case TLValue::AccountResetNotifySettings:
        return &AccountRpcOperation::processResetNotifySettings;
    case TLValue::AccountSendChangePhoneCode:
        return &AccountRpcOperation::processSendChangePhoneCode;
    case TLValue::AccountSendConfirmPhoneCode:
        return &AccountRpcOperation::processSendConfirmPhoneCode;
    case TLValue::AccountSetAccountTTL:
        return &AccountRpcOperation::processSetAccountTTL;
    case TLValue::AccountSetPrivacy:
        return &AccountRpcOperation::processSetPrivacy;
    case TLValue::AccountUnregisterDevice:
        return &AccountRpcOperation::processUnregisterDevice;
    case TLValue::AccountUpdateDeviceLocked:
        return &AccountRpcOperation::processUpdateDeviceLocked;
    case TLValue::AccountUpdateNotifySettings:
        return &AccountRpcOperation::processUpdateNotifySettings;
    case TLValue::AccountUpdatePasswordSettings:
        return &AccountRpcOperation::processUpdatePasswordSettings;
    case TLValue::AccountUpdateProfile:
        return &AccountRpcOperation::processUpdateProfile;
    case TLValue::AccountUpdateStatus:
        return &AccountRpcOperation::processUpdateStatus;
    case TLValue::AccountUpdateUsername:
        return &AccountRpcOperation::processUpdateUsername;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *AccountOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<AccountRpcOperation>(layer, context);
}

} // Server

} // Telegram
