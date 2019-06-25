#include "CDialogModel.hpp"

#include "Client.hpp"
#include "DataStorage_p.hpp"
#include "Debug.hpp"
#include "DialogList.hpp"
#include "MessagingApi.hpp"
#include "PendingOperation.hpp"

#include <QDateTime>

using namespace Telegram;
using namespace Telegram::Client;

static const int UserRoleOffset = Qt::UserRole + 1;

CDialogModel::CDialogModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QHash<int, QByteArray> CDialogModel::roleNames() const
{
    static const QHash<int, QByteArray> extraRoles {
        { UserRoleOffset + static_cast<int>(Role::Peer), "peer" },
        { UserRoleOffset + static_cast<int>(Role::DisplayName), "displayName" },
        { UserRoleOffset + static_cast<int>(Role::ChatType), "chatType" },
        { UserRoleOffset + static_cast<int>(Role::IsPinned), "isPinned" },
        { UserRoleOffset + static_cast<int>(Role::PictureFileId), "pictureFileId" },
        { UserRoleOffset + static_cast<int>(Role::UnreadMessageCount), "unreadMessageCount" },
        { UserRoleOffset + static_cast<int>(Role::LastMessage), "lastMessage" },
        { UserRoleOffset + static_cast<int>(Role::FormattedLastMessage), "formattedLastMessage" },
    };

    return extraRoles;
}

Client::Client *CDialogModel::client() const
{
    return m_client;
}

bool CDialogModel::hasPeer(const Peer peer) const
{
    return true;
}

QString CDialogModel::getName(const Peer peer) const
{
    return QString();
}

int CDialogModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(Column::Count);
}

int CDialogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_dialogs.count();
}

QVariant CDialogModel::data(const QModelIndex &index, int role) const
{
    const Role r = indexToRole(index, role);
    return getData(index.row(), r);
}

QVariant CDialogModel::getData(int index, CDialogModel::Role role) const
{
    if (index < 0 || index >= m_dialogs.count()) {
        return QVariant();
    }
    const DialogEntry dialog = m_dialogs.at(index);

    switch (role) {
    case Role::Peer:
        return QVariant::fromValue(dialog.info.peer());
    case Role::PeerAsString:
        return dialog.info.peer().toString();
    case Role::ChatType:
        return static_cast<int>(dialog.chatType);
    case Role::DisplayName:
        return dialog.name;
    case Role::IsPinned:
        return dialog.info.isPinned();
    case Role::UnreadMessageCount:
        return dialog.info.unreadCount();
    case Role::FormattedLastMessage:
        return dialog.formattedLastMessage;
    case Role::LastMessage:
        return getDialogLastMessageData(dialog);
    case Role::LastMessageText:
        return getDialogLastMessageData(dialog).value(QStringLiteral("text"));
    case Role::PictureFileId:
        return dialog.pictureFileId;
    case Role::MuteUntil:
    case Role::MuteUntilDate:
        // invalid roles
    case Role::Count:
    case Role::Invalid:
        return QVariant();
    }
    Q_UNREACHABLE();
    return QVariant();
}

void CDialogModel::setClient(Client::Client *client)
{
    m_client = client;
    emit clientChanged();
}

