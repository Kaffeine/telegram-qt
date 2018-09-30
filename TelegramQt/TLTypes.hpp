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
    constexpr TLAccountDaysTTL() :
        days(0),
        tlType(TLValue::AccountDaysTTL) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::AccountDaysTTL:
            return true;
        default:
            return false;
        };
    }
    quint32 days;
    TLValue tlType;
};

struct TLAccountPassword {
    TLAccountPassword() :
        hasRecovery(false),
        tlType(TLValue::AccountNoPassword) { }

    bool isValid() const {
        switch (tlType) {
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
    bool hasRecovery;
    TLValue tlType;
};

struct TLAccountPasswordInputSettings {
    TLAccountPasswordInputSettings() :
        flags(0),
        tlType(TLValue::AccountPasswordInputSettings) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QByteArray newSalt;
    QByteArray newPasswordHash;
    QString hint;
    QString email;
    TLValue tlType;
};

struct TLAccountPasswordSettings {
    TLAccountPasswordSettings() :
        tlType(TLValue::AccountPasswordSettings) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountPasswordSettings:
            return true;
        default:
            return false;
        };
    }
    QString email;
    TLValue tlType;
};

struct TLAccountTmpPassword {
    TLAccountTmpPassword() :
        validUntil(0),
        tlType(TLValue::AccountTmpPassword) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountTmpPassword:
            return true;
        default:
            return false;
        };
    }
    QByteArray tmpPassword;
    quint32 validUntil;
    TLValue tlType;
};

struct TLAuthCheckedPhone {
    constexpr TLAuthCheckedPhone() :
        phoneRegistered(false),
        tlType(TLValue::AuthCheckedPhone) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::AuthCheckedPhone:
            return true;
        default:
            return false;
        };
    }
    bool phoneRegistered;
    TLValue tlType;
};

struct TLAuthCodeType {
    constexpr TLAuthCodeType() :
        tlType(TLValue::AuthCodeTypeSms) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::AuthCodeTypeSms:
        case TLValue::AuthCodeTypeCall:
        case TLValue::AuthCodeTypeFlashCall:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLAuthExportedAuthorization {
    TLAuthExportedAuthorization() :
        id(0),
        tlType(TLValue::AuthExportedAuthorization) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthExportedAuthorization:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    QByteArray bytes;
    TLValue tlType;
};

struct TLAuthPasswordRecovery {
    TLAuthPasswordRecovery() :
        tlType(TLValue::AuthPasswordRecovery) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthPasswordRecovery:
            return true;
        default:
            return false;
        };
    }
    QString emailPattern;
    TLValue tlType;
};

struct TLAuthSentCodeType {
    TLAuthSentCodeType() :
        length(0),
        tlType(TLValue::AuthSentCodeTypeApp) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthSentCodeTypeApp:
        case TLValue::AuthSentCodeTypeSms:
        case TLValue::AuthSentCodeTypeCall:
        case TLValue::AuthSentCodeTypeFlashCall:
            return true;
        default:
            return false;
        };
    }
    quint32 length;
    QString pattern;
    TLValue tlType;
};

struct TLAuthorization {
    TLAuthorization() :
        hash(0),
        flags(0),
        apiId(0),
        dateCreated(0),
        dateActive(0),
        tlType(TLValue::Authorization) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Authorization:
            return true;
        default:
            return false;
        };
    }
    quint64 hash;
    quint32 flags;
    QString deviceModel;
    QString platform;
    QString systemVersion;
    quint32 apiId;
    QString appName;
    QString appVersion;
    quint32 dateCreated;
    quint32 dateActive;
    QString ip;
    QString country;
    QString region;
    TLValue tlType;
};

struct TLBadMsgNotification {
    constexpr TLBadMsgNotification() :
        badMsgId(0),
        badMsgSeqno(0),
        errorCode(0),
        newServerSalt(0),
        tlType(TLValue::BadMsgNotification) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::BadMsgNotification:
        case TLValue::BadServerSalt:
            return true;
        default:
            return false;
        };
    }
    quint64 badMsgId;
    quint32 badMsgSeqno;
    quint32 errorCode;
    quint64 newServerSalt;
    TLValue tlType;
};

struct TLBotCommand {
    TLBotCommand() :
        tlType(TLValue::BotCommand) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::BotCommand:
            return true;
        default:
            return false;
        };
    }
    QString command;
    QString description;
    TLValue tlType;
};

struct TLBotInfo {
    TLBotInfo() :
        userId(0),
        tlType(TLValue::BotInfo) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::BotInfo:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    QString description;
    TLVector<TLBotCommand> commands;
    TLValue tlType;
};

struct TLCdnFileHash {
    TLCdnFileHash() :
        offset(0),
        limit(0),
        tlType(TLValue::CdnFileHash) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::CdnFileHash:
            return true;
        default:
            return false;
        };
    }
    quint32 offset;
    quint32 limit;
    QByteArray hash;
    TLValue tlType;
};

struct TLCdnPublicKey {
    TLCdnPublicKey() :
        dcId(0),
        tlType(TLValue::CdnPublicKey) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::CdnPublicKey:
            return true;
        default:
            return false;
        };
    }
    quint32 dcId;
    QString publicKey;
    TLValue tlType;
};

struct TLChannelParticipantsFilter {
    TLChannelParticipantsFilter() :
        tlType(TLValue::ChannelParticipantsRecent) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLChatParticipant {
    constexpr TLChatParticipant() :
        userId(0),
        inviterId(0),
        date(0),
        tlType(TLValue::ChatParticipant) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::ChatParticipant:
        case TLValue::ChatParticipantCreator:
        case TLValue::ChatParticipantAdmin:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 inviterId;
    quint32 date;
    TLValue tlType;
};

struct TLChatParticipants {
    TLChatParticipants() :
        flags(0),
        chatId(0),
        version(0),
        tlType(TLValue::ChatParticipantsForbidden) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 chatId;
    TLChatParticipant selfParticipant;
    TLVector<TLChatParticipant> participants;
    quint32 version;
    TLValue tlType;
};

struct TLClientDHInnerData {
    TLClientDHInnerData() :
        retryId(0),
        tlType(TLValue::ClientDHInnerData) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ClientDHInnerData:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint64 retryId;
    QString gB;
    TLValue tlType;
};

struct TLContact {
    constexpr TLContact() :
        userId(0),
        mutual(false),
        tlType(TLValue::Contact) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::Contact:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    bool mutual;
    TLValue tlType;
};

struct TLContactBlocked {
    constexpr TLContactBlocked() :
        userId(0),
        date(0),
        tlType(TLValue::ContactBlocked) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::ContactBlocked:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 date;
    TLValue tlType;
};

struct TLContactLink {
    constexpr TLContactLink() :
        tlType(TLValue::ContactLinkUnknown) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::ContactLinkUnknown:
        case TLValue::ContactLinkNone:
        case TLValue::ContactLinkHasPhone:
        case TLValue::ContactLinkContact:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLDataJSON {
    TLDataJSON() :
        tlType(TLValue::DataJSON) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DataJSON:
            return true;
        default:
            return false;
        };
    }
    QString data;
    TLValue tlType;
};

struct TLDestroyAuthKeyRes {
    constexpr TLDestroyAuthKeyRes() :
        tlType(TLValue::DestroyAuthKeyOk) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::DestroyAuthKeyOk:
        case TLValue::DestroyAuthKeyNone:
        case TLValue::DestroyAuthKeyFail:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLDestroySessionRes {
    constexpr TLDestroySessionRes() :
        sessionId(0),
        tlType(TLValue::DestroySessionOk) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::DestroySessionOk:
        case TLValue::DestroySessionNone:
            return true;
        default:
            return false;
        };
    }
    quint64 sessionId;
    TLValue tlType;
};

struct TLDisabledFeature {
    TLDisabledFeature() :
        tlType(TLValue::DisabledFeature) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DisabledFeature:
            return true;
        default:
            return false;
        };
    }
    QString feature;
    QString description;
    TLValue tlType;
};

struct TLEncryptedChat {
    TLEncryptedChat() :
        id(0),
        accessHash(0),
        date(0),
        adminId(0),
        participantId(0),
        keyFingerprint(0),
        tlType(TLValue::EncryptedChatEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 id;
    quint64 accessHash;
    quint32 date;
    quint32 adminId;
    quint32 participantId;
    QByteArray gA;
    QByteArray gAOrB;
    quint64 keyFingerprint;
    TLValue tlType;
};

struct TLEncryptedFile {
    constexpr TLEncryptedFile() :
        id(0),
        accessHash(0),
        size(0),
        dcId(0),
        keyFingerprint(0),
        tlType(TLValue::EncryptedFileEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::EncryptedFileEmpty:
        case TLValue::EncryptedFile:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 size;
    quint32 dcId;
    quint32 keyFingerprint;
    TLValue tlType;
};

struct TLEncryptedMessage {
    TLEncryptedMessage() :
        randomId(0),
        chatId(0),
        date(0),
        tlType(TLValue::EncryptedMessage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::EncryptedMessage:
        case TLValue::EncryptedMessageService:
            return true;
        default:
            return false;
        };
    }
    quint64 randomId;
    quint32 chatId;
    quint32 date;
    QByteArray bytes;
    TLEncryptedFile file;
    TLValue tlType;
};

struct TLError {
    TLError() :
        code(0),
        tlType(TLValue::Error) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Error:
            return true;
        default:
            return false;
        };
    }
    quint32 code;
    QString text;
    TLValue tlType;
};

