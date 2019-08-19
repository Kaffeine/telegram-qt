#ifndef RPC_OPERATION_FACTORY_HPP
#define RPC_OPERATION_FACTORY_HPP

#include <QObject>

namespace Telegram {

namespace Server {

class RpcLayer;
class RpcOperation;
class RpcProcessingContext;

class RpcOperationFactory
{
public:
    virtual ~RpcOperationFactory() = default;

    virtual RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) = 0;
    virtual bool needLocalUser() const { return true; }
};

} // Server namespace

} // Telegram namespace

#endif // RPC_OPERATION_FACTORY_HPP
