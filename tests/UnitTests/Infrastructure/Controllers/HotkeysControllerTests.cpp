#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Infrastructure/Controllers/HotkeysController.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

TEST_CASE("HotkeysServiceTests", "[UnitTest]") {
    auto playerMock = PlayerMock::get();
    auto mainWindowMock = MainWindowMock::get();
    Tests::DependencyPool pool;
    Settings& settings = pool.getSettings();
    HotkeysController hotkeys(playerMock.get(), settings, mainWindowMock.get());
    hotkeys.start();

    SECTION("togglePlayPause") {
        hotkeys.togglePlayPause();
        Verify(Method(playerMock, togglePlayPause)).Exactly(1);
    }

    SECTION("next") {
        hotkeys.next();
        Verify(Method(playerMock, next)).Exactly(1);
    }

    SECTION("previous") {
        hotkeys.previous();
        Verify(Method(playerMock, previous)).Exactly(1);
    }

    SECTION("toggleFavoriteSong") {
        hotkeys.toggleFavoriteSong();
        Verify(Method(playerMock, toggleFavoriteSong)).Exactly(1);
    }

    SECTION("toggleFavoriteSong") {
        hotkeys.restoreWindow();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }
}
