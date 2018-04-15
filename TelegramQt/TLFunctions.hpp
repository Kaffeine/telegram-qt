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

#ifndef TELEGRAM_TL_FUNCTIONS_HPP
#define TELEGRAM_TL_FUNCTIONS_HPP

#include "TLTypes.hpp"

namespace Telegram {

namespace TLFunctions {

// Generated TLFunctions
struct TLAccountChangePhone
{
    static constexpr TLValue predicate = TLValue::AccountChangePhone;
    QString phoneNumber;
    QString phoneCodeHash;
    QString phoneCode;
};

struct TLAccountCheckUsername
{
    static constexpr TLValue predicate = TLValue::AccountCheckUsername;
    QString username;
};

struct TLAccountDeleteAccount
{
    static constexpr TLValue predicate = TLValue::AccountDeleteAccount;
    QString reason;
};

struct TLAccountGetAccountTTL
{
    static constexpr TLValue predicate = TLValue::AccountGetAccountTTL;
};

struct TLAccountGetAuthorizations
{
    static constexpr TLValue predicate = TLValue::AccountGetAuthorizations;
};

struct TLAccountGetNotifySettings
{
    static constexpr TLValue predicate = TLValue::AccountGetNotifySettings;
    TLInputNotifyPeer peer;
};

struct TLAccountGetPassword
{
    static constexpr TLValue predicate = TLValue::AccountGetPassword;
};

struct TLAccountGetPasswordSettings
{
    static constexpr TLValue predicate = TLValue::AccountGetPasswordSettings;
    QByteArray currentPasswordHash;
};

struct TLAccountGetPrivacy
{
    static constexpr TLValue predicate = TLValue::AccountGetPrivacy;
    TLInputPrivacyKey key;
};

struct TLAccountGetWallPapers
{
    static constexpr TLValue predicate = TLValue::AccountGetWallPapers;
};

struct TLAccountRegisterDevice
{
    static constexpr TLValue predicate = TLValue::AccountRegisterDevice;
    quint32 tokenType = 0;
    QString token;
    QString deviceModel;
    QString systemVersion;
    QString appVersion;
    bool appSandbox = false;
    QString langCode;
};

struct TLAccountReportPeer
{
    static constexpr TLValue predicate = TLValue::AccountReportPeer;
    TLInputPeer peer;
    TLReportReason reason;
};

struct TLAccountResetAuthorization
{
    static constexpr TLValue predicate = TLValue::AccountResetAuthorization;
    quint64 hash = 0;
};

struct TLAccountResetNotifySettings
{
    static constexpr TLValue predicate = TLValue::AccountResetNotifySettings;
};

struct TLAccountSendChangePhoneCode
{
    static constexpr TLValue predicate = TLValue::AccountSendChangePhoneCode;
    QString phoneNumber;
};

struct TLAccountSetAccountTTL
{
    static constexpr TLValue predicate = TLValue::AccountSetAccountTTL;
    TLAccountDaysTTL ttl;
};

struct TLAccountSetPrivacy
{
    static constexpr TLValue predicate = TLValue::AccountSetPrivacy;
    TLInputPrivacyKey key;
    TLVector<TLInputPrivacyRule*> rules;
};

struct TLAccountUnregisterDevice
{
    static constexpr TLValue predicate = TLValue::AccountUnregisterDevice;
    quint32 tokenType = 0;
    QString token;
};

struct TLAccountUpdateDeviceLocked
{
    static constexpr TLValue predicate = TLValue::AccountUpdateDeviceLocked;
    quint32 period = 0;
};

struct TLAccountUpdateNotifySettings
{
    static constexpr TLValue predicate = TLValue::AccountUpdateNotifySettings;
    TLInputNotifyPeer peer;
    TLInputPeerNotifySettings settings;
};

struct TLAccountUpdatePasswordSettings
{
    static constexpr TLValue predicate = TLValue::AccountUpdatePasswordSettings;
    QByteArray currentPasswordHash;
    TLAccountPasswordInputSettings newSettings;
};

struct TLAccountUpdateProfile
{
    static constexpr TLValue predicate = TLValue::AccountUpdateProfile;
    QString firstName;
    QString lastName;
};

struct TLAccountUpdateStatus
{
    static constexpr TLValue predicate = TLValue::AccountUpdateStatus;
    bool offline = false;
};

struct TLAccountUpdateUsername
{
    static constexpr TLValue predicate = TLValue::AccountUpdateUsername;
    QString username;
};

struct TLAuthBindTempAuthKey
{
    static constexpr TLValue predicate = TLValue::AuthBindTempAuthKey;
    quint64 permAuthKeyId = 0;
    quint64 nonce = 0;
    quint32 expiresAt = 0;
    QByteArray encryptedMessage;
};

struct TLAuthCheckPassword
{
    static constexpr TLValue predicate = TLValue::AuthCheckPassword;
    QByteArray passwordHash;
};

struct TLAuthCheckPhone
{
    static constexpr TLValue predicate = TLValue::AuthCheckPhone;
    QString phoneNumber;
};

struct TLAuthExportAuthorization
{
    static constexpr TLValue predicate = TLValue::AuthExportAuthorization;
    quint32 dcId = 0;
};

struct TLAuthImportAuthorization
{
    static constexpr TLValue predicate = TLValue::AuthImportAuthorization;
    quint32 id = 0;
    QByteArray bytes;
};

struct TLAuthImportBotAuthorization
{
    static constexpr TLValue predicate = TLValue::AuthImportBotAuthorization;
    quint32 flags = 0;
    quint32 apiId = 0;
    QString apiHash;
    QString botAuthToken;
};

struct TLAuthLogOut
{
    static constexpr TLValue predicate = TLValue::AuthLogOut;
};

struct TLAuthRecoverPassword
{
    static constexpr TLValue predicate = TLValue::AuthRecoverPassword;
    QString code;
};

struct TLAuthRequestPasswordRecovery
{
    static constexpr TLValue predicate = TLValue::AuthRequestPasswordRecovery;
};

struct TLAuthResetAuthorizations
{
    static constexpr TLValue predicate = TLValue::AuthResetAuthorizations;
};

struct TLAuthSendCall
{
    static constexpr TLValue predicate = TLValue::AuthSendCall;
    QString phoneNumber;
    QString phoneCodeHash;
};

struct TLAuthSendCode
{
    static constexpr TLValue predicate = TLValue::AuthSendCode;
    QString phoneNumber;
    quint32 smsType = 0;
    quint32 apiId = 0;
    QString apiHash;
    QString langCode;
};

struct TLAuthSendInvites
{
    static constexpr TLValue predicate = TLValue::AuthSendInvites;
    TLVector<QString*> phoneNumbers;
    QString message;
};

struct TLAuthSendSms
{
    static constexpr TLValue predicate = TLValue::AuthSendSms;
    QString phoneNumber;
    QString phoneCodeHash;
};

struct TLAuthSignIn
{
    static constexpr TLValue predicate = TLValue::AuthSignIn;
    QString phoneNumber;
    QString phoneCodeHash;
    QString phoneCode;
};

struct TLAuthSignUp
{
    static constexpr TLValue predicate = TLValue::AuthSignUp;
    QString phoneNumber;
    QString phoneCodeHash;
    QString phoneCode;
    QString firstName;
    QString lastName;
};

struct TLChannelsCheckUsername
{
    static constexpr TLValue predicate = TLValue::ChannelsCheckUsername;
    TLInputChannel channel;
    QString username;
};

struct TLChannelsCreateChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsCreateChannel;
    quint32 flags = 0;
    QString title;
    QString about;
};

struct TLChannelsDeleteChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsDeleteChannel;
    TLInputChannel channel;
};

