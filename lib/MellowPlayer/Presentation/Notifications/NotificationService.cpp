#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Interfaces/ILocalAlbumArtService.hpp>
#include <MellowPlayer/Application/Interfaces/INotificationPresenter.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include "NotificationService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


NotificationService::NotificationService(IPlayer& player,
                                         ILocalAlbumArtService& localAlbumArtService,
                                         INotificationPresenter& presenter,
                                         StreamingServicePluginService& pluginService,
                                         Settings& settings) :
        logger(LoggingManager::instance().getLogger("NotificationService")),
        player(player),
        localAlbumArtService(localAlbumArtService),
        presenter(presenter),
        pluginService(pluginService),
        settings(settings) {
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
    if (!isNotificationTypeEnabled(notification.type) || previousNotif == notification) {
        LOG_DEBUG(logger, "notification disabled: " + notification.toString());
        return false;
    }
    LOG_INFO(logger, "display notification: " + notification.toString());
    presenter.display(notification);
    return true;
}

void NotificationService::onCurrentSongChanged(Song* song) {
    LOG_TRACE(logger, "onCurrentSongChanged");
    showSongNotification(song, localAlbumArtService.getUrl());
}

void NotificationService::onPlaybackStatusChanged() {
    LOG_TRACE(logger, "onPlaybackStatusChanged");
    switch (player.getPlaybackStatus()) {
        case PlaybackStatus::Paused:
            display(notificationFactory.createPausedNotification(getCurrentServiceName(), getCurrentServiceLogo()));
            break;
        case PlaybackStatus::Playing:
            showSongNotification(player.getCurrentSong(), localAlbumArtService.getUrl());
            break;
        default:
            break;
    }
}

void NotificationService::onCurrentSongUrlChanged() {
    LOG_TRACE(logger, "onCurrentSongUrlChanged");
    showSongNotification(player.getCurrentSong(), localAlbumArtService.getUrl());
}

void NotificationService::showSongNotification(Song* song, const QString& localAlbumArtUrl) {
    LOG_TRACE(logger, "showSongNotification");
    if (song != nullptr && song->isValid() && isPlaying() && localAlbumArtService.isSongArtReady(*song)) {
        bool resume = song->getUniqueId() == previousSongId;
        previousSongId = song->getUniqueId();
        display(notificationFactory.createSongNotification(getCurrentServiceName(), song, localAlbumArtUrl, resume));
    }
}

bool NotificationService::isPlaying() const {
    return player.getPlaybackStatus() == PlaybackStatus::Playing;
}

const QString NotificationService::getCurrentServiceName() const {
    auto currentPlugin = pluginService.getCurrent();
    return currentPlugin != nullptr ? currentPlugin->getName() : "";
}

const QString NotificationService::getCurrentServiceLogo() const {
    auto currentPlugin = pluginService.getCurrent();
    return currentPlugin != nullptr ? currentPlugin->getLogo() : "";
}

bool NotificationService::isNotificationTypeEnabled(NotificationType type) const {
    auto check = [](const Setting& setting) {
        return setting.isEnabled() && setting.getValue().toBool();
    };

    switch (type) {
        case NotificationType::NewVersionAvailable: {
            const Setting& setting = settings.get(SettingKey::NOTIFICATIONS_NEW_VERSION);
            return check(setting);
        }
        case NotificationType::Paused: {
            const Setting& setting = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
            return check(setting);
        }
        case NotificationType::NewSong: {
            const Setting& setting = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
            return check(setting);
        }
        case NotificationType::Resumed: {
            const Setting& setting = settings.get(SettingKey::NOTIFICATIONS_RESUMED);
            return check(setting);
        }
    }

    return false;
}
