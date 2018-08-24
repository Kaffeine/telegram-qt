#ifndef TELEGRAM_SERVER_RPCLAYER_HPP
#define TELEGRAM_SERVER_RPCLAYER_HPP

#include "RpcLayer.hpp"

#include <QVector>

class CTelegramStream;
class RpcProcessingContext;

namespace Telegram {

class RpcError;

namespace Server {

class RpcOperation;
class RpcOperationFactory;

class User;
class ServerApi;
class Session;

class RpcLayer : public BaseRpcLayer
{
public:
    explicit RpcLayer(QObject *parent = nullptr);

    ServerApi *api();
    void setServerApi(ServerApi *api);
    void setLayerVersion(quint32 layer);

    User *getUser() const;

    quint64 sessionId() const override;
    Session *session() const;
    void setSession(Session *session);

    void setRpcFactories(const QVector<RpcOperationFactory*> &rpcFactories);

    bool processRpcQuery(const QByteArray &data, quint64 messageId);
    bool processRpcQuery(RpcProcessingContext &context);

    // Low level
    bool processInitConnection(RpcProcessingContext &context);
    bool processInvokeWithLayer(RpcProcessingContext &context);

    bool sendRpcError(const Telegram::RpcError &error, quint64 messageId);
    bool sendRpcReply(const QByteArray &reply, quint64 messageId);

protected:
    bool processDecryptedPackage(const QByteArray &decryptedData) override;
    SAesKey getDecryptionAesKey(const QByteArray &messageKey) const final { return generateClientToServerAesKey(messageKey); }
    SAesKey getEncryptionAesKey(const QByteArray &messageKey) const final { return generateServerToClientAesKey(messageKey); }

    quint32 m_layer = 0;
    Session *m_session = nullptr;
    ServerApi *m_api = nullptr;

    QVector<RpcOperationFactory*> m_operationFactories;
};

} // Server

} // Telegram

#endif // RPCLAYER_HPP
