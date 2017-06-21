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

#ifndef FILEREQUESTDESCRIPTOR_HPP
#define FILEREQUESTDESCRIPTOR_HPP

#include <QByteArray>

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

QT_FORWARD_DECLARE_CLASS(QCryptographicHash)

class FileRequestDescriptor
{
public:
    enum Type {
        Invalid,
        Download,
        Upload
    };

    FileRequestDescriptor();

    static FileRequestDescriptor uploadRequest(const QByteArray &data, const QString &fileName, quint32 dc);

    Type type() const { return m_type; }
    void setType(Type type) { m_type = type; }

    quint32 dcId() const { return m_dcId; }
    void setDcId(quint32 dc);

    bool isValid() const { return m_type != Invalid; }

    void setInputLocation(const TLInputFileLocation &inputLocation);
    TLInputFileLocation inputLocation() const { return m_inputLocation; }

    void setPeer(const Telegram::Peer peer);
    Telegram::Peer peer() const { return m_peer; }

    quint32 messageId() const { return m_messageId; }
    void setMessageId(quint32 messageId);

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
    Type m_type;
    Telegram::Peer m_peer;
    quint32 m_messageId;
    quint32 m_size;
    quint32 m_offset;
    quint32 m_part;
    quint32 m_chunkSize;
    QByteArray m_data;
    QByteArray m_md5Sum;
    QString m_fileName;
    quint64 m_fileId;
    QCryptographicHash *m_hash;

    TLInputFileLocation m_inputLocation;
    quint32 m_dcId;

};

#endif // FILEREQUESTDESCRIPTOR_HPP
