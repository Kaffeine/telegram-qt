#include "ContactList_p.hpp"

#include "ContactsApi.hpp"
#include "ContactsApi_p.hpp"
#include "DataStorage.hpp"

#include "Operations/PendingContactsOperation.hpp"

namespace Telegram {

namespace Client {

ContactList::ContactList(ContactsApi *api) :
    QObject(api),
    d(new ContactListPrivate)
{
    d->m_q = this;
    d->m_api = api;
}

ContactList::~ContactList()
{
}

QVector<quint32> ContactList::list() const
{
    Q_D(const ContactList);
    return d->m_userIds;
}

bool ContactList::isReady() const
{
    Q_D(const ContactList);
    return d->m_readyOperation && d->m_readyOperation->isSucceeded();
}

PendingOperation *ContactList::becomeReady()
{
    Q_D(ContactList);
    ContactsApiPrivate *api = ContactsApiPrivate::get(d->m_api);
    if (!d->m_readyOperation) {
        d->m_readyOperation = api->getContacts();
        d->m_readyOperation->startLater();
    }
    return d->m_readyOperation;
}

ContactList *ContactListPrivate::create(ContactsApi *api)
{
    return new ContactList(api);
}

ContactListPrivate *ContactListPrivate::get(ContactList *parent)
{
    return parent->d.data();
}

void ContactListPrivate::addUserIds(const QVector<quint32> &ids)
{
    Q_Q(ContactList);
    QVector<quint32> added;
    for (const quint32 id : ids) {
        if (!m_userIds.contains(id)) {
            added << id;
        }
    }
    m_userIds.append(added);
    emit q->listChanged(added, { });
}

void ContactListPrivate::setUserIds(const QVector<quint32> &ids)
{
    Q_Q(ContactList);
    QVector<quint32> added;
    for (const quint32 id : ids) {
        if (!m_userIds.contains(id)) {
            added << id;
        }
    }
    QVector<quint32> removed;
    for (const quint32 id : m_userIds) {
        if (!ids.contains(id)) {
            removed << id;
        }
    }
    m_userIds = ids;
    emit q->listChanged(added, removed);
}

} // Client namespace

} // Telegram namespace
