#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>
#include "FakeMainWindow.hpp"

using namespace MellowPlayer::Tests;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;
using namespace fakeit;

TEST_CASE("HotkeysServiceTests", "[UnitTest]")
{
    auto playerMock = PlayerMock::get();
    FakeMainWindow mainWindow;
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    Hotkeys hotkeys(playerMock.get(), settings, mainWindow);
    hotkeys.initialize();

    SECTION("togglePlayPause")
    {
        hotkeys.togglePlayPause();
        Verify(Method(playerMock, togglePlayPause)).Exactly(1);
    }

    SECTION("next")
    {
        hotkeys.next();
        Verify(Method(playerMock, next)).Exactly(1);
    }

    SECTION("previous")
    {
        hotkeys.previous();
        Verify(Method(playerMock, previous)).Exactly(1);
    }

    SECTION("toggleFavoriteSong")
    {
        hotkeys.toggleFavoriteSong();
        Verify(Method(playerMock, toggleFavoriteSong)).Exactly(1);
    }

    SECTION("toggleFavoriteSong")
    {
        hotkeys.restoreWindow();
        REQUIRE(mainWindow.isShown);
    }
}
