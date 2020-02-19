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

#include "ApiUtils.hpp"
#include "AuthService.hpp"
#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "LocalServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "ServerUtils.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool AccountRpcOperation::processAcceptAuthorization(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runAcceptAuthorization);
    context.inputStream() >> m_acceptAuthorization;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processCancelPasswordEmail(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runCancelPasswordEmail);
    context.inputStream() >> m_cancelPasswordEmail;
    return !context.inputStream().error();
}

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

bool AccountRpcOperation::processConfirmPasswordEmail(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runConfirmPasswordEmail);
    context.inputStream() >> m_confirmPasswordEmail;
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

bool AccountRpcOperation::processDeleteSecureValue(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runDeleteSecureValue);
    context.inputStream() >> m_deleteSecureValue;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processFinishTakeoutSession(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runFinishTakeoutSession);
    context.inputStream() >> m_finishTakeoutSession;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetAccountTTL(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetAccountTTL);
    context.inputStream() >> m_getAccountTTL;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetAllSecureValues(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetAllSecureValues);
    context.inputStream() >> m_getAllSecureValues;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetAuthorizationForm(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetAuthorizationForm);
    context.inputStream() >> m_getAuthorizationForm;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetAuthorizations(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetAuthorizations);
    context.inputStream() >> m_getAuthorizations;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetContactSignUpNotification(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetContactSignUpNotification);
    context.inputStream() >> m_getContactSignUpNotification;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processGetNotifyExceptions(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetNotifyExceptions);
    context.inputStream() >> m_getNotifyExceptions;
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

bool AccountRpcOperation::processGetSecureValue(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetSecureValue);
    context.inputStream() >> m_getSecureValue;
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

bool AccountRpcOperation::processGetWebAuthorizations(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runGetWebAuthorizations);
    context.inputStream() >> m_getWebAuthorizations;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processInitTakeoutSession(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runInitTakeoutSession);
    context.inputStream() >> m_initTakeoutSession;
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

bool AccountRpcOperation::processResendPasswordEmail(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runResendPasswordEmail);
    context.inputStream() >> m_resendPasswordEmail;
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

bool AccountRpcOperation::processResetWebAuthorization(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runResetWebAuthorization);
    context.inputStream() >> m_resetWebAuthorization;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processResetWebAuthorizations(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runResetWebAuthorizations);
    context.inputStream() >> m_resetWebAuthorizations;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSaveSecureValue(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSaveSecureValue);
    context.inputStream() >> m_saveSecureValue;
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

bool AccountRpcOperation::processSendVerifyEmailCode(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSendVerifyEmailCode);
    context.inputStream() >> m_sendVerifyEmailCode;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSendVerifyPhoneCode(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSendVerifyPhoneCode);
    context.inputStream() >> m_sendVerifyPhoneCode;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSetAccountTTL(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSetAccountTTL);
    context.inputStream() >> m_setAccountTTL;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processSetContactSignUpNotification(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runSetContactSignUpNotification);
    context.inputStream() >> m_setContactSignUpNotification;
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

bool AccountRpcOperation::processVerifyEmail(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runVerifyEmail);
    context.inputStream() >> m_verifyEmail;
    return !context.inputStream().error();
}

