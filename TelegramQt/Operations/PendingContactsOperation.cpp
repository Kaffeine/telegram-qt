#include "PendingContactsOperation.hpp"
#include "PendingContactsOperation_p.hpp"

namespace Telegram {

namespace Client {

PendingContactsOperationPrivate *PendingContactsOperationPrivate::get(PendingContactsOperation *parent)
{
    return reinterpret_cast<PendingContactsOperationPrivate*>(parent->d);
}

PendingContactsOperation::PendingContactsOperation(QObject *parent) :
    PendingOperation(parent)
{
    d = new PendingContactsOperationPrivate();
}

PendingContactsOperation::~PendingContactsOperation()
{
}

PeerList PendingContactsOperation::peers() const
{
    Q_D(const PendingContactsOperation);
    return d->m_peers;
}

} // Client namespace

} // Telegram namespace
