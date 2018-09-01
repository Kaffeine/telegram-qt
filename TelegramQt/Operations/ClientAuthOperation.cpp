#include "ClientAuthOperation.hpp"

#include "CAppInformation.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientRpcAuthLayer.hpp"
#include "ClientRpcAccountLayer.hpp"
#include "PendingRpcOperation.hpp"
#include "Utils.hpp"

#include "RpcError.hpp"

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

// Explicit templates instantiation to suppress compilation warnings
template <>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPassword *output);
template <>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthAuthorization *output);
template <>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthSentCode *output);

AuthOperation::AuthOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void AuthOperation::setBackend(Backend *backend)
{
    m_backend = backend;
}

void AuthOperation::setRunMethod(AuthOperation::RunMethod method)
{
    m_runMethod = method;
}

void AuthOperation::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

void AuthOperation::start()
{
    if (m_runMethod) {
        callMember<>(this, m_runMethod);
    }
}

void AuthOperation::abort()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

PendingOperation *AuthOperation::requestAuthCode()
{
    const CAppInformation *appInfo = m_backend->m_appInformation;
    if (!appInfo) {
        const QString text = QStringLiteral("Unable to request auth code, because the application information is not set");
        return PendingOperation::failOperation({{QStringLiteral("text"), text}});
    }

    PendingRpcOperation *requestCodeOperation = m_backend->authLayer()->sendCode(phoneNumber(), appInfo->appId(), appInfo->appHash());
    qDebug() << Q_FUNC_INFO << "requestPhoneCode" << Telegram::Utils::maskPhoneNumber(phoneNumber())
             << "on dc" << Connection::fromOperation(requestCodeOperation)->dcOption().id;
    connect(requestCodeOperation, &PendingRpcOperation::finished, this, &AuthOperation::onRequestAuthCodeFinished);
    return requestCodeOperation;
}

PendingOperation *AuthOperation::submitAuthCode(const QString &code)
{
    if (m_authCodeHash.isEmpty()) {
        const QString text = QStringLiteral("Unable to submit auth code without a code hash");
        qWarning() << Q_FUNC_INFO << text;
        return PendingOperation::failOperation({{QStringLiteral("text"), text}});
    }

    PendingRpcOperation *sendCodeOperation = authLayer()->signIn(phoneNumber(), m_authCodeHash, code);
    connect(sendCodeOperation, &PendingRpcOperation::finished, this, &AuthOperation::onSignInFinished);
    return sendCodeOperation;
}

PendingOperation *AuthOperation::getPassword()
{
    PendingRpcOperation *passwordRequest = accountLayer()->getPassword();
    connect(passwordRequest, &PendingRpcOperation::finished, this, &AuthOperation::onPasswordRequestFinished);
    return passwordRequest;
}

PendingOperation *AuthOperation::submitPassword(const QString &password)
{
    if (m_passwordCurrentSalt.isEmpty()) {
        const QString text = QStringLiteral("Unable to submit auth password (password salt is missing)");
        return PendingOperation::failOperation({{QStringLiteral("text"), text}});
    }
    const QByteArray pwdData = m_passwordCurrentSalt + password.toUtf8() + m_passwordCurrentSalt;
    const QByteArray pwdHash = Utils::sha256(pwdData);
    qDebug() << Q_FUNC_INFO << "slt:" << m_passwordCurrentSalt.toHex();
    qDebug() << Q_FUNC_INFO << "pwd:" << pwdHash.toHex();

    PendingRpcOperation *sendPasswordOperation = authLayer()->checkPassword(pwdHash);
    connect(sendPasswordOperation, &PendingRpcOperation::finished, this, &AuthOperation::onCheckPasswordFinished);
    return sendPasswordOperation;
}

void AuthOperation::requestCall()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

void AuthOperation::requestSms()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

void AuthOperation::recovery()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

void AuthOperation::setWantedDc(quint32 dcId)
{
    m_backend->setDcForLayer(ConnectionSpec(dcId), authLayer());
    m_backend->setDcForLayer(ConnectionSpec(dcId), accountLayer());
}

void AuthOperation::setPasswordCurrentSalt(const QByteArray &salt)
{
    m_passwordCurrentSalt = salt;
}

void AuthOperation::setPasswordHint(const QString &hint)
{
    if (m_passwordHint == hint) {
        return;
    }
    m_passwordHint = hint;
    emit passwordHintChanged(hint);
}

AccountRpcLayer *AuthOperation::accountLayer() const
{
    return m_backend->accountLayer();
}

AuthRpcLayer *AuthOperation::authLayer() const
{
    return m_backend->authLayer();
}

void AuthOperation::onRequestAuthCodeFinished(PendingRpcOperation *operation)
{
    if (operation->rpcError() && operation->rpcError()->type == RpcError::SeeOther) {
        setWantedDc(operation->rpcError()->argument);
        m_backend->processSeeOthers(operation);
        return;
    }

    if (!operation->isSucceeded()) {
        setDelayedFinishedWithError(operation->errorDetails());
        return;
    }
    TLAuthSentCode result;
    authLayer()->processReply(operation, &result);
    qDebug() << Q_FUNC_INFO << result.tlType << result.phoneCodeHash;
    if (result.isValid()) {
        m_authCodeHash = result.phoneCodeHash;
        emit authCodeRequired();
    }
}

void AuthOperation::onSignInFinished(PendingRpcOperation *operation)
{
    if (operation->rpcError()) {
        const RpcError *error = operation->rpcError();
        if (error->reason == RpcError::SessionPasswordNeeded) {
            emit passwordRequired();
            return;
        }
    }
    if (!operation->isSucceeded()) {
        setDelayedFinishedWithError(operation->errorDetails());
        return;
    }

    TLAuthAuthorization result;
    authLayer()->processReply(operation, &result);
    onGotAuthorization(operation, result);
}

void AuthOperation::onPasswordRequestFinished(PendingRpcOperation *operation)
{
    if (!operation->isSucceeded()) {
        setDelayedFinishedWithError(operation->errorDetails());
        return;
    }

    TLAccountPassword result;
    authLayer()->processReply(operation, &result);
    qDebug() << Q_FUNC_INFO << "Password data:" << result.currentSalt << result.newSalt << result.hasRecovery << result.hint;
    setPasswordCurrentSalt(result.currentSalt);
    setPasswordHint(result.hint);
}

void AuthOperation::onCheckPasswordFinished(PendingRpcOperation *operation)
{
    if (operation->rpcError()) {
        const RpcError *error = operation->rpcError();
        if (error->reason == RpcError::PasswordHashInvalid) {
            emit passwordCheckFailed();
            return;
        }
    }

    if (!operation->isSucceeded()) {
        setDelayedFinishedWithError(operation->errorDetails());
        return;
    }

    TLAuthAuthorization result;
    authLayer()->processReply(operation, &result);
    onGotAuthorization(operation, result);
}

void AuthOperation::onGotAuthorization(PendingRpcOperation *operation, const TLAuthAuthorization &authorization)
{
    qDebug() << authorization.user.phone << authorization.user.firstName << authorization.user.lastName;
    m_backend->setMainConnection(Connection::fromOperation(operation));
    setFinished();
}

} // Client

} // Telegram namespace
