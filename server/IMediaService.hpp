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

#ifndef TELEGRAM_QT_SERVER_IMEDIA_SERVICE_HPP
#define TELEGRAM_QT_SERVER_IMEDIA_SERVICE_HPP

#include "ServerNamespace.hpp"

QT_FORWARD_DECLARE_CLASS(QIODevice)

namespace Telegram {

namespace Server {

class IMediaService
{
public:
    virtual bool uploadFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes) = 0;
    virtual UploadDescriptor getUploadedData(quint64 fileId) const = 0;
    virtual void freeUploadedData(qint64 fileId) = 0;

    virtual FileDescriptor getSecretFileDescriptor(quint64 volumeId,
                                                   quint32 localId,
                                                   quint64 secret) const = 0;
    virtual FileDescriptor getDocumentFileDescriptor(quint64 fileId,
                                                     quint64 accessHash) const = 0;

    virtual QIODevice *beginReadFile(const FileDescriptor &descriptor) = 0;
    virtual void endReadFile(QIODevice *device) = 0;

    // TODO: Make processImageFile() async and return a PendingOperation?
    virtual ImageDescriptor processImageFile(const UploadDescriptor &upload,
                                             const QString &name = QString()) = 0;
    virtual FileDescriptor saveDocumentFile(const UploadDescriptor &upload,
                                            const QString &fileName,
                                            const QString &mimeType) = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_IMEDIA_SERVICE_HPP
