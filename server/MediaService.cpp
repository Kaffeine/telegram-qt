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

#include "MediaService.hpp"

#include "ApiUtils.hpp"
#include "Debug_p.hpp"
#include "RandomGenerator.hpp"

#include <QDir>
#include <QImage>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcMediaService, "telegram.server.media", QtWarningMsg)

static const QString c_storageFileDir = QLatin1String("storage%1/volume%2");

namespace Telegram {

namespace Server {

const QVector<int> ImageSizeDescriptor::Sizes = {
    ImageSizeDescriptor::Small,
    ImageSizeDescriptor::Medium,
    ImageSizeDescriptor::Large,
    ImageSizeDescriptor::Max
};

MediaService::MediaService(QObject *parent) :
    QObject(parent)
{
    RandomGenerator::instance()->generate(&m_lastFileLocalId);
}

quint32 MediaService::dcId() const
{
    return m_dcId;
}

void MediaService::setDcId(quint32 dcId)
{
    m_dcId = dcId;
    setObjectName(QStringLiteral("MediaService(dc%1)").arg(dcId));
}

bool MediaService::uploadFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes)
{
    if (!m_tmpFiles.contains(fileId)) {
        UploadDescriptor newFile;
        newFile.fileId = fileId;
        m_tmpFiles.insert(fileId, newFile);
    }
    UploadDescriptor &data = m_tmpFiles[fileId];
    if (filePart != static_cast<quint32>(data.partList.count())) {
        return false;
    }
    data.partList.append(bytes);
    return true;
}

UploadDescriptor MediaService::getUploadedData(quint64 fileId) const
{
    return m_tmpFiles.value(fileId);
}

void MediaService::freeUploadedData(qint64 fileId)
{
    m_tmpFiles.remove(fileId);
}

FileDescriptor MediaService::getSecretFileDescriptor(quint64 volumeId,
                                                quint32 localId,
                                                quint64 secret) const
{
    for (const FileDescriptor &descriptor : m_allFileDescriptors) {
        if ((descriptor.volumeId == volumeId) && (descriptor.localId == localId)) {
            if (descriptor.secret == secret) {
                return descriptor;
            }
            break;
        }
    }
    return FileDescriptor();
}

FileDescriptor MediaService::getDocumentFileDescriptor(quint64 fileId, quint64 accessHash) const
{
    for (const FileDescriptor &descriptor : m_allFileDescriptors) {
        if (descriptor.id == fileId) {
            if (descriptor.accessHash == accessHash) {
                return descriptor;
            }
            break;
        }
    }
    return FileDescriptor();
}

QIODevice *MediaService::beginReadFile(const FileDescriptor &descriptor)
{
    QFile *file = new QFile();
    m_openFiles.insert(file);
    file->setFileName(getFileName(descriptor.volumeId, descriptor.localId));
    qCDebug(lcMediaService) << CALL_INFO << file->fileName();
    if (!file->open(QIODevice::ReadOnly)) {
        qCWarning(lcMediaService) << CALL_INFO << "Unable to open file!";
        return nullptr;
    }
    return file;
}

void MediaService::endReadFile(QIODevice *device)
{
    QFile *file = static_cast<QFile *>(device);
    if (!m_openFiles.contains(file)) {
        qCWarning(lcMediaService) << CALL_INFO << "not such file" << device;
        return;
    }

    m_openFiles.remove(file);
    delete file;
}

QIODevice *MediaService::beginWriteFile()
{
    QDir().mkpath(getVolumeDirName(volumeId()));

    QFile *file = new QFile();
    m_openFiles.insert(file);
    file->setFileName(getFileName(volumeId(), ++m_lastFileLocalId));
    qCDebug(lcMediaService) << CALL_INFO << file->fileName();
    if (!file->open(QIODevice::WriteOnly)) {
        qCWarning(lcMediaService) << CALL_INFO << "Unable to open file!";
    }
    return file;
}

FileDescriptor *MediaService::endWriteFile(QIODevice *device, const QString &name)
{
    QFile *file = static_cast<QFile *>(device);
    if (!m_openFiles.contains(file)) {
        qCWarning(lcMediaService) << CALL_INFO << "not such file" << device;
        return nullptr;
    }

    FileDescriptor result;
    RandomGenerator::instance()->generate(&result.id);
    result.dcId = dcId();
    result.volumeId = volumeId();
    result.localId = m_lastFileLocalId;
    RandomGenerator::instance()->generate(&result.secret);
    result.date = Telegram::Utils::getCurrentTime();
    result.name = name;

    m_openFiles.remove(file);
    file->close();
    result.size = static_cast<quint32>(file->size());
    delete file;

    m_allFileDescriptors.append(result);

    return &m_allFileDescriptors.last();
}

QString MediaService::getVolumeDirName(quint64 volumeId) const
{
    return c_storageFileDir.arg(dcId()).arg(volumeId);
}

QString MediaService::getFileName(quint64 volumeId, quint32 localId) const
{
    return getVolumeDirName(volumeId) + QLatin1Char('/') + QString::number(localId);
}

FileDescriptor MediaService::saveDocumentFile(const UploadDescriptor &upload,
                                         const QString &fileName,
                                         const QString &mimeType)
{
    QIODevice *output = beginWriteFile();
    QByteArray data = upload.partList.join();
    output->write(data);
    FileDescriptor *savedFile = endWriteFile(output, fileName);
    if (!savedFile) {
        return FileDescriptor();
    }
    savedFile->mimeType = mimeType;
    RandomGenerator::instance()->generate(&savedFile->accessHash);

    freeUploadedData(upload.fileId);

    return *savedFile;
}

ImageDescriptor MediaService::processImageFile(const UploadDescriptor &upload, const QString &name)
{
    if (!upload.fileId) {
        return ImageDescriptor();
    }

    QByteArray data = upload.partList.join();
    QImage originalImage = QImage::fromData(data);

    if (originalImage.isNull()) {
        return ImageDescriptor();
    }

    ImageDescriptor result;
    result.date = Telegram::Utils::getCurrentTime();
    result.id = upload.fileId;
    result.accessHash = 0xdead;
    result.flags = 0;

    for (const int maxDimension : ImageSizeDescriptor::Sizes) {
        const int imageMaxDimension = qMax(originalImage.width(), originalImage.height());
        QImage sizedImage = originalImage;
        if (imageMaxDimension > maxDimension) {
            sizedImage = originalImage.scaled(maxDimension, maxDimension, Qt::KeepAspectRatio);
        }
        QIODevice *output = beginWriteFile();
        if (!sizedImage.save(output, "PNG")) {
            qCWarning(lcMediaService) << Q_FUNC_INFO << "Unable to save image size" << maxDimension;
        }
        const FileDescriptor *fileDescriptor = endWriteFile(output, name);

        ImageSizeDescriptor sizeDescriptor;
        sizeDescriptor.w = static_cast<quint32>(sizedImage.width());
        sizeDescriptor.h = static_cast<quint32>(sizedImage.height());
        sizeDescriptor.size = fileDescriptor->size;
        sizeDescriptor.fileDescriptor = *fileDescriptor;
        sizeDescriptor.sizeType = maxDimension;

        result.sizes.append(sizeDescriptor);

        if (imageMaxDimension <= maxDimension) {
            break;
        }
    }

    freeUploadedData(upload.fileId);

    return result;
}

quint64 MediaService::volumeId() const
{
    return 1;
}

} // Server namespace

} // Telegram namespace
