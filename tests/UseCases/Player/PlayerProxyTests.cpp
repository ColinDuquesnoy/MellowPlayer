#include <catch.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <QtTest/QSignalSpy>
#include "Mocks/PluginLoaderMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)

TEST_CASE("PlayerProxyTests") {
    auto mock = PluginLoaderMock::get();
    PluginManager pluginManager(mock.get());
    pluginManager.load();
    PlayersManager playersManager(pluginManager);
    PlayerProxy proxy(playersManager, pluginManager);

    SECTION("default properties (currentPlayer is null)") {
        REQUIRE(proxy.getPosition() == 0);
        REQUIRE(proxy.getPlaybackStatus() == IPlayer::PlaybackStatus::Stopped);
        REQUIRE(!proxy.getCanSeek());
        REQUIRE(!proxy.getCanGoNext());
        REQUIRE(!proxy.getCanGoPrevious());
        REQUIRE(!proxy.getCanAddToFavorites());
        REQUIRE(proxy.getVolume() == 0.0);

        REQUIRE(proxy.getCurrentSong()->getTitle() == "");
        REQUIRE(proxy.getCurrentSong()->getAlbum() == "");
        REQUIRE(proxy.getCurrentSong()->getArtist() == "");
        REQUIRE(proxy.getCurrentSong()->getUniqueId() == "");
        REQUIRE(proxy.getCurrentSong()->getArtUrl() == "");
        REQUIRE(proxy.getCurrentSong()->getDuration() == 0);
        REQUIRE(!proxy.getCurrentSong()->getIsFavorite());
    }

    Player& player1 = *playersManager.getPlayer(pluginManager.getAll()[0]->getName());
    Player& player2 = *playersManager.getPlayer(pluginManager.getAll()[1]->getName());
    pluginManager.setCurrent(pluginManager.getAll()[0].get());

    QSignalSpy currentSongChanged(&proxy, SIGNAL(currentSongChanged(Song*)));
    QSignalSpy positionChanged(&proxy, SIGNAL(positionChanged()));
    QSignalSpy playbackStatusChanged(&proxy, SIGNAL(playbackStatusChanged()));
    QSignalSpy canSeekChanged(&proxy, SIGNAL(canSeekChanged()));
    QSignalSpy canGoNextChanged(&proxy, SIGNAL(canGoNextChanged()));
    QSignalSpy canGoPreviousChanged(&proxy, SIGNAL(canGoPreviousChanged()));
    QSignalSpy canAddToFavoritesChanged(&proxy, SIGNAL(canAddToFavoritesChanged()));
    QSignalSpy volumeChanged(&proxy, SIGNAL(volumeChanged()));

    SECTION("control player1") {
        QSignalSpy jsSpy(&player1, SIGNAL(runJavascriptRequested(const QString&)));

        SECTION("togglePlayPause") {
            proxy.togglePlayPause();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "play();");
        }

        SECTION("play") {
            proxy.play();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "play();");
        }

        SECTION("pause") {
            proxy.play();
            proxy.pause();
            REQUIRE(jsSpy.count() == 2);
            REQUIRE(jsSpy[1][0] == "pause();");
        }

        SECTION("next") {
            proxy.next();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "goNext();");
        }

        SECTION("previous") {
            proxy.previous();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "goPrevious();");
        }

        SECTION("seekToPosition") {
            proxy.seekToPosition(153.5);
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "seekToPosition(153.5);");
        }

        SECTION("setVolume") {
            proxy.setVolume(0.5);
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "setVolume(0.5);");
        }

        SECTION("toggleFavoriteSong") {
            QVariantMap map;
            map["position"] = 1.0;
            map["playbackStatus"] = static_cast<int>(IPlayer::PlaybackStatus::Playing);
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

            proxy.toggleFavoriteSong();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "addToFavorites();");
        }

        SECTION("addToFavorites") {
            proxy.addToFavorites();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "addToFavorites();");
        }

        SECTION("removeFromFavorites") {
            proxy.removeFromFavorites();
            REQUIRE(jsSpy.count() == 1);
            REQUIRE(jsSpy[0][0] == "removeFromFavorites();");
        }
    }

    SECTION("setUpdateResults of active player") {
        QVariantMap map;
        map["position"] = 1.0;
        map["playbackStatus"] = static_cast<int>(IPlayer::PlaybackStatus::Playing);
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

        REQUIRE(proxy.getPosition() == 1.0);
        REQUIRE(proxy.getPlaybackStatus() == IPlayer::PlaybackStatus::Playing);
        REQUIRE(proxy.getCanSeek());
        REQUIRE(proxy.getCanGoNext());
        REQUIRE(proxy.getCanGoPrevious());
        REQUIRE(proxy.getCanAddToFavorites());
        REQUIRE(proxy.getVolume() == 0.5);

        REQUIRE(proxy.getCurrentSong()->getTitle() == "songTitle");
        REQUIRE(proxy.getCurrentSong()->getAlbum() == "albumTitle");
        REQUIRE(proxy.getCurrentSong()->getArtist() == "artistName");
        REQUIRE(proxy.getCurrentSong()->getUniqueId() == "010203");
        REQUIRE(proxy.getCurrentSong()->getArtUrl() == "artUrl");
        REQUIRE(proxy.getCurrentSong()->getDuration() == 350.0);
        REQUIRE(proxy.getCurrentSong()->getIsFavorite());

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

    SECTION("setUpdateResults of inactive player") {
        QVariantMap map;
        map["position"] = 1.0;
        map["playbackStatus"] = static_cast<int>(IPlayer::PlaybackStatus::Playing);
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

        REQUIRE(proxy.getPosition() == 0);
        REQUIRE(proxy.getPlaybackStatus() == IPlayer::PlaybackStatus::Stopped);
        REQUIRE(!proxy.getCanSeek());
        REQUIRE(!proxy.getCanGoNext());
        REQUIRE(!proxy.getCanGoPrevious());
        REQUIRE(!proxy.getCanAddToFavorites());
        REQUIRE(proxy.getVolume() == 1.0);

        REQUIRE(proxy.getCurrentSong()->getTitle() == "");
        REQUIRE(proxy.getCurrentSong()->getAlbum() == "");
        REQUIRE(proxy.getCurrentSong()->getArtist() == "");
        REQUIRE(proxy.getCurrentSong()->getUniqueId() == "");
        REQUIRE(proxy.getCurrentSong()->getArtUrl() == "");
        REQUIRE(proxy.getCurrentSong()->getDuration() == 0);
        REQUIRE(!proxy.getCurrentSong()->getIsFavorite());

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


    SECTION("setUpdateResults of new active player") {
        QVariantMap map;
        map["position"] = 1.0;
        map["playbackStatus"] = static_cast<int>(IPlayer::PlaybackStatus::Playing);
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
        pluginManager.setCurrent(pluginManager.getAll()[1].get());

        REQUIRE(proxy.getPosition() == 1.0);
        REQUIRE(proxy.getPlaybackStatus() == IPlayer::PlaybackStatus::Playing);
        REQUIRE(proxy.getCanSeek());
        REQUIRE(proxy.getCanGoNext());
        REQUIRE(proxy.getCanGoPrevious());
        REQUIRE(proxy.getCanAddToFavorites());
        REQUIRE(proxy.getVolume() == 0.5);

        REQUIRE(proxy.getCurrentSong()->getTitle() == "songTitle");
        REQUIRE(proxy.getCurrentSong()->getAlbum() == "albumTitle");
        REQUIRE(proxy.getCurrentSong()->getArtist() == "artistName");
        REQUIRE(proxy.getCurrentSong()->getUniqueId() == "010203");
        REQUIRE(proxy.getCurrentSong()->getArtUrl() == "artUrl");
        REQUIRE(proxy.getCurrentSong()->getDuration() == 350.0);
        REQUIRE(proxy.getCurrentSong()->getIsFavorite());

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