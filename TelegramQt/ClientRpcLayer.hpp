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

class CAppInformation;

namespace Telegram {

class AppInformation;
class PendingRpcOperation;

namespace Client {

class PendingAuthOperation;


// Generated low-level layers forward declarations
class AccountRpcLayer;
class AuthRpcLayer;
class ChannelsRpcLayer;
class ContactsRpcLayer;
class HelpRpcLayer;
class MessagesRpcLayer;
class PhotosRpcLayer;
class UpdatesRpcLayer;
class UploadRpcLayer;
class UsersRpcLayer;
// End of generated low-level layers forward declarations

class RpcLayer : public BaseRpcLayer
{
    Q_OBJECT
public:
    explicit RpcLayer(QObject *parent = nullptr);

    CAppInformation *appInformation() const { return m_appInfo; }
    void setAppInformation(CAppInformation *appInfo);

    void setSessionId(quint64 newSessionId);

    bool processRpcQuery(const QByteArray &data);

    // Generated low-level layers
    AccountRpcLayer *account() { return m_accountLayer; }
    AuthRpcLayer *auth() { return m_authLayer; }
    ChannelsRpcLayer *channels() { return m_channelsLayer; }
    ContactsRpcLayer *contacts() { return m_contactsLayer; }
    HelpRpcLayer *help() { return m_helpLayer; }
    MessagesRpcLayer *messages() { return m_messagesLayer; }
    PhotosRpcLayer *photos() { return m_photosLayer; }
    UpdatesRpcLayer *updates() { return m_updatesLayer; }
    UploadRpcLayer *upload() { return m_uploadLayer; }
    UsersRpcLayer *users() { return m_usersLayer; }
    // End of generated low-level layers

protected:
    bool processDecryptedPackage(const QByteArray &package) override;
    SAesKey getDecryptionAesKey(const QByteArray &messageKey) const final { return generateServerToClientAesKey(messageKey); }
    SAesKey getEncryptionAesKey(const QByteArray &messageKey) const final { return generateClientToServerAesKey(messageKey); }

    PendingRpcOperation *sendEncryptedPackage(const QByteArray &payload);
    static PendingRpcOperation *sendEncryptedPackage(RpcLayer *layer, const QByteArray &payload) { return layer->sendEncryptedPackage(payload); }
    QByteArray getInitConnection() const;

    CAppInformation *m_appInfo = nullptr;
    PendingAuthOperation *m_pendingAuthOperation = nullptr;
    QHash<quint64, PendingRpcOperation*> m_operations; // request message id, operation

    // Generated low-level layer members
    AccountRpcLayer *m_accountLayer = nullptr;
    AuthRpcLayer *m_authLayer = nullptr;
    ChannelsRpcLayer *m_channelsLayer = nullptr;
    ContactsRpcLayer *m_contactsLayer = nullptr;
    HelpRpcLayer *m_helpLayer = nullptr;
    MessagesRpcLayer *m_messagesLayer = nullptr;
    PhotosRpcLayer *m_photosLayer = nullptr;
    UpdatesRpcLayer *m_updatesLayer = nullptr;
    UploadRpcLayer *m_uploadLayer = nullptr;
    UsersRpcLayer *m_usersLayer = nullptr;
    // End of generated low-level layer members

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_HPP
