#include "LinuxFilter.hpp"

using namespace MellowPlayer::Infrastructure;

bool LinuxFilter::match() const
{
#ifdef Q_OS_LINUX
    return !isAppImage_;
#else
    return false;
#endif
}
