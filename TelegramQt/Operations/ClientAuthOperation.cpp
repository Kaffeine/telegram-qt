#include "ClientAuthOperation_p.hpp"

#include "AccountStorage.hpp"
#include "CAppInformation.hpp"
#include "ConnectionApi_p.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientRpcAuthLayer.hpp"
#include "ClientRpcAccountLayer.hpp"
#include "ConnectionError.hpp"
#include "DataStorage_p.hpp"
#include "Debug_p.hpp"
#include "PendingRpcOperation.hpp"
#include "Utils.hpp"

#include "RpcError.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_loggingClientAuthOperation, "telegram.client.auth.operation", QtWarningMsg)

namespace Telegram {

namespace Client {

// Explicit templates instantiation to suppress compilation warnings
template <>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPassword *output);
template <>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthAuthorization *output);
template <>
bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAuthSentCode *output);

AuthOperationPrivate::AuthOperationPrivate(AuthOperation *parent) :
    // It is important to NOT set QObject parent,
    // because the parent is not fully constructed yet.
    QObject(nullptr),
    PendingOperationPrivate(parent)
{
}

AuthOperationPrivate *AuthOperationPrivate::get(AuthOperation *parent)
{
    return static_cast<AuthOperationPrivate*>(parent->d->toQObject());
}

const AuthOperationPrivate *AuthOperationPrivate::get(const AuthOperation *parent)
{
    return static_cast<const AuthOperationPrivate*>(parent->d->toQObject());
}

void AuthOperationPrivate::setBackend(Backend *backend)
{
    m_backend = backend;
}

void AuthOperationPrivate::setRunMethod(RunMethod method)
{
    m_runMethod = method;
}

AuthOperation::AuthOperation(QObject *parent) :
    PendingOperation(new AuthOperationPrivate(this), parent)
{
    Q_D(AuthOperation);
    d->setParent(this);
}

QString AuthOperation::phoneNumber() const
{
    Q_D(const AuthOperation);
    return d->m_phoneNumber;
}

QString AuthOperation::passwordHint() const
{
    Q_D(const AuthOperation);
    return d->m_passwordHint;
}

bool AuthOperation::hasRecovery() const
{
    Q_D(const AuthOperation);
    return d->m_hasRecovery;
}

bool AuthOperation::isRegistered() const
{
    Q_D(const AuthOperation);
    return d->m_registered;
}

void AuthOperation::setPhoneNumber(const QString &phoneNumber)
{
    Q_D(AuthOperation);
    d->m_phoneNumber = phoneNumber;
}

void AuthOperation::startImplementation()
{
    Q_D(AuthOperation);
    if (d->m_runMethod) {
        callMember<>(d, d->m_runMethod);
    }
}

void AuthOperation::abort()
{
    qCWarning(c_loggingClientAuthOperation) << CALL_INFO << "STUB";
}

void AuthOperationPrivate::checkAuthorization()
{
    Q_Q(AuthOperation);
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO;
    AccountStorage *storage = m_backend->accountStorage();
    if (!storage->hasMinimalDataSet()) {
        q->setFinishedWithTextError(QLatin1String("No minimal account data set"));
        return;
    }
    // Backend::connectToServer() automatically takes the data from the account storage,
    // So just make some RPC call to check if connection works.
    PendingRpcOperation *rpcOperation = accountLayer()->updateStatus(false);
    connect(rpcOperation, &PendingRpcOperation::finished,
            this, &AuthOperationPrivate::onAccountStatusUpdateFinished);
}

void AuthOperationPrivate::requestAuthCode()
{
    Q_Q(AuthOperation);
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO;
    const AppInformation *appInfo = m_backend->m_appInformation;
    if (!appInfo) {
        q->setFinishedWithTextError(QLatin1String("Unable to request auth code: "
                                                  "Client::appInformation() is not set"));
        return;
    }

    if (m_backend->connectionApi()->status() != ConnectionApi::StatusWaitForAuthentication) {
        qCWarning(c_loggingClientAuthOperation) << CALL_INFO << "Connection doesn't wait for authentication";
        return;
    }

    if (m_phoneNumber.isEmpty()) {
        qCDebug(c_loggingClientAuthOperation) << CALL_INFO << "Phone number required";
        emit q->phoneNumberRequired();
        return;
    }

    Connection *connection = ConnectionApiPrivate::get(m_backend->connectionApi())->getDefaultConnection();
    if (!connection) {
        q->setFinishedWithTextError(QLatin1String("Unable to get default connection!"));
        return;
    }

    AuthRpcLayer::PendingAuthSentCode *rpcOperation
            = authLayer()->sendCode(m_phoneNumber, appInfo->appId(), appInfo->appHash());
    connect(connection, &BaseConnection::errorOccured, this, &AuthOperationPrivate::onConnectionError);
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO
                                          << "requestPhoneCode"
                                          << Telegram::Utils::maskPhoneNumber(m_phoneNumber)
                                          << "on dc" << connection->dcOption().id;
    connect(rpcOperation, &PendingRpcOperation::finished,
            this, &AuthOperationPrivate::onRequestAuthCodeFinished);
}

