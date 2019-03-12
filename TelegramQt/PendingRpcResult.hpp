#ifndef PENDING_RPC_RESULT_HPP
#define PENDING_RPC_RESULT_HPP

#include "PendingRpcOperation.hpp"
#include "ClientRpcLayerExtension.hpp"

namespace Telegram {

namespace Client {

class BasePendingRpcResult : public PendingRpcOperation
{
    Q_OBJECT
public:
    explicit BasePendingRpcResult(BaseRpcLayerExtension *layer,
                                  const QByteArray &requestData = QByteArray(),
                                  QObject *parent = nullptr);

protected:
    BaseRpcLayerExtension *m_layer = nullptr;
};

template <typename TLTypePtr>
class PendingRpcResult : public BasePendingRpcResult
{
public:
    explicit PendingRpcResult(BaseRpcLayerExtension *layer,
                              const QByteArray &requestData = QByteArray(),
                              QObject *parent = nullptr)
        : BasePendingRpcResult(layer, requestData, parent)
    {
    }

    bool getResult(TLTypePtr output)
    {
        if (isSucceeded()) {
            m_layer->processReply(this, output);
        }
        return isSucceeded() && output->isValid();
    }
};

} // Client namespace

} // Telegram namespace

#endif // PENDING_RPC_RESULT_HPP
