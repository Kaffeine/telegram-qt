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

#include <QIODevice>
#include <QBuffer>

static const char s_nulls[4] = { 0, 0, 0, 0 };

template CRawStream &CRawStream::operator>>(TLNumber128 &v);
template CRawStream &CRawStream::operator>>(TLNumber256 &v);

template CRawStream &CRawStream::operator<<(const TLNumber128 &v);
template CRawStream &CRawStream::operator<<(const TLNumber256 &v);

CRawStream::CRawStream(QByteArray *data, bool write) :
    m_device(new QBuffer(data)),
    m_ownDevice(true),
    m_error(false)
{
    if (write) {
        m_device->open(QIODevice::Append);
    } else {
        m_device->open(QIODevice::ReadOnly);
    }
}

CRawStream::CRawStream(const QByteArray &data) :
    m_device(0),
    m_ownDevice(true),
    m_error(false)
{
    QBuffer *buffer = new QBuffer();
    buffer->setData(data);
    m_device = buffer;

    m_device->open(QIODevice::ReadOnly);
}

CRawStream::CRawStream(QIODevice *d) :
    m_device(d),
    m_ownDevice(false),
    m_error(false)
{
}

CRawStream::~CRawStream()
{
    if (m_device && m_ownDevice) {
        delete m_device;
    }
}

void CRawStream::setDevice(QIODevice *newDevice)
{
    if (m_device) {
        if (m_ownDevice) {
            delete m_device;
        }
    }

    m_device = newDevice;
}

void CRawStream::unsetDevice()
{
    setDevice(0);
}

bool CRawStream::atEnd() const
{
    return m_device ? m_device->atEnd() : true;
}

int CRawStream::bytesRemaining() const
{
    return m_device->bytesAvailable();
}

bool CRawStream::read(void *data, qint64 size)
{
    m_error = m_error || m_device->read((char *) data, size) != size;
    return m_error;
}

bool CRawStream::write(const void *data, qint64 size)
{
    m_error = m_error || m_device->write((const char *) data, size) != size;
    return m_error;
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
    m_error = m_error || m_device->write(data) != data.size();

    return *this;
}

CRawStreamEx &CRawStreamEx::operator>>(QByteArray &data)
{
    quint32 length = 0;
    read(&length, 1);

    if (length < 0xfe) {
        data.resize(length);
        length += 1; // Plus one byte before data
    } else {
        read(&length, 3);
        data.resize(length);
        length += 4; // Plus four bytes before data
    }

    read(data.data(), data.size());

    if (length & 3) {
        readBytes(4 - (length & 3));
    }

    return *this;
}

CRawStreamEx &CRawStreamEx::operator<<(const QByteArray &data)
{
    quint32 length = data.size();

    if (length < 0xfe) {
        const char lengthToWrite = length;
        write(&lengthToWrite, 1);
        write(data.constData(), data.size());
        length += 1;
    } else {
        *this << quint32((length << 8) + 0xfe);
        write(data.constData(), data.size());
        length += 4;
    }

    if (length & 3) {
        write(s_nulls, 4 - (length & 3));
    }

    return *this;
}
