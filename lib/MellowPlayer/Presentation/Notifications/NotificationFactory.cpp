#include "../IconProvider.hpp"
#include "NotificationFactory.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


Notification NotificationFactory::createNewSong(const QString& serviceName, Song* song, const QString& albumArtUrl) {
    return Notification {
            getTitle(serviceName),
            song->toString(),
            QIcon(albumArtUrl),
            NotificationType::NewSong
    };
}

Notification NotificationFactory::createPaused(const QString& serviceName, const QString& serviceLogo) {
    return createPlaybackNotif(serviceName, serviceLogo, "Paused", NotificationType::Paused);
}

Notification NotificationFactory::createStopped(const QString& serviceName, const QString& serviceLogo) {
    return createPlaybackNotif(serviceName, serviceLogo, "Stopped", NotificationType::Stopped);
}

QString NotificationFactory::getTitle(const QString& serviceName) const {
    return serviceName;
}

Notification NotificationFactory::createPlaybackNotif(const QString& serviceName, const QString& serviceLogo,
                                                      const QString& message, NotificationType type) {
    QString sanitizedServiceLogo = serviceLogo;
    sanitizedServiceLogo = sanitizedServiceLogo.replace("file://", "");
    return Notification { getTitle(serviceName), message, QIcon(sanitizedServiceLogo), type };
}
