#ifndef TELEGRAM_CLIENT_RPC___VAR_GROUP_NAME_CAPITAL___LAYER_HPP
#define TELEGRAM_CLIENT_RPC___VAR_GROUP_NAME_CAPITAL___LAYER_HPP

#include "ClientRpcLayerExtension.hpp"
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class __VAR_GROUP_NAME__RpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit __VAR_GROUP_NAME__RpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC___VAR_GROUP_NAME_CAPITAL___LAYER_HPP
