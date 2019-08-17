/*
   Copyright (C) 2014-2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "FileRequestDescriptor.hpp"

#include "RandomGenerator.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#include <QCryptographicHash>
#include <QLoggingCategory>

namespace Telegram {

namespace Client {

FileRequestDescriptor FileRequestDescriptor::downloadRequest(quint32 dcId, const TLInputFileLocation &inputLocation, quint32 size)
{
    FileRequestDescriptor result;
    result.m_type = Download;
    result.m_dcId = dcId;
    result.m_inputLocation = inputLocation;
    result.m_size = size;
    return result;
}

FileRequestDescriptor FileRequestDescriptor::uploadRequest(const QByteArray &data, const QString &fileName, quint32 dcId)
{
    FileRequestDescriptor result;
    result.m_type = Upload;
    result.m_dcId = dcId;
    result.m_data = data;
    result.m_size = data.size();
    result.m_fileName = fileName;

    if (!result.isBigFile()) {
        result.m_hash = new QCryptographicHash(QCryptographicHash::Md5);
    }

    RandomGenerator::instance()->generate(&result.m_fileId);

    return result;
}

void FileRequestDescriptor::setDcId(quint32 dc)
{
    m_dcId = dc;
}

void FileRequestDescriptor::setInputLocation(const TLInputFileLocation &inputLocation)
{
    m_inputLocation = inputLocation;
}

void FileRequestDescriptor::setSize(quint32 size)
{
    m_size = size;
}

TLInputFile FileRequestDescriptor::inputFile() const
{
    TLInputFile file;

    if (isBigFile()) {
        file.tlType = TLValue::InputFileBig;
    } else {
        file.tlType = TLValue::InputFile;
//        file.md5Checksum = QString::fromLatin1(md5Sum().toHex());
    }

    file.id = m_fileId;
    file.parts = parts();
    file.name = m_fileName;

#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << file;
#endif

    return file;
}

quint32 FileRequestDescriptor::parts() const
{
    quint32 parts = m_size / chunkSize();
    if (m_size % chunkSize()) {
        ++parts;
    }

    return parts;
}

bool FileRequestDescriptor::isBigFile() const
{
    return size() > 10 * 1024 * 1024;
}

bool FileRequestDescriptor::finished() const
{
    return m_part * chunkSize() >= size();
}

void FileRequestDescriptor::bumpPart()
{
    if (m_hash) {
        m_hash->addData(data());
    }

    ++m_part;
    m_offset = m_part * chunkSize();

    if (m_offset > m_size) {
        m_offset = m_size;
    }

    if (m_hash && finished()) {
        m_md5Sum = m_hash->result();
        delete m_hash;
        m_hash = 0;
    }
}

QByteArray FileRequestDescriptor::data() const
{
    return m_data.mid(m_part * chunkSize(), chunkSize());
}

quint32 FileRequestDescriptor::chunkSize() const
{
    if (m_chunkSize) {
        return m_chunkSize;
    }

    return defaultDownloadPartSize();
}

void FileRequestDescriptor::setChunkSize(quint32 size)
{
    if (size % 1024) {
        qCritical() << "Requested chunk size is not valid";
    }
    m_chunkSize = size;
}

quint32 FileRequestDescriptor::defaultDownloadPartSize()
{
    return 1024 * 32; // Set chunkSize to some big number to get the whole avatar at once
}

} // Client namespace

} // Telegram namespace
