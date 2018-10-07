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

#include "TLValues.hpp"
#include "TLNumbers.hpp"
#include "UniqueLazyPointer.hpp"

#include <QMetaType>
#include <QVector>

template <typename TL>
using TLPtr = Telegram::UniqueLazyPointer<TL>;

template <typename T>
class TLVector : public QVector<T>
{
public:
    TLVector() : QVector<T>(), tlType(TLValue::Vector) { }
    explicit TLVector(int size) : QVector<T>(size), tlType(TLValue::Vector) { }
    TLVector(int size, const T &t) : QVector<T>(size, t), tlType(TLValue::Vector) { }
    TLVector(const TLVector<T> &v) : QVector<T>(v), tlType(v.tlType) { }
    TLVector(const QVector<T> &v) : QVector<T>(v), tlType(TLValue::Vector) { }
    TLVector(std::initializer_list<T> args) : QVector<T>(args), tlType(TLValue::Vector) { }

    template<typename T2>
    auto optionalIsValid(const T2 &obj) const -> decltype(obj.isValid())
    {
        return obj.isValid();
    }
    auto optionalIsValid(...) const -> bool
    {
        return true;
    }

    bool isValid() const {
        if (tlType != TLValue::Vector) {
            return false;
        }
        for (int i = 0; i < QVector<T>::size(); ++i) {
            if (!optionalIsValid(QVector<T>::at(i))) {
                return false;
            }
        }
        return true;
    }

    TLVector &operator=(const TLVector &v) {
        tlType = v.tlType;
        QVector<T>::operator =(v);
        return *this;
    }

    TLValue tlType;
};

// Generated TLTypes
struct TLAccountDaysTTL {
    constexpr TLAccountDaysTTL() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountDaysTTL:
            return true;
        default:
            return false;
        };
    }
    quint32 days = 0;
    TLValue tlType = TLValue::AccountDaysTTL;
};

struct TLAccountPassword {
    TLAccountPassword() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountNoPassword:
        case TLValue::AccountPassword:
            return true;
        default:
            return false;
        };
    }
    QByteArray newSalt;
    QString emailUnconfirmedPattern;
    QByteArray currentSalt;
    QString hint;
    bool hasRecovery = false;
    TLValue tlType = TLValue::AccountNoPassword;
};

struct TLAccountPasswordInputSettings {
    TLAccountPasswordInputSettings() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountPasswordInputSettings:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::AccountPasswordInputSettings;
};

struct TLAccountPasswordSettings {
    TLAccountPasswordSettings() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountPasswordSettings:
            return true;
        default:
            return false;
        };
    }
    QString email;
    TLValue tlType = TLValue::AccountPasswordSettings;
};

struct TLAccountTmpPassword {
    TLAccountTmpPassword() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountTmpPassword:
            return true;
        default:
            return false;
        };
    }
    QByteArray tmpPassword;
    quint32 validUntil = 0;
    TLValue tlType = TLValue::AccountTmpPassword;
};

struct TLAuthCheckedPhone {
    constexpr TLAuthCheckedPhone() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthCheckedPhone:
            return true;
        default:
            return false;
        };
    }
    bool phoneRegistered = false;
    TLValue tlType = TLValue::AuthCheckedPhone;
};

struct TLAuthCodeType {
    constexpr TLAuthCodeType() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthCodeTypeSms:
        case TLValue::AuthCodeTypeCall:
        case TLValue::AuthCodeTypeFlashCall:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::AuthCodeTypeSms;
};

struct TLAuthExportedAuthorization {
    TLAuthExportedAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthExportedAuthorization:
            return true;
        default:
            return false;
        };
    }
    quint32 id = 0;
    QByteArray bytes;
    TLValue tlType = TLValue::AuthExportedAuthorization;
};

struct TLAuthPasswordRecovery {
    TLAuthPasswordRecovery() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthPasswordRecovery:
            return true;
        default:
            return false;
        };
    }
    QString emailPattern;
    TLValue tlType = TLValue::AuthPasswordRecovery;
};

struct TLAuthSentCodeType {
    TLAuthSentCodeType() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthSentCodeTypeApp:
        case TLValue::AuthSentCodeTypeSms:
        case TLValue::AuthSentCodeTypeCall:
        case TLValue::AuthSentCodeTypeFlashCall:
            return true;
        default:
            return false;
        };
    }
    quint32 length = 0;
    QString pattern;
    TLValue tlType = TLValue::AuthSentCodeTypeApp;
};

struct TLAuthorization {
    TLAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Authorization:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::Authorization;
};

struct TLBadMsgNotification {
    constexpr TLBadMsgNotification() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::BadMsgNotification:
        case TLValue::BadServerSalt:
            return true;
        default:
            return false;
        };
    }
    quint64 badMsgId = 0;
    quint32 badMsgSeqno = 0;
    quint32 errorCode = 0;
    quint64 newServerSalt = 0;
    TLValue tlType = TLValue::BadMsgNotification;
};

struct TLBotCommand {
    TLBotCommand() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::BotCommand:
            return true;
        default:
            return false;
        };
    }
    QString command;
    QString description;
    TLValue tlType = TLValue::BotCommand;
};

struct TLBotInfo {
    TLBotInfo() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::BotInfo:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    QString description;
    TLVector<TLBotCommand> commands;
    TLValue tlType = TLValue::BotInfo;
};

struct TLCdnFileHash {
    TLCdnFileHash() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::CdnFileHash:
            return true;
        default:
            return false;
        };
    }
    quint32 offset = 0;
    quint32 limit = 0;
    QByteArray hash;
    TLValue tlType = TLValue::CdnFileHash;
};

struct TLCdnPublicKey {
    TLCdnPublicKey() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::CdnPublicKey:
            return true;
        default:
            return false;
        };
    }
    quint32 dcId = 0;
    QString publicKey;
    TLValue tlType = TLValue::CdnPublicKey;
};

struct TLChannelParticipantsFilter {
    TLChannelParticipantsFilter() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelParticipantsRecent:
        case TLValue::ChannelParticipantsAdmins:
        case TLValue::ChannelParticipantsKicked:
        case TLValue::ChannelParticipantsBots:
        case TLValue::ChannelParticipantsBanned:
        case TLValue::ChannelParticipantsSearch:
            return true;
        default:
            return false;
        };
    }
    QString q;
    TLValue tlType = TLValue::ChannelParticipantsRecent;
};

struct TLChatParticipant {
    constexpr TLChatParticipant() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatParticipant:
        case TLValue::ChatParticipantCreator:
        case TLValue::ChatParticipantAdmin:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    quint32 inviterId = 0;
    quint32 date = 0;
    TLValue tlType = TLValue::ChatParticipant;
};

struct TLChatParticipants {
    TLChatParticipants() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatParticipantsForbidden:
        case TLValue::ChatParticipants:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        SelfParticipant = 1 << 0,
    };
    quint32 flags = 0;
    quint32 chatId = 0;
    TLChatParticipant selfParticipant;
    TLVector<TLChatParticipant> participants;
    quint32 version = 0;
    TLValue tlType = TLValue::ChatParticipantsForbidden;
};

struct TLClientDHInnerData {
    TLClientDHInnerData() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ClientDHInnerData:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint64 retryId = 0;
    QString gB;
    TLValue tlType = TLValue::ClientDHInnerData;
};

struct TLContact {
    constexpr TLContact() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Contact:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    bool mutual = false;
    TLValue tlType = TLValue::Contact;
};

struct TLContactBlocked {
    constexpr TLContactBlocked() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactBlocked:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    quint32 date = 0;
    TLValue tlType = TLValue::ContactBlocked;
};

struct TLContactLink {
    constexpr TLContactLink() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactLinkUnknown:
        case TLValue::ContactLinkNone:
        case TLValue::ContactLinkHasPhone:
        case TLValue::ContactLinkContact:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::ContactLinkUnknown;
};

struct TLDataJSON {
    TLDataJSON() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DataJSON:
            return true;
        default:
            return false;
        };
    }
    QString data;
    TLValue tlType = TLValue::DataJSON;
};

struct TLDestroyAuthKeyRes {
    constexpr TLDestroyAuthKeyRes() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DestroyAuthKeyOk:
        case TLValue::DestroyAuthKeyNone:
        case TLValue::DestroyAuthKeyFail:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::DestroyAuthKeyOk;
};

struct TLDestroySessionRes {
    constexpr TLDestroySessionRes() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DestroySessionOk:
        case TLValue::DestroySessionNone:
            return true;
        default:
            return false;
        };
    }
    quint64 sessionId = 0;
    TLValue tlType = TLValue::DestroySessionOk;
};

struct TLDisabledFeature {
    TLDisabledFeature() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DisabledFeature:
            return true;
        default:
            return false;
        };
    }
    QString feature;
    QString description;
    TLValue tlType = TLValue::DisabledFeature;
};

struct TLEncryptedChat {
    TLEncryptedChat() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::EncryptedChatEmpty:
        case TLValue::EncryptedChatWaiting:
        case TLValue::EncryptedChatRequested:
        case TLValue::EncryptedChat:
        case TLValue::EncryptedChatDiscarded:
            return true;
        default:
            return false;
        };
    }
    quint32 id = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    quint32 adminId = 0;
    quint32 participantId = 0;
    QByteArray gA;
    QByteArray gAOrB;
    quint64 keyFingerprint = 0;
    TLValue tlType = TLValue::EncryptedChatEmpty;
};

struct TLEncryptedFile {
    constexpr TLEncryptedFile() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::EncryptedFileEmpty:
        case TLValue::EncryptedFile:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 size = 0;
    quint32 dcId = 0;
    quint32 keyFingerprint = 0;
    TLValue tlType = TLValue::EncryptedFileEmpty;
};

