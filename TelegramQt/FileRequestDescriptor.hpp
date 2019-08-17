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

#ifndef TELEGRAMQT_FILE_REQUEST_DESCRIPTOR_HPP
#define TELEGRAMQT_FILE_REQUEST_DESCRIPTOR_HPP

#include "MTProto/TLTypes.hpp"
#include "TelegramNamespace.hpp"

#include <QByteArray>
#include <QString>

QT_FORWARD_DECLARE_CLASS(QCryptographicHash)

namespace Telegram {

namespace Client {

class FileRequestDescriptor
{
public:
    enum Type {
        Invalid,
        Download,
        Upload
    };

    FileRequestDescriptor() = default;

    static FileRequestDescriptor downloadRequest(quint32 dcId, const TLInputFileLocation &inputLocation, quint32 size);
    static FileRequestDescriptor uploadRequest(const QByteArray &data, const QString &fileName, quint32 dcId);

    Type type() const { return m_type; }
    void setType(Type type) { m_type = type; }

    quint32 dcId() const { return m_dcId; }
    void setDcId(quint32 dc);

    bool isValid() const { return m_type != Invalid; }

    void setInputLocation(const TLInputFileLocation &inputLocation);
    TLInputFileLocation inputLocation() const { return m_inputLocation; }

    quint32 size() const { return m_size; }
    void setSize(quint32 size);

    quint32 offset() const { return m_offset; }

    void setOffset(quint32 newOffset) { m_offset = newOffset; }

    /* Upload stuff */
    TLInputFile inputFile() const;
    quint32 part() const { return m_part; }
    quint32 parts() const;
    QByteArray md5Sum() const { return m_md5Sum; }
    quint64 fileId() const { return m_fileId; }

    bool isBigFile() const;
    bool finished() const;
    void bumpPart();

    QByteArray data() const;

    quint32 chunkSize() const;
    void setChunkSize(quint32 size);

    QString uniqueId;

    static quint32 defaultDownloadPartSize();

protected:
    TLInputFileLocation m_inputLocation;
    QByteArray m_data;
    QByteArray m_md5Sum;
    QString m_fileName;
    QCryptographicHash *m_hash = nullptr;
    quint64 m_fileId = 0;
    quint32 m_size = 0;
    quint32 m_offset = 0;
    quint32 m_part = 0;
    quint32 m_chunkSize = 0;
    quint32 m_dcId = 0;
    Type m_type = Invalid;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_FILE_REQUEST_DESCRIPTOR_HPP
