/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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

#include <QMetaType>
#include <QVector>

template <typename T>
class TLVector : public QVector<T>
{
public:
    inline TLVector() : QVector<T>(), tlType(TLValue::Vector) { }
    explicit TLVector(int size) : QVector<T>(size), tlType(TLValue::Vector) { }
    TLVector(int size, const T &t) : QVector<T>(size, t), tlType(TLValue::Vector) { }
    inline TLVector(const TLVector<T> &v) : QVector<T>(v), tlType(v.tlType) { }
    inline TLVector(const QVector<T> &v) : QVector<T>(v), tlType(TLValue::Vector) { }

    TLVector &operator=(const TLVector &v) {
        tlType = v.tlType;
        QVector<T>::operator =(v);
        return *this;
    }

    TLValue tlType;
};

// Generated TLTypes
struct TLAccountDaysTTL {
    TLAccountDaysTTL() :
        days(0),
        tlType(TLValue::AccountDaysTTL) { }

    quint32 days;
    TLValue tlType;
};

struct TLAccountPassword {
    TLAccountPassword() :
        hasRecovery(false),
        tlType(TLValue::AccountNoPassword) { }

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

    QString email;
    TLValue tlType;
};

struct TLAccountSentChangePhoneCode {
    TLAccountSentChangePhoneCode() :
        sendCallTimeout(0),
        tlType(TLValue::AccountSentChangePhoneCode) { }

    QString phoneCodeHash;
    quint32 sendCallTimeout;
    TLValue tlType;
};

struct TLAudio {
    TLAudio() :
        id(0),
        accessHash(0),
        date(0),
        duration(0),
        size(0),
        dcId(0),
        tlType(TLValue::AudioEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 date;
    quint32 duration;
    QString mimeType;
    quint32 size;
    quint32 dcId;
    TLValue tlType;
};

struct TLAuthCheckedPhone {
    TLAuthCheckedPhone() :
        phoneRegistered(false),
        tlType(TLValue::AuthCheckedPhone) { }

    bool phoneRegistered;
    TLValue tlType;
};

struct TLAuthExportedAuthorization {
    TLAuthExportedAuthorization() :
        id(0),
        tlType(TLValue::AuthExportedAuthorization) { }

    quint32 id;
    QByteArray bytes;
    TLValue tlType;
};

struct TLAuthPasswordRecovery {
    TLAuthPasswordRecovery() :
        tlType(TLValue::AuthPasswordRecovery) { }

    QString emailPattern;
    TLValue tlType;
};

struct TLAuthSentCode {
    TLAuthSentCode() :
        phoneRegistered(false),
        sendCallTimeout(0),
        isPassword(false),
        tlType(TLValue::AuthSentCode) { }

    bool phoneRegistered;
    QString phoneCodeHash;
    quint32 sendCallTimeout;
    bool isPassword;
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

struct TLBotCommand {
    TLBotCommand() :
        tlType(TLValue::BotCommand) { }

    QString command;
    QString description;
    TLValue tlType;
};

struct TLBotInfo {
    TLBotInfo() :
        userId(0),
        version(0),
        tlType(TLValue::BotInfoEmpty) { }

    quint32 userId;
    quint32 version;
    QString shareText;
    QString description;
    TLVector<TLBotCommand> commands;
    TLValue tlType;
};

struct TLChannelParticipant {
    TLChannelParticipant() :
        userId(0),
        date(0),
        inviterId(0),
        kickedBy(0),
        tlType(TLValue::ChannelParticipant) { }

    quint32 userId;
    quint32 date;
    quint32 inviterId;
    quint32 kickedBy;
    TLValue tlType;
};

struct TLChannelParticipantRole {
    TLChannelParticipantRole() :
        tlType(TLValue::ChannelRoleEmpty) { }

    TLValue tlType;
};

struct TLChannelParticipantsFilter {
    TLChannelParticipantsFilter() :
        tlType(TLValue::ChannelParticipantsRecent) { }

