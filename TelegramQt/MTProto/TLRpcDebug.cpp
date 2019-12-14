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

#include "TLRpcDebug.hpp"

#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include "Stream.hpp"

using namespace Telegram::Debug;

namespace Telegram {

namespace MTProto {

void dumpRpc(Stream &stream)
{
    TLValue request;
    stream >> request;

    QDebug d = qDebug();
    d.nospace();

    switch (request) {
    case TLValue::MsgContainer: {
        quint32 itemsCount;
        stream >> itemsCount;

        qDebug() << request << "items" << itemsCount;
        for (quint32 i = 0; i < itemsCount; ++i) {
            quint64 id;
            stream >> id;
            //todo: ack
            quint32 seqNo;
            stream >> seqNo;
            quint32 size;
            stream >> size;

            const QByteArray data = stream.readBytes(size);
            Stream innerStream(data);
            dumpRpc(innerStream);
        }
        break;
    }
    case TLValue::InvokeWithLayer: {
        quint32 layer = 0;
        stream >> layer;
        qDebug() << request << "layer" << layer;
        dumpRpc(stream);
        break;
    }
    case TLValue::InitConnection: {
        quint32 appId;
        QString deviceInfo;
        QString osInfo;
        QString appVersion;
        QString languageCode;
        stream >> appId;
        stream >> deviceInfo;
        stream >> osInfo;
        stream >> appVersion;
        stream >> languageCode;

        qDebug() << request << "appId" << appId << "deviceInfo" << deviceInfo;
        dumpRpc(stream);
        break;
    }
    // Generated RPC debug cases
    case TLValue::AccountChangePhone:
        d << "AccountChangePhone(";
    {
        d << endl;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << endl;
    }
        d << ")";
        break;
    case TLValue::AccountCheckUsername:
        d << "AccountCheckUsername(";
    {
        d << endl;
        Spacer spacer;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << endl;
    }
        d << ")";
        break;
    case TLValue::AccountConfirmPhone:
        d << "AccountConfirmPhone(";
    {
        d << endl;
        Spacer spacer;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << endl;
    }
        d << ")";
        break;
    case TLValue::AccountDeleteAccount:
        d << "AccountDeleteAccount(";
    {
        d << endl;
        Spacer spacer;
        QString reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << endl;
    }
        d << ")";
        break;
    case TLValue::AccountGetAccountTTL:
        d << "AccountGetAccountTTL(";
        d << ")";
        break;
    case TLValue::AccountGetAuthorizations:
        d << "AccountGetAuthorizations(";
        d << ")";
        break;
    case TLValue::AccountGetNotifySettings:
        d << "AccountGetNotifySettings(";
    {
        d << endl;
        Spacer spacer;
        TLInputNotifyPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::AccountGetPassword:
        d << "AccountGetPassword(";
        d << ")";
        break;
    case TLValue::AccountGetPasswordSettings:
        d << "AccountGetPasswordSettings(";
    {
        d << endl;
        Spacer spacer;
        QByteArray currentPasswordHash;
        stream >> currentPasswordHash;
        d << spacer.innerSpaces() << "currentPasswordHash: " << currentPasswordHash.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::AccountGetPrivacy:
        d << "AccountGetPrivacy(";
    {
        d << endl;
        Spacer spacer;
        TLInputPrivacyKey key;
        stream >> key;
        d << spacer.innerSpaces() << "key: " << key << endl;
    }
        d << ")";
        break;
    case TLValue::AccountGetTmpPassword:
        d << "AccountGetTmpPassword(";
    {
        d << endl;
        Spacer spacer;
        QByteArray passwordHash;
        stream >> passwordHash;
        d << spacer.innerSpaces() << "passwordHash: " << passwordHash.toHex() << endl;
        quint32 period;
        stream >> period;
        d << spacer.innerSpaces() << "period: " << period << endl;
    }
        d << ")";
        break;
    case TLValue::AccountGetWallPapers:
        d << "AccountGetWallPapers(";
        d << ")";
        break;
    case TLValue::AccountRegisterDevice:
        d << "AccountRegisterDevice(";
    {
        d << endl;
        Spacer spacer;
        quint32 tokenType;
        stream >> tokenType;
        d << spacer.innerSpaces() << "tokenType: " << tokenType << endl;
        QString token;
        stream >> token;
        d << spacer.innerSpaces() << "token: " << token << endl;
    }
        d << ")";
        break;
    case TLValue::AccountReportPeer:
        d << "AccountReportPeer(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLReportReason reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << endl;
    }
        d << ")";
        break;
    case TLValue::AccountResetAuthorization:
        d << "AccountResetAuthorization(";
    {
        d << endl;
        Spacer spacer;
        quint64 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::AccountResetNotifySettings:
        d << "AccountResetNotifySettings(";
        d << ")";
        break;
    case TLValue::AccountSendChangePhoneCode:
        d << "AccountSendChangePhoneCode(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
    }
        d << ")";
        break;
    case TLValue::AccountSendConfirmPhoneCode:
        d << "AccountSendConfirmPhoneCode(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        QString hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::AccountSetAccountTTL:
        d << "AccountSetAccountTTL(";
    {
        d << endl;
        Spacer spacer;
        TLAccountDaysTTL ttl;
        stream >> ttl;
        d << spacer.innerSpaces() << "ttl: " << ttl << endl;
    }
        d << ")";
        break;
    case TLValue::AccountSetPrivacy:
        d << "AccountSetPrivacy(";
    {
        d << endl;
        Spacer spacer;
        TLInputPrivacyKey key;
        stream >> key;
        d << spacer.innerSpaces() << "key: " << key << endl;
        TLVector<TLInputPrivacyRule> rules;
        stream >> rules;
        d << spacer.innerSpaces() << "rules: " << rules << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUnregisterDevice:
        d << "AccountUnregisterDevice(";
    {
        d << endl;
        Spacer spacer;
        quint32 tokenType;
        stream >> tokenType;
        d << spacer.innerSpaces() << "tokenType: " << tokenType << endl;
        QString token;
        stream >> token;
        d << spacer.innerSpaces() << "token: " << token << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateDeviceLocked:
        d << "AccountUpdateDeviceLocked(";
    {
        d << endl;
        Spacer spacer;
        quint32 period;
        stream >> period;
        d << spacer.innerSpaces() << "period: " << period << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateNotifySettings:
        d << "AccountUpdateNotifySettings(";
    {
        d << endl;
        Spacer spacer;
        TLInputNotifyPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLInputPeerNotifySettings settings;
        stream >> settings;
        d << spacer.innerSpaces() << "settings: " << settings << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUpdatePasswordSettings:
        d << "AccountUpdatePasswordSettings(";
    {
        d << endl;
        Spacer spacer;
        QByteArray currentPasswordHash;
        stream >> currentPasswordHash;
        d << spacer.innerSpaces() << "currentPasswordHash: " << currentPasswordHash.toHex() << endl;
        TLAccountPasswordInputSettings newSettings;
        stream >> newSettings;
        d << spacer.innerSpaces() << "newSettings: " << newSettings << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateProfile:
        d << "AccountUpdateProfile(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateStatus:
        d << "AccountUpdateStatus(";
    {
        d << endl;
        Spacer spacer;
        bool offline;
        stream >> offline;
        d << spacer.innerSpaces() << "offline: " << offline << endl;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateUsername:
        d << "AccountUpdateUsername(";
    {
        d << endl;
        Spacer spacer;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << endl;
    }
        d << ")";
        break;
    case TLValue::AuthBindTempAuthKey:
        d << "AuthBindTempAuthKey(";
    {
        d << endl;
        Spacer spacer;
        quint64 permAuthKeyId;
        stream >> permAuthKeyId;
        d << spacer.innerSpaces() << "permAuthKeyId: " << permAuthKeyId << endl;
        quint64 nonce;
        stream >> nonce;
        d << spacer.innerSpaces() << "nonce: " << nonce << endl;
        quint32 expiresAt;
        stream >> expiresAt;
        d << spacer.innerSpaces() << "expiresAt: " << expiresAt << endl;
        QByteArray encryptedMessage;
        stream >> encryptedMessage;
        d << spacer.innerSpaces() << "encryptedMessage: " << encryptedMessage.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::AuthCancelCode:
        d << "AuthCancelCode(";
    {
        d << endl;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
    }
        d << ")";
        break;
    case TLValue::AuthCheckPassword:
        d << "AuthCheckPassword(";
    {
        d << endl;
        Spacer spacer;
        QByteArray passwordHash;
        stream >> passwordHash;
        d << spacer.innerSpaces() << "passwordHash: " << passwordHash.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::AuthCheckPhone:
        d << "AuthCheckPhone(";
    {
        d << endl;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
    }
        d << ")";
        break;
    case TLValue::AuthDropTempAuthKeys:
        d << "AuthDropTempAuthKeys(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint64> exceptAuthKeys;
        stream >> exceptAuthKeys;
        d << spacer.innerSpaces() << "exceptAuthKeys: " << exceptAuthKeys << endl;
    }
        d << ")";
        break;
    case TLValue::AuthExportAuthorization:
        d << "AuthExportAuthorization(";
    {
        d << endl;
        Spacer spacer;
        quint32 dcId;
        stream >> dcId;
        d << spacer.innerSpaces() << "dcId: " << dcId << endl;
    }
        d << ")";
        break;
    case TLValue::AuthImportAuthorization:
        d << "AuthImportAuthorization(";
    {
        d << endl;
        Spacer spacer;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        QByteArray bytes;
        stream >> bytes;
        d << spacer.innerSpaces() << "bytes: " << printBytes(bytes) << endl;
    }
        d << ")";
        break;
    case TLValue::AuthImportBotAuthorization:
        d << "AuthImportBotAuthorization(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 apiId;
        stream >> apiId;
        d << spacer.innerSpaces() << "apiId: " << apiId << endl;
        QString apiHash;
        stream >> apiHash;
        d << spacer.innerSpaces() << "apiHash: " << apiHash << endl;
        QString botAuthToken;
        stream >> botAuthToken;
        d << spacer.innerSpaces() << "botAuthToken: " << botAuthToken << endl;
    }
        d << ")";
        break;
    case TLValue::AuthLogOut:
        d << "AuthLogOut(";
        d << ")";
        break;
    case TLValue::AuthRecoverPassword:
        d << "AuthRecoverPassword(";
    {
        d << endl;
        Spacer spacer;
        QString code;
        stream >> code;
        d << spacer.innerSpaces() << "code: " << code << endl;
    }
        d << ")";
        break;
    case TLValue::AuthRequestPasswordRecovery:
        d << "AuthRequestPasswordRecovery(";
        d << ")";
        break;
    case TLValue::AuthResendCode:
        d << "AuthResendCode(";
    {
        d << endl;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
    }
        d << ")";
        break;
    case TLValue::AuthResetAuthorizations:
        d << "AuthResetAuthorizations(";
        d << ")";
        break;
    case TLValue::AuthSendCode:
        d << "AuthSendCode(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
        quint32 apiId;
        stream >> apiId;
        d << spacer.innerSpaces() << "apiId: " << apiId << endl;
        QString apiHash;
        stream >> apiHash;
        d << spacer.innerSpaces() << "apiHash: " << apiHash << endl;
    }
        d << ")";
        break;
    case TLValue::AuthSendInvites:
        d << "AuthSendInvites(";
    {
        d << endl;
        Spacer spacer;
        TLVector<QString> phoneNumbers;
        stream >> phoneNumbers;
        d << spacer.innerSpaces() << "phoneNumbers: " << phoneNumbers << endl;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << endl;
    }
        d << ")";
        break;
    case TLValue::AuthSignIn:
        d << "AuthSignIn(";
    {
        d << endl;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << endl;
    }
        d << ")";
        break;
    case TLValue::AuthSignUp:
        d << "AuthSignUp(";
    {
        d << endl;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << endl;
        QString firstName;
        stream >> firstName;
        d << spacer.innerSpaces() << "firstName: " << firstName << endl;
        QString lastName;
        stream >> lastName;
        d << spacer.innerSpaces() << "lastName: " << lastName << endl;
    }
        d << ")";
        break;
    case TLValue::BotsAnswerWebhookJSONQuery:
        d << "BotsAnswerWebhookJSONQuery(";
    {
        d << endl;
        Spacer spacer;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << endl;
        TLDataJSON data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data << endl;
    }
        d << ")";
        break;
    case TLValue::BotsSendCustomRequest:
        d << "BotsSendCustomRequest(";
    {
        d << endl;
        Spacer spacer;
        QString customMethod;
        stream >> customMethod;
        d << spacer.innerSpaces() << "customMethod: " << customMethod << endl;
        TLDataJSON params;
        stream >> params;
        d << spacer.innerSpaces() << "params: " << params << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsCheckUsername:
        d << "ChannelsCheckUsername(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsCreateChannel:
        d << "ChannelsCreateChannel(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << endl;
        QString about;
        stream >> about;
        d << spacer.innerSpaces() << "about: " << about << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteChannel:
        d << "ChannelsDeleteChannel(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteHistory:
        d << "ChannelsDeleteHistory(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteMessages:
        d << "ChannelsDeleteMessages(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteUserHistory:
        d << "ChannelsDeleteUserHistory(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditAbout:
        d << "ChannelsEditAbout(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        QString about;
        stream >> about;
        d << spacer.innerSpaces() << "about: " << about << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditAdmin:
        d << "ChannelsEditAdmin(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        TLChannelAdminRights adminRights;
        stream >> adminRights;
        d << spacer.innerSpaces() << "adminRights: " << adminRights << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditBanned:
        d << "ChannelsEditBanned(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        TLChannelBannedRights bannedRights;
        stream >> bannedRights;
        d << spacer.innerSpaces() << "bannedRights: " << bannedRights << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditPhoto:
        d << "ChannelsEditPhoto(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputChatPhoto photo;
        stream >> photo;
        d << spacer.innerSpaces() << "photo: " << photo << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditTitle:
        d << "ChannelsEditTitle(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsExportInvite:
        d << "ChannelsExportInvite(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsExportMessageLink:
        d << "ChannelsExportMessageLink(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetAdminLog:
        d << "ChannelsGetAdminLog(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << endl;
        quint64 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
        quint64 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetAdminedPublicChannels:
        d << "ChannelsGetAdminedPublicChannels(";
        d << ")";
        break;
    case TLValue::ChannelsGetChannels:
        d << "ChannelsGetChannels(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputChannel> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetFullChannel:
        d << "ChannelsGetFullChannel(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetMessages:
        d << "ChannelsGetMessages(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetParticipant:
        d << "ChannelsGetParticipant(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetParticipants:
        d << "ChannelsGetParticipants(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLChannelParticipantsFilter filter;
        stream >> filter;
        d << spacer.innerSpaces() << "filter: " << filter << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsInviteToChannel:
        d << "ChannelsInviteToChannel(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLVector<TLInputUser> users;
        stream >> users;
        d << spacer.innerSpaces() << "users: " << users << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsJoinChannel:
        d << "ChannelsJoinChannel(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsLeaveChannel:
        d << "ChannelsLeaveChannel(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsReadHistory:
        d << "ChannelsReadHistory(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsReadMessageContents:
        d << "ChannelsReadMessageContents(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsReportSpam:
        d << "ChannelsReportSpam(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsSetStickers:
        d << "ChannelsSetStickers(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsToggleInvites:
        d << "ChannelsToggleInvites(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsTogglePreHistoryHidden:
        d << "ChannelsTogglePreHistoryHidden(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsToggleSignatures:
        d << "ChannelsToggleSignatures(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsUpdatePinnedMessage:
        d << "ChannelsUpdatePinnedMessage(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ChannelsUpdateUsername:
        d << "ChannelsUpdateUsername(";
    {
        d << endl;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsBlock:
        d << "ContactsBlock(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsDeleteContact:
        d << "ContactsDeleteContact(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsDeleteContacts:
        d << "ContactsDeleteContacts(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputUser> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsExportCard:
        d << "ContactsExportCard(";
        d << ")";
        break;
    case TLValue::ContactsGetBlocked:
        d << "ContactsGetBlocked(";
    {
        d << endl;
        Spacer spacer;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsGetContacts:
        d << "ContactsGetContacts(";
    {
        d << endl;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsGetStatuses:
        d << "ContactsGetStatuses(";
        d << ")";
        break;
    case TLValue::ContactsGetTopPeers:
        d << "ContactsGetTopPeers(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsImportCard:
        d << "ContactsImportCard(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint32> exportCard;
        stream >> exportCard;
        d << spacer.innerSpaces() << "exportCard: " << exportCard << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsImportContacts:
        d << "ContactsImportContacts(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputContact> contacts;
        stream >> contacts;
        d << spacer.innerSpaces() << "contacts: " << contacts << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsResetSaved:
        d << "ContactsResetSaved(";
        d << ")";
        break;
    case TLValue::ContactsResetTopPeerRating:
        d << "ContactsResetTopPeerRating(";
    {
        d << endl;
        Spacer spacer;
        TLTopPeerCategory category;
        stream >> category;
        d << spacer.innerSpaces() << "category: " << category << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsResolveUsername:
        d << "ContactsResolveUsername(";
    {
        d << endl;
        Spacer spacer;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsSearch:
        d << "ContactsSearch(";
    {
        d << endl;
        Spacer spacer;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::ContactsUnblock:
        d << "ContactsUnblock(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::HelpGetAppChangelog:
        d << "HelpGetAppChangelog(";
    {
        d << endl;
        Spacer spacer;
        QString prevAppVersion;
        stream >> prevAppVersion;
        d << spacer.innerSpaces() << "prevAppVersion: " << prevAppVersion << endl;
    }
        d << ")";
        break;
    case TLValue::HelpGetAppUpdate:
        d << "HelpGetAppUpdate(";
        d << ")";
        break;
    case TLValue::HelpGetCdnConfig:
        d << "HelpGetCdnConfig(";
        d << ")";
        break;
    case TLValue::HelpGetConfig:
        d << "HelpGetConfig(";
        d << ")";
        break;
    case TLValue::HelpGetInviteText:
        d << "HelpGetInviteText(";
        d << ")";
        break;
    case TLValue::HelpGetNearestDc:
        d << "HelpGetNearestDc(";
        d << ")";
        break;
    case TLValue::HelpGetRecentMeUrls:
        d << "HelpGetRecentMeUrls(";
    {
        d << endl;
        Spacer spacer;
        QString referer;
        stream >> referer;
        d << spacer.innerSpaces() << "referer: " << referer << endl;
    }
        d << ")";
        break;
    case TLValue::HelpGetSupport:
        d << "HelpGetSupport(";
        d << ")";
        break;
    case TLValue::HelpGetTermsOfService:
        d << "HelpGetTermsOfService(";
        d << ")";
        break;
    case TLValue::HelpSaveAppLog:
        d << "HelpSaveAppLog(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputAppEvent> events;
        stream >> events;
        d << spacer.innerSpaces() << "events: " << events << endl;
    }
        d << ")";
        break;
    case TLValue::HelpSetBotUpdatesStatus:
        d << "HelpSetBotUpdatesStatus(";
    {
        d << endl;
        Spacer spacer;
        quint32 pendingUpdatesCount;
        stream >> pendingUpdatesCount;
        d << spacer.innerSpaces() << "pendingUpdatesCount: " << pendingUpdatesCount << endl;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << endl;
    }
        d << ")";
        break;
    case TLValue::LangpackGetDifference:
        d << "LangpackGetDifference(";
    {
        d << endl;
        Spacer spacer;
        quint32 fromVersion;
        stream >> fromVersion;
        d << spacer.innerSpaces() << "fromVersion: " << fromVersion << endl;
    }
        d << ")";
        break;
    case TLValue::LangpackGetLangPack:
        d << "LangpackGetLangPack(";
    {
        d << endl;
        Spacer spacer;
        QString langCode;
        stream >> langCode;
        d << spacer.innerSpaces() << "langCode: " << langCode << endl;
    }
        d << ")";
        break;
    case TLValue::LangpackGetLanguages:
        d << "LangpackGetLanguages(";
        d << ")";
        break;
    case TLValue::LangpackGetStrings:
        d << "LangpackGetStrings(";
    {
        d << endl;
        Spacer spacer;
        QString langCode;
        stream >> langCode;
        d << spacer.innerSpaces() << "langCode: " << langCode << endl;
        TLVector<QString> keys;
        stream >> keys;
        d << spacer.innerSpaces() << "keys: " << keys << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesAcceptEncryption:
        d << "MessagesAcceptEncryption(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QByteArray gB;
        stream >> gB;
        d << spacer.innerSpaces() << "gB: " << gB.toHex() << endl;
        quint64 keyFingerprint;
        stream >> keyFingerprint;
        d << spacer.innerSpaces() << "keyFingerprint: " << keyFingerprint << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesAddChatUser:
        d << "MessagesAddChatUser(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 fwdLimit;
        stream >> fwdLimit;
        d << spacer.innerSpaces() << "fwdLimit: " << fwdLimit << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesCheckChatInvite:
        d << "MessagesCheckChatInvite(";
    {
        d << endl;
        Spacer spacer;
        QString hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesClearRecentStickers:
        d << "MessagesClearRecentStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesCreateChat:
        d << "MessagesCreateChat(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputUser> users;
        stream >> users;
        d << spacer.innerSpaces() << "users: " << users << endl;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesDeleteChatUser:
        d << "MessagesDeleteChatUser(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesDeleteHistory:
        d << "MessagesDeleteHistory(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesDeleteMessages:
        d << "MessagesDeleteMessages(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesDiscardEncryption:
        d << "MessagesDiscardEncryption(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesEditChatAdmin:
        d << "MessagesEditChatAdmin(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        bool isAdmin;
        stream >> isAdmin;
        d << spacer.innerSpaces() << "isAdmin: " << isAdmin << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesEditChatPhoto:
        d << "MessagesEditChatPhoto(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
        TLInputChatPhoto photo;
        stream >> photo;
        d << spacer.innerSpaces() << "photo: " << photo << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesEditChatTitle:
        d << "MessagesEditChatTitle(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesEditInlineBotMessage:
        d << "MessagesEditInlineBotMessage(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputBotInlineMessageID id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesEditMessage:
        d << "MessagesEditMessage(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesExportChatInvite:
        d << "MessagesExportChatInvite(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesFaveSticker:
        d << "MessagesFaveSticker(";
    {
        d << endl;
        Spacer spacer;
        TLInputDocument id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        bool unfave;
        stream >> unfave;
        d << spacer.innerSpaces() << "unfave: " << unfave << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesForwardMessage:
        d << "MessagesForwardMessage(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesForwardMessages:
        d << "MessagesForwardMessages(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer fromPeer;
        stream >> fromPeer;
        d << spacer.innerSpaces() << "fromPeer: " << fromPeer << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        TLVector<quint64> randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        TLInputPeer toPeer;
        stream >> toPeer;
        d << spacer.innerSpaces() << "toPeer: " << toPeer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetAllChats:
        d << "MessagesGetAllChats(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint32> exceptIds;
        stream >> exceptIds;
        d << spacer.innerSpaces() << "exceptIds: " << exceptIds << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetAllDrafts:
        d << "MessagesGetAllDrafts(";
        d << ")";
        break;
    case TLValue::MessagesGetAllStickers:
        d << "MessagesGetAllStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetArchivedStickers:
        d << "MessagesGetArchivedStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint64 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetAttachedStickers:
        d << "MessagesGetAttachedStickers(";
    {
        d << endl;
        Spacer spacer;
        TLInputStickeredMedia media;
        stream >> media;
        d << spacer.innerSpaces() << "media: " << media << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetBotCallbackAnswer:
        d << "MessagesGetBotCallbackAnswer(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetChats:
        d << "MessagesGetChats(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetCommonChats:
        d << "MessagesGetCommonChats(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetDhConfig:
        d << "MessagesGetDhConfig(";
    {
        d << endl;
        Spacer spacer;
        quint32 version;
        stream >> version;
        d << spacer.innerSpaces() << "version: " << version << endl;
        quint32 randomLength;
        stream >> randomLength;
        d << spacer.innerSpaces() << "randomLength: " << randomLength << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetDialogs:
        d << "MessagesGetDialogs(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 offsetDate;
        stream >> offsetDate;
        d << spacer.innerSpaces() << "offsetDate: " << offsetDate << endl;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << endl;
        TLInputPeer offsetPeer;
        stream >> offsetPeer;
        d << spacer.innerSpaces() << "offsetPeer: " << offsetPeer << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetDocumentByHash:
        d << "MessagesGetDocumentByHash(";
    {
        d << endl;
        Spacer spacer;
        QByteArray sha256;
        stream >> sha256;
        d << spacer.innerSpaces() << "sha256: " << sha256.toHex() << endl;
        quint32 size;
        stream >> size;
        d << spacer.innerSpaces() << "size: " << size << endl;
        QString mimeType;
        stream >> mimeType;
        d << spacer.innerSpaces() << "mimeType: " << mimeType << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetFavedStickers:
        d << "MessagesGetFavedStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetFeaturedStickers:
        d << "MessagesGetFeaturedStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetFullChat:
        d << "MessagesGetFullChat(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetGameHighScores:
        d << "MessagesGetGameHighScores(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetHistory:
        d << "MessagesGetHistory(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << endl;
        quint32 offsetDate;
        stream >> offsetDate;
        d << spacer.innerSpaces() << "offsetDate: " << offsetDate << endl;
        quint32 addOffset;
        stream >> addOffset;
        d << spacer.innerSpaces() << "addOffset: " << addOffset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
        quint32 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << endl;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetInlineBotResults:
        d << "MessagesGetInlineBotResults(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputUser bot;
        stream >> bot;
        d << spacer.innerSpaces() << "bot: " << bot << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QString query;
        stream >> query;
        d << spacer.innerSpaces() << "query: " << query << endl;
        QString offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetInlineGameHighScores:
        d << "MessagesGetInlineGameHighScores(";
    {
        d << endl;
        Spacer spacer;
        TLInputBotInlineMessageID id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMaskStickers:
        d << "MessagesGetMaskStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMessageEditData:
        d << "MessagesGetMessageEditData(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMessages:
        d << "MessagesGetMessages(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMessagesViews:
        d << "MessagesGetMessagesViews(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        bool increment;
        stream >> increment;
        d << spacer.innerSpaces() << "increment: " << increment << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetPeerDialogs:
        d << "MessagesGetPeerDialogs(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputPeer> peers;
        stream >> peers;
        d << spacer.innerSpaces() << "peers: " << peers << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetPeerSettings:
        d << "MessagesGetPeerSettings(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetPinnedDialogs:
        d << "MessagesGetPinnedDialogs(";
        d << ")";
        break;
    case TLValue::MessagesGetRecentLocations:
        d << "MessagesGetRecentLocations(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetRecentStickers:
        d << "MessagesGetRecentStickers(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetSavedGifs:
        d << "MessagesGetSavedGifs(";
    {
        d << endl;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetStickerSet:
        d << "MessagesGetStickerSet(";
    {
        d << endl;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetUnreadMentions:
        d << "MessagesGetUnreadMentions(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << endl;
        quint32 addOffset;
        stream >> addOffset;
        d << spacer.innerSpaces() << "addOffset: " << addOffset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
        quint32 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetWebPage:
        d << "MessagesGetWebPage(";
    {
        d << endl;
        Spacer spacer;
        QString url;
        stream >> url;
        d << spacer.innerSpaces() << "url: " << url << endl;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesGetWebPagePreview:
        d << "MessagesGetWebPagePreview(";
    {
        d << endl;
        Spacer spacer;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesHideReportSpam:
        d << "MessagesHideReportSpam(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesImportChatInvite:
        d << "MessagesImportChatInvite(";
    {
        d << endl;
        Spacer spacer;
        QString hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesInstallStickerSet:
        d << "MessagesInstallStickerSet(";
    {
        d << endl;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << endl;
        bool archived;
        stream >> archived;
        d << spacer.innerSpaces() << "archived: " << archived << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesMigrateChat:
        d << "MessagesMigrateChat(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReadEncryptedHistory:
        d << "MessagesReadEncryptedHistory(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 maxDate;
        stream >> maxDate;
        d << spacer.innerSpaces() << "maxDate: " << maxDate << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReadFeaturedStickers:
        d << "MessagesReadFeaturedStickers(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint64> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReadHistory:
        d << "MessagesReadHistory(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReadMentions:
        d << "MessagesReadMentions(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReadMessageContents:
        d << "MessagesReadMessageContents(";
    {
        d << endl;
        Spacer spacer;
        TLVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReceivedMessages:
        d << "MessagesReceivedMessages(";
    {
        d << endl;
        Spacer spacer;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReceivedQueue:
        d << "MessagesReceivedQueue(";
    {
        d << endl;
        Spacer spacer;
        quint32 maxQts;
        stream >> maxQts;
        d << spacer.innerSpaces() << "maxQts: " << maxQts << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReorderPinnedDialogs:
        d << "MessagesReorderPinnedDialogs(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLVector<TLInputPeer> order;
        stream >> order;
        d << spacer.innerSpaces() << "order: " << order << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReorderStickerSets:
        d << "MessagesReorderStickerSets(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLVector<quint64> order;
        stream >> order;
        d << spacer.innerSpaces() << "order: " << order << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReportEncryptedSpam:
        d << "MessagesReportEncryptedSpam(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesReportSpam:
        d << "MessagesReportSpam(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesRequestEncryption:
        d << "MessagesRequestEncryption(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        QByteArray gA;
        stream >> gA;
        d << spacer.innerSpaces() << "gA: " << gA.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSaveDraft:
        d << "MessagesSaveDraft(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSaveGif:
        d << "MessagesSaveGif(";
    {
        d << endl;
        Spacer spacer;
        TLInputDocument id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        bool unsave;
        stream >> unsave;
        d << spacer.innerSpaces() << "unsave: " << unsave << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSaveRecentSticker:
        d << "MessagesSaveRecentSticker(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputDocument id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        bool unsave;
        stream >> unsave;
        d << spacer.innerSpaces() << "unsave: " << unsave << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSearch:
        d << "MessagesSearch(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << endl;
        TLMessagesFilter filter;
        stream >> filter;
        d << spacer.innerSpaces() << "filter: " << filter << endl;
        quint32 minDate;
        stream >> minDate;
        d << spacer.innerSpaces() << "minDate: " << minDate << endl;
        quint32 maxDate;
        stream >> maxDate;
        d << spacer.innerSpaces() << "maxDate: " << maxDate << endl;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << endl;
        quint32 addOffset;
        stream >> addOffset;
        d << spacer.innerSpaces() << "addOffset: " << addOffset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
        quint32 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSearchGifs:
        d << "MessagesSearchGifs(";
    {
        d << endl;
        Spacer spacer;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSearchGlobal:
        d << "MessagesSearchGlobal(";
    {
        d << endl;
        Spacer spacer;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << endl;
        quint32 offsetDate;
        stream >> offsetDate;
        d << spacer.innerSpaces() << "offsetDate: " << offsetDate << endl;
        TLInputPeer offsetPeer;
        stream >> offsetPeer;
        d << spacer.innerSpaces() << "offsetPeer: " << offsetPeer << endl;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendEncrypted:
        d << "MessagesSendEncrypted(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        QByteArray data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendEncryptedFile:
        d << "MessagesSendEncryptedFile(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        QByteArray data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data.toHex() << endl;
        TLInputEncryptedFile file;
        stream >> file;
        d << spacer.innerSpaces() << "file: " << file << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendEncryptedService:
        d << "MessagesSendEncryptedService(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        QByteArray data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendInlineBotResult:
        d << "MessagesSendInlineBotResult(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << endl;
        QString id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendMedia:
        d << "MessagesSendMedia(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLInputMedia media;
        stream >> media;
        d << spacer.innerSpaces() << "media: " << media << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendMessage:
        d << "MessagesSendMessage(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSendScreenshotNotification:
        d << "MessagesSendScreenshotNotification(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 replyToMsgId;
        stream >> replyToMsgId;
        d << spacer.innerSpaces() << "replyToMsgId: " << replyToMsgId << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetBotCallbackAnswer:
        d << "MessagesSetBotCallbackAnswer(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << endl;
        quint32 cacheTime;
        stream >> cacheTime;
        d << spacer.innerSpaces() << "cacheTime: " << cacheTime << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetBotPrecheckoutResults:
        d << "MessagesSetBotPrecheckoutResults(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetBotShippingResults:
        d << "MessagesSetBotShippingResults(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetEncryptedTyping:
        d << "MessagesSetEncryptedTyping(";
    {
        d << endl;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        bool typing;
        stream >> typing;
        d << spacer.innerSpaces() << "typing: " << typing << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetGameScore:
        d << "MessagesSetGameScore(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 score;
        stream >> score;
        d << spacer.innerSpaces() << "score: " << score << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetInlineBotResults:
        d << "MessagesSetInlineBotResults(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << endl;
        TLVector<TLInputBotInlineResult> results;
        stream >> results;
        d << spacer.innerSpaces() << "results: " << results << endl;
        quint32 cacheTime;
        stream >> cacheTime;
        d << spacer.innerSpaces() << "cacheTime: " << cacheTime << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetInlineGameScore:
        d << "MessagesSetInlineGameScore(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputBotInlineMessageID id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 score;
        stream >> score;
        d << spacer.innerSpaces() << "score: " << score << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesSetTyping:
        d << "MessagesSetTyping(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLSendMessageAction action;
        stream >> action;
        d << spacer.innerSpaces() << "action: " << action << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesStartBot:
        d << "MessagesStartBot(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser bot;
        stream >> bot;
        d << spacer.innerSpaces() << "bot: " << bot << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        QString startParam;
        stream >> startParam;
        d << spacer.innerSpaces() << "startParam: " << startParam << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesToggleChatAdmins:
        d << "MessagesToggleChatAdmins(";
    {
        d << endl;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << endl;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesToggleDialogPin:
        d << "MessagesToggleDialogPin(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesUninstallStickerSet:
        d << "MessagesUninstallStickerSet(";
    {
        d << endl;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << endl;
    }
        d << ")";
        break;
    case TLValue::MessagesUploadMedia:
        d << "MessagesUploadMedia(";
    {
        d << endl;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLInputMedia media;
        stream >> media;
        d << spacer.innerSpaces() << "media: " << media << endl;
    }
        d << ")";
        break;
    case TLValue::PaymentsClearSavedInfo:
        d << "PaymentsClearSavedInfo(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
    }
        d << ")";
        break;
    case TLValue::PaymentsGetPaymentForm:
        d << "PaymentsGetPaymentForm(";
    {
        d << endl;
        Spacer spacer;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << endl;
    }
        d << ")";
        break;
    case TLValue::PaymentsGetPaymentReceipt:
        d << "PaymentsGetPaymentReceipt(";
    {
        d << endl;
        Spacer spacer;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << endl;
    }
        d << ")";
        break;
    case TLValue::PaymentsGetSavedInfo:
        d << "PaymentsGetSavedInfo(";
        d << ")";
        break;
    case TLValue::PaymentsSendPaymentForm:
        d << "PaymentsSendPaymentForm(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << endl;
        TLInputPaymentCredentials credentials;
        stream >> credentials;
        d << spacer.innerSpaces() << "credentials: " << credentials << endl;
    }
        d << ")";
        break;
    case TLValue::PaymentsValidateRequestedInfo:
        d << "PaymentsValidateRequestedInfo(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << endl;
        TLPaymentRequestedInfo info;
        stream >> info;
        d << spacer.innerSpaces() << "info: " << info << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneAcceptCall:
        d << "PhoneAcceptCall(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QByteArray gB;
        stream >> gB;
        d << spacer.innerSpaces() << "gB: " << gB.toHex() << endl;
        TLPhoneCallProtocol protocol;
        stream >> protocol;
        d << spacer.innerSpaces() << "protocol: " << protocol << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneConfirmCall:
        d << "PhoneConfirmCall(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        QByteArray gA;
        stream >> gA;
        d << spacer.innerSpaces() << "gA: " << gA.toHex() << endl;
        quint64 keyFingerprint;
        stream >> keyFingerprint;
        d << spacer.innerSpaces() << "keyFingerprint: " << keyFingerprint << endl;
        TLPhoneCallProtocol protocol;
        stream >> protocol;
        d << spacer.innerSpaces() << "protocol: " << protocol << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneDiscardCall:
        d << "PhoneDiscardCall(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 duration;
        stream >> duration;
        d << spacer.innerSpaces() << "duration: " << duration << endl;
        TLPhoneCallDiscardReason reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << endl;
        quint64 connectionId;
        stream >> connectionId;
        d << spacer.innerSpaces() << "connectionId: " << connectionId << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneGetCallConfig:
        d << "PhoneGetCallConfig(";
        d << ")";
        break;
    case TLValue::PhoneReceivedCall:
        d << "PhoneReceivedCall(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneRequestCall:
        d << "PhoneRequestCall(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << endl;
        QByteArray gAHash;
        stream >> gAHash;
        d << spacer.innerSpaces() << "gAHash: " << gAHash.toHex() << endl;
        TLPhoneCallProtocol protocol;
        stream >> protocol;
        d << spacer.innerSpaces() << "protocol: " << protocol << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneSaveCallDebug:
        d << "PhoneSaveCallDebug(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        TLDataJSON debug;
        stream >> debug;
        d << spacer.innerSpaces() << "debug: " << debug << endl;
    }
        d << ")";
        break;
    case TLValue::PhoneSetCallRating:
        d << "PhoneSetCallRating(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << endl;
        quint32 rating;
        stream >> rating;
        d << spacer.innerSpaces() << "rating: " << rating << endl;
        QString comment;
        stream >> comment;
        d << spacer.innerSpaces() << "comment: " << comment << endl;
    }
        d << ")";
        break;
    case TLValue::PhotosDeletePhotos:
        d << "PhotosDeletePhotos(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputPhoto> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::PhotosGetUserPhotos:
        d << "PhotosGetUserPhotos(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint64 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::PhotosUpdateProfilePhoto:
        d << "PhotosUpdateProfilePhoto(";
    {
        d << endl;
        Spacer spacer;
        TLInputPhoto id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::PhotosUploadProfilePhoto:
        d << "PhotosUploadProfilePhoto(";
    {
        d << endl;
        Spacer spacer;
        TLInputFile file;
        stream >> file;
        d << spacer.innerSpaces() << "file: " << file << endl;
    }
        d << ")";
        break;
    case TLValue::StickersAddStickerToSet:
        d << "StickersAddStickerToSet(";
    {
        d << endl;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << endl;
        TLInputStickerSetItem sticker;
        stream >> sticker;
        d << spacer.innerSpaces() << "sticker: " << sticker << endl;
    }
        d << ")";
        break;
    case TLValue::StickersChangeStickerPosition:
        d << "StickersChangeStickerPosition(";
    {
        d << endl;
        Spacer spacer;
        TLInputDocument sticker;
        stream >> sticker;
        d << spacer.innerSpaces() << "sticker: " << sticker << endl;
        quint32 position;
        stream >> position;
        d << spacer.innerSpaces() << "position: " << position << endl;
    }
        d << ")";
        break;
    case TLValue::StickersCreateStickerSet:
        d << "StickersCreateStickerSet(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << endl;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << endl;
        QString shortName;
        stream >> shortName;
        d << spacer.innerSpaces() << "shortName: " << shortName << endl;
        TLVector<TLInputStickerSetItem> stickers;
        stream >> stickers;
        d << spacer.innerSpaces() << "stickers: " << stickers << endl;
    }
        d << ")";
        break;
    case TLValue::StickersRemoveStickerFromSet:
        d << "StickersRemoveStickerFromSet(";
    {
        d << endl;
        Spacer spacer;
        TLInputDocument sticker;
        stream >> sticker;
        d << spacer.innerSpaces() << "sticker: " << sticker << endl;
    }
        d << ")";
        break;
    case TLValue::UpdatesGetChannelDifference:
        d << "UpdatesGetChannelDifference(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << endl;
        TLChannelMessagesFilter filter;
        stream >> filter;
        d << spacer.innerSpaces() << "filter: " << filter << endl;
        quint32 pts;
        stream >> pts;
        d << spacer.innerSpaces() << "pts: " << pts << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::UpdatesGetDifference:
        d << "UpdatesGetDifference(";
    {
        d << endl;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << endl;
        quint32 pts;
        stream >> pts;
        d << spacer.innerSpaces() << "pts: " << pts << endl;
        quint32 date;
        stream >> date;
        d << spacer.innerSpaces() << "date: " << date << endl;
        quint32 qts;
        stream >> qts;
        d << spacer.innerSpaces() << "qts: " << qts << endl;
    }
        d << ")";
        break;
    case TLValue::UpdatesGetState:
        d << "UpdatesGetState(";
        d << ")";
        break;
    case TLValue::UploadGetCdnFile:
        d << "UploadGetCdnFile(";
    {
        d << endl;
        Spacer spacer;
        QByteArray fileToken;
        stream >> fileToken;
        d << spacer.innerSpaces() << "fileToken: " << fileToken.toHex() << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::UploadGetCdnFileHashes:
        d << "UploadGetCdnFileHashes(";
    {
        d << endl;
        Spacer spacer;
        QByteArray fileToken;
        stream >> fileToken;
        d << spacer.innerSpaces() << "fileToken: " << fileToken.toHex() << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
    }
        d << ")";
        break;
    case TLValue::UploadGetFile:
        d << "UploadGetFile(";
    {
        d << endl;
        Spacer spacer;
        TLInputFileLocation location;
        stream >> location;
        d << spacer.innerSpaces() << "location: " << location << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::UploadGetWebFile:
        d << "UploadGetWebFile(";
    {
        d << endl;
        Spacer spacer;
        TLInputWebFileLocation location;
        stream >> location;
        d << spacer.innerSpaces() << "location: " << location << endl;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << endl;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << endl;
    }
        d << ")";
        break;
    case TLValue::UploadReuploadCdnFile:
        d << "UploadReuploadCdnFile(";
    {
        d << endl;
        Spacer spacer;
        QByteArray fileToken;
        stream >> fileToken;
        d << spacer.innerSpaces() << "fileToken: " << fileToken.toHex() << endl;
        QByteArray requestToken;
        stream >> requestToken;
        d << spacer.innerSpaces() << "requestToken: " << requestToken.toHex() << endl;
    }
        d << ")";
        break;
    case TLValue::UploadSaveBigFilePart:
        d << "UploadSaveBigFilePart(";
    {
        d << endl;
        Spacer spacer;
        quint64 fileId;
        stream >> fileId;
        d << spacer.innerSpaces() << "fileId: " << fileId << endl;
        quint32 filePart;
        stream >> filePart;
        d << spacer.innerSpaces() << "filePart: " << filePart << endl;
        quint32 fileTotalParts;
        stream >> fileTotalParts;
        d << spacer.innerSpaces() << "fileTotalParts: " << fileTotalParts << endl;
        QByteArray bytes;
        stream >> bytes;
        d << spacer.innerSpaces() << "bytes: " << printBytes(bytes) << endl;
    }
        d << ")";
        break;
    case TLValue::UploadSaveFilePart:
        d << "UploadSaveFilePart(";
    {
        d << endl;
        Spacer spacer;
        quint64 fileId;
        stream >> fileId;
        d << spacer.innerSpaces() << "fileId: " << fileId << endl;
        quint32 filePart;
        stream >> filePart;
        d << spacer.innerSpaces() << "filePart: " << filePart << endl;
        QByteArray bytes;
        stream >> bytes;
        d << spacer.innerSpaces() << "bytes: " << printBytes(bytes) << endl;
    }
        d << ")";
        break;
    case TLValue::UsersGetFullUser:
        d << "UsersGetFullUser(";
    {
        d << endl;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    case TLValue::UsersGetUsers:
        d << "UsersGetUsers(";
    {
        d << endl;
        Spacer spacer;
        TLVector<TLInputUser> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << endl;
    }
        d << ")";
        break;
    // End of generated RPC debug cases
    default:
        qDebug() << "Unknown data" << request;
        break;
    }
}

} // MTProto namespace

} // Telegram namespace
