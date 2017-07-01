#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Infrastructure/Controllers/HotkeysController.hpp>
#include <Mocks/PlayerMock.hpp>
#include "DI.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("HotkeysServiceTests", "[UnitTest]") {
    auto playerMock = PlayerMock::get();
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    HotkeysController hotkeys(playerMock.get(), settings);
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
}
