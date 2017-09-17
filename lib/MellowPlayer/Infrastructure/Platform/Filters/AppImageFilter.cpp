#include "AppImageFilter.hpp"

using namespace MellowPlayer::Infrastructure;

bool AppImageFilter::match() const
{
#ifdef Q_OS_LINUX
    return isAppImage_;
#else
    return false;
#endif
}
