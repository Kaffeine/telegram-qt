/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#include <QObject>

#include "RandomGenerator.hpp"
#include "RpcLayer.hpp"
#include "SendPackageHelper.hpp"
#include "TelegramNamespace.hpp"
#include "CTelegramTransport.hpp"
#include "../utils/TestTransport.hpp"

#include "MTProto/MessageHeader.hpp"

#include <QTest>
#include <QDebug>
#include <QSignalSpy>

namespace Telegram {

namespace Test {

class MTProtoSendHelper : public BaseMTProtoSendHelper
{
public:
    explicit MTProtoSendHelper(BaseTransport *transport) :
        BaseMTProtoSendHelper(),
        m_transport(transport)
    {
    }

    quint64 newMessageId(SendMode mode) override
    {
        quint64 ts = m_ts;
        if (mode == SendMode::Client) {
            ts &= ~quint64(3);
        } else if (mode == SendMode::ServerReply) {
            ts &= ~quint64(3);
            ts |= 1;
        } else if (mode == SendMode::ServerInitiative) {
            ts |= 3;
        }
        return m_transport->getNewMessageId(ts);
    }

    void sendPacket(const QByteArray &package) override
    {
        return m_transport->sendPacket(package);
    }

    void setBaseTimestamp(quint64 ts) { m_ts = ts; qDebug() << ts; }

protected:
    BaseTransport *m_transport = nullptr;
    quint64 m_ts = 0;
};

class RpcLayer : public BaseRpcLayer
{
    Q_OBJECT
public:
    enum class Mode {
        Server,
        Client,
    };

    RpcLayer(Mode mode) :
        BaseRpcLayer(),
        m_mode(mode)
    {
        m_transport = new Transport(this);
        m_sendHelper = new MTProtoSendHelper(m_transport);
        m_sendHelper->setBaseTimestamp(1537207803787ull);
        setSessionId(123456789ull);

        setSendHelper(m_sendHelper);
    }
    ~RpcLayer() override
    {
        delete m_sendHelper;
    }

    Transport *transport() { return m_transport; }
    MTProtoSendHelper *sendHelper() { return m_sendHelper; }

    quint64 serverSalt() const override { return 3720780378715ull; }
    quint64 sessionId() const override { return m_sessionId; }
    void setSessionId(quint64 id) { m_sessionId = id; }

    MTProto::Message lastProcessedMessage() const { return m_lastProcessedMessage; }

    bool processMessageHeader(const MTProto::FullMessageHeader &) override { return true; }
    bool processMTProtoMessage(const MTProto::Message &message) override { m_lastProcessedMessage = message; return false; }

protected:
    Crypto::AesKey getEncryptionAesKey(const QByteArray &messageKey) const final
    {
        return m_mode == Mode::Client ? generateClientToServerAesKey(messageKey) : generateServerToClientAesKey(messageKey);
    }

    Crypto::AesKey getDecryptionAesKey(const QByteArray &messageKey) const final
    {
        return m_mode == Mode::Client ? generateServerToClientAesKey(messageKey) : generateClientToServerAesKey(messageKey);
    }

    QByteArray getEncryptionKeyPart() const override;
    QByteArray getVerificationKeyPart() const override;

    Mode m_mode;
    quint64 m_sessionId = 0;
    Transport *m_transport = nullptr;
    MTProtoSendHelper *m_sendHelper = nullptr;
    MTProto::Message m_lastProcessedMessage;
};

QByteArray RpcLayer::getEncryptionKeyPart() const
{
    if (m_mode == Mode::Client) {
        return m_sendHelper->getClientKeyPart();
    }
    return m_sendHelper->getServerKeyPart();
}

QByteArray RpcLayer::getVerificationKeyPart() const
{
    if (m_mode == Mode::Client) {
        return m_sendHelper->getServerKeyPart();
    }
    return m_sendHelper->getClientKeyPart();
}

class ClientRpcLayer : public RpcLayer
{
    Q_OBJECT
public:
    ClientRpcLayer() : RpcLayer(Mode::Client) { }

    quint64 sendPackageAsClient(const QByteArray &buffer)
    {
        return sendPacket(buffer, SendMode::Client, MessageType::ContentRelatedMessage);
    }
};

class ServerRpcLayer : public RpcLayer
{
    Q_OBJECT
public:
    ServerRpcLayer() : RpcLayer(Mode::Server) { }

