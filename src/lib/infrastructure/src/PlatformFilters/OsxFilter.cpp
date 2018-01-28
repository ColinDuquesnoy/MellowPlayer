#include <MellowPlayer/Infrastructure/PlatformFilters/OsxFilter.hpp>

using namespace MellowPlayer::Infrastructure;

bool OsxFilter::match() const
{
#ifdef Q_OS_OSX
    return true;
#else
    return false;
#endif
}
