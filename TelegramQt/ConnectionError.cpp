#include "ConnectionError.hpp"

#include <QtEndian>

namespace Telegram {

ConnectionError::ConnectionError(const QByteArray &data)
{
    if (data.size() == packetSize()) {
        m_code = qFromLittleEndian<qint32>(reinterpret_cast<const uchar *>(data.constData()));
    }
}

ConnectionError::ConnectionError(const qint32 code) :
    m_code(code)
{
}

ConnectionError::Code ConnectionError::code() const
{
    return static_cast<ConnectionError::Code>(m_code);
}

QByteArray ConnectionError::toByteArray() const
{
    QByteArray result(sizeof(qint32), Qt::Uninitialized);
    qToLittleEndian(m_code, reinterpret_cast<uchar *>(result.data()));
    return result;
}

QString ConnectionError::description() const
{
    switch (m_code) {
    case InvalidAuthKey:
        return QLatin1String("Invalid auth key");
    default:
        return QStringLiteral("Unknown error bytes: %1").arg(QString::fromLatin1(toByteArray().toHex()));
    }
}

} // Telegram namespace
