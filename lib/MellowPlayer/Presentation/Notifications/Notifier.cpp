#include "Notifier.hpp"
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Notifications/INotificationPresenter.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

Notifier::Notifier(IPlayer& player, ILocalAlbumArt& localAlbumArtService, INotificationPresenter& presenter,
                   StreamingServicesController& streamingServices, Settings& settings)
        : logger_(LoggingManager::logger("Notifier")),
          player_(player),
          localAlbumArtService_(localAlbumArtService),
          presenter_(presenter),
          streamingServices_(streamingServices),
          settings_(settings)
{
}

void Notifier::initialize()
{
    LOG_TRACE(logger_, "initialize");
    connect(&player_, &IPlayer::currentSongChanged, this, &Notifier::onCurrentSongChanged);
    connect(&player_, &IPlayer::playbackStatusChanged, this, &Notifier::onPlaybackStatusChanged);
    connect(&localAlbumArtService_, &ILocalAlbumArt::urlChanged, this, &Notifier::onCurrentSongUrlChanged);
    presenter_.initialize();
}

bool Notifier::display(const Notification& notification)
{
    LOG_TRACE(logger_, "display");
    if (!isNotificationTypeEnabled(notification.type) || previousNotif_ == notification) {
        LOG_DEBUG(logger_, "notification disabled: " + notification.toString());
        return false;
    }
    LOG_DEBUG(logger_, "display notification: " + notification.toString());
    presenter_.display(notification);
    return true;
}

void Notifier::onCurrentSongChanged(Song* song)
{
    LOG_TRACE(logger_, "onCurrentSongChanged");
    showSongNotification(song, localAlbumArtService_.url());
}

void Notifier::onPlaybackStatusChanged()
{
    LOG_TRACE(logger_, "onPlaybackStatusChanged");
    switch (player_.playbackStatus()) {
        case PlaybackStatus::Paused:
            display(notificationFactory_.createPausedNotification(currentServiceName(), currentServiceLogo()));
            break;
        case PlaybackStatus::Playing:
            showSongNotification(player_.currentSong(), localAlbumArtService_.url());
            break;
        default:
            break;
    }
}

void Notifier::onCurrentSongUrlChanged()
{
    LOG_TRACE(logger_, "onCurrentSongUrlChanged");
    showSongNotification(player_.currentSong(), localAlbumArtService_.url());
}

void Notifier::showSongNotification(Song* song, const QString& localAlbumArtUrl)
{
    LOG_TRACE(logger_, "showSongNotification");
    if (song != nullptr && song->isValid() && isPlaying() && localAlbumArtService_.isSongArtReady(*song)) {
        bool resume = song->uniqueId() == previousSongId_;
        previousSongId_ = song->uniqueId();
        display(notificationFactory_.createSongNotification(currentServiceName(), song, localAlbumArtUrl, resume));
    }
}

bool Notifier::isPlaying() const
{
    return player_.playbackStatus() == PlaybackStatus::Playing;
}

const QString Notifier::currentServiceName() const
{
    auto currentService = streamingServices_.current();
    return currentService != nullptr ? currentService->name() : "";
}

const QString Notifier::currentServiceLogo() const
{
    auto currentService = streamingServices_.current();
    return currentService != nullptr ? currentService->logo() : "";
}

bool Notifier::isNotificationTypeEnabled(NotificationType type) const
{
    auto check = [](const Setting& setting) { return setting.isEnabled() && setting.value().toBool(); };

    bool isEnabled = false;

    switch (type) {
        case NotificationType::Paused: {
            const Setting& setting = settings_.get(SettingKey::NOTIFICATIONS_PAUSED);
            isEnabled = check(setting);
            break;
        }
        case NotificationType::NewSong: {
            const Setting& setting = settings_.get(SettingKey::NOTIFICATIONS_NEW_SONG);
            isEnabled = check(setting);
            break;
        }
        case NotificationType::Resumed: {
            const Setting& setting = settings_.get(SettingKey::NOTIFICATIONS_RESUMED);
            isEnabled = check(setting);
            break;
        }
    }

    return isEnabled;
}
