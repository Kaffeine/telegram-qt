#ifndef TELEGRAMQT_PENDING_OPERATION_PRIVATE_HPP
#define TELEGRAMQT_PENDING_OPERATION_PRIVATE_HPP

#include "PendingOperation.hpp"

namespace Telegram {

class PendingOperationPrivate
{
public:
    virtual ~PendingOperationPrivate() = default;

    static const PendingOperationPrivate *get(const PendingOperation *op) { return op->d; }

    virtual QObject *toQObject() { return nullptr; }
    virtual const QObject *toQObject() const { return nullptr; }
};

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_OPERATION_PRIVATE_HPP
