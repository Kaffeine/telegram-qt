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

#ifndef CTELEGRAMSTREAM_HPP
#define CTELEGRAMSTREAM_HPP

#include <QVector>
#include <QString>

#include "CRawStream.hpp"
#include "TLTypes.hpp"

class CTelegramStream : public CRawStream
{
public:
    explicit CTelegramStream(QByteArray *data, bool write);
    explicit CTelegramStream(const QByteArray &data);

    explicit CTelegramStream(QIODevice *d = 0);

    using CRawStream::operator <<;
    using CRawStream::operator >>;

    CTelegramStream &operator>>(QByteArray &data);
    CTelegramStream &operator>>(QString &str);

    CTelegramStream &operator>>(bool &data);

    template <typename T>
    CTelegramStream &operator>>(TLVector<T> &v);

    // Generated read operators
    CTelegramStream &operator>>(TLAudio &audio);
    CTelegramStream &operator>>(TLAuthCheckedPhone &authCheckedPhone);
    CTelegramStream &operator>>(TLAuthExportedAuthorization &authExportedAuthorization);
    CTelegramStream &operator>>(TLAuthSentCode &authSentCode);
    CTelegramStream &operator>>(TLChatLocated &chatLocated);
    CTelegramStream &operator>>(TLChatParticipant &chatParticipant);
    CTelegramStream &operator>>(TLChatParticipants &chatParticipants);
    CTelegramStream &operator>>(TLContact &contact);
    CTelegramStream &operator>>(TLContactBlocked &contactBlocked);
    CTelegramStream &operator>>(TLContactFound &contactFound);
    CTelegramStream &operator>>(TLContactStatus &contactStatus);
    CTelegramStream &operator>>(TLContactSuggested &contactSuggested);
    CTelegramStream &operator>>(TLContactsForeignLink &contactsForeignLink);
    CTelegramStream &operator>>(TLContactsMyLink &contactsMyLink);
    CTelegramStream &operator>>(TLDcOption &dcOption);
    CTelegramStream &operator>>(TLEncryptedChat &encryptedChat);
    CTelegramStream &operator>>(TLEncryptedFile &encryptedFile);
    CTelegramStream &operator>>(TLEncryptedMessage &encryptedMessage);
    CTelegramStream &operator>>(TLError &error);
    CTelegramStream &operator>>(TLFileLocation &fileLocation);
    CTelegramStream &operator>>(TLGeoPoint &geoPoint);
    CTelegramStream &operator>>(TLGlobalPrivacySettings &globalPrivacySettings);
    CTelegramStream &operator>>(TLHelpAppUpdate &helpAppUpdate);
    CTelegramStream &operator>>(TLHelpInviteText &helpInviteText);
    CTelegramStream &operator>>(TLImportedContact &importedContact);
    CTelegramStream &operator>>(TLInputAppEvent &inputAppEvent);
    CTelegramStream &operator>>(TLInputAudio &inputAudio);
    CTelegramStream &operator>>(TLInputContact &inputContact);
    CTelegramStream &operator>>(TLInputDocument &inputDocument);
    CTelegramStream &operator>>(TLInputEncryptedChat &inputEncryptedChat);
    CTelegramStream &operator>>(TLInputEncryptedFile &inputEncryptedFile);
    CTelegramStream &operator>>(TLInputFile &inputFile);
    CTelegramStream &operator>>(TLInputFileLocation &inputFileLocation);
    CTelegramStream &operator>>(TLInputGeoChat &inputGeoChat);
    CTelegramStream &operator>>(TLInputGeoPoint &inputGeoPoint);
    CTelegramStream &operator>>(TLInputPeer &inputPeer);
    CTelegramStream &operator>>(TLInputPeerNotifyEvents &inputPeerNotifyEvents);
    CTelegramStream &operator>>(TLInputPeerNotifySettings &inputPeerNotifySettings);
    CTelegramStream &operator>>(TLInputPhoto &inputPhoto);
    CTelegramStream &operator>>(TLInputPhotoCrop &inputPhotoCrop);
    CTelegramStream &operator>>(TLInputUser &inputUser);
    CTelegramStream &operator>>(TLInputVideo &inputVideo);
    CTelegramStream &operator>>(TLMessagesAffectedHistory &messagesAffectedHistory);
    CTelegramStream &operator>>(TLMessagesDhConfig &messagesDhConfig);
    CTelegramStream &operator>>(TLMessagesFilter &messagesFilter);
    CTelegramStream &operator>>(TLMessagesSentEncryptedMessage &messagesSentEncryptedMessage);
    CTelegramStream &operator>>(TLNearestDc &nearestDc);
    CTelegramStream &operator>>(TLPeer &peer);
    CTelegramStream &operator>>(TLPeerNotifyEvents &peerNotifyEvents);
    CTelegramStream &operator>>(TLPeerNotifySettings &peerNotifySettings);
    CTelegramStream &operator>>(TLPhotoSize &photoSize);
    CTelegramStream &operator>>(TLSendMessageAction &sendMessageAction);
    CTelegramStream &operator>>(TLStorageFileType &storageFileType);
    CTelegramStream &operator>>(TLUpdatesState &updatesState);
    CTelegramStream &operator>>(TLUploadFile &uploadFile);
    CTelegramStream &operator>>(TLUserProfilePhoto &userProfilePhoto);
    CTelegramStream &operator>>(TLUserStatus &userStatus);
    CTelegramStream &operator>>(TLVideo &video);
    CTelegramStream &operator>>(TLWallPaper &wallPaper);
    CTelegramStream &operator>>(TLChatPhoto &chatPhoto);
    CTelegramStream &operator>>(TLConfig &config);
    CTelegramStream &operator>>(TLDialog &dialog);
    CTelegramStream &operator>>(TLDocument &document);
    CTelegramStream &operator>>(TLInputChatPhoto &inputChatPhoto);
    CTelegramStream &operator>>(TLInputMedia &inputMedia);
    CTelegramStream &operator>>(TLInputNotifyPeer &inputNotifyPeer);
    CTelegramStream &operator>>(TLNotifyPeer &notifyPeer);
    CTelegramStream &operator>>(TLPhoto &photo);
    CTelegramStream &operator>>(TLUser &user);
    CTelegramStream &operator>>(TLAuthAuthorization &authAuthorization);
    CTelegramStream &operator>>(TLChat &chat);
    CTelegramStream &operator>>(TLChatFull &chatFull);
    CTelegramStream &operator>>(TLContactsBlocked &contactsBlocked);
    CTelegramStream &operator>>(TLContactsContacts &contactsContacts);
    CTelegramStream &operator>>(TLContactsFound &contactsFound);
    CTelegramStream &operator>>(TLContactsImportedContacts &contactsImportedContacts);
    CTelegramStream &operator>>(TLContactsLink &contactsLink);
    CTelegramStream &operator>>(TLContactsSuggested &contactsSuggested);
    CTelegramStream &operator>>(TLHelpSupport &helpSupport);
    CTelegramStream &operator>>(TLMessageAction &messageAction);
    CTelegramStream &operator>>(TLMessageMedia &messageMedia);
    CTelegramStream &operator>>(TLMessagesChat &messagesChat);
    CTelegramStream &operator>>(TLMessagesChatFull &messagesChatFull);
    CTelegramStream &operator>>(TLMessagesChats &messagesChats);
    CTelegramStream &operator>>(TLMessagesSentMessage &messagesSentMessage);
    CTelegramStream &operator>>(TLPhotosPhoto &photosPhoto);
    CTelegramStream &operator>>(TLPhotosPhotos &photosPhotos);
    CTelegramStream &operator>>(TLUserFull &userFull);
    CTelegramStream &operator>>(TLGeoChatMessage &geoChatMessage);
    CTelegramStream &operator>>(TLGeochatsLocated &geochatsLocated);
    CTelegramStream &operator>>(TLGeochatsMessages &geochatsMessages);
    CTelegramStream &operator>>(TLGeochatsStatedMessage &geochatsStatedMessage);
    CTelegramStream &operator>>(TLMessage &message);
    CTelegramStream &operator>>(TLMessagesDialogs &messagesDialogs);
    CTelegramStream &operator>>(TLMessagesMessage &messagesMessage);
    CTelegramStream &operator>>(TLMessagesMessages &messagesMessages);
    CTelegramStream &operator>>(TLMessagesStatedMessage &messagesStatedMessage);
    CTelegramStream &operator>>(TLMessagesStatedMessages &messagesStatedMessages);
    CTelegramStream &operator>>(TLUpdate &update);
    CTelegramStream &operator>>(TLUpdates &updates);
    CTelegramStream &operator>>(TLUpdatesDifference &updatesDifference);
    // End of generated read operators

