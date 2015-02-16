/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef TLTYPES_HPP
#define TLTYPES_HPP

#include "TLNumbers.hpp"
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
struct TLAudio {
    TLAudio() :
        id(0),
        accessHash(0),
        userId(0),
        date(0),
        duration(0),
        size(0),
        dcId(0),
        tlType(TLValue::AudioEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 userId;
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
        phoneInvited(false),
        tlType(TLValue::AuthCheckedPhone) { }

    bool phoneRegistered;
    bool phoneInvited;
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

struct TLChatLocated {
    TLChatLocated() :
        chatId(0),
        distance(0),
        tlType(TLValue::ChatLocated) { }

    quint32 chatId;
    quint32 distance;
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
        chatId(0),
        adminId(0),
        version(0),
        tlType(TLValue::ChatParticipantsForbidden) { }

    quint32 chatId;
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

struct TLContactFound {
    TLContactFound() :
        userId(0),
        tlType(TLValue::ContactFound) { }

    quint32 userId;
    TLValue tlType;
};

struct TLContactStatus {
    TLContactStatus() :
        userId(0),
        expires(0),
        tlType(TLValue::ContactStatus) { }

    quint32 userId;
    quint32 expires;
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

struct TLContactsForeignLink {
    TLContactsForeignLink() :
        hasPhone(false),
        tlType(TLValue::ContactsForeignLinkUnknown) { }

    bool hasPhone;
    TLValue tlType;
};

struct TLContactsMyLink {
    TLContactsMyLink() :
        contact(false),
        tlType(TLValue::ContactsMyLinkEmpty) { }

    bool contact;
    TLValue tlType;
};

struct TLDcOption {
    TLDcOption() :
        id(0),
        port(0),
        tlType(TLValue::DcOption) { }

    quint32 id;
    QString hostname;
    QString ipAddress;
    quint32 port;
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

struct TLGlobalPrivacySettings {
    TLGlobalPrivacySettings() :
        noSuggestions(false),
        hideContacts(false),
        hideLocated(false),
        hideLastVisit(false),
        tlType(TLValue::GlobalPrivacySettings) { }

    bool noSuggestions;
    bool hideContacts;
    bool hideLocated;
    bool hideLastVisit;
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

struct TLInputGeoChat {
    TLInputGeoChat() :
        chatId(0),
        accessHash(0),
        tlType(TLValue::InputGeoChat) { }

    quint32 chatId;
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
        userId(0),
        accessHash(0),
        chatId(0),
        tlType(TLValue::InputPeerEmpty) { }

    quint32 userId;
    quint64 accessHash;
    quint32 chatId;
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

struct TLMessagesAffectedHistory {
    TLMessagesAffectedHistory() :
        pts(0),
        seq(0),
        offset(0),
        tlType(TLValue::MessagesAffectedHistory) { }

    quint32 pts;
    quint32 seq;
    quint32 offset;
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
        tlType(TLValue::PeerUser) { }

    quint32 userId;
    quint32 chatId;
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

struct TLSendMessageAction {
    TLSendMessageAction() :
        tlType(TLValue::SendMessageTypingAction) { }

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
        userId(0),
        date(0),
        duration(0),
        size(0),
        dcId(0),
        w(0),
        h(0),
        tlType(TLValue::VideoEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 userId;
    quint32 date;
    QString caption;
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
        testMode(false),
        thisDc(0),
        chatSizeMax(0),
        broadcastSizeMax(0),
        tlType(TLValue::Config) { }

    quint32 date;
    bool testMode;
    quint32 thisDc;
    TLVector<TLDcOption> dcOptions;
    quint32 chatSizeMax;
    quint32 broadcastSizeMax;
    TLValue tlType;
};

struct TLDialog {
    TLDialog() :
        topMessage(0),
        unreadCount(0),
        tlType(TLValue::Dialog) { }

    TLPeer peer;
    quint32 topMessage;
    quint32 unreadCount;
    TLPeerNotifySettings notifySettings;
    TLValue tlType;
};

struct TLDocument {
    TLDocument() :
        id(0),
        accessHash(0),
        userId(0),
        date(0),
        size(0),
        dcId(0),
        tlType(TLValue::DocumentEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 userId;
    quint32 date;
    QString fileName;
    QString mimeType;
    quint32 size;
    TLPhotoSize thumb;
    quint32 dcId;
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
    TLInputPhoto id;
    TLInputGeoPoint geoPoint;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 duration;
    quint32 w;
    quint32 h;
    QString mimeType;
    TLInputFile thumb;
    QString fileName;
    TLValue tlType;
};

struct TLInputNotifyPeer {
    TLInputNotifyPeer() :
        tlType(TLValue::InputNotifyPeer) { }

    TLInputPeer peer;
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
        userId(0),
        date(0),
        tlType(TLValue::PhotoEmpty) { }

    quint64 id;
    quint64 accessHash;
    quint32 userId;
    quint32 date;
    QString caption;
    TLGeoPoint geo;
    TLVector<TLPhotoSize> sizes;
    TLValue tlType;
};

struct TLUser {
    TLUser() :
        id(0),
        inactive(false),
        accessHash(0),
        tlType(TLValue::UserEmpty) { }

    quint32 id;
    QString firstName;
    QString lastName;
    QString username;
    QString phone;
    TLUserProfilePhoto photo;
    TLUserStatus status;
    bool inactive;
    quint64 accessHash;
    TLValue tlType;
};

struct TLAuthAuthorization {
    TLAuthAuthorization() :
        expires(0),
        tlType(TLValue::AuthAuthorization) { }

    quint32 expires;
    TLUser user;
    TLValue tlType;
};

struct TLChat {
    TLChat() :
        id(0),
        participantsCount(0),
        date(0),
        left(false),
        version(0),
        accessHash(0),
        checkedIn(false),
        tlType(TLValue::ChatEmpty) { }

    quint32 id;
    QString title;
    TLChatPhoto photo;
    quint32 participantsCount;
    quint32 date;
    bool left;
    quint32 version;
    quint64 accessHash;
    QString address;
    QString venue;
    TLGeoPoint geo;
    bool checkedIn;
    TLValue tlType;
};

struct TLChatFull {
    TLChatFull() :
        id(0),
        tlType(TLValue::ChatFull) { }

    quint32 id;
    TLChatParticipants participants;
    TLPhoto chatPhoto;
    TLPeerNotifySettings notifySettings;
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
        tlType(TLValue::ContactsContacts) { }

    TLVector<TLContact> contacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsFound {
    TLContactsFound() :
        tlType(TLValue::ContactsFound) { }

    TLVector<TLContactFound> results;
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

    TLContactsMyLink myLink;
    TLContactsForeignLink foreignLink;
    TLUser user;
    TLValue tlType;
};

struct TLContactsSuggested {
    TLContactsSuggested() :
        tlType(TLValue::ContactsSuggested) { }

    TLVector<TLContactSuggested> results;
    TLVector<TLUser> users;
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
        tlType(TLValue::MessageActionEmpty) { }

    QString title;
    TLVector<quint32> users;
    TLPhoto photo;
    quint32 userId;
    QString address;
    TLValue tlType;
};

struct TLMessageMedia {
    TLMessageMedia() :
        userId(0),
        tlType(TLValue::MessageMediaEmpty) { }

    TLPhoto photo;
    TLVideo video;
    TLGeoPoint geo;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    quint32 userId;
    QByteArray bytes;
    TLDocument document;
    TLAudio audio;
    TLValue tlType;
};

struct TLMessagesChat {
    TLMessagesChat() :
        tlType(TLValue::MessagesChat) { }

    TLChat chat;
    TLVector<TLUser> users;
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
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesSentMessage {
    TLMessagesSentMessage() :
        id(0),
        date(0),
        pts(0),
        seq(0),
        tlType(TLValue::MessagesSentMessage) { }

    quint32 id;
    quint32 date;
    quint32 pts;
    quint32 seq;
    TLVector<TLContactsLink> links;
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
    QString realFirstName;
    QString realLastName;
    TLValue tlType;
};

struct TLGeoChatMessage {
    TLGeoChatMessage() :
        chatId(0),
        id(0),
        fromId(0),
        date(0),
        tlType(TLValue::GeoChatMessageEmpty) { }

    quint32 chatId;
    quint32 id;
    quint32 fromId;
    quint32 date;
    QString message;
    TLMessageMedia media;
    TLMessageAction action;
    TLValue tlType;
};

struct TLGeochatsLocated {
    TLGeochatsLocated() :
        tlType(TLValue::GeochatsLocated) { }

    TLVector<TLChatLocated> results;
    TLVector<TLGeoChatMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLGeochatsMessages {
    TLGeochatsMessages() :
        count(0),
        tlType(TLValue::GeochatsMessages) { }

    TLVector<TLGeoChatMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLGeochatsStatedMessage {
    TLGeochatsStatedMessage() :
        seq(0),
        tlType(TLValue::GeochatsStatedMessage) { }

    TLGeoChatMessage message;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 seq;
    TLValue tlType;
};

struct TLMessage {
    TLMessage() :
        id(0),
        flags(0),
        fromId(0),
        date(0),
        fwdFromId(0),
        fwdDate(0),
        tlType(TLValue::MessageEmpty) { }

    quint32 id;
    quint32 flags;
    quint32 fromId;
    TLPeer toId;
    quint32 date;
    QString message;
    TLMessageMedia media;
    quint32 fwdFromId;
    quint32 fwdDate;
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

struct TLMessagesMessage {
    TLMessagesMessage() :
        tlType(TLValue::MessagesMessageEmpty) { }

    TLMessage message;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesMessages {
    TLMessagesMessages() :
        count(0),
        tlType(TLValue::MessagesMessages) { }

    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLMessagesStatedMessage {
    TLMessagesStatedMessage() :
        pts(0),
        seq(0),
        tlType(TLValue::MessagesStatedMessage) { }

    TLMessage message;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 pts;
    quint32 seq;
    TLVector<TLContactsLink> links;
    TLValue tlType;
};

struct TLMessagesStatedMessages {
    TLMessagesStatedMessages() :
        pts(0),
        seq(0),
        tlType(TLValue::MessagesStatedMessages) { }

    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 pts;
    quint32 seq;
    TLVector<TLContactsLink> links;
    TLValue tlType;
};

struct TLUpdate {
    TLUpdate() :
        pts(0),
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
        tlType(TLValue::UpdateNewMessage) { }

    TLMessage message;
    quint32 pts;
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
    TLContactsMyLink myLink;
    TLContactsForeignLink foreignLink;
    quint64 authKeyId;
    QString device;
    QString location;
    quint32 qts;
    TLEncryptedChat chat;
    quint32 maxDate;
    quint32 inviterId;
    quint32 version;
    TLVector<TLDcOption> dcOptions;
    bool blocked;
    TLNotifyPeer peer;
    TLPeerNotifySettings notifySettings;
    QString type;
    TLMessageMedia media;
    bool popup;
    TLValue tlType;
};

struct TLUpdates {
    TLUpdates() :
        id(0),
        fromId(0),
        pts(0),
        date(0),
        seq(0),
        chatId(0),
        seqStart(0),
        tlType(TLValue::UpdatesTooLong) { }

    quint32 id;
    quint32 fromId;
    QString message;
    quint32 pts;
    quint32 date;
    quint32 seq;
    quint32 chatId;
    TLUpdate update;
    TLVector<TLUpdate> updates;
    TLVector<TLUser> users;
    TLVector<TLChat> chats;
    quint32 seqStart;
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
