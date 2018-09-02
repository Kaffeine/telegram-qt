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

#include "CTelegramStream.hpp"
#include "CTelegramTransport.hpp"
#include "Utils.hpp"
#include "SendPackageHelper.hpp"
#include "TelegramUtils.hpp"
#include "Debug_p.hpp"

#include <QDateTime>
#include <QLoggingCategory>
#include <QtEndian>

Q_LOGGING_CATEGORY(c_serverDhLayerCategory, "telegram.server.dhlayer", QtWarningMsg)

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

DhLayer::DhLayer(QObject *parent) :
    BaseDhLayer(parent)
{
    m_p = 1244159563ul;
    m_q = 1558201013ul;
    m_pq = static_cast<quint64>(m_p) * static_cast<quint64>(m_q);
}

void DhLayer::init()
{
    setState(State::Idle);
}

bool DhLayer::processRequestPQ(const QByteArray &data)
{
    CTelegramStream inputStream(data);
    TLValue value;
    inputStream >> value;
    inputStream >> m_clientNonce;
    if (value != TLValue::ReqPq) {
        return false;
    }
    qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "Client nonce:" << m_clientNonce;
    return true;
}

bool DhLayer::sendResultPQ()
{
    Utils::randomBytes(m_serverNonce.data, m_serverNonce.size());
    const TLVector<quint64> fingerprints = { m_rsaKey.fingerprint };
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
//    qCDebug(c_serverDhLayerCategory) << "Write data:" << m_clientNonce << m_serverNonce << pqAsByteArray.toHex() << "fp:" << fingerprints << "(pq:" << m_pq << ")";
    outputStream << TLValue::ResPQ;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;
    outputStream << intToBytes(m_pq);
    outputStream << fingerprints;
//    qCDebug(c_serverDhLayerCategory) << "Wrote data:" << output.toHex();
    return sendReplyPackage(output);
}

bool DhLayer::processRequestDHParams(const QByteArray &data)
{
    QByteArray encryptedPackage;
    {
        CTelegramStream inputStream(data);
        TLValue value;
        inputStream >> value;
        if (value != TLValue::ReqDHParams) {
            qCWarning(c_serverDhLayerCategory) << Q_FUNC_INFO << "Invalid request data" << value.toString();
            return false;
        }
        if (!checkClientServerNonse(inputStream)) {
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

        if (m_p != readP) {
            qCWarning(c_serverDhLayerCategory) << Q_FUNC_INFO << "Invalid P";
            return false;
        }
        if (m_q != readQ) {
            qCWarning(c_serverDhLayerCategory) << Q_FUNC_INFO << "Invalid Q";
            return false;
        }
        if (fingerprint != m_rsaKey.fingerprint) {
            qCWarning(c_serverDhLayerCategory) << Q_FUNC_INFO << "Invalid server fingerprint" << fingerprint << "vs" << m_rsaKey.fingerprint;
            return false;
        }
        inputStream >> encryptedPackage;
    }

    qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "encrypted:" << encryptedPackage.toHex();

    QByteArray decryptedPackage = Utils::binaryNumberModExp(encryptedPackage, m_rsaKey.modulus, m_rsaKey.secretExponent);
    constexpr int c_innerPackageSize = 255;
    if (decryptedPackage.size() < c_innerPackageSize) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
        decryptedPackage.prepend(c_innerPackageSize - decryptedPackage.size(), char(0));
#else
        decryptedPackage = QByteArray(c_innerPackageSize - decryptedPackage.size(), char(0)) + decryptedPackage;
#endif
    }
    qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "Decrypted:" << decryptedPackage.toHex();

    const QByteArray sha = decryptedPackage.left(20);
    const QByteArray innerData = decryptedPackage.mid(20);
    QByteArray randomPadding;

    {
        QByteArray bigEndianNumber;
//        QByteArray innerData;
        CTelegramStream encryptedStream(innerData);
        TLValue v;
        encryptedStream >> v;
        if (v != TLValue::PQInnerData) {
            qCWarning(c_serverDhLayerCategory) << Q_FUNC_INFO << "Inner data does not start with PQInnerData value:" << v;
            return false;
        }
        qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "Read inner data";

        encryptedStream >> bigEndianNumber;
        if (bigEndianNumber.size() != sizeof(m_pq)) {
            return false;
        }
        m_pq = qFromBigEndian<quint64>(reinterpret_cast<const uchar*>(bigEndianNumber.constData()));

        encryptedStream >> bigEndianNumber;
        if (bigEndianNumber.size() != sizeof(m_p)) {
            return false;
        }
        m_p = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(bigEndianNumber.constData()));

        encryptedStream >> bigEndianNumber;
        if (bigEndianNumber.size() != sizeof(m_q)) {
            return false;
        }
        m_q = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(bigEndianNumber.constData()));

        TLNumber128 clientNonce;
        TLNumber128 serverNonce;
        TLNumber256 newNonce;

        encryptedStream >> clientNonce;
        if (clientNonce != m_clientNonce) {
            qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "Error: Client nonce in incoming package is different from our own.";
            return false;
        }
        encryptedStream >> serverNonce;
        if (serverNonce != m_serverNonce) {
            qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "Error: Client nonce in incoming package is different from our own.";
            return false;
        }
        encryptedStream >> newNonce;
        m_newNonce = newNonce;
    }
    return true;
}

