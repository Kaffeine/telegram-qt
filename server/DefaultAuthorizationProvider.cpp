#include "DefaultAuthorizationProvider.hpp"

#include "RandomGenerator.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

namespace Authorization {

DefaultProvider::DefaultProvider(QObject *parent) :
    QObject(parent),
    Provider()
{
}

SentCodeInfo DefaultProvider::sendCode(Session *session, const QString &identifier)
{
    Code code = generateCode(session, identifier);
    if (code.type == Code::Type::Default) {
        code.type = Code::Type::Sms;
    }
    m_sentCodeMap.insert(identifier, code);

    SentCodeInfo info;
    info.hash = code.hash;
    info.length = static_cast<quint32>(code.code.length());
    info.type = code.type;
    return info;
}

CodeStatus DefaultProvider::getCodeStatus(const QString &identifier, const QByteArray &hash, const QString &code)
{
    if (code.isEmpty()) {
        return CodeStatus::CodeEmpty;
    }
    if (hash.isEmpty()) {
        return CodeStatus::HashEmpty;
    }
    if (!m_sentCodeMap.contains(identifier)) {
        return CodeStatus::PhoneInvalid;
    }
    const Code c = m_sentCodeMap.value(identifier);
    if (c.hash != hash) {
        return CodeStatus::HashInvalid;
    }
    if (c.code != code) {
        return CodeStatus::CodeInvalid;
    }
    return CodeStatus::CodeValid;
}

QString DefaultProvider::generateAuthCode()
{
    const quint32 numCode = RandomGenerator::instance()->generate<quint32>() % 100000u;
    return QStringLiteral("%1").arg(numCode, 5, 10, QLatin1Char('0'));
}

Code DefaultProvider::generateCode(Session *session, const QString &identifier)
{
    Q_UNUSED(session)
    Q_UNUSED(identifier)
    Code code;
    code.hash = RandomGenerator::instance()->generate(8).toHex();
    code.code = generateAuthCode();
    code.type = Code::Type::Default;
    qInfo() << "sendAppCode(" << identifier << "):" << "hash:" << code.hash << "code:" << code.code;
    return code;
}

} // Authorization namespace

} // Server namespace

} // Telegram namespace
