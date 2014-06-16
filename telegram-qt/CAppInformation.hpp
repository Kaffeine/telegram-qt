#ifndef CAPPINFORMATION_HPP
#define CAPPINFORMATION_HPP

#include "telegramqt_export.h"

#include <QString>

class TELEGRAMQT_EXPORT CAppInformation
{
public:
    CAppInformation();
    CAppInformation(const CAppInformation *anotherInfo);

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

inline bool CAppInformation::isValid() const
{
    return m_appId && !m_appHash.isEmpty()
            && !m_appVersion.isEmpty() && !m_deviceInfo.isEmpty()
            && !m_osInfo.isEmpty() && !m_langCode.isEmpty();
}

inline quint32 CAppInformation::appId() const
{
    return m_appId;
}

inline QString CAppInformation::appHash() const
{
    return m_appHash;
}

inline QString CAppInformation::appVersion() const
{
    return m_appVersion;
}

inline QString CAppInformation::deviceInfo() const
{
    return m_deviceInfo;
}

inline QString CAppInformation::osInfo() const
{
    return m_osInfo;
}

inline QString CAppInformation::languageCode() const
{
    return m_langCode;
}

#endif // CAPPINFORMATION_HPP
