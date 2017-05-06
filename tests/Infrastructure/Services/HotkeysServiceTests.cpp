#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Infrastructure/Services/HotkeysService.hpp>
#include <Mocks/PlayerMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("HotkeysServiceTests", "[UnitTest]") {
    auto playerMock = PlayerMock::get();
    HotkeysService hotkeys(playerMock.get());
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
