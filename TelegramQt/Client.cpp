#include "Client_p.hpp"

namespace Telegram {

namespace Client {

/*!
    \class Telegram::Client::Client
    \brief The main class for Client implementation.
    \inmodule TelegramQt
    \ingroup Client
*/
Client::Client(QObject *parent) :
    QObject(parent),
    d_ptr(new ClientPrivate(this))
{
}

Client::~Client()
{
}

bool Client::isSignedIn() const
{
    Q_D(const Client);
    return d->isSignedIn();
}

Telegram::Client::AuthOperation *Client::signIn()
{
    Q_D(Client);
    return d->signIn();
}

AuthOperation *Client::checkIn()
{
    Q_D(Client);
    return d->checkIn();
}

CAppInformation *Client::appInformation() const
{
    Q_D(const Client);
    return d->m_appInformation;
}

void Client::setAppInformation(CAppInformation *newAppInfo)
{
    Q_D(Client);
    d->m_appInformation = newAppInfo;
}

Telegram::Client::Settings *Client::settings()
{
    Q_D(Client);
    return d->m_settings;
}

const Telegram::Client::Settings *Client::settings() const
{
    Q_D(const Client);
    return d->m_settings;
}

void Client::setSettings(Settings *settings)
{
    Q_D(Client);
    d->m_settings = settings;
}

AccountStorage *Client::accountStorage() const
{
    Q_D(const Client);
    return d->m_accountStorage;
}

void Client::setAccountStorage(AccountStorage *storage)
{
    Q_D(Client);
    d->m_accountStorage = storage;
}

DataStorage *Client::dataStorage() const
{
    Q_D(const Client);
    return d->m_dataStorage;
}

void Client::setDataStorage(DataStorage *storage)
{
    Q_D(Client);
    d->m_dataStorage = storage;
}

//void Client::setAppInformation(AppInformation *newAppInfo)
//{
//    d->m_appInformation = newAppInfo;
//}

} // Client

} // Telegram
