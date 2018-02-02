#include "DeclarativeOperation.hpp"
#include "DeclarativeClient.hpp"

#include <QTimer>
#include <QDebug>

namespace Telegram {

using namespace Client;

DeclarativeOperation::DeclarativeOperation(QObject *parent) :
    QObject(parent)
{
}

DeclarativeClient *DeclarativeOperation::target() const
{
    return m_target;
}

bool DeclarativeOperation::succeed() const
{
    return m_succeed;
}

void DeclarativeOperation::start()
{
//    m_running = true;
    emit started();
    startEvent();
}

void DeclarativeOperation::setTarget(DeclarativeClient *target)
{
    m_target = target;
}

void DeclarativeOperation::startEvent()
{
}

void DeclarativeOperation::setPendingOperation(PendingOperation *op)
{
    connect(op, &PendingOperation::succeeded, this, &DeclarativeOperation::onOperationSucceed);
    connect(op, &PendingOperation::failed, this, &DeclarativeOperation::onOperationFailed);
}

void DeclarativeOperation::onOperationSucceed(PendingOperation *op)
{
    Q_UNUSED(op)
    emit succeeded();
    setSucceed(true);
    emit finished();
}

void DeclarativeOperation::onOperationFailed(PendingOperation *op, const QVariantHash &details)
{
    Q_UNUSED(op)
    emit failed(details);
    setSucceed(false);
    emit finished();
}

void DeclarativeOperation::setSucceed(bool succeed)
{
    if (m_succeed == succeed) {
        return;
    }
    m_succeed = succeed;
    emit succeedChanged(succeed);
}

} // Telegram
