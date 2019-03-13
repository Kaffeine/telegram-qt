#ifndef TELEGRAMQT_CLIENT_PING_OPERATION
#define TELEGRAMQT_CLIENT_PING_OPERATION

#include "../PendingRpcOperation.hpp"

QT_FORWARD_DECLARE_CLASS(QTimer)

namespace Telegram {

namespace Client {

class RpcLayer;
class Settings;

class PingOperation : public QObject
{
    Q_OBJECT
public:
    explicit PingOperation(QObject *parent = nullptr);

    void setSettings(Settings *settings) { m_settings = settings; }
    void setRpcLayer(RpcLayer *layer) { m_rpcLayer = layer; }

    void ensureActive();
    void ensureInactive();
    void reset();

Q_SIGNALS:
    void pingFailed(const QVariantHash &details);

protected slots:
    void onTimeToKeepAlive();
    void onPingRpcFinished();

protected:
    void onPingResent(quint64 oldMessageId, quint64 newMessageId);

    PendingRpcOperation *m_pingRpcOperation = nullptr;

    quint64 m_pingId = 0;
    quint64 m_pingMessageId = 0;

    QTimer *m_pingTimer = nullptr;
    Settings *m_settings = nullptr;
    RpcLayer *m_rpcLayer = nullptr;
};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_PING_OPERATION