bool DhLayer::acceptDhParams()
{
    qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO;
    m_g = 7;
    m_dhPrime.resize(256);
    Utils::randomBytes(&m_dhPrime);
    m_dhPrime = c_hardcodedDhPrime;

    //    if ((m_g < 2) || (m_g > 7)) {
    //        qCDebug(c_serverDhLayerCategory) << "Error: 'g' number is out of acceptable range [2-7].";
    //        return nullptr;
    //    }

    //    if (m_dhPrime.length() != 2048 / 8) {
    //        qCDebug(c_serverDhLayerCategory) << "Error: dhPrime number length is not correct." << m_dhPrime.length() << 2048 / 8;
    //        return nullptr;
    //    }

    //    if (!(m_dhPrime.at(0) & 128)) {
    //        qCDebug(c_serverDhLayerCategory) << "Error: dhPrime is too small.";
    //        return nullptr;
    //    }

    // #5 Server computes random 2048-bit number a (using a sufficient amount of entropy)
    m_a.resize(256);
    Utils::randomBytes(&m_a);

    // IMPORTANT: Apart from the conditions on the Diffie-Hellman prime dh_prime and generator g,
    // both sides are to check that g, g_a and g_b are greater than 1 and less than dh_prime - 1.
    // We recommend checking that g_a and g_b are between 2^{2048-64} and dh_prime - 2^{2048-64} as well.

#ifdef TELEGRAMQT_DEBUG_REVEAL_SECRETS
    qCDebug(c_serverDhLayerCategory) << "m_b" << m_a;
#endif

    m_gA = Utils::binaryNumberModExp(intToBytes(m_g), m_dhPrime, m_a);

    const QByteArray innerData = [this](){
        QByteArray data;
        CTelegramStream stream(&data, /* write */ true);
        stream << TLValue::ServerDHInnerData;
        stream << m_clientNonce;
        stream << m_serverNonce;
        stream << m_g;
        stream << m_dhPrime;
        stream << m_gA;
        const quint32 serverTime = QDateTime::currentMSecsSinceEpoch() / 1000;
        stream << serverTime;
        return data;
    }();
    m_tmpAesKey = generateTmpAesKey();
    const QByteArray sha = Utils::sha1(innerData);
    QByteArray randomPadding;
    int packageLength = sha.length() + innerData.length();
    if ((packageLength) % 16) {
        randomPadding.resize(16 - (packageLength % 16));
        Utils::randomBytes(&randomPadding);

        packageLength += randomPadding.size();
    }

    const QByteArray encryptedAnswer = Utils::aesEncrypt(sha + innerData + randomPadding, m_tmpAesKey);

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);
    outputStream << TLValue::ServerDHParamsOk;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;
    outputStream << encryptedAnswer;
    return sendReplyPackage(output);
}

