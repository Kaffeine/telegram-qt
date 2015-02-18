/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef TELEGRAMNAMESPACE_HPP
#define TELEGRAMNAMESPACE_HPP

#include "telegramqt_export.h"

#include <QObject>

class TELEGRAMQT_EXPORT TelegramNamespace : public QObject
{
    Q_OBJECT
    Q_ENUMS(ContactStatus)
public:
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

    enum MessageFlags {
        MessageFlagNone = 0x0,
        MessageFlagRead = 0x1, // Message was read
        MessageFlagOut  = 0x2  // Message is outgoing
    };

    enum MessageType {
        MessageTypeUnsupported = 0x00,
        MessageTypeText        = 0x01,
        MessageTypePhoto       = 0x02,
        MessageTypeAudio       = 0x04,
        MessageTypeVideo       = 0x08,
        MessageTypeContact     = 0x10,
        MessageTypeDocument    = 0x20,
        MessageTypeGeo         = 0x40
    };

    enum AuthSignError {
        AuthSignErrorUnknown,
        AuthSignErrorAppIdIsInvalid,
        AuthSignErrorPhoneNumberIsInvalid,
        AuthSignErrorPhoneNumberIsOccupied,
        AuthSignErrorPhoneNumberIsUnoccupied,
        AuthSignErrorPhoneCodeIsInvalid,
        AuthSignErrorPhoneCodeIsExpired,
        AuthSignErrorFirstNameIsInvalid,
        AuthSignErrorLastNameIsInvalid
    };

    enum AccountUserNameStatus {
        AccountUserNameStatusUnknown,
        AccountUserNameStatusIsInvalid,
        AccountUserNameStatusIsOccupied,
        AccountUserNameStatusIsNotModified,
        AccountUserNameStatusCanBeUsed,
        AccountUserNameStatusCanNotBeUsed,
        AccountUserNameStatusAccepted
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
