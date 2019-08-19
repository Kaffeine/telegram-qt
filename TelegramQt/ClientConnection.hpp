#ifndef TELEGRAM_CLIENT_CONNECTION_HPP
#define TELEGRAM_CLIENT_CONNECTION_HPP

#include "Connection.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;
class RpcLayer;

class Connection : public Telegram::BaseConnection
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    DcOption dcOption() const { return m_dcOption; }
    void setDcOption(const DcOption &dcOption);

    qint32 deltaTime() const;
    void setDeltaTime(const qint32 newDt);

    static Connection *fromOperation(PendingRpcOperation *operation);

    RpcLayer *rpcLayer();

public slots:
    void connectToDc();
//    void disconnectFromDc();

protected slots:
    void onClientDhStateChanged();

protected:
    bool processAuthKey(quint64 authKeyId) override;

    DcOption m_dcOption;
    QVector<PendingRpcOperation *> m_queuedOperations;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_CONNECTION_HPP
