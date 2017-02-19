#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Mpris/Mpris2Root.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("Mpris2RootTests") {
    QQuickWindow window;
    Mpris2Root root(&window, nullptr);

    SECTION("raise should make the window visible") {
        window.hide();
        root.Raise();
        REQUIRE(window.isVisible());
    }

    SECTION("canRaise") {
        REQUIRE(root.canRaise());
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