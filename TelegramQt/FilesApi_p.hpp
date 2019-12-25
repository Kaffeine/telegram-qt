/*
   Copyright (C) 2019 Alexander Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_CLIENT_FILES_API_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_FILES_API_PRIVATE_HPP

#include <QQueue>

#include "ClientApi_p.hpp"

#include "FilesApi.hpp"
#include "FileRequestDescriptor.hpp"

#include "RpcLayers/ClientRpcUploadLayer.hpp"

QT_FORWARD_DECLARE_CLASS(QTimer)

namespace Telegram {

namespace Client {

class Connection;
class ConnectOperation;
class UploadRpcLayer;

class FilesApiPrivate : public ClientApiPrivate
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(FilesApi)
public:
    explicit FilesApiPrivate(FilesApi *parent = nullptr);
    static FilesApiPrivate *get(FilesApi *parent);

    FileOperation *downloadFile(const QString &fileId, QIODevice *output);
    FileOperation *downloadFile(const FileInfo *file, QIODevice *output);

    FileOperation *uploadFile(const QByteArray &fileContent, const QString &fileName);
    FileOperation *uploadFile(QIODevice *source, const QString &fileName);

    ConnectOperation *ensureConnection(quint32 dcId);

    void processFileRequestForConnection(FileOperation *operation, Connection *connection);

    UploadRpcLayer *uploadLayer() { return m_uploadLayer; }

protected slots:
    void onGetFileResult(FileOperation *operation, UploadRpcLayer::PendingUploadFile *rpcOperation);

    void onOperationCanceled(PendingOperation *operation);

    void onConnectOperationFinished(ConnectOperation *operation);
    void onFileOperationFinished(PendingOperation *operation);
    void onConnectionStatusChanged();
    void processConnectionStatus(Connection *connection);

    void processNextRequest();
    void processCurrentRequest();
protected:
//    FileOperation *addFileRequest(const FileInfo *file, QIODevice *device);
    FileOperation *addFileRequest(const FileRequestDescriptor &descriptor, QIODevice *device);

    void dumpCurrentState() const;

    bool isConnectionNeeded(quint32 dcId) const;

    // QHash<quint32, Connection *> m_connections; // dcId to connection
    QQueue<FileOperation*> m_fileRequests;
    FileOperation *m_currentOperation = nullptr;
    UploadRpcLayer *m_uploadLayer = nullptr;
    QTimer *m_monitorTimer = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_FILES_API_PRIVATE_HPP
