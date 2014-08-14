/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CTelegramStream.hpp"

#include <QtEndian>

#include <QIODevice>
#include <QDebug>

static const char s_nulls[4] = { 0, 0, 0, 0 };

template CTelegramStream &CTelegramStream::operator>>(TLVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<quint64> &v);

template CTelegramStream &CTelegramStream::operator<<(const TLVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<quint64> &v);

template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContact> &v);

template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputContact> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputUser> &v);

CTelegramStream::CTelegramStream(QByteArray *data, bool write) :
    CRawStream(data, write)
{

}

CTelegramStream::CTelegramStream(const QByteArray &data) :
    CRawStream(data)
{

}

CTelegramStream::CTelegramStream(QIODevice *d) :
    CRawStream(d)
{

}

CTelegramStream &CTelegramStream::operator>>(QByteArray &data)
{
    quint32 length = 0;
    m_device->getChar((char *) &length);

    if (length < 0xfe) {
        data.resize(length);
        length += 1; // Plus one byte before data
    } else {
        m_device->read((char *) &length, 3);
        data.resize(length);
        length += 4; // Plus four bytes before data
    }

    m_device->read(data.data(), data.size());

    if (length & 3) {
        m_device->read(4 - (length & 3));
    }

    return *this;
}

template <typename T>
CTelegramStream &CTelegramStream::operator>>(TLVector<T> &v)
{
    TLVector<T> result;

    *this >> result.tlType;

    if (result.tlType == Vector) {
        quint32 length = 0;
        *this >> length;
        for (int i = 0; i < length; ++i) {
            T value;
            *this >> value;
            result.append(value);
        }
    }

    v = result;
    return *this;
}

