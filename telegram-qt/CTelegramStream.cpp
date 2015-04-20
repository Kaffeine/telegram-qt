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

#include "CTelegramStream.hpp"

#include <QtEndian>

#include <QIODevice>
#include <QDebug>

static const char s_nulls[4] = { 0, 0, 0, 0 };

template CTelegramStream &CTelegramStream::operator>>(TLVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<quint64> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<QString> &v);

template CTelegramStream &CTelegramStream::operator<<(const TLVector<qint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<quint32> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<qint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<quint64> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<QString> &v);

// Generated vector read templates instancing
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChatParticipant> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPhotoSize> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDcOption> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDisabledFeature> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDocumentAttribute> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLInputUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLStickerPack> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDocument> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUser> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactBlocked> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactFound> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLImportedContact> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactSuggested> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChat> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLContactsLink> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLPhoto> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLChatLocated> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLGeoChatMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLDialog> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLMessage> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLUpdate> &v);
template CTelegramStream &CTelegramStream::operator>>(TLVector<TLEncryptedMessage> &v);
// End of generated vector read templates instancing

// Generated vector write templates instancing
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputPrivacyRule> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputUser> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputContact> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputAppEvent> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLInputPhoto> &v);
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLDocumentAttribute> &v);
// End of generated vector write templates instancing
template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLDcOption> &v);

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

    if (result.tlType == TLValue::Vector) {
        quint32 length = 0;
        *this >> length;
        for (quint32 i = 0; i < length; ++i) {
            T value;
            *this >> value;
            result.append(value);
        }
    }

    v = result;
    return *this;
}

