#include <MellowPlayer/Presentation/IconProvider.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

QIcon IconProvider::trayIcon()
{
    return windowIcon();
}

QIcon IconProvider::windowIcon()
{
    return QIcon::fromTheme("mellowplayer", QIcon("://MellowPlayer/Presentation/icons/mellowplayer.png"));
}

QIcon IconProvider::restoreWindow()
{
    return QIcon::fromTheme("view-restore", QIcon("://MellowPlayer/Presentation/icons/view-restore.png"));
}

QIcon IconProvider::play()
{
    return QIcon::fromTheme("media-playback-start", QIcon("://MellowPlayer/Presentation/icons/"
                                                          "media-playback-start.png"));
}

QIcon IconProvider::pause()
{
    return QIcon::fromTheme("media-playback-start", QIcon("://MellowPlayer/Presentation/icons/"
                                                          "media-playback-pause.png"));
}

QIcon IconProvider::next()
{
    return QIcon::fromTheme("media-seek-forward", QIcon("://MellowPlayer/Presentation/icons/"
                                                        "media-seek-forward.png"));
}

QIcon IconProvider::previous()
{
    return QIcon::fromTheme("media-seek-backward", QIcon("://MellowPlayer/Presentation/icons/"
                                                         "media-seek-backward.png"));
}

QIcon IconProvider::quit()
{
    return QIcon::fromTheme("application-exit", QIcon("://MellowPlayer/Presentation/icons/application-exit.png"));
}
