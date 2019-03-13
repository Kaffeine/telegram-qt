#include "ContactList.hpp"
#include "ContactsApi.hpp"
#include "ContactsApi_p.hpp"
#include "DataStorage.hpp"

#include "Operations/PendingContactsOperation.hpp"

namespace Telegram {

namespace Client {

ContactList::ContactList(ContactsApi *backend) :
    QObject(backend),
    m_backend(backend)
{
}

bool ContactList::isReady() const
{
    return m_readyOperation && m_readyOperation->isSucceeded();
}

PendingOperation *ContactList::becomeReady()
{
    ContactsApiPrivate *api = ContactsApiPrivate::get(m_backend);
    if (!m_readyOperation) {
        m_readyOperation = api->getContacts();
        connect(m_readyOperation, &PendingOperation::finished, this, &ContactList::onFinished);
        m_readyOperation->startLater();
    }
    return m_readyOperation;
}

void ContactList::onFinished()
{
    if (m_readyOperation->isFailed()) {
        return;
    }
    ContactsApiPrivate *api = ContactsApiPrivate::get(m_backend);
    m_peers = api->dataStorage()->contactList();
}

} // Client namespace

} // Telegram namespace
