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
    m_activeDc(0),
    m_wantedActiveDc(0)
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

void CTelegramCore::initialConnection(const QString &address, quint32 port)
{
    CTelegramConnection *connection = createConnection(SDcInfo(address, port));
    m_connections.insert(0, connection);
    connection->connectToDc();

    setActiveDc(0);
}

void CTelegramCore::requestAuthCode(const QString &phoneNumber)
{
    activeConnection()->requestAuthCode(phoneNumber);
}

void CTelegramCore::signIn(const QString &phoneNumber, const QString &authCode)
{
    activeConnection()->signIn(phoneNumber, authCode);
}

void CTelegramCore::getContacts()
{
    activeConnection()->getContacts();
}

void CTelegramCore::whenConnectionAuthChanged(int dc, int newState)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    if (newState == CTelegramConnection::AuthStateSuccess) {
        if (m_dcConfiguration.isEmpty()) {
            connection->getConfiguration();
        }

        if (m_wantedActiveDc == dc) {
            setActiveDc(dc);
        }

        foreach (const QByteArray &data, m_delayedPackages.values(dc)) {
            connection->processRedirectedPackage(data);
        }

        m_delayedPackages.remove(dc);
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

            if (m_wantedActiveDc == m_activeDc) {
                m_wantedActiveDc = newDcId;
            }

            setActiveDc(newDcId);
        }

        qDebug() << "Connection DC Id changed from" << connectionId << "to" << newDcId;
    }
}

void CTelegramCore::whenPackageRedirected(const QByteArray &data, int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() == CTelegramConnection::AuthStateSuccess) {
        connection->processRedirectedPackage(data);
    } else {
        m_delayedPackages.insertMulti(dc, data);
        establishConnectionToDc(dc);
    }
}

void CTelegramCore::whenWantedActiveDcChanged(int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() == CTelegramConnection::AuthStateSuccess) {
        setActiveDc(dc);
    } else {
        m_wantedActiveDc = dc;
        establishConnectionToDc(dc);
    }
}

void CTelegramCore::setActiveDc(int dc, bool syncWantedDc)
{
    m_activeDc = dc;

    if (syncWantedDc) {
        m_wantedActiveDc = dc;
    }

    qDebug() << "New active dc:" << dc;
}

CTelegramConnection *CTelegramCore::createConnection(const SDcInfo &dc)
{
    CTelegramConnection *connection = new CTelegramConnection(this);

    connect(connection, SIGNAL(authStateChanged(int,int)), SLOT(whenConnectionAuthChanged(int,int)));
    connect(connection, SIGNAL(dcConfigurationReceived(int)), SLOT(whenConnectionConfigurationUpdated(int)));
    connect(connection, SIGNAL(actualDcIdReceived(int,int)), SLOT(whenConnectionDcIdUpdated(int,int)));
    connect(connection, SIGNAL(newRedirectedPackage(QByteArray,int)), SLOT(whenPackageRedirected(QByteArray,int)));
    connect(connection, SIGNAL(wantedActiveDcChanged(int)), SLOT(whenWantedActiveDcChanged(int)));

    connection->setDcInfo(dc);
    connection->setAppId(m_appId);
    connection->setAppHash(m_appHash);

    return connection;
}

CTelegramConnection *CTelegramCore::establishConnectionToDc(int dc)
{
    SDcInfo info = infoById(dc);

    if (!info.isValid()) {
        qDebug() << "Error: Attempt to connect to unknown DC" << dc;
        return 0;
    }

    CTelegramConnection *connection = m_connections.value(dc);
    if (!connection) {
        connection = createConnection(info);
        m_connections.insert(dc, connection);
    }

    if (!connection->isConnected()) {
        connection->connectToDc(); // There is incorrectess in SocketState to bool isConnected() mapping.
    }

    return connection;
}

SDcInfo CTelegramCore::infoById(quint32 id) const
{
    foreach (SDcInfo info, m_dcConfiguration) {
        if (info.id == id) {
            return info;
        }
    }

    return SDcInfo();
}
