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

#ifndef AUTH_OPERATION_FACTORY_HPP
#define AUTH_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class AuthRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(AuthRpcOperation)
public:
    explicit AuthRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processBindTempAuthKey(RpcProcessingContext &context);
    bool processCancelCode(RpcProcessingContext &context);
    bool processCheckPassword(RpcProcessingContext &context);
    bool processCheckPhone(RpcProcessingContext &context);
    bool processDropTempAuthKeys(RpcProcessingContext &context);
    bool processExportAuthorization(RpcProcessingContext &context);
    bool processImportAuthorization(RpcProcessingContext &context);
    bool processImportBotAuthorization(RpcProcessingContext &context);
    bool processLogOut(RpcProcessingContext &context);
    bool processRecoverPassword(RpcProcessingContext &context);
    bool processRequestPasswordRecovery(RpcProcessingContext &context);
    bool processResendCode(RpcProcessingContext &context);
    bool processResetAuthorizations(RpcProcessingContext &context);
    bool processSendCode(RpcProcessingContext &context);
    bool processSendInvites(RpcProcessingContext &context);
    bool processSignIn(RpcProcessingContext &context);
    bool processSignUp(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runBindTempAuthKey();
    void runCancelCode();
    void runCheckPassword();
    void runCheckPhone();
    void runDropTempAuthKeys();
    void runExportAuthorization();
    void runImportAuthorization();
    void runImportBotAuthorization();
    void runLogOut();
    void runRecoverPassword();
    void runRequestPasswordRecovery();
    void runResendCode();
    void runResetAuthorizations();
    void runSendCode();
    void runSendInvites();
    void runSignIn();
    void runSignUp();
    // End of generated run methods

    bool verifyAuthCode(const QString &phoneNumber, const QString &hash, const QString &code);

    using RunMethod = void (AuthRpcOperation::*)();
    using ProcessingMethod = bool (AuthRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLAuthBindTempAuthKey m_bindTempAuthKey;
    TLFunctions::TLAuthCancelCode m_cancelCode;
    TLFunctions::TLAuthCheckPassword m_checkPassword;
    TLFunctions::TLAuthCheckPhone m_checkPhone;
    TLFunctions::TLAuthDropTempAuthKeys m_dropTempAuthKeys;
    TLFunctions::TLAuthExportAuthorization m_exportAuthorization;
    TLFunctions::TLAuthImportAuthorization m_importAuthorization;
    TLFunctions::TLAuthImportBotAuthorization m_importBotAuthorization;
    TLFunctions::TLAuthLogOut m_logOut;
    TLFunctions::TLAuthRecoverPassword m_recoverPassword;
    TLFunctions::TLAuthRequestPasswordRecovery m_requestPasswordRecovery;
    TLFunctions::TLAuthResendCode m_resendCode;
    TLFunctions::TLAuthResetAuthorizations m_resetAuthorizations;
    TLFunctions::TLAuthSendCode m_sendCode;
    TLFunctions::TLAuthSendInvites m_sendInvites;
    TLFunctions::TLAuthSignIn m_signIn;
    TLFunctions::TLAuthSignUp m_signUp;
    // End of generated RPC members
};

class AuthOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // RPC_OPERATION_FACTORY_HPP
