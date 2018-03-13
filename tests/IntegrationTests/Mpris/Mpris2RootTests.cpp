#include <QtCore>
#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#include <MellowPlayer/Presentation/Mpris/Linux/Mpris2Root.hpp>
#include <UnitTests/Presentation/FakeMainWindow.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;
using namespace fakeit;

TEST_CASE("Mpris2RootTests", "[IntegrationTest]")
{
    FakeMainWindow mainWindow;
    Mpris2Root root(mainWindow);

    SECTION("canRaise")
    {
        REQUIRE(root.canRaise());
    }

    SECTION("raise")
    {
        root.Raise();
        REQUIRE(mainWindow.isShown);
    }

    SECTION("quit")
    {
        root.Quit();
    }

    SECTION("canQuit")
    {
        REQUIRE(root.canQuit());
    }

    SECTION("hasTracklist")
    {
        REQUIRE(!root.hasTrackList());
    }

    SECTION("fullscreen")
    {
        root.setFullscreen(true);
        REQUIRE(!root.canSetFullscreen());
        REQUIRE(!root.fullscreen());
    }

    SECTION("identity is MellowPlayer")
    {
        REQUIRE(root.identity() == "MellowPlayer");
    }

    SECTION("desktopEntry is MellowPlayer lowercase")
    {
        REQUIRE(root.desktopEntry() == QString("MellowPlayer").toLower());
    }

    SECTION("supportedMimeTypes")
    {
        REQUIRE(root.supportedMimeTypes().isEmpty());
    }

    SECTION("supportedUriSchemes")
    {
        REQUIRE(root.supportedUriSchemes().isEmpty());
    }
}
#endif