// Generated read operators implementation
CTelegramStream &CTelegramStream::operator>>(TLAudio &audio)
{
    TLAudio result;

    *this >> result.tlType;

    switch (result.tlType) {
    case AudioEmpty:
        *this >> result.id;
        break;
    case Audio:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.userId;
        *this >> result.date;
        *this >> result.duration;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.dcId;
        break;
    default:
        break;
    }

    audio = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthCheckedPhone &authCheckedPhone)
{
    TLAuthCheckedPhone result;

    *this >> result.tlType;

    switch (result.tlType) {
    case AuthCheckedPhone:
        *this >> result.phoneRegistered;
        *this >> result.phoneInvited;
        break;
    default:
        break;
    }

    authCheckedPhone = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthExportedAuthorization &authExportedAuthorization)
{
    TLAuthExportedAuthorization result;

    *this >> result.tlType;

    switch (result.tlType) {
    case AuthExportedAuthorization:
        *this >> result.id;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    authExportedAuthorization = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthSentCode &authSentCode)
{
    TLAuthSentCode result;

    *this >> result.tlType;

    switch (result.tlType) {
    case AuthSentCode:
        *this >> result.phoneRegistered;
        *this >> result.phoneCodeHash;
        *this >> result.sendCallTimeout;
        *this >> result.isPassword;
        break;
    default:
        break;
    }

    authSentCode = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatLocated &chatLocated)
{
    TLChatLocated result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ChatLocated:
        *this >> result.chatId;
        *this >> result.distance;
        break;
    default:
        break;
    }

    chatLocated = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatParticipant &chatParticipant)
{
    TLChatParticipant result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ChatParticipant:
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.date;
        break;
    default:
        break;
    }

    chatParticipant = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatParticipants &chatParticipants)
{
    TLChatParticipants result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ChatParticipantsForbidden:
        *this >> result.chatId;
        break;
    case ChatParticipants:
        *this >> result.chatId;
        *this >> result.adminId;
        *this >> result.participants;
        *this >> result.version;
        break;
    default:
        break;
    }

    chatParticipants = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContact &contact)
{
    TLContact result;

    *this >> result.tlType;

    switch (result.tlType) {
    case Contact:
        *this >> result.userId;
        *this >> result.mutual;
        break;
    default:
        break;
    }

    contact = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactBlocked &contactBlocked)
{
    TLContactBlocked result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactBlocked:
        *this >> result.userId;
        *this >> result.date;
        break;
    default:
        break;
    }

    contactBlocked = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactFound &contactFound)
{
    TLContactFound result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactFound:
        *this >> result.userId;
        break;
    default:
        break;
    }

    contactFound = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactStatus &contactStatus)
{
    TLContactStatus result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactStatus:
        *this >> result.userId;
        *this >> result.expires;
        break;
    default:
        break;
    }

    contactStatus = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactSuggested &contactSuggested)
{
    TLContactSuggested result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactSuggested:
        *this >> result.userId;
        *this >> result.mutualContacts;
        break;
    default:
        break;
    }

    contactSuggested = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsForeignLink &contactsForeignLink)
{
    TLContactsForeignLink result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsForeignLinkUnknown:
        break;
    case ContactsForeignLinkRequested:
        *this >> result.hasPhone;
        break;
    case ContactsForeignLinkMutual:
        break;
    default:
        break;
    }

    contactsForeignLink = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsMyLink &contactsMyLink)
{
    TLContactsMyLink result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsMyLinkEmpty:
        break;
    case ContactsMyLinkRequested:
        *this >> result.contact;
        break;
    case ContactsMyLinkContact:
        break;
    default:
        break;
    }

    contactsMyLink = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDcOption &dcOption)
{
    TLDcOption result;

    *this >> result.tlType;

    switch (result.tlType) {
    case DcOption:
        *this >> result.id;
        *this >> result.hostname;
        *this >> result.ipAddress;
        *this >> result.port;
        break;
    default:
        break;
    }

    dcOption = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessageAction &decryptedMessageAction)
{
    TLDecryptedMessageAction result;

    *this >> result.tlType;

    switch (result.tlType) {
    case DecryptedMessageActionSetMessageTTL:
        *this >> result.ttlSeconds;
        break;
    case DecryptedMessageActionReadMessages:
        *this >> result.randomIds;
        break;
    case DecryptedMessageActionDeleteMessages:
        *this >> result.randomIds;
        break;
    case DecryptedMessageActionScreenshotMessages:
        *this >> result.randomIds;
        break;
    case DecryptedMessageActionFlushHistory:
        break;
    case DecryptedMessageActionNotifyLayer:
        *this >> result.layer;
        break;
    default:
        break;
    }

    decryptedMessageAction = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessageMedia &decryptedMessageMedia)
{
    TLDecryptedMessageMedia result;

    *this >> result.tlType;

    switch (result.tlType) {
    case DecryptedMessageMediaEmpty:
        break;
    case DecryptedMessageMediaPhoto:
        *this >> result.thumb;
        *this >> result.thumbW;
        *this >> result.thumbH;
        *this >> result.w;
        *this >> result.h;
        *this >> result.size;
        *this >> result.key;
        *this >> result.iv;
        break;
    case DecryptedMessageMediaVideo:
        *this >> result.thumb;
        *this >> result.thumbW;
        *this >> result.thumbH;
        *this >> result.duration;
        *this >> result.mimeType;
        *this >> result.w;
        *this >> result.h;
        *this >> result.size;
        *this >> result.key;
        *this >> result.iv;
        break;
    case DecryptedMessageMediaGeoPoint:
        *this >> result.latitude;
        *this >> result.longitude;
        break;
    case DecryptedMessageMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.userId;
        break;
    case DecryptedMessageMediaDocument:
        *this >> result.thumb;
        *this >> result.thumbW;
        *this >> result.thumbH;
        *this >> result.fileName;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.key;
        *this >> result.iv;
        break;
    case DecryptedMessageMediaAudio:
        *this >> result.duration;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.key;
        *this >> result.iv;
        break;
    default:
        break;
    }

    decryptedMessageMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedChat &encryptedChat)
{
    TLEncryptedChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case EncryptedChatEmpty:
        *this >> result.id;
        break;
    case EncryptedChatWaiting:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        break;
    case EncryptedChatRequested:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        *this >> result.gA;
        break;
    case EncryptedChat:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        *this >> result.gAOrB;
        *this >> result.keyFingerprint;
        break;
    case EncryptedChatDiscarded:
        *this >> result.id;
        break;
    default:
        break;
    }

    encryptedChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedFile &encryptedFile)
{
    TLEncryptedFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case EncryptedFileEmpty:
        break;
    case EncryptedFile:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.size;
        *this >> result.dcId;
        *this >> result.keyFingerprint;
        break;
    default:
        break;
    }

    encryptedFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedMessage &encryptedMessage)
{
    TLEncryptedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case EncryptedMessage:
        *this >> result.randomId;
        *this >> result.chatId;
        *this >> result.date;
        *this >> result.bytes;
        *this >> result.file;
        break;
    case EncryptedMessageService:
        *this >> result.randomId;
        *this >> result.chatId;
        *this >> result.date;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    encryptedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLError &error)
{
    TLError result;

    *this >> result.tlType;

    switch (result.tlType) {
    case Error:
        *this >> result.code;
        *this >> result.text;
        break;
    default:
        break;
    }

    error = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLFileLocation &fileLocation)
{
    TLFileLocation result;

    *this >> result.tlType;

    switch (result.tlType) {
    case FileLocationUnavailable:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case FileLocation:
        *this >> result.dcId;
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    default:
        break;
    }

    fileLocation = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeoPoint &geoPoint)
{
    TLGeoPoint result;

    *this >> result.tlType;

    switch (result.tlType) {
    case GeoPointEmpty:
        break;
    case GeoPoint:
        *this >> result.longitude;
        *this >> result.latitude;
        break;
    default:
        break;
    }

    geoPoint = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpAppUpdate &helpAppUpdate)
{
    TLHelpAppUpdate result;

    *this >> result.tlType;

    switch (result.tlType) {
    case HelpAppUpdate:
        *this >> result.id;
        *this >> result.critical;
        *this >> result.url;
        *this >> result.text;
        break;
    case HelpNoAppUpdate:
        break;
    default:
        break;
    }

    helpAppUpdate = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpInviteText &helpInviteText)
{
    TLHelpInviteText result;

    *this >> result.tlType;

    switch (result.tlType) {
    case HelpInviteText:
        *this >> result.message;
        break;
    default:
        break;
    }

    helpInviteText = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLImportedContact &importedContact)
{
    TLImportedContact result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ImportedContact:
        *this >> result.userId;
        *this >> result.clientId;
        break;
    default:
        break;
    }

    importedContact = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputAppEvent &inputAppEvent)
{
    TLInputAppEvent result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputAppEvent:
        *this >> result.time;
        *this >> result.type;
        *this >> result.peer;
        *this >> result.data;
        break;
    default:
        break;
    }

    inputAppEvent = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputAudio &inputAudio)
{
    TLInputAudio result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputAudioEmpty:
        break;
    case InputAudio:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputAudio = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputContact &inputContact)
{
    TLInputContact result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputPhoneContact:
        *this >> result.clientId;
        *this >> result.phone;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    default:
        break;
    }

    inputContact = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputDocument &inputDocument)
{
    TLInputDocument result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputDocumentEmpty:
        break;
    case InputDocument:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputDocument = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputEncryptedChat &inputEncryptedChat)
{
    TLInputEncryptedChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputEncryptedChat:
        *this >> result.chatId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputEncryptedChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputEncryptedFile &inputEncryptedFile)
{
    TLInputEncryptedFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputEncryptedFileEmpty:
        break;
    case InputEncryptedFileUploaded:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.md5Checksum;
        *this >> result.keyFingerprint;
        break;
    case InputEncryptedFile:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case InputEncryptedFileBigUploaded:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.keyFingerprint;
        break;
    default:
        break;
    }

    inputEncryptedFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputFile &inputFile)
{
    TLInputFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputFile:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.name;
        *this >> result.md5Checksum;
        break;
    case InputFileBig:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.name;
        break;
    default:
        break;
    }

    inputFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputFileLocation &inputFileLocation)
{
    TLInputFileLocation result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputFileLocation:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case InputVideoFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case InputEncryptedFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case InputAudioFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case InputDocumentFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputFileLocation = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputGeoChat &inputGeoChat)
{
    TLInputGeoChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputGeoChat:
        *this >> result.chatId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputGeoChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputGeoPoint &inputGeoPoint)
{
    TLInputGeoPoint result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputGeoPointEmpty:
        break;
    case InputGeoPoint:
        *this >> result.latitude;
        *this >> result.longitude;
        break;
    default:
        break;
    }

    inputGeoPoint = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeer &inputPeer)
{
    TLInputPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputPeerEmpty:
        break;
    case InputPeerSelf:
        break;
    case InputPeerContact:
        *this >> result.userId;
        break;
    case InputPeerForeign:
        *this >> result.userId;
        *this >> result.accessHash;
        break;
    case InputPeerChat:
        *this >> result.chatId;
        break;
    default:
        break;
    }

    inputPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeerNotifyEvents &inputPeerNotifyEvents)
{
    TLInputPeerNotifyEvents result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputPeerNotifyEventsEmpty:
        break;
    case InputPeerNotifyEventsAll:
        break;
    default:
        break;
    }

    inputPeerNotifyEvents = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeerNotifySettings &inputPeerNotifySettings)
{
    TLInputPeerNotifySettings result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputPeerNotifySettings:
        *this >> result.muteUntil;
        *this >> result.sound;
        *this >> result.showPreviews;
        *this >> result.eventsMask;
        break;
    default:
        break;
    }

    inputPeerNotifySettings = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPhoto &inputPhoto)
{
    TLInputPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputPhotoEmpty:
        break;
    case InputPhoto:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPhotoCrop &inputPhotoCrop)
{
    TLInputPhotoCrop result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputPhotoCropAuto:
        break;
    case InputPhotoCrop:
        *this >> result.cropLeft;
        *this >> result.cropTop;
        *this >> result.cropWidth;
        break;
    default:
        break;
    }

    inputPhotoCrop = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputUser &inputUser)
{
    TLInputUser result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputUserEmpty:
        break;
    case InputUserSelf:
        break;
    case InputUserContact:
        *this >> result.userId;
        break;
    case InputUserForeign:
        *this >> result.userId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputUser = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputVideo &inputVideo)
{
    TLInputVideo result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputVideoEmpty:
        break;
    case InputVideo:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    inputVideo = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesAffectedHistory &messagesAffectedHistory)
{
    TLMessagesAffectedHistory result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesAffectedHistory:
        *this >> result.pts;
        *this >> result.seq;
        *this >> result.offset;
        break;
    default:
        break;
    }

    messagesAffectedHistory = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesDhConfig &messagesDhConfig)
{
    TLMessagesDhConfig result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesDhConfigNotModified:
        *this >> result.random;
        break;
    case MessagesDhConfig:
        *this >> result.g;
        *this >> result.p;
        *this >> result.version;
        *this >> result.random;
        break;
    default:
        break;
    }

    messagesDhConfig = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesFilter &messagesFilter)
{
    TLMessagesFilter result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputMessagesFilterEmpty:
        break;
    case InputMessagesFilterPhotos:
        break;
    case InputMessagesFilterVideo:
        break;
    case InputMessagesFilterPhotoVideo:
        break;
    case InputMessagesFilterDocument:
        break;
    case InputMessagesFilterAudio:
        break;
    default:
        break;
    }

    messagesFilter = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessage)
{
    TLMessagesSentEncryptedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesSentEncryptedMessage:
        *this >> result.date;
        break;
    case MessagesSentEncryptedFile:
        *this >> result.date;
        *this >> result.file;
        break;
    default:
        break;
    }

    messagesSentEncryptedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNearestDc &nearestDc)
{
    TLNearestDc result;

    *this >> result.tlType;

    switch (result.tlType) {
    case NearestDc:
        *this >> result.country;
        *this >> result.thisDc;
        *this >> result.nearestDc;
        break;
    default:
        break;
    }

    nearestDc = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeer &peer)
{
    TLPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PeerUser:
        *this >> result.userId;
        break;
    case PeerChat:
        *this >> result.chatId;
        break;
    default:
        break;
    }

    peer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeerNotifyEvents &peerNotifyEvents)
{
    TLPeerNotifyEvents result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PeerNotifyEventsEmpty:
        break;
    case PeerNotifyEventsAll:
        break;
    default:
        break;
    }

    peerNotifyEvents = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeerNotifySettings &peerNotifySettings)
{
    TLPeerNotifySettings result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PeerNotifySettingsEmpty:
        break;
    case PeerNotifySettings:
        *this >> result.muteUntil;
        *this >> result.sound;
        *this >> result.showPreviews;
        *this >> result.eventsMask;
        break;
    default:
        break;
    }

    peerNotifySettings = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotoSize &photoSize)
{
    TLPhotoSize result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PhotoSizeEmpty:
        *this >> result.type;
        break;
    case PhotoSize:
        *this >> result.type;
        *this >> result.location;
        *this >> result.w;
        *this >> result.h;
        *this >> result.size;
        break;
    case PhotoCachedSize:
        *this >> result.type;
        *this >> result.location;
        *this >> result.w;
        *this >> result.h;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    photoSize = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStorageFileType &storageFileType)
{
    TLStorageFileType result;

    *this >> result.tlType;

    switch (result.tlType) {
    case StorageFileUnknown:
        break;
    case StorageFileJpeg:
        break;
    case StorageFileGif:
        break;
    case StorageFilePng:
        break;
    case StorageFilePdf:
        break;
    case StorageFileMp3:
        break;
    case StorageFileMov:
        break;
    case StorageFilePartial:
        break;
    case StorageFileMp4:
        break;
    case StorageFileWebp:
        break;
    default:
        break;
    }

    storageFileType = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesState &updatesState)
{
    TLUpdatesState result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UpdatesState:
        *this >> result.pts;
        *this >> result.qts;
        *this >> result.date;
        *this >> result.seq;
        *this >> result.unreadCount;
        break;
    default:
        break;
    }

    updatesState = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUploadFile &uploadFile)
{
    TLUploadFile result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UploadFile:
        *this >> result.type;
        *this >> result.mtime;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    uploadFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserProfilePhoto &userProfilePhoto)
{
    TLUserProfilePhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UserProfilePhotoEmpty:
        break;
    case UserProfilePhoto:
        *this >> result.photoId;
        *this >> result.photoSmall;
        *this >> result.photoBig;
        break;
    default:
        break;
    }

    userProfilePhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserStatus &userStatus)
{
    TLUserStatus result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UserStatusEmpty:
        break;
    case UserStatusOnline:
        *this >> result.expires;
        break;
    case UserStatusOffline:
        *this >> result.wasOnline;
        break;
    default:
        break;
    }

    userStatus = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLVideo &video)
{
    TLVideo result;

    *this >> result.tlType;

    switch (result.tlType) {
    case VideoEmpty:
        *this >> result.id;
        break;
    case Video:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.userId;
        *this >> result.date;
        *this >> result.caption;
        *this >> result.duration;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.thumb;
        *this >> result.dcId;
        *this >> result.w;
        *this >> result.h;
        break;
    default:
        break;
    }

    video = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLWallPaper &wallPaper)
{
    TLWallPaper result;

    *this >> result.tlType;

    switch (result.tlType) {
    case WallPaper:
        *this >> result.id;
        *this >> result.title;
        *this >> result.sizes;
        *this >> result.color;
        break;
    case WallPaperSolid:
        *this >> result.id;
        *this >> result.title;
        *this >> result.bgColor;
        *this >> result.color;
        break;
    default:
        break;
    }

    wallPaper = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatPhoto &chatPhoto)
{
    TLChatPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ChatPhotoEmpty:
        break;
    case ChatPhoto:
        *this >> result.photoSmall;
        *this >> result.photoBig;
        break;
    default:
        break;
    }

    chatPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLConfig &config)
{
    TLConfig result;

    *this >> result.tlType;

    switch (result.tlType) {
    case Config:
        *this >> result.date;
        *this >> result.testMode;
        *this >> result.thisDc;
        *this >> result.dcOptions;
        *this >> result.chatSizeMax;
        *this >> result.broadcastSizeMax;
        break;
    default:
        break;
    }

    config = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessage &decryptedMessage)
{
    TLDecryptedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case DecryptedMessage:
        *this >> result.randomId;
        *this >> result.randomBytes;
        *this >> result.message;
        *this >> result.media;
        break;
    case DecryptedMessageService:
        *this >> result.randomId;
        *this >> result.randomBytes;
        *this >> result.action;
        break;
    default:
        break;
    }

    decryptedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessageLayer &decryptedMessageLayer)
{
    TLDecryptedMessageLayer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case DecryptedMessageLayer:
        *this >> result.layer;
        *this >> result.message;
        break;
    default:
        break;
    }

    decryptedMessageLayer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDialog &dialog)
{
    TLDialog result;

    *this >> result.tlType;

    switch (result.tlType) {
    case Dialog:
        *this >> result.peer;
        *this >> result.topMessage;
        *this >> result.unreadCount;
        *this >> result.notifySettings;
        break;
    default:
        break;
    }

    dialog = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDocument &document)
{
    TLDocument result;

    *this >> result.tlType;

    switch (result.tlType) {
    case DocumentEmpty:
        *this >> result.id;
        break;
    case Document:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.userId;
        *this >> result.date;
        *this >> result.fileName;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.thumb;
        *this >> result.dcId;
        break;
    default:
        break;
    }

    document = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputChatPhoto &inputChatPhoto)
{
    TLInputChatPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputChatPhotoEmpty:
        break;
    case InputChatUploadedPhoto:
        *this >> result.file;
        *this >> result.crop;
        break;
    case InputChatPhoto:
        *this >> result.id;
        *this >> result.crop;
        break;
    default:
        break;
    }

    inputChatPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputMedia &inputMedia)
{
    TLInputMedia result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputMediaEmpty:
        break;
    case InputMediaUploadedPhoto:
        *this >> result.file;
        break;
    case InputMediaPhoto:
        *this >> result.id;
        break;
    case InputMediaGeoPoint:
        *this >> result.geoPoint;
        break;
    case InputMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    case InputMediaUploadedVideo:
        *this >> result.file;
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        *this >> result.mimeType;
        break;
    case InputMediaUploadedThumbVideo:
        *this >> result.file;
        *this >> result.thumb;
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        *this >> result.mimeType;
        break;
    case InputMediaVideo:
        *this >> result.id;
        break;
    case InputMediaUploadedAudio:
        *this >> result.file;
        *this >> result.duration;
        *this >> result.mimeType;
        break;
    case InputMediaAudio:
        *this >> result.id;
        break;
    case InputMediaUploadedDocument:
        *this >> result.file;
        *this >> result.fileName;
        *this >> result.mimeType;
        break;
    case InputMediaUploadedThumbDocument:
        *this >> result.file;
        *this >> result.thumb;
        *this >> result.fileName;
        *this >> result.mimeType;
        break;
    case InputMediaDocument:
        *this >> result.id;
        break;
    default:
        break;
    }

    inputMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputNotifyPeer &inputNotifyPeer)
{
    TLInputNotifyPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case InputNotifyPeer:
        *this >> result.peer;
        break;
    case InputNotifyUsers:
        break;
    case InputNotifyChats:
        break;
    case InputNotifyAll:
        break;
    case InputNotifyGeoChatPeer:
        *this >> result.peer;
        break;
    default:
        break;
    }

    inputNotifyPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNotifyPeer &notifyPeer)
{
    TLNotifyPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case NotifyPeer:
        *this >> result.peer;
        break;
    case NotifyUsers:
        break;
    case NotifyChats:
        break;
    case NotifyAll:
        break;
    default:
        break;
    }

    notifyPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhoto &photo)
{
    TLPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PhotoEmpty:
        *this >> result.id;
        break;
    case Photo:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.userId;
        *this >> result.date;
        *this >> result.caption;
        *this >> result.geo;
        *this >> result.sizes;
        break;
    default:
        break;
    }

    photo = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUser &user)
{
    TLUser result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UserEmpty:
        *this >> result.id;
        break;
    case UserSelf:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        *this >> result.inactive;
        break;
    case UserContact:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.accessHash;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        break;
    case UserRequest:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.accessHash;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        break;
    case UserForeign:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.accessHash;
        *this >> result.photo;
        *this >> result.status;
        break;
    case UserDeleted:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    default:
        break;
    }

    user = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthAuthorization &authAuthorization)
{
    TLAuthAuthorization result;

    *this >> result.tlType;

    switch (result.tlType) {
    case AuthAuthorization:
        *this >> result.expires;
        *this >> result.user;
        break;
    default:
        break;
    }

    authAuthorization = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChat &chat)
{
    TLChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ChatEmpty:
        *this >> result.id;
        break;
    case Chat:
        *this >> result.id;
        *this >> result.title;
        *this >> result.photo;
        *this >> result.participantsCount;
        *this >> result.date;
        *this >> result.left;
        *this >> result.version;
        break;
    case ChatForbidden:
        *this >> result.id;
        *this >> result.title;
        *this >> result.date;
        break;
    case GeoChat:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.title;
        *this >> result.address;
        *this >> result.venue;
        *this >> result.geo;
        *this >> result.photo;
        *this >> result.participantsCount;
        *this >> result.date;
        *this >> result.checkedIn;
        *this >> result.version;
        break;
    default:
        break;
    }

    chat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatFull &chatFull)
{
    TLChatFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ChatFull:
        *this >> result.id;
        *this >> result.participants;
        *this >> result.chatPhoto;
        *this >> result.notifySettings;
        break;
    default:
        break;
    }

    chatFull = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsBlocked &contactsBlocked)
{
    TLContactsBlocked result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsBlocked:
        *this >> result.blocked;
        *this >> result.users;
        break;
    case ContactsBlockedSlice:
        *this >> result.count;
        *this >> result.blocked;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsBlocked = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsContacts &contactsContacts)
{
    TLContactsContacts result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsContacts:
        *this >> result.contacts;
        *this >> result.users;
        break;
    case ContactsContactsNotModified:
        break;
    default:
        break;
    }

    contactsContacts = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsFound &contactsFound)
{
    TLContactsFound result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsFound:
        *this >> result.results;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsFound = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsImportedContacts &contactsImportedContacts)
{
    TLContactsImportedContacts result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsImportedContacts:
        *this >> result.imported;
        *this >> result.retryContacts;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsImportedContacts = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsLink &contactsLink)
{
    TLContactsLink result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsLink:
        *this >> result.myLink;
        *this >> result.foreignLink;
        *this >> result.user;
        break;
    default:
        break;
    }

    contactsLink = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsSuggested &contactsSuggested)
{
    TLContactsSuggested result;

    *this >> result.tlType;

    switch (result.tlType) {
    case ContactsSuggested:
        *this >> result.results;
        *this >> result.users;
        break;
    default:
        break;
    }

    contactsSuggested = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpSupport &helpSupport)
{
    TLHelpSupport result;

    *this >> result.tlType;

    switch (result.tlType) {
    case HelpSupport:
        *this >> result.phoneNumber;
        *this >> result.user;
        break;
    default:
        break;
    }

    helpSupport = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageAction &messageAction)
{
    TLMessageAction result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessageActionEmpty:
        break;
    case MessageActionChatCreate:
        *this >> result.title;
        *this >> result.users;
        break;
    case MessageActionChatEditTitle:
        *this >> result.title;
        break;
    case MessageActionChatEditPhoto:
        *this >> result.photo;
        break;
    case MessageActionChatDeletePhoto:
        break;
    case MessageActionChatAddUser:
        *this >> result.userId;
        break;
    case MessageActionChatDeleteUser:
        *this >> result.userId;
        break;
    case MessageActionGeoChatCreate:
        *this >> result.title;
        *this >> result.address;
        break;
    case MessageActionGeoChatCheckin:
        break;
    default:
        break;
    }

    messageAction = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageMedia &messageMedia)
{
    TLMessageMedia result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessageMediaEmpty:
        break;
    case MessageMediaPhoto:
        *this >> result.photo;
        break;
    case MessageMediaVideo:
        *this >> result.video;
        break;
    case MessageMediaGeo:
        *this >> result.geo;
        break;
    case MessageMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.userId;
        break;
    case MessageMediaUnsupported:
        *this >> result.bytes;
        break;
    case MessageMediaDocument:
        *this >> result.document;
        break;
    case MessageMediaAudio:
        *this >> result.audio;
        break;
    default:
        break;
    }

    messageMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChat &messagesChat)
{
    TLMessagesChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesChat:
        *this >> result.chat;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChatFull &messagesChatFull)
{
    TLMessagesChatFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesChatFull:
        *this >> result.fullChat;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesChatFull = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChats &messagesChats)
{
    TLMessagesChats result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesChats:
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesChats = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesSentMessage &messagesSentMessage)
{
    TLMessagesSentMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesSentMessage:
        *this >> result.id;
        *this >> result.date;
        *this >> result.pts;
        *this >> result.seq;
        break;
    case MessagesSentMessageLink:
        *this >> result.id;
        *this >> result.date;
        *this >> result.pts;
        *this >> result.seq;
        *this >> result.links;
        break;
    default:
        break;
    }

    messagesSentMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotosPhoto &photosPhoto)
{
    TLPhotosPhoto result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PhotosPhoto:
        *this >> result.photo;
        *this >> result.users;
        break;
    default:
        break;
    }

    photosPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotosPhotos &photosPhotos)
{
    TLPhotosPhotos result;

    *this >> result.tlType;

    switch (result.tlType) {
    case PhotosPhotos:
        *this >> result.photos;
        *this >> result.users;
        break;
    case PhotosPhotosSlice:
        *this >> result.count;
        *this >> result.photos;
        *this >> result.users;
        break;
    default:
        break;
    }

    photosPhotos = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserFull &userFull)
{
    TLUserFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UserFull:
        *this >> result.user;
        *this >> result.link;
        *this >> result.profilePhoto;
        *this >> result.notifySettings;
        *this >> result.blocked;
        *this >> result.realFirstName;
        *this >> result.realLastName;
        break;
    default:
        break;
    }

    userFull = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeoChatMessage &geoChatMessage)
{
    TLGeoChatMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case GeoChatMessageEmpty:
        *this >> result.chatId;
        *this >> result.id;
        break;
    case GeoChatMessage:
        *this >> result.chatId;
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.date;
        *this >> result.message;
        *this >> result.media;
        break;
    case GeoChatMessageService:
        *this >> result.chatId;
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.date;
        *this >> result.action;
        break;
    default:
        break;
    }

    geoChatMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeochatsLocated &geochatsLocated)
{
    TLGeochatsLocated result;

    *this >> result.tlType;

    switch (result.tlType) {
    case GeochatsLocated:
        *this >> result.results;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    geochatsLocated = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeochatsMessages &geochatsMessages)
{
    TLGeochatsMessages result;

    *this >> result.tlType;

    switch (result.tlType) {
    case GeochatsMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case GeochatsMessagesSlice:
        *this >> result.count;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    geochatsMessages = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeochatsStatedMessage &geochatsStatedMessage)
{
    TLGeochatsStatedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case GeochatsStatedMessage:
        *this >> result.message;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.seq;
        break;
    default:
        break;
    }

    geochatsStatedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessage &message)
{
    TLMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessageEmpty:
        *this >> result.id;
        break;
    case Message:
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.toId;
        *this >> result.out;
        *this >> result.unread;
        *this >> result.date;
        *this >> result.message;
        *this >> result.media;
        break;
    case MessageForwarded:
        *this >> result.id;
        *this >> result.fwdFromId;
        *this >> result.fwdDate;
        *this >> result.fromId;
        *this >> result.toId;
        *this >> result.out;
        *this >> result.unread;
        *this >> result.date;
        *this >> result.message;
        *this >> result.media;
        break;
    case MessageService:
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.toId;
        *this >> result.out;
        *this >> result.unread;
        *this >> result.date;
        *this >> result.action;
        break;
    default:
        break;
    }

    message = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesDialogs &messagesDialogs)
{
    TLMessagesDialogs result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesDialogs:
        *this >> result.dialogs;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case MessagesDialogsSlice:
        *this >> result.count;
        *this >> result.dialogs;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesDialogs = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesMessage &messagesMessage)
{
    TLMessagesMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesMessageEmpty:
        break;
    case MessagesMessage:
        *this >> result.message;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesMessages &messagesMessages)
{
    TLMessagesMessages result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case MessagesMessagesSlice:
        *this >> result.count;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    messagesMessages = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStatedMessage &messagesStatedMessage)
{
    TLMessagesStatedMessage result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesStatedMessage:
        *this >> result.message;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.pts;
        *this >> result.seq;
        break;
    case MessagesStatedMessageLink:
        *this >> result.message;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.links;
        *this >> result.pts;
        *this >> result.seq;
        break;
    default:
        break;
    }

    messagesStatedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStatedMessages &messagesStatedMessages)
{
    TLMessagesStatedMessages result;

    *this >> result.tlType;

    switch (result.tlType) {
    case MessagesStatedMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.pts;
        *this >> result.seq;
        break;
    case MessagesStatedMessagesLinks:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.links;
        *this >> result.pts;
        *this >> result.seq;
        break;
    default:
        break;
    }

    messagesStatedMessages = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdate &update)
{
    TLUpdate result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UpdateNewMessage:
        *this >> result.message;
        *this >> result.pts;
        break;
    case UpdateMessageID:
        *this >> result.id;
        *this >> result.randomId;
        break;
    case UpdateReadMessages:
        *this >> result.messages;
        *this >> result.pts;
        break;
    case UpdateDeleteMessages:
        *this >> result.messages;
        *this >> result.pts;
        break;
    case UpdateRestoreMessages:
        *this >> result.messages;
        *this >> result.pts;
        break;
    case UpdateUserTyping:
        *this >> result.userId;
        break;
    case UpdateChatUserTyping:
        *this >> result.chatId;
        *this >> result.userId;
        break;
    case UpdateChatParticipants:
        *this >> result.participants;
        break;
    case UpdateUserStatus:
        *this >> result.userId;
        *this >> result.status;
        break;
    case UpdateUserName:
        *this >> result.userId;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    case UpdateUserPhoto:
        *this >> result.userId;
        *this >> result.date;
        *this >> result.photo;
        *this >> result.previous;
        break;
    case UpdateContactRegistered:
        *this >> result.userId;
        *this >> result.date;
        break;
    case UpdateContactLink:
        *this >> result.userId;
        *this >> result.myLink;
        *this >> result.foreignLink;
        break;
    case UpdateActivation:
        *this >> result.userId;
        break;
    case UpdateNewAuthorization:
        *this >> result.authKeyId;
        *this >> result.date;
        *this >> result.device;
        *this >> result.location;
        break;
    case UpdateNewGeoChatMessage:
        *this >> result.message;
        break;
    case UpdateNewEncryptedMessage:
        *this >> result.message;
        *this >> result.qts;
        break;
    case UpdateEncryptedChatTyping:
        *this >> result.chatId;
        break;
    case UpdateEncryption:
        *this >> result.chat;
        *this >> result.date;
        break;
    case UpdateEncryptedMessagesRead:
        *this >> result.chatId;
        *this >> result.maxDate;
        *this >> result.date;
        break;
    case UpdateChatParticipantAdd:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.version;
        break;
    case UpdateChatParticipantDelete:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.version;
        break;
    case UpdateDcOptions:
        *this >> result.dcOptions;
        break;
    case UpdateUserBlocked:
        *this >> result.userId;
        *this >> result.blocked;
        break;
    case UpdateNotifySettings:
        *this >> result.peer;
        *this >> result.notifySettings;
        break;
    default:
        break;
    }

    update = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdates &updates)
{
    TLUpdates result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UpdatesTooLong:
        break;
    case UpdateShortMessage:
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.message;
        *this >> result.pts;
        *this >> result.date;
        *this >> result.seq;
        break;
    case UpdateShortChatMessage:
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.chatId;
        *this >> result.message;
        *this >> result.pts;
        *this >> result.date;
        *this >> result.seq;
        break;
    case UpdateShort:
        *this >> result.update;
        *this >> result.date;
        break;
    case UpdatesCombined:
        *this >> result.updates;
        *this >> result.users;
        *this >> result.chats;
        *this >> result.date;
        *this >> result.seqStart;
        *this >> result.seq;
        break;
    case Updates:
        *this >> result.updates;
        *this >> result.users;
        *this >> result.chats;
        *this >> result.date;
        *this >> result.seq;
        break;
    default:
        break;
    }

    updates = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesDifference &updatesDifference)
{
    TLUpdatesDifference result;

    *this >> result.tlType;

    switch (result.tlType) {
    case UpdatesDifferenceEmpty:
        *this >> result.date;
        *this >> result.seq;
        break;
    case UpdatesDifference:
        *this >> result.newMessages;
        *this >> result.newEncryptedMessages;
        *this >> result.otherUpdates;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.state;
        break;
    case UpdatesDifferenceSlice:
        *this >> result.newMessages;
        *this >> result.newEncryptedMessages;
        *this >> result.otherUpdates;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.intermediateState;
        break;
    default:
        break;
    }

    updatesDifference = result;

    return *this;
}

