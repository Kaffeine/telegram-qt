#include "CTelegramMediaModule.hpp"

#include "CTelegramDispatcher.hpp"
#include "CTelegramConnection.hpp"
#include "TelegramNamespace_p.hpp"
#include "TelegramUtils.hpp"
#include "Utils.hpp"

#include <QDebug>

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

using namespace TelegramUtils;

CTelegramMediaModule::CTelegramMediaModule(QObject *parent) :
    CTelegramModule(parent),
    m_mediaDataBufferSize(FileRequestDescriptor::defaultDownloadPartSize()),
    m_fileRequestCounter(0)
{
}

CTelegramMediaModule::~CTelegramMediaModule()
{
}

QString CTelegramMediaModule::contactAvatarToken(quint32 userId) const
{
    const TLUser *user = getUser(userId);

    if (!user) {
        qDebug() << Q_FUNC_INFO << "Unknown identifier" << userId;
        return QString();
    }

    return userAvatarToken(user);
}

void CTelegramMediaModule::setMediaDataBufferSize(quint32 size)
{
    if (size % 256) {
        qDebug() << Q_FUNC_INFO << "Unable to set incorrect size" << size << ". The value must be divisible by 1 KB";
        return;
    }

    if (!size) {
        size = FileRequestDescriptor::defaultDownloadPartSize();
    }

    m_mediaDataBufferSize = size;
}

void CTelegramMediaModule::requestContactAvatar(quint32 userId)
{
    qDebug() << Q_FUNC_INFO << userId;
    Telegram::UserInfo info;
    if (!getUserInfo(&info, userId)) {
        return;
    }

    Telegram::RemoteFile location;
    if (!info.getPeerPicture(&location)) {
        return;
    }

    quint32 requestId = requestFile(&location, /* chunkSize */ 512 * 256); // Set chunkSize to some big number to get the whole avatar at once

    if (!requestId) {
        return;
    }

    m_requestedFileDescriptors[requestId].setUserId(userId);
}

bool CTelegramMediaModule::requestMessageMediaData(quint32 messageId)
{
    Telegram::MessageMediaInfo info;
    if (!getMessageMediaInfo(&info, messageId)) {
        return false;
    }

    Telegram::RemoteFile location;
    if (!info.getRemoteFileInfo(&location)) {
        return false;
    }

    location.d->m_size = info.size();
    quint32 requestId = requestFile(&location, info.size());

    if (!requestId) {
        return false;
    }

    m_requestedFileDescriptors[requestId].setMessageId(messageId);
    return true;
}

quint32 CTelegramMediaModule::requestFile(const Telegram::RemoteFile *file, quint32 chunkSize)
{
    if (!file->isValid()) {
        return 0;
    }

    FileRequestDescriptor request;
    request.setType(FileRequestDescriptor::Download);
    request.setDcId(file->d->m_dcId);
    request.setInputLocation(*file->d->m_inputFileLocation);
    request.setSize(file->d->m_size);
    request.uniqueId = file->getUniqueId();

    if (chunkSize) {
        request.setChunkSize(chunkSize);
    } else {
        request.setChunkSize(m_mediaDataBufferSize);
    }
    return addFileRequest(request);
}

bool CTelegramMediaModule::getMessageMediaInfo(Telegram::MessageMediaInfo *messageInfo, quint32 messageId) const
{
    const TLMessage *message = getMessage(messageId);
    if (!message) {
        qDebug() << Q_FUNC_INFO << "Unknown media message" << messageId;
        return false;
    }

    const TLMessageMedia &media = message->media;
    TLMessageMedia &info = *messageInfo->d;
    info = media;
    return true;
}

quint32 CTelegramMediaModule::uploadFile(const QByteArray &fileContent, const QString &fileName)
{
    if (!activeConnection()) {
        qWarning() << Q_FUNC_INFO << "Called without connection";
        return 0;
    }
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << fileName;
#endif
    return addFileRequest(FileRequestDescriptor::uploadRequest(fileContent, fileName, activeConnection()->dcInfo().id));
}

quint32 CTelegramMediaModule::uploadFile(QIODevice *source, const QString &fileName)
{
    return uploadFile(source->readAll(), fileName);
}

