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

#include "ServerDhLayer.hpp"
#include "DhSession.hpp"

#include "BaseTransport.hpp"
#include "MTProto/Stream.hpp"
#include "Debug_p.hpp"
#include "RandomGenerator.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"

#include <QDateTime>
#include <QLoggingCategory>
#include <QtEndian>

Q_LOGGING_CATEGORY(lcServerDhLayer, "telegram.server.dhlayer", QtWarningMsg)

static const QByteArray c_hardcodedDhPrime =
        QByteArray::fromHex(QByteArrayLiteral(
                                "c71caeb9c6b1c9048e6c522f70f13f73980d40238e3e21c14934d037563d930f"
                                "48198a0aa7c14058229493d22530f4dbfa336f6e0ac925139543aed44cce7c37"
                                "20fd51f69458705ac68cd4fe6b6b13abdc9746512969328454f18faf8c595f64"
                                "2477fe96bb2a941d5bcd1d4ac8cc49880708fa9b378e3c4f3a9060bee67cf9a4"
                                "a4a695811051907e162753b56b0f6b410dba74d8a84b2a14b3144e0ef1284754"
                                "fd17ed950d5965b4b9dd46582db1178d169c6bc465b0d6ff9ca3928fef5b9ae4"
                                "e418fc15e83ebea0f87fa9ff5eed70050ded2849f47bf959d956850ce929851f"
                                "0d8115f635b105ee2e4e15d04b2454bf6f4fadf034b10403119cd8e3b92fcc5b"));

namespace Telegram {

namespace Server {

class DhSession : public BaseDhSession
{
public:
    QByteArray a;
};

DhLayer::DhLayer(QObject *parent) :
    BaseDhLayer(parent)
{
}

void DhLayer::init()
{
    setState(State::Idle);
}

bool DhLayer::processRequestPQ(const QByteArray &data)
{
    MTProto::Stream inputStream(data);
    TLValue value;
    TLNumber128 clientNonce;
    inputStream >> value;
    inputStream >> clientNonce;

    switch (value) {
    case TLValue::ReqPq:
        break;
    default:
        return false;
    }

    const DhSession *session = createSession(clientNonce);
    if (!session) {
        return false;
    }

    qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << "Client nonce:" << session->clientNonce;

    return sendResultPQ(session);
}

bool DhLayer::sendResultPQ(const DhSession *session)
{
    const QVector<quint64> fingerprints = { m_rsaKey.fingerprint };
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
    qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << session->clientNonce
                             << session->serverNonce << intToBytes(session->pq)
                             << "fp:" << fingerprints << "(pq:" << session->pq << ")";
#endif
    outputStream << TLValue::ResPQ;
    outputStream << session->clientNonce;
    outputStream << session->serverNonce;
    outputStream << intToBytes(session->pq);
    outputStream << fingerprints;

    if (!sendReplyPackage(outputStream.getData())) {
        return false;
    }

    setState(State::PqReplied);
    return true;
}

bool DhLayer::processRequestDHParams(const QByteArray &data)
{
    DhSession *session = nullptr;
    QByteArray encryptedPackage;
    {
        MTProto::Stream inputStream(data);
        TLValue value;
        inputStream >> value;
        if (value != TLValue::ReqDHParams) {
            qCWarning(lcServerDhLayer) << THIS_FUNC_INFO << "Invalid request data" << value.toString();
            return false;
        }

        TLNumber128 clientNonce;
        inputStream >> clientNonce;

        session = getSession(clientNonce);
        if (!session) {
            return false;
        }

        TLNumber128 serverNonce;
        inputStream >> serverNonce;

        if (session->serverNonce != serverNonce) {
            return false;
        }
        QByteArray bigEndianNumber1;
        QByteArray bigEndianNumber2;
        quint64 fingerprint = 0;
        inputStream >> bigEndianNumber1;
        inputStream >> bigEndianNumber2;
        inputStream >> fingerprint;
        quint32 readP = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(bigEndianNumber1.constData()));
        quint32 readQ = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(bigEndianNumber2.constData()));

        if (session->p != readP) {
            qCWarning(lcServerDhLayer) << THIS_FUNC_INFO << "Invalid P";
            return false;
        }
        if (session->q != readQ) {
            qCWarning(lcServerDhLayer) << THIS_FUNC_INFO << "Invalid Q";
            return false;
        }
        if (fingerprint != m_rsaKey.fingerprint) {
            qCWarning(lcServerDhLayer) << THIS_FUNC_INFO << "Invalid server fingerprint" << fingerprint << "vs" << m_rsaKey.fingerprint;
            return false;
        }
        inputStream >> encryptedPackage;
    }

    qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << "encrypted:" << encryptedPackage.toHex();

    QByteArray decryptedPackage = Utils::binaryNumberModExp(encryptedPackage, m_rsaKey.modulus, m_rsaKey.secretExponent);
    constexpr int c_innerPackageSize = 255;
    if (decryptedPackage.size() < c_innerPackageSize) {
#if QT_VERSION < QT_VERSION_CHECK(5, 7, 0)
        decryptedPackage = QByteArray(c_innerPackageSize - decryptedPackage.size(), char(0)) + decryptedPackage;
#else
        decryptedPackage.prepend(c_innerPackageSize - decryptedPackage.size(), char(0));
#endif
    }
    qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << "Decrypted:" << decryptedPackage.toHex();

