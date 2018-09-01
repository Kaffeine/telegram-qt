#ifndef TELEGRAM_CLIENT_CONNECTION_HPP
#define TELEGRAM_CLIENT_CONNECTION_HPP

#include "Connection.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class ConnectOperation;
class RpcLayer;

class Connection : public Telegram::BaseConnection
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    DcOption dcOption() const { return m_dcOption; }
    void setDcOption(const DcOption &dcOption);

    static Connection *fromOperation(PendingRpcOperation *operation);

    RpcLayer *rpcLayer();

public slots:
    ConnectOperation *connectToDc();
//    void disconnectFromDc();
    void processSeeOthers(PendingRpcOperation *operation);

protected slots:
    void onClientDhStateChanged();

protected:
    DcOption m_dcOption;
    QVector<PendingRpcOperation *> m_queuedOperations;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_CONNECTION_HPP
