#ifndef TELEGRAM_QT_SERVER_AUTH_PLUGIN_HPP
#define TELEGRAM_QT_SERVER_AUTH_PLUGIN_HPP

#include <QtPlugin>

#define AuthorizationProviderInterface_iid "TelegramQt.Server.AuthorizationProviderInterface/1.0"

namespace Telegram {

namespace Server {

namespace Authorization {

class Provider;

} // Authorization

class AuthorizationProviderInterface
{
public:
    virtual Authorization::Provider *create() = 0;
};

} // Server

} // Telegram

Q_DECLARE_INTERFACE(Telegram::Server::AuthorizationProviderInterface, AuthorizationProviderInterface_iid)

class AuthorizationProviderPlugin : public QObject
        , public Telegram::Server::AuthorizationProviderInterface
{
    Q_OBJECT
    Q_INTERFACES(Telegram::Server::AuthorizationProviderInterface)
public:
    explicit AuthorizationProviderPlugin(QObject *parent = nullptr);
    ~AuthorizationProviderPlugin() override;

    Telegram::Server::Authorization::Provider *create() override = 0;
};

#endif // TELEGRAM_QT_SERVER_AUTH_PLUGIN_HPP
