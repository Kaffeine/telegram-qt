#ifndef TELEGRAMQT_PENDING_OPERATION
#define TELEGRAMQT_PENDING_OPERATION

#include <QObject>
#include <QVariantHash>

namespace Telegram {

namespace Client {

class Backend;

} // Client

class RpcError;
class BaseConnection;

class PendingOperation : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PendingOperation)
public:
    explicit PendingOperation(QObject *parent = nullptr);
    bool isFinished() const;
    bool isSucceeded() const;

    QVariantHash errorDetails() const;

    template <typename OperationType>
    static OperationType *failOperation(const QVariantHash &failDetails, QObject *parent = nullptr)
    {
        OperationType *op = new OperationType();
        op->setParent(parent);
        op->setDelayedFinishedWithError(failDetails);
        return op;
    }

    template<typename T, typename M>
    static void callMember(T *obj, M method)
    {
        (obj->*method)();
    }
    static PendingOperation *failOperation(const QVariantHash &failDetails, QObject *parent = nullptr)
    {
        return failOperation<PendingOperation>(failDetails, parent);
    }

Q_SIGNALS:
    void finished(PendingOperation *operation);
    void succeeded(PendingOperation *operation);
    void failed(PendingOperation *operation, const QVariantHash &details);

public Q_SLOTS:
    virtual void start() { }
    void startLater();
    void runAfter(PendingOperation *operation);

    void setFinished();
    void setFinishedWithError(const QVariantHash &details);
    void setDelayedFinishedWithError(const QVariantHash &details);

protected:
    void onPreviousFailed(PendingOperation *operation, const QVariantHash &details);

private:
    QVariantHash m_errorDetails;
    bool m_finished;
    bool m_succeeded;
};

class PendingRpcOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingRpcOperation(const QByteArray &requestData = QByteArray(), QObject *parent = nullptr);
    ~PendingRpcOperation();

    QByteArray requestData() const { return m_requestData; }
    QByteArray replyData() const { return m_replyData; }
    void setFinishedWithReplyData(const QByteArray &data);

    RpcError *rpcError() const { return m_error; }

    quint64 requestId() const { return m_requestId; } // RPC message id
    void setRequestId(quint64 id) { m_requestId = id; }

    BaseConnection *getConnection() const { return m_connection; }
    void setConnection(BaseConnection *connection) { m_connection = connection; }

signals:
    void finished(PendingRpcOperation *operation);

protected:
    quint64 m_requestId;
    QByteArray m_replyData;
    QByteArray m_requestData;
    RpcError *m_error = nullptr;
    BaseConnection *m_connection;
};

}

#endif // TELEGRAMQT_PENDING_OPERATION
