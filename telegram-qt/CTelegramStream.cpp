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

template CTelegramStream &CTelegramStream::operator>>(QVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<quint64> &v);

template CTelegramStream &CTelegramStream::operator<<(const QVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const QVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const QVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const QVector<quint64> &v);

template CTelegramStream &CTelegramStream::operator>>(QVector<TLUser> &v);
template CTelegramStream &CTelegramStream::operator>>(QVector<TLContact> &v);

template CTelegramStream &CTelegramStream::operator<<(const QVector<TLInputContact> &v);

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
CTelegramStream &CTelegramStream::operator>>(QVector<T> &v)
{
    QVector<T> result;

    TLValue vectorHash;

    *this >> vectorHash;

    if (vectorHash == Vector) {
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

// Generated operators implementation
CTelegramStream &CTelegramStream::operator>>(TLAudio &audio)
{
    TLAudio result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    audio = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthCheckedPhone &authCheckedPhone)
{
    TLAuthCheckedPhone result;

    TLValue type;
    *this >> type;

    switch (type) {
    case AuthCheckedPhone:
        *this >> result.phoneRegistered;
        *this >> result.phoneInvited;
        break;
    default:
        break;
    }

    result.tlType = type;
    authCheckedPhone = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthExportedAuthorization &authExportedAuthorization)
{
    TLAuthExportedAuthorization result;

    TLValue type;
    *this >> type;

    switch (type) {
    case AuthExportedAuthorization:
        *this >> result.id;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    result.tlType = type;
    authExportedAuthorization = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthSentCode &authSentCode)
{
    TLAuthSentCode result;

    TLValue type;
    *this >> type;

    switch (type) {
    case AuthSentCode:
        *this >> result.phoneRegistered;
        *this >> result.phoneCodeHash;
        *this >> result.sendCallTimeout;
        *this >> result.isPassword;
        break;
    default:
        break;
    }

    result.tlType = type;
    authSentCode = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatLocated &chatLocated)
{
    TLChatLocated result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ChatLocated:
        *this >> result.chatId;
        *this >> result.distance;
        break;
    default:
        break;
    }

    result.tlType = type;
    chatLocated = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatParticipant &chatParticipant)
{
    TLChatParticipant result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ChatParticipant:
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.date;
        break;
    default:
        break;
    }

    result.tlType = type;
    chatParticipant = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatParticipants &chatParticipants)
{
    TLChatParticipants result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    chatParticipants = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContact &contact)
{
    TLContact result;

    TLValue type;
    *this >> type;

    switch (type) {
    case Contact:
        *this >> result.userId;
        *this >> result.mutual;
        break;
    default:
        break;
    }

    result.tlType = type;
    contact = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactBlocked &contactBlocked)
{
    TLContactBlocked result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactBlocked:
        *this >> result.userId;
        *this >> result.date;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactBlocked = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactFound &contactFound)
{
    TLContactFound result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactFound:
        *this >> result.userId;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactFound = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactStatus &contactStatus)
{
    TLContactStatus result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactStatus:
        *this >> result.userId;
        *this >> result.expires;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactStatus = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactSuggested &contactSuggested)
{
    TLContactSuggested result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactSuggested:
        *this >> result.userId;
        *this >> result.mutualContacts;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactSuggested = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsForeignLink &contactsForeignLink)
{
    TLContactsForeignLink result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    contactsForeignLink = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsMyLink &contactsMyLink)
{
    TLContactsMyLink result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    contactsMyLink = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDcOption &dcOption)
{
    TLDcOption result;

    TLValue type;
    *this >> type;

    switch (type) {
    case DcOption:
        *this >> result.id;
        *this >> result.hostname;
        *this >> result.ipAddress;
        *this >> result.port;
        break;
    default:
        break;
    }

    result.tlType = type;
    dcOption = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessageAction &decryptedMessageAction)
{
    TLDecryptedMessageAction result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    decryptedMessageAction = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessageMedia &decryptedMessageMedia)
{
    TLDecryptedMessageMedia result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    decryptedMessageMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedChat &encryptedChat)
{
    TLEncryptedChat result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    encryptedChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedFile &encryptedFile)
{
    TLEncryptedFile result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    encryptedFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedMessage &encryptedMessage)
{
    TLEncryptedMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    encryptedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLError &error)
{
    TLError result;

    TLValue type;
    *this >> type;

    switch (type) {
    case Error:
        *this >> result.code;
        *this >> result.text;
        break;
    default:
        break;
    }

    result.tlType = type;
    error = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLFileLocation &fileLocation)
{
    TLFileLocation result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    fileLocation = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeoPoint &geoPoint)
{
    TLGeoPoint result;

    TLValue type;
    *this >> type;

    switch (type) {
    case GeoPointEmpty:
        break;
    case GeoPoint:
        *this >> result.longitude;
        *this >> result.latitude;
        break;
    default:
        break;
    }

    result.tlType = type;
    geoPoint = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpAppUpdate &helpAppUpdate)
{
    TLHelpAppUpdate result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    helpAppUpdate = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpInviteText &helpInviteText)
{
    TLHelpInviteText result;

    TLValue type;
    *this >> type;

    switch (type) {
    case HelpInviteText:
        *this >> result.message;
        break;
    default:
        break;
    }

    result.tlType = type;
    helpInviteText = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLImportedContact &importedContact)
{
    TLImportedContact result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ImportedContact:
        *this >> result.userId;
        *this >> result.clientId;
        break;
    default:
        break;
    }

    result.tlType = type;
    importedContact = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputAppEvent &inputAppEvent)
{
    TLInputAppEvent result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputAppEvent:
        *this >> result.time;
        *this >> result.type;
        *this >> result.peer;
        *this >> result.data;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputAppEvent = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputAudio &inputAudio)
{
    TLInputAudio result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputAudioEmpty:
        break;
    case InputAudio:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputAudio = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputContact &inputContact)
{
    TLInputContact result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputPhoneContact:
        *this >> result.clientId;
        *this >> result.phone;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputContact = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputDocument &inputDocument)
{
    TLInputDocument result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputDocumentEmpty:
        break;
    case InputDocument:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputDocument = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputEncryptedChat &inputEncryptedChat)
{
    TLInputEncryptedChat result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputEncryptedChat:
        *this >> result.chatId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputEncryptedChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputEncryptedFile &inputEncryptedFile)
{
    TLInputEncryptedFile result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputEncryptedFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputFile &inputFile)
{
    TLInputFile result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputFileLocation &inputFileLocation)
{
    TLInputFileLocation result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputFileLocation = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputGeoChat &inputGeoChat)
{
    TLInputGeoChat result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputGeoChat:
        *this >> result.chatId;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputGeoChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputGeoPoint &inputGeoPoint)
{
    TLInputGeoPoint result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputGeoPointEmpty:
        break;
    case InputGeoPoint:
        *this >> result.latitude;
        *this >> result.longitude;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputGeoPoint = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeer &inputPeer)
{
    TLInputPeer result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeerNotifyEvents &inputPeerNotifyEvents)
{
    TLInputPeerNotifyEvents result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputPeerNotifyEventsEmpty:
        break;
    case InputPeerNotifyEventsAll:
        break;
    default:
        break;
    }

    result.tlType = type;
    inputPeerNotifyEvents = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPeerNotifySettings &inputPeerNotifySettings)
{
    TLInputPeerNotifySettings result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputPeerNotifySettings:
        *this >> result.muteUntil;
        *this >> result.sound;
        *this >> result.showPreviews;
        *this >> result.eventsMask;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputPeerNotifySettings = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPhoto &inputPhoto)
{
    TLInputPhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputPhotoEmpty:
        break;
    case InputPhoto:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPhotoCrop &inputPhotoCrop)
{
    TLInputPhotoCrop result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputPhotoCrop = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputUser &inputUser)
{
    TLInputUser result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputUser = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputVideo &inputVideo)
{
    TLInputVideo result;

    TLValue type;
    *this >> type;

    switch (type) {
    case InputVideoEmpty:
        break;
    case InputVideo:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    default:
        break;
    }

    result.tlType = type;
    inputVideo = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesAffectedHistory &messagesAffectedHistory)
{
    TLMessagesAffectedHistory result;

    TLValue type;
    *this >> type;

    switch (type) {
    case MessagesAffectedHistory:
        *this >> result.pts;
        *this >> result.seq;
        *this >> result.offset;
        break;
    default:
        break;
    }

    result.tlType = type;
    messagesAffectedHistory = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesDhConfig &messagesDhConfig)
{
    TLMessagesDhConfig result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesDhConfig = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesFilter &messagesFilter)
{
    TLMessagesFilter result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesFilter = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessage)
{
    TLMessagesSentEncryptedMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesSentEncryptedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNearestDc &nearestDc)
{
    TLNearestDc result;

    TLValue type;
    *this >> type;

    switch (type) {
    case NearestDc:
        *this >> result.country;
        *this >> result.thisDc;
        *this >> result.nearestDc;
        break;
    default:
        break;
    }

    result.tlType = type;
    nearestDc = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeer &peer)
{
    TLPeer result;

    TLValue type;
    *this >> type;

    switch (type) {
    case PeerUser:
        *this >> result.userId;
        break;
    case PeerChat:
        *this >> result.chatId;
        break;
    default:
        break;
    }

    result.tlType = type;
    peer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeerNotifyEvents &peerNotifyEvents)
{
    TLPeerNotifyEvents result;

    TLValue type;
    *this >> type;

    switch (type) {
    case PeerNotifyEventsEmpty:
        break;
    case PeerNotifyEventsAll:
        break;
    default:
        break;
    }

    result.tlType = type;
    peerNotifyEvents = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPeerNotifySettings &peerNotifySettings)
{
    TLPeerNotifySettings result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    peerNotifySettings = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotoSize &photoSize)
{
    TLPhotoSize result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    photoSize = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStorageFileType &storageFileType)
{
    TLStorageFileType result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    storageFileType = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesState &updatesState)
{
    TLUpdatesState result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    updatesState = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUploadFile &uploadFile)
{
    TLUploadFile result;

    TLValue type;
    *this >> type;

    switch (type) {
    case UploadFile:
        *this >> result.type;
        *this >> result.mtime;
        *this >> result.bytes;
        break;
    default:
        break;
    }

    result.tlType = type;
    uploadFile = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserProfilePhoto &userProfilePhoto)
{
    TLUserProfilePhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    userProfilePhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserStatus &userStatus)
{
    TLUserStatus result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    userStatus = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLVideo &video)
{
    TLVideo result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    video = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLWallPaper &wallPaper)
{
    TLWallPaper result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    wallPaper = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatPhoto &chatPhoto)
{
    TLChatPhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ChatPhotoEmpty:
        break;
    case ChatPhoto:
        *this >> result.photoSmall;
        *this >> result.photoBig;
        break;
    default:
        break;
    }

    result.tlType = type;
    chatPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLConfig &config)
{
    TLConfig result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    config = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessage &decryptedMessage)
{
    TLDecryptedMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    decryptedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDecryptedMessageLayer &decryptedMessageLayer)
{
    TLDecryptedMessageLayer result;

    TLValue type;
    *this >> type;

    switch (type) {
    case DecryptedMessageLayer:
        *this >> result.layer;
        *this >> result.message;
        break;
    default:
        break;
    }

    result.tlType = type;
    decryptedMessageLayer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDialog &dialog)
{
    TLDialog result;

    TLValue type;
    *this >> type;

    switch (type) {
    case Dialog:
        *this >> result.peer;
        *this >> result.topMessage;
        *this >> result.unreadCount;
        *this >> result.notifySettings;
        break;
    default:
        break;
    }

    result.tlType = type;
    dialog = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDocument &document)
{
    TLDocument result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    document = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputChatPhoto &inputChatPhoto)
{
    TLInputChatPhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputChatPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputMedia &inputMedia)
{
    TLInputMedia result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputNotifyPeer &inputNotifyPeer)
{
    TLInputNotifyPeer result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    inputNotifyPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNotifyPeer &notifyPeer)
{
    TLNotifyPeer result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    notifyPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhoto &photo)
{
    TLPhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    photo = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUser &user)
{
    TLUser result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    user = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthAuthorization &authAuthorization)
{
    TLAuthAuthorization result;

    TLValue type;
    *this >> type;

    switch (type) {
    case AuthAuthorization:
        *this >> result.expires;
        *this >> result.user;
        break;
    default:
        break;
    }

    result.tlType = type;
    authAuthorization = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChat &chat)
{
    TLChat result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    chat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLChatFull &chatFull)
{
    TLChatFull result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ChatFull:
        *this >> result.id;
        *this >> result.participants;
        *this >> result.chatPhoto;
        *this >> result.notifySettings;
        break;
    default:
        break;
    }

    result.tlType = type;
    chatFull = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsBlocked &contactsBlocked)
{
    TLContactsBlocked result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    contactsBlocked = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsContacts &contactsContacts)
{
    TLContactsContacts result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactsContacts:
        *this >> result.contacts;
        *this >> result.users;
        break;
    case ContactsContactsNotModified:
        break;
    default:
        break;
    }

    result.tlType = type;
    contactsContacts = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsFound &contactsFound)
{
    TLContactsFound result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactsFound:
        *this >> result.results;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactsFound = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsImportedContacts &contactsImportedContacts)
{
    TLContactsImportedContacts result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactsImportedContacts:
        *this >> result.imported;
        *this >> result.retryContacts;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactsImportedContacts = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsLink &contactsLink)
{
    TLContactsLink result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactsLink:
        *this >> result.myLink;
        *this >> result.foreignLink;
        *this >> result.user;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactsLink = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactsSuggested &contactsSuggested)
{
    TLContactsSuggested result;

    TLValue type;
    *this >> type;

    switch (type) {
    case ContactsSuggested:
        *this >> result.results;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    contactsSuggested = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLHelpSupport &helpSupport)
{
    TLHelpSupport result;

    TLValue type;
    *this >> type;

    switch (type) {
    case HelpSupport:
        *this >> result.phoneNumber;
        *this >> result.user;
        break;
    default:
        break;
    }

    result.tlType = type;
    helpSupport = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageAction &messageAction)
{
    TLMessageAction result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messageAction = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessageMedia &messageMedia)
{
    TLMessageMedia result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messageMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChat &messagesChat)
{
    TLMessagesChat result;

    TLValue type;
    *this >> type;

    switch (type) {
    case MessagesChat:
        *this >> result.chat;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    messagesChat = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChatFull &messagesChatFull)
{
    TLMessagesChatFull result;

    TLValue type;
    *this >> type;

    switch (type) {
    case MessagesChatFull:
        *this >> result.fullChat;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    messagesChatFull = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChats &messagesChats)
{
    TLMessagesChats result;

    TLValue type;
    *this >> type;

    switch (type) {
    case MessagesChats:
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    messagesChats = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesSentMessage &messagesSentMessage)
{
    TLMessagesSentMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesSentMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotosPhoto &photosPhoto)
{
    TLPhotosPhoto result;

    TLValue type;
    *this >> type;

    switch (type) {
    case PhotosPhoto:
        *this >> result.photo;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    photosPhoto = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPhotosPhotos &photosPhotos)
{
    TLPhotosPhotos result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    photosPhotos = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUserFull &userFull)
{
    TLUserFull result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    userFull = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeoChatMessage &geoChatMessage)
{
    TLGeoChatMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    geoChatMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeochatsLocated &geochatsLocated)
{
    TLGeochatsLocated result;

    TLValue type;
    *this >> type;

    switch (type) {
    case GeochatsLocated:
        *this >> result.results;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    default:
        break;
    }

    result.tlType = type;
    geochatsLocated = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeochatsMessages &geochatsMessages)
{
    TLGeochatsMessages result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    geochatsMessages = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLGeochatsStatedMessage &geochatsStatedMessage)
{
    TLGeochatsStatedMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
    case GeochatsStatedMessage:
        *this >> result.message;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.seq;
        break;
    default:
        break;
    }

    result.tlType = type;
    geochatsStatedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessage &message)
{
    TLMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    message = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesDialogs &messagesDialogs)
{
    TLMessagesDialogs result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesDialogs = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesMessage &messagesMessage)
{
    TLMessagesMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesMessages &messagesMessages)
{
    TLMessagesMessages result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesMessages = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStatedMessage &messagesStatedMessage)
{
    TLMessagesStatedMessage result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesStatedMessage = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStatedMessages &messagesStatedMessages)
{
    TLMessagesStatedMessages result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    messagesStatedMessages = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdate &update)
{
    TLUpdate result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    update = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdates &updates)
{
    TLUpdates result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    updates = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLUpdatesDifference &updatesDifference)
{
    TLUpdatesDifference result;

    TLValue type;
    *this >> type;

    switch (type) {
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

    result.tlType = type;
    updatesDifference = result;

    return *this;
}

// End of generated operators implementation

template <typename T>
CTelegramStream &CTelegramStream::operator<<(const QVector<T> &v)
{
    *this << Vector;
    *this << quint32(v.count());

    for (int i = 0; i < v.count(); ++i) {
        *this << v.at(i);
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

CTelegramStream &CTelegramStream::operator<<(const TLInputContact &inputContact)
{
    *this << inputContact.tlType;

    *this << inputContact.clientId;
    *this << inputContact.phone;
    *this << inputContact.firstName;
    *this << inputContact.lastName;

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
