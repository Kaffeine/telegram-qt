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

#include "CRawStream.hpp"
#include "AbridgedLength.hpp"

#include <QIODevice>
#include <QBuffer>

static const char s_nulls[4] = { 0, 0, 0, 0 };

CRawStream::CRawStream(QByteArray *data, bool write) :
    m_device(new QBuffer(data)),
    m_ownDevice(true)
{
    if (write) {
        m_device->open(QIODevice::Append);
    } else {
        m_device->open(QIODevice::ReadOnly);
    }
}

CRawStream::CRawStream(const QByteArray &data)
{
    setData(data);
}

CRawStream::CRawStream(CRawStream::Mode m, quint32 reserveBytes) :
    m_ownDevice(true)
{
    Q_UNUSED(m)
    QBuffer *buffer = new QBuffer();
    if (reserveBytes) {
        buffer->buffer().reserve(static_cast<int>(reserveBytes));
    }
    m_device = buffer;
    m_device->open(QIODevice::WriteOnly);
}

CRawStream::CRawStream(QIODevice *d) :
    m_device(d)
{
}

CRawStream::~CRawStream()
{
    if (m_device && m_ownDevice) {
        delete m_device;
    }
}

void CRawStream::setData(const QByteArray &data)
{
    QBuffer *buffer = new QBuffer();
    buffer->setData(data);
    setDevice(buffer);
    m_device->open(QIODevice::ReadOnly);
    m_ownDevice = true;
}

QByteArray CRawStream::getData() const
{
    if (m_ownDevice) {
        QBuffer *buffer = static_cast<QBuffer*>(m_device);
        return buffer->data();
    }
    return QByteArray();
}

void CRawStream::setDevice(QIODevice *newDevice)
{
    if (m_device) {
        if (m_ownDevice) {
            delete m_device;
            m_ownDevice = false;
        }
    }

    m_device = newDevice;
}

void CRawStream::unsetDevice()
{
    setDevice(nullptr);
}

bool CRawStream::atEnd() const
{
    return m_device ? m_device->atEnd() : true;
}

int CRawStream::bytesAvailable() const
{
    return m_device ? static_cast<int>(m_device->bytesAvailable()) : 0;
}

bool CRawStream::writeBytes(const QByteArray &data)
{
    m_error = m_error || m_device->write(data) != data.size();
    return m_error;
}

bool CRawStream::read(void *data, qint64 size)
{
    if (size) {
        m_error = m_error || m_device->read(static_cast<char *>(data), size) != size;
    }
    return m_error;
}

bool CRawStream::write(const void *data, qint64 size)
{
    if (size) {
        m_error = m_error || m_device->write(static_cast<const char *>(data), size) != size;
    }
    return m_error;
}

void CRawStream::setError(bool error)
{
    m_error = error;
}

QByteArray CRawStream::readBytes(int count)
{
    QByteArray result = m_device->read(count);
    m_error = m_error || result.size() != count;
    return result;
}

CRawStream &CRawStream::operator>>(qint8 &i)
{
    return protectedRead(i);
}

CRawStream &CRawStream::operator>>(qint16 &i)
{
    return protectedRead(i);
}

CRawStream &CRawStream::operator>>(qint32 &i)
{
    return protectedRead(i);
}

CRawStream &CRawStream::operator>>(qint64 &i)
{
    return protectedRead(i);
}

template<typename Int>
CRawStream &CRawStream::protectedRead(Int &i)
{
    read(&i, sizeof(Int));
    return *this;
}

CRawStream &CRawStream::operator<<(qint8 i)
{
    return protectedWrite(i);
}

CRawStream &CRawStream::operator<<(qint16 i)
{
    return protectedWrite(i);
}

CRawStream &CRawStream::operator<<(qint32 i)
{
    return protectedWrite(i);
}

CRawStream &CRawStream::operator<<(qint64 i)
{
    return protectedWrite(i);
}

template<typename Int>
CRawStream &CRawStream::protectedWrite(Int i)
{
    write(&i, sizeof(Int));
    return *this;
}

CRawStream &CRawStream::operator>>(double &d)
{
    read(&d, 8);
    return *this;
}

CRawStream &CRawStream::operator<<(const double &d)
{
    write(&d, 8);
    return *this;
}

CRawStream &CRawStream::operator<<(const QByteArray &data)
{
    writeBytes(data);
    return *this;
}

CRawStreamEx &CRawStreamEx::operator>>(Telegram::AbridgedLength &data)
{
    quint32 length = 0;
    read(&length, 1);
    if (Q_UNLIKELY(length == 0xfe)) {
        read(&length, 3);
    } else if (Q_UNLIKELY(length > 0xfe)) {
        setError(true);
    }
    data = length;
    return *this;
}

CRawStreamEx &CRawStreamEx::operator<<(const Telegram::AbridgedLength &data)
{
    if (data.packedSize() == 1) {
        quint8 l = static_cast<quint8>(data);
        *this << l;
    } else {
        *this << quint32((data << 8) + 0xfe);
    }
    return *this;
}

CRawStreamEx &CRawStreamEx::operator>>(QByteArray &data)
{
    Telegram::AbridgedLength length;
    *this >> length;
    data.resize(static_cast<int>(length));
    read(data.data(), data.size());
    readBytes(length.paddingForAlignment(4));
    return *this;
}

CRawStreamEx &CRawStreamEx::operator<<(const QByteArray &data)
{
    Telegram::AbridgedLength length(static_cast<quint32>(data.size()));
    *this << length;
    write(data.constData(), data.size());
    write(s_nulls, length.paddingForAlignment(4));
    return *this;
}
