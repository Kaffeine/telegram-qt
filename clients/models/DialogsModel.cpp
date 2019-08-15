#include "DialogsModel.hpp"

#include "Client.hpp"
#include "DataStorage_p.hpp"
#include "Debug.hpp"
#include "MessagingApi.hpp"
#include "DialogList.hpp"
#include "PendingOperation.hpp"

#include "TelegramNamespace_p.hpp"

#include <QDateTime>

#include <QDebug>

namespace Telegram {

namespace Client {

DialogsModel::DialogsModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

void DialogsModel::setClient(Client *client)
{
    m_client = client;
}

QModelIndex DialogsModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

Qt::ItemFlags DialogsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags f = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        f |= Qt::ItemNeverHasChildren;
    }
    return f;
}

bool DialogsModel::hasChildren(const QModelIndex &parent) const
{
    return parent.isValid() ? false : !m_dialogs.isEmpty();
}

bool DialogsModel::hasPeer(const Peer peer) const
{
    return true;
}

QString DialogsModel::getName(const Peer peer) const
{
    return QString();
}

Peer DialogsModel::getPeer(int index) const
{
    if (index < 0 || index >= m_dialogs.count()) {
        return Peer();
    }
    return m_dialogs.at(index).internal->peer;
}

int DialogsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_dialogs.count();
}

QVariant DialogsModel::data(const QModelIndex &index, int role) const
{
    const Role r = indexToRole(index, role);
    return getData(index.row(), r);
}

QVariant DialogsModel::getData(int index, DialogsModel::Role role) const
{
    if (index < 0 || index >= m_dialogs.count()) {
        return QVariant();
    }
    const DialogEntry dialog = m_dialogs.at(index);

    switch (role) {
    case Role::Peer:
        return QVariant::fromValue(dialog.internal->peer);
    case Role::ChatType:
        return static_cast<int>(dialog.chatType);
    case Role::DisplayName:
        return dialog.name;
    case Role::IsPinned:
        return dialog.internal->flags & UserDialog::Flags::Pinned;
    case Role::UnreadMessageCount:
        return dialog.internal->unreadCount;
    case Role::FormattedLastMessage:
        return dialog.formattedLastMessage;
    case Role::LastMessage:
        return getDialogLastMessageData(dialog);
    case Role::Picture:
        // Not implemented yet
        return QVariant();
    case Role::MuteUntil:
        return dialog.notificationSettings.muteUntil();
    case Role::MuteUntilDate:
        return QDateTime::fromSecsSinceEpoch(dialog.notificationSettings.muteUntil());
        // invalid roles
    case Role::Count:
    case Role::Invalid:
        return QVariant();
    }
    Q_UNREACHABLE();
    return QVariant();
}

QVariantMap DialogsModel::getDialogLastMessageData(const DialogEntry &dialog) const
{
    if (dialog.lastChatMessage.id == 0) {
        return {};
    }
    const Telegram::Message &lastChatMessage = dialog.lastChatMessage;
    QString text;
    if (lastChatMessage.type == Namespace::MessageTypeText) {
        text = lastChatMessage.text;
    } else {
        Telegram::MessageMediaInfo info;
        client()->dataStorage()->getMessageMediaInfo(&info, dialog.internal->peer, lastChatMessage.id);
        switch (lastChatMessage.type) {
        case Namespace::MessageTypeWebPage:
            text = lastChatMessage.text;
            //text = info.url();
            break;
        case Namespace::MessageTypeSticker:
            text = info.alt();
            break;
        case Namespace::MessageTypeDocument:
            text = info.documentFileName();
            break;
        default:
            text = info.caption();
            break;
        }
    }

    QString senderName;
    if (lastChatMessage.fromId) {
        Telegram::UserInfo userInfo;
        client()->dataStorage()->getUserInfo(&userInfo, lastChatMessage.fromId);
        senderName = userInfo.firstName();
    }

    return {
        { "type", static_cast<int>(lastChatMessage.type) },
        { "text", text },
        { "senderName", senderName },
        { "timestamp", QDateTime::fromSecsSinceEpoch(lastChatMessage.timestamp) },
        { "flags", static_cast<int>(lastChatMessage.flags / 2) },
    };
}

