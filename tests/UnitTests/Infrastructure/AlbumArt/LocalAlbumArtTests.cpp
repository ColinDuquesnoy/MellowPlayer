#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceWatcher.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>
#include <QTest>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;

SCENARIO("LocalAlbumArt download current song art url when it changed")
{
    FakeStreamingServiceLoader streamingServiceLoader;
    FakeStreamingServiceWatcher streamingServiceWatcher;
    StreamingServices streamingServices(streamingServiceLoader, streamingServiceWatcher);
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    FakeAlbumArtDownloader albumArtDownloader;
    int timeout = 1;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader, timeout);

    QSignalSpy urlChangedSpy(&localAlbumArt, &LocalAlbumArt::urlChanged);

    GIVEN("a new song with a valid url starts playing")
    {
        QString url = "https://deezer.com/arUrl-123.png";
        QString songId = "songId";

        Song song(songId, "", "", "", url, 0, false);
        emit player.currentSongChanged(&song);

        THEN("AlbumArtDownloader is called with the song artUrl")
        {
            REQUIRE(albumArtDownloader.artUrl() == url);

            THEN("urlChanged signal is emitted")
            {
                REQUIRE(urlChangedSpy.count() == 1);
            }

            THEN("album local url is taken from the albumArtDownload")
            {
                REQUIRE(localAlbumArt.url() == albumArtDownloader.localArtUrl());
            }
        }
    }

    GIVEN("a new song with an empty url")
    {
        QString url = "";
        QString songId = "songId";

        Song song(songId, "", "", "", url, 0, false);
        emit player.currentSongChanged(&song);

        THEN("urlChanged signal is not emitted immediately")
        {
            REQUIRE(urlChangedSpy.count() == 0);
        }

        AND_WHEN("timeout has elapsed without url change")
        {
            urlChangedSpy.wait();

            THEN("albumArtDownloader is called with MellowPlayer's logo url")
            {
                REQUIRE(albumArtDownloader.artUrl().toStdString() == localAlbumArt.fallbackUrl().toStdString());

                THEN("urlChanged signal is emitted")
                {
                    REQUIRE(urlChangedSpy.count() == 1);
                }

                AND_THEN("album local url is valid")
                {
                    REQUIRE(localAlbumArt.url() == albumArtDownloader.localArtUrl());
                }
            }
        }

        AND_WHEN("a new url is set")
        {
            song.setArtUrl("https://deezer.com/arUrl-123.png");


            THEN("AlbumArtDownloader is called with the song artUrl")
            {
                REQUIRE(albumArtDownloader.artUrl() == url);

                THEN("urlChanged signal is emitted")
                {
                    REQUIRE(urlChangedSpy.count() == 1);
                }

                THEN("album local url is valid")
                {
                    REQUIRE(localAlbumArt.url() == albumArtDownloader.localArtUrl());
                }
            }
        }
    }
}