quint64 CTelegramMediaModule::sendMedia(const Telegram::Peer &peer, const Telegram::MessageMediaInfo &info)
{
    if (!activeConnection()) {
        return 0;
    }

    const Telegram::MessageMediaInfo::Private *media = info.d;
    TLInputMedia inputMedia;

    if (media->m_isUploaded) {
        switch (media->tlType) {
        case TLValue::MessageMediaPhoto:
            inputMedia.tlType = TLValue::InputMediaUploadedPhoto;
            break;
        case TLValue::MessageMediaAudio:
            inputMedia.tlType = TLValue::InputMediaUploadedAudio;
            inputMedia.duration = media->audio.duration;
            inputMedia.mimeType = media->audio.mimeType;
            break;
        case TLValue::MessageMediaVideo:
            inputMedia.tlType = TLValue::InputMediaUploadedVideo;
            inputMedia.duration = media->video.duration;
            inputMedia.w = media->video.w;
            inputMedia.h = media->video.h;
            break;
        case TLValue::MessageMediaDocument:
            inputMedia.tlType = TLValue::InputMediaUploadedDocument;
            inputMedia.mimeType = media->document.mimeType;
            inputMedia.attributes = media->document.attributes;
            break;
        default:
            return 0;
            break;
        }
        inputMedia.file = *media->m_inputFile;
        inputMedia.caption = media->caption;
    } else {
        switch (media->tlType) {
        case TLValue::MessageMediaPhoto:
            inputMedia.tlType = TLValue::InputMediaPhoto;
            inputMedia.idInputPhoto.tlType = TLValue::InputPhoto;
            inputMedia.idInputPhoto.id = media->photo.id;
            inputMedia.idInputPhoto.accessHash = media->photo.accessHash;
            break;
        case TLValue::MessageMediaAudio:
            inputMedia.tlType = TLValue::InputMediaAudio;
            inputMedia.idInputAudio.tlType = TLValue::InputAudio;
            inputMedia.idInputAudio.id = media->audio.id;
            inputMedia.idInputAudio.accessHash = media->audio.accessHash;
            break;
        case TLValue::MessageMediaVideo:
            inputMedia.tlType = TLValue::InputMediaVideo;
            inputMedia.idInputVeo.tlType = TLValue::InputVideo;
            inputMedia.idInputVeo.id = media->video.id;
            inputMedia.idInputVeo.accessHash = media->video.accessHash;
            break;
        case TLValue::MessageMediaGeo:
            inputMedia.tlType = TLValue::InputMediaGeoPoint;
            inputMedia.geoPoint.tlType = TLValue::InputGeoPoint;
            inputMedia.geoPoint.longitude = media->geo.longitude;
            inputMedia.geoPoint.latitude = media->geo.latitude;
            break;
        case TLValue::MessageMediaContact:
            inputMedia.tlType = TLValue::InputMediaContact;
            inputMedia.firstName = media->firstName;
            inputMedia.lastName = media->lastName;
            inputMedia.phoneNumber = media->phoneNumber;
            break;
        case TLValue::MessageMediaDocument:
            inputMedia.tlType = TLValue::InputMediaDocument;
            inputMedia.idInputDocument.tlType = TLValue::InputDocument;
            inputMedia.idInputDocument.id = media->document.id;
            inputMedia.idInputDocument.accessHash = media->document.accessHash;
            break;
        default:
            return 0;
            break;
        }
    }

    return CTelegramModule::sendMedia(peer, inputMedia);
}

void CTelegramMediaModule::clear()
{
    m_requestedFileDescriptors.clear();
    m_fileRequestCounter = 0;
}

