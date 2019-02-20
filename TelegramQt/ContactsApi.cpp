#include "ContactsApi_p.hpp"

#include "ClientBackend.hpp"
#include "ContactList.hpp"
#include "RandomGenerator.hpp"
#include "RpcLayers/ClientRpcContactsLayer.hpp"

#include "Operations/PendingContactsOperation.hpp"
#include "Operations/PendingContactsOperation_p.hpp"

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

PendingOperation *ContactsApiPrivate::sync()
{
    PendingOperation *operation = new PendingOperation("ContactsApi::sync", this);

    TLInputUser selfInputUser;
    selfInputUser.tlType = TLValue::InputUserSelf;

    UsersRpcLayer::PendingUserVector *rpcOperation = m_backend->usersLayer()->getUsers({selfInputUser});
    rpcOperation->connectToFinished(this, &ContactsApiPrivate::onSelfUserResult, operation, rpcOperation);
    return operation;
}

quint32 ContactsApiPrivate::selfContactId() const
{
    return m_backend->dataStorage()->selfUserId();
}

PendingContactsOperation *ContactsApiPrivate::importContacts(const ContactsApi::ContactInfoList &contacts)
{
    PendingContactsOperation *operation = new PendingContactsOperation(this);

    TLVector<TLInputContact> tlContacts;
    tlContacts.reserve(contacts.count());
    for (const ContactsApi::ContactInfo &info : contacts) {
        TLInputContact contact;
        contact.clientId = RandomGenerator::instance()->generate<quint64>();
        contact.phone = info.phoneNumber;
        contact.firstName = info.firstName;
        contact.lastName = info.lastName;
        tlContacts.append(contact);
    }

    ContactsRpcLayer::PendingContactsImportedContacts *rpcOperation = contactsLayer()->importContacts(tlContacts);
    rpcOperation->connectToFinished(this, &ContactsApiPrivate::onContactsImported, operation, rpcOperation);
    return operation;
}

PendingContactsOperation *ContactsApiPrivate::getContacts()
{
    PendingContactsOperation *operation = new PendingContactsOperation(this);
    ContactsRpcLayer::PendingContactsContacts *rpcOperation = contactsLayer()->getContacts(0);
    rpcOperation->connectToFinished(this, &ContactsApiPrivate::onGetContactsResult, operation, rpcOperation);
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

DataInternalApi *ContactsApiPrivate::dataInternalApi()
{
    return DataInternalApi::get(m_backend->dataStorage());
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

    priv->m_userIds.reserve(result.users.count());
    for (const TLUser &user : result.users) {
        priv->m_userIds.append(user.id);
    }

    DataInternalApi::get(m_backend->dataStorage())->processData(result.users);

    operation->setFinished();
}

void ContactsApiPrivate::onGetContactsResult(PendingContactsOperation *operation, ContactsRpcLayer::PendingContactsContacts *rpcOperation)
{
    TLContactsContacts result;
    rpcOperation->getResult(&result);

    PendingContactsOperationPrivate *priv = PendingContactsOperationPrivate::get(operation);

    priv->m_userIds.reserve(result.contacts.count());
    for (const TLContact &contact : result.contacts) {
        priv->m_userIds.append(contact.userId);
    }

    dataInternalApi()->processData(result.users);
    dataInternalApi()->setContactList(result.contacts);

    operation->setFinished();
}

void ContactsApiPrivate::onSelfUserResult(PendingOperation *operation, UsersRpcLayer::PendingUserVector *rpcOperation)
{
    TLVector<TLUser> result;
    rpcOperation->getResult(&result);
    if (rpcOperation->isFailed()) {
        qCCritical(c_contactsApiLoggingCategory) << Q_FUNC_INFO << "failed";
        operation->setFinishedWithError(rpcOperation->errorDetails());
        return;
    }
    dataInternalApi()->processData(result);
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
    Q_D(const ContactsApi);
    return d->selfContactId();
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
