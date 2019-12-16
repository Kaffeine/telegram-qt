#include "DcConfiguration.hpp"

namespace Telegram {

int DcConfiguration::dcCount() const
{
    QVector<quint32> dcs;

    for (const DcOption &opt : dcOptions) {
        const quint32 dcId = opt.id;
        if (dcs.contains(dcId)) {
            continue;
        }
        dcs.append(dcId);
    }
    return dcs.count();
}

DcOption DcConfiguration::getOption(const ConnectionSpec spec) const
{
    DcOption result;

    for (const DcOption &opt : dcOptions) {
        if (opt.id != spec.dcId) {
            continue;
        }
        if (spec.flags & ConnectionSpec::RequestFlag::Ipv4Only) {
            if (opt.flags & DcOption::Ipv6) {
                continue;
            }
        }
        if (spec.flags & ConnectionSpec::RequestFlag::Ipv6Only) {
            if (!(opt.flags & DcOption::Ipv6)) {
                continue;
            }
        }
        if (opt.flags & DcOption::MediaOnly) {
            if (spec.flags & ConnectionSpec::RequestFlag::MediaOnly) {
                // Best match
                return opt;
            }
            continue;
        }

        // The Option meet the requirements, but maybe there is a better one
        result = opt;
        if (spec.flags & ConnectionSpec::RequestFlag::MediaOnly) {
            result.flags |= DcOption::MediaOnly;
        }
    }
    return result;
}

} // Telegram
