#include "CServerTcpTransport.hpp"

#include <QHostAddress>
#include <QMetaMethod>
#include <QTcpSocket>

namespace Telegram {

namespace Server {

TcpTransport::TcpTransport(QTcpSocket *socket, QObject *parent) :
    CTcpTransport(parent)
{
    setSocket(socket);
    setState(m_socket->state());
}

void TcpTransport::connectToHost(const QString &ipAddress, quint32 port)
{
    Q_UNUSED(ipAddress)
    Q_UNUSED(port)
    qCritical() << Q_FUNC_INFO << "The function must not be called in a server application";
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
        setSessionType(FullSize);
    }
    qDebug() << Q_FUNC_INFO << m_socket->peerAddress().toString() << "Session type:" << m_sessionType;
}

} // Server

} // Telegram
