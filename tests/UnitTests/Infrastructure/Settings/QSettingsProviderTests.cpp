#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("QSettingsStoreTests")
{
    QSettingsStore qSettingsStore;
    qSettingsStore.setOrganizationName("MellowPlayer.Tests");

    SECTION("defaultValue")
    {
        REQUIRE(qSettingsStore.value("foo", "fooBar").toString() == "fooBar");
    }

    SECTION("setValue")
    {
        qSettingsStore.setValue("foo", "bar");
        REQUIRE(qSettingsStore.value("foo").toString() == "bar");
    }

    qSettingsStore.clear();
}
