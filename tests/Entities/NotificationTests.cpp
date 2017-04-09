#include <catch.hpp>
#include <MellowPlayer/Entities/Notifications.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)

TEST_CASE("NotificationTests", "[UnitTest]") {
    Notification notification1 { "title", "message", "", NotificationType::Song };
    Notification sameAsnotification1 { "title", "message", "", NotificationType::Song };
    Notification notification2 { "title2", "message2", "", NotificationType::Paused };

    REQUIRE(notification1.toString() == "title - message");

    REQUIRE(notification1 != notification2);
    REQUIRE(notification1 == sameAsnotification1);
}