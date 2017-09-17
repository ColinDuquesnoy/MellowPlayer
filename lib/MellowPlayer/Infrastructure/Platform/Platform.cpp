#include "Platform.hpp"

using namespace MellowPlayer::Infrastructure;


QString Platform::Unsupported = "Unsupported platform";
QString Platform::Linux = "GNU/Linux";
QString Platform::AppImage = "AppImage";
QString Platform::Windows = "Windows";
QString Platform::OSX = "Mac OSX";

QString Platform::name() const
{
    QString plaformName = Unsupported;

#ifdef Q_OS_LINUX
    QString appImagePath = qgetenv("APPIMAGE");
    if (appImagePath.isEmpty())
        plaformName = Linux;
    else
        plaformName = AppImage;
#endif

#ifdef Q_OS_OSX
    plaformName = OSX;
#endif

#ifdef Q_OS_WIN
    plaformName = Windows;
#endif

    return plaformName;
}

bool Platform::match(QList<IPlatformFilter>&) const
{
    return false;
}

bool Platform::isLinux() const
{
    return name() == Linux;
}

bool Platform::isAppImage() const
{
    return name() == AppImage;
}

bool Platform::isWindows() const
{
    return name() == Windows;
}

bool Platform::isOsx() const
{
    return name() == OSX;
}

