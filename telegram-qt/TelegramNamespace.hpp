#ifndef TELEGRAMNAMESPACE_HPP
#define TELEGRAMNAMESPACE_HPP

#include "telegramqt_export.h"

#include <QObject>

class TELEGRAMQT_EXPORT TelegramNamespace : public QObject
{
    Q_OBJECT
    Q_ENUMS(ContactStatus)
public:
    explicit TelegramNamespace(QObject *parent = 0);

    enum ContactStatus {
        ContactStatusUnknown,
        ContactStatusOffline,
        ContactStatusOnline
    };

    enum MessageDeliveryStatus {
        MessageDeliveryStatusUnknown,
        MessageDeliveryStatusSent,
        MessageDeliveryStatusRead,
        MessageDeliveryStatusDeleted
    };

    static void registerTypes();
};

#endif // TELEGRAMNAMESPACE_HPP
