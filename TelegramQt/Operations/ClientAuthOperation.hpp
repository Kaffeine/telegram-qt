#ifndef TELEGRAMQT_CLIENT_AUTH_OPERATION
#define TELEGRAMQT_CLIENT_AUTH_OPERATION

#include "../PendingOperation.hpp"
#include "../TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class AuthOperationPrivate;
class TELEGRAMQT_EXPORT AuthOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit AuthOperation(QObject *parent = nullptr);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    QString passwordHint() const;
    bool hasRecovery() const;
    bool isRegistered() const;

public slots:
    void abort();

    void submitAuthCode(const QString &code);
    void submitPassword(const QString &password);

    void submitPhoneNumber(const QString &phoneNumber);
    bool submitName(const QString &firstName, const QString &lastName);

    void requestCall();
    void requestSms();
    void recovery();

Q_SIGNALS:
    void nameRequired();
    void phoneNumberRequired();
    void authCodeRequired();
    void passwordRequired();
    void passwordCheckFailed();
//    void callAvailable();

    void passwordHintChanged(const QString &hint);
    void hasRecoveryChanged(bool hasRecovery);
    void registeredChanged(bool registered); // Always emitted before authCodeRequired()

    // Error message description: https://core.telegram.org/api/errors
    void errorOccurred(const QVariantHash &details);

protected:
    void startImplementation() override;

    AuthOperationPrivate *d_func();
    const AuthOperationPrivate *d_func() const;
    friend class AuthOperationPrivate;

};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_AUTH_OPERATION
