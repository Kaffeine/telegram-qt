#include "PendingVariant.hpp"

namespace Telegram {

PendingVariant::PendingVariant(QObject *parent)
    : PendingOperation(parent)
{
}

void PendingVariant::setResult(const QVariant &result)
{
    m_result = result;
    setFinished();
}

} // Telegram
