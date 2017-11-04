#pragma once

#include <MellowPlayer/Domain/Notifications/Notifications.hpp>

namespace MellowPlayer::Domain
{
    class Song;
}

namespace MellowPlayer::Presentation
{
    class NotificationFactory
    {
    public:
        Domain::Notification createSongNotification(const QString& serviceName, Domain::Song* song, const QString& albumArtUrl,
                                                         bool resumed = false);
        Domain::Notification createPausedNotification(const QString& serviceName, const QString& serviceLogo);
    };
}
