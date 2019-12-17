#include "ServerRpcOperation.hpp"

#include "Debug_p.hpp"
#include "RawStream.hpp"
#include "ServerRpcLayer.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"

namespace Telegram {

namespace Server {

RpcOperation::RpcOperation(RpcLayer *rpcLayer) :
    PendingOperation(rpcLayer),
    m_layer(rpcLayer),
    m_api(rpcLayer->api()),
    m_layerNumber(rpcLayer->activeLayerNumber())
{
}

void RpcOperation::setMessageId(quint64 messageId)
{
    m_messageId = messageId;
}

bool RpcOperation::sendRpcError(const RpcError &error)
{
    qDebug() << Q_FUNC_INFO << error.type() << error.reason() << error.argument() << error.message() << m_messageId;

    RawStreamEx output(RawStreamEx::WriteOnly);
    output << error;

    return layer()->sendRpcReply(this, output.getData());
}

bool RpcOperation::verifyHasUserOrWantedUser()
{
    if (!layer()->session()) {
        return false;
    }
    if (!layer()->session()->userOrWantedUserId()) {
        return false;
    }
    return true;
}

bool RpcOperation::processNotImplementedMethod(TLValue functionCode)
{
    qWarning() << "RPC Operation is not implemented:" << functionCode;
    return false;
}

//void ServerRpcOperation::sendReply(const QByteArray &buffer)
//{
//    RawStreamEx output(RawStream::WriteOnly);
//    output << TLValue::RpcResult;
//    output << m_messageId;
//    output << buffer;
//    output.getData();
//}

//void ServerRpcOperation::start()
//{

//}

} // Server namespace

} //Telegram namespace
