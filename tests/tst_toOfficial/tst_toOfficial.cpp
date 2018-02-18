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

#include <QObject>

#include "AccountStorage.hpp"
#include "ClientConnection.hpp"
#include "ClientDhLayer.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientSettings.hpp"
#include "CClientTcpTransport.hpp"
#include "Utils.hpp"
#include "SendPackageHelper.hpp"
#include "TelegramNamespace.hpp"
#include "TelegramUtils.hpp"
#include "CAppInformation.hpp"

#include <QTest>
#include <QSignalSpy>
#include <QLoggingCategory>

using namespace Telegram;

CAppInformation *getAppInfo()
{
    static CAppInformation *appInfo = nullptr;
    if (!appInfo) {
        appInfo = new CAppInformation();
        appInfo->setAppId(14617);
        appInfo->setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
        appInfo->setAppVersion(QLatin1String("0.1"));
        appInfo->setDeviceInfo(QLatin1String("pc"));
        appInfo->setOsInfo(QLatin1String("GNU/Linux"));
        appInfo->setLanguageCode(QLatin1String("en"));
    }
    return appInfo;
}

class tst_toOfficial : public QObject
{
    Q_OBJECT
public:
    explicit tst_toOfficial(QObject *parent = nullptr);

private slots:
    void testClientDhLayer();
};

class TestSendPackageHelper : public BaseSendPackageHelper
{
public:
    explicit TestSendPackageHelper(CTelegramTransport *transport) :
        BaseSendPackageHelper(),
        m_transport(transport)
    {
    }

    quint64 newMessageId(SendMode mode) override
    {
        quint64 ts = TelegramUtils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch());
        if (mode == SendMode::Client) {
            ts &= ~quint64(3);
        } else {
            qWarning() << Q_FUNC_INFO << "Invalid mode";
        }
        return m_transport->getNewMessageId(ts);
    }

    void sendPackage(const QByteArray &package) override
    {
        return m_transport->sendPackage(package);
    }

protected:
    CTelegramTransport *m_transport;
};

tst_toOfficial::tst_toOfficial(QObject *parent) :
    QObject(parent)
{
    QLoggingCategory::setFilterRules(QStringLiteral("telegram.*.debug=true"));
}

void tst_toOfficial::testClientDhLayer()
{
    const auto serverConfig = Client::Settings::defaultServerConfiguration();
    QVERIFY(!serverConfig.isEmpty());
    const DcOption firstServer = serverConfig.first();
    Client::TcpTransport *transport = new Client::TcpTransport(this);

    TestSendPackageHelper *sendHelper = new TestSendPackageHelper(transport);
    Client::DhLayer *dhLayer = new Client::DhLayer(this);
    dhLayer->setSendPackageHelper(sendHelper);
    dhLayer->setServerRsaKey(Utils::loadHardcodedKey());

    connect(transport, &Client::TcpTransport::packageReceived, [dhLayer](const QByteArray &package) {
        if (package.size() == sizeof(quint32)) {
            qint32 errorCode = *(reinterpret_cast<const qint32 *>(package.constData()));
            qWarning() << "Error:" << errorCode;
            return;
        }
        if (package.size() < 8) {
            qWarning() << "Received package is too small to process:" << package.toHex();
            return;
        }
        const quint64 *authKeyIdBytes = reinterpret_cast<const quint64*>(package.constData());
        if (*authKeyIdBytes) {
            qDebug() << "Received a package for RPC Layer";
//            rpcLayer->processPackage(package);
        } else {
            qDebug() << "Received a plain package for DH Layer";
            dhLayer->processPlainPackage(package);
        }
    });

    transport->connectToHost(firstServer.address, firstServer.port);
    QTRY_VERIFY(transport->state() == QAbstractSocket::ConnectedState);

    PendingRpcOperation *operationReqPq = dhLayer->requestPqAuthorization();
    QTRY_VERIFY(operationReqPq->isFinished());
    QVERIFY(operationReqPq->isSucceeded());
    QVERIFY(dhLayer->acceptPqAuthorization(operationReqPq->replyData()));

    PendingRpcOperation *operationReqDhParams = dhLayer->requestDhParameters();
    QTRY_VERIFY(operationReqDhParams->isFinished());
    QVERIFY(operationReqDhParams->isSucceeded());
    QVERIFY(dhLayer->acceptDhAnswer(operationReqDhParams->replyData()));

    dhLayer->generateDh();

    PendingRpcOperation *operationSetClientDHParams = dhLayer->requestDhGenerationResult();
    QTRY_VERIFY(operationSetClientDHParams->isFinished());
    QVERIFY(operationSetClientDHParams->isSucceeded());
    QVERIFY(dhLayer->processServerDhAnswer(operationSetClientDHParams->replyData()));
}

QTEST_GUILESS_MAIN(tst_toOfficial)

#include "tst_toOfficial.moc"
