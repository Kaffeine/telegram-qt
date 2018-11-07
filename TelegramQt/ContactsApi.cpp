#include "ContactsApi_p.hpp"

#include "ClientBackend.hpp"
#include "ContactList.hpp"
#include "RpcLayers/ClientRpcContactsLayer.hpp"

#include "Operations/PendingContactsOperation.hpp"
#include "Operations/PendingContactsOperation_p.hpp"
#include "Utils.hpp"

#include "DataStorage.hpp"
#include "DataStorage_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_contactsApiLoggingCategory, "telegram.client.api.contacts", QtWarningMsg)

namespace Telegram {

namespace Client {

ContactsApiPrivate::ContactsApiPrivate(ContactsApi *parent) :
    ClientApiPrivate(parent)
{
}

ContactsApiPrivate *ContactsApiPrivate::get(ContactsApi *parent)
{
    return static_cast<ContactsApiPrivate*>(parent->d);
}

PendingContactsOperation *ContactsApiPrivate::importContacts(const ContactsApi::ContactInfoList &contacts)
{
    PendingContactsOperation *operation = new PendingContactsOperation(this);

    TLVector<TLInputContact> tlContacts;
    tlContacts.reserve(contacts.count());
    for (const ContactsApi::ContactInfo &info : contacts) {
        TLInputContact contact;
        contact.clientId = Utils::randomBytes<quint64>();
        contact.phone = info.phoneNumber;
        contact.firstName = info.firstName;
        contact.lastName = info.lastName;
        tlContacts.append(contact);
    }

    ContactsRpcLayer::PendingContactsImportedContacts *rpcOperation = contactsLayer()->importContacts(tlContacts);
    connect(rpcOperation, &PendingOperation::finished, this,
            [this, operation, rpcOperation]() { this->onContactsImported(operation, rpcOperation); }
    );
    return operation;
}

PendingContactsOperation *ContactsApiPrivate::getContacts()
{
    PendingContactsOperation *operation = new PendingContactsOperation(this);
    ContactsRpcLayer::PendingContactsContacts *rpcOperation = contactsLayer()->getContacts(0);
    connect(rpcOperation, &PendingOperation::finished, this,
            [this, operation, rpcOperation]() { this->onGetContactsResult(operation, rpcOperation); }
    );
    return operation;
}

ContactList *ContactsApiPrivate::getContactList()
{
    Q_Q(ContactsApi);
    if (!m_contactList) {
        m_contactList = new ContactList(q);
    }
    return m_contactList;
}

DataStorage *ContactsApiPrivate::dataStorage()
{
    return m_backend->dataStorage();
}

ContactsRpcLayer *ContactsApiPrivate::contactsLayer()
{
    return m_backend->contactsLayer();
}

void ContactsApiPrivate::onContactsImported(PendingContactsOperation *operation,
                                            ContactsRpcLayer::PendingContactsImportedContacts *rpcOperation)
{
    TLContactsImportedContacts result;
    rpcOperation->getResult(&result);

    PendingContactsOperationPrivate *priv = PendingContactsOperationPrivate::get(operation);

    for (const TLUser &user : result.users) {
        priv->m_peers.append(Peer::fromUserId(user.id));
    }

    m_backend->dataStorage()->internalApi()->processData(result.users);

    operation->setFinished();
}

void ContactsApiPrivate::onGetContactsResult(PendingContactsOperation *operation, ContactsRpcLayer::PendingContactsContacts *rpcOperation)
{
    TLContactsContacts result;
    rpcOperation->getResult(&result);

    PendingContactsOperationPrivate *priv = PendingContactsOperationPrivate::get(operation);

    for (const TLContact &contact : result.contacts) {
        priv->m_peers.append(Peer::fromUserId(contact.userId));
    }

    m_backend->dataStorage()->internalApi()->processData(result.users);
    m_backend->dataStorage()->internalApi()->setContactList(result.contacts);

    operation->setFinished();
}

ContactsApi::ContactsApi(QObject *parent) :
    ClientApi(parent)
{
    d = new ContactsApiPrivate(this);
}

ContactList *ContactsApi::getContactList()
{
    Q_D(ContactsApi);
    return d->getContactList();
}

QString ContactsApi::selfPhone() const
{
    return QString();
}

quint32 ContactsApi::selfContactId() const
{
    return 0;
}

PendingContactsOperation *ContactsApi::addContacts(const ContactsApi::ContactInfoList &contacts)
{
    Q_D(ContactsApi);
    return d->importContacts(contacts);
}

Telegram::PendingOperation *ContactsApi::deleteContacts(const QVector<quint32> &ids)
{
    return nullptr;
}

Telegram::PendingOperation *ContactsApi::blockContact(quint32 contactId)
{
    return nullptr;
}

Telegram::PendingOperation *ContactsApi::unblockContact(quint32 contactId)
{
    return nullptr;
}

PendingContactsOperation *ContactsApi::getBlockedContacts()
{
    return nullptr;
}

PendingContactsOperation *ContactsApi::search(const QString &query, int limit)
{
    return nullptr;
}

PendingContactsOperation *ContactsApi::resolveUsername(const QString &username)
{
    return nullptr;
}

PendingContactsOperation *ContactsApi::exportCard()
{
    return nullptr;
}

PendingContactsOperation *ContactsApi::importCard(const QByteArray &cardInfo)
{
    return nullptr;
}

} // Client namespace

} // Telegram namespace
