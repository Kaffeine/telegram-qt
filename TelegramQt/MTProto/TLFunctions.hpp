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

namespace MTProto {

namespace Functions {

struct TLPing
{
    static constexpr TLValue predicate = TLValue::Ping;
    static constexpr TLValue predicateDisconnect = TLValue::PingDelayDisconnect;
    TLValue tlType = TLValue::Ping; // clang-5 complains on "tlType = predicate;"
    quint64 pingId = 0;
    quint32 disconnectDelay = 0;
};

// Generated TLFunctions
struct TLAccountAcceptAuthorization
{
    static constexpr TLValue predicate = TLValue::AccountAcceptAuthorization;
    quint32 botId = 0;
    QString scope;
    QString publicKey;
    TLVector<TLSecureValueHash> valueHashes;
    TLSecureCredentialsEncrypted credentials;
};

struct TLAccountCancelPasswordEmail
{
    static constexpr TLValue predicate = TLValue::AccountCancelPasswordEmail;
};

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

struct TLAccountConfirmPasswordEmail
{
    static constexpr TLValue predicate = TLValue::AccountConfirmPasswordEmail;
    QString code;
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

struct TLAccountDeleteSecureValue
{
    static constexpr TLValue predicate = TLValue::AccountDeleteSecureValue;
    TLVector<TLSecureValueType> types;
};

struct TLAccountFinishTakeoutSession
{
    static constexpr TLValue predicate = TLValue::AccountFinishTakeoutSession;
    enum Flag {
        Success = 1 << 0,
    };
    quint32 flags = 0;
};

struct TLAccountGetAccountTTL
{
    static constexpr TLValue predicate = TLValue::AccountGetAccountTTL;
};

struct TLAccountGetAllSecureValues
{
    static constexpr TLValue predicate = TLValue::AccountGetAllSecureValues;
};

struct TLAccountGetAuthorizationForm
{
    static constexpr TLValue predicate = TLValue::AccountGetAuthorizationForm;
    quint32 botId = 0;
    QString scope;
    QString publicKey;
};

struct TLAccountGetAuthorizations
{
    static constexpr TLValue predicate = TLValue::AccountGetAuthorizations;
};

struct TLAccountGetContactSignUpNotification
{
    static constexpr TLValue predicate = TLValue::AccountGetContactSignUpNotification;
};

struct TLAccountGetNotifyExceptions
{
    static constexpr TLValue predicate = TLValue::AccountGetNotifyExceptions;
    enum Flag {
        Peer = 1 << 0,
        CompareSound = 1 << 1,
    };
    quint32 flags = 0;
    TLInputNotifyPeer peer;
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
    TLInputCheckPasswordSRP password;
};

struct TLAccountGetPrivacy
{
    static constexpr TLValue predicate = TLValue::AccountGetPrivacy;
    TLInputPrivacyKey key;
};

struct TLAccountGetSecureValue
{
    static constexpr TLValue predicate = TLValue::AccountGetSecureValue;
    TLVector<TLSecureValueType> types;
};

struct TLAccountGetTmpPassword
{
    static constexpr TLValue predicate = TLValue::AccountGetTmpPassword;
    TLInputCheckPasswordSRP password;
    quint32 period = 0;
};

struct TLAccountGetWallPapers
{
    static constexpr TLValue predicate = TLValue::AccountGetWallPapers;
};

struct TLAccountGetWebAuthorizations
{
    static constexpr TLValue predicate = TLValue::AccountGetWebAuthorizations;
};

struct TLAccountInitTakeoutSession
{
    static constexpr TLValue predicate = TLValue::AccountInitTakeoutSession;
    enum Flag {
        Contacts = 1 << 0,
        MessageUsers = 1 << 1,
        MessageChats = 1 << 2,
        MessageMegagroups = 1 << 3,
        MessageChannels = 1 << 4,
        FileMaxSize = 1 << 5,
        Files = 1 << 5,
    };
    quint32 flags = 0;
    quint32 fileMaxSize = 0;
};

struct TLAccountRegisterDevice
{
    static constexpr TLValue predicate = TLValue::AccountRegisterDevice;
    quint32 tokenType = 0;
    QString token;
    bool appSandbox = false;
    QByteArray secret;
    TLVector<quint32> otherUids;
};

struct TLAccountReportPeer
{
    static constexpr TLValue predicate = TLValue::AccountReportPeer;
    TLInputPeer peer;
    TLReportReason reason;
};

struct TLAccountResendPasswordEmail
{
    static constexpr TLValue predicate = TLValue::AccountResendPasswordEmail;
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

struct TLAccountResetWebAuthorization
{
    static constexpr TLValue predicate = TLValue::AccountResetWebAuthorization;
    quint64 hash = 0;
};

struct TLAccountResetWebAuthorizations
{
    static constexpr TLValue predicate = TLValue::AccountResetWebAuthorizations;
};

struct TLAccountSaveSecureValue
{
    static constexpr TLValue predicate = TLValue::AccountSaveSecureValue;
    TLInputSecureValue value;
    quint64 secureSecretId = 0;
};

struct TLAccountSendChangePhoneCode
{
    static constexpr TLValue predicate = TLValue::AccountSendChangePhoneCode;
    enum Flag {
        CurrentNumber = 1 << 0,
        AllowFlashcall = 1 << 0,
    };
    quint32 flags = 0;
    QString phoneNumber;
    bool currentNumber = false;
};

struct TLAccountSendConfirmPhoneCode
{
    static constexpr TLValue predicate = TLValue::AccountSendConfirmPhoneCode;
    enum Flag {
        CurrentNumber = 1 << 0,
        AllowFlashcall = 1 << 0,
    };
    quint32 flags = 0;
    QString hash;
    bool currentNumber = false;
};

struct TLAccountSendVerifyEmailCode
{
    static constexpr TLValue predicate = TLValue::AccountSendVerifyEmailCode;
    QString email;
};

struct TLAccountSendVerifyPhoneCode
{
    static constexpr TLValue predicate = TLValue::AccountSendVerifyPhoneCode;
    enum Flag {
        CurrentNumber = 1 << 0,
        AllowFlashcall = 1 << 0,
    };
    quint32 flags = 0;
    QString phoneNumber;
    bool currentNumber = false;
};

struct TLAccountSetAccountTTL
{
    static constexpr TLValue predicate = TLValue::AccountSetAccountTTL;
    TLAccountDaysTTL ttl;
};

struct TLAccountSetContactSignUpNotification
{
    static constexpr TLValue predicate = TLValue::AccountSetContactSignUpNotification;
    bool silent = false;
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
    TLVector<quint32> otherUids;
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
    TLInputCheckPasswordSRP password;
    TLAccountPasswordInputSettings newSettings;
};

struct TLAccountUpdateProfile
{
    static constexpr TLValue predicate = TLValue::AccountUpdateProfile;
    enum Flag {
        FirstName = 1 << 0,
        LastName = 1 << 1,
        About = 1 << 2,
    };
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

struct TLAccountVerifyEmail
{
    static constexpr TLValue predicate = TLValue::AccountVerifyEmail;
    QString email;
    QString code;
};

struct TLAccountVerifyPhone
{
    static constexpr TLValue predicate = TLValue::AccountVerifyPhone;
    QString phoneNumber;
    QString phoneCodeHash;
    QString phoneCode;
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
    TLInputCheckPasswordSRP password;
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
    enum Flag {
        CurrentNumber = 1 << 0,
        AllowFlashcall = 1 << 0,
    };
    quint32 flags = 0;
    QString phoneNumber;
    bool currentNumber = false;
    quint32 apiId = 0;
    QString apiHash;
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
    enum Flag {
        Broadcast = 1 << 0,
        Megagroup = 1 << 1,
    };
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
    bool grouped = false;
};

struct TLChannelsGetAdminLog
{
    static constexpr TLValue predicate = TLValue::ChannelsGetAdminLog;
    enum Flag {
        EventsFilter = 1 << 0,
        Admins = 1 << 1,
    };
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

struct TLChannelsGetLeftChannels
{
    static constexpr TLValue predicate = TLValue::ChannelsGetLeftChannels;
    quint32 offset = 0;
};

struct TLChannelsGetMessages
{
    static constexpr TLValue predicate = TLValue::ChannelsGetMessages;
    TLInputChannel channel;
    TLVector<TLInputMessage> id;
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

struct TLContactsDeleteByPhones
{
    static constexpr TLValue predicate = TLValue::ContactsDeleteByPhones;
    TLVector<QString> phones;
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

struct TLContactsGetBlocked
{
    static constexpr TLValue predicate = TLValue::ContactsGetBlocked;
    quint32 offset = 0;
    quint32 limit = 0;
};

struct TLContactsGetContactIDs
{
    static constexpr TLValue predicate = TLValue::ContactsGetContactIDs;
    quint32 hash = 0;
};

struct TLContactsGetContacts
{
    static constexpr TLValue predicate = TLValue::ContactsGetContacts;
    quint32 hash = 0;
};

struct TLContactsGetSaved
{
    static constexpr TLValue predicate = TLValue::ContactsGetSaved;
};

struct TLContactsGetStatuses
{
    static constexpr TLValue predicate = TLValue::ContactsGetStatuses;
};

struct TLContactsGetTopPeers
{
    static constexpr TLValue predicate = TLValue::ContactsGetTopPeers;
    enum Flag {
        Correspondents = 1 << 0,
        BotsPm = 1 << 1,
        BotsInline = 1 << 2,
        PhoneCalls = 1 << 3,
        Groups = 1 << 10,
        Channels = 1 << 15,
    };
    quint32 flags = 0;
    quint32 offset = 0;
    quint32 limit = 0;
    quint32 hash = 0;
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

struct TLContactsToggleTopPeers
{
    static constexpr TLValue predicate = TLValue::ContactsToggleTopPeers;
    bool enabled = false;
};

struct TLContactsUnblock
{
    static constexpr TLValue predicate = TLValue::ContactsUnblock;
    TLInputUser id;
};

struct TLHelpAcceptTermsOfService
{
    static constexpr TLValue predicate = TLValue::HelpAcceptTermsOfService;
    TLDataJSON id;
};

struct TLHelpEditUserInfo
{
    static constexpr TLValue predicate = TLValue::HelpEditUserInfo;
    TLInputUser userId;
    QString message;
    TLVector<TLMessageEntity> entities;
};

struct TLHelpGetAppChangelog
{
    static constexpr TLValue predicate = TLValue::HelpGetAppChangelog;
    QString prevAppVersion;
};

struct TLHelpGetAppConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetAppConfig;
};

struct TLHelpGetAppUpdate
{
    static constexpr TLValue predicate = TLValue::HelpGetAppUpdate;
    QString source;
};

struct TLHelpGetCdnConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetCdnConfig;
};

struct TLHelpGetConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetConfig;
};

struct TLHelpGetDeepLinkInfo
{
    static constexpr TLValue predicate = TLValue::HelpGetDeepLinkInfo;
    QString path;
};

struct TLHelpGetInviteText
{
    static constexpr TLValue predicate = TLValue::HelpGetInviteText;
};

struct TLHelpGetNearestDc
{
    static constexpr TLValue predicate = TLValue::HelpGetNearestDc;
};

struct TLHelpGetPassportConfig
{
    static constexpr TLValue predicate = TLValue::HelpGetPassportConfig;
    quint32 hash = 0;
};

struct TLHelpGetProxyData
{
    static constexpr TLValue predicate = TLValue::HelpGetProxyData;
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

struct TLHelpGetSupportName
{
    static constexpr TLValue predicate = TLValue::HelpGetSupportName;
};

struct TLHelpGetTermsOfServiceUpdate
{
    static constexpr TLValue predicate = TLValue::HelpGetTermsOfServiceUpdate;
};

struct TLHelpGetUserInfo
{
    static constexpr TLValue predicate = TLValue::HelpGetUserInfo;
    TLInputUser userId;
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
    QString langCode;
    quint32 fromVersion = 0;
};

struct TLLangpackGetLangPack
{
    static constexpr TLValue predicate = TLValue::LangpackGetLangPack;
    QString langPack;
    QString langCode;
};

struct TLLangpackGetLanguage
{
    static constexpr TLValue predicate = TLValue::LangpackGetLanguage;
    QString langPack;
    QString langCode;
};

struct TLLangpackGetLanguages
{
    static constexpr TLValue predicate = TLValue::LangpackGetLanguages;
    QString langPack;
};

struct TLLangpackGetStrings
{
    static constexpr TLValue predicate = TLValue::LangpackGetStrings;
    QString langPack;
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

struct TLMessagesClearAllDrafts
{
    static constexpr TLValue predicate = TLValue::MessagesClearAllDrafts;
};

struct TLMessagesClearRecentStickers
{
    static constexpr TLValue predicate = TLValue::MessagesClearRecentStickers;
    enum Flag {
        Attached = 1 << 0,
    };
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
    enum Flag {
        JustClear = 1 << 0,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 maxId = 0;
};

struct TLMessagesDeleteMessages
{
    static constexpr TLValue predicate = TLValue::MessagesDeleteMessages;
    enum Flag {
        Revoke = 1 << 0,
    };
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
    enum Flag {
        NoWebpage = 1 << 1,
        ReplyMarkup = 1 << 2,
        Entities = 1 << 3,
        Message = 1 << 11,
        Media = 1 << 14,
    };
    quint32 flags = 0;
    TLInputBotInlineMessageID id;
    QString message;
    TLInputMedia media;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
};

struct TLMessagesEditMessage
{
    static constexpr TLValue predicate = TLValue::MessagesEditMessage;
    enum Flag {
        NoWebpage = 1 << 1,
        ReplyMarkup = 1 << 2,
        Entities = 1 << 3,
        Message = 1 << 11,
        Media = 1 << 14,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 id = 0;
    QString message;
    TLInputMedia media;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
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

struct TLMessagesForwardMessages
{
    static constexpr TLValue predicate = TLValue::MessagesForwardMessages;
    enum Flag {
        Silent = 1 << 5,
        Background = 1 << 6,
        WithMyScore = 1 << 8,
        Grouped = 1 << 9,
    };
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
    enum Flag {
        Masks = 1 << 0,
    };
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
    enum Flag {
        Data = 1 << 0,
        Game = 1 << 1,
    };
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

struct TLMessagesGetDialogUnreadMarks
{
    static constexpr TLValue predicate = TLValue::MessagesGetDialogUnreadMarks;
};

struct TLMessagesGetDialogs
{
    static constexpr TLValue predicate = TLValue::MessagesGetDialogs;
    enum Flag {
        ExcludePinned = 1 << 0,
    };
    quint32 flags = 0;
    quint32 offsetDate = 0;
    quint32 offsetId = 0;
    TLInputPeer offsetPeer;
    quint32 limit = 0;
    quint32 hash = 0;
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
    enum Flag {
        GeoPoint = 1 << 0,
    };
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
    TLVector<TLInputMessage> id;
};

struct TLMessagesGetMessagesViews
{
    static constexpr TLValue predicate = TLValue::MessagesGetMessagesViews;
    TLInputPeer peer;
    TLVector<quint32> id;
    bool increment = false;
};

struct TLMessagesGetOnlines
{
    static constexpr TLValue predicate = TLValue::MessagesGetOnlines;
    TLInputPeer peer;
};

struct TLMessagesGetPeerDialogs
{
    static constexpr TLValue predicate = TLValue::MessagesGetPeerDialogs;
    TLVector<TLInputDialogPeer> peers;
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

struct TLMessagesGetPollResults
{
    static constexpr TLValue predicate = TLValue::MessagesGetPollResults;
    TLInputPeer peer;
    quint32 msgId = 0;
};

struct TLMessagesGetRecentLocations
{
    static constexpr TLValue predicate = TLValue::MessagesGetRecentLocations;
    TLInputPeer peer;
    quint32 limit = 0;
    quint32 hash = 0;
};

struct TLMessagesGetRecentStickers
{
    static constexpr TLValue predicate = TLValue::MessagesGetRecentStickers;
    enum Flag {
        Attached = 1 << 0,
    };
    quint32 flags = 0;
    quint32 hash = 0;
};

struct TLMessagesGetSavedGifs
{
    static constexpr TLValue predicate = TLValue::MessagesGetSavedGifs;
    quint32 hash = 0;
};

struct TLMessagesGetSplitRanges
{
    static constexpr TLValue predicate = TLValue::MessagesGetSplitRanges;
};

struct TLMessagesGetStatsURL
{
    static constexpr TLValue predicate = TLValue::MessagesGetStatsURL;
    TLInputPeer peer;
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
    quint32 hash = 0;
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
    enum Flag {
        Entities = 1 << 3,
    };
    quint32 flags = 0;
    QString message;
    TLVector<TLMessageEntity> entities;
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

struct TLMessagesMarkDialogUnread
{
    static constexpr TLValue predicate = TLValue::MessagesMarkDialogUnread;
    enum Flag {
        Unread = 1 << 0,
    };
    quint32 flags = 0;
    TLInputDialogPeer peer;
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
    enum Flag {
        Force = 1 << 0,
    };
    quint32 flags = 0;
    TLVector<TLInputDialogPeer> order;
};

struct TLMessagesReorderStickerSets
{
    static constexpr TLValue predicate = TLValue::MessagesReorderStickerSets;
    enum Flag {
        Masks = 1 << 0,
    };
    quint32 flags = 0;
    TLVector<quint64> order;
};

struct TLMessagesReport
{
    static constexpr TLValue predicate = TLValue::MessagesReport;
    TLInputPeer peer;
    TLVector<quint32> id;
    TLReportReason reason;
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
    enum Flag {
        ReplyToMsgId = 1 << 0,
        NoWebpage = 1 << 1,
        Entities = 1 << 3,
    };
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
    enum Flag {
        Attached = 1 << 0,
    };
    quint32 flags = 0;
    TLInputDocument id;
    bool unsave = false;
};

struct TLMessagesSearch
{
    static constexpr TLValue predicate = TLValue::MessagesSearch;
    enum Flag {
        FromId = 1 << 0,
    };
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
    quint32 hash = 0;
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

struct TLMessagesSearchStickerSets
{
    static constexpr TLValue predicate = TLValue::MessagesSearchStickerSets;
    enum Flag {
        ExcludeFeatured = 1 << 0,
    };
    quint32 flags = 0;
    QString q;
    quint32 hash = 0;
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
    enum Flag {
        ReplyToMsgId = 1 << 0,
        Silent = 1 << 5,
        Background = 1 << 6,
        ClearDraft = 1 << 7,
        HideVia = 1 << 11,
    };
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
    enum Flag {
        ReplyToMsgId = 1 << 0,
        ReplyMarkup = 1 << 2,
        Entities = 1 << 3,
        Silent = 1 << 5,
        Background = 1 << 6,
        ClearDraft = 1 << 7,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    TLInputMedia media;
    QString message;
    quint64 randomId = 0;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
};

struct TLMessagesSendMessage
{
    static constexpr TLValue predicate = TLValue::MessagesSendMessage;
    enum Flag {
        ReplyToMsgId = 1 << 0,
        NoWebpage = 1 << 1,
        ReplyMarkup = 1 << 2,
        Entities = 1 << 3,
        Silent = 1 << 5,
        Background = 1 << 6,
        ClearDraft = 1 << 7,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    QString message;
    quint64 randomId = 0;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
};

struct TLMessagesSendMultiMedia
{
    static constexpr TLValue predicate = TLValue::MessagesSendMultiMedia;
    enum Flag {
        ReplyToMsgId = 1 << 0,
        Silent = 1 << 5,
        Background = 1 << 6,
        ClearDraft = 1 << 7,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    TLVector<TLInputSingleMedia> multiMedia;
};

struct TLMessagesSendScreenshotNotification
{
    static constexpr TLValue predicate = TLValue::MessagesSendScreenshotNotification;
    TLInputPeer peer;
    quint32 replyToMsgId = 0;
    quint64 randomId = 0;
};

struct TLMessagesSendVote
{
    static constexpr TLValue predicate = TLValue::MessagesSendVote;
    TLInputPeer peer;
    quint32 msgId = 0;
    TLVector<QByteArray> options;
};

struct TLMessagesSetBotCallbackAnswer
{
    static constexpr TLValue predicate = TLValue::MessagesSetBotCallbackAnswer;
    enum Flag {
        Message = 1 << 0,
        Alert = 1 << 1,
        Url = 1 << 2,
    };
    quint32 flags = 0;
    quint64 queryId = 0;
    QString message;
    QString url;
    quint32 cacheTime = 0;
};

struct TLMessagesSetBotPrecheckoutResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetBotPrecheckoutResults;
    enum Flag {
        Error = 1 << 0,
        Success = 1 << 1,
    };
    quint32 flags = 0;
    quint64 queryId = 0;
    QString error;
};

struct TLMessagesSetBotShippingResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetBotShippingResults;
    enum Flag {
        Error = 1 << 0,
        ShippingOptions = 1 << 1,
    };
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
    enum Flag {
        EditMessage = 1 << 0,
        Force = 1 << 1,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 id = 0;
    TLInputUser userId;
    quint32 score = 0;
};

struct TLMessagesSetInlineBotResults
{
    static constexpr TLValue predicate = TLValue::MessagesSetInlineBotResults;
    enum Flag {
        Gallery = 1 << 0,
        IsPrivate = 1 << 1,
        NextOffset = 1 << 2,
        SwitchPm = 1 << 3,
    };
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
    enum Flag {
        EditMessage = 1 << 0,
        Force = 1 << 1,
    };
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
    enum Flag {
        Pinned = 1 << 0,
    };
    quint32 flags = 0;
    TLInputDialogPeer peer;
};

struct TLMessagesUninstallStickerSet
{
    static constexpr TLValue predicate = TLValue::MessagesUninstallStickerSet;
    TLInputStickerSet stickerset;
};

struct TLMessagesUpdatePinnedMessage
{
    static constexpr TLValue predicate = TLValue::MessagesUpdatePinnedMessage;
    enum Flag {
        Silent = 1 << 0,
    };
    quint32 flags = 0;
    TLInputPeer peer;
    quint32 id = 0;
};

struct TLMessagesUploadEncryptedFile
{
    static constexpr TLValue predicate = TLValue::MessagesUploadEncryptedFile;
    TLInputEncryptedChat peer;
    TLInputEncryptedFile file;
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
    enum Flag {
        Credentials = 1 << 0,
        Info = 1 << 1,
    };
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
    enum Flag {
        RequestedInfoId = 1 << 0,
        ShippingOptionId = 1 << 1,
    };
    quint32 flags = 0;
    quint32 msgId = 0;
    QString requestedInfoId;
    QString shippingOptionId;
    TLInputPaymentCredentials credentials;
};

struct TLPaymentsValidateRequestedInfo
{
    static constexpr TLValue predicate = TLValue::PaymentsValidateRequestedInfo;
    enum Flag {
        Save = 1 << 0,
    };
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
    enum Flag {
        Masks = 1 << 0,
    };
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
    enum Flag {
        Force = 1 << 0,
    };
    quint32 flags = 0;
    TLInputChannel channel;
    TLChannelMessagesFilter filter;
    quint32 pts = 0;
    quint32 limit = 0;
};

struct TLUpdatesGetDifference
{
    static constexpr TLValue predicate = TLValue::UpdatesGetDifference;
    enum Flag {
        PtsTotalLimit = 1 << 0,
    };
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

struct TLUploadGetFileHashes
{
    static constexpr TLValue predicate = TLValue::UploadGetFileHashes;
    TLInputFileLocation location;
    quint32 offset = 0;
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

struct TLUsersSetSecureValueErrors
{
    static constexpr TLValue predicate = TLValue::UsersSetSecureValueErrors;
    TLInputUser id;
    TLVector<TLSecureValueError> errors;
};
// End of generated TLFunctions

} // TLFunctions namespace

} // MTProto namespace

} // Telegram namespace

#endif // TELEGRAM_TL_FUNCTIONS_HPP
