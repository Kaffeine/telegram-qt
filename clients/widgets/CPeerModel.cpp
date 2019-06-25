#include "CPeerModel.hpp"

#include "Client.hpp"

#include <QPixmapCache>

CPeerModel::CPeerModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_backend(nullptr),
    m_fileManager(nullptr)
{

}

void CPeerModel::setBackend(Telegram::Client::Client *backend)
{
    m_backend = backend;
}

void CPeerModel::setFileManager(CFileManager *manager)
{
    m_fileManager = manager;
    // connect(m_fileManager, &CFileManager::requestComplete, this, &CPeerModel::onFileRequestComplete);
}

PeerPicture CPeerModel::getPicture(const Telegram::Peer peer, const Telegram::PeerPictureSize size) const
{
    return PeerPicture(); //getPicture(m_backend->peerPictureToken(peer), size);
}

PeerPicture CPeerModel::getPicture(const QString &fileId, const Telegram::PeerPictureSize size) const
{
    Q_UNUSED(size)

    if (fileId.isEmpty()) {
        return PeerPicture();
    }
    const QByteArray data; // = m_fileManager->getData(fileId);
    const QString pictureToken = getPictureCacheToken(fileId);
    const QPixmap picture = getScaledPixmap(QPixmap::fromImage(QImage::fromData(data)));
    if (!picture.isNull()) {
        QPixmapCache::insert(pictureToken, picture);
    }
    return { pictureToken, picture };
}

QString CPeerModel::getPictureCacheToken(const QString &key) const
{
    if (key.isEmpty()) {
        return QString();
    }
    return QStringLiteral("64-") + key;
}

void CPeerModel::onFileRequestComplete(const QString &uniqueId)
{
    if (!m_requests.contains(uniqueId)) {
        return;
    }
    m_requests.remove(uniqueId);
    const PeerPicture pictureData = getPicture(uniqueId);
    if (!pictureData.pixmap.isNull()) {
        updatePeerPicture(pictureData);
    }
}

void CPeerModel::updatePeerPicture(const PeerPicture &picture)
{
    Q_UNUSED(picture)
}

PeerPicture CPeerModel::getPeerPictureNowOrLater(const Telegram::Peer peer)
{
    const PeerPicture pictureData = getPicture(peer);
    if (pictureData.pixmap.isNull()) {
        const QString requestToken; // = m_fileManager->requestPeerPicture(peer);
        m_requests.insert(requestToken);
    }
    return pictureData;
}

QPixmap CPeerModel::getScaledPixmap(const QPixmap &picture)
{
    if (picture.isNull()) {
        return QPixmap();
    }
    return picture.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
