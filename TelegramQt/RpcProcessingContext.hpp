#ifndef RPC_PROCESSING_CONTEXT_HPP
#define RPC_PROCESSING_CONTEXT_HPP

#include "CTelegramStream.hpp"

class RpcProcessingContext
{
public:
    RpcProcessingContext(CTelegramStream &inputStream, quint64 requestId = 0, const QByteArray &requestData = QByteArray());

    bool isValid() const;

    CTelegramStream &inputStream() { return m_inputStream; }

    quint64 requestId() const { return m_id; }
    bool hasRequestData() const;
    QByteArray requestData() const { return m_requestData; }
    TLValue requestType() const;

    bool isSucceed() const { return m_succeed; }
    void setSucceed(bool isSucceed);

    TLValue readCode() const { return m_code; }
    void setReadCode(const TLValue code);

    template <typename T>
    bool readRpcResult(T *result);

    // Extra API
    QString userNameFromRequest() const;

protected:
    CTelegramStream &m_inputStream;
    CTelegramStream m_storedStream;
    quint64 m_id;
    QByteArray m_requestData;
    bool m_succeed;
    TLValue m_code;
    TLValue m_requestMethodId;
};

template<typename T>
inline bool RpcProcessingContext::readRpcResult(T *result)
{
    inputStream() >> *result;
    m_code = result->tlType;
    m_succeed = result->isValid() && !inputStream().error();
    return m_succeed;
}


#endif // RPC_PROCESSING_CONTEXT_HPP
