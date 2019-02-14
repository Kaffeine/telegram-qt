#include "ServerRpcOperation.hpp"

#include "ServerRpcLayer.hpp"
#include "CTelegramStream.hpp"

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

namespace Telegram {

namespace Server {

template<typename TLType>
bool RpcOperation::sendRpcReply(const TLType &reply)
{
    CTelegramStream output(CTelegramStream::WriteOnly);
    output << reply;
#ifdef DEVELOPER_BUILD
    qDebug() << this << reply;
#endif
    return layer()->sendRpcReply(output.getData(), m_requestId);
}

} // Server namespace

} //Telegram namespace
