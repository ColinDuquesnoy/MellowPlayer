#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Services/MprisService.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <QtDBus/QDBusConnection>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("MprisServiceTests", "[IntegrationTests]")
{
    auto streamingServicesLoaderMock = StreamingServiceLoaderMock::get();
    StreamingServicesManager streamingServicesManager(streamingServicesLoaderMock.get());
    PlayerProxy player(streamingServicesManager);
    AlbumArtDownloaderMock albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();

    MprisService mprisService(player, localAlbumArt, mainWindowMock.get(), qtAppMock.get());
    SECTION("startService should succeed the first time") {
        if (QDBusConnection::sessionBus().isConnected()) {
            REQUIRE(mprisService.startService());

            SECTION("should fail the second time ") {
                REQUIRE(!mprisService.startService());
            }
        }
    }
}

#endif