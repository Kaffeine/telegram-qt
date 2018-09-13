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
    bool isFailed() const;

    static QString c_text();

    QVariantHash errorDetails() const;

    template <typename OperationType>
    static OperationType *failOperation(const QVariantHash &failDetails, QObject *parent = nullptr)
    {
        OperationType *op = new OperationType();
        op->setParent(parent);
        op->setDelayedFinishedWithError(failDetails);
        return op;
    }

    template <typename OperationType>
    static OperationType *failOperation(const QString &failDescription, QObject *parent = nullptr)
    {
        return failOperation<OperationType>({{ c_text(), failDescription}}, parent);
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

    static PendingOperation *failOperation(const QString &failDescription, QObject *parent = nullptr)
    {
        return failOperation<PendingOperation>({{ c_text(), failDescription}}, parent);
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

inline bool PendingOperation::isFinished() const
{
    return m_finished;
}

inline bool PendingOperation::isSucceeded() const
{
    return m_finished && m_succeeded;
}

inline bool PendingOperation::isFailed() const
{
    return m_finished && !m_succeeded;
}

inline QVariantHash PendingOperation::errorDetails() const
{
    return m_errorDetails;
}

}

#endif // TELEGRAMQT_PENDING_OPERATION
