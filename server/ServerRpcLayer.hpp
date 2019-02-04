#ifndef TELEGRAM_SERVER_RPCLAYER_HPP
#define TELEGRAM_SERVER_RPCLAYER_HPP

#include "RpcLayer.hpp"

#include <QStack>
#include <QVector>

class CTelegramStream;
class RpcProcessingContext;

struct TLUpdates;

namespace Telegram {

class RpcError;

namespace Server {

class RpcOperation;
class RpcOperationFactory;

class LocalUser;
class ServerApi;
class Session;

class RpcLayer : public BaseRpcLayer
{
public:
    explicit RpcLayer(QObject *parent = nullptr);

    ServerApi *api();
    void setServerApi(ServerApi *api);

    LocalUser *getUser() const;

    quint64 serverSalt() const override;
    quint64 sessionId() const override;
    Session *session() const;
    void setSession(Session *session);

    void setRpcFactories(const QVector<RpcOperationFactory*> &rpcFactories);

    bool processMTProtoMessage(const MTProto::Message &message) override;

    void sendUpdates(const TLUpdates &updates);

    // Low level
    bool processInitConnection(const MTProto::Message &message);
    bool processInvokeWithLayer(const MTProto::Message &message);

    void sendIgnoredMessageNotification(quint32 errorCode, const MTProto::FullMessageHeader &header);
    bool sendRpcError(const Telegram::RpcError &error, quint64 messageId);
    bool sendRpcReply(const QByteArray &reply, quint64 messageId);
    bool sendRpcMessage(const QByteArray &message);

    static const char *gzipPackMessage();

    quint32 activeLayer() const;

protected:
    bool processDecryptedMessageHeader(const MTProto::FullMessageHeader &header) override;
    SAesKey getDecryptionAesKey(const QByteArray &messageKey) const final { return generateClientToServerAesKey(messageKey); }
    SAesKey getEncryptionAesKey(const QByteArray &messageKey) const final { return generateServerToClientAesKey(messageKey); }

    QByteArray getEncryptionKeyPart() const final;
    QByteArray getVerificationKeyPart() const final;

    Session *m_session = nullptr;
    ServerApi *m_api = nullptr;
    QStack<quint32> m_invokeWithLayer;

    QVector<RpcOperationFactory*> m_operationFactories;
};

} // Server

} // Telegram

#endif // RPCLAYER_HPP
