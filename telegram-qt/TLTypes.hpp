#ifndef TLTYPES_HPP
#define TLTYPES_HPP

#include "TLNumbers.hpp"
#include "TLValues.h"

#include <QMetaType>
#include <QVector>

template <typename T>
class TLVector : public QVector<T>
{
public:
    inline TLVector() : QVector<T>(), tlType(Vector) { }
    explicit TLVector(int size) : QVector<T>(size), tlType(Vector) { }
    TLVector(int size, const T &t) : QVector<T>(size, t), tlType(Vector) { }
    inline TLVector(const TLVector<T> &v) : QVector<T>(v), tlType(v.tlType) { }
    inline TLVector(const QVector<T> &v) : QVector<T>(v), tlType(Vector) { }

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
        tlType(AudioEmpty) { }

    TLAudio(const TLAudio &anotherAudio) :
        id(anotherAudio.id),
        accessHash(anotherAudio.accessHash),
        userId(anotherAudio.userId),
        date(anotherAudio.date),
        duration(anotherAudio.duration),
        mimeType(anotherAudio.mimeType),
        size(anotherAudio.size),
        dcId(anotherAudio.dcId),
        tlType(anotherAudio.tlType) { }

    TLAudio &operator=(const TLAudio &anotherAudio) {
        id = anotherAudio.id;
        accessHash = anotherAudio.accessHash;
        userId = anotherAudio.userId;
        date = anotherAudio.date;
        duration = anotherAudio.duration;
        mimeType = anotherAudio.mimeType;
        size = anotherAudio.size;
        dcId = anotherAudio.dcId;
        tlType = anotherAudio.tlType;

        return *this;
    }

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
        tlType(AuthCheckedPhone) { }

    TLAuthCheckedPhone(const TLAuthCheckedPhone &anotherAuthCheckedPhone) :
        phoneRegistered(anotherAuthCheckedPhone.phoneRegistered),
        phoneInvited(anotherAuthCheckedPhone.phoneInvited),
        tlType(anotherAuthCheckedPhone.tlType) { }

    TLAuthCheckedPhone &operator=(const TLAuthCheckedPhone &anotherAuthCheckedPhone) {
        phoneRegistered = anotherAuthCheckedPhone.phoneRegistered;
        phoneInvited = anotherAuthCheckedPhone.phoneInvited;
        tlType = anotherAuthCheckedPhone.tlType;

        return *this;
    }

    bool phoneRegistered;
    bool phoneInvited;
    TLValue tlType;
};

struct TLAuthExportedAuthorization {
    TLAuthExportedAuthorization() :
        id(0),
        tlType(AuthExportedAuthorization) { }

    TLAuthExportedAuthorization(const TLAuthExportedAuthorization &anotherAuthExportedAuthorization) :
        id(anotherAuthExportedAuthorization.id),
        bytes(anotherAuthExportedAuthorization.bytes),
        tlType(anotherAuthExportedAuthorization.tlType) { }

    TLAuthExportedAuthorization &operator=(const TLAuthExportedAuthorization &anotherAuthExportedAuthorization) {
        id = anotherAuthExportedAuthorization.id;
        bytes = anotherAuthExportedAuthorization.bytes;
        tlType = anotherAuthExportedAuthorization.tlType;

        return *this;
    }

    quint32 id;
    QByteArray bytes;
    TLValue tlType;
};

struct TLAuthSentCode {
    TLAuthSentCode() :
        phoneRegistered(false),
        sendCallTimeout(0),
        isPassword(false),
        tlType(AuthSentCode) { }

    TLAuthSentCode(const TLAuthSentCode &anotherAuthSentCode) :
        phoneRegistered(anotherAuthSentCode.phoneRegistered),
        phoneCodeHash(anotherAuthSentCode.phoneCodeHash),
        sendCallTimeout(anotherAuthSentCode.sendCallTimeout),
        isPassword(anotherAuthSentCode.isPassword),
        tlType(anotherAuthSentCode.tlType) { }

    TLAuthSentCode &operator=(const TLAuthSentCode &anotherAuthSentCode) {
        phoneRegistered = anotherAuthSentCode.phoneRegistered;
        phoneCodeHash = anotherAuthSentCode.phoneCodeHash;
        sendCallTimeout = anotherAuthSentCode.sendCallTimeout;
        isPassword = anotherAuthSentCode.isPassword;
        tlType = anotherAuthSentCode.tlType;

        return *this;
    }

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
        tlType(ChatLocated) { }

    TLChatLocated(const TLChatLocated &anotherChatLocated) :
        chatId(anotherChatLocated.chatId),
        distance(anotherChatLocated.distance),
        tlType(anotherChatLocated.tlType) { }

    TLChatLocated &operator=(const TLChatLocated &anotherChatLocated) {
        chatId = anotherChatLocated.chatId;
        distance = anotherChatLocated.distance;
        tlType = anotherChatLocated.tlType;

        return *this;
    }

    quint32 chatId;
    quint32 distance;
    TLValue tlType;
};

struct TLChatParticipant {
    TLChatParticipant() :
        userId(0),
        inviterId(0),
        date(0),
        tlType(ChatParticipant) { }

    TLChatParticipant(const TLChatParticipant &anotherChatParticipant) :
        userId(anotherChatParticipant.userId),
        inviterId(anotherChatParticipant.inviterId),
        date(anotherChatParticipant.date),
        tlType(anotherChatParticipant.tlType) { }

    TLChatParticipant &operator=(const TLChatParticipant &anotherChatParticipant) {
        userId = anotherChatParticipant.userId;
        inviterId = anotherChatParticipant.inviterId;
        date = anotherChatParticipant.date;
        tlType = anotherChatParticipant.tlType;

        return *this;
    }

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
        tlType(ChatParticipantsForbidden) { }

    TLChatParticipants(const TLChatParticipants &anotherChatParticipants) :
        chatId(anotherChatParticipants.chatId),
        adminId(anotherChatParticipants.adminId),
        participants(anotherChatParticipants.participants),
        version(anotherChatParticipants.version),
        tlType(anotherChatParticipants.tlType) { }

    TLChatParticipants &operator=(const TLChatParticipants &anotherChatParticipants) {
        chatId = anotherChatParticipants.chatId;
        adminId = anotherChatParticipants.adminId;
        participants = anotherChatParticipants.participants;
        version = anotherChatParticipants.version;
        tlType = anotherChatParticipants.tlType;

        return *this;
    }

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
        tlType(Contact) { }

    TLContact(const TLContact &anotherContact) :
        userId(anotherContact.userId),
        mutual(anotherContact.mutual),
        tlType(anotherContact.tlType) { }

    TLContact &operator=(const TLContact &anotherContact) {
        userId = anotherContact.userId;
        mutual = anotherContact.mutual;
        tlType = anotherContact.tlType;

        return *this;
    }

    quint32 userId;
    bool mutual;
    TLValue tlType;
};

struct TLContactBlocked {
    TLContactBlocked() :
        userId(0),
        date(0),
        tlType(ContactBlocked) { }

    TLContactBlocked(const TLContactBlocked &anotherContactBlocked) :
        userId(anotherContactBlocked.userId),
        date(anotherContactBlocked.date),
        tlType(anotherContactBlocked.tlType) { }

    TLContactBlocked &operator=(const TLContactBlocked &anotherContactBlocked) {
        userId = anotherContactBlocked.userId;
        date = anotherContactBlocked.date;
        tlType = anotherContactBlocked.tlType;

        return *this;
    }

    quint32 userId;
    quint32 date;
    TLValue tlType;
};

struct TLContactFound {
    TLContactFound() :
        userId(0),
        tlType(ContactFound) { }

    TLContactFound(const TLContactFound &anotherContactFound) :
        userId(anotherContactFound.userId),
        tlType(anotherContactFound.tlType) { }

    TLContactFound &operator=(const TLContactFound &anotherContactFound) {
        userId = anotherContactFound.userId;
        tlType = anotherContactFound.tlType;

        return *this;
    }

    quint32 userId;
    TLValue tlType;
};

struct TLContactStatus {
    TLContactStatus() :
        userId(0),
        expires(0),
        tlType(ContactStatus) { }

    TLContactStatus(const TLContactStatus &anotherContactStatus) :
        userId(anotherContactStatus.userId),
        expires(anotherContactStatus.expires),
        tlType(anotherContactStatus.tlType) { }

    TLContactStatus &operator=(const TLContactStatus &anotherContactStatus) {
        userId = anotherContactStatus.userId;
        expires = anotherContactStatus.expires;
        tlType = anotherContactStatus.tlType;

        return *this;
    }

    quint32 userId;
    quint32 expires;
    TLValue tlType;
};

struct TLContactSuggested {
    TLContactSuggested() :
        userId(0),
        mutualContacts(0),
        tlType(ContactSuggested) { }

    TLContactSuggested(const TLContactSuggested &anotherContactSuggested) :
        userId(anotherContactSuggested.userId),
        mutualContacts(anotherContactSuggested.mutualContacts),
        tlType(anotherContactSuggested.tlType) { }

    TLContactSuggested &operator=(const TLContactSuggested &anotherContactSuggested) {
        userId = anotherContactSuggested.userId;
        mutualContacts = anotherContactSuggested.mutualContacts;
        tlType = anotherContactSuggested.tlType;

        return *this;
    }

    quint32 userId;
    quint32 mutualContacts;
    TLValue tlType;
};

struct TLContactsForeignLink {
    TLContactsForeignLink() :
        hasPhone(false),
        tlType(ContactsForeignLinkUnknown) { }

    TLContactsForeignLink(const TLContactsForeignLink &anotherContactsForeignLink) :
        hasPhone(anotherContactsForeignLink.hasPhone),
        tlType(anotherContactsForeignLink.tlType) { }

    TLContactsForeignLink &operator=(const TLContactsForeignLink &anotherContactsForeignLink) {
        hasPhone = anotherContactsForeignLink.hasPhone;
        tlType = anotherContactsForeignLink.tlType;

        return *this;
    }

    bool hasPhone;
    TLValue tlType;
};

struct TLContactsMyLink {
    TLContactsMyLink() :
        contact(false),
        tlType(ContactsMyLinkEmpty) { }

    TLContactsMyLink(const TLContactsMyLink &anotherContactsMyLink) :
        contact(anotherContactsMyLink.contact),
        tlType(anotherContactsMyLink.tlType) { }

