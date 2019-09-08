#include "DeclarativeAuthOperation.hpp"

#include <QTimer>
#include <QDebug>

#include "Client.hpp"
#include "ConnectionApi.hpp"
#include "Operations/ClientAuthOperation.hpp"

namespace Telegram {

using namespace Client;

DeclarativeAuthOperation::DeclarativeAuthOperation(QObject *parent) :
    DeclarativeOperation(parent)
{
}

bool DeclarativeAuthOperation::isBusy() const
{
    return m_busy;
}

DeclarativeAuthOperation::AuthStatus DeclarativeAuthOperation::status() const
{
    return m_status;
}

QString DeclarativeAuthOperation::phoneNumber() const
{
    return m_phoneNumber;
}

bool DeclarativeAuthOperation::isRegistered() const
{
    return m_authOperation ? m_authOperation->isRegistered() : false;
}

QString DeclarativeAuthOperation::passwordHint() const
{
    return m_authOperation ? m_authOperation->passwordHint() : QString();
}

bool DeclarativeAuthOperation::hasRecovery() const
{
    return m_authOperation ? m_authOperation->hasRecovery() : false;
}

void DeclarativeAuthOperation::startAuthentication()
{
    if (m_authOperation) {
        if (m_authOperation->isFinished()) {
            m_authOperation->deleteLater();
            m_authOperation = nullptr;
        } else {
            qWarning() << Q_FUNC_INFO << "Another operation is in progress";
            return;
        }
    }
    if (!syncSettings()) {
        // SyncSettings will put own debug on this
        return;
    }

    m_authOperation = client()->connectionApi()->startAuthentication();
    m_authOperation->setPhoneNumber(phoneNumber());
    setPendingOperation(m_authOperation);

    // Signals propagation
    connect(m_authOperation, &AuthOperation::errorOccurred, this, &DeclarativeAuthOperation::errorOccurred);
    connect(m_authOperation, &AuthOperation::phoneNumberRequired, this, &DeclarativeAuthOperation::phoneNumberRequired);
    connect(m_authOperation, &AuthOperation::registeredChanged, this, &DeclarativeAuthOperation::registeredChanged);
    connect(m_authOperation, &AuthOperation::authCodeRequired, this, &DeclarativeAuthOperation::authCodeRequired);
    connect(m_authOperation, &AuthOperation::passwordRequired, this, &DeclarativeAuthOperation::onPasswordRequired);
    connect(m_authOperation, &AuthOperation::passwordCheckFailed, this, &DeclarativeAuthOperation::onPasswordCheckFailed);

    connect(m_authOperation, &AuthOperation::passwordHintChanged, this, &DeclarativeAuthOperation::passwordHintChanged);
    connect(m_authOperation, &AuthOperation::hasRecoveryChanged, this, &DeclarativeAuthOperation::hasRecoveryChanged);

    // Some method calls
    connect(m_authOperation, &AuthOperation::errorOccurred, this, &DeclarativeAuthOperation::unsetBusy);

    connect(m_authOperation, &AuthOperation::phoneNumberRequired, this, [this]() {
        this->setStatus(DeclarativeAuthOperation::PhoneNumberRequired);
    });
    connect(m_authOperation, &AuthOperation::authCodeRequired, this, [this]() {
        this->setStatus(DeclarativeAuthOperation::AuthCodeRequired);
    });
    connect(m_authOperation, &AuthOperation::passwordRequired, this, [this]() {
        this->setStatus(DeclarativeAuthOperation::PasswordRequired);
    });
    connect(m_authOperation, &PendingOperation::finished, this, [this](PendingOperation *op) {
        if (op->isSucceeded()) {
            this->setStatus(DeclarativeAuthOperation::SignedIn);
        } else {
            this->setStatus(DeclarativeAuthOperation::Idle);
        }
        emit this->signInFinished(op->isSucceeded());
    });
    start();
}

void DeclarativeAuthOperation::checkIn()
{
    if (m_authOperation) {
        if (m_authOperation->isFinished()) {
            m_authOperation->deleteLater();
            m_authOperation = nullptr;
        } else {
            qWarning() << Q_FUNC_INFO << "Another operation is in progress";
            return;
        }
    }
    syncSettings();
    m_authOperation = client()->connectionApi()->checkIn();
    setPendingOperation(m_authOperation);
    connect(m_authOperation, &PendingOperation::finished, this, [this](PendingOperation *op) {
        if (op->isSucceeded()) {
            this->setStatus(DeclarativeAuthOperation::SignedIn);
        } else {
            this->setStatus(DeclarativeAuthOperation::Idle);
        }
        emit this->checkInFinished(op->isSucceeded());
    });
    start();
}

void DeclarativeAuthOperation::abort()
{
    m_authOperation->abort();
}

void DeclarativeAuthOperation::submitPhoneNumber(const QString &phoneNumber)
{
    m_authOperation->submitPhoneNumber(phoneNumber);
    setPhoneNumber(phoneNumber);
}

bool DeclarativeAuthOperation::submitAuthCode(const QString &code)
{
    if (!m_authOperation) {
        return false;
    }
    m_authOperation->submitAuthCode(code);
    setBusy(true);
    // Unset busy on one of authCodeCheckFailed or passwordRequired or signedIn.
    return true;
}

bool DeclarativeAuthOperation::submitPassword(const QString &password)
{
    if (!m_authOperation) {
        return false;
    }
    m_authOperation->submitPassword(password);
    setBusy(true);
    // Unset busy on one of passwordCheckFailed or signedIn.
    return true;
}

bool DeclarativeAuthOperation::submitName(const QString &firstName, const QString &lastName)
{
    if (!m_authOperation) {
        return false;
    }
    return m_authOperation->submitName(firstName, lastName);
}

void DeclarativeAuthOperation::setPhoneNumber(const QString &phoneNumber)
{
    if (m_phoneNumber == phoneNumber) {
        return;
    }
    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged();
}

bool DeclarativeAuthOperation::recovery()
{
    if (!m_authOperation || !m_authOperation->hasRecovery()) {
        return false;
    }
    m_authOperation->recovery();
    setBusy(true);
    return true;
}

void DeclarativeAuthOperation::setStatus(const AuthStatus status)
{
    qWarning() << Q_FUNC_INFO << status;
    if (m_status == status) {
        return;
    }
    m_status = status;
    emit statusChanged(status);
}

void DeclarativeAuthOperation::setBusy(bool busy)
{
    if (m_busy == busy) {
        return;
    }
    m_busy = busy;
    emit busyChanged(busy);
}

void DeclarativeAuthOperation::unsetBusy()
{
    setBusy(false);
}

void DeclarativeAuthOperation::onPasswordRequired()
{
    unsetBusy();
    emit passwordRequired();
}

void DeclarativeAuthOperation::onPasswordCheckFailed()
{
    unsetBusy();
    emit passwordCheckFailed();
}

void DeclarativeAuthOperation::startEvent()
{
    syncSettings();
}

bool DeclarativeAuthOperation::requestCall()
{
    if (!m_authOperation) {
        return false;
    }
    m_authOperation->requestCall();
    return true;
}

bool DeclarativeAuthOperation::requestSms()
{
    if (!m_authOperation) {
        return false;
    }
    m_authOperation->requestSms();
    return true;
}

} // Telegram
