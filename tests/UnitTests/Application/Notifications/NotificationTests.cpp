#include <catch.hpp>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)

TEST_CASE("NotificationTests", "[UnitTest]") {
    Notification notification1 { "title", "message", "", NotificationType::NewSong };
    Notification sameAsnotification1 { "title", "message", "", NotificationType::NewSong };
    Notification notification2 { "title2", "message2", "", NotificationType::Paused };

    SECTION("toString") {
        REQUIRE(notification1.toString() == "title - message");
    }

    SECTION("equality operator") {
        REQUIRE(notification1 != notification2);
        REQUIRE(notification1 == sameAsnotification1);
    }
}