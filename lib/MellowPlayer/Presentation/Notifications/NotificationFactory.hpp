#pragma once

#include <MellowPlayer/Entities/Notifications.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationFactory {
public:
    Entities::Notification createSongNotification(const QString& serviceName, Entities::Song* song,
                                                  const QString& albumArtUrl, bool resumed=false);
    Entities::Notification createPausedNotification(const QString& serviceName, const QString& serviceLogo);

private:
    Entities::Notification createPlaybackNotif(const QString& serviceName, const QString& serviceLogo,
                                               const QString& message, Entities::NotificationType type);
};

END_MELLOWPLAYER_NAMESPACE
