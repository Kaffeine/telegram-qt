#ifndef CDIALOGMODEL_HPP
#define CDIALOGMODEL_HPP

#include "CPeerModel.hpp"

#include "TelegramNamespace.hpp"

class CDialogModel : public CPeerModel
{
    Q_OBJECT
public:
    enum class Column {
        PeerType,
        PeerId,
        PeerName,
        Picture, // Photo (in terms of Telegram)
        MuteUntil,
        MuteUntilDate,
        ColumnsCount
    };

    enum class Role {
        PeerType,
        PeerId,
        PeerName,
        Picture, // Photo (in terms of Telegram)
        MuteUntil,
        MuteUntilDate,
        Invalid,
    };

    explicit CDialogModel(Telegram::Client::Client *backend, QObject *parent = nullptr);

    bool hasPeer(const Telegram::Peer peer) const override;
    QString getName(const Telegram::Peer peer) const override;

    void addSourceModel(CPeerModel *peerModel);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Telegram::Peer getPeer(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//    QVariant data(const QString &phone, Section section) const;
//    QVariant data(quint32 id, Section section) const;
    QVariant data(int dialogIndex, Role role) const;

    int indexOfPeer(const Telegram::Peer peer) const;

public slots:
    void setDialogs(const QVector<Telegram::Peer> &dialogs);
    void syncDialogs(const QVector<Telegram::Peer> &added, const QVector<Telegram::Peer> &removed);

protected slots:
    void onPeerPictureChanged(const Telegram::Peer peer);

protected:
    static Role columnToRole(Column column, int qtRole);
    CPeerModel *modelForPeer(const Telegram::Peer peer) const;

private:
    QVector<CPeerModel*> m_sourceModels;
    QVector<Telegram::DialogInfo*> m_dialogs;

};

#endif // CDIALOGMODEL_HPP
