#ifndef TELEGRAMQT_PENDING_OPERATION
#define TELEGRAMQT_PENDING_OPERATION

#include <QObject>
#include <QVariantHash>

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class Backend;

} // Client

class RpcError;

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

signals:
    void finished(PendingRpcOperation *operation);

protected:
    quint64 m_requestId;
    QByteArray m_replyData;
    QByteArray m_requestData;
    RpcError *m_error = nullptr;
};

namespace Client {

class AccountRpcLayer;
class AuthRpcLayer;

class PendingAuthOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingAuthOperation(QObject *parent = nullptr);
    void setBackend(Backend *backend);

    using RunMethod = PendingOperation *(PendingAuthOperation::*)();

    void setRunMethod(RunMethod method);

    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString passwordHint() const { return m_passwordHint; }
    bool hasRecovery() const { return m_hasRecovery; }

public slots:
    void start() override;

    void abort();

    PendingOperation *requestAuthCode();
    PendingOperation *submitAuthCode(const QString &code);
    PendingOperation *getPassword();
    PendingOperation *submitPassword(const QString &password);

    void requestCall();
    void requestSms();
    void recovery();

Q_SIGNALS:
    void phoneNumberRequired();
    void authCodeRequired();
    void passwordRequired();
    void passwordCheckFailed();
//    void callAvailable();

    void passwordHintChanged(const QString &hint);
    void hasRecoveryChanged(bool hasRecovery);

    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage); // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);

protected:
    void setPasswordCurrentSalt(const QByteArray &salt);
    void setPasswordHint(const QString &hint);
    AccountRpcLayer *accountLayer() const;
    AuthRpcLayer *authLayer() const;

    Backend *m_backend = nullptr;
    RunMethod m_runMethod = nullptr;
    QString m_phoneNumber;
    QString m_passwordHint;
    QByteArray m_passwordCurrentSalt;
    bool m_hasRecovery;

protected:
    // Implementation:
    void onRequestAuthCodeFinished(PendingRpcOperation *operation);
    void onSignInFinished(PendingRpcOperation *operation);
    void onPasswordRequestFinished(PendingRpcOperation *operation);
    void onCheckPasswordFinished(PendingRpcOperation *operation);

    QString m_authCodeHash;
};

} // Client

}

#endif // TELEGRAMQT_PENDING_OPERATION
