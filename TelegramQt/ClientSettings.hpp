#ifndef TELEGRAM_CLIENT_SETTINGS_HPP
#define TELEGRAM_CLIENT_SETTINGS_HPP

#include <QObject>
#include <QVector>
#include <QNetworkProxy>

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pingInterval MEMBER m_pingInterval)
public:
    explicit Settings(QObject *parent = nullptr);

    QNetworkProxy proxy() const { return m_proxy; }
    void setProxy(const QNetworkProxy &proxy);

    Q_INVOKABLE static quint32 defaultPingInterval();
    // // By default, the app would ping server every 15 000 ms and instruct the server to close connection after 10 000 more ms. Pass interval = 0 to disable ping.
    // void setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionalTime = 10000);

    // void setMediaDataBufferSize(quint32 size);

    // Q_INVOKABLE Telegram::RsaKey defaultServerPublicRsaKey() const;

    Q_INVOKABLE static QVector<DcOption> defaultServerConfiguration();

    QVector<DcOption> serverConfiguration();

    RsaKey serverRsaKey() const;
    bool setServerRsaKey(const RsaKey &key);
    bool setServerConfiguration(const QVector<DcOption> &dcs);
    bool resetServerConfiguration();

    bool isValid() const;

protected:
    // TODO: PIMPL
    QNetworkProxy m_proxy;
    QVector<DcOption> m_serverConfiguration;
    RsaKey m_key;
    int m_pingInterval;
};

} // Client

} // Telegram

#endif // TELEGRAM_CLIENT_SETTINGS_HPP
