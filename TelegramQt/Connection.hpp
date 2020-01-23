#ifndef TELEGRAM_CONNECTION_HPP
#define TELEGRAM_CONNECTION_HPP

#include "telegramqt_global.h"

#include "RsaKey.hpp"

#include <QObject>
#include <QVector>
#include <QStringList>

namespace Telegram {

class BaseMTProtoSendHelper;
class BaseDhLayer;
class BaseRpcLayer;
class BaseTransport;

class TELEGRAMQT_INTERNAL_EXPORT BaseConnection : public QObject
{
    Q_OBJECT
public:
    enum class Status {
        Disconnected, // The initial and final status.
        Disconnecting, // Setted on disconnect initialized by the client.
        Connecting, // Never bypassed, setted on connectToDc() call.
        Connected, // Never bypassed, setted on transport connected.
        HasDhKey, // Never bypassed, setted on connected and has auth key or on DH established.
        Signed, // Never bypassed, setted by auth operation. CheckIn leads to reason Local, SignUp/SignIn leads to reason remote.
        Failed // Transport maybe still connected, but reconnection is needed.
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
    ~BaseConnection() override;

    static QString c_statusKey();
    static QString c_statusReasonKey();

    quint64 authId() const;

    QByteArray authKey() const;
    void setAuthKey(const QByteArray &authKey);

    void setServerRsaKey(const RsaKey &key);

    BaseTransport *transport() const { return m_transport; }
    void setTransport(BaseTransport *newTransport);

    Status status() const { return m_status; }
    void setStatus(Status status, StatusReason reason);

signals:
    void statusChanged(Status status, StatusReason reason);
    void errorOccured(const QByteArray &errorBytes);

protected slots:
    void onTransportStateChanged();
    void onTransportPacketReceived(const QByteArray &payload);
    void onDhStateChanged();

protected:
    virtual bool processAuthKey(quint64 authKeyId) = 0;

    BaseTransport *m_transport = nullptr;
    BaseMTProtoSendHelper *m_sendHelper;
    BaseDhLayer *m_dhLayer = nullptr;
    BaseRpcLayer *m_rpcLayer = nullptr;
    quint64 m_authId = 0;
    RsaKey m_rsaKey;
    Status m_status = Status::Disconnected;

};

} // Telegram namespace

#endif // TELEGRAM_CONNECTION_HPP
