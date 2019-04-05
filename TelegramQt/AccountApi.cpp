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

} // Client namespace

} // Telegram namespace
