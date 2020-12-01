/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "ClientDhLayer.hpp"
#include "DhSession.hpp"

#include "BaseTransport.hpp"
#include "MTProto/Stream.hpp"
#include "PendingRpcOperation.hpp"
#include "RandomGenerator.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"

#include <QDateTime>
#include <QLoggingCategory>
#include <QtEndian>

Q_LOGGING_CATEGORY(c_clientDhLayerCategory, "telegram.client.dhlayer", QtWarningMsg)

namespace Telegram {

namespace Client {

class DhSession : public BaseDhSession
{
public:
    QByteArray b;
};

/*
    \class Telegram::Client::DhLayer
    \brief The client implementation of Diffie-Hellman encryption.
    \inmodule TelegramQt
    \ingroup Client

    \sa BaseDhLayer
*/

DhLayer::DhLayer(QObject *parent) :
    BaseDhLayer(parent)
{
}

void DhLayer::init()
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    m_authRetryId = 0;
    m_session = new DhSession;

    RandomGenerator::instance()->generate(m_session->clientNonce.data, m_session->clientNonce.size());
    PendingRpcOperation *op = requestPqAuthorization();
    setState(State::PqRequested);
    connect(op, &PendingRpcOperation::finished, this, &DhLayer::onPqAuthorizationAnswer);
}

PendingRpcOperation *DhLayer::requestPqAuthorization()
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    DhSession *session = getSession();
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ReqPq;
    outputStream << session->clientNonce;
    return sendPlainPackage(outputStream.getData());
}

void DhLayer::onPqAuthorizationAnswer(PendingRpcOperation *operation)
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    if (!operation->isSucceeded()) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Bad1";
        setState(State::Failed);
        return;
    }
    if (!acceptPqAuthorization(operation->replyData())) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Bad2";
        setState(State::Failed);
        return;
    }
    PendingRpcOperation *op = requestDhParameters();
    setState(State::DhRequested);
    connect(op, &PendingRpcOperation::finished, this, &DhLayer::onDhParametersAnswer);
}

bool DhLayer::acceptPqAuthorization(const QByteArray &payload)
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    DhSession *session = getSession();
    MTProto::Stream inputStream(payload);

    TLValue responsePqValue;
    inputStream >> responsePqValue;

    if (responsePqValue != TLValue::ResPQ) {
        qCWarning(c_clientDhLayerCategory) << "Error: Unexpected operation code";
        return false;
    }

    TLNumber128 clientNonce;
    inputStream >> clientNonce;

    if (clientNonce != session->clientNonce) {
        qCWarning(c_clientDhLayerCategory) << "Error: The client nonce in the incoming packet"
                                              " is different from our own.";
#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Remote client nonce:" << clientNonce
                                         << "local:" << session->clientNonce;
#endif
        return false;
    }

    TLNumber128 serverNonce;
    inputStream >> serverNonce;
    session->serverNonce = serverNonce;

    QByteArray pq;

    inputStream >> pq;

    if (pq.size() != 8) {
        qCWarning(c_clientDhLayerCategory) << "Error: PQ should be 8 bytes in length";
        return false;
    }

    qCDebug(c_clientDhLayerCategory) << "PQ data:" << pq.toHex();
    session->pq = qFromBigEndian<quint64>(reinterpret_cast<const uchar*>(pq.constData()));

    qCDebug(c_clientDhLayerCategory) << "PQ:" << session->pq;

    if (session->pq == 0) {
        qCWarning(c_clientDhLayerCategory) << "Error: Invalid (zero) PQ value.";
        return false;
    }

    quint64 div1 = Utils::findDivider(session->pq);

    if (div1 == 1) {
        qCWarning(c_clientDhLayerCategory) << "Error: Can not solve PQ.";
        return false;
    }
    quint64 div2 = session->pq / div1;

    if (div1 < div2) {
        session->p = div1;
        session->q = div2;
    } else {
        session->p = div2;
        session->q = div1;
    }

    QVector<quint64> fingerprints;
    inputStream >> fingerprints;
    if (fingerprints.count() != 1) {
        qCDebug(c_clientDhLayerCategory) << "Error: Unexpected Server RSA Fingersprints vector size:"
                                         << fingerprints.size();
        return false;
    }
