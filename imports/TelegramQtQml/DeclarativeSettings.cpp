#include "DeclarativeSettings.hpp"

#include "CTelegramCore.hpp"

#include <QNetworkProxy>

namespace Telegram {

namespace Client {

DeclarativeProxySettings::DeclarativeProxySettings(QObject *parent) :
    QObject(parent)
{
}

void DeclarativeProxySettings::setPort(quint16 port)
{
    m_port = port;
}

void DeclarativeProxySettings::setAddress(const QString &address)
{
    m_address = address;
}

DeclarativeSettings::DeclarativeSettings(QObject *parent) :
    QObject(parent)
{
    m_proxySettings = new DeclarativeProxySettings(this);
}

void DeclarativeSettings::syncSettings()
{
    QNetworkProxy proxy;
    if (!m_proxySettings->address().isEmpty()) {
        proxy.setType(QNetworkProxy::Socks5Proxy);
        proxy.setHostName(m_proxySettings->address());
        proxy.setPort(m_proxySettings->port());
    }
    m_client->setProxy(proxy);
}

void DeclarativeSettings::setClient(CTelegramCore *client)
{
    if (m_client == client) {
        return;
    }
    m_client = client;
    emit clientChanged();
}

} // Client

} // Telegram
