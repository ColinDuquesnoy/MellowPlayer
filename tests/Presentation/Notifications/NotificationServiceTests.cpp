#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <Mocks/LocalAlbumArtServiceMock.hpp>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("NotificationServiceTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    LocalAlbumArtService& service = injector.create<LocalAlbumArtService&>();
    Mock<LocalAlbumArtService> localAlbumArtServiceSpy(service);
    PlayerProxy& player = injector.create<PlayerProxy&>();
    Mock<PlayerProxy> playerSpy(player);
    INotificationPresenter& notificationPresenter = injector.create<INotificationPresenter&>();
    PluginManager& pluginManager = injector.create<PluginManager&>();
    IApplicationSettings& appSettings = injector.create<IApplicationSettings&>();
    NotificationService notificationService(playerSpy.get(), localAlbumArtServiceSpy.get(), notificationPresenter,
                                            pluginManager, appSettings);
    NotificationPresenterMock::Reset(notificationPresenterMock);

    appSettings.enableNotificationType(NotificationType::NewSong, true);
    REQUIRE(appSettings.isNotificationTypeEnabled(NotificationType::NewSong));

    Song validSong("uniqueId", "songTitle", "artistName", "album", "artUrl", 50, false);
    REQUIRE(validSong.isValid());
    Song invalidSong("", "", "", "", "", 50, false);
    REQUIRE(!invalidSong.isValid());

    When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(IPlayer::PlaybackStatus::Playing);
    When(Method(localAlbumArtServiceSpy, isSongArtReady)).AlwaysReturn(true);
    When(Method(playerSpy, getCurrentSong)).AlwaysReturn(&validSong);


    SECTION("initialize") {
        notificationService.initialize();
        Verify(Method(notificationPresenterMock, initialize)).Once();
    }

    SECTION("display allowed notification") {
        Notification notif{"title", "message", QIcon(), NotificationType::NewSong};
        REQUIRE(notificationService.display(notif));
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display disallowed notification") {
        appSettings.enableNotificationType(NotificationType::NewSong, false);
        Notification notif{"title", "message", QIcon(), NotificationType::NewSong};
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
        When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(IPlayer::PlaybackStatus::Paused);
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
        When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(IPlayer::PlaybackStatus::Paused);
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display paused notification when playback status changed to Stopped")  {
        When(Method(playerSpy, getPlaybackStatus)).AlwaysReturn(IPlayer::PlaybackStatus::Stopped);
        notificationService.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Never();
    }
}
