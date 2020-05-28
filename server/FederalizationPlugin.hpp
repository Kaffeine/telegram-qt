#ifndef TELEGRAM_QT_SERVER_FEDERALIZATION_PLUGIN_HPP
#define TELEGRAM_QT_SERVER_FEDERALIZATION_PLUGIN_HPP

#include <QtPlugin>

#define FederalizationInterface_iid "TelegramQt.Server.FederalizationInterface/1.0"

namespace Telegram {

namespace Server {

class FederalizationApi;

class FederalizationInterface
{
public:
    virtual FederalizationApi *create() = 0;
};

} // Server

} // Telegram

Q_DECLARE_INTERFACE(Telegram::Server::FederalizationInterface, FederalizationInterface_iid)

class Q_DECL_EXPORT FederalizationPlugin : public QObject
        , public Telegram::Server::FederalizationInterface
{
    Q_OBJECT
    Q_INTERFACES(Telegram::Server::FederalizationInterface)
public:
    explicit FederalizationPlugin(QObject *parent = nullptr);
    ~FederalizationPlugin() override;

    Telegram::Server::FederalizationApi *create() override = 0;
};

#endif // TELEGRAM_QT_SERVER_FEDERALIZATION_PLUGIN_HPP
