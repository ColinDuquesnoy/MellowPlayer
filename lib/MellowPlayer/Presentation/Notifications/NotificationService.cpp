#include "NotificationService.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


NotificationService::NotificationService(IPlayer& player,
                                         LocalAlbumArtService& localAlbumArtService,
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
    connect(&localAlbumArtService, &LocalAlbumArtService::urlChanged,
            this, &NotificationService::onCurrentSongUrlChanged);
    presenter.initialize();
}

void NotificationService::display(const Notification& notification) {
    LOG_TRACE(logger, "display");
    if (!applicationSettings.isNotificationTypeEnabled(notification.type)) {
        LOG_DEBUG(logger, "notification disabled: " + notification.toString());
        return;
    }
    LOG_INFO(logger, "display notification: " + notification.toString());
    presenter.display(notification);
}

void NotificationService::onCurrentSongChanged(Song* song) {
    LOG_TRACE(logger, "onCurrentSongChanged");
    showNewSongNotification(song, localAlbumArtService.getUrl());
}

void NotificationService::onPlaybackStatusChanged() {
    LOG_TRACE(logger, "onPlaybackStatusChanged");
    switch (player.getPlaybackStatus()) {
        case IPlayer::PlaybackStatus::Paused:
            display(notificationFactory.createPaused(getCurrentServiceName(), getCurrentServiceLogo()));
            break;
        case IPlayer::PlaybackStatus::Playing:
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
    if (song != nullptr && song->isValid() && isPlaying() && isAlbumArtReady(song))
        display(notificationFactory.createNewSong(getCurrentServiceName(), song, localAlbumArtUrl));
}

bool NotificationService::isAlbumArtReady(const Song* song) const {
    return localAlbumArtService.getUrl().contains(song->getUniqueId()) &&
           QFileInfo(localAlbumArtService.getUrl()).exists();
}

bool NotificationService::isPlaying() const {
    return player.getPlaybackStatus() == IPlayer::PlaybackStatus::Playing;
}

const QString NotificationService::getCurrentServiceName() const {
    return pluginManager.getCurrent()->getName();
}

const QString NotificationService::getCurrentServiceLogo() const {
    return pluginManager.getCurrent()->getLogo();
}
