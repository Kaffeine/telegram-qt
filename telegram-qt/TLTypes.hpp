#ifndef TLTYPES_HPP
#define TLTYPES_HPP

#include <qglobal.h>

union MyQuint128 {
    char data[16];
    unsigned char udata[16];
    struct {
        quint64 little;
        quint64 big;
    } parts;

    MyQuint128() {
        parts.little = 0;
        parts.big = 0;
    }

    MyQuint128 &operator=(const MyQuint128 &anotherQuint128) {
        parts.little = anotherQuint128.parts.little;
        parts.big = anotherQuint128.parts.big;
        return *this;
    }

    bool operator ==(const MyQuint128 &anotherQuint128) {
        return (parts.little == anotherQuint128.parts.little) &&
                (parts.big == anotherQuint128.parts.big);
    }

    bool operator !=(const MyQuint128 &anotherQuint128) {
        return (parts.little != anotherQuint128.parts.little) ||
                (parts.big != anotherQuint128.parts.big);
    }
};

#endif // TLTYPES_HPP
