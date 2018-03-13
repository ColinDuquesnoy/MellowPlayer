#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceWatcher.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

TEST_CASE("CurrentPlayerTests", "[UnitTest]")
{
    FakeStreamingServiceLoader streamingServiceLoader;
    FakeStreamingServiceWatcher streamingServiceWatcher;
    StreamingServices streamingServices(streamingServiceLoader, streamingServiceWatcher);
    streamingServices.load();
    Players players(streamingServices);
    CurrentPlayer currentPlayer(players, streamingServices);

    SECTION("default properties (currentPlayer is null)")
    {
        REQUIRE(currentPlayer.position() == 0);
        REQUIRE(currentPlayer.playbackStatus() == PlaybackStatus::Stopped);
        REQUIRE(!currentPlayer.canSeek());
        REQUIRE(!currentPlayer.canGoNext());
        REQUIRE(!currentPlayer.canGoPrevious());
        REQUIRE(!currentPlayer.canAddToFavorites());
        REQUIRE(currentPlayer.volume() == 0.0);

        REQUIRE(currentPlayer.currentSong()->title() == "");
        REQUIRE(currentPlayer.currentSong()->album() == "");
        REQUIRE(currentPlayer.currentSong()->artist() == "");
        REQUIRE(currentPlayer.currentSong()->uniqueId() == "");
        REQUIRE(currentPlayer.currentSong()->artUrl() == "");
        REQUIRE(currentPlayer.currentSong()->duration() == 0);
        REQUIRE(!currentPlayer.currentSong()->isFavorite());
    }

    Player& player1 = *players.get(streamingServices.toList()[0]->name());
    Player& player2 = *players.get(streamingServices.toList()[1]->name());
    streamingServices.setCurrent(streamingServices.toList()[0].get());

    QSignalSpy currentSongChanged(&currentPlayer, &CurrentPlayer::currentSongChanged);
    QSignalSpy positionChanged(&currentPlayer, SIGNAL(positionChanged()));
    QSignalSpy playbackStatusChanged(&currentPlayer, SIGNAL(playbackStatusChanged()));
    QSignalSpy canSeekChanged(&currentPlayer, SIGNAL(canSeekChanged()));
    QSignalSpy canGoNextChanged(&currentPlayer, SIGNAL(canGoNextChanged()));
    QSignalSpy canGoPreviousChanged(&currentPlayer, SIGNAL(canGoPreviousChanged()));
    QSignalSpy canAddToFavoritesChanged(&currentPlayer, SIGNAL(canAddToFavoritesChanged()));
    QSignalSpy volumeChanged(&currentPlayer, SIGNAL(volumeChanged()));

    SECTION("control player1")
    {
        SECTION("togglePlayPause")
        {
            QSignalSpy spy(&player1, &Player::play);
            currentPlayer.togglePlayPause();
            REQUIRE(spy.count() == 1);
        }

        SECTION("play")
        {
            QSignalSpy spy(&player1, &Player::play);
            currentPlayer.play();
            REQUIRE(spy.count() == 1);
        }

        SECTION("pause")
        {
            QSignalSpy spy(&player1, &Player::pause);
            currentPlayer.pause();
            REQUIRE(spy.count() == 1);
        }

        SECTION("next")
        {
            QSignalSpy spy(&player1, &Player::next);
            currentPlayer.next();
            REQUIRE(spy.count() == 1);
        }

        SECTION("previous")
        {
            QSignalSpy spy(&player1, &Player::previous);
            currentPlayer.previous();
            REQUIRE(spy.count() == 1);
        }

        SECTION("seekToPosition")
        {
            QSignalSpy spy(&player1, &Player::seekToPositionRequest);
            currentPlayer.seekToPosition(160);
            REQUIRE(spy.count() == 1);
        }

        SECTION("setVolume")
        {
            QSignalSpy spy(&player1, &Player::changeVolumeRequest);
            currentPlayer.setVolume(0.67);
            REQUIRE(spy.count() == 1);
        }

        SECTION("toggleFavoriteSong")
        {
            QSignalSpy spy(&player1, &Player::addToFavorites);
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
            map["volume"] = 0.5;
            map["duration"] = 350.0;
            player1.setUpdateResults(QVariant::fromValue(map));
            currentPlayer.toggleFavoriteSong();

            currentPlayer.previous();
            REQUIRE(spy.count() == 1);
        }

        SECTION("addToFavorites")
        {
            QSignalSpy spy(&player1, &Player::addToFavorites);
            currentPlayer.addToFavorites();
            REQUIRE(spy.count() == 1);
        }

        SECTION("removeFromFavorites")
        {
            QSignalSpy spy(&player1, &Player::removeFromFavorites);
            currentPlayer.removeFromFavorites();
            REQUIRE(spy.count() == 1);
        }
    }

    SECTION("setUpdateResults of active player")
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
        map["volume"] = 0.5;
        map["duration"] = 350.0;
        player1.setUpdateResults(QVariant::fromValue(map));

        REQUIRE(currentPlayer.position() == 1.0);
        REQUIRE(currentPlayer.playbackStatus() == PlaybackStatus::Playing);
        REQUIRE(currentPlayer.canSeek());
        REQUIRE(currentPlayer.canGoNext());
        REQUIRE(currentPlayer.canGoPrevious());
        REQUIRE(currentPlayer.canAddToFavorites());
        REQUIRE(currentPlayer.volume() == 0.5);

        REQUIRE(currentPlayer.currentSong()->title() == "songTitle");
        REQUIRE(currentPlayer.currentSong()->album() == "albumTitle");
        REQUIRE(currentPlayer.currentSong()->artist() == "artistName");
        REQUIRE(currentPlayer.currentSong()->uniqueId() == "010203");
        REQUIRE(currentPlayer.currentSong()->artUrl() == "artUrl");
        REQUIRE(currentPlayer.currentSong()->duration() == 350.0);
        REQUIRE(currentPlayer.currentSong()->isFavorite());

        REQUIRE(currentSongChanged.count() == 1);
        REQUIRE(positionChanged.count() == 1);
        REQUIRE(playbackStatusChanged.count() == 1);
        REQUIRE(canSeekChanged.count() == 1);
        REQUIRE(currentSongChanged.count() == 1);
        REQUIRE(canGoNextChanged.count() == 1);
        REQUIRE(canGoPreviousChanged.count() == 1);
        REQUIRE(canAddToFavoritesChanged.count() == 1);
        REQUIRE(volumeChanged.count() == 1);
    }

    SECTION("setUpdateResults of inactive player")
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
        map["volume"] = 0.5;
        map["duration"] = 350.0;
        player2.setUpdateResults(QVariant::fromValue(map));

        REQUIRE(currentPlayer.position() == 0);
        REQUIRE(currentPlayer.playbackStatus() == PlaybackStatus::Stopped);
        REQUIRE(!currentPlayer.canSeek());
        REQUIRE(!currentPlayer.canGoNext());
        REQUIRE(!currentPlayer.canGoPrevious());
        REQUIRE(!currentPlayer.canAddToFavorites());
        REQUIRE(currentPlayer.volume() == 1.0);

        REQUIRE(currentPlayer.currentSong()->title() == "");
        REQUIRE(currentPlayer.currentSong()->album() == "");
        REQUIRE(currentPlayer.currentSong()->artist() == "");
        REQUIRE(currentPlayer.currentSong()->uniqueId() == "");
        REQUIRE(currentPlayer.currentSong()->artUrl() == "");
        REQUIRE(currentPlayer.currentSong()->duration() == 0);
        REQUIRE(!currentPlayer.currentSong()->isFavorite());

        REQUIRE(currentSongChanged.count() == 0);
        REQUIRE(positionChanged.count() == 0);
        REQUIRE(playbackStatusChanged.count() == 0);
        REQUIRE(canSeekChanged.count() == 0);
        REQUIRE(currentSongChanged.count() == 0);
        REQUIRE(canGoNextChanged.count() == 0);
        REQUIRE(canGoPreviousChanged.count() == 0);
        REQUIRE(canAddToFavoritesChanged.count() == 0);
        REQUIRE(volumeChanged.count() == 0);
    }

    SECTION("setUpdateResults of new active player")
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
        map["volume"] = 0.5;
        map["duration"] = 350.0;
        player2.setUpdateResults(QVariant::fromValue(map));
        streamingServices.setCurrent(streamingServices.toList()[1].get());

        REQUIRE(currentPlayer.position() == 1.0);
        REQUIRE(currentPlayer.playbackStatus() == PlaybackStatus::Playing);
        REQUIRE(currentPlayer.canSeek());
        REQUIRE(currentPlayer.canGoNext());
        REQUIRE(currentPlayer.canGoPrevious());
        REQUIRE(currentPlayer.canAddToFavorites());
        REQUIRE(currentPlayer.volume() == 0.5);

        REQUIRE(currentPlayer.currentSong()->title() == "songTitle");
        REQUIRE(currentPlayer.currentSong()->album() == "albumTitle");
        REQUIRE(currentPlayer.currentSong()->artist() == "artistName");
        REQUIRE(currentPlayer.currentSong()->uniqueId() == "010203");
        REQUIRE(currentPlayer.currentSong()->artUrl() == "artUrl");
        REQUIRE(currentPlayer.currentSong()->duration() == 350.0);
        REQUIRE(currentPlayer.currentSong()->isFavorite());

        REQUIRE(currentSongChanged.count() == 1);
        REQUIRE(positionChanged.count() == 1);
        REQUIRE(playbackStatusChanged.count() == 1);
        REQUIRE(canSeekChanged.count() == 1);
        REQUIRE(currentSongChanged.count() == 1);
        REQUIRE(canGoNextChanged.count() == 1);
        REQUIRE(canGoPreviousChanged.count() == 1);
        REQUIRE(canAddToFavoritesChanged.count() == 1);
        REQUIRE(volumeChanged.count() == 1);
    }
}
