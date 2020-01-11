#ifndef TELEGRAM_SERVER_DC_CONFIGURATION_HPP
#define TELEGRAM_SERVER_DC_CONFIGURATION_HPP

#include "TelegramNamespace.hpp"

#if QT_VERSION < QT_VERSION_CHECK(5, 6, 0)
#include <QHash>
#endif // Qt-5.6

#include <QVector>

namespace Telegram {

struct ConnectionSpec
{
    enum class RequestFlag {
        None = 0,
        Ipv4Only = 1 << 1,
        Ipv6Only = 1 << 2,
        MediaOnly = 1 << 3,
    };
    Q_DECLARE_FLAGS(RequestFlags, RequestFlag)

    ConnectionSpec() = default;
    explicit ConnectionSpec(quint32 id, RequestFlags f = RequestFlags()) :
        dcId(id),
        flags(f)
    {
    }
    bool operator==(const ConnectionSpec &spec) const
    {
        return spec.dcId == dcId && spec.flags == flags;
    }

    quint32 dcId = 0;
    RequestFlags flags;
};

struct TELEGRAMQT_INTERNAL_EXPORT DcConfiguration
{
    int dcCount() const;

    DcOption getOption(const ConnectionSpec spec) const;
    bool isValid() const { return !dcOptions.isEmpty(); }

    quint32 chatSizeMax = 0;
    quint32 megagroupSizeMax = 0;
    quint32 forwardedCountMax = 0;
    quint32 onlineCloudTimeoutMs = 0;
    quint32 onlineUpdatePeriodMs = 0;
    quint32 offlineBlurTimeoutMs = 0;
    quint32 offlineIdleTimeoutMs = 0;
    bool testMode = false;
    QString meUrlPrefix;
    QVector<DcOption> dcOptions;
};

inline uint qHash(const ConnectionSpec &key, uint seed)
{
    return ::qHash(static_cast<uint>(key.dcId | (static_cast<quint32>(key.flags) << 20)), seed);
}

} // Telegram namespace

#endif // TELEGRAM_SERVER_DC_CONFIGURATION_HPP
