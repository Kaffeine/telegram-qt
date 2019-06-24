#include "ClientSettings.hpp"

#include "Utils.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    m_serverConfiguration = defaultServerConfiguration();
    m_key = RsaKey::defaultKey();
    m_preferedSessionType = SessionType::Obfuscated;

    setPingInterval(defaultPingInterval());
}

void Settings::setProxy(const QNetworkProxy &proxy)
{
    m_proxy = proxy;
}

void Settings::setPreferedSessionType(const Settings::SessionType type)
{
    m_preferedSessionType = type;
}

quint32 Settings::defaultPingInterval()
{
    return 45000u;
}

void Settings::setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionalTime)
{
    if ((m_pingInterval == interval) && (m_serverDisconnectionAdditionalTime == serverDisconnectionAdditionalTime)) {
        return;
    }
    m_pingInterval = interval;
    m_serverDisconnectionAdditionalTime = serverDisconnectionAdditionalTime;
    emit pingIntervalChanged(interval, serverDisconnectionAdditionalTime);
}

QVector<DcOption> Settings::defaultServerConfiguration()
{
    static const QVector<DcOption> s_builtInDcs = {
            DcOption(QLatin1String("149.154.175.50") , 443),
            DcOption(QLatin1String("149.154.167.51") , 443),
            DcOption(QLatin1String("149.154.175.100"), 443),
            DcOption(QLatin1String("149.154.167.91") , 443),
            DcOption(QLatin1String("91.108.56.165")  , 443),
    };
    return s_builtInDcs;
}

QVector<DcOption> Settings::testServerConfiguration()
{
    static const QVector<DcOption> s_builtInTestDcs = {
            DcOption(QLatin1String("149.154.167.40") , 443, 2),
    };
    return s_builtInTestDcs;
}

QVector<DcOption> Settings::serverConfiguration()
{
    return m_serverConfiguration;
}

RsaKey Settings::serverRsaKey() const
{
    return m_key;
}

bool Settings::setServerRsaKey(const RsaKey &key)
{
    m_key = key;
    return true;
}

bool Settings::setServerConfiguration(const QVector<DcOption> &dcs)
{
    m_serverConfiguration = dcs;
    return true;
}

bool Settings::resetServerConfiguration()
{
    return false;
}

bool Settings::isValid() const
{
    return !m_serverConfiguration.isEmpty();
}

} // Client

} // Telegram
