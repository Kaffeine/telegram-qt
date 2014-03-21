#ifndef CTELEGRAMSTREAM_HPP
#define CTELEGRAMSTREAM_HPP

#include <qglobal.h>

#include "TLValues.h"

QT_BEGIN_NAMESPACE
class QByteArray;
class QIODevice;
QT_END_NAMESPACE

class CTelegramStream
{
public:
    explicit CTelegramStream(QIODevice *d = 0);

    inline QIODevice *device() const { return m_device; }
    void setDevice(QIODevice *newDevice);
    void unsetDevice();

    bool atEnd() const;

    CTelegramStream &operator>>(qint32 &i);
    CTelegramStream &operator>>(quint32 &i);
    CTelegramStream &operator>>(qint64 &i);
    CTelegramStream &operator>>(quint64 &i);

    CTelegramStream &operator>>(TLValues &v);

    CTelegramStream &operator<<(qint32 i);
    CTelegramStream &operator<<(quint32 i);
    CTelegramStream &operator<<(qint64 i);
    CTelegramStream &operator<<(quint64 i);

    CTelegramStream &operator<<(TLValues v);

    CTelegramStream &operator<<(const QString &str);

private:
    QIODevice *m_device;
};

inline CTelegramStream &CTelegramStream::operator>>(quint32 &i)
{
    return *this >> reinterpret_cast<qint32&>(i);
}

inline CTelegramStream &CTelegramStream::operator>>(quint64 &i)
{
    return *this >> reinterpret_cast<qint64&>(i);
}

inline CTelegramStream &CTelegramStream::operator>>(TLValues &v)
{
    quint32 i;
    *this >> i;
    v = TLValues(i);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(quint32 i)
{
    return *this << qint32(i);
}

inline CTelegramStream &CTelegramStream::operator<<(quint64 i)
{
    return *this << qint64(i);
}

inline CTelegramStream &CTelegramStream::operator<<(TLValues v)
{
    return *this << quint32(v);
}

#endif // CTELEGRAMSTREAM_HPP
