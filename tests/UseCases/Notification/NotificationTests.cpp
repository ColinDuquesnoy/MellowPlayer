#include <catch.hpp>
#include <MellowPlayer/UseCases.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)

TEST_CASE("NotificationTests") {
    Notification notification { "title", "message", "", NotificationType::Song };

    REQUIRE(notification.toString() == "title - message");
}