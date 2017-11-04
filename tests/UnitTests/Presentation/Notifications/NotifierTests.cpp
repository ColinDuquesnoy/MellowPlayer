#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifier.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch.hpp>
#include <fakeit.hpp>

using namespace fakeit;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

TEST_CASE("NotifierTests", "[UnitTest]")
{
    MellowPlayer::Tests::DependencyPool pool;

    Settings& settings = pool.getSettings();
    Notifier& notificationService = pool.getNotifier();
    Mock<LocalAlbumArt> localAlbumArtServiceSpy(pool.getLocalAlbumArt());
    Mock<IPlayer> playerSpy(pool.getCurrentPlayer());
    Mock<INotificationPresenter>& notificationPresenterMock = pool.getNotificationPresenterMock();

    Setting& playNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
    playNotifEnabled.setValue(true);
    Setting& pausedNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
    pausedNotifEnabled.setValue(true);

    Song validSong("uniqueId", "songTitle", "artistName", "album", "artUrl", 50, false);
    REQUIRE(validSong.isValid());
    Song invalidSong("", "", "", "", "", 50, false);
    REQUIRE(!invalidSong.isValid());

    When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Playing);
    When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(true);
    When(Method(playerSpy, currentSong)).AlwaysReturn(&validSong);

    SECTION("initialize")
    {
        notificationService.initialize();
        Verify(Method(notificationPresenterMock, initialize)).Once();
    }

    SECTION("display allowed notification")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(notificationService.display(notif));
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display disallowed notification")
    {
        playNotifEnabled.setValue(false);
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(!notificationService.display(notif));
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("display current song changed notification if "
            "song is valid and "
            "player is playing and "
            "art is ready")
    {
        notificationService.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display current song changed notification if player is not "
            "playing")
    {
        When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Paused);
        notificationService.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("don't display current song changed notification if art is not ready")
    {
        When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(false);
        notificationService.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();

        SECTION("display current song changed notification when album art is ready")
        {
            When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(true);
            notificationService.onCurrentSongUrlChanged();
            Verify(Method(notificationPresenterMock, display)).Once();
        }
    }

    SECTION("don't display current song changed notification if current song is "
            "invalid")
    {
        notificationService.onCurrentSongChanged(&invalidSong);
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("display current song changed notification when playback status "
            "changed to Playing")
    {
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display paused notification when playback status changed to Paused")
    {
        When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Paused);
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display paused notification when playback status changed to "
            "Stopped")
    {
        When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Stopped);
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Never();
    }
}