void DialogsModel::populate()
{
    m_list = client()->messagingApi()->getDialogList();

    connect(m_list, &DialogList::listChanged, this, &DialogsModel::onListChanged);
    connect(m_list->becomeReady(), &Telegram::PendingOperation::finished, this, &DialogsModel::onListReady);
    if (m_list->isReady()) {
        onListReady();
    }
}

QString getPeerAlias(const Telegram::Peer &peer, const Telegram::Client::Client *client)
{
    if (peer.type == Telegram::Peer::Type::User) {
        Telegram::UserInfo info;
        if (client->dataStorage()->getUserInfo(&info, peer.id)) {
            return info.getBestDisplayName();
        }
    } else {
        Telegram::ChatInfo info;
        if (client->dataStorage()->getChatInfo(&info, peer.id)) {
            return info.title();
        }
    }
    return peer.toString();
}

void DialogsModel::onListReady()
{
    qWarning() << Q_FUNC_INFO;
    beginResetModel();
    m_dialogs.clear();

    const QVector<Telegram::Peer> pinned = client()->dataStorage()->pinnedDialogs();
    for (const Telegram::Peer &peer : pinned) {
        addPeer(peer);
    }
    const QVector<Telegram::Peer> dialogs = client()->dataStorage()->dialogs();
    for (const Telegram::Peer &peer : dialogs) {
        if (pinned.contains(peer)) {
            continue;
        }
        addPeer(peer);
    }
    endResetModel();
}

void DialogsModel::onListChanged(const PeerList &added, const PeerList &removed)
{
    if (!removed.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Unimplemented argument";
    }
    if (!added.isEmpty()) {
        beginInsertRows(QModelIndex(), m_dialogs.count(), m_dialogs.count() + added.count() - 1);
        for (const Peer &p : added) {
            addPeer(p);
        }
        endInsertRows();
    }
}

void DialogsModel::addPeer(const Peer &peer)
{
    Client *c = client();
    DialogEntry d;
    DataInternalApi *internalApi = DataInternalApi::get(client()->dataStorage());
    UserDialog *dialogData = internalApi->getDialog(peer);
    if (!dialogData) {
        qWarning() << Q_FUNC_INFO << "Unknown dialog";
        return;
    }
    d.internal = dialogData;
    d.chatType = c->messagingApi()->getChatType(peer);
    d.name = getPeerAlias(peer, c);
    c->messagingApi()->getMessage(&d.lastChatMessage, peer, dialogData->topMessage);
    c->messagingApi()->getNotificationSettings(&d.notificationSettings, peer);

    m_dialogs << d;
}

QModelIndex DialogsModel::parent(const QModelIndex & /* child */) const
{
    return QModelIndex();
}

DialogsModel::Role DialogsModel::intToRole(int value)
{
    if (value < 0 || value > static_cast<int>(Role::Count)) {
        return Role::Invalid;
    }
    return static_cast<Role>(value);
}

DialogsTableModel::DialogsTableModel(QObject *parent)
    : DialogsModel(parent)
{
}

int DialogsTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(Column::Count);
}

QVariant DialogsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Column s = static_cast<Column>(section);

    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (s) {
    case Column::PeerName:
        return tr("Name");
    case Column::Picture:
        return tr("Picture");
    case Column::FormattedLastMessage:
        return tr("Message");
    case Column::MuteUntil:
        return tr("MuteUntil");
    default:
        break;
    }

    return QVariant();
}

DialogsModel::Role DialogsTableModel::indexToRole(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        break;
    default:
        return Role::Invalid;
    }

    Column column = static_cast<Column>(index.column());
    switch (column) {
    case Column::PeerName:
        return Role::DisplayName;
    case Column::FormattedLastMessage:
        return Role::FormattedLastMessage;
    case Column::MuteUntil:
        return Role::MuteUntilDate;
    default:
        return Role::Invalid;
    }
}

} // Client namespace

} // Telegram namespace
