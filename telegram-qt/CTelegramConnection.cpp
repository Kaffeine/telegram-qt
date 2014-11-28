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

#include "CTelegramConnection.hpp"

#include <QDebug>

#include <QDateTime>
#include <QStringList>

#include <QtEndian>

#include "CAppInformation.hpp"
#include "CTelegramStream.hpp"
#include "CTcpTransport.hpp"
#include "Utils.hpp"

CTelegramConnection::CTelegramConnection(const CAppInformation *appInfo, QObject *parent) :
    QObject(parent),
    m_appInfo(appInfo),
    m_transport(0),
    m_authState(AuthStateNone),
    m_authId(0),
    m_authKeyAuxHash(0),
    m_serverSalt(0),
    m_sessionId(0),
    m_lastMessageId(0),
    m_sequenceNumber(0),
    m_contentRelatedMessages(0),
    m_deltaTime(0),
    m_deltaTimeHeuristicState(DeltaTimeIsOk),
    m_serverPublicFingersprint(0)
{
    setTransport(new CTcpTransport(this));
}

void CTelegramConnection::setDcInfo(const TLDcOption &newDcInfo)
{
    m_dcInfo = newDcInfo;
}

void CTelegramConnection::connectToDc()
{
    m_transport->connectToHost(m_dcInfo.ipAddress, m_dcInfo.port);
}

bool CTelegramConnection::isConnected() const
{
    return m_transport->isConnected();
}

void CTelegramConnection::setTransport(CTelegramTransport *newTransport)
{
    m_transport = newTransport;

    connect(m_transport, SIGNAL(connected()), SLOT(whenConnected()));
    connect(m_transport, SIGNAL(readyRead()), SLOT(whenReadyRead()));
}

void CTelegramConnection::setAuthKey(const QByteArray &newAuthKey)
{
    m_authKey = newAuthKey;
    m_authId = Utils::getFingersprint(m_authKey);
    m_authKeyAuxHash = Utils::getFingersprint(m_authKey, /* lower-order */ false);
}

quint64 CTelegramConnection::formatTimeStamp(qint64 timeInMs)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;

    const quint64 secs = timeInMs / 1000;
    const quint64 msecs = maxMsecValue / 1000 * (timeInMs % 1000);

    return (secs << 32) + msecs;
}

quint64 CTelegramConnection::timeStampToMSecsSinceEpoch(quint64 ts)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;

    const quint64 secs = ts >> 32;
    quint64 msecs = ts & maxMsecValue;

    msecs = msecs * 10000 / maxMsecValue;

    if (msecs % 10 >= 5) {
        msecs += 5;
    }
    msecs /= 10;

    return secs * 1000 + msecs;
}

void CTelegramConnection::initAuth()
{
    if (m_authState == AuthStateNone) {
        m_authRetryId = 0;
        m_rsaKey = Utils::loadRsaKey();
        Utils::randomBytes(m_clientNonce.data, m_clientNonce.size());

        requestPqAuthorization();
    }
}

void CTelegramConnection::requestPqAuthorization()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << ReqPq;
    outputStream << m_clientNonce;

    sendPlainPackage(output);

    setAuthState(AuthStatePqRequested);
}

void CTelegramConnection::getConfiguration()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << HelpGetConfig;

    sendEncryptedPackage(output);
}

void CTelegramConnection::requestPhoneStatus(const QString &phoneNumber)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << AuthCheckPhone;
    outputStream << phoneNumber;

    sendEncryptedPackage(output);
}

void CTelegramConnection::requestPhoneCode(const QString &phoneNumber)
{
    qDebug() << "requestPhoneCode" << phoneNumber << m_dcInfo.id;
    QByteArray output;

    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << AuthSendCode;
    outputStream << phoneNumber;
    outputStream << quint32(0);
    outputStream << m_appInfo->appId();
    outputStream << m_appInfo->appHash();
    outputStream << m_appInfo->languageCode();

    sendEncryptedPackage(output);
}

void CTelegramConnection::signIn(const QString &phoneNumber, const QString &authCode)
{
    qDebug() << "SignIn" << phoneNumber;
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << AuthSignIn;
    outputStream << phoneNumber;
    outputStream << m_authCodeHash;
    outputStream << authCode;

    sendEncryptedPackage(output);
}

void CTelegramConnection::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    qDebug() << "SignUp" << phoneNumber;
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << AuthSignUp;
    outputStream << phoneNumber;
    outputStream << m_authCodeHash;
    outputStream << authCode;
    outputStream << firstName;
    outputStream << lastName;

    sendEncryptedPackage(output);
}

void CTelegramConnection::contactsGetContacts()
{
    qDebug() << "GetContacts";

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << ContactsGetContacts;
    outputStream << QString(); // Hash

    sendEncryptedPackage(output);
}

void CTelegramConnection::updatesGetState()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << UpdatesGetState;

    sendEncryptedPackage(output);
}

void CTelegramConnection::updatesGetDifference(quint32 pts, quint32 date, quint32 qts)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << UpdatesGetDifference;
    outputStream << pts;
    outputStream << date;
    outputStream << qts;

    sendEncryptedPackage(output);
}

void CTelegramConnection::getFile(const TLInputFileLocation &location, quint32 fileId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << UploadGetFile;
    outputStream << location;
    outputStream << quint32(0); // Offset
    outputStream << quint32(512 * 1024); // Limit

    const quint64 messageId = sendEncryptedPackage(output);

    m_requestedFilesIds.insert(messageId, fileId);
}