#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Client nonce:" << session->clientNonce;
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Server nonce:" << session->serverNonce;
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "PQ:" << session->pq;
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "P:" << session->p;
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Q:" << session->q;
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Fingerprints:" << fingerprints;
#endif
    for (quint64 serverFingerprint : fingerprints) {
        if (serverFingerprint == m_rsaKey.fingerprint) {
            return true;
        }
    }
    qCWarning(c_clientDhLayerCategory) << "Error: Server RSA fingersprints" << fingerprints
                                       << " do not match to the loaded key" << m_rsaKey.fingerprint;
    return false;
}

PendingRpcOperation *DhLayer::requestDhParameters()
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    DhSession *session = getSession();
    RandomGenerator::instance()->generate(session->newNonce.data, session->newNonce.size());

#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "New nonce:" << session->newNonce;
#endif

    QByteArray bigEndianNumber;
    bigEndianNumber.fill(char(0), 8);

    QByteArray encryptedPackage;
    {
        static const int requestedEncryptedPackageLength = 255;
        MTProto::Stream encryptedStream(MTProto::Stream::WriteOnly);
        encryptedStream << TLValue::PQInnerData;

        qToBigEndian(session->pq, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        bigEndianNumber.fill(char(0), 4);
        qToBigEndian(session->p, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        qToBigEndian(session->q, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        encryptedStream << session->clientNonce;
        encryptedStream << session->serverNonce;
        encryptedStream << session->newNonce;

        const QByteArray innerData = encryptedStream.getData();
        const QByteArray sha = Utils::sha1(innerData);
        QByteArray randomPadding;
        randomPadding.resize(requestedEncryptedPackageLength - (sha.length() + innerData.length()));
        RandomGenerator::instance()->generate(&randomPadding);
        encryptedPackage = Utils::rsa(sha + innerData + randomPadding, m_rsaKey);
#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Inner sha:"
                                         << QByteArrayLiteral("0x") + sha.toHex();
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Inner data:"
                                         << QByteArrayLiteral("0x") + innerData.toHex();
    #endif
    }

    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::ReqDHParams;
    outputStream << session->clientNonce;
    outputStream << session->serverNonce;

    bigEndianNumber.fill(char(0), 4);
    qToBigEndian(session->p, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    qToBigEndian(session->q, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "public server fs:" << m_rsaKey.fingerprint;
    outputStream << m_rsaKey.fingerprint;

    outputStream << encryptedPackage;
    return sendPlainPackage(outputStream.getData());
}

void DhLayer::onDhParametersAnswer(PendingRpcOperation *operation)
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    if (!operation->isSucceeded()) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Bad1";
        setState(State::Failed);
        return;
    }
    if (!acceptDhAnswer(operation->replyData())) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Bad2";
        setState(State::Failed);
        return;
    }
    generateDh();
    PendingRpcOperation *op = requestDhGenerationResult();
    setState(State::DhGenerationResultRequested);
    connect(op, &PendingRpcOperation::finished, this, &DhLayer::onDhGenerationResultAnswer);
}

bool DhLayer::acceptDhAnswer(const QByteArray &payload)
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    MTProto::Stream inputStream(payload);

    TLValue responseTLValue;
    inputStream >> responseTLValue;

    if (!checkClientServerNonse(inputStream)) {
        return false;
    }

    switch (responseTLValue) {
    case TLValue::ServerDHParamsOk: {
        QByteArray encryptedAnswer;
        inputStream >> encryptedAnswer;
        return processServerDHParamsOK(encryptedAnswer);
    }
    default:
        qCDebug(c_clientDhLayerCategory) << "Error: Server did not accept our DH params.";
    }
    return false;
}

