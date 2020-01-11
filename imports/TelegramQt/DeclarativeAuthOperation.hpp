#ifndef TELEGRAM_DECLARATIVE_AUTH_OPERATION_HPP
#define TELEGRAM_DECLARATIVE_AUTH_OPERATION_HPP

#include <QObject>

#include "DeclarativeOperation.hpp"

namespace Telegram {

namespace Client {

class DeclarativeClient;
class DeclarativeSettings;

class AuthOperation;

class TELEGRAMQT_QML_EXPORT DeclarativeAuthOperation : public DeclarativeOperation
{
    Q_OBJECT
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(bool registered READ isRegistered NOTIFY registeredChanged)
    Q_PROPERTY(QString passwordHint READ passwordHint NOTIFY passwordHintChanged)
    Q_PROPERTY(bool hasRecovery READ hasRecovery NOTIFY hasRecoveryChanged)
//    Q_PROPERTY(bool callAvailable READ isCallAvailable NOTIFY callAvailableChanged)
    Q_PROPERTY(AuthStatus status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)
//    Q_PROPERTY(bool passwordParamsKnown READ passwordParamsKnown)
public:
    explicit DeclarativeAuthOperation(QObject *parent = nullptr);

    enum AuthStatus {
        Idle,
        Connecting,
        Handshake,
        PhoneNumberRequired,
        AuthCodeRequired,
        PasswordRequired,
        SignedIn
    };
    Q_ENUM(AuthStatus)

    bool isBusy() const;
    AuthStatus status() const;

    QString phoneNumber() const;
    bool isRegistered() const;
    QString passwordHint() const;
    bool hasRecovery() const;

public slots:
    void startAuthentication();
    void checkIn();

    void abort();
    void submitPhoneNumber(const QString &phoneNumber);

    bool submitAuthCode(const QString &code);
    bool submitPassword(const QString &password);
    bool submitName(const QString &firstName, const QString &lastName);

    void setPhoneNumber(const QString &phoneNumber);

    bool recovery();

    bool requestCall();
    bool requestSms();

Q_SIGNALS:
    void busyChanged(bool busy);
    void checkInFinished(bool signedIn);
    void signInFinished(bool signedIn);

    void passwordHintChanged(const QString &hint);
    void hasRecoveryChanged();

    void phoneNumberRequired();
    void authCodeRequired();
    void authCodeCheckFailed();
    void passwordRequired();
    void passwordCheckFailed();

    void phoneNumberChanged();
    void registeredChanged(bool registered); // Always emitted before authCodeRequired()
//    void callAvailable();

    void statusChanged(AuthStatus status);

    // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void errorOccurred(Telegram::Namespace::AuthenticationError errorCode, const QByteArray &errorMessage);
    void authorizationErrorReceived(Telegram::Namespace::UnauthorizedError errorCode, const QString &errorMessage);

protected:
    void setStatus(const DeclarativeAuthOperation::AuthStatus status);
    void setBusy(bool busy);

    void unsetBusy();
    void onPasswordRequired();
    void onPasswordCheckFailed();

    AuthOperation *m_authOperation = nullptr;

    void startEvent() override;

    bool m_busy = false;
    AuthStatus m_status = AuthStatus::Idle;
    QString m_phoneNumber;

};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_AUTH_OPERATION_HPP
