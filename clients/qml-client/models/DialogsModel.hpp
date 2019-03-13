#ifndef TELEGRAMQT_DIALOGS_MODEL_HPP
#define TELEGRAMQT_DIALOGS_MODEL_HPP

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

#include "DeclarativeClientOperator.hpp"

namespace Telegram {

namespace Client {

class DeclarativeClient;
class DialogList;

class DialogsModel : public QAbstractTableModel, public DeclarativeClientMixin
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Client::DeclarativeClient *client READ qmlClient WRITE setQmlClient NOTIFY clientChanged)
public:
    struct DialogEntry {
        Telegram::Peer peer;
        QString typeIcon;
        QString name;
        QString formattedLastMessage;
        Telegram::Message lastChatMessage;
        quint32 unreadCount = 0;
    };

    enum class Column {
        PeerType,
        PeerId,
        PeerName,
        Picture, // Photo (in terms of Telegram)
        FormattedLastMessage,
        MuteUntil,
        MuteUntilDate,
        Count,
        Invalid
    };

    enum class Role {
        Peer,
        PeerTypeIcon,
        DisplayName,
        Picture, // Photo (in terms of Telegram)
        LastMessage,
        FormattedLastMessage,
        MuteUntil,
        MuteUntilDate,
        UnreadMessageCount,
        Count,
        Invalid
    };

    explicit DialogsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    bool hasPeer(const Peer peer) const;
    QString getName(const Peer peer) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant getData(int index, Role role) const;

public slots:
    void setQmlClient(DeclarativeClient *client);

    void populate();
//    void setDialogs(const QVector<Telegram::Peer> &dialogs);
//    void syncDialogs(const QVector<Telegram::Peer> &added, const QVector<Telegram::Peer> &removed);

//protected slots:
//    void onPeerPictureChanged(const Telegram::Peer peer);

//protected:
//    static Role columnToRole(Column column, int qtRole);
//    CPeerModel *modelForPeer(const Telegram::Peer peer) const;

Q_SIGNALS:
    void clientChanged();

private slots:
    void onListReady();
    void onListChanged(const Telegram::PeerList &added, const Telegram::PeerList &removed);
    void addPeer(const Telegram::Peer &peer);

private:
    QVariantMap getDialogLastMessageData(const DialogEntry &dialog) const;
    static Role intToRole(int value);
    static Column intToColumn(int value);
    static Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole);
    QVector<DialogEntry> m_dialogs;
    DialogList *m_list = nullptr;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DIALOGS_MODEL_HPP
