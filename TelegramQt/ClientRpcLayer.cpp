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
#include "ClientRpcUpdatesLayer.hpp"
#include "IgnoredMessageNotification.hpp"
#include "SendPackageHelper.hpp"
#include "Debug_p.hpp"
#include "CAppInformation.hpp"
#include "PendingRpcOperation.hpp"
#include "RandomGenerator.hpp"
#include "UpdatesLayer.hpp"

#include "MTProto/MessageHeader.hpp"
#include "MTProto/Stream.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcLayerCategory, "telegram.client.rpclayer", QtWarningMsg)
Q_LOGGING_CATEGORY(c_clientRpcDumpPackageCategory, "telegram.client.rpclayer.dump", QtWarningMsg)

namespace Telegram {

namespace Client {

RpcLayer::RpcLayer(QObject *parent) :
    BaseRpcLayer(parent)
{
}

void RpcLayer::setAppInformation(AppInformation *appInfo)
{
    m_appInfo = appInfo;
}

void RpcLayer::installUpdatesHandler(UpdatesInternalApi *updatesHandler)
{
    m_UpdatesInternalApi = updatesHandler;
}

void RpcLayer::setSessionData(quint64 sessionId, quint32 contentRelatedMessagesNumber)
{
    m_sessionId = sessionId;
    m_contentRelatedMessages = contentRelatedMessagesNumber;
}

void RpcLayer::setServerSalt(quint64 serverSalt)
{
    m_serverSalt = serverSalt;
}

void RpcLayer::startNewSession()
{
    m_sessionId = RandomGenerator::instance()->generate<quint64>();
    m_contentRelatedMessages = 0;
}

bool RpcLayer::processMTProtoMessage(const MTProto::Message &message)
{
    if (message.sequenceNumber & 1) {
        addMessageToAck(message.messageId);
    }

    const TLValue firstValue = message.firstValue();
    if (firstValue.isTypeOf<TLUpdates>()) {
        return processUpdates(message);
    }

    bool result = false;

    switch (firstValue) {
    case TLValue::NewSessionCreated:
        result = processSessionCreated(message.skipTLValue());
        break;
    case TLValue::MsgContainer:
        result = processMsgContainer(message.skipTLValue());
        break;
    case TLValue::RpcResult:
        result = processRpcResult(message.skipTLValue());
        break;
    case TLValue::MsgsAck:
        qCDebug(c_clientRpcLayerCategory) << "processMessageAck(stream);";
        break;
    case TLValue::BadMsgNotification:
    case TLValue::BadServerSalt:
        result = processIgnoredMessageNotification(message);
        break;
    case TLValue::GzipPacked:
        qCWarning(c_clientRpcLayerCategory) << CALL_INFO
                                            << "GzipPacked should be processed in the base class";
        break;
    case TLValue::Pong:
    {
        MTProto::Stream stream(message.data);
        TLPong pong;
        stream >> pong;
        PendingRpcOperation *op = m_operations.take(pong.msgId);
        if (op) {
            op->setFinishedWithReplyData(message.data);
            result = true;
        } else {
            qCWarning(c_clientRpcLayerCategory) << "Unexpected pong?!" << pong.msgId << pong.pingId;
        }
    }
        break;
    default:
        qCDebug(c_clientRpcLayerCategory) << Q_FUNC_INFO << "value:" << message.firstValue();
        break;
    }

    return result;
}

bool RpcLayer::processRpcResult(const MTProto::Message &message)
{
    qCDebug(c_clientRpcLayerCategory) << "processRpcQuery(stream);";
    MTProto::Stream stream(message.data);
    quint64 messageId = 0;
    stream >> messageId;
    PendingRpcOperation *op = m_operations.take(messageId);
    if (!op) {
        qCWarning(c_clientRpcLayerCategory) << "processRpcQuery():"
                                            << "Unhandled RPC result for messageId"
                                            << hex << showbase << messageId;
        return false;
    }
    op->setFinishedWithReplyData(stream.readAll());
#define DUMP_CLIENT_RPC_PACKETS
#ifdef DUMP_CLIENT_RPC_PACKETS
    qCDebug(c_clientRpcLayerCategory) << "Client: Answer for message"
                                      << messageId << "op:" << op;
    qCDebug(c_clientRpcLayerCategory).noquote() << "Client: RPC Reply bytes:"
                                                << op->replyData().size() << op->replyData().toHex();
#endif
    qCDebug(c_clientRpcLayerCategory) << "processRpcQuery():" << "Set finished op" << op
                                      << "messageId:" << hex << showbase << messageId
                                      << "error:" << op->errorDetails();
    return true;
}

bool RpcLayer::processUpdates(const MTProto::Message &message)
{
    qCDebug(c_clientRpcLayerCategory) << "processUpdates()" << message.firstValue();
    MTProto::Stream stream(message.data);

    TLUpdates updates;
    stream >> updates;
    return m_UpdatesInternalApi->processUpdates(updates);
}

bool RpcLayer::processSessionCreated(const MTProto::Message &message)
{
    MTProto::Stream stream(message.data);
    // https://core.telegram.org/mtproto/service_messages#new-session-creation-notification
    quint64 firstMsgId;
    quint64 uniqueId;
    quint64 serverSalt;

    stream >> firstMsgId;
    stream >> uniqueId;
    stream >> serverSalt;
    qCDebug(c_clientRpcLayerCategory) << "processSessionCreated(stream) {"
                                      << hex << showbase
                                      << "    firstMsgId:" << firstMsgId
                                      << "    uniqueId:" << uniqueId
                                      << "    serverSalt:" << serverSalt;

    return true;
}

bool RpcLayer::processIgnoredMessageNotification(const MTProto::Message &message)
{
    MTProto::Stream stream(message.data);
    TLBadMsgNotification tlNotification;
    stream >> tlNotification;
    // https://core.telegram.org/mtproto/service_messages_about_messages#notice-of-ignored-error-message
    MTProto::IgnoredMessageNotification notification(tlNotification);
    qCDebug(c_clientRpcLayerCategory) << CALL_INFO << notification.toString();

    MTProto::Message *m = m_messages.value(notification.messageId);
    if (!m) {
        qCWarning(c_clientRpcLayerCategory) << CALL_INFO
                                            << notification.toString() << "for unknown message id"
                                            << hex << showbase << notification.messageId;
        return false;
    }

    switch (notification.errorCode) {
    case MTProto::IgnoredMessageNotification::IncorrectServerSalt:
        // We sync local serverSalt value in processDecryptedMessageHeader().
        // Resend message will automatically apply the new salt
        return resendIgnoredMessage(notification.messageId);
    case MTProto::IgnoredMessageNotification::MessageIdTooOld:
        return resendIgnoredMessage(notification.messageId);
    case MTProto::IgnoredMessageNotification::SequenceNumberTooHigh:
        qCDebug(c_clientRpcLayerCategory) << "processIgnoredMessageNotification(SequenceNumberTooHigh):"
                                             " reduce seq num"
                                          << hex << showbase
                                          << " from" << m->sequenceNumber
                                          << " to" << (m->sequenceNumber - 2);
        m->sequenceNumber -= 2;
        return resendIgnoredMessage(notification.messageId);
    case MTProto::IgnoredMessageNotification::SequenceNumberTooLow:
        qCDebug(c_clientRpcLayerCategory) << "processIgnoredMessageNotification(SequenceNumberTooLow):"
                                             " increase seq num"
                                          << hex << showbase
                                          << " from" << m->sequenceNumber
                                          << " to" << (m->sequenceNumber + 2);
        m->sequenceNumber += 2;
    {
        quint32 messageContentNumber = m->sequenceNumber / 2;
        if (m_contentRelatedMessages <= messageContentNumber) {
            m_contentRelatedMessages = messageContentNumber + 1;
        }
    }
        return resendIgnoredMessage(notification.messageId);
    case MTProto::IgnoredMessageNotification::IncorrectTwoLowerOrderMessageIdBits:
        qCCritical(c_clientRpcLayerCategory) << "How we ever managed to mess with"
                                                " the lower messageId bytes?!";
        // Just resend the message. We regenerate message id, so it can help.
        return resendIgnoredMessage(notification.messageId);
    default:
        break;
    }

    qCWarning(c_clientRpcLayerCategory) << "Unhandled error:" << notification.toString();
    return false;
}

bool RpcLayer::processDecryptedMessageHeader(const MTProto::FullMessageHeader &header)
{
    if (serverSalt() != header.serverSalt) {
        qCDebug(c_clientRpcLayerCategory).noquote()
                << QStringLiteral("Received different server salt: %1 (remote) vs %2 (local)."
                                  " Fix local to remote.")
                   .arg(toHex(header.serverSalt))
                   .arg(toHex(serverSalt()));
        setServerSalt(header.serverSalt);
    }

    if (m_sessionId != header.sessionId) {
        qCWarning(c_clientRpcLayerCategory) << Q_FUNC_INFO << "Session Id is wrong.";
        return false;
    }
    return true;
}

QByteArray RpcLayer::getEncryptionKeyPart() const
{
    return m_sendHelper->getClientKeyPart();
}

QByteArray RpcLayer::getVerificationKeyPart() const
{
    return m_sendHelper->getServerKeyPart();
}

quint64 RpcLayer::sendRpc(PendingRpcOperation *operation)
{
    operation->setConnection(m_sendHelper->getConnection());

    MTProto::Message *message = new MTProto::Message();
    message->messageId = m_sendHelper->newMessageId(SendMode::Client);
    if (operation->isContentRelated()) {
        if (m_contentRelatedMessages == 0) {
            qCCritical(c_clientRpcLayerCategory) << CALL_INFO
                                                 << "First message should be content related!";
        }
        message->sequenceNumber = m_contentRelatedMessages * 2 + 1;
        ++m_contentRelatedMessages;
    } else {
        message->sequenceNumber = m_contentRelatedMessages * 2;
    }

    // We have to add InitConnection here because
    // sendPackage() implementation is shared with server
    if (message->sequenceNumber == 1) {
        message->setData(getInitConnection() + operation->requestData());
    } else {
        message->setData(operation->requestData());
    }
    m_operations.insert(message->messageId, operation);
    m_messages.insert(message->messageId, message);
    sendPackage(*message);
    return message->messageId;
}

bool RpcLayer::resendIgnoredMessage(quint64 messageId)
{
    MTProto::Message *message = m_messages.take(messageId);
    PendingRpcOperation *operation = m_operations.take(messageId);
    if (!operation) {
        qCCritical(c_clientRpcLayerCategory) << CALL_INFO
                                             << "Unable to find the message to resend"
                                             << hex << messageId;
        delete message;
        return false;
    }
    qCDebug(c_clientRpcLayerCategory) << "Resend message"
                                      << hex << messageId
                                      << message->firstValue();
    message->messageId = m_sendHelper->newMessageId(SendMode::Client);
    m_operations.insert(message->messageId, operation);
    m_messages.insert(message->messageId, message);
    sendPackage(*message);
    emit operation->resent(messageId, message->messageId);
    return message->messageId;
}

void RpcLayer::acknowledgeMessages()
{
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    TLVector<quint64> idsVector = m_messagesToAck;
    m_messagesToAck.clear();
    outputStream << TLValue::MsgsAck;
    outputStream << idsVector;

    MTProto::Message *message = new MTProto::Message();
    message->messageId = m_sendHelper->newMessageId(SendMode::Client);
    message->sequenceNumber = m_contentRelatedMessages * 2;
    message->setData(outputStream.getData());

    m_messages.insert(message->messageId, message);
    sendPackage(*message);
}

void RpcLayer::onConnectionFailed()
{
    for (PendingRpcOperation *op : m_operations) {
        if (!op->isFinished()) {
            op->setFinishedWithError({{
                                          PendingOperation::c_text(),
                                          QStringLiteral("connection failed")
                                      }});
        }
    }
    m_operations.clear();
    qDeleteAll(m_messages);
    m_messages.clear();
}

QByteArray RpcLayer::getInitConnection() const
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_clientRpcLayerCategory) << CALL_INFO << "layer" << TLValue::CurrentLayer;
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

void RpcLayer::addMessageToAck(quint64 messageId)
{
    if (m_messagesToAck.isEmpty()) {
        QMetaObject::invokeMethod(this, "acknowledgeMessages", Qt::QueuedConnection);
    }
    m_messagesToAck.append(messageId);
}

} // Client namespace

} // Telegram namespace
