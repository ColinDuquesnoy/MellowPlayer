#include <MellowPlayer/Presentation/Notifications/Notifications.hpp>
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

Notifications::Notifications(IPlayer& player,
                             ILocalAlbumArt& localAlbumArtService,
                             INotificationPresenter& presenter,
                             StreamingServices& streamingServices,
                             Settings& settings)
        : logger_(Loggers::logger("Notifier")),
          player_(player),
          localAlbumArt_(localAlbumArtService),
          presenter_(presenter),
          streamingServices_(streamingServices),
          settings_(settings)
{
}

void Notifications::initialize()
{
    LOG_TRACE(logger_, "initialize");
    connect(&player_, &IPlayer::currentSongChanged, this, &Notifications::onCurrentSongChanged);
    connect(&player_, &IPlayer::playbackStatusChanged, this, &Notifications::onPlaybackStatusChanged);
    connect(&localAlbumArt_, &ILocalAlbumArt::urlChanged, this, &Notifications::onCurrentSongUrlChanged);
    presenter_.initialize();
}

bool Notifications::display(const Notification& notification)
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

void Notifications::onCurrentSongChanged(Song* song)
{
    LOG_TRACE(logger_, "onCurrentSongChanged");
    showSongNotification(song, localAlbumArt_.url());
}

void Notifications::onPlaybackStatusChanged()
{
    LOG_TRACE(logger_, "onPlaybackStatusChanged");
    switch (player_.playbackStatus()) {
        case PlaybackStatus::Paused:
            display(notificationFactory_.createPausedNotification(currentServiceName(), currentServiceLogo()));
            break;
        case PlaybackStatus::Playing:
            showSongNotification(player_.currentSong(), localAlbumArt_.url());
            break;
        default:
            break;
    }
}

void Notifications::onCurrentSongUrlChanged()
{
    LOG_TRACE(logger_, "onCurrentSongUrlChanged");
    showSongNotification(player_.currentSong(), localAlbumArt_.url());
}

void Notifications::showSongNotification(Song* song, const QString& localAlbumArtUrl)
{
    LOG_TRACE(logger_, "showSongNotification");
    if (song == nullptr)
        return;

    bool isReady = song->isValid();
    isReady &= localAlbumArt_.isReady(*song);
    isReady &= isPlaying();
    isReady &= localAlbumArt_.isReady(*song);
    if (isReady) {
        bool resume = song->uniqueId() == previousSongId_;
        previousSongId_ = song->uniqueId();
        display(notificationFactory_.createSongNotification(currentServiceName(), song, localAlbumArtUrl, resume));
    }
}

bool Notifications::isPlaying() const
{
    return player_.playbackStatus() == PlaybackStatus::Playing;
}

const QString Notifications::currentServiceName() const
{
    auto currentService = streamingServices_.current();
    return currentService != nullptr ? currentService->name() : "";
}

const QString Notifications::currentServiceLogo() const
{
    auto currentService = streamingServices_.current();
    return currentService != nullptr ? currentService->logo() : "";
}

bool Notifications::isNotificationTypeEnabled(NotificationType type) const
{
    auto check = [](const Setting& setting) { return setting.isEnabled() && setting.value().toBool(); };

    bool isEnabled = false;

    auto settingKey = player_.serviceName() + "/notificationsEnabled";
    auto serviceNotificationsEnabled = settings_.store().value(settingKey, true).toBool();

    switch (type) {
        case NotificationType::Paused: {
            const Setting& setting = settings_.get(SettingKey::NOTIFICATIONS_PAUSED);
            isEnabled = check(setting) && serviceNotificationsEnabled;
            break;
        }
        case NotificationType::NewSong: {
            const Setting& setting = settings_.get(SettingKey::NOTIFICATIONS_NEW_SONG);
            isEnabled = check(setting)  && serviceNotificationsEnabled;
            break;
        }
        case NotificationType::Resumed: {
            const Setting& setting = settings_.get(SettingKey::NOTIFICATIONS_RESUMED);
            isEnabled = check(setting)  && serviceNotificationsEnabled;
            break;
        }
    }

    return isEnabled;
}
