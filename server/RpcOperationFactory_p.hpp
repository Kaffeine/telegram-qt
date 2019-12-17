#ifndef RPC_OPERATION_FACTORY_PRIVATE_HPP
#define RPC_OPERATION_FACTORY_PRIVATE_HPP

#include "RpcOperationFactory.hpp"
#include "RpcProcessingContext.hpp"
#include "RpcError.hpp"
#include "ServerRpcOperation.hpp"

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
    qDebug() << "processRpcCallImpl:" << context.readCode().toString() << "with messageId" << context.messageId();
    T *operation = new T(layer);
    bool fetchResult = (operation->*method)(context);
    RpcOperation *result = operation;
    result->setMessageId(context.messageId());
    if (!fetchResult) {
        RpcError error(RpcError::InputFetchError);
        result->sendRpcError(error);
        result->deleteLater();
        result->setFinishedWithError({{RpcOperation::c_text(), error.message()}});
        return nullptr;
    }
    return result;
}

} // Server namespace

} // Telegram namespace

#endif // RPC_OPERATION_FACTORY_PRIVATE_HPP
