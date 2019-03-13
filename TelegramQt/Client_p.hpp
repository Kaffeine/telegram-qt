#ifndef TELEGRAM_CLIENT_P_HPP
#define TELEGRAM_CLIENT_P_HPP

#include "Client.hpp"

#include "CAppInformation.hpp"
#include "ClientBackend.hpp"

namespace Telegram {

namespace Client {

class Connection;

class ClientPrivate : public Backend
{
    Q_OBJECT
public:
    explicit ClientPrivate(Client *parent) : Backend(parent) { }
    static const ClientPrivate *get(const Client *c) { return c->d; }
    static ClientPrivate *get(Client *c) { return c->d; }
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_P_HPP
