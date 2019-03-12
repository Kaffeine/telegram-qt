#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

BasePendingRpcResult::BasePendingRpcResult(BaseRpcLayerExtension *layer,
                                           const QByteArray &requestData,
                                           QObject *parent)
    : PendingRpcOperation(requestData, parent ? parent : layer),
    m_layer(layer)
{
}

} // Client namespace

} // Telegram namespace
