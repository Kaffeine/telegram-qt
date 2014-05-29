#ifndef SDCINFO_HPP
#define SDCINFO_HPP

#include <qglobal.h>
#include <QString>

struct SDcInfo {
    SDcInfo(const QString &newIpAddress = QString(), const quint32 &newPort = 0) :
        id(0),
        ipAddress(newIpAddress),
        port(newPort) { }

    SDcInfo(const SDcInfo &otherDcInfo) :
        id(otherDcInfo.id),
        hostName(otherDcInfo.hostName),
        ipAddress(otherDcInfo.ipAddress),
        port(otherDcInfo.port) { }

    quint32 id;
    QString hostName;
    QString ipAddress;
    quint32 port;
};

#endif // SDCINFO_HPP
