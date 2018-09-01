#include "ServerRpcLayer.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "Debug_p.hpp"
#include "TelegramServerUser.hpp"
#include "RpcProcessingContext.hpp"
#include "RpcError.hpp"
#include "ServerRpcOperation.hpp"
#include "RpcOperationFactory.hpp"

#include "ServerApi.hpp"

#include "CTelegramStream.hpp"
#include <QLoggingCategory>

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

void RpcLayer::setLayerVersion(quint32 layer)
{
    m_layer = layer;
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

bool RpcLayer::processRpcQuery(const QByteArray &data, quint64 messageId)
{
    CTelegramStream stream(data);

    RpcProcessingContext context(stream, messageId);
    return processRpcQuery(context);
}

bool RpcLayer::processRpcQuery(RpcProcessingContext &context)
{
    TLValue requestValue;
    context.inputStream() >> requestValue;
    context.setReadCode(requestValue);

    qWarning() << Q_FUNC_INFO << requestValue.toString();

    switch (requestValue) {
    case TLValue::InitConnection:
        return processInitConnection(context);
    case TLValue::InvokeWithLayer:
        return processInvokeWithLayer(context);
    default:
        break;
    }

    RpcOperation *op = nullptr;
    for (RpcOperationFactory *f : m_operationFactories) {
        op = f->processRpcCall(this, context);
        if (op) {
            break;
        }
    }
    if (!op) {
        qWarning() << Q_FUNC_INFO << requestValue.toString() << "is not processed!";
        return false;
    }
    op->startLater();
    return true;
}

bool RpcLayer::processInitConnection(RpcProcessingContext &context)
{
    quint32 appId;
    QString deviceInfo;
    QString osInfo;
    QString appVersion;
#if TELEGRAMQT_LAYER >= 67
    QString systemLanguage;
    QString languagePack;
#endif
    QString languageCode;
    context.inputStream() >> appId;
    context.inputStream() >> deviceInfo;
    context.inputStream() >> osInfo;
    context.inputStream() >> appVersion;
#if TELEGRAMQT_LAYER >= 67
    context.inputStream() >> systemLanguage;
    context.inputStream() >> languagePack; // If the pack is not registered on server, raise CONNECTION_LANG_PACK_INVALID RPC Error
#endif
    context.inputStream() >> languageCode;

    qDebug() << Q_FUNC_INFO << deviceInfo << osInfo << appId << appVersion << languageCode;
    if (context.inputStream().error()) {
        qWarning() << Q_FUNC_INFO << "Invalid read!";
        return false;
    }
    if (session()->appInfo) {
        qWarning() << Q_FUNC_INFO << "The session is already initialized!" << session()->sessionId;
    } else {
        session()->appInfo = new CAppInformation(this);
    }
    session()->appInfo->setAppId(appId);
    session()->appInfo->setAppVersion(appVersion);
    session()->appInfo->setLanguageCode(languageCode);
    session()->appInfo->setDeviceInfo(deviceInfo);
    session()->appInfo->setOsInfo(osInfo);
    return processRpcQuery(context);
}

bool RpcLayer::processInvokeWithLayer(RpcProcessingContext &context)
{
    quint32 layer = 0; // TLValue::CurrentLayer;
    context.inputStream() >> layer;
    qDebug() << Q_FUNC_INFO << "InvokeWithLayer" << layer;
//    context.setLayer(layer);
    return processRpcQuery(context);
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

bool RpcLayer::processDecryptedPackage(const QByteArray &decryptedData)
{
    CRawStream decryptedStream(decryptedData);
    quint64 serverSalt = 0;
    quint64 sessionId = 0;
    quint64 messageId  = 0;
    quint32 sequence = 0;
    quint32 contentLength = 0;
    decryptedStream >> serverSalt;
    decryptedStream >> sessionId;
    decryptedStream >> messageId;
    decryptedStream >> sequence;
    decryptedStream >> contentLength;

    if (m_sendHelper->serverSalt() != serverSalt) {
        qDebug() << Q_FUNC_INFO << "Received different server salt:" << serverSalt << "(remote) vs" << m_sendHelper->serverSalt() << "(local)";
        //            return;
    }

    if (!m_session) {
        qWarning() << Q_FUNC_INFO << "Unexpected RPC packet";
        return false;
    }

    if (!m_session->sessionId) {
        qDebug() << Q_FUNC_INFO << "Assign the client auth key to a session id";
        m_session->sessionId = sessionId;
    } else if (m_session->sessionId != sessionId) {
        qWarning() << Q_FUNC_INFO << "Unexpected Session Id";
        return false;
    }

    if (int(contentLength) > decryptedData.length()) {
        qDebug() << Q_FUNC_INFO << "Expected data length is more, than actual.";
        return false;
    }

    const int headerLength = sizeof(serverSalt) + sizeof(sessionId) + sizeof(messageId) + sizeof(sequence) + sizeof(contentLength);
    QByteArray expectedMessageKey = Utils::sha1(decryptedData.left(headerLength + contentLength)).mid(4);

    const QByteArray messageKey = expectedMessageKey;
    if (messageKey != expectedMessageKey) {
        qDebug() << Q_FUNC_INFO << "Wrong message key";
        return false;
    }

    QByteArray payload = decryptedStream.readAll();
    const bool result = processRpcQuery(payload, messageId);

#ifdef DEVELOPER_BUILD
    static int packagesCount = 0;
    qDebug() << Q_FUNC_INFO << "Got package" << ++packagesCount << TLValue::firstFromArray(payload);
#endif
    return result;
}

} // Server

} // Telegram