    quint64 sendPackageAsServerReply(const QByteArray &buffer)
    {
        return sendPacket(buffer, SendMode::ServerReply, MessageType::ContentRelatedMessage);
    }

    quint64 sendPackageAsServerInitiative(const QByteArray &buffer)
    {
        return sendPacket(buffer, SendMode::ServerInitiative, MessageType::ContentRelatedMessage);
    }
};

} // Test

} // Telegram

const QByteArray c_authKey = QByteArrayLiteral("some_auth_key_data_123456789_abcdefghijklmnopqrstuvwxyz");

class tst_RpcLayer : public QObject
{
    Q_OBJECT
public:
    explicit tst_RpcLayer(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void sendClientRequest();
    void sendServerReply();
    void processServerReply();

private:
    Telegram::DeterministicGenerator *m_generator = nullptr;
    Telegram::RandomGenerator *m_defaultGenerator = nullptr;

};

tst_RpcLayer::tst_RpcLayer(QObject *parent) :
    QObject(parent)
{
}

void tst_RpcLayer::initTestCase()
{
    Telegram::initialize();
    m_generator = new Telegram::DeterministicGenerator();
    m_defaultGenerator = Telegram::RandomGenerator::setInstance(m_generator);
}

void tst_RpcLayer::cleanupTestCase()
{
    Telegram::RandomGenerator::setInstance(m_defaultGenerator);
    delete m_generator;
}

static QByteArray c_clientRequestPackage = QByteArray::fromHex(
            "bedc61e0992109d063a1f98c0d0f57ff"
            "4868d3145dbe2fcf638b6c050afec4f6"
            "c278d6d2c7ca4d8322ca221056c2c07d"
            "cb3cb1b5c79b7474371e17e1219fb122"
            "8a3911239a3e56c8"
            );

static QByteArray c_serverReplyPackage = QByteArray::fromHex(
            "bedc61e0992109d093da43763734e845"
            "5d31822f4eca12a0760482e73e4ff85a"
            "5f09986b3b0d5b545b2a7f01ce463cc2"
            "09ed6666f78ed25de96ecd208e01dec8"
            "3519bc6ba42c4395"
            );

void tst_RpcLayer::sendClientRequest()
{
    QByteArray data = QByteArrayLiteral("abcd");
    Telegram::Test::ClientRpcLayer rpcLayer;
    QSignalSpy sentPackagesSpy(rpcLayer.transport(), &Telegram::Test::Transport::packetSent);
    rpcLayer.sendHelper()->setAuthKey(c_authKey);
    rpcLayer.sendPackageAsClient(data);
    QCOMPARE(sentPackagesSpy.count(), 1);
    QByteArray sentPackage = sentPackagesSpy.takeFirst().first().toByteArray();
    QCOMPARE(sentPackage.size(), 72);
    QCOMPARE(sentPackage.toHex(), c_clientRequestPackage.toHex());
}

void tst_RpcLayer::sendServerReply()
{
    QByteArray data = QByteArrayLiteral("abcd");

    Telegram::Test::ServerRpcLayer rpcLayer;
    QSignalSpy sentPackagesSpy(rpcLayer.transport(), &Telegram::Test::Transport::packetSent);
    rpcLayer.sendHelper()->setAuthKey(c_authKey);
    rpcLayer.sendPackageAsServerReply(data);
    QCOMPARE(sentPackagesSpy.count(), 1);
    QByteArray sentPackage = sentPackagesSpy.takeFirst().first().toByteArray();
    QCOMPARE(sentPackage.size(), 72);
    QCOMPARE(sentPackage.toHex(), c_serverReplyPackage.toHex());
}

void tst_RpcLayer::processServerReply()
{
    QByteArray data = QByteArrayLiteral("abcd");

    Telegram::Test::ClientRpcLayer rpcLayer;
    rpcLayer.sendHelper()->setAuthKey(c_authKey);
    rpcLayer.processPacket(c_serverReplyPackage);

    Telegram::MTProto::Message m = rpcLayer.lastProcessedMessage();
    QCOMPARE(m.data, data);
}

QTEST_APPLESS_MAIN(tst_RpcLayer)

#include "tst_RpcLayer.moc"