struct TLChannelsDeleteMessages
{
    static constexpr TLValue predicate = TLValue::ChannelsDeleteMessages;
    TLInputChannel channel;
    TLVector<quint32*> id;
};

struct TLChannelsDeleteUserHistory
{
    static constexpr TLValue predicate = TLValue::ChannelsDeleteUserHistory;
    TLInputChannel channel;
    TLInputUser userId;
};

struct TLChannelsEditAbout
{
    static constexpr TLValue predicate = TLValue::ChannelsEditAbout;
    TLInputChannel channel;
    QString about;
};

struct TLChannelsEditAdmin
{
    static constexpr TLValue predicate = TLValue::ChannelsEditAdmin;
    TLInputChannel channel;
    TLInputUser userId;
    TLChannelParticipantRole role;
};

struct TLChannelsEditPhoto
{
    static constexpr TLValue predicate = TLValue::ChannelsEditPhoto;
    TLInputChannel channel;
    TLInputChatPhoto photo;
};

struct TLChannelsEditTitle
{
    static constexpr TLValue predicate = TLValue::ChannelsEditTitle;
    TLInputChannel channel;
    QString title;
};

struct TLChannelsExportInvite
{
    static constexpr TLValue predicate = TLValue::ChannelsExportInvite;
    TLInputChannel channel;
};

