#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Presentation/IconProvider.hpp>
#include "NotificationFactory.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


Notification NotificationFactory::createSongNotification(
        const QString& serviceName, Song* song, const QString& albumArtUrl, bool resumed) {
    return Notification { serviceName, song->toString(), albumArtUrl,
                          resumed ? NotificationType::Resumed : NotificationType::NewSong };
}

Notification NotificationFactory::createPausedNotification(const QString& serviceName, const QString& serviceLogo) {
    QString sanitizedServiceLogo = serviceLogo;
    sanitizedServiceLogo = sanitizedServiceLogo.replace("file://", "");
    return Notification { serviceName, "Paused", sanitizedServiceLogo, NotificationType::Paused };
}
