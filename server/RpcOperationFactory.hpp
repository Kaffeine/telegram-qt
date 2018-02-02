#ifndef RPC_OPERATION_FACTORY_HPP
#define RPC_OPERATION_FACTORY_HPP

#include <QObject>

class RpcProcessingContext;

namespace Telegram {

namespace Server {

class RpcLayer;
class RpcOperation;

class RpcOperationFactory
{
public:
    virtual RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) = 0;
};

} // Server

} // Telegram

#endif // RPC_OPERATION_FACTORY_HPP
