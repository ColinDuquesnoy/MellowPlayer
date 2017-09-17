#include "PlatformFilters.hpp"

using namespace MellowPlayer::Infrastructure;


//QString Platform::name() const
//{
//    QString plaformName = Unsupported;
//
//#ifdef Q_OS_LINUX
//    QString appImagePath = qgetenv("APPIMAGE");
//    if (appImagePath.isEmpty())
//        plaformName = Linux;
//    else
//        plaformName = AppImage;
//#endif
//
//#ifdef Q_OS_OSX
//    plaformName = OSX;
//#endif
//
//#ifdef Q_OS_WIN
//    plaformName = Windows;
//#endif
//
//    return plaformName;
//}


bool PlatformFilters::match(QString) const
{
    return false;
}