bool DhLayer::processServerDHParamsOK(const QByteArray &encryptedAnswer)
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "encryptedAnswer.size():" << encryptedAnswer.size();
    DhSession *session = getSession();
    session->tmpAesKey = generateTmpAesKey(session);

    const QByteArray answerWithHash = Crypto::aesDecrypt(encryptedAnswer, session->tmpAesKey);
    const QByteArray sha1OfAnswer = answerWithHash.mid(0, 20);
    const QByteArray answer = answerWithHash.mid(20, 564);
    if (Utils::sha1(answer) != sha1OfAnswer) {
        qCDebug(c_clientDhLayerCategory) << "Error: SHA1 of encrypted answer is different from announced.";
        return false;
    }

    MTProto::Stream encryptedInputStream(answer);

    TLValue responseTLValue;
    encryptedInputStream >> responseTLValue;

    if (responseTLValue != TLValue::ServerDHInnerData) {
        qCDebug(c_clientDhLayerCategory) << "Error: Unexpected TL Value in encrypted answer.";
        return false;
    }

    if (!checkClientServerNonse(encryptedInputStream)) {
        return false;
    }

    encryptedInputStream >> session->g;
    encryptedInputStream >> session->dhPrime;
    encryptedInputStream >> session->gA;

    if ((session->g < 2) || (session->g > 7)) {
        qCDebug(c_clientDhLayerCategory) << "Error: Received 'g' number is out of the acceptable range [2-7].";
        return false;
    }

    if (session->dhPrime.length() != 2048 / 8) {
        qCDebug(c_clientDhLayerCategory) << "Error: Received dhPrime number length is not correct."
                                         << session->dhPrime.length() << 2048 / 8;
        return false;
    }

    if (!(session->dhPrime.at(0) & 128)) {
        qCDebug(c_clientDhLayerCategory) << "Error: Received dhPrime is too small.";
        return false;
    }

    qCDebug(c_clientDhLayerCategory) << "dhPrime size:" << session->dhPrime.size() << session->dhPrime.toHex();
    qCDebug(c_clientDhLayerCategory) << "gA size:" << session->gA.size() << session->gA.toHex();

    quint32 serverTime;
    encryptedInputStream >> serverTime;
    m_sendHelper->setDeltaTime(qint64(serverTime) - (QDateTime::currentMSecsSinceEpoch() / 1000));
    return true;
}

void DhLayer::generateDh()
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    DhSession *session = getSession();
    // #6 Client computes random 2048-bit number b (using a sufficient amount of entropy)
    // and sends the server a message
    session->b.resize(256);
    RandomGenerator::instance()->generate(&session->b);

    // IMPORTANT: Apart from the conditions on the Diffie-Hellman prime dh_prime and generator g,
    // both sides are to check that g, g_a and g_b are greater than 1 and less than dh_prime - 1.
    // We recommend checking that g_a and g_b are between 2^{2048-64} and dh_prime - 2^{2048-64} as well.

#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
    qCDebug(c_clientDhLayerCategory) << "session->b" << session->b;
#endif
}

PendingRpcOperation *DhLayer::requestDhGenerationResult()
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    DhSession *session = getSession();
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::SetClientDHParams;
    outputStream << session->clientNonce;
    outputStream << session->serverNonce;

    QByteArray encryptedPackage;
    {
        MTProto::Stream encryptedStream(MTProto::Stream::WriteOnly);
        encryptedStream << TLValue::ClientDHInnerData;
        encryptedStream << session->clientNonce;
        encryptedStream << session->serverNonce;
        encryptedStream << m_authRetryId;

        QByteArray binNumber;
        binNumber.resize(sizeof(session->g));
        qToBigEndian(session->g, (uchar *) binNumber.data());
        binNumber = Utils::binaryNumberModExp(binNumber, session->dhPrime, session->b);
        encryptedStream << binNumber;

        const QByteArray innerData = encryptedStream.getData();
        const QByteArray sha = Utils::sha1(innerData);
        QByteArray randomPadding;

        int packageLength = sha.length() + innerData.length();
        if ((packageLength) % 16) {
            randomPadding.resize(16 - (packageLength % 16));
            RandomGenerator::instance()->generate(&randomPadding);

            packageLength += randomPadding.size();
        }
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Inner data size:" << innerData.size();

        encryptedPackage = Crypto::aesEncrypt(sha + innerData + randomPadding, session->tmpAesKey);
        encryptedPackage.truncate(packageLength);
    }

    outputStream << encryptedPackage;
    return sendPlainPackage(outputStream.getData());
}

