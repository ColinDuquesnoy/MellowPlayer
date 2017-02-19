#include <catch.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <MellowPlayer/UseCases/LocalAlbumArt.hpp>
#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/UseCases/PlayerProxy.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)

TEST_CASE("LocalAlbumArtTests"){
    auto streamingServicesLoaderMock = StreamingServiceLoaderMock::get();
    StreamingServicesManager streamingServicesManager(streamingServicesLoaderMock.get());
    PlayerProxy player(streamingServicesManager);
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
    }
}