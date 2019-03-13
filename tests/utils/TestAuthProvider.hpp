#ifndef TEST_AUTH_PROVIDER_HPP
#define TEST_AUTH_PROVIDER_HPP

#include "DefaultAuthorizationProvider.hpp"

namespace Telegram {

namespace Test {

class AuthProvider : public Server::Authorization::DefaultProvider
{
    Q_OBJECT
public:
    using BaseClass = Server::Authorization::DefaultProvider;
    AuthProvider() = default;

signals:
    void codeSent(const QString &identifier, const QString &code);
protected:
    Server::Authorization::Code generateCode(Server::Session *session, const QString &identifier) override;
};

inline Server::Authorization::Code AuthProvider::generateCode(Server::Session *session, const QString &identifier)
{
    Server::Authorization::Code code = BaseClass::generateCode(session, identifier);
    emit codeSent(identifier, code.code);
    return code;
}

} // Test namespace

} // Telegram namespace

#endif // TEST_AUTH_PROVIDER_HPP
