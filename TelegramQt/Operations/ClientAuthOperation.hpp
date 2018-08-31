#ifndef TELEGRAMQT_CLIENT_AUTH_OPERATION
#define TELEGRAMQT_CLIENT_AUTH_OPERATION

#include "PendingOperation.hpp"
#include "TelegramNamespace.hpp"

struct TLAuthAuthorization;

namespace Telegram {

namespace Client {

class AccountRpcLayer;
class AuthRpcLayer;

class AuthOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit AuthOperation(QObject *parent = nullptr);
    void setBackend(Backend *backend);

    using RunMethod = PendingOperation *(AuthOperation::*)();

    void setRunMethod(RunMethod method);

    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString passwordHint() const { return m_passwordHint; }
    bool hasRecovery() const { return m_hasRecovery; }

public slots:
    void start() override;

    void abort();

    PendingOperation *requestAuthCode();
    PendingOperation *submitAuthCode(const QString &code);
    PendingOperation *getPassword();
    PendingOperation *submitPassword(const QString &password);

    void requestCall();
    void requestSms();
    void recovery();

Q_SIGNALS:
    void phoneNumberRequired();
    void authCodeRequired();
    void passwordRequired();
    void passwordCheckFailed();
//    void callAvailable();

    void passwordHintChanged(const QString &hint);
    void hasRecoveryChanged(bool hasRecovery);

    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage); // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void authorizationErrorReceived(TelegramNamespace::UnauthorizedError errorCode, const QString &errorMessage);

protected:
    void setWantedDc(quint32 dcId);
    void setPasswordCurrentSalt(const QByteArray &salt);
    void setPasswordHint(const QString &hint);
    AccountRpcLayer *accountLayer() const;
    AuthRpcLayer *authLayer() const;

    Backend *m_backend = nullptr;
    RunMethod m_runMethod = nullptr;
    QString m_phoneNumber;
    QString m_passwordHint;
    QByteArray m_passwordCurrentSalt;
    bool m_hasRecovery;

protected:
    // Implementation:
    void onRequestAuthCodeFinished(PendingRpcOperation *operation);
    void onSignInFinished(PendingRpcOperation *operation);
    void onPasswordRequestFinished(PendingRpcOperation *operation);
    void onCheckPasswordFinished(PendingRpcOperation *operation);
    void onGotAuthorization(PendingRpcOperation *operation, const TLAuthAuthorization &authorization);

    QString m_authCodeHash;
};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_AUTH_OPERATION
