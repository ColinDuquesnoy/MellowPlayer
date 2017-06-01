#include <catch.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)

TEST_CASE("PlayerTests", "[UnitTest]") {
    StreamingServicePluginMetadata metadata;
    auto settingsProviderMock = SettingsProviderMock::get();
    StreamingServicePlugin plugin(metadata);
    Player player(plugin);
    QSignalSpy runJavascriptRequestedSpy(&player, SIGNAL(runJavascriptRequested(const QString&)));

    SECTION("initialize test") {
        player.initialize();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(!runJavascriptRequestedSpy[0][0].toString().isEmpty());
    }

    SECTION("initialize test") {
        QSignalSpy updateRequestedSpy(&player, SIGNAL(updateRequested(const QString&)));
        player.refresh();
        REQUIRE(updateRequestedSpy.count() == 1);
        REQUIRE(!updateRequestedSpy[0][0].toString().isEmpty());
    }

    SECTION("setUpdateResults with empty QVariant") {
        player.setUpdateResults(QVariant());

        REQUIRE(player.getPosition() == 0);
        REQUIRE(player.getPlaybackStatus() == PlaybackStatus::Stopped);
        REQUIRE(!player.getCanSeek());
        REQUIRE(!player.getCanGoNext());
        REQUIRE(!player.getCanGoPrevious());
        REQUIRE(!player.getCanAddToFavorites());
        REQUIRE(player.getVolume() == 0);

        REQUIRE(player.getCurrentSong()->getTitle() == "");
        REQUIRE(player.getCurrentSong()->getAlbum() == "");
        REQUIRE(player.getCurrentSong()->getArtist() == "");
        REQUIRE(player.getCurrentSong()->getUniqueId() == "");
        REQUIRE(player.getCurrentSong()->getArtUrl() == "");
        REQUIRE(player.getCurrentSong()->getDuration() == 0);
        REQUIRE(!player.getCurrentSong()->getIsFavorite());
    }

    SECTION("setUpdateResults with valid QVariant") {
        QVariantMap map;
        map["position"] = 1.0;
        map["playbackStatus"] = static_cast<int>(PlaybackStatus::Playing);
        map["canSeek"] = true;
        map["canGoNext"] = true;
        map["canGoPrevious"] = true;
        map["canAddToFavorites"] = true;
        map["songId"] = "010203";
        map["songTitle"] = "songTitle";
        map["artistName"] = "artistName";
        map["albumTitle"] = "albumTitle";
        map["artUrl"] = "artUrl";
        map["isFavorite"] = true;
        map["volume"] = 1.0;
        player.setUpdateResults(QVariant::fromValue(map));
        map["duration"] = 350.0;
        player.setUpdateResults(QVariant::fromValue(map));

        REQUIRE(player.getPosition() == 1.0);
        REQUIRE(player.getPlaybackStatus() == PlaybackStatus::Playing);
        REQUIRE(player.getCanSeek());
        REQUIRE(player.getCanGoNext());
        REQUIRE(player.getCanGoPrevious());
        REQUIRE(player.getCanAddToFavorites());
        REQUIRE(player.getVolume() == 1.0);

        REQUIRE(player.getCurrentSong()->getTitle() == "songTitle");
        REQUIRE(player.getCurrentSong()->getAlbum() == "albumTitle");
        REQUIRE(player.getCurrentSong()->getArtist() == "artistName");
        REQUIRE(player.getCurrentSong()->getUniqueId() == "010203");
        REQUIRE(player.getCurrentSong()->getArtUrl() == "artUrl");
        REQUIRE(player.getCurrentSong()->getDuration() == 350.0);
        REQUIRE(player.getCurrentSong()->getIsFavorite());
    }

    SECTION("togglePlayPause") {
        player.togglePlayPause();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "play();");
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.togglePlayPause();
        REQUIRE(runJavascriptRequestedSpy.count() == 2);
        REQUIRE(runJavascriptRequestedSpy[1][0].toString() == "pause();");
    }

    SECTION("play") {
        player.play();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "play();");
    }

    SECTION("pause") {
        player.pause();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "pause();");
    }

    SECTION("next") {
        player.next();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "goNext();");
    }

    SECTION("previous") {
        player.previous();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "goPrevious();");
    }

    SECTION("seekToPosition") {
        player.seekToPosition(150.3);
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString().toStdString() == "seekToPosition(150.3);");
    }

    SECTION("setVolume") {
        player.setVolume(0.67);
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString().toStdString() == "setVolume(0.67);");
    }

    SECTION("toggleFavoriteSong null song") {
        player.toggleFavoriteSong();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
        player.toggleFavoriteSong();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
    }

    SECTION("toggleFavoriteSong valid song") {
        QVariantMap map;
        map["position"] = 1.0;
        map["playbackStatus"] = static_cast<int>(PlaybackStatus::Playing);
        map["canSeek"] = true;
        map["canGoNext"] = true;
        map["canGoPrevious"] = true;
        map["canAddToFavorites"] = true;
        map["songId"] = "010203";
        map["songTitle"] = "songTitle";
        map["artistName"] = "artistName";
        map["albumTitle"] = "albumTitle";
        map["artUrl"] = "artUrl";
        map["isFavorite"] = false;
        map["volume"] = 1.0;
        player.setUpdateResults(QVariant::fromValue(map));

        player.toggleFavoriteSong();
        player.getCurrentSong()->setIsFavorite(true);
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString().toStdString() == "addToFavorites();");

        player.toggleFavoriteSong();
        player.getCurrentSong()->setIsFavorite(false);
        REQUIRE(runJavascriptRequestedSpy.count() == 2);
        REQUIRE(runJavascriptRequestedSpy[1][0].toString().toStdString() == "removeFromFavorites();");
    }

    SECTION("suspend when not playing") {
        player.setPlaybackStatus(PlaybackStatus::Paused);
        player.suspend();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
    }

    SECTION("suspend when playing") {
        player.play();
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.suspend();
        REQUIRE(player.getPlaybackStatus() == PlaybackStatus::Paused);
    }

    SECTION("resume when not playing") {
        player.setPlaybackStatus(PlaybackStatus::Paused);
        player.suspend();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
        player.resume();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
    }

    SECTION("resume when playing") {
        player.play();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.suspend();
        REQUIRE(runJavascriptRequestedSpy.count() == 2);
        REQUIRE(player.getPlaybackStatus() == PlaybackStatus::Paused);
        player.resume();
        REQUIRE(runJavascriptRequestedSpy.count() == 3);

    }
}
