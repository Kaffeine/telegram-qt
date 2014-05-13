#ifndef CRYPTO_RSA_HPP
#define CRYPTO_RSA_HPP

#include <QByteArray>

struct SRsaKey {
    QByteArray key;
    QByteArray exp;
    quint64 fingersprint;

    inline SRsaKey(const QByteArray &initialKey = QByteArray(), const QByteArray &initialExp = QByteArray(), const quint64 initialFingersprint = 0) :
        key(initialKey), exp(initialExp), fingersprint(initialFingersprint) { }

    inline SRsaKey &operator=(const SRsaKey &anotherKey)
    {
        key = anotherKey.key;
        exp = anotherKey.exp;
        fingersprint = anotherKey.fingersprint;
        return *this;
    }
};

#endif // CRYPTO_RSA_HPP
