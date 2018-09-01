#ifndef TELEGRAM_CONNECTION_HPP
#define TELEGRAM_CONNECTION_HPP

#include "telegramqt_global.h"

#include "TelegramNamespace.hpp"

#include <QObject>
#include <QVector>
#include <QStringList>

class CTelegramTransport;

namespace Telegram {

class BaseSendPackageHelper;
class BaseDhLayer;
class BaseRpcLayer;

class TELEGRAMQT_EXPORT BaseConnection : public QObject
{
    Q_OBJECT
public:
    enum class Status {
        Disconnected,
        Disconnecting,
        Connecting,
        Connected,
        Authenticated, // Connected and has auth key
        Signed
    };
    Q_ENUM(Status)

    enum class StatusReason {
        None,
        Local,
        Remote,
        Timeout
    };
    Q_ENUM(StatusReason)

    explicit BaseConnection(QObject *parent = nullptr);

    quint64 authId() const;

    QByteArray authKey() const;
    void setAuthKey(const QByteArray &authKey);

    void setServerRsaKey(const RsaKey &key);

    CTelegramTransport *transport() const { return m_transport; }
    void setTransport(CTelegramTransport *newTransport);

    Status status() const { return m_status; }
    void setStatus(Status status, StatusReason reason);

signals:
    void statusChanged(Status status, StatusReason reason);

protected slots:
    void onTransportStateChanged();
    void onTransportPackageReceived(const QByteArray &package);
    void onDhStateChanged();

protected:
    CTelegramTransport *m_transport = nullptr;
    BaseSendPackageHelper *m_sendHelper;
    BaseDhLayer *m_dhLayer = nullptr;
    BaseRpcLayer *m_rpcLayer = nullptr;
    QByteArray m_authKey;
    quint64 m_authId = 0;
    RsaKey m_rsaKey;
    Status m_status = Status::Disconnected;

};

} // Telegram namespace

#endif // TELEGRAM_CONNECTION_HPP
