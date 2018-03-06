#include "CServerTcpTransport.hpp"

#include <QHostAddress>
#include <QMetaMethod>
#include <QTcpSocket>

#include "AesCtr.hpp"
#include "CRawStream.hpp"
#include "Utils.hpp"
#include "TLValues.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_loggingServerTcpTransport, "telegram.server.transport.tcp", QtDebugMsg)

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

bool TcpTransport::startObfuscatedSession()
{
    qCDebug(c_loggingServerTcpTransport()) << Q_FUNC_INFO;
    if (m_socket->bytesAvailable() < 64) {
        qCWarning(c_loggingServerTcpTransport()) << Q_FUNC_INFO << "Invalid package size";
        return false;
    }
    QByteArray plainData = m_socket->read(56);

    qCDebug(c_loggingServerTcpTransport()) << "read raw data:" << plainData.toHex();

    CRawStream raw(plainData);

    quint32 firstByte;
    quint32 secondByte;

//    qCDebug(c_loggingServerTcpTransport) << "read first";
    raw >> firstByte;
//    qCDebug(c_loggingServerTcpTransport) << "read second";
    raw >> secondByte;
//    qCDebug(c_loggingServerTcpTransport) << "read data";

    QByteArray encryptionSourceData = raw.readBytes(48);
//    qCDebug(c_loggingServerTcpTransport()) << "raw 48 bytes:" << encryptionSourceData.toHex();

    if (raw.error()) {
        qCWarning(c_loggingServerTcpTransport()) << Q_FUNC_INFO << "Read error";
        return false;
    }

//    Crypto::AesCtrContext context1;
//    context1.setKey(encryptionSourceData.left(Crypto::AesCtrContext::KeySize));
//    context1.setIVec(encryptionSourceData.mid(Crypto::AesCtrContext::KeySize, Crypto::AesCtrContext::IvecSize));

     //         ResPQ = 0x05162463, CRC32?

    // len, num, req num,

    // 0a, length 40 = 4 + 8 + 12 + 16 = 40.
    // 00 00 00 00 00 00 00 00 // Auth key
    // 00 00 00 00 // Message ID
    // 1f cc 7a 5a // Timestamp // Unix timestamp: 5A 7A CE E8
    // 14 00 00 00 // Request size in bytes, 20
    // 78 97 46 60 // ReqPq
    // 87 58 39 4b 22 90 ef 9a 53 f1 22 49 93 85 d4 a1 // nonce128

    // 0a // length
    // 00 00 00 00 00 00 00 00 // Auth key
    // 00 00 00 00 // Message ID
    // 20 cc 7a 5a // Timestamp // Unix timestamp: 5A 7A CE E8
    // 14 00 00 00 // Request size in bytes, 20
    // 78 97 46 60 // ReqPq
    // 54 9f cc f2 d5 bf 13 ba c0 8c a4 b1 a4 45 8e 19 // nonce128

    // The client sends its encryption key in plain text
    setCryptoKeysSourceData(encryptionSourceData, DirectIsReadReversedIsWrite);

    QByteArray content1 = plainData + m_socket->read(8);
    m_readAesContext->crypt(content1);

//    QByteArray contentData = m_socket->readAll();
//    QByteArray decrypted = m_readAesContext->crypt(contentData);

//    qCDebug(c_loggingServerTcpTransport()) << "dump:" << decrypted.toHex();
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
