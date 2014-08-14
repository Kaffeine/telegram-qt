#include "CMessagingModel.hpp"

QString messageDeliveryStatusStr(TelegramNamespace::MessageDeliveryStatus status)
{
    switch (status) {
    case TelegramNamespace::MessageDeliveryStatusUnknown:
        return QLatin1String("Unknown");
    case TelegramNamespace::MessageDeliveryStatusSent:
        return QLatin1String("Sent");
    case TelegramNamespace::MessageDeliveryStatusRead:
        return QLatin1String("Read");
    case TelegramNamespace::MessageDeliveryStatusDeleted:
        return QLatin1String("Deleted");
    default:
        return QString();
    }
}

CMessagingModel::CMessagingModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QVariant CMessagingModel::headerData(int section, Qt::Orientation orientation, int role) const
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
    case MessageId:
        return tr("Message Id");
    case Message:
        return tr("Message text");
    case Status:
        return tr("Status");
    default:
        break;
    }

    return QVariant();
}

QVariant CMessagingModel::data(const QModelIndex &index, int role) const
{
    int section = index.column();
    int messageIndex = index.row();

    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    if (messageIndex >= rowCount()) {
        return QVariant();
    }

    switch (section) {
    case Phone:
        return m_messages.at(messageIndex).phone;
    case MessageId:
        return m_messages.at(messageIndex).messageId;
    case Message:
        return m_messages.at(messageIndex).message;
    case Status:
        return messageDeliveryStatusStr(m_messages.at(messageIndex).status);
    default:
        break;
    }

    return QVariant();
}
void CMessagingModel::addMessage(const QString &phone, const QString &message, quint64 messageId)
{
    beginResetModel();

    m_messages.append(SMessageEntry(phone, message, messageId));

    endResetModel();
}

void CMessagingModel::setMessageDeliveryStatus(quint64 messageId, TelegramNamespace::MessageDeliveryStatus status)
{
    for (int i = 0; i < m_messages.count(); ++i) {
        if (m_messages.at(i).messageId == messageId) {
            m_messages[i].status = status;

            QModelIndex messageIndex = index(i, Status);
            emit dataChanged(messageIndex, messageIndex);
            break;
        }
    }
}
