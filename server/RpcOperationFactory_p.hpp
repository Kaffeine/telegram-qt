#ifndef RPC_OPERATION_FACTORY_PRIVATE_HPP
#define RPC_OPERATION_FACTORY_PRIVATE_HPP

#include "RpcOperationFactory.hpp"
#include "RpcProcessingContext.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

template <typename T>
RpcOperation *processRpcCallImpl(RpcLayer *layer, RpcProcessingContext &context)
{
    bool (T::* const method)(RpcProcessingContext &) = T::getMethodForRpcFunction(context.readCode());
    if (!method) {
        return nullptr;
    }
    qDebug() << Q_FUNC_INFO << "Process" << context.readCode().toString() << "with messageId" << context.requestId();
    T *operation = new T(layer);
    operation->setRequestId(context.requestId());
    (operation->*method)(context);
    return operation;
}

} // Server namespace

} // Telegram namespace

#endif // RPC_OPERATION_FACTORY_PRIVATE_HPP
