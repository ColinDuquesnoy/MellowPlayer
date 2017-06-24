#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <fakeit.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Root.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("Mpris2RootTests", "[IntegrationTest]") {
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();
    Mpris2Root root(mainWindowMock.get(), qtAppMock.get());

    SECTION("canRaise") {
        REQUIRE(root.canRaise());
    }

    SECTION("raise") {
        root.Raise();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("quit") {
        root.Quit();
        Verify(Method(qtAppMock, requestQuit)).Exactly(1);
    }

    SECTION("canQuit") {
        REQUIRE(root.canQuit());
    }

    SECTION("hasTracklist") {
        REQUIRE(!root.hasTrackList());
    }

    SECTION("fullscreen") {
        root.setFullscreen(true);
        REQUIRE(!root.canSetFullscreen());
        REQUIRE(!root.fullscreen());
    }

    SECTION("identity is MellowPlayer") {
        REQUIRE(root.identity() == "MellowPlayer");
    }

    SECTION("desktopEntry is MellowPlayer lowercase") {
        REQUIRE(root.desktopEntry() == QString("MellowPlayer").toLower());
    }

    SECTION("supportedMimeTypes") {
        REQUIRE(root.supportedMimeTypes().isEmpty());
    }

    SECTION("supportedUriSchemes") {
        REQUIRE(root.supportedUriSchemes().isEmpty());
    }
}
#endif