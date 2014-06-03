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

#include "TLTypes.hpp"
#include "crypto-rsa.hpp"
#include "crypto-aes.hpp"
#include "SDcInfo.hpp"

class CTelegramStream;
class CTelegramTransport;
class CRawStream;

class CTelegramConnection : public QObject
{
    Q_OBJECT
public:
    enum AuthState {
        AuthStateNone,
        AuthStatePqRequested,
        AuthStateDhRequested,
        AuthStateDhGenerationResultRequested,
        AuthStateSuccess
    };

    explicit CTelegramConnection(QObject *parent = 0);

    void setDcInfo(const SDcInfo &dc);

    inline SDcInfo dcInfo() const { return m_dcInfo; }

    void setAppId(quint32 newId);
    bool setAppHash(const QString &newHash);

    void connectToDc();

    bool isConnected() const;

    static quint64 formatTimeStamp(qint64 timeInMs);
    static inline quint64 formatClientTimeStamp(qint64 timeInMs) { return formatTimeStamp(timeInMs) & ~quint64(3); }

    static quint64 timeStampToMSecsSinceEpoch(quint64 ts);

    void initAuth();
    void getConfiguration();
    void requestAuthCode(const QString &phoneNumber);

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
    inline quint64 authId() const { return m_authId; }
    inline quint64 serverSalt() const { return m_serverSalt; }
    inline quint64 sessionId() const { return m_sessionId; }

    inline QVector<SDcInfo> dcConfiguration() { return m_dcConfiguration; }

    void processRedirectedPackage(const QByteArray &data);

signals:
    void wantedActiveDcChanged(int dc);
    void newRedirectedPackage(const QByteArray &data, int dc);

    void authStateChanged(int dc, int state);
    void actualDcIdReceived(int dc, int newDcId);
    void dcConfigurationReceived(int dc);

private slots:
    void whenConnected();
    void whenReadyRead();

protected:
    void processRpcQuery(const QByteArray &data);

    void processSessionCreated(CTelegramStream &stream);
    void processContainer(CTelegramStream &stream);
    void processRpcResult(CTelegramStream &stream);
    void processRpcError(CTelegramStream &stream, quint64 id);

    void processMessageAck(CTelegramStream &stream);
    void processBadMessageNotification(CTelegramStream &stream);

    void processConfig(CTelegramStream &stream, quint64 id, bool oldVersion = false);
    void processAuthSentCode(CTelegramStream &stream, quint64 id, bool oldVersion = false);

    bool processErrorSeeOther(const QString errorMessage, quint64 id);

    SAesKey generateTmpAesKey() const;
    SAesKey generateClientToServerAesKey(const QByteArray &messageKey) const;
    SAesKey generateServerToClientAesKey(const QByteArray &messageKey) const;

    SAesKey generateAesKey(const QByteArray &messageKey, int xValue) const;

    void sendPlainPackage(const QByteArray &buffer);
    void sendEncryptedPackage(const QByteArray &buffer);
    void setTransport(CTelegramTransport *newTransport);

    void setAuthState(AuthState newState);

    quint64 newMessageId();

    QMap<quint64, QByteArray> m_submittedPackages; // <message id, package data>

    quint32 m_appId;
    QString m_appHash;

    CTelegramTransport *m_transport;

    AuthState m_authState;

    QByteArray m_authKey;
    quint64 m_authId;
    quint64 m_authKeyAuxHash;
    quint64 m_serverSalt;
    quint64 m_sessionId;
    quint64 m_lastMessageId;
    quint32 m_sequenceNumber;
    quint32 m_contentRelatedMessages;

    qint32 m_deltaTime;

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

    SDcInfo m_dcInfo;

    QVector<SDcInfo> m_dcConfiguration;

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
