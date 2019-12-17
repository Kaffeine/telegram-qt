#include "ServerRpcOperation.hpp"

#include "ServerRpcLayer.hpp"
#include "MTProto/Stream.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

namespace Telegram {

namespace Server {

template<typename TLType>
bool RpcOperation::sendRpcReply(const TLType &reply)
{
    MTProto::Stream output(MTProto::Stream::WriteOnly);
    output << reply;
#ifdef DEVELOPER_BUILD
    qDebug() << this << reply;
#endif
    return layer()->sendRpcReply(this, output.getData());
}

} // Server namespace

} //Telegram namespace
