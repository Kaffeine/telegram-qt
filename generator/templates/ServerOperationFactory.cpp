#include "__VAR_GROUP_NAME__OperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_serverAuthRpcCategory, "telegram.server.rpc.__VAR_GROUP_NAME_SMALL__", QtWarningMsg)

namespace Telegram {

namespace Server {

// Generated process methods
// End of generated process methods

// Generated run methods
// End of generated run methods

void __VAR_GROUP_NAME__RpcOperation::setRunMethod(__VAR_GROUP_NAME__RpcOperation::RunMethod method)
{
    m_runMethod = method;
}

__VAR_GROUP_NAME__RpcOperation::ProcessingMethod __VAR_GROUP_NAME__RpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *__VAR_GROUP_NAME__OperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<__VAR_GROUP_NAME__RpcOperation>(layer, context);
}

} // Server

} // Telegram
