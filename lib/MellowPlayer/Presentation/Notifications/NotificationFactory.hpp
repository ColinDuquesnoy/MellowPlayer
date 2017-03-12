#pragma once

#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationFactory {
public:
    UseCases::Notification createNewSong(const QString& serviceName, UseCases::Song* song, const QString& albumArtUrl);
    UseCases::Notification createPaused(const QString& serviceName, const QString& serviceLogo);
    UseCases::Notification createStopped(const QString& serviceName, const QString& serviceLogo);

private:
    QString getTitle(const QString& serviceName) const;
    UseCases::Notification createPlaybackNotif(const QString& serviceName, const QString& serviceLogo,
                                               const QString& message, UseCases::NotificationType type);
};

END_MELLOWPLAYER_NAMESPACE
