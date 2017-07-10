#include <catch.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifier.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <Mocks/LocalAlbumArtMock.hpp>
#include "DI.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

TEST_CASE("NotifierTests", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    LocalAlbumArt& service = injector.create<LocalAlbumArt&>();
    Mock<LocalAlbumArt> localAlbumArtServiceSpy(service);
    CurrentPlayer& player = injector.create<CurrentPlayer&>();
    Mock<CurrentPlayer> playerSpy(player);
    StreamingServicesController& streamingServices = injector.create<StreamingServicesController&>();
    Settings& settings = injector.create<Settings&>();
    Notifier notificationService(playerSpy.get(), localAlbumArtServiceSpy.get(),
                                            notificationPresenterMock.get(), streamingServices, settings);
    NotificationPresenterMock::Reset(notificationPresenterMock);

    Setting& playNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
    playNotifEnabled.setValue(true);
    Setting& pausedNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
    pausedNotifEnabled.setValue(true);


    Song validSong("uniqueId", "songTitle", "artistName", "album", "artUrl", 50, false);
    REQUIRE(validSong.isValid());
    Song invalidSong("", "", "", "", "", 50, false);
    REQUIRE(!invalidSong.isValid());

    When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(PlaybackStatus::Playing);
    When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(true);
    When(Method(playerSpy, getCurrentSong)).AlwaysReturn(&validSong);


    SECTION("initialize") {
        notificationService.initialize();
        Verify(Method(notificationPresenterMock, initialize)).Once();
    }

    SECTION("display allowed notification") {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(notificationService.display(notif));
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display disallowed notification") {
        playNotifEnabled.setValue(false);
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(!notificationService.display(notif));
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("display current song changed notification if "
                    "song is valid and "
                    "player is playing and "
                    "art is ready") {
        notificationService.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display current song changed notification if player is not playing") {
        When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(PlaybackStatus::Paused);
        notificationService.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("don't display current song changed notification if art is not ready") {
        When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(false);
        notificationService.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();

        SECTION("display current song changed notification when album art is ready") {
            When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(true);
            notificationService.onCurrentSongUrlChanged();
            Verify(Method(notificationPresenterMock, display)).Once();
        }
    }

    SECTION("don't display current song changed notification if current song is invalid") {
        notificationService.onCurrentSongChanged(&invalidSong);
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("display current song changed notification when playback status changed to Playing")  {
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display paused notification when playback status changed to Paused")  {
        When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(PlaybackStatus::Paused);
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display paused notification when playback status changed to Stopped")  {
        When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(PlaybackStatus::Stopped);
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Never();
    }
}
