#ifndef TELEGRAMQT_PENDING_OPERATION
#define TELEGRAMQT_PENDING_OPERATION

#include "telegramqt_global.h"

#include <QObject>
#include <QVariantHash>

namespace Telegram {

class PendingOperationPrivate;
class TELEGRAMQT_EXPORT PendingOperation : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PendingOperation)
public:
    explicit PendingOperation(QObject *parent = nullptr);
    ~PendingOperation() override;
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

    template<typename T, typename M, typename... Arg>
    static void callMember(T *obj, M method, Arg... arg)
    {
        (obj->*method)(arg...);
    }

    static PendingOperation *failOperation(const QVariantHash &failDetails, QObject *parent = nullptr)
    {
        return failOperation<PendingOperation>(failDetails, parent);
    }

    static PendingOperation *failOperation(const QString &failDescription, QObject *parent = nullptr)
    {
        return failOperation<PendingOperation>({{ c_text(), failDescription}}, parent);
    }

#if Q_CC_GNU && (Q_CC_GNU < 409)
    // Workaround https://gcc.gnu.org/bugzilla/show_bug.cgi?id=55914
    // Remove this once we require GCC 4.9+
    template<typename Receiver, typename ReceiverMethod>
    void connectToFinished(Receiver *obj, ReceiverMethod method)
    {
        connect(this, &PendingOperation::finished, obj, [obj, method] () {
            callMember(obj, method);
        });
    }
    template<typename Receiver, typename ReceiverMethod, typename Arg1>
    void connectToFinished(Receiver *obj, ReceiverMethod method, Arg1 arg1)
    {
        connect(this, &PendingOperation::finished, obj, [obj, method, arg1] () {
            callMember(obj, method, arg1);
        });
    }
    template<typename Receiver, typename ReceiverMethod, typename Arg1, typename Arg2>
    void connectToFinished(Receiver *obj, ReceiverMethod method, Arg1 arg1, Arg2 arg2)
    {
        connect(this, &PendingOperation::finished, obj, [obj, method, arg1, arg2] () {
            callMember(obj, method, arg1, arg2);
        });
    }
    template<typename Receiver, typename ReceiverMethod, typename Arg1, typename Arg2,
             typename Arg3>
    void connectToFinished(Receiver *obj, ReceiverMethod method, Arg1 arg1, Arg2 arg2,
                           Arg3 arg3)
    {
        connect(this, &PendingOperation::finished, obj, [obj, method, arg1, arg2, arg3] () {
            callMember(obj, method, arg1, arg2, arg3);
        });
    }
    template<typename Receiver, typename ReceiverMethod, typename Arg1, typename Arg2,
             typename Arg3, typename Arg4>
    void connectToFinished(Receiver *obj, ReceiverMethod method, Arg1 arg1, Arg2 arg2,
                           Arg3 arg3, Arg4 arg4)
    {
        connect(this, &PendingOperation::finished, obj, [obj, method, arg1, arg2, arg3, arg4] () {
            callMember(obj, method, arg1, arg2, arg3, arg4);
        });
    }
#else
    template<typename Receiver, typename ReceiverMethod, typename ...Args>
    void connectToFinished(Receiver *obj, ReceiverMethod method, Args ...args)
    {
        connect(this, &PendingOperation::finished, obj, [obj, method, args...] () {
            callMember(obj, method, args...);
        });
    }
#endif
    template<typename Receiver, typename ReceiverMethod, typename ...Args>
    void invokeOnFinished(Receiver *obj, ReceiverMethod method, Args ...args)
    {
        if (isFinished()) {
            callMember(obj, method, args...);
        } else {
            connectToFinished(obj, method, args...);
        }
    }

Q_SIGNALS:
    void finished(PendingOperation *operation);
    void succeeded(PendingOperation *operation);
    void failed(PendingOperation *operation, const QVariantHash &details);

public Q_SLOTS:
    void start();
    void startLater();
    void finishLater();
    void deleteLater();
    void deleteOnFinished();

    void runAfter(PendingOperation *operation);

    void setFinished();
    void setFinishedWithError(const QVariantHash &details);
    void setFinishedWithTextError(const QString &text);
    void setDelayedFinishedWithError(const QVariantHash &details);
    void setOperationName(const char *name);
    virtual void clearResult();

protected:
    explicit PendingOperation(PendingOperationPrivate *priv, QObject *parent = nullptr);

    virtual void startImplementation() { }

    void onPreviousFailed(PendingOperation *operation, const QVariantHash &details);

protected:
    Q_DECLARE_PRIVATE_D(d, PendingOperation)
    PendingOperationPrivate *d = nullptr;
};

inline void PendingOperation::setFinishedWithTextError(const QString &text)
{
    setFinishedWithError({{PendingOperation::c_text(), text}});
}

class SucceededPendingOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit SucceededPendingOperation(QObject *parent = nullptr);

    void startImplementation() override;
};

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_OPERATION
