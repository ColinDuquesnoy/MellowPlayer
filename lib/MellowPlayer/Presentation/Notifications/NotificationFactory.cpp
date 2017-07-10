#include <MellowPlayer/Application/Player/Song.hpp>
#include <MellowPlayer/Presentation/Utils/IconProvider.hpp>
#include "NotificationFactory.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


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
