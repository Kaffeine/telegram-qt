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

#ifndef DH_LAYER_HPP
#define DH_LAYER_HPP

#include <QObject>
#include <QtEndian>

#include "Crypto/Aes.hpp"
#include "MTProto/TLNumbers.hpp"
#include "RsaKey.hpp"

#ifdef NETWORK_LOGGING
QT_FORWARD_DECLARE_CLASS(QFile)
#endif

namespace Telegram {

namespace MTProto {

class Stream;

} // MTProto namespace

class BaseMTProtoSendHelper;
class BaseDhSession;
enum class SendMode : quint8;

class TELEGRAMQT_INTERNAL_EXPORT BaseDhLayer : public QObject
{
    Q_OBJECT
public:
    // Diffie-Hellman key exchange; https://core.telegram.org/mtproto/auth_key
    enum class State {
        // Both, Client, Server
        Idle,
                 PqRequested,                 // #1 Client sends ReqPq
                         PqReplied,           // #2 Server sends ResPq
                 PqAccepted,                  // #3 Client processes ResPQ
                 DhRequested,                 // #4 Client sends ReqDHParams with PQInnerData
                         DhRepliedOK,         // #5a Server sends ServerDHParamsOk with ServerDHInnerData
                         DhRepliedFail,       // #5b Server sends ServerDHParamsFail
                 DhGenerationResultRequested, // #6 Client sends SetClientDHParams with ClientDHInnerData)
                                              // #7, #8 Possible auth key and the key id is known to server and client
                         DhGenOk,             // #9a Server sends DhGenOk
                         DhGenRetry,          // #9b Server sends DhGenRetry
                         DhGenFail,           // #9c Server sends DhGenFail
        Failed,
        HasKey,
    };
    Q_ENUM(State)

    explicit BaseDhLayer(QObject *parent = nullptr);
    virtual void init() = 0;

    void setSendPackageHelper(BaseMTProtoSendHelper *helper);
    void setServerRsaKey(const RsaKey &key);

    // AES
    static Crypto::AesKey generateTmpAesKey(const BaseDhSession *session);

    // Helpers
    bool checkClientServerNonse(MTProto::Stream &stream) const;
    quint64 sendPlainPackage(const QByteArray &payload, SendMode mode);
    bool processPlainPackage(const QByteArray &buffer);

    quint64 serverSalt() const { return m_serverSalt; }
    void setServerSalt(const quint64 salt) { m_serverSalt = salt; }

    bool hasKey() const;
    State state() { return m_state; }

    template <typename T>
    static QByteArray intToBytes(const T value) {
        QByteArray bytes(sizeof(value), Qt::Uninitialized);
        qToBigEndian<T>(value, reinterpret_cast<uchar *>(bytes.data()));
        return bytes;
    }

signals:
    void stateChanged(State newState);

protected:
    virtual void processReceivedPacket(const QByteArray &payload) = 0;

    void setState(State state);

    BaseMTProtoSendHelper *m_sendHelper = nullptr;
    BaseDhSession *m_session = nullptr;

    RsaKey m_rsaKey;

    State m_state = State::Idle;

    quint64 m_authRetryId = 0;
    quint64 m_serverSalt = 0;

#ifdef NETWORK_LOGGING
    QFile *getLogFile();
    QFile *m_logFile = nullptr;
#endif
};

} // Telegram namespace

#endif // DH_LAYER_HPP
