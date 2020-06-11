#include "ServerRpcLayer.hpp"

#include "Debug_p.hpp"
#include "FunctionStreamOperators.hpp"
#include "IgnoredMessageNotification.hpp"
#include "LocalServerApi.hpp"
#include "MTProto/MessageHeader.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/StreamExtraOperators.hpp"
#include "RemoteClientConnectionHelper.hpp"
#include "RpcError.hpp"
#include "RpcOperationFactory.hpp"
#include "RpcProcessingContext.hpp"
#include "SendPackageHelper.hpp"
#include "ServerRpcOperation.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"
#include "Utils.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_serverRpcLayerCategory, "telegram.server.rpclayer", QtWarningMsg)
Q_LOGGING_CATEGORY(c_serverRpcDumpPackageCategory, "telegram.server.rpclayer.dump", QtWarningMsg)

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
    TLValue::HelpGetNearestDc,
    TLValue::HelpGetAppUpdate,
    TLValue::HelpGetCdnConfig,
    TLValue::AuthSendCode,
    TLValue::AuthResendCode,
    TLValue::AuthCheckPassword,
    TLValue::AuthCheckPhone,
    TLValue::AuthSignIn,
    TLValue::AuthSignUp,
    TLValue::AuthImportAuthorization,
    TLValue::AccountGetPassword,
    TLValue::LangpackGetLangPack,
    TLValue::LangpackGetStrings,
    TLValue::LangpackGetDifference,
    TLValue::LangpackGetLanguages,
};

RpcLayer::RpcLayer(QObject *parent) :
    BaseRpcLayer(parent)
{
}

LocalServerApi *RpcLayer::api()
{
    return m_api;
}

void RpcLayer::setServerApi(LocalServerApi *api)
{
    m_api = api;
    setObjectName(QStringLiteral("dc%1").arg(api->dcId()));
}

bool RpcLayer::isAuthorized() const
{
    return m_session && m_session->userId();
}

LocalUser *RpcLayer::getUser() const
{
    if (!m_session) {
        return nullptr;
    }
    if (!m_session->userOrWantedUserId()) {
        return nullptr;
    }
    return m_api->getUser(m_session->userOrWantedUserId());
}

quint64 RpcLayer::serverSalt() const
{
    return m_session ? m_session->getServerSalt() : 0;
}

quint64 RpcLayer::sessionId() const
{
    return m_session ? m_session->id() : 0;
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
    qCInfo(c_serverRpcLayerCategory) << CALL_INFO << requestValue.toString();

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
        MTProto::Functions::TLPing ping;
        stream >> ping;

        MTProto::Stream output(MTProto::Stream::WriteOnly);
        output << TLValue::Pong;
        output << message.messageId;
        output << ping.pingId;
        sendPacket(output.getData(), SendMode::ServerReply, MessageType::NotContentRelatedMessage);
    }
        return true;
    case TLValue::MsgsAck:
        return processMessageAck(message.skipTLValue());
    default:
        break;
    }

    MTProto::Stream stream(message.data);
    RpcProcessingContext context(stream, message.messageId);

    context.inputStream() >> requestValue;
    context.setReadCode(requestValue);
    if (!isAuthorized() && !c_unregisteredUserAllowedRpcList.contains(requestValue)) {
        qCInfo(c_serverRpcLayerCategory) << CALL_INFO << "block" << requestValue.toString()
                                         << "for unauthorized connection" << getHelper()->authId();
        RpcError error(RpcError::Reason::AuthKeyUnregistered);
        return sendRpcError(error, context.messageId());
    }

    RpcOperation *op = nullptr;
    LocalUser *localUser = getUser();
    for (RpcOperationFactory *f : m_operationFactories) {
        if (f->needLocalUser() && !localUser) {
            // Skip
            continue;
        }
        op = f->processRpcCall(this, context);
        if (op) {
            break;
        }
    }
    if (!op) {
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << requestValue.toString() << "is not processed!";
        return false;
    }

    if (!op->isFinished()) {
        op->startLater();
        op->deleteOnFinished();
    }
    return true;
}

bool RpcLayer::processMessageAck(const MTProto::Message &message)
{
    MTProto::Stream stream(message.data);
    TLVector<quint64> idsVector;
    stream >> idsVector;
    qCDebug(c_serverRpcLayerCategory) << "processMessageAck():" << idsVector;

    for (quint64 messageId : idsVector) {
        RpcOperation *operation = m_operationsToConfirm.take(messageId);
        if (!operation) {
            continue;
        }
        qCDebug(c_serverRpcLayerCategory) << operation << "confirmed";
        operation->setFinished();
    }

    return true;
}