QVariantMap CDialogModel::getDialogLastMessageData(const DialogEntry &dialog) const
{
    if (dialog.lastChatMessage.id() == 0) {
        return {};
    }
    const Telegram::Message &lastChatMessage = dialog.lastChatMessage;
    QString text;
    if (lastChatMessage.type() == Namespace::MessageTypeText) {
        text = lastChatMessage.text();
    } else {
        Telegram::MessageMediaInfo info;
        client()->dataStorage()->getMessageMediaInfo(&info, dialog.info.peer(), lastChatMessage.id());
        switch (lastChatMessage.type()) {
        case Namespace::MessageTypeWebPage:
            text = lastChatMessage.text();
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
    if (lastChatMessage.fromUserId()) {
        Telegram::UserInfo userInfo;
        client()->dataStorage()->getUserInfo(&userInfo, lastChatMessage.fromUserId());
        senderName = userInfo.firstName();
    }

    return {
        { "type", static_cast<int>(lastChatMessage.type()) },
        { "text", text },
        { "senderName", senderName },
        { "timestamp", QDateTime::fromSecsSinceEpoch(lastChatMessage.timestamp()) },
        { "flags", static_cast<int>(lastChatMessage.flags()) },
    };
}

void CDialogModel::populate()
{
    m_list = client()->messagingApi()->getDialogList();

    connect(m_list, &Client::DialogList::listChanged, this, &CDialogModel::onListChanged);
    connect(m_list->becomeReady(), &Telegram::PendingOperation::finished, this, &CDialogModel::onListReady);
    if (m_list->isReady()) {
        onListReady();
    }
    connect(client()->messagingApi(), &Client::MessagingApi::messageReceived,
            this, &CDialogModel::onNewMessage);
}

QString getPeerAlias(const Telegram::Peer &peer, const Telegram::Client::Client *client)
{
    if (peer.type() == Telegram::Peer::Type::User) {
        Telegram::UserInfo info;
        if (client->dataStorage()->getUserInfo(&info, peer.id())) {
            return info.getBestDisplayName();
        }
    } else {
        Telegram::ChatInfo info;
        if (client->dataStorage()->getChatInfo(&info, peer)) {
            return info.title();
        }
    }
    return peer.toString();
}

QString getPeerPictureId(const Telegram::Peer &peer, const Telegram::Client::Client *client)
{
    FileInfo file;
    if (peer.type() == Telegram::Peer::Type::User) {
        Telegram::UserInfo info;
        if (client->dataStorage()->getUserInfo(&info, peer.id())) {
            info.getPeerPicture(&file, PeerPictureSize::Small);
        }
    } else {
        Telegram::ChatInfo info;
        if (client->dataStorage()->getChatInfo(&info, peer)) {
            info.getPeerPicture(&file, PeerPictureSize::Small);
        }
    }
    return file.getFileId();
}

void CDialogModel::onListReady()
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

void CDialogModel::onListChanged(const PeerList &added, const PeerList &removed)
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

void CDialogModel::addPeer(const Peer &peer)
{
    m_dialogs.resize(m_dialogs.size() + 1);
    DialogEntry &dialog = m_dialogs.last();
    Client::Client *c = client();
    c->dataStorage()->getDialogInfo(&dialog.info, peer);

    dialog.chatType = c->messagingApi()->getChatType(peer);
    dialog.name = getPeerAlias(peer, c);
    dialog.pictureFileId = getPeerPictureId(peer, c);
    updateDialogLastMessage(&dialog);
}

void CDialogModel::onNewMessage(const Telegram::Peer peer, quint32 messageId)
{
    // The method is called on dialog message sent or received
    Q_UNUSED(messageId)
    int dialogIndex = getDialogIndex(peer);
    if (dialogIndex < 0) {
        return;
    }
    DialogEntry &dialog = m_dialogs[dialogIndex];
    if (!updateDialogLastMessage(&dialog)) {
        return;
    }
    // const QModelIndex changedIndex = index(dialogIndex);
    // emit dataChanged(changedIndex, changedIndex, rolesToInt({
    //                                                             Role::LastMessage,
    //                                                             Role::FormattedLastMessage,
    //                                                             Role::UnreadMessageCount,
    //                                                         }));
}

int CDialogModel::getDialogIndex(const Peer peer) const
{
    for (int i = 0; i < m_dialogs.count(); ++i) {
        const DialogEntry &entry = m_dialogs.at(i);
        if (entry.info.peer() != peer) {
            continue;
        }
        return i;
    }
    return -1;
}

bool CDialogModel::updateDialogLastMessage(DialogEntry *entry)
{
    Client::Client *c = client();
    c->dataStorage()->getDialogInfo(&entry->info, entry->info.peer());
    if (!entry->lastMessageIsOutdated()) {
        return false;
    }
    c->messagingApi()->getMessage(&entry->lastChatMessage, entry->info.peer(), entry->info.lastMessageId());
    return true;
}

CDialogModel::Role CDialogModel::intToRole(int value)
{
    if (value < 0 || value > static_cast<int>(Role::Count)) {
        return Role::Invalid;
    }
    return static_cast<Role>(value);
}

CDialogModel::Column CDialogModel::intToColumn(int value)
{
    if (value < 0 || value > static_cast<int>(Column::Count)) {
        return Column::Invalid;
    }
    return static_cast<Column>(value);
}

QVector<int> CDialogModel::rolesToInt(const QVector<CDialogModel::Role> &roles)
{
    QVector<int> qtRoles;
    qtRoles.reserve(roles.count());
    for (const Role role : roles) {
        qtRoles << (static_cast<int>(role) + UserRoleOffset);
    }

    return qtRoles;
}

CDialogModel::Role CDialogModel::indexToRole(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    if (role >= UserRoleOffset) {
        return intToRole(role - UserRoleOffset);
    }

    const Column section = intToColumn(index.column());

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch (section) {
        case Column::Peer:
            return Role::PeerAsString;
        case Column::DisplayName:
            return Role::DisplayName;
        case Column::LastMessageText:
            return Role::LastMessageText;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return Role::Invalid;
}

bool CDialogModel::DialogEntry::lastMessageIsOutdated() const
{
    return info.lastMessageId() != lastChatMessage.id();
}
