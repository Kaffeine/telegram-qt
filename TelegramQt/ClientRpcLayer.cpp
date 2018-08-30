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

#include "ClientRpcLayer.hpp"
#include "SendPackageHelper.hpp"
#include "CTelegramStream.hpp"
#include "Utils.hpp"
#include "Debug_p.hpp"
#include "CAppInformation.hpp"
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcLayerCategory, "telegram.client.rpclayer", QtWarningMsg)

namespace Telegram {

namespace Client {

RpcLayer::RpcLayer(QObject *parent) :
    BaseRpcLayer(parent)
{
}

void RpcLayer::setAppInformation(CAppInformation *appInfo)
{
    m_appInfo = appInfo;
}

void RpcLayer::setSessionId(quint64 newSessionId)
{
    m_sessionId = newSessionId;
}

bool RpcLayer::processRpcQuery(const QByteArray &data)
{
    CTelegramStream stream(data);
    TLValue value;
    stream >> value;
    switch (value) {
    case TLValue::NewSessionCreated:
        qCDebug(c_clientRpcLayerCategory) << "processSessionCreated(stream)";
        break;
    case TLValue::MsgContainer:
        qCDebug(c_clientRpcLayerCategory) << "processContainer(stream);";
        break;
    case TLValue::RpcResult:
        qCDebug(c_clientRpcLayerCategory) << "processRpcQuery(stream);";
    {
        quint64 messageId = 0;
        stream >> messageId;
        PendingRpcOperation *op = m_operations.value(messageId);
        if (!op) {
            qCWarning(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Unhandled operation" << messageId;
            return false;
        }
        op->setFinishedWithReplyData(stream.readAll());
#define DUMP_CLIENT_RPC_PACKETS
#ifdef DUMP_CLIENT_RPC_PACKETS
        qCDebug(c_clientRpcLayerCategory) << "Client: Answer for message" << messageId << "op:" << op;
        qCDebug(c_clientRpcLayerCategory).noquote() << "Client: RPC Reply bytes:" << op->replyData().size() << op->replyData().toHex();
#endif
        qCWarning(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Set finished op" << op << "messageId:" << messageId << "error:" << op->errorDetails();
    }
        break;
    case TLValue::MsgsAck:
        qCDebug(c_clientRpcLayerCategory) << "processMessageAck(stream);";
        break;
    case TLValue::BadMsgNotification:
    case TLValue::BadServerSalt:
        qCDebug(c_clientRpcLayerCategory) << "processIgnoredMessageNotification(stream);";
        break;
    case TLValue::GzipPacked:
        qCDebug(c_clientRpcLayerCategory) << "processGzipPackedRpcQuery(stream);";
        break;
    case TLValue::Pong:
        qCDebug(c_clientRpcLayerCategory) << "processPingPong(stream);";
        break;
    default:
        qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "value:" << value;
        break;
    }
    return false;
}

bool RpcLayer::processDecryptedPackage(const QByteArray &decryptedData)
{
//    qWarning() << Q_FUNC_INFO << "Innerdata:" << decryptedData.toHex();
//    qWarning() << Q_FUNC_INFO << "key:" << messageKey.toHex();

    CRawStream decryptedStream(decryptedData);
    quint64 sessionId = 0;
    quint64 messageId  = 0;
    quint32 sequence = 0;
    quint32 contentLength = 0;
    decryptedStream >> m_receivedServerSalt;
    decryptedStream >> sessionId;
    decryptedStream >> messageId;
    decryptedStream >> sequence;
    decryptedStream >> contentLength;

    if (m_sendHelper->serverSalt() != m_receivedServerSalt) {
        qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Received different server salt:" << m_receivedServerSalt << "(remote) vs" << m_sendHelper->serverSalt() << "(local)";
        //            return;
    }

    if (m_sessionId != sessionId) {
        qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Session Id is wrong.";
        return false;
    }

    if (int(contentLength) > decryptedData.length()) {
        qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Expected data length is more, than actual.";
        return false;
    }

    const int headerLength = sizeof(m_receivedServerSalt) + sizeof(sessionId) + sizeof(messageId) + sizeof(sequence) + sizeof(contentLength);
    QByteArray expectedMessageKey = Utils::sha1(decryptedData.left(headerLength + contentLength)).mid(4);

    const QByteArray messageKey = expectedMessageKey;
    if (messageKey != expectedMessageKey) {
        qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Wrong message key";
        return false;
    }

    QByteArray payload = decryptedStream.readAll();

    processRpcQuery(payload);

#ifdef DEVELOPER_BUILD
    static int packagesCount = 0;
    qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Got package" << ++packagesCount << TLValue::firstFromArray(payload);
#endif
    return true;
}

bool RpcLayer::sendRpc(PendingRpcOperation *operation)
{
    quint64 messageId = 0;
    // We have to add InitConnection here because sendPackage() implementation is shared with server
    if (m_sequenceNumber == 0) {
        // sendPackage() adjusts sequence number
        messageId = sendPackage(getInitConnection() + operation->requestData(), SendMode::Client);
    } else {
        messageId = sendPackage(operation->requestData(), SendMode::Client);
    }
    if (!messageId) {
        return false;
    }
    operation->setRequestId(messageId);
    operation->setConnection(m_sendHelper->getConnection());
    m_operations.insert(messageId, operation);
    return true;
}

QByteArray RpcLayer::getInitConnection() const
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "layer" << TLValue::CurrentLayer;
#endif
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::InvokeWithLayer;
    outputStream << TLValue::CurrentLayer;
    outputStream << TLValue::InitConnection;
    outputStream << m_appInfo->appId();
    outputStream << m_appInfo->deviceInfo();
    outputStream << m_appInfo->osInfo();
    outputStream << m_appInfo->appVersion();
#if TELEGRAMQT_LAYER >= 67
    outputStream << m_appInfo->languageCode(); // System language
    outputStream << QString(); // Langpack
#endif
    outputStream << m_appInfo->languageCode(); // Lang code
    return outputStream.getData();
}

} // Client namespace

} // Telegram namespace
