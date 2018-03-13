#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/OsxFilter.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("OsxFilterTests")
{
    GIVEN("an OsxFilter instance")
    {
        OsxFilter filter;

#ifdef Q_OS_OSX
        WHEN("on OSX")
        {
            THEN("match always returns true")
            {
                REQUIRE(filter.match());
            }
        }
#else
        WHEN("not on OSX")
        {
            THEN("match always returns false")
            {
                REQUIRE(!filter.match());
            }
        }
#endif
    }
}
