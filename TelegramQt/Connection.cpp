#include "Connection.hpp"

#include "ConnectionError.hpp"
#include "DhLayer.hpp"
#include "RpcLayer.hpp"
#include "SendPackageHelper.hpp"
#include "CTelegramTransport.hpp"
#include "Utils.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_baseConnectionCategory, "telegram.base.connection", QtWarningMsg)

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
        qCCritical(c_baseConnectionCategory) << Q_FUNC_INFO << "DH Layer must be set before transport";
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

    if (status == Status::Failed) {
        m_rpcLayer->onConnectionFailed();
    }
}

void BaseConnection::onTransportStateChanged()
{
    switch (m_transport->state()) {
    case QAbstractSocket::ConnectedState:
        if (m_sendHelper->authKey().isEmpty()) {
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
    qCDebug(c_baseConnectionCategory) << QString::fromLatin1(metaObject()->className()) + QStringLiteral("::onTransportPackageReceived(%1 bytes)").arg(package.size());
    if (package.size() == ConnectionError::packageSize()) {
        ConnectionError e(package.constData());
        if (status() == Status::Failed) {
            // We still can get replies to already sent message even if the connection
            // is already failed, but it makes no sense to shout them out.
            qCDebug(c_baseConnectionCategory) << "Error:" << e.description();
            return;
        }
        qCWarning(c_baseConnectionCategory) << "Error:" << e.description();
        emit errorOccured(e.description());
        setStatus(Status::Failed, StatusReason::Remote);
        return;
    }
    if (package.size() < 8) {
        qCWarning(c_baseConnectionCategory) << "Received package is too small to process:" << package.toHex();
        return;
    }
    const quint64 *authKeyIdBytes = reinterpret_cast<const quint64*>(package.constData());
    if (*authKeyIdBytes) {
        if (!processAuthKey(*authKeyIdBytes)) {
            qCDebug(c_baseConnectionCategory) << "Received incorrect auth id.";
            return;
        }
        if (!m_rpcLayer->processPackage(package)) {
            qCDebug(c_baseConnectionCategory) << "Unable to process RPC packet:" << package.toHex();
        }
    } else {
        if (!m_dhLayer->processPlainPackage(package)) {
            qCDebug(c_baseConnectionCategory) << "Unable to process plain packet:" << package.toHex();
        }
    }
}

void BaseConnection::onDhStateChanged()
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_baseConnectionCategory) << QString::fromLatin1(metaObject()->className()) + QStringLiteral("::onDhStateChanged(") << m_dhLayer->state() << ")";
#endif
    if (m_dhLayer->state() == BaseDhLayer::State::HasKey) {
        setStatus(Status::Authenticated, StatusReason::Remote);
    }
}

} // Telegram namespace
