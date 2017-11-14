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

#include "CTelegramStream.hpp"

void dumpRpc(CTelegramStream &stream)
{
    TLValue request;
    stream >> request;

    switch (request) {
    // Generated RPC debug cases
    case TLValue::AccountChangePhone: {
        QString phoneNumber;
        stream >> phoneNumber;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        QString phoneCode;
        stream >> phoneCode;
        qDebug() << request << "phoneNumber" << phoneNumber << "phoneCodeHash" << phoneCodeHash << "phoneCode" << phoneCode;
    }
        break;

    case TLValue::AccountCheckUsername: {
        QString username;
        stream >> username;
        qDebug() << request << "username" << username;
    }
        break;

    case TLValue::AccountDeleteAccount: {
        QString reason;
        stream >> reason;
        qDebug() << request << "reason" << reason;
    }
        break;

    case TLValue::AccountGetAccountTTL: {
        qDebug() << request;
    }
        break;

    case TLValue::AccountGetAuthorizations: {
        qDebug() << request;
    }
        break;

    case TLValue::AccountGetNotifySettings: {
        TLInputNotifyPeer peer;
        stream >> peer;
        qDebug() << request << "peer" << peer;
    }
        break;

    case TLValue::AccountGetPassword: {
        qDebug() << request;
    }
        break;

    case TLValue::AccountGetPasswordSettings: {
        QByteArray currentPasswordHash;
        stream >> currentPasswordHash;
        qDebug() << request << "currentPasswordHash" << currentPasswordHash;
    }
        break;

    case TLValue::AccountGetPrivacy: {
        TLInputPrivacyKey key;
        stream >> key;
        qDebug() << request << "key" << key;
    }
        break;

    case TLValue::AccountGetWallPapers: {
        qDebug() << request;
    }
        break;

    case TLValue::AccountRegisterDevice: {
        quint32 tokenType;
        stream >> tokenType;
        QString token;
        stream >> token;
        QString deviceModel;
        stream >> deviceModel;
        QString systemVersion;
        stream >> systemVersion;
        QString appVersion;
        stream >> appVersion;
        bool appSandbox;
        stream >> appSandbox;
        QString langCode;
        stream >> langCode;
        qDebug() << request << "tokenType" << tokenType << "token" << token << "deviceModel" << deviceModel << "systemVersion" << systemVersion << "appVersion" << appVersion << "appSandbox" << appSandbox << "langCode" << langCode;
    }
        break;

    case TLValue::AccountReportPeer: {
        TLInputPeer peer;
        stream >> peer;
        TLReportReason reason;
        stream >> reason;
        qDebug() << request << "peer" << peer << "reason" << reason;
    }
        break;

    case TLValue::AccountResetAuthorization: {
        quint64 hash;
        stream >> hash;
        qDebug() << request << "hash" << hash;
    }
        break;

    case TLValue::AccountResetNotifySettings: {
        qDebug() << request;
    }
        break;

    case TLValue::AccountSendChangePhoneCode: {
        QString phoneNumber;
        stream >> phoneNumber;
        qDebug() << request << "phoneNumber" << phoneNumber;
    }
        break;

    case TLValue::AccountSetAccountTTL: {
        TLAccountDaysTTL ttl;
        stream >> ttl;
        qDebug() << request << "ttl" << ttl;
    }
        break;

    case TLValue::AccountSetPrivacy: {
        TLInputPrivacyKey key;
        stream >> key;
        TLVector<TLInputPrivacyRule> rules;
        stream >> rules;
        qDebug() << request << "key" << key << "rules" << rules;
    }
        break;

    case TLValue::AccountUnregisterDevice: {
        quint32 tokenType;
        stream >> tokenType;
        QString token;
        stream >> token;
        qDebug() << request << "tokenType" << tokenType << "token" << token;
    }
        break;

    case TLValue::AccountUpdateDeviceLocked: {
        quint32 period;
        stream >> period;
        qDebug() << request << "period" << period;
    }
        break;

    case TLValue::AccountUpdateNotifySettings: {
        TLInputNotifyPeer peer;
        stream >> peer;
        TLInputPeerNotifySettings settings;
        stream >> settings;
        qDebug() << request << "peer" << peer << "settings" << settings;
    }
        break;

    case TLValue::AccountUpdatePasswordSettings: {
        QByteArray currentPasswordHash;
        stream >> currentPasswordHash;
        TLAccountPasswordInputSettings newSettings;
        stream >> newSettings;
        qDebug() << request << "currentPasswordHash" << currentPasswordHash << "newSettings" << newSettings;
    }
        break;

    case TLValue::AccountUpdateProfile: {
        QString firstName;
        stream >> firstName;
        QString lastName;
        stream >> lastName;
        qDebug() << request << "firstName" << firstName << "lastName" << lastName;
    }
        break;

    case TLValue::AccountUpdateStatus: {
        bool offline;
        stream >> offline;
        qDebug() << request << "offline" << offline;
    }
        break;

    case TLValue::AccountUpdateUsername: {
        QString username;
        stream >> username;
        qDebug() << request << "username" << username;
    }
        break;

    case TLValue::AuthBindTempAuthKey: {
        quint64 permAuthKeyId;
        stream >> permAuthKeyId;
        quint64 nonce;
        stream >> nonce;
        quint32 expiresAt;
        stream >> expiresAt;
        QByteArray encryptedMessage;
        stream >> encryptedMessage;
        qDebug() << request << "permAuthKeyId" << permAuthKeyId << "nonce" << nonce << "expiresAt" << expiresAt << "encryptedMessage" << encryptedMessage;
    }
        break;

    case TLValue::AuthCheckPassword: {
        QByteArray passwordHash;
        stream >> passwordHash;
        qDebug() << request << "passwordHash" << passwordHash;
    }
        break;

    case TLValue::AuthCheckPhone: {
        QString phoneNumber;
        stream >> phoneNumber;
        qDebug() << request << "phoneNumber" << phoneNumber;
    }
        break;

    case TLValue::AuthExportAuthorization: {
        quint32 dcId;
        stream >> dcId;
        qDebug() << request << "dcId" << dcId;
    }
        break;

    case TLValue::AuthImportAuthorization: {
        quint32 id;
        stream >> id;
        QByteArray bytes;
        stream >> bytes;
        qDebug() << request << "id" << id << "bytes" << bytes;
    }
        break;

    case TLValue::AuthImportBotAuthorization: {
        quint32 flags;
        stream >> flags;
        quint32 apiId;
        stream >> apiId;
        QString apiHash;
        stream >> apiHash;
        QString botAuthToken;
        stream >> botAuthToken;
        qDebug() << request << "flags" << flags << "apiId" << apiId << "apiHash" << apiHash << "botAuthToken" << botAuthToken;
    }
        break;

    case TLValue::AuthLogOut: {
        qDebug() << request;
    }
        break;

    case TLValue::AuthRecoverPassword: {
        QString code;
        stream >> code;
        qDebug() << request << "code" << code;
    }
        break;

    case TLValue::AuthRequestPasswordRecovery: {
        qDebug() << request;
    }
        break;

    case TLValue::AuthResetAuthorizations: {
        qDebug() << request;
    }
        break;

    case TLValue::AuthSendCall: {
        QString phoneNumber;
        stream >> phoneNumber;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        qDebug() << request << "phoneNumber" << phoneNumber << "phoneCodeHash" << phoneCodeHash;
    }
        break;

    case TLValue::AuthSendCode: {
        QString phoneNumber;
        stream >> phoneNumber;
        quint32 smsType;
        stream >> smsType;
        quint32 apiId;
        stream >> apiId;
        QString apiHash;
        stream >> apiHash;
        QString langCode;
        stream >> langCode;
        qDebug() << request << "phoneNumber" << phoneNumber << "smsType" << smsType << "apiId" << apiId << "apiHash" << apiHash << "langCode" << langCode;
    }
        break;

    case TLValue::AuthSendInvites: {
        TLVector<QString> phoneNumbers;
        stream >> phoneNumbers;
        QString message;
        stream >> message;
        qDebug() << request << "phoneNumbers" << phoneNumbers << "message" << message;
    }
        break;

    case TLValue::AuthSendSms: {
        QString phoneNumber;
        stream >> phoneNumber;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        qDebug() << request << "phoneNumber" << phoneNumber << "phoneCodeHash" << phoneCodeHash;
    }
        break;

    case TLValue::AuthSignIn: {
        QString phoneNumber;
        stream >> phoneNumber;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        QString phoneCode;
        stream >> phoneCode;
        qDebug() << request << "phoneNumber" << phoneNumber << "phoneCodeHash" << phoneCodeHash << "phoneCode" << phoneCode;
    }
        break;

    case TLValue::AuthSignUp: {
        QString phoneNumber;
        stream >> phoneNumber;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        QString phoneCode;
        stream >> phoneCode;
        QString firstName;
        stream >> firstName;
        QString lastName;
        stream >> lastName;
        qDebug() << request << "phoneNumber" << phoneNumber << "phoneCodeHash" << phoneCodeHash << "phoneCode" << phoneCode << "firstName" << firstName << "lastName" << lastName;
    }
        break;

    case TLValue::ChannelsCheckUsername: {
        TLInputChannel channel;
        stream >> channel;
        QString username;
        stream >> username;
        qDebug() << request << "channel" << channel << "username" << username;
    }
        break;

    case TLValue::ChannelsDeleteChannel: {
        TLInputChannel channel;
        stream >> channel;
        qDebug() << request << "channel" << channel;
    }
        break;

    case TLValue::ChannelsDeleteMessages: {
        TLInputChannel channel;
        stream >> channel;
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "channel" << channel << "id" << id;
    }
        break;

    case TLValue::ChannelsDeleteUserHistory: {
        TLInputChannel channel;
        stream >> channel;
        TLInputUser userId;
        stream >> userId;
        qDebug() << request << "channel" << channel << "userId" << userId;
    }
        break;

    case TLValue::ChannelsEditAbout: {
        TLInputChannel channel;
        stream >> channel;
        QString about;
        stream >> about;
        qDebug() << request << "channel" << channel << "about" << about;
    }
        break;

    case TLValue::ChannelsEditAdmin: {
        TLInputChannel channel;
        stream >> channel;
        TLInputUser userId;
        stream >> userId;
        TLChannelParticipantRole role;
        stream >> role;
        qDebug() << request << "channel" << channel << "userId" << userId << "role" << role;
    }
        break;

    case TLValue::ChannelsEditPhoto: {
        TLInputChannel channel;
        stream >> channel;
        TLInputChatPhoto photo;
        stream >> photo;
        qDebug() << request << "channel" << channel << "photo" << photo;
    }
        break;

    case TLValue::ChannelsEditTitle: {
        TLInputChannel channel;
        stream >> channel;
        QString title;
        stream >> title;
        qDebug() << request << "channel" << channel << "title" << title;
    }
        break;

    case TLValue::ChannelsExportInvite: {
        TLInputChannel channel;
        stream >> channel;
        qDebug() << request << "channel" << channel;
    }
        break;

    case TLValue::ChannelsGetChannels: {
        TLVector<TLInputChannel> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::ChannelsGetDialogs: {
        quint32 offset;
        stream >> offset;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "offset" << offset << "limit" << limit;
    }
        break;

    case TLValue::ChannelsGetFullChannel: {
        TLInputChannel channel;
        stream >> channel;
        qDebug() << request << "channel" << channel;
    }
        break;

    case TLValue::ChannelsGetImportantHistory: {
        TLInputChannel channel;
        stream >> channel;
        quint32 offsetId;
        stream >> offsetId;
        quint32 addOffset;
        stream >> addOffset;
        quint32 limit;
        stream >> limit;
        quint32 maxId;
        stream >> maxId;
        quint32 minId;
        stream >> minId;
        qDebug() << request << "channel" << channel << "offsetId" << offsetId << "addOffset" << addOffset << "limit" << limit << "maxId" << maxId << "minId" << minId;
    }
        break;

    case TLValue::ChannelsGetMessages: {
        TLInputChannel channel;
        stream >> channel;
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "channel" << channel << "id" << id;
    }
        break;

    case TLValue::ChannelsGetParticipant: {
        TLInputChannel channel;
        stream >> channel;
        TLInputUser userId;
        stream >> userId;
        qDebug() << request << "channel" << channel << "userId" << userId;
    }
        break;

    case TLValue::ChannelsGetParticipants: {
        TLInputChannel channel;
        stream >> channel;
        TLChannelParticipantsFilter filter;
        stream >> filter;
        quint32 offset;
        stream >> offset;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "channel" << channel << "filter" << filter << "offset" << offset << "limit" << limit;
    }
        break;

    case TLValue::ChannelsInviteToChannel: {
        TLInputChannel channel;
        stream >> channel;
        TLVector<TLInputUser> users;
        stream >> users;
        qDebug() << request << "channel" << channel << "users" << users;
    }
        break;

    case TLValue::ChannelsJoinChannel: {
        TLInputChannel channel;
        stream >> channel;
        qDebug() << request << "channel" << channel;
    }
        break;

    case TLValue::ChannelsKickFromChannel: {
        TLInputChannel channel;
        stream >> channel;
        TLInputUser userId;
        stream >> userId;
        bool kicked;
        stream >> kicked;
        qDebug() << request << "channel" << channel << "userId" << userId << "kicked" << kicked;
    }
        break;

    case TLValue::ChannelsLeaveChannel: {
        TLInputChannel channel;
        stream >> channel;
        qDebug() << request << "channel" << channel;
    }
        break;

    case TLValue::ChannelsReadHistory: {
        TLInputChannel channel;
        stream >> channel;
        quint32 maxId;
        stream >> maxId;
        qDebug() << request << "channel" << channel << "maxId" << maxId;
    }
        break;

    case TLValue::ChannelsReportSpam: {
        TLInputChannel channel;
        stream >> channel;
        TLInputUser userId;
        stream >> userId;
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "channel" << channel << "userId" << userId << "id" << id;
    }
        break;

    case TLValue::ChannelsToggleComments: {
        TLInputChannel channel;
        stream >> channel;
        bool enabled;
        stream >> enabled;
        qDebug() << request << "channel" << channel << "enabled" << enabled;
    }
        break;

    case TLValue::ChannelsUpdateUsername: {
        TLInputChannel channel;
        stream >> channel;
        QString username;
        stream >> username;
        qDebug() << request << "channel" << channel << "username" << username;
    }
        break;

    case TLValue::ContactsBlock: {
        TLInputUser id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::ContactsDeleteContact: {
        TLInputUser id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::ContactsDeleteContacts: {
        TLVector<TLInputUser> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::ContactsExportCard: {
        qDebug() << request;
    }
        break;

    case TLValue::ContactsGetBlocked: {
        quint32 offset;
        stream >> offset;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "offset" << offset << "limit" << limit;
    }
        break;

    case TLValue::ContactsGetContacts: {
        QString hash;
        stream >> hash;
        qDebug() << request << "hash" << hash;
    }
        break;

    case TLValue::ContactsGetStatuses: {
        qDebug() << request;
    }
        break;

    case TLValue::ContactsGetSuggested: {
        quint32 limit;
        stream >> limit;
        qDebug() << request << "limit" << limit;
    }
        break;

    case TLValue::ContactsImportCard: {
        TLVector<quint32> exportCard;
        stream >> exportCard;
        qDebug() << request << "exportCard" << exportCard;
    }
        break;

    case TLValue::ContactsImportContacts: {
        TLVector<TLInputContact> contacts;
        stream >> contacts;
        bool replace;
        stream >> replace;
        qDebug() << request << "contacts" << contacts << "replace" << replace;
    }
        break;

    case TLValue::ContactsResolveUsername: {
        QString username;
        stream >> username;
        qDebug() << request << "username" << username;
    }
        break;

    case TLValue::ContactsSearch: {
        QString q;
        stream >> q;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "q" << q << "limit" << limit;
    }
        break;

    case TLValue::ContactsUnblock: {
        TLInputUser id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::HelpGetAppChangelog: {
        QString deviceModel;
        stream >> deviceModel;
        QString systemVersion;
        stream >> systemVersion;
        QString appVersion;
        stream >> appVersion;
        QString langCode;
        stream >> langCode;
        qDebug() << request << "deviceModel" << deviceModel << "systemVersion" << systemVersion << "appVersion" << appVersion << "langCode" << langCode;
    }
        break;

    case TLValue::HelpGetAppUpdate: {
        QString deviceModel;
        stream >> deviceModel;
        QString systemVersion;
        stream >> systemVersion;
        QString appVersion;
        stream >> appVersion;
        QString langCode;
        stream >> langCode;
        qDebug() << request << "deviceModel" << deviceModel << "systemVersion" << systemVersion << "appVersion" << appVersion << "langCode" << langCode;
    }
        break;

    case TLValue::HelpGetConfig: {
        qDebug() << request;
    }
        break;

    case TLValue::HelpGetInviteText: {
        QString langCode;
        stream >> langCode;
        qDebug() << request << "langCode" << langCode;
    }
        break;

    case TLValue::HelpGetNearestDc: {
        qDebug() << request;
    }
        break;

    case TLValue::HelpGetSupport: {
        qDebug() << request;
    }
        break;

    case TLValue::HelpGetTermsOfService: {
        QString langCode;
        stream >> langCode;
        qDebug() << request << "langCode" << langCode;
    }
        break;

    case TLValue::HelpSaveAppLog: {
        TLVector<TLInputAppEvent> events;
        stream >> events;
        qDebug() << request << "events" << events;
    }
        break;

    case TLValue::InitConnection: {
        qDebug() << request;
    }
        break;

    case TLValue::InvokeAfterMsg: {
        qDebug() << request;
    }
        break;

    case TLValue::InvokeAfterMsgs: {
        qDebug() << request;
    }
        break;

    case TLValue::InvokeWithLayer: {
        qDebug() << request;
    }
        break;

    case TLValue::InvokeWithoutUpdates: {
        qDebug() << request;
    }
        break;

    case TLValue::MessagesAcceptEncryption: {
        TLInputEncryptedChat peer;
        stream >> peer;
        QByteArray gB;
        stream >> gB;
        quint64 keyFingerprint;
        stream >> keyFingerprint;
        qDebug() << request << "peer" << peer << "gB" << gB << "keyFingerprint" << keyFingerprint;
    }
        break;

    case TLValue::MessagesAddChatUser: {
        quint32 chatId;
        stream >> chatId;
        TLInputUser userId;
        stream >> userId;
        quint32 fwdLimit;
        stream >> fwdLimit;
        qDebug() << request << "chatId" << chatId << "userId" << userId << "fwdLimit" << fwdLimit;
    }
        break;

    case TLValue::MessagesCheckChatInvite: {
        QString hash;
        stream >> hash;
        qDebug() << request << "hash" << hash;
    }
        break;

    case TLValue::MessagesCreateChat: {
        TLVector<TLInputUser> users;
        stream >> users;
        QString title;
        stream >> title;
        qDebug() << request << "users" << users << "title" << title;
    }
        break;

    case TLValue::MessagesDeleteChatUser: {
        quint32 chatId;
        stream >> chatId;
        TLInputUser userId;
        stream >> userId;
        qDebug() << request << "chatId" << chatId << "userId" << userId;
    }
        break;

    case TLValue::MessagesDeleteHistory: {
        TLInputPeer peer;
        stream >> peer;
        quint32 maxId;
        stream >> maxId;
        qDebug() << request << "peer" << peer << "maxId" << maxId;
    }
        break;

    case TLValue::MessagesDeleteMessages: {
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::MessagesDiscardEncryption: {
        quint32 chatId;
        stream >> chatId;
        qDebug() << request << "chatId" << chatId;
    }
        break;

    case TLValue::MessagesEditChatAdmin: {
        quint32 chatId;
        stream >> chatId;
        TLInputUser userId;
        stream >> userId;
        bool isAdmin;
        stream >> isAdmin;
        qDebug() << request << "chatId" << chatId << "userId" << userId << "isAdmin" << isAdmin;
    }
        break;

    case TLValue::MessagesEditChatPhoto: {
        quint32 chatId;
        stream >> chatId;
        TLInputChatPhoto photo;
        stream >> photo;
        qDebug() << request << "chatId" << chatId << "photo" << photo;
    }
        break;

    case TLValue::MessagesEditChatTitle: {
        quint32 chatId;
        stream >> chatId;
        QString title;
        stream >> title;
        qDebug() << request << "chatId" << chatId << "title" << title;
    }
        break;

    case TLValue::MessagesExportChatInvite: {
        quint32 chatId;
        stream >> chatId;
        qDebug() << request << "chatId" << chatId;
    }
        break;

    case TLValue::MessagesForwardMessage: {
        TLInputPeer peer;
        stream >> peer;
        quint32 id;
        stream >> id;
        quint64 randomId;
        stream >> randomId;
        qDebug() << request << "peer" << peer << "id" << id << "randomId" << randomId;
    }
        break;

    case TLValue::MessagesGetAllStickers: {
        quint32 hash;
        stream >> hash;
        qDebug() << request << "hash" << hash;
    }
        break;

    case TLValue::MessagesGetChats: {
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::MessagesGetDhConfig: {
        quint32 version;
        stream >> version;
        quint32 randomLength;
        stream >> randomLength;
        qDebug() << request << "version" << version << "randomLength" << randomLength;
    }
        break;

    case TLValue::MessagesGetDialogs: {
        quint32 offsetDate;
        stream >> offsetDate;
        quint32 offsetId;
        stream >> offsetId;
        TLInputPeer offsetPeer;
        stream >> offsetPeer;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "offsetDate" << offsetDate << "offsetId" << offsetId << "offsetPeer" << offsetPeer << "limit" << limit;
    }
        break;

    case TLValue::MessagesGetDocumentByHash: {
        QByteArray sha256;
        stream >> sha256;
        quint32 size;
        stream >> size;
        QString mimeType;
        stream >> mimeType;
        qDebug() << request << "sha256" << sha256 << "size" << size << "mimeType" << mimeType;
    }
        break;

    case TLValue::MessagesGetFullChat: {
        quint32 chatId;
        stream >> chatId;
        qDebug() << request << "chatId" << chatId;
    }
        break;

    case TLValue::MessagesGetHistory: {
        TLInputPeer peer;
        stream >> peer;
        quint32 offsetId;
        stream >> offsetId;
        quint32 addOffset;
        stream >> addOffset;
        quint32 limit;
        stream >> limit;
        quint32 maxId;
        stream >> maxId;
        quint32 minId;
        stream >> minId;
        qDebug() << request << "peer" << peer << "offsetId" << offsetId << "addOffset" << addOffset << "limit" << limit << "maxId" << maxId << "minId" << minId;
    }
        break;

    case TLValue::MessagesGetInlineBotResults: {
        TLInputUser bot;
        stream >> bot;
        QString query;
        stream >> query;
        QString offset;
        stream >> offset;
        qDebug() << request << "bot" << bot << "query" << query << "offset" << offset;
    }
        break;

    case TLValue::MessagesGetMessages: {
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::MessagesGetMessagesViews: {
        TLInputPeer peer;
        stream >> peer;
        TLVector<quint32> id;
        stream >> id;
        bool increment;
        stream >> increment;
        qDebug() << request << "peer" << peer << "id" << id << "increment" << increment;
    }
        break;

    case TLValue::MessagesGetSavedGifs: {
        quint32 hash;
        stream >> hash;
        qDebug() << request << "hash" << hash;
    }
        break;

    case TLValue::MessagesGetStickerSet: {
        TLInputStickerSet stickerset;
        stream >> stickerset;
        qDebug() << request << "stickerset" << stickerset;
    }
        break;

    case TLValue::MessagesGetStickers: {
        QString emoticon;
        stream >> emoticon;
        QString hash;
        stream >> hash;
        qDebug() << request << "emoticon" << emoticon << "hash" << hash;
    }
        break;

    case TLValue::MessagesGetWebPagePreview: {
        QString message;
        stream >> message;
        qDebug() << request << "message" << message;
    }
        break;

    case TLValue::MessagesImportChatInvite: {
        QString hash;
        stream >> hash;
        qDebug() << request << "hash" << hash;
    }
        break;

    case TLValue::MessagesInstallStickerSet: {
        TLInputStickerSet stickerset;
        stream >> stickerset;
        bool disabled;
        stream >> disabled;
        qDebug() << request << "stickerset" << stickerset << "disabled" << disabled;
    }
        break;

    case TLValue::MessagesMigrateChat: {
        quint32 chatId;
        stream >> chatId;
        qDebug() << request << "chatId" << chatId;
    }
        break;

    case TLValue::MessagesReadEncryptedHistory: {
        TLInputEncryptedChat peer;
        stream >> peer;
        quint32 maxDate;
        stream >> maxDate;
        qDebug() << request << "peer" << peer << "maxDate" << maxDate;
    }
        break;

    case TLValue::MessagesReadHistory: {
        TLInputPeer peer;
        stream >> peer;
        quint32 maxId;
        stream >> maxId;
        qDebug() << request << "peer" << peer << "maxId" << maxId;
    }
        break;

    case TLValue::MessagesReadMessageContents: {
        TLVector<quint32> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::MessagesReceivedMessages: {
        quint32 maxId;
        stream >> maxId;
        qDebug() << request << "maxId" << maxId;
    }
        break;

    case TLValue::MessagesReceivedQueue: {
        quint32 maxQts;
        stream >> maxQts;
        qDebug() << request << "maxQts" << maxQts;
    }
        break;

    case TLValue::MessagesReorderStickerSets: {
        TLVector<quint64> order;
        stream >> order;
        qDebug() << request << "order" << order;
    }
        break;

    case TLValue::MessagesReportSpam: {
        TLInputPeer peer;
        stream >> peer;
        qDebug() << request << "peer" << peer;
    }
        break;

    case TLValue::MessagesRequestEncryption: {
        TLInputUser userId;
        stream >> userId;
        quint32 randomId;
        stream >> randomId;
        QByteArray gA;
        stream >> gA;
        qDebug() << request << "userId" << userId << "randomId" << randomId << "gA" << gA;
    }
        break;

    case TLValue::MessagesSaveGif: {
        TLInputDocument id;
        stream >> id;
        bool unsave;
        stream >> unsave;
        qDebug() << request << "id" << id << "unsave" << unsave;
    }
        break;

    case TLValue::MessagesSearchGifs: {
        QString q;
        stream >> q;
        quint32 offset;
        stream >> offset;
        qDebug() << request << "q" << q << "offset" << offset;
    }
        break;

    case TLValue::MessagesSearchGlobal: {
        QString q;
        stream >> q;
        quint32 offsetDate;
        stream >> offsetDate;
        TLInputPeer offsetPeer;
        stream >> offsetPeer;
        quint32 offsetId;
        stream >> offsetId;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "q" << q << "offsetDate" << offsetDate << "offsetPeer" << offsetPeer << "offsetId" << offsetId << "limit" << limit;
    }
        break;

    case TLValue::MessagesSendBroadcast: {
        TLVector<TLInputUser> contacts;
        stream >> contacts;
        TLVector<quint64> randomId;
        stream >> randomId;
        QString message;
        stream >> message;
        TLInputMedia media;
        stream >> media;
        qDebug() << request << "contacts" << contacts << "randomId" << randomId << "message" << message << "media" << media;
    }
        break;

    case TLValue::MessagesSendEncrypted: {
        TLInputEncryptedChat peer;
        stream >> peer;
        quint64 randomId;
        stream >> randomId;
        QByteArray data;
        stream >> data;
        qDebug() << request << "peer" << peer << "randomId" << randomId << "data" << data;
    }
        break;

    case TLValue::MessagesSendEncryptedFile: {
        TLInputEncryptedChat peer;
        stream >> peer;
        quint64 randomId;
        stream >> randomId;
        QByteArray data;
        stream >> data;
        TLInputEncryptedFile file;
        stream >> file;
        qDebug() << request << "peer" << peer << "randomId" << randomId << "data" << data << "file" << file;
    }
        break;

    case TLValue::MessagesSendEncryptedService: {
        TLInputEncryptedChat peer;
        stream >> peer;
        quint64 randomId;
        stream >> randomId;
        QByteArray data;
        stream >> data;
        qDebug() << request << "peer" << peer << "randomId" << randomId << "data" << data;
    }
        break;

    case TLValue::MessagesSetEncryptedTyping: {
        TLInputEncryptedChat peer;
        stream >> peer;
        bool typing;
        stream >> typing;
        qDebug() << request << "peer" << peer << "typing" << typing;
    }
        break;

    case TLValue::MessagesSetTyping: {
        TLInputPeer peer;
        stream >> peer;
        TLSendMessageAction action;
        stream >> action;
        qDebug() << request << "peer" << peer << "action" << action;
    }
        break;

    case TLValue::MessagesStartBot: {
        TLInputUser bot;
        stream >> bot;
        TLInputPeer peer;
        stream >> peer;
        quint64 randomId;
        stream >> randomId;
        QString startParam;
        stream >> startParam;
        qDebug() << request << "bot" << bot << "peer" << peer << "randomId" << randomId << "startParam" << startParam;
    }
        break;

    case TLValue::MessagesToggleChatAdmins: {
        quint32 chatId;
        stream >> chatId;
        bool enabled;
        stream >> enabled;
        qDebug() << request << "chatId" << chatId << "enabled" << enabled;
    }
        break;

    case TLValue::MessagesUninstallStickerSet: {
        TLInputStickerSet stickerset;
        stream >> stickerset;
        qDebug() << request << "stickerset" << stickerset;
    }
        break;

    case TLValue::PhotosDeletePhotos: {
        TLVector<TLInputPhoto> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::PhotosGetUserPhotos: {
        TLInputUser userId;
        stream >> userId;
        quint32 offset;
        stream >> offset;
        quint64 maxId;
        stream >> maxId;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "userId" << userId << "offset" << offset << "maxId" << maxId << "limit" << limit;
    }
        break;

    case TLValue::PhotosUpdateProfilePhoto: {
        TLInputPhoto id;
        stream >> id;
        TLInputPhotoCrop crop;
        stream >> crop;
        qDebug() << request << "id" << id << "crop" << crop;
    }
        break;

    case TLValue::PhotosUploadProfilePhoto: {
        TLInputFile file;
        stream >> file;
        QString caption;
        stream >> caption;
        TLInputGeoPoint geoPoint;
        stream >> geoPoint;
        TLInputPhotoCrop crop;
        stream >> crop;
        qDebug() << request << "file" << file << "caption" << caption << "geoPoint" << geoPoint << "crop" << crop;
    }
        break;

    case TLValue::UpdatesGetChannelDifference: {
        TLInputChannel channel;
        stream >> channel;
        TLChannelMessagesFilter filter;
        stream >> filter;
        quint32 pts;
        stream >> pts;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "channel" << channel << "filter" << filter << "pts" << pts << "limit" << limit;
    }
        break;

    case TLValue::UpdatesGetDifference: {
        quint32 pts;
        stream >> pts;
        quint32 date;
        stream >> date;
        quint32 qts;
        stream >> qts;
        qDebug() << request << "pts" << pts << "date" << date << "qts" << qts;
    }
        break;

    case TLValue::UpdatesGetState: {
        qDebug() << request;
    }
        break;

    case TLValue::UploadGetFile: {
        TLInputFileLocation location;
        stream >> location;
        quint32 offset;
        stream >> offset;
        quint32 limit;
        stream >> limit;
        qDebug() << request << "location" << location << "offset" << offset << "limit" << limit;
    }
        break;

    case TLValue::UploadSaveBigFilePart: {
        quint64 fileId;
        stream >> fileId;
        quint32 filePart;
        stream >> filePart;
        quint32 fileTotalParts;
        stream >> fileTotalParts;
        QByteArray bytes;
        stream >> bytes;
        qDebug() << request << "fileId" << fileId << "filePart" << filePart << "fileTotalParts" << fileTotalParts << "bytes" << bytes;
    }
        break;

    case TLValue::UploadSaveFilePart: {
        quint64 fileId;
        stream >> fileId;
        quint32 filePart;
        stream >> filePart;
        QByteArray bytes;
        stream >> bytes;
        qDebug() << request << "fileId" << fileId << "filePart" << filePart << "bytes" << bytes;
    }
        break;

    case TLValue::UsersGetFullUser: {
        TLInputUser id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    case TLValue::UsersGetUsers: {
        TLVector<TLInputUser> id;
        stream >> id;
        qDebug() << request << "id" << id;
    }
        break;

    // End of generated RPC debug cases
    default:
        break;
    }
}
