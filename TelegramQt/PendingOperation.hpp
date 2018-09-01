#ifndef TELEGRAMQT_PENDING_OPERATION
#define TELEGRAMQT_PENDING_OPERATION

#include <QObject>
#include <QVariantHash>

namespace Telegram {

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
    virtual void clearResult();

protected:
    void onPreviousFailed(PendingOperation *operation, const QVariantHash &details);

private:
    QVariantHash m_errorDetails;
    bool m_finished;
    bool m_succeeded;
};

}

#endif // TELEGRAMQT_PENDING_OPERATION
