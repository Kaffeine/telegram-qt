/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "CTelegramMediaModule.hpp"

#include "CTelegramConnection.hpp"
#include "TelegramNamespace_p.hpp"
#include "TelegramUtils.hpp"
#include "Utils.hpp"
#include "Debug.hpp"

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

QString CTelegramMediaModule::peerPictureToken(const Telegram::Peer &peer, const Telegram::PeerPictureSize size) const
{
    switch (peer.type) {
    case Telegram::Peer::User:
        return getPictureToken(getUser(peer.id), size);
        break;
    case Telegram::Peer::Chat:
    case Telegram::Peer::Channel:
        return getPictureToken(getChat(peer), size);
        break;
    default:
        break;
    }
    return QString();
}

quint32 CTelegramMediaModule::requestFile(const Telegram::RemoteFile *file, quint32 chunkSize)
{
    if (!file->isValid()) {
        return 0;
    }

    FileRequestDescriptor request;
    request.setType(FileRequestDescriptor::Download);
    request.setDcId(file->d->m_dcId);
    request.setInputLocation(file->d->getInputFileLocation());
    request.setSize(file->d->m_size);
    request.uniqueId = file->getUniqueId();

    if (chunkSize) {
        request.setChunkSize(chunkSize);
    } else {
        request.setChunkSize(m_mediaDataBufferSize);
    }
    return addFileRequest(request);
}

bool CTelegramMediaModule::getMessageMediaInfo(Telegram::MessageMediaInfo *messageInfo, quint32 messageId, const Telegram::Peer &peer) const
{
    const TLMessage *message = getMessage(messageId, peer);
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
    if (!mainConnection()) {
        qWarning() << Q_FUNC_INFO << "Called without connection";
        return 0;
    }
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << fileName;
#endif
    return addFileRequest(FileRequestDescriptor::uploadRequest(fileContent, fileName, mainConnection()->dcInfo().id));
}

quint32 CTelegramMediaModule::uploadFile(QIODevice *source, const QString &fileName)
{
    return uploadFile(source->readAll(), fileName);
}

quint64 CTelegramMediaModule::sendMedia(const Telegram::Peer &peer, const Telegram::MessageMediaInfo &info)
{
    if (!mainConnection()) {
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
            inputMedia.inputPhotoId.tlType = TLValue::InputPhoto;
            inputMedia.inputPhotoId.id = media->photo.id;
            inputMedia.inputPhotoId.accessHash = media->photo.accessHash;
            break;
        case TLValue::MessageMediaAudio:
            inputMedia.tlType = TLValue::InputMediaAudio;
            inputMedia.inputAudioId.tlType = TLValue::InputAudio;
            inputMedia.inputAudioId.id = media->audio.id;
            inputMedia.inputAudioId.accessHash = media->audio.accessHash;
            break;
        case TLValue::MessageMediaVideo:
            inputMedia.tlType = TLValue::InputMediaVideo;
            inputMedia.inputVideoId.tlType = TLValue::InputVideo;
            inputMedia.inputVideoId.id = media->video.id;
            inputMedia.inputVideoId.accessHash = media->video.accessHash;
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
            inputMedia.inputDocumentId.tlType = TLValue::InputDocument;
            inputMedia.inputDocumentId.id = media->document.id;
            inputMedia.inputDocumentId.accessHash = media->document.accessHash;
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
             << "offset:" << descriptor.offset();
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
        if (mainConnection()) {
            result.d->m_dcId = mainConnection()->dcInfo().id;
        }
        result.d->m_size = descriptor.size();
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

void CTelegramMediaModule::onConnectionStateChanged(TelegramNamespace::ConnectionState newConnectionState)
{
    if (newConnectionState == TelegramNamespace::ConnectionStateDisconnected) {
        clear();
    }
}

void CTelegramMediaModule::onConnectionAuthChanged(CTelegramConnection *connection, int newAuthState)
{
    CTelegramConnection::AuthState state = static_cast<CTelegramConnection::AuthState>(newAuthState);
    if (connection == mainConnection()) {
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
    connect(connection, &CTelegramConnection::fileDataReceived, this, &CTelegramMediaModule::onFileDataReceived);
    connect(connection, &CTelegramConnection::fileDataSent, this, &CTelegramMediaModule::onFileDataUploaded);
}

template<typename T>
QString CTelegramMediaModule::getPictureToken(const T *peerData, const Telegram::PeerPictureSize size) const
{
    if (!peerData) {
        qDebug() << "CTelegramMediaModule::getPictureToken(): invalid peer data";
        return QString();
    }
    const TLFileLocation &picture = size == Telegram::PeerPictureSize::Small ? peerData->photo.photoSmall : peerData->photo.photoBig;
    if (picture.tlType == TLValue::FileLocationUnavailable) {
        return QString();
    }

    Telegram::RemoteFile file;
    file.d->setFileLocation(&picture);
    return file.getUniqueId();
}

template<typename T>
quint32 CTelegramMediaModule::getPeerPicture(const T *peerData, const Telegram::PeerPictureSize size)
{
    if (!peerData) {
        qDebug() << "CTelegramMediaModule::getPeerPicture(): invalid peer data";
        return 0;
    }
    const TLFileLocation &picture = size == Telegram::PeerPictureSize::Small ? peerData->photo.photoSmall : peerData->photo.photoBig;
    Telegram::RemoteFile location;
    if (!location.d->setFileLocation(&picture)) {
        return 0;
    }
    return requestFile(&location, /* chunkSize */ 512 * 256); // Set chunkSize to some big number to get the whole avatar at once
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
