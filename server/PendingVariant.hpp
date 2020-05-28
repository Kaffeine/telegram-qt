#ifndef TELEGRAMQT_PENDING_VARIANT_HPP
#define TELEGRAMQT_PENDING_VARIANT_HPP

#include "PendingOperation.hpp"

namespace Telegram {

class PendingVariant : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingVariant(QObject *parent = nullptr);

    QVariant result() const { return m_result; }
    void setResult(const QVariant &result);

protected:
    QVariant m_result;
};

} // Telegram

#endif // TELEGRAMQT_PENDING_VARIANT_HPP
