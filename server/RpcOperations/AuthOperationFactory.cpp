#include "AuthOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"

// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "AuthorizationProvider.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"
#include "Utils.hpp"

#include "CTelegramStreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_serverAuthRpcCategory, "telegram.server.rpc.auth", QtWarningMsg)

namespace Telegram {

namespace Server {

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
    if (processNotImplementedMethod(TLValue::AuthBindTempAuthKey)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runCancelCode()
{
    if (processNotImplementedMethod(TLValue::AuthCancelCode)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runCheckPassword()
{
    qCDebug(c_serverAuthRpcCategory) << Q_FUNC_INFO;
    Session *session = layer()->session();
    if (!session || !session->wanterUser()) {
        sendRpcError(RpcError::AuthKeyUnregistered);
        return;
    }
    LocalUser *user = session->wanterUser();
    const bool passwordIsCorrect = api()->checkPassword(user->phoneNumber(), m_checkPassword.passwordHash);
    if (!passwordIsCorrect) {
        sendRpcError(RpcError::PasswordHashInvalid);
        return;
    }
    user->addSession(session);

    TLAuthAuthorization result;
    qCDebug(c_serverAuthRpcCategory) << "Result type:" << result.tlType;
    api()->setupTLUser(&result.user, user, user);
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
    if (processNotImplementedMethod(TLValue::AuthDropTempAuthKeys)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runExportAuthorization()
{
    if (processNotImplementedMethod(TLValue::AuthExportAuthorization)) {
        return;
    }
    TLAuthExportedAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runImportAuthorization()
{
    if (processNotImplementedMethod(TLValue::AuthImportAuthorization)) {
        return;
    }
    TLAuthAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runImportBotAuthorization()
{
    if (processNotImplementedMethod(TLValue::AuthImportBotAuthorization)) {
        return;
    }
    TLAuthAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runLogOut()
{
    if (processNotImplementedMethod(TLValue::AuthLogOut)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runRecoverPassword()
{
    if (processNotImplementedMethod(TLValue::AuthRecoverPassword)) {
        return;
    }
    TLAuthAuthorization result;
    sendRpcReply(result);
}

void AuthRpcOperation::runRequestPasswordRecovery()
{
    if (processNotImplementedMethod(TLValue::AuthRequestPasswordRecovery)) {
        return;
    }
    TLAuthPasswordRecovery result;
    sendRpcReply(result);
}

void AuthRpcOperation::runResendCode()
{
    if (processNotImplementedMethod(TLValue::AuthResendCode)) {
        return;
    }
    TLAuthSentCode result;
    sendRpcReply(result);
}

void AuthRpcOperation::runResetAuthorizations()
{
    if (processNotImplementedMethod(TLValue::AuthResetAuthorizations)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runSendCode()
{
    qCDebug(c_serverAuthRpcCategory) << Q_FUNC_INFO;

    if (!api()->identifierIsValid(m_sendCode.phoneNumber)) {
        sendRpcError(RpcError::PhoneNumberInvalid);
        return;
    }
    PhoneStatus status = api()->getPhoneStatus(m_sendCode.phoneNumber);
    if (status.exists() && (status.dcId != api()->dcId())) {
        RpcError error(RpcError::PhoneMigrateX, status.dcId);
        sendRpcError(error);
        return;
    }

    Authorization::Provider *provider = api()->getAuthorizationProvider();
    const Authorization::SentCodeInfo code = provider->sendCode(layer()->session(), m_sendCode.phoneNumber);

    TLAuthSentCode result;
    {
        TLAuthSentCodeType codeType;
        switch (code.type) {
        case Authorization::Code::Type::App:
            codeType.tlType = TLValue::AuthSentCodeTypeApp;
            codeType.length = code.length;
            break;
        case Authorization::Code::Type::Default:
        case Authorization::Code::Type::Sms:
            codeType.tlType = TLValue::AuthSentCodeTypeSms;
            codeType.length = code.length;
            break;
        case Authorization::Code::Type::Call:
            codeType.tlType = TLValue::AuthSentCodeTypeCall;
            codeType.length = code.length;
            break;
        case Authorization::Code::Type::FlashCall:
            codeType.tlType = TLValue::AuthSentCodeTypeFlashCall;
            codeType.pattern = code.pattern;
            break;
#ifdef MTPROTO_FORK
        case Authorization::Code::Type::NotNeeded:
        case Authorization::Code::Type::Denied:
            qCritical() << Q_FUNC_INFO << "Not implemented";
            break;
#endif
        }
        result.type = codeType;
    }

    result.phoneCodeHash = QString::fromLatin1(code.hash);
    if (status.exists()) {
        result.flags |= TLAuthSentCode::PhoneRegistered;
    }
    sendRpcReply(result);
}

void AuthRpcOperation::runSendInvites()
{
    if (processNotImplementedMethod(TLValue::AuthSendInvites)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void AuthRpcOperation::runSignIn()
{
    qCDebug(c_serverAuthRpcCategory) << Q_FUNC_INFO;
    if (!api()->identifierIsValid(m_signIn.phoneNumber)) {
        sendRpcError(RpcError::PhoneNumberInvalid);
        return;
    }
    if (!verifyAuthCode(m_signIn.phoneNumber, m_signIn.phoneCodeHash, m_signIn.phoneCode)) {
        return;
    }

    PhoneStatus status = api()->getPhoneStatus(m_signIn.phoneNumber);
    if (status.exists() && (status.dcId != api()->dcId())) {
        RpcError error(RpcError::PhoneMigrateX, status.dcId);
        sendRpcError(error);
        return;
    }

    LocalUser *user = api()->getUser(m_signIn.phoneNumber);
    if (!user) {
        sendRpcError(RpcError::PhoneNumberUnoccupied);
        return;
    }
    if (!user->passwordHash().isEmpty()) {
        layer()->session()->setWantedUser(user);
        sendRpcError(RpcError::SessionPasswordNeeded);
        return;
    }
    user->addSession(layer()->session());

    TLAuthAuthorization result;
    api()->setupTLUser(&result.user, user, user);
    sendRpcReply(result);
}

void AuthRpcOperation::runSignUp()
{
    qCDebug(c_serverAuthRpcCategory) << Q_FUNC_INFO;
    if (!api()->identifierIsValid(m_signUp.phoneNumber)) {
        sendRpcError(RpcError::PhoneNumberInvalid);
        return;
    }

    if (m_signUp.firstName.isEmpty()) {
        sendRpcError(RpcError::FirstnameInvalid);
        return;
    }
    if (m_signUp.lastName.isEmpty()) {
        sendRpcError(RpcError::LastnameInvalid);
        return;
    }

    if (!verifyAuthCode(m_signUp.phoneNumber, m_signUp.phoneCodeHash, m_signUp.phoneCode)) {
        return;
    }
    LocalUser *user = api()->addUser(m_signUp.phoneNumber);
    user->setFirstName(m_signUp.firstName);
    user->setLastName(m_signUp.lastName);
    user->addSession(layer()->session());

    TLAuthAuthorization result;
    api()->setupTLUser(&result.user, user, user);
    sendRpcReply(result);
}
// End of generated run methods

bool AuthRpcOperation::verifyAuthCode(const QString &phoneNumber, const QString &hash, const QString &code)
{
    Authorization::Provider *provider = api()->getAuthorizationProvider();
    Authorization::CodeStatus status = provider->getCodeStatus(phoneNumber, hash.toLatin1(), code);
    if (status == Authorization::CodeStatus::CodeValid) {
        return true;
    }
    switch (status) {
    case Authorization::CodeStatus::PhoneInvalid:
        sendRpcError(RpcError::PhoneNumberInvalid);
        break;
    case Authorization::CodeStatus::CodeEmpty:
        sendRpcError(RpcError::PhoneCodeEmpty);
        break;
    case Authorization::CodeStatus::HashEmpty:
        sendRpcError(RpcError::PhoneCodeHashEmpty);
        break;
    case Authorization::CodeStatus::HashInvalid:
        sendRpcError(RpcError::PhoneCodeInvalid); // TODO: Check the behavior of the official server on invalid hash submission
        break;
    case Authorization::CodeStatus::CodeExpired:
        sendRpcError(RpcError::PhoneCodeExpired);
        break;
    case Authorization::CodeStatus::CodeInvalid:
        sendRpcError(RpcError::PhoneCodeInvalid);
        break;
    case Authorization::CodeStatus::CodeValid:
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

} // Server namespace

} // Telegram namespace
