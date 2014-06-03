#ifndef TLNUMBERS_HPP
#define TLNUMBERS_HPP

#include <qglobal.h>

template <int Size> union TLNumbers {
    char data[Size / 8];
    quint64 parts[Size / 8 / 8];

    int size() const { return Size / 8; }

    TLNumbers() {
        for (int i = 0; i < Size / 8 / 8; ++i)
            parts[i] = 0;
    }

    TLNumbers &operator=(const TLNumbers &anotherTLNumber) {
        for (int i = 0; i < Size / 8 / 8; ++i)
            parts[i] = anotherTLNumber.parts[i];

        return *this;
    }

    bool operator ==(const TLNumbers &anotherTLNumber) const {
        for (int i = 0; i < Size / 8 / 8; ++i) {
            if (parts[i] != anotherTLNumber.parts[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator !=(const TLNumbers &anotherTLNumber) const {
        for (int i = 0; i < Size / 8 / 8; ++i) {
            if (parts[i] != anotherTLNumber.parts[i]) {
                return true;
            }
        }
        return false;
    }
};

typedef TLNumbers<128> TLNumber128;
typedef TLNumbers<256> TLNumber256;

#endif // TLNUMBERS_HPP
