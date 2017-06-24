#pragma once

#include <MellowPlayer/Application/Notifications/Notifications.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Song)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationFactory {
public:
    Application::Notification createSongNotification(const QString& serviceName, Application::Song* song,
                                                  const QString& albumArtUrl, bool resumed=false);
    Application::Notification createPausedNotification(const QString& serviceName, const QString& serviceLogo);

private:
    Application::Notification createPlaybackNotif(const QString& serviceName, const QString& serviceLogo,
                                               const QString& message, Application::NotificationType type);
};

END_MELLOWPLAYER_NAMESPACE
