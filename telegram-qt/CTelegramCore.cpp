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
    m_transport(0),
    m_authState(AuthNone),
    m_authId(0),
    m_lastMessageId(0),
    m_serverPublicFingersprint(0)
{
    Utils::randomBytes(m_clientNonce.data, m_clientNonce.size());

    m_rsaKey = Utils::loadRsaKey();
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
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;

    const quint64 secs = timeInMs / 1000;
    const quint64 msecs = maxMsecValue / 1000 * (timeInMs % 1000);

    return (secs << 32) + msecs;
}

quint64 CTelegramCore::timeStampToMSecsSinceEpoch(quint64 ts)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;

    const quint64 secs = ts >> 32;
    quint64 msecs = ts & maxMsecValue;

    msecs = msecs * 10000 / maxMsecValue;

    if (msecs % 10 >= 5) {
        msecs += 5;
    }
    msecs /= 10;

    return secs * 1000 + msecs;
}

void CTelegramCore::initAuth()
{
    if (m_authState == AuthNone) {
        m_authRetryId = 0;
        requestPqAuthorization();
    }
}

void CTelegramCore::requestPqAuthorization()
{
    QBuffer output;
    output.open(QIODevice::WriteOnly);
    CTelegramStream outputStream(&output);

    outputStream << ReqPQ;
    outputStream << m_clientNonce;

    sendPlainPackage(output.buffer());

    setAuthState(AuthPqRequested);
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

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

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

    if (fingersprints.count() != 1) {
        qDebug() << "Error: Unexpected Server RSA Fingersprints vector.";
        return false;
    }

    m_serverPublicFingersprint = fingersprints.at(0);

    emit pqReceived();

    if (m_rsaKey.fingersprint != m_serverPublicFingersprint) {
        qDebug() << "Error: Server RSA Fingersprint does not match to loaded key";
        return false;
    }

    return true;
}