    const QByteArray sha = decryptedPackage.left(20);
    const QByteArray innerData = decryptedPackage.mid(20);
    QByteArray randomPadding;

    TLNumber256 newNonce;

    if (!processPqInnerData(innerData, session, &newNonce)) {
        return false;
    }

    prepareDhParams(session, newNonce);

    return acceptDhParams(session);
}

bool DhLayer::processPqInnerData(const QByteArray &innerData, const DhSession *session, TLNumber256 *newNonce)
{
    qCDebug(lcServerDhLayer) << __func__ << session;
    QByteArray bigEndianNumber;
    MTProto::Stream encryptedStream(innerData);
    TLValue v;
    encryptedStream >> v;
    if (v != TLValue::PQInnerData) {
        qCWarning(lcServerDhLayer) << __func__ << "Inner data does not start with PQInnerData value:" << v;
        return false;
    }

    encryptedStream >> bigEndianNumber;
    if (bigEndianNumber.size() != sizeof(session->pq)) {
        return false;
    }
    quint64 readPQ = qFromBigEndian<quint64>(reinterpret_cast<const uchar*>(bigEndianNumber.constData()));

    encryptedStream >> bigEndianNumber;
    if (bigEndianNumber.size() != sizeof(session->p)) {
        return false;
    }
    quint32 readP = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(bigEndianNumber.constData()));

    encryptedStream >> bigEndianNumber;
    if (bigEndianNumber.size() != sizeof(session->q)) {
        return false;
    }
    quint32 readQ = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(bigEndianNumber.constData()));

    if (session->pq != readPQ) {
        qCWarning(lcServerDhLayer) << __func__ << "Invalid PQ";
        return false;
    }
    if (session->p != readP) {
        qCWarning(lcServerDhLayer) << __func__ << "Invalid P";
        return false;
    }
    if (session->q != readQ) {
        qCWarning(lcServerDhLayer) << __func__ << "Invalid Q";
        return false;
    }

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    encryptedStream >> clientNonce;
    if (clientNonce != session->clientNonce) {
        qCDebug(lcServerDhLayer) << __func__
                                 << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }
    encryptedStream >> serverNonce;
    if (serverNonce != session->serverNonce) {
        qCDebug(lcServerDhLayer) << __func__
                                 << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }
    encryptedStream >> *newNonce;

    return true;
}

void DhLayer::prepareDhParams(DhSession *session, const TLNumber256 &newNonce)
{
    session->newNonce = newNonce;

    session->g = 7;
    session->dhPrime.resize(256);
    RandomGenerator::instance()->generate(&session->dhPrime);
    session->dhPrime = c_hardcodedDhPrime;

    //    if ((session()->g < 2) || (session()->g > 7)) {
    //        qCDebug(lcServerDhLayer) << "Error: 'g' number is out of acceptable range [2-7].";
    //        return nullptr;
    //    }

    //    if (session()->dhPrime.length() != 2048 / 8) {
    //        qCDebug(lcServerDhLayer) << "Error: dhPrime number length is not correct." << session()->dhPrime.length() << 2048 / 8;
    //        return nullptr;
    //    }

    //    if (!(session()->dhPrime.at(0) & 128)) {
    //        qCDebug(lcServerDhLayer) << "Error: dhPrime is too small.";
    //        return nullptr;
    //    }

    // #5 Server computes random 2048-bit number a (using a sufficient amount of entropy)
    session->a.resize(256);
    RandomGenerator::instance()->generate(&session->a);

    // IMPORTANT: Apart from the conditions on the Diffie-Hellman prime dh_prime and generator g,
    // both sides are to check that g, g_a and g_b are greater than 1 and less than dh_prime - 1.
    // We recommend checking that g_a and g_b are between 2^{2048-64} and dh_prime - 2^{2048-64} as well.

#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
    qCDebug(lcServerDhLayer) << "session->a" << session->a;
#endif

    session->gA = Utils::binaryNumberModExp(intToBytes(session->g), session->dhPrime, session->a);
    session->tmpAesKey = generateTmpAesKey(session);
}

bool DhLayer::acceptDhParams(const DhSession *session)
{
    qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << session;
    MTProto::Stream stream(MTProto::Stream::WriteOnly);
    stream << TLValue::ServerDHInnerData;
    stream << session->clientNonce;
    stream << session->serverNonce;
    stream << session->g;
    stream << session->dhPrime;
    stream << session->gA;
    const quint32 serverTime = QDateTime::currentMSecsSinceEpoch() / 1000;
    stream << serverTime;

    const QByteArray innerData = stream.getData();

    const QByteArray sha = Utils::sha1(innerData);
    QByteArray randomPadding;
    int packageLength = sha.length() + innerData.length();
    if ((packageLength) % 16) {
        randomPadding.resize(16 - (packageLength % 16));
        RandomGenerator::instance()->generate(&randomPadding);

        packageLength += randomPadding.size();
    }

    const QByteArray encryptedAnswer = Crypto::aesEncrypt(sha + innerData + randomPadding, session->tmpAesKey);

    QByteArray output;
    MTProto::Stream outputStream(&output, /* write */ true);
    outputStream << TLValue::ServerDHParamsOk;
    outputStream << session->clientNonce;
    outputStream << session->serverNonce;
    outputStream << encryptedAnswer;

    if (!sendReplyPackage(output)) {
        return false;
    }

    setState(State::DhRepliedOK);
    return true;
}

