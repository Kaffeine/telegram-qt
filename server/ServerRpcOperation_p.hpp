#ifndef TELEGRAM_SERVER_RPC_OPERATION_P_HPP
#define TELEGRAM_SERVER_RPC_OPERATION_P_HPP

#include "ServerRpcOperation.hpp"

#include "ServerRpcLayer.hpp"
#include "MTProto/Stream.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(lcServerRpcDump)

namespace Telegram {

namespace Server {

template<typename TLType>
bool RpcOperation::sendRpcReply(const TLType &reply)
{
    MTProto::Stream output(MTProto::Stream::WriteOnly);
    output << reply;
#ifdef DEVELOPER_BUILD
    qCDebug(lcServerRpcDump) << this << reply;
#endif
    return layer()->sendRpcReply(this, output.getData());
}

} // Server namespace

} //Telegram namespace

#endif // TELEGRAM_SERVER_RPC_OPERATION_P_HPP