struct TLEncryptedMessage {
    TLEncryptedMessage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::EncryptedMessage:
        case TLValue::EncryptedMessageService:
            return true;
        default:
            return false;
        };
    }
    quint64 randomId = 0;
    quint32 chatId = 0;
    quint32 date = 0;
    QByteArray bytes;
    TLEncryptedFile file;
    TLValue tlType = TLValue::EncryptedMessage;
};

struct TLError {
    TLError() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Error:
            return true;
        default:
            return false;
        };
    }
    quint32 code = 0;
    QString text;
    TLValue tlType = TLValue::Error;
};

struct TLExportedChatInvite {
    TLExportedChatInvite() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatInviteEmpty:
        case TLValue::ChatInviteExported:
            return true;
        default:
            return false;
        };
    }
    QString link;
    TLValue tlType = TLValue::ChatInviteEmpty;
};

struct TLExportedMessageLink {
    TLExportedMessageLink() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ExportedMessageLink:
            return true;
        default:
            return false;
        };
    }
    QString link;
    TLValue tlType = TLValue::ExportedMessageLink;
};

struct TLFileLocation {
    constexpr TLFileLocation() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::FileLocationUnavailable:
        case TLValue::FileLocation:
            return true;
        default:
            return false;
        };
    }
    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    quint32 dcId = 0;
    TLValue tlType = TLValue::FileLocationUnavailable;
};

struct TLFutureSalt {
    constexpr TLFutureSalt() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::FutureSalt:
            return true;
        default:
            return false;
        };
    }
    quint32 validSince = 0;
    quint32 validUntil = 0;
    quint64 salt = 0;
    TLValue tlType = TLValue::FutureSalt;
};

struct TLFutureSalts {
    TLFutureSalts() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::FutureSalts:
            return true;
        default:
            return false;
        };
    }
    quint64 reqMsgId = 0;
    quint32 now = 0;
    TLVector<TLFutureSalt> salts;
    TLValue tlType = TLValue::FutureSalts;
};

struct TLGeoPoint {
    constexpr TLGeoPoint() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::GeoPointEmpty:
        case TLValue::GeoPoint:
            return true;
        default:
            return false;
        };
    }
    double longitude = 0;
    double latitude = 0;
    TLValue tlType = TLValue::GeoPointEmpty;
};

struct TLHelpAppUpdate {
    TLHelpAppUpdate() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HelpAppUpdate:
        case TLValue::HelpNoAppUpdate:
            return true;
        default:
            return false;
        };
    }
    quint32 id = 0;
    bool critical = false;
    QString url;
    QString text;
    TLValue tlType = TLValue::HelpAppUpdate;
};

struct TLHelpInviteText {
    TLHelpInviteText() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HelpInviteText:
            return true;
        default:
            return false;
        };
    }
    QString message;
    TLValue tlType = TLValue::HelpInviteText;
};

struct TLHelpTermsOfService {
    TLHelpTermsOfService() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HelpTermsOfService:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType = TLValue::HelpTermsOfService;
};

struct TLHighScore {
    constexpr TLHighScore() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HighScore:
            return true;
        default:
            return false;
        };
    }
    quint32 pos = 0;
    quint32 userId = 0;
    quint32 score = 0;
    TLValue tlType = TLValue::HighScore;
};

struct TLHttpWait {
    constexpr TLHttpWait() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HttpWait:
            return true;
        default:
            return false;
        };
    }
    quint32 maxDelay = 0;
    quint32 waitAfter = 0;
    quint32 maxWait = 0;
    TLValue tlType = TLValue::HttpWait;
};

struct TLImportedContact {
    constexpr TLImportedContact() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ImportedContact:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    quint64 clientId = 0;
    TLValue tlType = TLValue::ImportedContact;
};

struct TLInlineBotSwitchPM {
    TLInlineBotSwitchPM() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InlineBotSwitchPM:
            return true;
        default:
            return false;
        };
    }
    QString text;
    QString startParam;
    TLValue tlType = TLValue::InlineBotSwitchPM;
};

struct TLInputAppEvent {
    TLInputAppEvent() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputAppEvent:
            return true;
        default:
            return false;
        };
    }
    double time = 0;
    QString type;
    quint64 peer = 0;
    QString data;
    TLValue tlType = TLValue::InputAppEvent;
};

struct TLInputBotInlineMessageID {
    constexpr TLInputBotInlineMessageID() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputBotInlineMessageID:
            return true;
        default:
            return false;
        };
    }
    quint32 dcId = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputBotInlineMessageID;
};

struct TLInputChannel {
    constexpr TLInputChannel() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputChannelEmpty:
        case TLValue::InputChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 channelId = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputChannelEmpty;
};

struct TLInputContact {
    TLInputContact() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPhoneContact:
            return true;
        default:
            return false;
        };
    }
    quint64 clientId = 0;
    QString phone;
    QString firstName;
    QString lastName;
    TLValue tlType = TLValue::InputPhoneContact;
};

struct TLInputDocument {
    constexpr TLInputDocument() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputDocumentEmpty:
        case TLValue::InputDocument:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputDocumentEmpty;
};

struct TLInputEncryptedChat {
    constexpr TLInputEncryptedChat() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputEncryptedChat:
            return true;
        default:
            return false;
        };
    }
    quint32 chatId = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputEncryptedChat;
};

struct TLInputEncryptedFile {
    TLInputEncryptedFile() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputEncryptedFileEmpty:
        case TLValue::InputEncryptedFileUploaded:
        case TLValue::InputEncryptedFile:
        case TLValue::InputEncryptedFileBigUploaded:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint32 parts = 0;
    QString md5Checksum;
    quint32 keyFingerprint = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputEncryptedFileEmpty;
};

struct TLInputFile {
    TLInputFile() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputFile:
        case TLValue::InputFileBig:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint32 parts = 0;
    QString name;
    QString md5Checksum;
    TLValue tlType = TLValue::InputFile;
};

struct TLInputFileLocation {
    constexpr TLInputFileLocation() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputFileLocation:
        case TLValue::InputEncryptedFileLocation:
        case TLValue::InputDocumentFileLocation:
            return true;
        default:
            return false;
        };
    }
    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 version = 0;
    TLValue tlType = TLValue::InputFileLocation;
};

struct TLInputGeoPoint {
    constexpr TLInputGeoPoint() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputGeoPointEmpty:
        case TLValue::InputGeoPoint:
            return true;
        default:
            return false;
        };
    }
    double latitude = 0;
    double longitude = 0;
    TLValue tlType = TLValue::InputGeoPointEmpty;
};

struct TLInputPeer {
    constexpr TLInputPeer() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPeerEmpty:
        case TLValue::InputPeerSelf:
        case TLValue::InputPeerChat:
        case TLValue::InputPeerUser:
        case TLValue::InputPeerChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 chatId = 0;
    quint32 userId = 0;
    quint64 accessHash = 0;
    quint32 channelId = 0;
    TLValue tlType = TLValue::InputPeerEmpty;
};

struct TLInputPeerNotifyEvents {
    constexpr TLInputPeerNotifyEvents() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPeerNotifyEventsEmpty:
        case TLValue::InputPeerNotifyEventsAll:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::InputPeerNotifyEventsEmpty;
};

struct TLInputPhoneCall {
    constexpr TLInputPhoneCall() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPhoneCall:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputPhoneCall;
};

struct TLInputPhoto {
    constexpr TLInputPhoto() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPhotoEmpty:
        case TLValue::InputPhoto:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputPhotoEmpty;
};

struct TLInputPrivacyKey {
    constexpr TLInputPrivacyKey() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPrivacyKeyStatusTimestamp:
        case TLValue::InputPrivacyKeyChatInvite:
        case TLValue::InputPrivacyKeyPhoneCall:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::InputPrivacyKeyStatusTimestamp;
};

struct TLInputStickerSet {
    TLInputStickerSet() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputStickerSetEmpty:
        case TLValue::InputStickerSetID:
        case TLValue::InputStickerSetShortName:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    QString shortName;
    TLValue tlType = TLValue::InputStickerSetEmpty;
};

struct TLInputStickeredMedia {
    TLInputStickeredMedia() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputStickeredMediaPhoto:
        case TLValue::InputStickeredMediaDocument:
            return true;
        default:
            return false;
        };
    }
    TLInputPhoto inputPhotoId;
    TLInputDocument inputDocumentId;
    TLValue tlType = TLValue::InputStickeredMediaPhoto;
};

struct TLInputUser {
    constexpr TLInputUser() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputUserEmpty:
        case TLValue::InputUserSelf:
        case TLValue::InputUser:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputUserEmpty;
};

struct TLInputWebFileLocation {
    TLInputWebFileLocation() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputWebFileLocation:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputWebFileLocation;
};

struct TLIpPort {
    constexpr TLIpPort() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::IpPort:
            return true;
        default:
            return false;
        };
    }
    quint32 ipv4 = 0;
    quint32 port = 0;
    TLValue tlType = TLValue::IpPort;
};

struct TLLabeledPrice {
    TLLabeledPrice() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::LabeledPrice:
            return true;
        default:
            return false;
        };
    }
    QString label;
    quint64 amount = 0;
    TLValue tlType = TLValue::LabeledPrice;
};

struct TLLangPackLanguage {
    TLLangPackLanguage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::LangPackLanguage:
            return true;
        default:
            return false;
        };
    }
    QString name;
    QString nativeName;
    QString langCode;
    TLValue tlType = TLValue::LangPackLanguage;
};

struct TLLangPackString {
    TLLangPackString() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::LangPackString:
        case TLValue::LangPackStringPluralized:
        case TLValue::LangPackStringDeleted:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::LangPackString;
};

