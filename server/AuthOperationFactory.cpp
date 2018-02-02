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

#include <QLoggingCategory>

namespace Telegram {

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSendCode &function)
{
//    stream >> function.tlType;
    stream >> function.phoneNumber;
    stream >> function.smsType;
    stream >> function.apiId;
    stream >> function.apiHash;
    stream >> function.langCode;
    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLFunctions::TLAuthSendCode &function)
{
//    stream << function.tlType;
    stream << function.phoneNumber;
    stream << function.smsType;
    stream << function.apiId;
    stream << function.apiHash;
    stream << function.langCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthCheckPhone &function)
{
//    stream >> function.tlType;
    stream >> function.phoneNumber;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSignUp &function)
{
//    stream >> function.tlType;
    stream >> function.phoneNumber;
    stream >> function.phoneCodeHash;
    stream >> function.phoneCode;
    stream >> function.firstName;
    stream >> function.lastName;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthSignIn &function)
{
//    stream >> function.tlType;
    stream >> function.phoneNumber;
    stream >> function.phoneCodeHash;
    stream >> function.phoneCode;
    return stream;
}

CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthCheckPassword &function)
{
//    stream >> function.tlType;
    stream >> function.passwordHash;
    return stream;
}

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
bool AuthRpcOperation::processCheckPhone(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runCheckPhone);
    context.inputStream() >> m_checkPhone;
    qWarning() << Q_FUNC_INFO << m_checkPhone.phoneNumber;
    return true;
}

bool AuthRpcOperation::processSendCode(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSendCode);
    context.inputStream() >> m_sendCode;
    qWarning() << Q_FUNC_INFO << "identifier:" << m_sendCode.phoneNumber;
    return true;
}

bool AuthRpcOperation::processSignUp(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSignUp);
    context.inputStream() >> m_signUp;
    qWarning() << Q_FUNC_INFO << m_signUp.phoneNumber << m_signUp.firstName << m_signUp.lastName;
    return true;
}

bool AuthRpcOperation::processSignIn(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runSignIn);
    context.inputStream() >> m_signIn;
    return true;
}

bool AuthRpcOperation::processCheckPassword(RpcProcessingContext &context)
{
    setRunMethod(&AuthRpcOperation::runCheckPassword);
    context.inputStream() >> m_checkPassword;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void AuthRpcOperation::runCheckPhone()
{
    PhoneStatus status = api()->getPhoneStatus(m_checkPhone.phoneNumber);
    TLAuthCheckedPhone result;
    result.phoneRegistered = status.exists();
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
    if (status.online) {
        result.tlType = TLValue::AuthSentAppCode;
    } else {
        result.tlType = TLValue::AuthSentCode;
    }
    result.phoneCodeHash = api()->sendAppCode(m_sendCode.phoneNumber);
    result.phoneRegistered = status.dcId;
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
    layer()->setUser(user);

    TLAuthAuthorization result;
    userToTlUser(user, &result.user);
    result.user.flags = TLUser::Self;
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
    layer()->setUser(user);
    if (!user->passwordHash().isEmpty()) {
        sendRpcError(RpcError::SessionPasswordNeeded);
        return;
    }

    TLAuthAuthorization result;
    qDebug() << "Result type:" << result.tlType;
    userToTlUser(user, &result.user);
    result.user.flags = TLUser::Self;
    bakeFlags(&result.user);
    sendRpcReply(result);
}

void AuthRpcOperation::runCheckPassword()
{
    qDebug() << Q_FUNC_INFO;
    User *user = layer()->getUser();
    if (!user) {
        sendRpcError(RpcError::AuthKeyUnregistered);
        return;
    }
    const bool passwordIsCorrect = api()->checkPassword(user->phoneNumber(), m_checkPassword.passwordHash);
    if (!passwordIsCorrect) {
        sendRpcError(RpcError::PasswordHashInvalid);
        return;
    }

    TLAuthAuthorization result;
    qDebug() << "Result type:" << result.tlType;
    userToTlUser(user, &result.user);
    result.user.flags = TLUser::Self;
    bakeFlags(&result.user);
    sendRpcReply(result);
}
// End of generated run methods

bool AuthRpcOperation::verifyAuthCode(const QString &phoneNumber, const QString &hash, const QString &code)
{
    ServerApi::AuthCodeStatus status = api()->getAuthCodeStatus(phoneNumber, hash, code);
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
    case TLValue::AuthCheckPhone:
        return &AuthRpcOperation::processCheckPhone;
    case TLValue::AuthSendCode:
        return &AuthRpcOperation::processSendCode;
    case TLValue::AuthSignUp:
        return &AuthRpcOperation::processSignUp;
    case TLValue::AuthSignIn:
        return &AuthRpcOperation::processSignIn;
    case TLValue::AuthCheckPassword:
        return &AuthRpcOperation::processCheckPassword;
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
