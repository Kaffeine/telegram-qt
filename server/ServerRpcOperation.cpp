#include "ServerRpcOperation.hpp"

#include "ServerRpcLayer.hpp"

#include "Debug_p.hpp"

namespace Telegram {

namespace Server {

RpcOperation::RpcOperation(RpcLayer *rpcLayer) :
    PendingOperation(rpcLayer),
    m_rpcLayer(rpcLayer),
    m_api(rpcLayer->api())
{
}

void RpcOperation::setRequestId(quint64 messageId)
{
    m_requestId = messageId;
}

bool RpcOperation::sendRpcError(const RpcError &error)
{
    qDebug() << Q_FUNC_INFO << error.type << error.reason << error.argument << error.message << m_requestId;
    return layer()->sendRpcError(error, m_requestId);
}

//void ServerRpcOperation::sendReply(const QByteArray &buffer)
//{
//    CRawStreamEx output(CRawStream::WriteOnly);
//    output << TLValue::RpcResult;
//    output << m_messageId;
//    output << buffer;
//    output.getData();
//}

//void ServerRpcOperation::start()
//{

//}

} // Server

} //Telegram