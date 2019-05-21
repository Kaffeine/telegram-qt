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

    bool isContentRelated() const { return m_contentRelated; }
    void setContentRelated(bool related) { m_contentRelated = related; }
    QByteArray requestData() const { return m_requestData; }
    QByteArray replyData() const { return m_replyData; }
    void setFinishedWithReplyData(const QByteArray &data);
    void clearResult() override;
    void reuse(const QByteArray &requestData);

    RpcError *rpcError() const { return m_error; }

    BaseConnection *getConnection() const { return m_connection; }
    void setConnection(BaseConnection *connection) { m_connection = connection; }

Q_SIGNALS:
    void finished(PendingRpcOperation *operation);
    void resent(quint64 oldMessageId, quint64 newMessageId);

protected:
    void setRequestData(const QByteArray &requestData);

    // The class is private, don't care about ABI
    QByteArray m_replyData;
    QByteArray m_requestData;
    RpcError *m_error = nullptr;
    BaseConnection *m_connection = nullptr;
    bool m_contentRelated = true;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_RPC_OPERATION
