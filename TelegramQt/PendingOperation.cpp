#include "PendingOperation.hpp"

#include "CRawStream.hpp"
#include "RpcError.hpp"
#include "TLValues.hpp"

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

namespace Telegram {

PendingOperation::PendingOperation(QObject *parent) :
    QObject(parent),
    m_finished(false),
    m_succeeded(true)
{
}

bool PendingOperation::isFinished() const
{
    return m_finished;
}

bool PendingOperation::isSucceeded() const
{
    return m_finished && m_succeeded;
}

QVariantHash PendingOperation::errorDetails() const
{
    return m_errorDetails;
}

void PendingOperation::startLater()
{
    QMetaObject::invokeMethod(this, "start", Qt::QueuedConnection);
}

void PendingOperation::runAfter(PendingOperation *operation)
{
    connect(operation, &PendingOperation::succeeded, this, &PendingOperation::start);
    connect(operation, &PendingOperation::failed, this, &PendingOperation::onPreviousFailed);
}

void PendingOperation::setFinished()
{
    qDebug() << "finished" << this;
    if (m_finished) {
        qWarning() << "Operation is already finished" << this;
        return;
    }
    m_finished = true;
    if (m_succeeded) {
        emit succeeded(this);
    }
    emit finished(this);
}

void PendingOperation::setFinishedWithError(const QVariantHash &details)
{
    qDebug() << "finished with error" << this << details;
    m_succeeded = false;
    m_errorDetails = details;
    emit failed(this, details);
    setFinished();
}

void PendingOperation::setDelayedFinishedWithError(const QVariantHash &details)
{
    QMetaObject::invokeMethod(this, "setFinishedWithError", Qt::QueuedConnection, Q_ARG(QVariantHash, details)); // Invoke after return
}

void PendingOperation::clearResult()
{
    m_finished = false;
    m_succeeded = true;
    m_errorDetails.clear();
}

void PendingOperation::onPreviousFailed(PendingOperation *operation, const QVariantHash &details)
{
    Q_UNUSED(operation)
    setFinishedWithError(details);
}

PendingRpcOperation::PendingRpcOperation(const QByteArray &requestData, QObject *parent) :
    PendingOperation(parent),
    m_requestData(requestData)
{
    connect(this, &PendingOperation::finished, [this]() { emit PendingRpcOperation::finished(this); });
}

PendingRpcOperation::~PendingRpcOperation()
{
    if (m_error) {
        delete m_error;
    }
}

void PendingRpcOperation::setFinishedWithReplyData(const QByteArray &data)
{
    m_replyData = data;
    TLValue answerValue = TLValue::firstFromArray(data);
    if (answerValue == TLValue::RpcError) {
        if (!m_error) {
            m_error = new RpcError();
        }
        CRawStreamEx stream(data);
        stream >> *m_error;
        setFinishedWithError({
                                 {QStringLiteral("RpcErrorCode"), m_error->type },
                                 {QStringLiteral("RpcError"), m_error->message }
                             });
    } else {
        setFinished();
    }
}

void PendingRpcOperation::clearResult()
{
    m_replyData.clear();
    if (m_error) {
        delete m_error;
        m_error = nullptr;
    }
    PendingOperation::clearResult();
}

} // Telegram namespace
