#ifndef TELEGRAMSERVERCLIENT_HPP
#define TELEGRAMSERVERCLIENT_HPP

#include <QObject>
#include <QVector>

#include "Connection.hpp"

namespace Telegram {

namespace Server {

class ServerApi;
class RpcLayer;
class RpcOperationFactory;
class Session;

class RemoteClientConnection : public BaseConnection
{
    Q_OBJECT
public:
    explicit RemoteClientConnection(QObject *parent = nullptr);

    RpcLayer *rpcLayer();

    void setRpcFactories(const QVector<RpcOperationFactory*> &rpcFactories);
    void setServerApi(ServerApi *api);
    void setSession(Session *session);

signals:
    void becomeOnline();

};

} // Server

} // Telegram

#endif // TELEGRAMSERVERCLIENT_HPP
