#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Infrastructure/MprisMediaPlayer.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("MprisMediaPlayerTests", "[IntegrationTests]")
{
    auto streamingServicesLoaderMock = StreamingServiceLoaderMock::get();
    StreamingServicesManager streamingServicesManager(streamingServicesLoaderMock.get());
    PlayerProxy player(streamingServicesManager);
    AlbumArtDownloaderMock albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);

    MprisMediaPlayer mediaPlayer(player, localAlbumArt, nullptr, LoggingManager::instance());
    SECTION("startService should succeed the first time") {
        REQUIRE(mediaPlayer.startService());

        SECTION("should fail the second time ") {
            REQUIRE(!mediaPlayer.startService());
        }
    }
}

#endif