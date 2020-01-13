#include "DeclarativeOperation.hpp"
#include "DeclarativeClient.hpp"

#include <QTimer>
#include <QDebug>

namespace Telegram {

using namespace Client;

DeclarativeOperation::DeclarativeOperation(QObject *parent) :
    DeclarativeClientOperator(parent)
{
}

bool DeclarativeOperation::isSucceeded() const
{
    return m_operation && m_operation->isSucceeded();
}

QVariantHash DeclarativeOperation::errorDetails() const
{
    static const QVariantHash defaultError = {
        { PendingOperation::c_text(), QLatin1String("no operation") },
    };

    return m_operation ? m_operation->errorDetails() : defaultError;
}

void DeclarativeOperation::start()
{
//    m_running = true;
    emit started();
    startEvent();
}

void DeclarativeOperation::startEvent()
{
}

void DeclarativeOperation::setPendingOperation(PendingOperation *op)
{
    if (m_operation == op) {
        return;
    }
    m_operation = op;
    connect(op, &PendingOperation::finished, this, &DeclarativeOperation::onOperationFinished);
}

void DeclarativeOperation::onOperationFinished(PendingOperation *operation)
{
    if (operation->isSucceeded()) {
        // Operation is not succeeded until finished, so if it is finished
        // and succeeded then the state is changed
        emit succeededChanged();
    } else {
        emit failed(operation->errorDetails());
    }
    emit finished(operation->isSucceeded());
    emit errorDetailsChanged();
}

} // Telegram