struct TLMaskCoords {
    constexpr TLMaskCoords() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MaskCoords:
            return true;
        default:
            return false;
        };
    }
    quint32 n = 0;
    double x = 0;
    double y = 0;
    double zoom = 0;
    TLValue tlType = TLValue::MaskCoords;
};

struct TLMessageEntity {
    TLMessageEntity() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessageEntityUnknown:
        case TLValue::MessageEntityMention:
        case TLValue::MessageEntityHashtag:
        case TLValue::MessageEntityBotCommand:
        case TLValue::MessageEntityUrl:
        case TLValue::MessageEntityEmail:
        case TLValue::MessageEntityBold:
        case TLValue::MessageEntityItalic:
        case TLValue::MessageEntityCode:
        case TLValue::MessageEntityPre:
        case TLValue::MessageEntityTextUrl:
        case TLValue::MessageEntityMentionName:
        case TLValue::InputMessageEntityMentionName:
            return true;
        default:
            return false;
        };
    }
    quint32 offset = 0;
    quint32 length = 0;
    QString language;
    QString url;
    quint32 quint32UserId = 0;
    TLInputUser inputUserUserId;
    TLValue tlType = TLValue::MessageEntityUnknown;
};

struct TLMessageFwdHeader {
    TLMessageFwdHeader() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessageFwdHeader:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::MessageFwdHeader;
};

struct TLMessageRange {
    constexpr TLMessageRange() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessageRange:
            return true;
        default:
            return false;
        };
    }
    quint32 minId = 0;
    quint32 maxId = 0;
    TLValue tlType = TLValue::MessageRange;
};

struct TLMessagesAffectedHistory {
    constexpr TLMessagesAffectedHistory() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesAffectedHistory:
            return true;
        default:
            return false;
        };
    }
    quint32 pts = 0;
    quint32 ptsCount = 0;
    quint32 offset = 0;
    TLValue tlType = TLValue::MessagesAffectedHistory;
};

struct TLMessagesAffectedMessages {
    constexpr TLMessagesAffectedMessages() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesAffectedMessages:
            return true;
        default:
            return false;
        };
    }
    quint32 pts = 0;
    quint32 ptsCount = 0;
    TLValue tlType = TLValue::MessagesAffectedMessages;
};

struct TLMessagesDhConfig {
    TLMessagesDhConfig() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesDhConfigNotModified:
        case TLValue::MessagesDhConfig:
            return true;
        default:
            return false;
        };
    }
    QByteArray random;
    quint32 g = 0;
    QByteArray p;
    quint32 version = 0;
    TLValue tlType = TLValue::MessagesDhConfigNotModified;
};

struct TLMessagesSentEncryptedMessage {
    TLMessagesSentEncryptedMessage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesSentEncryptedMessage:
        case TLValue::MessagesSentEncryptedFile:
            return true;
        default:
            return false;
        };
    }
    quint32 date = 0;
    TLEncryptedFile file;
    TLValue tlType = TLValue::MessagesSentEncryptedMessage;
};

struct TLMsgDetailedInfo {
    constexpr TLMsgDetailedInfo() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MsgDetailedInfo:
        case TLValue::MsgNewDetailedInfo:
            return true;
        default:
            return false;
        };
    }
    quint64 msgId = 0;
    quint64 answerMsgId = 0;
    quint32 bytes = 0;
    quint32 status = 0;
    TLValue tlType = TLValue::MsgDetailedInfo;
};

struct TLMsgResendReq {
    TLMsgResendReq() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MsgResendReq:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    TLValue tlType = TLValue::MsgResendReq;
};

struct TLMsgsAck {
    TLMsgsAck() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MsgsAck:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    TLValue tlType = TLValue::MsgsAck;
};

struct TLMsgsAllInfo {
    TLMsgsAllInfo() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MsgsAllInfo:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    QString info;
    TLValue tlType = TLValue::MsgsAllInfo;
};

struct TLMsgsStateInfo {
    TLMsgsStateInfo() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MsgsStateInfo:
            return true;
        default:
            return false;
        };
    }
    quint64 reqMsgId = 0;
    QString info;
    TLValue tlType = TLValue::MsgsStateInfo;
};

struct TLMsgsStateReq {
    TLMsgsStateReq() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MsgsStateReq:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    TLValue tlType = TLValue::MsgsStateReq;
};

struct TLNearestDc {
    TLNearestDc() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::NearestDc:
            return true;
        default:
            return false;
        };
    }
    QString country;
    quint32 thisDc = 0;
    quint32 nearestDc = 0;
    TLValue tlType = TLValue::NearestDc;
};

struct TLNewSession {
    constexpr TLNewSession() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::NewSessionCreated:
            return true;
        default:
            return false;
        };
    }
    quint64 firstMsgId = 0;
    quint64 uniqueId = 0;
    quint64 serverSalt = 0;
    TLValue tlType = TLValue::NewSessionCreated;
};

struct TLPQInnerData {
    TLPQInnerData() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PQInnerData:
            return true;
        default:
            return false;
        };
    }
    QString pq;
    QString p;
    QString q;
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber256 newNonce;
    TLValue tlType = TLValue::PQInnerData;
};

struct TLPaymentCharge {
    TLPaymentCharge() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentCharge:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString providerChargeId;
    TLValue tlType = TLValue::PaymentCharge;
};

struct TLPaymentSavedCredentials {
    TLPaymentSavedCredentials() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentSavedCredentialsCard:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString title;
    TLValue tlType = TLValue::PaymentSavedCredentialsCard;
};

struct TLPeer {
    constexpr TLPeer() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PeerUser:
        case TLValue::PeerChat:
        case TLValue::PeerChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    quint32 chatId = 0;
    quint32 channelId = 0;
    TLValue tlType = TLValue::PeerUser;
};

struct TLPeerNotifyEvents {
    constexpr TLPeerNotifyEvents() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PeerNotifyEventsEmpty:
        case TLValue::PeerNotifyEventsAll:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::PeerNotifyEventsEmpty;
};

struct TLPhoneCallDiscardReason {
    constexpr TLPhoneCallDiscardReason() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhoneCallDiscardReasonMissed:
        case TLValue::PhoneCallDiscardReasonDisconnect:
        case TLValue::PhoneCallDiscardReasonHangup:
        case TLValue::PhoneCallDiscardReasonBusy:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::PhoneCallDiscardReasonMissed;
};

struct TLPhoneConnection {
    TLPhoneConnection() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhoneConnection:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    QString ip;
    QString ipv6;
    quint32 port = 0;
    QByteArray peerTag;
    TLValue tlType = TLValue::PhoneConnection;
};

struct TLPhotoSize {
    TLPhotoSize() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhotoSizeEmpty:
        case TLValue::PhotoSize:
        case TLValue::PhotoCachedSize:
            return true;
        default:
            return false;
        };
    }
    QString type;
    TLFileLocation location;
    quint32 w = 0;
    quint32 h = 0;
    quint32 size = 0;
    QByteArray bytes;
    TLValue tlType = TLValue::PhotoSizeEmpty;
};

struct TLPong {
    constexpr TLPong() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Pong:
            return true;
        default:
            return false;
        };
    }
    quint64 msgId = 0;
    quint64 pingId = 0;
    TLValue tlType = TLValue::Pong;
};

struct TLPopularContact {
    constexpr TLPopularContact() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PopularContact:
            return true;
        default:
            return false;
        };
    }
    quint64 clientId = 0;
    quint32 importers = 0;
    TLValue tlType = TLValue::PopularContact;
};

struct TLPostAddress {
    TLPostAddress() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PostAddress:
            return true;
        default:
            return false;
        };
    }
    QString streetLine1;
    QString streetLine2;
    QString city;
    QString state;
    QString countryIso2;
    QString postCode;
    TLValue tlType = TLValue::PostAddress;
};

struct TLPrivacyKey {
    constexpr TLPrivacyKey() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PrivacyKeyStatusTimestamp:
        case TLValue::PrivacyKeyChatInvite:
        case TLValue::PrivacyKeyPhoneCall:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::PrivacyKeyStatusTimestamp;
};

struct TLPrivacyRule {
    TLPrivacyRule() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PrivacyValueAllowContacts:
        case TLValue::PrivacyValueAllowAll:
        case TLValue::PrivacyValueAllowUsers:
        case TLValue::PrivacyValueDisallowContacts:
        case TLValue::PrivacyValueDisallowAll:
        case TLValue::PrivacyValueDisallowUsers:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint32> users;
    TLValue tlType = TLValue::PrivacyValueAllowContacts;
};

struct TLReceivedNotifyMessage {
    constexpr TLReceivedNotifyMessage() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ReceivedNotifyMessage:
            return true;
        default:
            return false;
        };
    }
    quint32 id = 0;
    quint32 flags = 0;
    TLValue tlType = TLValue::ReceivedNotifyMessage;
};

struct TLReportReason {
    TLReportReason() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputReportReasonSpam:
        case TLValue::InputReportReasonViolence:
        case TLValue::InputReportReasonPornography:
        case TLValue::InputReportReasonOther:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType = TLValue::InputReportReasonSpam;
};

struct TLResPQ {
    TLResPQ() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ResPQ:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    QString pq;
    TLVector<quint64> serverPublicKeyFingerprints;
    TLValue tlType = TLValue::ResPQ;
};

struct TLRichText;
using TLRichTextPtr = TLPtr<TLRichText>;

