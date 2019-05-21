#ifndef TELEGRAMQT_PENDING_OPERATION_WITH_RESULT
#define TELEGRAMQT_PENDING_OPERATION_WITH_RESULT

#include "PendingOperation.hpp"

namespace Telegram {

class PendingVoidOperation : public PendingOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(PendingVoidOperation)
public:
    explicit PendingVoidOperation(QObject *parent);

public Q_SLOTS:
    void setFinished();
    void finishLater();
};

template <typename Result>
class PendingOperationWithResult : public PendingOperation
{
public:
    PendingOperationWithResult(QObject *parent)
        : PendingOperation(parent)
    {
    }
    Result getResult() const;

    void setFinished(const Result &result);
};

class PendingBoolOperation : public PendingOperationWithResult<bool>
{
    Q_OBJECT
public:
     PendingBoolOperation(QObject *parent)
         : PendingOperationWithResult(parent)
     {
     }
};

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_OPERATION_WITH_RESULT
