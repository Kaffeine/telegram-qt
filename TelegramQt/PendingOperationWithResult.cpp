#include "PendingOperationWithResult.hpp"

#include <QLoggingCategory>

namespace Telegram {

PendingVoidOperation::PendingVoidOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void PendingVoidOperation::setFinished()
{
    PendingOperation::setFinished();
}

void PendingVoidOperation::finishLater()
{
    PendingOperation::finishLater();
}

} // Telegram namespace
