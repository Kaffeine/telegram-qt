#ifndef __VAR_GROUP_NAME_CAPITAL___OPERATION_FACTORY_HPP
#define __VAR_GROUP_NAME_CAPITAL___OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class __VAR_GROUP_NAME__RpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(__VAR_GROUP_NAME__RpcOperation)
public:
    explicit __VAR_GROUP_NAME__RpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processAccountGetPassword(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAccountGetPassword();
    // End of generated run methods

    using RunMethod = void (__VAR_GROUP_NAME__RpcOperation::*)();
    using ProcessingMethod = bool (__VAR_GROUP_NAME__RpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    // End of generated RPC members
};

class __VAR_GROUP_NAME__OperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // __VAR_GROUP_NAME_CAPITAL___OPERATION_FACTORY_HPP