struct TLRichText {
    TLRichText() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::TextEmpty:
        case TLValue::TextPlain:
        case TLValue::TextBold:
        case TLValue::TextItalic:
        case TLValue::TextUnderline:
        case TLValue::TextStrike:
        case TLValue::TextFixed:
        case TLValue::TextUrl:
        case TLValue::TextEmail:
        case TLValue::TextConcat:
            return true;
        default:
            return false;
        };
    }
    QString stringText;
    TLRichTextPtr richText;
    QString url;
    quint64 webpageId = 0;
    QString email;
    TLVector<TLRichText*> texts;
    TLValue tlType = TLValue::TextEmpty;
};

struct TLRpcDropAnswer {
    constexpr TLRpcDropAnswer() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::RpcAnswerUnknown:
        case TLValue::RpcAnswerDroppedRunning:
        case TLValue::RpcAnswerDropped:
            return true;
        default:
            return false;
        };
    }
    quint64 msgId = 0;
    quint32 seqNo = 0;
    quint32 bytes = 0;
    TLValue tlType = TLValue::RpcAnswerUnknown;
};

struct TLRpcError {
    TLRpcError() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::RpcError:
            return true;
        default:
            return false;
        };
    }
    quint32 errorCode = 0;
    QString errorMessage;
    TLValue tlType = TLValue::RpcError;
};

struct TLSendMessageAction {
    constexpr TLSendMessageAction() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::SendMessageTypingAction:
        case TLValue::SendMessageCancelAction:
        case TLValue::SendMessageRecordVideoAction:
        case TLValue::SendMessageUploadVideoAction:
        case TLValue::SendMessageRecordAudioAction:
        case TLValue::SendMessageUploadAudioAction:
        case TLValue::SendMessageUploadPhotoAction:
        case TLValue::SendMessageUploadDocumentAction:
        case TLValue::SendMessageGeoLocationAction:
        case TLValue::SendMessageChooseContactAction:
        case TLValue::SendMessageGamePlayAction:
        case TLValue::SendMessageRecordRoundAction:
        case TLValue::SendMessageUploadRoundAction:
            return true;
        default:
            return false;
        };
    }
    quint32 progress = 0;
    TLValue tlType = TLValue::SendMessageTypingAction;
};

struct TLServerDHInnerData {
    TLServerDHInnerData() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ServerDHInnerData:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint32 g = 0;
    QString dhPrime;
    QString gA;
    quint32 serverTime = 0;
    TLValue tlType = TLValue::ServerDHInnerData;
};

struct TLServerDHParams {
    TLServerDHParams() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ServerDHParamsFail:
        case TLValue::ServerDHParamsOk:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber128 newNonceHash;
    QString encryptedAnswer;
    TLValue tlType = TLValue::ServerDHParamsFail;
};

struct TLSetClientDHParamsAnswer {
    TLSetClientDHParamsAnswer() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DhGenOk:
        case TLValue::DhGenRetry:
        case TLValue::DhGenFail:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber128 newNonceHash1;
    TLNumber128 newNonceHash2;
    TLNumber128 newNonceHash3;
    TLValue tlType = TLValue::DhGenOk;
};

struct TLShippingOption {
    TLShippingOption() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ShippingOption:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString title;
    TLVector<TLLabeledPrice> prices;
    TLValue tlType = TLValue::ShippingOption;
};

struct TLStickerPack {
    TLStickerPack() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::StickerPack:
            return true;
        default:
            return false;
        };
    }
    QString emoticon;
    TLVector<quint64> documents;
    TLValue tlType = TLValue::StickerPack;
};

struct TLStorageFileType {
    constexpr TLStorageFileType() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::StorageFileUnknown:
        case TLValue::StorageFilePartial:
        case TLValue::StorageFileJpeg:
        case TLValue::StorageFileGif:
        case TLValue::StorageFilePng:
        case TLValue::StorageFilePdf:
        case TLValue::StorageFileMp3:
        case TLValue::StorageFileMov:
        case TLValue::StorageFileMp4:
        case TLValue::StorageFileWebp:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::StorageFileUnknown;
};

struct TLTopPeer {
    TLTopPeer() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::TopPeer:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    double rating = 0;
    TLValue tlType = TLValue::TopPeer;
};

struct TLTopPeerCategory {
    constexpr TLTopPeerCategory() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::TopPeerCategoryBotsPM:
        case TLValue::TopPeerCategoryBotsInline:
        case TLValue::TopPeerCategoryCorrespondents:
        case TLValue::TopPeerCategoryGroups:
        case TLValue::TopPeerCategoryChannels:
        case TLValue::TopPeerCategoryPhoneCalls:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType = TLValue::TopPeerCategoryBotsPM;
};

struct TLTopPeerCategoryPeers {
    TLTopPeerCategoryPeers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::TopPeerCategoryPeers:
            return true;
        default:
            return false;
        };
    }
    TLTopPeerCategory category;
    quint32 count = 0;
    TLVector<TLTopPeer> peers;
    TLValue tlType = TLValue::TopPeerCategoryPeers;
};

struct TLUpdatesState {
    constexpr TLUpdatesState() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UpdatesState:
            return true;
        default:
            return false;
        };
    }
    quint32 pts = 0;
    quint32 qts = 0;
    quint32 date = 0;
    quint32 seq = 0;
    quint32 unreadCount = 0;
    TLValue tlType = TLValue::UpdatesState;
};

struct TLUploadCdnFile {
    TLUploadCdnFile() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UploadCdnFileReuploadNeeded:
        case TLValue::UploadCdnFile:
            return true;
        default:
            return false;
        };
    }
    QByteArray requestToken;
    QByteArray bytes;
    TLValue tlType = TLValue::UploadCdnFileReuploadNeeded;
};

struct TLUploadFile {
    TLUploadFile() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UploadFile:
        case TLValue::UploadFileCdnRedirect:
            return true;
        default:
            return false;
        };
    }
    TLStorageFileType type;
    quint32 mtime = 0;
    QByteArray bytes;
    quint32 dcId = 0;
    QByteArray fileToken;
    QByteArray encryptionKey;
    QByteArray encryptionIv;
    TLVector<TLCdnFileHash> cdnFileHashes;
    TLValue tlType = TLValue::UploadFile;
};

struct TLUploadWebFile {
    TLUploadWebFile() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UploadWebFile:
            return true;
        default:
            return false;
        };
    }
    quint32 size = 0;
    QString mimeType;
    TLStorageFileType fileType;
    quint32 mtime = 0;
    QByteArray bytes;
    TLValue tlType = TLValue::UploadWebFile;
};

struct TLUserProfilePhoto {
    TLUserProfilePhoto() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UserProfilePhotoEmpty:
        case TLValue::UserProfilePhoto:
            return true;
        default:
            return false;
        };
    }
    quint64 photoId = 0;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType = TLValue::UserProfilePhotoEmpty;
};

struct TLUserStatus {
    constexpr TLUserStatus() = default;

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UserStatusEmpty:
        case TLValue::UserStatusOnline:
        case TLValue::UserStatusOffline:
        case TLValue::UserStatusRecently:
        case TLValue::UserStatusLastWeek:
        case TLValue::UserStatusLastMonth:
            return true;
        default:
            return false;
        };
    }
    quint32 expires = 0;
    quint32 wasOnline = 0;
    TLValue tlType = TLValue::UserStatusEmpty;
};

struct TLWallPaper {
    TLWallPaper() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::WallPaper:
        case TLValue::WallPaperSolid:
            return true;
        default:
            return false;
        };
    }
    quint32 id = 0;
    QString title;
    TLVector<TLPhotoSize> sizes;
    quint32 color = 0;
    quint32 bgColor = 0;
    TLValue tlType = TLValue::WallPaper;
};

struct TLAccountAuthorizations {
    TLAccountAuthorizations() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountAuthorizations:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLAuthorization> authorizations;
    TLValue tlType = TLValue::AccountAuthorizations;
};

struct TLAuthSentCode {
    TLAuthSentCode() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthSentCode:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::AuthSentCode;
};

struct TLCdnConfig {
    TLCdnConfig() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::CdnConfig:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLCdnPublicKey> publicKeys;
    TLValue tlType = TLValue::CdnConfig;
};

struct TLChannelAdminLogEventsFilter {
    TLChannelAdminLogEventsFilter() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelAdminLogEventsFilter:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::ChannelAdminLogEventsFilter;
};

struct TLChannelAdminRights {
    TLChannelAdminRights() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelAdminRights:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::ChannelAdminRights;
};

struct TLChannelBannedRights {
    TLChannelBannedRights() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelBannedRights:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::ChannelBannedRights;
};

struct TLChannelMessagesFilter {
    TLChannelMessagesFilter() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelMessagesFilterEmpty:
        case TLValue::ChannelMessagesFilter:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        ExcludeNewMessages = 1 << 1,
    };
    bool excludeNewMessages() const { return flags & ExcludeNewMessages; }
    quint32 flags = 0;
    TLVector<TLMessageRange> ranges;
    TLValue tlType = TLValue::ChannelMessagesFilterEmpty;
};

struct TLChannelParticipant {
    TLChannelParticipant() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelParticipant:
        case TLValue::ChannelParticipantSelf:
        case TLValue::ChannelParticipantCreator:
        case TLValue::ChannelParticipantAdmin:
        case TLValue::ChannelParticipantBanned:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::ChannelParticipant;
};

struct TLChatPhoto {
    TLChatPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatPhotoEmpty:
        case TLValue::ChatPhoto:
            return true;
        default:
            return false;
        };
    }
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType = TLValue::ChatPhotoEmpty;
};

struct TLContactStatus {
    TLContactStatus() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactStatus:
            return true;
        default:
            return false;
        };
    }
    quint32 userId = 0;
    TLUserStatus status;
    TLValue tlType = TLValue::ContactStatus;
};

