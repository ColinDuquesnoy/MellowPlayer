#pragma once

#include <QFile>
#include <QIcon>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Settings)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class IconProvider {
public:
    IconProvider(UseCases::Settings& settings);

    static QIcon trayIcon();
    static QIcon windowIcon();
    static QIcon restoreWindow();
    static QIcon play();
    static QIcon pause();
    static QIcon next();
    static QIcon previous();
    static QIcon quit();
};

END_MELLOWPLAYER_NAMESPACE
