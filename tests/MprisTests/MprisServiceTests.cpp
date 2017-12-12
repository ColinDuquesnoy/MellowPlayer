#include <QtCore>
#include <catch.hpp>
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Presentation/Mpris/Linux/MprisService.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <QtDBus/QDBusConnection>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <UnitTests/Presentation/FakeMainWindow.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

TEST_CASE("MprisServiceTests", "[IntegrationTest]")
{
    auto plugionLoaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServices streamingServices(plugionLoaderMock.get(), watcherMock.get());
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    AlbumArtDownloaderMock albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);
    FakeMainWindow mainWindow;

    MprisService mprisService(player, localAlbumArt, mainWindow);
    SECTION("start should succeed the first time")
    {
        if (QDBusConnection::sessionBus().isConnected()) {
            REQUIRE(mprisService.start());

            SECTION("should fail the second time ")
            {
                REQUIRE(!mprisService.start());
            }
        }
    }
}

#endif
