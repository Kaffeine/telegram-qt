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

struct TLBool
{
    constexpr TLBool() = default;
    constexpr TLBool(bool b) :
        tlType(b ? TLValue::BoolTrue : TLValue::BoolFalse)
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

template <typename T>
class TELEGRAMQT_INTERNAL_EXPORT TLVector : public QVector<T>
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
struct TLJSONValue;
struct TLRichText;
struct TLSecureRequiredType;
struct TLPageBlock;

using TLJSONValuePtr = TLPtr<TLJSONValue>;
using TLRichTextPtr = TLPtr<TLRichText>;
using TLSecureRequiredTypePtr = TLPtr<TLSecureRequiredType>;
using TLPageBlockPtr = TLPtr<TLPageBlock>;

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountDaysTTL {
    constexpr TLAccountDaysTTL() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountDaysTTL &v) const;

    quint32 days = 0;
    TLValue tlType = TLValue::AccountDaysTTL;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountSentEmailCode {
    TLAccountSentEmailCode() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountSentEmailCode &v) const;

    QString emailPattern;
    quint32 length = 0;
    TLValue tlType = TLValue::AccountSentEmailCode;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountTakeout {
    constexpr TLAccountTakeout() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountTakeout &v) const;

    quint64 id = 0;
    TLValue tlType = TLValue::AccountTakeout;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountTmpPassword {
    TLAccountTmpPassword() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountTmpPassword &v) const;

    QByteArray tmpPassword;
    quint32 validUntil = 0;
    TLValue tlType = TLValue::AccountTmpPassword;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthCheckedPhone {
    constexpr TLAuthCheckedPhone() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthCheckedPhone &v) const;

    bool phoneRegistered = false;
    TLValue tlType = TLValue::AuthCheckedPhone;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthCodeType {
    constexpr TLAuthCodeType() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthCodeType &v) const;

    TLValue tlType = TLValue::AuthCodeTypeSms;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthExportedAuthorization {
    TLAuthExportedAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthExportedAuthorization &v) const;

    quint32 id = 0;
    QByteArray bytes;
    TLValue tlType = TLValue::AuthExportedAuthorization;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthPasswordRecovery {
    TLAuthPasswordRecovery() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthPasswordRecovery &v) const;

    QString emailPattern;
    TLValue tlType = TLValue::AuthPasswordRecovery;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthSentCodeType {
    TLAuthSentCodeType() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthSentCodeType &v) const;

    quint32 length = 0;
    QString pattern;
    TLValue tlType = TLValue::AuthSentCodeTypeApp;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBadMsgNotification {
    constexpr TLBadMsgNotification() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBadMsgNotification &v) const;

    quint64 badMsgId = 0;
    quint32 badMsgSeqno = 0;
    quint32 errorCode = 0;
    quint64 newServerSalt = 0;
    TLValue tlType = TLValue::BadMsgNotification;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotCommand {
    TLBotCommand() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBotCommand &v) const;

    QString command;
    QString description;
    TLValue tlType = TLValue::BotCommand;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotInfo {
    TLBotInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLBotInfo &v) const;

    quint32 userId = 0;
    QString description;
    TLVector<TLBotCommand> commands;
    TLValue tlType = TLValue::BotInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLCdnPublicKey {
    TLCdnPublicKey() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLCdnPublicKey &v) const;

    quint32 dcId = 0;
    QString publicKey;
    TLValue tlType = TLValue::CdnPublicKey;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelParticipantsFilter {
    TLChannelParticipantsFilter() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelParticipantsFilter &v) const;

    QString q;
    TLValue tlType = TLValue::ChannelParticipantsRecent;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatOnlines {
    constexpr TLChatOnlines() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatOnlines &v) const;

    quint32 onlines = 0;
    TLValue tlType = TLValue::ChatOnlines;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatParticipant {
    constexpr TLChatParticipant() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatParticipant &v) const;

    quint32 userId = 0;
    quint32 inviterId = 0;
    quint32 date = 0;
    TLValue tlType = TLValue::ChatParticipant;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatParticipants {
    TLChatParticipants() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatParticipants &v) const;
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

struct TELEGRAMQT_INTERNAL_EXPORT TLClientDHInnerData {
    TLClientDHInnerData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLClientDHInnerData &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint64 retryId = 0;
    QString gB;
    TLValue tlType = TLValue::ClientDHInnerData;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContact {
    constexpr TLContact() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContact &v) const;

    quint32 userId = 0;
    bool mutual = false;
    TLValue tlType = TLValue::Contact;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactBlocked {
    constexpr TLContactBlocked() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactBlocked &v) const;

    quint32 userId = 0;
    quint32 date = 0;
    TLValue tlType = TLValue::ContactBlocked;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactLink {
    constexpr TLContactLink() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactLink &v) const;

    TLValue tlType = TLValue::ContactLinkUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDataJSON {
    TLDataJSON() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDataJSON &v) const;

    QString data;
    TLValue tlType = TLValue::DataJSON;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDestroyAuthKeyRes {
    constexpr TLDestroyAuthKeyRes() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDestroyAuthKeyRes &v) const;

    TLValue tlType = TLValue::DestroyAuthKeyOk;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDestroySessionRes {
    constexpr TLDestroySessionRes() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDestroySessionRes &v) const;

