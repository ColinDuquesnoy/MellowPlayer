#pragma once

#include <QFile>
#include <QIcon>

namespace MellowPlayer::Application {

    class Settings;

}

namespace MellowPlayer::Presentation {

    class IconProvider {
    public:
        IconProvider(Application::Settings& settings);

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
