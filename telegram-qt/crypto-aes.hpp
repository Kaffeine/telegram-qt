#ifndef CRYPTOAES_HPP
#define CRYPTOAES_HPP

#include <QByteArray>

struct SAesKey {
    QByteArray key;
    QByteArray iv;

    inline SAesKey(const QByteArray &initialKey = QByteArray(), const QByteArray &initialIV = QByteArray()) :
        key(initialKey), iv(initialIV) { }

    inline SAesKey &operator=(const SAesKey &anotherKey)
    {
        key = anotherKey.key;
        iv  = anotherKey.iv;
        return *this;
    }
};

#endif // CRYPTOAES_HPP