struct TLExportedChatInvite {
    TLExportedChatInvite() :
        tlType(TLValue::ChatInviteEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatInviteEmpty:
        case TLValue::ChatInviteExported:
            return true;
        default:
            return false;
        };
    }
    QString link;
    TLValue tlType;
};

struct TLExportedMessageLink {
    TLExportedMessageLink() :
        tlType(TLValue::ExportedMessageLink) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ExportedMessageLink:
            return true;
        default:
            return false;
        };
    }
    QString link;
    TLValue tlType;
};

struct TLFileLocation {
    constexpr TLFileLocation() :
        volumeId(0),
        localId(0),
        secret(0),
        dcId(0),
        tlType(TLValue::FileLocationUnavailable) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::FileLocationUnavailable:
        case TLValue::FileLocation:
            return true;
        default:
            return false;
        };
    }
    quint64 volumeId;
    quint32 localId;
    quint64 secret;
    quint32 dcId;
    TLValue tlType;
};

struct TLFutureSalt {
    constexpr TLFutureSalt() :
        validSince(0),
        validUntil(0),
        salt(0),
        tlType(TLValue::FutureSalt) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::FutureSalt:
            return true;
        default:
            return false;
        };
    }
    quint32 validSince;
    quint32 validUntil;
    quint64 salt;
    TLValue tlType;
};

struct TLFutureSalts {
    TLFutureSalts() :
        reqMsgId(0),
        now(0),
        tlType(TLValue::FutureSalts) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::FutureSalts:
            return true;
        default:
            return false;
        };
    }
    quint64 reqMsgId;
    quint32 now;
    TLVector<TLFutureSalt> salts;
    TLValue tlType;
};

struct TLGeoPoint {
    constexpr TLGeoPoint() :
        longitude(0),
        latitude(0),
        tlType(TLValue::GeoPointEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::GeoPointEmpty:
        case TLValue::GeoPoint:
            return true;
        default:
            return false;
        };
    }
    double longitude;
    double latitude;
    TLValue tlType;
};

struct TLHelpAppUpdate {
    TLHelpAppUpdate() :
        id(0),
        critical(false),
        tlType(TLValue::HelpAppUpdate) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpAppUpdate:
        case TLValue::HelpNoAppUpdate:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    bool critical;
    QString url;
    QString text;
    TLValue tlType;
};

struct TLHelpInviteText {
    TLHelpInviteText() :
        tlType(TLValue::HelpInviteText) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpInviteText:
            return true;
        default:
            return false;
        };
    }
    QString message;
    TLValue tlType;
};

struct TLHelpTermsOfService {
    TLHelpTermsOfService() :
        tlType(TLValue::HelpTermsOfService) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpTermsOfService:
            return true;
        default:
            return false;
        };
    }
    QString text;
    TLValue tlType;
};

struct TLHighScore {
    constexpr TLHighScore() :
        pos(0),
        userId(0),
        score(0),
        tlType(TLValue::HighScore) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::HighScore:
            return true;
        default:
            return false;
        };
    }
    quint32 pos;
    quint32 userId;
    quint32 score;
    TLValue tlType;
};

struct TLHttpWait {
    constexpr TLHttpWait() :
        maxDelay(0),
        waitAfter(0),
        maxWait(0),
        tlType(TLValue::HttpWait) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::HttpWait:
            return true;
        default:
            return false;
        };
    }
    quint32 maxDelay;
    quint32 waitAfter;
    quint32 maxWait;
    TLValue tlType;
};

struct TLImportedContact {
    constexpr TLImportedContact() :
        userId(0),
        clientId(0),
        tlType(TLValue::ImportedContact) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::ImportedContact:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint64 clientId;
    TLValue tlType;
};

struct TLInlineBotSwitchPM {
    TLInlineBotSwitchPM() :
        tlType(TLValue::InlineBotSwitchPM) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InlineBotSwitchPM:
            return true;
        default:
            return false;
        };
    }
    QString text;
    QString startParam;
    TLValue tlType;
};

struct TLInputAppEvent {
    TLInputAppEvent() :
        time(0),
        peer(0),
        tlType(TLValue::InputAppEvent) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputAppEvent:
            return true;
        default:
            return false;
        };
    }
    double time;
    QString type;
    quint64 peer;
    QString data;
    TLValue tlType;
};

struct TLInputBotInlineMessageID {
    constexpr TLInputBotInlineMessageID() :
        dcId(0),
        id(0),
        accessHash(0),
        tlType(TLValue::InputBotInlineMessageID) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputBotInlineMessageID:
            return true;
        default:
            return false;
        };
    }
    quint32 dcId;
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputChannel {
    constexpr TLInputChannel() :
        channelId(0),
        accessHash(0),
        tlType(TLValue::InputChannelEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputChannelEmpty:
        case TLValue::InputChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 channelId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputContact {
    TLInputContact() :
        clientId(0),
        tlType(TLValue::InputPhoneContact) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputPhoneContact:
            return true;
        default:
            return false;
        };
    }
    quint64 clientId;
    QString phone;
    QString firstName;
    QString lastName;
    TLValue tlType;
};

struct TLInputDocument {
    constexpr TLInputDocument() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputDocumentEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputDocumentEmpty:
        case TLValue::InputDocument:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputEncryptedChat {
    constexpr TLInputEncryptedChat() :
        chatId(0),
        accessHash(0),
        tlType(TLValue::InputEncryptedChat) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputEncryptedChat:
            return true;
        default:
            return false;
        };
    }
    quint32 chatId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputEncryptedFile {
    TLInputEncryptedFile() :
        id(0),
        parts(0),
        keyFingerprint(0),
        accessHash(0),
        tlType(TLValue::InputEncryptedFileEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputEncryptedFileEmpty:
        case TLValue::InputEncryptedFileUploaded:
        case TLValue::InputEncryptedFile:
        case TLValue::InputEncryptedFileBigUploaded:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint32 parts;
    QString md5Checksum;
    quint32 keyFingerprint;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputFile {
    TLInputFile() :
        id(0),
        parts(0),
        tlType(TLValue::InputFile) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputFile:
        case TLValue::InputFileBig:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint32 parts;
    QString name;
    QString md5Checksum;
    TLValue tlType;
};

struct TLInputFileLocation {
    constexpr TLInputFileLocation() :
        volumeId(0),
        localId(0),
        secret(0),
        id(0),
        accessHash(0),
        version(0),
        tlType(TLValue::InputFileLocation) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputFileLocation:
        case TLValue::InputEncryptedFileLocation:
        case TLValue::InputDocumentFileLocation:
            return true;
        default:
            return false;
        };
    }
    quint64 volumeId;
    quint32 localId;
    quint64 secret;
    quint64 id;
    quint64 accessHash;
    quint32 version;
    TLValue tlType;
};

struct TLInputGeoPoint {
    constexpr TLInputGeoPoint() :
        latitude(0),
        longitude(0),
        tlType(TLValue::InputGeoPointEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputGeoPointEmpty:
        case TLValue::InputGeoPoint:
            return true;
        default:
            return false;
        };
    }
    double latitude;
    double longitude;
    TLValue tlType;
};

struct TLInputPeer {
    constexpr TLInputPeer() :
        chatId(0),
        userId(0),
        accessHash(0),
        channelId(0),
        tlType(TLValue::InputPeerEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
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
    quint32 chatId;
    quint32 userId;
    quint64 accessHash;
    quint32 channelId;
    TLValue tlType;
};

struct TLInputPeerNotifyEvents {
    constexpr TLInputPeerNotifyEvents() :
        tlType(TLValue::InputPeerNotifyEventsEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputPeerNotifyEventsEmpty:
        case TLValue::InputPeerNotifyEventsAll:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLInputPhoneCall {
    constexpr TLInputPhoneCall() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputPhoneCall) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputPhoneCall:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputPhoto {
    constexpr TLInputPhoto() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputPhotoEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputPhotoEmpty:
        case TLValue::InputPhoto:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputPrivacyKey {
    constexpr TLInputPrivacyKey() :
        tlType(TLValue::InputPrivacyKeyStatusTimestamp) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputPrivacyKeyStatusTimestamp:
        case TLValue::InputPrivacyKeyChatInvite:
        case TLValue::InputPrivacyKeyPhoneCall:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLInputStickerSet {
    TLInputStickerSet() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputStickerSetEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputStickerSetEmpty:
        case TLValue::InputStickerSetID:
        case TLValue::InputStickerSetShortName:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    QString shortName;
    TLValue tlType;
};

struct TLInputStickeredMedia {
    TLInputStickeredMedia() :
        tlType(TLValue::InputStickeredMediaPhoto) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputStickeredMediaPhoto:
        case TLValue::InputStickeredMediaDocument:
            return true;
        default:
            return false;
        };
    }
    TLInputPhoto inputPhotoId;
    TLInputDocument inputDocumentId;
    TLValue tlType;
};

struct TLInputUser {
    constexpr TLInputUser() :
        userId(0),
        accessHash(0),
        tlType(TLValue::InputUserEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::InputUserEmpty:
        case TLValue::InputUserSelf:
        case TLValue::InputUser:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputWebFileLocation {
    TLInputWebFileLocation() :
        accessHash(0),
        tlType(TLValue::InputWebFileLocation) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputWebFileLocation:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint64 accessHash;
    TLValue tlType;
};

struct TLIpPort {
    constexpr TLIpPort() :
        ipv4(0),
        port(0),
        tlType(TLValue::IpPort) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::IpPort:
            return true;
        default:
            return false;
        };
    }
    quint32 ipv4;
    quint32 port;
    TLValue tlType;
};

struct TLLabeledPrice {
    TLLabeledPrice() :
        amount(0),
        tlType(TLValue::LabeledPrice) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::LabeledPrice:
            return true;
        default:
            return false;
        };
    }
    QString label;
    quint64 amount;
    TLValue tlType;
};

struct TLLangPackLanguage {
    TLLangPackLanguage() :
        tlType(TLValue::LangPackLanguage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::LangPackLanguage:
            return true;
        default:
            return false;
        };
    }
    QString name;
    QString nativeName;
    QString langCode;
    TLValue tlType;
};