struct TLChannelsGetChannels
{
    static constexpr TLValue predicate = TLValue::ChannelsGetChannels;
    TLVector<TLInputChannel*> id;
};

struct TLChannelsGetDialogs
{
    static constexpr TLValue predicate = TLValue::ChannelsGetDialogs;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLChannelsGetFullChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsGetFullChannel;
    TLInputChannel channel;
};

struct TLChannelsGetImportantHistory
{
    static constexpr TLValue predicate = TLValue::ChannelsGetImportantHistory;
    TLInputChannel channel;
    quint32 offsetId = 0;
    quint32 addOffset = 0;
    quint32 limit = 0;
    quint32 maxId = 0;
    quint32 minId = 0;
};

struct TLChannelsGetMessages
{
    static constexpr TLValue predicate = TLValue::ChannelsGetMessages;
    TLInputChannel channel;
    TLVector<quint32*> id;
};

struct TLChannelsGetParticipant
{
    static constexpr TLValue predicate = TLValue::ChannelsGetParticipant;
    TLInputChannel channel;
    TLInputUser userId;
};

struct TLChannelsGetParticipants
{
    static constexpr TLValue predicate = TLValue::ChannelsGetParticipants;
    TLInputChannel channel;
    TLChannelParticipantsFilter filter;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLChannelsInviteToChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsInviteToChannel;
    TLInputChannel channel;
    TLVector<TLInputUser*> users;
};

struct TLChannelsJoinChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsJoinChannel;
    TLInputChannel channel;
};

struct TLChannelsKickFromChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsKickFromChannel;
    TLInputChannel channel;
    TLInputUser userId;
    bool kicked = false;
};

struct TLChannelsLeaveChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsLeaveChannel;
    TLInputChannel channel;
};

struct TLChannelsReadHistory
{
    static constexpr TLValue predicate = TLValue::ChannelsReadHistory;
    TLInputChannel channel;
    quint32 maxId = 0;
};

struct TLChannelsReportSpam
{
    static constexpr TLValue predicate = TLValue::ChannelsReportSpam;
    TLInputChannel channel;
    TLInputUser userId;
    TLVector<quint32*> id;
};

struct TLChannelsToggleComments
{
    static constexpr TLValue predicate = TLValue::ChannelsToggleComments;
    TLInputChannel channel;
    bool enabled = false;
};

struct TLChannelsUpdateUsername
{
    static constexpr TLValue predicate = TLValue::ChannelsUpdateUsername;
    TLInputChannel channel;
    QString username;
};

struct TLContactsBlock
{
    static constexpr TLValue predicate = TLValue::ContactsBlock;
    TLInputUser id;
};

struct TLContactsDeleteContact
{
    static constexpr TLValue predicate = TLValue::ContactsDeleteContact;
    TLInputUser id;
};

struct TLContactsDeleteContacts
{
    static constexpr TLValue predicate = TLValue::ContactsDeleteContacts;
    TLVector<TLInputUser*> id;
};

struct TLContactsExportCard
{
    static constexpr TLValue predicate = TLValue::ContactsExportCard;
};

