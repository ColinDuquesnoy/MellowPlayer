
#include <MellowPlayer/UseCases/Interfaces/IApplicationSettings.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Player/IPlayer.hpp>
#include <MellowPlayer/UseCases/Player/Song.hpp>
#include <MellowPlayer/UseCases/Plugin/Plugin.hpp>
#include <MellowPlayer/UseCases/Plugin/PluginManager.hpp>
#include <MellowPlayer/UseCases/Notifications/INotificationPresenter.hpp>
#include <MellowPlayer/UseCases/Services/ILocalAlbumArtService.hpp>

#include "NotificationService.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


NotificationService::NotificationService(IPlayer& player,
                                         ILocalAlbumArtService& localAlbumArtService,
                                         INotificationPresenter& presenter,
                                         PluginManager& pluginManager,
                                         IApplicationSettings& applicationSettings) :
        logger(LoggingManager::instance().getLogger("NotificationService")),
        player(player),
        localAlbumArtService(localAlbumArtService),
        presenter(presenter),
        pluginManager(pluginManager),
        applicationSettings(applicationSettings) {
}

void NotificationService::initialize() {
    LOG_TRACE(logger, "initialize");
    connect(&player, &IPlayer::currentSongChanged,
            this, &NotificationService::onCurrentSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged,
            this, &NotificationService::onPlaybackStatusChanged);
    connect(&localAlbumArtService, &ILocalAlbumArtService::urlChanged,
            this, &NotificationService::onCurrentSongUrlChanged);
    presenter.initialize();
}

bool NotificationService::display(const Notification& notification) {
    LOG_TRACE(logger, "display");
    if (!applicationSettings.isNotificationTypeEnabled(notification.type) || previousNotif == notification) {
        LOG_DEBUG(logger, "notification disabled: " + notification.toString());
        return false;
    }
    LOG_INFO(logger, "display notification: " + notification.toString());
    presenter.display(notification);
    return true;
}

void NotificationService::onCurrentSongChanged(Song* song) {
    LOG_TRACE(logger, "onCurrentSongChanged");
    showNewSongNotification(song, localAlbumArtService.getUrl());
}

void NotificationService::onPlaybackStatusChanged() {
    LOG_TRACE(logger, "onPlaybackStatusChanged");
    switch (player.getPlaybackStatus()) {
        case PlaybackStatus::Paused:
            display(notificationFactory.createPausedNotification(getCurrentServiceName(), getCurrentServiceLogo()));
            break;
        case PlaybackStatus::Playing:
            showNewSongNotification(player.getCurrentSong(), localAlbumArtService.getUrl());
            break;
        default:
            break;
    }
}

void NotificationService::onCurrentSongUrlChanged() {
    LOG_TRACE(logger, "onCurrentSongUrlChanged");
    showNewSongNotification(player.getCurrentSong(), localAlbumArtService.getUrl());
}

void NotificationService::showNewSongNotification(Song* song, const QString& localAlbumArtUrl) {
    LOG_TRACE(logger, "showNewSongNotification");
    if (song != nullptr && song->isValid() && isPlaying() && localAlbumArtService.isSongArtReady(*song))
        display(notificationFactory.createSongNotification(getCurrentServiceName(), song, localAlbumArtUrl));
}

bool NotificationService::isPlaying() const {
    return player.getPlaybackStatus() == PlaybackStatus::Playing;
}

const QString NotificationService::getCurrentServiceName() const {
    auto currentPlugin = pluginManager.getCurrent();
    return currentPlugin != nullptr ? currentPlugin->getName() : "";
}

const QString NotificationService::getCurrentServiceLogo() const {
    auto currentPlugin = pluginManager.getCurrent();
    return currentPlugin != nullptr ? currentPlugin->getLogo() : "";
}
