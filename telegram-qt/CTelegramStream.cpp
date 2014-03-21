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

#include "CTelegramStream.hpp"

#include <QtEndian>

#include <QIODevice>
#include <QDebug>

static const char s_nulls[4] = { 0, 0, 0, 0 };

CTelegramStream::CTelegramStream(QIODevice *d) :
    m_device(d)
{

}

void CTelegramStream::setDevice(QIODevice *newDevice)
{
    m_device = newDevice;
}

void CTelegramStream::unsetDevice()
{
    m_device = 0;
}

bool CTelegramStream::atEnd() const
{
    return m_device ? m_device->atEnd() : true;
}

CTelegramStream &CTelegramStream::operator>>(qint32 &i)
{
    m_device->read((char *)&i, 4);

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(qint64 &i)
{
    m_device->read((char *)&i, 8);

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(QString &str)
{
    return *this;
}

CTelegramStream &CTelegramStream::operator<<(qint32 i)
{
    m_device->write((const char *) &i, 4);

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(qint64 i)
{
    m_device->write((const char *) &i, 8);

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const QString &str)
{
    quint32 length = str.length();

    if (length < 0xfe) {
        const char lengthToWrite = length;
        m_device->putChar(lengthToWrite);
        m_device->write(str.toUtf8());
        length += 1;

    } else {
        *this << quint32((length << 8) + 0xfe);
        m_device->write(str.toUtf8());
        length += 4;
    }

    if (length & 3) {
        m_device->write(s_nulls, 4 - (length & 3));
    }

    return *this;
}
