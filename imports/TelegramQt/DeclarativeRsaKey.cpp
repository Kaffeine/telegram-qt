#include "DeclarativeRsaKey.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

DeclarativeRsaKey::DeclarativeRsaKey(QObject *parent)
    : QObject(parent)
{
    setKey(RsaKey::defaultKey());
}

bool DeclarativeRsaKey::isValid() const
{
    return m_key.isValid();
}

QString DeclarativeRsaKey::fingerprint() const
{
    return QStringLiteral("%1").arg(m_key.fingerprint, 16, 0x10, QLatin1Char('0'));
}

void DeclarativeRsaKey::setFileName(const QString &fileName)
{
    qDebug() << Q_FUNC_INFO << fileName;
    if (m_fileName == fileName) {
        return;
    }
    m_fileName = fileName;
    if (fileName.isEmpty()) {
        setKey(RsaKey::defaultKey());
    } else {
        setKey(RsaKey::fromFile(QUrl::fromUserInput(fileName).toLocalFile()));
    }
    emit fileNameChanged(fileName);
}

void DeclarativeRsaKey::setKey(const RsaKey &key)
{
    RsaKey oldKey = m_key;
    m_key = key;
    if (oldKey.isValid() != key.isValid()) {
        emit validChanged(key.isValid());
    }
    if (oldKey.fingerprint != key.fingerprint) {
        emit fingerprintChanged();
    }
}

} // Client namespace

} // Telegram namespace
