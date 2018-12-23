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

#include "FunctionStreamOperators.hpp"

#include "MTProto/MessageHeader.hpp"

#include "CTelegramStream.hpp"
#include "CTelegramStreamExtraOperators.hpp"
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_serverRpcLayerCategory, "telegram.server.rpclayer", QtWarningMsg)

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

static const QVector<TLValue> c_unregisteredUserAllowedRpcList =
{
    TLValue::HelpGetConfig,
    TLValue::AuthSendCode,
    TLValue::AuthCheckPassword,
    TLValue::AuthSignIn,
    TLValue::AuthSignUp,
    TLValue::AccountGetPassword,
};

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

quint64 RpcLayer::serverSalt() const
{
    return m_session ? m_session->getServerSalt() : 0;
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
    qCInfo(c_serverRpcLayerCategory) << this << __func__ << requestValue.toString();

    switch (requestValue) {
    case TLValue::InitConnection:
        return processInitConnection(message.skipTLValue());
    case TLValue::InvokeWithLayer:
        return processInvokeWithLayer(message.skipTLValue());
    case TLValue::MsgContainer:
        return processMsgContainer(message.skipTLValue());
    case TLValue::Ping:
    case TLValue::PingDelayDisconnect:
    {
        MTProto::Stream stream(message.data);
        TLFunctions::TLPing ping;
        stream >> ping;

        MTProto::Stream output(MTProto::Stream::WriteOnly);
        output << TLValue::Pong;
        output << message.messageId;
        output << ping.pingId;
        sendPackage(output.getData(), SendMode::ServerReply);
    }
        return true;
    default:
        break;
    }

    MTProto::Stream stream(message.data);
    RpcProcessingContext context(stream, message.messageId);

    context.inputStream() >> requestValue;
    context.setReadCode(requestValue);
    if (!session() && !c_unregisteredUserAllowedRpcList.contains(requestValue)) {
        RpcError error(RpcError::Reason::AuthKeyUnregistered);
        return sendRpcError(error, context.requestId());
    }

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

void RpcLayer::sendUpdates(const TLUpdates &updates)
{
    CTelegramStream stream(CTelegramStream::WriteOnly);
    stream << updates;
    sendRpcMessage(stream.getData());
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

void RpcLayer::sendIgnoredMessageNotification(quint32 errorCode, const MTProto::FullMessageHeader &header)
{
    MTProto::IgnoredMessageNotification messageNotification;
    messageNotification.errorCode = errorCode; // MTProto::IgnoredMessageNotification::IncorrectServerSalt;
    messageNotification.seqNo = header.sequenceNumber;
    messageNotification.messageId = header.messageId;
    qCDebug(c_serverRpcLayerCategory) << messageNotification.toString();

    CRawStream output(CRawStream::WriteOnly);
    if (errorCode == MTProto::IgnoredMessageNotification::IncorrectServerSalt) {
        output << TLValue::BadServerSalt;
    } else {
        output << TLValue::BadMsgNotification;
    }
    output << messageNotification;
    sendPackage(output.getData(), SendMode::ServerReply);
}

bool RpcLayer::sendRpcError(const RpcError &error, quint64 messageId)
{
    CRawStreamEx output(CRawStreamEx::WriteOnly);
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

bool RpcLayer::sendRpcMessage(const QByteArray &message)
{
    return sendPackage(message, SendMode::ServerInitiative);
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
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << "Unexpected Session Id"
                                            << showbase << hex
                                            << m_session->sessionId << "(in session)"
                                            << header.sessionId << "(in package header)";
        return false;
    }

    if (!m_session->checkSalt(header.serverSalt)) {
        sendIgnoredMessageNotification(MTProto::IgnoredMessageNotification::IncorrectServerSalt, header);
        return false;
    }

    // We can not check message header for too high sequence number because of Container packages
#if 0
    if (header.sequenceNumber > (m_session->lastSequenceNumber + 2)) {
        sendIgnoredMessageNotification(MTProto::IgnoredMessageNotification::SequenceNumberTooHigh, header);
        return false;
    }
#endif
    if (header.sequenceNumber < m_session->lastSequenceNumber) {
        sendIgnoredMessageNotification(MTProto::IgnoredMessageNotification::SequenceNumberTooLow, header);
        return false;
    }
    if (header.messageId & 3ull) {
        sendIgnoredMessageNotification(MTProto::IgnoredMessageNotification::IncorrectTwoLowerOrderMessageIdBits, header);
        return false;
    }
    m_session->lastSequenceNumber = header.sequenceNumber;
    m_session->lastMessageNumber = header.messageId;
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
