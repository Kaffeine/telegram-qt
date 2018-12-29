#include "DeclarativeUserInfo.hpp"

#include "Client.hpp"
#include "DataStorage.hpp"

namespace Telegram {

namespace Client {

DeclarativeUserInfo::DeclarativeUserInfo(QObject *parent) :
    DeclarativeClientOperator(parent)
{
}

void DeclarativeUserInfo::setContactId(quint32 contactId)
{
    if (m_contactId == contactId) {
        return;
    }
    m_contactId = contactId;
    emit contactIdChanged(contactId);

    updateDisplayName();
}

void DeclarativeUserInfo::setDisplayName(const QString &displayName)
{
    if (m_displayName == displayName) {
        return;
    }
    m_displayName = displayName;
    emit displayNameChanged(displayName);
}

void DeclarativeUserInfo::updateDisplayName()
{
    UserInfo info;
    client()->dataStorage()->getUserInfo(&info, m_contactId);
    setDisplayName(info.firstName());
}

} // Client

} // Telegram
