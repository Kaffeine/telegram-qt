#include "PendingContactsOperation.hpp"
#include "PendingContactsOperation_p.hpp"

namespace Telegram {

namespace Client {

PendingContactsOperationPrivate *PendingContactsOperationPrivate::get(PendingContactsOperation *parent)
{
    return reinterpret_cast<PendingContactsOperationPrivate*>(parent->d);
}

PendingContactsOperation::PendingContactsOperation(QObject *parent) :
    PendingOperation(new PendingContactsOperationPrivate(this), parent)
{
}

PendingContactsOperation::~PendingContactsOperation()
{
}

QVector<UserId> PendingContactsOperation::contacts() const
{
    Q_D(const PendingContactsOperation);
    return d->m_userIds;
}

PeerList PendingContactsOperation::peers() const
{
    Q_D(const PendingContactsOperation);
    PeerList result;
    result.reserve(d->m_userIds.count());
    for (UserId userId : d->m_userIds) {
        result.append(userId);
    }
    return result;
}

} // Client namespace

} // Telegram namespace
