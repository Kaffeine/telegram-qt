#include "CFileManager.hpp"

#include <TelegramQt/CTelegramCore>
#include <TelegramQt/Debug>

#include <QDir>
#include <QFile>

static const int c_maxConcurrentDownloads = 8;

void FileInfo::setMimeType(const QString &type)
{
    m_mimeType = type;
}

void FileInfo::addData(const QByteArray &newData)
{
    m_data += newData;
}

void FileInfo::completeDownload(const Telegram::RemoteFile &result)
{
    Q_UNUSED(result)
    m_complete = true;
}

CFileManager::CFileManager(CTelegramCore *backend, QObject *parent) :
    QObject(parent),
    m_backend(backend)
{
    connect(m_backend, SIGNAL(filePartReceived(quint32,QByteArray,QString,quint32,quint32)),
            SLOT(onFilePartReceived(quint32,QByteArray,QString,quint32,quint32)));
    connect(m_backend, SIGNAL(fileRequestFinished(quint32,Telegram::RemoteFile)),
            this, SLOT(onFileRequestFinished(quint32,Telegram::RemoteFile)));
}

QString CFileManager::requestFile(const Telegram::RemoteFile &file)
{
    const QString key = file.getUniqueId();
    if (m_files.contains(key)) {
        qDebug() << Q_FUNC_INFO << key << "already requested";
        return key; // Already requested
    }
    qDebug() << Q_FUNC_INFO << key << "requested";
    FileInfo requestFileInfo;
    m_files.insert(key, requestFileInfo);

    if (m_requestToStringId.count() >= c_maxConcurrentDownloads) {
        m_pendingRequests.insert(key, file);
        qDebug() << Q_FUNC_INFO << "Request delayed" << key;
        return key;
    }

    const quint32 requestId = m_backend->requestFile(&file);
    if (!requestId) {
        qDebug() << Q_FUNC_INFO << "File is not available" << key;
        return QString();
    }
    m_requestToStringId.insert(requestId, key);
    return key;
}

QString CFileManager::requestPeerPicture(const Telegram::Peer &peer, Telegram::PeerPictureSize size)
{
    Telegram::RemoteFile file;
    if (!getPeerPictureFileInfo(peer, &file, size)) {
        return QString();
    }

    const QString key = requestFile(file);
    qDebug() << Q_FUNC_INFO << peer << key;
    if (key.isEmpty()) {
        return QString();
    }
    return key;
}

const FileInfo *CFileManager::getFileInfo(const QString &uniqueId)
{
    if (!m_files.contains(uniqueId)) {
        return nullptr;
    }
    return &m_files[uniqueId];
}

QByteArray CFileManager::getData(const QString &uniqueId) const
{
    if (!m_files.contains(uniqueId)) {
        return QByteArray();
    }
    const FileInfo &info = m_files.value(uniqueId);
    return info.data();
}

bool CFileManager::getPeerPictureFileInfo(const Telegram::Peer &peer, Telegram::RemoteFile *file, Telegram::PeerPictureSize size) const
{
    switch (peer.type) {
    case Telegram::Peer::User:
    {
        Telegram::UserInfo info;
        m_backend->getUserInfo(&info, peer.id);
        return info.getPeerPicture(file, size);
    }
    case Telegram::Peer::Chat:
    case Telegram::Peer::Channel:
    {
        Telegram::ChatInfo info;
        m_backend->getChatInfo(&info, peer);
        return info.getPeerPicture(file, size);
    }
    default:
        break;
    }
    return false;
}

void CFileManager::onFilePartReceived(quint32 requestId, const QByteArray &data, const QString &mimeType, quint32 offset, quint32 totalSize)
{
    Q_UNUSED(offset)
    Q_UNUSED(totalSize)

    const QString key = m_requestToStringId.value(requestId);
    if (key.isEmpty()) {
        // Unknown requestId
        return;
    }
    if (!m_files.contains(key)) {
        // Unknown key. Assert?
        return;
    }

    FileInfo &info = m_files[key];
    if (info.mimeType().isEmpty() && !mimeType.isEmpty()) {
        info.setMimeType(mimeType);
    }
    info.addData(data);
}

void CFileManager::onFileRequestFinished(quint32 requestId, const Telegram::RemoteFile &requestResult)
{
    Q_UNUSED(requestResult)

    const QString key = m_requestToStringId.take(requestId);
    if (key.isEmpty()) {
        // Unknown requestId
        return;
    }
    if (!m_files.contains(key)) {
        // Unknown key. Assert?
        return;
    }

    m_files[key].completeDownload(requestResult);
    qDebug() << Q_FUNC_INFO << "Request complete:" << key << requestId;
    emit requestComplete(key);

    unqueuePendingRequest();
}

QString CFileManager::unqueuePendingRequest()
{
    if (m_pendingRequests.isEmpty()) {
        return QString();
    }

    qDebug() << Q_FUNC_INFO << "remains:" << m_pendingRequests.count() << m_pendingRequests.keys();
    const auto it = m_pendingRequests.begin();
    const QString key = it.key();
    const Telegram::RemoteFile info = m_pendingRequests.take(key);
    qDebug() << Q_FUNC_INFO << "took key:" << key;

    const quint32 requestId = m_backend->requestFile(&info);
    if (!requestId) {
        qDebug() << Q_FUNC_INFO << "File is not available" << key;
        return QString();
    }
    m_requestToStringId.insert(requestId, key);
    return key;
}