struct TLDcOption {
    TLDcOption() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DcOption:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::DcOption;
};

struct TLDocumentAttribute {
    TLDocumentAttribute() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DocumentAttributeImageSize:
        case TLValue::DocumentAttributeAnimated:
        case TLValue::DocumentAttributeSticker:
        case TLValue::DocumentAttributeVideo:
        case TLValue::DocumentAttributeAudio:
        case TLValue::DocumentAttributeFilename:
        case TLValue::DocumentAttributeHasStickers:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::DocumentAttributeImageSize;
};

struct TLDraftMessage {
    TLDraftMessage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DraftMessageEmpty:
        case TLValue::DraftMessage:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        ReplyToMsgId = 1 << 0,
        NoWebpage = 1 << 1,
        Entities = 1 << 3,
    };
    bool noWebpage() const { return flags & NoWebpage; }
    quint32 flags = 0;
    quint32 replyToMsgId = 0;
    QString message;
    TLVector<TLMessageEntity> entities;
    quint32 date = 0;
    TLValue tlType = TLValue::DraftMessageEmpty;
};

struct TLHelpConfigSimple {
    TLHelpConfigSimple() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HelpConfigSimple:
            return true;
        default:
            return false;
        };
    }
    quint32 date = 0;
    quint32 expires = 0;
    quint32 dcId = 0;
    TLVector<TLIpPort> ipPortList;
    TLValue tlType = TLValue::HelpConfigSimple;
};

struct TLInputChatPhoto {
    TLInputChatPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputChatPhotoEmpty:
        case TLValue::InputChatUploadedPhoto:
        case TLValue::InputChatPhoto:
            return true;
        default:
            return false;
        };
    }
    TLInputFile file;
    TLInputPhoto id;
    TLValue tlType = TLValue::InputChatPhotoEmpty;
};

struct TLInputGame {
    TLInputGame() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputGameID:
        case TLValue::InputGameShortName:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    TLInputUser botId;
    QString shortName;
    TLValue tlType = TLValue::InputGameID;
};

struct TLInputNotifyPeer {
    TLInputNotifyPeer() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputNotifyPeer:
        case TLValue::InputNotifyUsers:
        case TLValue::InputNotifyChats:
        case TLValue::InputNotifyAll:
            return true;
        default:
            return false;
        };
    }
    TLInputPeer peer;
    TLValue tlType = TLValue::InputNotifyPeer;
};

struct TLInputPaymentCredentials {
    TLInputPaymentCredentials() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPaymentCredentialsSaved:
        case TLValue::InputPaymentCredentials:
        case TLValue::InputPaymentCredentialsApplePay:
        case TLValue::InputPaymentCredentialsAndroidPay:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::InputPaymentCredentialsSaved;
};

struct TLInputPeerNotifySettings {
    TLInputPeerNotifySettings() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPeerNotifySettings:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
    };
    bool showPreviews() const { return flags & ShowPreviews; }
    bool silent() const { return flags & Silent; }
    quint32 flags = 0;
    quint32 muteUntil = 0;
    QString sound;
    TLValue tlType = TLValue::InputPeerNotifySettings;
};

struct TLInputPrivacyRule {
    TLInputPrivacyRule() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputPrivacyValueAllowContacts:
        case TLValue::InputPrivacyValueAllowAll:
        case TLValue::InputPrivacyValueAllowUsers:
        case TLValue::InputPrivacyValueDisallowContacts:
        case TLValue::InputPrivacyValueDisallowAll:
        case TLValue::InputPrivacyValueDisallowUsers:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLInputUser> users;
    TLValue tlType = TLValue::InputPrivacyValueAllowContacts;
};

struct TLInputStickerSetItem {
    TLInputStickerSetItem() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputStickerSetItem:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        MaskCoords = 1 << 0,
    };
    quint32 flags = 0;
    TLInputDocument document;
    QString emoji;
    TLMaskCoords maskCoords;
    TLValue tlType = TLValue::InputStickerSetItem;
};

struct TLInputWebDocument {
    TLInputWebDocument() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputWebDocument:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint32 size = 0;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType = TLValue::InputWebDocument;
};

struct TLInvoice {
    TLInvoice() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Invoice:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLLabeledPrice> prices;
    TLValue tlType = TLValue::Invoice;
};

struct TLKeyboardButton {
    TLKeyboardButton() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::KeyboardButton:
        case TLValue::KeyboardButtonUrl:
        case TLValue::KeyboardButtonCallback:
        case TLValue::KeyboardButtonRequestPhone:
        case TLValue::KeyboardButtonRequestGeoLocation:
        case TLValue::KeyboardButtonSwitchInline:
        case TLValue::KeyboardButtonGame:
        case TLValue::KeyboardButtonBuy:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        SamePeer = 1 << 0,
    };
    bool samePeer() const { return flags & SamePeer; }
    QString text;
    QString url;
    QByteArray data;
    quint32 flags = 0;
    QString query;
    TLValue tlType = TLValue::KeyboardButton;
};

struct TLKeyboardButtonRow {
    TLKeyboardButtonRow() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::KeyboardButtonRow:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLKeyboardButton> buttons;
    TLValue tlType = TLValue::KeyboardButtonRow;
};

struct TLLangPackDifference {
    TLLangPackDifference() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::LangPackDifference:
            return true;
        default:
            return false;
        };
    }
    QString langCode;
    quint32 fromVersion = 0;
    quint32 version = 0;
    TLVector<TLLangPackString> strings;
    TLValue tlType = TLValue::LangPackDifference;
};

struct TLMessagesBotCallbackAnswer {
    TLMessagesBotCallbackAnswer() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesBotCallbackAnswer:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::MessagesBotCallbackAnswer;
};

struct TLMessagesFilter {
    TLMessagesFilter() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputMessagesFilterEmpty:
        case TLValue::InputMessagesFilterPhotos:
        case TLValue::InputMessagesFilterVideo:
        case TLValue::InputMessagesFilterPhotoVideo:
        case TLValue::InputMessagesFilterDocument:
        case TLValue::InputMessagesFilterUrl:
        case TLValue::InputMessagesFilterGif:
        case TLValue::InputMessagesFilterVoice:
        case TLValue::InputMessagesFilterMusic:
        case TLValue::InputMessagesFilterChatPhotos:
        case TLValue::InputMessagesFilterPhoneCalls:
        case TLValue::InputMessagesFilterRoundVoice:
        case TLValue::InputMessagesFilterRoundVideo:
        case TLValue::InputMessagesFilterMyMentions:
        case TLValue::InputMessagesFilterGeo:
        case TLValue::InputMessagesFilterContacts:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Missed = 1 << 0,
    };
    bool missed() const { return flags & Missed; }
    quint32 flags = 0;
    TLValue tlType = TLValue::InputMessagesFilterEmpty;
};

struct TLMessagesMessageEditData {
    TLMessagesMessageEditData() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesMessageEditData:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Caption = 1 << 0,
    };
    bool caption() const { return flags & Caption; }
    quint32 flags = 0;
    TLValue tlType = TLValue::MessagesMessageEditData;
};

struct TLNotifyPeer {
    TLNotifyPeer() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::NotifyPeer:
        case TLValue::NotifyUsers:
        case TLValue::NotifyChats:
        case TLValue::NotifyAll:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    TLValue tlType = TLValue::NotifyPeer;
};

struct TLPaymentRequestedInfo {
    TLPaymentRequestedInfo() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentRequestedInfo:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::PaymentRequestedInfo;
};

struct TLPaymentsSavedInfo {
    TLPaymentsSavedInfo() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentsSavedInfo:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        SavedInfo = 1 << 0,
        HasSavedCredentials = 1 << 1,
    };
    bool hasSavedCredentials() const { return flags & HasSavedCredentials; }
    quint32 flags = 0;
    TLPaymentRequestedInfo savedInfo;
    TLValue tlType = TLValue::PaymentsSavedInfo;
};

struct TLPaymentsValidatedRequestedInfo {
    TLPaymentsValidatedRequestedInfo() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentsValidatedRequestedInfo:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Id = 1 << 0,
        ShippingOptions = 1 << 1,
    };
    quint32 flags = 0;
    QString id;
    TLVector<TLShippingOption> shippingOptions;
    TLValue tlType = TLValue::PaymentsValidatedRequestedInfo;
};

struct TLPeerNotifySettings {
    TLPeerNotifySettings() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PeerNotifySettingsEmpty:
        case TLValue::PeerNotifySettings:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
    };
    bool showPreviews() const { return flags & ShowPreviews; }
    bool silent() const { return flags & Silent; }
    quint32 flags = 0;
    quint32 muteUntil = 0;
    QString sound;
    TLValue tlType = TLValue::PeerNotifySettingsEmpty;
};

struct TLPeerSettings {
    TLPeerSettings() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PeerSettings:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        ReportSpam = 1 << 0,
    };
    bool reportSpam() const { return flags & ReportSpam; }
    quint32 flags = 0;
    TLValue tlType = TLValue::PeerSettings;
};

struct TLPhoneCallProtocol {
    TLPhoneCallProtocol() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhoneCallProtocol:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        UdpP2p = 1 << 0,
        UdpReflector = 1 << 1,
    };
    bool udpP2p() const { return flags & UdpP2p; }
    bool udpReflector() const { return flags & UdpReflector; }
    quint32 flags = 0;
    quint32 minLayer = 0;
    quint32 maxLayer = 0;
    TLValue tlType = TLValue::PhoneCallProtocol;
};

struct TLPhoto {
    TLPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhotoEmpty:
        case TLValue::Photo:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        HasStickers = 1 << 0,
    };
    bool hasStickers() const { return flags & HasStickers; }
    quint64 id = 0;
    quint32 flags = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    TLVector<TLPhotoSize> sizes;
    TLValue tlType = TLValue::PhotoEmpty;
};

