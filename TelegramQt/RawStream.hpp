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

#ifndef TELEGRAM_QT_RAW_STREAM_HPP
#define TELEGRAM_QT_RAW_STREAM_HPP

#include "telegramqt_global.h"

#include <QByteArray>

QT_FORWARD_DECLARE_CLASS(QIODevice)

namespace Telegram {

class AbridgedLength;

class TELEGRAMQT_INTERNAL_EXPORT RawStream
{
public:
    enum Mode {
        WriteOnly
    };
    explicit RawStream(QByteArray *data, bool write);
    explicit RawStream(const QByteArray &data);
    explicit RawStream(Mode mode, quint32 reserveBytes = 0);
    explicit RawStream(QIODevice *d = nullptr);

    virtual ~RawStream();

    QByteArray getData() const;
    void setData(const QByteArray &data);
    QIODevice *device() const { return m_device; }
    void setDevice(QIODevice *newDevice);
    void unsetDevice();

    bool error() const { return m_error; }
    void resetError();

    bool atEnd() const;
    int bytesAvailable() const;

    bool writeBytes(const QByteArray &bytes);
    QByteArray readBytes(int count);

    QByteArray readAll();

    RawStream &operator>>(qint8 &i);
    RawStream &operator>>(qint16 &i);
    RawStream &operator>>(qint32 &i);
    RawStream &operator>>(qint64 &i);
    RawStream &operator>>(quint8 &i);
    RawStream &operator>>(quint16 &i);
    RawStream &operator>>(quint32 &i);
    RawStream &operator>>(quint64 &i);

    RawStream &operator>>(double &d);

    RawStream &operator<<(qint8 i);
    RawStream &operator<<(qint16 i);
    RawStream &operator<<(qint32 i);
    RawStream &operator<<(qint64 i);
    RawStream &operator<<(quint8 i);
    RawStream &operator<<(quint16 i);
    RawStream &operator<<(quint32 i);
    RawStream &operator<<(quint64 i);

    RawStream &operator<<(const double &d);

    RawStream &operator<<(const QByteArray &data);

protected:
    bool read(void *data, qint64 size);
    bool write(const void *data, qint64 size);

    template<typename Int>
    inline RawStream &protectedWrite(Int i);

    template<typename Int>
    inline RawStream &protectedRead(Int &i);

    void setError(bool error);

private:
    QIODevice *m_device = nullptr;
    bool m_ownDevice = false;
    bool m_error = false;

};

class TELEGRAMQT_INTERNAL_EXPORT RawStreamEx : public RawStream
{
public:
    using RawStream::RawStream;
    using RawStream::operator <<;
    using RawStream::operator >>;

    RawStreamEx &operator>>(QByteArray &data);
    RawStreamEx &operator<<(const QByteArray &data);

    RawStreamEx &operator>>(Telegram::AbridgedLength &data);
    RawStreamEx &operator<<(const Telegram::AbridgedLength &data);
};

inline void RawStream::resetError()
{
    m_error = false;
}

inline QByteArray RawStream::readAll()
{
    return readBytes(bytesAvailable());
}

inline RawStream &RawStream::operator>>(quint8 &i)
{
    return *this >> reinterpret_cast<qint8&>(i);
}

inline RawStream &RawStream::operator>>(quint16 &i)
{
    return *this >> reinterpret_cast<qint16&>(i);
}

inline RawStream &RawStream::operator>>(quint32 &i)
{
    return *this >> reinterpret_cast<qint32&>(i);
}

inline RawStream &RawStream::operator>>(quint64 &i)
{
    return *this >> reinterpret_cast<qint64&>(i);
}

inline RawStream &RawStream::operator<<(quint8 i)
{
    return *this << qint8(i);
}

inline RawStream &RawStream::operator<<(quint16 i)
{
    return *this << qint16(i);
}

inline RawStream &RawStream::operator<<(quint32 i)
{
    return *this << qint32(i);
}

inline RawStream &RawStream::operator<<(quint64 i)
{
    return *this << qint64(i);
}

} // Telegram namespace

#endif // TELEGRAM_QT_RAW_STREAM_HPP
