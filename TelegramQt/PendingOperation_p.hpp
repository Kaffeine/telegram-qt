#ifndef TELEGRAMQT_PENDING_OPERATION_PRIVATE_HPP
#define TELEGRAMQT_PENDING_OPERATION_PRIVATE_HPP

#include "PendingOperation.hpp"

namespace Telegram {

class PendingOperationPrivate
{
public:
    Q_DECLARE_PUBLIC(PendingOperation)

    explicit PendingOperationPrivate(PendingOperation *parent) :
        q_ptr(parent)
    {
    }

    virtual ~PendingOperationPrivate() = default;

    static const PendingOperationPrivate *get(const PendingOperation *op) { return op->d; }
    static PendingOperationPrivate *get(PendingOperation *op) { return op->d; }

    virtual QObject *toQObject() { return nullptr; }
    virtual const QObject *toQObject() const { return nullptr; }

    QVariantHash m_errorDetails;
    bool m_finished = false;
    bool m_succeeded = true;

    PendingOperation *q_ptr = nullptr;
};

} // Telegram namespace

#endif // TELEGRAMQT_PENDING_OPERATION_PRIVATE_HPP