struct TLReplyMarkup {
    TLReplyMarkup() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ReplyKeyboardHide:
        case TLValue::ReplyKeyboardForceReply:
        case TLValue::ReplyKeyboardMarkup:
        case TLValue::ReplyInlineMarkup:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Resize = 1 << 0,
        SingleUse = 1 << 1,
        Selective = 1 << 2,
    };
    bool selective() const { return flags & Selective; }
    bool singleUse() const { return flags & SingleUse; }
    bool resize() const { return flags & Resize; }
    quint32 flags = 0;
    TLVector<TLKeyboardButtonRow> rows;
    TLValue tlType = TLValue::ReplyKeyboardHide;
};

struct TLStickerSet {
    TLStickerSet() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::StickerSet:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::StickerSet;
};

struct TLUser {
    TLUser() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UserEmpty:
        case TLValue::User:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::UserEmpty;
};

struct TLWebDocument {
    TLWebDocument() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::WebDocument:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint64 accessHash = 0;
    quint32 size = 0;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
    quint32 dcId = 0;
    TLValue tlType = TLValue::WebDocument;
};

struct TLAccountPrivacyRules {
    TLAccountPrivacyRules() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AccountPrivacyRules:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPrivacyRule> rules;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::AccountPrivacyRules;
};

struct TLAuthAuthorization {
    TLAuthAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::AuthAuthorization:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        TmpSessions = 1 << 0,
    };
    quint32 flags = 0;
    quint32 tmpSessions = 0;
    TLUser user;
    TLValue tlType = TLValue::AuthAuthorization;
};

struct TLBotInlineMessage {
    TLBotInlineMessage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::BotInlineMessageMediaAuto:
        case TLValue::BotInlineMessageText:
        case TLValue::BotInlineMessageMediaGeo:
        case TLValue::BotInlineMessageMediaVenue:
        case TLValue::BotInlineMessageMediaContact:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLMessageEntity> entities;
    TLGeoPoint geo;
    quint32 period = 0;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    TLValue tlType = TLValue::BotInlineMessageMediaAuto;
};

struct TLChannelsChannelParticipant {
    TLChannelsChannelParticipant() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelsChannelParticipant:
            return true;
        default:
            return false;
        };
    }
    TLChannelParticipant participant;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ChannelsChannelParticipant;
};

struct TLChannelsChannelParticipants {
    TLChannelsChannelParticipants() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelsChannelParticipants:
        case TLValue::ChannelsChannelParticipantsNotModified:
            return true;
        default:
            return false;
        };
    }
    quint32 count = 0;
    TLVector<TLChannelParticipant> participants;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ChannelsChannelParticipants;
};

struct TLChat {
    TLChat() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatEmpty:
        case TLValue::Chat:
        case TLValue::ChatForbidden:
        case TLValue::Channel:
        case TLValue::ChannelForbidden:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::ChatEmpty;
};

struct TLChatFull {
    TLChatFull() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatFull:
        case TLValue::ChannelFull:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLBotInfo> botInfo;
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
    TLValue tlType = TLValue::ChatFull;
};

struct TLChatInvite {
    TLChatInvite() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChatInviteAlready:
        case TLValue::ChatInvite:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLUser> participants;
    TLValue tlType = TLValue::ChatInviteAlready;
};

struct TLConfig {
    TLConfig() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Config:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLDcOption> dcOptions;
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
    TLVector<TLDisabledFeature> disabledFeatures;
    TLValue tlType = TLValue::Config;
};

struct TLContactsBlocked {
    TLContactsBlocked() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsBlocked:
        case TLValue::ContactsBlockedSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContactBlocked> blocked;
    TLVector<TLUser> users;
    quint32 count = 0;
    TLValue tlType = TLValue::ContactsBlocked;
};

struct TLContactsContacts {
    TLContactsContacts() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsContactsNotModified:
        case TLValue::ContactsContacts:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContact> contacts;
    quint32 savedCount = 0;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsContactsNotModified;
};

struct TLContactsFound {
    TLContactsFound() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsFound:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPeer> results;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsFound;
};

struct TLContactsImportedContacts {
    TLContactsImportedContacts() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsImportedContacts:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLImportedContact> imported;
    TLVector<TLPopularContact> popularInvites;
    TLVector<quint64> retryContacts;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsImportedContacts;
};

struct TLContactsLink {
    TLContactsLink() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsLink:
            return true;
        default:
            return false;
        };
    }
    TLContactLink myLink;
    TLContactLink foreignLink;
    TLUser user;
    TLValue tlType = TLValue::ContactsLink;
};

struct TLContactsResolvedPeer {
    TLContactsResolvedPeer() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsResolvedPeer:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsResolvedPeer;
};

struct TLContactsTopPeers {
    TLContactsTopPeers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ContactsTopPeersNotModified:
        case TLValue::ContactsTopPeers:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLTopPeerCategoryPeers> categories;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsTopPeersNotModified;
};

struct TLDialog {
    TLDialog() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Dialog:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::Dialog;
};

struct TLDocument {
    TLDocument() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::DocumentEmpty:
        case TLValue::Document:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 date = 0;
    QString mimeType;
    quint32 size = 0;
    TLPhotoSize thumb;
    quint32 dcId = 0;
    quint32 version = 0;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType = TLValue::DocumentEmpty;
};

struct TLFoundGif {
    TLFoundGif() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::FoundGif:
        case TLValue::FoundGifCached:
            return true;
        default:
            return false;
        };
    }
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w = 0;
    quint32 h = 0;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType = TLValue::FoundGif;
};

struct TLGame {
    TLGame() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::Game:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::Game;
};

struct TLHelpSupport {
    TLHelpSupport() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HelpSupport:
            return true;
        default:
            return false;
        };
    }
    QString phoneNumber;
    TLUser user;
    TLValue tlType = TLValue::HelpSupport;
};

struct TLInputBotInlineMessage {
    TLInputBotInlineMessage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputBotInlineMessageMediaAuto:
        case TLValue::InputBotInlineMessageText:
        case TLValue::InputBotInlineMessageMediaGeo:
        case TLValue::InputBotInlineMessageMediaVenue:
        case TLValue::InputBotInlineMessageMediaContact:
        case TLValue::InputBotInlineMessageGame:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLMessageEntity> entities;
    TLInputGeoPoint geoPoint;
    quint32 period = 0;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    TLValue tlType = TLValue::InputBotInlineMessageMediaAuto;
};

struct TLInputBotInlineResult {
    TLInputBotInlineResult() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputBotInlineResult:
        case TLValue::InputBotInlineResultPhoto:
        case TLValue::InputBotInlineResultDocument:
        case TLValue::InputBotInlineResultGame:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::InputBotInlineResult;
};

struct TLInputMedia {
    TLInputMedia() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::InputMediaEmpty:
        case TLValue::InputMediaUploadedPhoto:
        case TLValue::InputMediaPhoto:
        case TLValue::InputMediaGeoPoint:
        case TLValue::InputMediaContact:
        case TLValue::InputMediaUploadedDocument:
        case TLValue::InputMediaDocument:
        case TLValue::InputMediaVenue:
        case TLValue::InputMediaGifExternal:
        case TLValue::InputMediaPhotoExternal:
        case TLValue::InputMediaDocumentExternal:
        case TLValue::InputMediaGame:
        case TLValue::InputMediaInvoice:
        case TLValue::InputMediaGeoLive:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Photo = 1 << 0,
        Stickers = 1 << 0,
        TtlSeconds = 1 << 1,
        Thumb = 1 << 2,
        NosoundVideo = 1 << 3,
    };
    bool nosoundVideo() const { return flags & NosoundVideo; }
    quint32 flags = 0;
    TLInputFile file;
    QString caption;
    TLVector<TLInputDocument> stickers;
    quint32 ttlSeconds = 0;
    TLInputPhoto inputPhotoId;
    TLInputGeoPoint geoPoint;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    TLInputFile thumb;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
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
    TLValue tlType = TLValue::InputMediaEmpty;
};

struct TLMessageAction {
    TLMessageAction() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessageActionEmpty:
        case TLValue::MessageActionChatCreate:
        case TLValue::MessageActionChatEditTitle:
        case TLValue::MessageActionChatEditPhoto:
        case TLValue::MessageActionChatDeletePhoto:
        case TLValue::MessageActionChatAddUser:
        case TLValue::MessageActionChatDeleteUser:
        case TLValue::MessageActionChatJoinedByLink:
        case TLValue::MessageActionChannelCreate:
        case TLValue::MessageActionChatMigrateTo:
        case TLValue::MessageActionChannelMigrateFrom:
        case TLValue::MessageActionPinMessage:
        case TLValue::MessageActionHistoryClear:
        case TLValue::MessageActionGameScore:
        case TLValue::MessageActionPaymentSentMe:
        case TLValue::MessageActionPaymentSent:
        case TLValue::MessageActionPhoneCall:
        case TLValue::MessageActionScreenshotTaken:
        case TLValue::MessageActionCustomAction:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Reason = 1 << 0,
        Info = 1 << 0,
        Duration = 1 << 1,
        ShippingOptionId = 1 << 1,
    };
    QString title;
    TLVector<quint32> users;
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
    TLValue tlType = TLValue::MessageActionEmpty;
};

struct TLMessagesAllStickers {
    TLMessagesAllStickers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesAllStickersNotModified:
        case TLValue::MessagesAllStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash = 0;
    TLVector<TLStickerSet> sets;
    TLValue tlType = TLValue::MessagesAllStickersNotModified;
};

