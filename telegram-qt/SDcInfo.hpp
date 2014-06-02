#ifndef SDCINFO_HPP
#define SDCINFO_HPP

#include <qglobal.h>
#include <QString>

struct SDcInfo {
    SDcInfo(const QString &newIpAddress = QString(), const quint32 &newPort = 0) :
        id(0),
        ipAddress(newIpAddress),
        port(newPort) { }

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
