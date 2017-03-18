#pragma once

#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationFactory {
public:
    UseCases::Notification createSongNotification(const QString& serviceName, UseCases::Song* song,
                                                  const QString& albumArtUrl);
    UseCases::Notification createPausedNotification(const QString& serviceName, const QString& serviceLogo);

private:
    UseCases::Notification createPlaybackNotif(const QString& serviceName, const QString& serviceLogo,
                                               const QString& message, UseCases::NotificationType type);
};

END_MELLOWPLAYER_NAMESPACE