// End of generated read operators implementation

template <typename T>
CTelegramStream &CTelegramStream::operator<<(const TLVector<T> &v)
{
    *this << v.tlType;

    if (v.tlType == Vector) {
        *this << quint32(v.count());

        for (int i = 0; i < v.count(); ++i) {
            *this << v.at(i);
        }
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const QByteArray &data)
{
    quint32 length = data.size();

    if (length < 0xfe) {
        const char lengthToWrite = length;
        m_device->putChar(lengthToWrite);
        m_device->write(data);
        length += 1;

    } else {
        *this << quint32((length << 8) + 0xfe);
        m_device->write(data);
        length += 4;
    }

    if (length & 3) {
        m_device->write(s_nulls, 4 - (length & 3));
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLDcOption &dcOption)
{
    *this << dcOption.tlType;

    *this << dcOption.id;
    *this << dcOption.hostname;
    *this << dcOption.ipAddress;
    *this << dcOption.port;

    return *this;
}

// Generated write operators implementation
CTelegramStream &CTelegramStream::operator<<(const TLInputAppEvent &inputAppEvent)
{
    *this << inputAppEvent.tlType;

    switch (inputAppEvent.tlType) {
    case InputAppEvent:
        *this << inputAppEvent.time;
        *this << inputAppEvent.type;
        *this << inputAppEvent.peer;
        *this << inputAppEvent.data;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputContact &inputContact)
{
    *this << inputContact.tlType;

    switch (inputContact.tlType) {
    case InputPhoneContact:
        *this << inputContact.clientId;
        *this << inputContact.phone;
        *this << inputContact.firstName;
        *this << inputContact.lastName;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputEncryptedChat &inputEncryptedChat)
{
    *this << inputEncryptedChat.tlType;

    switch (inputEncryptedChat.tlType) {
    case InputEncryptedChat:
        *this << inputEncryptedChat.chatId;
        *this << inputEncryptedChat.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputEncryptedFile &inputEncryptedFile)
{
    *this << inputEncryptedFile.tlType;

    switch (inputEncryptedFile.tlType) {
    case InputEncryptedFileEmpty:
        break;
    case InputEncryptedFileUploaded:
        *this << inputEncryptedFile.id;
        *this << inputEncryptedFile.parts;
        *this << inputEncryptedFile.md5Checksum;
        *this << inputEncryptedFile.keyFingerprint;
        break;
    case InputEncryptedFile:
        *this << inputEncryptedFile.id;
        *this << inputEncryptedFile.accessHash;
        break;
    case InputEncryptedFileBigUploaded:
        *this << inputEncryptedFile.id;
        *this << inputEncryptedFile.parts;
        *this << inputEncryptedFile.keyFingerprint;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputFile &inputFile)
{
    *this << inputFile.tlType;

    switch (inputFile.tlType) {
    case InputFile:
        *this << inputFile.id;
        *this << inputFile.parts;
        *this << inputFile.name;
        *this << inputFile.md5Checksum;
        break;
    case InputFileBig:
        *this << inputFile.id;
        *this << inputFile.parts;
        *this << inputFile.name;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputFileLocation &inputFileLocation)
{
    *this << inputFileLocation.tlType;

    switch (inputFileLocation.tlType) {
    case InputFileLocation:
        *this << inputFileLocation.volumeId;
        *this << inputFileLocation.localId;
        *this << inputFileLocation.secret;
        break;
    case InputVideoFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    case InputEncryptedFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    case InputAudioFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    case InputDocumentFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputGeoChat &inputGeoChat)
{
    *this << inputGeoChat.tlType;

    switch (inputGeoChat.tlType) {
    case InputGeoChat:
        *this << inputGeoChat.chatId;
        *this << inputGeoChat.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputGeoPoint &inputGeoPoint)
{
    *this << inputGeoPoint.tlType;

    switch (inputGeoPoint.tlType) {
    case InputGeoPointEmpty:
        break;
    case InputGeoPoint:
        *this << inputGeoPoint.latitude;
        *this << inputGeoPoint.longitude;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPeer &inputPeer)
{
    *this << inputPeer.tlType;

    switch (inputPeer.tlType) {
    case InputPeerEmpty:
        break;
    case InputPeerSelf:
        break;
    case InputPeerContact:
        *this << inputPeer.userId;
        break;
    case InputPeerForeign:
        *this << inputPeer.userId;
        *this << inputPeer.accessHash;
        break;
    case InputPeerChat:
        *this << inputPeer.chatId;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettings)
{
    *this << inputPeerNotifySettings.tlType;

    switch (inputPeerNotifySettings.tlType) {
    case InputPeerNotifySettings:
        *this << inputPeerNotifySettings.muteUntil;
        *this << inputPeerNotifySettings.sound;
        *this << inputPeerNotifySettings.showPreviews;
        *this << inputPeerNotifySettings.eventsMask;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPhoto &inputPhoto)
{
    *this << inputPhoto.tlType;

    switch (inputPhoto.tlType) {
    case InputPhotoEmpty:
        break;
    case InputPhoto:
        *this << inputPhoto.id;
        *this << inputPhoto.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPhotoCrop &inputPhotoCrop)
{
    *this << inputPhotoCrop.tlType;

    switch (inputPhotoCrop.tlType) {
    case InputPhotoCropAuto:
        break;
    case InputPhotoCrop:
        *this << inputPhotoCrop.cropLeft;
        *this << inputPhotoCrop.cropTop;
        *this << inputPhotoCrop.cropWidth;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputUser &inputUser)
{
    *this << inputUser.tlType;

    switch (inputUser.tlType) {
    case InputUserEmpty:
        break;
    case InputUserSelf:
        break;
    case InputUserContact:
        *this << inputUser.userId;
        break;
    case InputUserForeign:
        *this << inputUser.userId;
        *this << inputUser.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLMessagesFilter &messagesFilter)
{
    *this << messagesFilter.tlType;

    switch (messagesFilter.tlType) {
    case InputMessagesFilterEmpty:
        break;
    case InputMessagesFilterPhotos:
        break;
    case InputMessagesFilterVideo:
        break;
    case InputMessagesFilterPhotoVideo:
        break;
    case InputMessagesFilterDocument:
        break;
    case InputMessagesFilterAudio:
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputChatPhoto &inputChatPhoto)
{
    *this << inputChatPhoto.tlType;

    switch (inputChatPhoto.tlType) {
    case InputChatPhotoEmpty:
        break;
    case InputChatUploadedPhoto:
        *this << inputChatPhoto.file;
        *this << inputChatPhoto.crop;
        break;
    case InputChatPhoto:
        *this << inputChatPhoto.id;
        *this << inputChatPhoto.crop;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputMedia &inputMedia)
{
    *this << inputMedia.tlType;

    switch (inputMedia.tlType) {
    case InputMediaEmpty:
        break;
    case InputMediaUploadedPhoto:
        *this << inputMedia.file;
        break;
    case InputMediaPhoto:
        *this << inputMedia.id;
        break;
    case InputMediaGeoPoint:
        *this << inputMedia.geoPoint;
        break;
    case InputMediaContact:
        *this << inputMedia.phoneNumber;
        *this << inputMedia.firstName;
        *this << inputMedia.lastName;
        break;
    case InputMediaUploadedVideo:
        *this << inputMedia.file;
        *this << inputMedia.duration;
        *this << inputMedia.w;
        *this << inputMedia.h;
        *this << inputMedia.mimeType;
        break;
    case InputMediaUploadedThumbVideo:
        *this << inputMedia.file;
        *this << inputMedia.thumb;
        *this << inputMedia.duration;
        *this << inputMedia.w;
        *this << inputMedia.h;
        *this << inputMedia.mimeType;
        break;
    case InputMediaVideo:
        *this << inputMedia.id;
        break;
    case InputMediaUploadedAudio:
        *this << inputMedia.file;
        *this << inputMedia.duration;
        *this << inputMedia.mimeType;
        break;
    case InputMediaAudio:
        *this << inputMedia.id;
        break;
    case InputMediaUploadedDocument:
        *this << inputMedia.file;
        *this << inputMedia.fileName;
        *this << inputMedia.mimeType;
        break;
    case InputMediaUploadedThumbDocument:
        *this << inputMedia.file;
        *this << inputMedia.thumb;
        *this << inputMedia.fileName;
        *this << inputMedia.mimeType;
        break;
    case InputMediaDocument:
        *this << inputMedia.id;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputNotifyPeer &inputNotifyPeer)
{
    *this << inputNotifyPeer.tlType;

    switch (inputNotifyPeer.tlType) {
    case InputNotifyPeer:
        *this << inputNotifyPeer.peer;
        break;
    case InputNotifyUsers:
        break;
    case InputNotifyChats:
        break;
    case InputNotifyAll:
        break;
    case InputNotifyGeoChatPeer:
        *this << inputNotifyPeer.peer;
        break;
    default:
        break;
    }

    return *this;
}

// End of generated write operators implementation
