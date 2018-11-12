#ifndef TELEGRAMQT_PENDING_RPC_OPERATION
#define TELEGRAMQT_PENDING_RPC_OPERATION

#include "PendingOperation.hpp"

namespace Telegram {

class RpcError;
class BaseConnection;

namespace Client {

class PendingRpcOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingRpcOperation(QObject *parent = nullptr);
    explicit PendingRpcOperation(const QByteArray &requestData, QObject *parent = nullptr);
    ~PendingRpcOperation() override;

    QByteArray requestData() const { return m_requestData; }
    QByteArray replyData() const { return m_replyData; }
    void setFinishedWithReplyData(const QByteArray &data);
    void clearResult() override;

    RpcError *rpcError() const { return m_error; }

    BaseConnection *getConnection() const { return m_connection; }
    void setConnection(BaseConnection *connection) { m_connection = connection; }

Q_SIGNALS:
    void finished(PendingRpcOperation *operation);

protected:
    QByteArray m_replyData;
    QByteArray m_requestData;
    RpcError *m_error = nullptr;
    BaseConnection *m_connection = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_RPC_OPERATION