void CTelegramConnection::usersGetUsers(const TLVector<TLInputUser> &users)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << UsersGetUsers;
    outputStream << users;

    sendEncryptedPackage(output);
}

void CTelegramConnection::usersGetFullUser(const TLInputUser &user)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << UsersGetFullUser;
    outputStream << user;

    sendEncryptedPackage(output);
}

void CTelegramConnection::contactsDeleteContacts(const TLVector<TLInputUser> &users)
{
    qDebug() << Q_FUNC_INFO << users.count();

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << ContactsDeleteContacts;
    outputStream << users;

    sendEncryptedPackage(output);
}

void CTelegramConnection::addContacts(const QStringList &phoneNumbers, bool replace)
{
    qDebug() << "addContacts" << phoneNumbers;

    TLVector<TLInputContact> contactsVector;
    for (int i = 0; i < phoneNumbers.count(); ++i) {
        TLInputContact contact;
        contact.clientId = i;
        contact.phone = phoneNumbers.at(i);
        contactsVector.append(contact);
    }

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << ContactsImportContacts;
    outputStream << contactsVector; // Hash
    outputStream << replace;

    sendEncryptedPackage(output);
}

void CTelegramConnection::accountUpdateStatus(bool offline)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << AccountUpdateStatus;
    outputStream << offline;

    sendEncryptedPackage(output);
}

