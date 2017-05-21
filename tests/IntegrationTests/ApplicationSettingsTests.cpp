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

    SECTION("defaultValue") {
        REQUIRE(applicationSettings.getValue("foo", "fooBar").toString() == "fooBar");
    }

    SECTION("setValue") {
        applicationSettings.setValue("foo", "bar");
        REQUIRE(applicationSettings.getValue("foo").toString() == "bar");
    }

    applicationSettings.clear();
}