    CTelegramStream &operator<<(const QByteArray &data);
    CTelegramStream &operator<<(const QString &str);

    CTelegramStream &operator<<(const bool &data);

    CTelegramStream &operator<<(const TLDcOption &dcOption);

    // Generated write operators
    CTelegramStream &operator<<(const TLInputAppEvent &inputAppEvent);
    CTelegramStream &operator<<(const TLInputContact &inputContact);
    CTelegramStream &operator<<(const TLInputEncryptedChat &inputEncryptedChat);
    CTelegramStream &operator<<(const TLInputEncryptedFile &inputEncryptedFile);
    CTelegramStream &operator<<(const TLInputFile &inputFile);
    CTelegramStream &operator<<(const TLInputFileLocation &inputFileLocation);
    CTelegramStream &operator<<(const TLInputGeoChat &inputGeoChat);
    CTelegramStream &operator<<(const TLInputGeoPoint &inputGeoPoint);
    CTelegramStream &operator<<(const TLInputPeer &inputPeer);
    CTelegramStream &operator<<(const TLInputPeerNotifySettings &inputPeerNotifySettings);
    CTelegramStream &operator<<(const TLInputPhoto &inputPhoto);
    CTelegramStream &operator<<(const TLInputPhotoCrop &inputPhotoCrop);
    CTelegramStream &operator<<(const TLInputUser &inputUser);
    CTelegramStream &operator<<(const TLMessagesFilter &messagesFilter);
    CTelegramStream &operator<<(const TLSendMessageAction &sendMessageAction);
    CTelegramStream &operator<<(const TLInputChatPhoto &inputChatPhoto);
    CTelegramStream &operator<<(const TLInputMedia &inputMedia);
    CTelegramStream &operator<<(const TLInputNotifyPeer &inputNotifyPeer);
    // End of generated write operators

    template <typename T>
    CTelegramStream &operator<<(const TLVector<T> &v);

};

inline CTelegramStream &CTelegramStream::operator>>(QString &str)
{
    QByteArray data;
    *this >> data;
    str = QString::fromUtf8(data);
    return *this;
}

inline CTelegramStream &CTelegramStream::operator>>(bool &data)
{
    TLValue val;
    *this >> val;

    if (val == BoolTrue) {
        data = true;
    } else if (val == BoolFalse) {
        data = false;
    }

    return *this;
}

inline CTelegramStream &CTelegramStream::operator<<(const QString &str)
{
    return *this << str.toUtf8();
}

inline CTelegramStream &CTelegramStream::operator<<(const bool &data)
{
    if (data) {
        *this << BoolTrue;
    } else {
        *this << BoolFalse;
    }

    return *this;
}

#endif // CTELEGRAMSTREAM_HPP
