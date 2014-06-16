#ifndef SDCINFO_HPP
#define SDCINFO_HPP

#include <QString>

struct SDcInfo {
    SDcInfo(const QString &newIpAddress = QString(), const quint32 &newPort = 0, const quint32 &newId = 0) :
        id(newId),
        ipAddress(newIpAddress),
        port(newPort) { }

    bool isValid() const {
        return (port > 0) && !ipAddress.isEmpty();
    }

    SDcInfo(const SDcInfo &anotherInfo) :
        id(anotherInfo.id),
        hostName(anotherInfo.hostName),
        ipAddress(anotherInfo.ipAddress),
        port(anotherInfo.port) { }

    SDcInfo &operator=(const SDcInfo &anotherInfo) {
        id = anotherInfo.id;
        hostName = anotherInfo.hostName;
        ipAddress = anotherInfo.ipAddress;
        port = anotherInfo.port;

        return *this;
    }

    quint32 id;
    QString hostName;
    QString ipAddress;
    quint32 port;
};

#endif // SDCINFO_HPP