struct TLContactsGetBlocked
{
    static constexpr TLValue predicate = TLValue::ContactsGetBlocked;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLContactsGetContacts
{
    static constexpr TLValue predicate = TLValue::ContactsGetContacts;
    QString hash;
};

struct TLContactsGetStatuses
{
    static constexpr TLValue predicate = TLValue::ContactsGetStatuses;
};

struct TLContactsGetSuggested
{
    static constexpr TLValue predicate = TLValue::ContactsGetSuggested;
    quint32 limit = 0;
};

struct TLContactsImportCard
{
    static constexpr TLValue predicate = TLValue::ContactsImportCard;
    TLVector<quint32*> exportCard;
};

struct TLContactsImportContacts
{
    static constexpr TLValue predicate = TLValue::ContactsImportContacts;
    TLVector<TLInputContact*> contacts;
    bool replace = false;
};

struct TLContactsResolveUsername
{
    static constexpr TLValue predicate = TLValue::ContactsResolveUsername;
    QString username;
};

struct TLContactsSearch
{
    static constexpr TLValue predicate = TLValue::ContactsSearch;
    QString q;
    quint32 limit = 0;
};

struct TLContactsUnblock
{
    static constexpr TLValue predicate = TLValue::ContactsUnblock;
    TLInputUser id;
};

struct TLHelpGetAppChangelog
{
    static constexpr TLValue predicate = TLValue::HelpGetAppChangelog;
    QString deviceModel;
    QString systemVersion;
    QString appVersion;
    QString langCode;
};

struct TLHelpGetAppUpdate
{
    static constexpr TLValue predicate = TLValue::HelpGetAppUpdate;
    QString deviceModel;
    QString systemVersion;
    QString appVersion;
    QString langCode;
};

struct TLHelpGetConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetConfig;
};

struct TLHelpGetInviteText
{
    static constexpr TLValue predicate = TLValue::HelpGetInviteText;
    QString langCode;
};

struct TLHelpGetNearestDc
{
    static constexpr TLValue predicate = TLValue::HelpGetNearestDc;
};

struct TLHelpGetSupport
{
    static constexpr TLValue predicate = TLValue::HelpGetSupport;
};

struct TLHelpGetTermsOfService
{
    static constexpr TLValue predicate = TLValue::HelpGetTermsOfService;
    QString langCode;
};

struct TLHelpSaveAppLog
{
    static constexpr TLValue predicate = TLValue::HelpSaveAppLog;
    TLVector<TLInputAppEvent*> events;
};

struct TLInitConnection
{
    static constexpr TLValue predicate = TLValue::InitConnection;
};

struct TLInvokeAfterMsg
{
    static constexpr TLValue predicate = TLValue::InvokeAfterMsg;
};

struct TLInvokeAfterMsgs
{
    static constexpr TLValue predicate = TLValue::InvokeAfterMsgs;
};

struct TLInvokeWithLayer
{
    static constexpr TLValue predicate = TLValue::InvokeWithLayer;
};

struct TLInvokeWithoutUpdates
{
    static constexpr TLValue predicate = TLValue::InvokeWithoutUpdates;
};

struct TLMessagesAcceptEncryption
{
    static constexpr TLValue predicate = TLValue::MessagesAcceptEncryption;
    TLInputEncryptedChat peer;
    QByteArray gB;
    quint64 keyFingerprint = 0;
};

struct TLMessagesAddChatUser
{
    static constexpr TLValue predicate = TLValue::MessagesAddChatUser;
    quint32 chatId = 0;
    TLInputUser userId;
    quint32 fwdLimit = 0;
};

struct TLMessagesCheckChatInvite
{
    static constexpr TLValue predicate = TLValue::MessagesCheckChatInvite;
    QString hash;
};

struct TLMessagesCreateChat
{
    static constexpr TLValue predicate = TLValue::MessagesCreateChat;
    TLVector<TLInputUser*> users;
    QString title;
};

struct TLMessagesDeleteChatUser
{
    static constexpr TLValue predicate = TLValue::MessagesDeleteChatUser;
    quint32 chatId = 0;
    TLInputUser userId;
};

struct TLMessagesDeleteHistory
{
    static constexpr TLValue predicate = TLValue::MessagesDeleteHistory;
    TLInputPeer peer;
    quint32 maxId = 0;
};

struct TLMessagesDeleteMessages
{
    static constexpr TLValue predicate = TLValue::MessagesDeleteMessages;
    TLVector<quint32*> id;
};

