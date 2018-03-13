#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

TEST_CASE("PlayerTests", "[UnitTest]")
{
    StreamingServiceMetadata metadata;
    FakeSettingsStore settingsStoreMock;
    StreamingService service(metadata);
    Player player(service);
    QSignalSpy runJavascriptRequestedSpy(&player, SIGNAL(runJavascriptRequested(const QString&)));

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
        QSignalSpy playSpy(&player, &Player::play);
        QSignalSpy pauseSpy(&player, &Player::pause);
        player.togglePlayPause();
        REQUIRE(playSpy.count() == 1);
        REQUIRE(pauseSpy.count() == 0);

        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.togglePlayPause();
        REQUIRE(playSpy.count() == 1);
        REQUIRE(pauseSpy.count() == 1);
    }

    SECTION("play")
    {
        QSignalSpy playSpy(&player, &Player::play);

        player.play();

        REQUIRE(playSpy.count() == 1);
    }

    SECTION("pause")
    {
        QSignalSpy pauseSpy(&player, &Player::pause);

        player.pause();

        REQUIRE(pauseSpy.count() == 1);
    }

    SECTION("next")
    {
        QSignalSpy spy(&player, &Player::next);

        player.next();

        REQUIRE(spy.count() == 1);
    }

    SECTION("previous")
    {
        QSignalSpy spy(&player, &Player::previous);

        player.previous();

        REQUIRE(spy.count() == 1);
    }

    SECTION("seekToPosition")
    {
        QSignalSpy spy(&player, &Player::seekToPositionRequest);

        player.seekToPosition(150.3);

        REQUIRE(spy.count() == 1);
        REQUIRE(spy.at(0).at(0).toDouble() == 150.3);
    }

    SECTION("setVolume")
    {
        QSignalSpy spy(&player, &Player::changeVolumeRequest);

        player.setVolume(0.67);

        REQUIRE(spy.count() == 1);
        REQUIRE(spy.at(0).at(0).toDouble() == 0.67);
    }

    SECTION("toggleFavoriteSong null song")
    {
        QSignalSpy addToFavoritesSpy(&player, &Player::addToFavorites);
        QSignalSpy removeFromFavoritesSpy(&player, &Player::removeFromFavorites);
        player.toggleFavoriteSong();
        REQUIRE(addToFavoritesSpy.count() == 0);
        REQUIRE(removeFromFavoritesSpy.count() == 0);

        player.toggleFavoriteSong();
        REQUIRE(addToFavoritesSpy.count() == 0);
        REQUIRE(removeFromFavoritesSpy.count() == 0);
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

        QSignalSpy addToFavoritesSpy(&player, &Player::addToFavorites);
        QSignalSpy removeFromFavoritesSpy(&player, &Player::removeFromFavorites);
        player.toggleFavoriteSong();
        player.currentSong()->setFavorite(true);
        REQUIRE(addToFavoritesSpy.count() == 1);
        REQUIRE(removeFromFavoritesSpy.count() == 0);

        player.toggleFavoriteSong();
        player.currentSong()->setFavorite(false);
        REQUIRE(addToFavoritesSpy.count() == 1);
        REQUIRE(removeFromFavoritesSpy.count() == 1);
    }

    SECTION("suspend when not playing")
    {
        QSignalSpy pauseSpy(&player, &Player::pause);

        player.setPlaybackStatus(PlaybackStatus::Paused);
        player.suspend();

        REQUIRE(pauseSpy.count() == 0);
    }

    SECTION("suspend when playing")
    {
        QSignalSpy pauseSpy(&player, &Player::pause);

        player.play();
        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.suspend();

        REQUIRE(pauseSpy.count() == 1);
        REQUIRE(player.playbackStatus() == PlaybackStatus::Paused);
    }

    SECTION("resume when not playing")
    {
        QSignalSpy playSpy(&player, &Player::play);

        player.setPlaybackStatus(PlaybackStatus::Playing);
        player.suspend();
        player.resume();

        REQUIRE(playSpy.count() == 1);
    }

    SECTION("resume when playing")
    {
        player.play();
        player.setPlaybackStatus(PlaybackStatus::Playing);
        QSignalSpy playSpy(&player, &Player::play);

        player.resume();
        REQUIRE(playSpy.count() == 0);
    }
}
