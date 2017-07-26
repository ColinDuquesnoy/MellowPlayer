#include <QtCore>
#include <catch.hpp>
#ifdef Q_OS_LINUX
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Player.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("Mpris2PlayerTests", "[IntegrationTest]")
{
    auto loaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServicesController streamingServices(loaderMock.get(), watcherMock.get());
    streamingServices.load();
    streamingServices.setCurrent(streamingServices.getAll()[0].get());
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    Player& currentPlayer = *players.get(streamingServices.getCurrent()->getName());
    AlbumArtDownloaderMock albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);
    Mpris2Player mpris2Player(player, localAlbumArt, nullptr);

    QSignalSpy currentSongChanged(&player, SIGNAL(currentSongChanged(Song*)));
    QSignalSpy positionChanged(&player, SIGNAL(positionChanged()));
    QSignalSpy playbackStatusChanged(&player, SIGNAL(playbackStatusChanged()));
    QSignalSpy canSeekChanged(&player, SIGNAL(canSeekChanged()));
    QSignalSpy canGoNextChanged(&player, SIGNAL(canGoNextChanged()));
    QSignalSpy canGoPreviousChanged(&player, SIGNAL(canGoPreviousChanged()));
    QSignalSpy canAddToFavoritesChanged(&player, SIGNAL(canAddToFavoritesChanged()));
    QSignalSpy volumeChanged(&player, SIGNAL(volumeChanged()));
    QSignalSpy jsSpy(&currentPlayer, SIGNAL(runJavascriptRequested(const QString&)));

    SECTION("PlaybackStatus")
    {
        SECTION("Default")
        {
            REQUIRE(mpris2Player.playbackStatus() == "Stopped");
        }

        SECTION("Playing")
        {
            mpris2Player.Play();
            currentPlayer.setPlaybackStatus(PlaybackStatus::Playing);
            REQUIRE(mpris2Player.playbackStatus() == "Playing");
        }

        SECTION("Paused")
        {
            mpris2Player.Play();
            mpris2Player.Pause();
            currentPlayer.setPlaybackStatus(PlaybackStatus::Paused);
            REQUIRE(mpris2Player.playbackStatus() == "Paused");
        }

        SECTION("Paused When buffering")
        {
            REQUIRE(mpris2Player.playbackStatus() != "Paused");
            QVariantMap results;
            results["playbackStatus"] = static_cast<int>(PlaybackStatus::Buffering);
            currentPlayer.setUpdateResults(results);
            REQUIRE(mpris2Player.playbackStatus() == "Paused");
        }
    }

    SECTION("LoopStatus cannot be set")
    {
        REQUIRE(mpris2Player.loopStatus() == "None");
        mpris2Player.setLoopStatus("ANYTHING");
        REQUIRE(mpris2Player.loopStatus() == "None");
    }

    SECTION("Shuffle cannot be set")
    {
        REQUIRE(!mpris2Player.shuffle());
        mpris2Player.setShuffle(true);
        REQUIRE(!mpris2Player.shuffle());
    }

    SECTION("Volume")
    {
        QVariantMap results;
        results["volume"] = 0.75;
        currentPlayer.setUpdateResults(results);
        REQUIRE(mpris2Player.volume() == 0.75);
        mpris2Player.setVolume(1.0);
    }

    SECTION("Metadata")
    {
        SECTION("ValidSong")
        {
            QVariantMap results;
            results["position"] = 1.0;
            results["playbackStatus"] = static_cast<int>(PlaybackStatus::Playing);
            results["canSeek"] = true;
            results["canGoNext"] = true;
            results["canGoPrevious"] = true;
            results["canAddToFavorites"] = true;
            results["songId"] = "010203";
            results["songTitle"] = "songTitle";
            results["artistName"] = "artistName";
            results["albumTitle"] = "albumTitle";
            results["artUrl"] = "artUrl";
            results["isFavorite"] = false;
            results["volume"] = 0.5;
            results["duration"] = 350.0;
            currentPlayer.setUpdateResults(results);

            auto map = mpris2Player.metadata();
            REQUIRE(map["xesam:artist"].toString().toStdString() == "artistName");
            REQUIRE(!map["xesam:album"].toString().isEmpty());
            REQUIRE(!map["xesam:title"].toString().isEmpty());
            REQUIRE(!map["mpris:length"].toString().isEmpty());
            REQUIRE(!map["mpris:trackid"].toString().isEmpty());
            REQUIRE(!map["mpris:artUrl"].toString().isEmpty());
        }
        SECTION("InValidSong")
        {
            Song song;
            emit player.currentSongChanged(&song);
            auto map = mpris2Player.metadata();
            REQUIRE(map["xesam:url"].toString().isEmpty());
            REQUIRE(map["xesam:artist"].toString().isEmpty());
            REQUIRE(map["xesam:album"].toString().isEmpty());
            REQUIRE(map["xesam:title"].toString().isEmpty());
            REQUIRE(map["mpris:length"].toString() == "0");
            REQUIRE(!map["mpris:trackid"].toString().isEmpty());
            REQUIRE(map["mpris:artUrl"].toString().isEmpty());
        }
    }

    SECTION("CanPlay")
    {
        REQUIRE(mpris2Player.canPlay());
    }

    SECTION("CanPause")
    {
        REQUIRE(mpris2Player.canPause());
    }

    SECTION("CanControl")
    {
        REQUIRE(mpris2Player.canControl());
    }

    SECTION("CannotStop")
    {
        REQUIRE(!mpris2Player.canStop());
    }

    SECTION("Rate cannot be set")
    {
        REQUIRE(mpris2Player.rate() == 1.0);
        REQUIRE(mpris2Player.minimumRate() == 1.0);
        REQUIRE(mpris2Player.maximumRate() == 1.0);
        mpris2Player.setRate(0.5);
        REQUIRE(mpris2Player.rate() == 1.0);
    }

    SECTION("TogglePlayPause")
    {
        mpris2Player.PlayPause();
        REQUIRE(jsSpy.count() == 1);
    }

    SECTION("Play")
    {
        mpris2Player.Play();
        REQUIRE(jsSpy.count() == 1);
    }

    SECTION("Pause")
    {
        mpris2Player.Play();
        mpris2Player.Pause();
        REQUIRE(jsSpy.count() == 2);
    }

    SECTION("Stop")
    {
        mpris2Player.Play();
        mpris2Player.Stop();
        REQUIRE(jsSpy.count() == 2);
    }

    SECTION("Next")
    {
        mpris2Player.Next();
        REQUIRE(jsSpy.count() == 1);
    }

    SECTION("Previous")
    {
        mpris2Player.Previous();
        REQUIRE(jsSpy.count() == 1);
    }

    SECTION("Seek")
    {
        mpris2Player.Seek(360000000);
        REQUIRE(jsSpy.count() == 1);
        REQUIRE(jsSpy[0][0].toString() == "seekToPosition(360);");
    }

    SECTION("SetPosition")
    {
        mpris2Player.SetPosition(QDBusObjectPath(), 360000000);
        REQUIRE(jsSpy.count() == 1);
        REQUIRE(jsSpy[0][0].toString() == "seekToPosition(360);");
    }

    SECTION("SongChanged")
    {
        Song song1;
        Song song2("uniqueId", "title", "artist", "album", "artUrl", 0, true);
        Song song3("uniqueId", "title", "artist", "album", "artUrl", 360, true);
        emit player.currentSongChanged(&song1);
        emit player.currentSongChanged(&song2);
        emit player.currentSongChanged(&song3);
        song3.setDuration(480);
    }

    SECTION("ChangePosition Emits Seeked")
    {
        QSignalSpy seekedSpy(&mpris2Player, SIGNAL(Seeked(qlonglong)));
        player.seekToPosition(480);
        REQUIRE(seekedSpy.count() == 1);
    }

    SECTION("ChangeCanSeek")
    {
        QSignalSpy seekedSpy(&mpris2Player, SIGNAL(Seeked(qlonglong)));
        QVariantMap results;
        results["canSeek"] = true;
        currentPlayer.setUpdateResults(results);
        REQUIRE(mpris2Player.canSeek());
    }

    SECTION("ChangeCanGoPrevious")
    {
        QSignalSpy seekedSpy(&mpris2Player, SIGNAL(Seeked(qlonglong)));
        QVariantMap results;
        results["canGoPrevious"] = true;
        currentPlayer.setUpdateResults(results);
        REQUIRE(mpris2Player.canGoPrevious());
    }

    SECTION("ChangeCanGoNext")
    {
        QSignalSpy seekedSpy(&mpris2Player, SIGNAL(Seeked(qlonglong)));
        QVariantMap results;
        results["canGoNext"] = true;
        currentPlayer.setUpdateResults(results);
        REQUIRE(mpris2Player.canGoNext());
    }
}
#endif