struct TLLangPackString {
    TLLangPackString() :
        flags(0),
        tlType(TLValue::LangPackString) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString zeroValue;
    QString oneValue;
    QString twoValue;
    QString fewValue;
    QString manyValue;
    QString otherValue;
    TLValue tlType;
};

struct TLMaskCoords {
    constexpr TLMaskCoords() :
        n(0),
        x(0),
        y(0),
        zoom(0),
        tlType(TLValue::MaskCoords) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::MaskCoords:
            return true;
        default:
            return false;
        };
    }
    quint32 n;
    double x;
    double y;
    double zoom;
    TLValue tlType;
};

struct TLMessageEntity {
    TLMessageEntity() :
        offset(0),
        length(0),
        quint32UserId(0),
        tlType(TLValue::MessageEntityUnknown) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 offset;
    quint32 length;
    QString language;
    QString url;
    quint32 quint32UserId;
    TLInputUser inputUserUserId;
    TLValue tlType;
};

struct TLMessageFwdHeader {
    TLMessageFwdHeader() :
        flags(0),
        fromId(0),
        date(0),
        channelId(0),
        channelPost(0),
        tlType(TLValue::MessageFwdHeader) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 fromId;
    quint32 date;
    quint32 channelId;
    quint32 channelPost;
    QString postAuthor;
    TLValue tlType;
};

struct TLMessageRange {
    constexpr TLMessageRange() :
        minId(0),
        maxId(0),
        tlType(TLValue::MessageRange) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::MessageRange:
            return true;
        default:
            return false;
        };
    }
    quint32 minId;
    quint32 maxId;
    TLValue tlType;
};

struct TLMessagesAffectedHistory {
    constexpr TLMessagesAffectedHistory() :
        pts(0),
        ptsCount(0),
        offset(0),
        tlType(TLValue::MessagesAffectedHistory) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesAffectedHistory:
            return true;
        default:
            return false;
        };
    }
    quint32 pts;
    quint32 ptsCount;
    quint32 offset;
    TLValue tlType;
};

struct TLMessagesAffectedMessages {
    constexpr TLMessagesAffectedMessages() :
        pts(0),
        ptsCount(0),
        tlType(TLValue::MessagesAffectedMessages) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesAffectedMessages:
            return true;
        default:
            return false;
        };
    }
    quint32 pts;
    quint32 ptsCount;
    TLValue tlType;
};

struct TLMessagesDhConfig {
    TLMessagesDhConfig() :
        g(0),
        version(0),
        tlType(TLValue::MessagesDhConfigNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesDhConfigNotModified:
        case TLValue::MessagesDhConfig:
            return true;
        default:
            return false;
        };
    }
    QByteArray random;
    quint32 g;
    QByteArray p;
    quint32 version;
    TLValue tlType;
};

struct TLMessagesSentEncryptedMessage {
    TLMessagesSentEncryptedMessage() :
        date(0),
        tlType(TLValue::MessagesSentEncryptedMessage) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesSentEncryptedMessage:
        case TLValue::MessagesSentEncryptedFile:
            return true;
        default:
            return false;
        };
    }
    quint32 date;
    TLEncryptedFile file;
    TLValue tlType;
};

struct TLMsgDetailedInfo {
    constexpr TLMsgDetailedInfo() :
        msgId(0),
        answerMsgId(0),
        bytes(0),
        status(0),
        tlType(TLValue::MsgDetailedInfo) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::MsgDetailedInfo:
        case TLValue::MsgNewDetailedInfo:
            return true;
        default:
            return false;
        };
    }
    quint64 msgId;
    quint64 answerMsgId;
    quint32 bytes;
    quint32 status;
    TLValue tlType;
};

struct TLMsgResendReq {
    TLMsgResendReq() :
        tlType(TLValue::MsgResendReq) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MsgResendReq:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    TLValue tlType;
};

struct TLMsgsAck {
    TLMsgsAck() :
        tlType(TLValue::MsgsAck) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MsgsAck:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    TLValue tlType;
};

struct TLMsgsAllInfo {
    TLMsgsAllInfo() :
        tlType(TLValue::MsgsAllInfo) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MsgsAllInfo:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    QString info;
    TLValue tlType;
};

struct TLMsgsStateInfo {
    TLMsgsStateInfo() :
        reqMsgId(0),
        tlType(TLValue::MsgsStateInfo) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MsgsStateInfo:
            return true;
        default:
            return false;
        };
    }
    quint64 reqMsgId;
    QString info;
    TLValue tlType;
};

struct TLMsgsStateReq {
    TLMsgsStateReq() :
        tlType(TLValue::MsgsStateReq) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MsgsStateReq:
            return true;
        default:
            return false;
        };
    }
    TLVector<quint64> msgIds;
    TLValue tlType;
};

struct TLNearestDc {
    TLNearestDc() :
        thisDc(0),
        nearestDc(0),
        tlType(TLValue::NearestDc) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::NearestDc:
            return true;
        default:
            return false;
        };
    }
    QString country;
    quint32 thisDc;
    quint32 nearestDc;
    TLValue tlType;
};

struct TLNewSession {
    constexpr TLNewSession() :
        firstMsgId(0),
        uniqueId(0),
        serverSalt(0),
        tlType(TLValue::NewSessionCreated) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::NewSessionCreated:
            return true;
        default:
            return false;
        };
    }
    quint64 firstMsgId;
    quint64 uniqueId;
    quint64 serverSalt;
    TLValue tlType;
};

struct TLPQInnerData {
    TLPQInnerData() :
        tlType(TLValue::PQInnerData) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLPaymentCharge {
    TLPaymentCharge() :
        tlType(TLValue::PaymentCharge) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PaymentCharge:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString providerChargeId;
    TLValue tlType;
};

struct TLPaymentSavedCredentials {
    TLPaymentSavedCredentials() :
        tlType(TLValue::PaymentSavedCredentialsCard) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PaymentSavedCredentialsCard:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString title;
    TLValue tlType;
};

struct TLPeer {
    constexpr TLPeer() :
        userId(0),
        chatId(0),
        channelId(0),
        tlType(TLValue::PeerUser) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::PeerUser:
        case TLValue::PeerChat:
        case TLValue::PeerChannel:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    quint32 chatId;
    quint32 channelId;
    TLValue tlType;
};

struct TLPeerNotifyEvents {
    constexpr TLPeerNotifyEvents() :
        tlType(TLValue::PeerNotifyEventsEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::PeerNotifyEventsEmpty:
        case TLValue::PeerNotifyEventsAll:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLPhoneCallDiscardReason {
    constexpr TLPhoneCallDiscardReason() :
        tlType(TLValue::PhoneCallDiscardReasonMissed) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::PhoneCallDiscardReasonMissed:
        case TLValue::PhoneCallDiscardReasonDisconnect:
        case TLValue::PhoneCallDiscardReasonHangup:
        case TLValue::PhoneCallDiscardReasonBusy:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLPhoneConnection {
    TLPhoneConnection() :
        id(0),
        port(0),
        tlType(TLValue::PhoneConnection) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhoneConnection:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    QString ip;
    QString ipv6;
    quint32 port;
    QByteArray peerTag;
    TLValue tlType;
};

struct TLPhotoSize {
    TLPhotoSize() :
        w(0),
        h(0),
        size(0),
        tlType(TLValue::PhotoSizeEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 w;
    quint32 h;
    quint32 size;
    QByteArray bytes;
    TLValue tlType;
};

struct TLPong {
    constexpr TLPong() :
        msgId(0),
        pingId(0),
        tlType(TLValue::Pong) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::Pong:
            return true;
        default:
            return false;
        };
    }
    quint64 msgId;
    quint64 pingId;
    TLValue tlType;
};

struct TLPopularContact {
    constexpr TLPopularContact() :
        clientId(0),
        importers(0),
        tlType(TLValue::PopularContact) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::PopularContact:
            return true;
        default:
            return false;
        };
    }
    quint64 clientId;
    quint32 importers;
    TLValue tlType;
};

struct TLPostAddress {
    TLPostAddress() :
        tlType(TLValue::PostAddress) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLPrivacyKey {
    constexpr TLPrivacyKey() :
        tlType(TLValue::PrivacyKeyStatusTimestamp) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::PrivacyKeyStatusTimestamp:
        case TLValue::PrivacyKeyChatInvite:
        case TLValue::PrivacyKeyPhoneCall:
            return true;
        default:
            return false;
        };
    }
    TLValue tlType;
};

