/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CTelegramCore.hpp"

#include <QDebug>

#include "CTelegramConnection.hpp"

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_appId(0),
    m_appHash(QLatin1String("00000000000000000000000000000000")),
    m_activeDc(0)
{
}

void CTelegramCore::setAppId(quint32 newId)
{
    m_appId = newId;
}

bool CTelegramCore::setAppHash(const QString &newHash)
{
    if (newHash.length() != 32)
        return false;

    m_appHash = newHash;

    return true;
}

void CTelegramCore::initConnection(const QString &address, quint32 port)
{
    CTelegramConnection *connection = createConnection(SDcInfo(address, port));
    m_connections.insert(0, connection);
    connection->connectToDc();

    m_activeDc = 0;
}

void CTelegramCore::whenConnectionAuthChanged(int dc, int newState)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    if (newState == CTelegramConnection::AuthSuccess) {
        if (m_dcConfiguration.isEmpty()) {
            connection->getConfiguration();
        }
    }
}

void CTelegramCore::whenConnectionConfigurationUpdated(int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    m_dcConfiguration = connection->dcConfiguration();

    qDebug() << "Core: DC Configuration:";
    for (int i = 0; i < m_dcConfiguration.count(); ++i) {
        qDebug() << m_dcConfiguration.at(i).id << ": " << m_dcConfiguration.at(i).ipAddress << ":"<< m_dcConfiguration.at(i).port;
    }
}

void CTelegramCore::whenConnectionDcIdUpdated(int connectionId, int newDcId)
{
    CTelegramConnection *connection = m_connections.value(connectionId);

    if (!connection) {
        return;
    }

    if (m_connections.value(newDcId)) {
        qDebug() << "Connection with wanted id already exists";
    } else {
        m_connections.remove(connectionId);
        m_connections.insert(newDcId, connection);

        SDcInfo info = connection->dcInfo();
        info.id = newDcId;
        connection->setDcInfo(info);

        if (m_activeDc == connectionId) {
            m_activeDc = newDcId;
        }

        qDebug() << "Connection DC Id changed from" << connectionId << "to" << newDcId;
    }
}

CTelegramConnection *CTelegramCore::createConnection(const SDcInfo &dc)
{
    CTelegramConnection *connection = new CTelegramConnection(this);

    connect(connection, SIGNAL(authStateChanged(int,int)), SLOT(whenConnectionAuthChanged(int,int)));
    connect(connection, SIGNAL(dcConfigurationReceived(int)), SLOT(whenConnectionConfigurationUpdated(int)));
    connect(connection, SIGNAL(actualDcIdReceived(int,int)), SLOT(whenConnectionDcIdUpdated(int,int)));

    connection->setDcInfo(dc);
    connection->setAppId(m_appId);
    connection->setAppHash(m_appHash);

    return connection;
}
