#ifndef TELEGRAMQT_DIALOGS_MODEL_HPP
#define TELEGRAMQT_DIALOGS_MODEL_HPP

#include "TelegramNamespace.hpp"

#include "DeclarativeClientOperator.hpp"

#include <QAbstractListModel>

namespace Telegram {

struct UserDialog;

namespace Client {

class DeclarativeClient;
class DialogList;

class DialogsModel : public QAbstractListModel, public DeclarativeClientMixin
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Client::DeclarativeClient *client READ qmlClient WRITE setQmlClient NOTIFY clientChanged)
public:
    class DialogEntry
    {
    public:
        bool lastMessageIsOutdated() const;
        Namespace::ChatType chatType;
        QString name;
        QString formattedLastMessage;
        Telegram::Message lastChatMessage;
        DialogInfo info;
        QString pictureFileId;
    };

    enum class Role {
        Peer,
        DisplayName,
        ChatType,
        IsPinned,
        PictureFileId, // Photo (in terms of Telegram)
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
    void onNewMessage(const Telegram::Peer peer, quint32 messageId);

private:
    int getDialogIndex(const Telegram::Peer peer) const;
    bool updateDialogLastMessage(DialogEntry *entry);
    QVariantMap getDialogLastMessageData(const DialogEntry &dialog) const;

    static Role intToRole(int value);
    static QVector<int> rolesToInt(const QVector<Role> &roles);
    virtual Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVector<DialogEntry> m_dialogs;
    DialogList *m_list = nullptr;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DIALOGS_MODEL_HPP
