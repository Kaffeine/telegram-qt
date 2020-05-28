#include "LocalCluster.hpp"

#include "DefaultAuthorizationProvider.hpp"
#include "RemoteServerConnection.hpp"
#include "MessageService.hpp"
#include "TelegramServer.hpp"
#include "TelegramServerUser.hpp"
#include "FederalizationApi.hpp"

#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcCluster, "telegram.server.cluster", QtWarningMsg)

namespace Telegram {

namespace Server {

LocalCluster::LocalCluster(QObject *parent)
    : QObject(parent)
{
    m_constructor = [](QObject *parent) { return new Server(parent); };
}

void LocalCluster::setServerContructor(LocalCluster::ServerConstructor constructor)
{
    m_constructor = constructor;
}

void LocalCluster::setMessageService(MessageService *service)
{
    m_messageService = service;
}

void LocalCluster::setAuthorizationProvider(Authorization::Provider *provider)
{
    m_authProvider = provider;
}

void LocalCluster::setListenAddress(const QHostAddress &address)
{
    m_listenAddress = address;
}

void LocalCluster::addFederalization(FederalizationApi *api)
{
    m_federalizations.append(api);
}

void LocalCluster::setServerConfiguration(const DcConfiguration &config)
{
    m_serverConfiguration = config;
}

void LocalCluster::setServerPrivateRsaKey(const Telegram::RsaKey &key)
{
    m_key = key;
}

bool LocalCluster::start()
{
    if (m_serverConfiguration.dcOptions.isEmpty()) {
        qCCritical(lcCluster) << CALL_INFO << "Unable to start cluster: DC options is empty.";
        return false;
    }

    if (!m_key.isPrivate()) {
        qCCritical(lcCluster) << CALL_INFO << "Unable to start cluster: Invalid private key.";
        return false;
    }

    if (!m_messageService) {
        qCDebug(lcCluster) << CALL_INFO << "Fallback to default Storage implementation";
        m_messageService = new MessageService(this);
    }

    if (!m_authProvider) {
        qCDebug(lcCluster) << CALL_INFO << "Fallback to default auth provider";
        m_authProvider = new Authorization::DefaultProvider();
    }

    quint32 maxDcId = 0;
    for (const DcOption &dc : m_serverConfiguration.dcOptions) {
        if (!dc.id) {
            qCCritical(lcCluster) << CALL_INFO << "Invalid configuration: DC id is null.";
            return false;
        }
        if (!dc.port) {
            qCCritical(lcCluster) << CALL_INFO << "Invalid configuration: Server port is not set.";
            return false;
        }
        if (dc.address.isEmpty()) {
            qCCritical(lcCluster) << CALL_INFO << "Invalid configuration: Server address is not set.";
            return false;
        }
        if (dc.id > maxDcId) {
            maxDcId = dc.id;
        }
        Server *server = m_constructor(this);
        server->setServerConfiguration(m_serverConfiguration);
        server->setDcOption(dc);
        server->setListenAddress(m_listenAddress);
        server->setServerPrivateRsaKey(m_key);
        server->setMessageService(m_messageService);
        server->setAuthorizationProvider(m_authProvider);
        m_serverInstances.append(server);
    }

    bool hasFails = false;
    for (Server *server : m_serverInstances) {
        for (Server *peer : m_serverInstances) {
            if (server == peer) {
                continue;
            }
            RemoteServerConnection *remote = new RemoteServerConnection(server);
            remote->setRemoteServer(peer);
            server->addServerConnection(remote);
        }

        if (!server->start()) {
            qCCritical(lcCluster) << CALL_INFO << "Unable to start server" << server->dcId();
            hasFails = true;
        }
    }

    if (!hasFails) {
        for (FederalizationApi *fed : m_federalizations) {
            fed->setDcId(++maxDcId);
            // fed->setDomain(m_listenAddress.toString());
            fed->setDomain(QLatin1String("thost"));
            fed->setListenAddress(m_listenAddress);

            FederalizationGateway *federalizationGateWay = new FederalizationGateway(this);
            federalizationGateWay->setApi(fed);

            fed->setMessageService(m_messageService);

            for (Server *peer : m_serverInstances) {
                peer->addServerConnection(federalizationGateWay);

                RemoteServerConnection *remote = new RemoteServerConnection(this); //fed
                remote->setRemoteServer(peer);
                fed->addServerConnection(remote);
            }

            fed->start();
        }
    }

    return !hasFails;
}

void LocalCluster::stop()
{
    for (Server *server : m_serverInstances) {
        server->stop();
    }
}

LocalUser *LocalCluster::addUser(const QString &identifier, quint32 dcId)
{
    Server *server = getServerInstance(dcId);
    if (!server) {
        qCWarning(lcCluster) << CALL_INFO << "Unable to add user"
                             << identifier << "to unknown server id" << dcId;
        return nullptr;
    }
    LocalUser *user = server->addUser(identifier);
    if (!user) {
        qCWarning(lcCluster) << CALL_INFO << "Unable to add user";
    }
    return user;
}

LocalUser *LocalCluster::getUser(const QString &identifier)
{
    AbstractUser *u = m_serverInstances.first()->getAbstractUser(identifier);
    if (!u) {
        return nullptr;
    }
    Server *s = getServerInstance(u->dcId());
    return s->getUser(identifier);
}

Server *LocalCluster::getServerInstance(quint32 dcId)
{
    for (Server *server : m_serverInstances) {
        if (server->dcId() == dcId) {
            return server;
        }
    }
    return nullptr;
}

AbstractServerApi *LocalCluster::getServerApiInstance(quint32 dcId)
{
    return getServerInstance(dcId);
}

void LocalCluster::sendMessage(MessageData *messageData)
{
    if (messageData->fromId() == 0) {
        qCWarning(lcCluster) << CALL_INFO << "Unable to process message without a sender";
        return;
    }
    AbstractUser *user = m_serverInstances.first()->getAbstractUser(messageData->fromId());

    Server *server = getServerInstance(user->dcId());
    Session *excludeClientSession = nullptr;
    server->processMessage(messageData, excludeClientSession);
}

} // Server namespace

} // Telegram namespace
