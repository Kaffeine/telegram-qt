#ifndef TELEGRAMQT_PENDING_RPC_OPERATION
#define TELEGRAMQT_PENDING_RPC_OPERATION

#include "PendingOperation.hpp"

namespace Telegram {

class RpcError;
class BaseConnection;

class PendingRpcOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingRpcOperation(const QByteArray &requestData = QByteArray(), QObject *parent = nullptr);
    ~PendingRpcOperation() override;

    QByteArray requestData() const { return m_requestData; }
    QByteArray replyData() const { return m_replyData; }
    void setFinishedWithReplyData(const QByteArray &data);
    void clearResult() override;

    RpcError *rpcError() const { return m_error; }

    quint64 requestId() const { return m_requestId; } // RPC message id
    void setRequestId(quint64 id) { m_requestId = id; }

    BaseConnection *getConnection() const { return m_connection; }
    void setConnection(BaseConnection *connection) { m_connection = connection; }

Q_SIGNALS:
    void finished(PendingRpcOperation *operation);

protected:
    quint64 m_requestId;
    QByteArray m_replyData;
    QByteArray m_requestData;
    RpcError *m_error = nullptr;
    BaseConnection *m_connection;
};

}

#endif // TELEGRAMQT_PENDING_RPC_OPERATION
