#ifndef CPEERMODEL_HPP
#define CPEERMODEL_HPP

#include <QObject>
#include <QAbstractTableModel>
#include <QPixmap>

#include <QSet>

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class Client;

} // Client namespace

} // Telegram namespace

class CFileManager;

struct PeerPicture {
    QString token;
    QPixmap pixmap;
};

class CPeerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CPeerModel(QObject *parent = nullptr);

    void setBackend(Telegram::Client::Client *backend);
    void setFileManager(CFileManager *manager);

    virtual bool hasPeer(const Telegram::Peer peer) const = 0;
    virtual QString getName(const Telegram::Peer peer) const = 0;
    PeerPicture getPicture(const Telegram::Peer peer, const Telegram::PeerPictureSize size = Telegram::PeerPictureSize::Small) const;
    PeerPicture getPicture(const QString &fileId, const Telegram::PeerPictureSize size = Telegram::PeerPictureSize::Small) const;

signals:
    void nameChanged(const Telegram::Peer peer);
    void pictureChanged(const Telegram::Peer peer);

protected slots:
    void onFileRequestComplete(const QString &uniqueId);

protected:
    virtual void updatePeerPicture(const PeerPicture &picture);
    PeerPicture getPeerPictureNowOrLater(const Telegram::Peer peer);

    static QPixmap getScaledPixmap(const QPixmap &picture);
    QString getPictureCacheToken(const QString &key) const;

    QSet<QString> m_requests;

    Telegram::Client::Client *m_backend;
    CFileManager *m_fileManager;
};

#endif // CPEERMODEL_HPP
