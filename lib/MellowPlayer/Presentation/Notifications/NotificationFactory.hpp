#pragma once

#include <MellowPlayer/Presentation/Notifications/Notification.hpp>

namespace MellowPlayer::Domain
{
    class Song;
}

namespace MellowPlayer::Presentation
{
    class NotificationFactory
    {
    public:
        Notification createSongNotification(const QString& serviceName, Domain::Song* song, const QString& albumArtUrl,
                                            bool resumed = false);
        Notification createPausedNotification(const QString& serviceName, const QString& serviceLogo);
    };
}
