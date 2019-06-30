#ifndef TELEGRAM_QT_SERVER_DEFAULT_AUTHORIZATION_PROVIDER_HPP
#define TELEGRAM_QT_SERVER_DEFAULT_AUTHORIZATION_PROVIDER_HPP

#include "AuthorizationProvider.hpp"

#include <QObject>
#include <QHash>

namespace Telegram {

namespace Server {

namespace Authorization {

class DefaultProvider : public QObject, public Provider
{
    Q_OBJECT
public:
    explicit DefaultProvider(QObject *parent = nullptr);
    ~DefaultProvider() override {}
    SentCodeInfo sendCode(Session *session, const QString &identifier) override;
    CodeStatus getCodeStatus(const QString &identifier, const QByteArray &hash, const QString &code) override;
protected:
    static QString generateAuthCode();
    virtual Code generateCode(Session *session, const QString &identifier);

    QHash<QString, Code> m_sentCodeMap;
};

} // Authorization namespace

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_DEFAULT_AUTHORIZATION_PROVIDER_HPP
