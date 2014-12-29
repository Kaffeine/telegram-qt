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

    struct GroupChat
    {
        GroupChat(quint32 id = 0) :
            id(id),
            participantsCount(0) {
        }

        GroupChat(const GroupChat &anotherChat) :
            id(anotherChat.id),
            title(anotherChat.title),
            participantsCount(anotherChat.participantsCount) {
        }

        GroupChat &operator =(const GroupChat &anotherChat) {
            id = anotherChat.id;
            title = anotherChat.title;
            participantsCount = anotherChat.participantsCount;

            return *this;
        }

        quint32 id;
        QString title;
        quint32 participantsCount;
    };

};

Q_DECLARE_TYPEINFO(TelegramNamespace::GroupChat, Q_MOVABLE_TYPE);

#endif // TELEGRAMNAMESPACE_HPP
