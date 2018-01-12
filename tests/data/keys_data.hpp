#ifndef TELEGRAM_QT_KEY_DATA_HPP
#define TELEGRAM_QT_KEY_DATA_HPP

#include <QByteArray>

QT_FORWARD_DECLARE_CLASS(QIODevice)

struct TestKeyData
{
    static const QByteArray keyModulus;
    static const QByteArray keyExponent;
    static const QByteArray keySecretExponent;
    static const quint64 keyFingerprint;

    static bool initKeyFiles();
    static bool cleanupKeyFiles();

    static bool copyFile(const QString &sourceFileName, QIODevice *output);
    static QString privateKeyFileName();
    static QString publicKeyFileName();
};

#endif //TELEGRAM_QT_KEY_DATA_HPP
