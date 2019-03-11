#include "DialogList.hpp"
#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"
#include "DataStorage.hpp"

namespace Telegram {

namespace Client {

DialogList::DialogList(MessagingApi *backend) :
    QObject(backend),
    m_backend(backend)
{
}

bool DialogList::isReady() const
{
    return m_readyOperation && m_readyOperation->isSucceeded();
}

PendingOperation *DialogList::becomeReady()
{
    MessagingApiPrivate *api = MessagingApiPrivate::get(m_backend);
    if (!m_readyOperation) {
        m_readyOperation = api->getDialogs();
        connect(m_readyOperation, &PendingOperation::finished, this, &DialogList::onFinished);
        m_readyOperation->startLater();
    }
    return m_readyOperation;
}

void DialogList::ensurePeer(const Peer &peer)
{
    if (m_peers.contains(peer)) {
        return;
    }
    m_peers.append(peer);
    emit listChanged({peer}, {});
}

void DialogList::onFinished()
{
    if (m_readyOperation->isFailed()) {
        return;
    }
    MessagingApiPrivate *api = MessagingApiPrivate::get(m_backend);
    m_peers = api->dataStorage()->dialogs();
}

} // Client namespace

} // Telegram namespace
