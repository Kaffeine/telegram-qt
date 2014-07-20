#include "CContactModel.hpp"

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
    case Status:
        return tr("Status");
    default:
        break;
    }

    return QVariant();
}

QVariant CContactsModel::data(const QModelIndex &index, int role) const
{
    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    int section = index.column();
    uint contactIndex = index.row();

    if (contactIndex > rowCount()) {
        return QVariant();
    }

    switch (section) {
    case Phone:
        return m_contacts.at(contactIndex).phone;
    case Status:
        return statusToStr(m_contacts.at(contactIndex).status);
    default:
        break;
    }

    return QVariant();
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

void CContactsModel::setContactStatus(const QString &phone, TelegramNamespace::ContactStatus status)
{
    int index = indexOfContact(phone);

    if (index > 0) {
        m_contacts[index].status = status;
    }

    QModelIndex modelIndex = createIndex(index, Status);
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

QString CContactsModel::statusToStr(TelegramNamespace::ContactStatus status) const
{
    switch (status) {
    case TelegramNamespace::ContactStatusOnline:
        return tr("Online");
    case TelegramNamespace::ContactStatusOffline:
        return tr("Offline");
    case TelegramNamespace::ContactStatusUnknown:
    default:
        return tr("Unknown");
    }
}
