#include <catch.hpp>
#include <MellowPlayer/Entities/Notifications.hpp>
#include <MellowPlayer/Infrastructure/Configuration/QSettingsProvider.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("ApplicationSettingsTests") {
    QSettingsProvider applicationSettings;

    SECTION("currentService") {
        SECTION("defaultValue") {
            REQUIRE(applicationSettings.getCurrentService().isEmpty());
        }

        SECTION("change current service") {
            applicationSettings.setCurrentService("Foo");
            REQUIRE(applicationSettings.getCurrentService() == "Foo");
        }
    }

    SECTION("trayIcon") {
        SECTION("defaultValue") {
            REQUIRE(applicationSettings.getTrayIcon().isEmpty());
        }

        SECTION("change tray icon") {
            applicationSettings.setTrayIcon("foo");
            REQUIRE(applicationSettings.getTrayIcon() == "foo");
        }
    }

    SECTION("getShowCloseToSysemTrayMessage") {
        SECTION("defaultValue") {
            REQUIRE(applicationSettings.getShowCloseToSysemTrayMessage());
        }

        SECTION("change getShowCloseToSysemTrayMessage") {
            applicationSettings.setShowCloseToSystemTrayMessage(false);
            REQUIRE(!applicationSettings.getShowCloseToSysemTrayMessage());
        }
    }

    SECTION("custom value") {
        applicationSettings.setValue("foo", "bar");
        REQUIRE(applicationSettings.getValue("foo").toString() == "bar");
    }

    applicationSettings.clear();
}