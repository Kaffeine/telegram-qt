#include "DeclarativeSettings.hpp"

#include "DeclarativeRsaKey.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

DeclarativeProxySettings::DeclarativeProxySettings(QObject *parent) :
    QObject(parent)
{
}

void DeclarativeProxySettings::setPort(quint16 port)
{
    if (m_port == port) {
        return;
    }
    m_port = port;
    emit portChanged(port);
}

void DeclarativeProxySettings::setAddress(const QString &address)
{
    if (m_address == address) {
        return;
    }
    m_address = address;
    emit addressChanged(address);
}

void DeclarativeProxySettings::setUser(const QString &username)
{
    if (m_user == username) {
        return;
    }
    m_user = username;
    emit userChanged(username);
}

void DeclarativeProxySettings::setPassword(const QString &password)
{
    if (m_password == password) {
        return;
    }
    m_password = password;
    emit passwordChanged(password);
}

DeclarativeSettings::DeclarativeSettings(QObject *parent) :
    Settings(parent)
{
    m_proxySettings = new DeclarativeProxySettings(this);
}

QQmlListProperty<DeclarativeServerOption> DeclarativeSettings::serverOptions()
{
    return QQmlListProperty<DeclarativeServerOption>(this, this,
                                                     &DeclarativeSettings::appendServerOption,
                                                     &DeclarativeSettings::serverOptionCount,
                                                     &DeclarativeSettings::getServerOption,
                                                     &DeclarativeSettings::clearServerOptions);
}

void DeclarativeSettings::appendServerOption(DeclarativeServerOption *option)
{
    m_options.append(option);
    syncSettings();
    emit serverOptionsChanged();
}

void DeclarativeSettings::clearServerOptions()
{
    m_options.clear();
    emit serverOptionsChanged();
}

void DeclarativeSettings::setServerKey(DeclarativeRsaKey *serverKey)
{
    m_serverKey = serverKey;
    emit serverKeyChanged();
    syncSettings();
}

void DeclarativeSettings::syncSettings()
{
    QVector<Telegram::DcOption> dcs;
    for (const DeclarativeServerOption *declOption : m_options) {
        dcs.append(*declOption);
    }
    if (m_serverKey) {
        setServerRsaKey(m_serverKey->key());
    }
    if (dcs.isEmpty()) {
        setServerConfiguration(defaultServerConfiguration());
    } else {
        setServerConfiguration(dcs);
    }
    QNetworkProxy proxy;
    if (!m_proxySettings->address().isEmpty()) {
        proxy.setType(QNetworkProxy::Socks5Proxy);
        proxy.setHostName(m_proxySettings->address());
        proxy.setPort(m_proxySettings->port());
        proxy.setUser(m_proxySettings->user());
        proxy.setPassword(m_proxySettings->password());

    }
    setProxy(proxy);
}

void DeclarativeSettings::appendServerOption(QQmlListProperty<DeclarativeServerOption> *list, DeclarativeServerOption *option)
{
    reinterpret_cast<DeclarativeSettings*>(list->data)->appendServerOption(option);
}

int DeclarativeSettings::serverOptionCount(QQmlListProperty<DeclarativeServerOption> *list)
{
    return reinterpret_cast<DeclarativeSettings*>(list->data)->serverOptionCount();
}

DeclarativeServerOption *DeclarativeSettings::getServerOption(QQmlListProperty<DeclarativeServerOption> *list, int index)
{
    return reinterpret_cast<DeclarativeSettings*>(list->data)->getServerOption(index);
}

void DeclarativeSettings::clearServerOptions(QQmlListProperty<DeclarativeServerOption> *list)
{
    reinterpret_cast<DeclarativeSettings*>(list->data)->clearServerOptions();
}

} // Client

} // Telegram
