#ifndef TELEGRAM_CLIENT_SETTINGS_HPP
#define TELEGRAM_CLIENT_SETTINGS_HPP

#include <QObject>
#include <QVector>
#include <QNetworkProxy>

#include "RsaKey.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class TELEGRAMQT_EXPORT Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pingInterval READ pingInterval WRITE setPingInterval NOTIFY pingIntervalChanged)
public:
    enum class SessionType {
        None,
        Abridged,
        Obfuscated,
    };
    Q_ENUM(SessionType)

    explicit Settings(QObject *parent = nullptr);

    QNetworkProxy proxy() const { return m_proxy; }
    void setProxy(const QNetworkProxy &proxy);

    SessionType preferedSessionType() const { return m_preferedSessionType; }
    void setPreferedSessionType(const SessionType type);

    Q_INVOKABLE static quint32 defaultPingInterval();
    // By default, the app will ping server every 45 seconds
    // Pass interval = 0 to disable ping; the additionalTime argument can be used to enable server-side disconnection
    quint32 pingInterval() const { return m_pingInterval; }
    quint32 serverDisconnectionAdditionalTime() const { return m_serverDisconnectionAdditionalTime; }
    void setPingInterval(quint32 interval, quint32 serverDisconnectionAdditionalTime = 0);

    // void setMediaDataBufferSize(quint32 size);

    Q_INVOKABLE static QVector<DcOption> defaultServerConfiguration();
    Q_INVOKABLE static QVector<DcOption> testServerConfiguration();

    QVector<DcOption> serverConfiguration();

    RsaKey serverRsaKey() const;
    bool setServerRsaKey(const RsaKey &key);
    bool setServerConfiguration(const QVector<DcOption> &dcs);
    bool resetServerConfiguration();

    bool isValid() const;

Q_SIGNALS:
    void pingIntervalChanged(quint32 interval, quint32 serverDisconnectionAdditionalTime);

protected:
    // TODO: PIMPL
    QNetworkProxy m_proxy;
    QVector<DcOption> m_serverConfiguration;
    RsaKey m_key;
    quint32 m_pingInterval = 0;
    quint32 m_serverDisconnectionAdditionalTime = 0;
    SessionType m_preferedSessionType = SessionType::None;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_SETTINGS_HPP
