#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Platform/Filters/AllFilter.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("AllFilterTests")
{
    GIVEN("an AllFilter instance")
    {
        AllFilter filter;

        WHEN("on any platform")
        {
            THEN("match always returns true")
            {
                REQUIRE(filter.match());
            }
        }
    }
}