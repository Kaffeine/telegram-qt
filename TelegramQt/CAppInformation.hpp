/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#ifndef CAPPINFORMATION_HPP
#define CAPPINFORMATION_HPP

#include "telegramqt_global.h"

#include <QString>
#include <QObject>

namespace Telegram {

namespace Client {

class TELEGRAMQT_EXPORT AppInformation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 appId READ appId WRITE setAppId)
    Q_PROPERTY(QString appHash READ appHash WRITE setAppHash)
    Q_PROPERTY(QString appVersion READ appVersion WRITE setAppVersion)
    Q_PROPERTY(QString deviceInfo READ deviceInfo WRITE setDeviceInfo)
    Q_PROPERTY(QString osInfo READ osInfo WRITE setOsInfo)
    Q_PROPERTY(QString languageCode READ languageCode WRITE setLanguageCode)
public:
    AppInformation(QObject *parent = nullptr);
    AppInformation(const AppInformation *anotherInfo, QObject *parent = nullptr);

    bool isValid() const;

    quint32 appId() const;
    QString appHash() const;
    QString appVersion() const;

    QString deviceInfo() const;
    QString osInfo() const;
    QString languageCode() const;

    bool setAppId(quint32 newId);
    bool setAppHash(const QString &newHash);
    bool setAppVersion(const QString &newVersion);

    bool setDeviceInfo(const QString &newDeviceInfo);
    bool setOsInfo(const QString &newOsInfo);
    bool setLanguageCode(const QString &newLanguageCode);

private:
    quint32 m_appId;
    QString m_appHash;
    QString m_appVersion;

    QString m_deviceInfo;
    QString m_osInfo;
    QString m_langCode;
};

inline bool AppInformation::isValid() const
{
    return m_appId && !m_appHash.isEmpty()
            && !m_appVersion.isEmpty() && !m_deviceInfo.isEmpty()
            && !m_osInfo.isEmpty() && !m_langCode.isEmpty();
}

inline quint32 AppInformation::appId() const
{
    return m_appId;
}

inline QString AppInformation::appHash() const
{
    return m_appHash;
}

inline QString AppInformation::appVersion() const
{
    return m_appVersion;
}

inline QString AppInformation::deviceInfo() const
{
    return m_deviceInfo;
}

inline QString AppInformation::osInfo() const
{
    return m_osInfo;
}

inline QString AppInformation::languageCode() const
{
    return m_langCode;
}

} // Client namespace

} // Telegram namespace

using CAppInformation = Telegram::Client::AppInformation;

#endif // CAPPINFORMATION_HPP