struct TLMessagesDiscardEncryption
{
    static constexpr TLValue predicate = TLValue::MessagesDiscardEncryption;
    quint32 chatId = 0;
};

struct TLMessagesEditChatAdmin
{
    static constexpr TLValue predicate = TLValue::MessagesEditChatAdmin;
    quint32 chatId = 0;
    TLInputUser userId;
    bool isAdmin = false;
};

struct TLMessagesEditChatPhoto
{
    static constexpr TLValue predicate = TLValue::MessagesEditChatPhoto;
    quint32 chatId = 0;
    TLInputChatPhoto photo;
};

struct TLMessagesEditChatTitle
{
    static constexpr TLValue predicate = TLValue::MessagesEditChatTitle;
    quint32 chatId = 0;
    QString title;
};

struct TLMessagesExportChatInvite
{
    static constexpr TLValue predicate = TLValue::MessagesExportChatInvite;
    quint32 chatId = 0;
};

struct TLMessagesForwardMessage
{
    static constexpr TLValue predicate = TLValue::MessagesForwardMessage;
    TLInputPeer peer;
    quint32 id = 0;
    quint64 randomId = 0;
};

struct TLMessagesForwardMessages
{
    static constexpr TLValue predicate = TLValue::MessagesForwardMessages;
    quint32 flags = 0;
    TLInputPeer fromPeer;
    TLVector<quint32*> id;
    TLVector<quint64*> randomId;
    TLInputPeer toPeer;
};

struct TLMessagesGetAllStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetAllStickers;
    quint32 hash = 0;
};

struct TLMessagesGetChats
{
    static constexpr TLValue predicate = TLValue::MessagesGetChats;
    TLVector<quint32*> id;
};

struct TLMessagesGetDhConfig
{
    static constexpr TLValue predicate = TLValue::MessagesGetDhConfig;
    quint32 version = 0;
    quint32 randomLength = 0;
};

struct TLMessagesGetDialogs
{
    static constexpr TLValue predicate = TLValue::MessagesGetDialogs;
    quint32 offsetDate = 0;
    quint32 offsetId = 0;
    TLInputPeer offsetPeer;
    quint32 limit = 0;
};

struct TLMessagesGetDocumentByHash
{
    static constexpr TLValue predicate = TLValue::MessagesGetDocumentByHash;
    QByteArray sha256;
    quint32 size = 0;
    QString mimeType;
};

struct TLMessagesGetFullChat
{
    static constexpr TLValue predicate = TLValue::MessagesGetFullChat;
    quint32 chatId = 0;
};

struct TLMessagesGetHistory
{
    static constexpr TLValue predicate = TLValue::MessagesGetHistory;
    TLInputPeer peer;
    quint32 offsetId = 0;
    quint32 addOffset = 0;
    quint32 limit = 0;
    quint32 maxId = 0;
    quint32 minId = 0;
};

struct TLMessagesGetInlineBotResults
{
    static constexpr TLValue predicate = TLValue::MessagesGetInlineBotResults;
    TLInputUser bot;
    QString query;
    QString offset;
};

struct TLMessagesGetMessages
{
    static constexpr TLValue predicate = TLValue::MessagesGetMessages;
    TLVector<quint32*> id;
};

struct TLMessagesGetMessagesViews
{
    static constexpr TLValue predicate = TLValue::MessagesGetMessagesViews;
    TLInputPeer peer;
    TLVector<quint32*> id;
    bool increment = false;
};

struct TLMessagesGetSavedGifs
{
    static constexpr TLValue predicate = TLValue::MessagesGetSavedGifs;
    quint32 hash = 0;
};

struct TLMessagesGetStickerSet
{
    static constexpr TLValue predicate = TLValue::MessagesGetStickerSet;
    TLInputStickerSet stickerset;
};

struct TLMessagesGetStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetStickers;
    QString emoticon;
    QString hash;
};

struct TLMessagesGetWebPagePreview
{
    static constexpr TLValue predicate = TLValue::MessagesGetWebPagePreview;
    QString message;
};

struct TLMessagesImportChatInvite
{
    static constexpr TLValue predicate = TLValue::MessagesImportChatInvite;
    QString hash;
};