// Generated Telegram API methods implementation
quint64 CTelegramConnection::messagesAcceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesAcceptEncryption;
    outputStream << peer;
    outputStream << gB;
    outputStream << keyFingerprint;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesAddChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesAddChatUser;
    outputStream << chatId;
    outputStream << userId;
    outputStream << fwdLimit;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesCreateChat(const TLVector<TLInputUser> &users, const QString &title)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesCreateChat;
    outputStream << users;
    outputStream << title;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDeleteChatUser(quint32 chatId, const TLInputUser &userId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesDeleteChatUser;
    outputStream << chatId;
    outputStream << userId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDeleteHistory(const TLInputPeer &peer, quint32 offset)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesDeleteHistory;
    outputStream << peer;
    outputStream << offset;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDeleteMessages(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesDeleteMessages;
    outputStream << id;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesDiscardEncryption(quint32 chatId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesDiscardEncryption;
    outputStream << chatId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesEditChatPhoto(quint32 chatId, const TLInputChatPhoto &photo)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesEditChatPhoto;
    outputStream << chatId;
    outputStream << photo;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesEditChatTitle(quint32 chatId, const QString &title)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesEditChatTitle;
    outputStream << chatId;
    outputStream << title;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesForwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesForwardMessage;
    outputStream << peer;
    outputStream << id;
    outputStream << randomId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesForwardMessages(const TLInputPeer &peer, const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesForwardMessages;
    outputStream << peer;
    outputStream << id;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetChats(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesGetChats;
    outputStream << id;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetDhConfig(quint32 version, quint32 randomLength)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesGetDhConfig;
    outputStream << version;
    outputStream << randomLength;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetDialogs(quint32 offset, quint32 maxId, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesGetDialogs;
    outputStream << offset;
    outputStream << maxId;
    outputStream << limit;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetFullChat(quint32 chatId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesGetFullChat;
    outputStream << chatId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetHistory(const TLInputPeer &peer, quint32 offset, quint32 maxId, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesGetHistory;
    outputStream << peer;
    outputStream << offset;
    outputStream << maxId;
    outputStream << limit;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesGetMessages(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesGetMessages;
    outputStream << id;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReadEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesReadEncryptedHistory;
    outputStream << peer;
    outputStream << maxDate;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReadHistory(const TLInputPeer &peer, quint32 maxId, quint32 offset)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesReadHistory;
    outputStream << peer;
    outputStream << maxId;
    outputStream << offset;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReceivedMessages(quint32 maxId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesReceivedMessages;
    outputStream << maxId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesReceivedQueue(quint32 maxQts)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesReceivedQueue;
    outputStream << maxQts;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesRequestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesRequestEncryption;
    outputStream << userId;
    outputStream << randomId;
    outputStream << gA;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesRestoreMessages(const TLVector<quint32> &id)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesRestoreMessages;
    outputStream << id;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSearch(const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSearch;
    outputStream << peer;
    outputStream << q;
    outputStream << filter;
    outputStream << minDate;
    outputStream << maxDate;
    outputStream << offset;
    outputStream << maxId;
    outputStream << limit;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendBroadcast(const TLVector<TLInputUser> &contacts, const QString &message, const TLInputMedia &media)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSendBroadcast;
    outputStream << contacts;
    outputStream << message;
    outputStream << media;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSendEncrypted;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSendEncryptedFile;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    outputStream << file;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSendEncryptedService;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendMedia(const TLInputPeer &peer, const TLInputMedia &media, quint64 randomId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSendMedia;
    outputStream << peer;
    outputStream << media;
    outputStream << randomId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSendMessage(const TLInputPeer &peer, const QString &message, quint64 randomId)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSendMessage;
    outputStream << peer;
    outputStream << message;
    outputStream << randomId;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSetEncryptedTyping(const TLInputEncryptedChat &peer, bool typing)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSetEncryptedTyping;
    outputStream << peer;
    outputStream << typing;

    return sendEncryptedPackage(output);
}

quint64 CTelegramConnection::messagesSetTyping(const TLInputPeer &peer, bool typing)
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << MessagesSetTyping;
    outputStream << peer;
    outputStream << typing;

    return sendEncryptedPackage(output);
}

// End of generated Telegram API methods implementation

bool CTelegramConnection::answerPqAuthorization(const QByteArray &payload)
{
    // Payload is passed as const, but we open device in read-only mode, so
    // Let's workaround const by construction variable copy with COW-feature.
    CTelegramStream inputStream(payload);

    TLValue responsePqValue;
    inputStream >> responsePqValue;

    if (responsePqValue != ResPQ) {
        qDebug() << "Error: Unexpected operation code";
        return false;
    }

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    m_serverNonce = serverNonce;

    QByteArray pq;

    inputStream >> pq;

    if (pq.size() != 8) {
        qDebug() << "Error: PQ should be 8 bytes in length";
        return false;
    }

    m_pq = qFromBigEndian<quint64>((uchar *) pq.data());

    quint64 div1 = Utils::findDivider(m_pq);

    if (div1 == 1) {
        qDebug() << "Error: Can not solve PQ.";
        return false;
    }
    quint64 div2 = m_pq / div1;

    if (div1 < div2) {
        m_p = div1;
        m_q = div2;
    } else {
        m_p = div2;
        m_q = div1;
    }

    TLVector<quint64> fingersprints;

    inputStream >> fingersprints;

    if (fingersprints.count() != 1) {
        qDebug() << "Error: Unexpected Server RSA Fingersprints vector.";
        return false;
    }

    m_serverPublicFingersprint = fingersprints.at(0);

    if (m_rsaKey.fingersprint != m_serverPublicFingersprint) {
        qDebug() << "Error: Server RSA Fingersprint does not match to loaded key";
        return false;
    }

    return true;
}

void CTelegramConnection::requestDhParameters()
{
    Utils::randomBytes(m_newNonce.data, m_newNonce.size());

    QByteArray bigEndianNumber;
    bigEndianNumber.fill(char(0), 8);

    QByteArray encryptedPackage;
    {
        static const int requestedEncryptedPackageLength = 255;
        QByteArray innerData;
        CTelegramStream encryptedStream(&innerData, /* write */ true);

        encryptedStream << PQInnerData;

        qToBigEndian(m_pq, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        bigEndianNumber.fill(char(0), 4);
        qToBigEndian(m_p, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        qToBigEndian(m_q, (uchar *) bigEndianNumber.data());
        encryptedStream << bigEndianNumber;

        encryptedStream << m_clientNonce;
        encryptedStream << m_serverNonce;
        encryptedStream << m_newNonce;

        QByteArray sha = Utils::sha1(innerData);
        QByteArray randomPadding;
        randomPadding.resize(requestedEncryptedPackageLength - (sha.length() + innerData.length()));
        Utils::randomBytes(&randomPadding);

        encryptedPackage = Utils::rsa(sha + innerData + randomPadding, m_rsaKey);
    }

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << ReqDHParams;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;

    bigEndianNumber.fill(char(0), 4);
    qToBigEndian(m_p, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    qToBigEndian(m_q, (uchar *) bigEndianNumber.data());
    outputStream << bigEndianNumber;

    outputStream << m_serverPublicFingersprint;

    outputStream << encryptedPackage;

    sendPlainPackage(output);

    setAuthState(AuthStateDhRequested);
}

bool CTelegramConnection::answerDh(const QByteArray &payload)
{
    CTelegramStream inputStream(payload);

    TLValue responseTLValue;
    inputStream >> responseTLValue;

    if (responseTLValue != ServerDHParamsOk) {
        qDebug() << "Error: Server did not accept our DH params";
        return false;
    }

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    QByteArray encryptedAnswer;

    inputStream >> encryptedAnswer;

    m_tmpAesKey = generateTmpAesKey();

    QByteArray answer = Utils::aesDecrypt(encryptedAnswer, m_tmpAesKey);

    QByteArray sha1OfAnswer = answer.mid(0, 20);
    answer = answer.mid(20, 564);

    if (Utils::sha1(answer) != sha1OfAnswer) {
        qDebug() << "Error: SHA1 of encrypted answer is different from announced.";
        return false;
    }

    CTelegramStream encryptedInputStream(answer);

    encryptedInputStream >> responseTLValue;

    if (responseTLValue != ServerDHInnerData) {
        qDebug() << "Error: Unexpected TL Value in encrypted answer";
        return false;
    }

    encryptedInputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    encryptedInputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    encryptedInputStream >> m_g;
    encryptedInputStream >> m_dhPrime;
    encryptedInputStream >> m_gA;

    quint32 serverTime;

    encryptedInputStream >> serverTime;

    m_deltaTime = qint64(serverTime) - (QDateTime::currentMSecsSinceEpoch() / 1000);
    m_deltaTimeHeuristicState = DeltaTimeIsOk;

    m_b.resize(256);
    Utils::randomBytes(&m_b);

    return true;
}

void CTelegramConnection::requestDhGenerationResult()
{
    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << SetClientDHParams;
    outputStream << m_clientNonce;
    outputStream << m_serverNonce;

    QByteArray encryptedPackage;
    {
        QByteArray innerData;
        CTelegramStream encryptedStream(&innerData, /* write */ true);

        encryptedStream << ClientDHInnerData;

        encryptedStream << m_clientNonce;
        encryptedStream << m_serverNonce;
        encryptedStream << m_authRetryId;

        QByteArray binNumber;
        binNumber.resize(sizeof(m_g));
        qToBigEndian(m_g, (uchar *) binNumber.data());

        binNumber = Utils::binaryNumberModExp(binNumber, m_dhPrime, m_b);

        encryptedStream << binNumber;

        QByteArray sha = Utils::sha1(innerData);
        QByteArray randomPadding;

        int packageLength = sha.length() + innerData.length();
        if ((packageLength) % 16) {
            randomPadding.resize(16 - (packageLength % 16));
            Utils::randomBytes(&randomPadding);

            packageLength += randomPadding.size();
        }

        encryptedPackage = Utils::aesEncrypt(sha + innerData + randomPadding, m_tmpAesKey);

        encryptedPackage.truncate(packageLength);
    }

    outputStream << encryptedPackage;

    sendPlainPackage(output);
    setAuthState(AuthStateDhGenerationResultRequested);
}

bool CTelegramConnection::processServersDHAnswer(const QByteArray &payload)
{
    CTelegramStream inputStream(payload);

    TLValue responseTLValue;
    inputStream >> responseTLValue;

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;

    inputStream >> clientNonce;

    if (clientNonce != m_clientNonce) {
        qDebug() << "Error: Client nonce in incoming package is different from our own.";
        return false;
    }

    inputStream >> serverNonce;

    if (serverNonce != m_serverNonce) {
        qDebug() << "Error: Server nonce in incoming package is different from known early.";
        return false;
    }

    TLNumber128 newNonceHashLower128;

    inputStream >> newNonceHashLower128;

    QByteArray readedHashPart(newNonceHashLower128.data, newNonceHashLower128.size());

    QByteArray expectedHashData(m_newNonce.data, m_newNonce.size());

    QByteArray newAuthKey = Utils::binaryNumberModExp(m_gA, m_dhPrime, m_b);

    expectedHashData.append(Utils::sha1(newAuthKey).left(8));

    if (responseTLValue == DhGenOk) {
//        qDebug() << "Answer OK";

        expectedHashData.insert(32, char(1));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }

        setAuthKey(newAuthKey);
        m_serverSalt = m_serverNonce.parts[0] ^ m_newNonce.parts[0];

        setAuthState(AuthStateSuccess);
        return true;
    } else if (responseTLValue == DhGenRetry) {
        qDebug() << "Answer RETRY";

        expectedHashData.insert(32, char(2));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }
    } else if (responseTLValue == DhGenFail) {
        qDebug() << "Answer FAIL";

        expectedHashData.insert(32, char(3));
        if (Utils::sha1(expectedHashData).mid(4) != readedHashPart) {
            qDebug() << "Error: Server (newNonce + auth key) hash is not correct.";
            return false;
        }
    }

    qDebug() << "Error: Unexpected server response.";

    return false;
}

void CTelegramConnection::processRedirectedPackage(const QByteArray &data)
{
    sendEncryptedPackage(data);
}

void CTelegramConnection::processRpcQuery(const QByteArray &data)
{
    CTelegramStream stream(data);

    bool isUpdate;
    TLValue val = processUpdate(stream, &isUpdate); // Doubtfully that this approach will work in next time.

    if (isUpdate) {
        return;
    }

    switch (val) {
    case NewSessionCreated:
        processSessionCreated(stream);
        break;
    case MsgContainer:
        processContainer(stream);
        break;
    case RpcResult:
        processRpcResult(stream);
        break;
    case MsgsAck:
        processMessageAck(stream);
        break;
    case BadMsgNotification:
    case BadServerSalt:
        processIgnoredMessageNotification(stream);
        break;
    case GzipPacked:
        processGzipPackedRpcQuery(stream);
        break;
    default:
        qDebug() << "VAL:" << QString::number(val, 16);
        break;
    }

    if ((val != BadMsgNotification) && (m_deltaTimeHeuristicState != DeltaTimeIsOk)) {
        // If we have no bad message notification, then time is synced.
        m_deltaTimeHeuristicState = DeltaTimeIsOk;
    }
}

void CTelegramConnection::processSessionCreated(CTelegramStream &stream)
{
    // https://core.telegram.org/mtproto/service_messages#new-session-creation-notification
    quint64 n;

    stream >> n;
    stream >> n;
    stream >> n;
}

void CTelegramConnection::processContainer(CTelegramStream &stream)
{
    // https://core.telegram.org/mtproto/service_messages#simple-container
    quint32 itemsCount;

    stream >> itemsCount;

    for (quint32 i = 0; i < itemsCount; ++i) {
        quint64 id;
        stream >> id;
        //todo: ack

        quint32 seqNo;
        stream >> seqNo;

        quint32 size;

        stream >> size;

        processRpcQuery(stream.readBytes(size));
    }
}

void CTelegramConnection::processRpcResult(CTelegramStream &stream, quint64 idHint)
{
    quint64 id = idHint;

    if (!id) {
        stream >> id;
    }

    TLValue request;

    const QByteArray &requestData = m_submittedPackages.value(id);

    if (!requestData.isEmpty()) {
        CTelegramStream storedStream(requestData);
        TLValue processingResult = Null; // Not really meaningful value, just a way to fix warning.

        storedStream >> request;

        switch (request) {
        case ContactsGetContacts:
            processingResult = processContactsGetContacts(stream, id);
            break;
        case ContactsImportContacts:
            processingResult = processContactsImportContacts(stream, id);
            break;
        case ContactsDeleteContacts:
            processingResult = processContactsDeleteContacts(stream, id);
            break;
        case UpdatesGetState:
            processingResult = processUpdatesGetState(stream, id);
            break;
        case UpdatesGetDifference:
            processingResult = processUpdatesGetDifference(stream, id);
            break;
        case UploadGetFile:
            processingResult = processUploadGetFile(stream, id);
            break;
        case UsersGetUsers:
            processingResult = processUsersGetUsers(stream, id);
            break;
        case UsersGetFullUser:
            processingResult = processUsersGetFullUser(stream, id);
            break;
        case AuthSignIn:
        case AuthSignUp:
            processingResult = processAuthSign(stream, id);
            break;
        case HelpGetConfig:
            processingResult = processHelpGetConfig(stream, id);
            break;
        case AuthCheckPhone:
            processingResult = processAuthCheckPhone(stream, id);
            break;
        case AuthSendCode:
            processingResult = processAuthSendCode(stream, id);
            break;
        case MessagesCreateChat:
            processingResult = processMessagesCreateChat(stream, id);
            break;
        case MessagesSendMessage:
            processingResult = processMessagesSendMessage(stream, id);
            break;
        case MessagesSetTyping:
            processingResult = processMessagesSetTyping(stream, id);
            break;
        case MessagesReadHistory:
            processingResult = processMessagesReadHistory(stream, id);
            break;
        case MessagesReceivedMessages:
            processingResult = processMessagesReceivedMessages(stream, id);
            break;
        case AccountUpdateStatus:
            processingResult = processAccountUpdateStatus(stream, id);
            break;
        default:
            qDebug() << "Unknown outgoing RPC type:" << QString::number(request, 16);
            break;
        }

        switch (processingResult) {
        case RpcError:
            processRpcError(stream, id, request);
            break;
        case GzipPacked:
            processGzipPackedRpcResult(stream, id);
            break;
        default:
            // Any other results considered as success
            m_submittedPackages.remove(id);
            break;
        }
    } else {
        stream >> request;
        qDebug() << "Unexpected RPC message:" << QString::number(request, 16);
    }
}

void CTelegramConnection::processGzipPackedRpcQuery(CTelegramStream &stream)
{
    QByteArray packedData;
    stream >> packedData;

    const QByteArray data = Utils::unpackGZip(packedData);

    if (!data.isEmpty()) {
        processRpcQuery(data);
    }
}

void CTelegramConnection::processGzipPackedRpcResult(CTelegramStream &stream, quint64 id)
{
    QByteArray packedData;
    stream >> packedData;

    const QByteArray data = Utils::unpackGZip(packedData);

    if (!data.isEmpty()) {
        CTelegramStream unpackedStream(data);
        processRpcResult(unpackedStream, id);
    }
}

bool CTelegramConnection::processRpcError(CTelegramStream &stream, quint64 id, TLValue request)
{
    quint32 errorCode;
    stream >> errorCode;

    QString errorMessage;
    stream >> errorMessage;

    qDebug() << "RPC Error" << errorCode << ":" << errorMessage << "for message" << id;

    switch (errorCode) {
    case 303: // ERROR_SEE_OTHER
        if (processErrorSeeOther(errorMessage, id)) {
            return true;
        }
        break;
    case 400:
        if (request == AuthSignIn) {
            emit phoneCodeIsInvalid();
            return true;
        }
    default:
        qDebug() << "RPC Error can not be handled.";
        break;
    }

    return false;
}

void CTelegramConnection::processMessageAck(CTelegramStream &stream)
{
    TLVector<quint64> idsVector;

    stream >> idsVector;

    foreach (quint64 id, idsVector) {
        qDebug() << "Packaged" << id << "acked";
//        m_submittedPackages.remove(id);
    }
}

void CTelegramConnection::processIgnoredMessageNotification(CTelegramStream &stream)
{
    // https://core.telegram.org/mtproto/service_messages_about_messages#notice-of-ignored-error-message
    quint64 id;
    stream >> id;

    quint32 seqNo;
    stream >> seqNo;

    quint32 errorCode;
    stream >> errorCode;

    QString errorText;
    switch (errorCode) {
    case 16:
        errorText = QLatin1String("Id too low");
        break;
    case 17:
        errorText = QLatin1String("Id too high");
        break;
    case 18:
        errorText = QLatin1String("Incorrect two lower order id bits");
        break;
    case 19:
        errorText = QLatin1String("Container id is the same as id of a previously received message");
        break;
    case 20:
        errorText = QLatin1String("Message too old, and it cannot be verified whether the server has received a message with this id or not");
        break;
    case 32:
        errorText = QLatin1String("Sequence number too low");
        break;
    case 33:
        errorText = QLatin1String("Sequence number too high");
        break;
    case 34:
        errorText = QLatin1String("An even sequence number expected");
        break;
    case 35:
        errorText = QLatin1String("Odd sequence number expected");
        break;
    case 48:
        errorText = QLatin1String("Incorrect server salt");
        break;
    case 64:
        errorText = QLatin1String("Invalid container");
        break;
    default:
        errorText = QLatin1String("Unknown error code");
        break;
    }
    qDebug() << QString(QLatin1String("Bad message %1/%2: Code %3 (%4).")).arg(id).arg(seqNo).arg(errorCode).arg(errorText);

    if (errorCode == 16) {
        if (m_deltaTimeHeuristicState == DeltaTimeIsOk) {
            m_deltaTimeHeuristicState = DeltaTimeCorrectionForward;
        }

        if (m_deltaTimeHeuristicState == DeltaTimeCorrectionForward) {
            m_deltaTime += 1000;
        } else {
            m_deltaTime += 100;
        }

        sendEncryptedPackage(m_submittedPackages.take(id));
        qDebug() << "DeltaTime factor increased to" << m_deltaTime;
    } else if (errorCode == 17) {
        if (m_deltaTimeHeuristicState == DeltaTimeIsOk) {
            m_deltaTimeHeuristicState = DeltaTimeCorrectionBackward;
        }

        if (m_deltaTimeHeuristicState == DeltaTimeCorrectionBackward) {
            m_deltaTime -= 1000;
        } else {
            m_deltaTime -= 100;
        }

        qDebug() << "DeltaTime factor reduced to" << m_deltaTime;
        sendEncryptedPackage(m_submittedPackages.take(id));
    } else if (errorCode == 48) {
        m_serverSalt = m_receivedServerSalt;
        sendEncryptedPackage(m_submittedPackages.take(id));
        qDebug() << "Local serverSalt fixed to" << m_serverSalt;
    }
}

TLValue CTelegramConnection::processHelpGetConfig(CTelegramStream &stream, quint64 id)
{
    TLConfig result;
    stream >> result;

    if (result.tlType == Config) {
        m_dcConfiguration = result.dcOptions;

        if (m_dcInfo.id != result.thisDc) {
            emit actualDcIdReceived(m_dcInfo.id, result.thisDc);
        }

        emit dcConfigurationReceived(m_dcInfo.id);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processContactsGetContacts(CTelegramStream &stream, quint64 id)
{
    TLContactsContacts result;
    stream >> result;

    if (result.tlType == ContactsContacts) {
        emit usersReceived(result.users);

        QStringList contactList;
        foreach (const TLUser &user, result.users) {
            contactList.append(user.phone);
        }

        emit contactListReceived(contactList);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processContactsImportContacts(CTelegramStream &stream, quint64 id)
{
    TLContactsImportedContacts result;
    stream >> result;

    if (result.tlType == ContactsImportedContacts) {
        emit usersReceived(result.users);

        QStringList addedList;
        foreach (const TLUser &user, result.users) {
            addedList.append(user.phone);
        }

        emit contactListChanged(addedList, QStringList());
    }

    return result.tlType;
}

TLValue CTelegramConnection::processContactsDeleteContacts(CTelegramStream &stream, quint64 id)
{
    TLValue result;
    stream >> result;

    return result;
}

TLValue CTelegramConnection::processUpdatesGetState(CTelegramStream &stream, quint64 id)
{
    TLUpdatesState result;
    stream >> result;

    switch (result.tlType) {
    case UpdatesState:
        emit updatesStateReceived(result);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processUpdatesGetDifference(CTelegramStream &stream, quint64 id)
{
    TLUpdatesDifference result;
    stream >> result;

    switch (result.tlType) {
    case UpdatesDifference:
    case UpdatesDifferenceSlice:
    case UpdatesDifferenceEmpty:
        emit updatesDifferenceReceived(result);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthCheckPhone(CTelegramStream &stream, quint64 id)
{
    TLAuthCheckedPhone result;
    stream >> result;

    if (result.tlType == AuthCheckedPhone) {
        const QByteArray data = m_submittedPackages.take(id);

        if (data.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Can not restore message" << id;
            return result.tlType;
        }

        CTelegramStream stream(data);
        TLValue value;
        QString phone;
        stream >> value;
        stream >> phone;

        emit phoneStatusReceived(phone, result.phoneRegistered, result.phoneInvited);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthSendCode(CTelegramStream &stream, quint64 id)
{
    TLAuthSentCode result;
    stream >> result;

    if (result.tlType == AuthSentCode) {
        m_authCodeHash = result.phoneCodeHash;

        emit phoneCodeRequired();
    }

    return result.tlType;
}

TLValue CTelegramConnection::processAuthSign(CTelegramStream &stream, quint64 id)
{
    TLAuthAuthorization result;
    stream >> result;

    qDebug() << "AuthAuthorization" << result.user.phone << result.expires;

    if (result.tlType == AuthAuthorization) {
        setAuthState(AuthStateSignedIn);
        emit selfPhoneReceived(result.user.phone);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processUploadGetFile(CTelegramStream &stream, quint64 id)
{
    TLUploadFile file;
    stream >> file;

    if (file.tlType == UploadFile) {
        emit fileReceived(file, m_requestedFilesIds.value(id));
    }

    return file.tlType;
}

TLValue CTelegramConnection::processUsersGetUsers(CTelegramStream &stream, quint64 id)
{
    TLVector<TLUser> result;

    stream >> result;

    if (result.tlType == Vector) {
        emit usersReceived(result);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processUsersGetFullUser(CTelegramStream &stream, quint64 id)
{
    TLUserFull result;

    stream >> result;

    switch (result.tlType) {
    case UserFull:
        emit fullUserReceived(result);
        break;
    default:
        break;
    }

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesCreateChat(CTelegramStream &stream, quint64 id)
{
    TLMessagesStatedMessage result;

    stream >> result;

    switch (result.tlType) {
    case MessagesStatedMessage:
        emit statedMessageReceived(result, id);
        break;
    default:
        break;
    }
    return result.tlType;
}

TLValue CTelegramConnection::processMessagesSendMessage(CTelegramStream &stream, quint64 id)
{
    TLMessagesSentMessage result;
    stream >> result;

    {
        const QByteArray data = m_submittedPackages.take(id);

        CTelegramStream outputStream(data);

        TLValue method;
        TLInputPeer peer;
        QString message;
        quint64 randomId;

        outputStream >> method;
        outputStream >> peer;
        outputStream >> message;
        outputStream >> randomId;

        emit messageSentInfoReceived(peer, randomId, result.id, result.pts, result.date, result.seq);
    }

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesSetTyping(CTelegramStream &stream, quint64 id)
{
    TLValue result;
    stream >> result;

    return result;
}

TLValue CTelegramConnection::processMessagesReadHistory(CTelegramStream &stream, quint64 id)
{
    TLMessagesAffectedHistory result;
    stream >> result;

    return result.tlType;
}

TLValue CTelegramConnection::processMessagesReceivedMessages(CTelegramStream &stream, quint64 id)
{
    TLVector<quint32> result;
    stream >> result;

    return result.tlType;
}

TLValue CTelegramConnection::processAccountUpdateStatus(CTelegramStream &stream, quint64 id)
{
    TLValue result;
    stream >> result;

    return result;
}

bool CTelegramConnection::processErrorSeeOther(const QString errorMessage, quint64 id)
{
    int lastSectionIndex = errorMessage.lastIndexOf(QChar(QLatin1Char('_')));
    if (lastSectionIndex < 0) {
        return false;
    }

    quint16 dc = 0;

    bool ok;

    const QString dcStr = errorMessage.mid(lastSectionIndex + 1);
    dc = dcStr.toUInt(&ok);

    if (!ok) {
        return false;
    }

    const QByteArray data = m_submittedPackages.take(id);

    if (data.isEmpty()) {
        qDebug() << "Can not restore message" << id;
        return false;
    }

    CTelegramStream stream(data);
    TLValue value;
    stream >> value;

    if (value == AuthSendCode) {
        emit wantedActiveDcChanged(dc);
    }

    emit newRedirectedPackage(data, dc);

    return true;
}

TLValue CTelegramConnection::processUpdate(CTelegramStream &stream, bool *ok)
{
    TLUpdates updates;
    stream >> updates;

    switch (updates.tlType) {
    case UpdatesTooLong:
    case UpdateShortMessage:
    case UpdateShortChatMessage:
    case UpdateShort:
    case UpdatesCombined:
    case Updates:
        emit updatesReceived(updates);
        *ok = true;
        break;
    default:
        *ok = false;
        break;
    }

    return updates.tlType;
}

void CTelegramConnection::whenConnected()
{
    if (m_authKey.isEmpty()) {
        initAuth();
    } else {
        setAuthState(AuthStateSignedIn);
    }
}

void CTelegramConnection::whenReadyRead()
{
    QByteArray input = m_transport->getPackage();
    CRawStream inputStream(input);

    quint64 auth = 0;
    quint64 timeStamp = 0;
    quint32 length = 0;
    QByteArray payload;

    inputStream >> auth;

    /* Will be reimplemented later */

    if (!auth) {
        // Plain Message
        inputStream >> timeStamp;
        inputStream >> length;

        if (inputStream.bytesRemaining() != int(length)) {
            qDebug() << "Corrupted packet. Specified length does not equal to real length";
            return;
        }

        payload = inputStream.readBytes(length);

        switch (m_authState) {
        case AuthStatePqRequested:
            if (answerPqAuthorization(payload)) {
                requestDhParameters();
            }
            break;
        case AuthStateDhRequested:
            if (answerDh(payload)) {
                requestDhGenerationResult();
            }
            break;
        case AuthStateDhGenerationResultRequested:
            processServersDHAnswer(payload);
            break;
        default:
            break;
        }
    } else if (m_authState >= AuthStateSuccess) {
        if (auth != m_authId) {
            qDebug() << "Incorrect auth id.";
            return;
        }
        // Encrypted Message
        const QByteArray messageKey = inputStream.readBytes(16);
        const QByteArray data = inputStream.readBytes(inputStream.bytesRemaining());

        const SAesKey key = generateServerToClientAesKey(messageKey);

        QByteArray decryptedData = Utils::aesDecrypt(data, key).left(data.length());
        CRawStream decryptedStream(decryptedData);

        quint64 sessionId = 0;
        quint64 messageId  = 0;
        quint32 sequence = 0;
        quint32 contentLength = 0;

        decryptedStream >> m_receivedServerSalt;
        decryptedStream >> sessionId;
        decryptedStream >> messageId;
        decryptedStream >> sequence;
        decryptedStream >> contentLength;

        if (m_serverSalt != m_receivedServerSalt) {
            qDebug() << "Received different server salt:" << m_receivedServerSalt << "(remove) vs" << m_serverSalt << "(local)";
//            return;
        }

        if (m_sessionId != sessionId) {
            qDebug() << "Session Id is wrong.";
            return;
        }

        if (int(contentLength) > decryptedData.length()) {
            qDebug() << "Expected data length is more, than actual.";
            return;
        }

        const int headerLength = sizeof(m_receivedServerSalt) + sizeof(sessionId) + sizeof(messageId) + sizeof(sequence) + sizeof(contentLength);
        QByteArray expectedMessageKey = Utils::sha1(decryptedData.left(headerLength + contentLength)).mid(4);

        if (messageKey != expectedMessageKey) {
            qDebug() << "Wrong message key";
            return;
        }

        processRpcQuery(decryptedStream.readRemainingBytes());
    }
}

SAesKey CTelegramConnection::generateTmpAesKey() const
{
    QByteArray newNonceAndServerNonce;
    newNonceAndServerNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndServerNonce.append(m_serverNonce.data, m_serverNonce.size());
    QByteArray serverNonceAndNewNonce;
    serverNonceAndNewNonce.append(m_serverNonce.data, m_serverNonce.size());
    serverNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    QByteArray newNonceAndNewNonce;
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());
    newNonceAndNewNonce.append(m_newNonce.data, m_newNonce.size());

    const QByteArray key = Utils::sha1(newNonceAndServerNonce) + Utils::sha1(serverNonceAndNewNonce).mid(0, 12);
    const QByteArray iv  = Utils::sha1(serverNonceAndNewNonce).mid(12, 8) + Utils::sha1(newNonceAndNewNonce) + QByteArray(m_newNonce.data, 4);

    return SAesKey(key, iv);
}

SAesKey CTelegramConnection::generateAesKey(const QByteArray &messageKey, int x) const
{
    QByteArray sha1_a = Utils::sha1(messageKey + m_authKey.mid(x, 32));
    QByteArray sha1_b = Utils::sha1(m_authKey.mid(32 + x, 16) + messageKey + m_authKey.mid(48 + x, 16));
    QByteArray sha1_c = Utils::sha1(m_authKey.mid(64 + x, 32) + messageKey);
    QByteArray sha1_d = Utils::sha1(messageKey + m_authKey.mid(96 + x, 32));

    const QByteArray key = sha1_a.mid(0, 8) + sha1_b.mid(8, 12) + sha1_c.mid(4, 12);
    const QByteArray iv  = sha1_a.mid(8, 12) + sha1_b.mid(0, 8) + sha1_c.mid(16, 4) + sha1_d.mid(0, 8);

    return SAesKey(key, iv);
}

void CTelegramConnection::insertInitConnection(QByteArray *data) const
{
    CTelegramStream outputStream(data, /* write */ true);

    outputStream << InvokeWithLayer14;
    outputStream << InitConnection;

    outputStream << m_appInfo->appId();
    outputStream << m_appInfo->deviceInfo();
    outputStream << m_appInfo->osInfo();
    outputStream << m_appInfo->appVersion();
    outputStream << m_appInfo->languageCode();
}

quint64 CTelegramConnection::sendPlainPackage(const QByteArray &buffer)
{
    quint64 messageId = newMessageId();

    QByteArray output;
    CRawStream outputStream(&output, /* write */ true);

    outputStream << quint64(0);
    outputStream << messageId;
    outputStream << quint32(buffer.length());
    outputStream << buffer;

    m_transport->sendPackage(output);

    return messageId;
}

quint64 CTelegramConnection::sendEncryptedPackage(const QByteArray &buffer)
{
    QByteArray encryptedPackage;
    QByteArray messageKey;
    quint64 messageId;
    {
        m_sequenceNumber = m_contentRelatedMessages * 2 + 1;
        ++m_contentRelatedMessages;

        messageId = newMessageId();

        m_submittedPackages.insert(messageId, buffer);

        QByteArray innerData;
        CRawStream stream(&innerData, /* write */ true);

        stream << m_serverSalt;
        stream << m_sessionId;
        stream << messageId;
        stream << m_sequenceNumber;

        QByteArray header;
        if (m_sequenceNumber == 1) {
            insertInitConnection(&header);
        }

        stream << quint32(header.length() + buffer.length());
        stream << header + buffer;

        messageKey = Utils::sha1(innerData).mid(4);
        const SAesKey key = generateClientToServerAesKey(messageKey);

        quint32 packageLength = innerData.length();

        if ((packageLength) % 16) {
            QByteArray randomPadding;
            randomPadding.resize(16 - (packageLength % 16));
            Utils::randomBytes(&randomPadding);

            packageLength += randomPadding.size();

            stream << randomPadding;
        }

        encryptedPackage = Utils::aesEncrypt(innerData, key).left(packageLength);
    }

    QByteArray output;
    CRawStream outputStream(&output, /* write */ true);

    outputStream << m_authId;
    outputStream << messageKey;
    outputStream << encryptedPackage;

    m_transport->sendPackage(output);

    return messageId;
}

void CTelegramConnection::setAuthState(CTelegramConnection::AuthState newState)
{
    qDebug() << "NAS:" << newState;
    if (m_authState == newState)
        return;

    m_authState = newState;

    if ((m_authState >= AuthStateSuccess) && !m_sessionId) {
        Utils::randomBytes(&m_sessionId);
    }

    emit authStateChanged(m_dcInfo.id, m_authState);
}

quint64 CTelegramConnection::newMessageId()
{
    quint64 newLastMessageId = formatClientTimeStamp(QDateTime::currentMSecsSinceEpoch() + m_deltaTime * 1000);

    if (newLastMessageId == m_lastMessageId) {
        newLastMessageId += 4; // Client's outgoing message id should be divisible by 4 and be greater than previous message id.
    }

    if (!(newLastMessageId & quint64(0xffffff))) {
        // The lower 32 bits of messageId passed by the client must not contain that many zeroes.
        newLastMessageId += quint64(0x1230);
    }

    m_lastMessageId = newLastMessageId;

    return m_lastMessageId;
}
