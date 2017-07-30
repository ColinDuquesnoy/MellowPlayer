#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Player/Song.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <Mocks/SettingsProviderMock.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Application;

TEST_CASE("PlayerTests", "[UnitTest]")
{
    StreamingServiceMetadata metadata;
    auto settingsProviderMock = SettingsProviderMock::get();
    StreamingService service(metadata);
    Player player(service);
    QSignalSpy runJavascriptRequestedSpy(&player, SIGNAL(runJavascriptRequested(const QString&)));

    SECTION("start test")
    {
        REQUIRE(!player.isRunning());
        player.start();
        REQUIRE(player.isRunning());
        player.stop();
        REQUIRE(!player.isRunning());
    }

    SECTION("loadPlugin emit runJavascriptRequested")
    {
        player.loadPlugin();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(!runJavascriptRequestedSpy[0][0].toString().isEmpty());
    }

    SECTION("refresh test")
    {
        QSignalSpy updateRequestedSpy(&player, SIGNAL(updateRequested(const QString&)));
        player.refresh();
        REQUIRE(updateRequestedSpy.count() == 1);
        REQUIRE(!updateRequestedSpy[0][0].toString().isEmpty());
    }

    SECTION("setUpdateResults with empty QVariant")
    {
        player.setUpdateResults(QVariant());

        REQUIRE(player.position() == 0);
        REQUIRE(player.playbackStatus() == PlaybackStatus::Stopped);
        REQUIRE(!player.canSeek());
        REQUIRE(!player.canGoNext());
        REQUIRE(!player.canGoPrevious());
        REQUIRE(!player.canAddToFavorites());
        REQUIRE(player.volume() == 0);

        REQUIRE(player.currentSong()->title() == "");
        REQUIRE(player.currentSong()->album() == "");
        REQUIRE(player.currentSong()->artist() == "");
        REQUIRE(player.currentSong()->uniqueId() == "");
        REQUIRE(player.currentSong()->artUrl() == "");
        REQUIRE(player.currentSong()->duration() == 0);
        REQUIRE(!player.currentSong()->isFavorite());
    }

    SECTION("setUpdateResults with valid QVariant")
    {
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

        REQUIRE(player.position() == 1.0);
        REQUIRE(player.playbackStatus() == PlaybackStatus::Playing);
        REQUIRE(player.canSeek());
        REQUIRE(player.canGoNext());
        REQUIRE(player.canGoPrevious());
        REQUIRE(player.canAddToFavorites());
        REQUIRE(player.volume() == 1.0);

        REQUIRE(player.currentSong()->title() == "songTitle");
        REQUIRE(player.currentSong()->album() == "albumTitle");
        REQUIRE(player.currentSong()->artist() == "artistName");
        REQUIRE(player.currentSong()->uniqueId() == "010203");
        REQUIRE(player.currentSong()->artUrl() == "artUrl");
        REQUIRE(player.currentSong()->duration() == 350.0);
        REQUIRE(player.currentSong()->isFavorite());
    }

    SECTION("togglePlayPause")
    {
        player.togglePlayPause();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "play();");
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.togglePlayPause();
        REQUIRE(runJavascriptRequestedSpy.count() == 2);
        REQUIRE(runJavascriptRequestedSpy[1][0].toString() == "pause();");
    }

    SECTION("play")
    {
        player.play();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "play();");
    }

    SECTION("pause")
    {
        player.pause();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "pause();");
    }

    SECTION("next")
    {
        player.next();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "goNext();");
    }

    SECTION("previous")
    {
        player.previous();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString() == "goPrevious();");
    }

    SECTION("seekToPosition")
    {
        player.seekToPosition(150.3);
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString().toStdString() == "seekToPosition(150.3);");
    }

    SECTION("setVolume")
    {
        player.setVolume(0.67);
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString().toStdString() == "setVolume(0.67);");
    }

    SECTION("toggleFavoriteSong null song")
    {
        player.toggleFavoriteSong();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
        player.toggleFavoriteSong();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
    }

    SECTION("toggleFavoriteSong valid song")
    {
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
        player.currentSong()->setFavorite(true);
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        REQUIRE(runJavascriptRequestedSpy[0][0].toString().toStdString() == "addToFavorites();");

        player.toggleFavoriteSong();
        player.currentSong()->setFavorite(false);
        REQUIRE(runJavascriptRequestedSpy.count() == 2);
        REQUIRE(runJavascriptRequestedSpy[1][0].toString().toStdString() == "removeFromFavorites();");
    }

    SECTION("suspend when not playing")
    {
        player.setPlaybackStatus(PlaybackStatus::Paused);
        player.suspend();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
    }

    SECTION("suspend when playing")
    {
        player.play();
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.suspend();
        REQUIRE(player.playbackStatus() == PlaybackStatus::Paused);
    }

    SECTION("resume when not playing")
    {
        player.setPlaybackStatus(PlaybackStatus::Paused);
        player.suspend();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
        player.resume();
        REQUIRE(runJavascriptRequestedSpy.count() == 0);
    }

    SECTION("resume when playing")
    {
        player.play();
        REQUIRE(runJavascriptRequestedSpy.count() == 1);
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.suspend();
        REQUIRE(runJavascriptRequestedSpy.count() == 2);
        REQUIRE(player.playbackStatus() == PlaybackStatus::Paused);
        player.resume();
        REQUIRE(runJavascriptRequestedSpy.count() == 3);
    }

    SECTION("reload plugin when streaming service script has changed")
    {
        QSignalSpy spy(&player, &Player::runJavascriptRequested);
        REQUIRE(spy.count() == 0);
        emit service.scriptChanged();
        REQUIRE(spy.count() == 1);
    }
}
