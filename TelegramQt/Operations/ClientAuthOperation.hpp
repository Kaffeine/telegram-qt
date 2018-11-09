#ifndef TELEGRAMQT_CLIENT_AUTH_OPERATION
#define TELEGRAMQT_CLIENT_AUTH_OPERATION

#include "PendingOperation.hpp"
#include "TelegramNamespace.hpp"

struct TLAuthAuthorization;

namespace Telegram {

namespace Client {

class AccountRpcLayer;
class AuthRpcLayer;
class Backend;
class Connection;
class ConnectionApiPrivate;
class PendingRpcOperation;

class AuthOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit AuthOperation(QObject *parent = nullptr);

    enum AuthCodeStatus {
        AuthCodeStatusUnknown,
        AuthCodeStatusInvalid,
        AuthCodeStatusExpired,
    };

    void setBackend(Backend *backend);

    using RunMethod = PendingOperation *(AuthOperation::*)();

    void setRunMethod(RunMethod method);

    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString passwordHint() const { return m_passwordHint; }
    bool hasRecovery() const { return m_hasRecovery; }
    bool isRegistered() const { return m_registered; }

public slots:
    void start() override;

    void abort();

    PendingOperation *checkAuthorization();
    PendingOperation *requestAuthCode();
    PendingOperation *submitAuthCode(const QString &code);
    PendingOperation *submitPassword(const QString &password);

    void submitPhoneNumber(const QString &phoneNumber);
    bool submitName(const QString &firstName, const QString &lastName);

    void requestCall();
    void requestSms();
    void recovery();

Q_SIGNALS:
    void phoneNumberRequired();
    void authCodeRequired();
    void authCodeCheckFailed(AuthCodeStatus status);
    void passwordRequired();
    void passwordCheckFailed();
//    void callAvailable();

    void passwordHintChanged(const QString &hint);
    void hasRecoveryChanged(bool hasRecovery);
    void registeredChanged(bool registered); // Always emitted before authCodeRequired()

    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QByteArray &errorMessage); // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QByteArray &errorMessage);

protected:
    void setWantedDc(quint32 dcId);
    void setPasswordCurrentSalt(const QByteArray &salt);
    void setPasswordHint(const QString &hint);
    void setRegistered(bool registered);

    AccountRpcLayer *accountLayer() const;
    AuthRpcLayer *authLayer() const;

    Backend *m_backend = nullptr;
    RunMethod m_runMethod = nullptr;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_passwordHint;
    QString m_authCodeHash;
    QByteArray m_passwordCurrentSalt;
    bool m_hasRecovery;
    bool m_registered = false;
    Connection *m_authenticatedConnection = nullptr;
    friend class ConnectionApiPrivate;

protected:
    // Implementation:
    PendingOperation *getPassword();

    void onRequestAuthCodeFinished(PendingRpcOperation *rpcOperation);
    void onSignInRpcFinished(PendingRpcOperation *rpcOperation, PendingOperation *submitAuthCodeOperation);
    void onSignUpRpcFinished(PendingRpcOperation *rpcOperation, PendingOperation *submitAuthCodeOperation);
    void onPasswordRequestFinished(PendingRpcOperation *operation);
    void onCheckPasswordFinished(PendingRpcOperation *operation);
    void onGotAuthorization(PendingRpcOperation *operation, const TLAuthAuthorization &authorization);

    void onAccountStatusUpdateFinished(PendingRpcOperation *operation);

    void onConnectionError(const QString &description);

};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_AUTH_OPERATION