PendingOperation *AuthOperation::submitAuthCode(const QString &code)
{
    Q_D(AuthOperation);
    return d->submitAuthCode(code);
}

PendingOperation *AuthOperationPrivate::submitAuthCode(const QString &code)
{
    if (m_authCodeHash.isEmpty()) {
        const QString text = QLatin1String("Unable to submit auth code without a code hash");
        qCWarning(c_loggingClientAuthOperation) << CALL_INFO << text;
        return PendingOperation::failOperation(text);
    }

    if (code.isEmpty()) {
        const QString text = QLatin1String("Deny to submit empty auth code");
        qCWarning(c_loggingClientAuthOperation) << CALL_INFO << text;
        return PendingOperation::failOperation(text);
    }

    QObject *parent = this;
    PendingOperation *submitOperation = new PendingOperation(parent);
    submitOperation->setOperationName("AuthOperationPrivate::submitAuthCode");
    PendingRpcOperation *sendCodeOperation = nullptr;
    if (m_registered) {
        sendCodeOperation = authLayer()->signIn(m_phoneNumber, m_authCodeHash, code);
        sendCodeOperation->connectToFinished(this, &AuthOperationPrivate::onSignInRpcFinished,
                                             sendCodeOperation, submitOperation);
    } else {
        sendCodeOperation = authLayer()->signUp(m_phoneNumber, m_authCodeHash, code, m_firstName, m_lastName);
        sendCodeOperation->connectToFinished(this, &AuthOperationPrivate::onSignUpRpcFinished,
                                             sendCodeOperation, submitOperation);
    }

    return sendCodeOperation;
}

PendingOperation *AuthOperationPrivate::getPassword()
{
    PendingRpcOperation *passwordRequest = accountLayer()->getPassword();
    connect(passwordRequest, &PendingRpcOperation::finished, this, &AuthOperationPrivate::onPasswordRequestFinished);
    return passwordRequest;
}

PendingOperation *AuthOperation::submitPassword(const QString &password)
{
    Q_D(AuthOperation);
    return d->submitPassword(password);
}

PendingOperation *AuthOperationPrivate::submitPassword(const QString &password)
{
    if (m_passwordCurrentSalt.isEmpty()) {
        const QString text = QLatin1String("Unable to submit auth password (password salt is missing)");
        return PendingOperation::failOperation(text);
    }
    const QByteArray pwdData = m_passwordCurrentSalt + password.toUtf8() + m_passwordCurrentSalt;
    const QByteArray pwdHash = Utils::sha256(pwdData);
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO << "slt:" << Utils::maskByteArray(m_passwordCurrentSalt);
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO << "pwd:" << Utils::maskByteArray(pwdHash);

    TLInputCheckPasswordSRP passwordData;

    PendingRpcOperation *sendPasswordOperation = authLayer()->checkPassword(passwordData);
    connect(sendPasswordOperation, &PendingRpcOperation::finished, this, &AuthOperationPrivate::onCheckPasswordFinished);
    return sendPasswordOperation;
}

void AuthOperation::submitPhoneNumber(const QString &phoneNumber)
{
    setPhoneNumber(phoneNumber);
    if (!isFinished()) {
        start();
    }
}

bool AuthOperation::submitName(const QString &firstName, const QString &lastName)
{
    Q_D(AuthOperation);
    d->m_firstName = firstName;
    d->m_lastName = lastName;
    return !firstName.isEmpty() && !lastName.isEmpty();
}

void AuthOperation::requestCall()
{
    qCWarning(c_loggingClientAuthOperation) << CALL_INFO << "STUB";
}

void AuthOperation::requestSms()
{
    qCWarning(c_loggingClientAuthOperation) << CALL_INFO << "STUB";
}

void AuthOperation::recovery()
{
    qCWarning(c_loggingClientAuthOperation) << CALL_INFO << "STUB";
}

void AuthOperationPrivate::setPasswordCurrentSalt(const QByteArray &salt)
{
    m_passwordCurrentSalt = salt;
}

void AuthOperationPrivate::setPasswordHint(const QString &hint)
{
    Q_Q(AuthOperation);
    if (m_passwordHint == hint) {
        return;
    }
    m_passwordHint = hint;
    emit q->passwordHintChanged(hint);
}

void AuthOperationPrivate::setRegistered(bool registered)
{
    Q_Q(AuthOperation);
    m_registered = registered;
    emit q->registeredChanged(registered);
}