    TLContactsMyLink &operator=(const TLContactsMyLink &anotherContactsMyLink) {
        contact = anotherContactsMyLink.contact;
        tlType = anotherContactsMyLink.tlType;

        return *this;
    }

    bool contact;
    TLValue tlType;
};

struct TLDcOption {
    TLDcOption() :
        id(0),
        port(0),
        tlType(DcOption) { }

    TLDcOption(const TLDcOption &anotherDcOption) :
        id(anotherDcOption.id),
        hostname(anotherDcOption.hostname),
        ipAddress(anotherDcOption.ipAddress),
        port(anotherDcOption.port),
        tlType(anotherDcOption.tlType) { }

    TLDcOption &operator=(const TLDcOption &anotherDcOption) {
        id = anotherDcOption.id;
        hostname = anotherDcOption.hostname;
        ipAddress = anotherDcOption.ipAddress;
        port = anotherDcOption.port;
        tlType = anotherDcOption.tlType;

        return *this;
    }

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
        tlType(EncryptedChatEmpty) { }

    TLEncryptedChat(const TLEncryptedChat &anotherEncryptedChat) :
        id(anotherEncryptedChat.id),
        accessHash(anotherEncryptedChat.accessHash),
        date(anotherEncryptedChat.date),
        adminId(anotherEncryptedChat.adminId),
        participantId(anotherEncryptedChat.participantId),
        gA(anotherEncryptedChat.gA),
        gAOrB(anotherEncryptedChat.gAOrB),
        keyFingerprint(anotherEncryptedChat.keyFingerprint),
        tlType(anotherEncryptedChat.tlType) { }

