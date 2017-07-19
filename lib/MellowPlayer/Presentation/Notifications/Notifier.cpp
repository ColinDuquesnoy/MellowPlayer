#include <MellowPlayer/Application/Player/Song.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include "Notifier.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


Notifier::Notifier(IPlayer& player,
                   ILocalAlbumArt& localAlbumArtService,
                   INotificationPresenter& presenter,
                   StreamingServicesController& streamingServices,
                   Settings& settings) :
        logger(LoggingManager::instance().getLogger("Notifier")),
        player(player),
        localAlbumArtService(localAlbumArtService),
        presenter(presenter),
        streamingServices(streamingServices),
        settings(settings) {
}

void Notifier::initialize() {
    LOG_TRACE(logger, "initialize");
    connect(&player, &IPlayer::currentSongChanged,
            this, &Notifier::onCurrentSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged,
            this, &Notifier::onPlaybackStatusChanged);
    connect(&localAlbumArtService, &ILocalAlbumArt::urlChanged,
            this, &Notifier::onCurrentSongUrlChanged);
    presenter.initialize();
}

bool Notifier::display(const Notification& notification) {
    LOG_TRACE(logger, "display");
    if (!isNotificationTypeEnabled(notification.type) || previousNotif == notification) {
        LOG_DEBUG(logger, "notification disabled: " + notification.toString());
        return false;
    }
    LOG_DEBUG(logger, "display notification: " + notification.toString());
    presenter.display(notification);
    return true;
}

void Notifier::onCurrentSongChanged(Song* song) {
    LOG_TRACE(logger, "onCurrentSongChanged");
    showSongNotification(song, localAlbumArtService.getUrl());
}

void Notifier::onPlaybackStatusChanged() {
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

void Notifier::onCurrentSongUrlChanged() {
    LOG_TRACE(logger, "onCurrentSongUrlChanged");
    showSongNotification(player.getCurrentSong(), localAlbumArtService.getUrl());
}

void Notifier::showSongNotification(Song* song, const QString& localAlbumArtUrl) {
    LOG_TRACE(logger, "showSongNotification");
    if (song != nullptr && song->isValid() && isPlaying() && localAlbumArtService.isSongArtReady(*song)) {
        bool resume = song->getUniqueId() == previousSongId;
        previousSongId = song->getUniqueId();
        display(notificationFactory.createSongNotification(getCurrentServiceName(), song, localAlbumArtUrl, resume));
    }
}

bool Notifier::isPlaying() const {
    return player.getPlaybackStatus() == PlaybackStatus::Playing;
}

const QString Notifier::getCurrentServiceName() const {
    auto currentService = streamingServices.getCurrent();
    return currentService != nullptr ? currentService->getName() : "";
}

const QString Notifier::getCurrentServiceLogo() const {
    auto currentService = streamingServices.getCurrent();
    return currentService != nullptr ? currentService->getLogo() : "";
}

bool Notifier::isNotificationTypeEnabled(NotificationType type) const {
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
