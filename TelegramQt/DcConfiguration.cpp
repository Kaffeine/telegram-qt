#include "DcConfiguration.hpp"

namespace Telegram {

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
        }
        // The Option meet the requirements, but maybe there is a better one
        result = opt;
    }
    return result;
}

} // Telegram
