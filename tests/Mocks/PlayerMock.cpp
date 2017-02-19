#include "PlayerMock.hpp"

fakeit::Mock<IPlayer> PlayerMock::basicMock() {
    Mock<IPlayer> mock;
    When(Method(mock, togglePlayPause)).AlwaysReturn();
    When(Method(mock, next)).AlwaysReturn();
    When(Method(mock, previous)).AlwaysReturn();
    When(Method(mock, toggleFavoriteSong)).AlwaysReturn();
    return mock;
}
