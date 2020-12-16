/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TLTYPES_HPP
#define TLTYPES_HPP

#include "telegramqt_global.h"

#include "TLValues.hpp"
#include "TLNumbers.hpp"
#include "UniqueLazyPointer.hpp"

#include <QMetaType>
#include <QVector>

template <typename TL>
using TLPtr = Telegram::UniqueLazyPointer<TL>;

struct TLType
{
    constexpr TLType() = default;
    constexpr TLType(TLValue::Value v)
        : tlType(v)
    {
    }

    TLValue tlType = TLValue::Invalid;
};

struct TLBool : public TLType
{
    constexpr TLBool() = default;
    constexpr TLBool(bool b) :
        TLType(b ? TLValue::BoolTrue : TLValue::BoolFalse)
    {
    }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::BoolFalse:
        case TLValue::BoolTrue:
            return true;
        default:
            return false;
        };
    }

    TLBool &operator=(const bool b)
    {
        if (b) {
            tlType = TLValue::BoolTrue;
        } else {
            tlType = TLValue::BoolFalse;
        }
        return *this;
    }

    operator bool() const
    {
        return tlType == TLValue::BoolTrue;
    }

    TLValue tlType = TLValue::BoolFalse;
};

// Generated TLTypes
struct TLRichText;
struct TLPageBlock;

