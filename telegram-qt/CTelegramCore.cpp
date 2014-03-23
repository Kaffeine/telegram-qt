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

#include "CTelegramCore.hpp"

#include <QFile>
#include <QBuffer>
#include <QDebug>

#include <QDateTime>

#include <QtEndian>

#include "CTelegramStream.hpp"
#include "CTelegramTransport.hpp"
#include "Utils.hpp"

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_appId(0),
    m_appHash(QLatin1String("00000000000000000000000000000000")),
    m_transport(0)
{
    Utils::randomBytes(m_clientNonce.udata, 16);
}

void CTelegramCore::setAppId(quint32 newId)
{
    m_appId = newId;
}

bool CTelegramCore::setAppHash(const QString &newHash)
{
    if (newHash.length() != 16)
        return false;

    m_appHash = newHash;

    return true;
}

void CTelegramCore::setTransport(CTelegramTransport *newTransport)
{
    m_transport = newTransport;

    connect(m_transport, SIGNAL(readyRead()), SLOT(whenReadyRead()));
}

quint64 CTelegramCore::formatTimeStamp(qint64 timeInMs)
{
    static const quint32 maxMsecValue = (1UL << 32) - 1;
    quint64 secs = timeInMs / 1000;

    quint32 msecs = timeInMs % 1000;

    msecs = maxMsecValue / 1000 * msecs;

    return (secs << 32) + msecs;
}

void CTelegramCore::requestPqAuthorization()
{
    QBuffer output;
    output.open(QIODevice::WriteOnly);
    CTelegramStream outputStream(&output);

    outputStream << quint64(0); // Zero auth for this message
    outputStream << formatClientTimeStamp(QDateTime::currentMSecsSinceEpoch());
    outputStream << quint32(20); // Message is 20 bytes in length
    outputStream << ReqPQ;
    outputStream << m_clientNonce;

    m_transport->sendPackage(output.buffer());
}

bool CTelegramCore::answerPqAuthorization(const QByteArray &payload)
{
    // Payload is passed as const, but we open device in read-only mode, so
    // Let's workaround const by construction variable copy with COW-feature.
    QByteArray data = payload;
    QBuffer input;
    input.setBuffer(&data);
    input.open(QIODevice::ReadOnly);
    CTelegramStream inputStream(&input);

    TLValues responsePqValue;
    inputStream >> responsePqValue;

    if (responsePqValue != ResPQ) {
        qDebug() << "Error: Unexpected operation code";
        return false;
    }

    MyQuint128 clientNonce;
    MyQuint128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    m_serverNonce = serverNonce;

    QByteArray pq;

    inputStream >> pq;

    if (pq.size() != 8) {
        qDebug() << "Error: PQ should be 8 bytes in length";
        return false;
    }

    m_pq = qFromBigEndian<quint64>((uchar *) pq.data());

    quint64 div1 = Utils::findDivider(m_pq);

    if (div1 == 1) {
        qDebug() << "Error: Can not solve PQ.";
        return false;
    }
    quint64 div2 = m_pq / div1;

    if (div1 < div2) {
        m_p = div1;
        m_q = div2;
    } else {
        m_p = div2;
        m_q = div1;
    }

    QVector<quint64> fingersprints;

    inputStream >> fingersprints;

    emit pqReceived();

    return true;
}

void CTelegramCore::whenReadyRead()
{
    QByteArray incoming = m_transport->getPackage();
    QBuffer input;
    input.setBuffer(&incoming);
    input.open(QIODevice::ReadOnly);
    CTelegramStream inputStream(&input);

    quint64 auth = 0;
    quint64 timeStamp = 0;
    quint32 length = 0;

    inputStream >> auth;
    inputStream >> timeStamp;
    inputStream >> length;

    if (inputStream.bytesRemaining() != length) {
        qDebug() << "Corrupted packet. Specified length does not equal to real length";
        return;
    }

    QByteArray payload = inputStream.readBytes(length);

    answerPqAuthorization(payload);
}
