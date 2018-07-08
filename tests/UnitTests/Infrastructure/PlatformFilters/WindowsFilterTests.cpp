#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/WindowsFilter.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("WindowsFilterTests")
{
    GIVEN("a WindowsFilter instance")
    {
        WindowsFilter filter;

#ifdef Q_OS_WIN
        WHEN("on Windows")
        {
            THEN("match always returns true")
            {
                REQUIRE(filter.match());
            }
        }
#else
        WHEN("not on Windows")
        {
            THEN("match always returns false")
            {
                REQUIRE(!filter.match());
            }
        }
#endif
    }
}
