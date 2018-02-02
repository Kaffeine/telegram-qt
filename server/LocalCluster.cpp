#include "LocalCluster.hpp"

#include "TelegramServer.hpp"
#include "RemoteServerConnection.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_loggingClusterCategory, "telegram.server.cluster", QtWarningMsg)

namespace Telegram {

namespace Server {

LocalCluster::LocalCluster(QObject *parent)
    : QObject(parent)
{
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
        return false;
    }

    for (const DcOption &dc : m_serverConfiguration.dcOptions) {
        Server *server = new Server(this);
        server->setServerConfiguration(m_serverConfiguration);
        server->setDcOption(dc);
        server->setServerPrivateRsaKey(m_key);
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
            qCCritical(c_loggingClusterCategory) << Q_FUNC_INFO << "Unable to start server" << server->dcId();
            hasFails = true;
        }
    }
    return !hasFails;
}

User *LocalCluster::addUser(const QString &identifier, quint32 dcId)
{
    Server *server = getServerInstance(dcId);
    if (!server) {
        qCWarning(c_loggingClusterCategory) << Q_FUNC_INFO << "Unable to add user" << identifier << "to unknown server id" << dcId;
        return nullptr;
    }
    return server->addUser(identifier);
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

} // Server

} // Telegram
