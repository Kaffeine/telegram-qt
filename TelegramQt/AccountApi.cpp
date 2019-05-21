#include "AccountApi_p.hpp"

#include "ClientBackend.hpp"
#include "PendingOperationWithResult.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcAccountApi, "telegram.client.api.account", QtInfoMsg)

namespace Telegram {

namespace Client {

AccountApiPrivate::AccountApiPrivate(AccountApi *parent) :
    ClientApiPrivate(parent)
{
}

AccountApiPrivate *AccountApiPrivate::get(AccountApi *parent)
{
    return static_cast<AccountApiPrivate*>(parent->d);
}

PendingBoolOperation *AccountApiPrivate::checkUsernameAvailability(const QString &newUsername)
{
    PendingBoolOperation *operation = new PendingBoolOperation(this);
    operation->setOperationName("AccountApi::checkUsername");
    AccountRpcLayer::PendingBool *rpcOperation = m_backend->accountLayer()->checkUsername(newUsername);
    rpcOperation->connectToFinished(this, &AccountApiPrivate::onCheckUsernameFinished, operation, rpcOperation);
    return operation;
}

PendingOperation *AccountApiPrivate::updateUsername(const QString &newUsername)
{
    return nullptr;
}

void AccountApiPrivate::onCheckUsernameFinished(PendingBoolOperation *operation, AccountRpcLayer::PendingBool *rpcOperation)
{
    TLBool result;
    rpcOperation->getResult(&result);
    //operation->setFinished(result);
}

/*!
    \class Telegram::Client::AccountApi
    \brief Provides API to work with the user account.

    \inmodule TelegramQt
    \ingroup Client
 */
AccountApi::AccountApi(QObject *parent) :
    ClientApi(parent)
{
    d = new AccountApiPrivate(this);
}

PendingBoolOperation *AccountApi::checkUsernameAvailability(const QString &newUsername)
{
    Q_D(AccountApi);
    return d->checkUsernameAvailability(newUsername);
}

PendingOperation *AccountApi::updateUsername(const QString &newUsername)
{
    Q_D(AccountApi);
    return d->updateUsername(newUsername);
}

} // Client namespace

} // Telegram namespace