void DhLayer::onDhGenerationResultAnswer(PendingRpcOperation *operation)
{
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO;
    if (!operation->isSucceeded()) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Bad1";
        setState(State::Failed);
        return;
    }
    if (!processServerDhAnswer(operation->replyData())) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Bad2";
        setState(State::Failed);
        return;
    }
    setState(State::HasKey);
}

bool DhLayer::processServerDhAnswer(const QByteArray &payload)
{
    MTProto::Stream inputStream(payload);
    DhSession *session = getSession();
    TLValue responseTLValue;
    inputStream >> responseTLValue;
    qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << responseTLValue;

    if (!checkClientServerNonse(inputStream)) {
        return false;
    }

    TLNumber128 newNonceHashLower128;
    inputStream >> newNonceHashLower128;
    const QByteArray readedHashPart(newNonceHashLower128.data, newNonceHashLower128.size());
    const QByteArray newAuthKey = Utils::binaryNumberModExp(session->gA, session->dhPrime, session->b);
    const QByteArray newAuthKeySha = Utils::sha1(newAuthKey);
    QByteArray expectedHashData(session->newNonce.data, session->newNonce.size());
    expectedHashData.append(newAuthKeySha.left(8));
    if (responseTLValue == TLValue::DhGenOk) {
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Answer OK";
        expectedHashData.insert(32, char(1));
    } else if (responseTLValue == TLValue::DhGenRetry) {
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Answer RETRY";
        expectedHashData.insert(32, char(2));
    } else if (responseTLValue == TLValue::DhGenFail) {
        qCDebug(c_clientDhLayerCategory) << Q_FUNC_INFO << "Answer FAIL";
        expectedHashData.insert(32, char(3));
    } else {
        qCDebug(c_clientDhLayerCategory) << "Error: Unexpected server response.";
        return false;
    }
    qCDebug(c_clientDhLayerCategory) << "readedHashPart..." << readedHashPart.toHex();

    if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
        qCDebug(c_clientDhLayerCategory) << "Error: Server (newNonce + auth key) hash is not correct.";
        return false;
    }
    if (responseTLValue == TLValue::DhGenOk) {
        qCDebug(c_clientDhLayerCategory) << "Server DH answer is accepted. Setup the auth key...";
        setServerSalt(session->serverNonce.parts[0] ^ session->newNonce.parts[0]);
        m_sendHelper->setAuthKey(newAuthKey);
    } else {
        qCDebug(c_clientDhLayerCategory) << "Server DH answer is not accepted. Retry...";
        if (newAuthKey.isEmpty()) {
            m_authRetryId = 0;
        } else {
            m_authRetryId = Utils::getFingerprints(newAuthKey, Utils::Higher64Bits);
        }
        generateDh();
        requestDhGenerationResult();
    }
    return true;
}

PendingRpcOperation *DhLayer::sendPlainPackage(const QByteArray &payload)
{
    BaseDhLayer::sendPlainPackage(payload, SendMode::Client);
    m_plainOperation = new PendingRpcOperation(payload, this);
    m_plainOperation->setConnection(m_sendHelper->getConnection());
    return m_plainOperation;
}

DhSession *DhLayer::getSession()
{
    return static_cast<DhSession *>(m_session);
}

void DhLayer::processReceivedPacket(const QByteArray &payload)
{
    if (!m_plainOperation) {
        qCCritical(c_clientDhLayerCategory) << Q_FUNC_INFO << "Unexpected unencrypted message";
        return;
    }
    PendingRpcOperation *op = m_plainOperation;
    m_plainOperation = nullptr;
    op->setFinishedWithReplyData(payload);
}

} // Client

} // Telegram namespace
