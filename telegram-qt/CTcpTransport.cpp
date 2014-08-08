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

#include "CTcpTransport.hpp"

#include <QTcpSocket>

#include <QDebug>

CTcpTransport::CTcpTransport(QObject *parent) :
    CTelegramTransport(parent),
    m_socket(new QTcpSocket(this)),
    m_firstPackage(true)
{
    connect(m_socket, SIGNAL(connected()), SLOT(whenConnected()));
    connect(m_socket, SIGNAL(readyRead()), SLOT(whenReadyRead()));
}

CTcpTransport::~CTcpTransport()
{
    if (m_socket->isWritable()) {
        m_socket->waitForBytesWritten(100);
        m_socket->disconnectFromHost();
    }
}

void CTcpTransport::connectToHost(const QString &ipAddress, quint32 port)
{
    m_socket->connectToHost(ipAddress, port);
}

bool CTcpTransport::isConnected() const
{
    return m_socket && (m_socket->state() == QAbstractSocket::ConnectedState);
}

void CTcpTransport::sendPackage(const QByteArray &payload)
{
    // quint32 length (included length itself + packet number + crc32 + payload // Length MUST be divisible by 4
    // quint32 packet number
    // quint32 CRC32 (length, quint32 packet number, payload)
    // Payload

    // Abridged version:
    // quint8: 0xef
    // DataLength / 4 < 0x7f ?
    //      (quint8: Packet length / 4) :
    //      (quint8: 0x7f, quint24: Packet length / 4)
    // Payload

    QByteArray package;

    if (m_firstPackage) {
        package.append(char(0xef)); // Start session in Abridged format
        m_firstPackage = false;
    }

    quint32 length = 0;
    length += payload.length();

    package.append(char(length / 4));
    package.append(payload);

    m_lastPackage = package;

    // Looks like server accept only first high-level package in tcp package.
    // So, to send several packages in one execution branch, client have to place packages into container.
    // To workaround this situation (until outgoing containers implementation),
    // we have to make sure that all previous data was written.
    m_socket->waitForBytesWritten();

    m_socket->write(package);
}

void CTcpTransport::whenConnected()
{
    m_expectedLength = 0;
    m_firstPackage = true;
    emit connected();
}

void CTcpTransport::whenReadyRead()
{
    while (m_socket->bytesAvailable() > 0) {
        if (m_expectedLength == 0) {
            if (m_socket->bytesAvailable() < 4) {
                // Four bytes is minimum readable size for new package
                return;
            }

            char length;
            m_socket->getChar(&length);

            if (length < char(0x7f)) {
                m_expectedLength = length * 4;
            } else if (length == char(0x7f)) {
                m_socket->read((char *) &m_expectedLength, 3);
                m_expectedLength *= 4;
            } else {
                qDebug() << "Incorrect TCP package!";
            }
        }

        if (m_socket->bytesAvailable() < m_expectedLength)
            return;

        m_receivedPackage = m_socket->read(m_expectedLength);

        m_expectedLength = 0;

        emit readyRead();
    }
}