    TLValue tlType;
};

struct TLChatParticipant {
    TLChatParticipant() :
        userId(0),
        inviterId(0),
        date(0),
        tlType(TLValue::ChatParticipant) { }

    quint32 userId;
    quint32 inviterId;
    quint32 date;
    TLValue tlType;
};

struct TLChatParticipants {
    TLChatParticipants() :
        flags(0),
        chatId(0),
        adminId(0),
        version(0),
        tlType(TLValue::ChatParticipantsForbidden) { }

    quint32 flags;
    quint32 chatId;
    TLChatParticipant selfParticipant;
    quint32 adminId;
    TLVector<TLChatParticipant> participants;
    quint32 version;
    TLValue tlType;
};

struct TLContact {
    TLContact() :
        userId(0),
        mutual(false),
        tlType(TLValue::Contact) { }

    quint32 userId;
    bool mutual;
    TLValue tlType;
};

struct TLContactBlocked {
    TLContactBlocked() :
        userId(0),
        date(0),
        tlType(TLValue::ContactBlocked) { }

    quint32 userId;
    quint32 date;
    TLValue tlType;
};

struct TLContactLink {
    TLContactLink() :
        tlType(TLValue::ContactLinkUnknown) { }

    TLValue tlType;
};

struct TLContactSuggested {
    TLContactSuggested() :
        userId(0),
        mutualContacts(0),
        tlType(TLValue::ContactSuggested) { }

    quint32 userId;
    quint32 mutualContacts;
    TLValue tlType;
};

struct TLDcOption {
    TLDcOption() :
        flags(0),
        id(0),
        port(0),
        tlType(TLValue::DcOption) { }

    quint32 flags;
    quint32 id;
    QString ipAddress;
    quint32 port;
    TLValue tlType;
};

struct TLDisabledFeature {
    TLDisabledFeature() :
        tlType(TLValue::DisabledFeature) { }

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
    TLEncryptedFile() :
        id(0),
        accessHash(0),
        size(0),
        dcId(0),
        keyFingerprint(0),
        tlType(TLValue::EncryptedFileEmpty) { }

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

    quint32 code;
    QString text;
    TLValue tlType;
};

struct TLExportedChatInvite {
    TLExportedChatInvite() :
        tlType(TLValue::ChatInviteEmpty) { }

    QString link;
    TLValue tlType;
};

struct TLFileLocation {
    TLFileLocation() :
        volumeId(0),
        localId(0),
        secret(0),
        dcId(0),
        tlType(TLValue::FileLocationUnavailable) { }

    quint64 volumeId;
    quint32 localId;
    quint64 secret;
    quint32 dcId;
    TLValue tlType;
};

struct TLGeoPoint {
    TLGeoPoint() :
        longitude(0),
        latitude(0),
        tlType(TLValue::GeoPointEmpty) { }

    double longitude;
    double latitude;
    TLValue tlType;
};

struct TLHelpAppChangelog {
    TLHelpAppChangelog() :
        tlType(TLValue::HelpAppChangelogEmpty) { }

    QString text;
    TLValue tlType;
};

struct TLHelpAppUpdate {
    TLHelpAppUpdate() :
        id(0),
        critical(false),
        tlType(TLValue::HelpAppUpdate) { }

    quint32 id;
    bool critical;
    QString url;
    QString text;
    TLValue tlType;
};

struct TLHelpInviteText {
    TLHelpInviteText() :
        tlType(TLValue::HelpInviteText) { }

    QString message;
    TLValue tlType;
};

struct TLImportedContact {
    TLImportedContact() :
        userId(0),
        clientId(0),
        tlType(TLValue::ImportedContact) { }

    quint32 userId;
    quint64 clientId;
    TLValue tlType;
};

struct TLInputAppEvent {
    TLInputAppEvent() :
        time(0),
        peer(0),
        tlType(TLValue::InputAppEvent) { }

