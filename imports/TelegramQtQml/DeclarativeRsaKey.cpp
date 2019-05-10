#include "DeclarativeRsaKey.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

DeclarativeRsaKey::DeclarativeRsaKey(QObject *parent)
    : QObject(parent)
{
}

bool DeclarativeRsaKey::isValid() const
{
    return m_key.isValid();
}

bool DeclarativeRsaKey::loadDefault() const
{
    return m_loadDefaultKey;
}

void DeclarativeRsaKey::setFileName(const QString &fileName)
{
    qDebug() << Q_FUNC_INFO << fileName;
    if (m_fileName == fileName) {
        return;
    }
    m_fileName = fileName;
    if (!fileName.isEmpty()) {
        setKey(RsaKey::fromFile(QUrl::fromUserInput(fileName).toLocalFile()));
    }
    emit fileNameChanged(fileName);
}

void DeclarativeRsaKey::setLoadDefault(bool loadDefault)
{
    if (m_loadDefaultKey == loadDefault) {
        return;
    }
    m_loadDefaultKey = loadDefault;
    if (loadDefault) {
        setKey(RsaKey::defaultKey());
    }
    emit loadDefaultChanged(loadDefault);
}

void DeclarativeRsaKey::setKey(const RsaKey &key)
{
    RsaKey oldKey = m_key;
    m_key = key;
    if (oldKey.isValid() != key.isValid()) {
        emit validChanged(key.isValid());
    }
}

} // Client namespace

} // Telegram namespace
