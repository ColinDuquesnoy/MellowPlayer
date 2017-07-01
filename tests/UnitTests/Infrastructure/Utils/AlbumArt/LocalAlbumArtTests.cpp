#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("LocalAlbumArtTests", "[UnitTest]"){
    auto serviceLoaderMock = StreamingServiceLoaderMock::get();
    StreamingServices streamingServices(serviceLoaderMock.get());
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    AlbumArtDownloaderMock albumArtDownloader;
    QSignalSpy downloadFinishedSpy(&albumArtDownloader, SIGNAL(downloadFinished(const QString&)));
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);

    SECTION("download when current song changed") {
        QString url = "https://deezer.com/arUrl-123.png";
        QString songId = "songId";

        Song song(songId, "", "", "", url, 0, false);
        emit player.currentSongChanged(&song);
        REQUIRE(downloadFinishedSpy.count() == 1);
        REQUIRE(downloadFinishedSpy[0][0] == LOCAL_URL);
        REQUIRE(localAlbumArt.getUrl() == LOCAL_URL);
        REQUIRE(!localAlbumArt.isSongArtReady(song)); // file does not exist because we use a downloader mock
    }
}