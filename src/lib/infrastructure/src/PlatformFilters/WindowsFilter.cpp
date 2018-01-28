#include <MellowPlayer/Infrastructure/PlatformFilters/WindowsFilter.hpp>

using namespace MellowPlayer::Infrastructure;

bool WindowsFilter::match() const
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}
