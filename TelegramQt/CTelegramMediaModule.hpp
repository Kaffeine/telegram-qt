/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef CTELEGRAMMEDIAMODULE_HPP
#define CTELEGRAMMEDIAMODULE_HPP

#include "CTelegramModule.hpp"

#include <QMap>

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"
#include "FileRequestDescriptor.hpp"

QT_FORWARD_DECLARE_CLASS(QIODevice)

class CTelegramMediaModule : public CTelegramModule
{
    Q_OBJECT
public:
    explicit CTelegramMediaModule(QObject *parent = 0);
    ~CTelegramMediaModule();

    void setMediaDataBufferSize(quint32 size);

    QString peerPictureToken(const Telegram::Peer &peer, const Telegram::PeerPictureSize size) const Q_REQUIRED_RESULT;
    quint32 requestPeerPicture(const Telegram::Peer &peer, const Telegram::PeerPictureSize size) Q_REQUIRED_RESULT;
    bool requestMessageMediaData(quint32 messageId);
    quint32 requestFile(const Telegram::RemoteFile *file, quint32 chunkSize = 0);
    bool getMessageMediaInfo(Telegram::MessageMediaInfo *messageInfo, quint32 messageId) const;

    quint32 uploadFile(const QByteArray &fileContent, const QString &fileName);
    quint32 uploadFile(QIODevice *source, const QString &fileName);

    quint64 sendMedia(const Telegram::Peer &peer, const Telegram::MessageMediaInfo &messageInfo);

    void clear() override;

signals:
    void filePartUploaded(quint32 requestId, quint32 offset, quint32 size);
    void fileRequestFinished(quint32 requestId, Telegram::RemoteFile uploadInfo);
    void filePartReceived(quint32 requestId, const QByteArray &data, const QString &mimeType, quint32 offset, quint32 totalSize);

    void avatarReceived(quint32 userId, const QByteArray &data, const QString &mimeType, const QString &avatarToken);
    void messageMediaDataReceived(Telegram::Peer peer, quint32 messageId, const QByteArray &data, const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);

protected slots:
    void onFileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset);
    void onFileDataUploaded(quint32 requestId);

protected:
    void onConnectionAuthChanged(CTelegramConnection *connection, int newState) override;
    void onNewConnection(CTelegramConnection *connection) override;

    template <typename T>
    QString getPictureToken(const T *peerData, const Telegram::PeerPictureSize size) const Q_REQUIRED_RESULT;

    template <typename T>
    quint32 getPeerPicture(const T *peerData, const Telegram::PeerPictureSize size) Q_REQUIRED_RESULT;

    quint32 addFileRequest(const FileRequestDescriptor &descriptor);
    void processFileRequestForConnection(CTelegramConnection *connection, quint32 requestId);

    quint32 m_mediaDataBufferSize;
    QMap<quint32, FileRequestDescriptor> m_requestedFileDescriptors; // fileId, file request descriptor
    quint32 m_fileRequestCounter;

};

#endif // CTELEGRAMMEDIAHANDLER_HPP
