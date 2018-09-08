#include "DeclarativeAuthOperation.hpp"
#include "DeclarativeClient.hpp"

#include <QTimer>
#include <QDebug>

#include "Client.hpp"
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

QString DeclarativeAuthOperation::passwordHint() const
{
    return m_authOperation ? m_authOperation->passwordHint() : QString();
}

bool DeclarativeAuthOperation::hasRecovery() const
{
    return m_authOperation ? m_authOperation->hasRecovery() : false;
}

void DeclarativeAuthOperation::signIn()
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
    m_target->syncSettings();
    m_authOperation = m_target->backend()->signIn();
    m_authOperation->setPhoneNumber(phoneNumber());
    setPendingOperation(m_authOperation);
    connect(m_authOperation, &AuthOperation::phoneNumberRequired, this, &DeclarativeAuthOperation::phoneNumberRequired);
    connect(m_authOperation, &AuthOperation::authCodeRequired, this, &DeclarativeAuthOperation::authCodeRequired);
    connect(m_authOperation, &AuthOperation::passwordRequired, this, &DeclarativeAuthOperation::onPasswordRequired);
    connect(m_authOperation, &AuthOperation::passwordCheckFailed, this, &DeclarativeAuthOperation::passwordCheckFailed);

    connect(m_authOperation, &AuthOperation::passwordHintChanged, this, &DeclarativeAuthOperation::passwordHintChanged);
    connect(m_authOperation, &AuthOperation::hasRecoveryChanged, this, &DeclarativeAuthOperation::hasRecoveryChanged);

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
    m_target->syncSettings();
    m_authOperation = m_target->backend()->checkIn();
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

void DeclarativeAuthOperation::checkRegistration()
{
    return signIn();
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
    PendingOperation *op = m_authOperation->submitAuthCode(code);
    setBusy(true);
    connect(op, &PendingOperation::finished, this, &DeclarativeAuthOperation::unsetBusy);
    return true;
}

bool DeclarativeAuthOperation::submitPassword(const QString &password)
{
    if (!m_authOperation) {
        return false;
    }
    PendingOperation *op = m_authOperation->submitPassword(password);
    setBusy(true);
    connect(op, &PendingOperation::finished, this, &DeclarativeAuthOperation::unsetBusy);
    return true;
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
    setBusy(true);
    PendingOperation *op = m_authOperation->getPassword();
    connect(op, &PendingOperation::finished, this, &DeclarativeAuthOperation::unsetBusy);
    emit passwordRequired();
}

void DeclarativeAuthOperation::startEvent()
{
    m_target->syncSettings();
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
