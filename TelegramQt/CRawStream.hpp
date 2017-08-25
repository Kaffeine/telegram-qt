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

#ifndef CRAWSTREAM_HPP
#define CRAWSTREAM_HPP

#include <qglobal.h>

#include <QByteArray>

#include "TLNumbers.hpp"
#include "TLValues.hpp"

QT_BEGIN_NAMESPACE
class QIODevice;
QT_END_NAMESPACE

class CRawStream
{
public:
    explicit CRawStream(QByteArray *data, bool write);
    explicit CRawStream(const QByteArray &data);

    explicit CRawStream(QIODevice *d = 0);

    virtual ~CRawStream();

    QIODevice *device() const { return m_device; }
    void setDevice(QIODevice *newDevice);
    void unsetDevice();

    bool error() const { return m_error; }
    void resetError();

    bool atEnd() const;
    int bytesRemaining() const;

    QByteArray readBytes(int count);

    QByteArray readRemainingBytes();

    CRawStream &operator>>(qint8 &i);
    CRawStream &operator>>(qint16 &i);
    CRawStream &operator>>(qint32 &i);
    CRawStream &operator>>(qint64 &i);
    CRawStream &operator>>(quint8 &i);
    CRawStream &operator>>(quint16 &i);
    CRawStream &operator>>(quint32 &i);
    CRawStream &operator>>(quint64 &i);

    CRawStream &operator>>(double &d);

    template <int Size>
    CRawStream &operator>>(TLNumber<Size> &n);

    CRawStream &operator>>(TLValue &v);

    CRawStream &operator<<(qint8 i);
    CRawStream &operator<<(qint16 i);
    CRawStream &operator<<(qint32 i);
    CRawStream &operator<<(qint64 i);
    CRawStream &operator<<(quint8 i);
    CRawStream &operator<<(quint16 i);
    CRawStream &operator<<(quint32 i);
    CRawStream &operator<<(quint64 i);

    CRawStream &operator<<(const double &d);

    template <int Size>
    CRawStream &operator<<(const TLNumber<Size> &n);

    CRawStream &operator<<(TLValue v);

    CRawStream &operator<<(const QByteArray &data);

protected:
    bool read(void *data, qint64 size);
    bool write(const void *data, qint64 size);

    template<typename Int>
    inline CRawStream &protectedWrite(Int i);

    template<typename Int>
    inline CRawStream &protectedRead(Int &i);

private:
    QIODevice *m_device;
    bool m_ownDevice;
    bool m_error;

};

class CRawStreamEx : public CRawStream
{
public:
    explicit CRawStreamEx(QByteArray *data, bool write) :
        CRawStream(data, write)
    {
    }
    explicit CRawStreamEx(const QByteArray &data) :
        CRawStream(data)
    {
    }

    explicit CRawStreamEx(QIODevice *d = 0) :
        CRawStream(d)
    {
    }

    using CRawStream::operator <<;
    using CRawStream::operator >>;

    CRawStreamEx &operator>>(QByteArray &data);
    CRawStreamEx &operator<<(const QByteArray &data);

};

inline void CRawStream::resetError()
{
    m_error = false;
}

inline QByteArray CRawStream::readRemainingBytes()
{
    return readBytes(bytesRemaining());
}

inline CRawStream &CRawStream::operator>>(quint8 &i)
{
    return *this >> reinterpret_cast<qint8&>(i);
}

inline CRawStream &CRawStream::operator>>(quint16 &i)
{
    return *this >> reinterpret_cast<qint16&>(i);
}

inline CRawStream &CRawStream::operator>>(quint32 &i)
{
    return *this >> reinterpret_cast<qint32&>(i);
}

inline CRawStream &CRawStream::operator>>(quint64 &i)
{
    return *this >> reinterpret_cast<qint64&>(i);
}

template <int Size>
CRawStream &CRawStream::operator>>(TLNumber<Size> &n)
{
    read(n.data, Size / 8);
    return *this;
}

inline CRawStream &CRawStream::operator>>(TLValue &v)
{
    quint32 i;
    *this >> i;
    v = TLValue(i);
    return *this;
}

inline CRawStream &CRawStream::operator<<(quint8 i)
{
    return *this << qint8(i);
}

inline CRawStream &CRawStream::operator<<(quint16 i)
{
    return *this << qint16(i);
}

inline CRawStream &CRawStream::operator<<(quint32 i)
{
    return *this << qint32(i);
}

inline CRawStream &CRawStream::operator<<(quint64 i)
{
    return *this << qint64(i);
}

template <int Size>
CRawStream &CRawStream::operator<<(const TLNumber<Size> &n)
{
    write(n.data, Size / 8);
    return *this;
}

inline CRawStream &CRawStream::operator<<(TLValue v)
{
    return *this << quint32(v);
}

#endif // CRAWSTREAM_HPP
