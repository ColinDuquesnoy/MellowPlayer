#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/MprisController.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <QtDBus/QDBusConnection>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("MprisServiceTests", "[IntegrationTest]")
{
    auto plugionLoaderMock = StreamingServiceLoaderMock::get();
    StreamingServicesController streamingServices(plugionLoaderMock.get());
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    AlbumArtDownloaderMock albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();

    MprisController mprisService(player, localAlbumArt, mainWindowMock.get(), qtAppMock.get());
    SECTION("start should succeed the first time") {
        if (QDBusConnection::sessionBus().isConnected()) {
            REQUIRE(mprisService.start());

            SECTION("should fail the second time ") {
                REQUIRE(!mprisService.start());
            }
        }
    }
}

#endif