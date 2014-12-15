#include "TelegramNamespace.hpp"

#include <QMetaType>

TelegramNamespace::TelegramNamespace(QObject *parent) :
    QObject(parent)
{
}

void TelegramNamespace::registerTypes()
{
    bool registered = false;
    if (!registered) {
        qRegisterMetaType<TelegramNamespace::ContactStatus>("TelegramNamespace::ContactStatus");
        qRegisterMetaType<TelegramNamespace::MessageDeliveryStatus>("TelegramNamespace::MessageDeliveryStatus");
        registered = true;
    }
}