// Generated read operators implementation
CTelegramStream &CTelegramStream::operator>>(TLAccountDaysTTL &accountDaysTTL)
{
    TLAccountDaysTTL result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountDaysTTL:
        *this >> result.days;
        break;
    default:
        break;
    }

    accountDaysTTL = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountSentChangePhoneCode &accountSentChangePhoneCode)
{
    TLAccountSentChangePhoneCode result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountSentChangePhoneCode:
        *this >> result.phoneCodeHash;
        *this >> result.sendCallTimeout;
        break;
    default:
        break;
    }

    accountSentChangePhoneCode = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAudio &audio)
{
    TLAudio result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AudioEmpty:
        *this >> result.id;
        break;
    case TLValue::Audio:
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
    case TLValue::AuthCheckedPhone:
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
    case TLValue::AuthExportedAuthorization:
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
    case TLValue::AuthSentCode:
        *this >> result.phoneRegistered;
        *this >> result.phoneCodeHash;
        *this >> result.sendCallTimeout;
        *this >> result.isPassword;
        break;
    case TLValue::AuthSentAppCode:
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
    case TLValue::ChatLocated:
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
    case TLValue::ChatParticipant:
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
    case TLValue::ChatParticipantsForbidden:
        *this >> result.chatId;
        break;
    case TLValue::ChatParticipants:
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
    case TLValue::Contact:
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
    case TLValue::ContactBlocked:
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
    case TLValue::ContactFound:
        *this >> result.userId;
        break;
    default:
        break;
    }

    contactFound = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactSuggested &contactSuggested)
{
    TLContactSuggested result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactSuggested:
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
    case TLValue::ContactsForeignLinkUnknown:
        break;
    case TLValue::ContactsForeignLinkRequested:
        *this >> result.hasPhone;
        break;
    case TLValue::ContactsForeignLinkMutual:
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
    case TLValue::ContactsMyLinkEmpty:
        break;
    case TLValue::ContactsMyLinkRequested:
        *this >> result.contact;
        break;
    case TLValue::ContactsMyLinkContact:
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
    case TLValue::DcOption:
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

CTelegramStream &CTelegramStream::operator>>(TLDisabledFeature &disabledFeature)
{
    TLDisabledFeature result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::DisabledFeature:
        *this >> result.feature;
        *this >> result.description;
        break;
    default:
        break;
    }

    disabledFeature = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDocumentAttribute &documentAttribute)
{
    TLDocumentAttribute result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::DocumentAttributeImageSize:
        *this >> result.w;
        *this >> result.h;
        break;
    case TLValue::DocumentAttributeAnimated:
        break;
    case TLValue::DocumentAttributeSticker:
        break;
    case TLValue::DocumentAttributeVideo:
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        break;
    case TLValue::DocumentAttributeAudio:
        *this >> result.duration;
        break;
    case TLValue::DocumentAttributeFilename:
        *this >> result.fileName;
        break;
    default:
        break;
    }

    documentAttribute = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLEncryptedChat &encryptedChat)
{
    TLEncryptedChat result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::EncryptedChatEmpty:
        *this >> result.id;
        break;
    case TLValue::EncryptedChatWaiting:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        break;
    case TLValue::EncryptedChatRequested:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        *this >> result.gA;
        break;
    case TLValue::EncryptedChat:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.adminId;
        *this >> result.participantId;
        *this >> result.gAOrB;
        *this >> result.keyFingerprint;
        break;
    case TLValue::EncryptedChatDiscarded:
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
    case TLValue::EncryptedFileEmpty:
        break;
    case TLValue::EncryptedFile:
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
    case TLValue::EncryptedMessage:
        *this >> result.randomId;
        *this >> result.chatId;
        *this >> result.date;
        *this >> result.bytes;
        *this >> result.file;
        break;
    case TLValue::EncryptedMessageService:
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
    case TLValue::Error:
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
    case TLValue::FileLocationUnavailable:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case TLValue::FileLocation:
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
    case TLValue::GeoPointEmpty:
        break;
    case TLValue::GeoPoint:
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
    case TLValue::HelpAppUpdate:
        *this >> result.id;
        *this >> result.critical;
        *this >> result.url;
        *this >> result.text;
        break;
    case TLValue::HelpNoAppUpdate:
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
    case TLValue::HelpInviteText:
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
    case TLValue::ImportedContact:
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
    case TLValue::InputAppEvent:
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
    case TLValue::InputAudioEmpty:
        break;
    case TLValue::InputAudio:
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
    case TLValue::InputPhoneContact:
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
    case TLValue::InputDocumentEmpty:
        break;
    case TLValue::InputDocument:
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
    case TLValue::InputEncryptedChat:
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
    case TLValue::InputEncryptedFileEmpty:
        break;
    case TLValue::InputEncryptedFileUploaded:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.md5Checksum;
        *this >> result.keyFingerprint;
        break;
    case TLValue::InputEncryptedFile:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case TLValue::InputEncryptedFileBigUploaded:
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
    case TLValue::InputFile:
        *this >> result.id;
        *this >> result.parts;
        *this >> result.name;
        *this >> result.md5Checksum;
        break;
    case TLValue::InputFileBig:
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
    case TLValue::InputFileLocation:
        *this >> result.volumeId;
        *this >> result.localId;
        *this >> result.secret;
        break;
    case TLValue::InputVideoFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case TLValue::InputEncryptedFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case TLValue::InputAudioFileLocation:
        *this >> result.id;
        *this >> result.accessHash;
        break;
    case TLValue::InputDocumentFileLocation:
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
    case TLValue::InputGeoChat:
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
    case TLValue::InputGeoPointEmpty:
        break;
    case TLValue::InputGeoPoint:
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
    case TLValue::InputPeerEmpty:
        break;
    case TLValue::InputPeerSelf:
        break;
    case TLValue::InputPeerContact:
        *this >> result.userId;
        break;
    case TLValue::InputPeerForeign:
        *this >> result.userId;
        *this >> result.accessHash;
        break;
    case TLValue::InputPeerChat:
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
    case TLValue::InputPeerNotifyEventsEmpty:
        break;
    case TLValue::InputPeerNotifyEventsAll:
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
    case TLValue::InputPeerNotifySettings:
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
    case TLValue::InputPhotoEmpty:
        break;
    case TLValue::InputPhoto:
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
    case TLValue::InputPhotoCropAuto:
        break;
    case TLValue::InputPhotoCrop:
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

CTelegramStream &CTelegramStream::operator>>(TLInputPrivacyKey &inputPrivacyKey)
{
    TLInputPrivacyKey result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }

    inputPrivacyKey = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputUser &inputUser)
{
    TLInputUser result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputUserEmpty:
        break;
    case TLValue::InputUserSelf:
        break;
    case TLValue::InputUserContact:
        *this >> result.userId;
        break;
    case TLValue::InputUserForeign:
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
    case TLValue::InputVideoEmpty:
        break;
    case TLValue::InputVideo:
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
    case TLValue::MessagesAffectedHistory:
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
    case TLValue::MessagesDhConfigNotModified:
        *this >> result.random;
        break;
    case TLValue::MessagesDhConfig:
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
    case TLValue::InputMessagesFilterEmpty:
        break;
    case TLValue::InputMessagesFilterPhotos:
        break;
    case TLValue::InputMessagesFilterVideo:
        break;
    case TLValue::InputMessagesFilterPhotoVideo:
        break;
    case TLValue::InputMessagesFilterPhotoVideoDocuments:
        break;
    case TLValue::InputMessagesFilterDocument:
        break;
    case TLValue::InputMessagesFilterAudio:
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
    case TLValue::MessagesSentEncryptedMessage:
        *this >> result.date;
        break;
    case TLValue::MessagesSentEncryptedFile:
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
    case TLValue::NearestDc:
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
    case TLValue::PeerUser:
        *this >> result.userId;
        break;
    case TLValue::PeerChat:
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
    case TLValue::PeerNotifyEventsEmpty:
        break;
    case TLValue::PeerNotifyEventsAll:
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
    case TLValue::PeerNotifySettingsEmpty:
        break;
    case TLValue::PeerNotifySettings:
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
    case TLValue::PhotoSizeEmpty:
        *this >> result.type;
        break;
    case TLValue::PhotoSize:
        *this >> result.type;
        *this >> result.location;
        *this >> result.w;
        *this >> result.h;
        *this >> result.size;
        break;
    case TLValue::PhotoCachedSize:
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

CTelegramStream &CTelegramStream::operator>>(TLPrivacyKey &privacyKey)
{
    TLPrivacyKey result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }

    privacyKey = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLPrivacyRule &privacyRule)
{
    TLPrivacyRule result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::PrivacyValueAllowContacts:
        break;
    case TLValue::PrivacyValueAllowAll:
        break;
    case TLValue::PrivacyValueAllowUsers:
        *this >> result.users;
        break;
    case TLValue::PrivacyValueDisallowContacts:
        break;
    case TLValue::PrivacyValueDisallowAll:
        break;
    case TLValue::PrivacyValueDisallowUsers:
        *this >> result.users;
        break;
    default:
        break;
    }

    privacyRule = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLSendMessageAction &sendMessageAction)
{
    TLSendMessageAction result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::SendMessageTypingAction:
        break;
    case TLValue::SendMessageCancelAction:
        break;
    case TLValue::SendMessageRecordVideoAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
        break;
    case TLValue::SendMessageRecordAudioAction:
        break;
    case TLValue::SendMessageUploadAudioAction:
        break;
    case TLValue::SendMessageUploadPhotoAction:
        break;
    case TLValue::SendMessageUploadDocumentAction:
        break;
    case TLValue::SendMessageGeoLocationAction:
        break;
    case TLValue::SendMessageChooseContactAction:
        break;
    default:
        break;
    }

    sendMessageAction = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStickerPack &stickerPack)
{
    TLStickerPack result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::StickerPack:
        *this >> result.emoticon;
        *this >> result.documents;
        break;
    default:
        break;
    }

    stickerPack = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLStorageFileType &storageFileType)
{
    TLStorageFileType result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::StorageFileUnknown:
        break;
    case TLValue::StorageFileJpeg:
        break;
    case TLValue::StorageFileGif:
        break;
    case TLValue::StorageFilePng:
        break;
    case TLValue::StorageFilePdf:
        break;
    case TLValue::StorageFileMp3:
        break;
    case TLValue::StorageFileMov:
        break;
    case TLValue::StorageFilePartial:
        break;
    case TLValue::StorageFileMp4:
        break;
    case TLValue::StorageFileWebp:
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
    case TLValue::UpdatesState:
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
    case TLValue::UploadFile:
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
    case TLValue::UserProfilePhotoEmpty:
        break;
    case TLValue::UserProfilePhoto:
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
    case TLValue::UserStatusEmpty:
        break;
    case TLValue::UserStatusOnline:
        *this >> result.expires;
        break;
    case TLValue::UserStatusOffline:
        *this >> result.wasOnline;
        break;
    case TLValue::UserStatusRecently:
        break;
    case TLValue::UserStatusLastWeek:
        break;
    case TLValue::UserStatusLastMonth:
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
    case TLValue::VideoEmpty:
        *this >> result.id;
        break;
    case TLValue::Video:
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
    case TLValue::WallPaper:
        *this >> result.id;
        *this >> result.title;
        *this >> result.sizes;
        *this >> result.color;
        break;
    case TLValue::WallPaperSolid:
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
    case TLValue::ChatPhotoEmpty:
        break;
    case TLValue::ChatPhoto:
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
    case TLValue::Config:
        *this >> result.date;
        *this >> result.expires;
        *this >> result.testMode;
        *this >> result.thisDc;
        *this >> result.dcOptions;
        *this >> result.chatBigSize;
        *this >> result.chatSizeMax;
        *this >> result.broadcastSizeMax;
        *this >> result.disabledFeatures;
        break;
    default:
        break;
    }

    config = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLContactStatus &contactStatus)
{
    TLContactStatus result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::ContactStatus:
        *this >> result.userId;
        *this >> result.status;
        break;
    default:
        break;
    }

    contactStatus = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLDialog &dialog)
{
    TLDialog result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::Dialog:
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
    case TLValue::DocumentEmpty:
        *this >> result.id;
        break;
    case TLValue::Document:
        *this >> result.id;
        *this >> result.accessHash;
        *this >> result.date;
        *this >> result.mimeType;
        *this >> result.size;
        *this >> result.thumb;
        *this >> result.dcId;
        *this >> result.attributes;
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
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        *this >> result.file;
        *this >> result.crop;
        break;
    case TLValue::InputChatPhoto:
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
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        *this >> result.file;
        break;
    case TLValue::InputMediaPhoto:
        *this >> result.id;
        break;
    case TLValue::InputMediaGeoPoint:
        *this >> result.geoPoint;
        break;
    case TLValue::InputMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        break;
    case TLValue::InputMediaUploadedVideo:
        *this >> result.file;
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        *this >> result.mimeType;
        break;
    case TLValue::InputMediaUploadedThumbVideo:
        *this >> result.file;
        *this >> result.thumb;
        *this >> result.duration;
        *this >> result.w;
        *this >> result.h;
        *this >> result.mimeType;
        break;
    case TLValue::InputMediaVideo:
        *this >> result.id;
        break;
    case TLValue::InputMediaUploadedAudio:
        *this >> result.file;
        *this >> result.duration;
        *this >> result.mimeType;
        break;
    case TLValue::InputMediaAudio:
        *this >> result.id;
        break;
    case TLValue::InputMediaUploadedDocument:
        *this >> result.file;
        *this >> result.mimeType;
        *this >> result.attributes;
        break;
    case TLValue::InputMediaUploadedThumbDocument:
        *this >> result.file;
        *this >> result.thumb;
        *this >> result.mimeType;
        *this >> result.attributes;
        break;
    case TLValue::InputMediaDocument:
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
    case TLValue::InputNotifyPeer:
        *this >> result.peer;
        break;
    case TLValue::InputNotifyUsers:
        break;
    case TLValue::InputNotifyChats:
        break;
    case TLValue::InputNotifyAll:
        break;
    case TLValue::InputNotifyGeoChatPeer:
        *this >> result.peer;
        break;
    default:
        break;
    }

    inputNotifyPeer = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLInputPrivacyRule &inputPrivacyRule)
{
    TLInputPrivacyRule result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
        break;
    case TLValue::InputPrivacyValueAllowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
        *this >> result.users;
        break;
    case TLValue::InputPrivacyValueDisallowContacts:
        break;
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueDisallowUsers:
        *this >> result.users;
        break;
    default:
        break;
    }

    inputPrivacyRule = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesAllStickers &messagesAllStickers)
{
    TLMessagesAllStickers result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesAllStickersNotModified:
        break;
    case TLValue::MessagesAllStickers:
        *this >> result.hash;
        *this >> result.packs;
        *this >> result.documents;
        break;
    default:
        break;
    }

    messagesAllStickers = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesStickers &messagesStickers)
{
    TLMessagesStickers result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesStickersNotModified:
        break;
    case TLValue::MessagesStickers:
        *this >> result.hash;
        *this >> result.stickers;
        break;
    default:
        break;
    }

    messagesStickers = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLNotifyPeer &notifyPeer)
{
    TLNotifyPeer result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::NotifyPeer:
        *this >> result.peer;
        break;
    case TLValue::NotifyUsers:
        break;
    case TLValue::NotifyChats:
        break;
    case TLValue::NotifyAll:
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
    case TLValue::PhotoEmpty:
        *this >> result.id;
        break;
    case TLValue::Photo:
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
    case TLValue::UserEmpty:
        *this >> result.id;
        break;
    case TLValue::UserSelf:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        *this >> result.inactive;
        break;
    case TLValue::UserContact:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        *this >> result.accessHash;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        break;
    case TLValue::UserRequest:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        *this >> result.accessHash;
        *this >> result.phone;
        *this >> result.photo;
        *this >> result.status;
        break;
    case TLValue::UserForeign:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        *this >> result.accessHash;
        *this >> result.photo;
        *this >> result.status;
        break;
    case TLValue::UserDeleted:
        *this >> result.id;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        break;
    default:
        break;
    }

    user = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAccountPrivacyRules &accountPrivacyRules)
{
    TLAccountPrivacyRules result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AccountPrivacyRules:
        *this >> result.rules;
        *this >> result.users;
        break;
    default:
        break;
    }

    accountPrivacyRules = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLAuthAuthorization &authAuthorization)
{
    TLAuthAuthorization result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::AuthAuthorization:
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
    case TLValue::ChatEmpty:
        *this >> result.id;
        break;
    case TLValue::Chat:
        *this >> result.id;
        *this >> result.title;
        *this >> result.photo;
        *this >> result.participantsCount;
        *this >> result.date;
        *this >> result.left;
        *this >> result.version;
        break;
    case TLValue::ChatForbidden:
        *this >> result.id;
        *this >> result.title;
        *this >> result.date;
        break;
    case TLValue::GeoChat:
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
    case TLValue::ChatFull:
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
    case TLValue::ContactsBlocked:
        *this >> result.blocked;
        *this >> result.users;
        break;
    case TLValue::ContactsBlockedSlice:
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
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        *this >> result.contacts;
        *this >> result.users;
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
    case TLValue::ContactsFound:
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
    case TLValue::ContactsImportedContacts:
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
    case TLValue::ContactsLink:
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
    case TLValue::ContactsSuggested:
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
    case TLValue::HelpSupport:
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
    case TLValue::MessageActionEmpty:
        break;
    case TLValue::MessageActionChatCreate:
        *this >> result.title;
        *this >> result.users;
        break;
    case TLValue::MessageActionChatEditTitle:
        *this >> result.title;
        break;
    case TLValue::MessageActionChatEditPhoto:
        *this >> result.photo;
        break;
    case TLValue::MessageActionChatDeletePhoto:
        break;
    case TLValue::MessageActionChatAddUser:
        *this >> result.userId;
        break;
    case TLValue::MessageActionChatDeleteUser:
        *this >> result.userId;
        break;
    case TLValue::MessageActionGeoChatCreate:
        *this >> result.title;
        *this >> result.address;
        break;
    case TLValue::MessageActionGeoChatCheckin:
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
    case TLValue::MessageMediaEmpty:
        break;
    case TLValue::MessageMediaPhoto:
        *this >> result.photo;
        break;
    case TLValue::MessageMediaVideo:
        *this >> result.video;
        break;
    case TLValue::MessageMediaGeo:
        *this >> result.geo;
        break;
    case TLValue::MessageMediaContact:
        *this >> result.phoneNumber;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.userId;
        break;
    case TLValue::MessageMediaUnsupported:
        *this >> result.bytes;
        break;
    case TLValue::MessageMediaDocument:
        *this >> result.document;
        break;
    case TLValue::MessageMediaAudio:
        *this >> result.audio;
        break;
    default:
        break;
    }

    messageMedia = result;

    return *this;
}

