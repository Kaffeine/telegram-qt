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

#ifndef CTELEGRAMCONNECTION_HPP
#define CTELEGRAMCONNECTION_HPP

#include <QObject>
#include <QByteArray>
#include <QVector>
#include <QMap>
#include <QStringList>

#include "TLTypes.hpp"
#include "crypto-rsa.hpp"
#include "crypto-aes.hpp"

class CAppInformation;
class CTelegramStream;
class CTelegramTransport;

class CTelegramConnection : public QObject
{
    Q_OBJECT
public:
    enum AuthState {
        AuthStateNone,
        AuthStatePqRequested,
        AuthStateDhRequested,
        AuthStateDhGenerationResultRequested,
        AuthStateSuccess,
        AuthStateSignedIn
    };

    enum DeltaTimeHeuristicState {
        DeltaTimeIsOk,
        DeltaTimeCorrectionForward,
        DeltaTimeCorrectionBackward,
    };

    explicit CTelegramConnection(const CAppInformation *appInfo, QObject *parent = 0);

    void setDcInfo(const TLDcOption &newDcInfo);

    inline TLDcOption dcInfo() const { return m_dcInfo; }

    void connectToDc();

    bool isConnected() const;

    static quint64 formatTimeStamp(qint64 timeInMs);
    static inline quint64 formatClientTimeStamp(qint64 timeInMs) { return formatTimeStamp(timeInMs) & ~quint64(3); }

    static quint64 timeStampToMSecsSinceEpoch(quint64 ts);

    void initAuth();
    void getConfiguration();