void CTelegramMediaModule::onFileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset)
{
    if (!m_requestedFileDescriptors.contains(requestId)) {
        qDebug() << Q_FUNC_INFO << "Unexpected request" << requestId;
        return;
    }

    FileRequestDescriptor &descriptor = m_requestedFileDescriptors[requestId];
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << "File:" << file.tlType << file.type << "mtime:" << file.mtime;
    qDebug() << Q_FUNC_INFO
             << "Descriptor:" << "request:" << requestId
             << "type:" << descriptor.type()
             << "size:" << descriptor.size()
             << "ids:" << descriptor.userId() << descriptor.messageId();
#endif

    if (descriptor.type() != FileRequestDescriptor::Download) {
        return;
    }

    const quint32 chunkSize = file.bytes.size();

    QString mimeType = mimeTypeByStorageFileType(file.type.tlType);

    // Depends on InputFileLocation tlType, we can either have descriptor.size() (for MediaMessage data (Audio, Video, Document)),
    // or have file type StorageFilePartial otherwise.

    bool isFinished = false;

    if (descriptor.size()) {
        isFinished = descriptor.offset() + chunkSize == descriptor.size();
    } else {
        isFinished = file.type.tlType != TLValue::StorageFilePartial;
    }

    if (isFinished) {
        descriptor.setSize(descriptor.offset() + chunkSize);
    }

    emit filePartReceived(requestId, file.bytes, mimeType, descriptor.offset(), descriptor.size()); // Size can be unknown (== 0)

    if (isFinished) {
#ifdef DEVELOPER_BUILD
        qDebug() << Q_FUNC_INFO << "file" << requestId << "download finished.";
#endif

        Telegram::RemoteFile result;
        const TLInputFileLocation location = descriptor.inputLocation();
        result.d->setInputFileLocation(&location);
        result.d->m_dcId = descriptor.dcId();
        result.d->m_type = Telegram::RemoteFile::Download;
        emit fileRequestFinished(requestId, result);

        m_requestedFileDescriptors.remove(requestId);
    } else {
        descriptor.setOffset(offset + chunkSize);

        CTelegramConnection *connection = qobject_cast<CTelegramConnection*>(sender());
        if (connection) {
            processFileRequestForConnection(connection, requestId);
        } else {
            qDebug() << Q_FUNC_INFO << "Invalid call. The method must be called only on CTelegramConnection signal.";
        }
    }

    // Legacy stuff:
    if (isFinished) {
        const TLUser *user = getUser(descriptor.userId());
        if (descriptor.userId() && user) {
            emit avatarReceived(descriptor.userId(), file.bytes, mimeType, userAvatarToken(user));
        }
    }

    const TLMessage *message = nullptr;
    if (descriptor.messageId() && (message = getMessage(descriptor.messageId()))) {
        const TelegramNamespace::MessageType messageType = telegramMessageTypeToPublicMessageType(message->media.tlType);

        Telegram::Peer peer = toPublicPeer(message->toId);

        // MimeType can not be resolved for some StorageFileType. Try to get the type from the message info in this case.
        if (mimeType.isEmpty()) {
            Telegram::MessageMediaInfo info;
            getMessageMediaInfo(&info, message->id);
            mimeType = info.mimeType();
        }

        if (!(message->flags & TelegramMessageFlagOut)) {
            if (peer.type == Telegram::Peer::User) {
                peer = message->fromId;
            }
        }

#ifdef DEVELOPER_BUILD
        qDebug() << Q_FUNC_INFO << "MessageMediaData:" << message->id << offset << "-" << offset + chunkSize << "/" << descriptor.size();
#endif
        emit messageMediaDataReceived(peer, message->id, file.bytes, mimeType, messageType, offset, descriptor.size());
    }
}

void CTelegramMediaModule::onFileDataUploaded(quint32 requestId)
{
    if (!m_requestedFileDescriptors.contains(requestId)) {
        qDebug() << Q_FUNC_INFO << "Unexpected fileId" << requestId;
        return;
    }

    FileRequestDescriptor &descriptor = m_requestedFileDescriptors[requestId];

    if (descriptor.type() != FileRequestDescriptor::Upload) {
        return;
    }

    descriptor.bumpPart();

    emit filePartUploaded(requestId, descriptor.offset(), descriptor.size());

    if (descriptor.finished()) {
        Telegram::RemoteFile result;
        const TLInputFile fileInfo = descriptor.inputFile();
        result.d->m_size = descriptor.size();
        result.d->m_type = Telegram::RemoteFile::Upload;
        result.d->setInputFile(&fileInfo);

        emit fileRequestFinished(requestId, result);
        return;
    }

    CTelegramConnection *connection = qobject_cast<CTelegramConnection*>(sender());
    if (connection) {
        processFileRequestForConnection(connection, requestId);
    } else {
        qDebug() << Q_FUNC_INFO << "Invalid call. The method must be called only on CTelegramConnection signal.";
    }
}

