/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CContactModel.hpp"

#include <QDateTime>

CContactsModel::CContactsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QVariant CContactsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (section) {
    case Phone:
        return tr("Phone");
    case FullName:
        return tr("Full name");
    case Status:
        return tr("Status");
    case TypingStatus:
        return tr("Typing status");
    case Avatar:
        return tr("Avatar");
    case Blocked:
        return tr("Blocked");
    default:
        break;
    }

    return QVariant();
}

QVariant CContactsModel::data(const QModelIndex &index, int role) const
{
    int section = index.column();
    int contactIndex = index.row();

    if ((role == Qt::DecorationRole) && (section == Avatar)) {
        if (!m_contacts.at(contactIndex).avatar.isNull()) {
            return m_contacts.at(contactIndex).avatar;
        }

        return QVariant();
    }

    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    if (contactIndex >= rowCount()) {
        return QVariant();
    }

    switch (section) {
    case Phone:
        return m_contacts.at(contactIndex).phone;
    case FullName:
        return m_contacts.at(contactIndex).fullName;
    case Status:
        return contactStatusStr(m_contacts.at(contactIndex));
    case TypingStatus:
        return m_contacts.at(contactIndex).typing ? tr("true") : tr("false");
    case Blocked:
        return m_contacts.at(contactIndex).blocked ? tr("true") : tr("false");
    default:
        break;
    }

    return QVariant();
}

QVariant CContactsModel::data(const QString &phone, int column) const
{
    int contactIndex = indexOfContact(phone);

    if (contactIndex < 0) {
        return QVariant();
    }

    switch (column) {
    case Phone:
        return m_contacts.at(contactIndex).phone;
    case FullName:
        return m_contacts.at(contactIndex).fullName;
    case Status:
        return contactStatusStr(m_contacts.at(contactIndex));
    case TypingStatus:
        return m_contacts.at(contactIndex).typing;
    case Blocked:
        return m_contacts.at(contactIndex).blocked;
    case Avatar:
        return m_contacts.at(contactIndex).avatar;
    default:
        return QVariant();
    }
}

void CContactsModel::addContact(const QString &phone)
{
    beginInsertRows(QModelIndex(), m_contacts.count(), m_contacts.count());
    m_contacts.append(SContact(phone));
    endInsertRows();
}

bool CContactsModel::removeContact(const QString &phone)
{
    for (int i = 0; i < m_contacts.count(); ++i) {
        if (m_contacts.at(i).phone != phone) {
            continue;
        }

        beginRemoveRows(QModelIndex(), i, i);
        m_contacts.removeAt(i);
        endRemoveRows();

        return true;
    }

    return false;
}

void CContactsModel::setContactList(const QStringList &list)
{
    beginResetModel();
    m_contacts.clear();

    for (int i = 0; i < list.count(); ++i) {
        m_contacts.append(SContact(list.at(i)));
    }

    endResetModel();
}

void CContactsModel::setContactStatus(const QString &contact, TelegramNamespace::ContactStatus status)
{
    int index = indexOfContact(contact);

    if (index < 0) {
        return;
    }

    m_contacts[index].status = status;

    QModelIndex modelIndex = createIndex(index, Status);
    emit dataChanged(modelIndex, modelIndex);
}

void CContactsModel::setContactLastOnline(const QString &contact, quint32 onlineDate)
{
    int index = indexOfContact(contact);

    if (index < 0) {
        return;
    }

    m_contacts[index].wasOnline = onlineDate;

    QModelIndex modelIndex = createIndex(index, Status);
    emit dataChanged(modelIndex, modelIndex);
}

void CContactsModel::setTypingStatus(const QString &contact, bool typingStatus)
{
    int index = indexOfContact(contact);

    if (index < 0) {
        return;
    }

    m_contacts[index].typing = typingStatus;

    QModelIndex modelIndex = createIndex(index, TypingStatus);
    emit dataChanged(modelIndex, modelIndex);
}

void CContactsModel::setContactAvatar(const QString &contact, const QString &avatarFileName)
{
    int index = indexOfContact(contact);

    if (index < 0) {
        return;
    }

    m_contacts[index].avatar = QPixmap(avatarFileName).scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QModelIndex modelIndex = createIndex(index, Avatar);
    emit dataChanged(modelIndex, modelIndex);

}

void CContactsModel::setContactFullName(const QString &contact, const QString &fullName)
{
    int index = indexOfContact(contact);

    if (index < 0) {
        return;
    }

    m_contacts[index].fullName = fullName;

    QModelIndex modelIndex = createIndex(index, FullName);
    emit dataChanged(modelIndex, modelIndex);
}

int CContactsModel::indexOfContact(const QString &phone) const
{
    for (int i = 0; i < m_contacts.count(); ++i) {
        if (m_contacts.at(i).phone == phone) {
            return i;
        }
    }

    return -1;
}

QStringList CContactsModel::contacts() const
{
    QStringList phones;

    for (int i = 0; i < m_contacts.count(); ++i) {
        phones.append(m_contacts.at(i).phone);
    }

    return phones;
}

QString CContactsModel::contactStatusStr(const SContact &contact) const
{
    switch (contact.status) {
    case TelegramNamespace::ContactStatusOnline:
        return tr("Online");
    case TelegramNamespace::ContactStatusOffline:
        if (contact.wasOnline > 0) {
            return tr("Offline (%1)").arg(QDateTime::fromMSecsSinceEpoch(quint64(contact.wasOnline) * 1000).toString(Qt::TextDate));
        } else  {
            return tr("Offline");
        }
    case TelegramNamespace::ContactStatusUnknown:
    default:
        return tr("Unknown");
    }
}
