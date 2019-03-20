#ifndef TEST_USER_DATA_HPP
#define TEST_USER_DATA_HPP

#include "Utils.hpp"

#include <QString>
#include <QMetaType>

struct UserData
{
    quint32 dcId;
    QString phoneNumber;
    QString firstName;
    QString lastName;
    QString password;
    QByteArray passwordSalt;
    QByteArray passwordHash;

    void setName(const QString &first, const QString &last)
    {
        firstName = first;
        lastName = last;
    }

    void unsetPassword()
    {
        setPassword(QString(), QByteArray());
    }

    void setPassword(const QString &pass, const QByteArray &salt)
    {
        password = pass;
        setPasswordSalt(salt);
    }

    void setPasswordSalt(const QByteArray &salt)
    {
        if (salt.isEmpty()) {
            passwordSalt.clear();
            passwordHash.clear();
            return;
        }
        QByteArray pwdData = salt + password.toUtf8() + salt;
        passwordSalt = salt;
        passwordHash = Telegram::Utils::sha256(pwdData);
    }
};

UserData mkUserData(int idNumber, quint32 dcId)
{
    const QString idStr = QString::number(idNumber);
    UserData userData;
    userData.dcId = dcId;
    userData.setName(QLatin1String("First") + idStr, QLatin1String("Last") + idStr);
    userData.phoneNumber = QLatin1String("12345") + idStr;
    return userData;
}

Q_DECLARE_METATYPE(UserData)

#endif // TEST_USER_DATA_HPP