struct TLMessagesChatFull {
    TLMessagesChatFull() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesChatFull:
            return true;
        default:
            return false;
        };
    }
    TLChatFull fullChat;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::MessagesChatFull;
};

struct TLMessagesChats {
    TLMessagesChats() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesChats:
        case TLValue::MessagesChatsSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLChat> chats;
    quint32 count = 0;
    TLValue tlType = TLValue::MessagesChats;
};

struct TLMessagesFavedStickers {
    TLMessagesFavedStickers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesFavedStickersNotModified:
        case TLValue::MessagesFavedStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash = 0;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> stickers;
    TLValue tlType = TLValue::MessagesFavedStickersNotModified;
};

struct TLMessagesFoundGifs {
    TLMessagesFoundGifs() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesFoundGifs:
            return true;
        default:
            return false;
        };
    }
    quint32 nextOffset = 0;
    TLVector<TLFoundGif> results;
    TLValue tlType = TLValue::MessagesFoundGifs;
};

struct TLMessagesHighScores {
    TLMessagesHighScores() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesHighScores:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLHighScore> scores;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::MessagesHighScores;
};

struct TLMessagesRecentStickers {
    TLMessagesRecentStickers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesRecentStickersNotModified:
        case TLValue::MessagesRecentStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash = 0;
    TLVector<TLDocument> stickers;
    TLValue tlType = TLValue::MessagesRecentStickersNotModified;
};

struct TLMessagesSavedGifs {
    TLMessagesSavedGifs() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesSavedGifsNotModified:
        case TLValue::MessagesSavedGifs:
            return true;
        default:
            return false;
        };
    }
    quint32 hash = 0;
    TLVector<TLDocument> gifs;
    TLValue tlType = TLValue::MessagesSavedGifsNotModified;
};

struct TLMessagesStickerSet {
    TLMessagesStickerSet() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesStickerSet:
            return true;
        default:
            return false;
        };
    }
    TLStickerSet set;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> documents;
    TLValue tlType = TLValue::MessagesStickerSet;
};

struct TLMessagesStickers {
    TLMessagesStickers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesStickersNotModified:
        case TLValue::MessagesStickers:
            return true;
        default:
            return false;
        };
    }
    QString hash;
    TLVector<TLDocument> stickers;
    TLValue tlType = TLValue::MessagesStickersNotModified;
};

struct TLPageBlock;
using TLPageBlockPtr = TLPtr<TLPageBlock>;

struct TLPageBlock {
    TLPageBlock() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PageBlockUnsupported:
        case TLValue::PageBlockTitle:
        case TLValue::PageBlockSubtitle:
        case TLValue::PageBlockAuthorDate:
        case TLValue::PageBlockHeader:
        case TLValue::PageBlockSubheader:
        case TLValue::PageBlockParagraph:
        case TLValue::PageBlockPreformatted:
        case TLValue::PageBlockFooter:
        case TLValue::PageBlockDivider:
        case TLValue::PageBlockAnchor:
        case TLValue::PageBlockList:
        case TLValue::PageBlockBlockquote:
        case TLValue::PageBlockPullquote:
        case TLValue::PageBlockPhoto:
        case TLValue::PageBlockVideo:
        case TLValue::PageBlockCover:
        case TLValue::PageBlockEmbed:
        case TLValue::PageBlockEmbedPost:
        case TLValue::PageBlockCollage:
        case TLValue::PageBlockSlideshow:
        case TLValue::PageBlockChannel:
        case TLValue::PageBlockAudio:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLRichText*> richTextItemsVector;
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
    TLVector<TLPageBlock*> blocks;
    TLVector<TLPageBlock*> pageBlockItemsVector;
    TLChat channel;
    quint64 audioId = 0;
    TLValue tlType = TLValue::PageBlockUnsupported;
};

struct TLPaymentsPaymentForm {
    TLPaymentsPaymentForm() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentsPaymentForm:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PaymentsPaymentForm;
};

struct TLPaymentsPaymentReceipt {
    TLPaymentsPaymentReceipt() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentsPaymentReceipt:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PaymentsPaymentReceipt;
};

struct TLPhoneCall {
    TLPhoneCall() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhoneCallEmpty:
        case TLValue::PhoneCallWaiting:
        case TLValue::PhoneCallRequested:
        case TLValue::PhoneCallAccepted:
        case TLValue::PhoneCall:
        case TLValue::PhoneCallDiscarded:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLPhoneConnection> alternativeConnections;
    quint32 startDate = 0;
    TLPhoneCallDiscardReason reason;
    quint32 duration = 0;
    TLValue tlType = TLValue::PhoneCallEmpty;
};

struct TLPhonePhoneCall {
    TLPhonePhoneCall() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhonePhoneCall:
            return true;
        default:
            return false;
        };
    }
    TLPhoneCall phoneCall;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PhonePhoneCall;
};

struct TLPhotosPhoto {
    TLPhotosPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhotosPhoto:
            return true;
        default:
            return false;
        };
    }
    TLPhoto photo;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PhotosPhoto;
};

struct TLPhotosPhotos {
    TLPhotosPhotos() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PhotosPhotos:
        case TLValue::PhotosPhotosSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPhoto> photos;
    TLVector<TLUser> users;
    quint32 count = 0;
    TLValue tlType = TLValue::PhotosPhotos;
};

struct TLStickerSetCovered {
    TLStickerSetCovered() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::StickerSetCovered:
        case TLValue::StickerSetMultiCovered:
            return true;
        default:
            return false;
        };
    }
    TLStickerSet set;
    TLDocument cover;
    TLVector<TLDocument> covers;
    TLValue tlType = TLValue::StickerSetCovered;
};

struct TLUserFull {
    TLUserFull() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UserFull:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::UserFull;
};

struct TLBotInlineResult {
    TLBotInlineResult() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::BotInlineResult:
        case TLValue::BotInlineMediaResult:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Photo = 1 << 0,
        Document = 1 << 1,
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
    TLBotInlineMessage sendMessage;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType = TLValue::BotInlineResult;
};

struct TLMessagesArchivedStickers {
    TLMessagesArchivedStickers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesArchivedStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 count = 0;
    TLVector<TLStickerSetCovered> sets;
    TLValue tlType = TLValue::MessagesArchivedStickers;
};

struct TLMessagesBotResults {
    TLMessagesBotResults() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesBotResults:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLBotInlineResult> results;
    quint32 cacheTime = 0;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::MessagesBotResults;
};

struct TLMessagesFeaturedStickers {
    TLMessagesFeaturedStickers() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesFeaturedStickersNotModified:
        case TLValue::MessagesFeaturedStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash = 0;
    TLVector<TLStickerSetCovered> sets;
    TLVector<quint64> unread;
    TLValue tlType = TLValue::MessagesFeaturedStickersNotModified;
};

struct TLMessagesStickerSetInstallResult {
    TLMessagesStickerSetInstallResult() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesStickerSetInstallResultSuccess:
        case TLValue::MessagesStickerSetInstallResultArchive:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLStickerSetCovered> sets;
    TLValue tlType = TLValue::MessagesStickerSetInstallResultSuccess;
};

struct TLPage {
    TLPage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PagePart:
        case TLValue::PageFull:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPageBlock*> blocks;
    TLVector<TLPhoto> photos;
    TLVector<TLDocument> documents;
    TLValue tlType = TLValue::PagePart;
};

struct TLRecentMeUrl {
    TLRecentMeUrl() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::RecentMeUrlUnknown:
        case TLValue::RecentMeUrlUser:
        case TLValue::RecentMeUrlChat:
        case TLValue::RecentMeUrlChatInvite:
        case TLValue::RecentMeUrlStickerSet:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint32 userId = 0;
    quint32 chatId = 0;
    TLChatInvite chatInvite;
    TLStickerSetCovered set;
    TLValue tlType = TLValue::RecentMeUrlUnknown;
};

struct TLWebPage {
    TLWebPage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::WebPageEmpty:
        case TLValue::WebPagePending:
        case TLValue::WebPage:
        case TLValue::WebPageNotModified:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::WebPageEmpty;
};

struct TLHelpRecentMeUrls {
    TLHelpRecentMeUrls() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::HelpRecentMeUrls:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLRecentMeUrl> urls;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::HelpRecentMeUrls;
};

struct TLMessageMedia {
    TLMessageMedia() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessageMediaEmpty:
        case TLValue::MessageMediaPhoto:
        case TLValue::MessageMediaGeo:
        case TLValue::MessageMediaContact:
        case TLValue::MessageMediaUnsupported:
        case TLValue::MessageMediaDocument:
        case TLValue::MessageMediaWebPage:
        case TLValue::MessageMediaVenue:
        case TLValue::MessageMediaGame:
        case TLValue::MessageMediaInvoice:
        case TLValue::MessageMediaGeoLive:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::MessageMediaEmpty;
};

struct TLMessage {
    TLMessage() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessageEmpty:
        case TLValue::Message:
        case TLValue::MessageService:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLMessageEntity> entities;
    quint32 views = 0;
    quint32 editDate = 0;
    QString postAuthor;
    TLMessageAction action;
    TLValue tlType = TLValue::MessageEmpty;
};

struct TLMessagesDialogs {
    TLMessagesDialogs() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesDialogs:
        case TLValue::MessagesDialogsSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLDialog> dialogs;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count = 0;
    TLValue tlType = TLValue::MessagesDialogs;
};

struct TLMessagesMessages {
    TLMessagesMessages() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesMessages:
        case TLValue::MessagesMessagesSlice:
        case TLValue::MessagesChannelMessages:
        case TLValue::MessagesMessagesNotModified:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count = 0;
    quint32 flags = 0;
    quint32 pts = 0;
    TLValue tlType = TLValue::MessagesMessages;
};

