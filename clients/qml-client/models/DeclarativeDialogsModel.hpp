#ifndef TELEGRAMQT_DECLARATIVE_DIALOGS_MODEL_HPP
#define TELEGRAMQT_DECLARATIVE_DIALOGS_MODEL_HPP

#include "DialogsModel.hpp"

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

#include "DeclarativeClientOperator.hpp"

namespace Telegram {

struct UserDialog;

namespace Client {

class DeclarativeClient;
class DialogList;

class DeclarativeDialogsModel : public DialogsModel, public DeclarativeClientMixin
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Client::DeclarativeClient *client READ qmlClient WRITE setQmlClient NOTIFY clientChanged)
public:
    explicit DeclarativeDialogsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

public slots:
    void setQmlClient(DeclarativeClient *client);

//    void setDialogs(const QVector<Telegram::Peer> &dialogs);
//    void syncDialogs(const QVector<Telegram::Peer> &added, const QVector<Telegram::Peer> &removed);

//protected slots:
//    void onPeerPictureChanged(const Telegram::Peer peer);

//protected:
//    static Role columnToRole(Column column, int qtRole);
//    CPeerModel *modelForPeer(const Telegram::Peer peer) const;

Q_SIGNALS:
    void clientChanged();

private:
    Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DECLARATIVE_DIALOGS_MODEL_HPP
