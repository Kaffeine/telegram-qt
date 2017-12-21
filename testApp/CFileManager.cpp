#include "CFileManager.hpp"

#include <TelegramQt/CTelegramCore>
#include <TelegramQt/Debug>

#ifdef STORE_MEDIA_FILES
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>

static const QString c_fileCacheDirectory = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QStringLiteral("/telegram-qt/files/");
#endif

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
    if (!m_data.isEmpty()) {
        setSize(m_data.size());
    }
}

#ifdef STORE_MEDIA_FILES
QHash<QString,FileInfo> getIndex()
{
    QFile indexFile(c_fileCacheDirectory + QStringLiteral("index.json"));
    if (!indexFile.open(QIODevice::ReadOnly)) {
        return {};
    }
    QJsonParseError parseError;
    const QJsonDocument indexDoc = QJsonDocument::fromJson(indexFile.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "CFileManager::getIndex(): Parse error:" << parseError.errorString() << "(" << parseError.error << ")";
        return {};
    }
    const QJsonObject indexObj = indexDoc.object();
    switch (indexObj.value(QLatin1String("format")).toInt()) {
    case 1:
        break;
    default:
        qWarning() << "CFileManager::getIndex(): Unknown index format";
        return {};
    }

    QVariantMap filesMap = indexObj.value("files").toObject().toVariantMap();
    QHash<QString,FileInfo> fileIndex;
    fileIndex.reserve(filesMap.size() + 10);
    for (const QString &id : filesMap.keys()) {
        const QVariantMap v = filesMap.value(id).toMap();
        FileInfo info;
        info.setSize(v.value("size").toInt());
        info.setMimeType(v.value("mimeType").toString());
        Telegram::RemoteFile f;
        info.completeDownload(f);

        fileIndex.insert(id, info);
    }
    return fileIndex;
}
#endif

CFileManager::CFileManager(CTelegramCore *backend, QObject *parent) :
    QObject(parent),
    m_backend(backend)
{
    connect(m_backend, SIGNAL(filePartReceived(quint32,QByteArray,QString,quint32,quint32)),
            SLOT(onFilePartReceived(quint32,QByteArray,QString,quint32,quint32)));
    connect(m_backend, SIGNAL(fileRequestFinished(quint32,Telegram::RemoteFile)),
            this, SLOT(onFileRequestFinished(quint32,Telegram::RemoteFile)));

#ifdef STORE_MEDIA_FILES
    m_files = getIndex();
#endif
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
#ifdef STORE_MEDIA_FILES
    if (info.data().isEmpty()) {
        QFile dataFile(c_fileCacheDirectory + uniqueId + QStringLiteral(".dat"));
        if (dataFile.open(QIODevice::ReadOnly)) {
            return dataFile.readAll();
        }
    }
#endif
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
#ifdef STORE_MEDIA_FILES
    QDir().mkpath(c_fileCacheDirectory);
    QFile dataFile(c_fileCacheDirectory + key + QStringLiteral(".dat"));
    dataFile.open(QIODevice::WriteOnly);
    dataFile.write(m_files.value(key).data());
    dataFile.close();

    QVariantMap filesMap;
    for (const QString &id : m_files.keys()) {
        const FileInfo &info = m_files.value(id);
        if (!info.isComplete()) {
            continue;
        }
        QVariantMap fileData = {
            { "mimeType", info.mimeType() },
            { "size", info.size() },
        };
        filesMap.insert(id, fileData);
    }
    QJsonObject indexObj;
    indexObj["format"] = 1;
    indexObj["files"] = QJsonObject::fromVariantMap(filesMap);
    QJsonDocument indexDoc(indexObj);

    QFile indexFile(c_fileCacheDirectory + QStringLiteral("index.json"));
    indexFile.open(QIODevice::WriteOnly);
    indexFile.write(indexDoc.toJson(QJsonDocument::Indented));
#endif
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