struct TLPrivacyRule {
    TLPrivacyRule() :
        tlType(TLValue::PrivacyValueAllowContacts) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLReceivedNotifyMessage {
    constexpr TLReceivedNotifyMessage() :
        id(0),
        flags(0),
        tlType(TLValue::ReceivedNotifyMessage) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::ReceivedNotifyMessage:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    quint32 flags;
    TLValue tlType;
};

struct TLReportReason {
    TLReportReason() :
        tlType(TLValue::InputReportReasonSpam) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLResPQ {
    TLResPQ() :
        tlType(TLValue::ResPQ) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLRichText {
    TLRichText() :
        webpageId(0),
        tlType(TLValue::TextEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    TLRichText *richText;
    QString url;
    quint64 webpageId;
    QString email;
    TLVector<TLRichText*> texts;
    TLValue tlType;
};

struct TLRpcDropAnswer {
    constexpr TLRpcDropAnswer() :
        msgId(0),
        seqNo(0),
        bytes(0),
        tlType(TLValue::RpcAnswerUnknown) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::RpcAnswerUnknown:
        case TLValue::RpcAnswerDroppedRunning:
        case TLValue::RpcAnswerDropped:
            return true;
        default:
            return false;
        };
    }
    quint64 msgId;
    quint32 seqNo;
    quint32 bytes;
    TLValue tlType;
};

struct TLRpcError {
    TLRpcError() :
        errorCode(0),
        tlType(TLValue::RpcError) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::RpcError:
            return true;
        default:
            return false;
        };
    }
    quint32 errorCode;
    QString errorMessage;
    TLValue tlType;
};

struct TLSendMessageAction {
    constexpr TLSendMessageAction() :
        progress(0),
        tlType(TLValue::SendMessageTypingAction) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
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
    quint32 progress;
    TLValue tlType;
};

struct TLServerDHInnerData {
    TLServerDHInnerData() :
        g(0),
        serverTime(0),
        tlType(TLValue::ServerDHInnerData) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ServerDHInnerData:
            return true;
        default:
            return false;
        };
    }
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint32 g;
    QString dhPrime;
    QString gA;
    quint32 serverTime;
    TLValue tlType;
};

struct TLServerDHParams {
    TLServerDHParams() :
        tlType(TLValue::ServerDHParamsFail) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLSetClientDHParamsAnswer {
    TLSetClientDHParamsAnswer() :
        tlType(TLValue::DhGenOk) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLShippingOption {
    TLShippingOption() :
        tlType(TLValue::ShippingOption) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ShippingOption:
            return true;
        default:
            return false;
        };
    }
    QString id;
    QString title;
    TLVector<TLLabeledPrice> prices;
    TLValue tlType;
};

struct TLStickerPack {
    TLStickerPack() :
        tlType(TLValue::StickerPack) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::StickerPack:
            return true;
        default:
            return false;
        };
    }
    QString emoticon;
    TLVector<quint64> documents;
    TLValue tlType;
};

struct TLStorageFileType {
    constexpr TLStorageFileType() :
        tlType(TLValue::StorageFileUnknown) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLTopPeer {
    TLTopPeer() :
        rating(0),
        tlType(TLValue::TopPeer) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::TopPeer:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    double rating;
    TLValue tlType;
};

struct TLTopPeerCategory {
    constexpr TLTopPeerCategory() :
        tlType(TLValue::TopPeerCategoryBotsPM) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLTopPeerCategoryPeers {
    TLTopPeerCategoryPeers() :
        count(0),
        tlType(TLValue::TopPeerCategoryPeers) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::TopPeerCategoryPeers:
            return true;
        default:
            return false;
        };
    }
    TLTopPeerCategory category;
    quint32 count;
    TLVector<TLTopPeer> peers;
    TLValue tlType;
};

struct TLUpdatesState {
    constexpr TLUpdatesState() :
        pts(0),
        qts(0),
        date(0),
        seq(0),
        unreadCount(0),
        tlType(TLValue::UpdatesState) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
        case TLValue::UpdatesState:
            return true;
        default:
            return false;
        };
    }
    quint32 pts;
    quint32 qts;
    quint32 date;
    quint32 seq;
    quint32 unreadCount;
    TLValue tlType;
};

struct TLUploadCdnFile {
    TLUploadCdnFile() :
        tlType(TLValue::UploadCdnFileReuploadNeeded) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UploadCdnFileReuploadNeeded:
        case TLValue::UploadCdnFile:
            return true;
        default:
            return false;
        };
    }
    QByteArray requestToken;
    QByteArray bytes;
    TLValue tlType;
};

struct TLUploadFile {
    TLUploadFile() :
        mtime(0),
        dcId(0),
        tlType(TLValue::UploadFile) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UploadFile:
        case TLValue::UploadFileCdnRedirect:
            return true;
        default:
            return false;
        };
    }
    TLStorageFileType type;
    quint32 mtime;
    QByteArray bytes;
    quint32 dcId;
    QByteArray fileToken;
    QByteArray encryptionKey;
    QByteArray encryptionIv;
    TLVector<TLCdnFileHash> cdnFileHashes;
    TLValue tlType;
};

struct TLUploadWebFile {
    TLUploadWebFile() :
        size(0),
        mtime(0),
        tlType(TLValue::UploadWebFile) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UploadWebFile:
            return true;
        default:
            return false;
        };
    }
    quint32 size;
    QString mimeType;
    TLStorageFileType fileType;
    quint32 mtime;
    QByteArray bytes;
    TLValue tlType;
};

struct TLUserProfilePhoto {
    TLUserProfilePhoto() :
        photoId(0),
        tlType(TLValue::UserProfilePhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UserProfilePhotoEmpty:
        case TLValue::UserProfilePhoto:
            return true;
        default:
            return false;
        };
    }
    quint64 photoId;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLUserStatus {
    constexpr TLUserStatus() :
        expires(0),
        wasOnline(0),
        tlType(TLValue::UserStatusEmpty) { }

    Q_DECL_RELAXED_CONSTEXPR bool isValid() const {
        switch (tlType) {
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
    quint32 expires;
    quint32 wasOnline;
    TLValue tlType;
};

struct TLWallPaper {
    TLWallPaper() :
        id(0),
        color(0),
        bgColor(0),
        tlType(TLValue::WallPaper) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::WallPaper:
        case TLValue::WallPaperSolid:
            return true;
        default:
            return false;
        };
    }
    quint32 id;
    QString title;
    TLVector<TLPhotoSize> sizes;
    quint32 color;
    quint32 bgColor;
    TLValue tlType;
};

struct TLAccountAuthorizations {
    TLAccountAuthorizations() :
        tlType(TLValue::AccountAuthorizations) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountAuthorizations:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLAuthorization> authorizations;
    TLValue tlType;
};

struct TLAuthSentCode {
    TLAuthSentCode() :
        flags(0),
        timeout(0),
        tlType(TLValue::AuthSentCode) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLAuthSentCodeType type;
    QString phoneCodeHash;
    TLAuthCodeType nextType;
    quint32 timeout;
    TLValue tlType;
};

struct TLCdnConfig {
    TLCdnConfig() :
        tlType(TLValue::CdnConfig) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::CdnConfig:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLCdnPublicKey> publicKeys;
    TLValue tlType;
};

struct TLChannelAdminLogEventsFilter {
    TLChannelAdminLogEventsFilter() :
        flags(0),
        tlType(TLValue::ChannelAdminLogEventsFilter) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLValue tlType;
};

struct TLChannelAdminRights {
    TLChannelAdminRights() :
        flags(0),
        tlType(TLValue::ChannelAdminRights) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLValue tlType;
};

struct TLChannelBannedRights {
    TLChannelBannedRights() :
        flags(0),
        untilDate(0),
        tlType(TLValue::ChannelBannedRights) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 untilDate;
    TLValue tlType;
};

struct TLChannelMessagesFilter {
    TLChannelMessagesFilter() :
        flags(0),
        tlType(TLValue::ChannelMessagesFilterEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLVector<TLMessageRange> ranges;
    TLValue tlType;
};

struct TLChannelParticipant {
    TLChannelParticipant() :
        userId(0),
        date(0),
        inviterId(0),
        flags(0),
        promotedBy(0),
        kickedBy(0),
        tlType(TLValue::ChannelParticipant) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 userId;
    quint32 date;
    quint32 inviterId;
    quint32 flags;
    quint32 promotedBy;
    TLChannelAdminRights adminRights;
    quint32 kickedBy;
    TLChannelBannedRights bannedRights;
    TLValue tlType;
};

struct TLChatPhoto {
    TLChatPhoto() :
        tlType(TLValue::ChatPhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChatPhotoEmpty:
        case TLValue::ChatPhoto:
            return true;
        default:
            return false;
        };
    }
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLContactStatus {
    TLContactStatus() :
        userId(0),
        tlType(TLValue::ContactStatus) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactStatus:
            return true;
        default:
            return false;
        };
    }
    quint32 userId;
    TLUserStatus status;
    TLValue tlType;
};

