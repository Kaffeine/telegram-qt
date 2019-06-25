#include "CDialogModel.hpp"

#include "Client.hpp"
#include "DataStorage.hpp"
#include "MessagingApi.hpp"
#include "DialogList.hpp"
#include "PendingOperation.hpp"
#include "Debug.hpp"

#include <QDateTime>

CDialogModel::CDialogModel(Telegram::Client::Client *backend, QObject *parent) :
    CPeerModel(parent)
{
    setBackend(backend);
}

bool CDialogModel::hasPeer(const Telegram::Peer peer) const
{
    return modelForPeer(peer);
}

QString CDialogModel::getName(const Telegram::Peer peer) const
{
    const CPeerModel *model = modelForPeer(peer);
    if (model) {
        return model->getName(peer);
    }
    return QString();
}

void CDialogModel::addSourceModel(CPeerModel *peerModel)
{
    m_sourceModels.append(peerModel);
    connect(peerModel, &CPeerModel::pictureChanged, this, &CDialogModel::onPeerPictureChanged);
    connect(peerModel, &CPeerModel::nameChanged, this, &CPeerModel::nameChanged);
    connect(peerModel, &CPeerModel::pictureChanged, this, &CPeerModel::pictureChanged);
}

int CDialogModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(Column::ColumnsCount);
}

int CDialogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_dialogs.count();
}

Telegram::Peer CDialogModel::getPeer(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() > rowCount()) {
        return Telegram::Peer();
    }
    const Telegram::DialogInfo *dialog = m_dialogs.at(index.row());
    return dialog->peer();
}

QVariant CDialogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Column s = static_cast<Column>(section);

    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (s) {
    case Column::PeerType:
        return tr("Type");
    case Column::PeerId:
        return tr("Id");
    case Column::PeerName:
        return tr("Name");
    case Column::Picture:
        return tr("Picture");
    case Column::MuteUntil:
        return tr("MuteUntil");
    case Column::MuteUntilDate:
        return tr("MuteUntilDate");
    default:
        break;
    }

    return QVariant();
}

QVariant CDialogModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::DecorationRole:
        break;
    default:
        return QVariant();
    }

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_dialogs.count()) {
        return QVariant();
    }

    const Column ownColumn = static_cast<Column>(index.column());
    const Role ownRole = columnToRole(ownColumn, role);
    if (ownRole == Role::Invalid) {
        return QVariant();
    }

    return data(index.row(), ownRole);
}

QVariant CDialogModel::data(int dialogIndex, CDialogModel::Role role) const
{
    const Telegram::DialogInfo *dialog = m_dialogs.at(dialogIndex);

    switch (role) {
    case Role::PeerType:
        return dialog->peer().type;
    case Role::PeerId:
        return dialog->peer().id;
    case Role::MuteUntil:
        return 0; //dialog->muteUntil();
    case Role::MuteUntilDate:
        // if (dialog->muteUntil()) {
        //     return QDateTime::fromMSecsSinceEpoch(dialog->muteUntil() * 1000);
        // }
        return QVariant();
        // PeerModel roles:
    case Role::PeerName:
        return getName(dialog->peer());
    case Role::Picture:
        return getPicture(dialog->peer(), Telegram::PeerPictureSize::Small).pixmap;
    default:
        break;
    }
    return QVariant();
}

int CDialogModel::indexOfPeer(const Telegram::Peer peer) const
{
    for (int i = 0; i < m_dialogs.count(); ++i) {
        if (m_dialogs.at(i)->peer() == peer) {
            return i;
        }
    }
    return -1;
}

void CDialogModel::setDialogs(const QVector<Telegram::Peer> &dialogs)
{
    qDebug() << Q_FUNC_INFO << dialogs;
    beginResetModel();
    qDeleteAll(m_dialogs);
    m_dialogs.clear();
    for (const Telegram::Peer &peer : dialogs) {
        Telegram::DialogInfo *info = new Telegram::DialogInfo();
        m_backend->dataStorage()->getDialogInfo(info, peer);
        m_dialogs.append(info);
    }
    endResetModel();
}

void CDialogModel::syncDialogs(const QVector<Telegram::Peer> &added, const QVector<Telegram::Peer> &removed)
{
    Q_UNUSED(removed)

    QVector<Telegram::Peer> reallyAddedDialogs;
    for (const Telegram::Peer &newPeer : added) {
        if (indexOfPeer(newPeer) < 0) {
            reallyAddedDialogs.append(newPeer);
        }
    }
    if (reallyAddedDialogs.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), m_dialogs.count(), m_dialogs.count() + reallyAddedDialogs.count() - 1);
    for (const Telegram::Peer &peer : reallyAddedDialogs) {
        Telegram::DialogInfo *info = new Telegram::DialogInfo();
        m_backend->dataStorage()->getDialogInfo(info, peer);
        m_dialogs.append(info);
    }
    endInsertRows();
}

void CDialogModel::onPeerPictureChanged(const Telegram::Peer peer)
{
    const int i = indexOfPeer(peer);
    if (i < 0) {
        return;
    }
    const QModelIndex modelIndex = index(i, static_cast<int>(Column::Picture));
    emit dataChanged(modelIndex, modelIndex);
}

CDialogModel::Role CDialogModel::columnToRole(Column column, int qtRole)
{
    if (qtRole == Qt::DecorationRole) {
        switch (column) {
        case Column::Picture:
            return Role::Picture;
        default:
            return Role::Invalid;
        }
    }

    switch (column) {
    case Column::PeerType:
        return Role::PeerType;
    case Column::PeerId:
        return Role::PeerId;
    case Column::PeerName:
        return Role::PeerName;
    case Column::MuteUntil:
        return Role::MuteUntil;
    case Column::MuteUntilDate:
        return Role::MuteUntilDate;
    default:
        return Role::Invalid;
    }
}

CPeerModel *CDialogModel::modelForPeer(const Telegram::Peer peer) const
{
    for (CPeerModel *model : m_sourceModels) {
        if (model->hasPeer(peer)) {
            return model;
        }
    }
    return nullptr;
}
