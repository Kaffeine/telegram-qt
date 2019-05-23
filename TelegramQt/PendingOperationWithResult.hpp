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

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_OPERATION_WITH_RESULT