    quint64 sessionId = 0;
    TLValue tlType = TLValue::DestroySessionOk;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLEncryptedChat {
    TLEncryptedChat() = default;

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
    TLValue tlType = TLValue::EncryptedChatEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLEncryptedFile {
    constexpr TLEncryptedFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLEncryptedFile &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 size = 0;
    quint32 dcId = 0;
    quint32 keyFingerprint = 0;
    TLValue tlType = TLValue::EncryptedFileEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLEncryptedMessage {
    TLEncryptedMessage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLEncryptedMessage &v) const;

    quint64 randomId = 0;
    quint32 chatId = 0;
    quint32 date = 0;
    QByteArray bytes;
    TLEncryptedFile file;
    TLValue tlType = TLValue::EncryptedMessage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLError {
    TLError() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLError &v) const;

    quint32 code = 0;
    QString text;
    TLValue tlType = TLValue::Error;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLExportedChatInvite {
    TLExportedChatInvite() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLExportedChatInvite &v) const;

    QString link;
    TLValue tlType = TLValue::ChatInviteEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLExportedMessageLink {
    TLExportedMessageLink() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLExportedMessageLink &v) const;

    QString link;
    QString html;
    TLValue tlType = TLValue::ExportedMessageLink;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFileHash {
    TLFileHash() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFileHash &v) const;

    quint32 offset = 0;
    quint32 limit = 0;
    QByteArray hash;
    TLValue tlType = TLValue::FileHash;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFileLocation {
    TLFileLocation() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFileLocation &v) const;

    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    quint32 dcId = 0;
    QByteArray fileReference;
    TLValue tlType = TLValue::FileLocationUnavailable;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFutureSalt {
    constexpr TLFutureSalt() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFutureSalt &v) const;

    quint32 validSince = 0;
    quint32 validUntil = 0;
    quint64 salt = 0;
    TLValue tlType = TLValue::FutureSalt;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFutureSalts {
    TLFutureSalts() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLFutureSalts &v) const;

    quint64 reqMsgId = 0;
    quint32 now = 0;
    TLVector<TLFutureSalt> salts;
    TLValue tlType = TLValue::FutureSalts;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLGeoPoint {
    constexpr TLGeoPoint() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLGeoPoint &v) const;

    double longitude = 0;
    double latitude = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::GeoPointEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpInviteText {
    TLHelpInviteText() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpInviteText &v) const;

    QString message;
    TLValue tlType = TLValue::HelpInviteText;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpPassportConfig {
    TLHelpPassportConfig() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpPassportConfig &v) const;

    quint32 hash = 0;
    TLDataJSON countriesLangs;
    TLValue tlType = TLValue::HelpPassportConfigNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpSupportName {
    TLHelpSupportName() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpSupportName &v) const;

    QString name;
    TLValue tlType = TLValue::HelpSupportName;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHighScore {
    constexpr TLHighScore() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHighScore &v) const;

    quint32 pos = 0;
    quint32 userId = 0;
    quint32 score = 0;
    TLValue tlType = TLValue::HighScore;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHttpWait {
    constexpr TLHttpWait() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHttpWait &v) const;

    quint32 maxDelay = 0;
    quint32 waitAfter = 0;
    quint32 maxWait = 0;
    TLValue tlType = TLValue::HttpWait;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLImportedContact {
    constexpr TLImportedContact() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLImportedContact &v) const;

    quint32 userId = 0;
    quint64 clientId = 0;
    TLValue tlType = TLValue::ImportedContact;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInlineBotSwitchPM {
    TLInlineBotSwitchPM() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInlineBotSwitchPM &v) const;

    QString text;
    QString startParam;
    TLValue tlType = TLValue::InlineBotSwitchPM;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputAppEvent {
    TLInputAppEvent() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputAppEvent &v) const;

    double time = 0;
    QString type;
    quint64 peer = 0;
    TLJSONValuePtr data;
    TLValue tlType = TLValue::InputAppEvent;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputBotInlineMessageID {
    constexpr TLInputBotInlineMessageID() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputBotInlineMessageID &v) const;

    quint32 dcId = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputBotInlineMessageID;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputChannel {
    constexpr TLInputChannel() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputChannel &v) const;

    quint32 channelId = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputChannelEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputCheckPasswordSRP {
    TLInputCheckPasswordSRP() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputCheckPasswordSRP &v) const;

    quint64 srpId = 0;
    QByteArray A;
    QByteArray M1;
    TLValue tlType = TLValue::InputCheckPasswordEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputClientProxy {
    TLInputClientProxy() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputClientProxy &v) const;

    QString address;
    quint32 port = 0;
    TLValue tlType = TLValue::InputClientProxy;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputContact {
    TLInputContact() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputContact &v) const;

    quint64 clientId = 0;
    QString phone;
    QString firstName;
    QString lastName;
    TLValue tlType = TLValue::InputPhoneContact;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputDocument {
    TLInputDocument() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputDocument &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    QByteArray fileReference;
    TLValue tlType = TLValue::InputDocumentEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputEncryptedChat {
    constexpr TLInputEncryptedChat() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputEncryptedChat &v) const;

    quint32 chatId = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputEncryptedChat;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputEncryptedFile {
    TLInputEncryptedFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputEncryptedFile &v) const;

    quint64 id = 0;
    quint32 parts = 0;
    QString md5Checksum;
    quint32 keyFingerprint = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputEncryptedFileEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputFile {
    TLInputFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputFile &v) const;

    quint64 id = 0;
    quint32 parts = 0;
    QString name;
    QString md5Checksum;
    TLValue tlType = TLValue::InputFile;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputFileLocation {
    TLInputFileLocation() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputFileLocation &v) const;

    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    QByteArray fileReference;
    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputFileLocation;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputGeoPoint {
    constexpr TLInputGeoPoint() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputGeoPoint &v) const;

    double latitude = 0;
    double longitude = 0;
    TLValue tlType = TLValue::InputGeoPointEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputMessage {
    constexpr TLInputMessage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputMessage &v) const;

    quint32 id = 0;
    TLValue tlType = TLValue::InputMessageID;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPeer {
    constexpr TLInputPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPeer &v) const;

    quint32 chatId = 0;
    quint32 userId = 0;
    quint64 accessHash = 0;
    quint32 channelId = 0;
    TLValue tlType = TLValue::InputPeerEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPeerNotifySettings {
    TLInputPeerNotifySettings() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPeerNotifySettings &v) const;
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
        MuteUntil = 1 << 2,
        Sound = 1 << 3,
    };

    quint32 flags = 0;
    bool showPreviews = false;
    bool silent = false;
    quint32 muteUntil = 0;
    QString sound;
    TLValue tlType = TLValue::InputPeerNotifySettings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPhoneCall {
    constexpr TLInputPhoneCall() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPhoneCall &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputPhoneCall;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPhoto {
    TLInputPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPhoto &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    QByteArray fileReference;
    TLValue tlType = TLValue::InputPhotoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPrivacyKey {
    constexpr TLInputPrivacyKey() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPrivacyKey &v) const;

    TLValue tlType = TLValue::InputPrivacyKeyStatusTimestamp;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputSecureFile {
    TLInputSecureFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputSecureFile &v) const;

    quint64 id = 0;
    quint32 parts = 0;
    QString md5Checksum;
    QByteArray fileHash;
    QByteArray secret;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputSecureFileUploaded;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputStickerSet {
    TLInputStickerSet() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputStickerSet &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    QString shortName;
    TLValue tlType = TLValue::InputStickerSetEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputStickeredMedia {
    TLInputStickeredMedia() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputStickeredMedia &v) const;

    TLInputPhoto inputPhotoId;
    TLInputDocument inputDocumentId;
    TLValue tlType = TLValue::InputStickeredMediaPhoto;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputUser {
    constexpr TLInputUser() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputUser &v) const;

    quint32 userId = 0;
    quint64 accessHash = 0;
    TLValue tlType = TLValue::InputUserEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputWebFileLocation {
    TLInputWebFileLocation() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputWebFileLocation &v) const;

    QString url;
    quint64 accessHash = 0;
    TLInputGeoPoint geoPoint;
    quint32 w = 0;
    quint32 h = 0;
    quint32 zoom = 0;
    quint32 scale = 0;
    TLValue tlType = TLValue::InputWebFileLocation;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLIpPort {
    TLIpPort() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLIpPort &v) const;

    quint32 ipv4 = 0;
    quint32 port = 0;
    QByteArray secret;
    TLValue tlType = TLValue::IpPort;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLJSONObjectValue {
    TLJSONObjectValue() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLJSONObjectValue &v) const;

    QString key;
    TLJSONValuePtr value;
    TLValue tlType = TLValue::JsonObjectValue;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLJSONValue {
    TLJSONValue() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLJSONValue &v) const;

    bool boolValue = false;
    double doubleValue = 0;
    QString stringValue;
    TLVector<TLJSONValue*> jSONValueVector;
    TLVector<TLJSONObjectValue> jSONObjectValueVector;
    TLValue tlType = TLValue::JsonNull;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLabeledPrice {
    TLLabeledPrice() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLabeledPrice &v) const;

    QString label;
    quint64 amount = 0;
    TLValue tlType = TLValue::LabeledPrice;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLangPackString {
    TLLangPackString() = default;

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
    TLValue tlType = TLValue::LangPackString;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMaskCoords {
    constexpr TLMaskCoords() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMaskCoords &v) const;

    quint32 n = 0;
    double x = 0;
    double y = 0;
    double zoom = 0;
    TLValue tlType = TLValue::MaskCoords;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageEntity {
    TLMessageEntity() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageEntity &v) const;

    quint32 offset = 0;
    quint32 length = 0;
    QString language;
    QString url;
    quint32 userId = 0;
    TLInputUser inputUserUserId;
    TLValue tlType = TLValue::MessageEntityUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageRange {
    constexpr TLMessageRange() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageRange &v) const;

    quint32 minId = 0;
    quint32 maxId = 0;
    TLValue tlType = TLValue::MessageRange;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesAffectedHistory {
    constexpr TLMessagesAffectedHistory() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesAffectedHistory &v) const;

    quint32 pts = 0;
    quint32 ptsCount = 0;
    quint32 offset = 0;
    TLValue tlType = TLValue::MessagesAffectedHistory;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesAffectedMessages {
    constexpr TLMessagesAffectedMessages() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesAffectedMessages &v) const;

    quint32 pts = 0;
    quint32 ptsCount = 0;
    TLValue tlType = TLValue::MessagesAffectedMessages;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesDhConfig {
    TLMessagesDhConfig() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesDhConfig &v) const;

    QByteArray random;
    quint32 g = 0;
    QByteArray p;
    quint32 version = 0;
    TLValue tlType = TLValue::MessagesDhConfigNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesSentEncryptedMessage {
    TLMessagesSentEncryptedMessage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesSentEncryptedMessage &v) const;

    quint32 date = 0;
    TLEncryptedFile file;
    TLValue tlType = TLValue::MessagesSentEncryptedMessage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgDetailedInfo {
    constexpr TLMsgDetailedInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgDetailedInfo &v) const;

    quint64 msgId = 0;
    quint64 answerMsgId = 0;
    quint32 bytes = 0;
    quint32 status = 0;
    TLValue tlType = TLValue::MsgDetailedInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgResendReq {
    TLMsgResendReq() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgResendReq &v) const;

    TLVector<quint64> msgIds;
    TLValue tlType = TLValue::MsgResendReq;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsAck {
    TLMsgsAck() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsAck &v) const;

    TLVector<quint64> msgIds;
    TLValue tlType = TLValue::MsgsAck;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsAllInfo {
    TLMsgsAllInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsAllInfo &v) const;

    TLVector<quint64> msgIds;
    QString info;
    TLValue tlType = TLValue::MsgsAllInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsStateInfo {
    TLMsgsStateInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsStateInfo &v) const;

    quint64 reqMsgId = 0;
    QString info;
    TLValue tlType = TLValue::MsgsStateInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMsgsStateReq {
    TLMsgsStateReq() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMsgsStateReq &v) const;

    TLVector<quint64> msgIds;
    TLValue tlType = TLValue::MsgsStateReq;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLNearestDc {
    TLNearestDc() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLNearestDc &v) const;

    QString country;
    quint32 thisDc = 0;
    quint32 nearestDc = 0;
    TLValue tlType = TLValue::NearestDc;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLNewSession {
    constexpr TLNewSession() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLNewSession &v) const;

    quint64 firstMsgId = 0;
    quint64 uniqueId = 0;
    quint64 serverSalt = 0;
    TLValue tlType = TLValue::NewSessionCreated;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPQInnerData {
    TLPQInnerData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPQInnerData &v) const;

    QString pq;
    QString p;
    QString q;
    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber256 newNonce;
    quint32 dc = 0;
    quint32 expiresIn = 0;
    TLValue tlType = TLValue::PQInnerData;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageCaption {
    TLPageCaption() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageCaption &v) const;

    TLRichTextPtr text;
    TLRichTextPtr credit;
    TLValue tlType = TLValue::PageCaption;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageListItem {
    TLPageListItem() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageListItem &v) const;

    TLRichTextPtr text;
    TLVector<TLPageBlock*> blocks;
    TLValue tlType = TLValue::PageListItemText;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageListOrderedItem {
    TLPageListOrderedItem() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageListOrderedItem &v) const;

    QString num;
    TLRichTextPtr text;
    TLVector<TLPageBlock*> blocks;
    TLValue tlType = TLValue::PageListOrderedItemText;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageRelatedArticle {
    TLPageRelatedArticle() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageRelatedArticle &v) const;
    enum Flags {
        Title = 1 << 0,
        Description = 1 << 1,
        PhotoId = 1 << 2,
        Author = 1 << 3,
        PublishedDate = 1 << 4,
    };

    quint32 flags = 0;
    QString url;
    quint64 webpageId = 0;
    QString title;
    QString description;
    quint64 photoId = 0;
    QString author;
    quint32 publishedDate = 0;
    TLValue tlType = TLValue::PageRelatedArticle;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPasswordKdfAlgo {
    TLPasswordKdfAlgo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPasswordKdfAlgo &v) const;

    QByteArray salt1;
    QByteArray salt2;
    quint32 g = 0;
    QByteArray p;
    TLValue tlType = TLValue::PasswordKdfAlgoUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentCharge {
    TLPaymentCharge() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentCharge &v) const;

    QString id;
    QString providerChargeId;
    TLValue tlType = TLValue::PaymentCharge;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentSavedCredentials {
    TLPaymentSavedCredentials() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentSavedCredentials &v) const;

    QString id;
    QString title;
    TLValue tlType = TLValue::PaymentSavedCredentialsCard;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeer {
    constexpr TLPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeer &v) const;

    quint32 userId = 0;
    quint32 chatId = 0;
    quint32 channelId = 0;
    TLValue tlType = TLValue::PeerUser;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeerNotifySettings {
    TLPeerNotifySettings() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeerNotifySettings &v) const;
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
        MuteUntil = 1 << 2,
        Sound = 1 << 3,
    };

    quint32 flags = 0;
    bool showPreviews = false;
    bool silent = false;
    quint32 muteUntil = 0;
    QString sound;
    TLValue tlType = TLValue::PeerNotifySettings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneCallDiscardReason {
    constexpr TLPhoneCallDiscardReason() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneCallDiscardReason &v) const;

    TLValue tlType = TLValue::PhoneCallDiscardReasonMissed;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneConnection {
    TLPhoneConnection() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneConnection &v) const;

    quint64 id = 0;
    QString ip;
    QString ipv6;
    quint32 port = 0;
    QByteArray peerTag;
    TLValue tlType = TLValue::PhoneConnection;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhotoSize {
    TLPhotoSize() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhotoSize &v) const;

    QString type;
    TLFileLocation location;
    quint32 w = 0;
    quint32 h = 0;
    quint32 size = 0;
    QByteArray bytes;
    TLValue tlType = TLValue::PhotoSizeEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPollAnswer {
    TLPollAnswer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPollAnswer &v) const;

    QString text;
    QByteArray option;
    TLValue tlType = TLValue::PollAnswer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPong {
    constexpr TLPong() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPong &v) const;

    quint64 msgId = 0;
    quint64 pingId = 0;
    TLValue tlType = TLValue::Pong;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPopularContact {
    constexpr TLPopularContact() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPopularContact &v) const;

    quint64 clientId = 0;
    quint32 importers = 0;
    TLValue tlType = TLValue::PopularContact;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPostAddress {
    TLPostAddress() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPostAddress &v) const;

    QString streetLine1;
    QString streetLine2;
    QString city;
    QString state;
    QString countryIso2;
    QString postCode;
    TLValue tlType = TLValue::PostAddress;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPrivacyKey {
    constexpr TLPrivacyKey() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPrivacyKey &v) const;

    TLValue tlType = TLValue::PrivacyKeyStatusTimestamp;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPrivacyRule {
    TLPrivacyRule() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPrivacyRule &v) const;

    TLVector<quint32> users;
    TLValue tlType = TLValue::PrivacyValueAllowContacts;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLReceivedNotifyMessage {
    constexpr TLReceivedNotifyMessage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLReceivedNotifyMessage &v) const;

    quint32 id = 0;
    quint32 flags = 0;
    TLValue tlType = TLValue::ReceivedNotifyMessage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLReportReason {
    TLReportReason() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLReportReason &v) const;

    QString text;
    TLValue tlType = TLValue::InputReportReasonSpam;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLResPQ {
    TLResPQ() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLResPQ &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    QString pq;
    TLVector<quint64> serverPublicKeyFingerprints;
    TLValue tlType = TLValue::ResPQ;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRichText {
    TLRichText() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRichText &v) const;

    QString stringText;
    TLRichTextPtr richText;
    QString url;
    quint64 webpageId = 0;
    QString email;
    TLVector<TLRichText*> texts;
    QString phone;
    quint64 documentId = 0;
    quint32 w = 0;
    quint32 h = 0;
    QString name;
    TLValue tlType = TLValue::TextEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRpcDropAnswer {
    constexpr TLRpcDropAnswer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRpcDropAnswer &v) const;

    quint64 msgId = 0;
    quint32 seqNo = 0;
    quint32 bytes = 0;
    TLValue tlType = TLValue::RpcAnswerUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRpcError {
    TLRpcError() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRpcError &v) const;

    quint32 errorCode = 0;
    QString errorMessage;
    TLValue tlType = TLValue::RpcError;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSavedContact {
    TLSavedContact() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSavedContact &v) const;

    QString phone;
    QString firstName;
    QString lastName;
    quint32 date = 0;
    TLValue tlType = TLValue::SavedPhoneContact;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureCredentialsEncrypted {
    TLSecureCredentialsEncrypted() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureCredentialsEncrypted &v) const;

    QByteArray data;
    QByteArray hash;
    QByteArray secret;
    TLValue tlType = TLValue::SecureCredentialsEncrypted;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureData {
    TLSecureData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureData &v) const;

    QByteArray data;
    QByteArray dataHash;
    QByteArray secret;
    TLValue tlType = TLValue::SecureData;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureFile {
    TLSecureFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureFile &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 size = 0;
    quint32 dcId = 0;
    quint32 date = 0;
    QByteArray fileHash;
    QByteArray secret;
    TLValue tlType = TLValue::SecureFileEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecurePasswordKdfAlgo {
    TLSecurePasswordKdfAlgo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecurePasswordKdfAlgo &v) const;

    QByteArray salt;
    TLValue tlType = TLValue::SecurePasswordKdfAlgoUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecurePlainData {
    TLSecurePlainData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecurePlainData &v) const;

    QString phone;
    QString email;
    TLValue tlType = TLValue::SecurePlainPhone;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureSecretSettings {
    TLSecureSecretSettings() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureSecretSettings &v) const;

    TLSecurePasswordKdfAlgo secureAlgo;
    QByteArray secureSecret;
    quint64 secureSecretId = 0;
    TLValue tlType = TLValue::SecureSecretSettings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureValueType {
    constexpr TLSecureValueType() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureValueType &v) const;

    TLValue tlType = TLValue::SecureValueTypePersonalDetails;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSendMessageAction {
    constexpr TLSendMessageAction() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSendMessageAction &v) const;

    quint32 progress = 0;
    TLValue tlType = TLValue::SendMessageTypingAction;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLServerDHInnerData {
    TLServerDHInnerData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLServerDHInnerData &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    quint32 g = 0;
    QString dhPrime;
    QString gA;
    quint32 serverTime = 0;
    TLValue tlType = TLValue::ServerDHInnerData;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLServerDHParams {
    TLServerDHParams() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLServerDHParams &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber128 newNonceHash;
    QString encryptedAnswer;
    TLValue tlType = TLValue::ServerDHParamsFail;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSetClientDHParamsAnswer {
    TLSetClientDHParamsAnswer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSetClientDHParamsAnswer &v) const;

    TLNumber128 nonce;
    TLNumber128 serverNonce;
    TLNumber128 newNonceHash1;
    TLNumber128 newNonceHash2;
    TLNumber128 newNonceHash3;
    TLValue tlType = TLValue::DhGenOk;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLShippingOption {
    TLShippingOption() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLShippingOption &v) const;

    QString id;
    QString title;
    TLVector<TLLabeledPrice> prices;
    TLValue tlType = TLValue::ShippingOption;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStatsURL {
    TLStatsURL() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStatsURL &v) const;

    QString url;
    TLValue tlType = TLValue::StatsURL;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStickerPack {
    TLStickerPack() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStickerPack &v) const;

    QString emoticon;
    TLVector<quint64> documents;
    TLValue tlType = TLValue::StickerPack;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStorageFileType {
    constexpr TLStorageFileType() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStorageFileType &v) const;

    TLValue tlType = TLValue::StorageFileUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLTopPeer {
    TLTopPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLTopPeer &v) const;

    TLPeer peer;
    double rating = 0;
    TLValue tlType = TLValue::TopPeer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLTopPeerCategory {
    constexpr TLTopPeerCategory() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLTopPeerCategory &v) const;

    TLValue tlType = TLValue::TopPeerCategoryBotsPM;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLTopPeerCategoryPeers {
    TLTopPeerCategoryPeers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLTopPeerCategoryPeers &v) const;

    TLTopPeerCategory category;
    quint32 count = 0;
    TLVector<TLTopPeer> peers;
    TLValue tlType = TLValue::TopPeerCategoryPeers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdatesState {
    constexpr TLUpdatesState() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdatesState &v) const;

    quint32 pts = 0;
    quint32 qts = 0;
    quint32 date = 0;
    quint32 seq = 0;
    quint32 unreadCount = 0;
    TLValue tlType = TLValue::UpdatesState;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUploadCdnFile {
    TLUploadCdnFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUploadCdnFile &v) const;

    QByteArray requestToken;
    QByteArray bytes;
    TLValue tlType = TLValue::UploadCdnFileReuploadNeeded;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUploadFile {
    TLUploadFile() = default;

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
    TLVector<TLFileHash> fileHashes;
    TLValue tlType = TLValue::UploadFile;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUploadWebFile {
    TLUploadWebFile() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUploadWebFile &v) const;

    quint32 size = 0;
    QString mimeType;
    TLStorageFileType fileType;
    quint32 mtime = 0;
    QByteArray bytes;
    TLValue tlType = TLValue::UploadWebFile;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUserProfilePhoto {
    TLUserProfilePhoto() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUserProfilePhoto &v) const;

    quint64 photoId = 0;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType = TLValue::UserProfilePhotoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUserStatus {
    constexpr TLUserStatus() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUserStatus &v) const;

    quint32 expires = 0;
    quint32 wasOnline = 0;
    TLValue tlType = TLValue::UserStatusEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWallPaper {
    TLWallPaper() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLWallPaper &v) const;

    quint32 id = 0;
    QString title;
    TLVector<TLPhotoSize> sizes;
    quint32 color = 0;
    quint32 bgColor = 0;
    TLValue tlType = TLValue::WallPaper;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWebAuthorization {
    TLWebAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLWebAuthorization &v) const;

    quint64 hash = 0;
    quint32 botId = 0;
    QString domain;
    QString browser;
    QString platform;
    quint32 dateCreated = 0;
    quint32 dateActive = 0;
    QString ip;
    QString region;
    TLValue tlType = TLValue::WebAuthorization;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccessPointRule {
    TLAccessPointRule() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccessPointRule &v) const;

    QString phonePrefixRules;
    quint32 dcId = 0;
    TLVector<TLIpPort> ips;
    TLValue tlType = TLValue::AccessPointRule;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPassword {
    TLAccountPassword() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPassword &v) const;
    enum Flags {
        HasRecovery = 1 << 0,
        HasSecureValues = 1 << 1,
        SrpId = 1 << 2,
        SrpB = 1 << 2,
        CurrentAlgo = 1 << 2,
        HasPassword = 1 << 2,
        Hint = 1 << 3,
        EmailUnconfirmedPattern = 1 << 4,
    };
    bool hasRecovery() const { return flags & HasRecovery; }
    bool hasSecureValues() const { return flags & HasSecureValues; }
    bool hasPassword() const { return flags & HasPassword; }

    quint32 flags = 0;
    TLPasswordKdfAlgo currentAlgo;
    QByteArray srpB;
    quint64 srpId = 0;
    QString hint;
    QString emailUnconfirmedPattern;
    TLPasswordKdfAlgo newAlgo;
    TLSecurePasswordKdfAlgo newSecureAlgo;
    QByteArray secureRandom;
    TLValue tlType = TLValue::AccountPassword;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPasswordInputSettings {
    TLAccountPasswordInputSettings() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPasswordInputSettings &v) const;
    enum Flags {
        Hint = 1 << 0,
        NewPasswordHash = 1 << 0,
        NewAlgo = 1 << 0,
        Email = 1 << 1,
        NewSecureSettings = 1 << 2,
    };

    quint32 flags = 0;
    TLPasswordKdfAlgo newAlgo;
    QByteArray newPasswordHash;
    QString hint;
    QString email;
    TLSecureSecretSettings newSecureSettings;
    TLValue tlType = TLValue::AccountPasswordInputSettings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPasswordSettings {
    TLAccountPasswordSettings() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPasswordSettings &v) const;
    enum Flags {
        Email = 1 << 0,
        SecureSettings = 1 << 1,
    };

    quint32 flags = 0;
    QString email;
    TLSecureSecretSettings secureSettings;
    TLValue tlType = TLValue::AccountPasswordSettings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthorization {
    TLAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthorization &v) const;
    enum Flags {
        Current = 1 << 0,
        OfficialApp = 1 << 1,
        PasswordPending = 1 << 2,
    };
    bool current() const { return flags & Current; }
    bool officialApp() const { return flags & OfficialApp; }
    bool passwordPending() const { return flags & PasswordPending; }

    quint32 flags = 0;
    quint64 hash = 0;
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

struct TELEGRAMQT_INTERNAL_EXPORT TLCdnConfig {
    TLCdnConfig() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLCdnConfig &v) const;

    TLVector<TLCdnPublicKey> publicKeys;
    TLValue tlType = TLValue::CdnConfig;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminLogEventsFilter {
    TLChannelAdminLogEventsFilter() = default;

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
    TLValue tlType = TLValue::ChannelAdminLogEventsFilter;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminRights {
    TLChannelAdminRights() = default;

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
        ManageCall = 1 << 10,
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
    bool manageCall() const { return flags & ManageCall; }

    quint32 flags = 0;
    TLValue tlType = TLValue::ChannelAdminRights;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelBannedRights {
    TLChannelBannedRights() = default;

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
    TLValue tlType = TLValue::ChannelBannedRights;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelMessagesFilter {
    TLChannelMessagesFilter() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelMessagesFilter &v) const;
    enum Flags {
        ExcludeNewMessages = 1 << 1,
    };
    bool excludeNewMessages() const { return flags & ExcludeNewMessages; }

    quint32 flags = 0;
    TLVector<TLMessageRange> ranges;
    TLValue tlType = TLValue::ChannelMessagesFilterEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelParticipant {
    TLChannelParticipant() = default;

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
    TLValue tlType = TLValue::ChannelParticipant;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatPhoto {
    TLChatPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatPhoto &v) const;

    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType = TLValue::ChatPhotoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactStatus {
    TLContactStatus() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactStatus &v) const;

    quint32 userId = 0;
    TLUserStatus status;
    TLValue tlType = TLValue::ContactStatus;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDcOption {
    TLDcOption() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDcOption &v) const;
    enum Flags {
        Ipv6 = 1 << 0,
        MediaOnly = 1 << 1,
        TcpoOnly = 1 << 2,
        Cdn = 1 << 3,
        IsStatic = 1 << 4,
        Secret = 1 << 10,
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
    QByteArray secret;
    TLValue tlType = TLValue::DcOption;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDialogPeer {
    TLDialogPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDialogPeer &v) const;

    TLPeer peer;
    TLValue tlType = TLValue::DialogPeer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDocumentAttribute {
    TLDocumentAttribute() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDocumentAttribute &v) const;
    enum Flags {
        Title = 1 << 0,
        RoundMessage = 1 << 0,
        MaskCoords = 1 << 0,
        Performer = 1 << 1,
        SupportsStreaming = 1 << 1,
        Mask = 1 << 1,
        Waveform = 1 << 2,
        Voice = 1 << 10,
    };
    bool mask() const { return flags & Mask; }
    bool roundMessage() const { return flags & RoundMessage; }
    bool supportsStreaming() const { return flags & SupportsStreaming; }
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

struct TELEGRAMQT_INTERNAL_EXPORT TLDraftMessage {
    TLDraftMessage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDraftMessage &v) const;
    enum Flags {
        ReplyToMsgId = 1 << 0,
        Date = 1 << 0,
        NoWebpage = 1 << 1,
        Entities = 1 << 3,
    };
    bool noWebpage() const { return flags & NoWebpage; }

    quint32 flags = 0;
    quint32 date = 0;
    quint32 replyToMsgId = 0;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLValue tlType = TLValue::DraftMessageEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpConfigSimple {
    TLHelpConfigSimple() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpConfigSimple &v) const;

    quint32 date = 0;
    quint32 expires = 0;
    TLVector<TLAccessPointRule> rules;
    TLValue tlType = TLValue::HelpConfigSimple;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpDeepLinkInfo {
    TLHelpDeepLinkInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpDeepLinkInfo &v) const;
    enum Flags {
        UpdateApp = 1 << 0,
        Entities = 1 << 1,
    };
    bool updateApp() const { return flags & UpdateApp; }

    quint32 flags = 0;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLValue tlType = TLValue::HelpDeepLinkInfoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpTermsOfService {
    TLHelpTermsOfService() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpTermsOfService &v) const;
    enum Flags {
        Popup = 1 << 0,
        MinAgeConfirm = 1 << 1,
    };
    bool popup() const { return flags & Popup; }

    quint32 flags = 0;
    TLDataJSON id;
    QString text;
    TLVector<TLMessageEntity> entities;
    quint32 minAgeConfirm = 0;
    TLValue tlType = TLValue::HelpTermsOfService;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpTermsOfServiceUpdate {
    TLHelpTermsOfServiceUpdate() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpTermsOfServiceUpdate &v) const;

    quint32 expires = 0;
    TLHelpTermsOfService termsOfService;
    TLValue tlType = TLValue::HelpTermsOfServiceUpdateEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpUserInfo {
    TLHelpUserInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpUserInfo &v) const;

    QString message;
    TLVector<TLMessageEntity> entities;
    QString author;
    quint32 date = 0;
    TLValue tlType = TLValue::HelpUserInfoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputChatPhoto {
    TLInputChatPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputChatPhoto &v) const;

    TLInputFile file;
    TLInputPhoto id;
    TLValue tlType = TLValue::InputChatPhotoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputDialogPeer {
    TLInputDialogPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputDialogPeer &v) const;

    TLInputPeer peer;
    TLValue tlType = TLValue::InputDialogPeer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputGame {
    TLInputGame() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputGame &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    TLInputUser botId;
    QString shortName;
    TLValue tlType = TLValue::InputGameID;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputNotifyPeer {
    TLInputNotifyPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputNotifyPeer &v) const;

    TLInputPeer peer;
    TLValue tlType = TLValue::InputNotifyPeer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPaymentCredentials {
    TLInputPaymentCredentials() = default;

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
    QString googleTransactionId;
    TLValue tlType = TLValue::InputPaymentCredentialsSaved;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputPrivacyRule {
    TLInputPrivacyRule() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputPrivacyRule &v) const;

    TLVector<TLInputUser> users;
    TLValue tlType = TLValue::InputPrivacyValueAllowContacts;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputSecureValue {
    TLInputSecureValue() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputSecureValue &v) const;
    enum Flags {
        Data = 1 << 0,
        FrontSide = 1 << 1,
        ReverseSide = 1 << 2,
        Selfie = 1 << 3,
        Files = 1 << 4,
        PlainData = 1 << 5,
        Translation = 1 << 6,
    };

    quint32 flags = 0;
    TLSecureValueType type;
    TLSecureData data;
    TLInputSecureFile frontSide;
    TLInputSecureFile reverseSide;
    TLInputSecureFile selfie;
    TLVector<TLInputSecureFile> translation;
    TLVector<TLInputSecureFile> files;
    TLSecurePlainData plainData;
    TLValue tlType = TLValue::InputSecureValue;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputStickerSetItem {
    TLInputStickerSetItem() = default;

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
    TLValue tlType = TLValue::InputStickerSetItem;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputWebDocument {
    TLInputWebDocument() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputWebDocument &v) const;

    QString url;
    quint32 size = 0;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType = TLValue::InputWebDocument;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInvoice {
    TLInvoice() = default;

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
        PhoneToProvider = 1 << 6,
        EmailToProvider = 1 << 7,
    };
    bool test() const { return flags & Test; }
    bool nameRequested() const { return flags & NameRequested; }
    bool phoneRequested() const { return flags & PhoneRequested; }
    bool emailRequested() const { return flags & EmailRequested; }
    bool shippingAddressRequested() const { return flags & ShippingAddressRequested; }
    bool flexible() const { return flags & Flexible; }
    bool phoneToProvider() const { return flags & PhoneToProvider; }
    bool emailToProvider() const { return flags & EmailToProvider; }

    quint32 flags = 0;
    QString currency;
    TLVector<TLLabeledPrice> prices;
    TLValue tlType = TLValue::Invoice;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLKeyboardButton {
    TLKeyboardButton() = default;

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
    TLValue tlType = TLValue::KeyboardButton;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLKeyboardButtonRow {
    TLKeyboardButtonRow() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLKeyboardButtonRow &v) const;

    TLVector<TLKeyboardButton> buttons;
    TLValue tlType = TLValue::KeyboardButtonRow;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLangPackDifference {
    TLLangPackDifference() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLangPackDifference &v) const;

    QString langCode;
    quint32 fromVersion = 0;
    quint32 version = 0;
    TLVector<TLLangPackString> strings;
    TLValue tlType = TLValue::LangPackDifference;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLLangPackLanguage {
    TLLangPackLanguage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLLangPackLanguage &v) const;
    enum Flags {
        Official = 1 << 0,
        BaseLangCode = 1 << 1,
        Rtl = 1 << 2,
        Beta = 1 << 3,
    };
    bool official() const { return flags & Official; }
    bool rtl() const { return flags & Rtl; }
    bool beta() const { return flags & Beta; }

    quint32 flags = 0;
    QString name;
    QString nativeName;
    QString langCode;
    QString baseLangCode;
    QString pluralCode;
    quint32 stringsCount = 0;
    quint32 translatedCount = 0;
    QString translationsUrl;
    TLValue tlType = TLValue::LangPackLanguage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageFwdHeader {
    TLMessageFwdHeader() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageFwdHeader &v) const;
    enum Flags {
        FromId = 1 << 0,
        ChannelId = 1 << 1,
        ChannelPost = 1 << 2,
        PostAuthor = 1 << 3,
        SavedFromMsgId = 1 << 4,
        SavedFromPeer = 1 << 4,
    };

    quint32 flags = 0;
    quint32 fromId = 0;
    quint32 date = 0;
    quint32 channelId = 0;
    quint32 channelPost = 0;
    QString postAuthor;
    TLPeer savedFromPeer;
    quint32 savedFromMsgId = 0;
    TLValue tlType = TLValue::MessageFwdHeader;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesBotCallbackAnswer {
    TLMessagesBotCallbackAnswer() = default;

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
    TLValue tlType = TLValue::MessagesBotCallbackAnswer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFilter {
    TLMessagesFilter() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFilter &v) const;
    enum Flags {
        Missed = 1 << 0,
    };
    bool missed() const { return flags & Missed; }

    quint32 flags = 0;
    TLValue tlType = TLValue::InputMessagesFilterEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesMessageEditData {
    TLMessagesMessageEditData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesMessageEditData &v) const;
    enum Flags {
        Caption = 1 << 0,
    };
    bool caption() const { return flags & Caption; }

    quint32 flags = 0;
    TLValue tlType = TLValue::MessagesMessageEditData;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLNotifyPeer {
    TLNotifyPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLNotifyPeer &v) const;

    TLPeer peer;
    TLValue tlType = TLValue::NotifyPeer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageTableCell {
    TLPageTableCell() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageTableCell &v) const;
    enum Flags {
        Header = 1 << 0,
        Colspan = 1 << 1,
        Rowspan = 1 << 2,
        AlignCenter = 1 << 3,
        AlignRight = 1 << 4,
        ValignMiddle = 1 << 5,
        ValignBottom = 1 << 6,
        Text = 1 << 7,
    };
    bool header() const { return flags & Header; }
    bool alignCenter() const { return flags & AlignCenter; }
    bool alignRight() const { return flags & AlignRight; }
    bool valignMiddle() const { return flags & ValignMiddle; }
    bool valignBottom() const { return flags & ValignBottom; }

    quint32 flags = 0;
    TLRichTextPtr text;
    quint32 colspan = 0;
    quint32 rowspan = 0;
    TLValue tlType = TLValue::PageTableCell;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageTableRow {
    TLPageTableRow() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageTableRow &v) const;

    TLVector<TLPageTableCell> cells;
    TLValue tlType = TLValue::PageTableRow;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentRequestedInfo {
    TLPaymentRequestedInfo() = default;

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
    TLValue tlType = TLValue::PaymentRequestedInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsSavedInfo {
    TLPaymentsSavedInfo() = default;

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
    TLValue tlType = TLValue::PaymentsSavedInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsValidatedRequestedInfo {
    TLPaymentsValidatedRequestedInfo() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsValidatedRequestedInfo &v) const;
    enum Flags {
        Id = 1 << 0,
        ShippingOptions = 1 << 1,
    };

    quint32 flags = 0;
    QString id;
    TLVector<TLShippingOption> shippingOptions;
    TLValue tlType = TLValue::PaymentsValidatedRequestedInfo;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPeerSettings {
    TLPeerSettings() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPeerSettings &v) const;
    enum Flags {
        ReportSpam = 1 << 0,
    };
    bool reportSpam() const { return flags & ReportSpam; }

    quint32 flags = 0;
    TLValue tlType = TLValue::PeerSettings;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneCallProtocol {
    TLPhoneCallProtocol() = default;

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
    TLValue tlType = TLValue::PhoneCallProtocol;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoto {
    TLPhoto() = default;

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
    QByteArray fileReference;
    quint32 date = 0;
    TLVector<TLPhotoSize> sizes;
    TLValue tlType = TLValue::PhotoEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPoll {
    TLPoll() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPoll &v) const;
    enum Flags {
        Closed = 1 << 0,
    };
    bool closed() const { return flags & Closed; }

    quint64 id = 0;
    quint32 flags = 0;
    QString question;
    TLVector<TLPollAnswer> answers;
    TLValue tlType = TLValue::Poll;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPollAnswerVoters {
    TLPollAnswerVoters() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPollAnswerVoters &v) const;
    enum Flags {
        Chosen = 1 << 0,
    };
    bool chosen() const { return flags & Chosen; }

    quint32 flags = 0;
    QByteArray option;
    quint32 voters = 0;
    TLValue tlType = TLValue::PollAnswerVoters;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPollResults {
    TLPollResults() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPollResults &v) const;
    enum Flags {
        Min = 1 << 0,
        Results = 1 << 1,
        TotalVoters = 1 << 2,
    };
    bool min() const { return flags & Min; }

    quint32 flags = 0;
    TLVector<TLPollAnswerVoters> results;
    quint32 totalVoters = 0;
    TLValue tlType = TLValue::PollResults;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLReplyMarkup {
    TLReplyMarkup() = default;

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
    TLVector<TLKeyboardButtonRow> rows;
    TLValue tlType = TLValue::ReplyKeyboardHide;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureRequiredType {
    TLSecureRequiredType() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureRequiredType &v) const;
    enum Flags {
        NativeNames = 1 << 0,
        SelfieRequired = 1 << 1,
        TranslationRequired = 1 << 2,
    };
    bool nativeNames() const { return flags & NativeNames; }
    bool selfieRequired() const { return flags & SelfieRequired; }
    bool translationRequired() const { return flags & TranslationRequired; }

    quint32 flags = 0;
    TLSecureValueType type;
    TLVector<TLSecureRequiredType*> types;
    TLValue tlType = TLValue::SecureRequiredType;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureValue {
    TLSecureValue() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureValue &v) const;
    enum Flags {
        Data = 1 << 0,
        FrontSide = 1 << 1,
        ReverseSide = 1 << 2,
        Selfie = 1 << 3,
        Files = 1 << 4,
        PlainData = 1 << 5,
        Translation = 1 << 6,
    };

    quint32 flags = 0;
    TLSecureValueType type;
    TLSecureData data;
    TLSecureFile frontSide;
    TLSecureFile reverseSide;
    TLSecureFile selfie;
    TLVector<TLSecureFile> translation;
    TLVector<TLSecureFile> files;
    TLSecurePlainData plainData;
    QByteArray hash;
    TLValue tlType = TLValue::SecureValue;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureValueError {
    TLSecureValueError() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureValueError &v) const;

    TLSecureValueType type;
    QByteArray dataHash;
    QString field;
    QString text;
    QByteArray byteArrayFileHash;
    TLVector<QByteArray> byteArrayFileHashVector;
    QByteArray hash;
    TLValue tlType = TLValue::SecureValueErrorData;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLSecureValueHash {
    TLSecureValueHash() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLSecureValueHash &v) const;

    TLSecureValueType type;
    QByteArray hash;
    TLValue tlType = TLValue::SecureValueHash;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStickerSet {
    TLStickerSet() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStickerSet &v) const;
    enum Flags {
        InstalledDate = 1 << 0,
        Archived = 1 << 1,
        Official = 1 << 2,
        Masks = 1 << 3,
    };
    bool archived() const { return flags & Archived; }
    bool official() const { return flags & Official; }
    bool masks() const { return flags & Masks; }

    quint32 flags = 0;
    quint32 installedDate = 0;
    quint64 id = 0;
    quint64 accessHash = 0;
    QString title;
    QString shortName;
    quint32 count = 0;
    quint32 hash = 0;
    TLValue tlType = TLValue::StickerSet;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUser {
    TLUser() = default;

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
    TLValue tlType = TLValue::UserEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWebDocument {
    TLWebDocument() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLWebDocument &v) const;

    QString url;
    quint64 accessHash = 0;
    quint32 size = 0;
    QString mimeType;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType = TLValue::WebDocument;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountAuthorizationForm {
    TLAccountAuthorizationForm() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountAuthorizationForm &v) const;
    enum Flags {
        PrivacyPolicyUrl = 1 << 0,
    };

    quint32 flags = 0;
    TLVector<TLSecureRequiredType*> requiredTypes;
    TLVector<TLSecureValue> values;
    TLVector<TLSecureValueError> errors;
    TLVector<TLUser> users;
    QString privacyPolicyUrl;
    TLValue tlType = TLValue::AccountAuthorizationForm;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountAuthorizations {
    TLAccountAuthorizations() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountAuthorizations &v) const;

    TLVector<TLAuthorization> authorizations;
    TLValue tlType = TLValue::AccountAuthorizations;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountPrivacyRules {
    TLAccountPrivacyRules() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountPrivacyRules &v) const;

    TLVector<TLPrivacyRule> rules;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::AccountPrivacyRules;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAccountWebAuthorizations {
    TLAccountWebAuthorizations() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAccountWebAuthorizations &v) const;

    TLVector<TLWebAuthorization> authorizations;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::AccountWebAuthorizations;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthAuthorization {
    TLAuthAuthorization() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthAuthorization &v) const;
    enum Flags {
        TmpSessions = 1 << 0,
    };

    quint32 flags = 0;
    quint32 tmpSessions = 0;
    TLUser user;
    TLValue tlType = TLValue::AuthAuthorization;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLAuthSentCode {
    TLAuthSentCode() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLAuthSentCode &v) const;
    enum Flags {
        PhoneRegistered = 1 << 0,
        NextType = 1 << 1,
        Timeout = 1 << 2,
        TermsOfService = 1 << 3,
    };
    bool phoneRegistered() const { return flags & PhoneRegistered; }

    quint32 flags = 0;
    TLAuthSentCodeType type;
    QString phoneCodeHash;
    TLAuthCodeType nextType;
    quint32 timeout = 0;
    TLHelpTermsOfService termsOfService;
    TLValue tlType = TLValue::AuthSentCode;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotInlineMessage {
    TLBotInlineMessage() = default;

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
    QString message;
    TLVector<TLMessageEntity> entities;
    TLReplyMarkup replyMarkup;
    TLGeoPoint geo;
    quint32 period = 0;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString venueType;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    QString vcard;
    TLValue tlType = TLValue::BotInlineMessageMediaAuto;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelsChannelParticipant {
    TLChannelsChannelParticipant() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelsChannelParticipant &v) const;

    TLChannelParticipant participant;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ChannelsChannelParticipant;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelsChannelParticipants {
    TLChannelsChannelParticipants() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelsChannelParticipants &v) const;

    quint32 count = 0;
    TLVector<TLChannelParticipant> participants;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ChannelsChannelParticipants;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChat {
    TLChat() = default;

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
        ParticipantsCount = 1 << 17,
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

struct TELEGRAMQT_INTERNAL_EXPORT TLChatFull {
    TLChatFull() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChatFull &v) const;
    enum Flags {
        ParticipantsCount = 1 << 0,
        AdminsCount = 1 << 1,
        BannedCount = 1 << 2,
        KickedCount = 1 << 2,
        ChatPhoto = 1 << 2,
        CanViewParticipants = 1 << 3,
        BotInfo = 1 << 3,
        MigratedFromMaxId = 1 << 4,
        MigratedFromChatId = 1 << 4,
        PinnedMsgId5 = 1 << 5,
        CanSetUsername = 1 << 6,
        PinnedMsgId6 = 1 << 6,
        CanSetStickers = 1 << 7,
        Stickerset = 1 << 8,
        AvailableMinId = 1 << 9,
        HiddenPrehistory = 1 << 10,
        CanViewStats = 1 << 12,
        OnlineCount = 1 << 13,
    };
    bool canViewParticipants() const { return flags & CanViewParticipants; }
    bool canSetUsername() const { return flags & CanSetUsername; }
    bool canSetStickers() const { return flags & CanSetStickers; }
    bool hiddenPrehistory() const { return flags & HiddenPrehistory; }
    bool canViewStats() const { return flags & CanViewStats; }

    quint32 flags = 0;
    quint32 id = 0;
    TLChatParticipants participants;
    TLPhoto chatPhoto;
    TLPeerNotifySettings notifySettings;
    TLExportedChatInvite exportedInvite;
    TLVector<TLBotInfo> botInfo;
    quint32 pinnedMsgId = 0;
    QString about;
    quint32 participantsCount = 0;
    quint32 adminsCount = 0;
    quint32 kickedCount = 0;
    quint32 bannedCount = 0;
    quint32 onlineCount = 0;
    quint32 readInboxMaxId = 0;
    quint32 readOutboxMaxId = 0;
    quint32 unreadCount = 0;
    quint32 migratedFromChatId = 0;
    quint32 migratedFromMaxId = 0;
    TLStickerSet stickerset;
    quint32 availableMinId = 0;
    TLValue tlType = TLValue::ChatFull;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChatInvite {
    TLChatInvite() = default;

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
    TLVector<TLUser> participants;
    TLValue tlType = TLValue::ChatInviteAlready;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLConfig {
    TLConfig() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLConfig &v) const;
    enum Flags {
        TmpSessions = 1 << 0,
        PhonecallsEnabled = 1 << 1,
        BaseLangPackVersion = 1 << 2,
        LangPackVersion = 1 << 2,
        SuggestedLangCode = 1 << 2,
        DefaultP2pContacts = 1 << 3,
        PreloadFeaturedStickers = 1 << 4,
        IgnorePhoneEntities = 1 << 5,
        RevokePmInbox = 1 << 6,
        AutoupdateUrlPrefix = 1 << 7,
        BlockedMode = 1 << 8,
        GifSearchUsername = 1 << 9,
        VenueSearchUsername = 1 << 10,
        ImgSearchUsername = 1 << 11,
        StaticMapsProvider = 1 << 12,
        PfsEnabled = 1 << 13,
    };
    bool phonecallsEnabled() const { return flags & PhonecallsEnabled; }
    bool defaultP2pContacts() const { return flags & DefaultP2pContacts; }
    bool preloadFeaturedStickers() const { return flags & PreloadFeaturedStickers; }
    bool ignorePhoneEntities() const { return flags & IgnorePhoneEntities; }
    bool revokePmInbox() const { return flags & RevokePmInbox; }
    bool blockedMode() const { return flags & BlockedMode; }
    bool pfsEnabled() const { return flags & PfsEnabled; }

    quint32 flags = 0;
    quint32 date = 0;
    quint32 expires = 0;
    bool testMode = false;
    quint32 thisDc = 0;
    TLVector<TLDcOption> dcOptions;
    QString dcTxtDomainName;
    quint32 chatSizeMax = 0;
    quint32 megagroupSizeMax = 0;
    quint32 forwardedCountMax = 0;
    quint32 onlineUpdatePeriodMs = 0;
    quint32 offlineBlurTimeoutMs = 0;
    quint32 offlineIdleTimeoutMs = 0;
    quint32 onlineCloudTimeoutMs = 0;
    quint32 notifyCloudDelayMs = 0;
    quint32 notifyDefaultDelayMs = 0;
    quint32 pushChatPeriodMs = 0;
    quint32 pushChatLimit = 0;
    quint32 savedGifsLimit = 0;
    quint32 editTimeLimit = 0;
    quint32 revokeTimeLimit = 0;
    quint32 revokePmTimeLimit = 0;
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
    QString autoupdateUrlPrefix;
    QString gifSearchUsername;
    QString venueSearchUsername;
    QString imgSearchUsername;
    QString staticMapsProvider;
    quint32 captionLengthMax = 0;
    quint32 messageLengthMax = 0;
    quint32 webfileDcId = 0;
    QString suggestedLangCode;
    quint32 langPackVersion = 0;
    quint32 baseLangPackVersion = 0;
    TLValue tlType = TLValue::Config;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsBlocked {
    TLContactsBlocked() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsBlocked &v) const;

    TLVector<TLContactBlocked> blocked;
    TLVector<TLUser> users;
    quint32 count = 0;
    TLValue tlType = TLValue::ContactsBlocked;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsContacts {
    TLContactsContacts() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsContacts &v) const;

    TLVector<TLContact> contacts;
    quint32 savedCount = 0;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsContactsNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsFound {
    TLContactsFound() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsFound &v) const;

    TLVector<TLPeer> myResults;
    TLVector<TLPeer> results;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsFound;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsImportedContacts {
    TLContactsImportedContacts() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsImportedContacts &v) const;

    TLVector<TLImportedContact> imported;
    TLVector<TLPopularContact> popularInvites;
    TLVector<quint64> retryContacts;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsImportedContacts;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsLink {
    TLContactsLink() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsLink &v) const;

    TLContactLink myLink;
    TLContactLink foreignLink;
    TLUser user;
    TLValue tlType = TLValue::ContactsLink;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsResolvedPeer {
    TLContactsResolvedPeer() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsResolvedPeer &v) const;

    TLPeer peer;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsResolvedPeer;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLContactsTopPeers {
    TLContactsTopPeers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLContactsTopPeers &v) const;

    TLVector<TLTopPeerCategoryPeers> categories;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::ContactsTopPeersNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLDialog {
    TLDialog() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDialog &v) const;
    enum Flags {
        Pts = 1 << 0,
        Draft = 1 << 1,
        Pinned = 1 << 2,
        UnreadMark = 1 << 3,
    };
    bool pinned() const { return flags & Pinned; }
    bool unreadMark() const { return flags & UnreadMark; }

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

struct TELEGRAMQT_INTERNAL_EXPORT TLDocument {
    TLDocument() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLDocument &v) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    QByteArray fileReference;
    quint32 date = 0;
    QString mimeType;
    quint32 size = 0;
    TLPhotoSize thumb;
    quint32 dcId = 0;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType = TLValue::DocumentEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLFoundGif {
    TLFoundGif() = default;

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
    TLValue tlType = TLValue::FoundGif;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLGame {
    TLGame() = default;

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
    TLValue tlType = TLValue::Game;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpAppUpdate {
    TLHelpAppUpdate() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpAppUpdate &v) const;
    enum Flags {
        Popup = 1 << 0,
        Document = 1 << 1,
        Url = 1 << 2,
    };
    bool popup() const { return flags & Popup; }

    quint32 flags = 0;
    quint32 id = 0;
    QString version;
    QString text;
    TLVector<TLMessageEntity> entities;
    TLDocument document;
    QString url;
    TLValue tlType = TLValue::HelpAppUpdate;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpProxyData {
    TLHelpProxyData() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpProxyData &v) const;

    quint32 expires = 0;
    TLPeer peer;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::HelpProxyDataEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpSupport {
    TLHelpSupport() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpSupport &v) const;

    QString phoneNumber;
    TLUser user;
    TLValue tlType = TLValue::HelpSupport;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputBotInlineMessage {
    TLInputBotInlineMessage() = default;

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
    QString message;
    TLVector<TLMessageEntity> entities;
    TLReplyMarkup replyMarkup;
    TLInputGeoPoint geoPoint;
    quint32 period = 0;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    QString venueType;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    QString vcard;
    TLValue tlType = TLValue::InputBotInlineMessageMediaAuto;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputBotInlineResult {
    TLInputBotInlineResult() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputBotInlineResult &v) const;
    enum Flags {
        Title = 1 << 1,
        Description = 1 << 2,
        Url = 1 << 3,
        Thumb = 1 << 4,
        Content = 1 << 5,
    };

    quint32 flags = 0;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    TLInputWebDocument thumb;
    TLInputWebDocument content;
    TLInputBotInlineMessage sendMessage;
    TLInputPhoto photo;
    TLInputDocument document;
    QString shortName;
    TLValue tlType = TLValue::InputBotInlineResult;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputMedia {
    TLInputMedia() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputMedia &v) const;
    enum Flags {
        Stopped = 1 << 0,
        Photo = 1 << 0,
        TtlSeconds0 = 1 << 0,
        Stickers = 1 << 0,
        Period = 1 << 1,
        TtlSeconds1 = 1 << 1,
        Thumb = 1 << 2,
        NosoundVideo = 1 << 3,
    };
    bool nosoundVideo() const { return flags & NosoundVideo; }
    bool stopped() const { return flags & Stopped; }

    quint32 flags = 0;
    TLInputFile file;
    TLVector<TLInputDocument> stickers;
    quint32 ttlSeconds = 0;
    TLInputPhoto inputPhotoId;
    TLInputGeoPoint geoPoint;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    QString vcard;
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
    TLDataJSON providerData;
    QString startParam;
    quint32 period = 0;
    TLPoll poll;
    TLValue tlType = TLValue::InputMediaEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLInputSingleMedia {
    TLInputSingleMedia() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLInputSingleMedia &v) const;
    enum Flags {
        Entities = 1 << 0,
    };

    quint32 flags = 0;
    TLInputMedia media;
    quint64 randomId = 0;
    QString message;
    TLVector<TLMessageEntity> entities;
    TLValue tlType = TLValue::InputSingleMedia;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageAction {
    TLMessageAction() = default;

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
    QString domain;
    TLVector<TLSecureValue> values;
    TLSecureCredentialsEncrypted credentials;
    TLVector<TLSecureValueType> types;
    TLValue tlType = TLValue::MessageActionEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesAllStickers {
    TLMessagesAllStickers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesAllStickers &v) const;

    quint32 hash = 0;
    TLVector<TLStickerSet> sets;
    TLValue tlType = TLValue::MessagesAllStickersNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesChatFull {
    TLMessagesChatFull() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesChatFull &v) const;

    TLChatFull fullChat;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::MessagesChatFull;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesChats {
    TLMessagesChats() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesChats &v) const;

    TLVector<TLChat> chats;
    quint32 count = 0;
    TLValue tlType = TLValue::MessagesChats;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFavedStickers {
    TLMessagesFavedStickers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFavedStickers &v) const;

    quint32 hash = 0;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> stickers;
    TLValue tlType = TLValue::MessagesFavedStickersNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFoundGifs {
    TLMessagesFoundGifs() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFoundGifs &v) const;

    quint32 nextOffset = 0;
    TLVector<TLFoundGif> results;
    TLValue tlType = TLValue::MessagesFoundGifs;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesHighScores {
    TLMessagesHighScores() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesHighScores &v) const;

    TLVector<TLHighScore> scores;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::MessagesHighScores;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesRecentStickers {
    TLMessagesRecentStickers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesRecentStickers &v) const;

    quint32 hash = 0;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> stickers;
    TLVector<quint32> dates;
    TLValue tlType = TLValue::MessagesRecentStickersNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesSavedGifs {
    TLMessagesSavedGifs() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesSavedGifs &v) const;

    quint32 hash = 0;
    TLVector<TLDocument> gifs;
    TLValue tlType = TLValue::MessagesSavedGifsNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesStickerSet {
    TLMessagesStickerSet() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesStickerSet &v) const;

    TLStickerSet set;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> documents;
    TLValue tlType = TLValue::MessagesStickerSet;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesStickers {
    TLMessagesStickers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesStickers &v) const;

    quint32 hash = 0;
    TLVector<TLDocument> stickers;
    TLValue tlType = TLValue::MessagesStickersNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPage {
    TLPage() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPage &v) const;
    enum Flags {
        Part = 1 << 0,
        Rtl = 1 << 1,
        V2 = 1 << 2,
    };
    bool part() const { return flags & Part; }
    bool rtl() const { return flags & Rtl; }
    bool v2() const { return flags & V2; }

    quint32 flags = 0;
    QString url;
    TLVector<TLPageBlock*> blocks;
    TLVector<TLPhoto> photos;
    TLVector<TLDocument> documents;
    TLValue tlType = TLValue::Page;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPageBlock {
    TLPageBlock() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPageBlock &v) const;
    enum Flags {
        Open = 1 << 0,
        Bordered = 1 << 0,
        FullWidth = 1 << 0,
        Autoplay = 1 << 0,
        WebpageId = 1 << 0,
        Url0 = 1 << 0,
        Striped = 1 << 1,
        Url1 = 1 << 1,
        Loop = 1 << 1,
        Html = 1 << 2,
        AllowScrolling = 1 << 3,
        PosterPhotoId = 1 << 4,
        H = 1 << 5,
        W = 1 << 5,
    };
    bool autoplay() const { return flags & Autoplay; }
    bool loop() const { return flags & Loop; }
    bool fullWidth() const { return flags & FullWidth; }
    bool allowScrolling() const { return flags & AllowScrolling; }
    bool bordered() const { return flags & Bordered; }
    bool striped() const { return flags & Striped; }
    bool open() const { return flags & Open; }

    TLRichTextPtr text;
    TLRichTextPtr richTextAuthor;
    quint32 publishedDate = 0;
    QString language;
    QString name;
    TLVector<TLPageListItem> pageListItemItemsVector;
    TLRichTextPtr richTextCaption;
    quint32 flags = 0;
    quint64 photoId = 0;
    TLPageCaption pageCaption;
    QString url;
    quint64 webpageId = 0;
    quint64 videoId = 0;
    TLPageBlockPtr cover;
    QString html;
    quint64 posterPhotoId = 0;
    quint32 w = 0;
    quint32 h = 0;
    quint64 authorPhotoId = 0;
    QString stringAuthor;
    quint32 date = 0;
    TLVector<TLPageBlock*> blocks;
    TLVector<TLPageBlock*> pageBlockItemsVector;
    TLChat channel;
    quint64 audioId = 0;
    TLRichTextPtr title;
    TLVector<TLPageTableRow> rows;
    TLVector<TLPageListOrderedItem> pageListOrderedItemItemsVector;
    TLVector<TLPageRelatedArticle> articles;
    TLGeoPoint geo;
    quint32 zoom = 0;
    TLValue tlType = TLValue::PageBlockUnsupported;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsPaymentForm {
    TLPaymentsPaymentForm() = default;

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
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PaymentsPaymentForm;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsPaymentReceipt {
    TLPaymentsPaymentReceipt() = default;

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
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PaymentsPaymentReceipt;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhoneCall {
    TLPhoneCall() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhoneCall &v) const;
    enum Flags {
        Reason = 1 << 0,
        ReceiveDate = 1 << 0,
        Duration = 1 << 1,
        NeedRating = 1 << 2,
        NeedDebug = 1 << 3,
        P2pAllowed = 1 << 5,
    };
    bool p2pAllowed() const { return flags & P2pAllowed; }
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

struct TELEGRAMQT_INTERNAL_EXPORT TLPhonePhoneCall {
    TLPhonePhoneCall() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhonePhoneCall &v) const;

    TLPhoneCall phoneCall;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PhonePhoneCall;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhotosPhoto {
    TLPhotosPhoto() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhotosPhoto &v) const;

    TLPhoto photo;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::PhotosPhoto;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPhotosPhotos {
    TLPhotosPhotos() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPhotosPhotos &v) const;

    TLVector<TLPhoto> photos;
    TLVector<TLUser> users;
    quint32 count = 0;
    TLValue tlType = TLValue::PhotosPhotos;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLStickerSetCovered {
    TLStickerSetCovered() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLStickerSetCovered &v) const;

    TLStickerSet set;
    TLDocument cover;
    TLVector<TLDocument> covers;
    TLValue tlType = TLValue::StickerSetCovered;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUserFull {
    TLUserFull() = default;

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
        PinnedMsgId = 1 << 6,
        CanPinMessage = 1 << 7,
    };
    bool blocked() const { return flags & Blocked; }
    bool phoneCallsAvailable() const { return flags & PhoneCallsAvailable; }
    bool phoneCallsPrivate() const { return flags & PhoneCallsPrivate; }
    bool canPinMessage() const { return flags & CanPinMessage; }

    quint32 flags = 0;
    TLUser user;
    QString about;
    TLContactsLink link;
    TLPhoto profilePhoto;
    TLPeerNotifySettings notifySettings;
    TLBotInfo botInfo;
    quint32 pinnedMsgId = 0;
    quint32 commonChatsCount = 0;
    TLValue tlType = TLValue::UserFull;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLWebPage {
    TLWebPage() = default;

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
    TLValue tlType = TLValue::WebPageEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLBotInlineResult {
    TLBotInlineResult() = default;

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
        Thumb = 1 << 4,
        Content = 1 << 5,
    };

    quint32 flags = 0;
    QString id;
    QString type;
    QString title;
    QString description;
    QString url;
    TLWebDocument thumb;
    TLWebDocument content;
    TLBotInlineMessage sendMessage;
    TLPhoto photo;
    TLDocument document;
    TLValue tlType = TLValue::BotInlineResult;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessageMedia {
    TLMessageMedia() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessageMedia &v) const;
    enum Flags {
        WebDocumentPhoto = 1 << 0,
        Document = 1 << 0,
        Photo = 1 << 0,
        ShippingAddressRequested = 1 << 1,
        ReceiptMsgId = 1 << 2,
        TtlSeconds = 1 << 2,
        Test = 1 << 3,
    };
    bool shippingAddressRequested() const { return flags & ShippingAddressRequested; }
    bool test() const { return flags & Test; }

    quint32 flags = 0;
    TLPhoto photo;
    quint32 ttlSeconds = 0;
    TLGeoPoint geo;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    QString vcard;
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
    TLPoll poll;
    TLPollResults results;
    TLValue tlType = TLValue::MessageMediaEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesArchivedStickers {
    TLMessagesArchivedStickers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesArchivedStickers &v) const;

    quint32 count = 0;
    TLVector<TLStickerSetCovered> sets;
    TLValue tlType = TLValue::MessagesArchivedStickers;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesBotResults {
    TLMessagesBotResults() = default;

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
    TLVector<TLBotInlineResult> results;
    quint32 cacheTime = 0;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::MessagesBotResults;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFeaturedStickers {
    TLMessagesFeaturedStickers() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFeaturedStickers &v) const;

    quint32 hash = 0;
    TLVector<TLStickerSetCovered> sets;
    TLVector<quint64> unread;
    TLValue tlType = TLValue::MessagesFeaturedStickersNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesFoundStickerSets {
    TLMessagesFoundStickerSets() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesFoundStickerSets &v) const;

    quint32 hash = 0;
    TLVector<TLStickerSetCovered> sets;
    TLValue tlType = TLValue::MessagesFoundStickerSetsNotModified;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesStickerSetInstallResult {
    TLMessagesStickerSetInstallResult() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesStickerSetInstallResult &v) const;

    TLVector<TLStickerSetCovered> sets;
    TLValue tlType = TLValue::MessagesStickerSetInstallResultSuccess;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLRecentMeUrl {
    TLRecentMeUrl() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLRecentMeUrl &v) const;

    QString url;
    quint32 userId = 0;
    quint32 chatId = 0;
    TLChatInvite chatInvite;
    TLStickerSetCovered set;
    TLValue tlType = TLValue::RecentMeUrlUnknown;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLHelpRecentMeUrls {
    TLHelpRecentMeUrls() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLHelpRecentMeUrls &v) const;

    TLVector<TLRecentMeUrl> urls;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType = TLValue::HelpRecentMeUrls;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessage {
    TLMessage() = default;

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
        GroupedId = 1 << 17,
        FromScheduled = 1 << 18,
    };
    bool out() const { return flags & Out; }
    bool mentioned() const { return flags & Mentioned; }
    bool mediaUnread() const { return flags & MediaUnread; }
    bool silent() const { return flags & Silent; }
    bool post() const { return flags & Post; }
    bool fromScheduled() const { return flags & FromScheduled; }

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
    quint64 groupedId = 0;
    TLMessageAction action;
    TLValue tlType = TLValue::MessageEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesDialogs {
    TLMessagesDialogs() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesDialogs &v) const;

    TLVector<TLDialog> dialogs;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count = 0;
    TLValue tlType = TLValue::MessagesDialogs;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesMessages {
    TLMessagesMessages() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesMessages &v) const;
    enum Flags {
        Inexact = 1 << 1,
    };
    bool inexact() const { return flags & Inexact; }

    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 flags = 0;
    quint32 count = 0;
    quint32 pts = 0;
    TLValue tlType = TLValue::MessagesMessages;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLMessagesPeerDialogs {
    TLMessagesPeerDialogs() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLMessagesPeerDialogs &v) const;

    TLVector<TLDialog> dialogs;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLUpdatesState state;
    TLValue tlType = TLValue::MessagesPeerDialogs;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdate {
    TLUpdate() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdate &v) const;
    enum Flags {
        Poll = 1 << 0,
        Unread = 1 << 0,
        Info = 1 << 0,
        DialogPeerOrderVector = 1 << 0,
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
    bool unread() const { return flags & Unread; }

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
    quint32 msgId = 0;
    quint64 chatInstance = 0;
    QByteArray byteArrayData;
    QString gameShortName;
    TLDraftMessage draft;
    TLDialogPeer dialogPeer;
    TLVector<TLDialogPeer> dialogPeerOrderVector;
    TLDataJSON jSONData;
    quint32 timeout = 0;
    QByteArray payload;
    TLPostAddress shippingAddress;
    TLPaymentRequestedInfo info;
    QString shippingOptionId;
    QString currency;
    quint64 totalAmount = 0;
    TLPhoneCall phoneCall;
    QString langCode;
    TLLangPackDifference difference;
    quint32 availableMinId = 0;
    quint64 pollId = 0;
    TLPoll poll;
    TLPollResults results;
    TLValue tlType = TLValue::UpdateNewMessage;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdates {
    TLUpdates() = default;

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

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdatesChannelDifference {
    TLUpdatesChannelDifference() = default;

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
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLVector<TLMessage> newMessages;
    TLVector<TLUpdate> otherUpdates;
    TLValue tlType = TLValue::UpdatesChannelDifferenceEmpty;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLUpdatesDifference {
    TLUpdatesDifference() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLUpdatesDifference &v) const;

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

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminLogEventAction {
    TLChannelAdminLogEventAction() = default;

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
    TLValue tlType = TLValue::ChannelAdminLogEventActionChangeTitle;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLPaymentsPaymentResult {
    TLPaymentsPaymentResult() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLPaymentsPaymentResult &v) const;

    TLUpdates updates;
    QString url;
    TLValue tlType = TLValue::PaymentsPaymentResult;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelAdminLogEvent {
    TLChannelAdminLogEvent() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelAdminLogEvent &v) const;

    quint64 id = 0;
    quint32 date = 0;
    quint32 userId = 0;
    TLChannelAdminLogEventAction action;
    TLValue tlType = TLValue::ChannelAdminLogEvent;
};

struct TELEGRAMQT_INTERNAL_EXPORT TLChannelsAdminLogResults {
    TLChannelsAdminLogResults() = default;

    bool isValid() const { return hasType(tlType); }
    static bool hasType(const quint32 value);
    bool operator==(const TLChannelsAdminLogResults &v) const;

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
