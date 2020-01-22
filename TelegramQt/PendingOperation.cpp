#include "PendingOperation.hpp"
#include "PendingOperation_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_pendingOperations, "telegram.operations", QtDebugMsg)

namespace Telegram {

PendingOperation::PendingOperation(PendingOperationPrivate *priv, QObject *parent) :
    QObject(parent),
    d(priv)
{
}

PendingOperation::PendingOperation(QObject *parent) :
    PendingOperation(new PendingOperationPrivate(this), parent)
{
}

PendingOperation::~PendingOperation()
{
    qCDebug(c_pendingOperations) << "deleted()" << this;
    delete d;
}

bool PendingOperation::isFinished() const
{
    Q_D(const PendingOperation);
    return d->m_finished;
}

bool PendingOperation::isSucceeded() const
{
    Q_D(const PendingOperation);
    return d->m_finished && d->m_succeeded;
}

bool PendingOperation::isFailed() const
{
    Q_D(const PendingOperation);
    return d->m_finished && !d->m_succeeded;
}

QVariantHash PendingOperation::errorDetails() const
{
    Q_D(const PendingOperation);
    return d->m_errorDetails;
}

QString PendingOperation::c_text()
{
    // Keep this as QStringLiteral because it is a short string used everywhere.
    return QStringLiteral("text");
}

void PendingOperation::start()
{
    qCDebug(c_pendingOperations) << this << "start()";
    startImplementation();
}

void PendingOperation::startLater()
{
    qCDebug(c_pendingOperations) << this << "startLater()";
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    QMetaObject::invokeMethod(this, [this] (){ start(); }, Qt::QueuedConnection);
#else
    QMetaObject::invokeMethod(this, "start", Qt::QueuedConnection);
#endif
}

void PendingOperation::finishLater()
{
    qCDebug(c_pendingOperations) << this << "startLater()";
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    QMetaObject::invokeMethod(this, [this] (){ setFinished(); }, Qt::QueuedConnection);
#else
    QMetaObject::invokeMethod(this, "setFinished", Qt::QueuedConnection);
#endif
}

void PendingOperation::deleteLater()
{
    qCDebug(c_pendingOperations) << "deleteLater()" << this;
    QObject::deleteLater();
}

void PendingOperation::deleteOnFinished()
{
    connect(this, &PendingOperation::finished, this, &PendingOperation::deleteLater);
}

void PendingOperation::runAfter(PendingOperation *operation)
{
    if (!operation) {
        qCCritical(c_pendingOperations) << this << "runAfter(nullptr)";
        return;
    }
    if (operation->isFinished()) {
        if (operation->isSucceeded()) {
            qCDebug(c_pendingOperations) << this << "runAfter(" << operation << "; succeeded)";
            startLater();
        } else {
            qCDebug(c_pendingOperations) << this << "runAfter(" << operation << "; failed)";
            setDelayedFinishedWithError(operation->errorDetails());
        }
    } else {
        qCDebug(c_pendingOperations) << this << "runAfter(" << operation << ")";
        connect(operation, &PendingOperation::succeeded, this, &PendingOperation::start);
        connect(operation, &PendingOperation::failed, this, &PendingOperation::onPreviousFailed);
    }
}

void PendingOperation::setFinished()
{
    if (d->m_finished) {
        qCWarning(c_pendingOperations) << "setFinished() called for an already finished operation" << this;
        return;
    }
    d->m_finished = true;
    if (d->m_succeeded) {
        qCDebug(c_pendingOperations) << this << "setFinished(succeeded)";
        emit succeeded(this);
    } else {
        qCDebug(c_pendingOperations) << this << "setFinished(failed)";
        emit failed(this, d->m_errorDetails);
    }
    emit finished(this);
}

void PendingOperation::setFinishedWithError(const QVariantHash &details)
{
    qCDebug(c_pendingOperations) << this << "setFinishedWithError(" << details << ")";
    d->m_succeeded = false;
    d->m_errorDetails = details;
    setFinished();
}

void PendingOperation::setDelayedFinishedWithError(const QVariantHash &details)
{
    QMetaObject::invokeMethod(this, "setFinishedWithError", Qt::QueuedConnection, Q_ARG(QVariantHash, details)); // Invoke after return
}

void PendingOperation::setOperationName(const char *name)
{
    setObjectName(QString::fromLatin1(name));
}

void PendingOperation::clearResult()
{
    qCDebug(c_pendingOperations) << "clearResult()" << this;
    d->m_finished = false;
    d->m_succeeded = true;
    d->m_errorDetails.clear();
}

void PendingOperation::onPreviousFailed(PendingOperation *operation, const QVariantHash &details)
{
    Q_UNUSED(operation)
    setFinishedWithError(details);
}

SucceededPendingOperation::SucceededPendingOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void SucceededPendingOperation::startImplementation()
{
    finishLater();
}

} // Telegram namespace