bool DhLayer::declineDhParams()
{
    return false;
}

bool DhLayer::processSetClientDHParams(const QByteArray &data)
{
    MTProto::Stream stream(data);

    TLValue value;
    stream >> value;

    if (value != TLValue::SetClientDHParams) {
        qCWarning(lcServerDhLayer) << THIS_FUNC_INFO << "Invalid request data" << value.toString();
        return false;
    }

    TLNumber128 clientNonce;
    stream >> clientNonce;

    DhSession *session = getSession(clientNonce);
    if (!session) {
        return false;
    }

    TLNumber128 serverNonce;
    stream >> serverNonce;

    if (session->serverNonce != serverNonce) {
        return false;
    }

    QByteArray encryptedPackage;
    stream >> encryptedPackage;

    const QByteArray answerWithHash = Crypto::aesDecrypt(encryptedPackage, session->tmpAesKey);
    const QByteArray sha1OfAnswer = answerWithHash.mid(0, 20);
    const QByteArray answer = answerWithHash.mid(20, 304);

    MTProto::Stream encryptedInputStream(answer);

    TLValue responseTLValue;
    encryptedInputStream >> responseTLValue;

    if (responseTLValue != TLValue::ClientDHInnerData) {
        qCDebug(lcServerDhLayer) << "Error: Unexpected TL Value in encrypted answer.";
        return false;
    }

    if (!checkClientServerNonse(encryptedInputStream)) {
        return false;
    }

    quint64 authRetryId = 0;
    encryptedInputStream >> authRetryId;
    m_authRetryId = authRetryId;

    QByteArray gB;
    encryptedInputStream >> gB;

    const QByteArray newAuthKey = Utils::binaryNumberModExp(gB, session->dhPrime, session->a);
    const QByteArray newAuthKeySha = Utils::sha1(newAuthKey);

    // answerDcGenOk
    {
        qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << "answerDcGenOk";

        QByteArray output;
        MTProto::Stream outputStream(&output, /* write */ true);

        outputStream << TLValue::DhGenOk;
        outputStream << session->clientNonce;
        outputStream << session->serverNonce;

        QByteArray expectedHashData(session->newNonce.data, session->newNonce.size());
        expectedHashData.append(newAuthKeySha.left(8));
        expectedHashData.insert(32, char(1));

        QByteArray newNonceHashLower128Array = Utils::sha1(expectedHashData).mid(4);
        TLNumber128 newNonceHashLower128;
        memcpy(newNonceHashLower128.data, newNonceHashLower128Array.constData(), TLNumber128::size());
        outputStream << newNonceHashLower128;
        sendReplyPackage(output);
#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
        qCDebug(lcServerDhLayer) << "NewNonce hash lower..." << newNonceHashLower128Array.toHex();
#endif
    }
    m_sendHelper->setAuthKey(newAuthKey);
    setServerSalt(session->serverNonce.parts[0] ^ session->newNonce.parts[0]);

    setState(State::HasKey);
    return true;
}

quint64 DhLayer::sendReplyPackage(const QByteArray &payload)
{
    return sendPlainPackage(payload, SendMode::ServerReply);
}

void DhLayer::processReceivedPacket(const QByteArray &payload)
{
    const TLValue v = TLValue::firstFromArray(payload);
    qCDebug(lcServerDhLayer) << THIS_FUNC_INFO << v.toString();
    switch (v) {
    case TLValue::ReqPq:
        if (!processRequestPQ(payload)) {
            setState(State::Failed);
        }
        break;
    case TLValue::ReqDHParams:
        if (!processRequestDHParams(payload)) {
            setState(State::Failed);
        }
        break;
    case TLValue::SetClientDHParams:
        if (!processSetClientDHParams(payload)) {
            setState(State::Failed);
        }
        break;
    default:
        break;
    }
}

DhSession *DhLayer::createSession(const TLNumber128 &clientNonce)
{
    DhSession *session = new DhSession;
    session->p = 1244159563ul;
    session->q = 1558201013ul;
    session->pq = static_cast<quint64>(session->p) * static_cast<quint64>(session->q);
    session->clientNonce = clientNonce;
    RandomGenerator::instance()->generate(session->serverNonce.data, session->serverNonce.size());

    m_session = session;
    return session;
}

DhSession *DhLayer::getSession(const TLNumber128 &clientNonce)
{
    if (m_session->clientNonce == clientNonce) {
        return static_cast<DhSession *>(m_session);
    }

    return nullptr;
}

} // Server namespace

} // Telegram namespace