void CTelegramCore::requestDhParameters()
{
    Utils::randomBytes(m_newNonce.data, m_newNonce.size());

    QByteArray bigEndianNumber;
    bigEndianNumber.fill(char(0), 8);

    QByteArray encryptedPackage;
    {
        static const int requestedEncryptedPackageLength = 255;
        QBuffer innerData;
        innerData.open(QIODevice::WriteOnly);
        CTelegramStream encryptedStream(&innerData);

        encryptedStream << PQInnerData;

        qToBigEndian(m_pq, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        bigEndianNumber.fill(char(0), 4);
        qToBigEndian(m_p, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        qToBigEndian(m_q, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        encryptedStream << m_clientNonce;
        encryptedStream << m_serverNonce;
        encryptedStream << m_newNonce;

        QByteArray sha = Utils::sha1(innerData.data());
        QByteArray randomPadding;
        randomPadding.resize(requestedEncryptedPackageLength - (sha.length() + innerData.data().length()));
        Utils::randomBytes(&randomPadding);

        encryptedPackage = Utils::rsa(sha + innerData.data() + randomPadding, m_rsaKey);
    }

    QBuffer output;
    output.open(QIODevice::WriteOnly);
    CTelegramStream outputStream(&output);

    outputStream << ReqDHParams;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;

    bigEndianNumber.fill(char(0), 4);
    qToBigEndian(m_p, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    qToBigEndian(m_q, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    outputStream << m_serverPublicFingersprint;

    outputStream << encryptedPackage;

    sendPlainPackage(output.buffer());

    setAuthState(AuthDhRequested);
}

bool CTelegramCore::answerDh(const QByteArray &payload)
{
    QByteArray data = payload;
    QBuffer input;
    input.setBuffer(&data);
    input.open(QIODevice::ReadOnly);
    CTelegramStream inputStream(&input);

    TLValues responseTLValue;
    inputStream >> responseTLValue;

    if (responseTLValue != ServerDHParamsOK) {
        qDebug() << "Error: Server did not accept our DH params";
        return false;
    }

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    QByteArray encryptedAnswer;

    inputStream >> encryptedAnswer;

    m_tmpAesKey = generateTmpAesKey();

    QByteArray answer = Utils::aesDecrypt(encryptedAnswer, m_tmpAesKey);

    QByteArray sha1OfAnswer = answer.mid(0, 20);
    answer = answer.mid(20, 564);

    if (Utils::sha1(answer) != sha1OfAnswer) {
        qDebug() << "Error: SHA1 of encrypted answer is different from announced.";
        return false;
    }

    QBuffer encryptedInput;
    encryptedInput.setBuffer(&answer);
    encryptedInput.open(QIODevice::ReadOnly);
    CTelegramStream encryptedInputStream(&encryptedInput);

    encryptedInputStream >> responseTLValue;

    if (responseTLValue != ServerDHInnerData) {
        qDebug() << "Error: Unexpected TL Value in encrypted answer";
        return false;
    }

    encryptedInputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    encryptedInputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    encryptedInputStream >> m_g;
    encryptedInputStream >> m_dhPrime;
    encryptedInputStream >> m_gA;

    quint32 serverTime;

    encryptedInputStream >> serverTime;

    qDebug() << serverTime << "vs" << QDateTime::currentMSecsSinceEpoch() / 1000;

    m_b.resize(256);
    Utils::randomBytes(&m_b);

    return true;
}

void CTelegramCore::requestDhGenerationResult()
{
    QBuffer output;
    output.open(QIODevice::WriteOnly);
    CTelegramStream outputStream(&output);

    outputStream << SetClientDHParams;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;

    QByteArray encryptedPackage;
    {
        QBuffer innerData;
        innerData.open(QIODevice::WriteOnly);
        CTelegramStream encryptedStream(&innerData);

        encryptedStream << ClientDHInnerData;

        encryptedStream << m_clientNonce;
        encryptedStream << m_serverNonce;
        encryptedStream << m_authRetryId;

        QByteArray binNumber;
        binNumber.resize(sizeof(m_g));
        qToBigEndian(m_g, (uchar *) binNumber.data());

        binNumber = Utils::binaryNumberModExp(binNumber, m_dhPrime, m_b);

        encryptedStream << binNumber;

        QByteArray sha = Utils::sha1(innerData.data());
        QByteArray randomPadding;

        int packageLength = sha.length() + innerData.data().length();
        if ((packageLength) % 16) {
            randomPadding.resize(16 - (packageLength % 16));
            Utils::randomBytes(&randomPadding);

            packageLength += randomPadding.size();
        }

        encryptedPackage = Utils::aesEncrypt(sha + innerData.data() + randomPadding, m_tmpAesKey);

        encryptedPackage.truncate(packageLength);
    }

    outputStream << encryptedPackage;

    sendPlainPackage(output.buffer());
    setAuthState(AuthDhGenerationResultRequested);

    m_authKey = Utils::binaryNumberModExp(m_gA, m_dhPrime, m_b);
    m_authId = Utils::getFingersprint(m_authKey);
    m_authKeyAuxHash = Utils::getFingersprint(m_authKey, /* lower-order */ false);
}

bool CTelegramCore::processServersDHAnswer(const QByteArray &payload)
{
    QByteArray data = payload;
    QBuffer input;
    input.setBuffer(&data);
    input.open(QIODevice::ReadOnly);
    CTelegramStream inputStream(&input);

    TLValues responseTLValue;
    inputStream >> responseTLValue;

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    TLNumber128 newNonceHashLower128;

    inputStream >> newNonceHashLower128;

    QByteArray readedHashPart(newNonceHashLower128.data, newNonceHashLower128.size());

    QByteArray expectedHashData(m_newNonce.data, m_newNonce.size());

    expectedHashData.append(Utils::sha1(m_authKey).left(8));

    if (responseTLValue == DhGenOk) {
//        qDebug() << "Answer OK";

        expectedHashData.insert(32, char(1));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }

        setAuthState(AuthSuccess);
        return true;
    } else if (responseTLValue == DhGenRetry) {
        qDebug() << "Answer RETRY";

        expectedHashData.insert(32, char(2));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }
    } else if (responseTLValue == DhGenFail) {
        qDebug() << "Answer FAIL";

        expectedHashData.insert(32, char(3));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }
    }

    qDebug() << "Error: Unexpected server response.";

    return false;
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

    /* Will be reimplemented later */

    switch (m_authState) {
    case AuthPqRequested:
        if (answerPqAuthorization(payload)) {
            requestDhParameters();
        }
        break;
    case AuthDhRequested:
        if (answerDh(payload)) {
            requestDhGenerationResult();
        }
        break;
    case AuthDhGenerationResultRequested:
        processServersDHAnswer(payload);
        break;
    default:
        break;
    }
}

SAesKey CTelegramCore::generateTmpAesKey() const
{
    QByteArray newNonceAndServerNonce;
    newNonceAndServerNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndServerNonce.append(m_serverNonce.data, m_serverNonce.size());
    QByteArray serverNonceAndNewNonce;
    serverNonceAndNewNonce.append(m_serverNonce.data, m_serverNonce.size());
    serverNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    QByteArray newNonceAndNewNonce;
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());

    const QByteArray key = Utils::sha1(newNonceAndServerNonce) + Utils::sha1(serverNonceAndNewNonce).mid(0, 12);
    const QByteArray iv  = Utils::sha1(serverNonceAndNewNonce).mid(12, 8) + Utils::sha1(newNonceAndNewNonce) + QByteArray(m_newNonce.data, 4);

    return SAesKey(key, iv);
}

SAesKey CTelegramCore::generateAesKey(const QByteArray &messageKey, int x) const
{
    QByteArray sha1_a = Utils::sha1(messageKey + m_authKey.mid(x, 32));
    QByteArray sha1_b = Utils::sha1(m_authKey.mid(32 + x, 16) + messageKey + m_authKey.mid(48 + x, 16));
    QByteArray sha1_c = Utils::sha1(m_authKey.mid(64 + x, 32) + messageKey);
    QByteArray sha1_d = Utils::sha1(messageKey + m_authKey.mid(96 + x, 32));

    const QByteArray key = sha1_a.mid(0, 8) + sha1_b.mid(8, 12) + sha1_c.mid(4, 12);
    const QByteArray iv  = sha1_a.mid(8, 12) + sha1_b.mid(0, 8) + sha1_c.mid(16, 4) + sha1_d.mid(0, 8);

    return SAesKey(key, iv);
}

void CTelegramCore::sendPlainPackage(const QByteArray &buffer)
{
    QBuffer output;
    output.open(QIODevice::WriteOnly);
    CTelegramStream outputStream(&output);

    outputStream << quint64(0);
    outputStream << newMessageId();
    outputStream << quint32(buffer.length());

    m_transport->sendPackage(output.buffer() + buffer);
}

void CTelegramCore::setAuthState(CTelegramCore::AuthState newState)
{
    if (m_authState == newState)
        return;

    m_authState = newState;
    emit authStateChanged();
}

quint64 CTelegramCore::newMessageId()
{
    quint64 newLastMessageId = formatClientTimeStamp(QDateTime::currentMSecsSinceEpoch());

    if (newLastMessageId == m_lastMessageId) {
        newLastMessageId += 4; // Client's outgoing message id should be divisible by 4 and be greater than previous message id.
    }

    if (!(newLastMessageId & quint64(0xffffff))) {
        // The lower 32 bits of messageId passed by the client must not contain that many zeroes.
        newLastMessageId += quint64(0x1230);
    }

    m_lastMessageId = newLastMessageId;

    return m_lastMessageId;
}