AccountRpcLayer *AuthOperationPrivate::accountLayer() const
{
    return m_backend->accountLayer();
}

AuthRpcLayer *AuthOperationPrivate::authLayer() const
{
    return m_backend->authLayer();
}

AuthOperationPrivate *AuthOperation::d_func()
{
    return AuthOperationPrivate::get(this);
}

const AuthOperationPrivate *AuthOperation::d_func() const
{
    return AuthOperationPrivate::get(this);
}

void AuthOperationPrivate::onRequestAuthCodeFinished(PendingRpcOperation *rpcOperation)
{
    Q_Q(AuthOperation);
    if (rpcOperation->rpcError() && rpcOperation->rpcError()->type() == RpcError::SeeOther) {
        if (m_backend->connectionApi()->status() != ConnectionApi::StatusWaitForAuthentication) {
            qCWarning(c_loggingClientAuthOperation) << CALL_INFO << "Unexpected SeeOther";
        }
        const quint32 dcId = rpcOperation->rpcError()->argument();
        ConnectionApiPrivate *privateApi = ConnectionApiPrivate::get(m_backend->connectionApi());
        connect(privateApi->connectToDc(dcId), &PendingOperation::finished,
                this, &AuthOperationPrivate::onRedirectedConnectFinished);
        return;
    }

    if (!rpcOperation->isSucceeded()) {
        q->setDelayedFinishedWithError(rpcOperation->errorDetails());
        return;
    }
    TLAuthSentCode result;
    authLayer()->processReply(rpcOperation, &result);

    qCDebug(c_loggingClientAuthOperation) << CALL_INFO << result.tlType << result.phoneCodeHash;
    if (result.isValid()) {
        m_authCodeHash = result.phoneCodeHash;
        setRegistered(result.phoneRegistered());
        emit q->authCodeRequired();
    }
}

void AuthOperationPrivate::onAuthenticationRpcError(const RpcError *error)
{
    Q_Q(AuthOperation);
    switch (error->reason()) {
    case RpcError::SessionPasswordNeeded:
        getPassword();
        return;
    case RpcError::FirstnameInvalid:
        emit q->errorOccurred(Namespace::AuthenticationErrorFirstNameInvalid, error->message());
        break;
    case RpcError::LastnameInvalid:
        emit q->errorOccurred(Namespace::AuthenticationErrorLastNameInvalid, error->message());
        break;
    case RpcError::PhoneCodeHashEmpty:
    case RpcError::PhoneCodeEmpty:
        emit q->errorOccurred(Namespace::AuthenticationErrorUnknown, error->message());
        break;
    case RpcError::PhoneCodeInvalid:
        emit q->errorOccurred(Namespace::AuthenticationErrorPhoneCodeInvalid, error->message());
        return;
    case RpcError::PhoneCodeExpired:
        emit q->errorOccurred(Namespace::AuthenticationErrorPhoneCodeExpired, error->message());
        return;
    default:
        qCCritical(c_loggingClientAuthOperation) << CALL_INFO << "Unexpected error" << error->message();
        return;
    }
    // The errors with 'break' usually means bad request from the client
    // side and can be prevented by local requests validation.
    qCCritical(c_loggingClientAuthOperation) << CALL_INFO << "internal error?" << error->message();
}

void AuthOperationPrivate::onSignInRpcFinished(PendingRpcOperation *rpcOperation, PendingOperation *submitAuthCodeOperation)
{
    Q_Q(AuthOperation);
    if (rpcOperation->rpcError()) {
        onAuthenticationRpcError(rpcOperation->rpcError());
        const RpcError *error = rpcOperation->rpcError();
        switch (error->reason()) {
        case RpcError::SessionPasswordNeeded:
            submitAuthCodeOperation->setFinished();
            return;
        case RpcError::PhoneCodeHashEmpty:
            qCCritical(c_loggingClientAuthOperation) << CALL_INFO << "internal error?" << error->message();
            break;
        case RpcError::PhoneCodeEmpty:
            qCCritical(c_loggingClientAuthOperation) << CALL_INFO << "internal error?" << error->message();
            break;
        case RpcError::PhoneCodeInvalid:
        case RpcError::PhoneCodeExpired:
            submitAuthCodeOperation->setDelayedFinishedWithError(rpcOperation->errorDetails());
            return;
        default:
            qCCritical(c_loggingClientAuthOperation) << CALL_INFO << "Unexpected error" << error->message();
            break;
        }
    }
    if (!rpcOperation->isSucceeded()) {
        submitAuthCodeOperation->setDelayedFinishedWithError(rpcOperation->errorDetails());
        q->setDelayedFinishedWithError(rpcOperation->errorDetails());
        return;
    }
    submitAuthCodeOperation->setFinished();

    TLAuthAuthorization result;
    authLayer()->processReply(rpcOperation, &result);
    onGotAuthorization(rpcOperation, result);
}

