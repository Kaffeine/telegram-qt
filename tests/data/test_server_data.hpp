#ifndef TEST_SERVER_DATA_HPP
#define TEST_SERVER_DATA_HPP

#include "TelegramNamespace.hpp"
#include "DcConfiguration.hpp"

static const QVector<Telegram::DcOption> c_localDcOptions = {
    Telegram::DcOption(QStringLiteral("127.0.0.11"), 11441, 1),
    Telegram::DcOption(QStringLiteral("127.0.0.12"), 11442, 2),
    Telegram::DcOption(QStringLiteral("127.0.0.13"), 11443, 3),
};

static const Telegram::DcConfiguration c_localDcConfiguration = []() {
    Telegram::DcConfiguration configuration;
    configuration.dcOptions = c_localDcOptions;
    return configuration;
}();

#endif // TEST_SERVER_DATA_HPP
