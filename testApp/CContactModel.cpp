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
    case TypingStatus:
        return tr("Typing status");
    case Avatar:
        return tr("Avatar");
    default:
        break;
    }

    return QVariant();
}

QVariant CContactsModel::data(const QModelIndex &index, int role) const
{
    int section = index.column();
    uint contactIndex = index.row();

    if ((role == Qt::DecorationRole) && (section == Avatar)) {
        if (!m_contacts.at(contactIndex).avatar.isNull()) {
            return m_contacts.at(contactIndex).avatar;
        }

        return QVariant();
    }

    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    if (contactIndex > rowCount()) {
        return QVariant();
    }

    switch (section) {
    case Phone:
        return m_contacts.at(contactIndex).phone;
    case FullName:
        return m_contacts.at(contactIndex).fullName;
    case Status:
        return statusToStr(m_contacts.at(contactIndex).status);
    case TypingStatus:
        return m_contacts.at(contactIndex).typing ? tr("true") : tr("false");
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
        return statusToStr(m_contacts.at(contactIndex).status);
    case TypingStatus:
        return m_contacts.at(contactIndex).typing;
    case Avatar:
        return m_contacts.at(contactIndex).avatar;
    default:
        return QVariant();
    }
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

    if (index < 0) {
        return;
    }

    m_contacts[index].status = status;

    QModelIndex modelIndex = createIndex(index, Status);
    emit dataChanged(modelIndex, modelIndex);
}

void CContactsModel::setTypingStatus(const QString &phone, bool typingStatus)
{
    int index = indexOfContact(phone);

    if (index < 0) {
        return;
    }

    m_contacts[index].typing = typingStatus;

    QModelIndex modelIndex = createIndex(index, TypingStatus);
    emit dataChanged(modelIndex, modelIndex);
}

void CContactsModel::setContactAvatar(const QString &phone, const QString &avatarFileName)
{
    int index = indexOfContact(phone);

    if (index < 0) {
        return;
    }

    m_contacts[index].avatar = QPixmap(avatarFileName).scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QModelIndex modelIndex = createIndex(index, Avatar);
    emit dataChanged(modelIndex, modelIndex);

}

void CContactsModel::setContactFullName(const QString &phone, const QString &fullName)
{
    int index = indexOfContact(phone);

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