void AuthOperationPrivate::onSignUpRpcFinished(PendingRpcOperation *rpcOperation, PendingOperation *submitAuthCodeOperation)
{
    Q_Q(AuthOperation);
    if (rpcOperation->rpcError()) {
        onAuthenticationRpcError(rpcOperation->rpcError());
        const RpcError *error = rpcOperation->rpcError();
        switch (error->reason()) {
        case RpcError::FirstnameInvalid:
        case RpcError::LastnameInvalid:
        case RpcError::PhoneCodeInvalid:
        case RpcError::PhoneCodeExpired:
            submitAuthCodeOperation->setDelayedFinishedWithError(rpcOperation->errorDetails());
            return;
        case RpcError::SessionPasswordNeeded:
        default:
            qCCritical(c_loggingClientAuthOperation) << CALL_INFO << "Unexpected error" << error->message();
            break;
        }
    }
    if (!rpcOperation->isSucceeded()) {
        submitAuthCodeOperation->setDelayedFinishedWithError(rpcOperation->errorDetails());
        q->setDelayedFinishedWithError(rpcOperation->errorDetails());
        return;
    }
    submitAuthCodeOperation->setFinished();

    TLAuthAuthorization result;
    authLayer()->processReply(rpcOperation, &result);
    onGotAuthorization(rpcOperation, result);
}

void AuthOperationPrivate::onPasswordRequestFinished(PendingRpcOperation *operation)
{
    Q_Q(AuthOperation);
    if (!operation->isSucceeded()) {
        q->setDelayedFinishedWithError(operation->errorDetails());
        return;
    }

    TLAccountPassword result;
    authLayer()->processReply(operation, &result);
#ifdef DEVELOPER_BUILD
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO << result;
#endif
#if TELEGRAMQT_LAYER >= 86
    // result.srpB
#else
    setPasswordCurrentSalt(result.currentSalt);
#endif
    setPasswordHint(result.hint);
    emit q->passwordRequired();
}

void AuthOperationPrivate::onCheckPasswordFinished(PendingRpcOperation *operation)
{
    Q_Q(AuthOperation);
    if (operation->rpcError()) {
        const RpcError *error = operation->rpcError();
        if (error->reason() == RpcError::PasswordHashInvalid) {
            emit q->passwordCheckFailed();
            return;
        }
        qCDebug(c_loggingClientAuthOperation) << CALL_INFO << error->message();
    }

    if (!operation->isSucceeded()) {
        q->setDelayedFinishedWithError(operation->errorDetails());
        return;
    }

    TLAuthAuthorization result;
    authLayer()->processReply(operation, &result);
    onGotAuthorization(operation, result);
}

void AuthOperationPrivate::onGotAuthorization(PendingRpcOperation *operation, const TLAuthAuthorization &authorization)
{
    Q_Q(AuthOperation);
    qCDebug(c_loggingClientAuthOperation) << authorization.user.phone
                                          << authorization.user.firstName
                                          << authorization.user.lastName;
    AccountStorage *storage = m_backend->accountStorage();
    storage->setPhoneNumber(authorization.user.phone);
    if (storage->accountIdentifier().isEmpty()) {
        storage->setAccountIdentifier(authorization.user.phone);
    }
    DataInternalApi::get(m_backend->dataStorage())->processData(authorization.user);
    m_authenticatedConnection = Connection::fromOperation(operation);
    m_authenticatedConnection->setStatus(BaseConnection::Status::Signed, BaseConnection::StatusReason::Remote);
    q->setFinished();
}

void AuthOperationPrivate::onAccountStatusUpdateFinished(PendingRpcOperation *operation)
{
    Q_Q(AuthOperation);
    if (!operation->isSucceeded()) {
        q->setFinishedWithError(operation->errorDetails());
        return;
    }
    m_authenticatedConnection = Connection::fromOperation(operation);
    m_authenticatedConnection->setStatus(BaseConnection::Status::Signed, BaseConnection::StatusReason::Local);
    q->setFinished();
}

void AuthOperationPrivate::onConnectionError(const QByteArray &errorBytes)
{
    const ConnectionError error(errorBytes);
    Q_Q(AuthOperation);
    if (q->isFinished()) {
        qCDebug(c_loggingClientAuthOperation) << CALL_INFO << "Connection error on finished auth operation:" << error.description();
        return;
    }
    q->setFinishedWithTextError(error.description());
}

void AuthOperationPrivate::onRedirectedConnectFinished(PendingOperation *operation)
{
    qCDebug(c_loggingClientAuthOperation) << CALL_INFO << operation->errorDetails();
    if (operation->isFailed()) {
        return;
    }
    requestAuthCode();
}

} // Client

} // Telegram namespace
