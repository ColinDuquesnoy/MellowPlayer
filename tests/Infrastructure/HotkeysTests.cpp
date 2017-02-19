#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Infrastructure/Hotkeys.hpp>
#include <Mocks/PlayerMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("HotkeysTests") {
    auto playerMock = PlayerMock::get();
    Hotkeys hotkeys(playerMock.get());

    SECTION("togglePlayPause_Test") {
        hotkeys.togglePlayPause();
        Verify(Method(playerMock, togglePlayPause)).Exactly(1);
    }

    SECTION("next_Test") {
        hotkeys.next();
        Verify(Method(playerMock, next)).Exactly(1);
    }

    SECTION("previous_Test") {
        hotkeys.previous();
        Verify(Method(playerMock, previous)).Exactly(1);
    }

    SECTION("toggleFavoriteSong_Test") {
        hotkeys.toggleFavoriteSong();
        Verify(Method(playerMock, toggleFavoriteSong)).Exactly(1);
    }
}
