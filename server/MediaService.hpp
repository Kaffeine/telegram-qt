/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_QT_SERVER_MEDIA_SERVICE_HPP
#define TELEGRAM_QT_SERVER_MEDIA_SERVICE_HPP

#include "ServerNamespace.hpp"

#include <QHash>
#include <QObject>
#include <QSet>

QT_FORWARD_DECLARE_CLASS(QFile)
QT_FORWARD_DECLARE_CLASS(QIODevice)

namespace Telegram {

namespace Server {

class MediaService : public QObject
{
    Q_OBJECT
public:
    explicit MediaService(QObject *parent = nullptr);

    bool uploadFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes);
    FileDescriptor getFileDescriptor(quint64 fileId, quint32 parts) const;

    FileDescriptor getSecretFileDescriptor(quint64 volumeId, quint32 localId, quint64 secret) const;
    FileDescriptor getDocumentFileDescriptor(quint64 fileId, quint64 accessHash) const;

    QIODevice *beginReadFile(const FileDescriptor &descriptor);
    void endReadFile(QIODevice *device);

    // TODO: Make processImageFile() async and return a PendingOperation?
    ImageDescriptor processImageFile(const FileDescriptor &file, const QString &name = QString());
    FileDescriptor saveDocumentFile(const FileDescriptor &descriptor,
                                    const QString &fileName,
                                    const QString &mimeType);

protected:
    QIODevice *beginWriteFile();
    FileDescriptor *endWriteFile(QIODevice *device, const QString &name);

    quint64 volumeId() const;

    QVector<FileDescriptor> m_allFileDescriptors;
    QHash<quint64, FileData> m_tmpFiles;
    QSet<QFile*> m_openFiles;
    quint64 m_lastGlobalId = 0;
    quint64 m_lastTimestamp = 0;
    quint32 m_lastFileLocalId = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_MEDIA_SERVICE_HPP