void CTelegramMediaModule::onConnectionAuthChanged(CTelegramConnection *connection, int newState)
{
    CTelegramConnection::AuthState state = static_cast<CTelegramConnection::AuthState>(newState);
    qDebug() << Q_FUNC_INFO << connection << "auth" << state;

    if (!connection) {
        qDebug() << Q_FUNC_INFO << "Invalid slot call";
        return;
    }

    if (connection == activeConnection()) {
        qDebug() << Q_FUNC_INFO << "Skip main connection"; // because media should work only via extra connection
        return;
    } else {
        foreach (quint32 fileId, m_requestedFileDescriptors.keys()) {
            if (m_requestedFileDescriptors.value(fileId).dcId() != connection->dcInfo().id) {
                continue;
            }

            if (connection->status() == CTelegramConnection::ConnectionStatusDisconnected) {
                connection->connectToDc();
                return;
            }

            if (state == CTelegramConnection::AuthStateSignedIn) {
                processFileRequestForConnection(connection, fileId);
            }
        }
    }
}

void CTelegramMediaModule::onNewConnection(CTelegramConnection *connection)
{
    qDebug() << Q_FUNC_INFO << connection;
    connect(connection, SIGNAL(fileDataReceived(TLUploadFile,quint32,quint32)), SLOT(onFileDataReceived(TLUploadFile,quint32,quint32)));
    connect(connection, SIGNAL(fileDataSent(quint32)), SLOT(onFileDataUploaded(quint32)));
}

QString CTelegramMediaModule::userAvatarToken(const TLUser *user) const
{
    const TLFileLocation &avatar = user->photo.photoSmall;

    if (avatar.tlType == TLValue::FileLocationUnavailable) {
        return QString();
    } else {
        return QString(QLatin1String("%1%2%3"))
                .arg(avatar.dcId, sizeof(avatar.dcId) * 2, 16, QLatin1Char('0'))
                .arg(avatar.volumeId, sizeof(avatar.dcId) * 2, 16, QLatin1Char('0'))
                .arg(avatar.localId, sizeof(avatar.dcId) * 2, 16, QLatin1Char('0'));
    }
}

quint32 CTelegramMediaModule::addFileRequest(const FileRequestDescriptor &descriptor)
{
    qDebug() << Q_FUNC_INFO << descriptor.dcId() << descriptor.fileId();

    if (!descriptor.isValid()) {
        return 0;
    }

    m_requestedFileDescriptors.insert(++m_fileRequestCounter, descriptor);

    CTelegramConnection *connection = getExtraConnection(descriptor.dcId());

    if (connection->authState() == CTelegramConnection::AuthStateSignedIn) {
        processFileRequestForConnection(connection, m_fileRequestCounter);
    }

    if (connection->status() == CTelegramConnection::ConnectionStatusDisconnected) {
        connection->connectToDc();
    }

    return m_fileRequestCounter;
}

void CTelegramMediaModule::processFileRequestForConnection(CTelegramConnection *connection, quint32 requestId)
{
    const FileRequestDescriptor descriptor = m_requestedFileDescriptors.value(requestId);
    qDebug() << Q_FUNC_INFO << requestId << descriptor.type();

    if (connection->authState() != CTelegramConnection::AuthStateSignedIn) {
        qDebug() << "Failed to request file operation" << connection << requestId << connection->authState();
        return;
    }

    switch (descriptor.type()) {
    case FileRequestDescriptor::Download:
        connection->downloadFile(descriptor.inputLocation(), descriptor.offset(), descriptor.chunkSize(), requestId);
        break;
    case FileRequestDescriptor::Upload:
        connection->uploadFile(descriptor.fileId(), descriptor.part(), descriptor.data(), requestId);
        break;
    default:
        break;
    }
}
