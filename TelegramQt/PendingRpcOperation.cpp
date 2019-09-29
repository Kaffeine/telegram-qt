#include "PendingRpcOperation.hpp"

#include "RawStream.hpp"
#include "RpcError.hpp"
#include "MTProto/TLValues.hpp"

namespace Telegram {

namespace Client {

PendingRpcOperation::PendingRpcOperation(QObject *parent) :
    PendingOperation(parent)
{
    connect(this, &PendingOperation::finished, [this]() { emit PendingRpcOperation::finished(this); });
}

PendingRpcOperation::PendingRpcOperation(const QByteArray &requestData, QObject *parent) :
    PendingRpcOperation(parent)
{
    setRequestData(requestData);
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
        RawStreamEx stream(data);
        stream >> *m_error;
        setFinishedWithError({
                                 {QStringLiteral("RpcRequestType"), TLValue::firstFromArray(m_requestData).toString() },
                                 {QStringLiteral("RpcErrorCode"), m_error->type() },
                                 {QStringLiteral("RpcErrorMessage"), m_error->message() }
                             });
    } else {
        setFinished();
    }
}

void PendingRpcOperation::clearResult()
{
    m_replyData.clear();
    m_contentRelated = true;
    if (m_error) {
        delete m_error;
        m_error = nullptr;
    }
    PendingOperation::clearResult();
}

void PendingRpcOperation::reuse(const QByteArray &requestData)
{
    clearResult();
    setRequestData(requestData);
}

void PendingRpcOperation::setRequestData(const QByteArray &requestData)
{
    m_requestData = requestData;
    if (!m_requestData.isEmpty()) {
        setObjectName(QLatin1String("RPC/") + TLValue::firstFromArray(m_requestData).toString());
    }
}

} // Client namespace

} // Telegram namespace
