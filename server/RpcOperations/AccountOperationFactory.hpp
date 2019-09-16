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

    using RunMethod = void (AccountRpcOperation::*)();
    using ProcessingMethod = bool (AccountRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLAccountChangePhone m_changePhone;
    MTProto::Functions::TLAccountCheckUsername m_checkUsername;
    MTProto::Functions::TLAccountConfirmPhone m_confirmPhone;
    MTProto::Functions::TLAccountDeleteAccount m_deleteAccount;
    MTProto::Functions::TLAccountGetAccountTTL m_getAccountTTL;
    MTProto::Functions::TLAccountGetAuthorizations m_getAuthorizations;
    MTProto::Functions::TLAccountGetNotifySettings m_getNotifySettings;
    MTProto::Functions::TLAccountGetPassword m_getPassword;
    MTProto::Functions::TLAccountGetPasswordSettings m_getPasswordSettings;
    MTProto::Functions::TLAccountGetPrivacy m_getPrivacy;
    MTProto::Functions::TLAccountGetTmpPassword m_getTmpPassword;
    MTProto::Functions::TLAccountGetWallPapers m_getWallPapers;
    MTProto::Functions::TLAccountRegisterDevice m_registerDevice;
    MTProto::Functions::TLAccountReportPeer m_reportPeer;
    MTProto::Functions::TLAccountResetAuthorization m_resetAuthorization;
    MTProto::Functions::TLAccountResetNotifySettings m_resetNotifySettings;
    MTProto::Functions::TLAccountSendChangePhoneCode m_sendChangePhoneCode;
    MTProto::Functions::TLAccountSendConfirmPhoneCode m_sendConfirmPhoneCode;
    MTProto::Functions::TLAccountSetAccountTTL m_setAccountTTL;
    MTProto::Functions::TLAccountSetPrivacy m_setPrivacy;
    MTProto::Functions::TLAccountUnregisterDevice m_unregisterDevice;
    MTProto::Functions::TLAccountUpdateDeviceLocked m_updateDeviceLocked;
    MTProto::Functions::TLAccountUpdateNotifySettings m_updateNotifySettings;
    MTProto::Functions::TLAccountUpdatePasswordSettings m_updatePasswordSettings;
    MTProto::Functions::TLAccountUpdateProfile m_updateProfile;
    MTProto::Functions::TLAccountUpdateStatus m_updateStatus;
    MTProto::Functions::TLAccountUpdateUsername m_updateUsername;
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
