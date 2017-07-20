#include <catch.hpp>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("QSettingsProviderTests") {
    QSettingsProvider settingsProvider;

    SECTION("defaultValue") {
        REQUIRE(settingsProvider.getValue("foo", "fooBar").toString() == "fooBar");
    }

    SECTION("setValue") {
        settingsProvider.setValue("foo", "bar");
        REQUIRE(settingsProvider.getValue("foo").toString() == "bar");
    }

    settingsProvider.clear();
}