struct TLMessagesPeerDialogs {
    TLMessagesPeerDialogs() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::MessagesPeerDialogs:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLDialog> dialogs;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLUpdatesState state;
    TLValue tlType = TLValue::MessagesPeerDialogs;
};

struct TLUpdate {
    TLUpdate() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UpdateNewMessage:
        case TLValue::UpdateMessageID:
        case TLValue::UpdateDeleteMessages:
        case TLValue::UpdateUserTyping:
        case TLValue::UpdateChatUserTyping:
        case TLValue::UpdateChatParticipants:
        case TLValue::UpdateUserStatus:
        case TLValue::UpdateUserName:
        case TLValue::UpdateUserPhoto:
        case TLValue::UpdateContactRegistered:
        case TLValue::UpdateContactLink:
        case TLValue::UpdateNewEncryptedMessage:
        case TLValue::UpdateEncryptedChatTyping:
        case TLValue::UpdateEncryption:
        case TLValue::UpdateEncryptedMessagesRead:
        case TLValue::UpdateChatParticipantAdd:
        case TLValue::UpdateChatParticipantDelete:
        case TLValue::UpdateDcOptions:
        case TLValue::UpdateUserBlocked:
        case TLValue::UpdateNotifySettings:
        case TLValue::UpdateServiceNotification:
        case TLValue::UpdatePrivacy:
        case TLValue::UpdateUserPhone:
        case TLValue::UpdateReadHistoryInbox:
        case TLValue::UpdateReadHistoryOutbox:
        case TLValue::UpdateWebPage:
        case TLValue::UpdateReadMessagesContents:
        case TLValue::UpdateChannelTooLong:
        case TLValue::UpdateChannel:
        case TLValue::UpdateNewChannelMessage:
        case TLValue::UpdateReadChannelInbox:
        case TLValue::UpdateDeleteChannelMessages:
        case TLValue::UpdateChannelMessageViews:
        case TLValue::UpdateChatAdmins:
        case TLValue::UpdateChatParticipantAdmin:
        case TLValue::UpdateNewStickerSet:
        case TLValue::UpdateStickerSetsOrder:
        case TLValue::UpdateStickerSets:
        case TLValue::UpdateSavedGifs:
        case TLValue::UpdateBotInlineQuery:
        case TLValue::UpdateBotInlineSend:
        case TLValue::UpdateEditChannelMessage:
        case TLValue::UpdateChannelPinnedMessage:
        case TLValue::UpdateBotCallbackQuery:
        case TLValue::UpdateEditMessage:
        case TLValue::UpdateInlineBotCallbackQuery:
        case TLValue::UpdateReadChannelOutbox:
        case TLValue::UpdateDraftMessage:
        case TLValue::UpdateReadFeaturedStickers:
        case TLValue::UpdateRecentStickers:
        case TLValue::UpdateConfig:
        case TLValue::UpdatePtsChanged:
        case TLValue::UpdateChannelWebPage:
        case TLValue::UpdateDialogPinned:
        case TLValue::UpdatePinnedDialogs:
        case TLValue::UpdateBotWebhookJSON:
        case TLValue::UpdateBotWebhookJSONQuery:
        case TLValue::UpdateBotShippingQuery:
        case TLValue::UpdateBotPrecheckoutQuery:
        case TLValue::UpdatePhoneCall:
        case TLValue::UpdateLangPackTooLong:
        case TLValue::UpdateLangPack:
        case TLValue::UpdateFavedStickers:
        case TLValue::UpdateChannelReadMessagesContents:
        case TLValue::UpdateContactsReset:
        case TLValue::UpdateChannelAvailableMessages:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Info = 1 << 0,
        PeerOrderVector = 1 << 0,
        Pinned = 1 << 0,
        ByteArrayData = 1 << 0,
        Geo = 1 << 0,
        Masks = 1 << 0,
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
    TLVector<quint32> messages;
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
    TLVector<TLDcOption> dcOptions;
    bool blocked = false;
    TLNotifyPeer notifyPeer;
    TLPeerNotifySettings notifySettings;
    quint32 flags = 0;
    quint32 inboxDate = 0;
    QString type;
    QString stringMessage;
    TLMessageMedia media;
    TLVector<TLMessageEntity> entities;
    TLPrivacyKey key;
    TLVector<TLPrivacyRule> rules;
    QString phone;
    TLPeer peer;
    quint32 maxId = 0;
    TLWebPage webpage;
    quint32 channelId = 0;
    quint32 views = 0;
    bool enabled = false;
    bool isAdmin = false;
    TLMessagesStickerSet stickerset;
    TLVector<quint64> quint64OrderVector;
    quint64 queryId = 0;
    QString query;
    TLGeoPoint geo;
    QString offset;
    QString stringId;
    TLInputBotInlineMessageID inputBotInlineMessageIDMsgId;
    quint32 quint32MsgId = 0;
    quint64 chatInstance = 0;
    QByteArray byteArrayData;
    QString gameShortName;
    TLDraftMessage draft;
    TLVector<TLPeer> peerOrderVector;
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
    TLValue tlType = TLValue::UpdateNewMessage;
};

struct TLUpdates {
    TLUpdates() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UpdatesTooLong:
        case TLValue::UpdateShortMessage:
        case TLValue::UpdateShortChatMessage:
        case TLValue::UpdateShort:
        case TLValue::UpdatesCombined:
        case TLValue::Updates:
        case TLValue::UpdateShortSentMessage:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLMessageEntity> entities;
    quint32 fromId = 0;
    quint32 chatId = 0;
    TLUpdate update;
    TLVector<TLUpdate> updates;
    TLVector<TLUser> users;
    TLVector<TLChat> chats;
    quint32 seqStart = 0;
    quint32 seq = 0;
    TLMessageMedia media;
    TLValue tlType = TLValue::UpdatesTooLong;
};

struct TLUpdatesChannelDifference {
    TLUpdatesChannelDifference() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UpdatesChannelDifferenceEmpty:
        case TLValue::UpdatesChannelDifferenceTooLong:
        case TLValue::UpdatesChannelDifference:
            return true;
        default:
            return false;
        };
    }
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
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLVector<TLMessage> newMessages;
    TLVector<TLUpdate> otherUpdates;
    TLValue tlType = TLValue::UpdatesChannelDifferenceEmpty;
};

struct TLUpdatesDifference {
    TLUpdatesDifference() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::UpdatesDifferenceEmpty:
        case TLValue::UpdatesDifference:
        case TLValue::UpdatesDifferenceSlice:
        case TLValue::UpdatesDifferenceTooLong:
            return true;
        default:
            return false;
        };
    }
    quint32 date = 0;
    quint32 seq = 0;
    TLVector<TLMessage> newMessages;
    TLVector<TLEncryptedMessage> newEncryptedMessages;
    TLVector<TLUpdate> otherUpdates;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLUpdatesState state;
    TLUpdatesState intermediateState;
    quint32 pts = 0;
    TLValue tlType = TLValue::UpdatesDifferenceEmpty;
};

struct TLChannelAdminLogEventAction {
    TLChannelAdminLogEventAction() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelAdminLogEventActionChangeTitle:
        case TLValue::ChannelAdminLogEventActionChangeAbout:
        case TLValue::ChannelAdminLogEventActionChangeUsername:
        case TLValue::ChannelAdminLogEventActionChangePhoto:
        case TLValue::ChannelAdminLogEventActionToggleInvites:
        case TLValue::ChannelAdminLogEventActionToggleSignatures:
        case TLValue::ChannelAdminLogEventActionUpdatePinned:
        case TLValue::ChannelAdminLogEventActionEditMessage:
        case TLValue::ChannelAdminLogEventActionDeleteMessage:
        case TLValue::ChannelAdminLogEventActionParticipantJoin:
        case TLValue::ChannelAdminLogEventActionParticipantLeave:
        case TLValue::ChannelAdminLogEventActionParticipantInvite:
        case TLValue::ChannelAdminLogEventActionParticipantToggleBan:
        case TLValue::ChannelAdminLogEventActionParticipantToggleAdmin:
        case TLValue::ChannelAdminLogEventActionChangeStickerSet:
        case TLValue::ChannelAdminLogEventActionTogglePreHistoryHidden:
            return true;
        default:
            return false;
        };
    }
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
    TLValue tlType = TLValue::ChannelAdminLogEventActionChangeTitle;
};

struct TLPaymentsPaymentResult {
    TLPaymentsPaymentResult() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::PaymentsPaymentResult:
        case TLValue::PaymentsPaymentVerficationNeeded:
            return true;
        default:
            return false;
        };
    }
    TLUpdates updates;
    QString url;
    TLValue tlType = TLValue::PaymentsPaymentResult;
};

struct TLChannelAdminLogEvent {
    TLChannelAdminLogEvent() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelAdminLogEvent:
            return true;
        default:
            return false;
        };
    }
    quint64 id = 0;
    quint32 date = 0;
    quint32 userId = 0;
    TLChannelAdminLogEventAction action;
    TLValue tlType = TLValue::ChannelAdminLogEvent;
};

struct TLChannelsAdminLogResults {
    TLChannelsAdminLogResults() = default;

    bool isValid() const { return hasType(tlType); }
    Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {
        switch (value) {
        case TLValue::ChannelsAdminLogResults:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLChannelAdminLogEvent> events;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ChannelsAdminLogResults;
};
// End of generated TLTypes

Q_DECLARE_METATYPE(TLUploadFile)
Q_DECLARE_METATYPE(QVector<TLUser>)
Q_DECLARE_METATYPE(TLUpdates)

#endif // TLTYPES_HPP
