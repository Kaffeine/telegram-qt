#include "ServerRpcOperation.hpp"

#include "ServerRpcLayer.hpp"
#include "CTelegramStream.hpp"

namespace Telegram {

namespace Server {

template<typename TLType>
bool RpcOperation::sendRpcReply(const TLType &reply)
{
    CTelegramStream output(CTelegramStream::WriteOnly);
    output << reply;
    return layer()->sendRpcReply(output.getData(), m_requestId);
}

} // Server

} //Telegram
