#include "RpcProcessingContext.hpp"

RpcProcessingContext::RpcProcessingContext(CTelegramStream &stream, quint64 requestId, const QByteArray &requestData) :
    m_inputStream(stream),
    m_storedStream(requestData),
    m_id(requestId),
    m_requestData(requestData),
    m_succeed(false)
{
    if (hasRequestData()) {
        m_storedStream >> m_requestMethodId;
    }
}

bool RpcProcessingContext::isValid() const
{
    return !m_storedStream.error();
}

bool RpcProcessingContext::hasRequestData() const
{
    return !m_requestData.isEmpty();
}

TLValue RpcProcessingContext::requestType() const
{
    return m_requestMethodId;
}

void RpcProcessingContext::setSucceed(bool succeed)
{
    m_succeed = succeed;
}

void RpcProcessingContext::setReadCode(const TLValue code)
{
    m_code = code;
}

QString RpcProcessingContext::userNameFromRequest() const
{
    if (!hasRequestData()) {
        return QString();
    }

    CTelegramStream outputStream(requestData());

    TLValue requestType;
    outputStream >> requestType;

    switch (requestType) {
    case TLValue::AccountCheckUsername:
    case TLValue::AccountUpdateUsername:
    case TLValue::ContactsResolveUsername:
        break;
    default:
        return QString();
    }

    QString name;
    outputStream >> name;
    return name;
}
