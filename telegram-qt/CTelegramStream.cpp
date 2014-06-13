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

template CTelegramStream &CTelegramStream::operator>>(QVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<quint64> &v);

template CTelegramStream &CTelegramStream::operator<<(const QVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const QVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const QVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const QVector<quint64> &v);

template CTelegramStream &CTelegramStream::operator>>(QVector<SDcInfo> &v);

template CTelegramStream &CTelegramStream::operator>>(QVector<TLUser> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<TLContact> &v);

CTelegramStream::CTelegramStream(QByteArray *data, bool write) :
    CRawStream(data, write)
{

}

CTelegramStream::CTelegramStream(const QByteArray &data) :
    CRawStream(data)
{

}

CTelegramStream::CTelegramStream(QIODevice *d) :
    CRawStream(d)
{

}

CTelegramStream &CTelegramStream::operator>>(QByteArray &data)
{
    quint32 length = 0;
    m_device->getChar((char *) &length);

    if (length < 0xfe) {
        data.resize(length);
        length += 1; // Plus one byte before data
    } else {
        m_device->read((char *) &length, 3);
        data.resize(length);
        length += 4; // Plus four bytes before data
    }

    m_device->read(data.data(), data.size());

    if (length & 3) {
        m_device->read(4 - (length & 3));
    }

    return *this;
}

template <typename T>
CTelegramStream &CTelegramStream::operator>>(QVector<T> &v)
{
    QVector<T> result;

    TLValue vectorHash;

    *this >> vectorHash;

    if (vectorHash == Vector) {
        quint32 length = 0;
        *this >> length;
        for (int i = 0; i < length; ++i) {
            T value;
            *this >> value;
            result.append(value);
        }
    }

    v = result;
    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLFileLocation &fileLocation)
{
    // https://core.telegram.org/type/FileLocation

    TLFileLocation result;

    TLValue type;
    *this >> type;

    switch (type) {
    case FileLocationUnavailable:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case FileLocation:
        *this >> result.dcId;
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    default:
        // ERROR!
        break;
    }

    fileLocation = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserProfilePhoto &photo)
{
    // https://core.telegram.org/type/UserProfilePhoto

    TLUserProfilePhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
    case UserProfilePhotoEmpty:
        break;
    case UserProfilePhoto:
        *this >> result.photoId;
        *this >> result.photoSmall;
        *this >> result.photoBig;
        break;
    default:
        // ERROR!
        break;
    }

    photo = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserStatus &status)
{
    // https://core.telegram.org/type/UserStatus
    TLUserStatus result;

    TLValue type;
    *this >> type;

    switch (type) {
    case UserStatusEmpty:
        result.tlType = type;
        break;
    case UserStatusOnline:
        result.tlType = type;
        *this >> result.expires;
        break;
    case UserStatusOffline:
        result.tlType = type;
        *this >> result.wasOnline;
        break;
    default:
        // ERROR!
        break;
    }

    status = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUser &user)
{
    // https://core.telegram.org/type/User
    TLUser result;

    TLValue type;
    *this >> type;

    switch (type) {
    case UserEmpty:
        *this >> result.id;
        break;
    case UserSelf:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        *this >> result.inactive;
        break;
    case UserContact:
    case UserRequest:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.accessHash;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        break;
    case UserForeign:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.accessHash;
        *this >> result.photo;
        *this >> result.status;
        break;
    case UserDeleted:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    default:
        // ERROR!
        break;
    }

    user = result;
    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContact &contact)
{
    // https://core.telegram.org/type/Contact
    TLContact result;

    TLValue contactValue;
    *this >> contactValue;

    if (contactValue == Contact) {
        *this >> result.userId;
        *this >> result.mutual;
    }

    contact = result;
    return *this;
}

template <typename T>
CTelegramStream &CTelegramStream::operator<<(const QVector<T> &v)
{
    *this << Vector;
    *this << quint32(v.count());

    for (int i = 0; i < v.count(); ++i) {
        *this << v.at(i);
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const QByteArray &data)
{
    quint32 length = data.size();

    if (length < 0xfe) {
        const char lengthToWrite = length;
        m_device->putChar(lengthToWrite);
        m_device->write(data);
        length += 1;

    } else {
        *this << quint32((length << 8) + 0xfe);
        m_device->write(data);
        length += 4;
    }

    if (length & 3) {
        m_device->write(s_nulls, 4 - (length & 3));
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(SDcInfo &info)
{
    TLValue optionCode;
    *this >> optionCode;

    if (optionCode != DcOption) {
        // ERROR!
        return *this;
    }

    *this >> info.id;
    *this >> info.hostName;
    *this >> info.ipAddress;
    *this >> info.port;

    return *this;
}
