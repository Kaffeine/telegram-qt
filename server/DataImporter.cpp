#include "DataImporter.hpp"

#include "LocalCluster.hpp"

namespace Telegram {

namespace Server {

DataImporter::~DataImporter()
{
}

void DataImporter::setTarget(LocalCluster *cluster)
{
    m_targetCluster = cluster;
}

void DataImporter::saveData()
{
    if (!prepare()) {
        return;
    }

    const QVector<Server*> servers = m_targetCluster->getServerInstances();
    for (Server *server : servers) {
        exportForServer(server);
    }
}

void Telegram::Server::DataImporter::loadData()
{
    if (!prepare()) {
        return;
    }

    const QVector<Server*> servers = m_targetCluster->getServerInstances();
    for (Server *server : servers) {
        importForServer(server);
    }
}

} // Server namespace

} // Telegram namespace
