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
    bool processChangePhone(RpcProcessingContext &context);
    bool processCheckUsername(RpcProcessingContext &context);
    bool processConfirmPhone(RpcProcessingContext &context);
    bool processDeleteAccount(RpcProcessingContext &context);
    bool processGetAccountTTL(RpcProcessingContext &context);
    bool processGetAuthorizations(RpcProcessingContext &context);
    bool processGetNotifySettings(RpcProcessingContext &context);
    bool processGetPassword(RpcProcessingContext &context);
    bool processGetPasswordSettings(RpcProcessingContext &context);
    bool processGetPrivacy(RpcProcessingContext &context);
    bool processGetTmpPassword(RpcProcessingContext &context);
    bool processGetWallPapers(RpcProcessingContext &context);
    bool processRegisterDevice(RpcProcessingContext &context);
    bool processReportPeer(RpcProcessingContext &context);
    bool processResetAuthorization(RpcProcessingContext &context);
    bool processResetNotifySettings(RpcProcessingContext &context);
    bool processSendChangePhoneCode(RpcProcessingContext &context);
    bool processSendConfirmPhoneCode(RpcProcessingContext &context);
    bool processSetAccountTTL(RpcProcessingContext &context);
    bool processSetPrivacy(RpcProcessingContext &context);
    bool processUnregisterDevice(RpcProcessingContext &context);
    bool processUpdateDeviceLocked(RpcProcessingContext &context);
    bool processUpdateNotifySettings(RpcProcessingContext &context);
    bool processUpdatePasswordSettings(RpcProcessingContext &context);
    bool processUpdateProfile(RpcProcessingContext &context);
    bool processUpdateStatus(RpcProcessingContext &context);
    bool processUpdateUsername(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runChangePhone();
    void runCheckUsername();
    void runConfirmPhone();
    void runDeleteAccount();
    void runGetAccountTTL();
    void runGetAuthorizations();
    void runGetNotifySettings();
    void runGetPassword();
    void runGetPasswordSettings();
    void runGetPrivacy();
    void runGetTmpPassword();
    void runGetWallPapers();
    void runRegisterDevice();
    void runReportPeer();
    void runResetAuthorization();
    void runResetNotifySettings();
    void runSendChangePhoneCode();
    void runSendConfirmPhoneCode();
    void runSetAccountTTL();
    void runSetPrivacy();
    void runUnregisterDevice();
    void runUpdateDeviceLocked();
    void runUpdateNotifySettings();
    void runUpdatePasswordSettings();
    void runUpdateProfile();
    void runUpdateStatus();
    void runUpdateUsername();
    // End of generated run methods

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (AccountRpcOperation::*)();
    using ProcessingMethod = bool (AccountRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLAccountChangePhone m_changePhone;
    TLFunctions::TLAccountCheckUsername m_checkUsername;
    TLFunctions::TLAccountConfirmPhone m_confirmPhone;
    TLFunctions::TLAccountDeleteAccount m_deleteAccount;
    TLFunctions::TLAccountGetAccountTTL m_getAccountTTL;
    TLFunctions::TLAccountGetAuthorizations m_getAuthorizations;
    TLFunctions::TLAccountGetNotifySettings m_getNotifySettings;
    TLFunctions::TLAccountGetPassword m_getPassword;
    TLFunctions::TLAccountGetPasswordSettings m_getPasswordSettings;
    TLFunctions::TLAccountGetPrivacy m_getPrivacy;
    TLFunctions::TLAccountGetTmpPassword m_getTmpPassword;
    TLFunctions::TLAccountGetWallPapers m_getWallPapers;
    TLFunctions::TLAccountRegisterDevice m_registerDevice;
    TLFunctions::TLAccountReportPeer m_reportPeer;
    TLFunctions::TLAccountResetAuthorization m_resetAuthorization;
    TLFunctions::TLAccountResetNotifySettings m_resetNotifySettings;
    TLFunctions::TLAccountSendChangePhoneCode m_sendChangePhoneCode;
    TLFunctions::TLAccountSendConfirmPhoneCode m_sendConfirmPhoneCode;
    TLFunctions::TLAccountSetAccountTTL m_setAccountTTL;
    TLFunctions::TLAccountSetPrivacy m_setPrivacy;
    TLFunctions::TLAccountUnregisterDevice m_unregisterDevice;
    TLFunctions::TLAccountUpdateDeviceLocked m_updateDeviceLocked;
    TLFunctions::TLAccountUpdateNotifySettings m_updateNotifySettings;
    TLFunctions::TLAccountUpdatePasswordSettings m_updatePasswordSettings;
    TLFunctions::TLAccountUpdateProfile m_updateProfile;
    TLFunctions::TLAccountUpdateStatus m_updateStatus;
    TLFunctions::TLAccountUpdateUsername m_updateUsername;
    // End of generated RPC members
};

class AccountOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // ACCOUNT_OPERATION_FACTORY_HPP
