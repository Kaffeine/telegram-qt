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

struct TLAccountConfirmPhone
{
    static constexpr TLValue predicate = TLValue::AccountConfirmPhone;
    QString phoneCodeHash;
    QString phoneCode;
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

struct TLAccountGetTmpPassword
{
    static constexpr TLValue predicate = TLValue::AccountGetTmpPassword;
    QByteArray passwordHash;
    quint32 period = 0;
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
    quint32 flags = 0;
    QString phoneNumber;
    bool currentNumber = false;
};

struct TLAccountSendConfirmPhoneCode
{
    static constexpr TLValue predicate = TLValue::AccountSendConfirmPhoneCode;
    quint32 flags = 0;
    QString hash;
    bool currentNumber = false;
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
    TLVector<TLInputPrivacyRule> rules;
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
    quint32 flags = 0;
    QString firstName;
    QString lastName;
    QString about;
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

struct TLAuthCancelCode
{
    static constexpr TLValue predicate = TLValue::AuthCancelCode;
    QString phoneNumber;
    QString phoneCodeHash;
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

struct TLAuthDropTempAuthKeys
{
    static constexpr TLValue predicate = TLValue::AuthDropTempAuthKeys;
    TLVector<quint64> exceptAuthKeys;
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

struct TLAuthResendCode
{
    static constexpr TLValue predicate = TLValue::AuthResendCode;
    QString phoneNumber;
    QString phoneCodeHash;
};

struct TLAuthResetAuthorizations
{
    static constexpr TLValue predicate = TLValue::AuthResetAuthorizations;
};

struct TLAuthSendCode
{
    static constexpr TLValue predicate = TLValue::AuthSendCode;
    quint32 flags = 0;
    QString phoneNumber;
    bool currentNumber = false;
    quint32 apiId = 0;
    QString apiHash;
};

struct TLAuthSendInvites
{
    static constexpr TLValue predicate = TLValue::AuthSendInvites;
    TLVector<QString> phoneNumbers;
    QString message;
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

struct TLBotsAnswerWebhookJSONQuery
{
    static constexpr TLValue predicate = TLValue::BotsAnswerWebhookJSONQuery;
    quint64 queryId = 0;
    TLDataJSON data;
};

struct TLBotsSendCustomRequest
{
    static constexpr TLValue predicate = TLValue::BotsSendCustomRequest;
    QString customMethod;
    TLDataJSON params;
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

struct TLChannelsDeleteHistory
{
    static constexpr TLValue predicate = TLValue::ChannelsDeleteHistory;
    TLInputChannel channel;
    quint32 maxId = 0;
};

struct TLChannelsDeleteMessages
{
    static constexpr TLValue predicate = TLValue::ChannelsDeleteMessages;
    TLInputChannel channel;
    TLVector<quint32> id;
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
    TLChannelAdminRights adminRights;
};

struct TLChannelsEditBanned
{
    static constexpr TLValue predicate = TLValue::ChannelsEditBanned;
    TLInputChannel channel;
    TLInputUser userId;
    TLChannelBannedRights bannedRights;
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

struct TLChannelsExportMessageLink
{
    static constexpr TLValue predicate = TLValue::ChannelsExportMessageLink;
    TLInputChannel channel;
    quint32 id = 0;
};

struct TLChannelsGetAdminLog
{
    static constexpr TLValue predicate = TLValue::ChannelsGetAdminLog;
    quint32 flags = 0;
    TLInputChannel channel;
    QString q;
    TLChannelAdminLogEventsFilter eventsFilter;
    TLVector<TLInputUser> admins;
    quint64 maxId = 0;
    quint64 minId = 0;
    quint32 limit = 0;
};

struct TLChannelsGetAdminedPublicChannels
{
    static constexpr TLValue predicate = TLValue::ChannelsGetAdminedPublicChannels;
};

struct TLChannelsGetChannels
{
    static constexpr TLValue predicate = TLValue::ChannelsGetChannels;
    TLVector<TLInputChannel> id;
};

struct TLChannelsGetFullChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsGetFullChannel;
    TLInputChannel channel;
};

struct TLChannelsGetMessages
{
    static constexpr TLValue predicate = TLValue::ChannelsGetMessages;
    TLInputChannel channel;
    TLVector<quint32> id;
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
    quint32 hash = 0;
};

struct TLChannelsInviteToChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsInviteToChannel;
    TLInputChannel channel;
    TLVector<TLInputUser> users;
};

struct TLChannelsJoinChannel
{
    static constexpr TLValue predicate = TLValue::ChannelsJoinChannel;
    TLInputChannel channel;
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

struct TLChannelsReadMessageContents
{
    static constexpr TLValue predicate = TLValue::ChannelsReadMessageContents;
    TLInputChannel channel;
    TLVector<quint32> id;
};

struct TLChannelsReportSpam
{
    static constexpr TLValue predicate = TLValue::ChannelsReportSpam;
    TLInputChannel channel;
    TLInputUser userId;
    TLVector<quint32> id;
};

struct TLChannelsSetStickers
{
    static constexpr TLValue predicate = TLValue::ChannelsSetStickers;
    TLInputChannel channel;
    TLInputStickerSet stickerset;
};

struct TLChannelsToggleInvites
{
    static constexpr TLValue predicate = TLValue::ChannelsToggleInvites;
    TLInputChannel channel;
    bool enabled = false;
};

struct TLChannelsTogglePreHistoryHidden
{
    static constexpr TLValue predicate = TLValue::ChannelsTogglePreHistoryHidden;
    TLInputChannel channel;
    bool enabled = false;
};

struct TLChannelsToggleSignatures
{
    static constexpr TLValue predicate = TLValue::ChannelsToggleSignatures;
    TLInputChannel channel;
    bool enabled = false;
};

struct TLChannelsUpdatePinnedMessage
{
    static constexpr TLValue predicate = TLValue::ChannelsUpdatePinnedMessage;
    quint32 flags = 0;
    TLInputChannel channel;
    quint32 id = 0;
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
    TLVector<TLInputUser> id;
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
    quint32 hash = 0;
};

struct TLContactsGetStatuses
{
    static constexpr TLValue predicate = TLValue::ContactsGetStatuses;
};

struct TLContactsGetTopPeers
{
    static constexpr TLValue predicate = TLValue::ContactsGetTopPeers;
    quint32 flags = 0;
    quint32 offset = 0;
    quint32 limit = 0;
    quint32 hash = 0;
};

struct TLContactsImportCard
{
    static constexpr TLValue predicate = TLValue::ContactsImportCard;
    TLVector<quint32> exportCard;
};

struct TLContactsImportContacts
{
    static constexpr TLValue predicate = TLValue::ContactsImportContacts;
    TLVector<TLInputContact> contacts;
};

struct TLContactsResetSaved
{
    static constexpr TLValue predicate = TLValue::ContactsResetSaved;
};

struct TLContactsResetTopPeerRating
{
    static constexpr TLValue predicate = TLValue::ContactsResetTopPeerRating;
    TLTopPeerCategory category;
    TLInputPeer peer;
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
    QString prevAppVersion;
};

struct TLHelpGetAppUpdate
{
    static constexpr TLValue predicate = TLValue::HelpGetAppUpdate;
};

struct TLHelpGetCdnConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetCdnConfig;
};

struct TLHelpGetConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetConfig;
};

struct TLHelpGetInviteText
{
    static constexpr TLValue predicate = TLValue::HelpGetInviteText;
};

struct TLHelpGetNearestDc
{
    static constexpr TLValue predicate = TLValue::HelpGetNearestDc;
};

struct TLHelpGetRecentMeUrls
{
    static constexpr TLValue predicate = TLValue::HelpGetRecentMeUrls;
    QString referer;
};

struct TLHelpGetSupport
{
    static constexpr TLValue predicate = TLValue::HelpGetSupport;
};

struct TLHelpGetTermsOfService
{
    static constexpr TLValue predicate = TLValue::HelpGetTermsOfService;
};

struct TLHelpSaveAppLog
{
    static constexpr TLValue predicate = TLValue::HelpSaveAppLog;
    TLVector<TLInputAppEvent> events;
};

struct TLHelpSetBotUpdatesStatus
{
    static constexpr TLValue predicate = TLValue::HelpSetBotUpdatesStatus;
    quint32 pendingUpdatesCount = 0;
    QString message;
};

struct TLLangpackGetDifference
{
    static constexpr TLValue predicate = TLValue::LangpackGetDifference;
    quint32 fromVersion = 0;
};

struct TLLangpackGetLangPack
{
    static constexpr TLValue predicate = TLValue::LangpackGetLangPack;
    QString langCode;
};

struct TLLangpackGetLanguages
{
    static constexpr TLValue predicate = TLValue::LangpackGetLanguages;
};

struct TLLangpackGetStrings
{
    static constexpr TLValue predicate = TLValue::LangpackGetStrings;
    QString langCode;
    TLVector<QString> keys;
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

struct TLMessagesClearRecentStickers
{
    static constexpr TLValue predicate = TLValue::MessagesClearRecentStickers;
    quint32 flags = 0;
};

struct TLMessagesCreateChat
{
    static constexpr TLValue predicate = TLValue::MessagesCreateChat;
    TLVector<TLInputUser> users;
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
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 maxId = 0;
};

struct TLMessagesDeleteMessages
{
    static constexpr TLValue predicate = TLValue::MessagesDeleteMessages;
    quint32 flags = 0;
    TLVector<quint32> id;
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

struct TLMessagesEditInlineBotMessage
{
    static constexpr TLValue predicate = TLValue::MessagesEditInlineBotMessage;
    quint32 flags = 0;
    TLInputBotInlineMessageID id;
    QString message;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
    TLInputGeoPoint geoPoint;
};

struct TLMessagesEditMessage
{
    static constexpr TLValue predicate = TLValue::MessagesEditMessage;
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 id = 0;
    QString message;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
    TLInputGeoPoint geoPoint;
};

struct TLMessagesExportChatInvite
{
    static constexpr TLValue predicate = TLValue::MessagesExportChatInvite;
    quint32 chatId = 0;
};

struct TLMessagesFaveSticker
{
    static constexpr TLValue predicate = TLValue::MessagesFaveSticker;
    TLInputDocument id;
    bool unfave = false;
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
    TLVector<quint32> id;
    TLVector<quint64> randomId;
    TLInputPeer toPeer;
};

struct TLMessagesGetAllChats
{
    static constexpr TLValue predicate = TLValue::MessagesGetAllChats;
    TLVector<quint32> exceptIds;
};

struct TLMessagesGetAllDrafts
{
    static constexpr TLValue predicate = TLValue::MessagesGetAllDrafts;
};

struct TLMessagesGetAllStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetAllStickers;
    quint32 hash = 0;
};

struct TLMessagesGetArchivedStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetArchivedStickers;
    quint32 flags = 0;
    quint64 offsetId = 0;
    quint32 limit = 0;
};

struct TLMessagesGetAttachedStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetAttachedStickers;
    TLInputStickeredMedia media;
};

struct TLMessagesGetBotCallbackAnswer
{
    static constexpr TLValue predicate = TLValue::MessagesGetBotCallbackAnswer;
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 msgId = 0;
    QByteArray data;
};

struct TLMessagesGetChats
{
    static constexpr TLValue predicate = TLValue::MessagesGetChats;
    TLVector<quint32> id;
};

struct TLMessagesGetCommonChats
{
    static constexpr TLValue predicate = TLValue::MessagesGetCommonChats;
    TLInputUser userId;
    quint32 maxId = 0;
    quint32 limit = 0;
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
    quint32 flags = 0;
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

struct TLMessagesGetFavedStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetFavedStickers;
    quint32 hash = 0;
};

struct TLMessagesGetFeaturedStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetFeaturedStickers;
    quint32 hash = 0;
};

struct TLMessagesGetFullChat
{
    static constexpr TLValue predicate = TLValue::MessagesGetFullChat;
    quint32 chatId = 0;
};

struct TLMessagesGetGameHighScores
{
    static constexpr TLValue predicate = TLValue::MessagesGetGameHighScores;
    TLInputPeer peer;
    quint32 id = 0;
    TLInputUser userId;
};

struct TLMessagesGetHistory
{
    static constexpr TLValue predicate = TLValue::MessagesGetHistory;
    TLInputPeer peer;
    quint32 offsetId = 0;
    quint32 offsetDate = 0;
    quint32 addOffset = 0;
    quint32 limit = 0;
    quint32 maxId = 0;
    quint32 minId = 0;
    quint32 hash = 0;
};

struct TLMessagesGetInlineBotResults
{
    static constexpr TLValue predicate = TLValue::MessagesGetInlineBotResults;
    quint32 flags = 0;
    TLInputUser bot;
    TLInputPeer peer;
    TLInputGeoPoint geoPoint;
    QString query;
    QString offset;
};

struct TLMessagesGetInlineGameHighScores
{
    static constexpr TLValue predicate = TLValue::MessagesGetInlineGameHighScores;
    TLInputBotInlineMessageID id;
    TLInputUser userId;
};

struct TLMessagesGetMaskStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetMaskStickers;
    quint32 hash = 0;
};

struct TLMessagesGetMessageEditData
{
    static constexpr TLValue predicate = TLValue::MessagesGetMessageEditData;
    TLInputPeer peer;
    quint32 id = 0;
};

struct TLMessagesGetMessages
{
    static constexpr TLValue predicate = TLValue::MessagesGetMessages;
    TLVector<quint32> id;
};

struct TLMessagesGetMessagesViews
{
    static constexpr TLValue predicate = TLValue::MessagesGetMessagesViews;
    TLInputPeer peer;
    TLVector<quint32> id;
    bool increment = false;
};

struct TLMessagesGetPeerDialogs
{
    static constexpr TLValue predicate = TLValue::MessagesGetPeerDialogs;
    TLVector<TLInputPeer> peers;
};

struct TLMessagesGetPeerSettings
{
    static constexpr TLValue predicate = TLValue::MessagesGetPeerSettings;
    TLInputPeer peer;
};

struct TLMessagesGetPinnedDialogs
{
    static constexpr TLValue predicate = TLValue::MessagesGetPinnedDialogs;
};

struct TLMessagesGetRecentLocations
{
    static constexpr TLValue predicate = TLValue::MessagesGetRecentLocations;
    TLInputPeer peer;
    quint32 limit = 0;
};

struct TLMessagesGetRecentStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetRecentStickers;
    quint32 flags = 0;
    quint32 hash = 0;
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

struct TLMessagesGetUnreadMentions
{
    static constexpr TLValue predicate = TLValue::MessagesGetUnreadMentions;
    TLInputPeer peer;
    quint32 offsetId = 0;
    quint32 addOffset = 0;
    quint32 limit = 0;
    quint32 maxId = 0;
    quint32 minId = 0;
};

struct TLMessagesGetWebPage
{
    static constexpr TLValue predicate = TLValue::MessagesGetWebPage;
    QString url;
    quint32 hash = 0;
};

struct TLMessagesGetWebPagePreview
{
    static constexpr TLValue predicate = TLValue::MessagesGetWebPagePreview;
    QString message;
};

struct TLMessagesHideReportSpam
{
    static constexpr TLValue predicate = TLValue::MessagesHideReportSpam;
    TLInputPeer peer;
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
    bool archived = false;
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

struct TLMessagesReadFeaturedStickers
{
    static constexpr TLValue predicate = TLValue::MessagesReadFeaturedStickers;
    TLVector<quint64> id;
};

struct TLMessagesReadHistory
{
    static constexpr TLValue predicate = TLValue::MessagesReadHistory;
    TLInputPeer peer;
    quint32 maxId = 0;
};

struct TLMessagesReadMentions
{
    static constexpr TLValue predicate = TLValue::MessagesReadMentions;
    TLInputPeer peer;
};

struct TLMessagesReadMessageContents
{
    static constexpr TLValue predicate = TLValue::MessagesReadMessageContents;
    TLVector<quint32> id;
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

struct TLMessagesReorderPinnedDialogs
{
    static constexpr TLValue predicate = TLValue::MessagesReorderPinnedDialogs;
    quint32 flags = 0;
    TLVector<TLInputPeer> order;
};

struct TLMessagesReorderStickerSets
{
    static constexpr TLValue predicate = TLValue::MessagesReorderStickerSets;
    quint32 flags = 0;
    TLVector<quint64> order;
};

struct TLMessagesReportEncryptedSpam
{
    static constexpr TLValue predicate = TLValue::MessagesReportEncryptedSpam;
    TLInputEncryptedChat peer;
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

struct TLMessagesSaveDraft
{
    static constexpr TLValue predicate = TLValue::MessagesSaveDraft;
    quint32 flags = 0;
    quint32 replyToMsgId = 0;
    TLInputPeer peer;
    QString message;
    TLVector<TLMessageEntity> entities;
};

struct TLMessagesSaveGif
{
    static constexpr TLValue predicate = TLValue::MessagesSaveGif;
    TLInputDocument id;
    bool unsave = false;
};

struct TLMessagesSaveRecentSticker
{
    static constexpr TLValue predicate = TLValue::MessagesSaveRecentSticker;
    quint32 flags = 0;
    TLInputDocument id;
    bool unsave = false;
};

struct TLMessagesSearch
{
    static constexpr TLValue predicate = TLValue::MessagesSearch;
    quint32 flags = 0;
    TLInputPeer peer;
    QString q;
    TLInputUser fromId;
    TLMessagesFilter filter;
    quint32 minDate = 0;
    quint32 maxDate = 0;
    quint32 offsetId = 0;
    quint32 addOffset = 0;
    quint32 limit = 0;
    quint32 maxId = 0;
    quint32 minId = 0;
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
    TLVector<TLMessageEntity> entities;
};

struct TLMessagesSendScreenshotNotification
{
    static constexpr TLValue predicate = TLValue::MessagesSendScreenshotNotification;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    quint64 randomId = 0;
};

struct TLMessagesSetBotCallbackAnswer
{
    static constexpr TLValue predicate = TLValue::MessagesSetBotCallbackAnswer;
    quint32 flags = 0;
    quint64 queryId = 0;
    QString message;
    QString url;
    quint32 cacheTime = 0;
};

struct TLMessagesSetBotPrecheckoutResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetBotPrecheckoutResults;
    quint32 flags = 0;
    quint64 queryId = 0;
    QString error;
};

struct TLMessagesSetBotShippingResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetBotShippingResults;
    quint32 flags = 0;
    quint64 queryId = 0;
    QString error;
    TLVector<TLShippingOption> shippingOptions;
};

struct TLMessagesSetEncryptedTyping
{
    static constexpr TLValue predicate = TLValue::MessagesSetEncryptedTyping;
    TLInputEncryptedChat peer;
    bool typing = false;
};

struct TLMessagesSetGameScore
{
    static constexpr TLValue predicate = TLValue::MessagesSetGameScore;
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 id = 0;
    TLInputUser userId;
    quint32 score = 0;
};

struct TLMessagesSetInlineBotResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetInlineBotResults;
    quint32 flags = 0;
    quint64 queryId = 0;
    TLVector<TLInputBotInlineResult> results;
    quint32 cacheTime = 0;
    QString nextOffset;
    TLInlineBotSwitchPM switchPm;
};

struct TLMessagesSetInlineGameScore
{
    static constexpr TLValue predicate = TLValue::MessagesSetInlineGameScore;
    quint32 flags = 0;
    TLInputBotInlineMessageID id;
    TLInputUser userId;
    quint32 score = 0;
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

struct TLMessagesToggleDialogPin
{
    static constexpr TLValue predicate = TLValue::MessagesToggleDialogPin;
    quint32 flags = 0;
    TLInputPeer peer;
};

struct TLMessagesUninstallStickerSet
{
    static constexpr TLValue predicate = TLValue::MessagesUninstallStickerSet;
    TLInputStickerSet stickerset;
};

struct TLMessagesUploadMedia
{
    static constexpr TLValue predicate = TLValue::MessagesUploadMedia;
    TLInputPeer peer;
    TLInputMedia media;
};

struct TLPaymentsClearSavedInfo
{
    static constexpr TLValue predicate = TLValue::PaymentsClearSavedInfo;
    quint32 flags = 0;
};

struct TLPaymentsGetPaymentForm
{
    static constexpr TLValue predicate = TLValue::PaymentsGetPaymentForm;
    quint32 msgId = 0;
};

struct TLPaymentsGetPaymentReceipt
{
    static constexpr TLValue predicate = TLValue::PaymentsGetPaymentReceipt;
    quint32 msgId = 0;
};

struct TLPaymentsGetSavedInfo
{
    static constexpr TLValue predicate = TLValue::PaymentsGetSavedInfo;
};

struct TLPaymentsSendPaymentForm
{
    static constexpr TLValue predicate = TLValue::PaymentsSendPaymentForm;
    quint32 flags = 0;
    quint32 msgId = 0;
    QString requestedInfoId;
    QString shippingOptionId;
    TLInputPaymentCredentials credentials;
};

struct TLPaymentsValidateRequestedInfo
{
    static constexpr TLValue predicate = TLValue::PaymentsValidateRequestedInfo;
    quint32 flags = 0;
    quint32 msgId = 0;
    TLPaymentRequestedInfo info;
};

struct TLPhoneAcceptCall
{
    static constexpr TLValue predicate = TLValue::PhoneAcceptCall;
    TLInputPhoneCall peer;
    QByteArray gB;
    TLPhoneCallProtocol protocol;
};

struct TLPhoneConfirmCall
{
    static constexpr TLValue predicate = TLValue::PhoneConfirmCall;
    TLInputPhoneCall peer;
    QByteArray gA;
    quint64 keyFingerprint = 0;
    TLPhoneCallProtocol protocol;
};

struct TLPhoneDiscardCall
{
    static constexpr TLValue predicate = TLValue::PhoneDiscardCall;
    TLInputPhoneCall peer;
    quint32 duration = 0;
    TLPhoneCallDiscardReason reason;
    quint64 connectionId = 0;
};

struct TLPhoneGetCallConfig
{
    static constexpr TLValue predicate = TLValue::PhoneGetCallConfig;
};

struct TLPhoneReceivedCall
{
    static constexpr TLValue predicate = TLValue::PhoneReceivedCall;
    TLInputPhoneCall peer;
};

struct TLPhoneRequestCall
{
    static constexpr TLValue predicate = TLValue::PhoneRequestCall;
    TLInputUser userId;
    quint32 randomId = 0;
    QByteArray gAHash;
    TLPhoneCallProtocol protocol;
};

struct TLPhoneSaveCallDebug
{
    static constexpr TLValue predicate = TLValue::PhoneSaveCallDebug;
    TLInputPhoneCall peer;
    TLDataJSON debug;
};

struct TLPhoneSetCallRating
{
    static constexpr TLValue predicate = TLValue::PhoneSetCallRating;
    TLInputPhoneCall peer;
    quint32 rating = 0;
    QString comment;
};

struct TLPhotosDeletePhotos
{
    static constexpr TLValue predicate = TLValue::PhotosDeletePhotos;
    TLVector<TLInputPhoto> id;
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
};

struct TLPhotosUploadProfilePhoto
{
    static constexpr TLValue predicate = TLValue::PhotosUploadProfilePhoto;
    TLInputFile file;
};

struct TLStickersAddStickerToSet
{
    static constexpr TLValue predicate = TLValue::StickersAddStickerToSet;
    TLInputStickerSet stickerset;
    TLInputStickerSetItem sticker;
};

struct TLStickersChangeStickerPosition
{
    static constexpr TLValue predicate = TLValue::StickersChangeStickerPosition;
    TLInputDocument sticker;
    quint32 position = 0;
};

struct TLStickersCreateStickerSet
{
    static constexpr TLValue predicate = TLValue::StickersCreateStickerSet;
    quint32 flags = 0;
    TLInputUser userId;
    QString title;
    QString shortName;
    TLVector<TLInputStickerSetItem> stickers;
};

struct TLStickersRemoveStickerFromSet
{
    static constexpr TLValue predicate = TLValue::StickersRemoveStickerFromSet;
    TLInputDocument sticker;
};

struct TLUpdatesGetChannelDifference
{
    static constexpr TLValue predicate = TLValue::UpdatesGetChannelDifference;
    quint32 flags = 0;
    TLInputChannel channel;
    TLChannelMessagesFilter filter;
    quint32 pts = 0;
    quint32 limit = 0;
};

struct TLUpdatesGetDifference
{
    static constexpr TLValue predicate = TLValue::UpdatesGetDifference;
    quint32 flags = 0;
    quint32 pts = 0;
    quint32 ptsTotalLimit = 0;
    quint32 date = 0;
    quint32 qts = 0;
};

struct TLUpdatesGetState
{
    static constexpr TLValue predicate = TLValue::UpdatesGetState;
};

struct TLUploadGetCdnFile
{
    static constexpr TLValue predicate = TLValue::UploadGetCdnFile;
    QByteArray fileToken;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLUploadGetCdnFileHashes
{
    static constexpr TLValue predicate = TLValue::UploadGetCdnFileHashes;
    QByteArray fileToken;
    quint32 offset = 0;
};

struct TLUploadGetFile
{
    static constexpr TLValue predicate = TLValue::UploadGetFile;
    TLInputFileLocation location;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLUploadGetWebFile
{
    static constexpr TLValue predicate = TLValue::UploadGetWebFile;
    TLInputWebFileLocation location;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLUploadReuploadCdnFile
{
    static constexpr TLValue predicate = TLValue::UploadReuploadCdnFile;
    QByteArray fileToken;
    QByteArray requestToken;
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
    TLVector<TLInputUser> id;
};
// End of generated TLFunctions

} // TLFunctions

} // Telegram

#endif // TELEGRAM_TL_FUNCTIONS_HPP
