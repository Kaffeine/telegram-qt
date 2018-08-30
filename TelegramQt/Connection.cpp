#include "Connection.hpp"

#include "DhLayer.hpp"
#include "RpcLayer.hpp"
#include "SendPackageHelper.hpp"
#include "CTelegramTransport.hpp"
#include "Utils.hpp"

#include <QLoggingCategory>

namespace Telegram {

BaseConnection::BaseConnection(QObject *parent) :
    QObject(parent)
{
}

quint64 BaseConnection::authId() const
{
    return m_sendHelper->authId();
}

QByteArray BaseConnection::authKey() const
{
    return m_sendHelper->authKey();
}

void BaseConnection::setAuthKey(const QByteArray &authKey)
{
    m_sendHelper->setAuthKey(authKey);
}

void BaseConnection::setServerRsaKey(const RsaKey &key)
{
    m_rsaKey = key;
}

void BaseConnection::setTransport(CTelegramTransport *newTransport)
{
    m_transport = newTransport;
    connect(m_transport, &CTelegramTransport::stateChanged, this, &BaseConnection::onTransportStateChanged);
    connect(m_transport, &CTelegramTransport::packageReceived, this, &BaseConnection::onTransportPackageReceived);
//    connect(m_transport, &CTelegramTransport::timeout, this, &CTelegramConnection::onTransportTimeout);
    onTransportStateChanged();

    if (!m_dhLayer) {
        qCritical() << Q_FUNC_INFO << "DH Layer must be set before transport";
        return;
    }
    connect(m_dhLayer, &BaseDhLayer::stateChanged, this, &BaseConnection::onDhStateChanged);
}

void BaseConnection::setStatus(BaseConnection::Status status, BaseConnection::StatusReason reason)
{
    if (m_status == status) {
        return;
    }

    m_status = status;
    emit statusChanged(status, reason);

//    if (status < ConnectionStatusConnected) {
//        stopPingTimer();
//    }
}

void BaseConnection::onTransportStateChanged()
{
    switch (m_transport->state()) {
    case QAbstractSocket::ConnectedState:
        if (m_authKey.isEmpty()) {
            m_dhLayer->setServerRsaKey(m_rsaKey);
            m_dhLayer->init();
            setStatus(Status::Connected, StatusReason::Remote);
        } else {
            setStatus(Status::Connected, StatusReason::Remote);
            setStatus(Status::Authenticated, StatusReason::Local);
        }
        break;
    case QAbstractSocket::UnconnectedState:
        setStatus(Status::Disconnected, status() == Status::Disconnecting ? StatusReason::Local : StatusReason::Remote);
        break;
    default:
        break;
    }
}

void BaseConnection::onTransportPackageReceived(const QByteArray &package)
{
    qDebug() << QString::fromLatin1(metaObject()->className()) + QStringLiteral("::onTransportPackageReceived(%1 bytes)").arg(package.size());
    if (package.size() == sizeof(quint32)) {
        const quint32 errorCode = *(reinterpret_cast<const quint32 *>(package.constData()));
        const qint32 signedCode = static_cast<const qint32>(errorCode);
        qWarning() << "Error:" << errorCode << package.toHex() << signedCode;
        return;
    }
    if (package.size() < 8) {
        qWarning() << "Received package is too small to process:" << package.toHex();
        return;
    }
    const quint64 *authKeyIdBytes = reinterpret_cast<const quint64*>(package.constData());
    if (*authKeyIdBytes) {
        if (!m_rpcLayer->processPackage(package)) {
            qWarning() << "Unable to process RPC packet:" << package.toHex();
        }
    } else {
        if (!m_dhLayer->processPlainPackage(package)) {
            qWarning() << "Unable to process plain packet:" << package.toHex();
        }
    }
}

void BaseConnection::onDhStateChanged()
{
#ifdef DEVELOPER_BUILD
    qDebug() << QString::fromLatin1(metaObject()->className()) + QStringLiteral("::onDhStateChanged(") << m_dhLayer->state() << ")";
#endif
    if (m_dhLayer->state() == BaseDhLayer::State::HasKey) {
        setStatus(Status::Authenticated, StatusReason::Remote);
    }
}

} // Telegram namespace
