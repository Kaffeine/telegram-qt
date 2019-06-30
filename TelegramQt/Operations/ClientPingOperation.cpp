#include "ClientPingOperation.hpp"

#include "ClientRpcLayer.hpp"
#include "ClientSettings.hpp"
#include "ClientConnection.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypes.hpp"

#include <QDateTime>
#include <QLoggingCategory>
#include <QTimer>

Q_LOGGING_CATEGORY(c_clientPingCategory, "telegram.client.ping", QtDebugMsg)

namespace Telegram {

namespace Client {

PingOperation::PingOperation(QObject *parent) :
    QObject(parent)
{
}

void PingOperation::ensureActive()
{
    if (!m_pingTimer) {
        qCDebug(c_clientPingCategory) << "startKeepAlive(): construct the timer";
        m_pingTimer = new QTimer(this);
        m_pingTimer->setSingleShot(true);
        connect(m_pingTimer, &QTimer::timeout, this, &PingOperation::onTimeToKeepAlive);
        m_pingTimer->start(m_settings->pingInterval());
        // The start is called right on connection, but we want to send our first ping after the pingInterval
        return;
    }

    m_pingTimer->start(m_settings->pingInterval());
}

void PingOperation::ensureInactive()
{
    if (m_pingTimer && m_pingTimer->isActive()) {
        qCDebug(c_clientPingCategory) << Q_FUNC_INFO;
        m_pingTimer->stop();
    }
}

void PingOperation::reset()
{
    // TODO: Reset ids on disconnected
    m_pingId = 0;
    m_pingMessageId = 0;
}

void PingOperation::onPingResent(quint64 oldMessageId, quint64 newMessageId)
{
    qCWarning(c_clientPingCategory) << Q_FUNC_INFO << "Ping operation resent";
    if (m_pingMessageId == oldMessageId) {
        m_pingMessageId = newMessageId;
    }
}

void PingOperation::onTimeToKeepAlive()
{
    if (m_pingMessageId) {
         qCWarning(c_clientPingCategory) << Q_FUNC_INFO << "Incomplete ping operation";
         emit pingFailed({{PendingOperation::c_text(), QLatin1String("The previous ping has no respond at the time for the next ping")}});
         return;
    }

    ++m_pingId;

    if (!m_pingRpcOperation) {
        m_pingRpcOperation = new PendingRpcOperation(this);
        connect(m_pingRpcOperation, &PendingRpcOperation::finished, this, &PingOperation::onPingRpcFinished);
        connect(m_pingRpcOperation, &PendingRpcOperation::resent, this, &PingOperation::onPingResent);
    }
    {
        Telegram::RawStream outputStream(Telegram::RawStream::WriteOnly);
        if (m_settings->serverDisconnectionAdditionalTime()) {
            // Server should close the connection after m_pingServerDisconnectionExtraTime ms more than our ping interval.
            const quint32 serverDisconnectTimeout = m_settings->pingInterval() + m_settings->serverDisconnectionAdditionalTime();
            outputStream << TLValue::PingDelayDisconnect;
            outputStream << m_pingId;
            outputStream << serverDisconnectTimeout;
        } else {
            outputStream << TLValue::Ping;
            outputStream << m_pingId;
        }
        m_pingRpcOperation->reuse(outputStream.getData());
        m_pingRpcOperation->setContentRelated(false);
    }
    m_pingMessageId = m_rpcLayer->sendRpc(m_pingRpcOperation);
    qCDebug(c_clientPingCategory) << "onTimeToKeepAlive(): send ping with id" << hex << m_pingId << ", messageId: " << m_pingMessageId;
    m_pingTimer->start(m_settings->pingInterval());
}

void PingOperation::onPingRpcFinished()
{
    if (m_pingTimer && !m_pingTimer->isActive()) {
        qCDebug(c_clientPingCategory) << "onPingRpcFinished(): ping timer is stopped, so ping result is not interested anymore";
        return;
    }
    if (!m_pingRpcOperation->isSucceeded()) {
        emit pingFailed(m_pingRpcOperation->errorDetails());
        return;
    }
    MTProto::Stream stream(m_pingRpcOperation->replyData());
    TLPong pong;
    stream >> pong;
    qCDebug(c_clientPingCategory) << "onPingRpcFinished() ping id:" << pong.pingId << "messageId:" << hex << pong.msgId << m_pingMessageId;
    if (!pong.isValid()) {
        emit pingFailed({{PendingOperation::c_text(), QLatin1String("Invalid ping reply")}});
        return;
    }
    if (m_pingMessageId != pong.msgId) {
        emit pingFailed({{PendingOperation::c_text(), QLatin1String("Unexpected message id")}});
        return;
    }
    if (m_pingId != pong.pingId) {
        emit pingFailed({{PendingOperation::c_text(), QLatin1String("Unexpected ping id")}});
        return;
    }
    m_pingMessageId = 0;
}

} // Client

} // Telegram namespace
