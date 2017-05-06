//#include <QtCore>
//#ifdef Q_OS_LINUX
//#include <catch.hpp>
//#include <MellowPlayer/UseCases/Services/PluginService.hpp>
//#include <MellowPlayer/UseCases/Player/PlayerProxy.hpp>
//#include <MellowPlayer/UseCases/Services/PlayerService.hpp>
//#include <MellowPlayer/Infrastructure/Services/LocalAlbumArtService.hpp>
//#include <MellowPlayer/Infrastructure/Services/MprisService.hpp>
//#include <MellowPlayer/Infrastructure/Services/LocalAlbumArtService.hpp>
//#include <Mocks/AlbumArtDownloaderMock.hpp>
//#include <Mocks/MainWindowMock.hpp>
//#include <Mocks/QtApplicationMock.hpp>
//#include <Mocks/PluginLoaderMock.hpp>
//#include <QtDBus/QDBusConnection>
//
//USE_MELLOWPLAYER_NAMESPACE(UseCases)
//USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
//
//TEST_CASE("MprisServiceTests", "[IntegrationTest]")
//{
//    auto plugionLoaderMock = PluginLoaderMock::get();
//    PluginService pluginService(plugionLoaderMock.get());
//    PlayerService playerService(pluginService);
//    PlayerProxy player(playerService, pluginService);
//    AlbumArtDownloaderMock albumArtDownloader;
//    LocalAlbumArtService localAlbumArt(player, albumArtDownloader);
//    auto mainWindowMock = MainWindowMock::get();
//    auto qtAppMock = QtApplicationMock::get();
//
//    MprisService mprisService(player, localAlbumArt, mainWindowMock.get(), qtAppMock.get());
//    SECTION("start should succeed the first time") {
//        if (QDBusConnection::sessionBus().isConnected()) {
//            REQUIRE(mprisService.start());
//
//            SECTION("should fail the second time ") {
//                REQUIRE(!mprisService.start());
//            }
//        }
//    }
//}
//
//#endif