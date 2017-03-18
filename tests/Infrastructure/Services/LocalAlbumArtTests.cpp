#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <MellowPlayer/Infrastructure.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("LocalAlbumArtTests"){
    auto pluginLoaderMock = PluginLoaderMock::get();
    PluginManager pluginManager(pluginLoaderMock.get());
    PlayersService playersService(pluginManager);
    PlayerProxy player(playersService, pluginManager);
    AlbumArtDownloaderMock albumArtDownloader;
    QSignalSpy downloadFinishedSpy(&albumArtDownloader, SIGNAL(downloadFinished(const QString&)));
    LocalAlbumArtService localAlbumArt(player, albumArtDownloader);

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