#include "PendingRpcOperation.hpp"

#include "CRawStream.hpp"
#include "RpcError.hpp"
#include "TLValues.hpp"

namespace Telegram {

namespace Client {

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
                                 {QStringLiteral("RpcRequestType"), TLValue::firstFromArray(m_requestData).toString() },
                                 {QStringLiteral("RpcErrorCode"), m_error->type },
                                 {QStringLiteral("RpcErrorMessage"), m_error->message }
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

} // Client namespace

} // Telegram namespace
