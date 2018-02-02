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
    static const ClientPrivate *get(const Client *c) { return c->d_ptr; }
    static ClientPrivate *get(Client *c) { return c->d_ptr; }
};

} // Client

} // Telegram

#endif // TELEGRAM_CLIENT_P_HPP