    double time;
    QString type;
    quint64 peer;
    QString data;
    TLValue tlType;
};

struct TLInputAudio {
    TLInputAudio() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputAudioEmpty) { }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputChannel {
    TLInputChannel() :
        channelId(0),
        accessHash(0),
        tlType(TLValue::InputChannelEmpty) { }

    quint32 channelId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputContact {
    TLInputContact() :
        clientId(0),
        tlType(TLValue::InputPhoneContact) { }

    quint64 clientId;
    QString phone;
    QString firstName;
    QString lastName;
    TLValue tlType;
};

struct TLInputDocument {
    TLInputDocument() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputDocumentEmpty) { }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputEncryptedChat {
    TLInputEncryptedChat() :
        chatId(0),
        accessHash(0),
        tlType(TLValue::InputEncryptedChat) { }

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

    quint64 id;
    quint32 parts;
    QString name;
    QString md5Checksum;
    TLValue tlType;
};

struct TLInputFileLocation {
    TLInputFileLocation() :
        volumeId(0),
        localId(0),
        secret(0),
        id(0),
        accessHash(0),
        tlType(TLValue::InputFileLocation) { }

    quint64 volumeId;
    quint32 localId;
    quint64 secret;
    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputGeoPoint {
    TLInputGeoPoint() :
        latitude(0),
        longitude(0),
        tlType(TLValue::InputGeoPointEmpty) { }

    double latitude;
    double longitude;
    TLValue tlType;
};

struct TLInputPeer {
    TLInputPeer() :
        chatId(0),
        userId(0),
        accessHash(0),
        channelId(0),
        tlType(TLValue::InputPeerEmpty) { }

    quint32 chatId;
    quint32 userId;
    quint64 accessHash;
    quint32 channelId;
    TLValue tlType;
};

struct TLInputPeerNotifyEvents {
    TLInputPeerNotifyEvents() :
        tlType(TLValue::InputPeerNotifyEventsEmpty) { }

    TLValue tlType;
};

struct TLInputPeerNotifySettings {
    TLInputPeerNotifySettings() :
        muteUntil(0),
        showPreviews(false),
        eventsMask(0),
        tlType(TLValue::InputPeerNotifySettings) { }

    quint32 muteUntil;
    QString sound;
    bool showPreviews;
    quint32 eventsMask;
    TLValue tlType;
};

struct TLInputPhoto {
    TLInputPhoto() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputPhotoEmpty) { }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputPhotoCrop {
    TLInputPhotoCrop() :
        cropLeft(0),
        cropTop(0),
        cropWidth(0),
        tlType(TLValue::InputPhotoCropAuto) { }

    double cropLeft;
    double cropTop;
    double cropWidth;
    TLValue tlType;
};

struct TLInputPrivacyKey {
    TLInputPrivacyKey() :
        tlType(TLValue::InputPrivacyKeyStatusTimestamp) { }

    TLValue tlType;
};

struct TLInputStickerSet {
    TLInputStickerSet() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputStickerSetEmpty) { }

    quint64 id;
    quint64 accessHash;
    QString shortName;
    TLValue tlType;
};

struct TLInputUser {
    TLInputUser() :
        userId(0),
        accessHash(0),
        tlType(TLValue::InputUserEmpty) { }

    quint32 userId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputVideo {
    TLInputVideo() :
        id(0),
        accessHash(0),
        tlType(TLValue::InputVideoEmpty) { }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLKeyboardButton {
    TLKeyboardButton() :
        tlType(TLValue::KeyboardButton) { }

    QString text;
    TLValue tlType;
};

struct TLKeyboardButtonRow {
    TLKeyboardButtonRow() :
        tlType(TLValue::KeyboardButtonRow) { }

    TLVector<TLKeyboardButton> buttons;
    TLValue tlType;
};

struct TLMessageEntity {
    TLMessageEntity() :
        offset(0),
        length(0),
        tlType(TLValue::MessageEntityUnknown) { }

    quint32 offset;
    quint32 length;
    QString language;
    QString url;
    TLValue tlType;
};

struct TLMessageGroup {
    TLMessageGroup() :
        minId(0),
        maxId(0),
        count(0),
        date(0),
        tlType(TLValue::MessageGroup) { }

    quint32 minId;
    quint32 maxId;
    quint32 count;
    quint32 date;
    TLValue tlType;
};

struct TLMessageRange {
    TLMessageRange() :
        minId(0),
        maxId(0),
        tlType(TLValue::MessageRange) { }

    quint32 minId;
    quint32 maxId;
    TLValue tlType;
};

struct TLMessagesAffectedHistory {
    TLMessagesAffectedHistory() :
        pts(0),
        ptsCount(0),
        offset(0),
        tlType(TLValue::MessagesAffectedHistory) { }

    quint32 pts;
    quint32 ptsCount;
    quint32 offset;
    TLValue tlType;
};

struct TLMessagesAffectedMessages {
    TLMessagesAffectedMessages() :
        pts(0),
        ptsCount(0),
        tlType(TLValue::MessagesAffectedMessages) { }

    quint32 pts;
    quint32 ptsCount;
    TLValue tlType;
};

struct TLMessagesDhConfig {
    TLMessagesDhConfig() :
        g(0),
        version(0),
        tlType(TLValue::MessagesDhConfigNotModified) { }

    QByteArray random;
    quint32 g;
    QByteArray p;
    quint32 version;
    TLValue tlType;
};

struct TLMessagesFilter {
    TLMessagesFilter() :
        tlType(TLValue::InputMessagesFilterEmpty) { }

    TLValue tlType;
};

struct TLMessagesSentEncryptedMessage {
    TLMessagesSentEncryptedMessage() :
        date(0),
        tlType(TLValue::MessagesSentEncryptedMessage) { }

    quint32 date;
    TLEncryptedFile file;
    TLValue tlType;
};

struct TLNearestDc {
    TLNearestDc() :
        thisDc(0),
        nearestDc(0),
        tlType(TLValue::NearestDc) { }

    QString country;
    quint32 thisDc;
    quint32 nearestDc;
    TLValue tlType;
};

struct TLPeer {
    TLPeer() :
        userId(0),
        chatId(0),
        channelId(0),
        tlType(TLValue::PeerUser) { }

    quint32 userId;
    quint32 chatId;
    quint32 channelId;
    TLValue tlType;
};

struct TLPeerNotifyEvents {
    TLPeerNotifyEvents() :
        tlType(TLValue::PeerNotifyEventsEmpty) { }

    TLValue tlType;
};

struct TLPeerNotifySettings {
    TLPeerNotifySettings() :
        muteUntil(0),
        showPreviews(false),
        eventsMask(0),
        tlType(TLValue::PeerNotifySettingsEmpty) { }

    quint32 muteUntil;
    QString sound;
    bool showPreviews;
    quint32 eventsMask;
    TLValue tlType;
};

struct TLPhotoSize {
    TLPhotoSize() :
        w(0),
        h(0),
        size(0),
        tlType(TLValue::PhotoSizeEmpty) { }

    QString type;
    TLFileLocation location;
    quint32 w;
    quint32 h;
    quint32 size;
    QByteArray bytes;
    TLValue tlType;
};

struct TLPrivacyKey {
    TLPrivacyKey() :
        tlType(TLValue::PrivacyKeyStatusTimestamp) { }

    TLValue tlType;
};

struct TLPrivacyRule {
    TLPrivacyRule() :
        tlType(TLValue::PrivacyValueAllowContacts) { }

    TLVector<quint32> users;
    TLValue tlType;
};

struct TLReceivedNotifyMessage {
    TLReceivedNotifyMessage() :
        id(0),
        flags(0),
        tlType(TLValue::ReceivedNotifyMessage) { }

    quint32 id;
    quint32 flags;
    TLValue tlType;
};

struct TLReplyMarkup {
    TLReplyMarkup() :
        flags(0),
        tlType(TLValue::ReplyKeyboardHide) { }

    quint32 flags;
    TLVector<TLKeyboardButtonRow> rows;
    TLValue tlType;
};

struct TLSendMessageAction {
    TLSendMessageAction() :
        progress(0),
        tlType(TLValue::SendMessageTypingAction) { }

    quint32 progress;
    TLValue tlType;
};

struct TLStickerPack {
    TLStickerPack() :
        tlType(TLValue::StickerPack) { }

    QString emoticon;
    TLVector<quint64> documents;
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

    quint32 flags;
    quint64 id;
    quint64 accessHash;
    QString title;
    QString shortName;
    quint32 count;
    quint32 hash;
    TLValue tlType;
};

struct TLStorageFileType {
    TLStorageFileType() :
        tlType(TLValue::StorageFileUnknown) { }

    TLValue tlType;
};

struct TLUpdatesState {
    TLUpdatesState() :
        pts(0),
        qts(0),
        date(0),
        seq(0),
        unreadCount(0),
        tlType(TLValue::UpdatesState) { }

    quint32 pts;
    quint32 qts;
    quint32 date;
    quint32 seq;
    quint32 unreadCount;
    TLValue tlType;
};

struct TLUploadFile {
    TLUploadFile() :
        mtime(0),
        tlType(TLValue::UploadFile) { }

    TLStorageFileType type;
    quint32 mtime;
    QByteArray bytes;
    TLValue tlType;
};

struct TLUserProfilePhoto {
    TLUserProfilePhoto() :
        photoId(0),
        tlType(TLValue::UserProfilePhotoEmpty) { }

    quint64 photoId;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLUserStatus {
    TLUserStatus() :
        expires(0),
        wasOnline(0),
        tlType(TLValue::UserStatusEmpty) { }

    quint32 expires;
    quint32 wasOnline;
    TLValue tlType;
};

struct TLVideo {
    TLVideo() :
        id(0),
        accessHash(0),
        date(0),
        duration(0),
        size(0),
        dcId(0),
        w(0),
        h(0),
        tlType(TLValue::VideoEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 date;
    quint32 duration;
    QString mimeType;
    quint32 size;
    TLPhotoSize thumb;
    quint32 dcId;
    quint32 w;
    quint32 h;
    TLValue tlType;
};

struct TLWallPaper {
    TLWallPaper() :
        id(0),
        color(0),
        bgColor(0),
        tlType(TLValue::WallPaper) { }

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

    TLVector<TLAuthorization> authorizations;
    TLValue tlType;
};

struct TLChannelMessagesFilter {
    TLChannelMessagesFilter() :
        flags(0),
        tlType(TLValue::ChannelMessagesFilterEmpty) { }

    quint32 flags;
    TLVector<TLMessageRange> ranges;
    TLValue tlType;
};

struct TLChatPhoto {
    TLChatPhoto() :
        tlType(TLValue::ChatPhotoEmpty) { }

    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLConfig {
    TLConfig() :
        date(0),
        expires(0),
        testMode(false),
        thisDc(0),
        chatSizeMax(0),
        broadcastSizeMax(0),
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
        tlType(TLValue::Config) { }

    quint32 date;
    quint32 expires;
    bool testMode;
    quint32 thisDc;
    TLVector<TLDcOption> dcOptions;
    quint32 chatSizeMax;
    quint32 broadcastSizeMax;
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
    TLVector<TLDisabledFeature> disabledFeatures;
    TLValue tlType;
};

struct TLContactStatus {
    TLContactStatus() :
        userId(0),
        tlType(TLValue::ContactStatus) { }

    quint32 userId;
    TLUserStatus status;
    TLValue tlType;
};

struct TLDialog {
    TLDialog() :
        topMessage(0),
        readInboxMaxId(0),
        unreadCount(0),
        topImportantMessage(0),
        unreadImportantCount(0),
        pts(0),
        tlType(TLValue::Dialog) { }

    TLPeer peer;
    quint32 topMessage;
    quint32 readInboxMaxId;
    quint32 unreadCount;
    TLPeerNotifySettings notifySettings;
    quint32 topImportantMessage;
    quint32 unreadImportantCount;
    quint32 pts;
    TLValue tlType;
};

struct TLDocumentAttribute {
    TLDocumentAttribute() :
        w(0),
        h(0),
        duration(0),
        tlType(TLValue::DocumentAttributeImageSize) { }

    quint32 w;
    quint32 h;
    QString alt;
    TLInputStickerSet stickerset;
    quint32 duration;
    QString title;
    QString performer;
    QString fileName;
    TLValue tlType;
};

struct TLInputChatPhoto {
    TLInputChatPhoto() :
        tlType(TLValue::InputChatPhotoEmpty) { }

    TLInputFile file;
    TLInputPhotoCrop crop;
    TLInputPhoto id;
    TLValue tlType;
};

struct TLInputMedia {
    TLInputMedia() :
        duration(0),
        w(0),
        h(0),
        tlType(TLValue::InputMediaEmpty) { }

    TLInputFile file;
    QString caption;
    TLInputPhoto idInputPhoto;
    TLInputGeoPoint geoPoint;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 duration;
    quint32 w;
    quint32 h;
    QString mimeType;
    TLInputFile thumb;
    TLInputVideo idInputVeo;
    TLInputAudio idInputAudio;
    TLVector<TLDocumentAttribute> attributes;
    TLInputDocument idInputDocument;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    TLValue tlType;
};

struct TLInputNotifyPeer {
    TLInputNotifyPeer() :
        tlType(TLValue::InputNotifyPeer) { }

    TLInputPeer peer;
    TLValue tlType;
};

struct TLInputPrivacyRule {
    TLInputPrivacyRule() :
        tlType(TLValue::InputPrivacyValueAllowContacts) { }

    TLVector<TLInputUser> users;
    TLValue tlType;
};

struct TLMessagesAllStickers {
    TLMessagesAllStickers() :
        tlType(TLValue::MessagesAllStickersNotModified) { }

    QString hash;
    TLVector<TLStickerSet> sets;
    TLValue tlType;
};

struct TLNotifyPeer {
    TLNotifyPeer() :
        tlType(TLValue::NotifyPeer) { }

    TLPeer peer;
    TLValue tlType;
};

struct TLPhoto {
    TLPhoto() :
        id(0),
        accessHash(0),
        date(0),
        tlType(TLValue::PhotoEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 date;
    TLVector<TLPhotoSize> sizes;
    TLValue tlType;
};

struct TLUser {
    TLUser() :
        id(0),
        flags(0),
        accessHash(0),
        botInfoVersion(0),
        tlType(TLValue::UserEmpty) { }

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
    TLValue tlType;
};

struct TLAccountPrivacyRules {
    TLAccountPrivacyRules() :
        tlType(TLValue::AccountPrivacyRules) { }

    TLVector<TLPrivacyRule> rules;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLAuthAuthorization {
    TLAuthAuthorization() :
        tlType(TLValue::AuthAuthorization) { }

    TLUser user;
    TLValue tlType;
};

struct TLChannelsChannelParticipant {
    TLChannelsChannelParticipant() :
        tlType(TLValue::ChannelsChannelParticipant) { }

    TLChannelParticipant participant;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLChannelsChannelParticipants {
    TLChannelsChannelParticipants() :
        count(0),
        tlType(TLValue::ChannelsChannelParticipants) { }

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
        tlType(TLValue::ChatEmpty) { }

    quint32 id;
    quint32 flags;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount;
    quint32 date;
    quint32 version;
    quint64 accessHash;
    QString username;
    TLValue tlType;
};

struct TLChatFull {
    TLChatFull() :
        id(0),
        flags(0),
        participantsCount(0),
        adminsCount(0),
        kickedCount(0),
        readInboxMaxId(0),
        unreadCount(0),
        unreadImportantCount(0),
        tlType(TLValue::ChatFull) { }

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
    quint32 readInboxMaxId;
    quint32 unreadCount;
    quint32 unreadImportantCount;
    TLValue tlType;
};

struct TLChatInvite {
    TLChatInvite() :
        flags(0),
        tlType(TLValue::ChatInviteAlready) { }

    TLChat chat;
    quint32 flags;
    QString title;
    TLValue tlType;
};

struct TLContactsBlocked {
    TLContactsBlocked() :
        count(0),
        tlType(TLValue::ContactsBlocked) { }

    TLVector<TLContactBlocked> blocked;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLContactsContacts {
    TLContactsContacts() :
        tlType(TLValue::ContactsContactsNotModified) { }

    TLVector<TLContact> contacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsFound {
    TLContactsFound() :
        tlType(TLValue::ContactsFound) { }

    TLVector<TLPeer> results;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsImportedContacts {
    TLContactsImportedContacts() :
        tlType(TLValue::ContactsImportedContacts) { }

    TLVector<TLImportedContact> imported;
    TLVector<quint64> retryContacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsLink {
    TLContactsLink() :
        tlType(TLValue::ContactsLink) { }

    TLContactLink myLink;
    TLContactLink foreignLink;
    TLUser user;
    TLValue tlType;
};

struct TLContactsResolvedPeer {
    TLContactsResolvedPeer() :
        tlType(TLValue::ContactsResolvedPeer) { }

    TLPeer peer;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsSuggested {
    TLContactsSuggested() :
        tlType(TLValue::ContactsSuggested) { }

    TLVector<TLContactSuggested> results;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLDocument {
    TLDocument() :
        id(0),
        accessHash(0),
        date(0),
        size(0),
        dcId(0),
        tlType(TLValue::DocumentEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 date;
    QString mimeType;
    quint32 size;
    TLPhotoSize thumb;
    quint32 dcId;
    TLVector<TLDocumentAttribute> attributes;
    TLValue tlType;
};

struct TLHelpSupport {
    TLHelpSupport() :
        tlType(TLValue::HelpSupport) { }

    QString phoneNumber;
    TLUser user;
    TLValue tlType;
};

struct TLMessageAction {
    TLMessageAction() :
        userId(0),
        inviterId(0),
        tlType(TLValue::MessageActionEmpty) { }

    QString title;
    TLVector<quint32> users;
    TLPhoto photo;
    quint32 userId;
    quint32 inviterId;
    TLValue tlType;
};

struct TLMessagesChatFull {
    TLMessagesChatFull() :
        tlType(TLValue::MessagesChatFull) { }

    TLChatFull fullChat;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesChats {
    TLMessagesChats() :
        tlType(TLValue::MessagesChats) { }

    TLVector<TLChat> chats;
    TLValue tlType;
};

struct TLMessagesStickerSet {
    TLMessagesStickerSet() :
        tlType(TLValue::MessagesStickerSet) { }

    TLStickerSet set;
    TLVector<TLStickerPack> packs;
    TLVector<TLDocument> documents;
    TLValue tlType;
};

struct TLMessagesStickers {
    TLMessagesStickers() :
        tlType(TLValue::MessagesStickersNotModified) { }

    QString hash;
    TLVector<TLDocument> stickers;
    TLValue tlType;
};

struct TLPhotosPhoto {
    TLPhotosPhoto() :
        tlType(TLValue::PhotosPhoto) { }

    TLPhoto photo;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPhotosPhotos {
    TLPhotosPhotos() :
        count(0),
        tlType(TLValue::PhotosPhotos) { }

    TLVector<TLPhoto> photos;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLUserFull {
    TLUserFull() :
        blocked(false),
        tlType(TLValue::UserFull) { }

    TLUser user;
    TLContactsLink link;
    TLPhoto profilePhoto;
    TLPeerNotifySettings notifySettings;
    bool blocked;
    TLBotInfo botInfo;
    TLValue tlType;
};

struct TLWebPage {
    TLWebPage() :
        id(0),
        date(0),
        flags(0),
        embedWidth(0),
        embedHeight(0),
        duration(0),
        tlType(TLValue::WebPageEmpty) { }

    quint64 id;
    quint32 date;
    quint32 flags;
    QString url;
    QString displayUrl;
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
    TLValue tlType;
};

struct TLMessageMedia {
    TLMessageMedia() :
        userId(0),
        tlType(TLValue::MessageMediaEmpty) { }

    TLPhoto photo;
    QString caption;
    TLVideo video;
    TLGeoPoint geo;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 userId;
    TLDocument document;
    TLAudio audio;
    TLWebPage webpage;
    QString title;
    QString address;
    QString provider;
    QString venueId;
    TLValue tlType;
};

struct TLMessage {
    TLMessage() :
        id(0),
        flags(0),
        fromId(0),
        fwdDate(0),
        replyToMsgId(0),
        date(0),
        views(0),
        tlType(TLValue::MessageEmpty) { }

    quint32 id;
    quint32 flags;
    quint32 fromId;
    TLPeer toId;
    TLPeer fwdFromId;
    quint32 fwdDate;
    quint32 replyToMsgId;
    quint32 date;
    QString message;
    TLMessageMedia media;
    TLReplyMarkup replyMarkup;
    TLVector<TLMessageEntity> entities;
    quint32 views;
    TLMessageAction action;
    TLValue tlType;
};

struct TLMessagesDialogs {
    TLMessagesDialogs() :
        count(0),
        tlType(TLValue::MessagesDialogs) { }

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

    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    quint32 flags;
    quint32 pts;
    TLVector<TLMessageGroup> collapsed;
    TLValue tlType;
};

struct TLUpdate {
    TLUpdate() :
        pts(0),
        ptsCount(0),
        id(0),
        randomId(0),
        userId(0),
        chatId(0),
        date(0),
        previous(false),
        authKeyId(0),
        qts(0),
        maxDate(0),
        inviterId(0),
        version(0),
        blocked(false),
        popup(false),
        maxId(0),
        channelId(0),
        views(0),
        tlType(TLValue::UpdateNewMessage) { }

    TLMessage message;
    quint32 pts;
    quint32 ptsCount;
    quint32 id;
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
    quint64 authKeyId;
    QString device;
    QString location;
    TLEncryptedMessage messageEncrypted;
    quint32 qts;
    TLEncryptedChat chat;
    quint32 maxDate;
    quint32 inviterId;
    quint32 version;
    TLVector<TLDcOption> dcOptions;
    bool blocked;
    TLNotifyPeer peerNotify;
    TLPeerNotifySettings notifySettings;
    QString type;
    QString messageQString;
    TLMessageMedia media;
    bool popup;
    TLPrivacyKey key;
    TLVector<TLPrivacyRule> rules;
    QString phone;
    TLPeer peer;
    quint32 maxId;
    TLWebPage webpage;
    quint32 channelId;
    TLMessageGroup group;
    quint32 views;
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
        fwdDate(0),
        replyToMsgId(0),
        fromId(0),
        chatId(0),
        seqStart(0),
        seq(0),
        tlType(TLValue::UpdatesTooLong) { }

    quint32 flags;
    quint32 id;
    quint32 userId;
    QString message;
    quint32 pts;
    quint32 ptsCount;
    quint32 date;
    TLPeer fwdFromId;
    quint32 fwdDate;
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
        topImportantMessage(0),
        readInboxMaxId(0),
        unreadCount(0),
        unreadImportantCount(0),
        tlType(TLValue::UpdatesChannelDifferenceEmpty) { }

    quint32 flags;
    quint32 pts;
    quint32 timeout;
    quint32 topMessage;
    quint32 topImportantMessage;
    quint32 readInboxMaxId;
    quint32 unreadCount;
    quint32 unreadImportantCount;
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
        tlType(TLValue::UpdatesDifferenceEmpty) { }

    quint32 date;
    quint32 seq;
    TLVector<TLMessage> newMessages;
    TLVector<TLEncryptedMessage> newEncryptedMessages;
    TLVector<TLUpdate> otherUpdates;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLUpdatesState state;
    TLUpdatesState intermediateState;
    TLValue tlType;
};

// End of generated TLTypes

Q_DECLARE_METATYPE(TLUploadFile)
Q_DECLARE_METATYPE(QVector<TLUser>)
Q_DECLARE_METATYPE(TLUpdates)

#endif // TLTYPES_HPP