struct TLMessagesInstallStickerSet
{
    static constexpr TLValue predicate = TLValue::MessagesInstallStickerSet;
    TLInputStickerSet stickerset;
    bool disabled = false;
};

struct TLMessagesMigrateChat
{
    static constexpr TLValue predicate = TLValue::MessagesMigrateChat;
    quint32 chatId = 0;
};

struct TLMessagesReadEncryptedHistory
{
    static constexpr TLValue predicate = TLValue::MessagesReadEncryptedHistory;
    TLInputEncryptedChat peer;
    quint32 maxDate = 0;
};

struct TLMessagesReadHistory
{
    static constexpr TLValue predicate = TLValue::MessagesReadHistory;
    TLInputPeer peer;
    quint32 maxId = 0;
};

struct TLMessagesReadMessageContents
{
    static constexpr TLValue predicate = TLValue::MessagesReadMessageContents;
    TLVector<quint32*> id;
};

struct TLMessagesReceivedMessages
{
    static constexpr TLValue predicate = TLValue::MessagesReceivedMessages;
    quint32 maxId = 0;
};

struct TLMessagesReceivedQueue
{
    static constexpr TLValue predicate = TLValue::MessagesReceivedQueue;
    quint32 maxQts = 0;
};

struct TLMessagesReorderStickerSets
{
    static constexpr TLValue predicate = TLValue::MessagesReorderStickerSets;
    TLVector<quint64*> order;
};

struct TLMessagesReportSpam
{
    static constexpr TLValue predicate = TLValue::MessagesReportSpam;
    TLInputPeer peer;
};

struct TLMessagesRequestEncryption
{
    static constexpr TLValue predicate = TLValue::MessagesRequestEncryption;
    TLInputUser userId;
    quint32 randomId = 0;
    QByteArray gA;
};

struct TLMessagesSaveGif
{
    static constexpr TLValue predicate = TLValue::MessagesSaveGif;
    TLInputDocument id;
    bool unsave = false;
};

struct TLMessagesSearch
{
    static constexpr TLValue predicate = TLValue::MessagesSearch;
    quint32 flags = 0;
    TLInputPeer peer;
    QString q;
    TLMessagesFilter filter;
    quint32 minDate = 0;
    quint32 maxDate = 0;
    quint32 offset = 0;
    quint32 maxId = 0;
    quint32 limit = 0;
};

struct TLMessagesSearchGifs
{
    static constexpr TLValue predicate = TLValue::MessagesSearchGifs;
    QString q;
    quint32 offset = 0;
};

struct TLMessagesSearchGlobal
{
    static constexpr TLValue predicate = TLValue::MessagesSearchGlobal;
    QString q;
    quint32 offsetDate = 0;
    TLInputPeer offsetPeer;
    quint32 offsetId = 0;
    quint32 limit = 0;
};

struct TLMessagesSendBroadcast
{
    static constexpr TLValue predicate = TLValue::MessagesSendBroadcast;
    TLVector<TLInputUser*> contacts;
    TLVector<quint64*> randomId;
    QString message;
    TLInputMedia media;
};

struct TLMessagesSendEncrypted
{
    static constexpr TLValue predicate = TLValue::MessagesSendEncrypted;
    TLInputEncryptedChat peer;
    quint64 randomId = 0;
    QByteArray data;
};

struct TLMessagesSendEncryptedFile
{
    static constexpr TLValue predicate = TLValue::MessagesSendEncryptedFile;
    TLInputEncryptedChat peer;
    quint64 randomId = 0;
    QByteArray data;
    TLInputEncryptedFile file;
};

struct TLMessagesSendEncryptedService
{
    static constexpr TLValue predicate = TLValue::MessagesSendEncryptedService;
    TLInputEncryptedChat peer;
    quint64 randomId = 0;
    QByteArray data;
};

struct TLMessagesSendInlineBotResult
{
    static constexpr TLValue predicate = TLValue::MessagesSendInlineBotResult;
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    quint64 randomId = 0;
    quint64 queryId = 0;
    QString id;
};

struct TLMessagesSendMedia
{
    static constexpr TLValue predicate = TLValue::MessagesSendMedia;
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    TLInputMedia media;
    quint64 randomId = 0;
    TLReplyMarkup replyMarkup;
};

