#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("QSettingsProviderTests")
{
    QSettingsProvider settingsProvider;

    SECTION("defaultValue")
    {
        REQUIRE(settingsProvider.value("foo", "fooBar").toString() == "fooBar");
    }

    SECTION("setValue")
    {
        settingsProvider.setValue("foo", "bar");
        REQUIRE(settingsProvider.value("foo").toString() == "bar");
    }

    settingsProvider.clear();
}