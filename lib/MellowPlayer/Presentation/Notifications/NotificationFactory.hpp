#pragma once

#include <MellowPlayer/Application/Notifications/Notifications.hpp>

namespace MellowPlayer::Application
{
    class Song;
}

namespace MellowPlayer::Presentation
{
    class NotificationFactory
    {
    public:
        Application::Notification createSongNotification(const QString &serviceName, Application::Song *song,
                                                         const QString &albumArtUrl, bool resumed = false);
        Application::Notification createPausedNotification(const QString &serviceName, const QString &serviceLogo);
    };
}
