#include <MellowPlayer/Presentation/Notifications/NotificationFactory.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Presentation/IconProvider.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

static QString PAUSED = QObject::tr("Paused");

Notification NotificationFactory::createSongNotification(const QString& serviceName, Song* song, const QString& albumArtUrl, bool resumed)
{
    return Notification{serviceName, song->toString(), albumArtUrl, resumed ? NotificationType::Resumed : NotificationType::NewSong};
}

Notification NotificationFactory::createPausedNotification(const QString& serviceName, const QString& serviceLogo)
{
    QString sanitizedServiceLogo = serviceLogo;
    sanitizedServiceLogo = sanitizedServiceLogo.replace("file://", "");
    return Notification{serviceName, PAUSED, sanitizedServiceLogo, NotificationType::Paused};
}
