#pragma once

#include <QFile>
#include <QIcon>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class IconProvider {
public:
    IconProvider(UseCases::IApplicationSettings& applicationSettings): applicationSettings(applicationSettings) { }

    QIcon trayIcon() {
        QString iconString = applicationSettings.getTrayIcon();
        if (iconString.trimmed().isEmpty())
            return windowIcon();
        else if (QFile::exists(iconString))
            return QIcon(iconString);
        else
            return QIcon::fromTheme(iconString);
    }

    static QIcon windowIcon() {
        return QIcon::fromTheme("mellowplayer", QIcon("://MellowPlayer/Presentation/icons/mellowplayer.png"));
    }

    static QIcon restoreWindow() {
        return QIcon::fromTheme("view-restore", QIcon("://MellowPlayer/Presentation/icons/view-restore.png"));
    }

    static QIcon play() {
        return QIcon::fromTheme("media-playback-start",
                                QIcon("://MellowPlayer/Presentation/icons/media-playback-start.png"));
    }

    static QIcon next() {
        return QIcon::fromTheme("media-seek-forward",
                                QIcon("://MellowPlayer/Presentation/icons/media-seek-forward.png"));
    }

    static QIcon previous() {
        return QIcon::fromTheme("media-seek-backward",
                                QIcon("://MellowPlayer/Presentation/icons/media-seek-backward.png"));
    }

    static QIcon quit() {
        return QIcon::fromTheme("application-exit",
                                QIcon("://MellowPlayer/Presentation/icons/application-exit.png"));
    }

private:
    UseCases::IApplicationSettings& applicationSettings;
};

END_MELLOWPLAYER_NAMESPACE
