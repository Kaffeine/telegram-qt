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

#include "Storage.hpp"

#include "ApiUtils.hpp"
#include "Debug_p.hpp"
#include "RandomGenerator.hpp"

#include <QDateTime>
#include <QDir>
#include <QLoggingCategory>

static const QString c_storageFileDir = QLatin1String("storage/volume%1");

namespace Telegram {

namespace Server {

Storage::Storage(QObject *parent) :
    QObject(parent)
{
}

MessageData *Storage::addMessage(quint32 fromId, Peer toPeer, const QString &text)
{
    ++m_lastGlobalId;
    m_messages.insert(m_lastGlobalId, MessageData(fromId, toPeer, text));
    MessageData *message = &m_messages[m_lastGlobalId];
    message->setDate64(getMessageUniqueTs());
    message->setGlobalId(m_lastGlobalId);
    return message;
}

const MessageData *Storage::getMessage(quint64 globalId)
{
    if (!m_messages.contains(globalId)) {
        return nullptr;
    }
    return &m_messages[globalId];
}

bool Storage::uploadFilePart(quint64 fileId, quint32 filePart, const QByteArray &bytes)
{
    if (!m_tmpFiles.contains(fileId)) {
        FileData newFile;
        newFile.fileId = fileId;
        m_tmpFiles.insert(fileId, newFile);
    }
    FileData &data = m_tmpFiles[fileId];
    if (filePart != static_cast<quint32>(data.partList.count())) {
        return false;
    }
    data.partList.append(bytes);
    return true;
}

quint64 Storage::getMessageUniqueTs()
{
    quint64 ts = Telegram::Utils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch());
    if (ts <= m_lastTimestamp) {
        ts = m_lastTimestamp + 1;
    }
    m_lastTimestamp = ts;
    return ts;
}

QIODevice *Storage::beginReadFile(const FileDescriptor &descriptor)
{
    QFile *file = new QFile();
    m_openFiles.insert(file);
    file->setFileName(c_storageFileDir.arg(descriptor.volumeId)
                      + QLatin1Char('/') + QString::number(descriptor.localId));
    qWarning() << CALL_INFO << file->fileName();
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning() << CALL_INFO << "Unable to open file!";
        return nullptr;
    }
    return file;
}

void Storage::endReadFile(QIODevice *device)
{
    QFile *file = static_cast<QFile *>(device);
    if (!m_openFiles.contains(file)) {
        qWarning() << CALL_INFO << "not such file" << device;
        return;
    }

    m_openFiles.remove(file);
    delete file;
}

QIODevice *Storage::beginWriteFile()
{
    QDir().mkpath(c_storageFileDir.arg(volumeId()));

    QFile *file = new QFile();
    m_openFiles.insert(file);
    file->setFileName(c_storageFileDir.arg(volumeId()) + QLatin1Char('/') + QString::number(++m_lastFileLocalId));
    qWarning() << CALL_INFO << file->fileName();
    if (!file->open(QIODevice::WriteOnly)) {
        qWarning() << CALL_INFO << "Unable to open file!";
    }
    return file;
}

FileDescriptor *Storage::endWriteFile(QIODevice *device, const QString &name)
{
    QFile *file = static_cast<QFile *>(device);
    if (!m_openFiles.contains(file)) {
        qWarning() << CALL_INFO << "not such file" << device;
        return nullptr;
    }

    FileDescriptor result;
    RandomGenerator::instance()->generate(&result.id);
    result.dcId = 1;
    result.volumeId = volumeId();
    result.localId = m_lastFileLocalId;
    result.secret = 0xbeef;
    result.date = Telegram::Utils::getCurrentTime();
    result.name = name;

    m_openFiles.remove(file);
    file->close();
    result.size = static_cast<quint32>(file->size());
    delete file;

    m_allFileDescriptors.append(result);

    return &m_allFileDescriptors.last();
}

quint64 Storage::volumeId() const
{
    return 1;
}

} // Server namespace

} // Telegram namespace
