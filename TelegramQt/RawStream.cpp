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

#include "RawStream.hpp"
#include "AbridgedLength.hpp"

#include <QIODevice>
#include <QBuffer>

static const char s_nulls[4] = { 0, 0, 0, 0 };

namespace Telegram {

RawStream::RawStream(QByteArray *data, bool write) :
    m_ownDevice(true)
{
    setDevice(new QBuffer(data));
    if (write) {
        m_device->open(QIODevice::Append);
    } else {
        m_device->open(QIODevice::ReadOnly);
    }
}

RawStream::RawStream(const QByteArray &data)
{
    setData(data);
}

RawStream::RawStream(Mode m, quint32 reserveBytes) :
    m_ownDevice(true)
{
    Q_UNUSED(m)
    QBuffer *buffer = new QBuffer();
    if (reserveBytes) {
        buffer->buffer().reserve(static_cast<int>(reserveBytes));
    }
    setDevice(buffer);
    m_device->open(QIODevice::WriteOnly);
}

RawStream::RawStream(QIODevice *d)
{
    setDevice(d);
}

RawStream::~RawStream()
{
    if (m_device && m_ownDevice) {
        delete m_device;
    }
}

void RawStream::setData(const QByteArray &data)
{
    QBuffer *buffer = new QBuffer();
    buffer->setData(data);
    setDevice(buffer);
    m_device->open(QIODevice::ReadOnly);
    m_ownDevice = true;
}

QByteArray RawStream::getData() const
{
    if (m_ownDevice) {
        QBuffer *buffer = static_cast<QBuffer*>(m_device);
        return buffer->data();
    }
    return QByteArray();
}

void RawStream::setDevice(QIODevice *newDevice)
{
    if (m_device) {
        if (m_ownDevice) {
            delete m_device;
            m_ownDevice = false;
        }
    }

    m_device = newDevice;
}

void RawStream::unsetDevice()
{
    setDevice(nullptr);
}

bool RawStream::atEnd() const
{
    return m_device ? m_device->atEnd() : true;
}

int RawStream::bytesAvailable() const
{
    return m_device ? static_cast<int>(m_device->bytesAvailable()) : 0;
}

bool RawStream::writeBytes(const QByteArray &data)
{
    m_error = m_error || m_device->write(data) != data.size();
    return m_error;
}

bool RawStream::read(void *data, qint64 size)
{
    if (size) {
        m_error = m_error || m_device->read(static_cast<char *>(data), size) != size;
    }
    return m_error;
}

bool RawStream::write(const void *data, qint64 size)
{
    if (size) {
        m_error = m_error || m_device->write(static_cast<const char *>(data), size) != size;
    }
    return m_error;
}

void RawStream::setError(bool error)
{
    m_error = error;
}

QByteArray RawStream::readBytes(int count)
{
    QByteArray result = m_device->read(count);
    m_error = m_error || result.size() != count;
    return result;
}

RawStream &RawStream::operator>>(qint8 &i)
{
    return protectedRead(i);
}

RawStream &RawStream::operator>>(qint16 &i)
{
    return protectedRead(i);
}

RawStream &RawStream::operator>>(qint32 &i)
{
    return protectedRead(i);
}

RawStream &RawStream::operator>>(qint64 &i)
{
    return protectedRead(i);
}

template<typename Int>
RawStream &RawStream::protectedRead(Int &i)
{
    read(&i, sizeof(Int));
    return *this;
}

RawStream &RawStream::operator<<(qint8 i)
{
    return protectedWrite(i);
}

RawStream &RawStream::operator<<(qint16 i)
{
    return protectedWrite(i);
}

RawStream &RawStream::operator<<(qint32 i)
{
    return protectedWrite(i);
}

RawStream &RawStream::operator<<(qint64 i)
{
    return protectedWrite(i);
}

template<typename Int>
RawStream &RawStream::protectedWrite(Int i)
{
    write(&i, sizeof(Int));
    return *this;
}

RawStream &RawStream::operator>>(double &d)
{
    read(&d, 8);
    return *this;
}

RawStream &RawStream::operator<<(const double &d)
{
    write(&d, 8);
    return *this;
}

RawStream &RawStream::operator<<(const QByteArray &data)
{
    writeBytes(data);
    return *this;
}

RawStreamEx &RawStreamEx::operator>>(Telegram::AbridgedLength &data)
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

RawStreamEx &RawStreamEx::operator<<(const Telegram::AbridgedLength &data)
{
    if (data.packedSize() == 1) {
        quint8 l = static_cast<quint8>(data);
        *this << l;
    } else {
        *this << quint32((data << 8) + 0xfe);
    }
    return *this;
}

RawStreamEx &RawStreamEx::operator>>(QByteArray &data)
{
    Telegram::AbridgedLength length;
    *this >> length;
    data.resize(static_cast<int>(length));
    read(data.data(), data.size());
    readBytes(length.paddingForAlignment(4));
    return *this;
}

RawStreamEx &RawStreamEx::operator<<(const QByteArray &data)
{
    Telegram::AbridgedLength length(static_cast<quint32>(data.size()));
    *this << length;
    write(data.constData(), data.size());
    write(s_nulls, length.paddingForAlignment(4));
    return *this;
}

} // Telegram namespace
