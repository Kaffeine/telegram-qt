#include "AuthOperationFactory.hpp"

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

bool userToTlUser(const User *user, TLUser *output)
{
    if (!user) {
        output->tlType = TLValue::UserEmpty;
        return false;
    }
    output->tlType = TLValue::User;
    output->phone = user->phoneNumber();
    output->id= user->id();
    output->firstName = user->firstName();
    output->lastName = user->lastName();
    return true;
}

// TODO: Generated flags bakers
void bakeFlags(TLUser *user)
{
    quint32 flags = 0;
    if (!user->firstName.isEmpty()) {
        flags |= TLUser::FirstName;
    }
    if (!user->lastName.isEmpty()) {
        flags |= TLUser::LastName;
    }
    if (!user->username.isEmpty()) {
        flags |= TLUser::Username;
    }
    if (!user->phone.isEmpty()) {
        flags |= TLUser::Phone;
    }
    user->flags &= ~flags;
    user->flags |= flags;
}

// Generated process methods
bool AuthRpcOperation::processBindTempAuthKey(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runBindTempAuthKey);
    context.inputStream() >> m_bindTempAuthKey;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processCancelCode(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runCancelCode);
    context.inputStream() >> m_cancelCode;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processCheckPassword(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runCheckPassword);
    context.inputStream() >> m_checkPassword;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processCheckPhone(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runCheckPhone);
    context.inputStream() >> m_checkPhone;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processDropTempAuthKeys(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runDropTempAuthKeys);
    context.inputStream() >> m_dropTempAuthKeys;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processExportAuthorization(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runExportAuthorization);
    context.inputStream() >> m_exportAuthorization;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processImportAuthorization(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runImportAuthorization);
    context.inputStream() >> m_importAuthorization;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processImportBotAuthorization(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runImportBotAuthorization);
    context.inputStream() >> m_importBotAuthorization;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processLogOut(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runLogOut);
    context.inputStream() >> m_logOut;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processRecoverPassword(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runRecoverPassword);
    context.inputStream() >> m_recoverPassword;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processRequestPasswordRecovery(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runRequestPasswordRecovery);
    context.inputStream() >> m_requestPasswordRecovery;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processResendCode(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runResendCode);
    context.inputStream() >> m_resendCode;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processResetAuthorizations(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runResetAuthorizations);
    context.inputStream() >> m_resetAuthorizations;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processSendCode(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSendCode);
    context.inputStream() >> m_sendCode;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processSendInvites(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSendInvites);
    context.inputStream() >> m_sendInvites;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processSignIn(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSignIn);
    context.inputStream() >> m_signIn;
    return !context.inputStream().error();
}

bool AuthRpcOperation::processSignUp(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSignUp);
    context.inputStream() >> m_signUp;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void AuthRpcOperation::runBindTempAuthKey()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runCancelCode()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runCheckPassword()
{
    qDebug() << Q_FUNC_INFO;
    Session *session = layer()->session();
    if (!session) {
        sendRpcError(RpcError::AuthKeyUnregistered);
        return;
    }
    User *user = session->wanterUser();
    const bool passwordIsCorrect = api()->checkPassword(user->phoneNumber(), m_checkPassword.passwordHash);
    if (!passwordIsCorrect) {
        sendRpcError(RpcError::PasswordHashInvalid);
        return;
    }
    user->addSession(session);

    TLAuthAuthorization result;
    qDebug() << "Result type:" << result.tlType;
    userToTlUser(user, &result.user);
    result.user.flags = TLUser::Self;
    bakeFlags(&result.user);
    sendRpcReply(result);
}

void AuthRpcOperation::runCheckPhone()
{
    PhoneStatus status = api()->getPhoneStatus(m_checkPhone.phoneNumber);
    TLAuthCheckedPhone result;
    result.phoneRegistered = status.exists();
    sendRpcReply(result);
}

void AuthRpcOperation::runDropTempAuthKeys()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runExportAuthorization()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthExportedAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runImportAuthorization()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runImportBotAuthorization()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runLogOut()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runRecoverPassword()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runRequestPasswordRecovery()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthPasswordRecovery result;
    sendRpcReply(result);
}

void AuthRpcOperation::runResendCode()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AuthRpcOperation::runResetAuthorizations()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runSendCode()
{
    qDebug() << Q_FUNC_INFO;
    PhoneStatus status = api()->getPhoneStatus(m_sendCode.phoneNumber);
    if (status.exists() && (status.dcId != api()->dcId())) {
        RpcError error(RpcError::PhoneMigrateX, status.dcId);
        sendRpcError(error);
        return;
    }
    TLAuthSentCode result;
    {
        TLAuthSentCodeType codeType;
        // TLValue::AuthSentCodeTypeCall:
        // TLValue::AuthSentCodeTypeFlashCall:
        if (status.online) {
            codeType.tlType = TLValue::AuthSentCodeTypeApp;
        } else {
            codeType.tlType = TLValue::AuthSentCodeTypeSms;
        }
        result.type = codeType;
    }

    result.phoneCodeHash = QString::fromLatin1(api()->sendAppCode(m_sendCode.phoneNumber));
    if (status.dcId) {
        result.flags |= TLAuthSentCode::PhoneRegistered;
    }
    sendRpcReply(result);
}

