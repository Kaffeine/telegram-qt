#ifndef TELEGRAMQT_PENDING_OPERATION_PRIVATE
#define TELEGRAMQT_PENDING_OPERATION_PRIVATE

#include "PendingOperation.hpp"
#include "TLValues.hpp"

namespace Telegram {

class PendingOperation::Private
{
public:
    static const Private *get(const PendingOperation *op) { return op->d; }

    TLValue requestType() const { return m_requestType; }
    QByteArray requestData;
    TLValue m_requestType;

    template <typename T>
    bool readRpcResult(T *result);
};

//template<typename T>
//inline bool PendingOperation::Private::readRpcResult(T *result)
//{
//    inputStream() >> *result;
//    m_code = result->tlType;
//    m_succeed = result->isValid() && !inputStream().error();
//    return m_succeed;
//}

//class PendingOperation::Private : public

}

#endif //TELEGRAMQT_PENDING_OPERATION_PRIVATE
