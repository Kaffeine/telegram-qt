/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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

    inline QIODevice *device() const { return m_device; }
    void setDevice(QIODevice *newDevice);
    void unsetDevice();

    bool error() const { return m_error; }
    void resetError();

    bool atEnd() const;
    int bytesRemaining() const;

    QByteArray readBytes(int count);

    QByteArray readRemainingBytes();

    CRawStream &operator>>(qint32 &i);
    CRawStream &operator>>(quint32 &i);
    CRawStream &operator>>(qint64 &i);
    CRawStream &operator>>(quint64 &i);

    CRawStream &operator>>(double &d);

    template <int Size>
    CRawStream &operator>>(TLNumbers<Size> &n);

    CRawStream &operator>>(TLValue &v);

    CRawStream &operator<<(qint32 i);
    CRawStream &operator<<(quint32 i);
    CRawStream &operator<<(qint64 i);
    CRawStream &operator<<(quint64 i);

    CRawStream &operator<<(const double &d);

    template <int Size>
    CRawStream &operator<<(const TLNumbers<Size> &n);

    CRawStream &operator<<(TLValue v);

    CRawStream &operator<<(const QByteArray &data);

protected:
    bool read(void *data, qint64 size);
    bool write(const void *data, qint64 size);

private:
    QIODevice *m_device;
    bool m_ownDevice;
    bool m_error;

};

inline void CRawStream::resetError()
{
    m_error = false;
}

inline QByteArray CRawStream::readRemainingBytes()
{
    return readBytes(bytesRemaining());
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
CRawStream &CRawStream::operator>>(TLNumbers<Size> &n)
{
    for (int i = 0; i < Size / /* Size of byte */ 8 / /* Size of quint64 (one of parts) */ 8; ++i) {
        *this >> n.parts[i];
    }
    return *this;
}

inline CRawStream &CRawStream::operator>>(TLValue &v)
{
    quint32 i;
    *this >> i;
    v = TLValue(i);
    return *this;
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
CRawStream &CRawStream::operator<<(const TLNumbers<Size> &n)
{
    for (int i = 0; i < Size / 8 / 8; ++i) {
        *this << n.parts[i];
    }
    return *this;
}

inline CRawStream &CRawStream::operator<<(TLValue v)
{
    return *this << quint32(v);
}

#endif // CRAWSTREAM_HPP
