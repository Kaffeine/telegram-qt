#include "ContactsApi_p.hpp"

#include "ClientBackend.hpp"
#include "ContactList_p.hpp"
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
    PendingOperation *operation = new PendingOperation(this);
    operation->setOperationName("ContactsApi::sync");

    TLInputUser selfInputUser;
    selfInputUser.tlType = TLValue::InputUserSelf;

    UsersRpcLayer::PendingUserVector *rpcOperation = m_backend->usersLayer()->getUsers({selfInputUser});
    rpcOperation->connectToFinished(this, &ContactsApiPrivate::onSelfUserResult, operation, rpcOperation);
    return operation;
}

quint32 ContactsApiPrivate::selfUserId() const
{
    return m_backend->dataStorage()->selfUserId();
}

PendingContactsOperation *ContactsApiPrivate::importContacts(const ContactsApi::ContactInfoList &contacts)
{
    PendingContactsOperation *operation = new PendingContactsOperation(this);

    QVector<TLInputContact> tlContacts;
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
        m_contactList = ContactListPrivate::create(q);
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

void ContactsApiPrivate::onUserStatusChanged(quint32 userId, const TLUserStatus &status)
{
    Q_Q(ContactsApi);
    DataInternalApi *dataApi = dataInternalApi();
    TLUser *user = dataApi->users().value(userId);
    if (!user) {
        // ignore
        return;
    }
    user->status = status;
    emit q->contactStatusChanged(userId, getApiContactStatus(status.tlType));
}

void ContactsApiPrivate::onUserPhotoChanged(quint32 userId, const TLUserProfilePhoto &photo)
{
    Q_Q(ContactsApi);
    if (!dataInternalApi()->updateUserPhoto(userId, photo)) {
        return;
    }
    emit q->contactPhotoChanged(userId);
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

    DataInternalApi *dataApi = dataInternalApi();
    dataApi->processData(result.users);

    if (m_contactList) {
        dataApi->ensureContacts(priv->m_userIds);

        ContactListPrivate *listPrivate = ContactListPrivate::get(m_contactList);
        listPrivate->addUserIds(priv->m_userIds);
    }

    operation->setFinished();
}

void ContactsApiPrivate::onGetContactsResult(PendingContactsOperation *operation,
                                             ContactsRpcLayer::PendingContactsContacts *rpcOperation)
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

    if (m_contactList) {
        ContactListPrivate *listPrivate = ContactListPrivate::get(m_contactList);
        listPrivate->setUserIds(priv->m_userIds);
    }

    operation->setFinished();
}

void ContactsApiPrivate::onSelfUserResult(PendingOperation *operation,
                                          UsersRpcLayer::PendingUserVector *rpcOperation)
{
    QVector<TLUser> result;
    rpcOperation->getResult(&result);
    if (rpcOperation->isFailed()) {
        qCCritical(c_contactsApiLoggingCategory) << Q_FUNC_INFO << "failed";
        operation->setFinishedWithError(rpcOperation->errorDetails());
        return;
    }
    dataInternalApi()->processData(result);
    operation->setFinished();
}

/*!
    \class Telegram::Client::ContactsApi
    \brief Provides an API to work with contacts.

    \inmodule TelegramQt
    \ingroup Client
 */
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

quint32 ContactsApi::selfUserId() const
{
    Q_D(const ContactsApi);
    return d->selfUserId();
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
