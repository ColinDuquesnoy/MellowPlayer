#include <QtCore>
#include <catch.hpp>
#include <fakeit.hpp>
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#include <MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Root.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/QtApplicationMock.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

TEST_CASE("Mpris2RootTests", "[IntegrationTest]")
{
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();
    Mpris2Root root(mainWindowMock.get(), qtAppMock.get());

    SECTION("canRaise")
    {
        REQUIRE(root.canRaise());
    }

    SECTION("raise")
    {
        root.Raise();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("quit")
    {
        root.Quit();
        Verify(Method(qtAppMock, requestQuit)).Exactly(1);
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