void RpcLayer::sendUpdates(const TLUpdates &updates)
{
    qCDebug(c_serverRpcLayerCategory) << CALL_INFO << "Send update to"
                                      << session()->userId()
                                      << "session:" << sessionId()
                                      << "IP:" << session()->ip;

#ifdef DEVELOPER_BUILD
    qCDebug(c_serverRpcLayerCategory) << updates;
#endif

    MTProto::Stream stream(MTProto::Stream::WriteOnly);
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
    QString systemLanguage;
    QString languagePack;
    QString languageCode;
    stream >> appId;
    stream >> deviceInfo;
    stream >> osInfo;
    stream >> appVersion;
    if (activeLayerNumber() >= MTProto::LayerNumber67) {
        stream >> systemLanguage;
        // If the pack is not registered on server, raise CONNECTION_LANG_PACK_INVALID RPC Error
        stream >> languagePack;
    }
    stream >> languageCode;

    qCDebug(c_serverRpcLayerCategory) << Q_FUNC_INFO << deviceInfo << osInfo << appId << appVersion << languageCode;
    if (stream.error()) {
        qCWarning(c_serverRpcLayerCategory) << Q_FUNC_INFO << "Invalid read!";
        return false;
    }
    session()->setLayer(activeLayerNumber());
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
    if (errorCode == MTProto::IgnoredMessageNotification::IncorrectServerSalt) {
        messageNotification.newServerSalt = m_session->getServerSalt();
    }
    messageNotification.errorCode = errorCode;
    messageNotification.seqNo = header.sequenceNumber;
    messageNotification.messageId = header.messageId;
    qCDebug(c_serverRpcLayerCategory) << messageNotification.toString();

    MTProto::Stream output(RawStream::WriteOnly);
    TLBadMsgNotification tlNotification;
    messageNotification.toTlNotification(&tlNotification);
    output << tlNotification;
    sendPacket(output.getData(), SendMode::ServerReply, MessageType::NotContentRelatedMessage);
}

bool RpcLayer::sendRpcError(const RpcError &error, quint64 messageId)
{
    RawStreamEx output(RawStreamEx::WriteOnly);
    output << error;
    return sendRpcReply(output.getData(), messageId);
}

quint64 RpcLayer::sendRpcReply(const QByteArray &reply, quint64 messageId)
{
#define DUMP_SERVER_RPC_PACKETS
#ifdef DUMP_SERVER_RPC_PACKETS
    qCDebug(c_serverRpcDumpPackageCategory) << "Server: Answer for message" << messageId;
    qCDebug(c_serverRpcDumpPackageCategory).noquote() << "Server: RPC Reply bytes:" << reply.size() << reply.toHex();
#endif
    RawStream output(RawStream::WriteOnly);
    output << TLValue::RpcResult;
    output << messageId;
    if (reply.size() > 128) { // Telegram spec says it should be 255, but we need to lower the limit to pack DcConfig
        const QByteArray innerData = Utils::packGZip(reply);
        if (innerData.size() + 8 < reply.size()) {
            MTProto::Stream innerStream(RawStream::WriteOnly);
            innerStream << TLValue::GzipPacked;
            innerStream << innerData;
            output.writeBytes(innerStream.getData());
            qCDebug(c_serverRpcDumpPackageCategory) << gzipPackMessage() << messageId << TLValue::firstFromArray(reply).toString();
        } else {
            qCDebug(c_serverRpcDumpPackageCategory) << "Server: It makes no sense to gzip the answer for message" << messageId;
            output.writeBytes(reply);
        }
    } else {
        output.writeBytes(reply);
    }
    qCDebug(c_serverRpcDumpPackageCategory) << Q_FUNC_INFO << TLValue::firstFromArray(reply) << "for message id" << messageId;
    return sendPacket(output.getData(), SendMode::ServerReply, MessageType::ContentRelatedMessage);
}

bool RpcLayer::sendRpcMessage(const QByteArray &message)
{
    return sendPacket(message, SendMode::ServerInitiative, MessageType::ContentRelatedMessage);
}

bool RpcLayer::sendRpcReply(RpcOperation *operation, const QByteArray &replyData)
{
    const quint64 operationReplyId = sendRpcReply(replyData, operation->messageId());
    if (!operationReplyId) {
        qCWarning(c_serverRpcLayerCategory) << "Unable to send RPC reply for" << operation
                                            << "op messageId:" << operation->messageId();
        return false;
    }
    qCDebug(c_serverRpcLayerCategory) << "Track reply" << operationReplyId << "for" << operation;
    m_operationsToConfirm.insert(operationReplyId, operation);
    return true;
}

const char *RpcLayer::gzipPackMessage()
{
    return "Server: gzip the answer for message";
}

quint32 RpcLayer::activeLayerNumber() const
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

bool RpcLayer::processMessageHeader(const MTProto::FullMessageHeader &header)
{
    if (!header.sessionId) {
        qCWarning(c_serverRpcLayerCategory) << this << __func__ << "Unexpected RPC packet without sessionId";
        return false;
    }

    if (!m_session) {
        api()->bindClientConnectionSession(getHelper()->getRemoteClientConnection(), header.sessionId);
    }

    if (m_session->id() != header.sessionId) {
        qCWarning(c_serverRpcLayerCategory) << this << __func__ << "Unexpected Session Id"
                                            << showbase << hex
                                            << m_session->id() << "(in session),"
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

MTProtoSendHelper *RpcLayer::getHelper() const
{
    return static_cast<MTProtoSendHelper *>(m_sendHelper);
}

} // Server namespace

} // Telegram namespace