void AuthRpcOperation::runSendInvites()
{
    qWarning() << Q_FUNC_INFO << "The method is not implemented!";
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runSignIn()
{
    qDebug() << Q_FUNC_INFO;
    if (!api()->identifierIsValid(m_signIn.phoneNumber)) {
        sendRpcError(RpcError::PhoneNumberInvalid);
        return;
    }
    if (!verifyAuthCode(m_signIn.phoneNumber, m_signIn.phoneCodeHash, m_signIn.phoneCode)) {
        return;
    }
    User *user = api()->getUser(m_signIn.phoneNumber);
    if (!user->passwordHash().isEmpty()) {
        layer()->session()->setWantedUser(user);
        sendRpcError(RpcError::SessionPasswordNeeded);
        return;
    }
    user->addSession(layer()->session());

    TLAuthAuthorization result;
    qDebug() << "Result type:" << result.tlType;
    userToTlUser(user, &result.user);
    result.user.flags = TLUser::Self;
    bakeFlags(&result.user);
    sendRpcReply(result);
}

void AuthRpcOperation::runSignUp()
{
    qDebug() << Q_FUNC_INFO;
    if (!api()->identifierIsValid(m_signIn.phoneNumber)) {
        sendRpcError(RpcError::PhoneNumberInvalid);
        return;
    }

    if (!verifyAuthCode(m_signUp.phoneNumber, m_signUp.phoneCodeHash, m_signUp.phoneCode)) {
        return;
    }
    User *user = api()->addUser(m_signIn.phoneNumber);
    user->setFirstName(m_signUp.firstName);
    user->setLastName(m_signUp.lastName);
    user->addSession(layer()->session());

    TLAuthAuthorization result;
    userToTlUser(user, &result.user);
    result.user.flags = TLUser::Self;
    sendRpcReply(result);
}
// End of generated run methods

bool AuthRpcOperation::verifyAuthCode(const QString &phoneNumber, const QString &hash, const QString &code)
{
    ServerApi::AuthCodeStatus status = api()->getAuthCodeStatus(phoneNumber, hash.toLatin1(), code);
    if (status == ServerApi::AuthCodeStatus::CodeValid) {
        return true;
    }
    switch (status) {
    case ServerApi::AuthCodeStatus::PhoneInvalid:
        sendRpcError(RpcError::PhoneNumberInvalid);
        break;
    case ServerApi::AuthCodeStatus::CodeEmpty:
        sendRpcError(RpcError::PhoneCodeEmpty);
        break;
    case ServerApi::AuthCodeStatus::HashEmpty:
        sendRpcError(RpcError::PhoneCodeHashEmpty);
        break;
    case ServerApi::AuthCodeStatus::HashInvalid:
        sendRpcError(RpcError::PhoneCodeInvalid); // TODO: Check the behavior of the official server on invalid hash submission
        break;
    case ServerApi::AuthCodeStatus::CodeExpired:
        sendRpcError(RpcError::PhoneCodeExpired);
        break;
    case ServerApi::AuthCodeStatus::CodeInvalid:
        sendRpcError(RpcError::PhoneCodeInvalid);
        break;
    case ServerApi::AuthCodeStatus::CodeValid:
        Q_UNREACHABLE();
        break;
    }
    return false;
}

void AuthRpcOperation::setRunMethod(AuthRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

AuthRpcOperation::ProcessingMethod AuthRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::AuthBindTempAuthKey:
        return &AuthRpcOperation::processBindTempAuthKey;
    case TLValue::AuthCancelCode:
        return &AuthRpcOperation::processCancelCode;
    case TLValue::AuthCheckPassword:
        return &AuthRpcOperation::processCheckPassword;
    case TLValue::AuthCheckPhone:
        return &AuthRpcOperation::processCheckPhone;
    case TLValue::AuthDropTempAuthKeys:
        return &AuthRpcOperation::processDropTempAuthKeys;
    case TLValue::AuthExportAuthorization:
        return &AuthRpcOperation::processExportAuthorization;
    case TLValue::AuthImportAuthorization:
        return &AuthRpcOperation::processImportAuthorization;
    case TLValue::AuthImportBotAuthorization:
        return &AuthRpcOperation::processImportBotAuthorization;
    case TLValue::AuthLogOut:
        return &AuthRpcOperation::processLogOut;
    case TLValue::AuthRecoverPassword:
        return &AuthRpcOperation::processRecoverPassword;
    case TLValue::AuthRequestPasswordRecovery:
        return &AuthRpcOperation::processRequestPasswordRecovery;
    case TLValue::AuthResendCode:
        return &AuthRpcOperation::processResendCode;
    case TLValue::AuthResetAuthorizations:
        return &AuthRpcOperation::processResetAuthorizations;
    case TLValue::AuthSendCode:
        return &AuthRpcOperation::processSendCode;
    case TLValue::AuthSendInvites:
        return &AuthRpcOperation::processSendInvites;
    case TLValue::AuthSignIn:
        return &AuthRpcOperation::processSignIn;
    case TLValue::AuthSignUp:
        return &AuthRpcOperation::processSignUp;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *AuthOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<AuthRpcOperation>(layer, context);
}

} // Server

} // Telegram
