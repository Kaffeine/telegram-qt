/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CTELEGRAMSTREAM_HPP
#define CTELEGRAMSTREAM_HPP

#include <QVector>
#include <QString>

#include "CRawStream.hpp"

class CTelegramStream : public CRawStream
{
public:
    explicit CTelegramStream(QByteArray *data, bool write);
    explicit CTelegramStream(const QByteArray &data);

    explicit CTelegramStream(QIODevice *d = 0);

    using CRawStream::operator <<;
    using CRawStream::operator >>;

    CTelegramStream &operator>>(QByteArray &data);
    CTelegramStream &operator>>(QString &str);

    CTelegramStream &operator>>(bool &data);

    template <typename T>
    CTelegramStream &operator>>(QVector<T> &v);

    CTelegramStream &operator<<(const QByteArray &data);
    CTelegramStream &operator<<(const QString &str);

    CTelegramStream &operator<<(const bool &data);

    template <typename T>
    CTelegramStream &operator<<(const QVector<T> &v);

    CTelegramStream &operator>>(TLDcOption &option);

};

inline CTelegramStream &CTelegramStream::operator>>(QString &str)
{
    QByteArray data;
    *this >> data;
    str = QString::fromUtf8(data);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(bool &data)
{
    TLValue val;
    *this >> val;

    if (val == BoolTrue) {
        data = true;
    } else if (val == BoolFalse) {
        data = false;
    }

    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const QString &str)
{
    return *this << str.toUtf8();
}

inline CTelegramStream &CTelegramStream::operator<<(const bool &data)
{
    if (data) {
        *this << BoolTrue;
    } else {
        *this << BoolFalse;
    }

    return *this;
}

#endif // CTELEGRAMSTREAM_HPP