bool AccountRpcOperation::processVerifyPhone(RpcProcessingContext &context)
{
    setRunMethod(&AccountRpcOperation::runVerifyPhone);
    context.inputStream() >> m_verifyPhone;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void AccountRpcOperation::runAcceptAuthorization()
{
    // MTProto::Functions::TLAccountAcceptAuthorization &arguments = m_acceptAuthorization;
    if (processNotImplementedMethod(TLValue::AccountAcceptAuthorization)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runCancelPasswordEmail()
{
    if (processNotImplementedMethod(TLValue::AccountCancelPasswordEmail)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runChangePhone()
{
    // MTProto::Functions::TLAccountChangePhone &arguments = m_changePhone;
    if (processNotImplementedMethod(TLValue::AccountChangePhone)) {
        return;
    }
    TLUser result;
    sendRpcReply(result);
}

void AccountRpcOperation::runCheckUsername()
{
    MTProto::Functions::TLAccountCheckUsername &arguments = m_checkUsername;
    bool result = !api()->getPeerByUserName(arguments.username).isValid();
    sendRpcReply(result);
}

void AccountRpcOperation::runConfirmPasswordEmail()
{
    // MTProto::Functions::TLAccountConfirmPasswordEmail &arguments = m_confirmPasswordEmail;
    if (processNotImplementedMethod(TLValue::AccountConfirmPasswordEmail)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runConfirmPhone()
{
    // MTProto::Functions::TLAccountConfirmPhone &arguments = m_confirmPhone;
    if (processNotImplementedMethod(TLValue::AccountConfirmPhone)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runDeleteAccount()
{
    // MTProto::Functions::TLAccountDeleteAccount &arguments = m_deleteAccount;
    if (processNotImplementedMethod(TLValue::AccountDeleteAccount)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runDeleteSecureValue()
{
    // MTProto::Functions::TLAccountDeleteSecureValue &arguments = m_deleteSecureValue;
    if (processNotImplementedMethod(TLValue::AccountDeleteSecureValue)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runFinishTakeoutSession()
{
    // MTProto::Functions::TLAccountFinishTakeoutSession &arguments = m_finishTakeoutSession;
    if (processNotImplementedMethod(TLValue::AccountFinishTakeoutSession)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetAccountTTL()
{
    if (processNotImplementedMethod(TLValue::AccountGetAccountTTL)) {
        return;
    }
    TLAccountDaysTTL result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetAllSecureValues()
{
    if (processNotImplementedMethod(TLValue::AccountGetAllSecureValues)) {
        return;
    }
    TLVector<TLSecureValue> result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetAuthorizationForm()
{
    // MTProto::Functions::TLAccountGetAuthorizationForm &arguments = m_getAuthorizationForm;
    if (processNotImplementedMethod(TLValue::AccountGetAuthorizationForm)) {
        return;
    }
    TLAccountAuthorizationForm result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetAuthorizations()
{
    if (processNotImplementedMethod(TLValue::AccountGetAuthorizations)) {
        return;
    }
    TLAccountAuthorizations result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetContactSignUpNotification()
{
    if (processNotImplementedMethod(TLValue::AccountGetContactSignUpNotification)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetNotifyExceptions()
{
    // MTProto::Functions::TLAccountGetNotifyExceptions &arguments = m_getNotifyExceptions;
    if (processNotImplementedMethod(TLValue::AccountGetNotifyExceptions)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetNotifySettings()
{
    // MTProto::Functions::TLAccountGetNotifySettings &arguments = m_getNotifySettings;
    if (processNotImplementedMethod(TLValue::AccountGetNotifySettings)) {
        return;
    }
    TLPeerNotifySettings result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetPassword()
{
    if (!verifyHasUserOrWantedUser()) {
        return;
    }
    LocalUser *user = api()->getUser(layer()->session()->userOrWantedUserId());
    PasswordInfo info = api()->authService()->getPassword(user);

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
    // MTProto::Functions::TLAccountGetPasswordSettings &arguments = m_getPasswordSettings;
    if (processNotImplementedMethod(TLValue::AccountGetPasswordSettings)) {
        return;
    }
    TLAccountPasswordSettings result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetPrivacy()
{
    // MTProto::Functions::TLAccountGetPrivacy &arguments = m_getPrivacy;
    if (processNotImplementedMethod(TLValue::AccountGetPrivacy)) {
        return;
    }
    TLAccountPrivacyRules result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetSecureValue()
{
    // MTProto::Functions::TLAccountGetSecureValue &arguments = m_getSecureValue;
    if (processNotImplementedMethod(TLValue::AccountGetSecureValue)) {
        return;
    }
    TLVector<TLSecureValue> result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetTmpPassword()
{
    // MTProto::Functions::TLAccountGetTmpPassword &arguments = m_getTmpPassword;
    if (processNotImplementedMethod(TLValue::AccountGetTmpPassword)) {
        return;
    }
    TLAccountTmpPassword result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetWallPapers()
{
    if (processNotImplementedMethod(TLValue::AccountGetWallPapers)) {
        return;
    }
    TLVector<TLWallPaper> result;
    sendRpcReply(result);
}

void AccountRpcOperation::runGetWebAuthorizations()
{
    if (processNotImplementedMethod(TLValue::AccountGetWebAuthorizations)) {
        return;
    }
    TLAccountWebAuthorizations result;
    sendRpcReply(result);
}

void AccountRpcOperation::runInitTakeoutSession()
{
    // MTProto::Functions::TLAccountInitTakeoutSession &arguments = m_initTakeoutSession;
    if (processNotImplementedMethod(TLValue::AccountInitTakeoutSession)) {
        return;
    }
    TLAccountTakeout result;
    sendRpcReply(result);
}

void AccountRpcOperation::runRegisterDevice()
{
    // MTProto::Functions::TLAccountRegisterDevice &arguments = m_registerDevice;
    if (processNotImplementedMethod(TLValue::AccountRegisterDevice)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runReportPeer()
{
    // MTProto::Functions::TLAccountReportPeer &arguments = m_reportPeer;
    if (processNotImplementedMethod(TLValue::AccountReportPeer)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResendPasswordEmail()
{
    if (processNotImplementedMethod(TLValue::AccountResendPasswordEmail)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResetAuthorization()
{
    // MTProto::Functions::TLAccountResetAuthorization &arguments = m_resetAuthorization;
    if (processNotImplementedMethod(TLValue::AccountResetAuthorization)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResetNotifySettings()
{
    if (processNotImplementedMethod(TLValue::AccountResetNotifySettings)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResetWebAuthorization()
{
    // MTProto::Functions::TLAccountResetWebAuthorization &arguments = m_resetWebAuthorization;
    if (processNotImplementedMethod(TLValue::AccountResetWebAuthorization)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runResetWebAuthorizations()
{
    if (processNotImplementedMethod(TLValue::AccountResetWebAuthorizations)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSaveSecureValue()
{
    // MTProto::Functions::TLAccountSaveSecureValue &arguments = m_saveSecureValue;
    if (processNotImplementedMethod(TLValue::AccountSaveSecureValue)) {
        return;
    }
    TLSecureValue result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSendChangePhoneCode()
{
    // MTProto::Functions::TLAccountSendChangePhoneCode &arguments = m_sendChangePhoneCode;
    if (processNotImplementedMethod(TLValue::AccountSendChangePhoneCode)) {
        return;
    }
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSendConfirmPhoneCode()
{
    // MTProto::Functions::TLAccountSendConfirmPhoneCode &arguments = m_sendConfirmPhoneCode;
    if (processNotImplementedMethod(TLValue::AccountSendConfirmPhoneCode)) {
        return;
    }
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSendVerifyEmailCode()
{
    // MTProto::Functions::TLAccountSendVerifyEmailCode &arguments = m_sendVerifyEmailCode;
    if (processNotImplementedMethod(TLValue::AccountSendVerifyEmailCode)) {
        return;
    }
    TLAccountSentEmailCode result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSendVerifyPhoneCode()
{
    // MTProto::Functions::TLAccountSendVerifyPhoneCode &arguments = m_sendVerifyPhoneCode;
    if (processNotImplementedMethod(TLValue::AccountSendVerifyPhoneCode)) {
        return;
    }
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSetAccountTTL()
{
    // MTProto::Functions::TLAccountSetAccountTTL &arguments = m_setAccountTTL;
    if (processNotImplementedMethod(TLValue::AccountSetAccountTTL)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSetContactSignUpNotification()
{
    // MTProto::Functions::TLAccountSetContactSignUpNotification &arguments = m_setContactSignUpNotification;
    if (processNotImplementedMethod(TLValue::AccountSetContactSignUpNotification)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runSetPrivacy()
{
    // MTProto::Functions::TLAccountSetPrivacy &arguments = m_setPrivacy;
    if (processNotImplementedMethod(TLValue::AccountSetPrivacy)) {
        return;
    }
    TLAccountPrivacyRules result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUnregisterDevice()
{
    // MTProto::Functions::TLAccountUnregisterDevice &arguments = m_unregisterDevice;
    if (processNotImplementedMethod(TLValue::AccountUnregisterDevice)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateDeviceLocked()
{
    // MTProto::Functions::TLAccountUpdateDeviceLocked &arguments = m_updateDeviceLocked;
    if (processNotImplementedMethod(TLValue::AccountUpdateDeviceLocked)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateNotifySettings()
{
    // MTProto::Functions::TLAccountUpdateNotifySettings &arguments = m_updateNotifySettings;
    if (processNotImplementedMethod(TLValue::AccountUpdateNotifySettings)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdatePasswordSettings()
{
    // MTProto::Functions::TLAccountUpdatePasswordSettings &arguments = m_updatePasswordSettings;
    if (processNotImplementedMethod(TLValue::AccountUpdatePasswordSettings)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runUpdateProfile()
{
    MTProto::Functions::TLAccountUpdateProfile &arguments = m_updateProfile;
    LocalUser *selfUser = layer()->getUser();

    bool nameChanged = false;
    if (arguments.flags & 1 << 0) {
        QString name = arguments.firstName.trimmed();
        if (name.isEmpty()) {
            sendRpcError(RpcError::FirstnameInvalid);
            return;
        }
        if (name != selfUser->firstName()) {
            nameChanged = true;
            selfUser->setFirstName(name);
        }
    }
    if (arguments.flags & 1 << 1) {
        QString name = arguments.lastName.trimmed();
        if (name != selfUser->lastName()) {
            nameChanged = true;
            selfUser->setLastName(name);
        }
    }
    if (arguments.flags & 1 << 2) {
        QString about = arguments.about.trimmed();
        selfUser->setAbout(about);
    }

    TLUser result;
    Utils::setupTLUser(&result, selfUser, selfUser);
    sendRpcReply(result);

    if (!nameChanged) {
        return;
    }

    const auto notifications = api()->createUpdates(UpdateNotification::Type::UpdateName,
                                                    selfUser, layer()->session());
    api()->queueUpdates(notifications);
}

void AccountRpcOperation::runUpdateStatus()
{
    MTProto::Functions::TLAccountUpdateStatus &arguments = m_updateStatus;
    LocalUser *selfUser = layer()->getUser();
    const bool statusChanged = api()->setUserOnline(selfUser, !arguments.offline,
                                                    layer()->session());

    // Return true is the status changed.
    sendRpcReply(statusChanged);
}

void AccountRpcOperation::runUpdateUsername()
{
    MTProto::Functions::TLAccountUpdateUsername &arguments = m_updateUsername;
    LocalUser *selfUser = layer()->getUser();

    // empty string if username is to be removed
    if (!arguments.username.isEmpty()) {
        if (!api()->usernameIsValid(arguments.username)) {
            sendRpcError(RpcError::UsernameInvalid);
            return;
        }
    }
    RpcError error;
    api()->setUserName(selfUser, arguments.username, &error);
    if (error.isValid()) {
        sendRpcError(error);
        return;
    }

    TLUser result;
    Utils::setupTLUser(&result, selfUser, selfUser);
    sendRpcReply(result);

    const auto notifications = api()->createUpdates(UpdateNotification::Type::UpdateName,
                                                    selfUser, layer()->session());
    api()->queueUpdates(notifications);
}

void AccountRpcOperation::runVerifyEmail()
{
    // MTProto::Functions::TLAccountVerifyEmail &arguments = m_verifyEmail;
    if (processNotImplementedMethod(TLValue::AccountVerifyEmail)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AccountRpcOperation::runVerifyPhone()
{
    // MTProto::Functions::TLAccountVerifyPhone &arguments = m_verifyPhone;
    if (processNotImplementedMethod(TLValue::AccountVerifyPhone)) {
        return;
    }
    bool result;
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
    case TLValue::AccountAcceptAuthorization:
        return &AccountRpcOperation::processAcceptAuthorization;
    case TLValue::AccountCancelPasswordEmail:
        return &AccountRpcOperation::processCancelPasswordEmail;
    case TLValue::AccountChangePhone:
        return &AccountRpcOperation::processChangePhone;
    case TLValue::AccountCheckUsername:
        return &AccountRpcOperation::processCheckUsername;
    case TLValue::AccountConfirmPasswordEmail:
        return &AccountRpcOperation::processConfirmPasswordEmail;
    case TLValue::AccountConfirmPhone:
        return &AccountRpcOperation::processConfirmPhone;
    case TLValue::AccountDeleteAccount:
        return &AccountRpcOperation::processDeleteAccount;
    case TLValue::AccountDeleteSecureValue:
        return &AccountRpcOperation::processDeleteSecureValue;
    case TLValue::AccountFinishTakeoutSession:
        return &AccountRpcOperation::processFinishTakeoutSession;
    case TLValue::AccountGetAccountTTL:
        return &AccountRpcOperation::processGetAccountTTL;
    case TLValue::AccountGetAllSecureValues:
        return &AccountRpcOperation::processGetAllSecureValues;
    case TLValue::AccountGetAuthorizationForm:
        return &AccountRpcOperation::processGetAuthorizationForm;
    case TLValue::AccountGetAuthorizations:
        return &AccountRpcOperation::processGetAuthorizations;
    case TLValue::AccountGetContactSignUpNotification:
        return &AccountRpcOperation::processGetContactSignUpNotification;
    case TLValue::AccountGetNotifyExceptions:
        return &AccountRpcOperation::processGetNotifyExceptions;
    case TLValue::AccountGetNotifySettings:
        return &AccountRpcOperation::processGetNotifySettings;
    case TLValue::AccountGetPassword:
        return &AccountRpcOperation::processGetPassword;
    case TLValue::AccountGetPasswordSettings:
        return &AccountRpcOperation::processGetPasswordSettings;
    case TLValue::AccountGetPrivacy:
        return &AccountRpcOperation::processGetPrivacy;
    case TLValue::AccountGetSecureValue:
        return &AccountRpcOperation::processGetSecureValue;
    case TLValue::AccountGetTmpPassword:
        return &AccountRpcOperation::processGetTmpPassword;
    case TLValue::AccountGetWallPapers:
        return &AccountRpcOperation::processGetWallPapers;
    case TLValue::AccountGetWebAuthorizations:
        return &AccountRpcOperation::processGetWebAuthorizations;
    case TLValue::AccountInitTakeoutSession:
        return &AccountRpcOperation::processInitTakeoutSession;
    case TLValue::AccountRegisterDevice:
        return &AccountRpcOperation::processRegisterDevice;
    case TLValue::AccountReportPeer:
        return &AccountRpcOperation::processReportPeer;
    case TLValue::AccountResendPasswordEmail:
        return &AccountRpcOperation::processResendPasswordEmail;
    case TLValue::AccountResetAuthorization:
        return &AccountRpcOperation::processResetAuthorization;
    case TLValue::AccountResetNotifySettings:
        return &AccountRpcOperation::processResetNotifySettings;
    case TLValue::AccountResetWebAuthorization:
        return &AccountRpcOperation::processResetWebAuthorization;
    case TLValue::AccountResetWebAuthorizations:
        return &AccountRpcOperation::processResetWebAuthorizations;
    case TLValue::AccountSaveSecureValue:
        return &AccountRpcOperation::processSaveSecureValue;
    case TLValue::AccountSendChangePhoneCode:
        return &AccountRpcOperation::processSendChangePhoneCode;
    case TLValue::AccountSendConfirmPhoneCode:
        return &AccountRpcOperation::processSendConfirmPhoneCode;
    case TLValue::AccountSendVerifyEmailCode:
        return &AccountRpcOperation::processSendVerifyEmailCode;
    case TLValue::AccountSendVerifyPhoneCode:
        return &AccountRpcOperation::processSendVerifyPhoneCode;
    case TLValue::AccountSetAccountTTL:
        return &AccountRpcOperation::processSetAccountTTL;
    case TLValue::AccountSetContactSignUpNotification:
        return &AccountRpcOperation::processSetContactSignUpNotification;
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
    case TLValue::AccountVerifyEmail:
        return &AccountRpcOperation::processVerifyEmail;
    case TLValue::AccountVerifyPhone:
        return &AccountRpcOperation::processVerifyPhone;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *AccountOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<AccountRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
