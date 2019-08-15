#ifndef TELEGRAMQT_DIALOGS_MODEL_HPP
#define TELEGRAMQT_DIALOGS_MODEL_HPP

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

namespace Telegram {

struct UserDialog;

namespace Client {

class Client;
class DialogList;

class DialogsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    struct DialogEntry {
        Namespace::ChatType chatType;
        QString name;
        QString formattedLastMessage;
        Telegram::Message lastChatMessage;
        UserDialog *internal = nullptr;
        NotificationSettings notificationSettings;
    };

    enum class Role {
        Peer,
        DisplayName,
        ChatType,
        IsPinned,
        Picture, // Photo (in terms of Telegram)
        LastMessage,
        FormattedLastMessage,
        MuteUntil,
        MuteUntilDate,
        UnreadMessageCount,
        Count,
        Invalid
    };

    using QObject::parent;

    explicit DialogsModel(QObject *parent = nullptr);

    Client *client() const { return m_client; }
    void setClient(Client *client);

    bool hasPeer(const Peer peer) const;
    QString getName(const Peer peer) const;

    Peer getPeer(int index) const;

    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool hasChildren(const QModelIndex &parent) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant getData(int index, Role role) const;

public slots:
    void populate();

Q_SIGNALS:
    void clientChanged();

private slots:
    void onListReady();
    void onListChanged(const Telegram::PeerList &added, const Telegram::PeerList &removed);
    void addPeer(const Telegram::Peer &peer);

protected:
    QModelIndex parent(const QModelIndex &child) const override;

    QVariantMap getDialogLastMessageData(const DialogEntry &dialog) const;

    static Role intToRole(int value);
    virtual Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;

    QVector<DialogEntry> m_dialogs;
    Client *m_client = nullptr;
    DialogList *m_list = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DIALOGS_MODEL_HPP
