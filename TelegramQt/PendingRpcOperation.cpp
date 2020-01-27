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

QString PendingRpcOperation::c_rpcErrorRequestKey()
{
    static const QString key = QLatin1String("rpc-error-request");
    return key;
}

QString PendingRpcOperation::c_rpcErrorCodeKey()
{
    static const QString key = QLatin1String("rpc-error-code");
    return key;
}

QString PendingRpcOperation::c_rpcErrorMessageKey()
{
    static const QString key = QLatin1String("rpc-error-message");
    return key;
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
        const QVariantHash details = {
            { c_rpcErrorRequestKey(), TLValue::firstFromArray(m_requestData).toString() },
            { c_rpcErrorCodeKey(), m_error->type() },
            { c_rpcErrorMessageKey(), m_error->message() },
        };
        setFinishedWithError(details);
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
