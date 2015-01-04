#include "icons.h"

QIcon Icons::play()
{
    return QIcon::fromTheme("media-playback-start",
                            QIcon(":/icons/media-playback-start.png"));

}

QIcon Icons::pause()
{
    return QIcon::fromTheme("media-playback-pause",
                            QIcon(":/icons/media-playback-pause.png"));
}

QIcon Icons::stop()
{
    return QIcon::fromTheme("media-playback-stop",
                            QIcon(":/icons/media-playback-stop.png"));
}

QIcon Icons::loading()
{
    return QIcon(":/icons/loading_static.png");
}

QIcon Icons::next()
{
    return QIcon::fromTheme("media-seek-forward",
                            QIcon(":/icons/media-seek-forward.png"));
}

QIcon Icons::previous()
{
    return QIcon::fromTheme("media-seek-backward",
                            QIcon(":/icons/media-seek-backward.png"));
}

QIcon Icons::selectCloudService()
{
    return QIcon::fromTheme("system-run",
                            QIcon(":/icons/system-run.png"));
}

QIcon Icons::preferences()
{
    return QIcon::fromTheme("preferences-system",
                            QIcon(":/icons/preferences-system.png"));
}

QIcon Icons::quit()
{
    return QIcon::fromTheme("application-exit",
                            QIcon(":/icons/application-exit.png"));
}

QIcon Icons::about()
{
    return QIcon::fromTheme("help-about",
                            QIcon(":/icons/help-about.png"));
}

QIcon Icons::reportBug()
{
    return QIcon::fromTheme("tools-report-bug",
                            QIcon(":/icons/tools-report-bug.png"));
}

QIcon Icons::mellowPlayer()
{
    return QIcon(":/icons/mellowplayer.png");
}
