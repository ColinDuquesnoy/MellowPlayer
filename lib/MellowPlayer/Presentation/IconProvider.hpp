#pragma once

#include <QFile>
#include <QIcon>

namespace MellowPlayer::Domain
{
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class IconProvider
    {
    public:
        static QIcon trayIcon();
        static QIcon windowIcon();
        static QIcon restoreWindow();
        static QIcon play();
        static QIcon pause();
        static QIcon next();
        static QIcon previous();
        static QIcon quit();
    };
}