bool DhLayer::declineDhParams()
{
    return false;
}

bool DhLayer::processSetClientDHParams(const QByteArray &data)
{
    CTelegramStream stream(data);

    TLValue value;
    stream >> value;

    if (value != TLValue::SetClientDHParams) {
        qCWarning(c_serverDhLayerCategory) << Q_FUNC_INFO << "Invalid request data" << value.toString();
        return false;
    }

    if (!checkClientServerNonse(stream)) {
        return false;
    }

    QByteArray encryptedPackage;
    stream >> encryptedPackage;

    const QByteArray answerWithHash = Utils::aesDecrypt(encryptedPackage, m_tmpAesKey);
    const QByteArray sha1OfAnswer = answerWithHash.mid(0, 20);
    const QByteArray answer = answerWithHash.mid(20, 304);

    CTelegramStream encryptedInputStream(answer);

    TLValue responseTLValue;
    encryptedInputStream >> responseTLValue;

    if (responseTLValue != TLValue::ClientDHInnerData) {
        qCDebug(c_serverDhLayerCategory) << "Error: Unexpected TL Value in encrypted answer.";
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

    const QByteArray newAuthKey = Utils::binaryNumberModExp(gB, m_dhPrime, m_a);
    const QByteArray newAuthKeySha = Utils::sha1(newAuthKey);

    // answerDcGenOk
    {
        qCDebug(c_serverDhLayerCategory) << Q_FUNC_INFO << "answerDcGenOk";

        QByteArray output;
        CTelegramStream outputStream(&output, /* write */ true);

        outputStream << TLValue::DhGenOk;
        outputStream << m_clientNonce;
        outputStream << m_serverNonce;

        QByteArray expectedHashData(m_newNonce.data, m_newNonce.size());
        expectedHashData.append(newAuthKeySha.left(8));
        expectedHashData.insert(32, char(1));

        QByteArray newNonceHashLower128Array = Utils::sha1(expectedHashData).mid(4);
        TLNumber128 newNonceHashLower128;
        memcpy(newNonceHashLower128.data, newNonceHashLower128Array.constData(), TLNumber128::size());
        outputStream << newNonceHashLower128;
        sendReplyPackage(output);
        qCDebug(c_serverDhLayerCategory) << "NewNonce hash lower..." << newNonceHashLower128Array.toHex();
    }
    m_sendHelper->setAuthKey(newAuthKey);
    m_sendHelper->setServerSalt(m_serverNonce.parts[0] ^ m_newNonce.parts[0]);
    return true;
}

quint64 DhLayer::sendReplyPackage(const QByteArray &payload)
{
    return sendPlainPackage(payload, SendMode::ServerReply);
}

void DhLayer::processReceivedPacket(const QByteArray &payload)
{
    TLValue v = TLValue::firstFromArray(payload);
    switch (v) {
    case TLValue::ReqPq:
        if (!processRequestPQ(payload)) {
            setState(State::Failed);
            return;
        }
        sendResultPQ();
        setState(State::PqReplied);
        break;
    case TLValue::ReqDHParams:
        if (!processRequestDHParams(payload)) {
            setState(State::Failed);
            return;
        }
        acceptDhParams();
        setState(State::DhRepliedOK);
        break;
    case TLValue::SetClientDHParams:
        if (!processSetClientDHParams(payload)) {
            setState(State::Failed);
            return;
        }
        setState(State::HasKey);
        break;
    default:
        break;
    }
}

} // Server

} // Telegram
