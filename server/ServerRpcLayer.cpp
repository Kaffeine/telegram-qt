#include "ServerRpcLayer.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "Debug_p.hpp"
#include "IgnoredMessageNotification.hpp"
#include "TelegramServerUser.hpp"
#include "RpcProcessingContext.hpp"
#include "RpcError.hpp"
#include "ServerRpcOperation.hpp"
#include "RpcOperationFactory.hpp"

#include "Session.hpp"
#include "ServerApi.hpp"

#include "MTProto/MessageHeader.hpp"

#include "CTelegramStream.hpp"
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_serverRpcLayerCategory, "telegram.server.rpclayer", QtDebugMsg)

template <typename T>
class StackValue
{
public:
    StackValue(QStack<T> *stack, const T value) :
        m_stack(stack)
    {
        m_stack->push(value);
    }
    ~StackValue()
    {
        m_stack->pop();
    }
private:
    QStack<T> *m_stack;
};

namespace Telegram {

namespace Server {

RpcLayer::RpcLayer(QObject *parent) :
    BaseRpcLayer(parent)
{
}

ServerApi *RpcLayer::api()
{
    return m_api;
}

void RpcLayer::setServerApi(ServerApi *api)
{
    m_api = api;
}

User *RpcLayer::getUser() const
{
    return m_session ? m_session->user() : nullptr;
}

quint64 RpcLayer::sessionId() const
{
    return m_session ? m_session->sessionId : 0;
}

Session *RpcLayer::session() const
{
    return m_session;
}

void RpcLayer::setSession(Session *session)
{
    m_session = session;
}

void RpcLayer::setRpcFactories(const QVector<RpcOperationFactory *> &rpcFactories)
{
    m_operationFactories = rpcFactories;
}

bool RpcLayer::processMTProtoMessage(const MTProto::Message &message)
{
    TLValue requestValue = message.firstValue();
    qCDebug(c_serverRpcLayerCategory) << Q_FUNC_INFO << requestValue.toString();

    switch (requestValue) {
    case TLValue::InitConnection:
        return processInitConnection(message.skipTLValue());
    case TLValue::InvokeWithLayer:
        return processInvokeWithLayer(message.skipTLValue());
    case TLValue::MsgContainer:
        return processMsgContainer(message.skipTLValue());
    default:
        break;
    }

    MTProto::Stream stream(message.data);
    RpcProcessingContext context(stream, message.messageId);

    context.inputStream() >> requestValue;
    context.setReadCode(requestValue);
    RpcOperation *op = nullptr;
    for (RpcOperationFactory *f : m_operationFactories) {
        op = f->processRpcCall(this, context);
        if (op) {
            break;
        }
    }
    if (!op) {
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << requestValue.toString() << "is not processed!";
        return false;
    }
    op->startLater();
    return true;
}

bool RpcLayer::processInitConnection(const MTProto::Message &message)
{
    MTProto::Stream stream(message.data);
    quint32 appId;
    QString deviceInfo;
    QString osInfo;
    QString appVersion;
#if TELEGRAMQT_LAYER >= 67
    QString systemLanguage;
    QString languagePack;
#endif
    QString languageCode;
    stream >> appId;
    stream >> deviceInfo;
    stream >> osInfo;
    stream >> appVersion;
#if TELEGRAMQT_LAYER >= 67
    if (activeLayer() >= 67) {
        stream >> systemLanguage;
        // If the pack is not registered on server, raise CONNECTION_LANG_PACK_INVALID RPC Error
        stream >> languagePack;
    }
#endif
    stream >> languageCode;

    qDebug() << Q_FUNC_INFO << deviceInfo << osInfo << appId << appVersion << languageCode;
    if (stream.error()) {
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << "Invalid read!";
        return false;
    }
    session()->setLayer(activeLayer());
    session()->appId = appId;
    session()->appVersion = appVersion;
    session()->languageCode = languageCode;
    session()->deviceInfo = deviceInfo;
    session()->osInfo = osInfo;
    MTProto::Message innerMessage = message;
    innerMessage.data = stream.readAll();
    return processMTProtoMessage(innerMessage);
}

bool RpcLayer::processInvokeWithLayer(const MTProto::Message &message)
{
    MTProto::Stream stream(message.data);
    quint32 layer = 0;
    stream >> layer;
    qCDebug(c_serverRpcLayerCategory) << Q_FUNC_INFO << "InvokeWithLayer" << layer;
    StackValue<quint32> layerValue(&m_invokeWithLayer, layer);
    MTProto::Message innerMessage = message;
    innerMessage.data = stream.readAll();
    return processMTProtoMessage(innerMessage);
}

bool RpcLayer::sendRpcError(const RpcError &error, quint64 messageId)
{
    CTelegramStream output(CTelegramStream::WriteOnly);
    output << error;
    return sendRpcReply(output.getData(), messageId);
}

bool RpcLayer::sendRpcReply(const QByteArray &reply, quint64 messageId)
{
#define DUMP_SERVER_RPC_PACKETS
#ifdef DUMP_SERVER_RPC_PACKETS
    qDebug() << "Server: Answer for message" << messageId;
    qDebug().noquote() << "Server: RPC Reply bytes:" << reply.size() << reply.toHex();
#endif
    CRawStream output(CRawStream::WriteOnly);
    output << TLValue::RpcResult;
    output << messageId;
    if (reply.size() > 128) { // Telegram spec says it should be 255, but we need to lower the limit to pack DcConfig
        const QByteArray innerData = Utils::packGZip(reply);
        if (innerData.size() + 8 < reply.size()) {
            CTelegramStream innerStream(CRawStream::WriteOnly);
            innerStream << TLValue::GzipPacked;
            innerStream << innerData;
            output.writeBytes(innerStream.getData());
            qDebug() << gzipPackMessage() << messageId << TLValue::firstFromArray(reply).toString();
        } else {
            qDebug() << "Server: It makes no sense to gzip the answer for message" << messageId;
            output.writeBytes(reply);
        }
    } else {
        output.writeBytes(reply);
    }
    qDebug() << Q_FUNC_INFO << TLValue::firstFromArray(reply) << "for message id" << messageId;
    return sendPackage(output.getData(), SendMode::ServerReply);
}

const char *RpcLayer::gzipPackMessage()
{
    return "Server: gzip the answer for message";
}

quint32 RpcLayer::activeLayer() const
{
    if (m_invokeWithLayer.isEmpty()) {
        if (m_session) {
            return m_session->layer();
        }
        qCritical() << Q_FUNC_INFO << "Unable to get active layer (version)";
        return 0;
    }
    return m_invokeWithLayer.top();
}

bool RpcLayer::processDecryptedMessageHeader(const MTProto::FullMessageHeader &header)
{
    if (!header.sessionId) {
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << "Unexpected RPC packet without sessionId";
        return false;
    }

    if (!m_session->sessionId) {
        qCDebug(c_serverRpcLayerCategory) << Q_FUNC_INFO << "Assign the client auth key to a session id";
        m_session->sessionId = header.sessionId;
    } else if (m_session->sessionId != header.sessionId) {
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << "Unexpected Session Id";
        return false;
    }

    if (m_sendHelper->serverSalt() != header.serverSalt) {
        qDebug() << Q_FUNC_INFO << "Received different server salt:"
                 << header.serverSalt << "(received) vs" << m_sendHelper->serverSalt() << "(local)";
        MTProto::IgnoredMessageNotification messageNotification;
        messageNotification.errorCode = MTProto::IgnoredMessageNotification::IncorrectServerSalt;
        messageNotification.seqNo = header.sequenceNumber;
        messageNotification.messageId = header.messageId;

        CRawStream output(CRawStream::WriteOnly);
        output << TLValue::BadServerSalt;
        output << messageNotification;
        sendPackage(output.getData(), SendMode::ServerReply);
        return false;
    }
    return true;
}

QByteArray RpcLayer::getEncryptionKeyPart() const
{
    return m_sendHelper->getServerKeyPart();
}

QByteArray RpcLayer::getVerificationKeyPart() const
{
    return m_sendHelper->getClientKeyPart();
}

} // Server

} // Telegram