    TLEncryptedChat &operator=(const TLEncryptedChat &anotherEncryptedChat) {
        id = anotherEncryptedChat.id;
        accessHash = anotherEncryptedChat.accessHash;
        date = anotherEncryptedChat.date;
        adminId = anotherEncryptedChat.adminId;
        participantId = anotherEncryptedChat.participantId;
        gA = anotherEncryptedChat.gA;
        gAOrB = anotherEncryptedChat.gAOrB;
        keyFingerprint = anotherEncryptedChat.keyFingerprint;
        tlType = anotherEncryptedChat.tlType;

        return *this;
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
    TLEncryptedFile() :
        id(0),
        accessHash(0),
        size(0),
        dcId(0),
        keyFingerprint(0),
        tlType(EncryptedFileEmpty) { }

    TLEncryptedFile(const TLEncryptedFile &anotherEncryptedFile) :
        id(anotherEncryptedFile.id),
        accessHash(anotherEncryptedFile.accessHash),
        size(anotherEncryptedFile.size),
        dcId(anotherEncryptedFile.dcId),
        keyFingerprint(anotherEncryptedFile.keyFingerprint),
        tlType(anotherEncryptedFile.tlType) { }

    TLEncryptedFile &operator=(const TLEncryptedFile &anotherEncryptedFile) {
        id = anotherEncryptedFile.id;
        accessHash = anotherEncryptedFile.accessHash;
        size = anotherEncryptedFile.size;
        dcId = anotherEncryptedFile.dcId;
        keyFingerprint = anotherEncryptedFile.keyFingerprint;
        tlType = anotherEncryptedFile.tlType;

        return *this;
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
        tlType(EncryptedMessage) { }

    TLEncryptedMessage(const TLEncryptedMessage &anotherEncryptedMessage) :
        randomId(anotherEncryptedMessage.randomId),
        chatId(anotherEncryptedMessage.chatId),
        date(anotherEncryptedMessage.date),
        bytes(anotherEncryptedMessage.bytes),
        file(anotherEncryptedMessage.file),
        tlType(anotherEncryptedMessage.tlType) { }

    TLEncryptedMessage &operator=(const TLEncryptedMessage &anotherEncryptedMessage) {
        randomId = anotherEncryptedMessage.randomId;
        chatId = anotherEncryptedMessage.chatId;
        date = anotherEncryptedMessage.date;
        bytes = anotherEncryptedMessage.bytes;
        file = anotherEncryptedMessage.file;
        tlType = anotherEncryptedMessage.tlType;

        return *this;
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
        tlType(Error) { }

    TLError(const TLError &anotherError) :
        code(anotherError.code),
        text(anotherError.text),
        tlType(anotherError.tlType) { }

    TLError &operator=(const TLError &anotherError) {
        code = anotherError.code;
        text = anotherError.text;
        tlType = anotherError.tlType;

        return *this;
    }

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
        tlType(FileLocationUnavailable) { }

    TLFileLocation(const TLFileLocation &anotherFileLocation) :
        volumeId(anotherFileLocation.volumeId),
        localId(anotherFileLocation.localId),
        secret(anotherFileLocation.secret),
        dcId(anotherFileLocation.dcId),
        tlType(anotherFileLocation.tlType) { }

    TLFileLocation &operator=(const TLFileLocation &anotherFileLocation) {
        volumeId = anotherFileLocation.volumeId;
        localId = anotherFileLocation.localId;
        secret = anotherFileLocation.secret;
        dcId = anotherFileLocation.dcId;
        tlType = anotherFileLocation.tlType;

        return *this;
    }

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
        tlType(GeoPointEmpty) { }

    TLGeoPoint(const TLGeoPoint &anotherGeoPoint) :
        longitude(anotherGeoPoint.longitude),
        latitude(anotherGeoPoint.latitude),
        tlType(anotherGeoPoint.tlType) { }

    TLGeoPoint &operator=(const TLGeoPoint &anotherGeoPoint) {
        longitude = anotherGeoPoint.longitude;
        latitude = anotherGeoPoint.latitude;
        tlType = anotherGeoPoint.tlType;

        return *this;
    }

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
        tlType(GlobalPrivacySettings) { }

    TLGlobalPrivacySettings(const TLGlobalPrivacySettings &anotherGlobalPrivacySettings) :
        noSuggestions(anotherGlobalPrivacySettings.noSuggestions),
        hideContacts(anotherGlobalPrivacySettings.hideContacts),
        hideLocated(anotherGlobalPrivacySettings.hideLocated),
        hideLastVisit(anotherGlobalPrivacySettings.hideLastVisit),
        tlType(anotherGlobalPrivacySettings.tlType) { }

    TLGlobalPrivacySettings &operator=(const TLGlobalPrivacySettings &anotherGlobalPrivacySettings) {
        noSuggestions = anotherGlobalPrivacySettings.noSuggestions;
        hideContacts = anotherGlobalPrivacySettings.hideContacts;
        hideLocated = anotherGlobalPrivacySettings.hideLocated;
        hideLastVisit = anotherGlobalPrivacySettings.hideLastVisit;
        tlType = anotherGlobalPrivacySettings.tlType;

        return *this;
    }

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
        tlType(HelpAppUpdate) { }

    TLHelpAppUpdate(const TLHelpAppUpdate &anotherHelpAppUpdate) :
        id(anotherHelpAppUpdate.id),
        critical(anotherHelpAppUpdate.critical),
        url(anotherHelpAppUpdate.url),
        text(anotherHelpAppUpdate.text),
        tlType(anotherHelpAppUpdate.tlType) { }

    TLHelpAppUpdate &operator=(const TLHelpAppUpdate &anotherHelpAppUpdate) {
        id = anotherHelpAppUpdate.id;
        critical = anotherHelpAppUpdate.critical;
        url = anotherHelpAppUpdate.url;
        text = anotherHelpAppUpdate.text;
        tlType = anotherHelpAppUpdate.tlType;

        return *this;
    }

    quint32 id;
    bool critical;
    QString url;
    QString text;
    TLValue tlType;
};

struct TLHelpInviteText {
    TLHelpInviteText() :
        tlType(HelpInviteText) { }

    TLHelpInviteText(const TLHelpInviteText &anotherHelpInviteText) :
        message(anotherHelpInviteText.message),
        tlType(anotherHelpInviteText.tlType) { }

    TLHelpInviteText &operator=(const TLHelpInviteText &anotherHelpInviteText) {
        message = anotherHelpInviteText.message;
        tlType = anotherHelpInviteText.tlType;

        return *this;
    }

    QString message;
    TLValue tlType;
};

struct TLImportedContact {
    TLImportedContact() :
        userId(0),
        clientId(0),
        tlType(ImportedContact) { }

    TLImportedContact(const TLImportedContact &anotherImportedContact) :
        userId(anotherImportedContact.userId),
        clientId(anotherImportedContact.clientId),
        tlType(anotherImportedContact.tlType) { }

    TLImportedContact &operator=(const TLImportedContact &anotherImportedContact) {
        userId = anotherImportedContact.userId;
        clientId = anotherImportedContact.clientId;
        tlType = anotherImportedContact.tlType;

        return *this;
    }

    quint32 userId;
    quint64 clientId;
    TLValue tlType;
};

struct TLInputAppEvent {
    TLInputAppEvent() :
        time(0),
        peer(0),
        tlType(InputAppEvent) { }

    TLInputAppEvent(const TLInputAppEvent &anotherInputAppEvent) :
        time(anotherInputAppEvent.time),
        type(anotherInputAppEvent.type),
        peer(anotherInputAppEvent.peer),
        data(anotherInputAppEvent.data),
        tlType(anotherInputAppEvent.tlType) { }

    TLInputAppEvent &operator=(const TLInputAppEvent &anotherInputAppEvent) {
        time = anotherInputAppEvent.time;
        type = anotherInputAppEvent.type;
        peer = anotherInputAppEvent.peer;
        data = anotherInputAppEvent.data;
        tlType = anotherInputAppEvent.tlType;

        return *this;
    }

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
        tlType(InputAudioEmpty) { }

    TLInputAudio(const TLInputAudio &anotherInputAudio) :
        id(anotherInputAudio.id),
        accessHash(anotherInputAudio.accessHash),
        tlType(anotherInputAudio.tlType) { }

    TLInputAudio &operator=(const TLInputAudio &anotherInputAudio) {
        id = anotherInputAudio.id;
        accessHash = anotherInputAudio.accessHash;
        tlType = anotherInputAudio.tlType;

        return *this;
    }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputContact {
    TLInputContact() :
        clientId(0),
        tlType(InputPhoneContact) { }

    TLInputContact(const TLInputContact &anotherInputContact) :
        clientId(anotherInputContact.clientId),
        phone(anotherInputContact.phone),
        firstName(anotherInputContact.firstName),
        lastName(anotherInputContact.lastName),
        tlType(anotherInputContact.tlType) { }

    TLInputContact &operator=(const TLInputContact &anotherInputContact) {
        clientId = anotherInputContact.clientId;
        phone = anotherInputContact.phone;
        firstName = anotherInputContact.firstName;
        lastName = anotherInputContact.lastName;
        tlType = anotherInputContact.tlType;

        return *this;
    }

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
        tlType(InputDocumentEmpty) { }

    TLInputDocument(const TLInputDocument &anotherInputDocument) :
        id(anotherInputDocument.id),
        accessHash(anotherInputDocument.accessHash),
        tlType(anotherInputDocument.tlType) { }

    TLInputDocument &operator=(const TLInputDocument &anotherInputDocument) {
        id = anotherInputDocument.id;
        accessHash = anotherInputDocument.accessHash;
        tlType = anotherInputDocument.tlType;

        return *this;
    }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputEncryptedChat {
    TLInputEncryptedChat() :
        chatId(0),
        accessHash(0),
        tlType(InputEncryptedChat) { }

    TLInputEncryptedChat(const TLInputEncryptedChat &anotherInputEncryptedChat) :
        chatId(anotherInputEncryptedChat.chatId),
        accessHash(anotherInputEncryptedChat.accessHash),
        tlType(anotherInputEncryptedChat.tlType) { }

    TLInputEncryptedChat &operator=(const TLInputEncryptedChat &anotherInputEncryptedChat) {
        chatId = anotherInputEncryptedChat.chatId;
        accessHash = anotherInputEncryptedChat.accessHash;
        tlType = anotherInputEncryptedChat.tlType;

        return *this;
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
        tlType(InputEncryptedFileEmpty) { }

    TLInputEncryptedFile(const TLInputEncryptedFile &anotherInputEncryptedFile) :
        id(anotherInputEncryptedFile.id),
        parts(anotherInputEncryptedFile.parts),
        md5Checksum(anotherInputEncryptedFile.md5Checksum),
        keyFingerprint(anotherInputEncryptedFile.keyFingerprint),
        accessHash(anotherInputEncryptedFile.accessHash),
        tlType(anotherInputEncryptedFile.tlType) { }

    TLInputEncryptedFile &operator=(const TLInputEncryptedFile &anotherInputEncryptedFile) {
        id = anotherInputEncryptedFile.id;
        parts = anotherInputEncryptedFile.parts;
        md5Checksum = anotherInputEncryptedFile.md5Checksum;
        keyFingerprint = anotherInputEncryptedFile.keyFingerprint;
        accessHash = anotherInputEncryptedFile.accessHash;
        tlType = anotherInputEncryptedFile.tlType;

        return *this;
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
        tlType(InputFile) { }

    TLInputFile(const TLInputFile &anotherInputFile) :
        id(anotherInputFile.id),
        parts(anotherInputFile.parts),
        name(anotherInputFile.name),
        md5Checksum(anotherInputFile.md5Checksum),
        tlType(anotherInputFile.tlType) { }

    TLInputFile &operator=(const TLInputFile &anotherInputFile) {
        id = anotherInputFile.id;
        parts = anotherInputFile.parts;
        name = anotherInputFile.name;
        md5Checksum = anotherInputFile.md5Checksum;
        tlType = anotherInputFile.tlType;

        return *this;
    }

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
        tlType(InputFileLocation) { }

    TLInputFileLocation(const TLInputFileLocation &anotherInputFileLocation) :
        volumeId(anotherInputFileLocation.volumeId),
        localId(anotherInputFileLocation.localId),
        secret(anotherInputFileLocation.secret),
        id(anotherInputFileLocation.id),
        accessHash(anotherInputFileLocation.accessHash),
        tlType(anotherInputFileLocation.tlType) { }

    TLInputFileLocation &operator=(const TLInputFileLocation &anotherInputFileLocation) {
        volumeId = anotherInputFileLocation.volumeId;
        localId = anotherInputFileLocation.localId;
        secret = anotherInputFileLocation.secret;
        id = anotherInputFileLocation.id;
        accessHash = anotherInputFileLocation.accessHash;
        tlType = anotherInputFileLocation.tlType;

        return *this;
    }

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
        tlType(InputGeoChat) { }

    TLInputGeoChat(const TLInputGeoChat &anotherInputGeoChat) :
        chatId(anotherInputGeoChat.chatId),
        accessHash(anotherInputGeoChat.accessHash),
        tlType(anotherInputGeoChat.tlType) { }

    TLInputGeoChat &operator=(const TLInputGeoChat &anotherInputGeoChat) {
        chatId = anotherInputGeoChat.chatId;
        accessHash = anotherInputGeoChat.accessHash;
        tlType = anotherInputGeoChat.tlType;

        return *this;
    }

    quint32 chatId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputGeoPoint {
    TLInputGeoPoint() :
        latitude(0),
        longitude(0),
        tlType(InputGeoPointEmpty) { }

    TLInputGeoPoint(const TLInputGeoPoint &anotherInputGeoPoint) :
        latitude(anotherInputGeoPoint.latitude),
        longitude(anotherInputGeoPoint.longitude),
        tlType(anotherInputGeoPoint.tlType) { }

    TLInputGeoPoint &operator=(const TLInputGeoPoint &anotherInputGeoPoint) {
        latitude = anotherInputGeoPoint.latitude;
        longitude = anotherInputGeoPoint.longitude;
        tlType = anotherInputGeoPoint.tlType;

        return *this;
    }

    double latitude;
    double longitude;
    TLValue tlType;
};

struct TLInputPeer {
    TLInputPeer() :
        userId(0),
        accessHash(0),
        chatId(0),
        tlType(InputPeerEmpty) { }

    TLInputPeer(const TLInputPeer &anotherInputPeer) :
        userId(anotherInputPeer.userId),
        accessHash(anotherInputPeer.accessHash),
        chatId(anotherInputPeer.chatId),
        tlType(anotherInputPeer.tlType) { }

    TLInputPeer &operator=(const TLInputPeer &anotherInputPeer) {
        userId = anotherInputPeer.userId;
        accessHash = anotherInputPeer.accessHash;
        chatId = anotherInputPeer.chatId;
        tlType = anotherInputPeer.tlType;

        return *this;
    }

    quint32 userId;
    quint64 accessHash;
    quint32 chatId;
    TLValue tlType;
};

struct TLInputPeerNotifyEvents {
    TLInputPeerNotifyEvents() :
        tlType(InputPeerNotifyEventsEmpty) { }

    TLInputPeerNotifyEvents(const TLInputPeerNotifyEvents &anotherInputPeerNotifyEvents) :
        tlType(anotherInputPeerNotifyEvents.tlType) { }

    TLInputPeerNotifyEvents &operator=(const TLInputPeerNotifyEvents &anotherInputPeerNotifyEvents) {
        tlType = anotherInputPeerNotifyEvents.tlType;

        return *this;
    }

    TLValue tlType;
};

struct TLInputPeerNotifySettings {
    TLInputPeerNotifySettings() :
        muteUntil(0),
        showPreviews(false),
        eventsMask(0),
        tlType(InputPeerNotifySettings) { }

    TLInputPeerNotifySettings(const TLInputPeerNotifySettings &anotherInputPeerNotifySettings) :
        muteUntil(anotherInputPeerNotifySettings.muteUntil),
        sound(anotherInputPeerNotifySettings.sound),
        showPreviews(anotherInputPeerNotifySettings.showPreviews),
        eventsMask(anotherInputPeerNotifySettings.eventsMask),
        tlType(anotherInputPeerNotifySettings.tlType) { }

    TLInputPeerNotifySettings &operator=(const TLInputPeerNotifySettings &anotherInputPeerNotifySettings) {
        muteUntil = anotherInputPeerNotifySettings.muteUntil;
        sound = anotherInputPeerNotifySettings.sound;
        showPreviews = anotherInputPeerNotifySettings.showPreviews;
        eventsMask = anotherInputPeerNotifySettings.eventsMask;
        tlType = anotherInputPeerNotifySettings.tlType;

        return *this;
    }

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
        tlType(InputPhotoEmpty) { }

    TLInputPhoto(const TLInputPhoto &anotherInputPhoto) :
        id(anotherInputPhoto.id),
        accessHash(anotherInputPhoto.accessHash),
        tlType(anotherInputPhoto.tlType) { }

    TLInputPhoto &operator=(const TLInputPhoto &anotherInputPhoto) {
        id = anotherInputPhoto.id;
        accessHash = anotherInputPhoto.accessHash;
        tlType = anotherInputPhoto.tlType;

        return *this;
    }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputPhotoCrop {
    TLInputPhotoCrop() :
        cropLeft(0),
        cropTop(0),
        cropWidth(0),
        tlType(InputPhotoCropAuto) { }

    TLInputPhotoCrop(const TLInputPhotoCrop &anotherInputPhotoCrop) :
        cropLeft(anotherInputPhotoCrop.cropLeft),
        cropTop(anotherInputPhotoCrop.cropTop),
        cropWidth(anotherInputPhotoCrop.cropWidth),
        tlType(anotherInputPhotoCrop.tlType) { }

    TLInputPhotoCrop &operator=(const TLInputPhotoCrop &anotherInputPhotoCrop) {
        cropLeft = anotherInputPhotoCrop.cropLeft;
        cropTop = anotherInputPhotoCrop.cropTop;
        cropWidth = anotherInputPhotoCrop.cropWidth;
        tlType = anotherInputPhotoCrop.tlType;

        return *this;
    }

    double cropLeft;
    double cropTop;
    double cropWidth;
    TLValue tlType;
};

struct TLInputUser {
    TLInputUser() :
        userId(0),
        accessHash(0),
        tlType(InputUserEmpty) { }

    TLInputUser(const TLInputUser &anotherInputUser) :
        userId(anotherInputUser.userId),
        accessHash(anotherInputUser.accessHash),
        tlType(anotherInputUser.tlType) { }

    TLInputUser &operator=(const TLInputUser &anotherInputUser) {
        userId = anotherInputUser.userId;
        accessHash = anotherInputUser.accessHash;
        tlType = anotherInputUser.tlType;

        return *this;
    }

    quint32 userId;
    quint64 accessHash;
    TLValue tlType;
};

struct TLInputVideo {
    TLInputVideo() :
        id(0),
        accessHash(0),
        tlType(InputVideoEmpty) { }

    TLInputVideo(const TLInputVideo &anotherInputVideo) :
        id(anotherInputVideo.id),
        accessHash(anotherInputVideo.accessHash),
        tlType(anotherInputVideo.tlType) { }

    TLInputVideo &operator=(const TLInputVideo &anotherInputVideo) {
        id = anotherInputVideo.id;
        accessHash = anotherInputVideo.accessHash;
        tlType = anotherInputVideo.tlType;

        return *this;
    }

    quint64 id;
    quint64 accessHash;
    TLValue tlType;
};

struct TLMessagesAffectedHistory {
    TLMessagesAffectedHistory() :
        pts(0),
        seq(0),
        offset(0),
        tlType(MessagesAffectedHistory) { }

    TLMessagesAffectedHistory(const TLMessagesAffectedHistory &anotherMessagesAffectedHistory) :
        pts(anotherMessagesAffectedHistory.pts),
        seq(anotherMessagesAffectedHistory.seq),
        offset(anotherMessagesAffectedHistory.offset),
        tlType(anotherMessagesAffectedHistory.tlType) { }

    TLMessagesAffectedHistory &operator=(const TLMessagesAffectedHistory &anotherMessagesAffectedHistory) {
        pts = anotherMessagesAffectedHistory.pts;
        seq = anotherMessagesAffectedHistory.seq;
        offset = anotherMessagesAffectedHistory.offset;
        tlType = anotherMessagesAffectedHistory.tlType;

        return *this;
    }

    quint32 pts;
    quint32 seq;
    quint32 offset;
    TLValue tlType;
};

struct TLMessagesDhConfig {
    TLMessagesDhConfig() :
        g(0),
        version(0),
        tlType(MessagesDhConfigNotModified) { }

    TLMessagesDhConfig(const TLMessagesDhConfig &anotherMessagesDhConfig) :
        random(anotherMessagesDhConfig.random),
        g(anotherMessagesDhConfig.g),
        p(anotherMessagesDhConfig.p),
        version(anotherMessagesDhConfig.version),
        tlType(anotherMessagesDhConfig.tlType) { }

    TLMessagesDhConfig &operator=(const TLMessagesDhConfig &anotherMessagesDhConfig) {
        random = anotherMessagesDhConfig.random;
        g = anotherMessagesDhConfig.g;
        p = anotherMessagesDhConfig.p;
        version = anotherMessagesDhConfig.version;
        tlType = anotherMessagesDhConfig.tlType;

        return *this;
    }

    QByteArray random;
    quint32 g;
    QByteArray p;
    quint32 version;
    TLValue tlType;
};

struct TLMessagesFilter {
    TLMessagesFilter() :
        tlType(InputMessagesFilterEmpty) { }

    TLMessagesFilter(const TLMessagesFilter &anotherMessagesFilter) :
        tlType(anotherMessagesFilter.tlType) { }

    TLMessagesFilter &operator=(const TLMessagesFilter &anotherMessagesFilter) {
        tlType = anotherMessagesFilter.tlType;

        return *this;
    }

    TLValue tlType;
};

struct TLMessagesSentEncryptedMessage {
    TLMessagesSentEncryptedMessage() :
        date(0),
        tlType(MessagesSentEncryptedMessage) { }

    TLMessagesSentEncryptedMessage(const TLMessagesSentEncryptedMessage &anotherMessagesSentEncryptedMessage) :
        date(anotherMessagesSentEncryptedMessage.date),
        file(anotherMessagesSentEncryptedMessage.file),
        tlType(anotherMessagesSentEncryptedMessage.tlType) { }

    TLMessagesSentEncryptedMessage &operator=(const TLMessagesSentEncryptedMessage &anotherMessagesSentEncryptedMessage) {
        date = anotherMessagesSentEncryptedMessage.date;
        file = anotherMessagesSentEncryptedMessage.file;
        tlType = anotherMessagesSentEncryptedMessage.tlType;

        return *this;
    }

    quint32 date;
    TLEncryptedFile file;
    TLValue tlType;
};

struct TLNearestDc {
    TLNearestDc() :
        thisDc(0),
        nearestDc(0),
        tlType(NearestDc) { }

    TLNearestDc(const TLNearestDc &anotherNearestDc) :
        country(anotherNearestDc.country),
        thisDc(anotherNearestDc.thisDc),
        nearestDc(anotherNearestDc.nearestDc),
        tlType(anotherNearestDc.tlType) { }

    TLNearestDc &operator=(const TLNearestDc &anotherNearestDc) {
        country = anotherNearestDc.country;
        thisDc = anotherNearestDc.thisDc;
        nearestDc = anotherNearestDc.nearestDc;
        tlType = anotherNearestDc.tlType;

        return *this;
    }

    QString country;
    quint32 thisDc;
    quint32 nearestDc;
    TLValue tlType;
};

struct TLPeer {
    TLPeer() :
        userId(0),
        chatId(0),
        tlType(PeerUser) { }

    TLPeer(const TLPeer &anotherPeer) :
        userId(anotherPeer.userId),
        chatId(anotherPeer.chatId),
        tlType(anotherPeer.tlType) { }

    TLPeer &operator=(const TLPeer &anotherPeer) {
        userId = anotherPeer.userId;
        chatId = anotherPeer.chatId;
        tlType = anotherPeer.tlType;

        return *this;
    }

    quint32 userId;
    quint32 chatId;
    TLValue tlType;
};

struct TLPeerNotifyEvents {
    TLPeerNotifyEvents() :
        tlType(PeerNotifyEventsEmpty) { }

    TLPeerNotifyEvents(const TLPeerNotifyEvents &anotherPeerNotifyEvents) :
        tlType(anotherPeerNotifyEvents.tlType) { }

    TLPeerNotifyEvents &operator=(const TLPeerNotifyEvents &anotherPeerNotifyEvents) {
        tlType = anotherPeerNotifyEvents.tlType;

        return *this;
    }

    TLValue tlType;
};

struct TLPeerNotifySettings {
    TLPeerNotifySettings() :
        muteUntil(0),
        showPreviews(false),
        eventsMask(0),
        tlType(PeerNotifySettingsEmpty) { }

    TLPeerNotifySettings(const TLPeerNotifySettings &anotherPeerNotifySettings) :
        muteUntil(anotherPeerNotifySettings.muteUntil),
        sound(anotherPeerNotifySettings.sound),
        showPreviews(anotherPeerNotifySettings.showPreviews),
        eventsMask(anotherPeerNotifySettings.eventsMask),
        tlType(anotherPeerNotifySettings.tlType) { }

    TLPeerNotifySettings &operator=(const TLPeerNotifySettings &anotherPeerNotifySettings) {
        muteUntil = anotherPeerNotifySettings.muteUntil;
        sound = anotherPeerNotifySettings.sound;
        showPreviews = anotherPeerNotifySettings.showPreviews;
        eventsMask = anotherPeerNotifySettings.eventsMask;
        tlType = anotherPeerNotifySettings.tlType;

        return *this;
    }

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
        tlType(PhotoSizeEmpty) { }

    TLPhotoSize(const TLPhotoSize &anotherPhotoSize) :
        type(anotherPhotoSize.type),
        location(anotherPhotoSize.location),
        w(anotherPhotoSize.w),
        h(anotherPhotoSize.h),
        size(anotherPhotoSize.size),
        bytes(anotherPhotoSize.bytes),
        tlType(anotherPhotoSize.tlType) { }

    TLPhotoSize &operator=(const TLPhotoSize &anotherPhotoSize) {
        type = anotherPhotoSize.type;
        location = anotherPhotoSize.location;
        w = anotherPhotoSize.w;
        h = anotherPhotoSize.h;
        size = anotherPhotoSize.size;
        bytes = anotherPhotoSize.bytes;
        tlType = anotherPhotoSize.tlType;

        return *this;
    }

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
        tlType(SendMessageTypingAction) { }

    TLSendMessageAction(const TLSendMessageAction &anotherSendMessageAction) :
        tlType(anotherSendMessageAction.tlType) { }

    TLSendMessageAction &operator=(const TLSendMessageAction &anotherSendMessageAction) {
        tlType = anotherSendMessageAction.tlType;

        return *this;
    }

    TLValue tlType;
};

struct TLStorageFileType {
    TLStorageFileType() :
        tlType(StorageFileUnknown) { }

    TLStorageFileType(const TLStorageFileType &anotherStorageFileType) :
        tlType(anotherStorageFileType.tlType) { }

    TLStorageFileType &operator=(const TLStorageFileType &anotherStorageFileType) {
        tlType = anotherStorageFileType.tlType;

        return *this;
    }

    TLValue tlType;
};

struct TLUpdatesState {
    TLUpdatesState() :
        pts(0),
        qts(0),
        date(0),
        seq(0),
        unreadCount(0),
        tlType(UpdatesState) { }

    TLUpdatesState(const TLUpdatesState &anotherUpdatesState) :
        pts(anotherUpdatesState.pts),
        qts(anotherUpdatesState.qts),
        date(anotherUpdatesState.date),
        seq(anotherUpdatesState.seq),
        unreadCount(anotherUpdatesState.unreadCount),
        tlType(anotherUpdatesState.tlType) { }

    TLUpdatesState &operator=(const TLUpdatesState &anotherUpdatesState) {
        pts = anotherUpdatesState.pts;
        qts = anotherUpdatesState.qts;
        date = anotherUpdatesState.date;
        seq = anotherUpdatesState.seq;
        unreadCount = anotherUpdatesState.unreadCount;
        tlType = anotherUpdatesState.tlType;

        return *this;
    }

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
        tlType(UploadFile) { }

    TLUploadFile(const TLUploadFile &anotherUploadFile) :
        type(anotherUploadFile.type),
        mtime(anotherUploadFile.mtime),
        bytes(anotherUploadFile.bytes),
        tlType(anotherUploadFile.tlType) { }

    TLUploadFile &operator=(const TLUploadFile &anotherUploadFile) {
        type = anotherUploadFile.type;
        mtime = anotherUploadFile.mtime;
        bytes = anotherUploadFile.bytes;
        tlType = anotherUploadFile.tlType;

        return *this;
    }

    TLStorageFileType type;
    quint32 mtime;
    QByteArray bytes;
    TLValue tlType;
};

struct TLUserProfilePhoto {
    TLUserProfilePhoto() :
        photoId(0),
        tlType(UserProfilePhotoEmpty) { }

    TLUserProfilePhoto(const TLUserProfilePhoto &anotherUserProfilePhoto) :
        photoId(anotherUserProfilePhoto.photoId),
        photoSmall(anotherUserProfilePhoto.photoSmall),
        photoBig(anotherUserProfilePhoto.photoBig),
        tlType(anotherUserProfilePhoto.tlType) { }

    TLUserProfilePhoto &operator=(const TLUserProfilePhoto &anotherUserProfilePhoto) {
        photoId = anotherUserProfilePhoto.photoId;
        photoSmall = anotherUserProfilePhoto.photoSmall;
        photoBig = anotherUserProfilePhoto.photoBig;
        tlType = anotherUserProfilePhoto.tlType;

        return *this;
    }

    quint64 photoId;
    TLFileLocation photoSmall;
    TLFileLocation photoBig;
    TLValue tlType;
};

struct TLUserStatus {
    TLUserStatus() :
        expires(0),
        wasOnline(0),
        tlType(UserStatusEmpty) { }

    TLUserStatus(const TLUserStatus &anotherUserStatus) :
        expires(anotherUserStatus.expires),
        wasOnline(anotherUserStatus.wasOnline),
        tlType(anotherUserStatus.tlType) { }

    TLUserStatus &operator=(const TLUserStatus &anotherUserStatus) {
        expires = anotherUserStatus.expires;
        wasOnline = anotherUserStatus.wasOnline;
        tlType = anotherUserStatus.tlType;

        return *this;
    }

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
        tlType(VideoEmpty) { }

    TLVideo(const TLVideo &anotherVideo) :
        id(anotherVideo.id),
        accessHash(anotherVideo.accessHash),
        userId(anotherVideo.userId),
        date(anotherVideo.date),
        caption(anotherVideo.caption),
        duration(anotherVideo.duration),
        mimeType(anotherVideo.mimeType),
        size(anotherVideo.size),
        thumb(anotherVideo.thumb),
        dcId(anotherVideo.dcId),
        w(anotherVideo.w),
        h(anotherVideo.h),
        tlType(anotherVideo.tlType) { }

    TLVideo &operator=(const TLVideo &anotherVideo) {
        id = anotherVideo.id;
        accessHash = anotherVideo.accessHash;
        userId = anotherVideo.userId;
        date = anotherVideo.date;
        caption = anotherVideo.caption;
        duration = anotherVideo.duration;
        mimeType = anotherVideo.mimeType;
        size = anotherVideo.size;
        thumb = anotherVideo.thumb;
        dcId = anotherVideo.dcId;
        w = anotherVideo.w;
        h = anotherVideo.h;
        tlType = anotherVideo.tlType;

        return *this;
    }

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
        tlType(WallPaper) { }

    TLWallPaper(const TLWallPaper &anotherWallPaper) :
        id(anotherWallPaper.id),
        title(anotherWallPaper.title),
        sizes(anotherWallPaper.sizes),
        color(anotherWallPaper.color),
        bgColor(anotherWallPaper.bgColor),
        tlType(anotherWallPaper.tlType) { }

    TLWallPaper &operator=(const TLWallPaper &anotherWallPaper) {
        id = anotherWallPaper.id;
        title = anotherWallPaper.title;
        sizes = anotherWallPaper.sizes;
        color = anotherWallPaper.color;
        bgColor = anotherWallPaper.bgColor;
        tlType = anotherWallPaper.tlType;

        return *this;
    }

    quint32 id;
    QString title;
    TLVector<TLPhotoSize> sizes;
    quint32 color;
    quint32 bgColor;
    TLValue tlType;
};

struct TLChatPhoto {
    TLChatPhoto() :
        tlType(ChatPhotoEmpty) { }

    TLChatPhoto(const TLChatPhoto &anotherChatPhoto) :
        photoSmall(anotherChatPhoto.photoSmall),
        photoBig(anotherChatPhoto.photoBig),
        tlType(anotherChatPhoto.tlType) { }

    TLChatPhoto &operator=(const TLChatPhoto &anotherChatPhoto) {
        photoSmall = anotherChatPhoto.photoSmall;
        photoBig = anotherChatPhoto.photoBig;
        tlType = anotherChatPhoto.tlType;

        return *this;
    }

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
        tlType(Config) { }

    TLConfig(const TLConfig &anotherConfig) :
        date(anotherConfig.date),
        testMode(anotherConfig.testMode),
        thisDc(anotherConfig.thisDc),
        dcOptions(anotherConfig.dcOptions),
        chatSizeMax(anotherConfig.chatSizeMax),
        broadcastSizeMax(anotherConfig.broadcastSizeMax),
        tlType(anotherConfig.tlType) { }

    TLConfig &operator=(const TLConfig &anotherConfig) {
        date = anotherConfig.date;
        testMode = anotherConfig.testMode;
        thisDc = anotherConfig.thisDc;
        dcOptions = anotherConfig.dcOptions;
        chatSizeMax = anotherConfig.chatSizeMax;
        broadcastSizeMax = anotherConfig.broadcastSizeMax;
        tlType = anotherConfig.tlType;

        return *this;
    }

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
        tlType(Dialog) { }

    TLDialog(const TLDialog &anotherDialog) :
        peer(anotherDialog.peer),
        topMessage(anotherDialog.topMessage),
        unreadCount(anotherDialog.unreadCount),
        notifySettings(anotherDialog.notifySettings),
        tlType(anotherDialog.tlType) { }

    TLDialog &operator=(const TLDialog &anotherDialog) {
        peer = anotherDialog.peer;
        topMessage = anotherDialog.topMessage;
        unreadCount = anotherDialog.unreadCount;
        notifySettings = anotherDialog.notifySettings;
        tlType = anotherDialog.tlType;

        return *this;
    }

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
        tlType(DocumentEmpty) { }

    TLDocument(const TLDocument &anotherDocument) :
        id(anotherDocument.id),
        accessHash(anotherDocument.accessHash),
        userId(anotherDocument.userId),
        date(anotherDocument.date),
        fileName(anotherDocument.fileName),
        mimeType(anotherDocument.mimeType),
        size(anotherDocument.size),
        thumb(anotherDocument.thumb),
        dcId(anotherDocument.dcId),
        tlType(anotherDocument.tlType) { }

    TLDocument &operator=(const TLDocument &anotherDocument) {
        id = anotherDocument.id;
        accessHash = anotherDocument.accessHash;
        userId = anotherDocument.userId;
        date = anotherDocument.date;
        fileName = anotherDocument.fileName;
        mimeType = anotherDocument.mimeType;
        size = anotherDocument.size;
        thumb = anotherDocument.thumb;
        dcId = anotherDocument.dcId;
        tlType = anotherDocument.tlType;

        return *this;
    }

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
        tlType(InputChatPhotoEmpty) { }

    TLInputChatPhoto(const TLInputChatPhoto &anotherInputChatPhoto) :
        file(anotherInputChatPhoto.file),
        crop(anotherInputChatPhoto.crop),
        id(anotherInputChatPhoto.id),
        tlType(anotherInputChatPhoto.tlType) { }

    TLInputChatPhoto &operator=(const TLInputChatPhoto &anotherInputChatPhoto) {
        file = anotherInputChatPhoto.file;
        crop = anotherInputChatPhoto.crop;
        id = anotherInputChatPhoto.id;
        tlType = anotherInputChatPhoto.tlType;

        return *this;
    }

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
        tlType(InputMediaEmpty) { }

    TLInputMedia(const TLInputMedia &anotherInputMedia) :
        file(anotherInputMedia.file),
        id(anotherInputMedia.id),
        geoPoint(anotherInputMedia.geoPoint),
        phoneNumber(anotherInputMedia.phoneNumber),
        firstName(anotherInputMedia.firstName),
        lastName(anotherInputMedia.lastName),
        duration(anotherInputMedia.duration),
        w(anotherInputMedia.w),
        h(anotherInputMedia.h),
        mimeType(anotherInputMedia.mimeType),
        thumb(anotherInputMedia.thumb),
        fileName(anotherInputMedia.fileName),
        tlType(anotherInputMedia.tlType) { }

    TLInputMedia &operator=(const TLInputMedia &anotherInputMedia) {
        file = anotherInputMedia.file;
        id = anotherInputMedia.id;
        geoPoint = anotherInputMedia.geoPoint;
        phoneNumber = anotherInputMedia.phoneNumber;
        firstName = anotherInputMedia.firstName;
        lastName = anotherInputMedia.lastName;
        duration = anotherInputMedia.duration;
        w = anotherInputMedia.w;
        h = anotherInputMedia.h;
        mimeType = anotherInputMedia.mimeType;
        thumb = anotherInputMedia.thumb;
        fileName = anotherInputMedia.fileName;
        tlType = anotherInputMedia.tlType;

        return *this;
    }

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
        tlType(InputNotifyPeer) { }

    TLInputNotifyPeer(const TLInputNotifyPeer &anotherInputNotifyPeer) :
        peer(anotherInputNotifyPeer.peer),
        tlType(anotherInputNotifyPeer.tlType) { }

    TLInputNotifyPeer &operator=(const TLInputNotifyPeer &anotherInputNotifyPeer) {
        peer = anotherInputNotifyPeer.peer;
        tlType = anotherInputNotifyPeer.tlType;

        return *this;
    }

    TLInputPeer peer;
    TLValue tlType;
};

struct TLNotifyPeer {
    TLNotifyPeer() :
        tlType(NotifyPeer) { }

    TLNotifyPeer(const TLNotifyPeer &anotherNotifyPeer) :
        peer(anotherNotifyPeer.peer),
        tlType(anotherNotifyPeer.tlType) { }

    TLNotifyPeer &operator=(const TLNotifyPeer &anotherNotifyPeer) {
        peer = anotherNotifyPeer.peer;
        tlType = anotherNotifyPeer.tlType;

        return *this;
    }

    TLPeer peer;
    TLValue tlType;
};

struct TLPhoto {
    TLPhoto() :
        id(0),
        accessHash(0),
        userId(0),
        date(0),
        tlType(PhotoEmpty) { }

    TLPhoto(const TLPhoto &anotherPhoto) :
        id(anotherPhoto.id),
        accessHash(anotherPhoto.accessHash),
        userId(anotherPhoto.userId),
        date(anotherPhoto.date),
        caption(anotherPhoto.caption),
        geo(anotherPhoto.geo),
        sizes(anotherPhoto.sizes),
        tlType(anotherPhoto.tlType) { }

    TLPhoto &operator=(const TLPhoto &anotherPhoto) {
        id = anotherPhoto.id;
        accessHash = anotherPhoto.accessHash;
        userId = anotherPhoto.userId;
        date = anotherPhoto.date;
        caption = anotherPhoto.caption;
        geo = anotherPhoto.geo;
        sizes = anotherPhoto.sizes;
        tlType = anotherPhoto.tlType;

        return *this;
    }

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
        tlType(UserEmpty) { }

    TLUser(const TLUser &anotherUser) :
        id(anotherUser.id),
        firstName(anotherUser.firstName),
        lastName(anotherUser.lastName),
        username(anotherUser.username),
        phone(anotherUser.phone),
        photo(anotherUser.photo),
        status(anotherUser.status),
        inactive(anotherUser.inactive),
        accessHash(anotherUser.accessHash),
        tlType(anotherUser.tlType) { }

    TLUser &operator=(const TLUser &anotherUser) {
        id = anotherUser.id;
        firstName = anotherUser.firstName;
        lastName = anotherUser.lastName;
        username = anotherUser.username;
        phone = anotherUser.phone;
        photo = anotherUser.photo;
        status = anotherUser.status;
        inactive = anotherUser.inactive;
        accessHash = anotherUser.accessHash;
        tlType = anotherUser.tlType;

        return *this;
    }

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
        tlType(AuthAuthorization) { }

    TLAuthAuthorization(const TLAuthAuthorization &anotherAuthAuthorization) :
        expires(anotherAuthAuthorization.expires),
        user(anotherAuthAuthorization.user),
        tlType(anotherAuthAuthorization.tlType) { }

    TLAuthAuthorization &operator=(const TLAuthAuthorization &anotherAuthAuthorization) {
        expires = anotherAuthAuthorization.expires;
        user = anotherAuthAuthorization.user;
        tlType = anotherAuthAuthorization.tlType;

        return *this;
    }

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
        tlType(ChatEmpty) { }

    TLChat(const TLChat &anotherChat) :
        id(anotherChat.id),
        title(anotherChat.title),
        photo(anotherChat.photo),
        participantsCount(anotherChat.participantsCount),
        date(anotherChat.date),
        left(anotherChat.left),
        version(anotherChat.version),
        accessHash(anotherChat.accessHash),
        address(anotherChat.address),
        venue(anotherChat.venue),
        geo(anotherChat.geo),
        checkedIn(anotherChat.checkedIn),
        tlType(anotherChat.tlType) { }

    TLChat &operator=(const TLChat &anotherChat) {
        id = anotherChat.id;
        title = anotherChat.title;
        photo = anotherChat.photo;
        participantsCount = anotherChat.participantsCount;
        date = anotherChat.date;
        left = anotherChat.left;
        version = anotherChat.version;
        accessHash = anotherChat.accessHash;
        address = anotherChat.address;
        venue = anotherChat.venue;
        geo = anotherChat.geo;
        checkedIn = anotherChat.checkedIn;
        tlType = anotherChat.tlType;

        return *this;
    }

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
        tlType(ChatFull) { }

    TLChatFull(const TLChatFull &anotherChatFull) :
        id(anotherChatFull.id),
        participants(anotherChatFull.participants),
        chatPhoto(anotherChatFull.chatPhoto),
        notifySettings(anotherChatFull.notifySettings),
        tlType(anotherChatFull.tlType) { }

    TLChatFull &operator=(const TLChatFull &anotherChatFull) {
        id = anotherChatFull.id;
        participants = anotherChatFull.participants;
        chatPhoto = anotherChatFull.chatPhoto;
        notifySettings = anotherChatFull.notifySettings;
        tlType = anotherChatFull.tlType;

        return *this;
    }

    quint32 id;
    TLChatParticipants participants;
    TLPhoto chatPhoto;
    TLPeerNotifySettings notifySettings;
    TLValue tlType;
};

struct TLContactsBlocked {
    TLContactsBlocked() :
        count(0),
        tlType(ContactsBlocked) { }

    TLContactsBlocked(const TLContactsBlocked &anotherContactsBlocked) :
        blocked(anotherContactsBlocked.blocked),
        users(anotherContactsBlocked.users),
        count(anotherContactsBlocked.count),
        tlType(anotherContactsBlocked.tlType) { }

    TLContactsBlocked &operator=(const TLContactsBlocked &anotherContactsBlocked) {
        blocked = anotherContactsBlocked.blocked;
        users = anotherContactsBlocked.users;
        count = anotherContactsBlocked.count;
        tlType = anotherContactsBlocked.tlType;

        return *this;
    }

    TLVector<TLContactBlocked> blocked;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLContactsContacts {
    TLContactsContacts() :
        tlType(ContactsContacts) { }

    TLContactsContacts(const TLContactsContacts &anotherContactsContacts) :
        contacts(anotherContactsContacts.contacts),
        users(anotherContactsContacts.users),
        tlType(anotherContactsContacts.tlType) { }

    TLContactsContacts &operator=(const TLContactsContacts &anotherContactsContacts) {
        contacts = anotherContactsContacts.contacts;
        users = anotherContactsContacts.users;
        tlType = anotherContactsContacts.tlType;

        return *this;
    }

    TLVector<TLContact> contacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsFound {
    TLContactsFound() :
        tlType(ContactsFound) { }

    TLContactsFound(const TLContactsFound &anotherContactsFound) :
        results(anotherContactsFound.results),
        users(anotherContactsFound.users),
        tlType(anotherContactsFound.tlType) { }

    TLContactsFound &operator=(const TLContactsFound &anotherContactsFound) {
        results = anotherContactsFound.results;
        users = anotherContactsFound.users;
        tlType = anotherContactsFound.tlType;

        return *this;
    }

    TLVector<TLContactFound> results;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsImportedContacts {
    TLContactsImportedContacts() :
        tlType(ContactsImportedContacts) { }

    TLContactsImportedContacts(const TLContactsImportedContacts &anotherContactsImportedContacts) :
        imported(anotherContactsImportedContacts.imported),
        retryContacts(anotherContactsImportedContacts.retryContacts),
        users(anotherContactsImportedContacts.users),
        tlType(anotherContactsImportedContacts.tlType) { }

    TLContactsImportedContacts &operator=(const TLContactsImportedContacts &anotherContactsImportedContacts) {
        imported = anotherContactsImportedContacts.imported;
        retryContacts = anotherContactsImportedContacts.retryContacts;
        users = anotherContactsImportedContacts.users;
        tlType = anotherContactsImportedContacts.tlType;

        return *this;
    }

    TLVector<TLImportedContact> imported;
    TLVector<quint64> retryContacts;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLContactsLink {
    TLContactsLink() :
        tlType(ContactsLink) { }

    TLContactsLink(const TLContactsLink &anotherContactsLink) :
        myLink(anotherContactsLink.myLink),
        foreignLink(anotherContactsLink.foreignLink),
        user(anotherContactsLink.user),
        tlType(anotherContactsLink.tlType) { }

    TLContactsLink &operator=(const TLContactsLink &anotherContactsLink) {
        myLink = anotherContactsLink.myLink;
        foreignLink = anotherContactsLink.foreignLink;
        user = anotherContactsLink.user;
        tlType = anotherContactsLink.tlType;

        return *this;
    }

    TLContactsMyLink myLink;
    TLContactsForeignLink foreignLink;
    TLUser user;
    TLValue tlType;
};

struct TLContactsSuggested {
    TLContactsSuggested() :
        tlType(ContactsSuggested) { }

    TLContactsSuggested(const TLContactsSuggested &anotherContactsSuggested) :
        results(anotherContactsSuggested.results),
        users(anotherContactsSuggested.users),
        tlType(anotherContactsSuggested.tlType) { }

    TLContactsSuggested &operator=(const TLContactsSuggested &anotherContactsSuggested) {
        results = anotherContactsSuggested.results;
        users = anotherContactsSuggested.users;
        tlType = anotherContactsSuggested.tlType;

        return *this;
    }

    TLVector<TLContactSuggested> results;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLHelpSupport {
    TLHelpSupport() :
        tlType(HelpSupport) { }

    TLHelpSupport(const TLHelpSupport &anotherHelpSupport) :
        phoneNumber(anotherHelpSupport.phoneNumber),
        user(anotherHelpSupport.user),
        tlType(anotherHelpSupport.tlType) { }

    TLHelpSupport &operator=(const TLHelpSupport &anotherHelpSupport) {
        phoneNumber = anotherHelpSupport.phoneNumber;
        user = anotherHelpSupport.user;
        tlType = anotherHelpSupport.tlType;

        return *this;
    }

    QString phoneNumber;
    TLUser user;
    TLValue tlType;
};

struct TLMessageAction {
    TLMessageAction() :
        userId(0),
        tlType(MessageActionEmpty) { }

    TLMessageAction(const TLMessageAction &anotherMessageAction) :
        title(anotherMessageAction.title),
        users(anotherMessageAction.users),
        photo(anotherMessageAction.photo),
        userId(anotherMessageAction.userId),
        address(anotherMessageAction.address),
        tlType(anotherMessageAction.tlType) { }

    TLMessageAction &operator=(const TLMessageAction &anotherMessageAction) {
        title = anotherMessageAction.title;
        users = anotherMessageAction.users;
        photo = anotherMessageAction.photo;
        userId = anotherMessageAction.userId;
        address = anotherMessageAction.address;
        tlType = anotherMessageAction.tlType;

        return *this;
    }

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
        tlType(MessageMediaEmpty) { }

    TLMessageMedia(const TLMessageMedia &anotherMessageMedia) :
        photo(anotherMessageMedia.photo),
        video(anotherMessageMedia.video),
        geo(anotherMessageMedia.geo),
        phoneNumber(anotherMessageMedia.phoneNumber),
        firstName(anotherMessageMedia.firstName),
        lastName(anotherMessageMedia.lastName),
        userId(anotherMessageMedia.userId),
        bytes(anotherMessageMedia.bytes),
        document(anotherMessageMedia.document),
        audio(anotherMessageMedia.audio),
        tlType(anotherMessageMedia.tlType) { }

    TLMessageMedia &operator=(const TLMessageMedia &anotherMessageMedia) {
        photo = anotherMessageMedia.photo;
        video = anotherMessageMedia.video;
        geo = anotherMessageMedia.geo;
        phoneNumber = anotherMessageMedia.phoneNumber;
        firstName = anotherMessageMedia.firstName;
        lastName = anotherMessageMedia.lastName;
        userId = anotherMessageMedia.userId;
        bytes = anotherMessageMedia.bytes;
        document = anotherMessageMedia.document;
        audio = anotherMessageMedia.audio;
        tlType = anotherMessageMedia.tlType;

        return *this;
    }

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
        tlType(MessagesChat) { }

    TLMessagesChat(const TLMessagesChat &anotherMessagesChat) :
        chat(anotherMessagesChat.chat),
        users(anotherMessagesChat.users),
        tlType(anotherMessagesChat.tlType) { }

    TLMessagesChat &operator=(const TLMessagesChat &anotherMessagesChat) {
        chat = anotherMessagesChat.chat;
        users = anotherMessagesChat.users;
        tlType = anotherMessagesChat.tlType;

        return *this;
    }

    TLChat chat;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesChatFull {
    TLMessagesChatFull() :
        tlType(MessagesChatFull) { }

    TLMessagesChatFull(const TLMessagesChatFull &anotherMessagesChatFull) :
        fullChat(anotherMessagesChatFull.fullChat),
        chats(anotherMessagesChatFull.chats),
        users(anotherMessagesChatFull.users),
        tlType(anotherMessagesChatFull.tlType) { }

    TLMessagesChatFull &operator=(const TLMessagesChatFull &anotherMessagesChatFull) {
        fullChat = anotherMessagesChatFull.fullChat;
        chats = anotherMessagesChatFull.chats;
        users = anotherMessagesChatFull.users;
        tlType = anotherMessagesChatFull.tlType;

        return *this;
    }

    TLChatFull fullChat;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesChats {
    TLMessagesChats() :
        tlType(MessagesChats) { }

    TLMessagesChats(const TLMessagesChats &anotherMessagesChats) :
        chats(anotherMessagesChats.chats),
        users(anotherMessagesChats.users),
        tlType(anotherMessagesChats.tlType) { }

    TLMessagesChats &operator=(const TLMessagesChats &anotherMessagesChats) {
        chats = anotherMessagesChats.chats;
        users = anotherMessagesChats.users;
        tlType = anotherMessagesChats.tlType;

        return *this;
    }

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
        tlType(MessagesSentMessage) { }

    TLMessagesSentMessage(const TLMessagesSentMessage &anotherMessagesSentMessage) :
        id(anotherMessagesSentMessage.id),
        date(anotherMessagesSentMessage.date),
        pts(anotherMessagesSentMessage.pts),
        seq(anotherMessagesSentMessage.seq),
        links(anotherMessagesSentMessage.links),
        tlType(anotherMessagesSentMessage.tlType) { }

    TLMessagesSentMessage &operator=(const TLMessagesSentMessage &anotherMessagesSentMessage) {
        id = anotherMessagesSentMessage.id;
        date = anotherMessagesSentMessage.date;
        pts = anotherMessagesSentMessage.pts;
        seq = anotherMessagesSentMessage.seq;
        links = anotherMessagesSentMessage.links;
        tlType = anotherMessagesSentMessage.tlType;

        return *this;
    }

    quint32 id;
    quint32 date;
    quint32 pts;
    quint32 seq;
    TLVector<TLContactsLink> links;
    TLValue tlType;
};

struct TLPhotosPhoto {
    TLPhotosPhoto() :
        tlType(PhotosPhoto) { }

    TLPhotosPhoto(const TLPhotosPhoto &anotherPhotosPhoto) :
        photo(anotherPhotosPhoto.photo),
        users(anotherPhotosPhoto.users),
        tlType(anotherPhotosPhoto.tlType) { }

    TLPhotosPhoto &operator=(const TLPhotosPhoto &anotherPhotosPhoto) {
        photo = anotherPhotosPhoto.photo;
        users = anotherPhotosPhoto.users;
        tlType = anotherPhotosPhoto.tlType;

        return *this;
    }

    TLPhoto photo;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLPhotosPhotos {
    TLPhotosPhotos() :
        count(0),
        tlType(PhotosPhotos) { }

    TLPhotosPhotos(const TLPhotosPhotos &anotherPhotosPhotos) :
        photos(anotherPhotosPhotos.photos),
        users(anotherPhotosPhotos.users),
        count(anotherPhotosPhotos.count),
        tlType(anotherPhotosPhotos.tlType) { }

    TLPhotosPhotos &operator=(const TLPhotosPhotos &anotherPhotosPhotos) {
        photos = anotherPhotosPhotos.photos;
        users = anotherPhotosPhotos.users;
        count = anotherPhotosPhotos.count;
        tlType = anotherPhotosPhotos.tlType;

        return *this;
    }

    TLVector<TLPhoto> photos;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLUserFull {
    TLUserFull() :
        blocked(false),
        tlType(UserFull) { }

    TLUserFull(const TLUserFull &anotherUserFull) :
        user(anotherUserFull.user),
        link(anotherUserFull.link),
        profilePhoto(anotherUserFull.profilePhoto),
        notifySettings(anotherUserFull.notifySettings),
        blocked(anotherUserFull.blocked),
        realFirstName(anotherUserFull.realFirstName),
        realLastName(anotherUserFull.realLastName),
        tlType(anotherUserFull.tlType) { }

    TLUserFull &operator=(const TLUserFull &anotherUserFull) {
        user = anotherUserFull.user;
        link = anotherUserFull.link;
        profilePhoto = anotherUserFull.profilePhoto;
        notifySettings = anotherUserFull.notifySettings;
        blocked = anotherUserFull.blocked;
        realFirstName = anotherUserFull.realFirstName;
        realLastName = anotherUserFull.realLastName;
        tlType = anotherUserFull.tlType;

        return *this;
    }

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
        tlType(GeoChatMessageEmpty) { }

    TLGeoChatMessage(const TLGeoChatMessage &anotherGeoChatMessage) :
        chatId(anotherGeoChatMessage.chatId),
        id(anotherGeoChatMessage.id),
        fromId(anotherGeoChatMessage.fromId),
        date(anotherGeoChatMessage.date),
        message(anotherGeoChatMessage.message),
        media(anotherGeoChatMessage.media),
        action(anotherGeoChatMessage.action),
        tlType(anotherGeoChatMessage.tlType) { }

    TLGeoChatMessage &operator=(const TLGeoChatMessage &anotherGeoChatMessage) {
        chatId = anotherGeoChatMessage.chatId;
        id = anotherGeoChatMessage.id;
        fromId = anotherGeoChatMessage.fromId;
        date = anotherGeoChatMessage.date;
        message = anotherGeoChatMessage.message;
        media = anotherGeoChatMessage.media;
        action = anotherGeoChatMessage.action;
        tlType = anotherGeoChatMessage.tlType;

        return *this;
    }

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
        tlType(GeochatsLocated) { }

    TLGeochatsLocated(const TLGeochatsLocated &anotherGeochatsLocated) :
        results(anotherGeochatsLocated.results),
        messages(anotherGeochatsLocated.messages),
        chats(anotherGeochatsLocated.chats),
        users(anotherGeochatsLocated.users),
        tlType(anotherGeochatsLocated.tlType) { }

    TLGeochatsLocated &operator=(const TLGeochatsLocated &anotherGeochatsLocated) {
        results = anotherGeochatsLocated.results;
        messages = anotherGeochatsLocated.messages;
        chats = anotherGeochatsLocated.chats;
        users = anotherGeochatsLocated.users;
        tlType = anotherGeochatsLocated.tlType;

        return *this;
    }

    TLVector<TLChatLocated> results;
    TLVector<TLGeoChatMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLGeochatsMessages {
    TLGeochatsMessages() :
        count(0),
        tlType(GeochatsMessages) { }

    TLGeochatsMessages(const TLGeochatsMessages &anotherGeochatsMessages) :
        messages(anotherGeochatsMessages.messages),
        chats(anotherGeochatsMessages.chats),
        users(anotherGeochatsMessages.users),
        count(anotherGeochatsMessages.count),
        tlType(anotherGeochatsMessages.tlType) { }

    TLGeochatsMessages &operator=(const TLGeochatsMessages &anotherGeochatsMessages) {
        messages = anotherGeochatsMessages.messages;
        chats = anotherGeochatsMessages.chats;
        users = anotherGeochatsMessages.users;
        count = anotherGeochatsMessages.count;
        tlType = anotherGeochatsMessages.tlType;

        return *this;
    }

    TLVector<TLGeoChatMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLGeochatsStatedMessage {
    TLGeochatsStatedMessage() :
        seq(0),
        tlType(GeochatsStatedMessage) { }

    TLGeochatsStatedMessage(const TLGeochatsStatedMessage &anotherGeochatsStatedMessage) :
        message(anotherGeochatsStatedMessage.message),
        chats(anotherGeochatsStatedMessage.chats),
        users(anotherGeochatsStatedMessage.users),
        seq(anotherGeochatsStatedMessage.seq),
        tlType(anotherGeochatsStatedMessage.tlType) { }

    TLGeochatsStatedMessage &operator=(const TLGeochatsStatedMessage &anotherGeochatsStatedMessage) {
        message = anotherGeochatsStatedMessage.message;
        chats = anotherGeochatsStatedMessage.chats;
        users = anotherGeochatsStatedMessage.users;
        seq = anotherGeochatsStatedMessage.seq;
        tlType = anotherGeochatsStatedMessage.tlType;

        return *this;
    }

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
        tlType(MessageEmpty) { }

    TLMessage(const TLMessage &anotherMessage) :
        id(anotherMessage.id),
        flags(anotherMessage.flags),
        fromId(anotherMessage.fromId),
        toId(anotherMessage.toId),
        date(anotherMessage.date),
        message(anotherMessage.message),
        media(anotherMessage.media),
        fwdFromId(anotherMessage.fwdFromId),
        fwdDate(anotherMessage.fwdDate),
        action(anotherMessage.action),
        tlType(anotherMessage.tlType) { }

    TLMessage &operator=(const TLMessage &anotherMessage) {
        id = anotherMessage.id;
        flags = anotherMessage.flags;
        fromId = anotherMessage.fromId;
        toId = anotherMessage.toId;
        date = anotherMessage.date;
        message = anotherMessage.message;
        media = anotherMessage.media;
        fwdFromId = anotherMessage.fwdFromId;
        fwdDate = anotherMessage.fwdDate;
        action = anotherMessage.action;
        tlType = anotherMessage.tlType;

        return *this;
    }

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
        tlType(MessagesDialogs) { }

    TLMessagesDialogs(const TLMessagesDialogs &anotherMessagesDialogs) :
        dialogs(anotherMessagesDialogs.dialogs),
        messages(anotherMessagesDialogs.messages),
        chats(anotherMessagesDialogs.chats),
        users(anotherMessagesDialogs.users),
        count(anotherMessagesDialogs.count),
        tlType(anotherMessagesDialogs.tlType) { }

    TLMessagesDialogs &operator=(const TLMessagesDialogs &anotherMessagesDialogs) {
        dialogs = anotherMessagesDialogs.dialogs;
        messages = anotherMessagesDialogs.messages;
        chats = anotherMessagesDialogs.chats;
        users = anotherMessagesDialogs.users;
        count = anotherMessagesDialogs.count;
        tlType = anotherMessagesDialogs.tlType;

        return *this;
    }

    TLVector<TLDialog> dialogs;
    TLVector<TLMessage> messages;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    quint32 count;
    TLValue tlType;
};

struct TLMessagesMessage {
    TLMessagesMessage() :
        tlType(MessagesMessageEmpty) { }

    TLMessagesMessage(const TLMessagesMessage &anotherMessagesMessage) :
        message(anotherMessagesMessage.message),
        chats(anotherMessagesMessage.chats),
        users(anotherMessagesMessage.users),
        tlType(anotherMessagesMessage.tlType) { }

    TLMessagesMessage &operator=(const TLMessagesMessage &anotherMessagesMessage) {
        message = anotherMessagesMessage.message;
        chats = anotherMessagesMessage.chats;
        users = anotherMessagesMessage.users;
        tlType = anotherMessagesMessage.tlType;

        return *this;
    }

    TLMessage message;
    TLVector<TLChat> chats;
    TLVector<TLUser> users;
    TLValue tlType;
};

struct TLMessagesMessages {
    TLMessagesMessages() :
        count(0),
        tlType(MessagesMessages) { }

    TLMessagesMessages(const TLMessagesMessages &anotherMessagesMessages) :
        messages(anotherMessagesMessages.messages),
        chats(anotherMessagesMessages.chats),
        users(anotherMessagesMessages.users),
        count(anotherMessagesMessages.count),
        tlType(anotherMessagesMessages.tlType) { }

    TLMessagesMessages &operator=(const TLMessagesMessages &anotherMessagesMessages) {
        messages = anotherMessagesMessages.messages;
        chats = anotherMessagesMessages.chats;
        users = anotherMessagesMessages.users;
        count = anotherMessagesMessages.count;
        tlType = anotherMessagesMessages.tlType;

        return *this;
    }

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
        tlType(MessagesStatedMessage) { }

    TLMessagesStatedMessage(const TLMessagesStatedMessage &anotherMessagesStatedMessage) :
        message(anotherMessagesStatedMessage.message),
        chats(anotherMessagesStatedMessage.chats),
        users(anotherMessagesStatedMessage.users),
        pts(anotherMessagesStatedMessage.pts),
        seq(anotherMessagesStatedMessage.seq),
        links(anotherMessagesStatedMessage.links),
        tlType(anotherMessagesStatedMessage.tlType) { }

    TLMessagesStatedMessage &operator=(const TLMessagesStatedMessage &anotherMessagesStatedMessage) {
        message = anotherMessagesStatedMessage.message;
        chats = anotherMessagesStatedMessage.chats;
        users = anotherMessagesStatedMessage.users;
        pts = anotherMessagesStatedMessage.pts;
        seq = anotherMessagesStatedMessage.seq;
        links = anotherMessagesStatedMessage.links;
        tlType = anotherMessagesStatedMessage.tlType;

        return *this;
    }

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
        tlType(MessagesStatedMessages) { }

    TLMessagesStatedMessages(const TLMessagesStatedMessages &anotherMessagesStatedMessages) :
        messages(anotherMessagesStatedMessages.messages),
        chats(anotherMessagesStatedMessages.chats),
        users(anotherMessagesStatedMessages.users),
        pts(anotherMessagesStatedMessages.pts),
        seq(anotherMessagesStatedMessages.seq),
        links(anotherMessagesStatedMessages.links),
        tlType(anotherMessagesStatedMessages.tlType) { }

    TLMessagesStatedMessages &operator=(const TLMessagesStatedMessages &anotherMessagesStatedMessages) {
        messages = anotherMessagesStatedMessages.messages;
        chats = anotherMessagesStatedMessages.chats;
        users = anotherMessagesStatedMessages.users;
        pts = anotherMessagesStatedMessages.pts;
        seq = anotherMessagesStatedMessages.seq;
        links = anotherMessagesStatedMessages.links;
        tlType = anotherMessagesStatedMessages.tlType;

        return *this;
    }

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
        tlType(UpdateNewMessage) { }

    TLUpdate(const TLUpdate &anotherUpdate) :
        message(anotherUpdate.message),
        pts(anotherUpdate.pts),
        id(anotherUpdate.id),
        randomId(anotherUpdate.randomId),
        messages(anotherUpdate.messages),
        userId(anotherUpdate.userId),
        action(anotherUpdate.action),
        chatId(anotherUpdate.chatId),
        participants(anotherUpdate.participants),
        status(anotherUpdate.status),
        firstName(anotherUpdate.firstName),
        lastName(anotherUpdate.lastName),
        username(anotherUpdate.username),
        date(anotherUpdate.date),
        photo(anotherUpdate.photo),
        previous(anotherUpdate.previous),
        myLink(anotherUpdate.myLink),
        foreignLink(anotherUpdate.foreignLink),
        authKeyId(anotherUpdate.authKeyId),
        device(anotherUpdate.device),
        location(anotherUpdate.location),
        qts(anotherUpdate.qts),
        chat(anotherUpdate.chat),
        maxDate(anotherUpdate.maxDate),
        inviterId(anotherUpdate.inviterId),
        version(anotherUpdate.version),
        dcOptions(anotherUpdate.dcOptions),
        blocked(anotherUpdate.blocked),
        peer(anotherUpdate.peer),
        notifySettings(anotherUpdate.notifySettings),
        type(anotherUpdate.type),
        media(anotherUpdate.media),
        popup(anotherUpdate.popup),
        tlType(anotherUpdate.tlType) { }

    TLUpdate &operator=(const TLUpdate &anotherUpdate) {
        message = anotherUpdate.message;
        pts = anotherUpdate.pts;
        id = anotherUpdate.id;
        randomId = anotherUpdate.randomId;
        messages = anotherUpdate.messages;
        userId = anotherUpdate.userId;
        action = anotherUpdate.action;
        chatId = anotherUpdate.chatId;
        participants = anotherUpdate.participants;
        status = anotherUpdate.status;
        firstName = anotherUpdate.firstName;
        lastName = anotherUpdate.lastName;
        username = anotherUpdate.username;
        date = anotherUpdate.date;
        photo = anotherUpdate.photo;
        previous = anotherUpdate.previous;
        myLink = anotherUpdate.myLink;
        foreignLink = anotherUpdate.foreignLink;
        authKeyId = anotherUpdate.authKeyId;
        device = anotherUpdate.device;
        location = anotherUpdate.location;
        qts = anotherUpdate.qts;
        chat = anotherUpdate.chat;
        maxDate = anotherUpdate.maxDate;
        inviterId = anotherUpdate.inviterId;
        version = anotherUpdate.version;
        dcOptions = anotherUpdate.dcOptions;
        blocked = anotherUpdate.blocked;
        peer = anotherUpdate.peer;
        notifySettings = anotherUpdate.notifySettings;
        type = anotherUpdate.type;
        media = anotherUpdate.media;
        popup = anotherUpdate.popup;
        tlType = anotherUpdate.tlType;

        return *this;
    }

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
        tlType(UpdatesTooLong) { }

    TLUpdates(const TLUpdates &anotherUpdates) :
        id(anotherUpdates.id),
        fromId(anotherUpdates.fromId),
        message(anotherUpdates.message),
        pts(anotherUpdates.pts),
        date(anotherUpdates.date),
        seq(anotherUpdates.seq),
        chatId(anotherUpdates.chatId),
        update(anotherUpdates.update),
        updates(anotherUpdates.updates),
        users(anotherUpdates.users),
        chats(anotherUpdates.chats),
        seqStart(anotherUpdates.seqStart),
        tlType(anotherUpdates.tlType) { }

    TLUpdates &operator=(const TLUpdates &anotherUpdates) {
        id = anotherUpdates.id;
        fromId = anotherUpdates.fromId;
        message = anotherUpdates.message;
        pts = anotherUpdates.pts;
        date = anotherUpdates.date;
        seq = anotherUpdates.seq;
        chatId = anotherUpdates.chatId;
        update = anotherUpdates.update;
        updates = anotherUpdates.updates;
        users = anotherUpdates.users;
        chats = anotherUpdates.chats;
        seqStart = anotherUpdates.seqStart;
        tlType = anotherUpdates.tlType;

        return *this;
    }

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
        tlType(UpdatesDifferenceEmpty) { }

    TLUpdatesDifference(const TLUpdatesDifference &anotherUpdatesDifference) :
        date(anotherUpdatesDifference.date),
        seq(anotherUpdatesDifference.seq),
        newMessages(anotherUpdatesDifference.newMessages),
        newEncryptedMessages(anotherUpdatesDifference.newEncryptedMessages),
        otherUpdates(anotherUpdatesDifference.otherUpdates),
        chats(anotherUpdatesDifference.chats),
        users(anotherUpdatesDifference.users),
        state(anotherUpdatesDifference.state),
        intermediateState(anotherUpdatesDifference.intermediateState),
        tlType(anotherUpdatesDifference.tlType) { }

    TLUpdatesDifference &operator=(const TLUpdatesDifference &anotherUpdatesDifference) {
        date = anotherUpdatesDifference.date;
        seq = anotherUpdatesDifference.seq;
        newMessages = anotherUpdatesDifference.newMessages;
        newEncryptedMessages = anotherUpdatesDifference.newEncryptedMessages;
        otherUpdates = anotherUpdatesDifference.otherUpdates;
        chats = anotherUpdatesDifference.chats;
        users = anotherUpdatesDifference.users;
        state = anotherUpdatesDifference.state;
        intermediateState = anotherUpdatesDifference.intermediateState;
        tlType = anotherUpdatesDifference.tlType;

        return *this;
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
    TLValue tlType;
};

// End of generated TLTypes

Q_DECLARE_METATYPE(TLUploadFile)
Q_DECLARE_METATYPE(QVector<TLUser>)
Q_DECLARE_METATYPE(TLUpdates)

#endif // TLTYPES_HPP
