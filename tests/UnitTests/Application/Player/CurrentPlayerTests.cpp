#include "Mocks/StreamingServiceLoaderMock.hpp"
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Application;

TEST_CASE("CurrentPlayerTests", "[UnitTest]")
{
    auto mock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServicesController streamingServices(mock.get(), watcherMock.get());
    streamingServices.load();
    Players players(streamingServices);
    CurrentPlayer currentPlayer(players, streamingServices);

    SECTION("default properties (currentPlayer is null)")
    {
        REQUIRE(currentPlayer.getPosition() == 0);
        REQUIRE(currentPlayer.getPlaybackStatus() == PlaybackStatus::Stopped);
        REQUIRE(!currentPlayer.getCanSeek());
        REQUIRE(!currentPlayer.getCanGoNext());
        REQUIRE(!currentPlayer.getCanGoPrevious());
        REQUIRE(!currentPlayer.getCanAddToFavorites());
        REQUIRE(currentPlayer.getVolume() == 0.0);

        REQUIRE(currentPlayer.getCurrentSong()->getTitle() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getAlbum() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getArtist() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getUniqueId() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getArtUrl() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getDuration() == 0);
        REQUIRE(!currentPlayer.getCurrentSong()->getIsFavorite());
    }

    Player &player1 = *players.get(streamingServices.getAll()[0]->getName());
    Player &player2 = *players.get(streamingServices.getAll()[1]->getName());
    streamingServices.setCurrent(streamingServices.getAll()[0].get());

    QSignalSpy currentSongChanged(&currentPlayer, SIGNAL(currentSongChanged(Song *)));
    QSignalSpy positionChanged(&currentPlayer, SIGNAL(positionChanged()));
    QSignalSpy playbackStatusChanged(&currentPlayer, SIGNAL(playbackStatusChanged()));
    QSignalSpy canSeekChanged(&currentPlayer, SIGNAL(canSeekChanged()));
    QSignalSpy canGoNextChanged(&currentPlayer, SIGNAL(canGoNextChanged()));
    QSignalSpy canGoPreviousChanged(&currentPlayer, SIGNAL(canGoPreviousChanged()));
    QSignalSpy canAddToFavoritesChanged(&currentPlayer, SIGNAL(canAddToFavoritesChanged()));
    QSignalSpy volumeChanged(&currentPlayer, SIGNAL(volumeChanged()));

    SECTION("control player1")
    {
        QSignalSpy jsSpy(&player1, SIGNAL(runJavascriptRequested(const QString &)));

        SECTION("togglePlayPause")
        {
            currentPlayer.togglePlayPause();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "play();");
        }

        SECTION("play")
        {
            currentPlayer.play();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "play();");
        }

        SECTION("pause")
        {
            currentPlayer.play();
            currentPlayer.pause();
            REQUIRE(jsSpy.count() == 2);
            REQUIRE(jsSpy[1][0] == "pause();");
        }

        SECTION("next")
        {
            currentPlayer.next();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "goNext();");
        }

        SECTION("previous")
        {
            currentPlayer.previous();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "goPrevious();");
        }

        SECTION("seekToPosition")
        {
            currentPlayer.seekToPosition(153.5);
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "seekToPosition(153.5);");
        }

        SECTION("setVolume")
        {
            currentPlayer.setVolume(0.5);
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0].toString().toStdString() == "setVolume(0.5);");
        }

        SECTION("toggleFavoriteSong")
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
            map["volume"] = 0.5;
            map["duration"] = 350.0;
            player1.setUpdateResults(QVariant::fromValue(map));

            currentPlayer.toggleFavoriteSong();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "addToFavorites();");
        }

        SECTION("addToFavorites")
        {
            currentPlayer.addToFavorites();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "addToFavorites();");
        }

        SECTION("removeFromFavorites")
        {
            currentPlayer.removeFromFavorites();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "removeFromFavorites();");
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

        REQUIRE(currentPlayer.getPosition() == 1.0);
        REQUIRE(currentPlayer.getPlaybackStatus() == PlaybackStatus::Playing);
        REQUIRE(currentPlayer.getCanSeek());
        REQUIRE(currentPlayer.getCanGoNext());
        REQUIRE(currentPlayer.getCanGoPrevious());
        REQUIRE(currentPlayer.getCanAddToFavorites());
        REQUIRE(currentPlayer.getVolume() == 0.5);

        REQUIRE(currentPlayer.getCurrentSong()->getTitle() == "songTitle");
        REQUIRE(currentPlayer.getCurrentSong()->getAlbum() == "albumTitle");
        REQUIRE(currentPlayer.getCurrentSong()->getArtist() == "artistName");
        REQUIRE(currentPlayer.getCurrentSong()->getUniqueId() == "010203");
        REQUIRE(currentPlayer.getCurrentSong()->getArtUrl() == "artUrl");
        REQUIRE(currentPlayer.getCurrentSong()->getDuration() == 350.0);
        REQUIRE(currentPlayer.getCurrentSong()->getIsFavorite());

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

        REQUIRE(currentPlayer.getPosition() == 0);
        REQUIRE(currentPlayer.getPlaybackStatus() == PlaybackStatus::Stopped);
        REQUIRE(!currentPlayer.getCanSeek());
        REQUIRE(!currentPlayer.getCanGoNext());
        REQUIRE(!currentPlayer.getCanGoPrevious());
        REQUIRE(!currentPlayer.getCanAddToFavorites());
        REQUIRE(currentPlayer.getVolume() == 1.0);

        REQUIRE(currentPlayer.getCurrentSong()->getTitle() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getAlbum() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getArtist() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getUniqueId() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getArtUrl() == "");
        REQUIRE(currentPlayer.getCurrentSong()->getDuration() == 0);
        REQUIRE(!currentPlayer.getCurrentSong()->getIsFavorite());

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
        streamingServices.setCurrent(streamingServices.getAll()[1].get());

        REQUIRE(currentPlayer.getPosition() == 1.0);
        REQUIRE(currentPlayer.getPlaybackStatus() == PlaybackStatus::Playing);
        REQUIRE(currentPlayer.getCanSeek());
        REQUIRE(currentPlayer.getCanGoNext());
        REQUIRE(currentPlayer.getCanGoPrevious());
        REQUIRE(currentPlayer.getCanAddToFavorites());
        REQUIRE(currentPlayer.getVolume() == 0.5);

        REQUIRE(currentPlayer.getCurrentSong()->getTitle() == "songTitle");
        REQUIRE(currentPlayer.getCurrentSong()->getAlbum() == "albumTitle");
        REQUIRE(currentPlayer.getCurrentSong()->getArtist() == "artistName");
        REQUIRE(currentPlayer.getCurrentSong()->getUniqueId() == "010203");
        REQUIRE(currentPlayer.getCurrentSong()->getArtUrl() == "artUrl");
        REQUIRE(currentPlayer.getCurrentSong()->getDuration() == 350.0);
        REQUIRE(currentPlayer.getCurrentSong()->getIsFavorite());

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