CTelegramStream &CTelegramStream::operator>>(TLMessagesChatFull &messagesChatFull)
{
    TLMessagesChatFull result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesChatFull:
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
    case TLValue::MessagesChats:
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
    case TLValue::MessagesSentMessage:
        *this >> result.id;
        *this >> result.date;
        *this >> result.pts;
        *this >> result.seq;
        break;
    case TLValue::MessagesSentMessageLink:
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
    case TLValue::PhotosPhoto:
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
    case TLValue::PhotosPhotos:
        *this >> result.photos;
        *this >> result.users;
        break;
    case TLValue::PhotosPhotosSlice:
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
    case TLValue::UserFull:
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
    case TLValue::GeoChatMessageEmpty:
        *this >> result.chatId;
        *this >> result.id;
        break;
    case TLValue::GeoChatMessage:
        *this >> result.chatId;
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.date;
        *this >> result.message;
        *this >> result.media;
        break;
    case TLValue::GeoChatMessageService:
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
    case TLValue::GeochatsLocated:
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
    case TLValue::GeochatsMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::GeochatsMessagesSlice:
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
    case TLValue::GeochatsStatedMessage:
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
    case TLValue::MessageEmpty:
        *this >> result.id;
        break;
    case TLValue::Message:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.toId;
        *this >> result.date;
        *this >> result.message;
        *this >> result.media;
        break;
    case TLValue::MessageForwarded:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.fwdFromId;
        *this >> result.fwdDate;
        *this >> result.fromId;
        *this >> result.toId;
        *this >> result.date;
        *this >> result.message;
        *this >> result.media;
        break;
    case TLValue::MessageService:
        *this >> result.flags;
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.toId;
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
    case TLValue::MessagesDialogs:
        *this >> result.dialogs;
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::MessagesDialogsSlice:
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

CTelegramStream &CTelegramStream::operator>>(TLMessagesMessages &messagesMessages)
{
    TLMessagesMessages result;

    *this >> result.tlType;

    switch (result.tlType) {
    case TLValue::MessagesMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        break;
    case TLValue::MessagesMessagesSlice:
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
    case TLValue::MessagesStatedMessage:
        *this >> result.message;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.pts;
        *this >> result.seq;
        break;
    case TLValue::MessagesStatedMessageLink:
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
    case TLValue::MessagesStatedMessages:
        *this >> result.messages;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.pts;
        *this >> result.seq;
        break;
    case TLValue::MessagesStatedMessagesLinks:
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
    case TLValue::UpdateNewMessage:
        *this >> result.message;
        *this >> result.pts;
        break;
    case TLValue::UpdateMessageID:
        *this >> result.id;
        *this >> result.randomId;
        break;
    case TLValue::UpdateReadMessages:
        *this >> result.messages;
        *this >> result.pts;
        break;
    case TLValue::UpdateDeleteMessages:
        *this >> result.messages;
        *this >> result.pts;
        break;
    case TLValue::UpdateUserTyping:
        *this >> result.userId;
        *this >> result.action;
        break;
    case TLValue::UpdateChatUserTyping:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.action;
        break;
    case TLValue::UpdateChatParticipants:
        *this >> result.participants;
        break;
    case TLValue::UpdateUserStatus:
        *this >> result.userId;
        *this >> result.status;
        break;
    case TLValue::UpdateUserName:
        *this >> result.userId;
        *this >> result.firstName;
        *this >> result.lastName;
        *this >> result.username;
        break;
    case TLValue::UpdateUserPhoto:
        *this >> result.userId;
        *this >> result.date;
        *this >> result.photo;
        *this >> result.previous;
        break;
    case TLValue::UpdateContactRegistered:
        *this >> result.userId;
        *this >> result.date;
        break;
    case TLValue::UpdateContactLink:
        *this >> result.userId;
        *this >> result.myLink;
        *this >> result.foreignLink;
        break;
    case TLValue::UpdateNewAuthorization:
        *this >> result.authKeyId;
        *this >> result.date;
        *this >> result.device;
        *this >> result.location;
        break;
    case TLValue::UpdateNewGeoChatMessage:
        *this >> result.message;
        break;
    case TLValue::UpdateNewEncryptedMessage:
        *this >> result.message;
        *this >> result.qts;
        break;
    case TLValue::UpdateEncryptedChatTyping:
        *this >> result.chatId;
        break;
    case TLValue::UpdateEncryption:
        *this >> result.chat;
        *this >> result.date;
        break;
    case TLValue::UpdateEncryptedMessagesRead:
        *this >> result.chatId;
        *this >> result.maxDate;
        *this >> result.date;
        break;
    case TLValue::UpdateChatParticipantAdd:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.inviterId;
        *this >> result.version;
        break;
    case TLValue::UpdateChatParticipantDelete:
        *this >> result.chatId;
        *this >> result.userId;
        *this >> result.version;
        break;
    case TLValue::UpdateDcOptions:
        *this >> result.dcOptions;
        break;
    case TLValue::UpdateUserBlocked:
        *this >> result.userId;
        *this >> result.blocked;
        break;
    case TLValue::UpdateNotifySettings:
        *this >> result.peer;
        *this >> result.notifySettings;
        break;
    case TLValue::UpdateServiceNotification:
        *this >> result.type;
        *this >> result.message;
        *this >> result.media;
        *this >> result.popup;
        break;
    case TLValue::UpdatePrivacy:
        *this >> result.key;
        *this >> result.rules;
        break;
    case TLValue::UpdateUserPhone:
        *this >> result.userId;
        *this >> result.phone;
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
    case TLValue::UpdatesTooLong:
        break;
    case TLValue::UpdateShortMessage:
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.message;
        *this >> result.pts;
        *this >> result.date;
        *this >> result.seq;
        break;
    case TLValue::UpdateShortChatMessage:
        *this >> result.id;
        *this >> result.fromId;
        *this >> result.chatId;
        *this >> result.message;
        *this >> result.pts;
        *this >> result.date;
        *this >> result.seq;
        break;
    case TLValue::UpdateShort:
        *this >> result.update;
        *this >> result.date;
        break;
    case TLValue::UpdatesCombined:
        *this >> result.updates;
        *this >> result.users;
        *this >> result.chats;
        *this >> result.date;
        *this >> result.seqStart;
        *this >> result.seq;
        break;
    case TLValue::Updates:
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
    case TLValue::UpdatesDifferenceEmpty:
        *this >> result.date;
        *this >> result.seq;
        break;
    case TLValue::UpdatesDifference:
        *this >> result.newMessages;
        *this >> result.newEncryptedMessages;
        *this >> result.otherUpdates;
        *this >> result.chats;
        *this >> result.users;
        *this >> result.state;
        break;
    case TLValue::UpdatesDifferenceSlice:
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

    if (v.tlType == TLValue::Vector) {
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
CTelegramStream &CTelegramStream::operator<<(const TLAccountDaysTTL &accountDaysTTL)
{
    *this << accountDaysTTL.tlType;

    switch (accountDaysTTL.tlType) {
    case TLValue::AccountDaysTTL:
        *this << accountDaysTTL.days;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLDocumentAttribute &documentAttribute)
{
    *this << documentAttribute.tlType;

    switch (documentAttribute.tlType) {
    case TLValue::DocumentAttributeImageSize:
        *this << documentAttribute.w;
        *this << documentAttribute.h;
        break;
    case TLValue::DocumentAttributeAnimated:
        break;
    case TLValue::DocumentAttributeSticker:
        break;
    case TLValue::DocumentAttributeVideo:
        *this << documentAttribute.duration;
        *this << documentAttribute.w;
        *this << documentAttribute.h;
        break;
    case TLValue::DocumentAttributeAudio:
        *this << documentAttribute.duration;
        break;
    case TLValue::DocumentAttributeFilename:
        *this << documentAttribute.fileName;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputAppEvent &inputAppEvent)
{
    *this << inputAppEvent.tlType;

    switch (inputAppEvent.tlType) {
    case TLValue::InputAppEvent:
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

CTelegramStream &CTelegramStream::operator<<(const TLInputAudio &inputAudio)
{
    *this << inputAudio.tlType;

    switch (inputAudio.tlType) {
    case TLValue::InputAudioEmpty:
        break;
    case TLValue::InputAudio:
        *this << inputAudio.id;
        *this << inputAudio.accessHash;
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
    case TLValue::InputPhoneContact:
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

CTelegramStream &CTelegramStream::operator<<(const TLInputDocument &inputDocument)
{
    *this << inputDocument.tlType;

    switch (inputDocument.tlType) {
    case TLValue::InputDocumentEmpty:
        break;
    case TLValue::InputDocument:
        *this << inputDocument.id;
        *this << inputDocument.accessHash;
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
    case TLValue::InputEncryptedChat:
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
    case TLValue::InputEncryptedFileEmpty:
        break;
    case TLValue::InputEncryptedFileUploaded:
        *this << inputEncryptedFile.id;
        *this << inputEncryptedFile.parts;
        *this << inputEncryptedFile.md5Checksum;
        *this << inputEncryptedFile.keyFingerprint;
        break;
    case TLValue::InputEncryptedFile:
        *this << inputEncryptedFile.id;
        *this << inputEncryptedFile.accessHash;
        break;
    case TLValue::InputEncryptedFileBigUploaded:
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
    case TLValue::InputFile:
        *this << inputFile.id;
        *this << inputFile.parts;
        *this << inputFile.name;
        *this << inputFile.md5Checksum;
        break;
    case TLValue::InputFileBig:
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
    case TLValue::InputFileLocation:
        *this << inputFileLocation.volumeId;
        *this << inputFileLocation.localId;
        *this << inputFileLocation.secret;
        break;
    case TLValue::InputVideoFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    case TLValue::InputEncryptedFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    case TLValue::InputAudioFileLocation:
        *this << inputFileLocation.id;
        *this << inputFileLocation.accessHash;
        break;
    case TLValue::InputDocumentFileLocation:
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
    case TLValue::InputGeoChat:
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
    case TLValue::InputGeoPointEmpty:
        break;
    case TLValue::InputGeoPoint:
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
    case TLValue::InputPeerEmpty:
        break;
    case TLValue::InputPeerSelf:
        break;
    case TLValue::InputPeerContact:
        *this << inputPeer.userId;
        break;
    case TLValue::InputPeerForeign:
        *this << inputPeer.userId;
        *this << inputPeer.accessHash;
        break;
    case TLValue::InputPeerChat:
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
    case TLValue::InputPeerNotifySettings:
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
    case TLValue::InputPhotoEmpty:
        break;
    case TLValue::InputPhoto:
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
    case TLValue::InputPhotoCropAuto:
        break;
    case TLValue::InputPhotoCrop:
        *this << inputPhotoCrop.cropLeft;
        *this << inputPhotoCrop.cropTop;
        *this << inputPhotoCrop.cropWidth;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPrivacyKey &inputPrivacyKey)
{
    *this << inputPrivacyKey.tlType;

    switch (inputPrivacyKey.tlType) {
    case TLValue::InputPrivacyKeyStatusTimestamp:
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
    case TLValue::InputUserEmpty:
        break;
    case TLValue::InputUserSelf:
        break;
    case TLValue::InputUserContact:
        *this << inputUser.userId;
        break;
    case TLValue::InputUserForeign:
        *this << inputUser.userId;
        *this << inputUser.accessHash;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputVideo &inputVideo)
{
    *this << inputVideo.tlType;

    switch (inputVideo.tlType) {
    case TLValue::InputVideoEmpty:
        break;
    case TLValue::InputVideo:
        *this << inputVideo.id;
        *this << inputVideo.accessHash;
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
    case TLValue::InputMessagesFilterEmpty:
        break;
    case TLValue::InputMessagesFilterPhotos:
        break;
    case TLValue::InputMessagesFilterVideo:
        break;
    case TLValue::InputMessagesFilterPhotoVideo:
        break;
    case TLValue::InputMessagesFilterPhotoVideoDocuments:
        break;
    case TLValue::InputMessagesFilterDocument:
        break;
    case TLValue::InputMessagesFilterAudio:
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLSendMessageAction &sendMessageAction)
{
    *this << sendMessageAction.tlType;

    switch (sendMessageAction.tlType) {
    case TLValue::SendMessageTypingAction:
        break;
    case TLValue::SendMessageCancelAction:
        break;
    case TLValue::SendMessageRecordVideoAction:
        break;
    case TLValue::SendMessageUploadVideoAction:
        break;
    case TLValue::SendMessageRecordAudioAction:
        break;
    case TLValue::SendMessageUploadAudioAction:
        break;
    case TLValue::SendMessageUploadPhotoAction:
        break;
    case TLValue::SendMessageUploadDocumentAction:
        break;
    case TLValue::SendMessageGeoLocationAction:
        break;
    case TLValue::SendMessageChooseContactAction:
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
    case TLValue::InputChatPhotoEmpty:
        break;
    case TLValue::InputChatUploadedPhoto:
        *this << inputChatPhoto.file;
        *this << inputChatPhoto.crop;
        break;
    case TLValue::InputChatPhoto:
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
    case TLValue::InputMediaEmpty:
        break;
    case TLValue::InputMediaUploadedPhoto:
        *this << inputMedia.file;
        break;
    case TLValue::InputMediaPhoto:
        *this << inputMedia.id;
        break;
    case TLValue::InputMediaGeoPoint:
        *this << inputMedia.geoPoint;
        break;
    case TLValue::InputMediaContact:
        *this << inputMedia.phoneNumber;
        *this << inputMedia.firstName;
        *this << inputMedia.lastName;
        break;
    case TLValue::InputMediaUploadedVideo:
        *this << inputMedia.file;
        *this << inputMedia.duration;
        *this << inputMedia.w;
        *this << inputMedia.h;
        *this << inputMedia.mimeType;
        break;
    case TLValue::InputMediaUploadedThumbVideo:
        *this << inputMedia.file;
        *this << inputMedia.thumb;
        *this << inputMedia.duration;
        *this << inputMedia.w;
        *this << inputMedia.h;
        *this << inputMedia.mimeType;
        break;
    case TLValue::InputMediaVideo:
        *this << inputMedia.id;
        break;
    case TLValue::InputMediaUploadedAudio:
        *this << inputMedia.file;
        *this << inputMedia.duration;
        *this << inputMedia.mimeType;
        break;
    case TLValue::InputMediaAudio:
        *this << inputMedia.id;
        break;
    case TLValue::InputMediaUploadedDocument:
        *this << inputMedia.file;
        *this << inputMedia.mimeType;
        *this << inputMedia.attributes;
        break;
    case TLValue::InputMediaUploadedThumbDocument:
        *this << inputMedia.file;
        *this << inputMedia.thumb;
        *this << inputMedia.mimeType;
        *this << inputMedia.attributes;
        break;
    case TLValue::InputMediaDocument:
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
    case TLValue::InputNotifyPeer:
        *this << inputNotifyPeer.peer;
        break;
    case TLValue::InputNotifyUsers:
        break;
    case TLValue::InputNotifyChats:
        break;
    case TLValue::InputNotifyAll:
        break;
    case TLValue::InputNotifyGeoChatPeer:
        *this << inputNotifyPeer.peer;
        break;
    default:
        break;
    }

    return *this;
}

CTelegramStream &CTelegramStream::operator<<(const TLInputPrivacyRule &inputPrivacyRule)
{
    *this << inputPrivacyRule.tlType;

    switch (inputPrivacyRule.tlType) {
    case TLValue::InputPrivacyValueAllowContacts:
        break;
    case TLValue::InputPrivacyValueAllowAll:
        break;
    case TLValue::InputPrivacyValueAllowUsers:
        *this << inputPrivacyRule.users;
        break;
    case TLValue::InputPrivacyValueDisallowContacts:
        break;
    case TLValue::InputPrivacyValueDisallowAll:
        break;
    case TLValue::InputPrivacyValueDisallowUsers:
        *this << inputPrivacyRule.users;
        break;
    default:
        break;
    }

    return *this;
}

// End of generated write operators implementation
