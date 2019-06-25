#ifndef TELEGRAMQT_WIDGETS_DIALOGS_MODEL_HPP
#define TELEGRAMQT_WIDGETS_DIALOGS_MODEL_HPP

#include "TelegramNamespace.hpp"

#include <QAbstractTableModel>

namespace Telegram {

struct UserDialog;

namespace Client {

class Client;
class DialogList;

} // Client namespace

} // Telegram namespace

class CDialogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    class DialogEntry
    {
    public:
        bool lastMessageIsOutdated() const;
        Telegram::Namespace::ChatType chatType;
        QString name;
        QString formattedLastMessage;
        Telegram::Message lastChatMessage;
        Telegram::DialogInfo info;
        QString pictureFileId;
    };

    enum class Role {
        Peer,
        PeerAsString,
        DisplayName,
        ChatType,
        IsPinned,
        PictureFileId, // Photo (in terms of Telegram)
        LastMessage,
        LastMessageText,
        FormattedLastMessage,
        MuteUntil,
        MuteUntilDate,
        UnreadMessageCount,
        Count,
        Invalid
    };

    enum class Column {
        Peer,
        DisplayName,
        LastMessageText,
        Count,
        Invalid
    };

    explicit CDialogModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    Telegram::Client::Client *client() const;

    bool hasPeer(const Telegram::Peer peer) const;
    QString getName(const Telegram::Peer peer) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant getData(int index, Role role) const;

public slots:
    void setClient(Telegram::Client::Client *client);

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
    void onNewMessage(const Telegram::Peer peer, quint32 messageId);

private:
    int getDialogIndex(const Telegram::Peer peer) const;
    bool updateDialogLastMessage(DialogEntry *entry);
    QVariantMap getDialogLastMessageData(const DialogEntry &dialog) const;

    static Role intToRole(int value);
    static Column intToColumn(int value);
    static QVector<int> rolesToInt(const QVector<Role> &roles);
    virtual Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Telegram::Client::Client *m_client = nullptr;
    QVector<DialogEntry> m_dialogs;
    Telegram::Client::DialogList *m_list = nullptr;
};

#endif // TELEGRAMQT_DIALOGS_MODEL_HPP