struct TLDcOption {
    TLDcOption() :
        flags(0),
        id(0),
        port(0),
        tlType(TLValue::DcOption) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 id;
    QString ipAddress;
    quint32 port;
    TLValue tlType;
};

struct TLDocumentAttribute {
    TLDocumentAttribute() :
        w(0),
        h(0),
        flags(0),
        duration(0),
        tlType(TLValue::DocumentAttributeImageSize) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 w;
    quint32 h;
    quint32 flags;
    QString alt;
    TLInputStickerSet stickerset;
    TLMaskCoords maskCoords;
    quint32 duration;
    QString title;
    QString performer;
    QByteArray waveform;
    QString fileName;
    TLValue tlType;
};

struct TLDraftMessage {
    TLDraftMessage() :
        flags(0),
        replyToMsgId(0),
        date(0),
        tlType(TLValue::DraftMessageEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 replyToMsgId;
    QString message;
    TLVector<TLMessageEntity> entities;
    quint32 date;
    TLValue tlType;
};

struct TLHelpConfigSimple {
    TLHelpConfigSimple() :
        date(0),
        expires(0),
        dcId(0),
        tlType(TLValue::HelpConfigSimple) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpConfigSimple:
            return true;
        default:
            return false;
        };
    }
    quint32 date;
    quint32 expires;
    quint32 dcId;
    TLVector<TLIpPort> ipPortList;
    TLValue tlType;
};

struct TLInputChatPhoto {
    TLInputChatPhoto() :
        tlType(TLValue::InputChatPhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLInputGame {
    TLInputGame() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputGameID) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputGameID:
        case TLValue::InputGameShortName:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    TLInputUser botId;
    QString shortName;
    TLValue tlType;
};

struct TLInputNotifyPeer {
    TLInputNotifyPeer() :
        tlType(TLValue::InputNotifyPeer) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLInputPaymentCredentials {
    TLInputPaymentCredentials() :
        flags(0),
        tlType(TLValue::InputPaymentCredentialsSaved) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLDataJSON data;
    TLDataJSON paymentData;
    TLDataJSON paymentToken;
    TLValue tlType;
};

struct TLInputPeerNotifySettings {
    TLInputPeerNotifySettings() :
        flags(0),
        muteUntil(0),
        tlType(TLValue::InputPeerNotifySettings) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 muteUntil;
    QString sound;
    TLValue tlType;
};

struct TLInputPrivacyRule {
    TLInputPrivacyRule() :
        tlType(TLValue::InputPrivacyValueAllowContacts) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLInputStickerSetItem {
    TLInputStickerSetItem() :
        flags(0),
        tlType(TLValue::InputStickerSetItem) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputStickerSetItem:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        MaskCoords = 1 << 0,
    };
    quint32 flags;
    TLInputDocument document;
    QString emoji;
    TLMaskCoords maskCoords;
    TLValue tlType;
};

struct TLInputWebDocument {
    TLInputWebDocument() :
        size(0),
        tlType(TLValue::InputWebDocument) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::InputWebDocument:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint32 size;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType;
};

struct TLInvoice {
    TLInvoice() :
        flags(0),
        tlType(TLValue::Invoice) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString currency;
    TLVector<TLLabeledPrice> prices;
    TLValue tlType;
};

struct TLKeyboardButton {
    TLKeyboardButton() :
        flags(0),
        tlType(TLValue::KeyboardButton) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString query;
    TLValue tlType;
};

struct TLKeyboardButtonRow {
    TLKeyboardButtonRow() :
        tlType(TLValue::KeyboardButtonRow) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::KeyboardButtonRow:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLKeyboardButton> buttons;
    TLValue tlType;
};

struct TLLangPackDifference {
    TLLangPackDifference() :
        fromVersion(0),
        version(0),
        tlType(TLValue::LangPackDifference) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::LangPackDifference:
            return true;
        default:
            return false;
        };
    }
    QString langCode;
    quint32 fromVersion;
    quint32 version;
    TLVector<TLLangPackString> strings;
    TLValue tlType;
};

struct TLMessagesBotCallbackAnswer {
    TLMessagesBotCallbackAnswer() :
        flags(0),
        cacheTime(0),
        tlType(TLValue::MessagesBotCallbackAnswer) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString message;
    QString url;
    quint32 cacheTime;
    TLValue tlType;
};

