#ifndef TELEGRAM_SERVER_DC_CONFIGURATION_HPP
#define TELEGRAM_SERVER_DC_CONFIGURATION_HPP

#include "TelegramNamespace.hpp"

#include <QVector>

namespace Telegram {

namespace Server {

struct DcConfiguration
{
    QVector<DcOption> dcOptions;
};

} // Server

} // Telegram

#endif // TELEGRAM_SERVER_DC_CONFIGURATION_HPP
