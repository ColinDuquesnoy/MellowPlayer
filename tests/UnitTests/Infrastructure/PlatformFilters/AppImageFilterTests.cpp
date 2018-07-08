#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/AppImageFilter.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("AppImageFilterTests")
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    GIVEN("the test runs on GNU/Linux")
    {
        WHEN("in an AppImage")
        {
            qputenv("APPIMAGE", "/path/to/appimage");
            AppImageFilter filter;

            THEN("match returns true")
            {
                REQUIRE(filter.match());
            }
            qputenv("APPIMAGE", "");
        }

        AND_WHEN("not in an AppImage")
        {
            qputenv("APPIMAGE", "");
            AppImageFilter filter;

            THEN("match returns false")
            {
                REQUIRE(!filter.match());
            }
        }
    }
#else
    GIVEN("the test does not run on GNU/Linux")
    {
        WHEN("using AppImageFilter")
        {
            AppImageFilter filter;

            THEN("match returns false")
            {
                REQUIRE(!filter.match());
            }
        }
    }
#endif
}