struct TLMessagesFilter {
    TLMessagesFilter() :
        flags(0),
        tlType(TLValue::InputMessagesFilterEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLValue tlType;
};

struct TLMessagesMessageEditData {
    TLMessagesMessageEditData() :
        flags(0),
        tlType(TLValue::MessagesMessageEditData) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLValue tlType;
};

struct TLNotifyPeer {
    TLNotifyPeer() :
        tlType(TLValue::NotifyPeer) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLPaymentRequestedInfo {
    TLPaymentRequestedInfo() :
        flags(0),
        tlType(TLValue::PaymentRequestedInfo) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString name;
    QString phone;
    QString email;
    TLPostAddress shippingAddress;
    TLValue tlType;
};

struct TLPaymentsSavedInfo {
    TLPaymentsSavedInfo() :
        flags(0),
        tlType(TLValue::PaymentsSavedInfo) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLPaymentRequestedInfo savedInfo;
    TLValue tlType;
};

struct TLPaymentsValidatedRequestedInfo {
    TLPaymentsValidatedRequestedInfo() :
        flags(0),
        tlType(TLValue::PaymentsValidatedRequestedInfo) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString id;
    TLVector<TLShippingOption> shippingOptions;
    TLValue tlType;
};

struct TLPeerNotifySettings {
    TLPeerNotifySettings() :
        flags(0),
        muteUntil(0),
        tlType(TLValue::PeerNotifySettingsEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 muteUntil;
    QString sound;
    TLValue tlType;
};

struct TLPeerSettings {
    TLPeerSettings() :
        flags(0),
        tlType(TLValue::PeerSettings) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLValue tlType;
};

struct TLPhoneCallProtocol {
    TLPhoneCallProtocol() :
        flags(0),
        minLayer(0),
        maxLayer(0),
        tlType(TLValue::PhoneCallProtocol) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 minLayer;
    quint32 maxLayer;
    TLValue tlType;
};

struct TLPhoto {
    TLPhoto() :
        id(0),
        flags(0),
        accessHash(0),
        date(0),
        tlType(TLValue::PhotoEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint64 id;
    quint32 flags;
    quint64 accessHash;
    quint32 date;
    TLVector<TLPhotoSize> sizes;
    TLValue tlType;
};

struct TLReplyMarkup {
    TLReplyMarkup() :
        flags(0),
        tlType(TLValue::ReplyKeyboardHide) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLVector<TLKeyboardButtonRow> rows;
    TLValue tlType;
};

struct TLStickerSet {
    TLStickerSet() :
        flags(0),
        id(0),
        accessHash(0),
        count(0),
        hash(0),
        tlType(TLValue::StickerSet) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint64 id;
    quint64 accessHash;
    QString title;
    QString shortName;
    quint32 count;
    quint32 hash;
    TLValue tlType;
};

struct TLUser {
    TLUser() :
        id(0),
        flags(0),
        accessHash(0),
        botInfoVersion(0),
        tlType(TLValue::UserEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 id;
    quint32 flags;
    quint64 accessHash;
    QString firstName;
    QString lastName;
    QString username;
    QString phone;
    TLUserProfilePhoto photo;
    TLUserStatus status;
    quint32 botInfoVersion;
    QString restrictionReason;
    QString botInlinePlaceholder;
    QString langCode;
    TLValue tlType;
};

struct TLWebDocument {
    TLWebDocument() :
        accessHash(0),
        size(0),
        dcId(0),
        tlType(TLValue::WebDocument) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::WebDocument:
            return true;
        default:
            return false;
        };
    }
    QString url;
    quint64 accessHash;
    quint32 size;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
    quint32 dcId;
    TLValue tlType;
};

struct TLAccountPrivacyRules {
    TLAccountPrivacyRules() :
        tlType(TLValue::AccountPrivacyRules) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AccountPrivacyRules:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPrivacyRule> rules;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLAuthAuthorization {
    TLAuthAuthorization() :
        flags(0),
        tmpSessions(0),
        tlType(TLValue::AuthAuthorization) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::AuthAuthorization:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        TmpSessions = 1 << 0,
    };
    quint32 flags;
    quint32 tmpSessions;
    TLUser user;
    TLValue tlType;
};

struct TLBotInlineMessage {
    TLBotInlineMessage() :
        flags(0),
        period(0),
        tlType(TLValue::BotInlineMessageMediaAuto) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString caption;
    TLReplyMarkup replyMarkup;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLGeoPoint geo;
    quint32 period;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    TLValue tlType;
};

struct TLChannelsChannelParticipant {
    TLChannelsChannelParticipant() :
        tlType(TLValue::ChannelsChannelParticipant) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelsChannelParticipant:
            return true;
        default:
            return false;
        };
    }
    TLChannelParticipant participant;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLChannelsChannelParticipants {
    TLChannelsChannelParticipants() :
        count(0),
        tlType(TLValue::ChannelsChannelParticipants) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelsChannelParticipants:
        case TLValue::ChannelsChannelParticipantsNotModified:
            return true;
        default:
            return false;
        };
    }
    quint32 count;
    TLVector<TLChannelParticipant> participants;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLChat {
    TLChat() :
        id(0),
        flags(0),
        participantsCount(0),
        date(0),
        version(0),
        accessHash(0),
        untilDate(0),
        tlType(TLValue::ChatEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 id;
    quint32 flags;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount;
    quint32 date;
    quint32 version;
    TLInputChannel migratedTo;
    quint64 accessHash;
    QString username;
    QString restrictionReason;
    TLChannelAdminRights adminRights;
    TLChannelBannedRights bannedRights;
    quint32 untilDate;
    TLValue tlType;
};

struct TLChatFull {
    TLChatFull() :
        id(0),
        flags(0),
        participantsCount(0),
        adminsCount(0),
        kickedCount(0),
        bannedCount(0),
        readInboxMaxId(0),
        readOutboxMaxId(0),
        unreadCount(0),
        migratedFromChatId(0),
        migratedFromMaxId(0),
        pinnedMsgId(0),
        availableMinId(0),
        tlType(TLValue::ChatFull) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 id;
    TLChatParticipants participants;
    TLPhoto chatPhoto;
    TLPeerNotifySettings notifySettings;
    TLExportedChatInvite exportedInvite;
    TLVector<TLBotInfo> botInfo;
    quint32 flags;
    QString about;
    quint32 participantsCount;
    quint32 adminsCount;
    quint32 kickedCount;
    quint32 bannedCount;
    quint32 readInboxMaxId;
    quint32 readOutboxMaxId;
    quint32 unreadCount;
    quint32 migratedFromChatId;
    quint32 migratedFromMaxId;
    quint32 pinnedMsgId;
    TLStickerSet stickerset;
    quint32 availableMinId;
    TLValue tlType;
};

struct TLChatInvite {
    TLChatInvite() :
        flags(0),
        participantsCount(0),
        tlType(TLValue::ChatInviteAlready) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount;
    TLVector<TLUser> participants;
    TLValue tlType;
};

struct TLConfig {
    TLConfig() :
        flags(0),
        date(0),
        expires(0),
        testMode(false),
        thisDc(0),
        chatSizeMax(0),
        megagroupSizeMax(0),
        forwardedCountMax(0),
        onlineUpdatePeriodMs(0),
        offlineBlurTimeoutMs(0),
        offlineIdleTimeoutMs(0),
        onlineCloudTimeoutMs(0),
        notifyCloudDelayMs(0),
        notifyDefaultDelayMs(0),
        chatBigSize(0),
        pushChatPeriodMs(0),
        pushChatLimit(0),
        savedGifsLimit(0),
        editTimeLimit(0),
        ratingEDecay(0),
        stickersRecentLimit(0),
        stickersFavedLimit(0),
        channelsReadMediaPeriod(0),
        tmpSessions(0),
        pinnedDialogsCountMax(0),
        callReceiveTimeoutMs(0),
        callRingTimeoutMs(0),
        callConnectTimeoutMs(0),
        callPacketTimeoutMs(0),
        langPackVersion(0),
        tlType(TLValue::Config) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 date;
    quint32 expires;
    bool testMode;
    quint32 thisDc;
    TLVector<TLDcOption> dcOptions;
    quint32 chatSizeMax;
    quint32 megagroupSizeMax;
    quint32 forwardedCountMax;
    quint32 onlineUpdatePeriodMs;
    quint32 offlineBlurTimeoutMs;
    quint32 offlineIdleTimeoutMs;
    quint32 onlineCloudTimeoutMs;
    quint32 notifyCloudDelayMs;
    quint32 notifyDefaultDelayMs;
    quint32 chatBigSize;
    quint32 pushChatPeriodMs;
    quint32 pushChatLimit;
    quint32 savedGifsLimit;
    quint32 editTimeLimit;
    quint32 ratingEDecay;
    quint32 stickersRecentLimit;
    quint32 stickersFavedLimit;
    quint32 channelsReadMediaPeriod;
    quint32 tmpSessions;
    quint32 pinnedDialogsCountMax;
    quint32 callReceiveTimeoutMs;
    quint32 callRingTimeoutMs;
    quint32 callConnectTimeoutMs;
    quint32 callPacketTimeoutMs;
    QString meUrlPrefix;
    QString suggestedLangCode;
    quint32 langPackVersion;
    TLVector<TLDisabledFeature> disabledFeatures;
    TLValue tlType;
};

struct TLContactsBlocked {
    TLContactsBlocked() :
        count(0),
        tlType(TLValue::ContactsBlocked) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsBlocked:
        case TLValue::ContactsBlockedSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContactBlocked> blocked;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLContactsContacts {
    TLContactsContacts() :
        savedCount(0),
        tlType(TLValue::ContactsContactsNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsContactsNotModified:
        case TLValue::ContactsContacts:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLContact> contacts;
    quint32 savedCount;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsFound {
    TLContactsFound() :
        tlType(TLValue::ContactsFound) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsFound:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPeer> results;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsImportedContacts {
    TLContactsImportedContacts() :
        tlType(TLValue::ContactsImportedContacts) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLContactsLink {
    TLContactsLink() :
        tlType(TLValue::ContactsLink) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsLink:
            return true;
        default:
            return false;
        };
    }
    TLContactLink myLink;
    TLContactLink foreignLink;
    TLUser user;
    TLValue tlType;
};

struct TLContactsResolvedPeer {
    TLContactsResolvedPeer() :
        tlType(TLValue::ContactsResolvedPeer) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ContactsResolvedPeer:
            return true;
        default:
            return false;
        };
    }
    TLPeer peer;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsTopPeers {
    TLContactsTopPeers() :
        tlType(TLValue::ContactsTopPeersNotModified) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLDialog {
    TLDialog() :
        flags(0),
        topMessage(0),
        readInboxMaxId(0),
        readOutboxMaxId(0),
        unreadCount(0),
        unreadMentionsCount(0),
        pts(0),
        tlType(TLValue::Dialog) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLPeer peer;
    quint32 topMessage;
    quint32 readInboxMaxId;
    quint32 readOutboxMaxId;
    quint32 unreadCount;
    quint32 unreadMentionsCount;
    TLPeerNotifySettings notifySettings;
    quint32 pts;
    TLDraftMessage draft;
    TLValue tlType;
};

struct TLDocument {
    TLDocument() :
        id(0),
        accessHash(0),
        date(0),
        size(0),
        dcId(0),
        version(0),
        tlType(TLValue::DocumentEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::DocumentEmpty:
        case TLValue::Document:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint64 accessHash;
    quint32 date;
    QString mimeType;
    quint32 size;
    TLPhotoSize thumb;
    quint32 dcId;
    quint32 version;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType;
};

struct TLFoundGif {
    TLFoundGif() :
        w(0),
        h(0),
        tlType(TLValue::FoundGif) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 w;
    quint32 h;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType;
};

struct TLGame {
    TLGame() :
        flags(0),
        id(0),
        accessHash(0),
        tlType(TLValue::Game) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::Game:
            return true;
        default:
            return false;
        };
    }
    enum Flags {
        Document = 1 << 0,
    };
    quint32 flags;
    quint64 id;
    quint64 accessHash;
    QString shortName;
    QString title;
    QString description;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType;
};

struct TLHelpSupport {
    TLHelpSupport() :
        tlType(TLValue::HelpSupport) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpSupport:
            return true;
        default:
            return false;
        };
    }
    QString phoneNumber;
    TLUser user;
    TLValue tlType;
};

struct TLInputBotInlineMessage {
    TLInputBotInlineMessage() :
        flags(0),
        period(0),
        tlType(TLValue::InputBotInlineMessageMediaAuto) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString caption;
    TLReplyMarkup replyMarkup;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLInputGeoPoint geoPoint;
    quint32 period;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    TLValue tlType;
};

struct TLInputBotInlineResult {
    TLInputBotInlineResult() :
        flags(0),
        w(0),
        h(0),
        duration(0),
        tlType(TLValue::InputBotInlineResult) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w;
    quint32 h;
    quint32 duration;
    TLInputBotInlineMessage sendMessage;
    TLInputPhoto photo;
    TLInputDocument document;
    QString shortName;
    TLValue tlType;
};

struct TLInputMedia {
    TLInputMedia() :
        flags(0),
        ttlSeconds(0),
        period(0),
        tlType(TLValue::InputMediaEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLInputFile file;
    QString caption;
    TLVector<TLInputDocument> stickers;
    quint32 ttlSeconds;
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
    quint32 period;
    TLValue tlType;
};

struct TLMessageAction {
    TLMessageAction() :
        userId(0),
        inviterId(0),
        channelId(0),
        chatId(0),
        gameId(0),
        score(0),
        flags(0),
        totalAmount(0),
        callId(0),
        duration(0),
        tlType(TLValue::MessageActionEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 userId;
    quint32 inviterId;
    quint32 channelId;
    quint32 chatId;
    quint64 gameId;
    quint32 score;
    quint32 flags;
    QString currency;
    quint64 totalAmount;
    QByteArray payload;
    TLPaymentRequestedInfo info;
    QString shippingOptionId;
    TLPaymentCharge charge;
    quint64 callId;
    TLPhoneCallDiscardReason reason;
    quint32 duration;
    QString message;
    TLValue tlType;
};

struct TLMessagesAllStickers {
    TLMessagesAllStickers() :
        hash(0),
        tlType(TLValue::MessagesAllStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesAllStickersNotModified:
        case TLValue::MessagesAllStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLStickerSet> sets;
    TLValue tlType;
};

struct TLMessagesChatFull {
    TLMessagesChatFull() :
        tlType(TLValue::MessagesChatFull) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesChatFull:
            return true;
        default:
            return false;
        };
    }
    TLChatFull fullChat;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesChats {
    TLMessagesChats() :
        count(0),
        tlType(TLValue::MessagesChats) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesChats:
        case TLValue::MessagesChatsSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLChat> chats;
    quint32 count;
    TLValue tlType;
};

struct TLMessagesFavedStickers {
    TLMessagesFavedStickers() :
        hash(0),
        tlType(TLValue::MessagesFavedStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesFavedStickersNotModified:
        case TLValue::MessagesFavedStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> stickers;
    TLValue tlType;
};

struct TLMessagesFoundGifs {
    TLMessagesFoundGifs() :
        nextOffset(0),
        tlType(TLValue::MessagesFoundGifs) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesFoundGifs:
            return true;
        default:
            return false;
        };
    }
    quint32 nextOffset;
    TLVector<TLFoundGif> results;
    TLValue tlType;
};

struct TLMessagesHighScores {
    TLMessagesHighScores() :
        tlType(TLValue::MessagesHighScores) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesHighScores:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLHighScore> scores;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesRecentStickers {
    TLMessagesRecentStickers() :
        hash(0),
        tlType(TLValue::MessagesRecentStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesRecentStickersNotModified:
        case TLValue::MessagesRecentStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLDocument> stickers;
    TLValue tlType;
};

struct TLMessagesSavedGifs {
    TLMessagesSavedGifs() :
        hash(0),
        tlType(TLValue::MessagesSavedGifsNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesSavedGifsNotModified:
        case TLValue::MessagesSavedGifs:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLDocument> gifs;
    TLValue tlType;
};

struct TLMessagesStickerSet {
    TLMessagesStickerSet() :
        tlType(TLValue::MessagesStickerSet) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesStickerSet:
            return true;
        default:
            return false;
        };
    }
    TLStickerSet set;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> documents;
    TLValue tlType;
};

struct TLMessagesStickers {
    TLMessagesStickers() :
        tlType(TLValue::MessagesStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesStickersNotModified:
        case TLValue::MessagesStickers:
            return true;
        default:
            return false;
        };
    }
    QString hash;
    TLVector<TLDocument> stickers;
    TLValue tlType;
};

struct TLPageBlock {
    TLPageBlock() :
        publishedDate(0),
        ordered(false),
        photoId(0),
        flags(0),
        videoId(0),
        posterPhotoId(0),
        w(0),
        h(0),
        webpageId(0),
        authorPhotoId(0),
        date(0),
        audioId(0),
        tlType(TLValue::PageBlockUnsupported) { }

    bool isValid() const {
        switch (tlType) {
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
    TLRichText *text;
    TLRichText *richTextAuthor;
    quint32 publishedDate;
    QString language;
    QString name;
    bool ordered;
    TLVector<TLRichText*> richTextItemsVector;
    TLRichText *caption;
    quint64 photoId;
    quint32 flags;
    quint64 videoId;
    TLPageBlock *cover;
    QString url;
    QString html;
    quint64 posterPhotoId;
    quint32 w;
    quint32 h;
    quint64 webpageId;
    quint64 authorPhotoId;
    QString stringAuthor;
    quint32 date;
    TLVector<TLPageBlock*> blocks;
    TLVector<TLPageBlock*> pageBlockItemsVector;
    TLChat channel;
    quint64 audioId;
    TLValue tlType;
};

struct TLPaymentsPaymentForm {
    TLPaymentsPaymentForm() :
        flags(0),
        botId(0),
        providerId(0),
        tlType(TLValue::PaymentsPaymentForm) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 botId;
    TLInvoice invoice;
    quint32 providerId;
    QString url;
    QString nativeProvider;
    TLDataJSON nativeParams;
    TLPaymentRequestedInfo savedInfo;
    TLPaymentSavedCredentials savedCredentials;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPaymentsPaymentReceipt {
    TLPaymentsPaymentReceipt() :
        flags(0),
        date(0),
        botId(0),
        providerId(0),
        totalAmount(0),
        tlType(TLValue::PaymentsPaymentReceipt) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 date;
    quint32 botId;
    TLInvoice invoice;
    quint32 providerId;
    TLPaymentRequestedInfo info;
    TLShippingOption shipping;
    QString currency;
    quint64 totalAmount;
    QString credentialsTitle;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPhoneCall {
    TLPhoneCall() :
        id(0),
        flags(0),
        accessHash(0),
        date(0),
        adminId(0),
        participantId(0),
        receiveDate(0),
        keyFingerprint(0),
        startDate(0),
        duration(0),
        tlType(TLValue::PhoneCallEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint64 id;
    quint32 flags;
    quint64 accessHash;
    quint32 date;
    quint32 adminId;
    quint32 participantId;
    TLPhoneCallProtocol protocol;
    quint32 receiveDate;
    QByteArray gAHash;
    QByteArray gB;
    QByteArray gAOrB;
    quint64 keyFingerprint;
    TLPhoneConnection connection;
    TLVector<TLPhoneConnection> alternativeConnections;
    quint32 startDate;
    TLPhoneCallDiscardReason reason;
    quint32 duration;
    TLValue tlType;
};

struct TLPhonePhoneCall {
    TLPhonePhoneCall() :
        tlType(TLValue::PhonePhoneCall) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhonePhoneCall:
            return true;
        default:
            return false;
        };
    }
    TLPhoneCall phoneCall;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPhotosPhoto {
    TLPhotosPhoto() :
        tlType(TLValue::PhotosPhoto) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhotosPhoto:
            return true;
        default:
            return false;
        };
    }
    TLPhoto photo;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPhotosPhotos {
    TLPhotosPhotos() :
        count(0),
        tlType(TLValue::PhotosPhotos) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PhotosPhotos:
        case TLValue::PhotosPhotosSlice:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLPhoto> photos;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLStickerSetCovered {
    TLStickerSetCovered() :
        tlType(TLValue::StickerSetCovered) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLUserFull {
    TLUserFull() :
        flags(0),
        commonChatsCount(0),
        tlType(TLValue::UserFull) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLUser user;
    QString about;
    TLContactsLink link;
    TLPhoto profilePhoto;
    TLPeerNotifySettings notifySettings;
    TLBotInfo botInfo;
    quint32 commonChatsCount;
    TLValue tlType;
};

struct TLBotInlineResult {
    TLBotInlineResult() :
        flags(0),
        w(0),
        h(0),
        duration(0),
        tlType(TLValue::BotInlineResult) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    QString thumbUrl;
    QString contentUrl;
    QString contentType;
    quint32 w;
    quint32 h;
    quint32 duration;
    TLBotInlineMessage sendMessage;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType;
};

struct TLMessagesArchivedStickers {
    TLMessagesArchivedStickers() :
        count(0),
        tlType(TLValue::MessagesArchivedStickers) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesArchivedStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 count;
    TLVector<TLStickerSetCovered> sets;
    TLValue tlType;
};

struct TLMessagesBotResults {
    TLMessagesBotResults() :
        flags(0),
        queryId(0),
        cacheTime(0),
        tlType(TLValue::MessagesBotResults) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint64 queryId;
    QString nextOffset;
    TLInlineBotSwitchPM switchPm;
    TLVector<TLBotInlineResult> results;
    quint32 cacheTime;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesFeaturedStickers {
    TLMessagesFeaturedStickers() :
        hash(0),
        tlType(TLValue::MessagesFeaturedStickersNotModified) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesFeaturedStickersNotModified:
        case TLValue::MessagesFeaturedStickers:
            return true;
        default:
            return false;
        };
    }
    quint32 hash;
    TLVector<TLStickerSetCovered> sets;
    TLVector<quint64> unread;
    TLValue tlType;
};

struct TLMessagesStickerSetInstallResult {
    TLMessagesStickerSetInstallResult() :
        tlType(TLValue::MessagesStickerSetInstallResultSuccess) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::MessagesStickerSetInstallResultSuccess:
        case TLValue::MessagesStickerSetInstallResultArchive:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLStickerSetCovered> sets;
    TLValue tlType;
};

struct TLPage {
    TLPage() :
        tlType(TLValue::PagePart) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLRecentMeUrl {
    TLRecentMeUrl() :
        userId(0),
        chatId(0),
        tlType(TLValue::RecentMeUrlUnknown) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 userId;
    quint32 chatId;
    TLChatInvite chatInvite;
    TLStickerSetCovered set;
    TLValue tlType;
};

struct TLWebPage {
    TLWebPage() :
        id(0),
        date(0),
        flags(0),
        hash(0),
        embedWidth(0),
        embedHeight(0),
        duration(0),
        tlType(TLValue::WebPageEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint64 id;
    quint32 date;
    quint32 flags;
    QString url;
    QString displayUrl;
    quint32 hash;
    QString type;
    QString siteName;
    QString title;
    QString description;
    TLPhoto photo;
    QString embedUrl;
    QString embedType;
    quint32 embedWidth;
    quint32 embedHeight;
    quint32 duration;
    QString author;
    TLDocument document;
    TLPage cachedPage;
    TLValue tlType;
};

struct TLHelpRecentMeUrls {
    TLHelpRecentMeUrls() :
        tlType(TLValue::HelpRecentMeUrls) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::HelpRecentMeUrls:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLRecentMeUrl> urls;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessageMedia {
    TLMessageMedia() :
        flags(0),
        ttlSeconds(0),
        userId(0),
        receiptMsgId(0),
        totalAmount(0),
        period(0),
        tlType(TLValue::MessageMediaEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    TLPhoto photo;
    QString caption;
    quint32 ttlSeconds;
    TLGeoPoint geo;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 userId;
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
    quint32 receiptMsgId;
    QString currency;
    quint64 totalAmount;
    QString startParam;
    quint32 period;
    TLValue tlType;
};

struct TLMessage {
    TLMessage() :
        id(0),
        flags(0),
        fromId(0),
        viaBotId(0),
        replyToMsgId(0),
        date(0),
        views(0),
        editDate(0),
        tlType(TLValue::MessageEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 id;
    quint32 flags;
    quint32 fromId;
    TLPeer toId;
    TLMessageFwdHeader fwdFrom;
    quint32 viaBotId;
    quint32 replyToMsgId;
    quint32 date;
    QString message;
    TLMessageMedia media;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
    quint32 views;
    quint32 editDate;
    QString postAuthor;
    TLMessageAction action;
    TLValue tlType;
};

struct TLMessagesDialogs {
    TLMessagesDialogs() :
        count(0),
        tlType(TLValue::MessagesDialogs) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 count;
    TLValue tlType;
};

struct TLMessagesMessages {
    TLMessagesMessages() :
        count(0),
        flags(0),
        pts(0),
        tlType(TLValue::MessagesMessages) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 count;
    quint32 flags;
    quint32 pts;
    TLValue tlType;
};

struct TLMessagesPeerDialogs {
    TLMessagesPeerDialogs() :
        tlType(TLValue::MessagesPeerDialogs) { }

    bool isValid() const {
        switch (tlType) {
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
    TLValue tlType;
};

struct TLUpdate {
    TLUpdate() :
        pts(0),
        ptsCount(0),
        quint32Id(0),
        randomId(0),
        userId(0),
        chatId(0),
        date(0),
        previous(false),
        qts(0),
        maxDate(0),
        inviterId(0),
        version(0),
        blocked(false),
        flags(0),
        inboxDate(0),
        maxId(0),
        channelId(0),
        views(0),
        enabled(false),
        isAdmin(false),
        queryId(0),
        quint32MsgId(0),
        chatInstance(0),
        timeout(0),
        totalAmount(0),
        availableMinId(0),
        tlType(TLValue::UpdateNewMessage) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 pts;
    quint32 ptsCount;
    quint32 quint32Id;
    quint64 randomId;
    TLVector<quint32> messages;
    quint32 userId;
    TLSendMessageAction action;
    quint32 chatId;
    TLChatParticipants participants;
    TLUserStatus status;
    QString firstName;
    QString lastName;
    QString username;
    quint32 date;
    TLUserProfilePhoto photo;
    bool previous;
    TLContactLink myLink;
    TLContactLink foreignLink;
    TLEncryptedMessage encryptedMessage;
    quint32 qts;
    TLEncryptedChat chat;
    quint32 maxDate;
    quint32 inviterId;
    quint32 version;
    TLVector<TLDcOption> dcOptions;
    bool blocked;
    TLNotifyPeer notifyPeer;
    TLPeerNotifySettings notifySettings;
    quint32 flags;
    quint32 inboxDate;
    QString type;
    QString stringMessage;
    TLMessageMedia media;
    TLVector<TLMessageEntity> entities;
    TLPrivacyKey key;
    TLVector<TLPrivacyRule> rules;
    QString phone;
    TLPeer peer;
    quint32 maxId;
    TLWebPage webpage;
    quint32 channelId;
    quint32 views;
    bool enabled;
    bool isAdmin;
    TLMessagesStickerSet stickerset;
    TLVector<quint64> quint64OrderVector;
    quint64 queryId;
    QString query;
    TLGeoPoint geo;
    QString offset;
    QString stringId;
    TLInputBotInlineMessageID inputBotInlineMessageIDMsgId;
    quint32 quint32MsgId;
    quint64 chatInstance;
    QByteArray byteArrayData;
    QString gameShortName;
    TLDraftMessage draft;
    TLVector<TLPeer> peerOrderVector;
    TLDataJSON jSONData;
    quint32 timeout;
    QByteArray payload;
    TLPostAddress shippingAddress;
    TLPaymentRequestedInfo info;
    QString shippingOptionId;
    QString currency;
    quint64 totalAmount;
    TLPhoneCall phoneCall;
    TLLangPackDifference difference;
    quint32 availableMinId;
    TLValue tlType;
};

struct TLUpdates {
    TLUpdates() :
        flags(0),
        id(0),
        userId(0),
        pts(0),
        ptsCount(0),
        date(0),
        viaBotId(0),
        replyToMsgId(0),
        fromId(0),
        chatId(0),
        seqStart(0),
        seq(0),
        tlType(TLValue::UpdatesTooLong) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 id;
    quint32 userId;
    QString message;
    quint32 pts;
    quint32 ptsCount;
    quint32 date;
    TLMessageFwdHeader fwdFrom;
    quint32 viaBotId;
    quint32 replyToMsgId;
    TLVector<TLMessageEntity> entities;
    quint32 fromId;
    quint32 chatId;
    TLUpdate update;
    TLVector<TLUpdate> updates;
    TLVector<TLUser> users;
    TLVector<TLChat> chats;
    quint32 seqStart;
    quint32 seq;
    TLMessageMedia media;
    TLValue tlType;
};

struct TLUpdatesChannelDifference {
    TLUpdatesChannelDifference() :
        flags(0),
        pts(0),
        timeout(0),
        topMessage(0),
        readInboxMaxId(0),
        readOutboxMaxId(0),
        unreadCount(0),
        unreadMentionsCount(0),
        tlType(TLValue::UpdatesChannelDifferenceEmpty) { }

    bool isValid() const {
        switch (tlType) {
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
    quint32 flags;
    quint32 pts;
    quint32 timeout;
    quint32 topMessage;
    quint32 readInboxMaxId;
    quint32 readOutboxMaxId;
    quint32 unreadCount;
    quint32 unreadMentionsCount;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLVector<TLMessage> newMessages;
    TLVector<TLUpdate> otherUpdates;
    TLValue tlType;
};

struct TLUpdatesDifference {
    TLUpdatesDifference() :
        date(0),
        seq(0),
        pts(0),
        tlType(TLValue::UpdatesDifferenceEmpty) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::UpdatesDifferenceEmpty:
        case TLValue::UpdatesDifference:
        case TLValue::UpdatesDifferenceSlice:
        case TLValue::UpdatesDifferenceTooLong:
            return true;
        default:
            return false;
        };
    }
    quint32 date;
    quint32 seq;
    TLVector<TLMessage> newMessages;
    TLVector<TLEncryptedMessage> newEncryptedMessages;
    TLVector<TLUpdate> otherUpdates;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLUpdatesState state;
    TLUpdatesState intermediateState;
    quint32 pts;
    TLValue tlType;
};

struct TLChannelAdminLogEventAction {
    TLChannelAdminLogEventAction() :
        boolNewValue(false),
        tlType(TLValue::ChannelAdminLogEventActionChangeTitle) { }

    bool isValid() const {
        switch (tlType) {
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
    bool boolNewValue;
    TLMessage message;
    TLMessage prevMessage;
    TLMessage newMessage;
    TLChannelParticipant participant;
    TLChannelParticipant prevParticipant;
    TLChannelParticipant newParticipant;
    TLInputStickerSet prevStickerset;
    TLInputStickerSet newStickerset;
    TLValue tlType;
};

struct TLPaymentsPaymentResult {
    TLPaymentsPaymentResult() :
        tlType(TLValue::PaymentsPaymentResult) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::PaymentsPaymentResult:
        case TLValue::PaymentsPaymentVerficationNeeded:
            return true;
        default:
            return false;
        };
    }
    TLUpdates updates;
    QString url;
    TLValue tlType;
};

struct TLChannelAdminLogEvent {
    TLChannelAdminLogEvent() :
        id(0),
        date(0),
        userId(0),
        tlType(TLValue::ChannelAdminLogEvent) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelAdminLogEvent:
            return true;
        default:
            return false;
        };
    }
    quint64 id;
    quint32 date;
    quint32 userId;
    TLChannelAdminLogEventAction action;
    TLValue tlType;
};

struct TLChannelsAdminLogResults {
    TLChannelsAdminLogResults() :
        tlType(TLValue::ChannelsAdminLogResults) { }

    bool isValid() const {
        switch (tlType) {
        case TLValue::ChannelsAdminLogResults:
            return true;
        default:
            return false;
        };
    }
    TLVector<TLChannelAdminLogEvent> events;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};
// End of generated TLTypes

Q_DECLARE_METATYPE(TLUploadFile)
Q_DECLARE_METATYPE(QVector<TLUser>)
Q_DECLARE_METATYPE(TLUpdates)

#endif // TLTYPES_HPP