using TLRichTextPtr = TLPtr<TLRichText>;
using TLPageBlockPtr = TLPtr<TLPageBlock>;

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountDaysTTL : public TLType
{
    constexpr TLAccountDaysTTL() :
        TLType(TLValue::AccountDaysTTL)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountDaysTTL &v) const;

    quint32 days = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPassword : public TLType
{
    TLAccountPassword() :
        TLType(TLValue::AccountNoPassword)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPassword &v) const;

    QByteArray newSalt;
    QString emailUnconfirmedPattern;
    QByteArray currentSalt;
    QString hint;
    bool hasRecovery = false;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPasswordInputSettings : public TLType
{
    TLAccountPasswordInputSettings() :
        TLType(TLValue::AccountPasswordInputSettings)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPasswordInputSettings &v) const;
    enum Flags {
        Hint = 1 << 0,
        NewPasswordHash = 1 << 0,
        NewSalt = 1 << 0,
        Email = 1 << 1,
    };

    quint32 flags = 0;
    QByteArray newSalt;
    QByteArray newPasswordHash;
    QString hint;
    QString email;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPasswordSettings : public TLType
{
    TLAccountPasswordSettings() :
        TLType(TLValue::AccountPasswordSettings)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPasswordSettings &v) const;

    QString email;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountTmpPassword : public TLType
{
    TLAccountTmpPassword() :
        TLType(TLValue::AccountTmpPassword)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountTmpPassword &v) const;

    QByteArray tmpPassword;
    quint32 validUntil = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthCheckedPhone : public TLType
{
    constexpr TLAuthCheckedPhone() :
        TLType(TLValue::AuthCheckedPhone)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthCheckedPhone &v) const;

    bool phoneRegistered = false;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthCodeType : public TLType
{
    constexpr TLAuthCodeType() :
        TLType(TLValue::AuthCodeTypeSms)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthCodeType &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthExportedAuthorization : public TLType
{
    TLAuthExportedAuthorization() :
        TLType(TLValue::AuthExportedAuthorization)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthExportedAuthorization &v) const;

    quint32 id = 0;
    QByteArray bytes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthPasswordRecovery : public TLType
{
    TLAuthPasswordRecovery() :
        TLType(TLValue::AuthPasswordRecovery)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthPasswordRecovery &v) const;

    QString emailPattern;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthSentCodeType : public TLType
{
    TLAuthSentCodeType() :
        TLType(TLValue::AuthSentCodeTypeApp)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthSentCodeType &v) const;

    quint32 length = 0;
    QString pattern;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthorization : public TLType
{
    TLAuthorization() :
        TLType(TLValue::Authorization)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthorization &v) const;

    quint64 hash = 0;
    quint32 flags = 0;
    QString deviceModel;
    QString platform;
    QString systemVersion;
    quint32 apiId = 0;
    QString appName;
    QString appVersion;
    quint32 dateCreated = 0;
    quint32 dateActive = 0;
    QString ip;
    QString country;
    QString region;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBadMsgNotification : public TLType
{
    constexpr TLBadMsgNotification() :
        TLType(TLValue::BadMsgNotification)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBadMsgNotification &v) const;

    quint64 badMsgId = 0;
    quint32 badMsgSeqno = 0;
    quint32 errorCode = 0;
    quint64 newServerSalt = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotCommand : public TLType
{
    TLBotCommand() :
        TLType(TLValue::BotCommand)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBotCommand &v) const;

    QString command;
    QString description;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotInfo : public TLType
{
    TLBotInfo() :
        TLType(TLValue::BotInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBotInfo &v) const;

    quint32 userId = 0;
    QString description;
    QVector<TLBotCommand> commands;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLCdnFileHash : public TLType
{
    TLCdnFileHash() :
        TLType(TLValue::CdnFileHash)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLCdnFileHash &v) const;

    quint32 offset = 0;
    quint32 limit = 0;
    QByteArray hash;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLCdnPublicKey : public TLType
{
    TLCdnPublicKey() :
        TLType(TLValue::CdnPublicKey)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLCdnPublicKey &v) const;

    quint32 dcId = 0;
    QString publicKey;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelParticipantsFilter : public TLType
{
    TLChannelParticipantsFilter() :
        TLType(TLValue::ChannelParticipantsRecent)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelParticipantsFilter &v) const;

    QString q;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatParticipant : public TLType
{
    constexpr TLChatParticipant() :
        TLType(TLValue::ChatParticipant)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatParticipant &v) const;

    quint32 userId = 0;
    quint32 inviterId = 0;
    quint32 date = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatParticipants : public TLType
{
    TLChatParticipants() :
        TLType(TLValue::ChatParticipantsForbidden)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatParticipants &v) const;
    enum Flags {
        SelfParticipant = 1 << 0,
    };

    quint32 flags = 0;
    quint32 chatId = 0;
    TLChatParticipant selfParticipant;
    QVector<TLChatParticipant> participants;
    quint32 version = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLClientDHInnerData : public TLType
{
    TLClientDHInnerData() :
        TLType(TLValue::ClientDHInnerData)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLClientDHInnerData &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint64 retryId = 0;
    QString gB;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContact : public TLType
{
    constexpr TLContact() :
        TLType(TLValue::Contact)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContact &v) const;

    quint32 userId = 0;
    bool mutual = false;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactBlocked : public TLType
{
    constexpr TLContactBlocked() :
        TLType(TLValue::ContactBlocked)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactBlocked &v) const;

    quint32 userId = 0;
    quint32 date = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactLink : public TLType
{
    constexpr TLContactLink() :
        TLType(TLValue::ContactLinkUnknown)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactLink &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLDataJSON : public TLType
{
    TLDataJSON() :
        TLType(TLValue::DataJSON)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDataJSON &v) const;

    QString data;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDestroyAuthKeyRes : public TLType
{
    constexpr TLDestroyAuthKeyRes() :
        TLType(TLValue::DestroyAuthKeyOk)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDestroyAuthKeyRes &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLDestroySessionRes : public TLType
{
    constexpr TLDestroySessionRes() :
        TLType(TLValue::DestroySessionOk)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDestroySessionRes &v) const;

    quint64 sessionId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDisabledFeature : public TLType
{
    TLDisabledFeature() :
        TLType(TLValue::DisabledFeature)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDisabledFeature &v) const;

    QString feature;
    QString description;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLEncryptedChat : public TLType
{
    TLEncryptedChat() :
        TLType(TLValue::EncryptedChatEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLEncryptedChat &v) const;

    quint32 id = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    quint32 adminId = 0;
    quint32 participantId = 0;
    QByteArray gA;
    QByteArray gAOrB;
    quint64 keyFingerprint = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLEncryptedFile : public TLType
{
    constexpr TLEncryptedFile() :
        TLType(TLValue::EncryptedFileEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLEncryptedFile &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 size = 0;
    quint32 dcId = 0;
    quint32 keyFingerprint = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLEncryptedMessage : public TLType
{
    TLEncryptedMessage() :
        TLType(TLValue::EncryptedMessage)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLEncryptedMessage &v) const;

    quint64 randomId = 0;
    quint32 chatId = 0;
    quint32 date = 0;
    QByteArray bytes;
    TLEncryptedFile file;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLError : public TLType
{
    TLError() :
        TLType(TLValue::Error)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLError &v) const;

    quint32 code = 0;
    QString text;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLExportedChatInvite : public TLType
{
    TLExportedChatInvite() :
        TLType(TLValue::ChatInviteEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLExportedChatInvite &v) const;

    QString link;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLExportedMessageLink : public TLType
{
    TLExportedMessageLink() :
        TLType(TLValue::ExportedMessageLink)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLExportedMessageLink &v) const;

    QString link;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFileLocation : public TLType
{
    constexpr TLFileLocation() :
        TLType(TLValue::FileLocationUnavailable)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFileLocation &v) const;

    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    quint32 dcId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFutureSalt : public TLType
{
    constexpr TLFutureSalt() :
        TLType(TLValue::FutureSalt)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFutureSalt &v) const;

    quint32 validSince = 0;
    quint32 validUntil = 0;
    quint64 salt = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFutureSalts : public TLType
{
    TLFutureSalts() :
        TLType(TLValue::FutureSalts)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFutureSalts &v) const;

    quint64 reqMsgId = 0;
    quint32 now = 0;
    QVector<TLFutureSalt> salts;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLGeoPoint : public TLType
{
    constexpr TLGeoPoint() :
        TLType(TLValue::GeoPointEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLGeoPoint &v) const;

    double longitude = 0;
    double latitude = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpAppUpdate : public TLType
{
    TLHelpAppUpdate() :
        TLType(TLValue::HelpAppUpdate)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpAppUpdate &v) const;

    quint32 id = 0;
    bool critical = false;
    QString url;
    QString text;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpInviteText : public TLType
{
    TLHelpInviteText() :
        TLType(TLValue::HelpInviteText)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpInviteText &v) const;

    QString message;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpTermsOfService : public TLType
{
    TLHelpTermsOfService() :
        TLType(TLValue::HelpTermsOfService)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpTermsOfService &v) const;

    QString text;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHighScore : public TLType
{
    constexpr TLHighScore() :
        TLType(TLValue::HighScore)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHighScore &v) const;

    quint32 pos = 0;
    quint32 userId = 0;
    quint32 score = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHttpWait : public TLType
{
    constexpr TLHttpWait() :
        TLType(TLValue::HttpWait)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHttpWait &v) const;

    quint32 maxDelay = 0;
    quint32 waitAfter = 0;
    quint32 maxWait = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLImportedContact : public TLType
{
    constexpr TLImportedContact() :
        TLType(TLValue::ImportedContact)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLImportedContact &v) const;

    quint32 userId = 0;
    quint64 clientId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInlineBotSwitchPM : public TLType
{
    TLInlineBotSwitchPM() :
        TLType(TLValue::InlineBotSwitchPM)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInlineBotSwitchPM &v) const;

    QString text;
    QString startParam;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputAppEvent : public TLType
{
    TLInputAppEvent() :
        TLType(TLValue::InputAppEvent)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputAppEvent &v) const;

    double time = 0;
    QString type;
    quint64 peer = 0;
    QString data;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputBotInlineMessageID : public TLType
{
    constexpr TLInputBotInlineMessageID() :
        TLType(TLValue::InputBotInlineMessageID)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputBotInlineMessageID &v) const;

    quint32 dcId = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputChannel : public TLType
{
    constexpr TLInputChannel() :
        TLType(TLValue::InputChannelEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputChannel &v) const;

    quint32 channelId = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputContact : public TLType
{
    TLInputContact() :
        TLType(TLValue::InputPhoneContact)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputContact &v) const;

    quint64 clientId = 0;
    QString phone;
    QString firstName;
    QString lastName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputDocument : public TLType
{
    constexpr TLInputDocument() :
        TLType(TLValue::InputDocumentEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputDocument &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputEncryptedChat : public TLType
{
    constexpr TLInputEncryptedChat() :
        TLType(TLValue::InputEncryptedChat)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputEncryptedChat &v) const;

    quint32 chatId = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputEncryptedFile : public TLType
{
    TLInputEncryptedFile() :
        TLType(TLValue::InputEncryptedFileEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputEncryptedFile &v) const;

    quint64 id = 0;
    quint32 parts = 0;
    QString md5Checksum;
    quint32 keyFingerprint = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputFile : public TLType
{
    TLInputFile() :
        TLType(TLValue::InputFile)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputFile &v) const;

    quint64 id = 0;
    quint32 parts = 0;
    QString name;
    QString md5Checksum;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputFileLocation : public TLType
{
    constexpr TLInputFileLocation() :
        TLType(TLValue::InputFileLocation)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputFileLocation &v) const;

    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 version = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputGeoPoint : public TLType
{
    constexpr TLInputGeoPoint() :
        TLType(TLValue::InputGeoPointEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputGeoPoint &v) const;

    double latitude = 0;
    double longitude = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPeer : public TLType
{
    constexpr TLInputPeer() :
        TLType(TLValue::InputPeerEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPeer &v) const;

    quint32 chatId = 0;
    quint32 userId = 0;
    quint64 accessHash = 0;
    quint32 channelId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPeerNotifyEvents : public TLType
{
    constexpr TLInputPeerNotifyEvents() :
        TLType(TLValue::InputPeerNotifyEventsEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPeerNotifyEvents &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPhoneCall : public TLType
{
    constexpr TLInputPhoneCall() :
        TLType(TLValue::InputPhoneCall)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPhoneCall &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPhoto : public TLType
{
    constexpr TLInputPhoto() :
        TLType(TLValue::InputPhotoEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPhoto &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPrivacyKey : public TLType
{
    constexpr TLInputPrivacyKey() :
        TLType(TLValue::InputPrivacyKeyStatusTimestamp)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPrivacyKey &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputStickerSet : public TLType
{
    TLInputStickerSet() :
        TLType(TLValue::InputStickerSetEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputStickerSet &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    QString shortName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputStickeredMedia : public TLType
{
    TLInputStickeredMedia() :
        TLType(TLValue::InputStickeredMediaPhoto)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputStickeredMedia &v) const;

    TLInputPhoto inputPhotoId;
    TLInputDocument inputDocumentId;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputUser : public TLType
{
    constexpr TLInputUser() :
        TLType(TLValue::InputUserEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputUser &v) const;

    quint32 userId = 0;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputWebFileLocation : public TLType
{
    TLInputWebFileLocation() :
        TLType(TLValue::InputWebFileLocation)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputWebFileLocation &v) const;

    QString url;
    quint64 accessHash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLIpPort : public TLType
{
    constexpr TLIpPort() :
        TLType(TLValue::IpPort)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLIpPort &v) const;

    quint32 ipv4 = 0;
    quint32 port = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLabeledPrice : public TLType
{
    TLLabeledPrice() :
        TLType(TLValue::LabeledPrice)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLabeledPrice &v) const;

    QString label;
    quint64 amount = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLangPackLanguage : public TLType
{
    TLLangPackLanguage() :
        TLType(TLValue::LangPackLanguage)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLangPackLanguage &v) const;

    QString name;
    QString nativeName;
    QString langCode;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLangPackString : public TLType
{
    TLLangPackString() :
        TLType(TLValue::LangPackString)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLangPackString &v) const;
    enum Flags {
        ZeroValue = 1 << 0,
        OneValue = 1 << 1,
        TwoValue = 1 << 2,
        FewValue = 1 << 3,
        ManyValue = 1 << 4,
    };

    QString key;
    QString value;
    quint32 flags = 0;
    QString zeroValue;
    QString oneValue;
    QString twoValue;
    QString fewValue;
    QString manyValue;
    QString otherValue;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMaskCoords : public TLType
{
    constexpr TLMaskCoords() :
        TLType(TLValue::MaskCoords)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMaskCoords &v) const;

    quint32 n = 0;
    double x = 0;
    double y = 0;
    double zoom = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageEntity : public TLType
{
    TLMessageEntity() :
        TLType(TLValue::MessageEntityUnknown)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageEntity &v) const;

    quint32 offset = 0;
    quint32 length = 0;
    QString language;
    QString url;
    quint32 userId = 0;
    TLInputUser inputUserUserId;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageFwdHeader : public TLType
{
    TLMessageFwdHeader() :
        TLType(TLValue::MessageFwdHeader)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageFwdHeader &v) const;
    enum Flags {
        FromId = 1 << 0,
        ChannelId = 1 << 1,
        ChannelPost = 1 << 2,
        PostAuthor = 1 << 3,
    };

    quint32 flags = 0;
    quint32 fromId = 0;
    quint32 date = 0;
    quint32 channelId = 0;
    quint32 channelPost = 0;
    QString postAuthor;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageRange : public TLType
{
    constexpr TLMessageRange() :
        TLType(TLValue::MessageRange)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageRange &v) const;

    quint32 minId = 0;
    quint32 maxId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesAffectedHistory : public TLType
{
    constexpr TLMessagesAffectedHistory() :
        TLType(TLValue::MessagesAffectedHistory)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesAffectedHistory &v) const;

    quint32 pts = 0;
    quint32 ptsCount = 0;
    quint32 offset = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesAffectedMessages : public TLType
{
    constexpr TLMessagesAffectedMessages() :
        TLType(TLValue::MessagesAffectedMessages)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesAffectedMessages &v) const;

    quint32 pts = 0;
    quint32 ptsCount = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesDhConfig : public TLType
{
    TLMessagesDhConfig() :
        TLType(TLValue::MessagesDhConfigNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesDhConfig &v) const;

    QByteArray random;
    quint32 g = 0;
    QByteArray p;
    quint32 version = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesSentEncryptedMessage : public TLType
{
    TLMessagesSentEncryptedMessage() :
        TLType(TLValue::MessagesSentEncryptedMessage)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesSentEncryptedMessage &v) const;

    quint32 date = 0;
    TLEncryptedFile file;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgDetailedInfo : public TLType
{
    constexpr TLMsgDetailedInfo() :
        TLType(TLValue::MsgDetailedInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgDetailedInfo &v) const;

    quint64 msgId = 0;
    quint64 answerMsgId = 0;
    quint32 bytes = 0;
    quint32 status = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgResendReq : public TLType
{
    TLMsgResendReq() :
        TLType(TLValue::MsgResendReq)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgResendReq &v) const;

    QVector<quint64> msgIds;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsAck : public TLType
{
    TLMsgsAck() :
        TLType(TLValue::MsgsAck)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsAck &v) const;

    QVector<quint64> msgIds;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsAllInfo : public TLType
{
    TLMsgsAllInfo() :
        TLType(TLValue::MsgsAllInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsAllInfo &v) const;

    QVector<quint64> msgIds;
    QString info;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsStateInfo : public TLType
{
    TLMsgsStateInfo() :
        TLType(TLValue::MsgsStateInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsStateInfo &v) const;

    quint64 reqMsgId = 0;
    QString info;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsStateReq : public TLType
{
    TLMsgsStateReq() :
        TLType(TLValue::MsgsStateReq)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsStateReq &v) const;

    QVector<quint64> msgIds;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLNearestDc : public TLType
{
    TLNearestDc() :
        TLType(TLValue::NearestDc)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLNearestDc &v) const;

    QString country;
    quint32 thisDc = 0;
    quint32 nearestDc = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLNewSession : public TLType
{
    constexpr TLNewSession() :
        TLType(TLValue::NewSessionCreated)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLNewSession &v) const;

    quint64 firstMsgId = 0;
    quint64 uniqueId = 0;
    quint64 serverSalt = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPQInnerData : public TLType
{
    TLPQInnerData() :
        TLType(TLValue::PQInnerData)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPQInnerData &v) const;

    QString pq;
    QString p;
    QString q;
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber256 newNonce;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentCharge : public TLType
{
    TLPaymentCharge() :
        TLType(TLValue::PaymentCharge)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentCharge &v) const;

    QString id;
    QString providerChargeId;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentSavedCredentials : public TLType
{
    TLPaymentSavedCredentials() :
        TLType(TLValue::PaymentSavedCredentialsCard)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentSavedCredentials &v) const;

    QString id;
    QString title;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeer : public TLType
{
    constexpr TLPeer() :
        TLType(TLValue::PeerUser)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeer &v) const;

    quint32 userId = 0;
    quint32 chatId = 0;
    quint32 channelId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeerNotifyEvents : public TLType
{
    constexpr TLPeerNotifyEvents() :
        TLType(TLValue::PeerNotifyEventsEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeerNotifyEvents &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneCallDiscardReason : public TLType
{
    constexpr TLPhoneCallDiscardReason() :
        TLType(TLValue::PhoneCallDiscardReasonMissed)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneCallDiscardReason &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneConnection : public TLType
{
    TLPhoneConnection() :
        TLType(TLValue::PhoneConnection)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneConnection &v) const;

    quint64 id = 0;
    QString ip;
    QString ipv6;
    quint32 port = 0;
    QByteArray peerTag;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhotoSize : public TLType
{
    TLPhotoSize() :
        TLType(TLValue::PhotoSizeEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhotoSize &v) const;

    QString type;
    TLFileLocation location;
    quint32 w = 0;
    quint32 h = 0;
    quint32 size = 0;
    QByteArray bytes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPong : public TLType
{
    constexpr TLPong() :
        TLType(TLValue::Pong)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPong &v) const;

    quint64 msgId = 0;
    quint64 pingId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPopularContact : public TLType
{
    constexpr TLPopularContact() :
        TLType(TLValue::PopularContact)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPopularContact &v) const;

    quint64 clientId = 0;
    quint32 importers = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPostAddress : public TLType
{
    TLPostAddress() :
        TLType(TLValue::PostAddress)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPostAddress &v) const;

    QString streetLine1;
    QString streetLine2;
    QString city;
    QString state;
    QString countryIso2;
    QString postCode;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPrivacyKey : public TLType
{
    constexpr TLPrivacyKey() :
        TLType(TLValue::PrivacyKeyStatusTimestamp)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPrivacyKey &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLPrivacyRule : public TLType
{
    TLPrivacyRule() :
        TLType(TLValue::PrivacyValueAllowContacts)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPrivacyRule &v) const;

    QVector<quint32> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLReceivedNotifyMessage : public TLType
{
    constexpr TLReceivedNotifyMessage() :
        TLType(TLValue::ReceivedNotifyMessage)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLReceivedNotifyMessage &v) const;

    quint32 id = 0;
    quint32 flags = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLReportReason : public TLType
{
    TLReportReason() :
        TLType(TLValue::InputReportReasonSpam)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLReportReason &v) const;

    QString text;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLResPQ : public TLType
{
    TLResPQ() :
        TLType(TLValue::ResPQ)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLResPQ &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    QString pq;
    QVector<quint64> serverPublicKeyFingerprints;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRichText : public TLType
{
    TLRichText() :
        TLType(TLValue::TextEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRichText &v) const;

    QString stringText;
    TLRichTextPtr richText;
    QString url;
    quint64 webpageId = 0;
    QString email;
    QVector<TLRichText*> texts;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRpcDropAnswer : public TLType
{
    constexpr TLRpcDropAnswer() :
        TLType(TLValue::RpcAnswerUnknown)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRpcDropAnswer &v) const;

    quint64 msgId = 0;
    quint32 seqNo = 0;
    quint32 bytes = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRpcError : public TLType
{
    TLRpcError() :
        TLType(TLValue::RpcError)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRpcError &v) const;

    quint32 errorCode = 0;
    QString errorMessage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSendMessageAction : public TLType
{
    constexpr TLSendMessageAction() :
        TLType(TLValue::SendMessageTypingAction)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSendMessageAction &v) const;

    quint32 progress = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLServerDHInnerData : public TLType
{
    TLServerDHInnerData() :
        TLType(TLValue::ServerDHInnerData)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLServerDHInnerData &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint32 g = 0;
    QString dhPrime;
    QString gA;
    quint32 serverTime = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLServerDHParams : public TLType
{
    TLServerDHParams() :
        TLType(TLValue::ServerDHParamsFail)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLServerDHParams &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber128 newNonceHash;
    QString encryptedAnswer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSetClientDHParamsAnswer : public TLType
{
    TLSetClientDHParamsAnswer() :
        TLType(TLValue::DhGenOk)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSetClientDHParamsAnswer &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber128 newNonceHash1;
    TLNumber128 newNonceHash2;
    TLNumber128 newNonceHash3;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLShippingOption : public TLType
{
    TLShippingOption() :
        TLType(TLValue::ShippingOption)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLShippingOption &v) const;

    QString id;
    QString title;
    QVector<TLLabeledPrice> prices;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStickerPack : public TLType
{
    TLStickerPack() :
        TLType(TLValue::StickerPack)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStickerPack &v) const;

    QString emoticon;
    QVector<quint64> documents;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStorageFileType : public TLType
{
    constexpr TLStorageFileType() :
        TLType(TLValue::StorageFileUnknown)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStorageFileType &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLTopPeer : public TLType
{
    TLTopPeer() :
        TLType(TLValue::TopPeer)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLTopPeer &v) const;

    TLPeer peer;
    double rating = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLTopPeerCategory : public TLType
{
    constexpr TLTopPeerCategory() :
        TLType(TLValue::TopPeerCategoryBotsPM)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLTopPeerCategory &v) const;

};

struct TELEGRAMQT_INTERNAL_EXPORT TLTopPeerCategoryPeers : public TLType
{
    TLTopPeerCategoryPeers() :
        TLType(TLValue::TopPeerCategoryPeers)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLTopPeerCategoryPeers &v) const;

    TLTopPeerCategory category;
    quint32 count = 0;
    QVector<TLTopPeer> peers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdatesState : public TLType
{
    constexpr TLUpdatesState() :
        TLType(TLValue::UpdatesState)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdatesState &v) const;

    quint32 pts = 0;
    quint32 qts = 0;
    quint32 date = 0;
    quint32 seq = 0;
    quint32 unreadCount = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUploadCdnFile : public TLType
{
    TLUploadCdnFile() :
        TLType(TLValue::UploadCdnFileReuploadNeeded)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUploadCdnFile &v) const;

    QByteArray requestToken;
    QByteArray bytes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUploadFile : public TLType
{
    TLUploadFile() :
        TLType(TLValue::UploadFile)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUploadFile &v) const;

    TLStorageFileType type;
    quint32 mtime = 0;
    QByteArray bytes;
    quint32 dcId = 0;
    QByteArray fileToken;
    QByteArray encryptionKey;
    QByteArray encryptionIv;
    QVector<TLCdnFileHash> cdnFileHashes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUploadWebFile : public TLType
{
    TLUploadWebFile() :
        TLType(TLValue::UploadWebFile)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUploadWebFile &v) const;

    quint32 size = 0;
    QString mimeType;
    TLStorageFileType fileType;
    quint32 mtime = 0;
    QByteArray bytes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUserProfilePhoto : public TLType
{
    TLUserProfilePhoto() :
        TLType(TLValue::UserProfilePhotoEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUserProfilePhoto &v) const;

    quint64 photoId = 0;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUserStatus : public TLType
{
    constexpr TLUserStatus() :
        TLType(TLValue::UserStatusEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUserStatus &v) const;

    quint32 expires = 0;
    quint32 wasOnline = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWallPaper : public TLType
{
    TLWallPaper() :
        TLType(TLValue::WallPaper)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLWallPaper &v) const;

    quint32 id = 0;
    QString title;
    QVector<TLPhotoSize> sizes;
    quint32 color = 0;
    quint32 bgColor = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountAuthorizations : public TLType
{
    TLAccountAuthorizations() :
        TLType(TLValue::AccountAuthorizations)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountAuthorizations &v) const;

    QVector<TLAuthorization> authorizations;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthSentCode : public TLType
{
    TLAuthSentCode() :
        TLType(TLValue::AuthSentCode)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthSentCode &v) const;
    enum Flags {
        PhoneRegistered = 1 << 0,
        NextType = 1 << 1,
        Timeout = 1 << 2,
    };
    bool phoneRegistered() const { return flags & PhoneRegistered; }

    quint32 flags = 0;
    TLAuthSentCodeType type;
    QString phoneCodeHash;
    TLAuthCodeType nextType;
    quint32 timeout = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLCdnConfig : public TLType
{
    TLCdnConfig() :
        TLType(TLValue::CdnConfig)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLCdnConfig &v) const;

    QVector<TLCdnPublicKey> publicKeys;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminLogEventsFilter : public TLType
{
    TLChannelAdminLogEventsFilter() :
        TLType(TLValue::ChannelAdminLogEventsFilter)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelAdminLogEventsFilter &v) const;
    enum Flags {
        Join = 1 << 0,
        Leave = 1 << 1,
        Invite = 1 << 2,
        Ban = 1 << 3,
        Unban = 1 << 4,
        Kick = 1 << 5,
        Unkick = 1 << 6,
        Promote = 1 << 7,
        Demote = 1 << 8,
        Info = 1 << 9,
        Settings = 1 << 10,
        Pinned = 1 << 11,
        Edit = 1 << 12,
        Deleted = 1 << 13,
    };
    bool join() const { return flags & Join; }
    bool leave() const { return flags & Leave; }
    bool invite() const { return flags & Invite; }
    bool ban() const { return flags & Ban; }
    bool unban() const { return flags & Unban; }
    bool kick() const { return flags & Kick; }
    bool unkick() const { return flags & Unkick; }
    bool promote() const { return flags & Promote; }
    bool demote() const { return flags & Demote; }
    bool info() const { return flags & Info; }
    bool settings() const { return flags & Settings; }
    bool pinned() const { return flags & Pinned; }
    bool edit() const { return flags & Edit; }
    bool deleted() const { return flags & Deleted; }

    quint32 flags = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminRights : public TLType
{
    TLChannelAdminRights() :
        TLType(TLValue::ChannelAdminRights)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelAdminRights &v) const;
    enum Flags {
        ChangeInfo = 1 << 0,
        PostMessages = 1 << 1,
        EditMessages = 1 << 2,
        DeleteMessages = 1 << 3,
        BanUsers = 1 << 4,
        InviteUsers = 1 << 5,
        InviteLink = 1 << 6,
        PinMessages = 1 << 7,
        AddAdmins = 1 << 9,
    };
    bool changeInfo() const { return flags & ChangeInfo; }
    bool postMessages() const { return flags & PostMessages; }
    bool editMessages() const { return flags & EditMessages; }
    bool deleteMessages() const { return flags & DeleteMessages; }
    bool banUsers() const { return flags & BanUsers; }
    bool inviteUsers() const { return flags & InviteUsers; }
    bool inviteLink() const { return flags & InviteLink; }
    bool pinMessages() const { return flags & PinMessages; }
    bool addAdmins() const { return flags & AddAdmins; }

    quint32 flags = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelBannedRights : public TLType
{
    TLChannelBannedRights() :
        TLType(TLValue::ChannelBannedRights)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelBannedRights &v) const;
    enum Flags {
        ViewMessages = 1 << 0,
        SendMessages = 1 << 1,
        SendMedia = 1 << 2,
        SendStickers = 1 << 3,
        SendGifs = 1 << 4,
        SendGames = 1 << 5,
        SendInline = 1 << 6,
        EmbedLinks = 1 << 7,
    };
    bool viewMessages() const { return flags & ViewMessages; }
    bool sendMessages() const { return flags & SendMessages; }
    bool sendMedia() const { return flags & SendMedia; }
    bool sendStickers() const { return flags & SendStickers; }
    bool sendGifs() const { return flags & SendGifs; }
    bool sendGames() const { return flags & SendGames; }
    bool sendInline() const { return flags & SendInline; }
    bool embedLinks() const { return flags & EmbedLinks; }

    quint32 flags = 0;
    quint32 untilDate = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelMessagesFilter : public TLType
{
    TLChannelMessagesFilter() :
        TLType(TLValue::ChannelMessagesFilterEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelMessagesFilter &v) const;
    enum Flags {
        ExcludeNewMessages = 1 << 1,
    };
    bool excludeNewMessages() const { return flags & ExcludeNewMessages; }

    quint32 flags = 0;
    QVector<TLMessageRange> ranges;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelParticipant : public TLType
{
    TLChannelParticipant() :
        TLType(TLValue::ChannelParticipant)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelParticipant &v) const;
    enum Flags {
        Left = 1 << 0,
        CanEdit = 1 << 0,
    };
    bool canEdit() const { return flags & CanEdit; }
    bool left() const { return flags & Left; }

    quint32 userId = 0;
    quint32 date = 0;
    quint32 inviterId = 0;
    quint32 flags = 0;
    quint32 promotedBy = 0;
    TLChannelAdminRights adminRights;
    quint32 kickedBy = 0;
    TLChannelBannedRights bannedRights;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatPhoto : public TLType
{
    TLChatPhoto() :
        TLType(TLValue::ChatPhotoEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatPhoto &v) const;

    TLFileLocation photoSmall;
    TLFileLocation photoBig;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactStatus : public TLType
{
    TLContactStatus() :
        TLType(TLValue::ContactStatus)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactStatus &v) const;

    quint32 userId = 0;
    TLUserStatus status;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDcOption : public TLType
{
    TLDcOption() :
        TLType(TLValue::DcOption)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDcOption &v) const;
    enum Flags {
        Ipv6 = 1 << 0,
        MediaOnly = 1 << 1,
        TcpoOnly = 1 << 2,
        Cdn = 1 << 3,
        IsStatic = 1 << 4,
    };
    bool ipv6() const { return flags & Ipv6; }
    bool mediaOnly() const { return flags & MediaOnly; }
    bool tcpoOnly() const { return flags & TcpoOnly; }
    bool cdn() const { return flags & Cdn; }
    bool isStatic() const { return flags & IsStatic; }

    quint32 flags = 0;
    quint32 id = 0;
    QString ipAddress;
    quint32 port = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDocumentAttribute : public TLType
{
    TLDocumentAttribute() :
        TLType(TLValue::DocumentAttributeImageSize)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDocumentAttribute &v) const;
    enum Flags {
        Title = 1 << 0,
        RoundMessage = 1 << 0,
        MaskCoords = 1 << 0,
        Performer = 1 << 1,
        Mask = 1 << 1,
        Waveform = 1 << 2,
        Voice = 1 << 10,
    };
    bool mask() const { return flags & Mask; }
    bool roundMessage() const { return flags & RoundMessage; }
    bool voice() const { return flags & Voice; }

    quint32 w = 0;
    quint32 h = 0;
    quint32 flags = 0;
    QString alt;
    TLInputStickerSet stickerset;
    TLMaskCoords maskCoords;
    quint32 duration = 0;
    QString title;
    QString performer;
    QByteArray waveform;
    QString fileName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDraftMessage : public TLType
{
    TLDraftMessage() :
        TLType(TLValue::DraftMessageEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDraftMessage &v) const;
    enum Flags {
        ReplyToMsgId = 1 << 0,
        NoWebpage = 1 << 1,
        Entities = 1 << 3,
    };
    bool noWebpage() const { return flags & NoWebpage; }

    quint32 flags = 0;
    quint32 replyToMsgId = 0;
    QString message;
    QVector<TLMessageEntity> entities;
    quint32 date = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpConfigSimple : public TLType
{
    TLHelpConfigSimple() :
        TLType(TLValue::HelpConfigSimple)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpConfigSimple &v) const;

    quint32 date = 0;
    quint32 expires = 0;
    quint32 dcId = 0;
    QVector<TLIpPort> ipPortList;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputChatPhoto : public TLType
{
    TLInputChatPhoto() :
        TLType(TLValue::InputChatPhotoEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputChatPhoto &v) const;

    TLInputFile file;
    TLInputPhoto id;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputGame : public TLType
{
    TLInputGame() :
        TLType(TLValue::InputGameID)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputGame &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    TLInputUser botId;
    QString shortName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputNotifyPeer : public TLType
{
    TLInputNotifyPeer() :
        TLType(TLValue::InputNotifyPeer)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputNotifyPeer &v) const;

    TLInputPeer peer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPaymentCredentials : public TLType
{
    TLInputPaymentCredentials() :
        TLType(TLValue::InputPaymentCredentialsSaved)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPaymentCredentials &v) const;
    enum Flags {
        Save = 1 << 0,
    };
    bool save() const { return flags & Save; }

    QString id;
    QByteArray tmpPassword;
    quint32 flags = 0;
    TLDataJSON data;
    TLDataJSON paymentData;
    TLDataJSON paymentToken;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPeerNotifySettings : public TLType
{
    TLInputPeerNotifySettings() :
        TLType(TLValue::InputPeerNotifySettings)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPeerNotifySettings &v) const;
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
    };
    bool showPreviews() const { return flags & ShowPreviews; }
    bool silent() const { return flags & Silent; }

    quint32 flags = 0;
    quint32 muteUntil = 0;
    QString sound;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPrivacyRule : public TLType
{
    TLInputPrivacyRule() :
        TLType(TLValue::InputPrivacyValueAllowContacts)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPrivacyRule &v) const;

    QVector<TLInputUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputStickerSetItem : public TLType
{
    TLInputStickerSetItem() :
        TLType(TLValue::InputStickerSetItem)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputStickerSetItem &v) const;
    enum Flags {
        MaskCoords = 1 << 0,
    };

    quint32 flags = 0;
    TLInputDocument document;
    QString emoji;
    TLMaskCoords maskCoords;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputWebDocument : public TLType
{
    TLInputWebDocument() :
        TLType(TLValue::InputWebDocument)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputWebDocument &v) const;

    QString url;
    quint32 size = 0;
    QString mimeType;
    QVector<TLDocumentAttribute> attributes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInvoice : public TLType
{
    TLInvoice() :
        TLType(TLValue::Invoice)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInvoice &v) const;
    enum Flags {
        Test = 1 << 0,
        NameRequested = 1 << 1,
        PhoneRequested = 1 << 2,
        EmailRequested = 1 << 3,
        ShippingAddressRequested = 1 << 4,
        Flexible = 1 << 5,
    };
    bool test() const { return flags & Test; }
    bool nameRequested() const { return flags & NameRequested; }
    bool phoneRequested() const { return flags & PhoneRequested; }
    bool emailRequested() const { return flags & EmailRequested; }
    bool shippingAddressRequested() const { return flags & ShippingAddressRequested; }
    bool flexible() const { return flags & Flexible; }

    quint32 flags = 0;
    QString currency;
    QVector<TLLabeledPrice> prices;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLKeyboardButton : public TLType
{
    TLKeyboardButton() :
        TLType(TLValue::KeyboardButton)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLKeyboardButton &v) const;
    enum Flags {
        SamePeer = 1 << 0,
    };
    bool samePeer() const { return flags & SamePeer; }

    QString text;
    QString url;
    QByteArray data;
    quint32 flags = 0;
    QString query;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLKeyboardButtonRow : public TLType
{
    TLKeyboardButtonRow() :
        TLType(TLValue::KeyboardButtonRow)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLKeyboardButtonRow &v) const;

    QVector<TLKeyboardButton> buttons;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLangPackDifference : public TLType
{
    TLLangPackDifference() :
        TLType(TLValue::LangPackDifference)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLangPackDifference &v) const;

    QString langCode;
    quint32 fromVersion = 0;
    quint32 version = 0;
    QVector<TLLangPackString> strings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesBotCallbackAnswer : public TLType
{
    TLMessagesBotCallbackAnswer() :
        TLType(TLValue::MessagesBotCallbackAnswer)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesBotCallbackAnswer &v) const;
    enum Flags {
        Message = 1 << 0,
        Alert = 1 << 1,
        Url = 1 << 2,
        HasUrl = 1 << 3,
        NativeUi = 1 << 4,
    };
    bool alert() const { return flags & Alert; }
    bool hasUrl() const { return flags & HasUrl; }
    bool nativeUi() const { return flags & NativeUi; }

    quint32 flags = 0;
    QString message;
    QString url;
    quint32 cacheTime = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFilter : public TLType
{
    TLMessagesFilter() :
        TLType(TLValue::InputMessagesFilterEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFilter &v) const;
    enum Flags {
        Missed = 1 << 0,
    };
    bool missed() const { return flags & Missed; }

    quint32 flags = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesMessageEditData : public TLType
{
    TLMessagesMessageEditData() :
        TLType(TLValue::MessagesMessageEditData)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesMessageEditData &v) const;
    enum Flags {
        Caption = 1 << 0,
    };
    bool caption() const { return flags & Caption; }

    quint32 flags = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLNotifyPeer : public TLType
{
    TLNotifyPeer() :
        TLType(TLValue::NotifyPeer)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLNotifyPeer &v) const;

    TLPeer peer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentRequestedInfo : public TLType
{
    TLPaymentRequestedInfo() :
        TLType(TLValue::PaymentRequestedInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentRequestedInfo &v) const;
    enum Flags {
        Name = 1 << 0,
        Phone = 1 << 1,
        Email = 1 << 2,
        ShippingAddress = 1 << 3,
    };

    quint32 flags = 0;
    QString name;
    QString phone;
    QString email;
    TLPostAddress shippingAddress;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsSavedInfo : public TLType
{
    TLPaymentsSavedInfo() :
        TLType(TLValue::PaymentsSavedInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsSavedInfo &v) const;
    enum Flags {
        SavedInfo = 1 << 0,
        HasSavedCredentials = 1 << 1,
    };
    bool hasSavedCredentials() const { return flags & HasSavedCredentials; }

    quint32 flags = 0;
    TLPaymentRequestedInfo savedInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsValidatedRequestedInfo : public TLType
{
    TLPaymentsValidatedRequestedInfo() :
        TLType(TLValue::PaymentsValidatedRequestedInfo)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsValidatedRequestedInfo &v) const;
    enum Flags {
        Id = 1 << 0,
        ShippingOptions = 1 << 1,
    };

    quint32 flags = 0;
    QString id;
    QVector<TLShippingOption> shippingOptions;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeerNotifySettings : public TLType
{
    TLPeerNotifySettings() :
        TLType(TLValue::PeerNotifySettingsEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeerNotifySettings &v) const;
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
    };
    bool showPreviews() const { return flags & ShowPreviews; }
    bool silent() const { return flags & Silent; }

    quint32 flags = 0;
    quint32 muteUntil = 0;
    QString sound;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeerSettings : public TLType
{
    TLPeerSettings() :
        TLType(TLValue::PeerSettings)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeerSettings &v) const;
    enum Flags {
        ReportSpam = 1 << 0,
    };
    bool reportSpam() const { return flags & ReportSpam; }

    quint32 flags = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneCallProtocol : public TLType
{
    TLPhoneCallProtocol() :
        TLType(TLValue::PhoneCallProtocol)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneCallProtocol &v) const;
    enum Flags {
        UdpP2p = 1 << 0,
        UdpReflector = 1 << 1,
    };
    bool udpP2p() const { return flags & UdpP2p; }
    bool udpReflector() const { return flags & UdpReflector; }

    quint32 flags = 0;
    quint32 minLayer = 0;
    quint32 maxLayer = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoto : public TLType
{
    TLPhoto() :
        TLType(TLValue::PhotoEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoto &v) const;
    enum Flags {
        HasStickers = 1 << 0,
    };
    bool hasStickers() const { return flags & HasStickers; }

    quint64 id = 0;
    quint32 flags = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    QVector<TLPhotoSize> sizes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLReplyMarkup : public TLType
{
    TLReplyMarkup() :
        TLType(TLValue::ReplyKeyboardHide)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLReplyMarkup &v) const;
    enum Flags {
        Resize = 1 << 0,
        SingleUse = 1 << 1,
        Selective = 1 << 2,
    };
    bool selective() const { return flags & Selective; }
    bool singleUse() const { return flags & SingleUse; }
    bool resize() const { return flags & Resize; }

    quint32 flags = 0;
    QVector<TLKeyboardButtonRow> rows;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStickerSet : public TLType
{
    TLStickerSet() :
        TLType(TLValue::StickerSet)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStickerSet &v) const;
    enum Flags {
        Installed = 1 << 0,
        Archived = 1 << 1,
        Official = 1 << 2,
        Masks = 1 << 3,
    };
    bool installed() const { return flags & Installed; }
    bool archived() const { return flags & Archived; }
    bool official() const { return flags & Official; }
    bool masks() const { return flags & Masks; }

    quint32 flags = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    QString title;
    QString shortName;
    quint32 count = 0;
    quint32 hash = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUser : public TLType
{
    TLUser() :
        TLType(TLValue::UserEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUser &v) const;
    enum Flags {
        AccessHash = 1 << 0,
        FirstName = 1 << 1,
        LastName = 1 << 2,
        Username = 1 << 3,
        Phone = 1 << 4,
        Photo = 1 << 5,
        Status = 1 << 6,
        Self = 1 << 10,
        Contact = 1 << 11,
        MutualContact = 1 << 12,
        Deleted = 1 << 13,
        BotInfoVersion = 1 << 14,
        Bot = 1 << 14,
        BotChatHistory = 1 << 15,
        BotNochats = 1 << 16,
        Verified = 1 << 17,
        RestrictionReason = 1 << 18,
        Restricted = 1 << 18,
        BotInlinePlaceholder = 1 << 19,
        Min = 1 << 20,
        BotInlineGeo = 1 << 21,
        LangCode = 1 << 22,
    };
    bool self() const { return flags & Self; }
    bool contact() const { return flags & Contact; }
    bool mutualContact() const { return flags & MutualContact; }
    bool deleted() const { return flags & Deleted; }
    bool bot() const { return flags & Bot; }
    bool botChatHistory() const { return flags & BotChatHistory; }
    bool botNochats() const { return flags & BotNochats; }
    bool verified() const { return flags & Verified; }
    bool restricted() const { return flags & Restricted; }
    bool min() const { return flags & Min; }
    bool botInlineGeo() const { return flags & BotInlineGeo; }

    quint32 id = 0;
    quint32 flags = 0;
    quint64 accessHash = 0;
    QString firstName;
    QString lastName;
    QString username;
    QString phone;
    TLUserProfilePhoto photo;
    TLUserStatus status;
    quint32 botInfoVersion = 0;
    QString restrictionReason;
    QString botInlinePlaceholder;
    QString langCode;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWebDocument : public TLType
{
    TLWebDocument() :
        TLType(TLValue::WebDocument)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLWebDocument &v) const;

    QString url;
    quint64 accessHash = 0;
    quint32 size = 0;
    QString mimeType;
    QVector<TLDocumentAttribute> attributes;
    quint32 dcId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPrivacyRules : public TLType
{
    TLAccountPrivacyRules() :
        TLType(TLValue::AccountPrivacyRules)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPrivacyRules &v) const;

    QVector<TLPrivacyRule> rules;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthAuthorization : public TLType
{
    TLAuthAuthorization() :
        TLType(TLValue::AuthAuthorization)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthAuthorization &v) const;
    enum Flags {
        TmpSessions = 1 << 0,
    };

    quint32 flags = 0;
    quint32 tmpSessions = 0;
    TLUser user;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotInlineMessage : public TLType
{
    TLBotInlineMessage() :
        TLType(TLValue::BotInlineMessageMediaAuto)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBotInlineMessage &v) const;
    enum Flags {
        NoWebpage = 1 << 0,
        Entities = 1 << 1,
        ReplyMarkup = 1 << 2,
    };
    bool noWebpage() const { return flags & NoWebpage; }

    quint32 flags = 0;
    QString caption;
    TLReplyMarkup replyMarkup;
    QString message;
    QVector<TLMessageEntity> entities;
    TLGeoPoint geo;
    quint32 period = 0;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelsChannelParticipant : public TLType
{
    TLChannelsChannelParticipant() :
        TLType(TLValue::ChannelsChannelParticipant)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelsChannelParticipant &v) const;

    TLChannelParticipant participant;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelsChannelParticipants : public TLType
{
    TLChannelsChannelParticipants() :
        TLType(TLValue::ChannelsChannelParticipants)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelsChannelParticipants &v) const;

    quint32 count = 0;
    QVector<TLChannelParticipant> participants;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChat : public TLType
{
    TLChat() :
        TLType(TLValue::ChatEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChat &v) const;
    enum Flags {
        Creator = 1 << 0,
        Kicked = 1 << 1,
        Left = 1 << 2,
        Editor = 1 << 3,
        AdminsEnabled = 1 << 3,
        Admin = 1 << 4,
        Broadcast = 1 << 5,
        Deactivated = 1 << 5,
        Username = 1 << 6,
        MigratedTo = 1 << 6,
        Verified = 1 << 7,
        Megagroup = 1 << 8,
        RestrictionReason = 1 << 9,
        Restricted = 1 << 9,
        Democracy = 1 << 10,
        Signatures = 1 << 11,
        Min = 1 << 12,
        AccessHash = 1 << 13,
        AdminRights = 1 << 14,
        BannedRights = 1 << 15,
        UntilDate = 1 << 16,
    };
    bool creator() const { return flags & Creator; }
    bool kicked() const { return flags & Kicked; }
    bool left() const { return flags & Left; }
    bool adminsEnabled() const { return flags & AdminsEnabled; }
    bool admin() const { return flags & Admin; }
    bool deactivated() const { return flags & Deactivated; }
    bool editor() const { return flags & Editor; }
    bool broadcast() const { return flags & Broadcast; }
    bool verified() const { return flags & Verified; }
    bool megagroup() const { return flags & Megagroup; }
    bool restricted() const { return flags & Restricted; }
    bool democracy() const { return flags & Democracy; }
    bool signatures() const { return flags & Signatures; }
    bool min() const { return flags & Min; }

    quint32 id = 0;
    quint32 flags = 0;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount = 0;
    quint32 date = 0;
    quint32 version = 0;
    TLInputChannel migratedTo;
    quint64 accessHash = 0;
    QString username;
    QString restrictionReason;
    TLChannelAdminRights adminRights;
    TLChannelBannedRights bannedRights;
    quint32 untilDate = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatFull : public TLType
{
    TLChatFull() :
        TLType(TLValue::ChatFull)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatFull &v) const;
    enum Flags {
        ParticipantsCount = 1 << 0,
        AdminsCount = 1 << 1,
        BannedCount = 1 << 2,
        KickedCount = 1 << 2,
        CanViewParticipants = 1 << 3,
        MigratedFromMaxId = 1 << 4,
        MigratedFromChatId = 1 << 4,
        PinnedMsgId = 1 << 5,
        CanSetUsername = 1 << 6,
        CanSetStickers = 1 << 7,
        Stickerset = 1 << 8,
        AvailableMinId = 1 << 9,
        HiddenPrehistory = 1 << 10,
    };
    bool canViewParticipants() const { return flags & CanViewParticipants; }
    bool canSetUsername() const { return flags & CanSetUsername; }
    bool canSetStickers() const { return flags & CanSetStickers; }
    bool hiddenPrehistory() const { return flags & HiddenPrehistory; }

    quint32 id = 0;
    TLChatParticipants participants;
    TLPhoto chatPhoto;
    TLPeerNotifySettings notifySettings;
    TLExportedChatInvite exportedInvite;
    QVector<TLBotInfo> botInfo;
    quint32 flags = 0;
    QString about;
    quint32 participantsCount = 0;
    quint32 adminsCount = 0;
    quint32 kickedCount = 0;
    quint32 bannedCount = 0;
    quint32 readInboxMaxId = 0;
    quint32 readOutboxMaxId = 0;
    quint32 unreadCount = 0;
    quint32 migratedFromChatId = 0;
    quint32 migratedFromMaxId = 0;
    quint32 pinnedMsgId = 0;
    TLStickerSet stickerset;
    quint32 availableMinId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatInvite : public TLType
{
    TLChatInvite() :
        TLType(TLValue::ChatInviteAlready)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatInvite &v) const;
    enum Flags {
        Channel = 1 << 0,
        Broadcast = 1 << 1,
        IsPublic = 1 << 2,
        Megagroup = 1 << 3,
        Participants = 1 << 4,
    };
    bool channel() const { return flags & Channel; }
    bool broadcast() const { return flags & Broadcast; }
    bool isPublic() const { return flags & IsPublic; }
    bool megagroup() const { return flags & Megagroup; }

    TLChat chat;
    quint32 flags = 0;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount = 0;
    QVector<TLUser> participants;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLConfig : public TLType
{
    TLConfig() :
        TLType(TLValue::Config)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLConfig &v) const;
    enum Flags {
        TmpSessions = 1 << 0,
        PhonecallsEnabled = 1 << 1,
        LangPackVersion = 1 << 2,
        SuggestedLangCode = 1 << 2,
    };
    bool phonecallsEnabled() const { return flags & PhonecallsEnabled; }

    quint32 flags = 0;
    quint32 date = 0;
    quint32 expires = 0;
    bool testMode = false;
    quint32 thisDc = 0;
    QVector<TLDcOption> dcOptions;
    quint32 chatSizeMax = 0;
    quint32 megagroupSizeMax = 0;
    quint32 forwardedCountMax = 0;
    quint32 onlineUpdatePeriodMs = 0;
    quint32 offlineBlurTimeoutMs = 0;
    quint32 offlineIdleTimeoutMs = 0;
    quint32 onlineCloudTimeoutMs = 0;
    quint32 notifyCloudDelayMs = 0;
    quint32 notifyDefaultDelayMs = 0;
    quint32 chatBigSize = 0;
    quint32 pushChatPeriodMs = 0;
    quint32 pushChatLimit = 0;
    quint32 savedGifsLimit = 0;
    quint32 editTimeLimit = 0;
    quint32 ratingEDecay = 0;
    quint32 stickersRecentLimit = 0;
    quint32 stickersFavedLimit = 0;
    quint32 channelsReadMediaPeriod = 0;
    quint32 tmpSessions = 0;
    quint32 pinnedDialogsCountMax = 0;
    quint32 callReceiveTimeoutMs = 0;
    quint32 callRingTimeoutMs = 0;
    quint32 callConnectTimeoutMs = 0;
    quint32 callPacketTimeoutMs = 0;
    QString meUrlPrefix;
    QString suggestedLangCode;
    quint32 langPackVersion = 0;
    QVector<TLDisabledFeature> disabledFeatures;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsBlocked : public TLType
{
    TLContactsBlocked() :
        TLType(TLValue::ContactsBlocked)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsBlocked &v) const;

    QVector<TLContactBlocked> blocked;
    QVector<TLUser> users;
    quint32 count = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsContacts : public TLType
{
    TLContactsContacts() :
        TLType(TLValue::ContactsContactsNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsContacts &v) const;

    QVector<TLContact> contacts;
    quint32 savedCount = 0;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsFound : public TLType
{
    TLContactsFound() :
        TLType(TLValue::ContactsFound)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsFound &v) const;

    QVector<TLPeer> results;
    QVector<TLChat> chats;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsImportedContacts : public TLType
{
    TLContactsImportedContacts() :
        TLType(TLValue::ContactsImportedContacts)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsImportedContacts &v) const;

    QVector<TLImportedContact> imported;
    QVector<TLPopularContact> popularInvites;
    QVector<quint64> retryContacts;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsLink : public TLType
{
    TLContactsLink() :
        TLType(TLValue::ContactsLink)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsLink &v) const;

    TLContactLink myLink;
    TLContactLink foreignLink;
    TLUser user;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsResolvedPeer : public TLType
{
    TLContactsResolvedPeer() :
        TLType(TLValue::ContactsResolvedPeer)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsResolvedPeer &v) const;

    TLPeer peer;
    QVector<TLChat> chats;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsTopPeers : public TLType
{
    TLContactsTopPeers() :
        TLType(TLValue::ContactsTopPeersNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsTopPeers &v) const;

    QVector<TLTopPeerCategoryPeers> categories;
    QVector<TLChat> chats;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDialog : public TLType
{
    TLDialog() :
        TLType(TLValue::Dialog)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDialog &v) const;
    enum Flags {
        Pts = 1 << 0,
        Draft = 1 << 1,
        Pinned = 1 << 2,
    };
    bool pinned() const { return flags & Pinned; }

    quint32 flags = 0;
    TLPeer peer;
    quint32 topMessage = 0;
    quint32 readInboxMaxId = 0;
    quint32 readOutboxMaxId = 0;
    quint32 unreadCount = 0;
    quint32 unreadMentionsCount = 0;
    TLPeerNotifySettings notifySettings;
    quint32 pts = 0;
    TLDraftMessage draft;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDocument : public TLType
{
    TLDocument() :
        TLType(TLValue::DocumentEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDocument &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    QString mimeType;
    quint32 size = 0;
    TLPhotoSize thumb;
    quint32 dcId = 0;
    quint32 version = 0;
    QVector<TLDocumentAttribute> attributes;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFoundGif : public TLType
{
    TLFoundGif() :
        TLType(TLValue::FoundGif)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFoundGif &v) const;

    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w = 0;
    quint32 h = 0;
    TLPhoto photo;
    TLDocument document;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLGame : public TLType
{
    TLGame() :
        TLType(TLValue::Game)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLGame &v) const;
    enum Flags {
        Document = 1 << 0,
    };

    quint32 flags = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    QString shortName;
    QString title;
    QString description;
    TLPhoto photo;
    TLDocument document;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpSupport : public TLType
{
    TLHelpSupport() :
        TLType(TLValue::HelpSupport)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpSupport &v) const;

    QString phoneNumber;
    TLUser user;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputBotInlineMessage : public TLType
{
    TLInputBotInlineMessage() :
        TLType(TLValue::InputBotInlineMessageMediaAuto)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputBotInlineMessage &v) const;
    enum Flags {
        NoWebpage = 1 << 0,
        Entities = 1 << 1,
        ReplyMarkup = 1 << 2,
    };
    bool noWebpage() const { return flags & NoWebpage; }

    quint32 flags = 0;
    QString caption;
    TLReplyMarkup replyMarkup;
    QString message;
    QVector<TLMessageEntity> entities;
    TLInputGeoPoint geoPoint;
    quint32 period = 0;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputBotInlineResult : public TLType
{
    TLInputBotInlineResult() :
        TLType(TLValue::InputBotInlineResult)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputBotInlineResult &v) const;
    enum Flags {
        Title = 1 << 1,
        Description = 1 << 2,
        Url = 1 << 3,
        ThumbUrl = 1 << 4,
        ContentType = 1 << 5,
        ContentUrl = 1 << 5,
        H = 1 << 6,
        W = 1 << 6,
        Duration = 1 << 7,
    };

    quint32 flags = 0;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w = 0;
    quint32 h = 0;
    quint32 duration = 0;
    TLInputBotInlineMessage sendMessage;
    TLInputPhoto photo;
    TLInputDocument document;
    QString shortName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputMedia : public TLType
{
    TLInputMedia() :
        TLType(TLValue::InputMediaEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputMedia &v) const;
    enum Flags {
        Photo = 1 << 0,
        TtlSeconds0 = 1 << 0,
        Stickers = 1 << 0,
        TtlSeconds1 = 1 << 1,
        Thumb = 1 << 2,
        NosoundVideo = 1 << 3,
    };
    bool nosoundVideo() const { return flags & NosoundVideo; }

    quint32 flags = 0;
    TLInputFile file;
    QString caption;
    QVector<TLInputDocument> stickers;
    quint32 ttlSeconds = 0;
    TLInputPhoto inputPhotoId;
    TLInputGeoPoint geoPoint;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    TLInputFile thumb;
    QString mimeType;
    QVector<TLDocumentAttribute> attributes;
    TLInputDocument inputDocumentId;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString venueType;
    QString url;
    QString q;
    TLInputGame inputGameId;
    QString description;
    TLInputWebDocument photo;
    TLInvoice invoice;
    QByteArray payload;
    QString startParam;
    quint32 period = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageAction : public TLType
{
    TLMessageAction() :
        TLType(TLValue::MessageActionEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageAction &v) const;
    enum Flags {
        Reason = 1 << 0,
        Info = 1 << 0,
        Duration = 1 << 1,
        ShippingOptionId = 1 << 1,
    };

    QString title;
    QVector<quint32> users;
    TLPhoto photo;
    quint32 userId = 0;
    quint32 inviterId = 0;
    quint32 channelId = 0;
    quint32 chatId = 0;
    quint64 gameId = 0;
    quint32 score = 0;
    quint32 flags = 0;
    QString currency;
    quint64 totalAmount = 0;
    QByteArray payload;
    TLPaymentRequestedInfo info;
    QString shippingOptionId;
    TLPaymentCharge charge;
    quint64 callId = 0;
    TLPhoneCallDiscardReason reason;
    quint32 duration = 0;
    QString message;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesAllStickers : public TLType
{
    TLMessagesAllStickers() :
        TLType(TLValue::MessagesAllStickersNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesAllStickers &v) const;

    quint32 hash = 0;
    QVector<TLStickerSet> sets;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesChatFull : public TLType
{
    TLMessagesChatFull() :
        TLType(TLValue::MessagesChatFull)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesChatFull &v) const;

    TLChatFull fullChat;
    QVector<TLChat> chats;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesChats : public TLType
{
    TLMessagesChats() :
        TLType(TLValue::MessagesChats)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesChats &v) const;

    QVector<TLChat> chats;
    quint32 count = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFavedStickers : public TLType
{
    TLMessagesFavedStickers() :
        TLType(TLValue::MessagesFavedStickersNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFavedStickers &v) const;

    quint32 hash = 0;
    QVector<TLStickerPack> packs;
    QVector<TLDocument> stickers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFoundGifs : public TLType
{
    TLMessagesFoundGifs() :
        TLType(TLValue::MessagesFoundGifs)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFoundGifs &v) const;

    quint32 nextOffset = 0;
    QVector<TLFoundGif> results;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesHighScores : public TLType
{
    TLMessagesHighScores() :
        TLType(TLValue::MessagesHighScores)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesHighScores &v) const;

    QVector<TLHighScore> scores;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesRecentStickers : public TLType
{
    TLMessagesRecentStickers() :
        TLType(TLValue::MessagesRecentStickersNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesRecentStickers &v) const;

    quint32 hash = 0;
    QVector<TLDocument> stickers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesSavedGifs : public TLType
{
    TLMessagesSavedGifs() :
        TLType(TLValue::MessagesSavedGifsNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesSavedGifs &v) const;

    quint32 hash = 0;
    QVector<TLDocument> gifs;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesStickerSet : public TLType
{
    TLMessagesStickerSet() :
        TLType(TLValue::MessagesStickerSet)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesStickerSet &v) const;

    TLStickerSet set;
    QVector<TLStickerPack> packs;
    QVector<TLDocument> documents;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesStickers : public TLType
{
    TLMessagesStickers() :
        TLType(TLValue::MessagesStickersNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesStickers &v) const;

    QString hash;
    QVector<TLDocument> stickers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPage : public TLType
{
    TLPage() :
        TLType(TLValue::PagePart)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPage &v) const;

    QVector<TLPageBlock*> blocks;
    QVector<TLPhoto> photos;
    QVector<TLDocument> documents;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageBlock : public TLType
{
    TLPageBlock() :
        TLType(TLValue::PageBlockUnsupported)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageBlock &v) const;
    enum Flags {
        FullWidth = 1 << 0,
        Autoplay = 1 << 0,
        Url = 1 << 1,
        Loop = 1 << 1,
        Html = 1 << 2,
        AllowScrolling = 1 << 3,
        PosterPhotoId = 1 << 4,
    };
    bool autoplay() const { return flags & Autoplay; }
    bool loop() const { return flags & Loop; }
    bool fullWidth() const { return flags & FullWidth; }
    bool allowScrolling() const { return flags & AllowScrolling; }

    TLRichTextPtr text;
    TLRichTextPtr richTextAuthor;
    quint32 publishedDate = 0;
    QString language;
    QString name;
    bool ordered = false;
    QVector<TLRichText*> richTextItemsVector;
    TLRichTextPtr caption;
    quint64 photoId = 0;
    quint32 flags = 0;
    quint64 videoId = 0;
    TLPageBlockPtr cover;
    QString url;
    QString html;
    quint64 posterPhotoId = 0;
    quint32 w = 0;
    quint32 h = 0;
    quint64 webpageId = 0;
    quint64 authorPhotoId = 0;
    QString stringAuthor;
    quint32 date = 0;
    QVector<TLPageBlock*> blocks;
    QVector<TLPageBlock*> pageBlockItemsVector;
    TLChat channel;
    quint64 audioId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsPaymentForm : public TLType
{
    TLPaymentsPaymentForm() :
        TLType(TLValue::PaymentsPaymentForm)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsPaymentForm &v) const;
    enum Flags {
        SavedInfo = 1 << 0,
        SavedCredentials = 1 << 1,
        CanSaveCredentials = 1 << 2,
        PasswordMissing = 1 << 3,
        NativeParams = 1 << 4,
        NativeProvider = 1 << 4,
    };
    bool canSaveCredentials() const { return flags & CanSaveCredentials; }
    bool passwordMissing() const { return flags & PasswordMissing; }

    quint32 flags = 0;
    quint32 botId = 0;
    TLInvoice invoice;
    quint32 providerId = 0;
    QString url;
    QString nativeProvider;
    TLDataJSON nativeParams;
    TLPaymentRequestedInfo savedInfo;
    TLPaymentSavedCredentials savedCredentials;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsPaymentReceipt : public TLType
{
    TLPaymentsPaymentReceipt() :
        TLType(TLValue::PaymentsPaymentReceipt)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsPaymentReceipt &v) const;
    enum Flags {
        Info = 1 << 0,
        Shipping = 1 << 1,
    };

    quint32 flags = 0;
    quint32 date = 0;
    quint32 botId = 0;
    TLInvoice invoice;
    quint32 providerId = 0;
    TLPaymentRequestedInfo info;
    TLShippingOption shipping;
    QString currency;
    quint64 totalAmount = 0;
    QString credentialsTitle;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneCall : public TLType
{
    TLPhoneCall() :
        TLType(TLValue::PhoneCallEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneCall &v) const;
    enum Flags {
        Reason = 1 << 0,
        ReceiveDate = 1 << 0,
        Duration = 1 << 1,
        NeedRating = 1 << 2,
        NeedDebug = 1 << 3,
    };
    bool needRating() const { return flags & NeedRating; }
    bool needDebug() const { return flags & NeedDebug; }

    quint64 id = 0;
    quint32 flags = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    quint32 adminId = 0;
    quint32 participantId = 0;
    TLPhoneCallProtocol protocol;
    quint32 receiveDate = 0;
    QByteArray gAHash;
    QByteArray gB;
    QByteArray gAOrB;
    quint64 keyFingerprint = 0;
    TLPhoneConnection connection;
    QVector<TLPhoneConnection> alternativeConnections;
    quint32 startDate = 0;
    TLPhoneCallDiscardReason reason;
    quint32 duration = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhonePhoneCall : public TLType
{
    TLPhonePhoneCall() :
        TLType(TLValue::PhonePhoneCall)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhonePhoneCall &v) const;

    TLPhoneCall phoneCall;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhotosPhoto : public TLType
{
    TLPhotosPhoto() :
        TLType(TLValue::PhotosPhoto)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhotosPhoto &v) const;

    TLPhoto photo;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhotosPhotos : public TLType
{
    TLPhotosPhotos() :
        TLType(TLValue::PhotosPhotos)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhotosPhotos &v) const;

    QVector<TLPhoto> photos;
    QVector<TLUser> users;
    quint32 count = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStickerSetCovered : public TLType
{
    TLStickerSetCovered() :
        TLType(TLValue::StickerSetCovered)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStickerSetCovered &v) const;

    TLStickerSet set;
    TLDocument cover;
    QVector<TLDocument> covers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUserFull : public TLType
{
    TLUserFull() :
        TLType(TLValue::UserFull)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUserFull &v) const;
    enum Flags {
        Blocked = 1 << 0,
        About = 1 << 1,
        ProfilePhoto = 1 << 2,
        BotInfo = 1 << 3,
        PhoneCallsAvailable = 1 << 4,
        PhoneCallsPrivate = 1 << 5,
    };
    bool blocked() const { return flags & Blocked; }
    bool phoneCallsAvailable() const { return flags & PhoneCallsAvailable; }
    bool phoneCallsPrivate() const { return flags & PhoneCallsPrivate; }

    quint32 flags = 0;
    TLUser user;
    QString about;
    TLContactsLink link;
    TLPhoto profilePhoto;
    TLPeerNotifySettings notifySettings;
    TLBotInfo botInfo;
    quint32 commonChatsCount = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWebPage : public TLType
{
    TLWebPage() :
        TLType(TLValue::WebPageEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLWebPage &v) const;
    enum Flags {
        Type = 1 << 0,
        SiteName = 1 << 1,
        Title = 1 << 2,
        Description = 1 << 3,
        Photo = 1 << 4,
        EmbedType = 1 << 5,
        EmbedUrl = 1 << 5,
        EmbedHeight = 1 << 6,
        EmbedWidth = 1 << 6,
        Duration = 1 << 7,
        Author = 1 << 8,
        Document = 1 << 9,
        CachedPage = 1 << 10,
    };

    quint64 id = 0;
    quint32 date = 0;
    quint32 flags = 0;
    QString url;
    QString displayUrl;
    quint32 hash = 0;
    QString type;
    QString siteName;
    QString title;
    QString description;
    TLPhoto photo;
    QString embedUrl;
    QString embedType;
    quint32 embedWidth = 0;
    quint32 embedHeight = 0;
    quint32 duration = 0;
    QString author;
    TLDocument document;
    TLPage cachedPage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotInlineResult : public TLType
{
    TLBotInlineResult() :
        TLType(TLValue::BotInlineResult)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBotInlineResult &v) const;
    enum Flags {
        Photo = 1 << 0,
        Document = 1 << 1,
        Title1 = 1 << 1,
        Title2 = 1 << 2,
        Description2 = 1 << 2,
        Description3 = 1 << 3,
        Url = 1 << 3,
        ThumbUrl = 1 << 4,
        ContentType = 1 << 5,
        ContentUrl = 1 << 5,
        H = 1 << 6,
        W = 1 << 6,
        Duration = 1 << 7,
    };

    quint32 flags = 0;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w = 0;
    quint32 h = 0;
    quint32 duration = 0;
    TLBotInlineMessage sendMessage;
    TLPhoto photo;
    TLDocument document;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageMedia : public TLType
{
    TLMessageMedia() :
        TLType(TLValue::MessageMediaEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageMedia &v) const;
    enum Flags {
        WebDocumentPhoto = 1 << 0,
        Document = 1 << 0,
        Photo = 1 << 0,
        ShippingAddressRequested = 1 << 1,
        Caption = 1 << 1,
        ReceiptMsgId = 1 << 2,
        TtlSeconds = 1 << 2,
        Test = 1 << 3,
    };
    bool shippingAddressRequested() const { return flags & ShippingAddressRequested; }
    bool test() const { return flags & Test; }

    quint32 flags = 0;
    TLPhoto photo;
    QString caption;
    quint32 ttlSeconds = 0;
    TLGeoPoint geo;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 userId = 0;
    TLDocument document;
    TLWebPage webpage;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString venueType;
    TLGame game;
    QString description;
    TLWebDocument webDocumentPhoto;
    quint32 receiptMsgId = 0;
    QString currency;
    quint64 totalAmount = 0;
    QString startParam;
    quint32 period = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesArchivedStickers : public TLType
{
    TLMessagesArchivedStickers() :
        TLType(TLValue::MessagesArchivedStickers)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesArchivedStickers &v) const;

    quint32 count = 0;
    QVector<TLStickerSetCovered> sets;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesBotResults : public TLType
{
    TLMessagesBotResults() :
        TLType(TLValue::MessagesBotResults)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesBotResults &v) const;
    enum Flags {
        Gallery = 1 << 0,
        NextOffset = 1 << 1,
        SwitchPm = 1 << 2,
    };
    bool gallery() const { return flags & Gallery; }

    quint32 flags = 0;
    quint64 queryId = 0;
    QString nextOffset;
    TLInlineBotSwitchPM switchPm;
    QVector<TLBotInlineResult> results;
    quint32 cacheTime = 0;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFeaturedStickers : public TLType
{
    TLMessagesFeaturedStickers() :
        TLType(TLValue::MessagesFeaturedStickersNotModified)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFeaturedStickers &v) const;

    quint32 hash = 0;
    QVector<TLStickerSetCovered> sets;
    QVector<quint64> unread;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesStickerSetInstallResult : public TLType
{
    TLMessagesStickerSetInstallResult() :
        TLType(TLValue::MessagesStickerSetInstallResultSuccess)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesStickerSetInstallResult &v) const;

    QVector<TLStickerSetCovered> sets;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRecentMeUrl : public TLType
{
    TLRecentMeUrl() :
        TLType(TLValue::RecentMeUrlUnknown)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRecentMeUrl &v) const;

    QString url;
    quint32 userId = 0;
    quint32 chatId = 0;
    TLChatInvite chatInvite;
    TLStickerSetCovered set;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpRecentMeUrls : public TLType
{
    TLHelpRecentMeUrls() :
        TLType(TLValue::HelpRecentMeUrls)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpRecentMeUrls &v) const;

    QVector<TLRecentMeUrl> urls;
    QVector<TLChat> chats;
    QVector<TLUser> users;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessage : public TLType
{
    TLMessage() :
        TLType(TLValue::MessageEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessage &v) const;
    enum Flags {
        Out = 1 << 1,
        FwdFrom = 1 << 2,
        ReplyToMsgId = 1 << 3,
        Mentioned = 1 << 4,
        MediaUnread = 1 << 5,
        ReplyMarkup = 1 << 6,
        Entities = 1 << 7,
        FromId = 1 << 8,
        Media = 1 << 9,
        Views = 1 << 10,
        ViaBotId = 1 << 11,
        Silent = 1 << 13,
        Post = 1 << 14,
        EditDate = 1 << 15,
        PostAuthor = 1 << 16,
    };
    bool out() const { return flags & Out; }
    bool mentioned() const { return flags & Mentioned; }
    bool mediaUnread() const { return flags & MediaUnread; }
    bool silent() const { return flags & Silent; }
    bool post() const { return flags & Post; }

    quint32 id = 0;
    quint32 flags = 0;
    quint32 fromId = 0;
    TLPeer toId;
    TLMessageFwdHeader fwdFrom;
    quint32 viaBotId = 0;
    quint32 replyToMsgId = 0;
    quint32 date = 0;
    QString message;
    TLMessageMedia media;
    TLReplyMarkup replyMarkup;
    QVector<TLMessageEntity> entities;
    quint32 views = 0;
    quint32 editDate = 0;
    QString postAuthor;
    TLMessageAction action;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesDialogs : public TLType
{
    TLMessagesDialogs() :
        TLType(TLValue::MessagesDialogs)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesDialogs &v) const;

    QVector<TLDialog> dialogs;
    QVector<TLMessage> messages;
    QVector<TLChat> chats;
    QVector<TLUser> users;
    quint32 count = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesMessages : public TLType
{
    TLMessagesMessages() :
        TLType(TLValue::MessagesMessages)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesMessages &v) const;

    QVector<TLMessage> messages;
    QVector<TLChat> chats;
    QVector<TLUser> users;
    quint32 count = 0;
    quint32 flags = 0;
    quint32 pts = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesPeerDialogs : public TLType
{
    TLMessagesPeerDialogs() :
        TLType(TLValue::MessagesPeerDialogs)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesPeerDialogs &v) const;

    QVector<TLDialog> dialogs;
    QVector<TLMessage> messages;
    QVector<TLChat> chats;
    QVector<TLUser> users;
    TLUpdatesState state;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdate : public TLType
{
    TLUpdate() :
        TLType(TLValue::UpdateNewMessage)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdate &v) const;
    enum Flags {
        Info = 1 << 0,
        PeerOrderVector = 1 << 0,
        Pinned = 1 << 0,
        ByteArrayData = 1 << 0,
        Geo = 1 << 0,
        Masks = 1 << 0,
        Pts = 1 << 0,
        Popup = 1 << 0,
        ShippingOptionId = 1 << 1,
        GameShortName = 1 << 1,
        InputBotInlineMessageIDMsgId = 1 << 1,
        InboxDate = 1 << 1,
    };
    bool popup() const { return flags & Popup; }
    bool masks() const { return flags & Masks; }
    bool pinned() const { return flags & Pinned; }

    TLMessage message;
    quint32 pts = 0;
    quint32 ptsCount = 0;
    quint32 quint32Id = 0;
    quint64 randomId = 0;
    QVector<quint32> messages;
    quint32 userId = 0;
    TLSendMessageAction action;
    quint32 chatId = 0;
    TLChatParticipants participants;
    TLUserStatus status;
    QString firstName;
    QString lastName;
    QString username;
    quint32 date = 0;
    TLUserProfilePhoto photo;
    bool previous = false;
    TLContactLink myLink;
    TLContactLink foreignLink;
    TLEncryptedMessage encryptedMessage;
    quint32 qts = 0;
    TLEncryptedChat chat;
    quint32 maxDate = 0;
    quint32 inviterId = 0;
    quint32 version = 0;
    QVector<TLDcOption> dcOptions;
    bool blocked = false;
    TLNotifyPeer notifyPeer;
    TLPeerNotifySettings notifySettings;
    quint32 flags = 0;
    quint32 inboxDate = 0;
    QString type;
    QString stringMessage;
    TLMessageMedia media;
    QVector<TLMessageEntity> entities;
    TLPrivacyKey key;
    QVector<TLPrivacyRule> rules;
    QString phone;
    TLPeer peer;
    quint32 maxId = 0;
    TLWebPage webpage;
    quint32 channelId = 0;
    quint32 views = 0;
    bool enabled = false;
    bool isAdmin = false;
    TLMessagesStickerSet stickerset;
    QVector<quint64> quint64OrderVector;
    quint64 queryId = 0;
    QString query;
    TLGeoPoint geo;
    QString offset;
    QString stringId;
    TLInputBotInlineMessageID inputBotInlineMessageIDMsgId;
    quint32 msgId = 0;
    quint64 chatInstance = 0;
    QByteArray byteArrayData;
    QString gameShortName;
    TLDraftMessage draft;
    QVector<TLPeer> peerOrderVector;
    TLDataJSON jSONData;
    quint32 timeout = 0;
    QByteArray payload;
    TLPostAddress shippingAddress;
    TLPaymentRequestedInfo info;
    QString shippingOptionId;
    QString currency;
    quint64 totalAmount = 0;
    TLPhoneCall phoneCall;
    TLLangPackDifference difference;
    quint32 availableMinId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdates : public TLType
{
    TLUpdates() :
        TLType(TLValue::UpdatesTooLong)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdates &v) const;
    enum Flags {
        Out = 1 << 1,
        FwdFrom = 1 << 2,
        ReplyToMsgId = 1 << 3,
        Mentioned = 1 << 4,
        MediaUnread = 1 << 5,
        Entities = 1 << 7,
        Media = 1 << 9,
        ViaBotId = 1 << 11,
        Silent = 1 << 13,
    };
    bool out() const { return flags & Out; }
    bool mentioned() const { return flags & Mentioned; }
    bool mediaUnread() const { return flags & MediaUnread; }
    bool silent() const { return flags & Silent; }

    quint32 flags = 0;
    quint32 id = 0;
    quint32 userId = 0;
    QString message;
    quint32 pts = 0;
    quint32 ptsCount = 0;
    quint32 date = 0;
    TLMessageFwdHeader fwdFrom;
    quint32 viaBotId = 0;
    quint32 replyToMsgId = 0;
    QVector<TLMessageEntity> entities;
    quint32 fromId = 0;
    quint32 chatId = 0;
    TLUpdate update;
    QVector<TLUpdate> updates;
    QVector<TLUser> users;
    QVector<TLChat> chats;
    quint32 seqStart = 0;
    quint32 seq = 0;
    TLMessageMedia media;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdatesChannelDifference : public TLType
{
    TLUpdatesChannelDifference() :
        TLType(TLValue::UpdatesChannelDifferenceEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdatesChannelDifference &v) const;
    enum Flags {
        Final = 1 << 0,
        Timeout = 1 << 1,
    };
    bool final() const { return flags & Final; }

    quint32 flags = 0;
    quint32 pts = 0;
    quint32 timeout = 0;
    quint32 topMessage = 0;
    quint32 readInboxMaxId = 0;
    quint32 readOutboxMaxId = 0;
    quint32 unreadCount = 0;
    quint32 unreadMentionsCount = 0;
    QVector<TLMessage> messages;
    QVector<TLChat> chats;
    QVector<TLUser> users;
    QVector<TLMessage> newMessages;
    QVector<TLUpdate> otherUpdates;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdatesDifference : public TLType
{
    TLUpdatesDifference() :
        TLType(TLValue::UpdatesDifferenceEmpty)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdatesDifference &v) const;

    quint32 date = 0;
    quint32 seq = 0;
    QVector<TLMessage> newMessages;
    QVector<TLEncryptedMessage> newEncryptedMessages;
    QVector<TLUpdate> otherUpdates;
    QVector<TLChat> chats;
    QVector<TLUser> users;
    TLUpdatesState state;
    TLUpdatesState intermediateState;
    quint32 pts = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminLogEventAction : public TLType
{
    TLChannelAdminLogEventAction() :
        TLType(TLValue::ChannelAdminLogEventActionChangeTitle)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelAdminLogEventAction &v) const;

    QString prevValue;
    QString stringNewValue;
    TLChatPhoto prevPhoto;
    TLChatPhoto newPhoto;
    bool boolNewValue = false;
    TLMessage message;
    TLMessage prevMessage;
    TLMessage newMessage;
    TLChannelParticipant participant;
    TLChannelParticipant prevParticipant;
    TLChannelParticipant newParticipant;
    TLInputStickerSet prevStickerset;
    TLInputStickerSet newStickerset;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsPaymentResult : public TLType
{
    TLPaymentsPaymentResult() :
        TLType(TLValue::PaymentsPaymentResult)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsPaymentResult &v) const;

    TLUpdates updates;
    QString url;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminLogEvent : public TLType
{
    TLChannelAdminLogEvent() :
        TLType(TLValue::ChannelAdminLogEvent)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelAdminLogEvent &v) const;

    quint64 id = 0;
    quint32 date = 0;
    quint32 userId = 0;
    TLChannelAdminLogEventAction action;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelsAdminLogResults : public TLType
{
    TLChannelsAdminLogResults() :
        TLType(TLValue::ChannelsAdminLogResults)
    {
    }

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelsAdminLogResults &v) const;

    QVector<TLChannelAdminLogEvent> events;
    QVector<TLChat> chats;
    QVector<TLUser> users;
};
// End of generated TLTypes

Q_DECLARE_METATYPE(TLUploadFile)
Q_DECLARE_METATYPE(QVector<TLUser>)
Q_DECLARE_METATYPE(TLUpdates)

#endif // TLTYPES_HPP
