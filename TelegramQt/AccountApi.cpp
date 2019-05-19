#include "AccountApi_p.hpp"

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
    return nullptr;
}

PendingOperation *AccountApiPrivate::updateUsername(const QString &newUsername)
{
    return nullptr;
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
