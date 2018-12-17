#include "CServerTcpTransport.hpp"

#include <QHostAddress>
#include <QMetaMethod>
#include <QTcpSocket>

#include "AesCtr.hpp"
#include "CRawStream.hpp"
#include "Utils.hpp"
#include "TLValues.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_loggingServerTcpTransport, "telegram.server.transport.tcp", QtWarningMsg)

namespace Telegram {

namespace Server {

TcpTransport::TcpTransport(QTcpSocket *socket, QObject *parent) :
    BaseTcpTransport(parent)
{
    setSocket(socket);
    setState(m_socket->state());
}

void TcpTransport::connectToHost(const QString &, quint16)
{
    qCritical() << Q_FUNC_INFO << "The function must not be called in a server application";
}

bool TcpTransport::startObfuscatedSession()
{
    qCDebug(c_loggingServerTcpTransport()) << Q_FUNC_INFO;
    if (m_socket->bytesAvailable() < 64) {
        qCWarning(c_loggingServerTcpTransport()) << Q_FUNC_INFO << "Invalid package size";
        return false;
    }
    QByteArray plainData = m_socket->read(56);
    CRawStream raw(plainData);

    quint32 firstByte;
    quint32 secondByte;
    raw >> firstByte;
    raw >> secondByte;

    QByteArray encryptionSourceData = raw.readBytes(48);

    if (raw.error()) {
        qCWarning(c_loggingServerTcpTransport()) << Q_FUNC_INFO << "Read error";
        return false;
    }

    // The client sends its encryption key in plain text
    setCryptoKeysSourceData(encryptionSourceData, DirectIsReadReversedIsWrite);
    QByteArray content1 = plainData + m_socket->read(8);
    m_readAesContext->crypt(content1);
    return true;
}

void TcpTransport::readEvent()
{
    if (Q_LIKELY(m_sessionType != Unknown)) {
        return;
    }
    char sessionSign;
    m_socket->getChar(&sessionSign);
    if (sessionSign == char(0xef)) {
        setSessionType(Abridged);
    } else {
        m_socket->ungetChar(sessionSign);
        if (startObfuscatedSession()) {
            setSessionType(Obfuscated);
        } else {
            qCCritical(c_loggingServerTcpTransport()) << Q_FUNC_INFO << "Invalid data";
        }
    }
    qCDebug(c_loggingServerTcpTransport()) << Q_FUNC_INFO << m_socket->peerAddress().toString() << "Session type:" << m_sessionType;
}

} // Server

} // Telegram
