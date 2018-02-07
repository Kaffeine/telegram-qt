#ifndef TELEGRAM_SERVER_DC_CONFIGURATION_HPP
#define TELEGRAM_SERVER_DC_CONFIGURATION_HPP

#include "TelegramNamespace.hpp"

#include <QVector>

namespace Telegram {

struct DcConfiguration
{
    QVector<DcOption> dcOptions;
};

} // Telegram

#endif // TELEGRAM_SERVER_DC_CONFIGURATION_HPP
