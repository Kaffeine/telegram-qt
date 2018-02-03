#include "PendingOperation.hpp"

#include "CTelegramStream.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientRpcAuthLayer.hpp"
#include "ClientRpcAccountLayer.hpp"
#include "Utils.hpp"

#include <QDebug>
#include <QTimer>

#include "TLFunctions.hpp"
#include "RpcError.hpp"

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

namespace Telegram {

PendingOperation::PendingOperation(QObject *parent) :
    QObject(parent),
    m_finished(false),
    m_succeeded(true)
{
}

bool PendingOperation::isFinished() const
{
    return m_finished;
}

bool PendingOperation::isSucceeded() const
{
    return m_finished && m_succeeded;
}

QVariantHash PendingOperation::errorDetails() const
{
    return m_errorDetails;
}

void PendingOperation::startLater()
{
    QMetaObject::invokeMethod(this, "start", Qt::QueuedConnection);
}

void PendingOperation::runAfter(PendingOperation *operation)
{
    connect(operation, &PendingOperation::succeeded, this, &PendingOperation::start);
    connect(operation, &PendingOperation::failed, this, &PendingOperation::onPreviousFailed);
}

void PendingOperation::setFinished()
{
    qDebug() << "finished" << this;
    if (m_finished) {
        qWarning() << "Operation is already finished" << this;
        return;
    }
    m_finished = true;
    if (m_succeeded) {
        emit succeeded(this);
    }
    emit finished(this);
}

void PendingOperation::setFinishedWithError(const QVariantHash &details)
{
    qDebug() << "finished with error" << this << details;
    m_succeeded = false;
    m_errorDetails = details;
    emit failed(this, details);
    setFinished();
}

void PendingOperation::setDelayedFinishedWithError(const QVariantHash &details)
{
    QMetaObject::invokeMethod(this, "setFinishedWithError", Qt::QueuedConnection, Q_ARG(QVariantHash, details)); // Invoke after return
}

void PendingOperation::onPreviousFailed(PendingOperation *operation, const QVariantHash &details)
{
    Q_UNUSED(operation)
    setFinishedWithError(details);
}

PendingRpcOperation::PendingRpcOperation(const QByteArray &requestData, QObject *parent) :
    PendingOperation(parent),
    m_requestData(requestData)
{
    connect(this, &PendingOperation::finished, [this]() { emit PendingRpcOperation::finished(this); });
}

PendingRpcOperation::~PendingRpcOperation()
{
    if (m_error) {
        delete m_error;
    }
}

void PendingRpcOperation::setFinishedWithReplyData(const QByteArray &data)
{
    m_replyData = data;
    TLValue answerValue = TLValue::firstFromArray(data);
    if (answerValue == TLValue::RpcError) {
        if (!m_error) {
            m_error = new RpcError();
        }
        CRawStreamEx stream(data);
        stream >> *m_error;
        setFinishedWithError({
                                 {QStringLiteral("RpcErrorCode"), m_error->type },
                                 {QStringLiteral("RpcError"), m_error->message }
                             });
    } else {
        setFinished();
    }
}

namespace Client {

PendingAuthOperation::PendingAuthOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void PendingAuthOperation::setBackend(Backend *backend)
{
    m_backend = backend;
}

void PendingAuthOperation::setRunMethod(PendingAuthOperation::RunMethod method)
{
    m_runMethod = method;
}

void PendingAuthOperation::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

void PendingAuthOperation::start()
{
    if (m_runMethod) {
        callMember<>(this, m_runMethod);
    }
}

//void PendingAuthOperation::processAuthSendCodeReply()
//{
//    qDebug() << "On auth send code answer:";
//    CTelegramStream stream(replyData());
//    TLAuthSentCode result;
//    stream >> result;
//    qDebug() << result.tlType.toString() << result.phoneCodeHash << result.phoneRegistered;
//}

void PendingAuthOperation::abort()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

PendingOperation *PendingAuthOperation::requestAuthCode()
{
    RpcLayer *layer = m_backend->mainConnection()->rpcLayer();
    const CAppInformation *appInfo = layer->appInformation();
    if (!appInfo) {
        const QString text = QStringLiteral("Unable to request auth code, because the application information is not set");
        return PendingOperation::failOperation({{QStringLiteral("text"), text}});
    }
    qDebug() << Q_FUNC_INFO << "requestPhoneCode" << Telegram::Utils::maskPhoneNumber(phoneNumber())
             << "on dc" << m_backend->mainConnection()->dcOption().id;

    PendingRpcOperation *requestCodeOperation = authLayer()->sendCode(phoneNumber(), appInfo->appId(), appInfo->appHash());
    connect(requestCodeOperation, &PendingRpcOperation::finished, this, &PendingAuthOperation::onRequestAuthCodeFinished);
    return requestCodeOperation;
}

PendingOperation *PendingAuthOperation::submitAuthCode(const QString &code)
{
    if (m_authCodeHash.isEmpty()) {
        const QString text = QStringLiteral("Unable to submit auth code without a code hash");
        qWarning() << Q_FUNC_INFO << text;
        return PendingOperation::failOperation({{QStringLiteral("text"), text}});
    }

    PendingRpcOperation *sendCodeOperation = authLayer()->signIn(phoneNumber(), m_authCodeHash, code);
    connect(sendCodeOperation, &PendingRpcOperation::finished, this, &PendingAuthOperation::onSignInFinished);
    return sendCodeOperation;
}

PendingOperation *PendingAuthOperation::getPassword()
{
    PendingRpcOperation *passwordRequest = accountLayer()->getPassword();
    connect(passwordRequest, &PendingRpcOperation::finished, this, &PendingAuthOperation::onPasswordRequestFinished);
    return passwordRequest;
}

PendingOperation *PendingAuthOperation::submitPassword(const QString &password)
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
    connect(sendPasswordOperation, &PendingRpcOperation::finished, this, &PendingAuthOperation::onCheckPasswordFinished);
    return sendPasswordOperation;
}

void PendingAuthOperation::requestCall()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

void PendingAuthOperation::requestSms()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

void PendingAuthOperation::recovery()
{
    qWarning() << Q_FUNC_INFO << "STUB";
}

void PendingAuthOperation::setPasswordCurrentSalt(const QByteArray &salt)
{
    m_passwordCurrentSalt = salt;
}

void PendingAuthOperation::setPasswordHint(const QString &hint)
{
    if (m_passwordHint == hint) {
        return;
    }
    m_passwordHint = hint;
    emit passwordHintChanged(hint);
}

AccountRpcLayer *PendingAuthOperation::accountLayer() const
{
    return m_backend->rpcLayer()->account();
}

AuthRpcLayer *PendingAuthOperation::authLayer() const
{
    return m_backend->rpcLayer()->auth();
}

void PendingAuthOperation::onRequestAuthCodeFinished(PendingRpcOperation *operation)
{
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

void PendingAuthOperation::onSignInFinished(PendingRpcOperation *operation)
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
    qDebug() << result.user.phone << result.user.firstName << result.user.lastName;
    setFinished();
}

void PendingAuthOperation::onPasswordRequestFinished(PendingRpcOperation *operation)
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

void PendingAuthOperation::onCheckPasswordFinished(PendingRpcOperation *operation)
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
    qDebug() << result.user.phone << result.user.firstName << result.user.lastName;
    setFinished();
}

} // Client

}
