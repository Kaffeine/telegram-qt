#ifndef TELEGRAMQT_READY_OBJECT_HPP
#define TELEGRAMQT_READY_OBJECT_HPP

#include "telegramqt_global.h"

namespace Telegram {

class PendingOperation;

class TELEGRAMQT_EXPORT ReadyObject
{
public:
    virtual ~ReadyObject() = default;
    virtual bool isReady() const = 0;
    virtual PendingOperation *becomeReady() = 0;
};

} // Telegram namespace

#endif // TELEGRAMQT_READY_OBJECT_HPP