struct TLMessagesSendMessage
{
    static constexpr TLValue predicate = TLValue::MessagesSendMessage;
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    QString message;
    quint64 randomId = 0;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity*> entities;
};

struct TLMessagesSetEncryptedTyping
{
    static constexpr TLValue predicate = TLValue::MessagesSetEncryptedTyping;
    TLInputEncryptedChat peer;
    bool typing = false;
};

struct TLMessagesSetInlineBotResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetInlineBotResults;
    quint32 flags = 0;
    quint64 queryId = 0;
    TLVector<TLInputBotInlineResult*> results;
    quint32 cacheTime = 0;
    QString nextOffset;
};

struct TLMessagesSetTyping
{
    static constexpr TLValue predicate = TLValue::MessagesSetTyping;
    TLInputPeer peer;
    TLSendMessageAction action;
};

struct TLMessagesStartBot
{
    static constexpr TLValue predicate = TLValue::MessagesStartBot;
    TLInputUser bot;
    TLInputPeer peer;
    quint64 randomId = 0;
    QString startParam;
};

struct TLMessagesToggleChatAdmins
{
    static constexpr TLValue predicate = TLValue::MessagesToggleChatAdmins;
    quint32 chatId = 0;
    bool enabled = false;
};

struct TLMessagesUninstallStickerSet
{
    static constexpr TLValue predicate = TLValue::MessagesUninstallStickerSet;
    TLInputStickerSet stickerset;
};

struct TLPhotosDeletePhotos
{
    static constexpr TLValue predicate = TLValue::PhotosDeletePhotos;
    TLVector<TLInputPhoto*> id;
};

struct TLPhotosGetUserPhotos
{
    static constexpr TLValue predicate = TLValue::PhotosGetUserPhotos;
    TLInputUser userId;
    quint32 offset = 0;
    quint64 maxId = 0;
    quint32 limit = 0;
};

struct TLPhotosUpdateProfilePhoto
{
    static constexpr TLValue predicate = TLValue::PhotosUpdateProfilePhoto;
    TLInputPhoto id;
    TLInputPhotoCrop crop;
};

struct TLPhotosUploadProfilePhoto
{
    static constexpr TLValue predicate = TLValue::PhotosUploadProfilePhoto;
    TLInputFile file;
    QString caption;
    TLInputGeoPoint geoPoint;
    TLInputPhotoCrop crop;
};

struct TLUpdatesGetChannelDifference
{
    static constexpr TLValue predicate = TLValue::UpdatesGetChannelDifference;
    TLInputChannel channel;
    TLChannelMessagesFilter filter;
    quint32 pts = 0;
    quint32 limit = 0;
};

struct TLUpdatesGetDifference
{
    static constexpr TLValue predicate = TLValue::UpdatesGetDifference;
    quint32 pts = 0;
    quint32 date = 0;
    quint32 qts = 0;
};

struct TLUpdatesGetState
{
    static constexpr TLValue predicate = TLValue::UpdatesGetState;
};

struct TLUploadGetFile
{
    static constexpr TLValue predicate = TLValue::UploadGetFile;
    TLInputFileLocation location;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLUploadSaveBigFilePart
{
    static constexpr TLValue predicate = TLValue::UploadSaveBigFilePart;
    quint64 fileId = 0;
    quint32 filePart = 0;
    quint32 fileTotalParts = 0;
    QByteArray bytes;
};

struct TLUploadSaveFilePart
{
    static constexpr TLValue predicate = TLValue::UploadSaveFilePart;
    quint64 fileId = 0;
    quint32 filePart = 0;
    QByteArray bytes;
};

struct TLUsersGetFullUser
{
    static constexpr TLValue predicate = TLValue::UsersGetFullUser;
    TLInputUser id;
};

struct TLUsersGetUsers
{
    static constexpr TLValue predicate = TLValue::UsersGetUsers;
    TLVector<TLInputUser*> id;
};
// End of generated TLFunctions

} // TLFunctions

} // Telegram

#endif // TELEGRAM_TL_FUNCTIONS_HPP
