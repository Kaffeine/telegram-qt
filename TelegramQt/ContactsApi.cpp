#include "ContactsApi_p.hpp"

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

ContactsApi::ContactsApi(QObject *parent) :
    ClientApi(parent)
{
    d = new ContactsApiPrivate(this);
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
    return nullptr;
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
