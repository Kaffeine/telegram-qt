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

#include "CMessagingModel.hpp"

#include <QDateTime>

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
    case Direction:
        return tr("Direction");
    case Timestamp:
        return tr("Timestamp");
        break;
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
    case Direction:
        return m_messages.at(messageIndex).outgoing ? tr("out") : tr("in");
    case Timestamp:
        return QDateTime::fromMSecsSinceEpoch(quint64(m_messages.at(messageIndex).timestamp) * 1000);
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

void CMessagingModel::addMessage(const QString &phone, const QString &message, TelegramNamespace::MessageType type, bool outgoing, quint64 messageId, quint32 timestamp)
{
    Q_UNUSED(type);

    if (!timestamp) {
        timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
    }

    beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count());
    m_messages.append(SMessageEntry(phone, message, messageId, timestamp));
    m_messages.last().outgoing = outgoing;
    endInsertRows();
}

void CMessagingModel::setMessageDeliveryStatus(const QString &phone, quint64 messageId, TelegramNamespace::MessageDeliveryStatus status)
{
    Q_UNUSED(phone);
    for (int i = 0; i < m_messages.count(); ++i) {
        if (m_messages.at(i).messageId == messageId) {
            m_messages[i].status = status;

            QModelIndex messageIndex = index(i, Status);
            emit dataChanged(messageIndex, messageIndex);
            break;
        }
    }
}
