#include "TelegramNamespace.hpp"

#include <QMetaType>

void TelegramNamespace::registerTypes()
{
    static bool registered = false;
    if (!registered) {
        qRegisterMetaType<TelegramNamespace::ContactStatus>("TelegramNamespace::ContactStatus");
        qRegisterMetaType<TelegramNamespace::MessageDeliveryStatus>("TelegramNamespace::MessageDeliveryStatus");
        qRegisterMetaType<TelegramNamespace::MessageFlags>("TelegramNamespace::MessageFlags");
        registered = true;
    }
}
