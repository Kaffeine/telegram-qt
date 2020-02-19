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

#ifndef ACCOUNT_OPERATION_FACTORY_HPP
#define ACCOUNT_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class AccountRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(AccountRpcOperation)
public:
    explicit AccountRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processAcceptAuthorization(RpcProcessingContext &context);
    bool processCancelPasswordEmail(RpcProcessingContext &context);
    bool processChangePhone(RpcProcessingContext &context);
    bool processCheckUsername(RpcProcessingContext &context);
    bool processConfirmPasswordEmail(RpcProcessingContext &context);
    bool processConfirmPhone(RpcProcessingContext &context);
    bool processDeleteAccount(RpcProcessingContext &context);
    bool processDeleteSecureValue(RpcProcessingContext &context);
    bool processFinishTakeoutSession(RpcProcessingContext &context);
    bool processGetAccountTTL(RpcProcessingContext &context);
    bool processGetAllSecureValues(RpcProcessingContext &context);
    bool processGetAuthorizationForm(RpcProcessingContext &context);
    bool processGetAuthorizations(RpcProcessingContext &context);
    bool processGetContactSignUpNotification(RpcProcessingContext &context);
    bool processGetNotifyExceptions(RpcProcessingContext &context);
    bool processGetNotifySettings(RpcProcessingContext &context);
    bool processGetPassword(RpcProcessingContext &context);
    bool processGetPasswordSettings(RpcProcessingContext &context);
    bool processGetPrivacy(RpcProcessingContext &context);
    bool processGetSecureValue(RpcProcessingContext &context);
    bool processGetTmpPassword(RpcProcessingContext &context);
    bool processGetWallPapers(RpcProcessingContext &context);
    bool processGetWebAuthorizations(RpcProcessingContext &context);
    bool processInitTakeoutSession(RpcProcessingContext &context);
    bool processRegisterDevice(RpcProcessingContext &context);
    bool processReportPeer(RpcProcessingContext &context);
    bool processResendPasswordEmail(RpcProcessingContext &context);
    bool processResetAuthorization(RpcProcessingContext &context);
    bool processResetNotifySettings(RpcProcessingContext &context);
    bool processResetWebAuthorization(RpcProcessingContext &context);
    bool processResetWebAuthorizations(RpcProcessingContext &context);
    bool processSaveSecureValue(RpcProcessingContext &context);
    bool processSendChangePhoneCode(RpcProcessingContext &context);
    bool processSendConfirmPhoneCode(RpcProcessingContext &context);
    bool processSendVerifyEmailCode(RpcProcessingContext &context);
    bool processSendVerifyPhoneCode(RpcProcessingContext &context);
    bool processSetAccountTTL(RpcProcessingContext &context);
    bool processSetContactSignUpNotification(RpcProcessingContext &context);
    bool processSetPrivacy(RpcProcessingContext &context);
    bool processUnregisterDevice(RpcProcessingContext &context);
    bool processUpdateDeviceLocked(RpcProcessingContext &context);
    bool processUpdateNotifySettings(RpcProcessingContext &context);
    bool processUpdatePasswordSettings(RpcProcessingContext &context);
    bool processUpdateProfile(RpcProcessingContext &context);
    bool processUpdateStatus(RpcProcessingContext &context);
    bool processUpdateUsername(RpcProcessingContext &context);
    bool processVerifyEmail(RpcProcessingContext &context);
    bool processVerifyPhone(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAcceptAuthorization();
    void runCancelPasswordEmail();
    void runChangePhone();
    void runCheckUsername();
    void runConfirmPasswordEmail();
    void runConfirmPhone();
    void runDeleteAccount();
    void runDeleteSecureValue();
    void runFinishTakeoutSession();
    void runGetAccountTTL();
    void runGetAllSecureValues();
    void runGetAuthorizationForm();
    void runGetAuthorizations();
    void runGetContactSignUpNotification();
    void runGetNotifyExceptions();
    void runGetNotifySettings();
    void runGetPassword();
    void runGetPasswordSettings();
    void runGetPrivacy();
    void runGetSecureValue();
    void runGetTmpPassword();
    void runGetWallPapers();
    void runGetWebAuthorizations();
    void runInitTakeoutSession();
    void runRegisterDevice();
    void runReportPeer();
    void runResendPasswordEmail();
    void runResetAuthorization();
    void runResetNotifySettings();
    void runResetWebAuthorization();
    void runResetWebAuthorizations();
    void runSaveSecureValue();
    void runSendChangePhoneCode();
    void runSendConfirmPhoneCode();
    void runSendVerifyEmailCode();
    void runSendVerifyPhoneCode();
    void runSetAccountTTL();
    void runSetContactSignUpNotification();
    void runSetPrivacy();
    void runUnregisterDevice();
    void runUpdateDeviceLocked();
    void runUpdateNotifySettings();
    void runUpdatePasswordSettings();
    void runUpdateProfile();
    void runUpdateStatus();
    void runUpdateUsername();
    void runVerifyEmail();
    void runVerifyPhone();
    // End of generated run methods

    using RunMethod = void (AccountRpcOperation::*)();
    using ProcessingMethod = bool (AccountRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLAccountAcceptAuthorization m_acceptAuthorization;
    MTProto::Functions::TLAccountCancelPasswordEmail m_cancelPasswordEmail;
    MTProto::Functions::TLAccountChangePhone m_changePhone;
    MTProto::Functions::TLAccountCheckUsername m_checkUsername;
    MTProto::Functions::TLAccountConfirmPasswordEmail m_confirmPasswordEmail;
    MTProto::Functions::TLAccountConfirmPhone m_confirmPhone;
    MTProto::Functions::TLAccountDeleteAccount m_deleteAccount;
    MTProto::Functions::TLAccountDeleteSecureValue m_deleteSecureValue;
    MTProto::Functions::TLAccountFinishTakeoutSession m_finishTakeoutSession;
    MTProto::Functions::TLAccountGetAccountTTL m_getAccountTTL;
    MTProto::Functions::TLAccountGetAllSecureValues m_getAllSecureValues;
    MTProto::Functions::TLAccountGetAuthorizationForm m_getAuthorizationForm;
    MTProto::Functions::TLAccountGetAuthorizations m_getAuthorizations;
    MTProto::Functions::TLAccountGetContactSignUpNotification m_getContactSignUpNotification;
    MTProto::Functions::TLAccountGetNotifyExceptions m_getNotifyExceptions;
    MTProto::Functions::TLAccountGetNotifySettings m_getNotifySettings;
    MTProto::Functions::TLAccountGetPassword m_getPassword;
    MTProto::Functions::TLAccountGetPasswordSettings m_getPasswordSettings;
    MTProto::Functions::TLAccountGetPrivacy m_getPrivacy;
    MTProto::Functions::TLAccountGetSecureValue m_getSecureValue;
    MTProto::Functions::TLAccountGetTmpPassword m_getTmpPassword;
    MTProto::Functions::TLAccountGetWallPapers m_getWallPapers;
    MTProto::Functions::TLAccountGetWebAuthorizations m_getWebAuthorizations;
    MTProto::Functions::TLAccountInitTakeoutSession m_initTakeoutSession;
    MTProto::Functions::TLAccountRegisterDevice m_registerDevice;
    MTProto::Functions::TLAccountReportPeer m_reportPeer;
    MTProto::Functions::TLAccountResendPasswordEmail m_resendPasswordEmail;
    MTProto::Functions::TLAccountResetAuthorization m_resetAuthorization;
    MTProto::Functions::TLAccountResetNotifySettings m_resetNotifySettings;
    MTProto::Functions::TLAccountResetWebAuthorization m_resetWebAuthorization;
    MTProto::Functions::TLAccountResetWebAuthorizations m_resetWebAuthorizations;
    MTProto::Functions::TLAccountSaveSecureValue m_saveSecureValue;
    MTProto::Functions::TLAccountSendChangePhoneCode m_sendChangePhoneCode;
    MTProto::Functions::TLAccountSendConfirmPhoneCode m_sendConfirmPhoneCode;
    MTProto::Functions::TLAccountSendVerifyEmailCode m_sendVerifyEmailCode;
    MTProto::Functions::TLAccountSendVerifyPhoneCode m_sendVerifyPhoneCode;
    MTProto::Functions::TLAccountSetAccountTTL m_setAccountTTL;
    MTProto::Functions::TLAccountSetContactSignUpNotification m_setContactSignUpNotification;
    MTProto::Functions::TLAccountSetPrivacy m_setPrivacy;
    MTProto::Functions::TLAccountUnregisterDevice m_unregisterDevice;
    MTProto::Functions::TLAccountUpdateDeviceLocked m_updateDeviceLocked;
    MTProto::Functions::TLAccountUpdateNotifySettings m_updateNotifySettings;
    MTProto::Functions::TLAccountUpdatePasswordSettings m_updatePasswordSettings;
    MTProto::Functions::TLAccountUpdateProfile m_updateProfile;
    MTProto::Functions::TLAccountUpdateStatus m_updateStatus;
    MTProto::Functions::TLAccountUpdateUsername m_updateUsername;
    MTProto::Functions::TLAccountVerifyEmail m_verifyEmail;
    MTProto::Functions::TLAccountVerifyPhone m_verifyPhone;
    // End of generated RPC members
};

class AccountOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // ACCOUNT_OPERATION_FACTORY_HPP
