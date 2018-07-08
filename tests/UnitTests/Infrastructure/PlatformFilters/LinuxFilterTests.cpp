#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/LinuxFilter.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("LinuxFilterTests")
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    GIVEN("the test runs on GNU/Linux")
    {
        WHEN("not in an AppImage")
        {
            qputenv("APPIMAGE", "");
            LinuxFilter filter;

            THEN("match returns true")
            {
                REQUIRE(filter.match());
            }
        }

        AND_WHEN("in an AppImage")
        {
            qputenv("APPIMAGE", "/path/to/appimage");
            LinuxFilter filter;

            THEN("match returns false")
            {
                REQUIRE(!filter.match());
            }
            qputenv("APPIMAGE", "");
        }
    }
#else
    GIVEN("the test does not run on GNU/Linux")
    {
        WHEN("using LinuxFilter")
        {
            LinuxFilter filter;

            THEN("match returns false")
            {
                REQUIRE(!filter.match());
            }
        }
    }
#endif
}
