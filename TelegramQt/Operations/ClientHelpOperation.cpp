#include "ClientHelpOperation.hpp"

#include "DataStorage.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientRpcHelpLayer.hpp"
#include "PendingRpcOperation.hpp"

#include "RpcError.hpp"

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

HelpOperation::HelpOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void HelpOperation::setBackend(Backend *backend)
{
    m_backend = backend;
}

void HelpOperation::setRunMethod(HelpOperation::RunMethod method)
{
    m_runMethod = method;
}

void HelpOperation::start()
{
    if (m_runMethod) {
        callMember<>(this, m_runMethod);
    }
}

PendingOperation *HelpOperation::requestDcConfig()
{
    PendingRpcOperation *requestCodeOperation = helpLayer()->getConfig();
    connect(requestCodeOperation, &PendingRpcOperation::finished, this, &HelpOperation::onGetDcCondigurationFinished);
    return requestCodeOperation;
}

HelpRpcLayer *HelpOperation::helpLayer() const
{
    return m_backend->helpLayer();
}

void HelpOperation::onGetDcCondigurationFinished(PendingRpcOperation *operation)
{
    TLConfig result;
    helpLayer()->processReply(operation, &result);
    if (!result.isValid()) {
        setFinishedWithError(operation->errorDetails());
    }
    DcConfiguration config;
    for (const TLDcOption &opt : result.dcOptions) {
        DcOption o;
        o.id = opt.id;
        o.flags = opt.flags;
        o.address = opt.ipAddress;
        o.port = opt.port;
        config.dcOptions.append(o);
    }
    m_backend->dataStorage()->setServerConfiguration(config);
    setFinished();
}

} // Client

} // Telegram namespace
