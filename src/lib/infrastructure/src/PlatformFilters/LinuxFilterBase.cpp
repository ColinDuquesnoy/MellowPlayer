#include <MellowPlayer/Infrastructure/PlatformFilters/LinuxFilterBase.hpp>

using namespace MellowPlayer::Infrastructure;

LinuxFilterBase::LinuxFilterBase():
    isAppImage_(false)
{
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty())
        isAppImage_ = true;
}