    // Generated Telegram API methods declaration
    void messagesAcceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint);
    void messagesAddChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit);
    void messagesCreateChat(const TLVector<TLInputUser> &users, const QString &title);
    void messagesDeleteChatUser(quint32 chatId, const TLInputUser &userId);
    void messagesDeleteHistory(const TLInputPeer &peer, quint32 offset);
    void messagesDeleteMessages(const TLVector<quint32> &id);
    void messagesDiscardEncryption(quint32 chatId);
    void messagesEditChatPhoto(quint32 chatId, const TLInputChatPhoto &photo);
    void messagesEditChatTitle(quint32 chatId, const QString &title);
    void messagesForwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId);
    void messagesForwardMessages(const TLInputPeer &peer, const TLVector<quint32> &id);
    void messagesGetChats(const TLVector<quint32> &id);
    void messagesGetDhConfig(quint32 version, quint32 randomLength);
    void messagesGetDialogs(quint32 offset, quint32 maxId, quint32 limit);
    void messagesGetFullChat(quint32 chatId);
    void messagesGetHistory(const TLInputPeer &peer, quint32 offset, quint32 maxId, quint32 limit);
    void messagesGetMessages(const TLVector<quint32> &id);
    void messagesReadEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate);
    void messagesReadHistory(const TLInputPeer &peer, quint32 maxId, quint32 offset);
    void messagesReceivedMessages(quint32 maxId);
    void messagesReceivedQueue(quint32 maxQts);
    void messagesRequestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA);
    void messagesRestoreMessages(const TLVector<quint32> &id);
    void messagesSearch(const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit);
    void messagesSendBroadcast(const TLVector<TLInputUser> &contacts, const QString &message, const TLInputMedia &media);
    void messagesSendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    void messagesSendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file);
    void messagesSendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    void messagesSendMedia(const TLInputPeer &peer, const TLInputMedia &media, quint64 randomId);
    void messagesSendMessage(const TLInputPeer &peer, const QString &message, quint64 randomId);
    void messagesSetEncryptedTyping(const TLInputEncryptedChat &peer, bool typing);
    void messagesSetTyping(const TLInputPeer &peer, bool typing);
    // End of generated Telegram API methods declaration

    void requestPhoneStatus(const QString &phoneNumber);
    void requestPhoneCode(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void requestContacts();

    void updatesGetState();
    void updatesGetDifference(quint32 pts, quint32 date, quint32 qts);

    void getFile(const TLInputFileLocation &location, quint32 fileId);

    void usersGetUsers(const TLVector<TLInputUser> &users);
    void usersGetFullUser(const TLInputUser &user);

    void contactsDeleteContacts(const TLVector<TLInputUser> &users);
    void addContacts(const QStringList &phoneNumbers, bool replace);

    void accountUpdateStatus(bool offline);

    AuthState authState() { return m_authState; }

    void requestPqAuthorization();
    bool answerPqAuthorization(const QByteArray &payload);
    void requestDhParameters();
    bool answerDh(const QByteArray &payload);
    void requestDhGenerationResult();
    bool processServersDHAnswer(const QByteArray &payload);

    inline TLNumber128 clientNonce() const { return m_clientNonce; }
    inline TLNumber128 serverNonce() const { return m_serverNonce; }

    inline quint64 pq() const { return m_pq; }
    inline quint64 p() const { return m_p; }
    inline quint64 q() const { return m_q; }

    inline quint64 serverPublicFingersprint() const { return m_serverPublicFingersprint; }

    inline QByteArray authKey() const { return m_authKey; }
    void setAuthKey(const QByteArray &newAuthKey);
    inline quint64 authId() const { return m_authId; }

    inline quint64 serverSalt() const { return m_serverSalt; }
    void setServerSalt(const quint64 salt) { m_serverSalt = salt; }
    inline quint64 sessionId() const { return m_sessionId; }

    inline QVector<TLDcOption> dcConfiguration() const { return m_dcConfiguration; }

    inline qint32 deltaTime() const { return m_deltaTime; }
    void setDeltaTime(const qint32 delta) { m_deltaTime = delta; }

    void processRedirectedPackage(const QByteArray &data);

signals:
    void wantedActiveDcChanged(int dc);
    void newRedirectedPackage(const QByteArray &data, int dc);

    void selfPhoneReceived(const QString &phoneNumber);
    void authStateChanged(int dc, int state);
    void actualDcIdReceived(int dc, int newDcId);
    void dcConfigurationReceived(int dc);
    void phoneStatusReceived(const QString &phone, bool registered, bool invited);
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void usersReceived(const QVector<TLUser> &users);
    void contactListReceived(const QStringList &contactList);
    void contactListChanged(const QStringList &added, const QStringList &removed);
    void fileReceived(const TLUploadFile &file, quint32 fileId);

    void fullUserReceived(const TLUserFull &userFull);

    void updatesReceived(const TLUpdates &update);
    void updatesStateReceived(const TLUpdatesState &updatesState);
    void updatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

    void messageSentInfoReceived(const TLInputPeer &peer, quint64 randomId, quint32 messageId, quint32 pts, quint32 date, quint32 seq);

private slots:
    void whenConnected();
    void whenReadyRead();

protected:
    void processRpcQuery(const QByteArray &data);

    void processSessionCreated(CTelegramStream &stream);
    void processContainer(CTelegramStream &stream);
    void processRpcResult(CTelegramStream &stream, quint64 idHint = 0);
    void processGzipPackedRpcQuery(CTelegramStream &stream);
    void processGzipPackedRpcResult(CTelegramStream &stream, quint64 id);
    bool processRpcError(CTelegramStream &stream, quint64 id, TLValue request);

    void processMessageAck(CTelegramStream &stream);
    void processIgnoredMessageNotification(CTelegramStream &stream);

    TLValue processHelpGetConfig(CTelegramStream &stream, quint64 id);
    TLValue processContactsGetContacts(CTelegramStream &stream, quint64 id);
    TLValue processContactsImportContacts(CTelegramStream &stream, quint64 id);
    TLValue processContactsDeleteContacts(CTelegramStream &stream, quint64 id);
    TLValue processUpdatesGetState(CTelegramStream &stream, quint64 id);
    TLValue processUpdatesGetDifference(CTelegramStream &stream, quint64 id);
    TLValue processAuthCheckPhone(CTelegramStream &stream, quint64 id);
    TLValue processAuthSendCode(CTelegramStream &stream, quint64 id);
    TLValue processAuthSign(CTelegramStream &stream, quint64 id);
    TLValue processUploadGetFile(CTelegramStream &stream, quint64 id);
    TLValue processUsersGetUsers(CTelegramStream &stream, quint64 id);
    TLValue processUsersGetFullUser(CTelegramStream &stream, quint64 id);
    TLValue processMessagesSendMessage(CTelegramStream &stream, quint64 id);
    TLValue processMessagesSetTyping(CTelegramStream &stream, quint64 id);
    TLValue processMessagesReadHistory(CTelegramStream &stream, quint64 id);
    TLValue processMessagesReceivedMessages(CTelegramStream &stream, quint64 id);
    TLValue processAccountUpdateStatus(CTelegramStream &stream, quint64 id);

    bool processErrorSeeOther(const QString errorMessage, quint64 id);

    TLValue processUpdate(CTelegramStream &stream, bool *ok);

    SAesKey generateTmpAesKey() const;
    SAesKey generateClientToServerAesKey(const QByteArray &messageKey) const;
    SAesKey generateServerToClientAesKey(const QByteArray &messageKey) const;

    SAesKey generateAesKey(const QByteArray &messageKey, int xValue) const;

    void insertInitConnection(QByteArray *data) const;

    quint64 sendPlainPackage(const QByteArray &buffer);
    quint64 sendEncryptedPackage(const QByteArray &buffer);
    void setTransport(CTelegramTransport *newTransport);

    void setAuthState(AuthState newState);

    quint64 newMessageId();

    const CAppInformation *m_appInfo;

    QMap<quint64, QByteArray> m_submittedPackages; // <message id, package data>
    QMap<quint64, quint32> m_requestedFilesIds; // <message id, file id>

    CTelegramTransport *m_transport;

    AuthState m_authState;

    QByteArray m_authKey;
    quint64 m_authId;
    quint64 m_authKeyAuxHash;
    quint64 m_serverSalt;
    quint64 m_receivedServerSalt;
    quint64 m_sessionId;
    quint64 m_lastMessageId;
    quint32 m_sequenceNumber;
    quint32 m_contentRelatedMessages;

    qint32 m_deltaTime;
    DeltaTimeHeuristicState m_deltaTimeHeuristicState;

    TLNumber128 m_clientNonce;
    TLNumber128 m_serverNonce;
    TLNumber256 m_newNonce;

    quint64 m_pq;
    quint32 m_p;
    quint32 m_q;

    quint64 m_serverPublicFingersprint;
    SRsaKey m_rsaKey;
    SAesKey m_tmpAesKey;

    quint32 m_g;
    QByteArray m_dhPrime;
    QByteArray m_gA;
    QByteArray m_b;

    quint64 m_authRetryId;

    TLDcOption m_dcInfo;

    QVector<TLDcOption> m_dcConfiguration;

    QString m_authCodeHash;

};

inline SAesKey CTelegramConnection::generateClientToServerAesKey(const QByteArray &messageKey) const
{
    return generateAesKey(messageKey, 0);
}

inline SAesKey CTelegramConnection::generateServerToClientAesKey(const QByteArray &messageKey) const
{
    return generateAesKey(messageKey, 8);
}

#endif // CTELEGRAMCONNECTION_HPP
