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

#ifndef TELEGRAM_CLIENT_RPC_HPP
#define TELEGRAM_CLIENT_RPC_HPP

#include "RpcLayer.hpp"

#include <QHash>
#include <QVector>

class CTelegramStream;

namespace Telegram {

namespace MTProto {

struct IgnoredMessageNotification;
struct Message;

} // MTProto namespace

namespace Client {

class AppInformation;
class AuthOperation;
class PendingRpcOperation;
class UpdatesInternalApi;

class RpcLayer : public Telegram::BaseRpcLayer
{
    Q_OBJECT
public:
    enum class DeltaTimeHeuristicState {
        Ok,
        ForwardStep1,
        ForwardStep2,
        BackwardStep1,
        BackwardStep2,
    };

    explicit RpcLayer(QObject *parent = nullptr);
    ~RpcLayer() override;

    AppInformation *appInformation() const { return m_appInfo; }
    void setAppInformation(AppInformation *appInfo);

    void installUpdatesHandler(UpdatesInternalApi *updatesHandler);

    quint64 sessionId() const override { return m_sessionId; }
    void setSessionData(quint64 sessionId, quint32 contentRelatedMessagesNumber);

    quint64 serverSalt() const override { return m_serverSalt; }
    void setServerSalt(quint64 serverSalt);

    void startNewSession();

    bool processMTProtoMessage(const MTProto::Message &message) override;
    bool processSessionCreated(const MTProto::Message &message);
    bool processIgnoredMessageNotification(const MTProto::Message &message);
    bool processUnsyncMessageId(const MTProto::IgnoredMessageNotification &notification);
    bool processRpcResult(const MTProto::Message &message);
    bool processUpdates(const MTProto::Message &message);
    bool processMessageAck(const MTProto::Message &message);

    quint64 sendRpc(PendingRpcOperation *operation);
    bool resendIgnoredMessage(quint64 messageId);

    void onConnectionLost(const QVariantHash &details) override;

protected Q_SLOTS:
    void acknowledgeMessages();

protected:
    bool processMessageHeader(const MTProto::FullMessageHeader &header) override;
    Crypto::AesKey getDecryptionAesKey(const QByteArray &messageKey) const final { return generateServerToClientAesKey(messageKey); }
    Crypto::AesKey getEncryptionAesKey(const QByteArray &messageKey) const final { return generateClientToServerAesKey(messageKey); }

    QByteArray getEncryptionKeyPart() const final;
    QByteArray getVerificationKeyPart() const final;

    QByteArray getInitConnection() const;

    void addMessageToAck(quint64 messageId);

    AppInformation *m_appInfo = nullptr;
    UpdatesInternalApi *m_UpdatesInternalApi = nullptr;
    AuthOperation *m_pendingAuthOperation = nullptr;
    QHash<quint64, PendingRpcOperation*> m_operations; // request message id, operation
    QHash<quint64, MTProto::Message*> m_messages; // request message id to MTProto::Message
    quint64 m_sessionId = 0;
    quint64 m_serverSalt = 0;
    QVector<quint64> m_messagesToAck;
    DeltaTimeHeuristicState m_deltaTimeHeuristicState = DeltaTimeHeuristicState::Ok;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_HPP
